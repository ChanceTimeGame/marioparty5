/*
 * m562dll stage.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/m562dll/asm/REL/m562dll/stage.s.
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
static const float lbl_1_rodata_190 = 0.0f; /* 0x190 */
static const float lbl_1_rodata_194 = 0.4f; /* 0x194 */
static const float lbl_1_rodata_198 = 120.0f; /* 0x198 */
static const float lbl_1_rodata_19C = 2000.0f; /* 0x19C */
static const float lbl_1_rodata_1A0 = 400.0f; /* 0x1A0 */
static const float lbl_1_rodata_1A4 = 1.0f; /* 0x1A4 */
static const double lbl_1_rodata_1A8 = 60.0; /* 0x1A8 */
static const double lbl_1_rodata_1B0 = 3.141592653589793; /* 0x1B0 */
static const float lbl_1_rodata_1B8 = 180.0f; /* 0x1B8 */
static const double lbl_1_rodata_1C0 = 180.0; /* 0x1C0 */
/* 0x1C8 lbl_1_rodata_1C8 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_1D0 = -500.0f; /* 0x1D0 */
static const float lbl_1_rodata_1D4 = 250.0f; /* 0x1D4 */
static const float lbl_1_rodata_1D8 = -375.0f; /* 0x1D8 */
static const float lbl_1_rodata_1DC = 10000.0f; /* 0x1DC */
static const float lbl_1_rodata_1E0 = 3.0f; /* 0x1E0 */
static const float lbl_1_rodata_1E4 = 1.5f; /* 0x1E4 */
static const float lbl_1_rodata_1E8 = -1000.0f; /* 0x1E8 */
static const float lbl_1_rodata_1EC = -5000.0f; /* 0x1EC */
static const float lbl_1_rodata_1F0 = 200.0f; /* 0x1F0 */
static const float lbl_1_rodata_1F4 = 0.5f; /* 0x1F4 */
static const float lbl_1_rodata_1F8 = 50.0f; /* 0x1F8 */
static const float lbl_1_rodata_1FC = 20000.0f; /* 0x1FC */
static const float lbl_1_rodata_200 = 0.1f; /* 0x200 */
static const float lbl_1_rodata_204 = 0.9f; /* 0x204 */
static const float lbl_1_rodata_208 = 100.0f; /* 0x208 */
static const float lbl_1_rodata_20C = 0.2f; /* 0x20C */
static const float lbl_1_rodata_210 = 1000.0f; /* 0x210 */
/* 0x218 lbl_1_rodata_218 = 4503599627370496: int->float conversion constant, compiler-generated */

/* --- functions (reference order), .data placed before its first user --- */

#define M562_DATA(n) HuDataSelHeapReadNum(DATANUM(DATA_m562, n), HU_MEMNUM_OVL, HEAP_MODEL)

/* 343 insns. Stage init: the tile master models, the arena pieces, the two tile-break effect
   models and the 4x5 floor tiles. */
void fn_1_5688(M562_STAGE *stage, M562_WORK *work)
{
    HU3DMODELID modelId;
    s16 k;
    s16 j;
    s16 n;
    M562_WORK *w;
    M562_STAGETILE *tile;
    M562_CAMERA *camera;

    w = work;
    camera = &w->camera[0];
    memset(stage, 0, sizeof(M562_STAGE));
    stage->unk000 = work;
    stage->unk5D8 = -1;
    stage->unk5A8 = modelId = Hu3DModelCreate(M562_DATA(0x00));
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    stage->unk5AA = modelId = Hu3DModelCreate(M562_DATA(0x01));
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    stage->unk5AC = modelId = Hu3DModelCreate(M562_DATA(0x02));
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    stage->unk5AE = modelId = Hu3DModelCreate(M562_DATA(0x05));
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelShadowMapSet(modelId);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    stage->unk5B0 = modelId = Hu3DModelCreate(M562_DATA(0x06));
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelShadowMapSet(modelId);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    stage->unk5B2 = Hu3DJointMotion(modelId, M562_DATA(0x2A));
    Hu3DMotionSet(modelId, stage->unk5B2);
    Hu3DMotionSpeedSet(modelId, 0.0f);
    Hu3DModelAttrReset(modelId, HU3D_MOTATTR_LOOP);
    stage->unk5B4 = modelId = Hu3DModelCreate(M562_DATA(0x07));
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelShadowMapSet(modelId);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    stage->unk5B6 = modelId = Hu3DModelCreate(M562_DATA(0x03));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    Hu3DMotionSpeedSet(modelId, 0.4f);
    stage->unk5B8 = Hu3DJointMotion(modelId, M562_DATA(0x28));
    Hu3DMotionSet(modelId, stage->unk5B8);
    Hu3DModelAttrReset(modelId, HU3D_MOTATTR_LOOP);
    stage->unk5BC = 0;
    stage->unk5C0 = modelId = Hu3DModelCreate(M562_DATA(0x04));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    stage->unk5C2 = Hu3DJointMotion(modelId, M562_DATA(0x29));
    Hu3DMotionSet(modelId, stage->unk5C2);
    Hu3DModelAttrReset(modelId, HU3D_MOTATTR_LOOP);
    n = 0;
    for (j = 0; j < 4; j++) {
        for (k = 0; k < 5; k++) {
            tile = &stage->unk008[n];
            fn_1_60F8(tile, k, j, stage);
            n++;
        }
    }
}

