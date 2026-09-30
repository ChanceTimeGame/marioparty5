#ifndef M533DLL_H
#define M533DLL_H

/*
 * m533dll (MG_TYPE_2VS2, overlay #47): types and prototypes shared by m533.c
 * and pillar.c.
 *
 * Both units open with the same 16-function helper block as m563dll (list,
 * model cache, camera lerp, angle, seq fade, obj mtx, rand range, circle hit,
 * 3D->2D). Its instruction streams are identical to m563's util.o copy, so
 * both units #include "REL/m563dll/math.c" first, exactly as m563's units do.
 * Helper address map (m533.c / pillar.c -> math.c name):
 *   5580/7390 66D4  55A4/73B4 66F8  562C/743C 6780  56D0/74E0 6824
 *   5728/7538 687C  583C/764C 6990  5998/77A8 6AEC  5A24/7834 6B78
 *   5D58/7B68 6EAC  613C/7F4C 7290  6240/8050 7394  62AC/80BC 7400
 *   6304/8114 7458  6340/8150 7494  63A0/81B0 74F4  6464/8274 75B8
 *
 * Offsets are GameCube ones from build/mp5-asm/m533dll.
 */

#include "dolphin/types.h"
#include "game/object.h"
#include "game/hu3d.h"
#include "humath.h"

/* 0x9C bytes per player object (group 0, fn_1_6A8). */
typedef struct M533Player_s {
    /* 0x00 */ u32 flags;             /* 1 front (rows), 2 back (pumps), 4/8 swap, 0x10, 0x20 swap request */
    /* 0x04 */ s32 motNo;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 playerNo;
    /* 0x10 */ s32 partnerNo;
    /* 0x14 */ s32 charNo;
    /* 0x18 */ s32 padNo;
    /* 0x1C */ s32 grp;
    /* 0x20 */ s32 cameraNo;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 stopTime;
    /* 0x2C */ HuVecF pos;
    /* 0x38 */ HuVecF rot;
    /* 0x44 */ HuVecF unk44;
    /* 0x50 */ u16 btn;
    /* 0x52 */ u16 pad52;
    /* 0x54 */ s32 btnTime;
    /* 0x58 */ s32 pressFrame;
    /* 0x5C */ s32 pressInterval;
    /* 0x60 */ float speed;
    /* 0x64 */ s32 timer;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ float angle;
    /* 0x70 */ float angleSpeed;
    /* 0x74 */ s32 pressNum;
    /* 0x78 */ s32 dif;
    /* 0x7C */ s32 difNo;             /* dif for a CPU, 4 for a human */
    /* 0x80 */ s32 comWaitMax;
    /* 0x84 */ s32 comWaitNext;
    /* 0x88 */ s32 comWait;
    /* 0x8C */ float stamina;
    /* 0x90 */ float comRestMax;
    /* 0x94 */ float comRestMin;
    /* 0x98 */ float comRest;
} M533_PLAYER;

/* 0x10 bytes (group 1, fn_1_165C). */
typedef struct M533Work2_s {
    /* 0x00 */ s32 no;
    /* 0x04 */ HuVecF pos;
} M533_WORK2;

/* 0x48 bytes (group 2, fn_1_1F98): one boat per team. */
typedef struct M533Work3_s {
    /* 0x00 */ s32 goalF;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 team;
    /* 0x0C */ HuVecF pos;
    /* 0x18 */ HuVecF rot;
    /* 0x24 */ float speed;
    /* 0x28 */ float unk28;
    /* 0x2C */ float unk2C;
    /* 0x30 */ float dist;
    /* 0x34 */ float unk34;
    /* 0x38 */ float bobAngle;
    /* 0x3C */ s32 work4F;
    /* 0x40 */ s32 work5F;
    /* 0x44 */ s32 pauseF;
} M533_WORK3;

/* 0x18 bytes (group 4, fn_1_4A44): the four fish that jump beside the boats. */
typedef struct M533Work4_s {
    /* 0x00 */ float posY;
    /* 0x04 */ float angle;
    /* 0x08 */ float amp;
    /* 0x0C */ s16 timer;
    /* 0x0E */ s16 timerMax;
    /* 0x10 */ s32 activeF;
    /* 0x14 */ s32 no;
} M533_WORK4;

/* 0x14 bytes (group 5, fn_1_4F84): the 24 scenery objects. */
typedef struct M533Work5_s {
    /* 0x00 */ s32 activeF;
    /* 0x04 */ s32 no;
    /* 0x08 */ float speed;
    /* 0x0C */ s32 cameraNo;
    /* 0x10 */ float dist;
} M533_WORK5;

/* 0x14 bytes: one row of lbl_1_data_108 / lbl_1_data_2E8. */
typedef struct M533Spawn_s {
    /* 0x00 */ HuVecF pos;
    /* 0x0C */ s32 type;
    /* 0x10 */ float speed;
} M533_SPAWN;

/* m533.c */
void ObjectSetup(void);
void fn_1_6A8(OMOBJ *obj);
void fn_1_A80(OMOBJ *obj);
void fn_1_165C(OMOBJ *obj);
void fn_1_1840(OMOBJ *obj);
void fn_1_1A5C(OMOBJ *obj, s32 motNo);
void fn_1_1AE8(OMOBJ *obj, s32 motNo, float shift, u32 attr);
void fn_1_1BA0(OMOBJ *obj);
u16 fn_1_1CD0(OMOBJ *obj);
void fn_1_1DAC(OMOBJ *obj);
void fn_1_1E3C(OMOBJ *obj);
void fn_1_1F98(OMOBJ *obj);
s32 fn_1_2698(s32 grp);
void fn_1_2724(OMOBJ *obj);
void fn_1_2D4C(s16 mode, s16 frameNo);
void fn_1_3424(s16 mode, s16 frameNo);
void fn_1_3890(s16 mode, s16 frameNo);
void fn_1_3950(s16 mode, s16 frameNo);
void fn_1_3D50(s16 mode, s16 frameNo);
void fn_1_4080(s16 mode, s16 frameNo);
void fn_1_44D4(void);
void fn_1_44D8(void);
float fn_1_45B8(s32 rank);
void fn_1_46A4(float x);
void fn_1_48B8(void);
void fn_1_48BC(s32 show);
void fn_1_4A44(OMOBJ *obj);
void fn_1_4CC8(OMOBJ *obj);
void fn_1_4F84(OMOBJ *obj);
void fn_1_5154(OMOBJ *obj);
void fn_1_52C4(void);
void fn_1_5544(void);

/* pillar.c */
void fn_1_6528(void);
void fn_1_6590(OMOBJ *obj);
void fn_1_6770(OMOBJ *obj, s32 cameraBit);
void fn_1_6984(OMOBJ *obj, HuVecF *pos, s32 type, float unused, u16 cameraBit);
void fn_1_6B18(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx);
void fn_1_6F54(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx);

#endif
