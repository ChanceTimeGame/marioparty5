/*
 * m535dll -- a Battle minigame (MG_TYPE_BATTLE, overlay #49).
 *
 * One translation unit, 17 functions, 12,174 instructions, all of it this
 * overlay's own code: the twin scan against every other reference object found
 * no shared block, not even with the other Battle overlay m538dll.
 *
 * Line ranges are into build/mp5-asm/m535Dll/asm/REL/m535Dll/m535.s.
 *
 * Shape: own OMOBJ graph, no mgframe.h, no seqman, no MgActor. ObjectSetup
 * calls omInitObjMan(600, 0x2000) + omGameSysInit itself, creates two cameras
 * (bits 1 and 2) with omOutViewMulti, and adds five objects:
 *
 *   prio 101  mdl 75 mtn 2  grp 1  fn_1_A3C4   stage   -> lbl_1_bss_8268
 *   prio 100  mdl 1  mtn 4  grp 0  fn_1_B31C   player  -> lbl_1_bss_826C[4]
 *   prio 32730                     omOutViewMulti      -> lbl_1_bss_827C
 *   prio 102                       fn_1_B700           -> lbl_1_bss_8280
 *   prio 103  mdl 1              fn_1_BDC8             -> lbl_1_bss_8264
 *
 * No omMakeGroupEx call: the group numbers are handed to omAddObjEx and the
 * object pointers are kept in .bss by hand.
 *
 * _prolog and _epilog are not reproduced.
 */

#include "game/audio.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/flag.h"
#include "game/frand.h"
#include "game/gamemes.h"
#include "game/gamework.h"
#include "game/esprite.h"
#include "game/hsfex.h"
#include "game/hu3d.h"
#include "game/init.h"
#include "game/memory.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/wipe.h"

#include <string.h>

#include "datadir_enum.h"

#include "dolphin/gx.h"
#include "dolphin/mtx.h"
#include "dolphin/os.h"

#include "math.h"
#include "humath.h"

#include "REL/m535Dll/m535.h"

/* esprite.c keeps ESPRITE/ESPANIM file-local, so the overlay redeclares them. */
typedef struct esprite_s {
    /* 0x00 */ s16 memberNo;
    /* 0x02 */ s16 animNo;
} ESPRITE;

typedef struct espanim_s {
    /* 0x00 */ unsigned int dataNum;
    /* 0x04 */ u16 useCnt;
    /* 0x08 */ ANIMDATA *anim;
} ESPANIM;

extern ESPRITE esprite[];
extern ESPANIM espanim[];

/* sprite.h has this prototype commented out. */
void HuSprTexLoad(ANIMDATA *anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);

/* ---- .data ------------------------------------------------------------ */

/* .data:0x0 -- the ten character model directories. Nothing in the overlay
 * reads it; dtk names it pad_04_00000000_data. Written anyway. */
s32 lbl_1_data_0[13] = {
    DATA_mariomdl1, DATA_luigimdl1, DATA_peachmdl1, DATA_yoshimdl1,
    DATA_wariomdl1, DATA_daisymdl1, DATA_waluigimdl1, DATA_kinopiomdl1,
    DATA_teresamdl1, DATA_minikoopamdl1, 0, 0, 0,
};

s32 lbl_1_data_34[4] = {
    DATA_mariomot, DATANUM(DATA_mario, 0xBC), DATANUM(DATA_mariomot, 6),
    DATANUM(DATA_mariomot, 0x31),
};

u8 lbl_1_data_44[4] = { 0, 1, 1, 1 };
u8 lbl_1_data_48[4] = { 20, 38, 8, 8 };
s32 lbl_1_data_4C[4] = { 0, 0, 0, 0 };
s32 lbl_1_data_5C = -1;
s32 lbl_1_data_60 = -1;
s32 lbl_1_data_64 = 1;
s32 lbl_1_data_68 = -1;
s32 lbl_1_data_6C = -1;
s32 lbl_1_data_70 = -1;

/* Four player start placements: position and facing. */
f32 lbl_1_data_74[4][4] = {
    { -175.0f,    0.0f, -150.0f,  45.0f },
    {  175.0f,    0.0f, -150.0f, -45.0f },
    { -225.0f,    0.0f,    0.0f,  90.0f },
    {  225.0f,    0.0f,    0.0f, -90.0f },
};

char lbl_1_data_B4[] = "m535_omote";
char lbl_1_data_BF[] = "m535_ura";

s32 lbl_1_data_C8[3][64][64] = { 0 };  /* three ping-pong 64x64 height buffers */
s32 lbl_1_data_C0C8 = -1;
s32 lbl_1_data_C0CC[6][6] = { 0 };     /* the 6x6 raised-cosine splash kernel */
s32 lbl_1_data_C15C[4] = { 0, 0, 0, 0 };

/* .data:0xC16C.. are literals: fn_1_53F8's OSReport and jump table, and
 * ObjectSetup's banner. */

/* ---- .bss ------------------------------------------------------------- */

/* CodeWarrior emits .bss in reverse declaration order, so these are declared
 * descending to land at the reference's addresses. */
M535_OBJ lbl_1_bss_8374[54];    /* 0xBD0 */
M535_SE lbl_1_bss_8284[12];     /* a 3-deep pending sound-effect queue per slot */
OMOBJ *lbl_1_bss_8280;
OMOBJ *lbl_1_bss_827C;
OMOBJ *lbl_1_bss_826C[4];       /* the four player objects */
OMOBJ *lbl_1_bss_8268;          /* the stage object */
OMOBJ *lbl_1_bss_8264;
s32 lbl_1_bss_8260;
OMOBJMAN *lbl_1_bss_825C;
s16 lbl_1_bss_825A;
s16 lbl_1_bss_8258;
s32 lbl_1_bss_8254;
s32 lbl_1_bss_8250;             /* the s16 light id, stored word-wide */
void *lbl_1_bss_8210[16];       /* 13 used; dtk folds the tail pad */
s32 lbl_1_bss_81DC[13];         /* espEntry ids, stored word-wide */
s32 lbl_1_bss_81D8;
u32 lbl_1_bss_81D4;             /* GXGetTexBufferSize(64, 64, 3, 0, 0) */
void *lbl_1_bss_81D0;           /* the tex buffer */
f32 lbl_1_bss_81CC;
f32 lbl_1_bss_81C8;
f32 lbl_1_bss_81C4;
s32 lbl_1_bss_81B8[3];          /* the cells holding the rarest card type */
s32 lbl_1_bss_4170[0x1012];     /* tile order -> texel x; dtk folds a 0x48 tail in */
s32 lbl_1_bss_170[0x1000];      /* tile order -> texel y */
u8 lbl_1_bss_100[0x70];
u8 lbl_1_bss_D0[0x30];
GXTexObj lbl_1_bss_90[2];       /* GXTexObj is 32 bytes for CW, 88 on the host */
f32 lbl_1_bss_28[0x1A];         /* only [0] is ever touched */
s32 lbl_1_bss_24;
s32 lbl_1_bss_20;
s32 lbl_1_bss_1C;
s32 lbl_1_bss_18;
s32 lbl_1_bss_14;
s32 lbl_1_bss_10;
s32 lbl_1_bss_C;
s32 lbl_1_bss_4[2];
f32 lbl_1_bss_0;

/* ---- prototypes, in reference order ----------------------------------- */

static void fn_1_A0(void);
static void fn_1_69C(OMOBJ *obj);
static f32 fn_1_2D68(f32 t, f32 accel, f32 flat, f32 decel);
static void fn_1_2F2C(s32 arg0, s32 arg1);
static void fn_1_39A8(OMOBJ *obj);
static void fn_1_53F8(OMOBJ *obj);
static void fn_1_88F0(void);
static void fn_1_8FD8(HU3DMODEL *modelP, Mtx *mtx);
static void fn_1_97AC(HU3DMODEL *modelP, Mtx *mtx);
static void fn_1_9830(HU3DMODEL *modelP, Mtx *mtx);
static void fn_1_9F2C(HU3DMODEL *modelP, Mtx *mtx);
static void fn_1_A3C4(OMOBJ *obj);
static void fn_1_B31C(OMOBJ *obj);
static void fn_1_B700(OMOBJ *obj);
static void fn_1_BDC8(OMOBJ *obj);
static void fn_1_BE20(OMOBJ *obj);

/* ---- bodies, in reference order --------------------------------------- */

/* asm 61..447 -- unreferenced */
static void fn_1_A0(void)
{
    HuVecF pos;
    HuVecF center;
    HuVecF up;
    f32 rx;
    f32 ry;
    f32 rz;
    s16 i;

    for (i = 0; i < 2; i++) {
        CenterM[i].x += 5.0 * (((HuPadBtn[0] & PAD_BUTTON_RIGHT) != 0) - ((HuPadBtn[0] & PAD_BUTTON_LEFT) != 0));
        CenterM[i].y += 5.0 * (((HuPadBtn[0] & PAD_BUTTON_UP) != 0) - ((HuPadBtn[0] & PAD_BUTTON_DOWN) != 0));
        CZoomM[i] += 5.0 * (((HuPadBtn[0] & PAD_BUTTON_X) != 0) - ((HuPadBtn[0] & PAD_BUTTON_Y) != 0));
        CRotM[i].y += HuPadSubStkX[0] / 32.0;
        CRotM[i].x += HuPadSubStkY[0] / -32.0;
        rx = CRotM[i].x;
        ry = CRotM[i].y;
        rz = CRotM[i].z;
        pos.x = CenterM[i].x + CZoomM[i] * (sin(M_PI * ry / 180.0) * cos(M_PI * rx / 180.0));
        pos.y = CenterM[i].y + CZoomM[i] * -sin(M_PI * rx / 180.0);
        pos.z = CenterM[i].z + CZoomM[i] * (cos(M_PI * ry / 180.0) * cos(M_PI * rx / 180.0));
        center.x = CenterM[i].x;
        center.y = CenterM[i].y;
        center.z = CenterM[i].z;
        up.x = sin(M_PI * ry / 180.0) * sin(M_PI * rx / 180.0);
        up.y = cos(M_PI * rx / 180.0);
        up.z = cos(M_PI * ry / 180.0) * sin(M_PI * rx / 180.0);
    }
}

