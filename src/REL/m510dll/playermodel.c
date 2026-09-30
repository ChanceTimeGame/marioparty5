/*
 * m510dll playermodel.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m510dll/asm/REL/m510dll/playermodel.s.
 */

#include "REL/m510dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0xB0 */ /* s32 lbl_1_rodata_B0[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0xBC */ /* s32 lbl_1_rodata_BC[3] = { 0x00000000, 0x43340000, 0x00000000 }; */
/* 0xC8 */ /* float lbl_1_rodata_C8 = 0.0f; */
/* 0xCC */ /* float lbl_1_rodata_CC[4] = { 4.0f, 50.0f, 0.0f, 0.0f }; */
/* 0xDC */ /* float lbl_1_rodata_DC = 1.5f; */
/* 0xE0 */ /* float lbl_1_rodata_E0 = 2.0f; */
/* 0xE4 */ /* float lbl_1_rodata_E4 = 1.0f; */

/* --- .data --- */
/* 0x140 */ unsigned int lbl_1_data_140[13][7] = { 0x008C0000, 0x008C0001, 0x008C0002, 0x008C0072, 0x008C0073, 0x008C0006, 0x008C0031, 0x00330000, 0x00330001, 0x00330002, 0x00330072, 0x00330073, 0x00330006, 0x00330031, 0x00B70000, 0x00B70001, 0x00B70002, 0x00B70072, 0x00B70073, 0x00B70006, 0x00B70031, 0x00ED0000, 0x00ED0001, 0x00ED0002, 0x00ED0072, 0x00ED0073, 0x00ED0006, 0x00ED0031, 0x00E60000, 0x00E60001, 0x00E60002, 0x00E60072, 0x00E60073, 0x00E60006, 0x00E60031, 0x00170000, 0x00170001, 0x00170002, 0x00170072, 0x00170073, 0x00170006, 0x00170031, 0x00E00000, 0x00E00001, 0x00E00002, 0x00E00072, 0x00E00073, 0x00E00006, 0x00E00031, 0x002D0000, 0x002D0001, 0x002D0002, 0x002D0072, 0x002D0073, 0x002D0006, 0x002D0031, 0x00C90000, 0x00C90001, 0x00C90002, 0x00C90072, 0x00C90073, 0x00C90006, 0x00C90031, 0x00B00000, 0x00B00001, 0x00B00002, 0x00B00072, 0x00B00073, 0x00B00006, 0x00B00031, 0x008C0000, 0x008C0001, 0x008C0002, 0x008C0072, 0x008C0073, 0x008C0006, 0x008C0031, 0x008C0000, 0x008C0001, 0x008C0002, 0x008C0072, 0x008C0073, 0x008C0006, 0x008C0031, 0x008C0000, 0x008C0001, 0x008C0002, 0x008C0072, 0x008C0073, 0x008C0006, 0x008C0031 };
/* 0x2AC */ float lbl_1_data_2AC[16] = { -113.176f, -88.14909f, -52.90621f, -16.67476f, 26.3934f, 69.22196f, 101.1403f, 127.9546f, 151.4606f, 171.4761f, -172.7292f, -161.7649f, -155.779f, -155.779f, -155.779f, -155.779f };
/* 0x2EC */ float lbl_1_data_2EC[12] = { -154.6163f, -159.2135f, -172.7292f, 165.2307f, 136.154f, 101.1403f, 55.91046f, -3.053231f, -52.90621f, -100.0638f, -100.0638f, -100.0638f };

