/* random.h -- CRandom (random.cpp): the overlay's random source, a static CMT19937 seeded with 5489 at
 * static-init time (the game reseeds it, m501 from OSGetTick() in CGameMaster::on_setup). Global namespace.
 * Symbol names are m501's (random.o); the other overlays' copies are unnamed. */
#ifndef MGCPP_RANDOM_H
#define MGCPP_RANDOM_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/mt19937.h"

class CRandom {
public:
    static void setSeed(int seed);
    static s32 irandom();
    static float randomMantissa();
    static float frandom(float max);            /* max * randInstance.frandom() (not in m501) */
    static float frandom(float min, float max); /* min + (max-min)*randInstance.frandom() (in double) */

    static CMT19937 randInstance;
};

#endif
