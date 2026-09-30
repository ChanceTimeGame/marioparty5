/*
 * m565dll stage.c -- written 2026-09-23 (W1 forks; see NOTES.md). Functions are in reference
 * order. Line ranges are into build/mp5-asm/m565dll/asm/REL/m565dll/stage.s.
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

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x148 */ /* float lbl_1_rodata_148 = 0.0f; */
/* 0x14C */ /* float lbl_1_rodata_14C = 10.0f; */
/* 0x150 */ /* float lbl_1_rodata_150 = 2.0f; */
/* 0x158 */ /* double lbl_1_rodata_158 = 4503601774854144; */
/* 0x160 */ /* float lbl_1_rodata_160 = 1.0f; */
/* 0x164 */ /* float lbl_1_rodata_164 = -1.0f; */
/* 0x168 */ /* float lbl_1_rodata_168 = 3.0f; */
/* 0x16C */ /* float lbl_1_rodata_16C = 200.0f; */
/* 0x170 */ /* float lbl_1_rodata_170 = 0.1f; */
/* 0x174 */ /* float lbl_1_rodata_174 = 0.2f; */
/* 0x178 */ /* float lbl_1_rodata_178 = -10000.0f; */
/* 0x17C */ /* float lbl_1_rodata_17C = 100.0f; */
/* 0x180 */ /* float lbl_1_rodata_180 = 65535.0f; */
/* 0x184 */ /* float lbl_1_rodata_184 = 6.4941406f; */
/* 0x188 */ /* float lbl_1_rodata_188 = 1.5f; */
/* 0x18C */ /* float lbl_1_rodata_18C = 50000.0f; */
/* 0x190 */ /* float lbl_1_rodata_190 = 10000.0f; */
/* 0x198 */ /* double lbl_1_rodata_198 = 4503599627370496; */
/* 0x1A0 */ /* float lbl_1_rodata_1A0 = 0.4f; */
/* 0x1A4 */ /* float lbl_1_rodata_1A4 = 0.02f; */
/* 0x1A8 */ /* float lbl_1_rodata_1A8 = -50.0f; */
/* 0x1AC */ /* float lbl_1_rodata_1AC = 5.0f; */
/* 0x1B0 */ /* float lbl_1_rodata_1B0 = 60.0f; */
/* 0x1B4 */ /* float lbl_1_rodata_1B4 = 540.0f; */
/* 0x1B8 */ /* float lbl_1_rodata_1B8 = 255.0f; */
/* 0x1BC */ /* s32 lbl_1_rodata_1BC[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x1C8 */ /* float lbl_1_rodata_1C8[2] = { -20.0f, 0.0f }; */

