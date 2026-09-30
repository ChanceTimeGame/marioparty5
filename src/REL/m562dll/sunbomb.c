/*
 * m562dll sunbomb.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/m562dll/asm/REL/m562dll/sunbomb.s.
 */

#include "REL/m562dll.h"

#include "game/audio.h"
#include "game/frand.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/wipe.h"
#include "game/charman.h"
#include "game/mg/seqman.h"
#include "game/gamemes.h"
#include "game/printfunc.h"
#include "math.h"
#include "string.h"

#ifndef __MWERKS__
#include "game/hsfex.h"
#include "game/esprite.h"
#endif

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x8A0 lbl_1_rodata_8A0 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_8AC = 0.0f; /* 0x8AC */
static const float lbl_1_rodata_8B0 = 1.0f; /* 0x8B0 */
static const float lbl_1_rodata_8B4 = 8.96f; /* 0x8B4 */
/* 0x8B8 lbl_1_rodata_8B8 (0xC): 0x00000000 0x42480000 0x42C80000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_8C4 = 120.0f; /* 0x8C4 */
static const float lbl_1_rodata_8C8 = 30.0f; /* 0x8C8 */
static const float lbl_1_rodata_8CC = 2.0f; /* 0x8CC */
static const float lbl_1_rodata_8D0 = 1.5f; /* 0x8D0 */
static const float lbl_1_rodata_8D4 = 40.0f; /* 0x8D4 */
static const float lbl_1_rodata_8D8 = 0.4f; /* 0x8D8 */
static const double lbl_1_rodata_8E0 = 3.141592653589793; /* 0x8E0 */
static const float lbl_1_rodata_8E8 = 90.0f; /* 0x8E8 */
static const double lbl_1_rodata_8F0 = 180.0; /* 0x8F0 */
static const float lbl_1_rodata_8F8 = 250.0f; /* 0x8F8 */
static const float lbl_1_rodata_8FC = 0.6f; /* 0x8FC */
static const float lbl_1_rodata_900 = 0.5f; /* 0x900 */
static const float lbl_1_rodata_904 = 10.0f; /* 0x904 */
static const float lbl_1_rodata_908 = 0.3f; /* 0x908 */
static const float lbl_1_rodata_90C = 0.7f; /* 0x90C */
static const float lbl_1_rodata_910 = 60.0f; /* 0x910 */
static const float lbl_1_rodata_914 = 100.0f; /* 0x914 */
static const double lbl_1_rodata_918 = 300.0; /* 0x918 */
static const float lbl_1_rodata_920 = 180.0f; /* 0x920 */
static const double lbl_1_rodata_928 = 2.5; /* 0x928 */
static const float lbl_1_rodata_930 = 50.0f; /* 0x930 */
static const float lbl_1_rodata_934 = 150.0f; /* 0x934 */
static const float lbl_1_rodata_938 = 0.1f; /* 0x938 */
static const float lbl_1_rodata_93C = -360.0f; /* 0x93C */
static const float lbl_1_rodata_940 = 55.0f; /* 0x940 */
static const float lbl_1_rodata_944 = 1125.0f; /* 0x944 */
static const float lbl_1_rodata_948 = -1125.0f; /* 0x948 */
static const float lbl_1_rodata_94C = 600.0f; /* 0x94C */
static const float lbl_1_rodata_950 = 300.0f; /* 0x950 */
/* 0x958 lbl_1_rodata_958 = 4503601774854144: int->float conversion constant, compiler-generated */

