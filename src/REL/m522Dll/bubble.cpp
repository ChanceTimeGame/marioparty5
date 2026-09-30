#include "REL/m522Dll/bubble.h"
#include "REL/m522Dll/fire.h"
#include "REL/m522Dll/stage.h"
#include "REL/m522Dll/player.h"
#include "REL/mgcpp/random.h"
extern "C" {
/* actman.h does not declare it (as include/REL/m520Dll.h) */
void MgActorPosGet(MGACTOR* actorP, HuVecF* pos);
void GXSetVtxAttrFmtv(GXVtxFmt vtxfmt, GXVtxAttrFmtList* list);
}

namespace m522 {

/* a = 2pi/3 * rand; three points (200 sin a, 2500, 200 cos a) on the spawn circle, a += 2pi/3 */
CBubbleMan::CBubbleMan() : m_count(0)
{
    double a = (2.0 * M_PI / 3.0) * CRandom::randomMantissa();
    Vec p;
    p.y = 2500.0f;
    for (int i = 0; i < 3; i++, a += 2.0 * M_PI / 3.0) {
        p.x = 200.0 * sin(a);
        p.z = 200.0 * cos(a);
        m_points.insert(m_points.end(), 1, p);
    }
}

CBubbleMan::~CBubbleMan() {}

void CBubbleMan::Spawn()
{
    if (m_points.size()) {
        u32 i = CRandom::irandom() % m_points.size();
        CBubble* b = new CBubble(&m_points[i], m_count + 4);
        int h = b->GetHandle();
        m_handles.insert(m_handles.end(), 1, h);
        Vec* used = &m_points[i]; /* retail: at() a second time (4EC0), through a pointer temporary */
        m_points.erase(used);
        m_count++;
    }
}

/* vector<int> begin()/end() as raw pointers: retail copies each one temporary more than the in-tree <vector>
 * gives (GetHandles 4EFC) -- m532 man_map.cpp's VecBegin shape (CW only: the host walk uses iterators) */
template <class T> inline T* VecBegin(std::vector<T>& v)
{
    return (T*)v.begin();
}
template <class T> inline T* VecEnd(std::vector<T>& v)
{
    return (T*)v.end();
}

std::vector<int>* CBubbleMan::GetHandles()
{
    int* it = VecBegin(m_handles);
    int* end = VecEnd(m_handles);
    for (; it != end; ++it) {
        if (!CSunFireObj::GetHandlePtr(*it)) {
            m_handles.erase(it);
        }
    }
    return &m_handles;
}

Vec* CBubble::GetPos(Vec* out)
{
    Vec p;
    MgActorPosGet(m_actor, &p);
    *out = p;
    return out;
}

/* the spawn position goes through a double-parameter setter (retail: lfs; frsp; stfs, sheet §2.6) */
static inline void SetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

CBubble::CBubble(Vec* pos, int id)
    : m_proc(&CBubble::procMain), m_light(Hu3DGLightCreate(pos->x, pos->y, pos->z, 0.0f, 0.0f, 1.0f, 0xFF, 0xA0, 0x00)),
      m_model(new CModel(0x50000Cu)), m_dead(false), m_wasLanded(true), m_scale(1.0f), m_alpha(0), m_unk44(0),
      m_frame(0)
{
    setLayer(6);
    Hu3DGLightStaticSet((s16)m_light, TRUE);
    Hu3DGLightPointSet((s16)m_light, 20.0f, 0.99f, GX_DA_STEEP);
    MGACTOR_PARAM param = { 40.0f, 20.0f, 0, 1, NULL, 0, 0, NULL };
    param.param = id;
    m_actor = MgActorCreate(&param, m_model->id());
    MgActorColAttrSet(m_actor, 0x100);
    m_actor->gravity = 75.0f;
    m_model->setLayer(6);
    m_model->setAttr(HU3D_MOTATTR_LOOP);
    SetVec(&m_spawn, pos->x, pos->y, pos->z);
    Respawn();
    m_actor->rotY = 0.0f;
}

CBubble::~CBubble()
{
    MgActorKill(m_actor);
    Hu3DGLightKill((s16)m_light);
}

void CBubble::Respawn()
{
    MgActorPosUpdate(m_actor, &m_spawn);
    m_unk44 = (int)(600.0 * CRandom::randomMantissa());
}

/* the glow fades out over the 1000 units above the tower top; a landing (not landed -> landed) bursts */
void CBubble::update()
{
    (this->*m_proc)();
    if (m_dead) {
        delete this;
        return;
    }
    UpdateLight();
    float y = m_actor->pos.y;
    float t = (y - CStage::GetInstance()->GetTopY()) / 1000.0f;
    float c;
    if (t < 0.0f) {
        c = 0.0f;
    } else if (t > 1.0f) {
        c = 1.0f;
    } else {
        c = t;
    }
    m_alpha = 255.0 * (1.0 - c); /* double -> u8 directly (no clrlwi) */
    bool land = IsLanded();
    if (!m_wasLanded && land) {
        Burst(0x40);
        m_scale = 0.6f;
        Vec p;
        GetPos(&p);
        HuAudFXPlayPan(0x745, GetPan(&p));
    }
    m_wasLanded = land; /* retail: clrlwi; stb -- a u8 member (bool -> u8); the proven layout keeps bool (OUT.md) */
    m_frame++;
}

void CBubble::procMain()
{
    if (CStage::GetInstance()->GetBlocksLeft() <= 0) {
        onFinish();
    }
    if (IsLanded() && CStage::GetInstance()->IsDropDone()) {
        MgActorColAttrReset(m_actor, 4);
    } else {
        MgActorColAttrSet(m_actor, 4);
    }
    Vec p;
    MgActorPosGet(m_actor, &p);
    if (p.x > 1000.0f) {
        Respawn();
    }
    if (m_scale < 1.0f) {
        m_scale += 0.02;
        Hu3DModelScaleSet((s16)m_actor->mdlId, 1.0f, m_scale, 1.0f);
    }
}

void CBubble::onFinish()
{
    MgActorColAttrSet(m_actor, 4);
}

/* a pointer through a local (m532 VecUnit): retail's `addi r29; mr r30,r29` pointer temporaries */
static inline void VecUnit(Vec* v)
{
    Vec* u = v;
    PSVECNormalize(u, u);
}

/* the light sits on the bubble and points at the camera. The actor position is read into a temporary first
 * (retail: the temporary is the frame's highest slot, above `pos`) */
void CBubble::UpdateLight()
{
    Vec tmp;
    MgActorPosGet(m_actor, &tmp);
    Vec pos;
    pos = tmp;
    Vec target;
    Vec eye;
    Vec up;
    Hu3DCameraPosGet(1, &eye, &up, &target);
    PSVECSubtract(&eye, &target, &target);
    Vec* dir = &target;
    VecUnit(dir);
    Hu3DGLightPosSetV((s16)m_light, &pos, &target);
}

/* unreferenced: shrink away once landed; the only m_dead = 1 */
void CBubble::procSink()
{
    if (IsLanded()) {
        Hu3DModelScaleSet((s16)m_actor->mdlId, m_scale, m_scale, m_scale);
        Vec p;
        MgActorPosGet(m_actor, &p);
        if ((m_scale -= 1.0 / 60.0) <= 0.0f || p.x > 1000.0f) {
            m_dead = true;
        }
    }
}

bool CBubble::IsLanded()
{
    return m_actor->colGroundAttr & 0x407F; /* int -> bool (retail's closing clrlwi) */
}

void CBubble::Burst(int n)
{
    Vec p;
    p = m_actor->pos;
    new CFlare(&p, 200.0f, 2.0f, n);
}

void CBubble::draw(Mtx* mtx)
{
    if (m_scale <= 0.0f || m_alpha == 0) {
        return;
    }
    SetupDraw(mtx);
    DrawDisk();
}

/* s = scale (60 + 5 sin(2pi frame / 48)); the disk sits 0.5 above the tower top under the bubble; unlit vertex
 * colour, C = RASC, A = RASA * A0 (TEVREG0.a = the glow alpha), additive (SRCALPHA, ONE), z test without update */
void CBubble::SetupDraw(Mtx* mtx)
{
    Mtx m;
    Vec p;
    MgActorPosGet(m_actor, &p);
    float s = m_scale * (60.0 + 5.0 * sin(2.0 * M_PI * m_frame / 48.0));
    PSMTXScale(m, s, 1.0f, s);
    PSMTXTransApply(m, m, p.x, CStage::GetInstance()->GetTopY() + 0.5, p.z);
    PSMTXConcat(*mtx, m, m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTexGens(0);
    GXColor c = { 0, 0, 0, 0 };
    c.a = (u8)m_alpha; /* retail: lbz; clrlwi */
    GXSetTevColor(GX_TEVREG0, c);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_A0, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetCullMode(GX_CULL_NONE);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetZCompLoc(GX_TRUE);
    GXSetZMode(GX_TRUE, GX_LESS, GX_FALSE);
    GXSetAlphaCompare(GX_ALWAYS, 255, GX_AOP_OR, GX_ALWAYS, 255);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
}

#define DISK_ALIGNED(decl) static const decl ATTRIBUTE_ALIGN(32)
void CBubble::DrawDisk()
{
    static const GXVtxDescList diskDesc[] = {
        { GX_VA_POS, GX_INDEX8 },
        { GX_VA_CLR0, GX_INDEX8 },
        { GX_VA_NULL, GX_NONE },
    };
    static const GXVtxAttrFmtList diskFmt[] = {
        { GX_VA_POS, GX_POS_XYZ, GX_S8, 6 },
        { GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA4, 0 },
        { GX_VA_NULL, GX_POS_XY, GX_U8, 0 },
    };
    DISK_ALIGNED(s8 diskPos[13][3]) = {
        { 0, 0, 0 }, { 0, 0, 64 }, { 31, 0, 55 }, { 55, 0, 32 }, { 64, 0, 0 }, { 55, 0, -31 }, { 31, 0, -55 },
        { 0, 0, -64 }, { -31, 0, -55 }, { -55, 0, -32 }, { -64, 0, 0 }, { -55, 0, 32 }, { -32, 0, 55 },
    };
    DISK_ALIGNED(u8 diskColor[2][2]) = { { 0xFC, 0x0F }, { 0xF0, 0x00 } };
    DISK_ALIGNED(u8 diskList[32]) = {
        0xA0, 0x00, 0x0E, 0, 0, 1, 1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7, 1, 8, 1, 9, 1, 10, 1, 11, 1, 12, 1, 1, 1, 0,
    };
    GXClearVtxDesc();
    GXSetVtxDescv((GXVtxDescList*)diskDesc);
    GXSetVtxAttrFmtv(GX_VTXFMT0, (GXVtxAttrFmtList*)diskFmt);
    GXSetArray(GX_VA_POS, diskPos, 3);
    GXSetArray(GX_VA_CLR0, diskColor, 2);
    GXCallDisplayList((void*)diskList, sizeof(diskList));
}
#undef DISK_ALIGNED

} // namespace m522

template <> m522::CStage* CSingleton<m522::CStage>::ms_pointer = 0;
template <> m522::CBubbleMan* CSingleton<m522::CBubbleMan>::ms_pointer = 0;
