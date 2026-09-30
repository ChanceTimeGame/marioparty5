#include "REL/m537Dll/water.h"
#include "REL/mgcpp/random.h"
extern "C" {
#include "game/hsfformat.h"
void HuSprTexLoad(ANIMDATA* anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);
}

namespace m537 {

/* ---- CMist, CSplash, CSplashModel, CWater Hook .. Splash (F5: .text 0x125AC..0x14B8C) ---- */

CMist::CMist(const Vec* pos, const Vec* rot)
{
    m_anim = HuSprAnimRead(HuDataSelHeapReadNum(0x5F0018, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_anim);
    HU3DMODELID id = Hu3DParticleCreate(m_anim, 32);
    Hu3DParticleHookSet((int)id, Hook);
    Hu3DParticleColSet((int)id, 0xFF, 0xFF, 0xFF);
    Hu3DParticleBlendModeSet((int)id, 0);
    Hu3DModelLayerSet((int)id, 4);
    Hu3DModelPosSet((int)id, pos->x, pos->y, pos->z);
    Hu3DModelRotSet((int)id, rot->x, rot->y, rot->z);
    m_particle = (int)id;
}

CMist::~CMist()
{
    HuSprAnimKill(m_anim);
    Hu3DModelKill(m_particle);
}

void CMist::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

/* fn_1_12770: the waterfall spray. First call (count == 0): spawn every particle on a ring; then per particle fade
 * in (time 0: alpha += speed up to 220), fade out (alpha > 32: alpha -= speed / 2) or respawn; grow, fall, drift. */
void CMist::Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx)
{
    HU3DPARTICLEDATA* d;
    int i;
    if (particle->count == 0) {
        d = particle->data;
        for (i = 0; i < particle->maxCnt; i++, d++) {
            d->vel.x = sin(0.017453292f * (360.0f * i / particle->maxCnt));
            d->vel.y = d->accel.y = 0.27240694f * CRandom::frandom(10.0f, 40.0f);
            d->vel.z = cos(0.017453292f * (360.0f * i / particle->maxCnt));
            d->scale = 200.0f;
            d->pos.x = 100.0f * CRandom::frandom(-3.2f, 3.2f);
            d->pos.y = 0.0f;
            d->pos.z = 100.0f * CRandom::frandom(-0.32f, 0.32f);
            d->color.a = 0;
            d->time = 0;
            d->parManId = (CRandom::irandom() & 15) + 15;
            d->zRot = 0.017453292f * CRandom::frandom(360.0f);
        }
    }
    d = particle->data;
    for (i = 0; i < particle->maxCnt; i++, d++) {
        if (d->time == 0) {
            d->color.a += d->parManId;
            if (d->color.a >= 220) {
                d->color.a = 220;
                d->time++;
            }
        } else if (d->color.a > 32) {
            d->color.a -= (u8)(0.5f * d->parManId);
        } else {
            d->pos.x = 100.0f * CRandom::frandom(-3.2f, 3.2f);
            d->pos.y = 0.0f;
            d->pos.z = 100.0f * CRandom::frandom(-0.32f, 0.32f);
            d->vel.y = d->accel.y;
            d->scale = 200.0f;
            d->color.a = 0;
            d->parManId = (CRandom::irandom() & 15) + 15;
            d->time = 0;
        }
        d->scale += 3.3333333333333335;
        float vy = d->vel.y;
        d->vel.y += -0.27240694f;
        float dy = 0.5f * (vy + d->vel.y);
        d->pos.x += (1.0 / 60.0) * (100.0f * (2.0f * d->vel.x));
        d->pos.y += dy;
        d->pos.z += (1.0 / 60.0) * (100.0f * (2.0f * d->vel.z));
    }
}

void CSplash::Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx)
{
    CSplash* self = (CSplash*)particle->work;
    self->Update(mtx);
}

