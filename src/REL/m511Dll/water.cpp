#include "REL/m511Dll/config.h"
#include "REL/m511Dll/water.h"
#include "REL/mgcpp/random.h"
extern "C" {
/* no live prototype (game/sprite.h has it commented out); as m537 water.cpp */
void HuSprTexLoad(ANIMDATA* anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);
}

namespace m511 {

/* the arguments are evaluated right to left (retail computes z first) and narrowed at the stores */
static inline void SetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

/* the grid index clamp (1..14: every access below touches +-1) */
static inline int ClampCell(int i)
{
    if (i < 1) {
        return 1;
    } else if (i > CWater::MESH - 2) {
        return CWater::MESH - 2;
    }
    return i;
}

void CWater::Hook(HU3DMODEL* model, Mtx* mtx)
{
    CWater* self = (CWater*)model->hookData;
    self->Draw(mtx);
}

CWater::CWater() : m_time(0.0f), m_frame(0)
{
    HU3DMODELID id = Hu3DHookFuncCreate(Hook);
    HU3DMODEL* model = &Hu3DData[(int)id];
    model->hookData = this;
    m_model = (int)id;
    Hu3DModelLayerSet((int)id, 3);
    Hu3DModelCameraSet((int)id, 0xF);
    m_surfaceAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x450021, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_surfaceAnim);
    m_glareAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x45002B, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_glareAnim);
    InitMesh();
    m_scroll.x = 0.0f;
    m_scroll.y = 0.0f;
    m_scroll.z = 0.0f;
}

CWater::~CWater()
{
    Hu3DModelKill(m_model);
    HuSprAnimKill(m_surfaceAnim);
    HuSprAnimKill(m_glareAnim);
}

/* the rest grid: 1600 apart, centred; uv = cell / 16; colour 0 (alpha 0xB4); velocity 0 */
void CWater::InitMesh()
{
    Vec* pos = m_meshPos[0];
    Vec* uv = m_meshUV[0];
    GXColor* col = m_meshCol[0];
    int j;
    int i;
    for (i = 0; i < MESH; i++) {
        for (j = 0; j < MESH; j++) {
            int k = j + i * MESH;
            Vec* p = &pos[k];
            Vec* t = &uv[k];
            GXColor* c = &col[k];
            p->x = 1600.0f * j - 12800.0f;
            p->y = 0.0f;
            p->z = 1600.0f * i - 12800.0f;
            t->x = 0.0625f * j;
            t->z = 0.0625f * i;
            c->r = c->g = c->b = 0;
            c->a = 0xB4;
            (&m_meshVel[0][0])[k] = 0.0f;
        }
    }
}

/* one spring step on the inner cells 3..12: vel += laplacian / 120, h += vel, clamp +-100 (vel 0 at the clamp),
 * grey = 180 * 0.005 (100 + h) */
void CWater::UpdateMesh()
{
    Vec* pos = m_meshPos[0];
    GXColor* col = m_meshCol[0];
    float* vel = m_meshVel[0];
    int i;
    int j;
    float* prev = m_meshPrev[0];
    Vec* src = pos;
    for (i = 0; i < MESH; i++) {
        for (j = 0; j < MESH; j++, src++, prev++) {
            *prev = src->y;
        }
    }
    prev = m_meshPrev[0];
    for (i = 3; i < MESH - 3; i++) {
        for (j = 3; j < MESH - 3; j++) {
            float* h = &prev[i * MESH] + j;
            float* n = &prev[(i + 1) * MESH] + j;
            float* s = &prev[(i - 1) * MESH] + j;
            float lap = 0.0f;
            lap += 0.04f * h[1];
            lap += 0.04f * h[-1];
            lap += 0.04f * n[0];
            lap += 0.04f * s[0];
            lap -= 4.0f * (0.04f * h[0]);
            int k = j + i * MESH;
            Vec* p = &pos[k];
            float* v = &vel[k];
            GXColor* c = &col[k];
            *v += (1.0 / 120.0) * lap;
            p->y += *v;
            if (p->y > 100.0f) {
                p->y = 100.0f;
                *v = 0.0f;
            }
            if (p->y < -100.0f) {
                p->y = -100.0f;
                *v = 0.0f;
            }
            float g = 0.005f * (100.0f + p->y);
            u8 grey = 180.0f * g;
            c->r = c->g = c->b = grey;
        }
    }
}

