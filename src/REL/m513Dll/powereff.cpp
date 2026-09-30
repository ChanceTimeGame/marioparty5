#include "REL/m513Dll/powereff.h"
#include "REL/m513Dll/powerind.h"
extern "C" {
#include "game/frand.h"
/* no live prototype (game/sprite.h has it commented out); as m531 cleaneff.cpp */
void HuSprTexLoad(ANIMDATA* anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);
}

namespace m513 {

void CPowerParticle::Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx m)
{
    CPowerParticle* self = (CPowerParticle*)particle->work;
    self->UpdateParticles(m);
}

CPowerParticle::CPowerParticle()
{
    m_active = false;
    CPowerInd* ind = CSingleton<CPowerInd>::GetInstance();
    ANIMDATA* anim = ind->GetParticleAnim();
    HU3DMODELID id = Hu3DParticleCreate(anim, 2);
    m_particle = (HU3DPARTICLE*)Hu3DData[(int)id].hookData;
    m_particle->work = this;
    Hu3DParticleHookSet((int)id, Hook);
    Hu3DParticleColSet((int)id, 0xFF, 0xFF, 0xFF);
    Hu3DParticleTPLvlSet((int)id, 0.0f);
    Hu3DParticleBlendModeSet((int)id, 1);
    Hu3DModelLayerSet((int)id, 5);
    Hu3DModelCameraSet((int)id, 1);
    Hu3DModelPosSet((int)id, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet((int)id, 0.0f, 0.0f, 0.0f);
    m_pos.x = 0.0f;
    m_pos.y = 0.0f;
    m_pos.z = 0.0f;
    m_vec.x = 0.0f;
    m_vec.y = 0.0f;
    m_vec.z = 0.0f;
    m_id = (int)id;
    int i;
    HU3DPARTICLEDATA* p;
    for (i = 0, p = m_particle->data; i < m_particle->maxCnt; i++, p++) {
        InitParticle(p);
        p->time = 0xFF;
    }
}

CPowerParticle::~CPowerParticle()
{
    m_particle->work = 0;
    Hu3DModelKill(m_id);
}

void CPowerParticle::Start(Vec* pos)
{
    HU3DPARTICLEDATA* p;
    int i;
    for (i = 0, p = m_particle->data; i < m_particle->maxCnt; i++, p++) {
        InitParticle(p);
    }
    m_pos = *pos;
    m_active = true;
}

void CPowerParticle::Stop()
{
    int i;
    HU3DPARTICLEDATA* p;
    for (i = 0, p = m_particle->data; i < m_particle->maxCnt; i++, p++) {
        p->color.a = 0;
        p->time = 0xFF;
    }
    m_active = false;
}

void CPowerParticle::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

void CPowerParticle::InitParticle(HU3DPARTICLEDATA* p)
{
    p->time = 0;
    p->parManId = (frand() & 15) + 4;
    p->pos.x = m_pos.x + 50.0f * ((1.0f / 32768) * ((frand() & 0xFFFF) - 32768.0f));
    p->pos.y = m_pos.y;
    p->pos.z = m_pos.z + 50.0f * ((1.0f / 32768) * ((frand() & 0xFFFF) - 32768.0f));
    p->scale = 100.0f * (0.2f + 0.2f * ((1.0f / 65536) * (frand() & 0xFFFF)));
    p->zRot = (float)(M_PI / 180.0) * (360.0f * ((1.0f / 65536) * (frand() & 0xFFFF)));
    u32 rgb = frand();
    p->vel.y = 0.0f;
    p->color.r = rgb & 0xFF;
    p->color.g = (rgb >> 8) & 0xFF;
    p->color.b = (rgb >> 16) & 0xFF;
    p->color.a = 0;
}

/* time 0: fade in by 16 to 0xFF, then time 1: fade out by the particle's speed and respawn below 20 (InitParticle,
 * inlined); spin 1 degree and fall */
void CPowerParticle::UpdateParticles(Mtx m)
{
    if (!m_active) {
        return;
    }
    HU3DMODEL* model = &Hu3DData[m_id]; /* unused (retail keeps the store) */
    HU3DPARTICLE* particle = m_particle;
    int i;
    HU3DPARTICLEDATA* p;
    for (i = 0, p = particle->data; i < particle->maxCnt; i++, p++) {
        if (p->time == 0xFF) {
            continue;
        }
        if (p->time == 0) {
            p->color.a += 16;
            if (p->color.a > 238) {
                p->color.a = 0xFF;
                p->time++;
            }
        } else {
            p->color.a -= p->parManId;
            if (p->color.a < 20) {
                InitParticle(p);
            }
        }
        p->zRot += (float)(M_PI / 180.0);
        float vy = p->vel.y;
        /* retail's double -0.05448138970072485 (bfabe4fc_1602af67) = -(9.80665 * 100 / 3600) * 0.2f to within 2 ulp;
         * no natural spelling found that folds to the exact bits, so the literal is written out */
        p->vel.y += -0.05448138970072485;
        vy = 0.5f * (vy + p->vel.y);
        p->pos.y += vy;
    }
}

void CPowerParticle::SetPos(Vec* pos)
{
    m_pos = *pos;
}

void CPowerParticle::SetVec(Vec* v)
{
    m_vec = *v;
}

void CPowerEff::DrawHook(HU3DMODEL* model, Mtx* mtx)
{
    CPowerEff* self = (CPowerEff*)model->hookData;
    self->Draw(*mtx);
}

/* CPowerParticle() and its InitParticle loop are inlined here */
CPowerEff::CPowerEff() : m_time(0.0f), m_state(0), m_delay(0.0f), m_frame(0), m_scale(0.0f)
{
    m_pos.x = 0.0f;
    m_pos.y = 0.0f;
    m_pos.z = 0.0f;
    m_target.x = 0.0f;
    m_target.y = 0.0f;
    m_target.z = 0.0f;
    HU3DMODELID id = Hu3DHookFuncCreate(DrawHook);
    HU3DMODEL* model = &Hu3DData[id];
    model->hookData = this;
    Hu3DModelLayerSet(id, 4);
    Hu3DModelCameraSet(id, 1);
    m_hook = id;
    m_color.r = m_color.g = m_color.b = 0xFF;
    m_color.a = 0;
    m_particle.reset(new CPowerParticle);
}

CPowerEff::~CPowerEff()
{
    Hu3DModelKill(m_hook);
}

void CPowerEff::Start(Vec* from, Vec* to, float delay)
{
    m_time = 0.0f;
    m_state = 0;
    m_pos = *from;
    m_target = *to;
    m_delay = delay;
    m_frame = 0;
    m_scale = 0.0f;
    m_color.r = m_color.g = m_color.b = 0xFF;
    m_color.a = 0;
}

void CPowerEff::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

/* 0: wait the delay, start the sparkle; 1: fade in; 2: fly until within 50 of the target; 3: fade out; 4: stop the
 * sparkle; 5: idle. Every state > 0 short of 4/5 moves the ball 1.5/60 of the way to the target, eases the scale to
 * 1.5 and steps the warp frame; the sparkle follows the ball. (CPowerParticle::Start / Stop / SetPos inlined.) */
void CPowerEff::on_update()
{
    switch (m_state) {
    case 0:
        m_time += 1.0 / 60.0;
        if (m_delay > m_time) {
            break;
        }
        m_particle->Start(&m_pos);
        m_state++;
    case 1:
        m_color.a += 16;
        if (m_color.a < 220) {
            break;
        }
        m_state++;
    case 2: {
        Vec d;
        PSVECSubtract(&m_pos, &m_target, &d);
        float dist = PSVECMag(&d);
        if (dist > 50.0f) {
            break;
        }
        m_state++;
    }
    case 3:
        m_color.a -= 8;
        if (m_color.a > 8) {
            break;
        }
        m_color.a = 0;
        m_state++;
    case 4:
        m_particle->Stop();
        m_state++;
    case 5:
        return;
    }
    if (m_state > 0) {
        Vec v = m_pos;
        PSVECSubtract(&m_target, &v, &v);
        PSVECScale(&v, &v, 1.5f * (1.0f / 60));
        PSVECAdd(&v, &m_pos, &m_pos);
        m_scale += (1.5f - m_scale) / 48.0;
        m_frame++;
        if (m_frame > 31) {
            m_frame = 0;
        }
    }
    m_particle->SetPos(&m_pos);
}

void CPowerEff::Draw(Mtx view)
{
    if (m_state == 0 || m_state > 4) {
        return;
    }
    if (m_color.a == 0) {
        return;
    }
    Mtx m;
    Mtx inv;
    PSMTXInverse(view, inv);
    inv[0][3] = inv[1][3] = inv[2][3] = 0.0f;
    PSMTXTrans(m, m_pos.x, m_pos.y, m_pos.z);
    PSMTXConcat(m, inv, m);
    PSMTXConcat(view, m, view);
    GXLoadPosMtxImm(view, GX_PNMTX0);
    CPowerInd* ind = CSingleton<CPowerInd>::GetInstance();
    GXLoadTexObj(ind->GetTexObj(), GX_TEXMAP0);
    ANIMDATA* mask = ind->GetMask();
    HuSprTexLoad(mask, 0, GX_TEXMAP1, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    ANIMDATA* warp = ind->GetWarp(m_frame);
    HuSprTexLoad(warp, 0, GX_TEXMAP2, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT0, GX_DF_CLAMP, GX_AF_SPOT);
    GXSetNumTevStages(3);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_ZERO, GX_CC_TEXA, GX_CC_CPREV);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_KONST, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumTexGens(3);
    HU3DCAMERA* cam = &Hu3DCamera[Hu3DCameraNo];
    Mtx texMtx;
    Mtx proj;
    C_MTXLightPerspective(proj, cam->fov, cam->aspect, 0.5f, -0.5f, 0.5f, 0.5f);
    PSMTXConcat(proj, view, texMtx);
    GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumIndStages(1);
    Mtx trans;
    Mtx scale;
    PSMTXTrans(trans, 0.0f, 0.0f, 0.0f);
    PSMTXScale(scale, 1.0f, 1.0f, 1.0f);
    PSMTXConcat(scale, trans, texMtx);
    GXLoadTexMtxImm(texMtx, GX_TEXMTX1, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD2, GX_TEXMAP2);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
    static const f32 s_indMtx[2][3] = { { 0.1f, 0.0f, 0.0f }, { 0.0f, 0.1f, 0.0f } };
    GXSetIndTexMtx(GX_ITM_0, (f32(*)[3])s_indMtx, 0); /* the SDK prototype is non-const */
    GXSetCullMode(GX_CULL_BACK);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    float s = 40.0f;
    if (m_state > 0) {
        s *= m_scale;
    }
    GXColor color = m_color;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-s, -s, 0.0f);
    GXColor4u8(color.r, color.g, color.b, color.a);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(-s, s, 0.0f);
    GXColor4u8(color.r, color.g, color.b, color.a);
    GXTexCoord2f32(0.0f, 1.0f);
    GXPosition3f32(s, s, 0.0f);
    GXColor4u8(color.r, color.g, color.b, color.a);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(s, -s, 0.0f);
    GXColor4u8(color.r, color.g, color.b, color.a);
    GXTexCoord2f32(1.0f, 0.0f);
    GXEnd();
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevDirect(GX_TEVSTAGE1);
    GXSetTevDirect(GX_TEVSTAGE2);
    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_FALSE, 0, 0);
    GXSetTexCoordScaleManually(GX_TEXCOORD1, GX_FALSE, 0, 0);
    GXSetTexCoordScaleManually(GX_TEXCOORD2, GX_FALSE, 0, 0);
}

} // namespace m513