CSplash::CSplash(const Vec* pos)
{
    m_anim = HuSprAnimRead(HuDataSelHeapReadNum(0x5F0017, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_anim);
    HU3DMODELID id = Hu3DParticleCreate(m_anim, 32);
    m_particleData = (HU3DPARTICLE*)Hu3DData[(int)id].hookData;
    m_particleData->work = this;
    Hu3DParticleHookSet((int)id, Hook);
    Hu3DParticleColSet((int)id, 0xFF, 0xFF, 0xFF);
    Hu3DParticleBlendModeSet((int)id, 0);
    Hu3DModelLayerSet((int)id, 4);
    Hu3DModelPosSet((int)id, pos->x, pos->y, pos->z);
    Hu3DModelRotSet((int)id, 0.0f, 0.0f, 0.0f);
    m_particle = (int)id;
}

CSplash::~CSplash()
{
    HuSprAnimKill(m_anim);
    Hu3DModelKill(m_particle);
}

void CSplash::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

void CSplash::Update(Mtx mtx)
{
    HU3DMODEL* model = &Hu3DData[m_particle];
    HU3DPARTICLE* particle = m_particleData;
    HU3DPARTICLEDATA* d;
    int i;
    if (particle->count == 0) {
        d = particle->data;
        for (i = 0; i < particle->maxCnt; i++, d++) {
            d->vel.x = sin(0.017453292f * (360.0f * i / particle->maxCnt));
            d->vel.y = 0.27240694f * CRandom::frandom(20.0f, 80.0f);
            d->vel.z = cos(0.017453292f * (360.0f * i / particle->maxCnt));
            d->scale = 200.0f;
            d->pos.x = 0.5f * (100.0f * d->vel.x);
            d->pos.y = 0.0f;
            d->pos.z = 0.5f * (100.0f * d->vel.z);
            d->color.a = 0;
            d->time = 0;
            d->parManId = 0;
            d->zRot = 0.017453292f * CRandom::frandom(360.0f);
        }
    }
    d = particle->data;
    int alive = 0;
    for (i = 0; i < particle->maxCnt; i++, d++) {
        if (d->time == 2) {
            continue;
        }
        if (d->time == 0) {
            d->color.a += 16;
            if (d->color.a >= 200) {
                d->color.a = 200;
                d->time++;
            }
        } else if (d->color.a != 0) {
            d->color.a -= 4;
        } else {
            d->time++;
        }
        alive++;
        d->scale += 1.6666666666666667;
        float vy = d->vel.y;
        d->vel.y += -0.27240694f;
        float dy = 0.5f * (vy + d->vel.y);
        d->pos.x += (1.0 / 60.0) * (100.0f * (2.0f * d->vel.x));
        d->pos.y += dy;
        d->pos.z += (1.0 / 60.0) * (100.0f * (2.0f * d->vel.z));
    }
    if (alive == 0) {
        delete this;
    }
}

CSplashModel::CSplashModel(const Vec* pos) : CModel(0x5F0013u)
{
    HU3DMODELID id = ((CModel*)this)->id();
    Hu3DModelLayerSet((int)id, 4);
    Hu3DModelLightInfoSet((int)id, 0);
    Hu3DModelPosSet((int)id, pos->x, 0.0f, pos->z);
    Hu3DModelRotSet((int)id, 0.0f, 0.0f, 0.0f);
    HuAudFXPlay(0x7DB);
}

CSplashModel::~CSplashModel() {}

void CSplashModel::on_update()
{
    HU3DMODELID id = ((CModel*)this)->id();
    if (Hu3DMotionEndCheck((int)id)) {
        delete this;
    }
}

void CSplashModel::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

void CWater::Hook(HU3DMODEL* model, Mtx* mtx)
{
    CWater* self = CSingleton<CWater>::GetInstancePtr();
    self->Draw(mtx);
}

/* lbl_1_rodata_670 / 694: the three waterfall feet (CMist positions, AddForce points) and the spray rotations */
static const Vec s_mistPos[CWater::NUM_MIST] = { { -1600.0f, 0.0f, 650.0f }, { 0.0f, 0.0f, -1600.0f }, { 1400.0f, 0.0f, 0.0f } };
static const Vec s_mistRot[CWater::NUM_MIST] = { { 0.0f, 120.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 90.0f, 0.0f } };

CWater::CWater(s16 stageModel)
{
    m_stageModel = (int)stageModel;
    m_time = 0.0f;
    m_se = HuAudFXPlay(0x7D8);
    HU3DMODELID id = Hu3DHookFuncCreate(Hook);
    Hu3DModelLayerSet((int)id, 3);
    Hu3DModelCameraSet((int)id, 1);
    m_takiWarpAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x5F0016, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_takiWarpAnim);
    m_surfaceAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x5F0015, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_surfaceAnim);
    m_takiAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x5F0014, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_takiAnim);
    m_model = Hu3DModelCreate(HuDataSelHeapReadNum(0x5F0012, HU_MEMNUM_OVL, HEAP_MODEL));
    m_scroll.x = 0.0f;
    m_scroll.y = 0.0f;
    m_scroll.z = 0.0f;
    InitTaki();
    for (int i = 0; i < NUM_MIST; i++) {
        new CMist(&s_mistPos[i], &s_mistRot[i]);
    }
    InitMesh();
    InitTexObj();
}

