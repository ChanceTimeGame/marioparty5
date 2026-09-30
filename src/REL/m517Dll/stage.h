#ifndef M517_STAGE_H
#define M517_STAGE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"

namespace m517 {

class CStage : public CGameObject, public CSingleton<CStage> {
public:
    CStage();                           /* fn_1_E3A4 */
    virtual void on_update();           /* fn_1_E81C empty */
    virtual void on_new_mode(int mode); /* fn_1_EAB8 */
    virtual ~CStage();                  /* fn_1_EAE0 (the layer hooks stay: retail) */

    /* the layer-0 / layer-1 fog hooks (the layer number is unused) */
    static void FogHookLayer0(s16 layer); /* fn_1_E820 GX_FOG_PERSP_LIN */
    static void FogHookLayer1(s16 layer); /* fn_1_E96C GX_FOG_PERSP_EXP */

    /* read / written across units (player update, choro CheckImpact) */
    Vec* GetImpact() { return &m_impact; }

    /* three named members, not an array: three separate CModel(u32) calls */
    CModel m_bg0;  /* 0x10 0x4B0001 layer 1 */
    CModel m_bg1;  /* 0x12 0x4B0002 shadow receiver, layer 1 */
    CModel m_bg2;  /* 0x14 0x4B0003 layer 1, attr 0x40000001 */
    Vec m_impact;  /* 0x18 zeroed by the ctor */
};

} // namespace m517

#ifndef __MWERKS__
template <> m517::CStage* CSingleton<m517::CStage>::ms_pointer; /* defined in effect.cpp (.bss 0x10) */
#endif

#endif