/* unreferenced (inlined in on_update with dv = -0.5): a 3x3 impulse at the cell 8 + x / 1600 (truncating toward 0:
 * a different rounding from GetHeight's, retail) */
void CWater::AddWave(const Vec* pos, float dv)
{
    int ix = 8.0f + (int)(0.000625f * pos->x);
    int iz = 8.0f + (int)(0.000625f * pos->z);
    int cx = ClampCell(ix);
    int cz = ClampCell(iz);
    float* vel = m_meshVel[0];
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            int k = cx + x + (cz + y) * MESH;
            vel[k] += dv;
        }
    }
}

/* bilinear over the cell (x + 12800) / 1600, clamped to 1..14 (extrapolates at the rim) */
float CWater::GetHeight(const Vec* pos)
{
    int ix = 0.000625f * (12800.0f + pos->x);
    int iz = 0.000625f * (12800.0f + pos->z);
    int cx = ClampCell(ix);
    int cz = ClampCell(iz);
    int i0 = cx + cz * MESH;
    int i1 = cx + (cz + 1) * MESH;
    Vec* mesh = m_meshPos[0];
    float h00 = mesh[i0].y;
    float h01 = (mesh + i0)[1].y;
    float h10 = mesh[i1].y;
    float h11 = (mesh + i1)[1].y;
    Vec d = *pos;
    d.x -= mesh[i0].x;
    d.z -= mesh[i0].z;
    d.x *= 0.000625f;
    d.z *= 0.000625f;
    return (1.0f - d.z) * (h00 * (1.0f - d.x) + h01 * d.x) + d.z * (h10 * (1.0f - d.x) + h11 * d.x);
}

/* normalize((p00 - p10) x (p00 - p01)) of the cell under pos */
Vec CWater::GetNormal(const Vec* pos)
{
    int ix = 0.000625f * (12800.0f + pos->x);
    int iz = 0.000625f * (12800.0f + pos->z);
    int cx = ClampCell(ix);
    int cz = ClampCell(iz);
    int i0 = cx + cz * MESH;
    int i1 = cx + (cz + 1) * MESH;
    Vec* mesh = m_meshPos[0];
    Vec* p00 = &mesh[i0];
    Vec* p01 = &mesh[i0] + 1;
    Vec* p10 = &mesh[i1];
    Vec* p11 = &mesh[i1] + 1; /* unused (retail keeps it) */
    Vec n;
    Vec a;
    Vec b;
    PSVECSubtract(p00, p01, &a);
    PSVECSubtract(p00, p10, &b);
    PSVECCrossProduct(&b, &a, &n);
    PSVECNormalize(&n, &n);
    return n;
}

void CWater::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

/* the scroll, the spring step, and every 64th frame a random drop within +-9500 */
void CWater::on_update()
{
    m_time += 1.0 / 60.0;
    UpdateMesh();
    float a = 0.017453292f * (10.0f * m_time);
    float b = 0.017453292f * (20.0f * m_time);
    SetVec(&m_scroll, sin(a), 0.0f, sin(b));
    if ((m_frame & 63) == 0) {
        Vec p;
        p.x = 100.0f * (95.0f * ((1.0f / 32768) * ((CRandom::irandom() & 0xFFFF) - 32768.0f)));
        p.y = 0.0f;
        p.z = 100.0f * (95.0f * ((1.0f / 32768) * ((CRandom::irandom() & 0xFFFF) - 32768.0f)));
        AddWave(&p, -0.5f);
    }
    m_frame++;
}