CWater::~CWater()
{
    HuSprAnimKill(m_takiWarpAnim);
    HuSprAnimKill(m_surfaceAnim);
    HuSprAnimKill(m_takiAnim);
    Hu3DModelKill(m_model);
    HuAudFXStop(m_se);
}

/* lbl_1_data_6C4: the waterfall objects of 0x5F0012 (a .data table, relocated) */
static const char* s_takiName[CWater::NUM_TAKI] = { "taki_a", "taki_b", "taki_c" };

void CWater::InitTaki()
{
    for (int i = 0; i < NUM_TAKI; i++) {
        m_taki[i] = Hu3DModelObjPtrGet(m_model, (char*)s_takiName[i]);
    }
    Hu3DModelAttrSet(m_model, HU3D_ATTR_DISPOFF);
}

static inline void SetVec3(Vec& v, float x, float y, float z)
{
    v.x = x;
    v.y = y;
    v.z = z;
}

/* fn_1_13AC8: the rest grid (200 apart, centred), uv = cell / 32, colour 0, velocity 0 */
void CWater::InitMesh()
{
    int x;
    int y;
    for (y = 0; y < MESH_N; y++) {
        for (x = 0; x < MESH_N; x++) {
            Vec* pos = &m_meshPos[y][x];
            Vec* uv = &m_meshUV[y][x];
            GXColor* col = &m_meshCol[y][x];
            pos->x = 200.0f * x - 3200.0f;
            pos->y = 0.0f;
            pos->z = 200.0f * y - 3200.0f;
            uv->x = 0.03125f * x;
            uv->z = 0.03125f * y;
            col->r = col->g = col->b = col->a = 0;
            SetVec3(m_meshVel[y][x], 0.0f, 0.0f, 0.0f);
        }
    }
}

void CWater::UpdateMesh()
{
    int y;
    int x;
    Vec tmp[MESH_N][MESH_N];
    Vec force;
    Vec dir;
    Vec spring;
    Vec step;
    Vec* p = &m_meshPos[0][0];
    for (y = 0; y < MESH_N; y++) {
        for (x = 0; x < MESH_N; x++, p++) {
            tmp[y][x].x = p->x;
            tmp[y][x].y = p->y;
            tmp[y][x].z = p->z;
            PSVECScale(&tmp[y][x], &tmp[y][x], 0.005f);
        }
    }
    for (y = 1; y < MESH_N - 1; y++) {
        for (x = 1; x < MESH_N - 1; x++) {
            SetVec3(force, 0.0f, 0.0f, 0.0f);
            PSVECSubtract(&tmp[y][x], &tmp[y][x + 1], &dir);
            float len = PSVECMag(&dir);
            PSVECNormalize(&dir, &dir);
            PSVECScale(&dir, &spring, 1.0f - len);
            PSVECAdd(&force, &spring, &force);
            PSVECSubtract(&tmp[y][x], &tmp[y][x - 1], &dir);
            len = PSVECMag(&dir);
            PSVECNormalize(&dir, &dir);
            PSVECScale(&dir, &spring, 1.0f - len);
            PSVECAdd(&force, &spring, &force);
            PSVECSubtract(&tmp[y][x], &tmp[y + 1][x], &dir);
            len = PSVECMag(&dir);
            PSVECNormalize(&dir, &dir);
            PSVECScale(&dir, &spring, 1.0f - len);
            PSVECAdd(&force, &spring, &force);
            PSVECSubtract(&tmp[y][x], &tmp[y - 1][x], &dir);
            len = PSVECMag(&dir);
            PSVECNormalize(&dir, &dir);
            PSVECScale(&dir, &spring, 1.0f - len);
            PSVECAdd(&force, &spring, &force);
            PSVECScale(&force, &force, 5.0f);
            PSVECAdd(&m_meshVel[y][x], &force, &m_meshVel[y][x]);
        }
    }
    for (y = 1; y < MESH_N - 1; y++) {
        for (x = 1; x < MESH_N - 1; x++) {
            PSVECScale(&m_meshVel[y][x], &step, 5.0f);
            PSVECAdd(&m_meshPos[y][x], &step, &m_meshPos[y][x]);
            if (m_meshPos[y][x].y > 30.000002f) {
                m_meshPos[y][x].y = 30.000002f;
                m_meshVel[y][x].y = 0.0f;
            }
            if (m_meshPos[y][x].y < -150.0f) {
                m_meshPos[y][x].y = -150.0f;
                m_meshVel[y][x].y = 0.0f;
            }
            float t = (150.0f + m_meshPos[y][x].y) / 180.0f;
            u8 grey = 160.0f * t;
            u8 alpha = 130;
            float dist = PSVECMag(&m_meshPos[y][x]);
            if (dist > 2400.0f) {
                grey = 0;
            } else if (dist >= 2000.0f) {
                grey = grey * ((2400.0f - dist) / 400.0f);
            }
            if (dist > 3000.0f) {
                alpha = 0;
            } else if (dist >= 2000.0f) {
                alpha = alpha * ((3000.0f - dist) / 1000.0f);
            }
            m_meshCol[y][x].r = m_meshCol[y][x].g = m_meshCol[y][x].b = grey;
            m_meshCol[y][x].a = alpha;
        }
    }
}

