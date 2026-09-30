/* mt19937.cpp -- CMT19937: Matsumoto & Nishimura's MT19937 (mt19937ar.c) as a class. Retail order.
 * random() is inlined into every later generator, so each carries its own copy of the refill loop.
 * Unlike mt19937ar.c there is no auto-seed when random() is called before setSeed (mti == N+1): the
 * constructor seeds with 5489. */
#include "REL/mgcpp/mt19937.h"

#define MT_M 397
#define MT_MATRIX_A 0x9908B0DF
#define MT_UPPER_MASK 0x80000000
#define MT_LOWER_MASK 0x7FFFFFFF

void CMT19937::setSeed(int seed)
{
    mt[0] = seed;
    for (mti = 1; mti < N; mti++) {
        mt[mti] = mti + 1812433253 * (mt[mti - 1] ^ (mt[mti - 1] >> 30));
    }
}

/* init_by_array(key, len) */
void CMT19937::setSeedDefault(u32* key, u32 len)
{
    u32 i, j, k;
    setSeed(19650218);
    i = 1;
    j = 0;
    k = (N > len ? N : len);
    for (; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 30)) * 1664525)) + key[j] + j;
        i++;
        j++;
        if (i >= N) {
            mt[0] = mt[N - 1];
            i = 1;
        }
        if (j >= len) {
            j = 0;
        }
    }
    for (k = N - 1; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 30)) * 1566083941)) - i;
        i++;
        if (i >= N) {
            mt[0] = mt[N - 1];
            i = 1;
        }
    }
    mt[0] = 0x80000000;
}

/* lbl_1_rodata_50 (map.m501.txt). File scope rather than a function static only so its symbol name
 * is stable (a function static is named mag01$<counter>); the code is the same. */
static const u32 s_mtMag01[2] = { 0, MT_MATRIX_A };

u32 CMT19937::random()
{
    u32 y;
    if (mti >= N) {
        u32 kk;
        for (kk = 0; kk < N - MT_M; kk++) {
            y = (mt[kk] & MT_UPPER_MASK) | (mt[kk + 1] & MT_LOWER_MASK);
            mt[kk] = s_mtMag01[y & 1] ^ (mt[kk + MT_M] ^ (y >> 1));
        }
        for (; kk < N - 1; kk++) {
            y = (mt[kk] & MT_UPPER_MASK) | (mt[kk + 1] & MT_LOWER_MASK);
            mt[kk] = s_mtMag01[y & 1] ^ (mt[kk + (MT_M - N)] ^ (y >> 1));
        }
        y = (mt[N - 1] & MT_UPPER_MASK) | (mt[0] & MT_LOWER_MASK);
        mt[N - 1] = (y >> 1) ^ mt[MT_M - 1] ^ s_mtMag01[y & 1];
        mti = 0;
    }
    y = mt[mti++];
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9D2C5680;
    y ^= (y << 15) & 0xEFC60000;
    y ^= (y >> 18);
    return y;
}

s32 CMT19937::irandom()
{
    return random() >> 1;
}

/* [0,1): genrand_real2 */
float CMT19937::nrandom()
{
    return random() * (1.0f / 4294967296.0f);
}

/* genrand_real1 in the original (1/4294967295); both constants round to the same float */
float CMT19937::nrandom2()
{
    return random() * (1.0f / 4294967295.0f);
}

/* (0,1): genrand_real3 */
float CMT19937::nrandomMid()
{
    return (random() + 0.5f) * (1.0f / 4294967296.0f);
}

/* [0,1) with 53-bit resolution: genrand_res53 */
double CMT19937::frandom()
{
    u32 a = random() >> 5;
    u32 b = random() >> 6;
    return (a * 67108864.0 + b) * (1.0 / 9007199254740992.0);
}

float CMT19937::randomMantissa()
{
    u32 mantissa = random() >> 9;
    return mantissa * (1.0f / 8388608.0f);
}
