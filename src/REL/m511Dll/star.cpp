#include "REL/m511Dll/config.h"
#include "REL/m511Dll/star.h"
#include "REL/m511Dll/boatshadow.h"

extern "C" {
void HuSprTexLoad(ANIMDATA* anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);
}

namespace m511 {

/* lbl_1_rodata_388: the five star gates, then the goal (index 5; GetPos only) */
static const Vec s_pos[CStarMan::NUM_STAR + 1] = {
    { -2500.0f, 280.0f, -2000.0f }, { 2700.0f, 280.0f, -3200.0f }, { -2000.0f, 280.0f, 3000.0f },
    { 2180.0f, 280.0f, 1600.0f },   { -3500.0f, 280.0f, 0.0f },    { 0.0f, 280.0f, -5500.0f },
};

/* the borrowed column texture (CEffTex, through GetInstance: singleton.h:39) */
static inline ANIMDATA* GetRingAnim(CEffTex* tex)
{
    return tex->m_ringAnim;
}

CStarMan::CStarMan()
    : m_star(0x450016u), m_mark0(0x450017u), m_mark1(0x450018u), m_mark2(0x450019u), m_mark3(0x45001Au),
      m_mark4(0x45001Bu), m_frame(0), m_yaw(0.0f)
{
    HU3DMODELID id;
    int i;
    int j;
    int k;
    int n;
    m_starMdl[0] = m_star.id();
    m_starMdl[1] = Hu3DModelLink(m_star.id());
    m_starMdl[2] = Hu3DModelLink(m_star.id());
    m_starMdl[3] = Hu3DModelLink(m_star.id());
    m_starMdl[4] = Hu3DModelLink(m_star.id());
    for (i = 0; i < NUM_STAR; i++) {
        m_ring[i].reset(new CStarRing);
        Vec pos = s_pos[i];
        pos.y -= 300.0f;
        m_ring[i]->SetPos(&pos);
    }
    for (j = 0; j < NUM_STAR; j++) {
        id = m_starMdl[j];
        Hu3DModelLayerSet(id, 5);
        Hu3DModelPosSetV(id, (Vec*)&s_pos[j]);
        Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(id, HU3D_ATTR_NOCULL);
        Hu3DModelCameraSet(id, 0xF);
    }
    m_markMdl[0] = m_mark0.id();
    m_markMdl[1] = m_mark1.id();
    m_markMdl[2] = m_mark2.id();
    m_markMdl[3] = m_mark3.id();
    m_markMdl[4] = m_mark4.id();
    for (k = 0; k < NUM_STAR; k++) {
        id = m_markMdl[k];
        Hu3DModelLayerSet(id, 5);
        Hu3DModelPosSetV(id, (Vec*)&s_pos[k]);
        Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(id, HU3D_ATTR_NOCULL);
        Hu3DModelCameraSet(id, 0xF);
        m_eff[k].reset(new CStarEff((Vec*)&s_pos[k]));
    }
    for (n = 0; n < NUM_STAR; n++) {
        m_hits[n] = 0;
        m_phase[n] = 0;
        m_pop[n] = 0;
    }
}

CStarMan::~CStarMan()
{
    for (int i = 1; i < NUM_STAR; i++) {
        Hu3DModelKill(m_starMdl[i]);
    }
}

void CStarMan::GetPos(int gate, Vec* out)
{
    *out = s_pos[gate];
}

/* per star: pop scale (player sets m_pop = 18), spin by the number of players that took it and bob; the
 * markers turn with m_yaw; the columns scroll; the sparkles follow */
void CStarMan::on_update()
{
    for (int i = 0; i < NUM_STAR; i++) {
        Vec pos = s_pos[i];
        float yaw = 0.0f;
        float scale = 1.0f;
        if (m_pop[i] != 0) {
            m_pop[i]--;
            scale += (m_pop[i] * 2) / 18.0f;
        }
        float bob = 0.0f;
        if (m_hits[i] != 0) {
            m_phase[i] += m_hits[i];
            if (m_phase[i] > 120.0f) {
                m_phase[i] -= 120.0f;
            }
            yaw = 360.0f * m_phase[i] / 120.0f;
            if (yaw > 180.0f) {
                yaw -= 360.0f;
            }
            bob = sin(M_PI * yaw / 180.0);
            pos.y += 50.0f * bob;
        }
        HU3DMODELID id = m_starMdl[i];
        Hu3DModelPosSetV(id, &pos);
        Hu3DModelRotSet(id, 0.0f, yaw, 0.0f);
        Hu3DModelScaleSet(id, scale, scale, scale);
        id = m_markMdl[i];
        Hu3DModelPosSetV(id, &pos);
        Hu3DModelRotSet(id, 0.0f, m_yaw, 0.0f);
        CStarRing* ring = m_ring[i].get();
        ring->Update();
        double markYaw = m_yaw; /* retail: a double (frsp at the store) */
        Vec rot;
        rot.x = 0.0f;
        rot.y = markYaw;
        rot.z = 0.0f;
        m_eff[i]->SetPos(&pos, &rot);
    }
    m_frame++;
    m_yaw += 2.0f;
    if (m_yaw > 180.0f) {
        m_yaw -= 360.0f;
    }
}

void CStarMan::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    switch (mode) { /* every mode 0..4 empty: CW's range test (cmpwi 5 / bge, cmpwi 0 / b) */
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        break;
    }
}