enum { MESH_LAST = CWater::MESH_N - 2 };

static inline int ClampCell(int v)
{
    if (v < 1) {
        return 1;
    } else if (v > MESH_LAST) {
        return MESH_LAST;
    }
    return v;
}

/* fn_1_14414: push the 3x3 cells around p (cell clamped to the interior) */
void CWater::AddForce(const Vec* p, float dy)
{
    int ix = 16.0f + (int)(p->x / 200.0f);
    int iz = 16.0f + (int)(p->z / 200.0f);
    int cx = ClampCell(ix);
    int cz = ClampCell(iz);
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            m_meshVel[cz + y][cx + x].y += dy;
        }
    }
}

/* fn_1_145A0: 15.000001 + the mean height of the 3x3 cells around p */
float CWater::GetHeight(const Vec* p)
{
    int ix = 16.0f + (int)(p->x / 200.0f);
    int iz = 16.0f + (int)(p->z / 200.0f);
    int cx = ClampCell(ix);
    int cz = ClampCell(iz);
    float sum = 0.0f;
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            sum += m_meshPos[cz + y][cx + x].y;
        }
    }
    return 15.000001f + sum / 9.0f;
}

void CWater::Splash(const Vec* p, float dy)
{
    AddForce(p, dy);
    new CSplash(p);
    new CSplashModel(p);
    new CRipple(p);
}

/* ---- CWater UpdateWarpTex .. DrawMesh, CRipple (F6: .text 0x14B8C..0x172D0) ---- */

void CWater::UpdateWarpTex()
{
    int unused = 0;
    int x;
    int y;
    for (y = 0; y < WARP_N; y++) {
        for (x = 0; x < WARP_N; x++) {
            int mx = x * MESH_N / WARP_N;
            int my = y * MESH_N / WARP_N;
            Vec rest;
            rest.x = 200.0f * mx - 3200.0f;
            rest.z = 200.0f * my - 3200.0f;
            float dx = m_meshPos[my][mx].x - rest.x;
            float dz = m_meshPos[my][mx].z - rest.z;
            u8 s = 128 + (int)(127.0f * (dx / 84.0f));
            u8 t = 128 + (int)(127.0f * (dz / 84.0f));
            int ofs = (((y >> 2) << 7) | (((y & 3) << 2) | ((x & 3) | ((x >> 2) << 4)))) * 2;
            m_warpBuf[ofs] = s;
            m_warpBuf[ofs + 1] = t;
        }
    }
    DCFlushRange(m_warpBuf, sizeof(m_warpBuf));
}

