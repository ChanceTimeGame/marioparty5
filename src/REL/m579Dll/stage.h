#ifndef M579_STAGE_H
#define M579_STAGE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"

namespace m579 {

class CStage : public CGameObject, public CSingleton<CStage> {
public:
    CStage();                                     /* fn_1_B2C8 */
    virtual void on_update();                     /* fn_1_B574 empty (defined right after the ctor) */
    virtual void on_new_mode(int mode);           /* fn_1_B578 (= m509 ED2C / m512 8758) */
    static void DrawHook(HU3DMODEL* model, Mtx* mtx); /* fn_1_B5A0 dead: GetInstancePtr()->draw(mtx) (= m512 8780) */
    void draw(Mtx* mtx);                          /* fn_1_B5F0 dead (= m512 87D0) */
    static void DrawRing();                       /* fn_1_B620 dead: grey annulus 450..850 (GX immediate) */
    virtual ~CStage();                            /* fn_1_B98C (= m509 ED54) defined LAST */

    CModel m_model;   /* 0x10 0x850000 */
    CModel m_sub;     /* 0x12 0x850001 */
};

} // namespace m579

#ifndef __MWERKS__
template <> m579::CStage* CSingleton<m579::CStage>::ms_pointer; /* defined in game_master.cpp (bss A30) */
#endif

#endif
