#include "REL/m511Dll/config.h"
#include "REL/m511Dll/boatsplash.h"
#include "REL/m511Dll/boatshadow.h"
#include "REL/mgcpp/random.h"
extern "C" {
#include "game/frand.h"
/* no live prototype (game/sprite.h has it commented out); as m537 water.cpp */
void HuSprTexLoad(ANIMDATA* anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);
}

namespace m511 {

/* the borrowed anims (CEffTex, through GetInstance: singleton.h:39) */
static inline ANIMDATA* GetSplashAnim(CEffTex* tex)
{
    return tex->m_splashAnim;
}

static inline ANIMDATA* GetWakeAnim(CEffTex* tex)
{
    return tex->m_wakeAnim;
}

/* the arguments are evaluated right to left (retail computes z first) and stored x, y, z */
static inline void SetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void CBoatSplash::Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx)
{
    CBoatSplash* self = (CBoatSplash*)particle->work;
    self->Update(mtx);
}

CBoatSplash::CBoatSplash() : m_active(false)
{
    CEffTex* tex = CSingleton<CEffTex>::GetInstance();
    HU3DMODELID id = Hu3DParticleCreate(GetSplashAnim(tex), 32);
    m_particleData = (HU3DPARTICLE*)Hu3DData[(int)id].hookData;
    m_particleData->work = this;
    Hu3DParticleHookSet((int)id, Hook);
    Hu3DParticleColSet((int)id, 0xEF, 0xFF, 0xFF);
    Hu3DParticleTPLvlSet((int)id, 0.0f);
    Hu3DParticleBlendModeSet((int)id, 0);
    Hu3DModelAttrSet((int)id, 0x400000);
    Hu3DModelLayerSet((int)id, 3);
    Hu3DModelCameraSet((int)id, 0xF);
    Hu3DModelPosSet((int)id, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet((int)id, 0.0f, 0.0f, 0.0f);
    m_pos.x = 0.0f;
    m_pos.y = 0.0f;
    m_pos.z = 0.0f;
    m_rot.x = 0.0f;
    m_rot.y = 0.0f;
    m_rot.z = 0.0f;
    m_speed = 0.0f;
    m_particle = (int)id;
    int i;
    HU3DPARTICLEDATA* p;
    for (p = m_particleData->data, i = 0; i < m_particleData->maxCnt; i++, p++) {
        InitParticle(p, i);
    }
    m_particleData->dataCnt = 0;
    m_speed = 0.0f;
}

CBoatSplash::~CBoatSplash()
{
    Hu3DModelKill(m_particle);
}

/* one drop from the emitter 100 behind the boat: out to the side (even i to the left, odd to the right) at
 * min(7 speed, 1), up at g/9; fade step 7..22 */
void CBoatSplash::InitParticle(HU3DPARTICLEDATA* p, int i)
{
    p->time = 0;
    p->parManId = (frand() & 15) + 7;
    float side = ((i & 1) == 0) ? -1.0f : 1.0f;
    float a = M_PI * (180.0f + m_rot.y) / 180.0;
    float s = sin(a);
    float c = cos(a);
    SetVec(&m_emitPos, m_pos.x + 100.0f * s, m_pos.y, m_pos.z + 100.0f * c);
    float b;
    if (side > -1.0f) {
        b = M_PI * (m_rot.y - 90.0f) / 180.0;
    } else {
        b = M_PI * (90.0f + m_rot.y) / 180.0;
    }
    float k = 7.0f * m_speed;
    if (k > 1.0f) {
        k = 1.0f;
    }
    float vx = k * sin(b);
    float vz = k * cos(b);
    p->accel.x = vx;
    p->accel.y = k;
    p->accel.z = vz;
    p->vel.y = 1.0896277f; /* g / 9 */
    p->pos.x = m_emitPos.x + 50.0f * vx;
    p->pos.y = m_emitPos.y;
    p->pos.z = m_emitPos.z + 50.0f * vz;
    p->scale = 100.0f * (0.4f + 0.2f * ((1.0f / 65536) * (CRandom::irandom() & 0xFFFF)));
    p->zRot = 0.017453292f * (360.0f * ((1.0f / 65536) * (CRandom::irandom() & 0xFFFF)));
    static const GXColor col = { 0xEF, 0xFF, 0xFF, 0x00 };
    p->color = col;
}

void CBoatSplash::SetPos(Vec* pos, Vec* rot, float speed)
{
    m_pos = *pos;
    m_rot = *rot;
    m_speed = speed;
}

/* time 0: fade in (+16) to 128; 1: fade out by the drop's step to <= 25; 2: dead, respawned (InitParticle, inlined)
 * while m_active. Live drops spin, grow to 100, fall (g / 36 per frame) onto the floor y + 0.2 scale, drift. */
void CBoatSplash::Update(Mtx mtx)
{
    HU3DMODEL* model = &Hu3DData[m_particle]; /* unused (retail keeps the store) */
    HU3DPARTICLE* particle = m_particleData;
    int i;
    HU3DPARTICLEDATA* p;
    for (p = particle->data, i = 0; i < particle->maxCnt; i++, p++) {
        switch (p->time) {
        case 0:
            p->color.a += 16;
            if (p->color.a < 128) {
                break;
            }
            p->color.a = 128;
            p->time++;
        case 1:
            p->color.a -= p->parManId;
            if (p->color.a > 25) {
                break;
            }
            p->color.a = 0;
            p->time++;
        case 2:
            if (m_active == 1) {
                InitParticle(p, i);
            }
            continue;
        }
        p->zRot += 0.017453292f;
        p->scale += 3.0f;
        if (p->scale > 100.0f) {
            p->scale = 100.0f;
        }
        float vy = p->vel.y;
        p->vel.y += -0.27240694444444447;
        vy = 0.5f * (vy + p->vel.y);
        p->pos.y += vy;
        float floor = 0.2f * p->scale + m_pos.y;
        if (p->pos.y < floor) {
            p->pos.y = floor;
        }
        p->pos.x += p->accel.x;
        p->pos.z += p->accel.z;
    }
    DCStoreRangeNoSync(particle->data, particle->maxCnt * sizeof(HU3DPARTICLEDATA));
}

void CBoatWake::Hook(HU3DMODEL* model, Mtx* mtx)
{
    CBoatWake* self = (CBoatWake*)model->hookData;
    self->Draw(mtx);
}

CBoatWake::CBoatWake() : m_active(false), m_t(0.0f), m_power(0.0f)
{
    HU3DMODELID id = Hu3DHookFuncCreate(Hook);
    HU3DMODEL* model = &Hu3DData[(int)id];
    model->hookData = this;
    Hu3DModelLayerSet((int)id, 2);
    Hu3DModelCameraSet((int)id, 0xF);
    m_model = (int)id;
    CEffTex* tex = CSingleton<CEffTex>::GetInstance();
    m_anim = GetWakeAnim(tex);
}

CBoatWake::~CBoatWake()
{
    Hu3DModelKill(m_model);
}

/* 100 behind the boat; power = the boat's speed */
void CBoatWake::Start(Vec* pos, Vec* rot, float power)
{
    float a = M_PI * (180.0f + rot->y) / 180.0;
    float s = sin(a);
    float c = cos(a);
    SetVec(&m_pos, pos->x + 100.0f * s, pos->y, pos->z + 100.0f * c);
    m_power = power;
    m_active = true;
}

void CBoatWake::Update()
{
    if (!m_active) {
        return;
    }
    m_t += 1.0 / 60.0;
    if (m_t < 0.5f) {
        return;
    }
    m_t = 0.0f;
    m_active = false;
}

/* a +-100 square in XZ, scaled (1 + 1.5 t) min(7 power, 1), alpha 2 * 255 (0.5 - t) in TEV REG0 */
void CBoatWake::Draw(Mtx* mtx)
{
    if (!m_active) {
        return;
    }
    Mtx trans;
    Mtx m;
    PSMTXTrans(trans, m_pos.x, m_pos.y, m_pos.z);
    float k = 7.0f * m_power;
    if (k > 1.0f) {
        k = 1.0f;
    }
    float s = (1.0f + 1.5f * m_t) * k;
    PSMTXScale(m, s, 1.0f, s);
    PSMTXConcat(*mtx, trans, *mtx);
    PSMTXConcat(*mtx, m, m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    HuSprTexLoad(m_anim, 0, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZCompLoc(GX_TRUE);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetNumChans(0);
    GXSetChanCtrl(GX_COLOR_NULL, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    float a = 2.0f * (255.0f * (0.5f - m_t));
    GXColor col = { 0xFF, 0xFF, 0xFF, 0x00 };
    col.a = a;
    GXSetTevColor(GX_TEVREG0, col);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-100.0f, 0.0f, -100.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(100.0f, 0.0f, -100.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(100.0f, 0.0f, 100.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(-100.0f, 0.0f, 100.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();
}

void CKibakoSplash::Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx)
{
    CKibakoSplash* self = (CKibakoSplash*)particle->work;
    self->Update(mtx);
}

/* 40 drops in a ring (i * 360 / maxCnt), up at (20..40) g / 36, hidden until Start */
CKibakoSplash::CKibakoSplash() : m_done(false), m_started(false)
{
    CEffTex* tex = CSingleton<CEffTex>::GetInstance();
    HU3DMODELID id = Hu3DParticleCreate(GetSplashAnim(tex), 40);
    m_particleData = (HU3DPARTICLE*)Hu3DData[(int)id].hookData;
    m_particleData->work = this;
    Hu3DParticleHookSet((int)id, Hook);
    Hu3DParticleColSet((int)id, 0xEF, 0xEF, 0xFF);
    Hu3DParticleBlendModeSet((int)id, 0);
    Hu3DModelLayerSet((int)id, 3);
    Hu3DModelCameraSet((int)id, 0xF);
    Hu3DModelPosSet((int)id, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet((int)id, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet((int)id, HU3D_ATTR_DISPOFF);
    m_particle = (int)id;
    HU3DPARTICLE* particle = m_particleData;
    int i;
    HU3DPARTICLEDATA* p;
    for (p = particle->data, i = 0; i < m_particleData->maxCnt; i++, p++) {
        p->vel.x = sin(0.017453292f * (360.0f * i / particle->maxCnt));
        p->vel.y = 0.27240694444444447 * CRandom::frandom(20.0f, 40.0f);
        p->vel.z = cos(0.017453292f * (360.0f * i / particle->maxCnt));
        p->scale = 80.0f;
        p->pos.x = 0.5f * (100.0f * p->vel.x);
        p->pos.y = 0.0f;
        p->pos.z = 0.5f * (100.0f * p->vel.z);
        static const GXColor col = { 0xEF, 0xFF, 0xFF, 0x00 };
        p->color = col;
        p->time = 0;
        p->parManId = 0;
        p->zRot = 0.017453292f * CRandom::frandom(360.0f);
    }
}

CKibakoSplash::~CKibakoSplash()
{
    Hu3DModelKill(m_particle);
}

void CKibakoSplash::Start(Vec* pos)
{
    HU3DMODELID id = m_particle;
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(id, pos->x, pos->y, pos->z);
    m_started = true;
}

/* time 0: alpha +16 to 200; 1: -4 to 0; 2: dead. Hides the model once no drop is alive. */
void CKibakoSplash::Update(Mtx mtx)
{
    if (m_started && m_done != 1) {
        HU3DMODEL* model = &Hu3DData[m_particle]; /* unused (retail keeps the store) */
        HU3DPARTICLE* particle = m_particleData;
        int i;
        HU3DPARTICLEDATA* p;
        int alive;
        for (p = particle->data, alive = 0, i = 0; i < particle->maxCnt; i++, p++) {
            if (p->time == 2) {
                continue;
            }
            if (p->time == 0) {
                p->color.a += 16;
                if (p->color.a >= 200) {
                    p->color.a = 200;
                    p->time++;
                }
            } else if (p->color.a != 0) {
                p->color.a -= 4;
            } else {
                p->time++;
            }
            alive++;
            p->scale += 1.6666666666666667;
            float vy0 = p->vel.y;
            p->vel.y += -0.27240694444444447;
            float vy = 0.5f * (vy0 + p->vel.y);
            p->pos.x += (1.0 / 60.0) * (100.0f * (1.5f * p->vel.x));
            p->pos.y += vy;
            p->pos.z += (1.0 / 60.0) * (100.0f * (1.5f * p->vel.z));
        }
        DCStoreRangeNoSync(particle->data, particle->maxCnt * sizeof(HU3DPARTICLEDATA));
        if (alive == 0) {
            Hu3DModelAttrSet(m_particle, HU3D_ATTR_DISPOFF);
            m_done = true;
        }
    }
}

} // namespace m511
