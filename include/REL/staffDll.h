#ifndef REL_STAFFDLL_H
#define REL_STAFFDLL_H

/* staffdll: the staff roll at the end of a story (staff.c). */

#include "game/object.h"
#include "game/hsfex.h"
#include "game/sprite.h"
#include "game/hu3d.h"
#include "game/window.h"
#include "game/process.h"

void StaffStub(void);
float StaffPosGet(float time, float accelTime, float flatTime, float decelTime);
void StaffMain(OMOBJ *obj);
void StaffInit(OMOBJ *obj);
void ObjectSetup(void);
void StaffExit(OMOBJ *obj);

#endif
