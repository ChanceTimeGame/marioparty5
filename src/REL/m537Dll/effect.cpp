#include "REL/m537Dll/effect.h"

extern "C" {
void HuSprTexLoad(ANIMDATA* anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);
}

namespace m537 {

void CEffect::DrawHook(HU3DMODEL* model, Mtx* mtx)
{
    CEffect* self = CSingleton<CEffect>::GetInstancePtr();
    self->Draw(mtx);
}

/* lbl_1_rodata_F8: the four flare sprites */
static const u32 s_animData[CEffect::NUM_ANIM] = { 0x5F0019, 0x5F001A, 0x5F001B, 0x5F001C };

CEffect::CEffect()
{
    HU3DMODELID id = Hu3DHookFuncCreate(DrawHook);
    Hu3DModelLayerSet((int)id, 7);
    Hu3DModelCameraSet((int)id, 1);
    for (int i = 0; i < NUM_ANIM; i++) {
        m_anim[i] = HuSprAnimRead(HuDataSelHeapReadNum(s_animData[i], HU_MEMNUM_OVL, HEAP_MODEL));
        HuSprAnimLock(m_anim[i]);
    }
}

CEffect::~CEffect()
{
    for (int i = 0; i < NUM_ANIM; i++) {
        HuSprAnimKill(m_anim[i]);
    }
}

void CEffect::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

/* lbl_1_rodata_108 */
static const int s_texMap[CEffect::NUM_ANIM] = { 0, 1, 2, 3 };

void CEffect::LoadTex()
{
    for (int i = 1; i < NUM_ANIM; i++) {
        HuSprTexLoad(m_anim[i], 0, (s16)s_texMap[i], GX_REPEAT, GX_REPEAT, GX_LINEAR);
    }
}

/* lbl_1_data_2FC: the sun (retail's is .data: not const) */
static Vec s_sunPos = { 0.0f, 3537.0f, 0.0f };

/* lbl_1_rodata_118: size, position along the sun-centre line (screen units of 240), colour 0xAABBGGRR, TEXMAP */
struct Flare {
    float size;
    float pos;
    u32 color;
    int tex;
};
static const Flare s_flare[CEffect::NUM_FLARE] = {
    { 10.0f, -1.0f, 0xFFFFFFFF, 0 }, { 8.0f, -0.8f, 0x30FFFF80, 2 },  { 7.0f, -0.7f, 0x60C080FF, 1 },
    { 5.0f, 0.1f, 0x50FFFFFF, 1 },   { 10.0f, 0.2f, 0x30FFFFC0, 2 },  { 15.0f, 0.7f, 0x60FFFFFF, 1 },
    { 20.0f, 0.8f, 0x40FFC0FF, 2 },  { 12.0f, 1.0f, 0x30C0FFFF, 1 },
};

void CEffect::Draw(Mtx* mtx)
{
    HU3DCAMERA* cam = Hu3DCamera;
    Vec dir;
    PSVECSubtract(&cam->pos, &s_sunPos, &dir);
    PSVECNormalize(&dir, &dir);
    Mtx id;
    PSMTXIdentity(id);
    GXLoadPosMtxImm(id, GX_PNMTX0);
    Vec vd;
    PSMTXMultVecSR(*mtx, &dir, &vd);
    float k = vd.z;
    if (k < 0.0f) {
        return;
    }
    HuSprTexLoad(m_anim[0], 0, GX_TEXMAP0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT0, GX_DF_CLAMP, GX_AF_SPOT);
    GXSetZCompLoc(GX_FALSE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
    GXSetAlphaUpdate(GX_TRUE);
    float sc = 240.0f * s_flare[0].pos;
    Vec p;
    p.x = vd.x * sc;
    p.y = vd.y * sc;
    p.z = -100.0f;
    DrawFlare(1.0f, p, s_flare[0].size, s_flare[0].color, s_flare[0].tex);
    float fov = cam->fov;
    float c = cos(0.017453292f * fov);
    k = (k - c) / (1.0f - c);
    PSVECScale(&vd, &vd, 1.0f - c);
    if (k < 0.0f) {
        return;
    }
    Vec scr;
    Vec sun = s_sunPos;
    scr = Project(sun, mtx);
    int sx = scr.x; /* retail: dead stores */
    int sy = scr.y;
    LoadTex();
    for (int i = 1; i < NUM_FLARE; i++) {
        float fsc = 240.0f * s_flare[i].pos;
        p.x = vd.x * fsc;
        p.y = vd.y * fsc;
        p.z = -100.0f;
        DrawFlare(k, p, s_flare[i].size, s_flare[i].color, s_flare[i].tex);
    }
    if (k < 0.8f) {
        return;
    }
    float w = (k - 0.8f) / 0.2f;
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    float a = 220.0f * w; /* converted to u8 at every vertex (retail) */
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-320.0f, -240.0f, -100.0f);
    GXColor4u8(0xFF, 0xFF, 0xFF, a);
    GXPosition3f32(-320.0f, 240.0f, -100.0f);
    GXColor4u8(0xFF, 0xFF, 0xFF, a);
    GXPosition3f32(320.0f, 240.0f, -100.0f);
    GXColor4u8(0xFF, 0xFF, 0xFF, a);
    GXPosition3f32(320.0f, -240.0f, -100.0f);
    GXColor4u8(0xFF, 0xFF, 0xFF, a);
    GXEnd();
}

/* fn_1_7DBC: one flare quad; the half-size includes 4 * the TEXMAP number
 * (retail formula) */
void CEffect::DrawFlare(float alpha, Vec pos, float size, u32 color, int tex)
{
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, (GXTexMapID)tex, GX_COLOR0A0);
    u8 r0 = color;
    u8 r = r0;
    u8 g0 = color >> 8;
    u8 g = g0;
    u8 b0 = color >> 16;
    u8 b = b0;
    u8 a0 = color >> 24;
    u8 alphaA = alpha * a0;
    /* the half-size includes 4 * the TEXMAP number (retail formula) */
    float h = size * alpha + alpha * (4.0f * tex);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(pos.x - h, pos.y - h, pos.z);
    GXColor4u8(r, g, b, alphaA);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(pos.x - h, pos.y + h, pos.z);
    GXColor4u8(r, g, b, alphaA);
    GXTexCoord2f32(0.0f, 1.0f);
    GXPosition3f32(pos.x + h, pos.y + h, pos.z);
    GXColor4u8(r, g, b, alphaA);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(pos.x + h, pos.y - h, pos.z);
    GXColor4u8(r, g, b, alphaA);
    GXTexCoord2f32(1.0f, 0.0f);
    GXEnd();
}

/* fn_1_81AC: view space -> 576x480 screen (a hidden-return Vec; `this`
 * unused); cos is called first, sin / cos recomputed for each axis */
Vec CEffect::Project(Vec p, Mtx* mtx)
{
    HU3DCAMERA* cam = Hu3DCamera;
    Vec v;
    PSMTXMultVec(*mtx, &p, &v);
    /* retail recomputes the angle for every call (no common subexpression) */
    float tx = 1.2f * (v.z * (sin(M_PI * (cam->fov / 2.0f) / 180.0) / cos(M_PI * (cam->fov / 2.0f) / 180.0)));
    float ty = v.z * (sin(M_PI * (cam->fov / 2.0f) / 180.0) / cos(M_PI * (cam->fov / 2.0f) / 180.0));
    Vec r;
    r.x = 288.0f + v.x * (288.0f / -tx);
    r.y = 240.0f + v.y * (240.0f / ty);
    r.z = 0.0f;
    return r;
}

} // namespace m537

template <> m537::CEffect* CSingleton<m537::CEffect>::ms_pointer = 0;
