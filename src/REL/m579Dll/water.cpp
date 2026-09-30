#include "REL/m579Dll/water.h"
#include "REL/mgcpp/random.h"

extern "C" {
/* exported, but its prototype is commented out in game/sprite.h (m537 effect.cpp precedent) */
void HuSprTexLoad(ANIMDATA* anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);
void GXSetVtxAttrFmtv(GXVtxFmt vtxfmt, GXVtxAttrFmtList* list);
}

namespace m579 {

TLinkList<CWaterSpray> CWaterSpray::s_list;
TLinkList<CWaterDrop> CWaterDrop::s_list;
TLinkList<CRipple> CRipple::s_list;

/* lbl_1_rodata_280: spray particle, ripple texture, drop particle */
static const u32 s_animData[CWater::NUM_ANIM] = { 0x850003, 0x850004, 0x850005 };

CWater::CWater()
{
    for (int i = 0; i < NUM_ANIM; i++) {
        m_anim[i] = HuSprAnimRead(HuDataSelHeapReadNum(s_animData[i], HU_MEMNUM_OVL, HEAP_MODEL));
        HuSprAnimLock(m_anim[i]);
    }
}

CWater::~CWater()
{
    CWaterSpray::DeleteAll();
    CWaterDrop::DeleteAll();
    CRipple::DeleteAll();
    for (int i = 0; i < NUM_ANIM; i++) {
        HuSprAnimKill(m_anim[i]);
    }
}

/* unreferenced out-of-line copy (inlined at 9B98 / A0EC / AB10): singleton.h:39 */
ANIMDATA* CWater::GetAnim(int i)
{
    return CSingleton<CWater>::GetInstance()->m_anim[i];
}

void CWater::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

void CWater::on_update()
{
    CWaterSpray::UpdateAll();
    CWaterDrop::UpdateAll();
    CRipple::UpdateAll();
}

/* never called (dead, as m536 CKillerSpark) */
CWaterSpray::CWaterSpray(Vec* pos)
{
    insertBack(&s_list);
    ANIMDATA* anim = CWater::GetAnim(0);
    m_id = Hu3DParticleCreate(anim, 1);
    Hu3DModelPosSetV(m_id, pos);
    Hu3DModelLayerSet(m_id, 5);
    Hu3DParticleScaleSet(m_id, 100.0f);
    Hu3DParticleHookSet(m_id, Hook);
    Hu3DParticleTPLvlSet(m_id, 0.0f);
    Hu3DParticleBlendModeSet(m_id, 0);
    m_unk0C = 0;
}

CWaterSpray::~CWaterSpray()
{
    Hu3DModelKill(m_id);
}

void CWaterSpray::DeleteAll()
{
    while (!s_list.isEmpty()) {
        CWaterSpray* e = s_list.last();
        delete e;
    }
}

void CWaterSpray::UpdateAll()
{
    TLinkList<CWaterSpray>::exec(&s_list, Update);
}

/* deletes e once the hook has marked the particle set dead (the host list walk reads next first) */
void CWaterSpray::Update(CWaterSpray* e)
{
    HU3DPARTICLE* particle = (HU3DPARTICLE*)Hu3DData[e->m_id].hookData;
    if (particle->dataCnt < 0) {
        delete e;
    }
}

/* fn_1_9E80: random velocity +-2.5, gravity, x0.8 drag, fade to white, alpha -8 */
void CWaterSpray::Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx)
{
    HU3DPARTICLEDATA* end = &particle->data[particle->maxCnt];
    int count;
    if (particle->count == 0) {
        for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
            data->vel.x = 2.5f * CRandom::frandom(-1.0f, 1.0f);
            data->vel.y = 2.5f * CRandom::frandom(-1.0f, 1.0f);
            data->vel.z = 2.5f * CRandom::frandom(-1.0f, 1.0f);
            data->pos.x = data->pos.y = data->pos.z = 0.0f;
            data->color.r = 0x80;
            data->color.g = 0xFF;
            data->color.b = 0xFF;
            data->color.a = 0x80;
        }
    }
    count = 0;
    for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
        data->vel.y = data->vel.y - 980.665 / 60.0 / 60.0;
        PSVECScale(&data->vel, &data->vel, 0.8f);
        PSVECAdd(&data->vel, &data->pos, &data->pos);
        data->color.r = 0xFF;
        int g = data->color.g;
        g += 0x20;
        if (g > 0xFF) {
            g = 0xFF;
        }
        data->color.g = g;
        int b = data->color.b;
        b += 0x20;
        if (b > 0xFF) {
            b = 0xFF;
        }
        data->color.b = b;
        int a = data->color.a;
        a -= 8;
        if (a < 0) {
            a = 0;
            data->scale = 0.0f;
            particle->dataCnt = -1;
        }
        data->color.a = a;
        count++;
    }
    particle->emitCnt = count;
}

