/* stage.h -- m521::CStage (stage.cpp): the stage model, its shadow receiver, the light and shadow set-up, and the
 * three clocks (owned through auto_ptr; their pointers published in gamemaster's s_clockR / s_clockB / s_clockQ).
 * GC 0x30 (gamemaster `li r3,0x30`): CGameObject +0x00, empty CSingleton<CStage> +0x10, m_clockR +0x10, m_clockQ
 * +0x14, m_clockB +0x18, m_model +0x1C, m_shadowRecv +0x20, m_proc +0x24. Declaration order R, Q, B (the dtor
 * destroys 0x20 .. 0x10). Vtable data_66C {~, on_new_mode, on_update}. stage.cpp includes minigame.h (triple
 * .bss A98). Names ours (sheet §5). */
#ifndef M521_STAGE_H
#define M521_STAGE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include <memory>

namespace m521 {

class CClock;

class CStage : public CGameObject, public CSingleton<CStage> {
public:
    typedef void (CStage::*ProcFunc)();

    static void CheckInstance();              /* fn_1_1490C (unreferenced; = m539 man_map BEBC) */
    static void SetShadowReceiver(s16 id);    /* fn_1_1497C (unreferenced; inlined in the ctor) */
    CStage();                                 /* fn_1_149C0 */
    void proc_idle();                         /* fn_1_15080 */
    virtual void on_update();                 /* fn_1_15084 */
    virtual void on_new_mode(int mode);       /* fn_1_15108 */
    virtual ~CStage();                        /* fn_1_15120 */
    /* by value: retail copies the PTMF constant to a stack temporary before storing it */
    void setProc(ProcFunc proc) { m_proc = proc; }

    std::auto_ptr<CClock> m_clockR;     /* 0x10 id 0 */
    std::auto_ptr<CClock> m_clockQ;     /* 0x14 id 2 */
    std::auto_ptr<CClock> m_clockB;     /* 0x18 id 1 */
    std::auto_ptr<CModel> m_model;      /* 0x1C 0x4F0000 */
    std::auto_ptr<CModel> m_shadowRecv; /* 0x20 0x4F0001 */
    ProcFunc m_proc;                    /* 0x24 */
};

} // namespace m521

#ifndef __MWERKS__
template <> m521::CStage* CSingleton<m521::CStage>::ms_pointer; /* defined in gamemaster.cpp (A78) */
#endif

#endif