/* --- .data --- */
/* 0x58 */ M565_STAGECELL lbl_1_data_58[10][10] = {
    { { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 100, 0, 0x780003, 0x780036, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 40.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f } },
    { { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 100, 0, 0x780004, 0x780037, 0, 0, -10.0f, 0.0f }, { 100, 0, 0x780005, 0x780038, 0, 0, 0.0f, -10.0f }, { 0, 0, 0x0, 0x0, 0, 0, -20.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f } },
    { { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, -40.0f, 0.0f }, { 100, 0, 0x780006, 0x780039, 0, 0, 0.0f, 0.0f }, { 100, 0, 0x780007, 0x78003A, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 40.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f } },
    { { 100, 0, 0x780008, 0x78003B, 0, 0, 0.0f, 0.0f }, { 100, 0, 0x780009, 0x78003C, 0, 0, 20.0f, 0.0f }, { 100, 0, 0x78000A, 0x78003D, 0, 0, 0.0f, 0.0f }, { 100, 0, 0x78000B, 0x78003E, 1, 0, 0.0f, 15.0f }, { 100, 0, 0x78000C, 0x78003F, 1, 0, 0.0f, 0.0f }, { 100, 0, 0x78000D, 0x780040, 1, 0, -20.0f, 15.0f }, { 100, 0, 0x78000E, 0x780041, 1, 0, 0.0f, 0.0f }, { 100, 0, 0x78000F, 0x780042, 0, 0, 0.0f, 0.0f }, { 100, 0, 0x780010, 0x780043, 0, 0, 0.0f, 0.0f }, { 100, 0, 0x780011, 0x780044, 0, 0, 0.0f, -5.0f } },
    { { 0, 0, 0x0, 0x0, 0, 0, -40.0f, 20.0f }, { 100, 0, 0x780012, 0x780045, 0, 0, 0.0f, -10.0f }, { 100, 0, 0x780013, 0x780046, 0, 0, -10.0f, 5.0f }, { 100, 0, 0x780014, 0x780047, 1, 0, 10.0f, 10.0f }, { 100, 0, 0x780015, 0x780048, 0, 0, 0.0f, 0.0f }, { 100, 0, 0x780016, 0x780049, 0, 0, 0.0f, 0.0f }, { 100, 0, 0x780017, 0x78004A, 1, 0, 0.0f, 0.0f }, { 100, 0, 0x780018, 0x78004B, 0, 0, 0.0f, 0.0f }, { 100, 0, 0x780019, 0x78004C, 0, 0, -30.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 40.0f, 20.0f } },
    { { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 100, 0, 0x78001A, 0x78004D, 0, 0, 25.0f, 0.0f }, { 100, 0, 0x78001B, 0x78004E, 1, 0, 0.0f, 0.0f }, { 100, 0, 0x78001C, 0x78004F, 0, 0, 0.0f, 0.0f }, { 100, 0, 0x78001D, 0x780050, 0, 0, 0.0f, 0.0f }, { 100, 0, 0x78001E, 0x780051, 0, 0, -10.0f, -10.0f }, { 100, 0, 0x78001F, 0x780052, 0, 0, 0.0f, -15.0f }, { 100, 0, 0x780020, 0x780053, 1, 0, -10.0f, 0.0f }, { 100, 0, 0x780021, 0x780054, 0, 0, -10.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f } },
    { { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 100, 0, 0x780022, 0x780055, 1, 0, 20.0f, 0.0f }, { 100, 0, 0x780023, 0x780056, 1, 0, -10.0f, -20.0f }, { 100, 0, 0x780024, 0x780057, 0, 0, 10.0f, -15.0f }, { 100, 0, 0x780025, 0x780058, 0, 0, -10.0f, -10.0f }, { 100, 0, 0x780026, 0x780059, 1, 0, 0.0f, 0.0f }, { 100, 0, 0x780027, 0x78005A, 1, 0, -20.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f } },
    { { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 100, 0, 0x780028, 0x78005B, 0, 0, 0.0f, -25.0f }, { 100, 0, 0x780029, 0x78005C, 0, 0, 0.0f, -10.0f }, { 100, 0, 0x78002A, 0x78005D, 1, 0, 0.0f, 0.0f }, { 100, 0, 0x78002B, 0x78005E, 1, 0, 0.0f, -15.0f }, { 100, 0, 0x78002C, 0x78005F, 0, 0, -10.0f, 0.0f }, { 100, 0, 0x78002D, 0x780060, 0, 0, -10.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f } },
    { { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 100, 0, 0x78002E, 0x780061, 0, 0, 10.0f, -15.0f }, { 100, 0, 0x78002F, 0x780062, 0, 0, 5.0f, -20.0f }, { 100, 0, 0x780030, 0x780063, 1, 0, 25.0f, -25.0f }, { 100, 0, 0x780031, 0x780064, 1, 0, -10.0f, -10.0f }, { 100, 0, 0x780032, 0x780065, 0, 0, 0.0f, -15.0f }, { 100, 0, 0x780033, 0x780066, 0, 0, 0.0f, -35.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f } },
    { { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 100, 0, 0x780034, 0x780067, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 100, 0, 0x780035, 0x780068, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f }, { 0, 0, 0x0, 0x0, 0, 0, 0.0f, 0.0f } }
};

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x7818 */ s32 lbl_1_bss_7818[2]; /* 0x8: 4-aligned, retype */

/* --- functions (reference order) --- */
/* 355 insns */
void fn_1_4554(M565_STAGE *stage, M565_OBJECT *obj)
{
    float sumX[10];
    float sumZ[10];
    s16 cntX[10];
    s16 cntZ[10];
    M565_STAGEGRID *cell;
    s32 row;
    HU3DMODELID modelId;
    s32 col;
    M565_STAGEFX *fx;
    M565_OBJECT *obj2;

    obj2 = obj; /* dead copy (m502 fn_1_1690 idiom): keeps obj in a register and spills this */
    memset(stage, 0, sizeof(M565_STAGE));
    stage->unk000 = obj;
    stage->unk3354 = -1;
    fn_1_0(&stage->unk30E0);
    fn_1_0(&stage->unk30EC);
    memset(sumX, 0, sizeof(sumX));
    memset(sumZ, 0, sizeof(sumZ));
    memset(cntX, 0, sizeof(cntX));
    memset(cntZ, 0, sizeof(cntZ));
    for (row = 0; row < 10; row++) {
        for (col = 0; col < 10; col++) {
            cell = &stage->unk004[row][col];
            memset(cell, 0, sizeof(M565_STAGEGRID));
            cell->unk000 = stage;
            cell->unk004 = lbl_1_data_58[row][col].unk00;
            cell->unk006 = (s16)lbl_1_data_58[row][col].unk0C;
            cell->unk00E = col;
            cell->unk010 = row;
            if (cell->unk004 == 100) {
                modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_58[row][col].unk04, HU_MEMNUM_OVL, HEAP_MODEL));
                cell->unk012 = modelId;
                Hu3DModelShadowMapSet(modelId);
                Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
                Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
                Hu3DModelCameraSet(modelId, 1);
                Hu3DModelLayerSet(modelId, 0);
                Hu3DModelAttrReset(modelId, 1);
                modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_58[row][col].unk08, HU_MEMNUM_OVL, HEAP_MODEL));
                cell->unk014 = modelId;
                Hu3DModelAttrSet(modelId, 1);
                fn_1_76C0(cell);
                sumX[cell->unk00E] += cell->unk018.x;
                sumZ[cell->unk010] += cell->unk018.z;
                cntX[cell->unk00E]++;
                cntZ[cell->unk010]++;
                fn_1_A0(&stage->unk30E0, &cell->unk04C, cell);
                fn_1_A0(&stage->unk30EC, &cell->unk05C, cell);
            }
            else {
                cell->unk012 = 0;
            }
        }
    }
    for (row = 0; row < 10; row++) {
        for (col = 0; col < 10; col++) {
            cell = &stage->unk004[row][col];
            if (cell->unk004 == 0) {
                cell->unk018.x = sumX[cell->unk00E] / cntX[cell->unk00E];
                cell->unk018.y = 0.0f;
                cell->unk018.z = sumZ[cell->unk010] / cntZ[cell->unk010];
                cell->unk018.x += lbl_1_data_58[cell->unk010][cell->unk00E].unk10;
                cell->unk018.z += lbl_1_data_58[cell->unk010][cell->unk00E].unk14;
            }
        }
    }
    for (row = 0; row < 10; row++) {
        fx = &stage->unk3074[row];
        memset(fx, 0, sizeof(M565_STAGEFX));
        modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x69), HU_MEMNUM_OVL, HEAP_MODEL));
        fx->unk004 = modelId;
        Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(modelId, 10.0f, 10.0f, 10.0f);
        Hu3DModelCameraSet(modelId, 1);
        Hu3DModelLayerSet(modelId, 4);
        fx->unk006 = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x77), HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DMotionSpeedSet(modelId, 2.0f);
        Hu3DMotionSet(modelId, fx->unk006);
        Hu3DModelAttrReset(modelId, 0x40000001);
        Hu3DModelAttrSet(modelId, 1);
    }
    fn_1_5998(stage);
}

