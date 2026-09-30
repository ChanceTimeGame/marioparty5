#include "REL/m568Dll/stage.h"
#include "REL/m568Dll/octtree.h"
#include "REL/m568Dll/heiho.h"

namespace m568 {

/* Vec setter with DOUBLE components (m501/m539 player.h's SetVec): retail stores the non-constant components with
 * `frsp; stfs` (SnapToGround's ray ends). File-local: no m568 header carries one. */
inline Vec& SetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
    return *v;
}

/* lbl_1_rodata_258: the course's downhill direction (0, -sin 60, -cos 60) */
static const Vec s_gravityDir = { 0.0f, -0.8660254f, -0.5f };
/* lbl_1_rodata_264 / 294: the obstacles, kind 1 (4) and kind 0 (7) */
static const Vec s_obstacle1[4] = {
    { 425.0f, 0.0f, -12500.0f }, { -425.0f, 0.0f, -14500.0f }, { 5.0f, 0.0f, -15000.0f }, { 425.0f, 0.0f, -18000.0f },
};
static const Vec s_obstacle0[7] = {
    { 5.0f, 0.0f, -7500.0f }, { -425.0f, 0.0f, -8000.0f }, { 5.0f, 0.0f, -11000.0f }, { -425.0f, 0.0f, -16500.0f },
    { -425.0f, 0.0f, -19000.0f }, { 375.0f, 0.0f, -22500.0f }, { 5.0f, 0.0f, -25000.0f },
};

void CStage::GetGravityDir(Vec* out)
{
    *out = s_gravityDir;
}

void CStage::GetGravity(Vec* out, float mass)
{
    float g = (1.0 / 3600.0) * (9.80665f * (100.0f * mass));
    PSVECScale(&s_gravityDir, out, g);
}

/* retail's clamp: an inline whose bound expressions are re-evaluated for the result */
inline float StageClamp(float v, float lo, float hi)
{
    if (v < lo) {
        return lo;
    }
    if (v > hi) {
        return hi;
    }
    return v;
}

/* x into [-800 + r, 800 - r], z into the scroll window [s + 400 + r, s + 2200 - r] */
void CStage::ClampToCourse(Vec* p, float r)
{
    CStage* stage = GetInstance();
    float s = stage->GetScrollZ();
    p->x = StageClamp(p->x, -800.0f + r, 800.0f - r);
    p->z = StageClamp(p->z, r + (400.0f + s), 2200.0f + s - r);
}

/* p's position in the course window, each axis in [-1, 1] (not clamped), y = 0 */
void CStage::GetNormPos(Vec* out, const Vec* p, float r)
{
    CStage* stage = GetInstance();
    float s = stage->GetScrollZ();
    float d = 2.0f * r;
    out->x = -1.0f + (p->x - (-800.0f + r)) / ((1600.0f - d) / 2.0f);
    out->y = 0.0f;
    out->z = -1.0f + (p->z - (r + (400.0f + s))) / ((1800.0f - d) / 2.0f);
}

void CStage::SetShadowReceiver(s16 id)
{
    Hu3DModelShadowMapSet(id);
    Hu3DModelShadowDispOn(id);
    Hu3DModelLayerSet(id, 0);
}

/* lbl_1_bss_A60: the light direction (-normalize(s_lightPos)), written by the ctor */
static Vec s_lightDir;
/* lbl_1_data_464 / 470: the light (non-const: their addresses go to PSVECNormalize / Hu3DGLightCreateV) */
static Vec s_lightPos = { -9654.0f, 8151.0f, 2774.0f };
static GXColor s_white = { 255, 255, 255, 255 };