void CWater::DrawTakiAll(Mtx* mtx)
{
    for (int i = 0; i < NUM_TAKI; i++) {
        HSFOBJECT* obj = m_taki[i];
        DrawTaki(mtx, obj);
    }
}

void CWater::DrawTaki(Mtx* mtx, HSFOBJECT* obj)
{
    HSFBUFFER* faces = obj->mesh.face;
    HSFBUFFER* vtx = obj->mesh.vertex;
    HSFBUFFER* st = obj->mesh.st;
    HSFBUFFER* col = obj->mesh.color;
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetArray(GX_VA_POS, vtx->data, sizeof(HuVecF));
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetArray(GX_VA_CLR0, col->data, sizeof(GXColor));
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetArray(GX_VA_TEX0, st->data, sizeof(HuVec2f));
    HSFFACE* f = (HSFFACE*)faces->data;
    for (int i = 0; i < faces->count; i++, f++) {
        switch (f->type & HSF_FACE_MASK) {
        case HSF_FACE_TRI:
            GXBegin(GX_TRIANGLES, GX_VTXFMT0, 3);
            GXPosition1x16(f->index[0].vertex);
            GXColor1x16(f->index[0].color);
            GXTexCoord1x16(f->index[0].st);
            GXPosition1x16(f->index[2].vertex);
            GXColor1x16(f->index[2].color);
            GXTexCoord1x16(f->index[2].st);
            GXPosition1x16(f->index[1].vertex);
            GXColor1x16(f->index[1].color);
            GXTexCoord1x16(f->index[1].st);
            GXEnd();
            break;
        case HSF_FACE_QUAD:
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition1x16(f->index[0].vertex);
            GXColor1x16(f->index[0].color);
            GXTexCoord1x16(f->index[0].st);
            GXPosition1x16(f->index[2].vertex);
            GXColor1x16(f->index[2].color);
            GXTexCoord1x16(f->index[2].st);
            GXPosition1x16(f->index[3].vertex);
            GXColor1x16(f->index[3].color);
            GXTexCoord1x16(f->index[3].st);
            GXPosition1x16(f->index[1].vertex);
            GXColor1x16(f->index[1].color);
            GXTexCoord1x16(f->index[1].st);
            GXEnd();
            break;
        case HSF_FACE_TRISTRIP: {
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, f->strip.count + 3);
            GXPosition1x16(f->strip.index[0].vertex);
            GXColor1x16(f->strip.index[0].color);
            GXTexCoord1x16(f->strip.index[0].st);
            GXPosition1x16(f->strip.index[2].vertex);
            GXColor1x16(f->strip.index[2].color);
            GXTexCoord1x16(f->strip.index[2].st);
            GXPosition1x16(f->strip.index[1].vertex);
            GXColor1x16(f->strip.index[1].color);
            GXTexCoord1x16(f->strip.index[1].st);
            HSFFACEINDEX* s = f->strip.data;
            for (u32 k = 0; k < f->strip.count; k++, s++) {
                GXPosition1x16(s->vertex);
                GXColor1x16(s->color);
                GXTexCoord1x16(s->st);
            }
            GXEnd();
            break;
        }
        }
    }
}