/* 59 insns */
void fn_1_4AE0(M565_STAGE *stage)
{
    s32 row;
    s32 col;
    M565_STAGEGRID *cell;
    M565_STAGEFX *fx;

    for (row = 0; row < 10; row++) {
        fx = &stage->unk3074[row];
        Hu3DMotionKill(fx->unk006);
        Hu3DModelKill(fx->unk004);
        memset(fx, 0, sizeof(M565_STAGEFX));
    }
    fn_1_30(&stage->unk30EC);
    fn_1_30(&stage->unk30E0);
    for (row = 0; row < 10; row++) {
        for (col = 0; col < 10; col++) {
            cell = &stage->unk004[row][col];
            Hu3DModelKill(cell->unk014);
            Hu3DModelKill(cell->unk012);
            memset(cell, 0, sizeof(M565_STAGEGRID));
        }
    }
    memset(stage, 0, sizeof(M565_STAGE));
}

/* 430 insns */
void fn_1_4BCC(M565_STAGE *stage)
{
    float vol0, pan0;
    float vol1, pan1;
    float sign;
    float speed;
    float ofs;
    M565_OBJECT *obj;
    M565_WORK *work;
    M565_LISTNODE *node;
    M565_LISTNODE *next;
    M565_STAGEGRID *cell;
    M565_LIST *list;
    s32 i;
    int se;
    s16 tries;
    s32 dc;
    s32 dr;

    obj = stage->unk000;
    work = obj->unk000;
    stage->unk30D0 = 0;
    for (node = stage->unk30EC.unk004; node; node = node->unk004) {
        cell = node->unk000;
        if (cell->unk004 == 101) {
            if (work->unk3870 != 0) {
                if (cell->unk00C <= 0) {
                    fn_1_6474(stage, cell);
                    if (stage->unk3354 >= 0) {
                        fn_1_C40(stage->unk3354);
                        stage->unk3354 = -1;
                    }
                    if (MgSeqModeGet() == 5 && stage->unk3358 <= 0) {
                        fn_1_A10(&cell->unk018, &vol0, &pan0);
                        se = fn_1_C18(0x8DB);
                        fn_1_CC8(se, vol0);
                        fn_1_C98(se, pan0);
                        stage->unk3358 = 10;
                    }
                }
                else if (cell->unk00C <= 60) {
                    if ((lbl_1_bss_0->unk008 / 3) & 1) {
                        sign = 1.0f;
                    }
                    else {
                        sign = -1.0f;
                    }
                    ofs = 3.0f * sign;
                    Hu3DModelPosSet(cell->unk012, 0.0f, ofs, 0.0f);
                    if (stage->unk3354 < 0 && MgSeqModeGet() == 5) {
                        fn_1_A10(&cell->unk018, &vol1, &pan1);
                        stage->unk3354 = fn_1_C18(0x8E0);
                        fn_1_CC8(stage->unk3354, vol1);
                        fn_1_C98(stage->unk3354, pan1);
                    }
                }
            }
            else {
                Hu3DModelPosSet(cell->unk012, 0.0f, 0.0f, 0.0f);
                cell->unk004 = 100;
            }
            if (cell->unk00C != 0) {
                cell->unk00C--;
            }
            if (stage->unk30EC.unk000 <= 1) {
                cell->unk004 = 100;
            }
        }
        else if (cell->unk004 == 102) {
            fn_1_6540(stage, cell);
            stage->unk30D0 = 1;
        }
        memset(&cell->unk06C, 0, sizeof(M565_LISTNODE));
        cell->unk030 = 0;
    }
    for (node = stage->unk30D4.unk004; node; node = next) {
        cell = node->unk000;
        next = node->unk004;
        if (cell->unk028 < 200.0f) {
            speed = 0.1f + 0.2f * cell->unk028;
        }
        else {
            speed = 0.0f;
        }
        cell->unk028 += speed;
        cell->unk024 -= cell->unk028;
        if (cell->unk024 <= -10000.0f) {
            cell->unk024 = -10000.0f;
            fn_1_E4(&stage->unk30D4, &cell->unk03C);
        }
        Hu3DModelPosSet(cell->unk014, 0.0f, cell->unk024, 0.0f);
    }
    if (stage->unk30CC != 0 && work->unk3870 != 0) {
        stage->unk3350 = stage->unk3352 = 0;
        memset(stage->unk30F8, 0, sizeof(stage->unk30F8));
        for (node = stage->unk30EC.unk004; node; node = node->unk004) {
            cell = node->unk000;
            if (cell->unk030 == 0) {
                list = &stage->unk30F8[stage->unk3350];
                fn_1_5700(stage, cell, list);
                if (stage->unk3352 < list->unk000) {
                    stage->unk3352 = list->unk000;
                }
                stage->unk3350++;
            }
        }
        for (i = 0; i < stage->unk3350; i++) {
            list = &stage->unk30F8[i];
            if (list->unk000 < 10 && list->unk000 < stage->unk3352 && stage->unk30EC.unk000 > 9
                && frand() % 100 < 100 - list->unk000 * 10) {
                for (node = list->unk004; node; node = node->unk004) {
                    cell = node->unk000;
                    if (cell->unk004 == 100) {
                        cell->unk004 = 101;
                        cell->unk00C = 60;
                    }
                    else if (cell->unk004 == 101 && cell->unk00C > 60) {
                        cell->unk00C = 60;
                    }
                }
            }
        }
        fn_1_5998(stage);
    }
    if (!stage->unk30C4) {
        if (work->unk010 < 2400 && work->unk010 > 1200 && frand() % 10000 < 2000) {
            fn_1_5284(stage, &stage->unk30C4);
            if (stage->unk30C4) {
                tries = 0;
                do {
                    stage->unk30C8 = NULL;
                    fn_1_5284(stage, &stage->unk30C8);
                    if (stage->unk30C4 && stage->unk30C8) {
                        if (stage->unk30C4->unk00E - stage->unk30C8->unk00E >= 0) {
                            dc = stage->unk30C4->unk00E - stage->unk30C8->unk00E;
                        }
                        else {
                            dc = -(stage->unk30C4->unk00E - stage->unk30C8->unk00E);
                        }
                        if (dc > 3) {
                            if (stage->unk30C4->unk010 - stage->unk30C8->unk010 >= 0) {
                                dr = stage->unk30C4->unk010 - stage->unk30C8->unk010;
                            }
                            else {
                                dr = -(stage->unk30C4->unk010 - stage->unk30C8->unk010);
                            }
                            if (dr > 4) {
                                goto found;
                            }
                        }
                    }
                } while (tries++ <= 20);
                stage->unk30C8 = NULL;
            }
        }
        else {
            fn_1_5284(stage, &stage->unk30C4);
        }
    }
found:
    fn_1_7624(stage);
    if (stage->unk3358 != 0) {
        stage->unk3358--;
    }
    stage->unk30CC = 0;
}