void CStarRing::DrawHook(HU3DMODEL* model, Mtx* mtx)
{
    CStarRing* self = (CStarRing*)model->hookData;
    self->Draw(mtx);
}

CStarRing::CStarRing() : m_yScale(1.0f), m_scroll(0.0f)
{
    HU3DMODELID id = Hu3DHookFuncCreate(DrawHook);
    HU3DMODEL* model = &Hu3DData[(int)id];
    model->hookData = this;
    Hu3DModelLayerSet((int)id, 5);
    Hu3DModelCameraSet((int)id, 0xF);
    m_model = (int)id;
    CEffTex* tex = CSingleton<CEffTex>::GetInstance();
    m_anim = GetRingAnim(tex);
    Init();
}

CStarRing::~CStarRing()
{
    Hu3DModelKill(m_model);
}

/* three rings of 16 (radius 150, y 0 / 180 / 360); the top ring is transparent */
void CStarRing::Init()
{
    for (int i = 0; i < NUM_VTX; i++) {
        m_alpha[i] = (i < 32) ? 0x80 : 0;
        float ang = M_PI * (22.5f * i) / 180.0;
        m_vtx[i].x = 150.0 * sin(ang);
        m_vtx[i].y = 180.0f * (i / 16);
        m_vtx[i].z = 150.0 * cos(ang);
    }
}

void CStarRing::Update()
{
    m_scroll += 1.0 / 60.0;
    if (m_scroll < 1.0f) {
        return;
    }
    m_scroll = 0.0f;
}

void CStarRing::Draw(Mtx* mtx)
{
    Mtx trans;
    Mtx scale;
    PSMTXTrans(trans, m_pos.x, m_pos.y, m_pos.z);
    PSMTXScale(scale, 1.0f, m_yScale, 1.0f);
    PSMTXConcat(*mtx, trans, *mtx);
    PSMTXConcat(*mtx, scale, scale);
    GXLoadPosMtxImm(scale, GX_PNMTX0);
    HuSprTexLoad(m_anim, 0, GX_TEXMAP0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
    GXSetZCompLoc(GX_TRUE);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTexGens(1);
    float t = 2.0f * (1.0f - m_scroll);
    Mtx texMtx;
    PSMTXTrans(texMtx, 0.0f, t, 0.0f);
    GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_RASC, GX_CC_HALF, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 128);
    for (int i = 0; i < 32; i++) {
        int row = (i / 16) * 16;
        int row2 = row + 16;
        int i0 = (i & 15) + row;
        int i1 = ((i + 1) & 15) + row;
        int i2 = ((i + 1) & 15) + row2;
        int i3 = (i & 15) + row2;
        Vec v0 = m_vtx[i0];
        Vec v1 = m_vtx[i1];
        Vec v2 = m_vtx[i2];
        Vec v3 = m_vtx[i3];
        GXPosition3f32(v0.x, v0.y, v0.z);
        GXColor4u8(0x80, 0x80, 0x50, m_alpha[i0]);
        GXTexCoord2f32(0.0f, 0.0f);
        GXPosition3f32(v1.x, v1.y, v1.z);
        GXColor4u8(0x80, 0x80, 0x50, m_alpha[i1]);
        GXTexCoord2f32(4.0f, 0.0f);
        GXPosition3f32(v2.x, v2.y, v2.z);
        GXColor4u8(0x80, 0x80, 0x50, m_alpha[i2]);
        GXTexCoord2f32(4.0f, 2.0f);
        GXPosition3f32(v3.x, v3.y, v3.z);
        GXColor4u8(0x80, 0x80, 0x50, m_alpha[i3]);
        GXTexCoord2f32(0.0f, 2.0f);
    }
    GXEnd();
}

} // namespace m511