/* --- functions (reference order) --- */
/* 303 insns */
void fn_1_3DC8(M510_PLAYERMODEL *pm, s16 no, M510_PLAYER *player)
{
    u16 i;
    M510_WORK *work;
    M510_CAMERA *camera;
    OMOBJ *obj;
    HU3DMODELID mdlId;
    char *hook;

    work = player->unk000;
    camera = &work->unk2474;
    obj = NULL;
    memset(pm, 0, sizeof(M510_PLAYERMODEL));
    pm->unk000 = player;
    pm->unk008 = no;
    pm->unk010 = GwPlayerConf[pm->unk008].grp;
    pm->unk00C = GwPlayerConf[pm->unk008].charNo;
    obj = omAddObjEx(work->unk000, 100, 1, 7, -1, NULL);
    pm->unk014 = obj;
    pm->unk0FC = 0;
    mdlId = CharModelCreate(pm->unk00C, 1);
    pm->unk018 = mdlId;
    obj->mdlId[0] = mdlId;
    Hu3DModelShadowSet(mdlId);
    CharModelStepFxSet(pm->unk00C, 0);
    CharEffectLayerSet(4);
    for (i = 0; i < 7; i++) {
        obj->mtnId[i] = CharMotionCreate(pm->unk00C, lbl_1_data_140[pm->unk00C][i]);
        CharMotionSet(pm->unk00C, obj->mtnId[i]);
    }
    Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(mdlId, 3);
    Hu3DMotionSet(mdlId, obj->mtnId[0]);
    Hu3DModelCameraSet(mdlId, camera->unk004);
    Hu3DMotionShiftSet(mdlId, pm->unk014->mtnId[3], 0.0f, 4.0f, 0);
    pm->unk0B2 = pm->unk0B0 = 3;
    pm->unk0B4 = 1;
    pm->unk0D0 = &Hu3DData[mdlId].pos;
    pm->unk0D4 = &Hu3DData[mdlId].rot;
    {
        HuVecF pos = { 0.0f, 0.0f, 0.0f };
        HuVecF *posP = &pos;
        pm->unk0B8 = *posP;
    }
    {
        HuVecF rot = { 0.0f, 180.0f, 0.0f };
        HuVecF *rotP = &rot;
        pm->unk0C4 = *rotP;
    }
    omSetTra(obj, pm->unk0B8.x, pm->unk0B8.y, pm->unk0B8.z);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(0x440002, HU_MEMNUM_OVL, HEAP_MODEL));
    pm->unk0D8 = mdlId;
    Hu3DModelPosSet(mdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(mdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(mdlId, camera->unk004);
    Hu3DModelLayerSet(mdlId, 3);
    Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelShadowSet(mdlId);
    hook = CharModelItemHookGet(pm->unk00C, 1, 1);
    Hu3DModelHookSet(pm->unk018, hook, mdlId);
    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(0x44000D, HU_MEMNUM_OVL, HEAP_MODEL));
    pm->unk108 = mdlId;
    Hu3DModelPosSet(mdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(mdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(mdlId, camera->unk004);
    Hu3DModelLayerSet(mdlId, 3);
    Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
    pm->unk10A = Hu3DJointMotion(mdlId, HuDataSelHeapReadNum(0x44001E, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(mdlId, pm->unk10A);
    Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_LOOP);
    fn_1_8184(&pm->unk02C, no, pm);
}

/* 41 insns */
void fn_1_4284(M510_PLAYERMODEL *pm)
{
    M510_PLAYER *player;
    M510_WORK *work;

    player = pm->unk000;
    work = player->unk000;
    Hu3DMotionKill(pm->unk10A);
    Hu3DModelKill(pm->unk108);
    Hu3DModelHookReset(pm->unk018);
    Hu3DModelKill(pm->unk0D8);
    fn_1_81F4(&pm->unk02C);
    if (pm->unk014) {
        CharModelKill(pm->unk00C);
        omDelObjEx(work->unk000, pm->unk014);
        pm->unk014 = NULL;
    }
    memset(pm, 0, sizeof(M510_PLAYERMODEL));
}

/* 274 insns */
s32 fn_1_4328(M510_PLAYERMODEL *pm)
{
    M510_PAD *pad;
    M510_PLAYER *player;
    M510_WORK *work;
    HU3DMODELID mdlId;
    s32 dbgI;
    u32 attr;
    float maxTime;
    float dbgF;

    pad = &pm->unk02C;
    player = pm->unk000;
    work = player->unk000;
    if (work->unk00C >= 7) {
        return 0;
    }
    pad->unk070 = pad->unk074 = pad->unk078 = pad->unk079 = 0;
    if (pm->unk0FC != 0) {
        fn_1_8234(pad);
    }
    /*
     * Compile-time-dead block. Retail pools a { 50.0f, 0.0f, 0.0f } vector
     * literal here (.rodata 0x20, referenced by no code) and saves r26 and f31
     * without using them: an s32 and a float local whose only uses were in
     * code CodeWarrior dropped. This reproduces both; it never runs.
     */
    if (0) {
        HuVecF ofs = { 50.0f, 0.0f, 0.0f };
        dbgF = ofs.x;
        dbgI = 0;
        Hu3DModelPosSet(dbgI, dbgF, dbgF, dbgF);
        Hu3DModelPosSet(dbgI, dbgF, dbgF, dbgF);
    }
    switch (pm->unk004) {
        case 0:
            if ((pm->unk02C.unk074 & 0x100) || pm->unk100 != 0) {
                pm->unk0B0 = pm->unk0B2 = 4;
                Hu3DModelAttrReset(pm->unk018, HU3D_MOTATTR_LOOP);
                Hu3DMotionSet(pm->unk018, pm->unk014->mtnId[4]);
                Hu3DMotionSpeedSet(pm->unk018, 1.5f);
                if (pm->unk008 == 0) {
                    fn_1_5B4(0x693);
                }
                else if (pm->unk008 == 1) {
                    fn_1_5B4(0x694);
                }
                else if (pm->unk008 == 2) {
                    fn_1_5B4(0x695);
                }
                else {
                    fn_1_5B4(0x696);
                }
                pm->unk0B4 = 0;
                pm->unk006 = 0;
                pm->unk004 = 1;
                pm->unk100 = 0;
            }
            break;
        case 1:
            fn_1_4770(pm);
            pm->unk006++;
            maxTime = Hu3DMotionMaxTimeGet(pm->unk018);
            if (Hu3DMotionTimeGet(pm->unk018) >= maxTime) {
                Hu3DMotionSpeedSet(pm->unk018, 2.0f);
                Hu3DModelAttrSet(pm->unk018, HU3D_MOTATTR_REV);
                pm->unk006 = 0;
                pm->unk004 = 2;
            }
            break;
        case 2:
            fn_1_4770(pm);
            pm->unk006++;
            if (Hu3DMotionTimeGet(pm->unk018) <= 0.0f) {
                pm->unk0B2 = 3;
                Hu3DMotionSpeedSet(pm->unk018, 1.0f);
                Hu3DMotionSet(pm->unk018, pm->unk014->mtnId[3]);
                Hu3DModelAttrReset(pm->unk018, HU3D_MOTATTR_REV);
                pm->unk0DC = pm->unk0E0 = 0.0f;
                pm->unk0B4 = 1;
                pm->unk006 = 0;
                pm->unk004 = 0;
            }
            break;
        case 3:
            if (pm->unk006-- <= 0) {
                pm->unk006 = 0;
                pm->unk004 = 0;
            }
            break;
    }
    /* pans are constants 0x28/0x38/0x48/0x58 by player number: always 0..127 */
    if (pm->unk008 == 0) {
        CharModelVoicePanSet(pm->unk00C, 40);
    }
    else if (pm->unk008 == 1) {
        CharModelVoicePanSet(pm->unk00C, 56);
    }
    else if (pm->unk008 == 2) {
        CharModelVoicePanSet(pm->unk00C, 72);
    }
    else {
        CharModelVoicePanSet(pm->unk00C, 88);
    }
    mdlId = pm->unk018;
    if (pm->unk0B0 != pm->unk0B2 && Hu3DMotionShiftIDGet(mdlId) < 0) {
        pm->unk0B0 = pm->unk0B2;
        Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_LOOP);
        if (pm->unk0B4 != 0) {
            attr = HU3D_MOTATTR_LOOP;
        }
        else {
            attr = 0;
        }
        Hu3DMotionShiftSet(mdlId, pm->unk014->mtnId[pm->unk0B0], 0.0f, 4.0f, attr);
    }
    omSetTra(pm->unk014, pm->unk0B8.x, pm->unk0B8.y, pm->unk0B8.z);
    omSetRot(pm->unk014, pm->unk0C4.x, pm->unk0C4.y, pm->unk0C4.z);
    if (pm->unk10C != 0) {
        maxTime = Hu3DMotionMaxTimeGet(pm->unk108);
        if (Hu3DMotionTimeGet(pm->unk108) >= maxTime) {
            Hu3DModelAttrSet(pm->unk108, HU3D_ATTR_DISPOFF);
            pm->unk10C = 0;
        }
    }
    return 0;
}

/* 21 insns */
void fn_1_4770(M510_PLAYERMODEL *pm)
{
    pm->unk0E0 = pm->unk0DC;
    if (pm->unk004 == 1) {
        pm->unk0DC = lbl_1_data_2AC[pm->unk006];
    }
    else {
        pm->unk0DC = lbl_1_data_2EC[pm->unk006];
    }
}