CStage::CStage()
    : m_model(new CModel(0x7B0000u)), m_model2(new CModel(0x7B0001u)), m_model3(0), m_archive(0), m_heiho(0)
{
    Hu3DLighInit();
    PSVECNormalize(&s_lightPos, &s_lightDir);
    PSVECScale(&s_lightDir, &s_lightDir, -1.0f);
    int light = Hu3DGLightCreateV(&s_lightPos, &s_lightDir, &s_white);
    Hu3DGLightInfinitytSet(light);
    Hu3DShadowCreate(30.0f, 20.0f, 25000.0f);
    SetShadowReceiver(m_model.get()->id());
    LoadCollision();
    CreateObstacles(0, s_obstacle0, 7);
    CreateObstacles(1, s_obstacle1, 4);
    m_frame = 0;
    setState(&CStage::stateNone);
}

void CStage::stateNone() {}

/* retail reaches Raycast through an inline taking the interface by reference: no null check on the base
 * conversion (SKELETON §5.4) and the bool result copied once more (SnapToGround D690) */
inline bool StageRay(ICollision& c, Vec* out, const Vec* from, const Vec* to)
{
    return c.Raycast(out, from, to);
}

bool CStage::SnapToGround(Vec* p)
{
    CStage* stage = GetInstance();
    Vec from;
    Vec to;
    SetVec(&from, p->x, 5000.0f, p->z);
    SetVec(&to, p->x, -5000.0f, p->z);
    /* retail converts to the ICollision base with no null check (SKELETON §5.4): a reference conversion */
    bool hit = StageRay(*stage, p, &from, &to);
    if (!hit) {
        p->y = 0.0f;
    }
    return hit;
}

void CStage::CreateObstacles(int kind, const Vec* pos, int n)
{
    for (int i = 0; i < n; i++) {
        new CObstacle(kind, &pos[i]);
    }
}

/* retail reads each archive entry through an inline (every result lands in its own register first) */
template <class T>
inline T* ArcGet(IArchive* arc, const char* name)
{
    return (T*)arc->GetData(name);
}
template <class T>
inline T ArcGetValue(IArchive* arc, const char* name)
{
    return *(T*)arc->GetData(name);
}

void CStage::LoadCollision()
{
    m_archive.reset(new CArchive(0x7B0002));
    IArchive* arc = m_archive.get();
    m_triTable = ArcGet<Tri>(arc, "TriangleTable");
    m_triCount = ArcGetValue<s32>(arc, "TriangleCount");
    m_vtxTable = ArcGet<Vec>(arc, "VertexTable");
    m_vtxCount = ArcGetValue<s32>(arc, "VertexCount");
    m_octTable = ArcGet<OctNode>(arc, "OctTable");
    m_triIdx = ArcGet<u16>(arc, "TriIdxTable");
    Hu3DShadowTPLvlSet(0.8f);
    RelocateOctree(m_octTable, ArcGetValue<s32>(arc, "OctCount"));
}

void CStage::on_update()
{
    if (m_state) {
        (this->*m_state)();
    }
    m_frame++;
    if (m_heiho.get() == NULL && GetScrollZ() < -9000.0f) {
        m_heiho.reset(new CHeiho);
    }
    UpdateShadow();
}

/* the guarded initialisers of UpdateShadow's two tuning statics (retail stores constants under guards, so the
 * initialiser is not a constant expression: m512's GetFps / m539's FogSelInit spelling guess) */
inline float ShadowOfsInit() { return 12.8f; }
inline float ShadowDistInit() { return 60.0f; }

/* lbl_1_data_4E4: the shadow projector's direction (unit length; non-const) */
static Vec s_shadowDir = { -0.68376344f, 0.56980288f, 0.45584232f };

/* the shadow projector: from -100 s_dist along s_shadowDir, looking at the scroll position (+ 100 s_ofs ahead); in
 * mode 4 (the result view) at the origin */
