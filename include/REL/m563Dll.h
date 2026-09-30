#ifndef _M563DLL_H
#define _M563DLL_H

#include "dolphin/types.h"
#include "humath.h"

#define M563_SIDE_MAX 4
#define M563_COINPOS_MAX 30

/* util.c: two 30-entry landing-position sets, mirrored in X per side. */
extern HuVecF lbl_1_data_358[2][M563_COINPOS_MAX];

BOOL fn_1_767C(float *x, float *y, float *z, int side, int *idx);
void fn_1_7818(float *x, float *y, float *z, int side);
int fn_1_79A8(int side, int idx);
void fn_1_79C8(int side, int idx, int usedF);
void fn_1_79E8(void);

#endif