/* 287 insns */
void fn_1_5284(M565_STAGE *stage, M565_STAGEGRID **out)
{
    float chance;
    M565_STAGEGRID *cell;
    s32 edge;
    s32 empty;
    M565_WORK *work;
    M565_PUKU2 *puku2;
    s16 col;
    s16 row;
    s32 anyCell;
    M565_OBJECT *obj;
    s16 tries;
    s16 retry;
    s16 rnd;

    obj = stage->unk000;
    puku2 = &obj->unk3648;
    work = obj->unk000;
    if (*out) {
        return;
    }
    empty = edge = anyCell = 0;
    if (work->unk010 > 3000) {
        empty = frand() % 10000 < 9000;
        edge = 0;
    }
    else if (work->unk010 > 2700) {
        empty = frand() % 10000 < 8000;
        edge = 0;
    }
    else if (work->unk010 > 2400) {
        empty = frand() % 10000 < 6000;
        edge = 0;
    }
    else if (work->unk010 > 1800) {
        empty = frand() % 10000 < 2000;
        edge = 0;
    }
    else if (work->unk010 > 600) {
        empty = 0;
        edge = 0;
    }
    else {
        empty = frand() % 10000 < 9000;
        edge = 1;
    }
    if (puku2->unk1D6 == 8) {
        empty = edge = 0;
        anyCell = 1;
    }
    else if (puku2->unk1D6 == 10) {
        empty = edge = 0;
        anyCell = 1;
    }
    else if (puku2->unk1D6 == 12) {
        empty = edge = 0;
        anyCell = 1;
    }
    if (stage->unk30EC.unk000 <= 9) {
        empty = edge = 1;
    }
    tries = 0;
    while (!*out) {
        if (anyCell) {
            retry = 0;
            while (TRUE) {
                col = frand() % 10;
                row = frand() % 10;
                cell = &stage->unk004[row][col];
                if (cell->unk004 == 100 || cell->unk004 == 101) {
                    break;
                }
                if (retry++ > 20) {
                    break;
                }
            }
        }
        else {
            if (edge) {
                col = (frand() & 1) ? (frand() & 1) : 9 - (frand() & 1);
                row = (frand() & 1) ? (frand() & 1) : 9 - (frand() & 1);
            }
            else {
                col = frand() % 10;
                row = frand() % 10;
            }
            cell = &stage->unk004[row][col];
        }
        if (empty) {
            if (cell->unk004 <= 1) {
                *out = cell;
                return;
            }
        }
        else if (edge || (!edge && cell->unk004 != 0)) {
            rnd = (frand() & 0xFFFF) ^ (frand() & 0xFFFF);
            chance = 100.0f * (rnd / 65535.0f);
            switch (cell->unk006) {
                case 1:
                    if (chance < 6.4941406f) {
                        *out = cell;
                    }
                    break;
                default:
                    if (chance < 1.5f) {
                        *out = cell;
                    }
                    break;
            }
        }
        if (tries++ > 20) {
            break;
        }
    }
}

