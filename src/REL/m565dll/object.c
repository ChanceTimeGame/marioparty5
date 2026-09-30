/*
 * m565dll object.c -- written 2026-09-23 (W1 forks; see NOTES.md). Functions are in reference
 * order. Line ranges are into build/mp5-asm/m565dll/asm/REL/m565dll/object.s.
 */

#include "REL/m565dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"
#include "game/charman.h"
#include "game/mg/actman.h"
#include "datadir_enum.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0xA8 */ /* HuVecF literal { 0, 0, 0 } (fn_1_25B4 local initializer) */
/* 0xB4 */ /* float lbl_1_rodata_B4 = 0.0f; */
/* 0xB8 */ /* float lbl_1_rodata_B8 = 10000.0f; */
/* 0xBC */ /* float lbl_1_rodata_BC = 5.0f; */
/* 0xC0 */ /* float lbl_1_rodata_C0 = 50.0f; */
/* 0xC8 */ /* double lbl_1_rodata_C8 = 3.141592653589793; */
/* 0xD0 */ /* double lbl_1_rodata_D0 = 180; */
/* 0xD8 */ /* double lbl_1_rodata_D8 = 4503599627370496; */
/* 0xE0 */ /* double lbl_1_rodata_E0 = 4503601774854144; */
/* 0xE8 */ /* float lbl_1_rodata_E8 = 1300.0f; */
/* 0xEC */ /* float lbl_1_rodata_EC = 1200.0f; */
/* 0xF0 */ /* float lbl_1_rodata_F0 = 200.0f; */
/* 0xF4 */ /* float lbl_1_rodata_F4 = -800.0f; */
/* 0xF8 */ /* float lbl_1_rodata_F8 = -1000.0f; */
/* 0xFC */ /* float lbl_1_rodata_FC = 500.0f; */
/* 0x100 */ /* float lbl_1_rodata_100[2] = { 90.0f, 0.0f }; */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x7810 */ s32 lbl_1_bss_7810[2]; /* [0]: frames since the last puku spawn check (a counter, not a pointer); [1] unused */

void ColKill(void);

/* one block's position onto a player, y forced to 0 */
#define PLAYER_BLOCK_SET(player_, stage_, col_, row_, pos_)                            \
    do {                                                                               \
        (player_)->unk088 = (col_);                                                    \
        (player_)->unk08A = (row_);                                                    \
        pos_ = (stage_)->unk004[(player_)->unk08A][(player_)->unk088].unk018;          \
        pos_.y = 0.0f;                                                                 \
        (player_)->unk004->actor->pos.x = (player_)->unk074->x = pos_.x;               \
        (player_)->unk004->actor->pos.y = (player_)->unk074->y = pos_.y;               \
        (player_)->unk004->actor->pos.z = (player_)->unk074->z = pos_.z;               \
    } while (0)

/* --- functions (reference order) --- */
/* 312 insns */
void fn_1_25B4(M565_OBJECT *obj, M565_WORK *work)
{
    HU3DMODELID ids[100];
    HuVecF pos;
    s32 i;
    s32 num;
    M565_LISTNODE *node;
    M565_STAGEGRID *block;
    HU3DMODELID modelId;
    M565_STAGE *stage;
    M565_PLAYER *player;

    stage = &obj->unk2E4;
    memset(obj, 0, sizeof(M565_OBJECT));
    obj->unk000 = work;
    fn_1_FCBC(&obj->unk3640, obj);
    fn_1_3690(&obj->unk2B8, obj);
    fn_1_4554(&obj->unk2E4, obj);
    fn_1_8AD0(&obj->unk3648, obj);
    modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x6A), HU_MEMNUM_OVL, HEAP_MODEL));
    obj->unk3820 = modelId;
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, 1);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelShadowMapSet(modelId);
    obj->unk3822 = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x78), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrReset(modelId, 0x40000001);
    Hu3DModelAttrReset(modelId, 1);
    Hu3DMotionSpeedSet(modelId, 0.0f);
    Hu3DMotionSet(modelId, obj->unk3822);
    num = 0;
    for (node = obj->unk2E4.unk30E0.unk004; node; node = node->unk004) {
        block = node->unk000;
        ids[num] = block->unk014;
        num++;
    }
    ColKill();
    MgActorColMapInit(ids, num, 40);
    for (i = 0; i < 4; i++) {
        fn_1_78BC(&obj->unk008[i], i, obj);
    }
    player = &obj->unk008[0];
    PLAYER_BLOCK_SET(player, stage, 3, 4, pos);
    player = &obj->unk008[1];
    PLAYER_BLOCK_SET(player, stage, 6, 4, pos);
    player = &obj->unk008[2];
    PLAYER_BLOCK_SET(player, stage, 3, 7, pos);
    player = &obj->unk008[3];
    PLAYER_BLOCK_SET(player, stage, 6, 7, pos);
    MgActorExec();
    obj->unk3824 = 1;
    obj->unk3828 = 1;
    CharEffectLayerSet(4);
    {
        HuVecF *src;
        HuVecF zero = { 0.0f, 0.0f, 0.0f };
        src = &zero;
        obj->unk3838 = *src;
    }
    obj->unk382C = Center;
}

