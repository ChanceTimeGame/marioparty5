#include "REL/m517Dll/config.h"
#include "REL/m517Dll/papereff.h"
#include "REL/m517Dll/audio.h"
extern "C" {
#include "game/frand.h"
/* exported, but its prototype is commented out in game/sprite.h (m537 effect.cpp precedent) */
void HuSprTexLoad(ANIMDATA* anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);
}

namespace m517 {

void CPaperEff::Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx m)
{
    CPaperEff* self = (CPaperEff*)particle->work;
    self->Update(m);
}

CPaperEff::CPaperEff(Vec* pos)
{
    m_anim = HuSprAnimRead(HuDataSelHeapReadNum(0x4B0012, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_anim);
    HU3DMODELID id = Hu3DParticleCreate(m_anim, 10);
    m_particle = (HU3DPARTICLE*)Hu3DData[(int)id].hookData;
    m_particle->work = this;
    Hu3DParticleHookSet((int)id, Hook);
    Hu3DParticleColSet((int)id, 0xFF, 0xFF, 0xFF);
    Hu3DParticleTPLvlSet((int)id, 0.0f);
    Hu3DParticleBlendModeSet((int)id, 1);
    Hu3DModelLayerSet((int)id, 5);
    Hu3DModelPosSet((int)id, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet((int)id, 0.0f, 0.0f, 0.0f);
    m_pos = *pos;
    m_vel.x = 0.0f;
    m_vel.y = 0.0f;
    m_vel.z = 0.0f;
    m_model = (int)id;
}

CPaperEff::~CPaperEff()
{
    m_particle->work = 0;
    Hu3DModelKill(m_model);
    HuSprAnimKill(m_anim);
}

void CPaperEff::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

void CPaperEff::InitParticle(HU3DPARTICLEDATA* p)
{
    p->time = 0;
    p->parManId = (frand() & 15) + 4;
    p->pos.x = m_pos.x + 50.0f * ((1.0f / 32768) * ((frand() & 0xFFFF) - 32768.0f));
    p->pos.y = m_pos.y;
    p->pos.z = m_pos.z + 50.0f * ((1.0f / 32768) * ((frand() & 0xFFFF) - 32768.0f));
    p->scale = 100.0f * (0.2f + 0.2f * ((1.0f / 65536) * (frand() & 0xFFFF)));
    p->zRot = (float)(M_PI / 180.0) * (360.0f * ((1.0f / 65536) * (frand() & 0xFFFF)));
    u32 rgb = frand();
    p->color.r = rgb & 0xFF;
    p->color.g = (rgb >> 8) & 0xFF;
    p->color.b = (rgb >> 16) & 0xFF;
    p->color.a = 0;
}

/* the first call (count 0) spawns every particle; then fade in by 16 to 0xFF (time 0 -> 1), fade out by the
 * particle's speed and respawn below 20; spin 1 degree a frame */
void CPaperEff::Update(Mtx m)
{
    HU3DMODEL* model = &Hu3DData[m_model]; /* unused (retail keeps the store) */
    HU3DPARTICLE* particle = m_particle;
    int i;
    HU3DPARTICLEDATA* p;
    if (particle->count == 0) {
        for (i = 0, p = particle->data; i < particle->maxCnt; i++, p++) {
            InitParticle(p);
        }
    }
    for (i = 0, p = particle->data; i < particle->maxCnt; i++, p++) {
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
    }
}

void CPaperEff::SetPos(Vec* pos)
{
    m_pos = *pos;
}

void CPaperEff::SetVel(Vec* vel)
{
    m_vel = *vel;
}

/* front / back cut-out textures per character (rodata 4C8 / 4FC, read in place) */
static const u32 s_frontTbl[CPaperTex::NUM_CHAR] = {
    0x4B0014, 0x4B0016, 0x4B0018, 0x4B001A, 0x4B001C, 0x4B001E, 0x4B0020,
    0x4B0022, 0x4B0024, 0x4B0026, 0x4B0028, 0x4B002A, 0x4B002C,
};
static const u32 s_backTbl[CPaperTex::NUM_CHAR] = {
    0x4B0015, 0x4B0017, 0x4B0019, 0x4B001B, 0x4B001D, 0x4B001F, 0x4B0021,
    0x4B0023, 0x4B0025, 0x4B0027, 0x4B0029, 0x4B002B, 0x4B002D,
};

/* only the team players (grp != 0) get textures: only they can be flattened */
CPaperTex::CPaperTex()
{
    for (int i = 0; i < NUM_PLAYER; i++) {
        int charNo = GwPlayerConf[i].charNo;
        if (GwPlayerConf[i].grp == 0) {
            m_front[i] = 0;
            m_back[i] = 0;
        } else {
            m_front[i] = HuSprAnimRead(HuDataSelHeapReadNum(s_frontTbl[charNo], HU_MEMNUM_OVL, HEAP_MODEL));
            HuSprAnimLock(m_front[i]);
            m_back[i] = HuSprAnimRead(HuDataSelHeapReadNum(s_backTbl[charNo], HU_MEMNUM_OVL, HEAP_MODEL));
            HuSprAnimLock(m_back[i]);
        }
    }
}

CPaperTex::~CPaperTex()
{
    for (int i = 0; i < NUM_PLAYER; i++) {
        if (m_front[i] != 0 && m_back[i] != 0) {
            HuSprAnimKill(m_front[i]);
            HuSprAnimKill(m_back[i]);
        }
    }
}

ANIMDATA* CPaperTex::GetFront(int idx)
{
    return m_front[idx];
}

ANIMDATA* CPaperTex::GetBack(int idx)
{
    return m_back[idx];
}

void CPaper::DrawHook(HU3DMODEL* model, Mtx* mtx)
{
    CPaper* self = (CPaper*)model->hookData;
    self->Draw(mtx);
}

CPaper::CPaper(Vec* pos, Vec* target, Vec* rot, int idx) : m_time(0.0f), m_done(false), m_state(0)
{
    HU3DMODELID id = Hu3DHookFuncCreate(DrawHook);
    Hu3DModelLayerSet((int)id, 4);
    Hu3DModelCameraSet((int)id, 1);
    HU3DMODEL* model = &Hu3DData[(int)id];
    model->hookData = this;
    m_model = (int)id;
    CPaperTex* tex = CPaperTex::GetInstance();
    m_front = tex->GetFront(idx);
    m_back = tex->GetBack(idx);
    m_pos = *pos;
    m_target = *target;
    m_rot = *rot;
    ANIMBMP* bmp = m_front->bmp;
    m_size.x = 2.0f * (bmp->sizeX / 256.0f);
    m_size.z = 2.0f * (bmp->sizeY / 256.0f);
    m_unk44.x = 0.0f;
    m_unk44.y = 0.0f;
    m_unk44.z = 0.0f;
    InitMesh();
    m_eff.reset(new CPaperEff(&m_pos));
    m_pos.y += 1800 * (1.0f / 60); /* 30.000002f (0x41F00001) */
    m_se = PlaySe(0x6F3, m_pos);
}

CPaper::~CPaper()
{
    m_eff.reset(0);
    HuAudFXStop(m_se);
    Hu3DModelKill(m_model);
}

void CPaper::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

/* retail keeps the returned distance through one inline level (two fmr) */
static inline float Mag(Vec* v)
{
    return PSVECMag(v);
}

/* 0: sink to y 0 for 1 s; 1: float 1/120 of the way to the gallery spot until within 200; 2: done; then ripple and
 * carry the confetti along */
void CPaper::on_update()
{
    switch (m_state) {
    case 0:
        m_time += 1.0 / 60.0;
        m_pos.y += -m_pos.y / 60.0f;
        if (m_time < 1.0f) {
            break;
        }
        m_time = 0.0f;
        m_state++;
    case 1: {
        float rate = 120.0f; /* a variable, not a literal: retail holds it in f31 */
        m_pos.x += (m_target.x - m_pos.x) / rate;
        m_pos.y += (m_target.y - m_pos.y) / rate;
        m_pos.z += (m_target.z - m_pos.z) / rate;
        Vec d;
        PSVECSubtract(&m_pos, &m_target, &d);
        float dist = Mag(&d);
        m_time += 1.0 / 60.0;
        if (dist > 200.0f) {
            break;
        }
        m_state++;
    }
    case 2:
        m_done = true;
        m_state++;
        break;
    }
    Wave(m_state);
    m_eff->SetPos(&m_pos);
}

/* a two-sided textured quad mesh: RotY(rot.y) then the position, the front texture culled back, the back texture
 * culled front; texture colour, texture alpha * 0.6 (TEVREG0 alpha 0x99) */
void CPaper::Draw(Mtx* view)
{
    Mtx trans;
    Mtx rot;
    Vec pos = m_pos;
    PSMTXRotRad(rot, 'y', (float)(M_PI / 180.0) * m_rot.y);
    PSMTXTrans(trans, pos.x, pos.y, pos.z);
    PSMTXConcat(trans, rot, trans);
    PSMTXConcat(*view, trans, trans);
    GXLoadPosMtxImm(trans, GX_PNMTX0);
    HuSprTexLoad(m_front, 0, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    HuSprTexLoad(m_back, 0, GX_TEXMAP1, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXColor color = { 0xFF, 0xFF, 0xFF, 0x99 };
    GXSetTevColor(GX_TEVREG0, color);
    /* zero channels with a COLOR0A0 channel control and TEV order (retail; harmless on hardware) */
    GXSetNumChans(0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetCullMode(GX_CULL_BACK);
    DrawMesh(false);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetCullMode(GX_CULL_FRONT);
    DrawMesh(true);
}

/* a flat 9x9 grid of m_size (x = width, z = height), 100 units per texture unit, centred */
void CPaper::InitMesh()
{
    Vec* v = &m_mesh[0][0];
    int i;
    int j;
    for (i = 0; i < MESH_N; i++) {
        for (j = 0; j < MESH_N; j++, v++) {
            v->x = m_size.x * (100.0f * (0.125f * j - 0.5f));
            v->y = 0.0f;
            v->z = m_size.z * (100.0f * (0.125f * i - 0.5f));
        }
    }
}

/* while floating (state 1): rows ripple, fading with the height reached (retail divides by m_target.y, 800 from
 * the player: a zero would give inf/NaN) */
void CPaper::Wave(int state)
{
    if (state == 1) {
        Vec* v = &m_mesh[0][0];
        float ph = 2.0f * m_time;
        float k = 1.0f; /* dead initialiser (retail loads it) */
        k = 1.0f - m_pos.y / m_target.y;
        ph *= 5.0f * k;
        int i;
        int j;
        for (i = 0; i < MESH_N; i++) {
            for (j = 0; j < MESH_N; j++, v++) {
                float a = ph + M_PI * (i * 20) / 180.0;
                v->y = k * (50.0 * sin(a));
            }
        }
    }
}

/* 8x8 quads (v[i][j], v[i][j+1], v[i+1][j+1], v[i+1][j]); s = j/8, t = i/8 (front) or 1 - i/8 (back) */
void CPaper::DrawMesh(bool back)
{
    Vec* mesh = &m_mesh[0][0];
    GXBegin(GX_QUADS, GX_VTXFMT0, 256);
    for (int i = 0; i < MESH_N - 1; i++) {
        int row0 = i * MESH_N;
        int row1 = (i + 1) * MESH_N;
        float t0;
        float t1;
        if (!back) {
            t0 = 0.125f * i;
            t1 = 0.125f * (i + 1);
        } else {
            t0 = 1.0f - 0.125f * i;
            t1 = 1.0f - 0.125f * (i + 1);
        }
        for (int j = 0; j < MESH_N - 1; j++) {
            int col0 = j;
            int col1 = j + 1;
            float s0 = 0.125f * j;
            float s1 = 0.125f * (j + 1);
            Vec* v0 = mesh + row0 + col0;
            Vec* v1 = mesh + row0 + col1;
            Vec* v2 = mesh + row1 + col1;
            Vec* v3 = mesh + row1 + col0;
            GXPosition3f32(v0->x, v0->y, v0->z);
            GXTexCoord2f32(s0, t0);
            GXPosition3f32(v1->x, v1->y, v1->z);
            GXTexCoord2f32(s1, t0);
            GXPosition3f32(v2->x, v2->y, v2->z);
            GXTexCoord2f32(s1, t1);
            GXPosition3f32(v3->x, v3->y, v3->z);
            GXTexCoord2f32(s0, t1);
        }
    }
    GXEnd();
}

} // namespace m517