/* 57 insns */
void fn_1_5700(M565_STAGE *stage, M565_STAGEGRID *cell, M565_LIST *list)
{
    if (cell->unk030 == 0) {
        fn_1_A0(list, &cell->unk06C, cell);
        cell->unk030 = 1;
        fn_1_57E4(stage, cell, cell->unk00E, cell->unk010 - 1, list);
        fn_1_57E4(stage, cell, cell->unk00E, cell->unk010 + 1, list);
        fn_1_57E4(stage, cell, cell->unk00E - 1, cell->unk010, list);
        fn_1_57E4(stage, cell, cell->unk00E + 1, cell->unk010, list);
    }
}

/* 109 insns */
void fn_1_57E4(M565_STAGE *stage, M565_STAGEGRID *from, s16 col, s16 row, M565_LIST *list)
{
    M565_STAGEGRID *cell;

    if (col >= 0 && col < 10 && row >= 0 && row < 10) {
        cell = &stage->unk004[row][col];
        if ((cell->unk004 == 100 || cell->unk004 == 101) && cell->unk030 == 0) {
            /* the two cells (4,8) and (5,8) are never joined */
            if (from->unk010 == 8 && from->unk00E == 4 && row == 8 && col == 5) {
                return;
            }
            if (from->unk010 == 8 && from->unk00E == 5 && row == 8 && col == 4) {
                return;
            }
            fn_1_5700(stage, cell, list);
        }
    }
}

/* one 3x3 neighbour of fn_1_5998: count it if it is inside the grid and standable */
#define STAGE_NBCOUNT(stage_, c_, r_)                                    \
    if ((c_) >= 0 && (c_) < 10 && (r_) >= 0 && (r_) < 10) {              \
        nb = &(stage_)->unk004[r_][c_];                                  \
        if (nb->unk004 == 100 || nb->unk004 == 101) {                    \
            nb->unk02C++;                                                \
        }                                                                \
    }

/* 326 insns */
void fn_1_5998(M565_STAGE *stage)
{
    s16 col;
    s16 row;
    M565_STAGEGRID *cell;
    M565_STAGEGRID *nb;

    for (row = 0; row < 10; row++) {
        for (col = 0; col < 10; col++) {
            cell = &stage->unk004[row][col];
            cell->unk02C = 0;
            if (cell->unk004 == 100 || cell->unk004 == 101) {
                STAGE_NBCOUNT(stage, col, row);
                STAGE_NBCOUNT(stage, col - 1, row);
                STAGE_NBCOUNT(stage, col + 1, row);
                STAGE_NBCOUNT(stage, col - 1, row - 1);
                STAGE_NBCOUNT(stage, col + 1, row - 1);
                STAGE_NBCOUNT(stage, col - 1, row + 1);
                STAGE_NBCOUNT(stage, col + 1, row + 1);
                STAGE_NBCOUNT(stage, col, row - 1);
                STAGE_NBCOUNT(stage, col, row + 1);
            }
        }
    }
}

/* 29 insns */
void fn_1_5EB0(M565_STAGE *stage, HuVecF *pos, s32 flag, M565_STAGEGRID **out)
{
    if (flag == 0) {
        fn_1_5F24(stage, pos, out);
    }
    else {
        fn_1_6140(stage, pos, out);
    }
}

/* no SDK header declares rand8 (same declaration as m502dll.h) */
int rand8(void);