/* 35 insns */
void fn_1_2A94(M565_OBJECT *obj)
{
    s32 i;

    Hu3DMotionKill(obj->unk3822);
    Hu3DModelKill(obj->unk3820);
    fn_1_8B44(&obj->unk3648);
    for (i = 0; i < 4; i++) {
        fn_1_7B8C(&obj->unk008[i]);
    }
    fn_1_4AE0(&obj->unk2E4);
    fn_1_3E54(&obj->unk2B8);
    memset(obj, 0, sizeof(M565_OBJECT));
}

/* project a puku position to volume/pan and play seNo there */
#define PUKU_SE_PLAY(puku_, seNo_, se_, vol_, pan_) \
    do {                                            \
        fn_1_A10(&(puku_)->unk010, &vol_, &pan_);   \
        se_ = fn_1_C18(seNo_);                      \
        fn_1_CC8(se_, vol_);                        \
        fn_1_C98(se_, pan_);                        \
    } while (0)

/* 320 insns */
s32 fn_1_2B20(M565_OBJECT *obj)
{
    float vol0, pan0, vol1, pan1, vol2, pan2, vol3, pan3;
    float ofs;
    float max;
    s32 i;
    M565_STAGE *stage;
    s32 result;
    s32 alive;
    M565_WORK *work;
    M565_PLAYER *player;
    M565_PUKU2OBJ *puku;
    s32 flag;
    int se0, se1, se2, se3;
    s16 interval;

    work = obj->unk000;
    stage = &obj->unk2E4;
    result = 0;
    fn_1_8BA8(&obj->unk3648);
    alive = 0;
    for (i = 0; i < 4; i++) {
        player = &obj->unk008[i];
        fn_1_7BDC(player);
        if (player->unk090 == 0) {
            alive++;
        }
    }
    if (alive <= 1) {
        result = 1;
    }
    fn_1_4BCC(&obj->unk2E4);
    fn_1_3F14(&obj->unk2B8);
    interval = work->unk010 / 60 + 30;
    if (lbl_1_bss_7810[0]++ >= interval) {
        if (MgSeqModeGet() == 5) {
            if (stage->unk30C4 && stage->unk30C8) {
                flag = 1;
                if (obj->unk3648.unk1D2 >= 2) {
                    flag = 0;
                }
                puku = fn_1_3020(obj, stage->unk30C4, flag);
                if (puku) {
                    PUKU_SE_PLAY(puku, 0x8DE, se0, vol0, pan0);
                }
                puku = fn_1_3020(obj, stage->unk30C8, flag);
                if (puku) {
                    PUKU_SE_PLAY(puku, 0x8DE, se1, vol1, pan1);
                }
                stage->unk30C4 = NULL;
                stage->unk30C8 = NULL;
            }
            else if (stage->unk30C4) {
                flag = (frand() % 10000) / 10000.0f < 5.0f / (50.0f + work->unk010 / 60);
                if (obj->unk3648.unk1D2 >= 2) {
                    flag = 0;
                }
                puku = fn_1_3020(obj, stage->unk30C4, flag);
                stage->unk30C4 = NULL;
                if (flag) {
                    if (puku) {
                        PUKU_SE_PLAY(puku, 0x8DE, se2, vol2, pan2);
                    }
                }
                else if (puku) {
                    PUKU_SE_PLAY(puku, 0x8DD, se3, vol3, pan3);
                }
            }
        }
        lbl_1_bss_7810[0] = 0;
    }
    if (obj->unk3828) {
        max = Hu3DMotionMaxTimeGet(obj->unk3820);
        if (Hu3DMotionTimeGet(obj->unk3820) >= max) {
            Hu3DModelAttrSet(obj->unk3820, 1);
            obj->unk3828 = 0;
        }
    }
    if (obj->unk3844) {
        ofs = obj->unk3848 * sin(M_PI * obj->unk3854 / 180.0);
        obj->unk3854 += obj->unk3850;
        obj->unk3848 *= obj->unk384C;
        if (--obj->unk3844 == 0) {
            obj->unk3848 = obj->unk384C = obj->unk3850 = obj->unk3854 = 0.0f;
        }
        obj->unk3838.x = ofs;
    }
    Center.x = obj->unk382C.x + obj->unk3838.x;
    Center.y = obj->unk382C.y + obj->unk3838.y;
    Center.z = obj->unk382C.z + obj->unk3838.z;
    return result;
}

