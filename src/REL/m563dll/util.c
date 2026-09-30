#include "REL/m563dll/math.c"

#include "REL/m563Dll.h"

HuVecF lbl_1_data_358[2][M563_COINPOS_MAX] = {
    {
        { -656.37f, 275.0f, -374.58f }, { -611.32f, 275.0f, -269.54f }, { -580.76f, 275.0f, -449.21f },
        { -410.12f, 275.0f, -438.82f }, { -405.87f, 275.0f, -318.71f }, { -299.85f, 275.0f, -423.99f },
        { -191.97f, 275.0f, -428.29f }, { -496.53f, 275.0f, -378.35f }, { -640.12f, 275.0f, -178.55f },
        { -505.99f, 275.0f, -267.83f }, { -521.6f, 275.0f, -149.12f }, { -599.5f, 275.0f, -59.4f },
        { -71.51f, 275.0f, -443.27f }, { -115.31f, 225.0f, -247.72f }, { -48.84f, 225.0f, -324.95f },
        { -210.0f, 225.0f, -290.93f }, { -272.56f, 175.0f, -158.9f }, { -326.64f, 175.0f, -243.11f },
        { -329.66f, 125.0f, -50.17f }, { -423.81f, 125.0f, -83.33f }, { -215.25f, 75.0f, 18.77f },
        { -43.95f, 75.0f, -89.69f }, { -159.76f, 75.0f, -99.5f },
    },
    {
        { -645.03f, 225.0f, 124.54f }, { -552.23f, 225.0f, 67.48f }, { -553.21f, 175.0f, 333.57f },
        { -645.57f, 175.0f, 267.78f }, { -37.07f, 158.09f, 289.81f }, { -153.2f, 157.7f, 310.96f },
        { -262.04f, 156.17f, 271.3f }, { -611.53f, 125.0f, 479.41f }, { -510.2f, 125.0f, 467.18f },
        { -634.24f, 125.0f, 591.55f }, { -632.27f, 125.0f, 705.62f }, { -492.9f, 125.0f, 687.64f },
        { -495.52f, 125.0f, 577.2f }, { -367.34f, 125.0f, 675.43f }, { -375.27f, 125.0f, 540.36f },
        { -407.87f, 125.0f, 428.11f }, { -439.37f, 125.0f, 295.02f }, { -330.24f, 125.0f, 339.34f },
        { -90.0f, 75.0f, 688.37f }, { -206.75f, 75.0f, 701.42f }, { -100.24f, 75.0f, 576.49f },
        { -217.41f, 75.0f, 592.6f }, { -206.53f, 75.0f, 479.42f }, { -431.31f, 75.0f, 99.33f },
        { -315.66f, 75.0f, 91.26f }, { -148.88f, 75.0f, 105.1f }, { -45.2f, 75.0f, 51.37f },
        { -84.73f, 75.0f, 456.83f },
    },
};

static int lbl_1_bss_3C0[M563_SIDE_MAX][M563_COINPOS_MAX];

/* Pick one of the first 29 positions of a side's set. Y is returned relative
 * to the water surface (75); the result says whether it lands in the water. */
BOOL fn_1_767C(float *x, float *y, float *z, int side, int *idx)
{
    int set;
    int no;
    BOOL waterF;
    float scale;

    switch (side) {
        case 0:
            set = 0;
            scale = 1.0f;
            break;
        case 1:
            set = 0;
            scale = -1.0f;
            break;
        case 2:
            set = 1;
            scale = 1.0f;
            break;
        case 3:
            set = 1;
            scale = -1.0f;
            break;
    }
    no = frandmod(29);
    *x = scale * lbl_1_data_358[set][no].x;
    if (75.0f == lbl_1_data_358[set][no].y) {
        *y = 0.0f;
        waterF = TRUE;
    } else {
        *y = lbl_1_data_358[set][no].y - 75.0f;
        waterF = FALSE;
    }
    *z = lbl_1_data_358[set][no].z;
    *idx = no;
    return waterF;
}

void fn_1_7818(float *x, float *y, float *z, int side)
{
    int set;
    int no;
    BOOL waterF;
    float scale;

    switch (side) {
        case 0:
            set = 0;
            scale = 1.0f;
            break;
        case 1:
            set = 0;
            scale = -1.0f;
            break;
        case 2:
            set = 1;
            scale = 1.0f;
            break;
        case 3:
            set = 1;
            scale = -1.0f;
            break;
    }
    no = frandmod(29);
    *x = scale * lbl_1_data_358[set][no].x;
    if (75.0f == lbl_1_data_358[set][no].y) {
        *y = 0.0f;
        waterF = TRUE;
    } else {
        *y = lbl_1_data_358[set][no].y - 75.0f;
        waterF = FALSE;
    }
    *z = lbl_1_data_358[set][no].z;
}

int fn_1_79A8(int side, int idx)
{
    return lbl_1_bss_3C0[side][idx];
}

void fn_1_79C8(int side, int idx, int usedF)
{
    lbl_1_bss_3C0[side][idx] = usedF;
}

void fn_1_79E8(void)
{
    int i;
    int j;

    for (i = 0; i < M563_SIDE_MAX; i++) {
        for (j = 0; j < M563_COINPOS_MAX; j++) {
            lbl_1_bss_3C0[i][j] = 0;
        }
    }
}
