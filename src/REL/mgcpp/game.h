/* game.h -- the ONE place the C game/SDK headers enter the C++ framework and the C++ overlays.
 * Everything here has C linkage (DOL functions and data); nothing in an overlay is exported except
 * extern "C" void ObjectSetup(void).
 *
 * CodeWarrior: u32/s32 are unsigned long/signed long (mangle Ul/l); the host has 32-bit uint32_t/int32_t.
 * Never write a bare long/unsigned long in a signature -- use u32/s32 (or unsigned int where the retail
 * name mangles Ui).
 */
#ifndef MGCPP_GAME_H
#define MGCPP_GAME_H

/* First, so NULL is the C++ null (MSL stddef.h: 0L) before dolphin/types.h defines ((void*)0): retail's
 * `p != NULL` asserts compile to `cmplwi p,0`, not `li r0,0; cmplw` (new.cpp:23). */
#include <stddef.h>

extern "C" {
#include "dolphin.h"
#include "humath.h"
#include "game/memory.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/charman.h"
#include "game/object.h"
#include "game/process.h"
#include "game/gamemes.h"
#include "game/wipe.h"
#include "game/audio.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/timer.h"
#include "game/mg/actman.h"

#ifndef _DOLPHIN_OSSEMAPHORE
#define _DOLPHIN_OSSEMAPHORE
typedef struct OSSemaphore {
    s32 count;
    OSThreadQueue queue;
} OSSemaphore;
void OSInitSemaphore(OSSemaphore* sem, s32 count);
s32 OSWaitSemaphore(OSSemaphore* sem);
s32 OSTryWaitSemaphore(OSSemaphore* sem);
s32 OSSignalSemaphore(OSSemaphore* sem);
s32 OSGetSemaphoreCount(OSSemaphore* sem);
#endif
}

#ifdef __MWERKS__
/* MSL C stdio: FILE, __files, fprintf/printf/sprintf/vprintf (mslconfig uses the same header). */
extern "C" {
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h"
#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/abort_exit.h"
}
#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif
#include <stddef.h>

#endif