/* mark the (up to four) blocks fn_1_5EB0 reports as targeted by puku */
#define BLOCK_MARK(block_, puku_)      \
    do {                               \
        if (block_) {        \
            (block_)->unk034 = 1;      \
            (block_)->unk038 = (puku_); \
        }                              \
    } while (0)

/* 153 insns */
M565_PUKU2OBJ *fn_1_3020(M565_OBJECT *obj, M565_STAGEGRID *block, s32 flag)
{
    M565_STAGEGRID *blocks[4];
    HuVecF dir;
    HuVecF tmp;
    HuVecF start;
    HuVecF end;
    float mag;
    float base;
    float dist;
    M565_STAGE *stage;
    M565_PUKU2OBJ *puku;

    stage = &obj->unk2E4;
    puku = NULL;
    if (flag) {
        base = 1300.0f;
    }
    else {
        base = 1200.0f;
    }
    dist = base;
    dir.x = block->unk018.x;
    dir.y = 0.0f;
    dir.z = block->unk018.z;
    mag = PSVECMag(&dir);
    PSVECNormalize(&dir, &dir);
    if (dist < 200.0f + mag) {
        dist = 200.0f + mag;
    }
    PSVECScale(&dir, &tmp, dist);
    start = tmp;
    start.y = -800.0f;
    end = block->unk018;
    end.y = -1000.0f;
    puku = fn_1_8C70(&obj->unk3648, &start, &end, 500.0f, flag);
    if (!puku) {
        return NULL;
    }
    if (flag) {
        puku->unk030 = 60;
    }
    puku->unk034 = block;
    fn_1_5EB0(stage, &end, flag, blocks);
    if (flag) {
        BLOCK_MARK(blocks[0], puku);
        BLOCK_MARK(blocks[1], puku);
        BLOCK_MARK(blocks[2], puku);
        BLOCK_MARK(blocks[3], puku);
    }
    else {
        BLOCK_MARK(blocks[0], puku);
    }
    return puku;
}

/* 166 insns */
M565_PUKU2OBJ *fn_1_3284(M565_OBJECT *obj, float angle, float scale, s32 flag)
{
    HuVecF dir;
    HuVecF tmp;
    HuVecF start;
    HuVecF end;
    M565_STAGEGRID *blocks[4];
    float dist;
    float base;
    M565_STAGE *stage;
    M565_PUKU2OBJ *puku;

    stage = &obj->unk2E4;
    puku = NULL;
    if (flag) {
        base = 1300.0f;
    }
    else {
        base = 1200.0f;
    }
    dist = base;
    dir.x = sin(M_PI * angle / 180.0);
    dir.y = 0.0f;
    dir.z = cos(M_PI * angle / 180.0);
    PSVECScale(&dir, &tmp, dist);
    start = tmp;
    start.y = -800.0f;
    PSVECScale(&dir, &tmp, dist * scale);
    end = tmp;
    end.y = -1000.0f;
    puku = fn_1_8C70(&obj->unk3648, &start, &end, 500.0f, flag);
    if (!puku) {
        return NULL;
    }
    if (flag) {
        puku->unk030 = 60;
    }
    puku->unk034 = NULL;
    fn_1_5EB0(stage, &end, flag, blocks);
    if (flag) {
        BLOCK_MARK(blocks[0], puku);
        BLOCK_MARK(blocks[1], puku);
        BLOCK_MARK(blocks[2], puku);
        BLOCK_MARK(blocks[3], puku);
    }
    else {
        BLOCK_MARK(blocks[0], puku);
    }
    return puku;
}

/* 84 insns */
void fn_1_351C(M565_OBJECT *obj)
{
    s32 row;
    s32 col;
    M565_STAGEGRID *block;
    HU3DMODELID modelId;
    M565_STAGE *stage;

    stage = &obj->unk2E4;
    Hu3DModelAttrReset(obj->unk3820, 1);
    Hu3DMotionTimeSet(obj->unk3820, 0.0f);
    Hu3DMotionSpeedSet(obj->unk3820, 0.0f);
    obj->unk3824 = 1;
    for (row = 0; row < 10; row++) {
        for (col = 0; col < 10; col++) {
            block = &stage->unk004[row][col];
            if (block->unk004 != 100 && block->unk004 != 0) {
                Hu3DModelPosSet(block->unk012, 0.0f, 0.0f, 0.0f);
                Hu3DModelAttrReset(block->unk012, 1);
                if (block->unk004 == 1) {
                    fn_1_A0(&stage->unk30EC, &block->unk05C, block);
                }
                block->unk004 = 100;
                modelId = block->unk014;
                Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
            }
        }
    }
}

/* 9 insns */
void fn_1_366C(M565_OBJECT *obj, s32 time, float amp, float decay, float speed)
{
    obj->unk3844 = time;
    obj->unk3848 = amp;
    obj->unk384C = decay;
    obj->unk3850 = speed;
    obj->unk3854 = 90.0f;
}