void CStage::UpdateShadow()
{
    static float s_ofs = ShadowOfsInit();   /* bss A6C (guard A70) */
    static float s_dist = ShadowDistInit(); /* bss A74 (guard A78) */
    if (GetUpdateMode() != 4) {
        Vec pos;
        Vec up;
        Vec target;
        SetVec(&up, 0.0f, 1.0f, 0.0f);
        SetVec(&target, 0.0f, 0.0f, 100.0f * s_ofs + GetScrollZ());
        float scale = -100.0f * s_dist;
        PSVECScale(&s_shadowDir, &pos, scale);
        PSVECAdd(&target, &pos, &pos);
        Hu3DShadowPosSet(&pos, &up, &target);
    } else {
        Vec pos;
        Vec up;
        Vec target;
        SetVec(&up, 0.0f, 1.0f, 0.0f);
        SetVec(&target, 0.0f, 0.0f, 0.0f);
        float scale = -100.0f * s_dist;
        PSVECScale(&s_shadowDir, &pos, scale);
        PSVECAdd(&target, &pos, &pos);
        Hu3DShadowPosSet(&pos, &up, &target);
    }
    Hu3DShadowTPLvlSet(0.35f);
    Hu3DShadowColSet(15, 16, 180);
}

void CStage::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    switch (mode) {
    case 0:
        break;
    case 4:
        m_model.reset(0);
        m_model2.reset(0);
        m_model.reset(new CModel(0x7B0003u));
        SetShadowReceiver(m_model.get()->id());
        break;
    }
}

/* frames to seconds (retail: an inline, its float result copied twice) */
inline float FrameToSec(float frame)
{
    return (1.0 / 60.0) * frame;
}

/* the course scrolls toward -z at 14.5 m/s (x100 units): 6000 - 1450 t */
float CStage::GetScrollZ()
{
    float t = FrameToSec(m_frame);
    return 6000.0f + 14.5f * (-100.0f * t);
}

/* lbl_1_rodata_368: the debug colour per triangle attr (attr >= 15 reads past it: retail, dead code) */
static const GXColor s_debugColor[15] = {
    { 0xB2, 0x00, 0x00, 0xFF }, { 0xB2, 0xB2, 0xB2, 0xFF }, { 0xB2, 0xB2, 0x00, 0xFF }, { 0xB2, 0x4C, 0x00, 0xFF },
    { 0x00, 0xB2, 0x00, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF }, { 0x00, 0xB2, 0xB2, 0xFF }, { 0x00, 0x00, 0xB2, 0xFF },
    { 0xB2, 0x00, 0xB2, 0xFF }, { 0xB2, 0xB2, 0xFF, 0xFF }, { 0xFF, 0xFF, 0x00, 0xFF }, { 0x4C, 0x4C, 0x00, 0xFF },
    { 0x4C, 0x00, 0x4C, 0xFF }, { 0x00, 0x4C, 0x00, 0xFF }, { 0x00, 0x00, 0x4C, 0xFF },
};

void CStage::DrawOctNode(const OctNode* n)
{
    if (n) {
        Vec* vtx = m_vtxTable;
        Tri* tris = m_triTable;
        u16* idx = &m_triIdx[n->first];
        int count = n->count;
        for (int i = 0; i < count; i++) {
            Tri* tri = &tris[idx[i]];
            Vec* a = &vtx[tri->v[0]];
            Vec* b = &vtx[tri->v[1]];
            Vec* c = &vtx[tri->v[2]];
            const GXColor* col = &s_debugColor[tri->attr];
            GXBegin(GX_LINESTRIP, GX_VTXFMT0, 4);
            GXPosition3f32(a->x, a->y, a->z);
            GXColor4u8(col->r, col->g, col->b, col->a);
            GXPosition3f32(b->x, b->y, b->z);
            GXColor4u8(col->r, col->g, col->b, col->a);
            GXPosition3f32(c->x, c->y, c->z);
            GXColor4u8(col->r, col->g, col->b, col->a);
            GXPosition3f32(a->x, a->y, a->z);
            GXColor4u8(col->r, col->g, col->b, col->a);
            GXEnd();
        }
    }
}