/* stage.c fn_1_5F24, 135 insns. fn_1_5EB0 flag == 0: the one block nearest pos (XZ,
 * < 200). With out, hand it back in out[0] (out[1..3] = NULL); without, drop it. */
void fn_1_5F24(M565_STAGE *stage, HuVecF *pos, M565_STAGEGRID **out)
{
    HuVecF diff;
    HuVecF fxPos;
    M565_LISTNODE *node;
    float vol;
    float pan;
    s16 col;
    s16 row;
    M565_STAGEGRID *cell;
    float dist;
    float minDist;
    M565_STAGEGRID *best;
    s32 hit;
    int seId;

    best = NULL;
    minDist = 50000.0f;
    node = stage->unk30E0.unk004;
    for (row = 0; row < 10; row++) {
        for (col = 0; col < 10; col++) {
            cell = &stage->unk004[row][col];
            PSVECSubtract(pos, &cell->unk018, &diff);
            diff.y = 0.0f;
            dist = PSVECMag(&diff);
            if (dist < 200.0f && dist < minDist) {
                minDist = dist;
                best = cell;
            }
        }
    }
    hit = 0;
    if (out) {
        out[0] = best;
        out[1] = NULL;
        out[2] = NULL;
        out[3] = NULL;
    } else if (best) {
        if (best->unk004 == 100 || best->unk004 == 101) {
            fn_1_677C(stage, best);
            hit = 1;
        } else if (best->unk004 == 102 && pos->y < best->unk024) {
            fxPos.x = best->unk018.x;
            fxPos.y = pos->y;
            fxPos.z = best->unk018.z;
            fn_1_7578(stage, &fxPos);
            fn_1_66D4(stage, best);
            hit = 1;
        }
        if (hit && MgSeqModeGet() == 5) {
            fn_1_A10(&best->unk018, &vol, &pan);
            seId = fn_1_C18(0x8DA);
            fn_1_CC8(seId, vol);
            fn_1_C98(seId, pan);
        }
    }
}

/* stage.c fn_1_6140, 205 insns. fn_1_5EB0 flag != 0: up to four blocks within 200,
 * one per slot, the slot rotated by the lbl_1_bss_7818[0] counter. */
void fn_1_6140(M565_STAGE *stage, HuVecF *pos, M565_STAGEGRID **out)
{
    float dists[4];
    M565_STAGEGRID *cells[4];
    HuVecF diff;
    HuVecF fxPos;
    float vol;
    float pan;
    s16 col;
    s16 row;
    s32 i;
    s32 slot;
    M565_STAGEGRID *cell;
    float dist;
    s16 played;
    s32 hit;
    int seId;

    cells[0] = cells[1] = cells[2] = cells[3] = NULL;
    dists[0] = dists[1] = dists[2] = dists[3] = 50000.0f;
    for (row = 0; row < 10; row++) {
        for (col = 0; col < 10; col++) {
            cell = &stage->unk004[row][col];
            PSVECSubtract(pos, &cell->unk018, &diff);
            diff.y = 0.0f;
            dist = PSVECMag(&diff);
            for (i = 0; i < 4; i++) {
                slot = (i + lbl_1_bss_7818[0]) % 4;
                if (dist < 200.0f && dist < dists[slot]) {
                    dists[slot] = dist;
                    cells[slot] = cell;
                    lbl_1_bss_7818[0]++;
                    break;
                }
            }
        }
    }
    played = 0;
    hit = 0;
    if (out) {
        out[0] = cells[0];
        out[1] = cells[1];
        out[2] = cells[2];
        out[3] = cells[3];
    } else {
        for (i = 0; i < 4; i++) {
            if (cells[i]) {
                if (cells[i]->unk004 == 100 || cells[i]->unk004 == 101) {
                    fn_1_677C(stage, cells[i]);
                    hit = 1;
                } else if (cells[i]->unk004 == 102 && pos->y < cells[i]->unk024) {
                    fxPos.x = cells[i]->unk018.x;
                    fxPos.y = pos->y;
                    fxPos.z = cells[i]->unk018.z;
                    fn_1_7578(stage, &fxPos);
                    fn_1_66D4(stage, cells[i]);
                    hit = 1;
                }
                if (hit && MgSeqModeGet() == 5 && played == 0) {
                    fn_1_A10(&cells[i]->unk018, &vol, &pan);
                    seId = fn_1_C18(0x8DA);
                    fn_1_CC8(seId, vol);
                    fn_1_C98(seId, pan);
                    played++;
                }
            }
        }
    }
}

/* stage.c fn_1_6474, 51 insns. Start a block sinking (kind 102). */
void fn_1_6474(M565_STAGE *stage, M565_STAGEGRID *cell)
{
    Hu3DModelPosSet(cell->unk012, 0.0f, 0.0f, 0.0f);
    cell->unk024 = 0.0f;
    cell->unk028 = 0.1f * ((frand() % 10000) / 10000.0f);
    cell->unk004 = 102;
}

