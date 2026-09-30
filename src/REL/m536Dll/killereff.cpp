/* killereff.cpp -- the Bullet Bill particle effects (fork E: every body written; 32/36 raw, the other 4 differ only in unmapped data labels).
 * Retail emits, per effect class and in this order: ctor, the TLinkItem<T> dtor copy (weak), the dtor,
 * DeleteAll, UpdateAll, Update, the particle hook; the three list walks, the __sinit and the three list
 * dtors follow at the end of the unit (template instances). */
#include "REL/m536Dll/killereff.h"
#include "REL/mgcpp/random.h"

namespace m536 {

/* lbl_1_bss_A28: the particle sprite bank (declared before the lists: first in .bss) */
static ANIMDATA* s_anim;

TLinkList<CKillerSpark> CKillerSpark::list;
TLinkList<CKillerSmoke> CKillerSmoke::list;
TLinkList<CKillerBomb> CKillerBomb::list;

CKillerEffMan::CKillerEffMan()
{
    s_anim = HuSprAnimDataRead(0x5E000E);
    HuSprAnimLock(s_anim);
}

CKillerEffMan::~CKillerEffMan()
{
    CKillerSpark::DeleteAll();
    CKillerSmoke::DeleteAll();
    CKillerBomb::DeleteAll();
    HuSprAnimKill(s_anim);
}

void CKillerEffMan::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

void CKillerEffMan::on_update()
{
    CKillerSpark::UpdateAll();
    CKillerSmoke::UpdateAll();
    CKillerBomb::UpdateAll();
}

CKillerSpark::CKillerSpark(Vec* pos)
{
    insertBack(&list);
    m_id = Hu3DParticleCreate(s_anim, 1);
    Hu3DModelPosSetV(m_id, pos);
    Hu3DModelLayerSet(m_id, 6);
    Hu3DParticleScaleSet(m_id, 100.0f);
    Hu3DParticleHookSet(m_id, Hook);
    Hu3DParticleTPLvlSet(m_id, 0.0f);
    Hu3DParticleBlendModeSet(m_id, 0);
    m_unk0C = 0;
}

CKillerSpark::~CKillerSpark()
{
    Hu3DModelKill(m_id);
}

void CKillerSpark::DeleteAll()
{
    while (!list.isEmpty()) {
        CKillerSpark* e = list.last();
        delete e;
    }
}

void CKillerSpark::UpdateAll()
{
    TLinkList<CKillerSpark>::exec(&list, Update);
}

/* deletes e once the hook has marked the particle set dead (the host list walk reads next first) */
void CKillerSpark::Update(CKillerSpark* e)
{
    HU3DPARTICLE* particle = (HU3DPARTICLE*)Hu3DData[e->m_id].hookData;
    if (particle->dataCnt < 0) {
        delete e;
    }
}

/* orange sparks: random velocity, fade to white while the alpha drops by 8 a frame */
void CKillerSpark::Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx)
{
    HU3DPARTICLEDATA* end = &particle->data[particle->maxCnt];
    int count = 0;
    if (particle->count == 0) {
        for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
            data->vel.x = 5.0f * (CRandom::randomMantissa() - 0.5f);
            data->vel.y = 5.0f * (CRandom::randomMantissa() - 0.5f);
            data->vel.z = 5.0f * (CRandom::randomMantissa() - 0.5f);
            data->pos.x = data->pos.y = data->pos.z = 0.0f;
            data->color.r = 0xFF;
            data->color.g = 0x80;
            data->color.b = 0x00;
            data->color.a = 0xFF;
        }
    }
    for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
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

CKillerSmoke::CKillerSmoke(Vec* pos, float rot)
{
    insertBack(&list);
    m_id = Hu3DParticleCreate(s_anim, 32);
    Hu3DModelPosSetV(m_id, pos);
    Hu3DModelRotSet(m_id, 0.0f, rot, 0.0f);
    Hu3DModelLayerSet(m_id, 6);
    Hu3DParticleScaleSet(m_id, 0.0f);
    Hu3DParticleHookSet(m_id, Hook);
    Hu3DParticleTPLvlSet(m_id, 0.0f);
    Hu3DParticleBlendModeSet(m_id, 0);
    m_unk0C = 0;
}

CKillerSmoke::~CKillerSmoke()
{
    Hu3DModelKill(m_id);
}

void CKillerSmoke::DeleteAll()
{
    while (!list.isEmpty()) {
        CKillerSmoke* e = list.last();
        delete e;
    }
}

void CKillerSmoke::UpdateAll()
{
    TLinkList<CKillerSmoke>::exec(&list, Update);
}