const Vec* CStage::GetNormal()
{
    return &m_hitPlane.n;
}

bool CStage::Raycast(Vec* out, const Vec* from, const Vec* to)
{
    OctNode* n0 = FindLeaf(m_octTable, from->x, from->y, from->z);
    OctNode* nm = FindLeaf(m_octTable, (from->x + to->x) / 2.0f, (from->y + to->y) / 2.0f, (from->z + to->z) / 2.0f);
    OctNode* n1 = FindLeaf(m_octTable, to->x, to->y, to->z);
    if (RayNode(out, from, to, n0)) {
        return true;
    }
    if (nm != n0 && RayNode(out, from, to, nm)) {
        return true;
    }
    if (n1 != nm && RayNode(out, from, to, n1)) {
        return true;
    }
    return false;
}

bool CStage::RayNode(Vec* out, const Vec* from, const Vec* to, OctNode* n)
{
    if (!n) {
        return false;
    }
    s32 count = n->count;
    if (count == 0) {
        return false;
    }
    u16* idx = m_triIdx + n->first;
    u16* end = idx + count;
    Tri* tris = m_triTable;
    Vec* vtx = m_vtxTable;
    HitCtx ctx;
    ctx.best = 0.0f;
    ctx.hit = 0;
    ctx.out = out;
    ctx.from = from;
    ctx.to = to;
    for (; idx != end; idx++) {
        Tri* tri = &tris[*idx];
        Vec* a = &vtx[tri->v[0]];
        Vec* b = &vtx[tri->v[1]];
        Vec* c = &vtx[tri->v[2]];
        HitTri(&ctx, tri, a, b, c);
    }
    return ctx.hit != 0;
}

void CStage::HitTri(HitCtx* ctx, Tri* tri, Vec* a, Vec* b, Vec* c)
{
    Plane pl;
    Vec p;
    PlaneFromPoints(&pl, a, b, c);
    float d0 = PlaneDist(&pl, ctx->from);
    float d1 = PlaneDist(&pl, ctx->to);
    /* the segment crosses the plane front to back (NaN distances fall through, as retail's negated compares) */
    if (!(d0 < d1) && !(d0 < 0.0f) && !(d1 > 0.0f)) {
        SegPlane(&p, ctx->from, d0, ctx->to, d1);
        if (InTriangle(a, b, c, &p, &pl.n) && !(ctx->best <= d1)) {
            ctx->best = d1;
            ctx->hit = tri;
            *ctx->out = p;
            CStage* stage = GetInstance();
            stage->m_hitPlane.n = pl.n;
            stage->m_hitPlane.d = pl.d;
        }
    }
}

/* PSVECScale returning its output (retail: Project passes the scaled vector on through an inline's return) */
inline Vec* StageVecScale(const Vec* v, Vec* out, float s)
{
    PSVECScale(v, out, s);
    return out;
}

/* out = p projected onto the last hit plane (never called) */
void CStage::Project(Vec* out, const Vec* p)
{
    float dot = PSVECDotProduct(&m_hitPlane.n, p);
    float d = m_hitPlane.d + dot;
    Vec t;
    Vec* tp = StageVecScale(&m_hitPlane.n, &t, -d);
    PSVECAdd(p, tp, out);
}

void CStage::SetSePos(const Vec* p, int se)
{
    if (se >= 0 && !omSysExitReq) {
        Vec np;
        GetNormPos(&np, p, 0.0f);
        float x = StageClamp(np.x, -1.0f, 1.0f);
        float z = StageClamp(np.z, -1.0f, 1.0f);
        MSM_SEPARAM param;
        param.flag = MSM_SEPARAM_VOL | MSM_SEPARAM_PAN;
        param.vol = 72.0f + 55.0f * ((1.0f + z) / 2.0f);
        param.pan = 64.0f + 24.0f * x;
        msmSeSetParam(se, &param);
    }
}

CStage::~CStage()
{
}

} // namespace m568
