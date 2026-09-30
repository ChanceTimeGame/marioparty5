#ifndef M511_BOATSHADOW_H
#define M511_BOATSHADOW_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"

namespace m511 {

class CEffTex : public CGameObject, public CSingleton<CEffTex> {
public:
    CEffTex();                          /* fn_1_BD18 */
    virtual ~CEffTex();                 /* fn_1_BF28 HuSprAnimKill x5 */
    virtual void on_new_mode(int mode); /* fn_1_C01C */
    virtual void on_update();           /* fn_1_C034 empty (out of line) */

    ANIMDATA* m_starGetAnim; /* 0x10 0x450029: CStarGetEff / CStarEff particles */
    ANIMDATA* m_splashAnim;  /* 0x14 0x450028: CBoatSplash / CKibakoSplash particles */
    ANIMDATA* m_wakeAnim;    /* 0x18 0x45002A: CBoatWake */
    ANIMDATA* m_yajiAnim;    /* 0x1C 0x450030: CStarYaji */
    ANIMDATA* m_ringAnim;    /* 0x20 0x45002E: CStarRing */
};

class CBoatShadow {
public:
    static void Hook(HU3DMODEL* model, Mtx* mtx); /* fn_1_C038 ((CBoatShadow*)hookData)->Draw(mtx) */
    CBoatShadow();                                /* fn_1_C07C layer 3, camera 0xF */
    ~CBoatShadow();                               /* fn_1_C124 Hu3DModelKill, HuSprAnimKill */
    void SetPos(Vec* pos, Vec* rot);              /* fn_1_C180 player UpdateMain: pos (y + 10), rot */
    void Draw(Mtx* mtx);                          /* fn_1_C1CC */

    ANIMDATA* m_anim;    /* 0x00 0x45002D, locked; killed in the dtor */
    HU3DMODELID m_model; /* 0x04 Hu3DHookFuncCreate(Hook), hookData = this */
    Vec m_pos;           /* 0x08 SetPos (y + 10) */
    Vec m_rot;           /* 0x14 only rot.y is drawn */
};

} // namespace m511

#ifndef __MWERKS__
template <> m511::CEffTex* CSingleton<m511::CEffTex>::ms_pointer; /* defined in gamemaster.cpp (.bss A38) */
#endif

#endif
