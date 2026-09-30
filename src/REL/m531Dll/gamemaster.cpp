/* gamemaster.cpp -- CGameMaster (gamemaster.h): on_setup, setMode, the seven trampolines interleaved with the
 * empty virtual modeN defaults (one macro per mode), the static trampoline table (rodata 5D0, 7 + NULL) and the
 * minigame.h triple (__sinit, bss 70/74/78). Every function written whole (skeleton). */
#include "REL/m531Dll/gamemaster.h"

namespace m531 {

/* rodata_5D0: setMode's table; the trailing NULL is real (8 words) */
static void (* const s_modeFunc[8])(omObj_s*) = {
    CGameMaster::Mode0Func, CGameMaster::Mode1Func, CGameMaster::Mode2Func, CGameMaster::Mode3Func,
    CGameMaster::Mode4Func, CGameMaster::Mode5Func, CGameMaster::Mode6Func, NULL,
};

void CGameMaster::on_setup(Process_s* om)
{
    m_om = om;
    m_obj = omAddObjEx(om, 0, 0, 0, -1, Mode0Func);
    m_obj->data = this;
    m_obj->objFunc = Mode0Func; /* redundant, retail */
}

void CGameMaster::setMode(int mode)
{
    m_mode = mode;
    m_obj->objFunc = s_modeFunc[mode];
}

#define M531_MODE(n)                                          \
    void CGameMaster::Mode##n##Func(omObj_s* obj)             \
    {                                                         \
        CGameMaster* self = (CGameMaster*)obj->data;          \
        self->mode##n();                                      \
    }                                                         \
    void CGameMaster::mode##n() {}

M531_MODE(0)
M531_MODE(1)
M531_MODE(2)
M531_MODE(3)
M531_MODE(4)
M531_MODE(5)
M531_MODE(6)

} // namespace m531
