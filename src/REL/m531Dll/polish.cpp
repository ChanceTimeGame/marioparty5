/* polish.cpp -- the particle/draw effects of polish.h, in retail order; ~CSparkle and ~CSpray are implicit and
 * land at the unit end. Every function written whole (W1 fork F5). */
#include "REL/m531Dll/polish.h"
extern "C" {
#include "game/frand.h"
}

/* frand() & 0xFFFF as an unsigned fraction 0..1 and as a signed -1..1 (the unsigned int->float is retail) */
#define RAND_U() ((1.0f / 65536.0f) * (frand() & 0xFFFF))
#define RAND_S() ((1.0f / 32768.0f) * ((frand() & 0xFFFF) - 32768.0f))

namespace m531 {

/* the ctors and hooks read m_model / m_particle through accessors (retail: lha+extsh+mr / lwz+mr copies) */
static inline s16 ModelOf(CParticleEffect* e)
{
    return (s16)e->m_model;
}

static inline HU3DPARTICLE* ParticleOf(CParticleEffect* e)
{
    return e->m_particle;
}

CLandSmoke::CLandSmoke(Vec pos) : CParticleEffect(0x590002, 8, 1)
{
    s16 model = ModelOf(this);

    Hu3DParticleColSet(model, 255, 255, 255);
    Hu3DParticleTPLvlSet(model, 0.0f);
    Hu3DParticleBlendModeSet(model, 0);
    Hu3DParticleHookSet(model, Hook);
    Hu3DModelLayerSet(model, 5);
    Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
}

void CLandSmoke::on_hook(Mtx mtx)
{
    HU3DMODEL* model = &Hu3DData[ModelOf(this)];
    HU3DPARTICLE* particle = ParticleOf(this);
    HU3DPARTICLEDATA* data;
    int i;
    int alive;

    if (particle->count == 0) {
        data = particle->data;
        for (i = 0; i < particle->maxCnt; i++, data++) {
            data->vel.x = sin(0.017453292f * (360.0f * i / particle->maxCnt));
            data->vel.y = 0.01f + RAND_U();
            data->vel.z = cos(0.017453292f * (360.0f * i / particle->maxCnt));
            data->scale = 100.0f + 50.0f * RAND_U();
            data->pos.x = 0.05f * (100.0f * data->vel.x);
            data->pos.y = 0.0f;
            data->pos.z = 0.05f * (100.0f * data->vel.z);
            data->color.a = 0;
            data->time = 0;
            data->parManId = 0;
            data->zRot = 0.017453292f * (360.0f * RAND_U());
        }
    }
    data = particle->data;
    alive = 0;
    for (i = 0; i < particle->maxCnt; i++, data++) {
        if (data->time != 0 && data->color.a == 0) {
            continue;
        }
        if (data->time == 0) {
            data->color.a += 16;
            if (data->color.a >= 240) {
                data->color.a = 240;
                data->time++;
            }
        } else if (data->color.a != 0) {
            data->color.a -= 8;
        }
        alive++;
        data->scale += 0.1f * data->parManId++;
        /* retail: an unparenthesised ABS(600 - scale) -- the negative branch is -600 - scale */
        float spread;
        if (600.0f - data->scale < 0.0f) {
            spread = -600.0f - data->scale;
        } else {
            spread = 600.0f - data->scale;
        }
        float k = 0.005f * spread;
        if (data->scale <= 0.0f) {
            data->color.a = 0;
        }
        data->pos.x += data->vel.x * k;
        data->pos.y += data->vel.y;
        data->pos.z += data->vel.z * k;
    }
    if (alive == 0) {
        delete this;
    }
}

CLandSmoke::~CLandSmoke() {}

CSpray::CSpray(u32 dataNum, int count, Vec pos, Vec rot) : CParticleEffect(dataNum, count, 1)
{
    s16 model = ModelOf(this);

    Hu3DParticleColSet(model, 0xE0, 0xFF, 0xFF);
    Hu3DParticleBlendModeSet(model, 0);
    Hu3DParticleHookSet(model, Hook);
    Hu3DModelLayerSet(model, 5);
    Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
    Hu3DModelRotSet(model, rot.x, rot.y, rot.z);
}

void CSpray::on_hook(Mtx mtx)
{
    HU3DMODEL* model = &Hu3DData[ModelOf(this)];
    HU3DPARTICLE* particle = ParticleOf(this);
    HU3DPARTICLEDATA* data;
    int i;

    if (particle->count == 0) {
        for (i = 0, data = particle->data; i < particle->maxCnt; i++, data++) {
            data->vel.x = 0.0f;
            data->vel.y = 0.0f;
            data->vel.z = 10.0f;
            data->scale = 0.0f;
            data->pos.x = 0.0f;
            data->pos.y = 0.0f;
            data->pos.z = i * (150.0f / particle->maxCnt);
            data->color.a = 255;
            data->time = 0;
            data->parManId = 0;
            data->zRot = 0.017453292f * (360.0f * RAND_U());
        }
    }
    for (i = 0, data = particle->data; i < particle->maxCnt; i++, data++) {
        if (data->pos.z > 150.0f) {
            data->pos.x = 0.0f;
            data->pos.y = 0.0f;
            data->pos.z = 0.0f;
            data->scale = 0.0f;
            data->color.a = 255;
        } else {
            data->pos.x += data->vel.x;
            data->pos.y += data->vel.y;
            data->pos.z += data->vel.z;
            data->scale = data->pos.z / 1.5f;
        }
    }
}

CConfetti::CConfetti(int count, Vec pos, Vec rot) : CParticleEffect(0x590004, count, 1)
{
    s16 model = ModelOf(this);

    Hu3DParticleColSet(model, 255, 255, 255);
    Hu3DParticleTPLvlSet(model, 0.0f);
    Hu3DParticleBlendModeSet(model, 1);
    Hu3DParticleHookSet(model, Hook);
    Hu3DModelLayerSet(model, 5);
    Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
    Hu3DModelRotSet(model, rot.x, rot.y, rot.z);
}

void CConfetti::on_hook(Mtx mtx)
{
    HU3DMODEL* model = &Hu3DData[ModelOf(this)];
    HU3DPARTICLE* particle = ParticleOf(this);
    HU3DPARTICLEDATA* data;
    int i;

    if (particle->count == 0) {
        for (i = 0, data = particle->data; i < particle->maxCnt; i++, data++) {
            data->vel.y = 0.0f;
            /* vel.x keeps the base scale */
            data->scale = 100.0f * (0.25f + 0.25f * RAND_U());
            data->vel.x = data->scale;
            data->pos.x = 150.0f * RAND_S();
            data->pos.y = 150.0f * RAND_S();
            data->pos.z = 100.0f * RAND_S();
            data->time = 0;
            data->zRot = 0.017453292f * (360.0f * RAND_U());
            u32 col = frand();
            data->color.r = col;
            data->color.g = (u8)((col >> 8) & 0xFF);
            data->color.b = (u8)((col >> 16) & 0xFF);
            data->color.a = 0;
        }
    }
    /* dataCnt counts the live pieces */
    particle->dataCnt = 0;
    for (i = 0, data = particle->data; i < particle->maxCnt; i++, data++) {
        if (data->time > 1) {
            continue;
        }
        switch (data->time) {
        case 0:
            data->color.a = data->color.a + 4.0f * (0.04f * data->scale);
            particle->dataCnt++;
            if (data->color.a < 250) {
                break;
            }
            data->color.a = 255;
            data->time++;
            /* fall through */
        case 1:
            data->color.a = data->color.a - 4.0f * (0.04f * data->scale);
            data->scale = data->vel.x * (data->color.a / 255.0f);
            if (data->scale < 0.0f) {
                data->scale = 0.0f;
            }
            particle->dataCnt++;
            if (data->color.a <= 8) {
                data->time++;
            }
            break;
        }
        data->zRot += 0.017453292f * data->vel.y;
        data->vel.y += 0.002724069383556748;
        data->pos.y -= data->vel.y;
    }
    if (particle->dataCnt == 0) {
        delete this;
    }
}

CConfetti::~CConfetti() {}

CSparkle::CSparkle(int count, Vec center, Vec rot) : CParticleEffect(0x590004, count, 1)
{
    s16 model = ModelOf(this);

    Hu3DParticleColSet(model, 255, 255, 255);
    Hu3DParticleTPLvlSet(model, 0.0f);
    Hu3DParticleBlendModeSet(model, 1);
    Hu3DParticleHookSet(model, Hook);
    Hu3DModelLayerSet(model, 5);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    m_center = center;
    m_rot = rot;
    hide();
}

void CSparkle::Respawn(HU3DPARTICLEDATA* data)
{
    data->time = 0;
    data->parManId = (frand() & 15) + 4;
    data->pos.x = m_center.x + 50.0f * RAND_S();
    data->pos.y = 50.0f + 50.0f * RAND_S();
    data->pos.z = m_center.z + 50.0f * RAND_S();
    data->scale = 100.0f * (0.2f + 0.2f * RAND_U());
    data->zRot = 0.017453292f * (360.0f * RAND_U());
    u32 col = frand();
    data->color.r = col;
    data->color.g = (u8)((col >> 8) & 0xFF);
    data->color.b = (u8)((col >> 16) & 0xFF);
    data->color.a = 0;
}

void CSparkle::on_hook(Mtx mtx)
{
    HU3DMODEL* model = &Hu3DData[ModelOf(this)];
    HU3DPARTICLE* particle = ParticleOf(this);
    HU3DPARTICLEDATA* data;
    int i;

    if (particle->count == 0) {
        for (i = 0, data = particle->data; i < particle->maxCnt; i++, data++) {
            Respawn(data);
        }
    }
    for (i = 0, data = particle->data; i < particle->maxCnt; i++, data++) {
        if (data->time == 0) {
            data->color.a += 4;
            if (data->color.a > 250) {
                data->color.a = 255;
                data->time++;
            }
        } else {
            data->color.a = (u8)(data->color.a - data->parManId);
            if (data->color.a < 20) {
                Respawn(data);
            }
        }
        data->zRot += 0.017453292f;
    }
}

void CSparkle::SetPos(Vec* pos)
{
    m_center = *pos;
}

void CSparkle::SetRot(Vec* rot)
{
    m_rot = *rot;
}

CDebugRect::CDebugRect(Process_s* om) : CHookEffect(om, 4, 5, 1) {}

CDebugRect::~CDebugRect() {}

void CDebugRect::on_update() {}

void CDebugRect::draw(Mtx* mtx)
{
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT0, GX_DF_CLAMP, GX_AF_SPOT);
    GXSetZCompLoc(GX_FALSE);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ONE, GX_LO_NOOP);
    GXSetAlphaUpdate(GX_TRUE);
    Vec* min = &m_min;
    Vec* max = &m_max;
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);
    GXPosition3f32(min->x, 0.0f, min->z);
    GXColor4u8(255, 40, 40, 255);
    GXPosition3f32(min->x, 0.0f, max->z);
    GXColor4u8(255, 40, 40, 255);
    GXPosition3f32(max->x, 0.0f, max->z);
    GXColor4u8(255, 40, 40, 255);
    GXPosition3f32(max->x, 0.0f, min->z);
    GXColor4u8(255, 40, 40, 255);
    GXPosition3f32(min->x, 0.0f, min->z);
    GXColor4u8(255, 40, 40, 255);
    GXEnd();
}

} // namespace m531
