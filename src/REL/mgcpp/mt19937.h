/* mt19937.h -- CMT19937 (mt19937.cpp): Mersenne Twister MT19937. GC size 0x9C4.
 * mt[] must be 32-bit on every target (u32, never unsigned long): the algorithm relies on 32-bit wrap. */
#ifndef MGCPP_MT19937_H
#define MGCPP_MT19937_H

#include "REL/mgcpp/game.h"

class CMT19937 {
public:
    enum { N = 624 };
    /* random.cpp's __sinit calls setSeed(5489) on CRandom::randInstance and nothing else */
    CMT19937() { setSeed(5489); }
    void setSeed(int seed);
    /* retail symbol setSeedDefault__8CMT19937Fv, but the body is MT init_by_array(key, len): it reads r4/r5
     * (map.m501.txt). Unreferenced. */
    void setSeedDefault(u32* key, u32 len);
    u32 random();
    s32 irandom();         /* random() >> 1 */
    float nrandom();       /* [0,1) */
    float nrandom2();
    float nrandomMid();
    double frandom();      /* 53-bit [0,1) */
    float randomMantissa();

    u32 mt[N]; /* 0x000 */
    u32 mti;   /* 0x9C0 */
};

#endif
