/* random.cpp -- CRandom: the overlay's random source (a static MT19937).
 *
 * m501 compiles this file as its own unit (m501dll/random.cpp), so the CMT19937 calls stay calls. Every
 * other framework-unit overlay of the survey includes it in the framework unit between om.cpp and
 * sphere.cpp, after mt19937.cpp, so -inline auto inlines setSeed/irandom/randomMantissa (54/143/157
 * instructions) and the framework __sinit grows the inlined setSeed(5489) (34 -> 88).
 *
 * Knob: MGCPP_RANDOM_NO_FRANDOM_MAX -- omit frandom(float) (m501). */
#include "REL/mgcpp/random.h"

CMT19937 CRandom::randInstance; /* __sinit: setSeed(5489) via the inline CMT19937() */

void CRandom::setSeed(int seed) { randInstance.setSeed(seed); }
s32 CRandom::irandom() { return randInstance.irandom(); }
float CRandom::randomMantissa() { return randInstance.randomMantissa(); }
#ifndef MGCPP_RANDOM_NO_FRANDOM_MAX
float CRandom::frandom(float max) { return max * randInstance.frandom(); }
#endif
float CRandom::frandom(float min, float max) { return min + (max - min) * randInstance.frandom(); }