/* --- functions (reference order), .data placed before its first user --- */
/* 191 insns */
void fn_1_1EE3C(M562_SUNBOMB *sunbomb, M562_KOOPABOSS *boss)
{
    HU3DMODELID mdl;
    s32 i;
    M562_SUNBOMBOBJ *bomb;

    memset(sunbomb, 0, sizeof(M562_SUNBOMB));
    sunbomb->unk000 = boss;
    sunbomb->unk25E = mdl = Hu3DModelCreate(HuDataSelHeapReadNum(0x75001B, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
    sunbomb->unk26C = Hu3DJointMotion(mdl, HuDataSelHeapReadNum(0x750050, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(mdl, sunbomb->unk26C);
    Hu3DModelAttrSet(mdl, HU3D_MOTATTR_LOOP);
    sunbomb->unk260 = mdl = Hu3DModelCreate(HuDataSelHeapReadNum(0x750023, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
    sunbomb->unk26E = Hu3DJointMotion(mdl, HuDataSelHeapReadNum(0x750058, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(mdl, sunbomb->unk26E);
    Hu3DModelAttrSet(mdl, HU3D_MOTATTR_LOOP);
    sunbomb->unk262 = mdl = Hu3DModelCreate(HuDataSelHeapReadNum(0x750024, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
    sunbomb->unk270 = Hu3DJointMotion(mdl, HuDataSelHeapReadNum(0x750059, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(mdl, sunbomb->unk270);
    Hu3DModelAttrReset(mdl, HU3D_MOTATTR_LOOP);
    sunbomb->unk264 = mdl = Hu3DModelCreate(HuDataSelHeapReadNum(0x750025, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
    sunbomb->unk272 = Hu3DJointMotion(mdl, HuDataSelHeapReadNum(0x75005A, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(mdl, sunbomb->unk272);
    Hu3DModelAttrSet(mdl, HU3D_MOTATTR_LOOP);
    sunbomb->unk266 = mdl = Hu3DModelCreate(HuDataSelHeapReadNum(0x750026, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
    sunbomb->unk274 = Hu3DJointMotion(mdl, HuDataSelHeapReadNum(0x75005B, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(mdl, sunbomb->unk274);
    Hu3DModelAttrSet(mdl, HU3D_MOTATTR_LOOP);
    sunbomb->unk268 = mdl = Hu3DModelCreate(HuDataSelHeapReadNum(0x750015, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
    sunbomb->unk26A = mdl = Hu3DModelCreate(HuDataSelHeapReadNum(0x750016, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
    for (i = 0; i < 5; i++) {
        bomb = &sunbomb->unk004[i];
        fn_1_1F324(bomb, sunbomb);
    }
}

/* 52 insns */
void fn_1_1F138(M562_SUNBOMB *sunbomb)
{
    s32 i;
    M562_SUNBOMBOBJ *bomb;

    Hu3DModelKill(sunbomb->unk26A);
    Hu3DModelKill(sunbomb->unk268);
    Hu3DMotionKill(sunbomb->unk274);
    Hu3DModelKill(sunbomb->unk266);
    Hu3DMotionKill(sunbomb->unk272);
    Hu3DModelKill(sunbomb->unk264);
    Hu3DMotionKill(sunbomb->unk270);
    Hu3DModelKill(sunbomb->unk262);
    Hu3DMotionKill(sunbomb->unk26E);
    Hu3DModelKill(sunbomb->unk260);
    Hu3DMotionKill(sunbomb->unk26C);
    Hu3DModelKill(sunbomb->unk25E);
    for (i = 0; i < 5; i++) {
        bomb = &sunbomb->unk004[i];
        fn_1_1F818(bomb);
    }
    memset(sunbomb, 0, sizeof(M562_SUNBOMB));
}

/* 36 insns */
void fn_1_1F208(M562_SUNBOMB *sunbomb)
{
    M562_KOOPABOSS *boss = sunbomb->unk000;
    HuVecF up = { 0.0f, 1.0f, 0.0f };
    s32 i;
    M562_SUNBOMBOBJ *bomb;

    for (i = 0; i < 5; i++) {
        bomb = &sunbomb->unk004[i];
        fn_1_1F870(bomb);
    }
    sunbomb->unk294 = 0;
}

/* 35 insns */
M562_SUNBOMBOBJ *fn_1_1F298(M562_SUNBOMB *sunbomb, HuVecF *pos)
{
    M562_SUNBOMBOBJ *result = NULL;
    s32 i;
    M562_SUNBOMBOBJ *bomb;

    for (i = 0; i < 5; i++) {
        bomb = &sunbomb->unk004[i];
        if (bomb->unk10 == 0) {
            bomb->unk5C = *pos;
            bomb->unk10 = 1;
            sunbomb->unk25C++;
            result = bomb;
            break;
        }
    }
    return result;
}

/* 317 insns */
void fn_1_1F324(M562_SUNBOMBOBJ *bomb, M562_SUNBOMB *owner)
{
    M562_SUNBOMB *sunbomb = owner;
    M562_KOOPABOSS *boss = sunbomb->unk000;
    M562_WORK *work = boss->unk000;
    M562_CAMERA *camera = &work->camera[0];
    HU3DMODELID mdl;

    memset(bomb, 0, sizeof(M562_SUNBOMBOBJ));
    bomb->unk00 = owner;
    bomb->unk24 = mdl = Hu3DModelLink(sunbomb->unk25E);
    Hu3DModelRotSet(mdl, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(mdl, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(mdl, camera->unk04);
    Hu3DModelLayerSet(mdl, 4);
    Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
    Hu3DMotionSet(mdl, sunbomb->unk26C);
    Hu3DModelAttrSet(mdl, HU3D_MOTATTR_LOOP);
    bomb->unk26 = mdl = Hu3DModelLink(sunbomb->unk260);
    Hu3DModelRotSet(mdl, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(mdl, 1.0f, 1.0f, 1.0f);
    Hu3DModelCameraSet(mdl, camera->unk04);
    Hu3DModelLayerSet(mdl, 4);
    Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
    Hu3DMotionSet(mdl, sunbomb->unk26E);
    Hu3DModelAttrReset(mdl, HU3D_MOTATTR_LOOP);
    bomb->unk28 = mdl = Hu3DModelLink(sunbomb->unk262);
    Hu3DModelRotSet(mdl, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(mdl, 1.0f, 1.0f, 1.0f);
    Hu3DModelCameraSet(mdl, camera->unk04);
    Hu3DModelLayerSet(mdl, 4);
    Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
    Hu3DMotionSet(mdl, sunbomb->unk270);
    Hu3DModelAttrReset(mdl, HU3D_MOTATTR_LOOP);
    bomb->unk2A = mdl = Hu3DModelLink(sunbomb->unk264);
    Hu3DModelRotSet(mdl, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(mdl, 1.0f, 1.0f, 1.0f);
    Hu3DModelCameraSet(mdl, camera->unk04);
    Hu3DModelLayerSet(mdl, 4);
    Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
    Hu3DMotionSet(mdl, sunbomb->unk272);
    Hu3DModelAttrSet(mdl, HU3D_MOTATTR_LOOP);
    bomb->unk2C = mdl = Hu3DModelLink(sunbomb->unk266);
    Hu3DModelRotSet(mdl, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(mdl, 1.0f, 1.0f, 1.0f);
    Hu3DModelCameraSet(mdl, camera->unk04);
    Hu3DModelLayerSet(mdl, 5);
    Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
    Hu3DMotionSet(mdl, sunbomb->unk274);
    Hu3DMotionSpeedSet(mdl, 8.96f);
    Hu3DModelAttrSet(mdl, HU3D_MOTATTR_LOOP);
    bomb->unk2E = mdl = Hu3DModelLink(sunbomb->unk268);
    Hu3DModelRotSet(mdl, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(mdl, 1.0f, 1.0f, 1.0f);
    Hu3DModelCameraSet(mdl, camera->unk04);
    Hu3DModelLayerSet(mdl, 0);
    Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
    bomb->unk30 = mdl = Hu3DModelLink(sunbomb->unk26A);
    Hu3DModelRotSet(mdl, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(mdl, 1.0f, 1.0f, 1.0f);
    Hu3DModelCameraSet(mdl, camera->unk04);
    Hu3DModelLayerSet(mdl, 0);
    Hu3DModelLayerSet(mdl, 0);
    Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
}

/* 22 insns */
/* retail @0x1F818: kills only the first four model links (unk24..unk2A); unk2C/unk2E/unk30 are left to the
   overlay-exit Hu3D cleanup */
void fn_1_1F818(M562_SUNBOMBOBJ *bomb)
{
    Hu3DModelKill(bomb->unk2A);
    Hu3DModelKill(bomb->unk28);
    Hu3DModelKill(bomb->unk26);
    Hu3DModelKill(bomb->unk24);
    memset(bomb, 0, sizeof(M562_SUNBOMBOBJ));
}

/* 1308 insns */
#define SB_CLAMP(x, lo, hi) (((x) > (hi)) ? (hi) : (((x) < (lo)) ? (lo) : (x)))
#define SB_ABS(x) (((x) >= 0.0f) ? (x) : -(x))

void fn_1_1F870(M562_SUNBOMBOBJ *bomb)
{
    float scale;
    float t;
    float s;
    float mag;
    float yOfs;
    float floorY;
    HuVecF dir;
    HuVecF pos;
    s32 pushed;
    M562_SUNBOMB *sunbomb = bomb->unk00;
    M562_KOOPABOSS *boss = sunbomb->unk000;
    M562_WORK *work = boss->unk000;
    M562_PLAYER *player = &work->player;
    M562_CAMERA *camera = &work->camera[0];
    MtxPtr mtx;
    HuVecF ofs;
    HuVecF ofsInit = { 0.0f, 50.0f, 100.0f };
    HuVecF *ofsP = &ofsInit;

    ofs = *ofsP;
    if (bomb->unk10 == 0 && bomb->unk04 > 1) {
        Hu3DModelAttrSet(bomb->unk24, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(bomb->unk26, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(bomb->unk28, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(bomb->unk2A, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(bomb->unk2C, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(bomb->unk2E, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(bomb->unk30, HU3D_ATTR_DISPOFF);
        bomb->unk04 = 0;
    }
    yOfs = 0.0f;
    switch (bomb->unk04) {
        case 0:
            bomb->unk0C = 0;
            Hu3DModelAttrSet(bomb->unk24, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(bomb->unk26, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(bomb->unk28, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(bomb->unk2A, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(bomb->unk2C, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(bomb->unk2E, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(bomb->unk30, HU3D_ATTR_DISPOFF);
            bomb->unk18 = 0;
            bomb->unk1C = 120.0f;
            bomb->unk20 = 0;
            bomb->unk04 = 1;
        case 1:
            if (bomb->unk10 == 0) {
                break;
            }
            bomb->unk34 = 0.0f;
            Hu3DModelScaleSet(bomb->unk24, 0.0f, 0.0f, 0.0f);
            Hu3DModelAttrReset(bomb->unk24, HU3D_ATTR_DISPOFF);
            Hu3DModelScaleSet(bomb->unk2E, 0.0f, 0.0f, 0.0f);
            Hu3DModelAttrReset(bomb->unk2E, HU3D_ATTR_DISPOFF);
            mtx = fn_1_1010C(boss);
            Hu3DMtxTransGet(mtx, &pos);
            VECAdd(&pos, &ofs, &bomb->unk38);
            bomb->unk18 = 0;
            bomb->unk08 = 0;
            bomb->unk04 = 2;
            break;
        case 2:
            mtx = fn_1_1010C(boss);
            Hu3DMtxTransGet(mtx, &pos);
            VECAdd(&pos, &ofs, &bomb->unk38);
            t = bomb->unk08 / 30.0f;
            t = SB_CLAMP(t, 0.0f, 1.0f);
            scale = 2.0f * t;
            bomb->unk34 = scale;
            Hu3DModelScaleSet(bomb->unk24, scale, scale, scale);
            scale *= 1.5f;
            Hu3DModelScaleSet(bomb->unk2E, scale, scale, scale);
            bomb->unk08++;
            if (bomb->unk18 != 0) {
                bomb->unk18 = 0;
                bomb->unk50 = bomb->unk38;
                bomb->unk08 = 0;
                bomb->unk04 = 3;
            }
            break;
        case 3:
            t = bomb->unk08 / 40.0f;
            if (t < 0.4f) {
                s = t / 0.4f;
                s = HuSin(90.0f * s);
                bomb->unk38.y = bomb->unk50.y + 250.0f * s;
            } else {
                s = (t - 0.4f) / 0.6f;
                s = HuSin(90.0f + 90.0f * s);
                bomb->unk38.y = bomb->unk5C.y + s * (250.0f + (bomb->unk50.y - bomb->unk5C.y));
            }
            bomb->unk38.x = bomb->unk50.x + t * (bomb->unk5C.x - bomb->unk50.x);
            bomb->unk38.z = bomb->unk50.z + t * (bomb->unk5C.z - bomb->unk50.z);
            if (++bomb->unk08 >= 40) {
                bomb->unk38 = bomb->unk5C;
                bomb->unk38.y = 0.0f;
                Hu3DMotionTimeSet(bomb->unk26, 0.0f);
                Hu3DMotionSpeedSet(bomb->unk26, 0.5f);
                Hu3DModelAttrReset(bomb->unk26, HU3D_ATTR_DISPOFF);
                bomb->unk08 = 0;
                bomb->unk04 = 4;
                fn_1_934(0x8AB, &bomb->unk38);
                scale = 1.0f;
                Hu3DModelScaleSet(bomb->unk2E, scale, scale, scale);
                fn_1_21B68(camera, 1, 50, 40.0f, 0.6f, 90.0f);
                omVibrate(player->unk014, 10, 12, 0);
            }
            break;
        case 4:
            Hu3DMotionTimeSet(bomb->unk28, 0.0f);
            if (bomb->unk08 < 10) {
                t = bomb->unk08 / 10.0f;
                t = 1.0f - SB_CLAMP(t, 0.0f, 1.0f);
                t = 0.3f + 0.7f * t;
                scale = 2.0f * t;
                bomb->unk34 = scale;
                Hu3DModelScaleSet(bomb->unk24, scale, scale, scale);
            } else if (bomb->unk08 == 10) {
                Hu3DModelAttrSet(bomb->unk24, HU3D_ATTR_DISPOFF);
            }
            t = bomb->unk08 / 60.0f;
            bomb->unk1C = 100.0f + 100.0f * t;
            bomb->unk08++;
            if (bomb->unk08 == 10) {
                scale = 1.0f;
                Hu3DModelScaleSet(bomb->unk28, scale, scale, scale);
                Hu3DMotionTimeSet(bomb->unk28, 0.0f);
                Hu3DModelAttrReset(bomb->unk28, HU3D_ATTR_DISPOFF);
            } else if (bomb->unk08 > 10 && bomb->unk08 < 40) {
                t = (bomb->unk08 - 10) / 30.0f;
                t = SB_CLAMP(t, 0.0f, 1.0f);
                yOfs = 300.0 * HuSin(180.0f * t);
            } else if (bomb->unk08 >= 60) {
                bomb->unk0C = 1;
                Hu3DModelAttrSet(bomb->unk24, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(bomb->unk26, HU3D_ATTR_DISPOFF);
                bomb->unk08 = 0;
                bomb->unk04 = 5;
                bomb->unk1C = 40.0f;
            }
            break;
        case 5:
            break;
        case 6:
            if (bomb->unk08 == 0) {
                fn_1_934(0x8AE, &bomb->unk38);
            }
            bomb->unk0C = 2;
            t = bomb->unk08 / 40.0f;
            scale = 2.5 * HuSin(180.0f * t);
            Hu3DModelScaleSet(bomb->unk2C, scale, scale, scale);
            Hu3DModelAttrReset(bomb->unk2C, HU3D_ATTR_DISPOFF);
            if (bomb->unk08 == 20) {
                Hu3DModelAttrSet(bomb->unk28, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(bomb->unk2A, HU3D_ATTR_DISPOFF);
                scale = 1.5f;
                Hu3DModelScaleSet(bomb->unk2A, scale, scale, scale);
                scale = 2.0f;
                Hu3DModelScaleSet(bomb->unk30, scale, scale, scale);
                Hu3DModelAttrReset(bomb->unk30, HU3D_ATTR_DISPOFF);
            }
            if (++bomb->unk08 >= 40) {
                Hu3DModelAttrSet(bomb->unk2E, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(bomb->unk2C, HU3D_ATTR_DISPOFF);
                bomb->unk08 = 0;
                bomb->unk04 = 7;
            }
            break;
        case 7:
            t = (bomb->unk38.y - 50.0f) / 150.0f;
            t = SB_CLAMP(t, 0.0f, 1.0f);
            scale = 2.0f + 2.0f * t;
            Hu3DModelScaleSet(bomb->unk30, scale, scale, scale);
            break;
        case 8:
            t = bomb->unk08 / 10.0f;
            t = 1.0f - SB_CLAMP(t, 0.0f, 1.0f);
            scale = bomb->unk34 * t;
            Hu3DModelScaleSet(bomb->unk24, scale, scale, scale);
            scale *= 1.5f;
            Hu3DModelScaleSet(bomb->unk2E, scale, scale, scale);
            if (++bomb->unk08 >= 10) {
                Hu3DModelAttrSet(bomb->unk24, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(bomb->unk26, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(bomb->unk28, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(bomb->unk2E, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(bomb->unk2A, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(bomb->unk30, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(bomb->unk2C, HU3D_ATTR_DISPOFF);
                bomb->unk08 = 0;
                bomb->unk04 = 10;
            }
            break;
        case 9:
            if (bomb->unk0C == 0 || bomb->unk0C == 1) {
                if (bomb->unk08 & 1) {
                    Hu3DModelAttrSet(bomb->unk28, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(bomb->unk2E, HU3D_ATTR_DISPOFF);
                } else {
                    Hu3DModelAttrReset(bomb->unk28, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(bomb->unk2E, HU3D_ATTR_DISPOFF);
                }
            } else if (bomb->unk0C == 2) {
                if (bomb->unk08 & 1) {
                    Hu3DModelAttrSet(bomb->unk2A, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(bomb->unk30, HU3D_ATTR_DISPOFF);
                } else {
                    Hu3DModelAttrReset(bomb->unk2A, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(bomb->unk30, HU3D_ATTR_DISPOFF);
                }
            }
            if (++bomb->unk08 >= 60) {
                Hu3DModelAttrSet(bomb->unk24, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(bomb->unk26, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(bomb->unk28, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(bomb->unk2E, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(bomb->unk2A, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(bomb->unk30, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(bomb->unk2C, HU3D_ATTR_DISPOFF);
                bomb->unk08 = 0;
                bomb->unk04 = 10;
            }
            break;
        case 10:
            bomb->unk08 = 0;
            bomb->unk10 = 0;
            sunbomb->unk25C--;
            break;
    }
    pushed = 0;
    if (sunbomb->unk294 != 0 && bomb != player->unk134) {
        VECSubtract(&bomb->unk38, &sunbomb->unk298, &dir);
        dir.y = 0.0f;
        mag = VECMag(&dir);
        if (mag < sunbomb->unk2A4 && mag > sunbomb->unk2A4 - 100.0f) {
            if (dir.x || dir.z) {
                VECNormalize(&dir, &dir);
            } else {
                dir.z = 1.0f;
            }
            VECScale(&dir, &dir, sunbomb->unk2A4 - mag);
            VECAdd(&bomb->unk38, &dir, &pos);
            if (pos.z < sunbomb->unk298.z) {
                pos.z += 0.1f * (sunbomb->unk298.z - pos.z);
            }
            bomb->unk38 = pos;
            bomb->unk20 = 1;
            pushed = 1;
        }
    }
    if (bomb != player->unk134) {
        if (bomb->unk04 >= 5) {
            floorY = (bomb->unk38.z < -360.0f) ? 55.0f : 0.0f;
            if (bomb->unk38.y > floorY) {
                bomb->unk68 -= 1.5f;
                bomb->unk38.x += bomb->unk6C;
                bomb->unk38.z += bomb->unk74;
                bomb->unk38.y += bomb->unk68;
                if (bomb->unk38.y <= 0.0f) {
                    bomb->unk6C = bomb->unk74 = 0.0f;
                    bomb->unk38.y = floorY;
                    bomb->unk68 = 0.0f;
                }
            }
        }
        if (bomb->unk04 >= 4 && !pushed) {
            bomb->unk38.x = SB_CLAMP(bomb->unk38.x, -1125.0f, 1125.0f);
            /* retail @0x209AC: the lower bound is z itself, so only the 600 upper bound applies */
            bomb->unk38.z = SB_CLAMP(bomb->unk38.z, bomb->unk38.z, 600.0f);
            if (bomb->unk38.z < -360.0f && bomb->unk38.y < 55.0f) {
                if (SB_ABS(55.0f - bomb->unk38.y) < SB_ABS(-360.0f - bomb->unk38.z)) {
                    bomb->unk38.y = 55.0f;
                    if (bomb->unk04 <= 7) {
                        bomb->unk08 = 0;
                        bomb->unk04 = 9;
                    }
                } else {
                    bomb->unk38.z = -360.0f;
                }
            }
        }
    }
    VECAdd(&bomb->unk38, &bomb->unk44, &pos);
    Hu3DModelPosSet(bomb->unk24, pos.x, pos.y, pos.z);
    Hu3DModelPosSet(bomb->unk26, pos.x, pos.y, pos.z);
    Hu3DModelPosSet(bomb->unk28, pos.x, pos.y + yOfs, pos.z);
    Hu3DModelPosSet(bomb->unk2A, pos.x, pos.y, pos.z);
    Hu3DModelPosSet(bomb->unk2C, pos.x, pos.y, pos.z);
    Hu3DModelPosSet(bomb->unk2E, pos.x, 0.0f, pos.z);
    Hu3DModelPosSet(bomb->unk30, pos.x, 0.0f, pos.z);
    if (bomb->unk10 != 0 && bomb != player->unk134 && bomb->unk04 >= 3 && bomb->unk04 < 9) {
        fn_1_2CE8C(&work->unk286C[2], 5, 0, &bomb->unk38, 300.0f, bomb);
    }
}