void CWater::Draw(Mtx* mtx)
{
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    HuSprTexLoad(m_surfaceAnim, 0, GX_TEXMAP0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    HuSprTexLoad(m_glareAnim, 0, GX_TEXMAP1, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetCullMode(GX_CULL_BACK);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    DrawMesh();
    DrawGlare(mtx);
}

/* 15 x 15 QUADS (900 vertices), POS f32 + CLR0 RGBA8 + TEX0 f32 through TEXMTX0 = Scale(10, 10, 1) Trans(0.2 scroll) */
void CWater::DrawMesh()
{
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_TEXC, GX_CC_RASA, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    Mtx trans;
    Mtx scale;
    Mtx m;
    PSMTXTrans(trans, 0.2f * m_scroll.x, 0.0f, 0.2f * m_scroll.z);
    PSMTXScale(scale, 10.0f, 10.0f, 1.0f);
    PSMTXConcat(scale, trans, m);
    GXLoadTexMtxImm(m, GX_TEXMTX0, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    Vec* pos = m_meshPos[0];
    Vec* uv = m_meshUV[0];
    GXColor* col = m_meshCol[0];
    GXBegin(GX_QUADS, GX_VTXFMT0, (MESH - 1) * (MESH - 1) * 4);
    for (int i = 0; i < MESH - 1; i++) {
        int row0 = i * MESH;
        int row1 = (i + 1) * MESH;
        for (int j = 0; j < MESH - 1; j++) {
            int c0 = j;
            int c1 = j + 1;
            int k00 = row0 + c0;
            int k01 = row0 + c1;
            int k11 = row1 + c1;
            int k10 = row1 + c0;
            Vec* p00 = &pos[k00];
            Vec* p01 = &pos[k01];
            Vec* p11 = &pos[k11];
            Vec* p10 = &pos[k10];
            GXColor* q00 = &col[k00];
            GXColor* q01 = &col[k01];
            GXColor* q11 = &col[k11];
            GXColor* q10 = &col[k10];
            Vec* t00 = &uv[k00];
            Vec* t01 = &uv[k01];
            Vec* t11 = &uv[k11];
            Vec* t10 = &uv[k10];
            GXPosition3f32(p00->x, p00->y, p00->z);
            GXColor4u8(q00->r, q00->g, q00->b, q00->a);
            GXTexCoord2f32(t00->x, t00->z);
            GXPosition3f32(p01->x, p01->y, p01->z);
            GXColor4u8(q01->r, q01->g, q01->b, q01->a);
            GXTexCoord2f32(t01->x, t01->z);
            GXPosition3f32(p11->x, p11->y, p11->z);
            GXColor4u8(q11->r, q11->g, q11->b, q11->a);
            GXTexCoord2f32(t11->x, t11->z);
            GXPosition3f32(p10->x, p10->y, p10->z);
            GXColor4u8(q10->r, q10->g, q10->b, q10->a);
            GXTexCoord2f32(t10->x, t10->z);
        }
    }
    GXEnd();
}

/* the additive glare quad in the camera's yaw frame; alpha 160 |yaw| / 180 */
void CWater::DrawGlare(Mtx* mtx)
{
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    HU3DCAMERA* cam = &Hu3DCamera[Hu3DCameraNo];
    Vec d;
    PSVECSubtract(&cam->pos, &cam->target, &d);
    float yaw = 180.0 * (atan2(d.x, d.z) / M_PI);
    Mtx m;
    Mtx rot;
    PSMTXTrans(m, cam->pos.x, 0.0f, cam->pos.z);
    PSMTXRotRad(rot, 'y', 0.017453292f * yaw);
    PSMTXConcat(m, rot, m);
    PSMTXConcat(*mtx, m, m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    u8 a = 160.0f * (((yaw < 0.0f) ? -yaw : yaw) / 180.0f);
    GXColor col = { 0xFF, 0xFF, 0xFF, 0x00 };
    col.a = a;
    GXSetNumTevStages(1);
    GXSetTevColor(GX_TEVREG0, col);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-4000.0f, 0.0f, -8000.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(4000.0f, 0.0f, -8000.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(4000.0f, 0.0f, -1000.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(-4000.0f, 0.0f, -1000.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();
}

/* PSVECMag through one more inline level (retail's extra result copy) */
static inline float VecMag(Vec* v)
{
    return PSVECMag(v);
}

void CWaterRipple::Hook(HU3DMODEL* model, Mtx* mtx)
{
    CWaterRipple* self = (CWaterRipple*)model->hookData;
    self->Draw(mtx);
}

/* 80 patches at y -350: 30 on rings round the origin, 30 round z -5000, 20 round z +5000;
 * angle 30 i degrees, radius 100 (15 + 10 (i % 5)) (the % is unsigned in retail) */
CWaterRipple::CWaterRipple() : m_time(0.0f)
{
    HU3DMODELID id = Hu3DHookFuncCreate(Hook);
    HU3DMODEL* model = &Hu3DData[(int)id];
    model->hookData = this;
    m_model = (int)id;
    Hu3DModelLayerSet((int)id, 1);
    Hu3DModelCameraSet((int)id, 0xF);
    m_anim = HuSprAnimRead(HuDataSelHeapReadNum(0x450022, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_anim);
    m_warpAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x45002F, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_warpAnim);
    Vec* p = m_patch;
    for (int i = 0; i < 30; i++, p++) {
        float a = M_PI * (30.0f * i) / 180.0;
        float r = 100.0f * (15.0f + 10.0f * ((u32)i % 5));
        SetVec(p, r * sin(a), -350.0f, r * cos(a));
    }
    for (int i = 30; i < 60; i++, p++) {
        float a = M_PI * (30.0f * i) / 180.0;
        float r = 100.0f * (15.0f + 10.0f * ((u32)i % 5));
        SetVec(p, r * sin(a), -350.0f, r * cos(a) - 5000.0);
    }
    for (int i = 60; i < NUM_PATCH; i++, p++) {
        float a = M_PI * (30.0f * i) / 180.0;
        float r = 100.0f * (15.0f + 10.0f * ((u32)i % 5));
        SetVec(p, r * sin(a), -350.0f, 5000.0 + r * cos(a));
    }
    m_scroll.x = 0.0f;
    m_scroll.y = 0.0f;
    m_scroll.z = 0.0f;
}

CWaterRipple::~CWaterRipple()
{
    HuSprAnimKill(m_anim);
    HuSprAnimKill(m_warpAnim);
    Hu3DModelKill(m_model);
}

void CWaterRipple::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

void CWaterRipple::on_update()
{
    m_time += 1.0 / 60.0;
    float a = 0.017453292f * (10.0f * m_time);
    float b = 0.017453292f * (20.0f * m_time);
    SetVec(&m_scroll, sin(a), 0.0f, sin(b));
}

void CWaterRipple::Draw(Mtx* mtx)
{
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    HuSprTexLoad(m_anim, 0, GX_TEXMAP0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    HuSprTexLoad(m_warpAnim, 0, GX_TEXMAP1, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetCullMode(GX_CULL_BACK);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    DrawPatches();
}

/* each patch within 8000 of the eye: a 2000 x 2000 QUAD, TEXCOORD1 (TEXMTX1 = Trans(scroll.x, scroll.z)) warping
 * TEXCOORD0 through the indirect stage (ITM_1 = 0.1 I) */
void CWaterRipple::DrawPatches()
{
    static const f32 s_indMtx[2][3] = { { 0.1f, 0.0f, 0.0f }, { 0.0f, 0.1f, 0.0f } };
    GXSetNumTexGens(2);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    Mtx m;
    PSMTXTrans(m, m_scroll.x, m_scroll.z, 0.0f);
    GXLoadTexMtxImm(m, GX_TEXMTX1, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumIndStages(1);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_1);
    GXSetIndTexMtx(GX_ITM_1, (f32(*)[3])s_indMtx, 0); /* the SDK prototype is non-const */
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    HU3DCAMERA* cam = &Hu3DCamera[Hu3DCameraNo];
    Vec* p = m_patch;
    for (int i = 0; i < NUM_PATCH; i++, p++) {
        Vec d;
        Vec c = *p;
        PSVECSubtract(&c, &cam->pos, &d);
        float dist = VecMag(&d);
        if (dist > 8000.0f) {
            continue;
        }
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(c.x - 1000.0f, c.y, c.z - 1000.0f);
        GXTexCoord2f32(0.0f, 0.0f);
        GXPosition3f32(1000.0f + c.x, c.y, c.z - 1000.0f);
        GXTexCoord2f32(0.0f, 1.0f);
        GXPosition3f32(1000.0f + c.x, c.y, 1000.0f + c.z);
        GXTexCoord2f32(1.0f, 1.0f);
        GXPosition3f32(c.x - 1000.0f, c.y, 1000.0f + c.z);
        GXTexCoord2f32(1.0f, 0.0f);
        GXEnd();
    }
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevDirect(GX_TEVSTAGE1);
    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_FALSE, 0, 0);
    GXSetTexCoordScaleManually(GX_TEXCOORD1, GX_FALSE, 0, 0);
}

void CWaterRing::Hook(HU3DMODEL* model, Mtx* mtx)
{
    CWaterRing* self = (CWaterRing*)model->hookData;
    self->Draw(mtx);
}

CWaterRing::CWaterRing(const Vec* pos) : m_time(0.0f), m_pos(*pos)
{
    HU3DMODELID id = Hu3DHookFuncCreate(Hook);
    HU3DMODEL* model = &Hu3DData[(int)id];
    model->hookData = this;
    m_model = (int)id;
    Hu3DModelLayerSet((int)id, 3);
    Hu3DModelCameraSet((int)id, 0xF);
    m_tex = HuSprAnimRead(HuDataSelHeapReadNum(0x45002C, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_tex);
    m_warpAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x45002F, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_warpAnim);
    InitRing();
}

CWaterRing::~CWaterRing()
{
    Hu3DModelKill(m_model);
    HuSprAnimKill(m_tex);
    HuSprAnimKill(m_warpAnim);
}

/* 16 segments: even vertices radius 550, odd 800, at 22.5 (i / 2) degrees */
void CWaterRing::InitRing()
{
    for (int i = 0; i < NUM_VTX; i++) {
        float a = M_PI * (22.5f * (i >> 1)) / 180.0;
        float r = ((i & 1) == 0) ? 550.0f : 800.0f;
        m_ring[i].x = r * sin(a);
        m_ring[i].y = 0.0f;
        m_ring[i].z = r * cos(a);
    }
}

void CWaterRing::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

void CWaterRing::on_update()
{
    m_time += 1.0 / 60.0;
    float a = 0.017453292f * (10.0f * m_time);
    float b = 0.017453292f * (20.0f * m_time);
    SetVec(&m_scroll, sin(a), 0.0f, sin(b));
    CWater* water = CSingleton<CWater>::GetInstance();
    m_pos.y = 30.000002f + water->GetHeight(&m_pos); /* 0x41F00001 */
}

void CWaterRing::Draw(Mtx* mtx)
{
    static const f32 s_indMtx[2][3] = { { 0.1f, 0.0f, 0.0f }, { 0.0f, 0.1f, 0.0f } };
    Mtx m;
    PSMTXTrans(m, m_pos.x, m_pos.y, m_pos.z);
    PSMTXConcat(*mtx, m, m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    HuSprTexLoad(m_tex, 0, GX_TEXMAP0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    HuSprTexLoad(m_warpAnim, 0, GX_TEXMAP1, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetNumTexGens(2);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    Mtx t;
    PSMTXTrans(t, m_scroll.x, m_scroll.z, 0.0f);
    GXLoadTexMtxImm(t, GX_TEXMTX1, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_RASA, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumIndStages(1);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_1);
    GXSetIndTexMtx(GX_ITM_1, (f32(*)[3])s_indMtx, 0); /* the SDK prototype is non-const */
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetCullMode(GX_CULL_NONE);
    GXBegin(GX_QUADS, GX_VTXFMT0, NUM_VTX * 2);
    for (int i = 0; i < NUM_VTX; i += 2) {
        Vec a = m_ring[i & (NUM_VTX - 1)];
        Vec b = m_ring[(i + 1) & (NUM_VTX - 1)];
        Vec c = m_ring[(i + 3) & (NUM_VTX - 1)];
        Vec d = m_ring[(i + 2) & (NUM_VTX - 1)];
        GXPosition3f32(a.x, a.y, a.z);
        GXColor4u8(0xFF, 0xFF, 0xFF, 0xFF);
        GXTexCoord2f32(0.0f, 0.0f);
        GXPosition3f32(b.x, b.y, b.z);
        GXColor4u8(0xFF, 0xFF, 0xFF, 0x00);
        GXTexCoord2f32(0.0f, 1.0f);
        GXPosition3f32(c.x, c.y, c.z);
        GXColor4u8(0xFF, 0xFF, 0xFF, 0x00);
        GXTexCoord2f32(1.0f, 1.0f);
        GXPosition3f32(d.x, d.y, d.z);
        GXColor4u8(0xFF, 0xFF, 0xFF, 0xFF);
        GXTexCoord2f32(1.0f, 0.0f);
    }
    GXEnd();
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevDirect(GX_TEVSTAGE1);
    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_FALSE, 0, 0);
    GXSetTexCoordScaleManually(GX_TEXCOORD1, GX_FALSE, 0, 0);
}

} // namespace m511
