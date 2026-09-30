#ifndef M532_MAN_MAP_H
#define M532_MAN_MAP_H

#include "REL/m532Dll/config.h"
#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include <vector>

namespace m532 {

class CMapMan : public CGameObject, public CSingleton<CMapMan>, public CModel {
public:
    CMapMan();                           /* fn_1_9D7C */
    /* fn_1_A3C0: does not delete the balls, stop m_se or reset the layer hooks (retail) */
    virtual ~CMapMan();
    void startSpin();                    /* fn_1_A518 1.125 deg/frame, SE 0x7AB */
    void stopSpin();                     /* fn_1_A55C */
    float getAngle();                    /* fn_1_A59C (ball CalcPivot) */
    /* fn_1_A5A4: a free ball on the +z side within 20 of x == a (game_master playRounds; meaning a guess) */
    bool isBallAt(float a);
    /* fn_1_A6C0: shoot the nearest free hanging ball at `pos`; the new CBall's handle, 0 if none */
    int grabNearest(Vec* pos);
    virtual void on_new_mode(int mode);  /* fn_1_A7FC */
    virtual void on_update();            /* fn_1_A814 */
    void initFog();                      /* fn_1_A874 the HSF scene fog, always GX_FOG_EXP (retail) */
    void setFog();                       /* fn_1_A9E0 unreferenced (inlined into FogOnHook) */
    static void FogOnHook(s16 layer);
    static void FogOffHook(s16 layer);   /* fn_1_AB38 */

    CModel m_model0;                     /* 0x12 0x5A0002 layer 0 */
    CModel m_model1;                     /* 0x14 0x5A0003 layer 1 */
    CModel m_model2;                     /* 0x16 0x5A0004 layer 2, shadow map, "kaidan" flag 0x4000 */
    std::vector<int> m_balls;            /* 0x18 CHangBall handles */
    float* m_sunRot;
    float* m_sunRotB;                    /* 0x28 &tenmen_sun_b->mesh.base.rot.y */
    float m_angle;                       /* 0x2C degrees, 11.25 at start */
    float m_speed;                       /* 0x30 */
    int m_se;                            /* 0x34 HuAudFXPlay(0x7AB) handle */
    HSFSCENE m_fog;                      /* 0x38 GXSetFog's type, start, end, colour */
};

} // namespace m532

#ifndef __MWERKS__
template <> m532::CMapMan* CSingleton<m532::CMapMan>::ms_pointer; /* defined in ball.cpp (bss_8) */
#endif

#endif
