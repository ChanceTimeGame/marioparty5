#ifndef M531_EFFECT_H
#define M531_EFFECT_H

#include "REL/mgcpp/game.h"

namespace m531 {

class CHookEffect {
public:
    Process_s* m_om;  /* 0x0 */
    omObj_s* m_obj;   /* 0x4 omAddObjEx(om, prio, 0, 0, -1, ObjUpdate); obj->data = this */
    s16 m_model;      /* 0x8 Hu3DHookFuncCreate(HookDraw); Hu3DData[m_model].hookData = this */

    static void ObjUpdate(omObj_s* obj);            /* fn_1_26EC */
    virtual void on_update();                       /* fn_1_2734 empty (vtable +0x08) */
    static void HookDraw(HU3DMODEL* model, Mtx* mtx); /* fn_1_2738 */
    virtual void draw(Mtx* mtx);                    /* fn_1_2788 empty (vtable +0x0C) */
    CHookEffect(Process_s* om, s16 layer, s16 prio, u16 camBit); /* fn_1_278C */
    virtual ~CHookEffect();                         /* fn_1_2854 (vtable +0x10) */
    void setCamera(u16 camBit);                     /* fn_1_28CC unreferenced */
    void show();                                    /* fn_1_2904 unreferenced */
    void hide();                                    /* fn_1_2938 unreferenced */
};

class CParticleEffect {
public:
    ANIMDATA* m_anim;           /* 0x0 HuSprAnimRead + HuSprAnimLock */
    s16 m_model;                /* 0x4 Hu3DParticleCreate */
    HU3DPARTICLE* m_particle;   /* 0x8 Hu3DData[m_model].hookData; m_particle->work = this */

    virtual ~CParticleEffect();                     /* fn_1_2A68 (vtable +0x08: declared first) */
    static void Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx); /* fn_1_296C */
    virtual void on_hook(Mtx mtx);                  /* fn_1_29BC empty (vtable +0x0C) */
    CParticleEffect(u32 dataNum, int maxCnt, u16 camBit); /* fn_1_29C0 */
    void setCamera(u16 camBit);                     /* fn_1_2AD0 */
    void show();                                    /* fn_1_2B08 DispOn (player 9CEC) */
    void hide();                                    /* fn_1_2B3C DispOff (polish 67E8) */
};

} // namespace m531

#endif
