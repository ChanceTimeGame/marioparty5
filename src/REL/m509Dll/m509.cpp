/* m509.cpp -- the minigame framework unit of m509dll: the shared framework (src/REL/mgcpp) as one translation
 * unit, in m509's own retail order (an older build of the same library -- the __FILE__ strings read assert,
 * new, thread, subthread, om, singleton.h, model, timer). No handle, random, shadow or sphere files.
 * Every function body is the current mgcpp's; what differs is where things sit:
 *  - CW emits a TU's .text/.data/.rodata grouped by SOURCE FILE, in order of each file's first appearance
 *    (not in definition order), so a file's position in this list is part of the object:
 *  - the debug camera (printView, GetStick*, GetSubStick*, debugView) was a file of its own after timer.cpp:
 *    camera.cpp once with MGCPP_CAMERA_NO_DEBUG, then again with MGCPP_CAMERA_DEBUG_ONLY (a #line names it);
 *  - <math.h> (sqrtf's weak _half/_three .rodata) first appeared after mt19937.cpp, not with game.h;
 *  - _prolog/_epilog are m509's objectsetup.cpp's (MGCPP_V0_NO_PROLOG drops new.cpp's). */
#define MGCPP_V0_NO_PROLOG
#ifdef __MWERKS__
#define _MATH_H /* keep libc/math.h out until after mt19937.cpp (humath.h includes it from game.h) */
#endif
#include "REL/mgcpp/assert.cpp"
#include "REL/mgcpp/new.cpp"
#include "REL/mgcpp/thread.cpp"
#include "REL/mgcpp/subthread.cpp"
#include "REL/mgcpp/link.cpp"
#include "REL/mgcpp/mt19937.cpp"
#ifdef __MWERKS__
#undef _MATH_H
extern "C" {
#include <math.h>
}
#endif
#include "REL/mgcpp/om.cpp"
#include "REL/mgcpp/minigame.cpp"
#include "REL/mgcpp/gameobject.cpp"
#include "REL/mgcpp/model.cpp"
#define MGCPP_CAMERA_NO_DEBUG
#include "REL/mgcpp/camera.cpp"
#include "REL/mgcpp/timer.cpp"
#undef MGCPP_CAMERA_NO_DEBUG
#define MGCPP_CAMERA_DEBUG_ONLY
#include "REL/mgcpp/camera.cpp"
#undef MGCPP_CAMERA_DEBUG_ONLY

/* The CMinigameCore singleton pointer: retail's weak template static, at the end of the TU's .bss. */
template <> CMinigameCore* CSingleton<CMinigameCore>::ms_pointer = 0;
