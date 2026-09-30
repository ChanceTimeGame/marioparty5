/* m511.cpp -- the minigame framework unit of m511dll: the shared framework (src/REL/mgcpp) as one
 * translation unit, in retail order. m511's list (plan Phase 4 framework survey): random.cpp, sphere.cpp and
 * timer.cpp, no handle.cpp, with m532's CGameObject knobs. It is the THIRD unit in link order (after boat, math). */
#define MGCPP_GAMEOBJECT_INLINE_UPDATE
#define MGCPP_GAMEOBJECT_NO_VIRTUALS
#include "REL/mgcpp/new.cpp"
#include "REL/mgcpp/assert.cpp"
#include "REL/mgcpp/camera.cpp"
#include "REL/mgcpp/link.cpp"
#include "REL/mgcpp/gameobject.cpp"
#include "REL/mgcpp/minigame.cpp"
#include "REL/mgcpp/model.cpp"
#include "REL/mgcpp/mt19937.cpp"
#include "REL/mgcpp/om.cpp"
#include "REL/mgcpp/random.cpp"
#include "REL/mgcpp/sphere.cpp"
#include "REL/mgcpp/subthread.cpp"
#include "REL/mgcpp/thread.cpp"
#include "REL/mgcpp/timer.cpp"

/* The CMinigameCore singleton pointer: retail's weak template static, at the end of the TU's .bss (A0C). */
template <> CMinigameCore* CSingleton<CMinigameCore>::ms_pointer = 0;
