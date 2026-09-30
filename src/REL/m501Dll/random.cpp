/* random.cpp -- m501's random unit: the shared CRandom (REL/mgcpp/random.cpp), compiled on its own, so the
 * CMT19937 calls are not inlined. m501 has no frandom(float). */
#define MGCPP_RANDOM_NO_FRANDOM_MAX
#include "REL/mgcpp/random.cpp"
