/* stage.h -- m501::CStage (stage.cpp): stage models, light and shadow, the scoop-pile bob.
 * GC: CGameObject +0x00, empty CSingleton<CStage> at +0x10, four CModels +0x10/0x12/0x14/0x16,
 * m_timer +0x18, m_angle +0x1C; size 0x20. stage.cpp does not include minigame.h. */
#ifndef M501_STAGE_H
#define M501_STAGE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"

namespace m501 {

class CStage : public CGameObject, public CSingleton<CStage> {
public:
    CStage();
    void setAisuMotion();
    virtual void on_update();
    virtual void on_new_mode(int mode);
    virtual ~CStage();

    CModel m_stageModel;  /* 0x10 data 0x3B0000 */
    CModel m_shadowModel; /* 0x12 data 0x3B0002 */
    CModel m_camModel;    /* 0x14 data 0x3B0001 (camera motion) */
    CModel m_aisuModel;   /* 0x16 data 0x3B0004 (scoop pile) */
    int m_timer;          /* 0x18 */
    float m_angle;        /* 0x1C radians */
};

} // namespace m501

#ifndef __MWERKS__
template <> m501::CStage* CSingleton<m501::CStage>::ms_pointer; /* defined in gamemaster.cpp */
#endif

#endif
