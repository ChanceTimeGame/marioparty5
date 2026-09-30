#ifndef M531_GAMEMASTER_H
#define M531_GAMEMASTER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/minigame.h"

namespace m531 {

class CGameMaster : public CMinigameCore {
public:
    CGameMaster() : m_mode(0) {}               /* inline: ObjectSetup */
    virtual ~CGameMaster() {}                  /* fn_1_BB34 (weak, objectsetup.o) */
    virtual void on_setup(Process_s* om);      /* fn_1_BBCC adds the mode omObj (Mode0Func) */
    void setMode(int mode);                    /* fn_1_BC40 m_mode = mode; objFunc = s_modeFunc[mode] (no check) */

    /* fn_1_BC64.. : ((CGameMaster*)obj->data)->modeN(), interleaved with the empty defaults (gamemaster.cpp) */
    static void Mode0Func(omObj_s* obj);
    virtual void mode0();                      /* vtable +0x18 */
    static void Mode1Func(omObj_s* obj);
    virtual void mode1();
    static void Mode2Func(omObj_s* obj);
    virtual void mode2();
    static void Mode3Func(omObj_s* obj);
    virtual void mode3();
    static void Mode4Func(omObj_s* obj);
    virtual void mode4();
    static void Mode5Func(omObj_s* obj);
    virtual void mode5();
    static void Mode6Func(omObj_s* obj);
    virtual void mode6();                      /* vtable +0x30 */

    int m_mode;       /* 0x20 */
    omObj_s* m_obj;   /* 0x24 the mode omObj; never omDelObjEx'd (freed with the object manager) */
    Process_s* m_om;  /* 0x28 the object manager passed to on_setup */

    /* inline (player.cpp CPlayer ctor, F4; CFlow::mode0's `new X(GetOm())`: the spilled argument) */
    Process_s* GetOm() const { return m_om; }
};

} // namespace m531

#endif