/* stage.c fn_1_6540, 101 insns. A sinking block: accelerate down, wobble the top
 * model, retire it below -10000. */
void fn_1_6540(M565_STAGE *stage, M565_STAGEGRID *cell)
{
    float sign;
    float accel;
    float wobble;

    if ((lbl_1_bss_0->unk008 / 3) & 1) {
        sign = 1.0f;
    } else {
        sign = -1.0f;
    }
    wobble = 3.0f * sign;
    if (cell->unk028 < 100.0f) {
        accel = 0.4f + 0.02f * cell->unk028;
    } else {
        accel = 0.0f;
    }
    cell->unk028 += accel;
    cell->unk024 -= cell->unk028;
    Hu3DModelPosSet(cell->unk012, 0.0f, cell->unk024 + wobble, 0.0f);
    Hu3DModelPosSet(cell->unk014, 0.0f, cell->unk024, 0.0f);
    if (cell->unk024 <= -10000.0f) {
        fn_1_66D4(stage, cell);
    }
}

/* stage.c fn_1_66D4, 42 insns. Remove a block for good (kind 1). */
void fn_1_66D4(M565_STAGE *stage, M565_STAGEGRID *cell)
{
    Hu3DModelAttrSet(cell->unk012, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(cell->unk012, 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(cell->unk014, 0.0f, -10000.0f, 0.0f);
    fn_1_E4(&stage->unk30EC, &cell->unk05C);
    cell->unk004 = 1;
}

/* stage.c fn_1_677C, 73 insns. Knock a block out: onto the dropping list, spawn the
 * effect, and mark its neighbours (fn_1_68A0). Never the last standing block. */
void fn_1_677C(M565_STAGE *stage, M565_STAGEGRID *cell)
{
    HuVecF fxPos;

    if (stage->unk30EC.unk000 > 1) {
        if (stage->unk3354 >= 0) {
            fn_1_C40(stage->unk3354);
            stage->unk3354 = -1;
        }
        Hu3DModelAttrSet(cell->unk012, HU3D_ATTR_DISPOFF);
        cell->unk004 = 1;
        cell->unk024 = -50.0f;
        cell->unk028 = (cell->unk028 < 5.0f) ? 5.0f : cell->unk028;
        fn_1_A0(&stage->unk30D4, &cell->unk03C, cell);
        fn_1_E4(&stage->unk30EC, &cell->unk05C);
        fxPos = cell->unk018;
        fxPos.y = 0.0f;
        fn_1_7578(stage, &fxPos);
        fn_1_68A0(stage, cell);
        stage->unk30CC = 1;
    }
}

/* 60..600 frames */
#define M565_CRUMBLETIME() (60.0f + 540.0f * ((rand8() % 256) / 255.0f))

/* stage.c fn_1_68A0, 822 insns. A removed block (kind 1) two away, or diagonal, from
 * this one leaves a one-block bridge: set the block(s) between them crumbling (kind
 * 101) with a random countdown. */
void fn_1_68A0(M565_STAGE *stage, M565_STAGEGRID *cell)
{
    s16 col;
    s16 row;
    s32 r;
    M565_STAGEGRID *c;

    col = cell->unk00E;
    row = cell->unk010;
    if (col >= 0 && col < 10 && row - 2 >= 0 && row - 2 < 10 && stage->unk004[row - 2][col].unk004 == 1) {
        c = &stage->unk004[row - 1][col];
        if (c->unk004 == 100) {
            c->unk004 = 101;
            c->unk00C = M565_CRUMBLETIME();
        }
        return;
    }
    if (col + 2 >= 0 && col + 2 < 10 && row >= 0 && row < 10 && stage->unk004[row][col + 2].unk004 == 1) {
        c = &stage->unk004[row][col + 1];
        if (c->unk004 == 100) {
            c->unk004 = 101;
            c->unk00C = M565_CRUMBLETIME();
        }
        return;
    }
    if (col >= 0 && col < 10 && row + 2 >= 0 && row + 2 < 10 && stage->unk004[row + 2][col].unk004 == 1) {
        c = &stage->unk004[row + 1][col];
        if (c->unk004 == 100) {
            c->unk004 = 101;
            c->unk00C = M565_CRUMBLETIME();
        }
        return;
    }
    if (col - 2 >= 0 && col - 2 < 10 && row >= 0 && row < 10 && stage->unk004[row][col - 2].unk004 == 1) {
        c = &stage->unk004[row][col - 1];
        if (c->unk004 == 100) {
            c->unk004 = 101;
            c->unk00C = M565_CRUMBLETIME();
        }
        return;
    }
    if (col + 1 >= 0 && col + 1 < 10 && row - 1 >= 0 && row - 1 < 10 && stage->unk004[row - 1][col + 1].unk004 == 1) {
        r = rand8() % 100;
        if (r < 30 || r >= 60) {
            c = &stage->unk004[row - 1][col];
            if (c->unk004 == 100) {
                c->unk004 = 101;
                c->unk00C = M565_CRUMBLETIME();
            } else {
                r = 60;
            }
        }
        if (r >= 30) {
            c = &stage->unk004[row][col + 1];
            if (c->unk004 == 100) {
                c->unk004 = 101;
                c->unk00C = M565_CRUMBLETIME();
            }
        }
        return;
    }
    if (col + 1 >= 0 && col + 1 < 10 && row + 1 >= 0 && row + 1 < 10 && stage->unk004[row + 1][col + 1].unk004 == 1) {
        r = rand8() % 100;
        if (r < 30 || r >= 60) {
            c = &stage->unk004[row][col + 1];
            if (c->unk004 == 100) {
                c->unk004 = 101;
                c->unk00C = M565_CRUMBLETIME();
            } else {
                r = 60;
            }
        }
        if (r >= 30) {
            c = &stage->unk004[row + 1][col];
            if (c->unk004 == 100) {
                c->unk004 = 101;
                c->unk00C = M565_CRUMBLETIME();
            }
        }
        return;
    }
    if (col - 1 >= 0 && col - 1 < 10 && row + 1 >= 0 && row + 1 < 10 && stage->unk004[row + 1][col - 1].unk004 == 1) {
        r = rand8() % 100;
        if (r < 30 || r >= 60) {
            c = &stage->unk004[row + 1][col];
            if (c->unk004 == 100) {
                c->unk004 = 101;
                c->unk00C = M565_CRUMBLETIME();
            } else {
                r = 60;
            }
        }
        if (r >= 30) {
            c = &stage->unk004[row][col - 1];
            if (c->unk004 == 100) {
                c->unk004 = 101;
                c->unk00C = M565_CRUMBLETIME();
            }
        }
        return;
    }
    if (col - 1 >= 0 && col - 1 < 10 && row >= 0 && row < 10 && stage->unk004[row][col - 1].unk004 == 1) {
        /* retail: tests [row][col-1], not the diagonal [row-1][col-1] (see OUT.txt) */
        r = rand8() % 100;
        if (r < 30 || r >= 60) {
            c = &stage->unk004[row][col - 1];
            if (c->unk004 == 100) {
                c->unk004 = 101;
                c->unk00C = M565_CRUMBLETIME();
            } else {
                r = 60;
            }
        }
        /* retail writes [row-1] without a row check; host: skip it on row 0 */
        if (r >= 30 && M565_PC_OK(row - 1 >= 0)) {
            c = &stage->unk004[row - 1][col];
            if (c->unk004 == 100) {
                c->unk004 = 101;
                c->unk00C = M565_CRUMBLETIME();
            }
        }
        return;
    }
}

/* stage.c fn_1_7578, 43 insns. Play the first free pooled effect at pos. */
void fn_1_7578(M565_STAGE *stage, HuVecF *pos)
{
    s32 i;
    M565_STAGEFX *fx;

    for (i = 0; i < 10; i++) {
        fx = &stage->unk3074[i];
        if (fx->unk000 == 0) {
            Hu3DModelPosSet(fx->unk004, pos->x, pos->y, pos->z);
            Hu3DMotionTimeSet(fx->unk004, 0.0f);
            Hu3DModelAttrReset(fx->unk004, HU3D_ATTR_DISPOFF);
            fx->unk000 = 1;
            break;
        }
    }
}

/* stage.c fn_1_7624, 39 insns. Hide pooled effects whose motion has finished. */
void fn_1_7624(M565_STAGE *stage)
{
    s32 i;
    M565_STAGEFX *fx;
    float maxTime;

    for (i = 0; i < 10; i++) {
        fx = &stage->unk3074[i];
        if (fx->unk000 != 0) {
            maxTime = Hu3DMotionMaxTimeGet(fx->unk004);
            if (Hu3DMotionTimeGet(fx->unk004) >= maxTime) {
                Hu3DModelAttrSet(fx->unk004, HU3D_ATTR_DISPOFF);
                fx->unk000 = 0;
            }
        }
    }
}

/* stage.c fn_1_76C0, 127 insns. Block centre = mean of its model's vertices above
 * y -20, plus the per-cell offset from lbl_1_data_58. */
void fn_1_76C0(M565_STAGEGRID *cell)
{
    HuVecF sum;
    HSFDATA *hsf = Hu3DData[cell->unk014].hsf;
    HSFBUFFER *buf = hsf->vertex;
    HuVecF *vtx = buf->data;
    s32 n = 0;
    HuVecF zero = { 0.0f, 0.0f, 0.0f };
    HuVecF *src = &zero;
    s32 i;

    sum = *src;
    for (i = 0; i < buf->count; i++) {
        if (vtx[i].y > -20.0f) {
            sum.x += vtx[i].x;
            sum.y += vtx[i].y;
            sum.z += vtx[i].z;
            n++;
        }
    }
    cell->unk018.x = sum.x / n;
    cell->unk018.y = sum.y / n;
    cell->unk018.z = sum.z / n;
    cell->unk018.x += lbl_1_data_58[cell->unk010][cell->unk00E].unk10;
    cell->unk018.z += lbl_1_data_58[cell->unk010][cell->unk00E].unk14;
}