/* 50 insns. Stage kill. */
void fn_1_5BE4(M562_STAGE *stage)
{
    s32 i;
    M562_STAGETILE *tile;

    for (i = 0; i < 20; i++) {
        tile = &stage->unk008[i];
        fn_1_62A8(tile);
    }
    Hu3DMotionKill(stage->unk5C2);
    Hu3DModelKill(stage->unk5C0);
    Hu3DMotionKill(stage->unk5B8);
    Hu3DModelKill(stage->unk5B6);
    Hu3DModelKill(stage->unk5B4);
    Hu3DMotionKill(stage->unk5B2);
    Hu3DModelKill(stage->unk5B0);
    Hu3DModelKill(stage->unk5AE);
    Hu3DModelKill(stage->unk5AC);
    Hu3DModelKill(stage->unk5AA);
    Hu3DModelKill(stage->unk5A8);
    memset(stage, 0, sizeof(M562_STAGE));
}

/* 275 insns. Stage frame. Phase 3: run the tiles and the floor quake (a ring expanding from
   unk5CC over 120 frames, SE 0x8A8 for its first 80). Phase 4 (the final fight on Bowser's
   hand): tiles hidden, the arena swapped. Then hide the break effects when their motion ends. */
void fn_1_5CAC(M562_STAGE *stage)
{
    HuVecF d;
    float t;
    float inner;
    float rate;
    float dist;
    float outer;
    float y;
    s32 i;
    M562_STAGETILE *tile;
    M562_WORK *work;

    work = stage->unk000;
    switch (stage->unk004) {
        case 0:
            if (work->unk000E != 4) {
                if (work->unk000E == 3) {
                    for (i = 0; i < 20; i++) {
                        tile = &stage->unk008[i];
                        fn_1_62E8(tile);
                        if (stage->unk5C8 != 0) {
                            rate = stage->unk5C8 / 120.0f;
                            PSVECSubtract(&tile->unk10, &stage->unk5CC, &d);
                            d.y = 0.0f;
                            dist = PSVECMag(&d);
                            inner = 2000.0f * rate;
                            outer = 400.0f + inner;
                            t = (dist - inner) / (outer - inner);
                            t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
                            y = (1.0f - rate) * (60.0 * sin(3.141592653589793 * (180.0f * t) / 180.0));
                            tile->unk10.y = y;
                        }
                    }
                    if (stage->unk5C8 != 0) {
                        if (stage->unk5C8 < 80) {
                            if (stage->unk5D8 < 0) {
                                stage->unk5D8 = fn_1_814(0x8A8);
                            }
                        } else if (stage->unk5D8 >= 0) {
                            fn_1_83C(stage->unk5D8);
                            stage->unk5D8 = -1;
                        }
                        if (++stage->unk5C8 >= 120) {
                            stage->unk5C8 = 0;
                        }
                    }
                }
            } else {
                for (i = 0; i < 20; i++) {
                    tile = &stage->unk008[i];
                    Hu3DModelAttrSet(tile->unk08, HU3D_ATTR_DISPOFF);
                }
                Hu3DModelAttrReset(stage->unk5AE, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(stage->unk5B0, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(stage->unk5B4, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(stage->unk5B6, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(stage->unk5C0, HU3D_ATTR_DISPOFF);
                stage->unk004 = 1;
            }
            break;
        case 1:
            if (work->unk000E != 4) {
                for (i = 0; i < 20; i++) {
                    tile = &stage->unk008[i];
                    Hu3DModelAttrReset(tile->unk08, HU3D_ATTR_DISPOFF);
                }
                Hu3DModelAttrSet(stage->unk5AE, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(stage->unk5B0, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(stage->unk5B4, HU3D_ATTR_DISPOFF);
                stage->unk004 = 0;
            }
            break;
    }
    if (stage->unk5BC != 0) {
        if (Hu3DMotionTimeGet(stage->unk5B6) >= Hu3DMotionMaxTimeGet(stage->unk5B6)) {
            Hu3DModelAttrSet(stage->unk5B6, HU3D_ATTR_DISPOFF);
            stage->unk5BC = 0;
        }
    }
    if (stage->unk5C4 != 0) {
        if (Hu3DMotionTimeGet(stage->unk5C0) >= Hu3DMotionMaxTimeGet(stage->unk5C0)) {
            Hu3DModelAttrSet(stage->unk5C0, HU3D_ATTR_DISPOFF);
            stage->unk5C4 = 0;
        }
    }
}

/* 108 insns. Tile init: a link of the tile master at column col, row row. */
void fn_1_60F8(M562_STAGETILE *tile, s16 col, s16 row, M562_STAGE *stage)
{
    HuVecF pos;
    HU3DMODELID modelId;
    M562_STAGE *s;
    M562_WORK *work;
    M562_CAMERA *camera;

    s = stage;
    work = s->unk000;
    camera = &work->camera[0];
    memset(tile, 0, sizeof(M562_STAGETILE));
    tile->unk00 = stage;
    tile->unk0C = col;
    tile->unk0E = row;
    tile->unk08 = modelId = Hu3DModelLink(stage->unk5A8);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_LLIGHT);
    Hu3DModelShadowMapSet(modelId);
    pos.x = -500.0f + 250.0f * col;
    pos.y = 0.0f;
    pos.z = -375.0f + 250.0f * row;
    Hu3DModelPosSet(modelId, pos.x, pos.y, pos.z);
    tile->unk10 = pos;
}

/* 16 insns. Tile kill. */
void fn_1_62A8(M562_STAGETILE *tile)
{
    Hu3DModelKill(tile->unk08);
    memset(tile, 0, sizeof(M562_STAGETILE));
}

/* 0xC8 */ s16 lbl_1_data_C8[32] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
/* 0x108 */ float lbl_1_data_108[3] = { 0.0f, -3300.0f, -26000.0f };

/* 528 insns. Tile frame. States 0..2: hit (unk34 set by koopa.c): swap to the cracked, then the
   broken model, playing a break effect; 10..11: fall into the lava; 20..21: fly off towards the
   distant background (data_108); 30: gone. */
void fn_1_62E8(M562_STAGETILE *tile)
{
    HuVecF d;
    float t;
    float dist;
    float clamp1;
    float clamp0;
    HU3DMODELID modelId;
    M562_STAGE *stage;
    M562_WORK *work;
    M562_CAMERA *camera;
    M562_LIGHT *light;

    stage = tile->unk00;
    work = stage->unk000;
    camera = &work->camera[0];
    light = &work->light;
    switch (tile->unk04) {
        case 0:
            if (tile->unk34 != 0) {
                Hu3DModelShadowMapObjReset(tile->unk08);
                Hu3DModelKill(tile->unk08);
                tile->unk08 = modelId = Hu3DModelLink(stage->unk5AA);
                Hu3DModelAmbSet(tile->unk08, light->unk0C.x, light->unk0C.y, light->unk0C.z);
                Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
                Hu3DModelCameraSet(modelId, camera->unk04);
                Hu3DModelLayerSet(modelId, 0);
                Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(modelId, HU3D_ATTR_LLIGHT);
                Hu3DModelShadowMapSet(modelId);
                Hu3DModelPosSet(modelId, tile->unk10.x, tile->unk10.y, tile->unk10.z);
                Hu3DMotionTimeSet(stage->unk5B6, 0.0f);
                Hu3DModelPosSet(stage->unk5B6, tile->unk10.x, tile->unk10.y, tile->unk10.z);
                Hu3DModelAttrReset(stage->unk5B6, HU3D_ATTR_DISPOFF);
                stage->unk5BC = 1;
                tile->unk34 = 0;
                tile->unk04++;
            }
            break;
        case 1:
            if (tile->unk34 != 0) {
                Hu3DModelShadowMapObjReset(tile->unk08);
                Hu3DModelKill(tile->unk08);
                tile->unk08 = modelId = Hu3DModelLink(stage->unk5AC);
                Hu3DModelAmbSet(tile->unk08, light->unk0C.x, light->unk0C.y, light->unk0C.z);
                Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
                Hu3DModelCameraSet(modelId, camera->unk04);
                Hu3DModelLayerSet(modelId, 0);
                Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(modelId, HU3D_ATTR_LLIGHT);
                Hu3DModelShadowMapSet(modelId);
                Hu3DModelPosSet(modelId, tile->unk10.x, tile->unk10.y, tile->unk10.z);
                Hu3DMotionTimeSet(stage->unk5B6, 0.0f);
                Hu3DModelPosSet(stage->unk5B6, tile->unk10.x, tile->unk10.y, tile->unk10.z);
                Hu3DModelAttrReset(stage->unk5B6, HU3D_ATTR_DISPOFF);
                stage->unk5BC = 1;
                tile->unk34 = 0;
                tile->unk04++;
            }
            break;
        case 2:
            if (tile->unk34 != 0) {
                Hu3DModelShadowMapObjReset(tile->unk08);
                Hu3DModelKill(tile->unk08);
                tile->unk08 = modelId = Hu3DModelLink(stage->unk5A8);
                Hu3DModelAmbSet(tile->unk08, light->unk0C.x, light->unk0C.y, light->unk0C.z);
                Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
                Hu3DModelCameraSet(modelId, camera->unk04);
                Hu3DModelLayerSet(modelId, 0);
                Hu3DModelAttrSet(modelId, HU3D_ATTR_LLIGHT);
                Hu3DModelShadowMapSet(modelId);
                Hu3DModelPosSet(modelId, tile->unk10.x, tile->unk10.y, tile->unk10.z);
                Hu3DMotionTimeSet(stage->unk5C0, 0.0f);
                Hu3DModelPosSet(stage->unk5C0, tile->unk10.x, tile->unk10.y, tile->unk10.z);
                Hu3DModelAttrReset(stage->unk5C0, HU3D_ATTR_DISPOFF);
                stage->unk5C4 = 1;
                Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
                tile->unk34 = 0;
                tile->unk04 = 3;
            }
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            break;
        case 10:
            tile->unk38 = 0.0f;
            t = (frand() % 10000) / 10000.0f;
            tile->unk28.x = 3.0f * t;
            t = (frand() % 10000) / 10000.0f;
            tile->unk28.y = 3.0f * t;
            t = (frand() % 10000) / 10000.0f;
            tile->unk28.z = 3.0f * t;
            tile->unk04++;
        case 11:
            tile->unk38 -= 1.5f;
            tile->unk10.y += tile->unk38;
            if (tile->unk10.y < -1000.0f) {
                tile->unk38 = 0.0f;
                tile->unk04 = 20;
            }
            break;
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
            break;
        case 20:
            tile->unk10.y = -5000.0f;
            t = (frand() % 10000) / 10000.0f;
            tile->unk3C.x = 200.0f * (t - 0.5f);
            t = (frand() % 10000) / 10000.0f;
            tile->unk3C.y = 50.0f * (t - 0.5f);
            tile->unk3C.z = 0.0f;
            tile->unk04++;
        case 21:
            PSVECSubtract((Vec *)lbl_1_data_108, &tile->unk10, &d);
            dist = PSVECMag(&d);
            t = dist / 20000.0f;
            if (t > 1.0f) {
                clamp1 = 1.0f;
            } else {
                if (t < 0.0f) {
                    clamp0 = 0.0f;
                } else {
                    clamp0 = t;
                }
                clamp1 = clamp0;
            }
            t = 1.0f - clamp1;
            t = t * t;
            t = 0.1f + 0.9f * t;
            PSVECNormalize(&d, &d);
            PSVECScale(&d, &d, 100.0f);
            tile->unk3C.x += d.x * t;
            tile->unk3C.y += d.y * t;
            tile->unk3C.z += 0.2f * (d.z * t);
            PSVECAdd(&tile->unk10, &tile->unk3C, &tile->unk10);
            if (dist < 1000.0f || tile->unk10.z < lbl_1_data_108[2]) {
                Hu3DModelAttrSet(tile->unk08, HU3D_ATTR_DISPOFF);
                tile->unk04 = 30;
            }
            break;
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
            break;
    }
    tile->unk1C.x += tile->unk28.x;
    tile->unk1C.y += tile->unk28.y;
    tile->unk1C.z += tile->unk28.z;
    Hu3DModelPosSet(tile->unk08, tile->unk10.x, tile->unk10.y, tile->unk10.z);
    Hu3DModelRotSet(tile->unk08, tile->unk1C.x, tile->unk1C.y, tile->unk1C.z);
}