/* asm 450..3084 */
static void fn_1_69C(OMOBJ *obj)
{
    Mtx mtx;
    M535_PLAYER *players[4];
    HU3DMODEL *model;
    M535_PLAYER *work;
    f32 stkX;
    f32 stkY;
    f32 btn;
    f32 prevX;
    f32 prevY;
    f32 rate;
    s16 unused;
    int i;
    int j;
    int humanNum;
    int aliveNum;
    int hitNum;
    int angle;

    work = obj->data;
    unused = -1;
    stkX = 0.0f;
    stkY = 0.0f;
    btn = 0.0f;
    prevX = work->unk028;
    prevY = work->unk02C;
    for (i = 0; i < 4; i++) {
        players[i] = lbl_1_bss_826C[i]->data;
    }
    work->unk024++;
    if (work->unk020 == 2) {
        work->unk038 = -1;
        if (lbl_1_bss_8260 == 1007) {
            if (work->unk010 != -1) {
                stkX = HuPadStkX[work->unk010];
                stkY = HuPadStkY[work->unk010];
                btn = (HuPadBtnDown[work->unk010] & PAD_BUTTON_A) != 0;
            } else {
                humanNum = 0;
                aliveNum = 0;
                for (i = 0; i < 4; i++) {
                    if (players[i]->unk010 != -1 && players[i]->unk020 != 4) {
                        aliveNum++;
                    }
                    if (players[i]->unk010 != -1) {
                        humanNum++;
                    }
                }
                j = 1;
                if (humanNum != 0 && aliveNum <= 0) {
                    j = 0;
                }
                humanNum = j;
                if (lbl_1_bss_8260 == 1007 && lbl_1_bss_8254 == 600) {
                    f32 tbl[2][4] = { { 8.0f, 7.0f, 5.5f, 4.5f }, { 1.5f, 1.5f, 1.5f, 1.5f } };
                    f32 dead[4] = { 20.0f, 1.0f, 0.0f, 0.0f };

                    work->unk054 = 600.0f - (f32)(humanNum > 0) * (60.0f * (tbl[0][work->unk014] + tbl[1][work->unk014] * rand8() / 255.0f));
                    work->unk05C = lbl_1_bss_81B8[rand8() % (3 - lbl_1_bss_1C)];
                    if (lbl_1_bss_8254 >= work->unk054) {
                        work->unk064 = 1;
                        work->unk068 = 30.0f + 150.0f * (rand8() / 255.0f);
                    } else {
                        work->unk064 = 0;
                    }
                    if (work->unk064 != 0) {
                        do {
                            work->unk05C = rand8() % 54;
                        } while (lbl_1_bss_8374[work->unk05C].unk28 == 0);
                    }
                    work->unk058 = 0;
                }
                if (lbl_1_bss_8254 < work->unk054 && work->unk064 != 0) {
                    work->unk064 = 2;
                }
                if ((players[(work->playerNo + 1) % 4]->unk020 == 5 && work->unk05C == players[(work->playerNo + 1) % 4]->unk038)
                 || (players[(work->playerNo + 2) % 4]->unk020 == 5 && work->unk05C == players[(work->playerNo + 2) % 4]->unk038)
                 || (players[(work->playerNo + 3) % 4]->unk020 == 5 && work->unk05C == players[(work->playerNo + 3) % 4]->unk038)
                 || work->unk064 == 2) {
                    f32 tbl[2][4] = { { 1.0f, 1.0f, 1.0f, 1.0f }, { 3.0f, 2.5f, 1.0f, 0.5f } };

                    if (lbl_1_bss_8254 < work->unk054) {
                        if (work->unk064 != 2) {
                            work->unk054 = (f32)lbl_1_bss_8254 - (f32)(humanNum > 0) * (60.0f * (tbl[0][work->unk014] + tbl[1][work->unk014] * rand8() / 255.0f));
                        }
                        for (i = 0; i < 32; i++) {
                            work->unk05C = lbl_1_bss_81B8[rand8() % (3 - lbl_1_bss_1C)];
                            if (players[(work->playerNo + 1) % 4]->unk020 == 5 && work->unk05C == players[(work->playerNo + 1) % 4]->unk038) {
                                continue;
                            }
                            if (players[(work->playerNo + 2) % 4]->unk020 == 5 && work->unk05C == players[(work->playerNo + 2) % 4]->unk038) {
                                continue;
                            }
                            if (players[(work->playerNo + 3) % 4]->unk020 == 5 && work->unk05C == players[(work->playerNo + 3) % 4]->unk038) {
                                continue;
                            }
                            break;
                        }
                        if (i == 32) {
                            work->unk054 = -1;
                        }
                        work->unk064 = 0;
                    } else {
                        work->unk064 = 1;
                        work->unk068 = 30.0f + 30.0f * (rand8() / 255.0f);
                        if (work->unk064 != 0) {
                            do {
                                work->unk05C = rand8() % 54;
                            } while (lbl_1_bss_8374[work->unk05C].unk28 == 0);
                        }
                    }
                    if (fabs(lbl_1_bss_8374[work->unk05C].unk00) >= 37.5
                     && (fabs(work->unk028) < 37.5 || work->unk028 * lbl_1_bss_8374[work->unk05C].unk00 <= 0.0f)) {
                        work->unk058 = 0;
                    } else {
                        work->unk058 = 3;
                    }
                }
                work->unk068 -= work->unk068 > 0;
                if ((work->unk064 == 1 && work->unk068 == 0) || lbl_1_bss_8254 < work->unk054) {
                    switch (work->unk058) {
                    case 0:
                        work->unk058++;
                        /* fallthrough */
                    case 1:
                        if (work->unk02C < -10.0f) {
                            stkY = -70.0f;
                            break;
                        }
                        work->unk058++;
                        /* fallthrough */
                    case 2:
                        if (work->unk02C < -10.0f) {
                            stkY = -70.0f;
                        }
                        if (fabs(lbl_1_bss_8374[work->unk05C].unk00) >= 37.5
                         && (fabs(work->unk028) < 37.5 || work->unk028 * lbl_1_bss_8374[work->unk05C].unk00 <= 0.0f)) {
                            if (lbl_1_bss_8374[work->unk05C].unk00 < 0.0f) {
                                j = -70;
                            } else {
                                j = 70;
                            }
                            stkX = j;
                            break;
                        }
                        work->unk058++;
                        /* fallthrough */
                    case 3:
                        stkX = lbl_1_bss_8374[work->unk05C].unk00 - work->unk028;
                        stkY = -(lbl_1_bss_8374[work->unk05C].unk04 - work->unk02C);
                        if (HuMagPoint2D(stkX, stkY) < work->unk014 + 5) {
                            if (work->unk064 != 0) {
                                work->unk064 += work->unk064 == 1;
                                if (work->unk014 < 1) {
                                    btn = rand8() % 4 == 0;
                                }
                            } else {
                                btn = 1.0f;
                            }
                        }
                        break;
                    }
                }
                {
                    HuVecF dir = { 0.0f, 0.0f, 0.0f };

                    dir.x = stkX;
                    dir.z = -stkY;
                    j = rand8() % 2 * 2;
                    angle = work->unk060 * 3 % 360 + (j - 1);
                    PSMTXRotRad(mtx, 'y', 0.017453292f * (45.0 * HuSin(angle)));
                    PSMTXMultVec(mtx, &dir, &dir);
                    stkX = dir.x;
                    stkY = -dir.z;
                    stkX *= 4.0f;
                    stkY *= 4.0f;
                }
            }
        }
        {
            f32 mag;

            stkX /= 20.0f;
            stkY /= 20.0f;
            mag = HuMagPoint2D(stkX, stkY);
            if (mag > 1.0f) {
                stkX *= 1.0f / mag;
                stkY *= 1.0f / mag;
            }
        }
        work->unk028 = work->unk028 + 1.25 * stkX;
        work->unk02C = work->unk02C - 1.25 * stkY;
    } else if (work->unk020 == 5) {
        f32 dx;
        f32 dy;
        f32 mag;

        dx = work->unk028 - lbl_1_bss_8374[work->unk038].unk00;
        dy = work->unk02C - lbl_1_bss_8374[work->unk038].unk04;
        mag = HuMagPoint2D(dx, dy);
        if (mag > 0.0f) {
            dx = dx / mag * ((mag < 1.0f) ? 0.0f : mag - 1.0f);
            dy = dy / mag * ((mag < 1.0f) ? 0.0f : mag - 1.0f);
            work->unk028 = dx + lbl_1_bss_8374[work->unk038].unk00;
            work->unk02C = dy + lbl_1_bss_8374[work->unk038].unk04;
        }
        work->unk030 -= 0.2f;
        work->unk030 = (work->unk030 < 0.0f) ? 0.0f : work->unk030;
        Hu3DModelPosSet(lbl_1_bss_8268->mdlId[work->playerNo + 13], work->unk028, 61.0f + work->unk030, work->unk02C);
    } else if (work->unk020 == 3) {
        work->unk038 = -1;
        if (work->unk024 >= 45) {
            work->unk020 = 2;
            work->unk024 = 0;
        }
    }
    if (work->unk020 == 2 || work->unk020 == 3) {
        hitNum = 0;
        for (i = 0; i < 4; i++) {
            f32 dx;
            f32 dy;
            f32 mag;

            if (work->playerNo == i) {
                continue;
            }
            if (players[i]->unk020 == 4) {
                continue;
            }
            dx = players[i]->unk028 - work->unk028;
            dy = players[i]->unk02C - work->unk02C;
            mag = HuMagPoint2D(dx, dy);
            if (mag < 15.0f) {
                work->unk028 = players[i]->unk028 - 15.0f * (dx / mag);
                work->unk02C = players[i]->unk02C - 15.0f * (dy / mag);
                hitNum++;
            }
        }
        work->unk060 = (hitNum != 0) ? work->unk060 + 1 : 0;
        work->unk028 = (work->unk028 < -105.0f) ? -105.0f : ((work->unk028 > 105.0f) ? 105.0f : work->unk028);
        work->unk02C = (work->unk02C < -80.0f) ? -80.0f : ((work->unk02C > 80.0f) ? 80.0f : work->unk02C);
        for (i = 0; i < 3; i++) {
            f32 px;
            f32 py;
            f32 rad;
            f32 dx;
            f32 dy;
            f32 mag;

            if (i == 0) {
                px = 0.0f;
                py = -60.0f;
                rad = 22.5f;
            } else {
                px = work->unk028;
                py = work->unk02C;
                if (i == 1) {
                    j = 10;
                } else {
                    j = 2;
                }
                rad = j;
                if (i == 1) {
                    px = (px < -20.0f) ? -20.0f : ((px > 20.0f) ? 20.0f : px);
                    py = (py < -100.0f) ? -100.0f : ((py > -57.0f) ? -57.0f : py);
                } else {
                    px = (px < -37.0f) ? -37.0f : ((px > 37.0f) ? 37.0f : px);
                    py = (py < -100.0f) ? -100.0f : ((py > -63.0f) ? -63.0f : py);
                }
            }
            dx = px - work->unk028;
            dy = py - work->unk02C;
            mag = HuMagPoint2D(dx, dy);
            if (mag < 7.5f + rad && 0.0f != mag) {
                work->unk028 = px - (7.5f + rad) * (dx / mag);
                work->unk02C = py - (7.5f + rad) * (dy / mag);
            }
        }
        if (lbl_1_bss_8260 >= 1006 || (lbl_1_bss_8260 == 1005 && lbl_1_bss_0 >= 60.0f)) {
            work->unk030 += 0.2f;
        }
        work->unk030 = (work->unk030 > 3.0f) ? 3.0f : work->unk030;
        Hu3DModelPosSet(lbl_1_bss_8268->mdlId[work->playerNo + 13], work->unk028, 61.0f + work->unk030, work->unk02C);
        if (work->unk020 == 2 && btn != 0.0f) {
            for (i = 0; i < 54; i++) {
                if (lbl_1_bss_8374[i].unk00 - 12.5f <= work->unk028
                 && work->unk028 <= 12.5f + lbl_1_bss_8374[i].unk00
                 && lbl_1_bss_8374[i].unk04 - 12.5f <= work->unk02C
                 && work->unk02C <= 12.5f + lbl_1_bss_8374[i].unk04) {
                    break;
                }
            }
            work->unk038 = i;
            work->unk050 = 0;
        }
    }
    if (work->unk050 >= 0) {
        if (work->unk050 == 0) {
            Hu3DModelAttrReset(lbl_1_bss_8268->mdlId[work->playerNo + 17], HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(lbl_1_bss_8268->mdlId[work->playerNo + 17], 0.0f);
        }
        Hu3DModelPosSet(lbl_1_bss_8268->mdlId[work->playerNo + 17], work->unk028, 61.0f, work->unk02C);
        if (work->unk050 >= 30) {
            work->unk050 = -1;
            Hu3DModelAttrSet(lbl_1_bss_8268->mdlId[work->playerNo + 17], HU3D_ATTR_DISPOFF);
        } else {
            work->unk050++;
        }
    }
    work->unk33C -= work->unk020 == 2 && 0.0f != stkX && 0.0f != stkY && prevX != work->unk028 && prevY != work->unk02C;
    if (work->unk33C <= 0) {
        for (i = 0; i < 30; i++) {
            if (work->unk2C4[i] < 0) {
                work->unk2C4[i] = 0;
                work->unk06C[i] = work->unk028 + 6.0f * (rand8() / 255.0f) - 3.0f;
                work->unk0E4[i] = 5.0f + (61.0f + 2.0f * (rand8() / 255.0f));
                work->unk15C[i] = work->unk02C + 6.0f * (rand8() / 255.0f) - 3.0f;
                work->unk24C[i] = 255;
                break;
            }
        }
        work->unk33C = rand8() % 5 + 2;
    }
    for (i = 0; i < 30; i++) {
        if (work->unk2C4[i] < 0) {
            continue;
        }
        if (work->unk2C4[i] >= 40) {
            work->unk2C4[i] = -1;
        } else {
            work->unk2C4[i]++;
        }
        work->unk0E4[i] -= 0.125f;
        work->unk24C[i] = (work->unk0E4[i] < 3.0f) ? 192.0f * (work->unk0E4[i] / 3.0f) : 192.0f;
        work->unk1D4[i] = ((work->unk2C4[i] < 20) ? 1.0f : (f32)(40 - work->unk2C4[i]) / 20.0f) * (3.5 * (0.25 + 0.75 * (rand8() / 255.0f)));
    }
    {
        f32 tblX[2][10] = {
            { 10.0f, 10.0f, 15.0f, 0.0f, 0.0f, 15.0f, 0.0f, 8.0f, 0.0f, 0.0f },
            { 0.0f, 0.0f, 5.0f, -3.0f, 0.0f, 5.0f, 0.0f, 22.0f, 0.0f, 9.0f },
        };
        f32 tblZ[2][10] = {
            { 0.0f, 0.0f, 0.0f, 0.0f, 15.0f, 0.0f, 15.0f, 10.0f, 0.0f, 10.0f },
            { 0.0f, 0.0f, 5.0f, -3.0f, 0.0f, 5.0f, 0.0f, -8.0f, 0.0f, 9.0f },
        };
        int mot;
        int row;

        model = &Hu3DData[obj->mdlId[0]];
        if (model->motIdShift != -1) {
            rate = model->motOvlWork.start / model->motOvlWork.end;
            if (model->motId == obj->mtnId[1]) {
                rate = 1.0f - rate;
            }
            if (model->motId != obj->mtnId[1] && model->motIdShift != obj->mtnId[1]) {
                rate = 0.0f;
            }
        } else {
            mot = (model->motId == obj->mtnId[1]) ? 1 : 0;
            rate = mot;
        }
        row = (work->playerNo / 2 == 1) ? 1 : 0;
        obj->trans.x = lbl_1_data_74[work->playerNo][0] + (f32)((work->playerNo % 2 == 1) ? -1 : 1) * (rate * tblX[row][work->unk008]);
        obj->trans.z = lbl_1_data_74[work->playerNo][2] + rate * tblZ[(work->playerNo / 2 == 1) ? 1 : 0][work->unk008];
    }
}

/* asm 3087..3207 -- unreferenced, leaf */
static f32 fn_1_2D68(f32 t, f32 accel, f32 flat, f32 decel)
{
    f32 total;

    total = decel * 0.5f + (accel * 0.5f + flat);
    return (t < accel)
               ? (1.0f + t) * 0.5f * t / accel / total
               : (t < accel + flat)
                     ? (1.0f + accel) * 0.5f * accel / accel / total + (t - accel) / total
                     : (t < decel + (accel + flat) - 1.0f)
                           ? 1.0f - (1.0f + (decel + (accel + flat) - t - 1.0f)) * 0.5f
                                        * (decel + (accel + flat) - 1.0f - t - 1.0f) / (decel - 1.0f) / total
                           : 1.0f;
}

/* asm 3210..3905 */
static void fn_1_2F2C(s32 arg0, s32 arg1)
{
    s32 variant = rand8() % 3;
    s32 kind[12] = { 0 };
    s32 kindUsed[12] = { 0 };
    s32 kindNum[3][3][12] = {
        {
            {  3,  3,  3,  3,  3,  6,  6,  6,  6,  5,  5,  5 },
            {  3,  3,  3,  3,  3,  9,  8,  7,  5,  4,  4,  2 },
            {  3,  3,  3,  3,  3, 12,  7,  6,  5,  4,  4,  1 },
        },
        {
            {  2,  2,  2,  2,  2,  2,  2,  8,  8,  8,  8,  8 },
            {  2,  2,  2,  2,  2,  2,  2, 12, 11,  8,  5,  4 },
            {  2,  2,  2,  2,  2,  2,  2, 10,  9,  8,  7,  6 },
        },
        {
            {  1,  1,  1,  1,  1,  1,  1,  1, 12, 12, 11, 11 },
            {  1,  1,  1,  1,  1,  1,  1,  1, 20, 15,  8,  3 },
            {  1,  1,  1,  1,  1,  1,  1,  1, 15, 15, 10,  6 },
        },
    };
    s32 colNum[9] = { 0 };
    s32 cellUsed[9][6] = { 0 };
    s32 grid[11][9] = { 0 };
    char *animName;
    s32 i;
    s32 n;
    s32 cell;
    s32 cell2;
    s32 row;
    s32 gx;
    s32 gy;
    s32 gx2;
    s32 gy2;
    s32 r;
    s32 tmp2;
    s32 tmp;

    for (i = 0; i < 11; i++) {
        for (r = 0; r < 9; r++) {
            grid[i][r] = -1;
        }
    }
    for (i = 0; i < 12; i++) {
        do {
            r = rand8();
        } while (r >= 252 || kindUsed[r % 12] != 0 || (i == 0 && r % 12 == lbl_1_data_6C));
        r = r % 12;
        kind[i] = r;
        kindUsed[r] = 1;
    }
    lbl_1_data_6C = kind[0];
    n = 0;
    for (i = 0; i < 54; i++) {
        do {
            r = rand8();
        } while (r >= 252 || colNum[r % 9] >= 6);
        r = r % 9;
        do {
            row = rand8();
        } while (row >= 252 || cellUsed[r][row % 6] >= 1);
        row = row % 6;
        cell = row + r * 6;
        colNum[r]++;
        cellUsed[r][row]++;
        lbl_1_bss_8374[cell].unk28 = n;
        grid[(s32)(1.0f + (4.0f + lbl_1_bss_8374[cell].unk00 / 25.0f))]
            [(s32)(1.0f + (3.0f + lbl_1_bss_8374[cell].unk04 / 25.0f))] = n;
        kindNum[arg0][variant][n]--;
        if (n == 0) {
            lbl_1_bss_81B8[kindNum[arg0][variant][n]] = cell;
        }
        n += (kindNum[arg0][variant][n] <= 0);
    }
    for (i = 0; i < 3 - arg0; i++) {
        cell = lbl_1_bss_81B8[i];
        gx = (s32)(1.0f + (4.0f + lbl_1_bss_8374[cell].unk00 / 25.0f));
        gy = (s32)(1.0f + (3.0f + lbl_1_bss_8374[cell].unk04 / 25.0f));
        if (lbl_1_bss_8374[cell].unk28 == grid[gx - 1][gy]
            || lbl_1_bss_8374[cell].unk28 == grid[gx + 1][gy]
            || lbl_1_bss_8374[cell].unk28 == grid[gx][gy - 1]
            || lbl_1_bss_8374[cell].unk28 == grid[gx][gy + 1]) {
            do {
                cell2 = rand8();
            } while (cell2 == cell || cell2 >= 216
                     || lbl_1_bss_8374[cell2 % 54].unk28 == lbl_1_bss_8374[cell].unk28);
            cell2 = cell2 % 54;
            gx2 = (s32)(1.0f + (4.0f + lbl_1_bss_8374[cell2].unk00 / 25.0f));
            gy2 = (s32)(1.0f + (3.0f + lbl_1_bss_8374[cell2].unk04 / 25.0f));
            tmp = lbl_1_bss_8374[cell2].unk28;
            lbl_1_bss_8374[cell2].unk28 = lbl_1_bss_8374[cell].unk28;
            lbl_1_bss_8374[cell].unk28 = tmp;
            lbl_1_bss_81B8[i] = cell2;
            tmp2 = grid[gx2][gy2];
            grid[gx2][gy2] = grid[gx][gy];
            grid[gx][gy] = tmp2;
            i = 0;
        }
    }
    for (i = 0; i < 54; i++) {
        cell = i;
        lbl_1_bss_8374[cell].unk1C[arg0] = kind[lbl_1_bss_8374[cell].unk28];
        if (lbl_1_bss_8374[cell].unk30[arg1 % 2] != -1) {
            Hu3DAnimKill(lbl_1_bss_8374[cell].unk30[arg1 % 2]);
        }
        if (arg1 % 2 == 0) {
            animName = lbl_1_data_B4;
        } else {
            animName = lbl_1_data_BF;
        }
        lbl_1_bss_8374[cell].unk30[arg1 % 2] =
            Hu3DAnimCreate(lbl_1_bss_8210[kind[lbl_1_bss_8374[cell].unk28]],
                           lbl_1_bss_8268->mdlId[cell + 0x15], animName);
    }
}

/* asm 3908..5691 */
static void fn_1_39A8(OMOBJ *obj)
{
    M535_PLAYER *works[4];
    u32 total;
    s32 sum;
    int prev1;
    int prev2;
    int cx;
    int cy;
    int i;
    int j;
    int x;
    int y;
    int v;                      /* the grid layer, the clamped cell value and the
                                 * player index all share this register in retail */
    int parity0;
    int parity1;
    float dx;
    float dy;
    float dist;
    float span;
    float amp;
    float frame;
    float t0;
    float t1;
    float t2;
    float denom;
    float scale;                /* both dead: retail writes them and never reads */
    float scale2;
    float progA;
    float progB;
    float prog;
    float invProg;

    for (i = 0; i < 4; i++) {
        works[i] = lbl_1_bss_826C[i]->data;
    }
    if (Hu3DMotionTimeGet(lbl_1_bss_8268->mdlId[7]) >= Hu3DMotionMaxTimeGet(lbl_1_bss_8268->mdlId[7])) {
        Hu3DModelAttrSet(lbl_1_bss_8268->mdlId[7], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_8268->mdlId[4], HU3D_MOTATTR_PAUSE);
        Hu3DMotionTimeSet(lbl_1_bss_8268->mdlId[7], 0.0f);
    }
    if (lbl_1_data_70 == 1 || lbl_1_data_70 == -1) {
        total = 0;
        if (lbl_1_data_70 == -1) {
            lbl_1_data_70 = 0;
        }
        if (lbl_1_data_C0C8 == -1) {
            /* border cells stay at 0 so the simulation has a fixed edge */
            for (v = 0; v < 3; v++) {
                for (y = 0; y < 64; y++) {
                    for (x = 0; x < 64; x++) {
                        lbl_1_data_C8[v][y][x] = (x == 0 || y == 0 || x == 63 || y == 63) ? 0 : 1;
                    }
                }
            }
            for (y = 0; y < 6; y++) {
                for (x = 0; x < 6; x++) {
                    float radius = 2.5f;

                    dx = (float)x - radius;
                    dy = (float)y - radius;
                    dist = HuMagPoint2D(dx, dy);
                    lbl_1_data_C0CC[y][x] = (dist < radius)
                        ? 256.0 * (64.0 * (0.5 * (1.0 + HuCos(180.0f * (dist / radius)))))
                        : 0.0;
                }
            }
            /* GX 4x4-tile order -> texel (x, y); x and y here are dead */
            for (i = 0; i < 4096; i++) {
                x = i % 64;
                y = i / 64;
                lbl_1_bss_4170[i] = i % 4 + i / 16 * 4 % 64;
                lbl_1_bss_170[i] = i / 4 % 4 + i / 16 * 4 / 64 * 4;
            }
        }
        lbl_1_data_C0C8 = lbl_1_data_C0C8 + 1;
        lbl_1_data_C0C8 = lbl_1_data_C0C8 % 3;
        prev2 = (lbl_1_data_C0C8 + 2) % 3;
        prev1 = (lbl_1_data_C0C8 + 1) % 3;
        for (y = 1; y < 63; y++) {
            for (x = 1; x < 63; x++) {
                if (lbl_1_data_C8[lbl_1_data_C0C8][y][x] > 0) {
                    v = (lbl_1_data_C8[prev2][y - 1][x] + lbl_1_data_C8[prev2][y][x - 1]
                         + lbl_1_data_C8[prev2][y][x + 1] + lbl_1_data_C8[prev2][y + 1][x]) / 2
                        - lbl_1_data_C8[prev1][y][x];
                    lbl_1_data_C8[lbl_1_data_C0C8][y][x] = (v < 1) ? 1 : ((v > 0xFFFF) ? 0xFFFF : v);
                }
                total += lbl_1_data_C8[lbl_1_data_C0C8][y][x] >> 8;
            }
        }
        /* one forced drop per queued hit, then the ambient rain */
        for (i = -lbl_1_bss_18;
             i < ((lbl_1_bss_8260 == 1007 && lbl_1_bss_8254 == 600) ? 15 : ((lbl_1_bss_8260 == 1007) ? 1 : 0));
             i++) {
            cx = (i == -1) ? 64.0f * lbl_1_bss_81CC : (float)(rand8() % 64);
            cy = (i == -1) ? 64.0f * lbl_1_bss_81C8 : (float)(rand8() % 64);
            {
                float speedTbl[3] = { 4.0f, 5.0f, 6.0f };

                span = 600.0f * speedTbl[lbl_1_bss_1C] / 10.0f;
            }
            amp = (i == -1)
                ? lbl_1_bss_81C4
                : (((float)lbl_1_bss_8254 > 600.0f - span)
                   ? 3.0f * ((float)lbl_1_bss_8254 - (600.0f - span)) / span
                   : 0.0f);
            amp = (amp > 2.5) ? 3.0 : ((amp > 1.75) ? 1.0 + 2.0 * ((amp - 1.75) / 0.75) : amp / 1.75);
            for (y = 0; y < 6; y++) {
                for (x = 0; x < 6; x++) {
                    int px = x + cx - 3;
                    int py = y + cy - 3;

                    if (px > 0 && px < 63 && py > 0 && py < 63
                        && lbl_1_data_C8[lbl_1_data_C0C8][py][px] > 0) {
                        v = (float)lbl_1_data_C8[lbl_1_data_C0C8][py][px] + amp * (float)lbl_1_data_C0CC[y][x];
                        lbl_1_data_C8[lbl_1_data_C0C8][py][px] = (v < 1) ? 1 : ((v > 0xFFFF) ? 0xFFFF : v);
                    }
                }
            }
        }
        if (lbl_1_bss_8260 >= 1007) {
            lbl_1_bss_14 = (lbl_1_bss_14 < 4) ? 0 : lbl_1_bss_14 - 4;
        }
        /* sum is read below even when this whole block is skipped -- see NOTES. */
        sum = total;
        lbl_1_bss_28[0] = (float)total * 0.015625f * 0.015625f;
        total = total / 3 / 64 / 64 - 3;    /* dead store; nothing reads it again */
        for (i = 0; i < 4096; i++) {
            ((u8 *)lbl_1_bss_81D0)[i * 2] =
                0x80 - (lbl_1_data_C8[lbl_1_data_C0C8][lbl_1_bss_170[i]][lbl_1_bss_4170[i]] >> 8 >> 2);
            ((u8 *)lbl_1_bss_81D0)[i * 2 + 1] =
                0x80 - ((u32)(lbl_1_data_C8[lbl_1_data_C0C8][lbl_1_bss_170[i]][lbl_1_bss_4170[i]] >> 8 >> 2) >> 2);
        }
    }
    if (lbl_1_bss_8284[8].unk10 != -1) {
        if (sum < ((lbl_1_bss_8260 == 1007) ? 4800 : 6000) || lbl_1_data_70 != 1) {
            if (lbl_1_bss_8284[8].unk10 != -1) {
                HuAudFXStop(lbl_1_bss_8284[8].unk10);
                lbl_1_bss_8284[8].unk10 = -1;
            }
            if (lbl_1_bss_8284[9].unk00 < 3) {
                lbl_1_bss_8284[9].unk04[lbl_1_bss_8284[9].unk00] = 0.0f;
                lbl_1_bss_8284[9].unk00++;
            }
        }
    }
    if (lbl_1_data_70 != 0) {
        Hu3DModelAttrSet(lbl_1_bss_826C[2]->mdlId[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_826C[3]->mdlId[0], HU3D_ATTR_DISPOFF);
    } else {
        Hu3DModelAttrReset(lbl_1_bss_826C[2]->mdlId[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(lbl_1_bss_826C[3]->mdlId[0], HU3D_ATTR_DISPOFF);
    }
    parity1 = rand8() % 2;
    parity0 = rand8() % 2;
    for (i = 0; i < 4; i++) {
        v = parity0 + parity1 * 2;
        parity1 = (i % 2 == 1) ? 1 - parity1 : parity1;
        parity0 = 1 - parity0;
        if (works[v]->unk038 == -1) {
            continue;
        }
        if (works[v]->unk020 != 2) {
            continue;
        }
        for (j = 1; j < 4; j++) {
            if (works[v]->unk038 == works[(v + j) % 4]->unk038
                && works[(v + j) % 4]->unk020 != 2) {
                break;
            }
        }
        Hu3DModelAttrReset(obj->mdlId[v + 13], HU3D_MOTATTR_PAUSE);
        if (j < 4 || works[v]->unk038 == 0x36 || lbl_1_bss_8374[works[v]->unk038].unk28 != 0) {
            works[v]->unk020 = 3;
            Hu3DMotionSet(obj->mdlId[v + 13], obj->mtnId[1]);
            omVibrate(works[v]->padIdx, 12, 4, 2);
            if (lbl_1_bss_8284[5].unk00 < 3) {
                lbl_1_bss_8284[5].unk04[lbl_1_bss_8284[5].unk00] = works[v]->unk028 / 110.0f;
                lbl_1_bss_8284[5].unk00++;
            }
        } else {
            works[v]->unk020 = 5;
            Hu3DMotionSet(obj->mdlId[v + 13], obj->mtnId[0]);
            omVibrate(works[v]->padIdx, 12, 6, 6);
            if (lbl_1_bss_8284[4].unk00 < 3) {
                lbl_1_bss_8284[4].unk04[lbl_1_bss_8284[4].unk00] = works[v]->unk028 / 110.0f;
                lbl_1_bss_8284[4].unk00++;
            }
        }
        works[v]->unk024 = 0;
    }
    lbl_1_bss_18 = 0;
    if (lbl_1_data_68 != -1) {
        lbl_1_bss_10 = lbl_1_bss_10 + 1;
        {
            float zoomTbl[3] = { 500.0f, 1100.0f, 210.0f };
            float centerTbl[3] = { 70.0f, 115.0f, 140.0f };
            float rotTbl[3] = { -66.0f, -11.5f, -50.0f };
            int pairTbl[3][2] = { { 1, 2 }, { 2, 0 }, { 0, 1 } };
            int timeTbl[3][3] = { { 35, 35, 50 }, { 15, 2, 40 }, { 10, 30, 50 } };

            t2 = (float)timeTbl[lbl_1_data_68][2];
            t1 = (float)timeTbl[lbl_1_data_68][1];
            t0 = (float)timeTbl[lbl_1_data_68][0];
            frame = (float)lbl_1_bss_10;
            scale = frame;
            scale2 = scale;
            denom = t2 * 0.5f + (t0 * 0.5f + t1);
            progA = (frame < t0)
                ? (1.0f + frame) * 0.5f * frame / t0 / denom
                : ((frame < t0 + t1)
                   ? (1.0f + t0) * 0.5f * t0 / t0 / denom + (frame - t0) / denom
                   : ((frame < t2 + (t0 + t1) - 1.0f)
                      ? 1.0f - (1.0f + (t2 + (t0 + t1) - frame - 1.0f)) * 0.5f
                                * ((t2 + (t0 + t1) - 1.0f - frame) - 1.0f) / (t2 - 1.0f) / denom
                      : 1.0f));
            progB = progA;
            prog = progB;
            invProg = 1.0f - prog;
            for (i = 0; i < 2; i++) {
                CZoomM[i] = invProg * zoomTbl[pairTbl[lbl_1_data_68][0]] + prog * zoomTbl[pairTbl[lbl_1_data_68][1]];
                CenterM[i].y = invProg * centerTbl[pairTbl[lbl_1_data_68][0]] + prog * centerTbl[pairTbl[lbl_1_data_68][1]];
                CRotM[i].x = invProg * rotTbl[pairTbl[lbl_1_data_68][0]] + prog * rotTbl[pairTbl[lbl_1_data_68][1]];
            }
            if (lbl_1_bss_10 >= timeTbl[lbl_1_data_68][0] + timeTbl[lbl_1_data_68][1] + timeTbl[lbl_1_data_68][2]) {
                lbl_1_data_68 = -1;
                lbl_1_bss_10 = 0;
            }
        }
    }
    DCFlushRange(lbl_1_bss_81D0, lbl_1_bss_81D4);
}

/* asm 5694..9233 -- the main mode machine (11 cases) */
static void fn_1_53F8(OMOBJ *obj)
{
    M535_PLAYER *works[4];
    s32 i;

    lbl_1_bss_4[0]++;
    for (i = 0; i < 4; i++) {
        works[i] = lbl_1_bss_826C[i]->data;
    }
    for (i = 0; i < 12; i++) {
        s32 handle;
        s32 seNo[12] = {
            0x7C3, 0x7C4, 0x7C5, 0x7C6, 0x7C7, 0x7C8,
            0x7C9, 0x7CA, 0x7CB, 0x7CC, 0x7CD, 0x7CE,
        };

        if (lbl_1_bss_8284[i].unk00 > 3) {
            lbl_1_bss_8284[i].unk00 = 3;
        }
        if (lbl_1_bss_8284[i].unk00 > 0) {
            if (seNo[i] != -1) {
                handle = HuAudFXPlay(seNo[i]);
                lbl_1_bss_8284[i].unk10 = handle;
                HuAudFXPanning(handle, 0.5 + (64.0f + 32.0f * lbl_1_bss_8284[i].unk04[lbl_1_bss_8284[i].unk00 - 1]));
                lbl_1_bss_8284[i].unk00--;
            }
        }
    }
    if (omSysExitReq != 0) {
        if (!WipeCheckEnd()) {
            if (lbl_1_bss_C == 0) {
                HuAudFadeOut(1000);
                lbl_1_data_64 = 1;
                lbl_1_bss_C = 1;
            }
        }
    }
    switch (lbl_1_bss_8260) {
    case 1000:
        lbl_1_bss_0 += 1.0f;
        if (!WipeCheckEnd()) {
            lbl_1_bss_8260++;
            lbl_1_bss_0 = 0.0f;
        }
        break;

    case 1001: {
        s32 attr;

        lbl_1_bss_0 += 1.0f;
        if (20.0f == lbl_1_bss_0) {
            for (i = 0; i < 4; i++) {
                if (lbl_1_data_44[1]) {
                    attr = HU3D_MOTATTR_NONE;
                } else {
                    attr = HU3D_MOTATTR_LOOP;
                }
                Hu3DMotionShiftSet(lbl_1_bss_826C[i]->mdlId[0], lbl_1_bss_826C[i]->mtnId[1],
                                   lbl_1_data_4C[1], lbl_1_data_48[1], attr);
            }
            lbl_1_data_68 = 0;
        }
        if (lbl_1_bss_0 >= 70.0f) {
            lbl_1_bss_8260++;
            lbl_1_bss_0 = 0.0f;
        }
        break;
    }

    case 1002:
        lbl_1_bss_0 += 1.0f;
        if (1.0f == lbl_1_bss_0) {
            Hu3DModelAttrReset(lbl_1_bss_8268->mdlId[4], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(lbl_1_bss_8268->mdlId[4], HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrReset(lbl_1_bss_8268->mdlId[5], HU3D_MOTATTR_PAUSE);
            if (lbl_1_bss_8284[0].unk00 < 3) {
                lbl_1_bss_8284[0].unk04[lbl_1_bss_8284[0].unk00] = 0.0f;
                lbl_1_bss_8284[0].unk00++;
            }
            if (lbl_1_bss_8284[10].unk00 < 3) {
                lbl_1_bss_8284[10].unk04[lbl_1_bss_8284[10].unk00] = 0.0f;
                lbl_1_bss_8284[10].unk00++;
            }
            for (i = 0; i < 54; i++) {
                lbl_1_bss_8374[i].unk10 = 70.0f;
            }
        }
        if (lbl_1_bss_0 >= 106.0f) {
            lbl_1_bss_8260++;
            lbl_1_bss_0 = 0.0f;
            lbl_1_data_70 = 1;
        }
        break;

    case 1003: {
        s32 j;
        s32 attr;
        s32 cnt;
        f32 posY;
        f32 speed;
        f32 rate;
        f32 inv;
        f32 scale;

        if (15.0f == lbl_1_bss_0) {
            lbl_1_data_68 = 1;
            for (i = 0; i < 4; i++) {
                j = 0;
                if (lbl_1_data_44[j]) {
                    attr = HU3D_MOTATTR_NONE;
                } else {
                    attr = HU3D_MOTATTR_LOOP;
                }
                Hu3DMotionShiftSet(lbl_1_bss_826C[i]->mdlId[0], lbl_1_bss_826C[i]->mtnId[j],
                                   lbl_1_data_4C[j], lbl_1_data_48[j], attr);
            }
        }
        cnt = 0;
        if ((s32)lbl_1_bss_0 < 54) {
            i = 53 - (s32)lbl_1_bss_0;
            if (i == 53) {
                if (lbl_1_bss_8284[1].unk00 < 3) {
                    lbl_1_bss_8284[1].unk04[lbl_1_bss_8284[1].unk00] = 0.0f;
                    lbl_1_bss_8284[1].unk00++;
                }
            }
            Hu3DModelAttrReset(lbl_1_bss_8268->mdlId[i + 0x15], HU3D_ATTR_DISPOFF);
            Hu3DModelShadowMapObjReset(lbl_1_bss_8268->mdlId[i + 0x15]);
            Hu3DModelShadowDispOn(lbl_1_bss_8268->mdlId[i + 0x15]);
            lbl_1_bss_8374[i].unk2C = 1;
            posY = lbl_1_bss_8374[i].unk10;
            speed = 10.0f;
            lbl_1_bss_8374[i].unk14 = speed;
            lbl_1_bss_8374[i].unk18 = 0;
            while (posY > 61.0f || speed > 0.0f) {
                posY += speed;
                speed -= 0.5f;
                lbl_1_bss_8374[i].unk18++;
            }
            lbl_1_bss_18 = 1;
            lbl_1_bss_81C4 = 0.6f;
            lbl_1_bss_81CC = 0.5 + 0.125 * (2.0f * (rand8() / 255.0f) - 1.0f);
            lbl_1_bss_81C8 = 0.5 + 0.125 * (2.0f * (rand8() / 255.0f) - 1.0f);
            lbl_1_bss_8374[i].unk08 = 18.0 * ((lbl_1_bss_81CC - 0.5) / 0.5);
            lbl_1_bss_8374[i].unk0C = -60.0 + 18.0 * ((lbl_1_bss_81C8 - 0.5) / 0.5);
        }
        lbl_1_bss_0 += 1.0f;
        for (i = 0; i < 54; i++) {
            if (lbl_1_bss_8374[i].unk2C > 0) {
                rate = (f32)lbl_1_bss_8374[i].unk2C / (f32)lbl_1_bss_8374[i].unk18;
                inv = 1.0f - rate;
                if (rate <= 1.0f) {
                    lbl_1_bss_8374[i].unk10 += lbl_1_bss_8374[i].unk14;
                    if (1.0f == rate) {
                        lbl_1_bss_8374[i].unk10 = 61.0f;
                        Hu3DModelShadowDispOff(lbl_1_bss_8268->mdlId[i + 0x15]);
                        Hu3DModelShadowMapSet(lbl_1_bss_8268->mdlId[i + 0x15]);
                        if (i == 53) {
                            if (lbl_1_bss_8284[2].unk00 < 3) {
                                lbl_1_bss_8284[2].unk04[lbl_1_bss_8284[2].unk00] = 0.0f;
                                lbl_1_bss_8284[2].unk00++;
                            }
                        }
                        if (i == 0) {
                            if (lbl_1_bss_8284[10].unk10 != -1) {
                                HuAudFXStop(lbl_1_bss_8284[10].unk10);
                                lbl_1_bss_8284[10].unk10 = -1;
                            }
                        }
                    }
                    lbl_1_bss_8374[i].unk14 -= 0.5f;
                    Hu3DModelPosSet(lbl_1_bss_8268->mdlId[i + 0x15],
                                    rate * lbl_1_bss_8374[i].unk00 + inv * lbl_1_bss_8374[i].unk08,
                                    lbl_1_bss_8374[i].unk10,
                                    rate * lbl_1_bss_8374[i].unk04 + inv * lbl_1_bss_8374[i].unk0C);
                    scale = 0.25 + 0.75 * rate;
                    Hu3DModelScaleSet(lbl_1_bss_8268->mdlId[i + 0x15], scale, scale, scale);
                    lbl_1_bss_8374[i].unk2C++;
                    cnt++;
                }
            }
        }
        if (cnt == 0) {
            lbl_1_bss_8260++;
            lbl_1_bss_0 = 0.0f;
            for (i = 0; i < 4; i++) {
                works[i]->unk020 = 2;
            }
        }
        break;
    }

    case 1004: {
        s32 cnt;
        f32 speed;
        f32 rate;
        f32 inv;
        f32 scale;
        f32 posY;

        cnt = 0;
        if ((s32)lbl_1_bss_0 % 10 == 2) {
            if ((s32)lbl_1_bss_0 / 10 < 4) {
                do {
                    i = rand8() % 4;
                } while (lbl_1_data_C15C[i] == 1);
                lbl_1_data_C15C[i] = 1;
                works[i]->unk040 = 1;
                posY = works[i]->unk044;
                speed = 14.400001f;
                works[i]->unk048 = speed;
                works[i]->unk04C = 0;
                while (posY > 61.0f || speed >= 0.0f) {
                    posY += speed;
                    speed -= 0.90000004f;
                    works[i]->unk04C++;
                }
                Hu3DModelAttrReset(lbl_1_bss_8268->mdlId[i + 0xD], HU3D_ATTR_DISPOFF);
                lbl_1_bss_18 = 1;
                lbl_1_bss_81C4 = 1.75f;
                lbl_1_bss_81CC = 0.5f;
                lbl_1_bss_81C8 = 0.5f;
            }
        }
        lbl_1_bss_0 += 1.0f;
        for (i = 0; i < 4; i++) {
            if (works[i]->unk040 > 0) {
                rate = (f32)works[i]->unk040 / (f32)works[i]->unk04C;
                inv = 1.0f - rate;
                if (rate <= 1.0f) {
                    scale = (rate < 0.45) ? rate / 0.45f : 1.0f;
                    works[i]->unk044 += works[i]->unk048;
                    if (works[i]->unk040 == 3) {
                        if (lbl_1_data_C15C[0] + (lbl_1_data_C15C[1] + lbl_1_data_C15C[2] + lbl_1_data_C15C[3]) == 1) {
                            if (lbl_1_bss_8284[3].unk00 < 3) {
                                lbl_1_bss_8284[3].unk04[lbl_1_bss_8284[3].unk00] = 0.0f;
                                lbl_1_bss_8284[3].unk00++;
                            }
                        }
                    }
                    if (works[i]->unk040 == works[i]->unk04C - 1) {
                        if (lbl_1_bss_8284[11].unk00 < 3) {
                            lbl_1_bss_8284[11].unk04[lbl_1_bss_8284[11].unk00] = 0.0f;
                            lbl_1_bss_8284[11].unk00++;
                        }
                    }
                    if (1.0f == rate) {
                        works[i]->unk044 = 61.0f;
                        omVibrate(works[i]->padIdx, 12, 6, 6);
                    }
                    works[i]->unk048 -= 0.90000004f;
                    Hu3DModelPosSet(lbl_1_bss_8268->mdlId[i + 0xD],
                                    rate * works[i]->unk028,
                                    10.0f * scale + (works[i]->unk044 - scale * (10.0 * HuCos(-600.0f * inv))),
                                    (-68.0f * inv + rate * works[i]->unk02C) - scale * (10.0 * HuSin(-600.0f * inv)));
                    Hu3DModelRotSet(lbl_1_bss_8268->mdlId[i + 0xD], -600.0f * inv, 0.0f, 0.0f);
                    Hu3DModelScaleSet(lbl_1_bss_8268->mdlId[i + 0xD], scale, scale, scale);
                    works[i]->unk040++;
                    cnt++;
                }
            }
        }
        if (cnt == 0) {
            if ((s32)lbl_1_bss_0 / 10 >= 4) {
                lbl_1_bss_8260++;
                lbl_1_bss_0 = 0.0f;
            }
        }
        break;
    }

    case 1005:
        lbl_1_bss_0 += 1.0f;
        if (5.0f == lbl_1_bss_0) {
            if (lbl_1_bss_825A < 0) {
                lbl_1_bss_825A = GameMesMgStartCreate();
            }
        }
        if (lbl_1_bss_0 >= 5.0f) {
            if (lbl_1_data_60 == -1) {
                lbl_1_data_60 = HuAudSStreamPlay(0x34);
            }
        }
        if (lbl_1_bss_0 >= 30.0f) {
            if (lbl_1_bss_0 <= 90.0f) {
                lbl_1_bss_14 = 255.0f * ((lbl_1_bss_0 - 30.0f) / 60.0f);
            }
        }
        if (lbl_1_bss_0 >= 5.0f) {
            if (!GameMesStatGet(lbl_1_bss_825A)) {
                if (lbl_1_bss_825A >= 0) {
                    lbl_1_bss_8260++;
                    lbl_1_bss_8254 = 0;
                    lbl_1_bss_825A = -1;
                    lbl_1_bss_0 = 0.0f;
                    Hu3DModelAttrSet(lbl_1_bss_8268->mdlId[4], HU3D_ATTR_DISPOFF);
                }
            }
        }
        break;

    case 1006:
        lbl_1_bss_0 += 1.0f;
        lbl_1_bss_8260++;
        lbl_1_bss_8254 = 600;
        lbl_1_bss_0 = 0.0f;
        lbl_1_bss_8258 = GameMesTimerCreate(lbl_1_bss_8254 / 60);
        GameMesPosSet(lbl_1_bss_8258, 288.0f, 64.0f);
        lbl_1_bss_24 = lbl_1_data_6C;
        Hu3DModelAttrReset(lbl_1_bss_8268->mdlId[7], HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrReset(lbl_1_bss_8268->mdlId[7], HU3D_ATTR_DISPOFF);
        Hu3DMotionTimeSet(lbl_1_bss_8268->mdlId[7], 0.0f);
        if (lbl_1_bss_8284[8].unk00 < 3) {
            lbl_1_bss_8284[8].unk04[lbl_1_bss_8284[8].unk00] = 0.0f;
            lbl_1_bss_8284[8].unk00++;
        }
        break;

    case 1007: {
        s32 num;

        lbl_1_bss_0 += 1.0f;
        if (lbl_1_bss_8258 != -1) {
            GameMesTimerValueSet(lbl_1_bss_8258, (lbl_1_bss_8254 + 58) / 60);
        }
        lbl_1_bss_8254 -= lbl_1_bss_8254 > 0;
        num = (works[0]->unk020 == 5) + ((works[1]->unk020 == 5) + (works[2]->unk020 == 5) + (works[3]->unk020 == 5));
        if (lbl_1_bss_8254 > 0 && num < 3 - lbl_1_bss_1C) {
            break;
        }
        lbl_1_bss_8260 = 1008;
        lbl_1_bss_0 = 0.0f;
        break;
    }

    case 1008: {
        s32 j;
        s32 num;
        s32 cnt;
        s32 any;
        s32 time;
        f32 rate;
        f32 inv;
        f32 dist;
        f32 baseDist;
        f32 dirX;
        f32 dirZ;

        lbl_1_bss_0 += 1.0f;
        if (1.0f == lbl_1_bss_0) {
            GameMesTimerEnd(lbl_1_bss_8258);
            for (i = 0; i < 4; i++) {
                if (works[i]->unk020 == 5) {
                    continue;
                }
                if (works[i]->unk03C != 0) {
                    continue;
                }
                works[i]->unk03C = 3 - lbl_1_bss_1C;
            }
            num = (works[0]->unk020 == 5) + ((works[1]->unk020 == 5) + (works[2]->unk020 == 5) + (works[3]->unk020 == 5));
            if (num <= 1) {
                lbl_1_bss_825A = GameMesMgFinishCreate();
                if (lbl_1_data_60 != -1) {
                    HuAudSStreamFadeOut(lbl_1_data_60, 100);
                }
                lbl_1_data_5C = 4;
                for (i = 0; i < 4; i++) {
                    if (works[i]->unk020 == 5) {
                        lbl_1_data_5C = i;
                        break;
                    }
                }
            } else {
                lbl_1_bss_1C = 4 - num;
                lbl_1_bss_20++;
            }
        }
        if (lbl_1_bss_0 >= 30.0f && lbl_1_bss_0 <= 150.0f) {
            cnt = 0;
            for (i = 0; i < 4; i++) {
                if (works[i]->unk020 != 5 && works[i]->unk020 != 4) {
                rate = (lbl_1_bss_0 - 30.0f) / 90.0f;
                inv = 1.0f - rate;
                dist = HuMagPoint2D(works[i]->unk028, -60.0f - works[i]->unk02C);
                baseDist = dist;
                dirX = works[i]->unk028 / dist;
                dirZ = (-60.0f - works[i]->unk02C) / dist;
                dist -= 300.0f * ((lbl_1_bss_0 - 30.0f) / 120.0f);
                if (30.0f == lbl_1_bss_0) {
                    omVibrate(works[i]->padIdx, 20, 1, 0);
                    if (lbl_1_bss_8284[6].unk00 < 3) {
                        lbl_1_bss_8284[6].unk04[lbl_1_bss_8284[6].unk00] = works[i]->unk028 / 110.0f;
                        lbl_1_bss_8284[6].unk00++;
                    }
                }
                if (dist >= 0.0f) {
                    dist = (dist < 0.0f) ? 0.0f : dist;
                    rate = 1.0f - dist / baseDist;
                    inv = 1.0f - rate;
                    Hu3DModelPosSet(lbl_1_bss_8268->mdlId[i + 0xD],
                                    inv * works[i]->unk028,
                                    61.0 + 30.0 * ((rate < 0.5) ? HuSin(90.0 * (rate / 0.5)) : 1.0),
                                    -60.0f * rate + inv * works[i]->unk02C);
                    Hu3DModelRotSet(lbl_1_bss_8268->mdlId[i + 0xD],
                                    10.0 + 10.0 * ((rate < 0.5) ? HuSin(90.0 * (rate / 0.5)) : 1.0),
                                    -HuAtan(dirX, dirZ), 0.0f);
                    Hu3DModelScaleSet(lbl_1_bss_8268->mdlId[i + 0xD], 1.0f, 1.0f, 1.0f);
                    works[i]->unk034 = 0.0f;
                } else {
                    works[i]->unk034 += 1.0f;
                    if (20.0f == works[i]->unk034) {
                        lbl_1_bss_18 = 1;
                        lbl_1_bss_81CC = lbl_1_bss_81C8 = 0.5f;
                        lbl_1_bss_81C4 = 1.5f;
                    }
                    if (works[i]->unk034 < 25.0f) {
                        rate = works[i]->unk034 / 25.0f;
                        inv = 1.0f - rate;
                        Hu3DModelPosSet(lbl_1_bss_8268->mdlId[i + 0xD], 0.0f, 91.0f + -30.0f * rate, -60.0f);
                        Hu3DModelScaleSet(lbl_1_bss_8268->mdlId[i + 0xD], inv, inv, inv);
                        Hu3DModelRotSet(lbl_1_bss_8268->mdlId[i + 0xD],
                                        380.0f * rate + -HuAtan(dirX, dirZ), 20.0f, 0.0f);
                    } else {
                        Hu3DModelAttrSet(lbl_1_bss_8268->mdlId[i + 0xD], HU3D_ATTR_DISPOFF);
                        cnt++;
                    }
                }
                } else {
                    cnt++;
                }
            }
            if (cnt >= 4) {
                lbl_1_bss_0 = 150.0f;
            }
        }
        if (lbl_1_data_5C == -1 || !GameMesStatGet(lbl_1_bss_825A)) {
            if (lbl_1_data_5C == -1) {
                time = 15;
            } else {
                time = 0;
            }
            if (lbl_1_bss_0 > (f32)(time + 150)) {
                if (lbl_1_data_5C == -1) {
                    lbl_1_bss_8260++;
                    lbl_1_bss_0 = 0.0f;
                } else {
                    lbl_1_bss_8260 = 1010;
                    lbl_1_bss_0 = 0.0f;
                    lbl_1_data_68 = 2;
                    {
                    s32 rank = 0;
                    s32 place[4] = { 0, 0, 0, 0 };

                    for (i = 0; i < 4; i++) {
                        any = 0;
                        for (j = 0; j < 4; j++) {
                            if (i == works[j]->unk03C) {
                                place[j] = rank;
                                any = 1;
                            }
                        }
                        rank += any;
                    }
                    for (i = 0; i < 4; i++) {
                        if (place[0] == place[1] && place[0] == place[2] && place[0] == place[3]) {
                            GWMgCoinBonusSet(works[i]->padIdx, 3);
                        } else {
                            GWMgCoinBonusSet(works[i]->padIdx, place[i]);
                        }
                    }
                    }
                }
            }
        }
        if (lbl_1_data_5C != -1) {
            break;
        }
        if (lbl_1_bss_0 > 150.0f && lbl_1_bss_0 <= 165.0f) {
            for (i = 0; i < 4; i++) {
                if (works[i]->unk020 == 5) {
                    Hu3DModelAttrSet(lbl_1_bss_8268->mdlId[i + 0xD], HU3D_MOTATTR_PAUSE);
                    Hu3DMotionTimeSet(lbl_1_bss_8268->mdlId[i + 0xD], 15.0f - ((lbl_1_bss_0 - 30.0f) - 120.0f));
                }
            }
        }
        break;
    }

    case 1009: {
        s32 maxTime;
        s32 time;
        s32 any;
        f32 rate;
        f32 inv;
        f32 scale;

        lbl_1_bss_0 += 1.0f;
        if (1.0f == lbl_1_bss_0) {
            fn_1_2F2C(lbl_1_bss_1C, lbl_1_bss_20);
            if (lbl_1_bss_8284[7].unk00 < 3) {
                lbl_1_bss_8284[7].unk04[lbl_1_bss_8284[7].unk00] = 0.0f;
                lbl_1_bss_8284[7].unk00++;
            }
        }
        maxTime = Hu3DMotionMaxTimeGet(lbl_1_bss_8268->mdlId[i + 0x15]);
        {
            f32 tbl[4][2] = {
                { -25.0f, -38.0f },
                { -10.0f, -27.0f },
                {  10.0f, -27.0f },
                {  25.0f, -38.0f },
            };

            any = 0;
            if (lbl_1_bss_0 >= 0.0f && lbl_1_bss_0 <= (f32)maxTime) {
                any = 1;
            }
            time = (any) ? lbl_1_bss_0 : (f32)maxTime;
            for (i = 0; i < 4; i++) {
                if (works[i]->unk020 == 5) {
                    rate = (f32)time / (f32)maxTime;
                    inv = 1.0f - rate;
                    scale = 1.0f - (rate - 0.5f) * (rate - 0.5f) / 0.5f / 0.5f;
                    Hu3DModelPosSet(lbl_1_bss_8268->mdlId[i + 0xD],
                                    inv * works[i]->unk028 + rate * tbl[i][0],
                                    61.0f + 70.0f * scale,
                                    inv * works[i]->unk02C + rate * tbl[i][1]);
                }
            }
            lbl_1_bss_14 = 255.0f * lbl_1_bss_0 / (f32)maxTime;
            lbl_1_bss_14 = (lbl_1_bss_14 < 0) ? 0 : ((lbl_1_bss_14 > 255) ? 255 : lbl_1_bss_14);
            time = (lbl_1_bss_20 % 2 == 0) ? maxTime - time : time;
            for (i = 0; i < 54; i++) {
                Hu3DMotionTimeSet(lbl_1_bss_8268->mdlId[i + 0x15], time);
                if (1.0f == lbl_1_bss_0) {
                    Hu3DModelShadowMapObjReset(lbl_1_bss_8268->mdlId[i + 0x15]);
                    Hu3DModelShadowDispOn(lbl_1_bss_8268->mdlId[i + 0x15]);
                } else if (lbl_1_bss_0 == (f32)(maxTime - 1)) {
                    Hu3DModelShadowDispOff(lbl_1_bss_8268->mdlId[i + 0x15]);
                    Hu3DModelShadowMapSet(lbl_1_bss_8268->mdlId[i + 0x15]);
                }
            }
            if (lbl_1_bss_0 == (f32)(maxTime + 30)) {
                lbl_1_bss_8260 = 1006;
                lbl_1_bss_8254 = 0;
                lbl_1_bss_825A = -1;
                lbl_1_bss_0 = 0.0f;
                for (i = 0; i < 4; i++) {
                    if (works[i]->unk020 == 5) {
                        works[i]->unk020 = 2;
                        works[i]->unk028 = tbl[i][0];
                        works[i]->unk02C = tbl[i][1];
                    } else {
                        works[i]->unk020 = 4;
                    }
                    works[i]->unk024 = 0;
                }
            }
        }
        break;
    }

    case 1010: {
        s32 k;

        lbl_1_bss_0 += 1.0f;
        if (5.0f == lbl_1_bss_0) {
            lbl_1_data_70 = 0;
        }
        if (76.0f == lbl_1_bss_0) {
            for (i = 0; i < 4; i++) {
                k = (lbl_1_data_5C == i) ? 2 : 3;
                Hu3DMotionShiftSet(lbl_1_bss_826C[i]->mdlId[0], lbl_1_bss_826C[i]->mtnId[k],
                                   lbl_1_data_4C[k], lbl_1_data_48[k],
                                   lbl_1_data_44[k] ? HU3D_MOTATTR_NONE : HU3D_MOTATTR_LOOP);
                if (lbl_1_data_5C == 4) {
                    CharFXPlay(works[i]->charNo, 0x200);
                }
            }
            if (lbl_1_data_5C != 4) {
                HuAudSStreamPlay(0x79);
            } else {
                HuAudSStreamPlay(0x7B);
            }
        }
        if (lbl_1_bss_0 >= 76.0f) {
            for (i = 0; i < 4; i++) {
                if (lbl_1_data_5C == i || works[i]->unk008 != 6 || works[i]->playerNo < 2) {
                    lbl_1_bss_826C[i]->rot.y *= 0.8f;
                }
            }
        }
        for (i = 0; i < 4; i++) {
            if (lbl_1_data_5C == 4 || lbl_1_data_5C == i / 2) {
                works[i]->unk020 = (works[i]->unk020 == 7) ? 9 : works[i]->unk020;
            }
        }
        if (286.0f < lbl_1_bss_0) {
            if (lbl_1_bss_C == 0) {
                lbl_1_bss_825A = -1;
                lbl_1_bss_C = 1;
            }
        }
        break;
    }

    default:
        OSReport("*** main mode error(%d)!!\n", lbl_1_bss_8260);
        break;
    }
}

/* asm 9236..9681 -- unreferenced */
static void fn_1_88F0(void)
{
    GXColor clear = { 0, 0, 0, 0 };
    s32 i;
    s32 a;
    s32 b;

    C_MTXOrtho((void *)lbl_1_bss_D0, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f);
    GXSetProjection((void *)lbl_1_bss_D0, GX_ORTHOGRAPHIC);
    PSMTXIdentity((void *)lbl_1_bss_100);
    GXLoadPosMtxImm((void *)lbl_1_bss_100, GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 130);
    for (i = 0; i < 64; i++) {
        a = 128.0 + 127.0 * cos(M_PI * (i / 64.0f * 360.0f) / 180.0);
        b = 128.0 + 127.0 * cos(M_PI * (i / 64.0f * 360.0f * 2.0f) / 180.0);
        GXPosition3f32(0.0f, i / 480.0f, 0.0f);
        GXColor4u8(0, b, a, 255);
        GXPosition3f32(0.1f, i / 480.0f, 0.0f);
        GXColor4u8(0, b, a, 255);
    }
    GXPosition3f32(0.0f, i / 480.0f, 0.0f);
    GXColor4u8(0, b, a, 255);
    GXPosition3f32(0.1f, i / 480.0f, 0.0f);
    GXColor4u8(0, b, a, 255);
    GXSetCopyFilter(GX_FALSE, RenderMode->sample_pattern, GX_FALSE, RenderMode->vfilter);
    GXSetTexCopySrc(0, 0, 64, 64);
    GXSetTexCopyDst(64, 64, GX_CTF_GB8, GX_FALSE);
    GXSetCopyClear(clear, 0xFFFFFF);
    GXCopyTex(lbl_1_bss_81D0, GX_TRUE);
    DCFlushRange(lbl_1_bss_81D0, lbl_1_bss_81D4);
    GXPixModeSync();
    GXSetCopyFilter(RenderMode->aa, RenderMode->sample_pattern, GX_TRUE, RenderMode->vfilter);
}

/* asm 9684..10193 */
static void fn_1_8FD8(HU3DMODEL *modelP, Mtx *mtx)
{
    f32 unused24 = 1.0f;
    f32 unused20 = 1.0f;
    f32 unused1C = 1.0f;
    f32 unused18 = 1.0f;
    f32 span = 60.0f;
    f32 unused14 = (lbl_1_bss_4[0] % (s32)span) / span;
    GXColor col = { 255, 255, 255, 255 };
    int no;

    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ONE, GX_CC_A0, GX_CC_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    col.a = lbl_1_bss_14;
    GXSetTevColor(GX_TEVREG0, col);
    if (lbl_1_bss_8260 < 1006) {
        no = 12;
    } else {
        no = lbl_1_bss_24;
    }
    HuSprTexLoad(espanim[esprite[lbl_1_bss_81DC[no]].animNo].anim, 0, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    GXSetVtxDesc(GX_VA_TEX1, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX1, GX_TEX_ST, GX_F32, 0);
    GXInitTexObj(&lbl_1_bss_90[1], lbl_1_bss_81D0, 64, 64, GX_TF_IA8, GX_REPEAT, GX_REPEAT, GX_FALSE);
    GXLoadTexObj(&lbl_1_bss_90[1], GX_TEXMAP1);
    GXInitTexObjLOD(&lbl_1_bss_90[1], GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    {
        f32 indMtx[2][3] = {
            { 0.0f, 1.0f, 0.0f },
            { 1.0f, 0.0f, 0.0f },
        };

        GXSetNumTexGens(2);
        GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
        GXSetNumIndStages(1);
        GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP1);
        GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
        GXSetIndTexMtx(GX_ITM_0, indMtx, 0);
        GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
        {
            f32 warpAmp = -0.4f;
            f32 warpBias = -0.05f;
            f32 pts[14][2] = {
                {        0.0f,        0.0f },
                {        20.0f,       0.0f },
                {   17.320507f,     -10.0f },
                {    9.999999f, -17.320509f },
                {      -1e-06f,     -20.0f },
                {      -10.0f, -17.320509f },
                {  -17.320507f,     -10.0f },
                {  -19.999998f,      0.0f },
                {  -17.320505f,      10.0f },
                {   -9.999998f,  17.320509f },
                {       1e-06f,  19.999998f },
                {       10.0f,  17.320503f },
                {   17.320507f,      10.0f },
                {       20.0f,       0.0f },
            };
            int i;
            int n;
            int j;

            GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 14);
            for (i = 0; i < 14; i++) {
                if (i == 0) {
                    n = 0;
                } else {
                    n = 13 - (i - 1);
                }
                j = n;
                GXPosition3f32(pts[j][0], 0.0f, pts[j][1]);
                GXTexCoord2f32(0.5f + pts[j][0] / 20.0f / 2.0f + warpAmp * (lbl_1_bss_28[0] / 128.0f + warpBias) / 4.0f,
                               0.5f + pts[j][1] / 20.0f / 2.0f + warpAmp * (lbl_1_bss_28[0] / 128.0f + warpBias));
                GXTexCoord2f32(0.5f + pts[j][0] / 20.0f / 2.0f + warpAmp * (lbl_1_bss_28[0] / 128.0f + warpBias) / 4.0f,
                               0.5f + pts[j][1] / 20.0f / 2.0f + warpAmp * (lbl_1_bss_28[0] / 128.0f + warpBias));
            }
            GXSetNumIndStages(0);
            GXSetTevDirect(GX_TEVSTAGE0);
        }
    }
}

/* asm 10196..10230 -- unreferenced */
static void fn_1_97AC(HU3DMODEL *modelP, Mtx *mtx)
{
    Mtx m;

    Hu3DModelObjDrawInit();
    PSMTXTrans(m, 0.0f, 400.0f, 0.0f);
    PSMTXConcat(*mtx, m, m);
    Hu3DModelObjDraw(lbl_1_bss_8268->mdlId[21], "test4-omote", m);
}

/* asm 10233..10689 */
static void fn_1_9830(HU3DMODEL *modelP, Mtx *mtx)
{
    Mtx lookAt;
    Mtx trans;
    HuVecF quad[4] = {
        {  0.0f,  1.0f, 0.0f },
        {  1.0f,  0.0f, 0.0f },
        {  0.0f, -1.0f, 0.0f },
        { -1.0f,  0.0f, 0.0f },
    };
    HuVecF corner[4];
    HU3DCAMERA *cam;
    M535_PLAYER *work;
    int i;
    int j;
    s32 alpha;
    f32 scale;

    for (i = 0; i < 16; i++) {
        if (modelP->cameraBit & (1 << i)) {
            break;
        }
    }
    cam = &Hu3DCamera[i];
    C_MTXLookAt(lookAt, &cam->pos, &cam->up, &cam->target);
    PSMTXTranspose(lookAt, trans);
    PSMTXMultVecArray(trans, quad, corner, 4);
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASA, GX_CC_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_NOOP);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    HuSprTexLoad(espanim[esprite[lbl_1_bss_81D8].animNo].anim, 0, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    for (i = 0; i < 4; i++) {
        work = lbl_1_bss_826C[i]->data;
        for (j = 0; j < 30; j++) {
            HuVecF pos = { 0.0f, 0.0f, 0.0f };

            if (work->unk2C4[j] < 0) {
                continue;
            }
            pos.x = work->unk06C[j];
            pos.y = work->unk0E4[j];
            pos.z = work->unk15C[j];
            alpha = work->unk24C[j];
            scale = work->unk1D4[j];
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(pos.x + corner[0].x * scale, pos.y + corner[0].y * scale, pos.z + corner[0].z * scale);
            GXColor4u8(255, 255, 255, alpha);
            GXTexCoord2f32(0.0f, 0.0f);
            GXPosition3f32(pos.x + corner[1].x * scale, pos.y + corner[1].y * scale, pos.z + corner[1].z * scale);
            GXColor4u8(255, 255, 255, alpha);
            GXTexCoord2f32(1.0f, 0.0f);
            GXPosition3f32(pos.x + corner[2].x * scale, pos.y + corner[2].y * scale, pos.z + corner[2].z * scale);
            GXColor4u8(255, 255, 255, alpha);
            GXTexCoord2f32(1.0f, 1.0f);
            GXPosition3f32(pos.x + corner[3].x * scale, pos.y + corner[3].y * scale, pos.z + corner[3].z * scale);
            GXColor4u8(255, 255, 255, alpha);
            GXTexCoord2f32(0.0f, 1.0f);
            GXPixModeSync();
        }
    }
}

/* asm 10692..10987 */
static void fn_1_9F2C(HU3DMODEL *modelP, Mtx *mtx)
{
    Mtx m;
    Mtx proj;
    u8 r;
    u8 g;
    u8 b;

    C_MTXOrtho(proj, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    PSMTXIdentity(m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCCLR, GX_BL_ZERO, GX_LO_NOOP);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    r = 227;
    g = 224;
    b = 220;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXColor4u8(r, g, b, 255);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(1.0f, 0.0f, 0.0f);
    GXColor4u8(r, g, b, 255);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(1.0f, 1.0f, 0.0f);
    GXColor4u8(r, g, b, 255);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(0.0f, 1.0f, 0.0f);
    GXColor4u8(r, g, b, 255);
    GXTexCoord2f32(0.0f, 1.0f);
}

/* asm 10990..11999 -- stage init */
static void fn_1_A3C4(OMOBJ *obj)
{
    M535_PLAYER *work;
    int mdl;
    int i;
    int j;

    mdl = 0;
    obj->mdlId[mdl] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m535, 0), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelLayerSet(obj->mdlId[mdl], 3);
    Hu3DModelAttrSet(obj->mdlId[mdl], HU3D_MOTATTR_LOOP);
    Hu3DModelCameraSet(obj->mdlId[mdl], 1);
    mdl = 1;
    obj->mdlId[mdl] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m535, 1), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelLayerSet(obj->mdlId[mdl], 3);
    Hu3DModelAttrSet(obj->mdlId[mdl], HU3D_MOTATTR_LOOP);
    Hu3DModelCameraSet(obj->mdlId[mdl], 1);
    Hu3DModelShadowMapSet(obj->mdlId[mdl]);
    mdl = 2;
    obj->mdlId[mdl] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m535, 2), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelLayerSet(obj->mdlId[mdl], 3);
    Hu3DModelAttrSet(obj->mdlId[mdl], HU3D_MOTATTR_LOOP);
    Hu3DModelCameraSet(obj->mdlId[mdl], 2);
    Hu3DModelShadowMapSet(obj->mdlId[mdl]);
    mdl = 3;
    obj->mdlId[mdl] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m535, 3), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelLayerSet(obj->mdlId[mdl], 3);
    Hu3DModelPosSet(obj->mdlId[mdl], 0.0f, 0.0f, -60.0f);
    Hu3DModelCameraSet(obj->mdlId[mdl], 2);
    Hu3DModelShadowMapSet(obj->mdlId[mdl]);
    mdl = 4;
    obj->mdlId[mdl] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m535, 4), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelLayerSet(obj->mdlId[mdl], 3);
    Hu3DModelPosSet(obj->mdlId[mdl], 0.0f, 0.0f, -60.0f);
    Hu3DModelAttrSet(obj->mdlId[mdl], HU3D_MOTATTR_PAUSE);
    Hu3DModelCameraSet(obj->mdlId[mdl], 2);
    Hu3DModelAttrSet(obj->mdlId[mdl], HU3D_ATTR_DISPOFF);
    mdl = 5;
    obj->mdlId[mdl] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m535, 5), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelLayerSet(obj->mdlId[mdl], 3);
    Hu3DModelAttrSet(obj->mdlId[mdl], HU3D_MOTATTR_PAUSE);
    Hu3DModelPosSet(obj->mdlId[mdl], 0.0f, 0.0f, -60.0f);
    Hu3DModelCameraSet(obj->mdlId[mdl], 2);
    Hu3DModelShadowSet(obj->mdlId[mdl]);
    mdl = 6;
    obj->mdlId[mdl] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m535, 6), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelLayerSet(obj->mdlId[mdl], 5);
    Hu3DModelAttrSet(obj->mdlId[mdl], HU3D_MOTATTR_LOOP);
    Hu3DModelPosSet(obj->mdlId[mdl], 0.0f, 69.0f, -60.0f);
    Hu3DModelCameraSet(obj->mdlId[mdl], 2);
    mdl = 7;
    obj->mdlId[mdl] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m535, 7), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelLayerSet(obj->mdlId[mdl], 5);
    Hu3DModelAttrSet(obj->mdlId[mdl], HU3D_MOTATTR_PAUSE);
    Hu3DModelPosSet(obj->mdlId[mdl], 0.0f, 0.0f, -60.0f);
    Hu3DModelCameraSet(obj->mdlId[mdl], 2);
    memset(lbl_1_bss_8374, 0, sizeof(lbl_1_bss_8374));
    {
        int colUse[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        int cellUse[9][6] = { 0 };
        int col;
        int cell;
        int idx;

        for (j = 0; j < 54; j++) {
            do {
                col = rand8();
            } while (col >= 252 || colUse[col % 9] >= 6);
            col = col % 9;
            do {
                cell = rand8();
            } while (cell >= 252 || cellUse[col][cell % 6] >= 1);
            cell = cell % 6;
            idx = cell + col * 6;
            colUse[col]++;
            cellUse[col][cell]++;
            lbl_1_bss_8374[j].unk00 = (idx < 21) ? (idx / 7) * 25 - 100 : (idx < 33) ? ((idx - 21) / 4) * 25 - 25 : ((idx - 33) / 7) * 25 + 50;
            lbl_1_bss_8374[j].unk04 = (idx < 21) ? (idx % 7) * 25 - 75 : (idx < 33) ? ((idx - 21) % 4) * 25 : ((idx - 33) % 7) * 25 - 75;
            lbl_1_bss_8374[j].unk10 = 70.0f + 0.125f * j;
            lbl_1_bss_8374[j].unk2C = 0;
            lbl_1_bss_8374[j].unk30[0] = lbl_1_bss_8374[j].unk30[1] = -1;
            mdl = j + 21;
            if (j == 0) {
                obj->mdlId[mdl] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m535, 8), HU_MEMNUM_OVL, HEAP_MODEL));
            } else {
                obj->mdlId[mdl] = Hu3DModelLink(obj->mdlId[21]);
            }
            Hu3DModelAttrSet(obj->mdlId[mdl], HU3D_MOTATTR_PAUSE);
            Hu3DModelPosSet(obj->mdlId[mdl], 0.0f, lbl_1_bss_8374[j].unk10, -60.0f);
            Hu3DModelLayerSet(obj->mdlId[mdl], 3);
            Hu3DModelCameraSet(obj->mdlId[mdl], 2);
            Hu3DModelShadowSet(obj->mdlId[mdl]);
            Hu3DModelShadowDispOff(obj->mdlId[mdl]);
            Hu3DModelShadowMapSet(obj->mdlId[mdl]);
            Hu3DModelAttrSet(obj->mdlId[mdl], HU3D_ATTR_DISPOFF);
        }
    }
    mdl = 9;
    obj->mdlId[mdl] = Hu3DHookFuncCreate(fn_1_8FD8);
    Hu3DModelLayerSet(obj->mdlId[mdl], 4);
    Hu3DModelPosSet(obj->mdlId[mdl], 0.0f, 69.0f, -60.0f);
    Hu3DModelCameraSet(obj->mdlId[mdl], 2);
    mdl = 11;
    obj->mdlId[mdl] = Hu3DHookFuncCreate(fn_1_9830);
    Hu3DModelLayerSet(obj->mdlId[mdl], 6);
    Hu3DModelCameraSet(obj->mdlId[mdl], 2);
    mdl = 12;
    obj->mdlId[mdl] = Hu3DHookFuncCreate(fn_1_9F2C);
    Hu3DModelLayerSet(obj->mdlId[mdl], 2);
    Hu3DModelCameraSet(obj->mdlId[mdl], 1);
    for (i = 0; i < 13; i++) {
        unsigned int dataTbl[2][13] = {
            {
                DATANUM(DATA_m535, 0x19), DATANUM(DATA_m535, 0x1A), DATANUM(DATA_m535, 0x1B),
                DATANUM(DATA_m535, 0x1C), DATANUM(DATA_m535, 0x1D), DATANUM(DATA_m535, 0x1E),
                DATANUM(DATA_m535, 0x1F), DATANUM(DATA_m535, 0x20), DATANUM(DATA_m535, 0x21),
                DATANUM(DATA_m535, 0x22), DATANUM(DATA_m535, 0x23), DATANUM(DATA_m535, 0x24),
                0,
            },
            {
                DATANUM(DATA_m535, 0x25), DATANUM(DATA_m535, 0x26), DATANUM(DATA_m535, 0x27),
                DATANUM(DATA_m535, 0x28), DATANUM(DATA_m535, 0x29), DATANUM(DATA_m535, 0x2A),
                DATANUM(DATA_m535, 0x2B), DATANUM(DATA_m535, 0x2C), DATANUM(DATA_m535, 0x2D),
                DATANUM(DATA_m535, 0x2E), DATANUM(DATA_m535, 0x2F), DATANUM(DATA_m535, 0x30),
                DATANUM(DATA_m535, 0x31),
            },
        };

        lbl_1_bss_8210[i] = HuDataSelHeapReadNum(dataTbl[0][i], HU_MEMNUM_OVL, HEAP_MODEL);
        lbl_1_bss_81DC[i] = espEntry(dataTbl[1][i], 0, 0);
        espDispOff(lbl_1_bss_81DC[i]);
    }
    lbl_1_bss_81D8 = espEntry(DATANUM(DATA_effect, 1), 0, 0);
    espDispOff(lbl_1_bss_81D8);
    fn_1_2F2C(0, 0);
    for (i = 0; i < 54; i++) {
        Hu3DAnimCreate(lbl_1_bss_8210[rand8() % 12], lbl_1_bss_8268->mdlId[i + 21], lbl_1_data_BF);
    }
    {
        int flag[4] = { 0, 0, 0, 0 };
        int no;

        for (i = 0; i < 4; i++) {
            unsigned int charMdl[13] = {
                DATANUM(DATA_m535, 0x09), DATANUM(DATA_m535, 0x0A), DATANUM(DATA_m535, 0x0B),
                DATANUM(DATA_m535, 0x0C), DATANUM(DATA_m535, 0x0D), DATANUM(DATA_m535, 0x0E),
                DATANUM(DATA_m535, 0x0F), DATANUM(DATA_m535, 0x10), DATANUM(DATA_m535, 0x11),
                DATANUM(DATA_m535, 0x12), DATANUM(DATA_m535, 0x13), DATANUM(DATA_m535, 0x14),
                DATANUM(DATA_m535, 0x15),
            };
            f32 posTbl[4][2] = {
                { -25.0f, -38.0f },
                { -10.0f, -27.0f },
                {  10.0f, -27.0f },
                {  25.0f, -38.0f },
            };

            work = lbl_1_bss_826C[i]->data;
            do {
                no = rand8() % 4;
            } while (flag[no] == 1);
            flag[no] = 1;
            mdl = i + 13;
            obj->mdlId[mdl] = Hu3DModelCreate(HuDataSelHeapReadNum(charMdl[work->charNo], HU_MEMNUM_OVL, HEAP_MODEL));
            Hu3DModelLayerSet(obj->mdlId[mdl], 3);
            work->unk028 = posTbl[i][0];
            work->unk02C = posTbl[i][1];
            Hu3DModelPosSet(obj->mdlId[mdl], work->unk028, 61.0f, work->unk02C);
            Hu3DModelCameraSet(obj->mdlId[mdl], 2);
            Hu3DModelAttrSet(obj->mdlId[mdl], HU3D_ATTR_DISPOFF);
            Hu3DModelShadowSet(obj->mdlId[mdl]);
            mdl = i + 17;
            obj->mdlId[mdl] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m535, 0x16), HU_MEMNUM_OVL, HEAP_MODEL));
            Hu3DModelLayerSet(obj->mdlId[mdl], 6);
            Hu3DModelAttrSet(obj->mdlId[mdl], HU3D_ATTR_DISPOFF);
            Hu3DModelCameraSet(obj->mdlId[mdl], 2);
        }
    }
    obj->mtnId[0] = Hu3DJointMotion(obj->mdlId[13], HuDataSelHeapReadNum(DATANUM(DATA_m535, 0x17), HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mtnId[1] = Hu3DJointMotion(obj->mdlId[13], HuDataSelHeapReadNum(DATANUM(DATA_m535, 0x18), HU_MEMNUM_OVL, HEAP_MODEL));
    for (i = 0; i < 4; i++) {
        Hu3DMotionSet(obj->mdlId[i + 13], obj->mtnId[1]);
    }
    for (i = 0; i < 12; i++) {
        lbl_1_bss_8284[i].unk10 = -1;
    }
    obj->objFunc = fn_1_39A8;
}

/* asm 12002..12268 -- player init */
static void fn_1_B31C(OMOBJ *obj)
{
    M535_PLAYER *work;
    int padList[4] = { 0, 1, 2, 3 };
    int n;
    int i;
    int j;
    int no;

    n = 0;
    work = obj->data;
    memset(work, 0, sizeof(M535_PLAYER));
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == GwPlayerConf[j].grp) {
                padList[n] = j;
                n++;
            }
        }
    }
    work->playerNo = obj->work[0];
    work->padIdx = padList[work->playerNo];
    if (work->padIdx == 4) {
        work->padIdx = work->playerNo;
    }
    work->charNo = GwPlayerConf[work->padIdx].charNo;
    work->unk008 = (work->charNo >= 9) ? 9 : work->charNo;
    work->unk010 = (GwPlayerConf[work->padIdx].type != 0) ? -1 : GwPlayerConf[work->padIdx].padNo;
    work->unk014 = (work->unk010 != -1) ? 0 : GwPlayerConf[work->padIdx].dif;
    work->unk020 = 2;
    work->unk050 = -1;
    work->unk33C = 0;
    work->unk03C = 0;
    for (i = 0; i < 30; i++) {
        work->unk2C4[i] = -1;
    }
    obj->mdlId[0] = CharModelCreate(work->charNo, 2);
    Hu3DModelLayerSet(obj->mdlId[0], 1);
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_LOOP);
    Hu3DModelCameraSet(obj->mdlId[0], 1);
    Hu3DModelShadowSet(obj->mdlId[0]);
    CharEffectLayerSet(6);
    Hu3DModelAmbSet(obj->mdlId[0], 1.1f, 1.1f, 1.1f);
    work->unk018 = 0;
    work->unk01C = -1;
    for (i = 0; i < 4; i++) {
        obj->mtnId[i] = CharMotionCreate(work->charNo, lbl_1_data_34[i]);
    }
    Hu3DMotionSet(obj->mdlId[0], obj->mtnId[work->unk018]);
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_LOOP);
    obj->trans.x = lbl_1_data_74[work->playerNo][0];
    obj->trans.y = lbl_1_data_74[work->playerNo][1];
    obj->trans.z = lbl_1_data_74[work->playerNo][2];
    obj->rot.y = lbl_1_data_74[work->playerNo][3];
    obj->rot.x = obj->rot.z = 0.0f;
    CharModelVoicePanSet(work->charNo, 64.0f + 32.0f * (obj->trans.x / 250.0f));
    obj->objFunc = fn_1_69C;
}

