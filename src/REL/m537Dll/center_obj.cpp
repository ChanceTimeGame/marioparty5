#include "REL/m537Dll/center_obj.h"
#include "REL/m537Dll/player.h"
#include "REL/m537Dll/water.h"

extern "C" {
void HuSprTexLoad(ANIMDATA* anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);
}

namespace m537 {

static TLinkList<CRope> s_ropeList; /* bss A5C (DestructorChain A50) */

/* lbl_1_rodata_528: the four rope anchors */
static const Vec s_anchor[CCenterObj::NUM_ROPE] = {
    { -250.0f, 1050.0f, -250.0f }, { 250.0f, 1050.0f, -250.0f }, { -250.0f, 1050.0f, 250.0f }, { 250.0f, 1050.0f, 250.0f }
};

/* m513 player's copy helper: the ctor's pos = target goes through two inline pointer copies */
static inline Vec& SetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
    return *v;
}

static inline Vec& SetVec(Vec* d, const Vec& s)
{
    d->x = s.x;
    d->y = s.y;
    d->z = s.z;
    return *d;
}

CCenterObj::CCenterObj() : CModel(0x5F000Au), m_released(0)
{
    setLayer(5);
    setAttr(0x40000001);
    SetVec(&m_pos, SetVec(&m_target, 0.0f, 1050.0f, 0.0f));
    setPos(&m_pos);
    m_vel.x = 0.0f;
    m_vel.y = 0.0f;
    m_vel.z = 0.0f;
    for (int i = 0; i < NUM_ROPE; i++) {
        m_rope[i].reset(new CRope(i, &s_anchor[i]));
    }
}

CCenterObj::~CCenterObj() {}

const Vec* CCenterObj::GetPos()
{
    return &m_pos;
}

CRope* CCenterObj::GetRope(int i)
{
    return m_rope[i].get();
}

void CCenterObj::Release()
{
    m_released = 1;
}

/* the 0.9 / 0.1 smoothing (double; retail's register copies of the arguments and the result show an inline) */
static inline float Smooth(float cur, float target)
{
    return 0.9 * cur + 0.1 * target;
}

void CCenterObj::Update()
{
    if (!m_released) {
        CPlayer::GetCenter(&m_target);
    } else {
        PSVECAdd(&m_vel, &m_target, &m_target);
        m_vel.y -= 0.27240694f;
    }
    float oldY = m_pos.y;
    m_pos.x = Smooth(m_pos.x, m_target.x);
    m_pos.y = Smooth(m_pos.y, m_target.y);
    m_pos.z = Smooth(m_pos.z, m_target.z);
    setPos(&m_pos);
    if (oldY > 0.0f && m_pos.y <= 0.0f) {
        setLayer(2);
        new CSplashModel(&m_pos);
        new CSplash(&m_pos);
    }
}

void CCenterObj::Exec()
{
    CSingleton<CCenterObj>::GetInstance()->Update();
    TLinkList<CRope>::exec(&s_ropeList, CRope::UpdateFunc);
}

void CRope::UpdateFunc(CRope* r)
{
    r->Update();
}

void CRope::Hook(HU3DMODEL* model, Mtx* mtx)
{
    CRope* self = (CRope*)model->hookData;
    self->Draw(mtx);
}

CRope::CRope(int idx, const Vec* anchor)
    : CModel(Hook), m_num(NUM_NODE), m_segLen(24.0f), m_node(m_num), m_started(0)
{
    insertBack(&s_ropeList);
    setLayer(5);
    setHookData(this);
    LoadTex(idx);
    Layout(anchor);
}

CRope::~CRope() {}

void CRope::Reset(const Vec* anchor)
{
    Layout(anchor);
    m_started = 0;
}

/* lbl_1_rodata_57C */
static const u32 s_texId[CCenterObj::NUM_ROPE] = { 0x5F000B, 0x5F000C, 0x5F000D, 0x5F000E };