CWaterDrop::CWaterDrop(Vec* pos)
{
    insertBack(&s_list);
    ANIMDATA* anim = CWater::GetAnim(2);
    m_id = Hu3DParticleCreate(anim, 1);
    Hu3DModelPosSetV(m_id, pos);
    Hu3DModelLayerSet(m_id, 5);
    Hu3DParticleScaleSet(m_id, 30.0f + 50.0f * CRandom::randomMantissa());
    Hu3DParticleHookSet(m_id, Hook);
    Hu3DParticleTPLvlSet(m_id, 0.0f);
    Hu3DParticleBlendModeSet(m_id, 0);
    m_unk0C = 0;
}

CWaterDrop::~CWaterDrop()
{
    Hu3DModelKill(m_id);
}

void CWaterDrop::DeleteAll()
{
    while (!s_list.isEmpty()) {
        CWaterDrop* e = s_list.last();
        delete e;
    }
}

void CWaterDrop::UpdateAll()
{
    TLinkList<CWaterDrop>::exec(&s_list, Update);
}

void CWaterDrop::Update(CWaterDrop* e)
{
    HU3DPARTICLE* particle = (HU3DPARTICLE*)Hu3DData[e->m_id].hookData;
    if (particle->dataCnt < 0) {
        delete e;
    }
}

/* lbl_1_rodata_2B4 / 2C0: the drop direction before the random rotation, the eight drop colours (RGBA) */
static const Vec s_dropDir = { 0.0f, 0.0f, 75.0f };
static const GXColor s_dropColor[8] = {
    { 0xFF, 0xFF, 0xFF, 0xFF }, { 0xFF, 0xFF, 0xC0, 0xFF }, { 0xFF, 0xC0, 0xFF, 0xFF }, { 0xFF, 0xC0, 0xC0, 0xFF },
    { 0xC0, 0xFF, 0xFF, 0xFF }, { 0xC0, 0xFF, 0xC0, 0xFF }, { 0xC0, 0xC0, 0xFF, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF },
};

/* fn_1_A3EC: one drop thrown in a random direction; alpha falls by a growing step
 * (emitCnt is a frame counter here: quadratic fade), +5 degrees of spin a frame */
void CWaterDrop::Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx)
{
    HU3DPARTICLEDATA* end = &particle->data[particle->maxCnt];
    if (particle->count == 0) {
        for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
            float k = 1.0f / 60.0f;
            Mtx rx;
            Mtx ry;
            Vec v;
            PSMTXRotRad(rx, 'X', 0.017453292f * (180.0f * CRandom::randomMantissa() - 90.0f));
            PSMTXRotRad(ry, 'Y', 0.017453292f * (360.0f * CRandom::randomMantissa() - 180.0f));
            PSMTXConcat(ry, rx, rx);
            PSMTXMultVec(rx, (Vec*)&s_dropDir, &v);
            data->vel.x = v.x * k;
            data->vel.y = v.y * k;
            data->vel.z = v.z * k;
            data->pos = v;
            data->color = s_dropColor[CRandom::irandom() & 7];
            data->zRot = M_PI * (360.0f * CRandom::randomMantissa()) / 180.0;
        }
    }
    for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
        PSVECAdd(&data->vel, &data->pos, &data->pos);
        int a = data->color.a;
        a -= particle->emitCnt;
        if (a < 0) {
            a = 0;
            data->scale = 0.0f;
            particle->dataCnt = -1;
        }
        data->color.a = a;
        data->zRot = M_PI * (5.0 + 180.0 * (data->zRot / M_PI)) / 180.0;
    }
    particle->emitCnt += 1;
}