/* asm 12271..12293 */
static void fn_1_B700(OMOBJ *obj)
{
    lbl_1_bss_8260 = 1000;
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_PREVTYPE, 60);
    obj->objFunc = fn_1_53F8;
}

/* asm 12296..12716 */
void ObjectSetup(void)
{
    OMOBJ *obj;
    int i;
    int cam;
    int x;
    int y;
    int w;
    int h;

    OSReport("******* M535 ObjectSetup *********\n");
    lbl_1_bss_825C = omInitObjMan(600, 0x2000);
    omGameSysInit(lbl_1_bss_825C);
    Hu3DCameraCreate(3);
    for (i = 0; i < 2; i++) {
        cam = (i == 0) ? 1 : 2;
        w = 640;
        h = w * 3 / 4;
        x = (640 - w) / 2;
        y = (480 - h) / 2;
        Hu3DCameraPerspectiveSet(cam, 25.0f, 20.0f, 10000.0f, 1.2f);
        Hu3DCameraViewportSet(cam, x, y, w, h, 0.0f, 1.0f);
        Hu3DCameraScissorSet(cam, x, y, w, h);
        CZoomM[i] = 1100.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = 115.0f;
        CenterM[i].z = 0.0f;
        CRotM[i].x = -11.5f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
    }
    Hu3DLighInit();
    {
        HuVecF lightPos = { 0.0f, 5000.0f, 0.0f };
        HuVecF lightDir = { 0.0f, -1.0f, -0.5f };
        GXColor lightColor = { 255, 255, 255, 255 };

        lbl_1_bss_8250 = Hu3DGLightCreateV(&lightPos, &lightDir, &lightColor);
    }
    Hu3DGLightStaticSet(lbl_1_bss_8250, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_8250);
    {
        HuVecF pos;
        HuVecF up;
        HuVecF target;

        pos.x = 0.0f;
        pos.y = 12000.0f;
        pos.z = -500.0f;
        up.x = 0.0f;
        up.y = 0.0f;
        up.z = -1.0f;
        target.x = 0.0f;
        target.y = 60.0f;
        target.z = 0.0f;
        Hu3DShadowMultiCreate(3.0f, 200.0f, 20000.0f, 3);
        Hu3DShadowMultiPosSet(&pos, &up, &target, 1);
        pos.y = 4500.0f;
        pos.z = -500.0f;
        target.z = 0.0f;
        Hu3DShadowMultiPosSet(&pos, &up, &target, 2);
    }
    Hu3DShadowMultiTPLvlSet(0.3f, 1);
    Hu3DShadowMultiTPLvlSet(0.4f, 2);
    lbl_1_bss_825A = -1;
    lbl_1_data_5C = -1;
    lbl_1_bss_8268 = omAddObjEx(lbl_1_bss_825C, 101, 75, 2, 1, fn_1_A3C4);
    for (i = 0; i < 4; i++) {
        obj = lbl_1_bss_826C[i] = omAddObjEx(lbl_1_bss_825C, 100, 1, 4, 0, fn_1_B31C);
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M535_PLAYER), HU_MEMNUM_OVL);
        obj->work[0] = i;
    }
    lbl_1_bss_827C = omAddObjEx(lbl_1_bss_825C, 32730, 0, 0, -1, omOutViewMulti);
    lbl_1_bss_827C->work[0] = 2;
    lbl_1_bss_8280 = omAddObjEx(lbl_1_bss_825C, 102, 0, 0, -1, fn_1_B700);
    lbl_1_bss_8264 = omAddObjEx(lbl_1_bss_825C, 103, 1, 0, -1, fn_1_BDC8);
    lbl_1_bss_81D4 = GXGetTexBufferSize(64, 64, GX_TF_IA8, 0, 0);
    lbl_1_bss_81D0 = HuMemDirectMallocNum(HEAP_MODEL, lbl_1_bss_81D4, HU_MEMNUM_OVL);
    memset(lbl_1_bss_81D0, 0, lbl_1_bss_81D4);
}

/* asm 12719..12743 */
static void fn_1_BDC8(OMOBJ *obj)
{
    if (lbl_1_bss_C != 0) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
        obj->objFunc = fn_1_BE20;
    }
}

/* asm 12746..12797 */
static void fn_1_BE20(OMOBJ *obj)
{
    M535_PLAYER *work;
    int i;

    if (WipeCheckEnd()) {
        return;
    }
    for (i = 0; i < 4; i++) {
        work = lbl_1_bss_826C[i]->data;
        CharModelKill(work->charNo);
    }
    if (lbl_1_bss_825A >= 0) {
        GameMesKill(lbl_1_bss_825A);
    }
    GameMesClose();
    HuAudAllStop();
    omOvlReturnEx(lbl_1_data_64, 1);
}