void CWater::LoadTextures()
{
    GXSetTexCopySrc(0, 0, SCREEN_W, SCREEN_H);
    GXSetTexCopyDst(SCREEN_W, SCREEN_H, GX_TF_RGB565, GX_FALSE);
    GXCopyTex(m_copyBuf, GX_FALSE);
    GXLoadTexObj(&m_copyTex, GX_TEXMAP0);
    GXLoadTexObj(&m_warpTex, GX_TEXMAP1);
    HuSprTexLoad(m_takiWarpAnim, 0, GX_TEXMAP2, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    HuSprTexLoad(m_surfaceAnim, 0, GX_TEXMAP3, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    HuSprTexLoad(m_takiAnim, 0, GX_TEXMAP4, GX_REPEAT, GX_REPEAT, GX_LINEAR);
}

void CWater::InitTexObj()
{
    GXInitTexObj(&m_copyTex, m_copyBuf, SCREEN_W, SCREEN_H, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&m_copyTex, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXInitTexObj(&m_warpTex, m_warpBuf, WARP_N, WARP_N, GX_TF_IA8, GX_REPEAT, GX_REPEAT, GX_FALSE);
    GXInitTexObjLOD(&m_warpTex, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
}

/* m513 powerind SetProjTexGen with camera 0 */
void CWater::SetProjTexGen(Mtx* mtx)
{
    HU3DCAMERA* cam = &Hu3DCamera[0];
    Mtx texMtx;
    Mtx proj;
    GXSetNumTexGens(1);
    C_MTXLightPerspective(proj, cam->fov, cam->aspect, 0.5f, -0.5f, 0.5f, 0.5f);
    PSMTXConcat(proj, *mtx, texMtx);
    GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
}

void CWater::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

/* s_frame's initialiser: non-constant (retail has the guard byte A9C; m512 zako GetFps() spelling, a guess) */
static inline int FrameStart()
{
    return 0;
}

/* time, scroll, the mesh step, the warp map (UpdateWarpTex inlined) and every 240 frames a push under each waterfall
 * (AddForce inlined) */
void CWater::on_update()
{
    m_time += 1.0 / 60.0;
    m_scroll.y = 0.5f * -m_time;
    UpdateMesh();
    UpdateWarpTex();
    static int s_frame = FrameStart();
    if (s_frame % 240 == 0) {
        for (int i = 0; i < NUM_MIST; i++) {
            AddForce(&s_mistPos[i], -0.5f);
        }
    }
    s_frame++;
}

void CWater::Draw(Mtx* mtx)
{
    static const float waterIndMtx[2][3] = { { 0.2f, 0.0f, 0.0f }, { 0.0f, 0.2f, 0.0f } };
    static const float takiIndMtx[2][3] = { { 0.1f, 0.0f, 0.0f }, { 0.0f, 0.1f, 0.0f } };
    Mtx trans;
    Mtx scale;
    Mtx texMtx;
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    SetProjTexGen(mtx);
    LoadTextures();
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetNumTexGens(3);
    PSMTXTrans(trans, m_scroll.x, 2.0f * m_scroll.y, m_scroll.z);
    PSMTXScale(scale, 1.0f, 1.0f, 1.0f);
    PSMTXConcat(scale, trans, texMtx);
    GXLoadTexMtxImm(texMtx, GX_TEXMTX2, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX2, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(3);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP4, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumIndStages(1);
    PSMTXTrans(trans, m_scroll.x, m_scroll.y, m_scroll.z);
    PSMTXScale(scale, 1.0f, 1.0f, 1.0f);
    PSMTXConcat(scale, trans, texMtx);
    GXLoadTexMtxImm(texMtx, GX_TEXMTX1, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD2, GX_TEXMAP2);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
    GXSetIndTexMtx(GX_ITM_0, (float(*)[3])takiIndMtx, 0);
    DrawTakiAll(mtx);
    GXSetNumTevStages(2);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP3, GX_COLOR0);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_RASA, GX_CC_RASC);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumTexGens(3);
    float ax = 0.017453292f * (10.0f * m_time);
    float az = 0.017453292f * (20.0f * m_time);
    float sx = 0.5 * sin(ax);
    float sz = 0.5 * sin(az);
    PSMTXTrans(trans, sx, 0.0f, sz);
    PSMTXScale(scale, 1.0f, 1.0f, 1.0f);
    PSMTXConcat(scale, trans, texMtx);
    GXLoadTexMtxImm(texMtx, GX_TEXMTX3, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_TEXMTX3, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumIndStages(1);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD2, GX_TEXMAP1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_1);
    GXSetIndTexMtx(GX_ITM_1, (float(*)[3])waterIndMtx, 0);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_COPY);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    DrawMesh();
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevDirect(GX_TEVSTAGE1);
    GXSetTevDirect(GX_TEVSTAGE2);
    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_FALSE, 0, 0);
    GXSetTexCoordScaleManually(GX_TEXCOORD1, GX_FALSE, 0, 0);
    GXSetTexCoordScaleManually(GX_TEXCOORD2, GX_FALSE, 0, 0);
}

void CWater::DrawMesh()
{
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetVtxDesc(GX_VA_TEX1, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX1, GX_TEX_ST, GX_F32, 0);
    Vec* pos = m_meshPos[0];
    Vec* uv = m_meshUV[0];
    GXColor* col = m_meshCol[0];
    GXBegin(GX_QUADS, GX_VTXFMT0, (MESH_N - 1) * (MESH_N - 1) * 4);
    for (int y = 0; y < MESH_N - 1; y++) {
        int y0 = y * MESH_N;
        int y1 = (y + 1) * MESH_N;
        for (int x = 0; x < MESH_N - 1; x++) {
            int x0 = x;
            int x1 = x + 1;
            Vec* p00 = pos + y0 + x0;
            Vec* p01 = pos + y0 + x1;
            Vec* p11 = pos + y1 + x1;
            Vec* p10 = pos + y1 + x0;
            GXColor* c00 = col + y0 + x0;
            GXColor* c01 = col + y0 + x1;
            GXColor* c11 = col + y1 + x1;
            GXColor* c10 = col + y1 + x0;
            Vec* t00 = uv + y0 + x0;
            Vec* t01 = uv + y0 + x1;
            Vec* t11 = uv + y1 + x1;
            Vec* t10 = uv + y1 + x0;
            GXPosition3f32(p00->x, p00->y, p00->z);
            GXColor4u8(c00->r, c00->g, c00->b, c00->a);
            GXTexCoord2f32(t00->x, t00->z);
            GXTexCoord2f32(8.0f * t00->x, 8.0f * t00->z);
            GXPosition3f32(p01->x, p01->y, p01->z);
            GXColor4u8(c01->r, c01->g, c01->b, c01->a);
            GXTexCoord2f32(t01->x, t01->z);
            GXTexCoord2f32(8.0f * t01->x, 8.0f * t01->z);
            GXPosition3f32(p11->x, p11->y, p11->z);
            GXColor4u8(c11->r, c11->g, c11->b, c11->a);
            GXTexCoord2f32(t11->x, t11->z);
            GXTexCoord2f32(8.0f * t11->x, 8.0f * t11->z);
            GXPosition3f32(p10->x, p10->y, p10->z);
            GXColor4u8(c10->r, c10->g, c10->b, c10->a);
            GXTexCoord2f32(t10->x, t10->z);
            GXTexCoord2f32(8.0f * t10->x, 8.0f * t10->z);
        }
    }
    GXEnd();
}

void CRipple::Hook(HU3DMODEL* model, Mtx* mtx)
{
    CRipple* self = (CRipple*)model->hookData;
    self->Draw(mtx);
}

CRipple::CRipple(const Vec* pos) : m_pos(*pos)
{
    m_t = 0.0f;
    HU3DMODELID id = Hu3DHookFuncCreate(Hook);
    HU3DMODEL* model = &Hu3DData[(int)id];
    model->hookData = this;
    Hu3DModelLayerSet((int)id, 4);
    Hu3DModelCameraSet((int)id, 1);
    m_model = (int)id;
    m_anim = HuSprAnimRead(HuDataSelHeapReadNum(0x5F001D, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_anim);
}

CRipple::~CRipple()
{
    Hu3DModelKill(m_model);
    HuSprAnimKill(m_anim);
}

void CRipple::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

void CRipple::on_update()
{
    m_t += 1.0 / 60.0;
    if (m_t > 1.0f) {
        m_t = 0.0f;
    }
    CWater* water = CSingleton<CWater>::GetInstance();
    m_pos.y = water->GetHeight(&m_pos);
}

void CRipple::Draw(Mtx* mtx)
{
    Mtx trans;
    Mtx m;
    PSMTXTrans(trans, m_pos.x, m_pos.y, m_pos.z);
    float s = 1.5f * m_t;
    PSMTXScale(m, s, 1.0f, s);
    PSMTXConcat(*mtx, trans, *mtx);
    PSMTXConcat(*mtx, m, m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    HuSprTexLoad(m_anim, 0, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_LEQUAL, 255);
    GXSetNumChans(0);
    GXSetChanCtrl(GX_COLOR_NULL, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    float a = 255.0f * (1.0f - m_t);
    GXColor col = { 255, 255, 255, 0 };
    col.a = a;
    GXSetTevColor(GX_TEVREG0, col);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVREG1);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVREG1);
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

} // namespace m537
