#ifndef M512_STAGE_H
#define M512_STAGE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"

namespace m512 {

class CStage : public CGameObject, public CSingleton<CStage> {
public:
    CStage();
    virtual void on_update();  /* fn_1_8754 empty */
    virtual void on_new_mode(int mode);
    /* fn_1_8780: a HU3DMODELHOOK that nothing registers (dead); reads ms_pointer without the assert */
    static void DrawHook(HU3DMODEL* model, Mtx* mtx);
    void draw(Mtx* mtx);       /* fn_1_87D0 r3 unused: GXLoadPosMtxImm + DrawTrack */
    static void DrawTrack();   /* fn_1_8800 the track outline as a grey triangle strip (dead) */
    virtual ~CStage();

    /* eight named members, not an array: the ctor makes eight separate CModel(u32) calls (sheet §5.1) */
    CModel m_model0; /* 0x10 0x460000 layer 2, LightInfoSet */
    CModel m_model1; /* 0x12 0x460001 layer 2, ShadowMapSet */
    CModel m_model2; /* 0x14 0x460002 layer 2 */
    CModel m_model3; /* 0x16 0x460003 layer 1, ShadowMapSet */
    CModel m_model4; /* 0x18 0x460004 layer 0 */
    CModel m_model5; /* 0x1A 0x460005 layer 0 */
    CModel m_model6; /* 0x1C 0x460007 (6 is the skate) layer 2, shape motion */
    CModel m_model7; /* 0x1E 0x460008 layer 0, shape motion */
};

} // namespace m512

#ifndef __MWERKS__
template <> m512::CStage* CSingleton<m512::CStage>::ms_pointer; /* defined in gamemaster.cpp */
#endif

#endif