void CRope::LoadTex(int idx)
{
    u32 dataNum = s_texId[idx];
    m_anim = HuSprAnimRead(HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
}

/* PSVEC helpers returning their output (retail hands the result on through register copies: inlines) */
static inline Vec* VecSub(const Vec* a, const Vec* b, Vec* d)
{
    PSVECSubtract((Vec*)a, (Vec*)b, d);
    return d;
}

static inline Vec* Normalize(Vec* v)
{
    PSVECNormalize(v, v);
    return v;
}

static inline float VecDot(const Vec* a, const Vec* b)
{
    return PSVECDotProduct((Vec*)a, (Vec*)b);
}

/* bend c around b to at most maxAng from the a-b direction, at distance len from b */
void CRope::LimitBend(const Vec* a, const Vec* b, Vec* c, float len, float maxAng)
{
    Mtx m;
    Vec d1;
    Vec d2;
    Vec axis;
    Normalize(VecSub(b, a, &d1));
    Normalize(VecSub(c, b, &d2));
    float dot = VecDot(&d1, &d2);
    /* const: otherwise the inlined fabs keeps register copies where LimitBend is inlined into Update */
    const float ang = acos(dot);
    if (fabs(ang) > maxAng) {
        PSVECCrossProduct(&d1, &d2, &axis);
        PSMTXRotAxisRad(m, &axis, maxAng - ang);
        PSMTXMultVec(m, &d2, &d2);
    }
    PSVECScale(&d2, &d2, len);
    PSVECAdd((Vec*)b, &d2, c);
}

/* element i: retail indexes vector<Node> / vector<Vec> unchecked, straight off the data pointer (an inline
 * returning the element: data + i, the reference spilled) -- not MSL's at()-calling operator[] (there is no
 * at<Node> / at<Vec> in retail). The host's std::vector has no data_: operator[] */
template <class T> static inline T& VecAt(std::vector<T>& v, int i)
{
#ifdef __MWERKS__
    return v.data_.first()[i];
#else
    return v[i];
#endif
}

/* the Verlet step: pin nodes 0 / 1 to the centre object, integrate the rest, limit the bends, settle */
void CRope::Update()
{
    if (!m_started) {
        m_started = 1;
        return;
    }
    Vec c = *CSingleton<CCenterObj>::GetInstance()->GetPos();
    VecAt(m_node, 0).Set(&c);
    PSVECAdd(&m_dir, &c, &c);
    VecAt(m_node, 1).Set(&c);
    std::vector<Node>::iterator it;
    for (it = m_node.begin() + 2; it != m_node.end(); it++) {
        it->Integrate();
    }
    for (it = m_node.begin(); it != m_node.end() - 2; it++) {
        LimitBend(&it[0].pos, &it[1].pos, &it[2].pos, m_segLen, 0.5235988f);
    }
    for (it = m_node.begin() + 2; it != m_node.end(); it++) {
        it->Settle();
    }
}

void Node::Set(const Vec* p)
{
    pos = *p;
    prev = *p;
    vel.x = 0.0f;
    vel.y = 0.0f;
    vel.z = 0.0f;
}

void Node::Integrate()
{
    PSVECAdd(&vel, &pos, &pos);
    pos.y -= 0.8172208f;
}

void Node::Settle()
{
    PSVECSubtract(&pos, &prev, &vel);
    PSVECScale(&vel, &vel, 0.8f);
    prev = pos;
}

/* (1 - t) a + t b in double (the arguments and the result pass through register copies: an inline) */
static inline float Lerp(float a, float b, double t)
{
    return (1.0 - t) * a + t * b;
}

static inline Vec* Scale(Vec* v, float s)
{
    PSVECScale(v, v, s);
    return v;
}

static inline Vec* VecLerp(Vec* out, const Vec* a, const Vec* b, double t)
{
    out->x = Lerp(a->x, b->x, t);
    out->y = Lerp(a->y, b->y, t);
    out->z = Lerp(a->z, b->z, t);
    return out;
}

/* a straight line of nodes from the centre object to the anchor; m_dir = the first segment (30 long) */
void CRope::Layout(const Vec* anchor)
{
    Vec p;
    Vec c = *CSingleton<CCenterObj>::GetInstance()->GetPos();
    PSVECSubtract((Vec*)anchor, &c, &m_dir);
    Scale(Normalize(&m_dir), 30.0f);
    for (int i = 0; i < m_num; i++) {
        float t = (float)i / (float)(m_num - 1);
        VecAt(m_node, i).Set(VecLerp(&p, &c, anchor, t));
    }
}

void CRope::Draw(Mtx* mtx)
{
    SetupGX(mtx);
    DrawRibbon();
}

/* textured, alpha-tested, depth-writing, direct POS / TEX0 (F32) */
void CRope::SetupGX(Mtx* mtx)
{
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXSetNumChans(0);
    HuSprTexLoad(m_anim, 0, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetCullMode(GX_CULL_NONE);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetZCompLoc(GX_FALSE);
    GXSetZMode(GX_TRUE, GX_LESS, GX_TRUE);
    GXSetAlphaCompare(GX_GEQUAL, 0xC0, GX_AOP_AND, GX_LEQUAL, 0xFF);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
}

/* retail copies the result into a register first (an inline) */
static inline float SquareMag(const Vec* v)
{
    return PSVECSquareMag((Vec*)v);
}

void CRope::RibbonSide(const Vec* eye, const Vec p[3], Vec out[2], float w)
{
    Vec a;
    Vec b;
    PSVECSubtract((Vec*)&p[1], (Vec*)&p[0], &a);
    PSVECSubtract((Vec*)&p[2], (Vec*)&p[1], &b);
    if (SquareMag(&a) <= 0.0f) {
        SetVec(&a, b);
    } else if (SquareMag(&b) <= 0.0f) {
        SetVec(&b, a);
    }
    Normalize(&a);
    Normalize(&b);
    PSVECAdd(&b, &a, &a);
    PSVECSubtract((Vec*)&p[1], (Vec*)eye, &b);
    PSVECCrossProduct(&b, &a, &a);
    Scale(Normalize(&a), w);
    PSVECAdd((Vec*)&p[1], &a, &out[0]);
    PSVECSubtract((Vec*)&p[1], &a, &out[1]);
}

static inline int Clamp(int v, int lo, int hi)
{
    if (v < lo) {
        return lo;
    } else if (v > hi) {
        return hi;
    } else {
        return v;
    }
}

void CRope::DrawRibbon()
{
    std::vector<Vec> side(2 * m_num);
    Vec eye;
    Vec target;
    Vec up;
    Hu3DCameraPosGet(1, &eye, &up, &target);
    for (int i = 0; i < m_num; i++) {
        int i0 = Clamp(i - 1, 0, m_num - 1);
        int i1 = Clamp(i, 0, m_num - 1);
        int i2 = Clamp(i + 1, 0, m_num - 1);
        /* non-constant aggregate: CW copies a zero template (rodata 5B8), then stores each element */
        Vec p[3] = { VecAt(m_node, i0).pos, VecAt(m_node, i1).pos, VecAt(m_node, i2).pos };
        RibbonSide(&eye, p, &VecAt(side, 2 * i), 9.0f);
    }
    for (int i = 0; i < m_num - 1; i++) {
        Vec* v0 = &VecAt(side, 2 * i);
        Vec* v1 = &VecAt(side, 2 * i + 1);
        Vec* v2 = &VecAt(side, 2 * i + 2);
        Vec* v3 = &VecAt(side, 2 * i + 3);
        float s0 = i == m_num - 2 ? 0.6 : 0.2;
        float s1 = s0 + 0.4;
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
        GXPosition3f32(v0->x, v0->y, v0->z);
        GXTexCoord2f32(s0, 0.0f);
        GXPosition3f32(v1->x, v1->y, v1->z);
        GXTexCoord2f32(s0, 1.0f);
        GXPosition3f32(v2->x, v2->y, v2->z);
        GXTexCoord2f32(s1, 0.0f);
        GXPosition3f32(v3->x, v3->y, v3->z);
        GXTexCoord2f32(s1, 1.0f);
        GXEnd();
    }
}

} // namespace m537
