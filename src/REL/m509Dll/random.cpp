/* random.cpp -- m509's random unit: byte-identical to m501's (the shared CRandom, REL/mgcpp/random.cpp,
 * compiled on its own so the CMT19937 calls stay calls). No frandom(float). */
#define MGCPP_RANDOM_NO_FRANDOM_MAX
#include "REL/mgcpp/random.cpp"
