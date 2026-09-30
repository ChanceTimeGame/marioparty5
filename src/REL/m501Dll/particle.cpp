/* particle.cpp -- m501::CParticle: owns the footprint model (drawn by CAsiatoMan) and makes the scoop
 * splash (landing) and burst (take) particles. */
#include "REL/m501Dll/particle.h"
#include "REL/m501Dll/asiato.h"
#include "REL/m501Dll/random.h"

namespace m501 {

/* lbl_1_rodata_1B0: splash colour per flavour (RGB) */
static const u8 s_flavorColor[8][3] = {
    { 0xF9, 0xB5, 0xCD }, { 0xF1, 0xD4, 0xA3 }, { 0x6B, 0xC0, 0xB7 }, { 0x94, 0x61, 0x3E },
    { 0x74, 0xE4, 0x82 }, { 0xF0, 0xDF, 0x6F }, { 0xFF, 0xB0, 0x6C }, { 0xF1, 0xD4, 0xA3 },
};
static ANIMDATA* s_particleAnim; /* lbl_1_bss_D0 HuSprAnimRead(0x3B0008) */

CParticle::CParticle() : m_model(0x3B0007U)
{
    s_particleAnim = HuSprAnimDataRead(0x3B0008);
    CAsiatoMan::init();
}

CParticle::~CParticle()
{
    CAsiatoMan::close();
}

void CParticle::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

void CParticle::on_update()
{
    CAsiatoMan::update();
}

CModel* CParticle::getInstance()
{
    return &GetInstance()->m_model;
}

/* fn_1_A6C0: landing splash; color is CAisu::m_type (0..7, unchecked) */
void CParticle::createSplash(Vec* pos, int color)
{
    HU3DMODELID id = Hu3DParticleCreate(s_particleAnim, 32);
    Hu3DModelPosSetV(id, pos);
    Hu3DParticleScaleSet(id, 1.0f);
    Hu3DParticleHookSet(id, splashHook);
    HU3DMODEL* model = &Hu3DData[id];
    *(const u8**)&model->motShapeWork.start = s_flavorColor[color];
}

/* fn_1_A768: take burst (flat, no gravity) */
void CParticle::createBurst(Vec* pos, int color)
{
    HU3DMODELID id = Hu3DParticleCreate(s_particleAnim, 32);
    Hu3DModelPosSetV(id, pos);
    Hu3DParticleScaleSet(id, 1.0f);
    Hu3DParticleHookSet(id, burstHook);
    HU3DMODEL* model = &Hu3DData[id];
    *(const u8**)&model->motShapeWork.start = s_flavorColor[color];
}

/* fn_1_A810: splash particles fly out, fall, bounce on y = 1 and shrink */
void CParticle::splashHook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx)
{
    HU3DPARTICLEDATA* end = &particle->data[particle->maxCnt];
    if (particle->count == 0) {
        const u8* color = *(const u8**)&model->motShapeWork.start;
        for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
            data->pos.x = 0.0f;
            data->pos.y = 0.0f;
            data->pos.z = 0.0f;
            float angle = CRandom::frandom(-3.1415927f, 3.1415927f);
            float speed = CRandom::frandom(10.0f, 20.0f);
            data->vel.x = speed * sin(angle);
            data->vel.y = CRandom::frandom(10.0f, 20.0f);
            data->vel.z = speed * cos(angle);
            data->color.r = color[0];
            data->color.g = color[1];
            data->color.b = color[2];
            data->scale = 20.0f;
        }
    }
    int count = 0;
    for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
        if (data->scale != 0.0f) {
            PSVECAdd(&data->vel, &data->pos, &data->pos);
            data->vel.x *= 0.999f;
            data->vel.y -= 3.0f;
            data->vel.z *= 0.999f;
            if (data->pos.y <= 1.0f) {
                data->pos.y = 1.0f;
                data->vel.y *= -0.8f;
            }
            data->scale -= 1.25f;
            if (data->scale <= 0.0f) {
                data->scale = 0.0f;
            }
            count++;
        }
    }
    particle->emitCnt = count;
}

/* fn_1_AAA4: burst particles fly out flat and shrink */
void CParticle::burstHook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx)
{
    HU3DPARTICLEDATA* end = &particle->data[particle->maxCnt];
    if (particle->count == 0) {
        const u8* color = *(const u8**)&model->motShapeWork.start;
        for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
            data->pos.x = 0.0f;
            data->pos.y = 0.0f;
            data->pos.z = 0.0f;
            float angle = CRandom::frandom(-3.1415927f, 3.1415927f);
            float speed = CRandom::frandom(10.0f, 20.0f);
            data->vel.x = speed * sin(angle);
            data->vel.z = speed * cos(angle);
            data->vel.y = 0.0f;
            data->color.r = color[0];
            data->color.g = color[1];
            data->color.b = color[2];
            data->scale = 20.0f;
        }
    }
    int count = 0;
    for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
        if (data->scale != 0.0f) {
            PSVECAdd(&data->vel, &data->pos, &data->pos);
            data->vel.x *= 0.999f;
            data->vel.z *= 0.999f;
            data->scale -= 2.0f;
            if (data->scale <= 0.0f) {
                data->scale = 0.0f;
            }
            count++;
        }
    }
    particle->emitCnt = count;
}

} // namespace m501