/* effect CSplash ctor: an expanding ring at the splash (0.1 max -> max) */
CRipple::CRipple(Vec* pos, float maxRadius) : CModel(DrawHook), m_pos(*pos)
{
    m_radius = 0.1 * maxRadius;
    m_maxRadius = maxRadius;
    m_alpha = 0xFF;
    insertBack(&s_list);
    setHookData(this);
    setLayer(1);
}

CRipple::~CRipple() {}

void CRipple::DrawHook(HU3DMODEL* model, Mtx* mtx)
{
    ((CRipple*)model->hookData)->Draw(mtx);
}

void CRipple::DeleteAll()
{
    while (!s_list.isEmpty()) {
        CRipple* r = s_list.last();
        delete r;
    }
}

void CRipple::UpdateAll()
{
    execList(s_list.asList(), UpdateThunk);
}

void CRipple::UpdateThunk(CRipple* r)
{
    r->Update();
}

/* alpha from the radius; grows by max / 48 a frame; deletes itself at full radius (inside the copy walk: safe) */
void CRipple::Update()
{
    m_alpha = 255.0 * (1.0 - m_radius / m_maxRadius);
    if ((m_radius += m_maxRadius / 48.0) >= m_maxRadius) {
        delete this;
    }
}

/* lbl_1_rodata_330 / 334 / 34C: the TEV colour template, the vertex descriptors and formats */
static const GXColor s_color0 = { 0, 0, 0, 0 };
static const GXVtxDescList s_vtxDesc[] = {
    { GX_VA_POS, GX_DIRECT },
    { GX_VA_TEX0, GX_DIRECT },
    { GX_VA_NULL, GX_NONE },
};
static const GXVtxAttrFmtList s_vtxFmt[] = {
    { GX_VA_POS, GX_POS_XYZ, GX_F32, 0 },
    { GX_VA_TEX0, GX_TEX_ST, GX_F32, 0 },
    { GX_VA_NULL, GX_POS_XY, GX_U8, 0 },
};

void CRipple::Draw(Mtx* mtx)
{
    Mtx m;
    PSMTXScale(m, m_radius, 1.0f, m_radius);
    PSMTXTransApply(m, m, m_pos.x, -150.0f, m_pos.z);
    PSMTXConcat(*mtx, m, m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    GXSetNumChans(0);
    GXSetChanCtrl(GX_COLOR_NULL, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    ANIMDATA* anim = CWater::GetAnim(1);
    HuSprTexLoad(anim, 0, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    PSMTXIdentity(m);
    MtxPtr pm = m; /* retail keeps &m in a saved register here (and the 16 bytes more frame) */
    GXLoadTexMtxImm(pm, GX_TEXMTX0, GX_MTX2x4);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXColor c = s_color0;
    c.a = (u8)m_alpha; /* retail: lbz; clrlwi (m522 bubble) */
    GXSetTevColor(GX_TEVREG0, c);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ONE);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetCullMode(GX_CULL_BACK);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetZCompLoc(GX_TRUE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_LEQUAL, 255);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXClearVtxDesc();
    GXSetVtxDescv((GXVtxDescList*)s_vtxDesc);
    GXSetVtxAttrFmtv(GX_VTXFMT0, (GXVtxAttrFmtList*)s_vtxFmt);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-0.5f, 1.0f, -0.5f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXPosition3f32(0.5f, 1.0f, -0.5f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(0.5f, 1.0f, 0.5f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(-0.5f, 1.0f, 0.5f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXEnd();
}

/* the delete-safe walk (= m522 sunfire E65C): the list moves to a local, each node is re-inserted before fn */
void CRipple::execList(CLinkList* list, ExecFunc fn)
{
    if (!list->isEmpty()) {
        TLinkList<CRipple> tmp;
        list->copyLink(tmp.asList());
        while (!tmp.isEmpty()) {
            CRipple* r = tmp.begin();
            r->unlink();
            r->CLinkNode::insertBack(list);
            fn(r);
        }
    }
}

} // namespace m579