/* deletes e once the hook has marked the particle set dead (the host list walk reads next first) */
void CKillerSmoke::Update(CKillerSmoke* e)
{
    HU3DPARTICLE* particle = (HU3DPARTICLE*)Hu3DData[e->m_id].hookData;
    if (particle->dataCnt < 0) {
        delete e;
    }
}

/* muzzle ring: 32 particles thrown out in the model's XY plane, slowing (x0.95) and fading (alpha -4) */
void CKillerSmoke::Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx)
{
    HU3DPARTICLEDATA* end = &particle->data[particle->maxCnt];
    if (particle->count == 0) {
        for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
            float angle = M_PI * (360.0f * CRandom::randomMantissa() - 180.0f) / 180.0;
            data->vel.x = 10.0 * cos(angle);
            data->vel.y = 10.0 * sin(angle);
            data->vel.z = 0.0f;
            data->pos.x = 0.0f;
            data->pos.y = 0.0f;
            data->pos.z = 0.0f;
            data->color.r = 0xE0;
            data->color.g = 0xE8;
            data->color.b = 0xFF;
            data->color.a = 0x80;
            data->scale = 150.0f;
        }
    }
    int count = 0;
    for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
        PSVECAdd(&data->vel, &data->pos, &data->pos);
        data->vel.x *= 0.95;
        data->vel.y *= 0.95;
        data->vel.z *= 0.95;
        int a = data->color.a;
        a -= 4;
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

CKillerBomb::CKillerBomb(Vec* pos)
{
    insertBack(&list);
    m_id = Hu3DParticleCreate(s_anim, 32);
    Hu3DModelPosSetV(m_id, pos);
    Hu3DModelRotSet(m_id, 0.0f, 0.0f, 0.0f);
    Hu3DModelLayerSet(m_id, 6);
    Hu3DParticleScaleSet(m_id, 0.0f);
    Hu3DParticleHookSet(m_id, Hook);
    Hu3DParticleTPLvlSet(m_id, 0.0f);
    Hu3DParticleBlendModeSet(m_id, 0);
    m_unk0C = 0;
}

CKillerBomb::~CKillerBomb()
{
    Hu3DModelKill(m_id);
}

void CKillerBomb::DeleteAll()
{
    while (!list.isEmpty()) {
        CKillerBomb* e = list.last();
        delete e;
    }
}

void CKillerBomb::UpdateAll()
{
    TLinkList<CKillerBomb>::exec(&list, Update);
}

/* deletes e once the hook has marked the particle set dead (the host list walk reads next first) */
void CKillerBomb::Update(CKillerBomb* e)
{
    HU3DPARTICLE* particle = (HU3DPARTICLE*)Hu3DData[e->m_id].hookData;
    if (particle->dataCnt < 0) {
        delete e;
    }
}

/* lbl_1_data_314: the explosion's particle direction before the random rotation (non-const .data) */
static Vec s_bombDir = { 0.0f, 0.0f, 10.0f };

/* explosion: 32 particles along s_bombDir turned by a random X and Y rotation; they slow (x0.95), redden
 * to black, fade (alpha -8) and grow by 5 a frame (also after the set is marked dead: retail order) */
void CKillerBomb::Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx)
{
    HU3DPARTICLEDATA* end = &particle->data[particle->maxCnt];
    if (particle->count == 0) {
        for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
            Mtx mx;
            Mtx my;
            Vec dir;
            float rx = 360.0f * CRandom::randomMantissa() - 180.0f;
            float ry = 360.0f * CRandom::randomMantissa() - 180.0f;
            PSMTXRotRad(mx, 'x', 0.017453292f * rx);
            PSMTXRotRad(my, 'y', 0.017453292f * ry);
            PSMTXConcat(mx, my, mx);
            PSMTXMultVec(mx, &s_bombDir, &dir);
            data->vel = dir;
            data->pos.x = 0.0f;
            data->pos.y = 0.0f;
            data->pos.z = 0.0f;
            data->color.r = 0xE0;
            data->color.g = 0xE8;
            data->color.b = 0x00;
            data->color.a = 0xFF;
            data->scale = 50.0f;
        }
    }
    int count = 0;
    for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
        PSVECAdd(&data->vel, &data->pos, &data->pos);
        data->vel.x *= 0.95;
        data->vel.y *= 0.95;
        data->vel.z *= 0.95;
        int r = data->color.r;
        r -= 8;
        if (r < 0) {
            r = 0;
        }
        data->color.r = r;
        int g = data->color.g;
        g -= 0x10;
        if (g < 0) {
            g = 0;
        }
        data->color.g = g;
        int a = data->color.a;
        a -= 8;
        if (a < 0) {
            a = 0;
            data->scale = 0.0f;
            particle->dataCnt = -1;
        }
        data->color.a = a;
        data->scale += 5.0f;
        count++;
    }
    particle->emitCnt = count;
}

} // namespace m536
