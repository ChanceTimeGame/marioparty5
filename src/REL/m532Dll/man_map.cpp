/* man_map.cpp -- m532::CMapMan (man_map.h). The ctor's asserts are retail's man_map.cpp:53 and :59 (keep the
 * lines). Retail order: ctor, [~vector<int>, ~__vector_pod<int>, ~__vector_base<int>, ~CSingleton<CMapMan>],
 * dtor, startSpin, stopSpin, getAngle, isBallAt, grabNearest, on_new_mode, on_update, initFog, setFog,
 * FogOnHook, FogOffHook, [__vector_pod<int>::insert], __sinit (the 300/60 pair).
 * Drafts written whole from the sheet (master_camera_map_score_rumble.md §5) and the asm. */
#include "REL/m532Dll/config.h"
#include "REL/m532Dll/param.h"
#include "REL/m532Dll/man_map.h"
#include "REL/m532Dll/ball.h"

void ShadowSetup(s16 camBit, Vec* lightDir, Vec* target, float size, float depth); /* mgcpp shadow.cpp */

namespace m532 {

CMapMan::CMapMan()
    : CModel(0x5A0001U), m_model0(0x5A0002U), m_model1(0x5A0003U), m_model2(0x5A0004U), m_balls(),
      m_sunRot(&getObjPtr("tenmen_sun")->mesh.base.rot.y), m_sunRotB(&getObjPtr("tenmen_sun_b")->mesh.base.rot.y),
      m_angle(11.25f), m_speed(0.0f), m_se(0)
{
    setLayer(2);
    setAttr(HU3D_MOTATTR_LOOP);
    m_model0.setLayer(0);
    m_model1.setLayer(1);
    m_model2.setLayer(2);
    m_model2.setShadowMap();
    m_model2.getObjPtr("kaidan")->flags |= 0x4000;
    /* line padding: the asserts below are retail's man_map.cpp:53 and :59 */





















    int lights = Hu3DModelLightInfoSet(((CModel*)this)->id(), 1);
    assert(lights > 0);




    HU3DLIGHTID light_id = Hu3DModelLightIdGet(((CModel*)this)->id(), (char*)"inf_light1");
    assert(light_id >= 0);
    Vec dir;
    Vec pos;
    GXColor col;
    Hu3DGLightParamGet((int)light_id, &pos, &dir, &col);
    Vec target = { 0.0f, 170.0f, 300.0f };
    ShadowSetup(1, &dir, &target, 680.0f, 445.0f);
    setShadowMap();
    initFog();
    Hu3DLayerHookSet(0, FogOffHook);
    Hu3DLayerHookSet(1, FogOnHook);
    Hu3DLayerHookSet(7, FogOffHook);
    for (int i = 0; i < 16; i++) {
        float angle = 360.0 * ((0.5 + i) / 16.0);
        m_balls.push_back((new CHangBall(angle, i))->GetHandle());
    }
}

CMapMan::~CMapMan() {}

void CMapMan::startSpin()
{
    m_speed = 1.125f;
    m_se = HuAudFXPlay(0x7AB);
}

void CMapMan::stopSpin()
{
    m_speed = 0.0f;
    HuAudFXStop(m_se);
}

float CMapMan::getAngle()
{
    return m_angle;
}

/* vector<int> begin()/end() as raw pointers: retail copies each one temporary more than the in-tree <vector>
 * gives (isBallAt A5A4, grabNearest A6C0) -- m531 cleaneff.cpp's VecBegin shape. The host's iterators are classes. */
template <class T> inline T* VecBegin(std::vector<T>& v)
{
    return (T*)v.begin();
}
template <class T> inline T* VecEnd(std::vector<T>& v)
{
    return (T*)v.end();
}

/* |a - b|: retail copies the PSVECMag result twice (A6C0), a nested inline's return */
inline float VecMag(Vec* v)
{
    return PSVECMag(v);
}
inline float VecDist(Vec* a, Vec* b)
{
    Vec d;
    PSVECSubtract(a, b, &d);
    return VecMag(&d);
}

bool CMapMan::isBallAt(float a)
{
    int* it = VecBegin(m_balls);
    int* end = VecEnd(m_balls);
    for (; it != end; it++) {
        CHangBall* ball = static_cast<CHangBall*>(CObject::GetHandlePtr(*it));
        if (!ball->IsShot()) {
            Vec* p = ball->GetPos();
            if (!(p->z <= 0.0f) && fabs(a - p->x) < 20.0) {
                return true;
            }
        }
    }
    return false;
}

int CMapMan::grabNearest(Vec* pos)
{
    int* it = VecBegin(m_balls);
    int* end = VecEnd(m_balls);
    CHangBall* best = 0;
    float bestDist = 10000.0f;
    for (; it != end; it++) {
        CHangBall* ball = static_cast<CHangBall*>(CObject::GetHandlePtr(*it));
        if (!ball->IsShot()) {
            float dist = VecDist(pos, ball->GetPos());
            if (bestDist > dist) {
                bestDist = dist;
                best = ball;
            }
        }
    }
    if (best == 0) {
        return 0;
    }
    return best->Shoot(pos);
}

void CMapMan::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

void CMapMan::on_update()
{
    if ((m_angle += m_speed) >= 360.0f) {
        m_angle -= 360.0f;
    }
    *m_sunRot = m_angle;
    *m_sunRotB = -m_angle;
}

/* lbl_1_rodata_290: no fog */
static const HSFSCENE s_noFog = { GX_FOG_NONE, 0.0f, 0.0f, { 0, 0, 0, 0 } };

void CMapMan::initFog()
{
    HU3DMODELID id = ((CModel*)this)->id();
    HU3DMODEL* model = &Hu3DData[id];
    if (model->hsf->sceneNum > 0) {
        HSFSCENE scene = *model->hsf->scene;
        if (!(scene.fogStart <= 0.0f) && !(scene.fogStart >= scene.fogEnd)) {
            m_fog.fogType = GX_FOG_EXP; /* retail ignores scene.fogType */
            m_fog.fogStart = scene.fogStart;
            m_fog.fogEnd = scene.fogEnd;
            /* the (u8) casts are retail's clrlwi after each lbz (A874) */
            m_fog.fogColor.r = (u8)scene.fogColor.r;
            m_fog.fogColor.g = (u8)scene.fogColor.g;
            m_fog.fogColor.b = (u8)scene.fogColor.b;
            m_fog.fogColor.a = 0xFF;
            return;
        }
    }
    m_fog = s_noFog;
}

void CMapMan::setFog()
{
    float near;
    float far;
    float fov;
    Hu3DCameraPerspectiveGet(1, &fov, &near, &far);
    GXSetFog(m_fog.fogType, m_fog.fogStart, m_fog.fogEnd, near, far, m_fog.fogColor);
}

void CMapMan::FogOnHook(s16 layer)
{
    GetInstance()->setFog();
}

/* lbl_1_rodata_2A0 */
static const GXColor s_black = { 0, 0, 0, 0 };

void CMapMan::FogOffHook(s16 layer)
{
    GXColor color = s_black;
    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, color);
}

} // namespace m532
