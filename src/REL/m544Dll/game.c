/*
 * m544dll/game.c -- the grab duel: the sequence steps, the item hook, the
 * duellists' reactions, the thrown items and the computer duellists. Written
 * from the reference assembly, functions in reference order; line ranges are
 * into build/mp5-asm/m544Dll/asm/REL/m544Dll/game.s.
 */

#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/audio.h"
#include "game/frand.h"
#include "game/pad.h"
#include "game/flag.h"
#include "game/mg/seqman.h"
#include "game/mg/timer.h"

#include "REL/m544Dll/m544.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

void fn_1_5574(void);
void fn_1_5B0C(void);
void fn_1_5C48(void);
s16 fn_1_5E38(void);
s16 fn_1_5EFC(s16 player);
s16 fn_1_614C(s16 player);
s16 fn_1_6274(s16 player);
s16 fn_1_65EC(void);
s16 fn_1_6B64(void);
void fn_1_6E9C(s16 itemNo);
s16 fn_1_6F38(s16 player, s16 hideF);
s16 fn_1_7288(void);
s16 fn_1_753C(void);
s32 fn_1_7F30(void);
s32 fn_1_817C(void);
void fn_1_8710(int player, int slot);
void fn_1_8E98(int slot, int type);
void fn_1_91B4(int slot, int time);
s32 fn_1_9364(int slot, int loserF);
void fn_1_95D8(int slotA, int slotB);
void fn_1_9798(s16 player);
s16 fn_1_9C84(s16 player);

/* --- .data: the sprintf strings, fn_1_6274's jumptable, then lbl_1_data_3EC --- */

/* --- .bss (CodeWarrior lays it out in reverse definition order) --- */

M544_WORK *lbl_1_bss_914;           /* set by fn_1_4328 */
M544_ITEM lbl_1_bss_8D8[10];
M544_THROW lbl_1_bss_828[4];
HU3DMODELID lbl_1_bss_826;          /* the dust particle model */
HU3DMODELID lbl_1_bss_824;          /* the flash particle model */
M544_PARTICLEPARAM *lbl_1_bss_820;  /* one spawn parameter per dust particle */

/*
 * asm 9-726, 696 insns. Init step: the state, the ten items (decoys get likelier
 * later), the computer duellists, the item, hand and throw models, then the
 * particles and the timer.
 */
s32 fn_1_4328(M544_WORK *work)
{
    s32 result = 1;
    s16 decoyMax[10] = { 5, 6, 7, 8, 9, 9, 9, 9, 9, 9 };
    s16 i;
    s16 j;
    s16 no;
    s16 r;

    memset(&lbl_1_bss_D0, 0, sizeof(M544_GAME));
    memset(lbl_1_bss_80, 0, sizeof(lbl_1_bss_80));
    memset(&lbl_1_bss_C, 0, sizeof(M544_HOOK));
    for(i=0; i<6; i++) {
        lbl_1_bss_D0.seF[i] = -1;
    }
    lbl_1_bss_914 = work;
    for(i=0; i<2; i++) {
        lbl_1_bss_80[i].scale.x = 1.0f;
        lbl_1_bss_80[i].scale.y = 1.0f;
        lbl_1_bss_80[i].scale.z = 1.0f;
        lbl_1_bss_80[i].hookName = CharModelItemHookGet(lbl_1_bss_914->chr[i].charNo, 1, 0);
    }
    sprintf(lbl_1_bss_C.name, "%s", "g003m1-itemhook_R");
    lbl_1_bss_C.tpLvl = 1.0f;
    for(i=0; i<10; i++) {
        lbl_1_bss_8D8[i].waitTime = (frandmod(45)+5)*6;
        lbl_1_bss_8D8[i].hangTime = (frandmod(15)+5)*6;
        r = frandmod(11);
        if(i >= 10 || r <= decoyMax[i]) {
            lbl_1_bss_8D8[i].kind = frandmod(6);
        } else {
            lbl_1_bss_8D8[i].kind = frandmod(4)+6;
        }
    }
    for(i=0; i<2; i++) {
        if(lbl_1_bss_914->chr[i].dif != 0) {
            fn_1_9798(i);
        }
    }
    for(i=0, j=0, no=0; i<10; i++, j++, no++) {
        lbl_1_bss_914->models[no].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_914->stageDataTbl[j], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_914->models[no].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_914->models[no].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_914->models[no].modelId, 2);
        Hu3DModelShadowSet(lbl_1_bss_914->models[no].modelId);
        lbl_1_bss_914->models[no].pos.x = 0.0f;
        lbl_1_bss_914->models[no].pos.y = 0.0f;
        lbl_1_bss_914->models[no].pos.z = 0.0f;
        lbl_1_bss_914->models[no].rot.x = 0.0f;
        lbl_1_bss_914->models[no].rot.y = 0.0f;
        lbl_1_bss_914->models[no].rot.z = -50.0f;
    }
    Hu3DModelAttrReset(lbl_1_bss_914->models[lbl_1_bss_8D8[0].kind].modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelHookSet(lbl_1_bss_914->models[34].modelId, lbl_1_bss_C.name, lbl_1_bss_914->models[lbl_1_bss_8D8[0].kind].modelId);
    for(i=0, no=10; i<2; i++, no++) {
        lbl_1_bss_914->models[no].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_914->stageDataTbl[10], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_914->models[no].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_914->models[no].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_914->models[no].modelId, 0);
        Hu3DModelShadowSet(lbl_1_bss_914->models[no].modelId);
        Hu3DModelAttrReset(lbl_1_bss_914->models[no].modelId, HU3D_ATTR_DISPOFF);
        lbl_1_bss_914->models[no].pos.x = 0.0f;
        lbl_1_bss_914->models[no].pos.y = 0.0f;
        lbl_1_bss_914->models[no].pos.z = 0.0f;
        lbl_1_bss_914->models[no].rot.x = 0.0f;
        lbl_1_bss_914->models[no].rot.y = 0.0f;
        lbl_1_bss_914->models[no].rot.z = 0.0f;
        Hu3DModelHookSet(lbl_1_bss_914->models[i+32].modelId, lbl_1_bss_80[i].hookName, lbl_1_bss_914->models[no].modelId);
    }
    for(i=0; i<4; i++) {
        lbl_1_bss_914->models[i+12].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_914->stageDataTbl[11], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_914->models[i+12].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_914->models[i+12].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_914->models[i+12].modelId, 0);
        Hu3DMotionSpeedSet(lbl_1_bss_914->models[i+12].modelId, 0.0f);
        Hu3DMotionTimeSet(lbl_1_bss_914->models[i+12].modelId, 0.0f);
    }
    /* Retail sets the motion of model i+12 (always 16 here) instead of model no. */
    for(no=16; no<=19; no++) {
        lbl_1_bss_914->models[no].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_914->stageDataTbl[12], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_914->models[no].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_914->models[no].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_914->models[no].modelId, 0);
        Hu3DMotionSpeedSet(lbl_1_bss_914->models[i+12].modelId, 0.0f);
        Hu3DMotionTimeSet(lbl_1_bss_914->models[i+12].modelId, 0.0f);
    }
    fn_1_2330();
    fn_1_34D0();
    fn_1_5C48();
    lbl_1_bss_D0.timer2 = fn_1_1A1C(0, 5, 0, 292.0f, 64.0f);
    return result;
}

/* asm 729-743, 13 insns. Fade-in step: the camera pan. Never done by itself; mode 2's delay ends it. */
s32 fn_1_4E08(void)
{
    s32 result;

    result = 0;
    fn_1_7F30();
    fn_1_5C48();
    return result;
}

/* asm 746-778, 30 insns. Start step: the music. */
s32 fn_1_4E3C(void)
{
    s32 result;

    result = 1;
    if(lbl_1_bss_D0.bgmF == 0) {
        fn_1_3F28();
        lbl_1_bss_D0.bgmF = 1;
    }
    lbl_1_bss_D0.mode = 0;
    lbl_1_bss_D0.timer = 0;
    fn_1_5C48();
    return result;
}

/* asm 781-911, 121 insns. Main step: items until someone reacts, the reactions, then the result. */
s32 fn_1_4EB4(void)
{
    s32 result;
    s16 done;
    s32 no;

    result = 0;
    done = 0;
    switch(lbl_1_bss_D0.mode) {
        case 0:
            done += fn_1_6B64();
            done += fn_1_65EC();
            if(done != 0) {
                fn_1_1AE4(lbl_1_bss_D0.timer2);
                lbl_1_bss_D0.mode++;
            }
            break;

        case 1:
            done = fn_1_5E38();
            if(done != 0) {
                lbl_1_bss_D0.mode++;
            }
            break;

        case 2:
            lbl_1_bss_D0.mode++;
            break;

        case 3:
            if(lbl_1_bss_D0.result != 0) {
                MgSeqWinnerSet(lbl_1_bss_914->chr[lbl_1_bss_D0.result & 1].charNo, CHARNO_NONE, CHARNO_NONE, CHARNO_NONE);
                no = lbl_1_bss_914->chr[lbl_1_bss_D0.result & 1].no;
                if(!_CheckFlag(FLAG_MG_PRACTICE)) {
                    GwPlayer[no].mgCoinBonus = 10;
                }
            } else {
                MgSeqWinnerSet(CHARNO_NONE, CHARNO_NONE, CHARNO_NONE, CHARNO_NONE);
            }
            lbl_1_bss_D0.bgmF = 0;
            result = 1;
            break;
    }
    fn_1_5C48();
    return result;
}

/* asm 914-949, 33 insns. Finish step: fade the music, drop the item and the held ones. */
s32 fn_1_5098(void)
{
    s32 result;

    result = 0;
    if(lbl_1_bss_D0.bgmF == 0) {
        fn_1_3F58(1, 100);
        lbl_1_bss_D0.bgmF = 1;
    }
    lbl_1_bss_D0.timer = 0;
    lbl_1_bss_D0.mode = 0;
    fn_1_753C();
    fn_1_5C48();
    return result;
}

/* asm 952-968, 15 insns. Pre-winner step. */
s16 fn_1_511C(void)
{
    s16 result;

    result = 0;
    result = fn_1_817C();
    fn_1_753C();
    fn_1_5C48();
    return result;
}

/* asm 971-1217, 239 insns. Winner step: the poses, then turn the duellists to face the camera. */
s32 fn_1_5158(void)
{
    DS_PLAYER *pl;
    s32 result;
    float speed;

    result = 0;
    if(lbl_1_bss_914->mode[0] == 0) {
        if(lbl_1_bss_D0.result != 0) {
            CharModelVoicePanSet(lbl_1_bss_914->chr[lbl_1_bss_D0.result & 1].charNo, 64);
            CharModelFxFlagSet(lbl_1_bss_914->chr[lbl_1_bss_D0.result & 1].charNo, 1);
            pl = &lbl_1_bss_914->player[lbl_1_bss_D0.result & 1];
            pl->motNo = 5;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            pl = &lbl_1_bss_914->player[(lbl_1_bss_D0.result & 2) >> 1];
            pl->motNo = 6;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
        } else {
            pl = &lbl_1_bss_914->player[0];
            pl->motNo = 6;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            pl = &lbl_1_bss_914->player[1];
            pl->motNo = 6;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            CharModelVoicePanSet(lbl_1_bss_914->chr[0].charNo, 48);
            CharModelVoicePanSet(lbl_1_bss_914->chr[1].charNo, 80);
            CharLoseVoicePlay(lbl_1_bss_914->chr[0].charNo, lbl_1_bss_914->chr[1].charNo, CHARNO_NONE, CHARNO_NONE);
        }
        lbl_1_bss_914->mode[0] = 1;
    }
    speed = 10.0f;
    if(lbl_1_bss_D0.result == 0) {
        fn_1_18E8(&lbl_1_bss_914->models[32].rot.y, speed, 90.0f, 0.0f);
        fn_1_18E8(&lbl_1_bss_914->models[33].rot.y, speed, -90.0f, 0.0f);
    } else if(lbl_1_bss_D0.result & 1) {
        fn_1_18E8(&lbl_1_bss_914->models[33].rot.y, speed, -90.0f, -30.0f);
    } else {
        fn_1_18E8(&lbl_1_bss_914->models[32].rot.y, speed, 90.0f, 29.0f);
    }
    fn_1_5C48();
    return result;
}

/* asm 1220-1233, 12 insns. Fade-out step. */
s32 fn_1_5514(void)
{
    s32 result;

    result = 1;
    fn_1_5C48();
    return result;
}

/* asm 1236-1249, 12 insns. Close step. */
s32 fn_1_5544(void)
{
    s32 result;

    result = 1;
    fn_1_4308();
    return result;
}

/*
 * asm 1252-1619, 358 insns. The item on the actor's hook: hang it while the
 * actor idles, carry it at the hook's matrix while it dangles, let go once
 * dropF is set.
 */
void fn_1_5574(void)
{
    DS_PLAYER *pl;
    HU3DMODEL *model;

    pl = &lbl_1_bss_914->player[2];
    Hu3DModelObjMtxGet(lbl_1_bss_914->models[34].modelId, lbl_1_bss_C.name, lbl_1_bss_C.mtx);
    model = &Hu3DData[lbl_1_bss_914->models[lbl_1_bss_8D8[lbl_1_bss_C.itemNo].kind].modelId];
    if(pl->motNo == 0) {
        model->rot.z = -50.0f;
        if(pl->motNo == pl->motNoCur && 1.0f == pl->time) {
            Hu3DModelHookSet(lbl_1_bss_914->models[34].modelId, lbl_1_bss_C.name, lbl_1_bss_914->models[lbl_1_bss_8D8[lbl_1_bss_C.itemNo].kind].modelId);
            lbl_1_bss_C.hookMode = 0;
        }
    }
    if(pl->motNo == 1) {
        if(pl->motNo != pl->motNoCur) {
            Hu3DModelHookObjReset(lbl_1_bss_914->models[34].modelId, lbl_1_bss_C.name);
        }
        lbl_1_bss_C.hookMode = 1;
    }
    if(lbl_1_bss_C.dropF == 1) {
        lbl_1_bss_C.hookMode = 2;
    }
    switch(lbl_1_bss_C.hookMode) {
        case 0:
            PSMTXIdentity(model->mtx);
            lbl_1_bss_914->models[lbl_1_bss_8D8[lbl_1_bss_C.itemNo].kind].pos.x = 0.0f;
            lbl_1_bss_914->models[lbl_1_bss_8D8[lbl_1_bss_C.itemNo].kind].pos.y = 0.0f;
            lbl_1_bss_914->models[lbl_1_bss_8D8[lbl_1_bss_C.itemNo].kind].pos.z = 0.0f;
            lbl_1_bss_914->models[lbl_1_bss_8D8[lbl_1_bss_C.itemNo].kind].rot.x = 0.0f;
            lbl_1_bss_914->models[lbl_1_bss_8D8[lbl_1_bss_C.itemNo].kind].rot.y = 0.0f;
            lbl_1_bss_914->models[lbl_1_bss_8D8[lbl_1_bss_C.itemNo].kind].rot.z = -50.0f;
            break;

        case 1:
            PSMTXIdentity(model->mtx);
            lbl_1_bss_914->models[lbl_1_bss_8D8[lbl_1_bss_C.itemNo].kind].pos.x = lbl_1_bss_C.mtx[0][3];
            lbl_1_bss_914->models[lbl_1_bss_8D8[lbl_1_bss_C.itemNo].kind].pos.y = lbl_1_bss_C.mtx[1][3];
            lbl_1_bss_914->models[lbl_1_bss_8D8[lbl_1_bss_C.itemNo].kind].pos.z = lbl_1_bss_C.mtx[2][3];
            lbl_1_bss_914->models[lbl_1_bss_8D8[lbl_1_bss_C.itemNo].kind].rot.x = -7.5f*(1.0f+pl->time);
            lbl_1_bss_914->models[lbl_1_bss_8D8[lbl_1_bss_C.itemNo].kind].rot.y = 0.0f;
            lbl_1_bss_914->models[lbl_1_bss_8D8[lbl_1_bss_C.itemNo].kind].rot.z = 0.0f;
            break;

        case 2:
            break;
    }
}

/* asm 1622-1704, 79 insns. Push every model's position and rotation at Hu3D; unreferenced, inlined into fn_1_5C48. */
void fn_1_5B0C(void)
{
    s16 i;

    for(i=0; i<M544_MODEL_MAX; i++) {
        Hu3DModelPosSet(lbl_1_bss_914->models[i].modelId, lbl_1_bss_914->models[i].pos.x, lbl_1_bss_914->models[i].pos.y, lbl_1_bss_914->models[i].pos.z);
        Hu3DModelRotSet(lbl_1_bss_914->models[i].modelId, lbl_1_bss_914->models[i].rot.x, lbl_1_bss_914->models[i].rot.y, lbl_1_bss_914->models[i].rot.z);
    }
}

/* asm 1707-1834, 124 insns. Every step ends here: the hook, the models, the camera, the light and shadow. */
void fn_1_5C48(void)
{
    fn_1_5574();
    fn_1_5B0C();
    fn_1_9C0(0);
    lbl_1_bss_4->rot.x = lbl_1_bss_8->rot.x;
    lbl_1_bss_4->rot.y = lbl_1_bss_8->rot.y;
    lbl_1_bss_4->dist = lbl_1_bss_8->zoom;
    lbl_1_bss_4->target.x = lbl_1_bss_8->center.x;
    lbl_1_bss_4->target.z = lbl_1_bss_8->center.y;
    fn_1_1168();
    fn_1_1570();
}

/* asm 1837-1894, 49 insns. Run both duellists' reactions; done when both are. */
s16 fn_1_5E38(void)
{
    s16 result;
    s16 i;

    result = 1;
    for(i=0; i<2; i++) {
        switch(lbl_1_bss_80[i].result) {
            case 0:
                break;

            case 1:
                result *= fn_1_5EFC(i);
                break;

            case 2:
                result *= fn_1_614C(i);
                break;

            case 3:
                result *= fn_1_6274(i);
                break;
        }
    }
    return result;
}

/* asm 1897-2054, 148 insns. The winner grabs the item and throws it at the other duellist. */
s16 fn_1_5EFC(s16 player)
{
    DS_PLAYER *pl;
    s16 result;

    pl = &lbl_1_bss_914->player[player];
    result = 0;
    switch(lbl_1_bss_80[player].mode) {
        case 0:
            pl->motNo = 2;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            lbl_1_bss_80[player].mode++;
            break;

        case 1:
            if(pl->endF != 0) {
                if(lbl_1_bss_80[player].throwCnt >= 1) {
                    lbl_1_bss_80[player].mode++;
                } else {
                    fn_1_8710(player, lbl_1_bss_80[player].throwCnt);
                    pl->motNo = 3;
                    pl->speed = 1.0f;
                    pl->time = 0.0f;
                    pl->attr = 0;
                    pl->attrReset = 0;
                    fn_1_4098(2, 127, (player*32)+48);
                }
                lbl_1_bss_80[player].throwCnt++;
            }
            break;

        case 2:
            if(lbl_1_bss_80[player].timer++ > 60) {
                lbl_1_bss_80[player].timer = 0;
                lbl_1_bss_80[player].mode++;
            }
            break;

        case 3:
            result = 1;
            break;
    }
    return result;
}

/* asm 2057-2137, 74 insns. The duellist who was beaten to it: a sound once the thrown item shows. */
s16 fn_1_614C(s16 player)
{
    DS_PLAYER *pl;
    s16 result;
    s16 i;

    pl = &lbl_1_bss_914->player[player];
    result = 0;
    if(lbl_1_bss_80[player].hitF == 0) {
        for(i=16; i<=19; i++) {
            if(!(Hu3DModelAttrGet(lbl_1_bss_914->models[i].modelId) & HU3D_ATTR_DISPOFF)) {
                fn_1_4098(3, 127, (player*32)+48);
                lbl_1_bss_80[player].hitF = 1;
            }
        }
    }
    if(lbl_1_bss_80[player].timer++ > 60) {
        result = 1;
    }
    return result;
}

/* asm 2140-2376, 222 insns. The fooled duellist: grab at nothing, a flash, then have something thrown at them. */
s16 fn_1_6274(s16 player)
{
    DS_PLAYER *pl;
    s16 result;

    pl = &lbl_1_bss_914->player[player];
    result = 0;
    switch(lbl_1_bss_80[player].mode) {
        case 0:
            pl->motNo = 2;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            lbl_1_bss_80[player].mode++;
            break;

        case 1:
            if(pl->endF != 0) {
                lbl_1_bss_80[player].mode++;
            }
            break;

        case 2:
            if(lbl_1_bss_80[player].timer++ > 60) {
                fn_1_35DC(player);
                lbl_1_bss_80[player].timer = 0;
                lbl_1_bss_80[player].mode++;
            }
            break;

        case 3:
            if(lbl_1_bss_D0.flashF == 0) {
                fn_1_35DC(player);
            }
            if(lbl_1_bss_80[player].timer++ > 180 || lbl_1_bss_D0.flashF != 0) {
                lbl_1_bss_80[player].timer = 0;
                lbl_1_bss_80[player].mode++;
            }
            break;

        case 4:
            if(lbl_1_bss_80[player].timer++ > 60) {
                fn_1_4098(4, 127, (player*32)+48);
                lbl_1_bss_80[player].timer = 0;
                lbl_1_bss_80[player].mode++;
            }
            break;

        case 5:
            if(lbl_1_bss_80[0].result == 3 && lbl_1_bss_80[1].result == 3) {
                if(player == 0) {
                    fn_1_95D8(1, 2);
                }
            } else if(player != 0) {
                fn_1_95D8(-1, 1);
            } else {
                fn_1_95D8(1, -1);
            }
            lbl_1_bss_80[player].mode++;
            break;

        case 6:
            if(lbl_1_bss_80[player].timer++ > 60) {
                result = 1;
            }
            break;
    }
    return result;
}

/* --- .data --- */

/* A computer duellist's odds per difficulty: timer min and max, then the fooled, early and late percentiles. */
s16 lbl_1_data_3EC[4][5] = {
    { 70, 90, 85, 70, 90 },
    { 50, 70, 90, 80, 95 },
    { 35, 45, 95, 90, 100 },
    { 30, 35, 100, 100, 100 }
};

/*
 * asm 2379-2746, 350 insns. Input: each duellist's button this frame (a
 * human's A/B/X/Y/L/R, or the computer's). On a real item the first right
 * button wins; a wrong button or any button on a decoy fools that duellist.
 * Two at once are decided with frandmod(2).
 */
s16 fn_1_65EC(void)
{
    s16 press;
    s16 player;
    s16 result;

    result = 0;
    for(player=1; player>=0; player--) {
        press = 0;
        if(lbl_1_bss_914->chr[player].dif == 0) {
            if(lbl_1_bss_914->chr[player].btnDown & PAD_BUTTON_A) {
                press += 128;
            }
            if(lbl_1_bss_914->chr[player].btnDown & PAD_BUTTON_B) {
                press += 129;
            }
            if(lbl_1_bss_914->chr[player].btnDown & PAD_BUTTON_X) {
                press += 130;
            }
            if(lbl_1_bss_914->chr[player].btnDown & PAD_BUTTON_Y) {
                press += 131;
            }
            if(lbl_1_bss_914->chr[player].btnDown & PAD_TRIGGER_L) {
                press += 132;
            }
            if(lbl_1_bss_914->chr[player].btnDown & PAD_TRIGGER_R) {
                press += 133;
            }
        } else {
            press = fn_1_9C84(player);
        }
        if(press == 0) {
            continue;
        }
        result = 1;
        if(lbl_1_bss_D0.realF != 0) {
            press &= 0x7F;
            if(press == lbl_1_bss_8D8[lbl_1_bss_C.itemNo].kind) {
                if(lbl_1_bss_D0.result & 1) {
                    lbl_1_bss_D0.result = 0;
                    press = frandmod(2);
                    lbl_1_bss_D0.result = press | ((press^1) << 1);
                    lbl_1_bss_80[lbl_1_bss_D0.result & 1].result = 1;
                    lbl_1_bss_80[(lbl_1_bss_D0.result & 2) >> 1].result = 2;
                } else {
                    lbl_1_bss_80[player].result = 1;
                    lbl_1_bss_80[player^1].result = 2;
                    lbl_1_bss_D0.result |= player;
                    lbl_1_bss_D0.result |= (player^1) << 1;
                }
            } else if(press != lbl_1_bss_8D8[lbl_1_bss_C.itemNo].kind) {
                if(lbl_1_bss_80[player].result == 0) {
                    lbl_1_bss_80[player].result = 3;
                }
                if(lbl_1_bss_D0.result & 2) {
                    lbl_1_bss_D0.result = 0;
                    press = frandmod(2);
                    lbl_1_bss_D0.result = press | ((press^1) << 1);
                    lbl_1_bss_80[lbl_1_bss_D0.result & 1].result = 0;
                    lbl_1_bss_80[(lbl_1_bss_D0.result & 2) >> 1].result = 3;
                } else {
                    lbl_1_bss_D0.result |= player << 1;
                    lbl_1_bss_D0.result |= player^1;
                }
            }
        } else if(lbl_1_bss_D0.result & 2) {
            lbl_1_bss_D0.result = 0;
            press = frandmod(2);
            lbl_1_bss_D0.result = press | ((press^1) << 1);
            lbl_1_bss_80[lbl_1_bss_D0.result & 1].result = 0;
            lbl_1_bss_80[(lbl_1_bss_D0.result & 2) >> 1].result = 3;
        } else {
            lbl_1_bss_80[player].result = 3;
            lbl_1_bss_80[player^1].result = 0;
            lbl_1_bss_D0.result |= player << 1;
            lbl_1_bss_D0.result |= player^1;
        }
    }
    return result;
}

/*
 * asm 2749-2964, 206 insns. The item hook: wait, lower the item, dangle it
 * (a real item for up to 600 frames, then nobody wins), reel in and bring the
 * next.
 */
s16 fn_1_6B64(void)
{
    DS_PLAYER *pl;
    s16 result;

    pl = &lbl_1_bss_914->player[2];
    result = 0;
    switch(lbl_1_bss_C.mode) {
        case 0:
            if(lbl_1_bss_C.timer++ >= lbl_1_bss_8D8[lbl_1_bss_C.itemNo].waitTime) {
                if(lbl_1_bss_8D8[lbl_1_bss_C.itemNo].kind < 6) {
                    lbl_1_bss_D0.realF = 1;
                }
                pl->motNo = 1;
                pl->speed = 1.0f;
                pl->time = 0.0f;
                pl->attr = 0;
                pl->attrReset = 0x40000005;
                fn_1_4020(1);
                lbl_1_bss_C.timer = 0;
                lbl_1_bss_C.timer2 = 0;
                lbl_1_bss_C.mode++;
            }
            break;

        case 1:
            if(lbl_1_bss_D0.realF != 0) {
                if(lbl_1_bss_C.timer2++ >= 600) {
                    lbl_1_bss_80[0].result = 0;
                    lbl_1_bss_80[1].result = 0;
                    lbl_1_bss_D0.result = 0;
                    lbl_1_bss_C.mode = 3;
                    result = 1;
                }
                if(lbl_1_bss_C.timer2 == 300) {
                    fn_1_1A90(lbl_1_bss_D0.timer2);
                }
            } else if(lbl_1_bss_C.timer2++ >= lbl_1_bss_8D8[lbl_1_bss_C.itemNo].hangTime) {
                pl->motNo = 1;
                pl->speed = 1.0f;
                pl->time = 11.0f;
                pl->attr = 0x40000004;
                pl->attrReset = 0;
                lbl_1_bss_C.mode++;
            }
            break;

        case 2:
            if(pl->time < 1.0f) {
                lbl_1_bss_C.itemNo++;
                fn_1_6E9C(lbl_1_bss_C.itemNo);
                pl->motNo = 0;
                pl->speed = 1.0f;
                pl->time = 0.0f;
                pl->attr = HU3D_MOTATTR_LOOP;
                pl->attrReset = 0x40000004;
                lbl_1_bss_C.mode = 0;
            }
            break;

        case 3:
            break;
    }
    return result;
}

/* asm 2967-3007, 39 insns. Hide the previous item, show item itemNo. */
void fn_1_6E9C(s16 itemNo)
{
    Hu3DModelAttrSet(lbl_1_bss_914->models[lbl_1_bss_8D8[itemNo-1].kind].modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_914->models[lbl_1_bss_8D8[itemNo].kind].modelId, HU3D_ATTR_DISPOFF);
}

/* asm 3010-3229, 212 insns. Unreferenced, inlined into fn_1_753C and fn_1_89AC: shrink a duellist's held item away. */
s16 fn_1_6F38(s16 player, s16 hideF)
{
    s16 result;
    s16 no;

    result = 0;
    no = player+10;
    if(hideF == 0) {
        switch(lbl_1_bss_80[player].holdMode) {
            case 0:
                Hu3DModelObjPosGet(lbl_1_bss_914->models[player+32].modelId, lbl_1_bss_80[player].hookName, &lbl_1_bss_914->models[no].pos);
                lbl_1_bss_914->models[no].rot.y = 90.0f-(180.0f*player);
                Hu3DModelHookObjReset(lbl_1_bss_914->models[player+32].modelId, lbl_1_bss_80[player].hookName);
                lbl_1_bss_80[player].holdMode++;
                break;

            case 1:
                lbl_1_bss_80[player].scale.x -= 0.05f;
                lbl_1_bss_80[player].scale.y -= 0.05f;
                lbl_1_bss_80[player].scale.z -= 0.05f;
                lbl_1_bss_914->models[no].rot.x += 20.0f;
                Hu3DModelScaleSetV(lbl_1_bss_914->models[no].modelId, &lbl_1_bss_80[player].scale);
                if(lbl_1_bss_80[player].scale.x <= 0.1f) {
                    Hu3DModelAttrSet(lbl_1_bss_914->models[no].modelId, HU3D_ATTR_DISPOFF);
                    lbl_1_bss_80[player].holdMode++;
                }
                break;

            case 2:
                result = 1;
                break;
        }
    } else {
        Hu3DModelAttrSet(lbl_1_bss_914->models[no].modelId, HU3D_ATTR_DISPOFF);
        result = 1;
    }
    return result;
}

/* asm 3232-3413, 173 insns. Unreferenced, inlined into fn_1_753C: drop the hooked item with dust and fade it. */
s16 fn_1_7288(void)
{
    HuVecF pos;
    s16 result;

    result = 0;
    switch(lbl_1_bss_C.dropMode) {
        case 0:
            Hu3DModelObjPosGet(lbl_1_bss_914->models[34].modelId, lbl_1_bss_C.name, &pos);
            if(lbl_1_bss_914->player[2].motNo == 0) {
                fn_1_2834(&pos, 1);
            } else {
                Hu3DModelHookObjReset(lbl_1_bss_914->models[34].modelId, lbl_1_bss_C.name);
                lbl_1_bss_914->models[lbl_1_bss_8D8[lbl_1_bss_C.itemNo].kind].pos = pos;
                lbl_1_bss_914->models[lbl_1_bss_8D8[lbl_1_bss_C.itemNo].kind].rot.x = -90.0f;
                lbl_1_bss_914->models[lbl_1_bss_8D8[lbl_1_bss_C.itemNo].kind].rot.z = 0.0f;
                fn_1_2834(&pos, 0);
            }
            lbl_1_bss_C.dropMode++;
            break;

        case 1:
            Hu3DModelTPLvlSet(lbl_1_bss_914->models[lbl_1_bss_8D8[lbl_1_bss_C.itemNo].kind].modelId, lbl_1_bss_C.tpLvl);
            if((lbl_1_bss_C.tpLvl -= 0.05f) <= 0.0f) {
                Hu3DModelAttrSet(lbl_1_bss_914->models[lbl_1_bss_8D8[lbl_1_bss_C.itemNo].kind].modelId, HU3D_ATTR_DISPOFF);
                lbl_1_bss_C.dropMode++;
            }
            break;

        case 2:
            result = 1;
            break;
    }
    return result;
}

/* asm 3416-4082, 637 insns. Finish: everyone back to idle, drop the item, shrink away the held ones. */
s16 fn_1_753C(void)
{
    DS_PLAYER *pl;
    s16 result;
    s16 i;

    pl = &lbl_1_bss_914->player[0];
    result = 0;
    switch(lbl_1_bss_D0.endMode) {
        case 0:
            pl->shiftMode = 1;
            pl->shiftMotNo = 0;
            pl->shiftTime = 0.0f;
            pl->shiftSpeed = 20.0f;
            pl->shiftAttr = HU3D_MOTATTR_LOOP;
            pl->attrReset = 0;
            pl++;
            pl->shiftMode = 1;
            pl->shiftMotNo = 0;
            pl->shiftTime = 0.0f;
            pl->shiftSpeed = 20.0f;
            pl->shiftAttr = HU3D_MOTATTR_LOOP;
            pl->attrReset = 0;
            pl++;
            pl->shiftMode = 1;
            pl->shiftMotNo = 0;
            pl->shiftTime = 0.0f;
            pl->shiftSpeed = 20.0f;
            pl->shiftAttr = HU3D_MOTATTR_LOOP;
            pl->attrReset = 0;
            lbl_1_bss_C.dropF = 1;
            fn_1_7288();
            lbl_1_bss_D0.endMode++;
            break;

        case 1:
            result = fn_1_7288();
            for(i=0; i<2; i++) {
                if(lbl_1_bss_80[i].result == 0 || lbl_1_bss_80[i].result == 1) {
                    result *= fn_1_6F38(i, 0);
                }
            }
            if(result != 0) {
                lbl_1_bss_D0.endMode++;
            }
            break;

        case 2:
            result = 1;
            break;
    }
    return result;
}

/* asm 4085-4238, 147 insns. The opening: the jingle, start the arena swinging, wait, then pan the camera. */
s32 fn_1_7F30(void)
{
    s32 result;
    s16 done;
    float speed;

    result = 0;
    done = 0;
    switch(lbl_1_bss_D0.mode) {
        case 0:
            fn_1_3EF8();
            fn_1_B36C();
            lbl_1_bss_D0.mode++;
            break;

        case 1:
            if(lbl_1_bss_D0.timer++ > 240) {
                lbl_1_bss_D0.mode++;
            }
            break;

        case 2:
            speed = 60.0f;
            done += fn_1_18E8(&lbl_1_bss_8->center.x, speed, -12.0f, -211.0f);
            done += fn_1_18E8(&lbl_1_bss_8->center.y, speed, 208.0f, 218.0f);
            done += fn_1_18E8(&lbl_1_bss_8->center.z, speed, -120.0f, 0.0f);
            done += fn_1_18E8(&lbl_1_bss_8->rot.x, speed, -11.0f, -11.0f);
            done += fn_1_18E8(&lbl_1_bss_8->rot.y, speed, 0.0f, -29.0f);
            done += fn_1_18E8(&lbl_1_bss_8->zoom, speed, 141.0f, 310.0f);
            if(done == 0) {
                lbl_1_bss_D0.mode++;
            }
            break;

        case 3:
            break;
    }
    return result;
}

/* asm 4241-4590, 336 insns. Pre-winner: the actor's verdict motion, then the camera onto the winner (or back out for a draw). */
s32 fn_1_817C(void)
{
    DS_PLAYER *pl;
    s32 result;
    s16 done;
    float speed;

    pl = &lbl_1_bss_914->player[2];
    result = 0;
    done = 0;
    switch(lbl_1_bss_D0.mode) {
        case 0:
            if(lbl_1_bss_D0.timer++ > 60) {
                if(lbl_1_bss_D0.result != 0) {
                    pl->shiftMode = 1;
                    pl->shiftMotNo = (lbl_1_bss_D0.result & 1)+2;
                    pl->shiftTime = 0.0f;
                    pl->shiftSpeed = 14.0f;
                    pl->shiftAttr = 0;
                    pl->attrReset = HU3D_MOTATTR_LOOP;
                    fn_1_4020(5);
                }
                lbl_1_bss_D0.timer = 0;
                lbl_1_bss_D0.mode++;
            }
            break;

        case 1:
            if(lbl_1_bss_D0.result != 0) {
                if(pl->shiftMode == 3) {
                    lbl_1_bss_D0.mode++;
                }
            } else {
                lbl_1_bss_D0.mode++;
            }
            break;

        case 2:
            if(lbl_1_bss_D0.result != 0) {
                if(lbl_1_bss_D0.timer++ >= 30) {
                    lbl_1_bss_D0.mode++;
                }
            } else {
                lbl_1_bss_D0.mode++;
            }
            break;

        case 3:
            speed = 30.0f;
            if(lbl_1_bss_D0.result == 0) {
                done += fn_1_18E8(&lbl_1_bss_8->center.x, speed, -211.0f, 0.0f);
                done += fn_1_18E8(&lbl_1_bss_8->rot.y, speed, -29.0f, 0.0f);
                done += fn_1_18E8(&lbl_1_bss_8->zoom, speed, 310.0f, 560.0f);
                if(done == 0) {
                    lbl_1_bss_D0.mode++;
                }
            } else if((lbl_1_bss_D0.result & 1) == 0) {
                done += fn_1_18E8(&lbl_1_bss_8->center.x, speed, -211.0f, -217.0f);
                done += fn_1_18E8(&lbl_1_bss_8->center.z, speed, 0.0f, -120.0f);
                done += fn_1_18E8(&lbl_1_bss_8->rot.y, speed, -29.0f, 32.0f);
                done += fn_1_18E8(&lbl_1_bss_8->zoom, speed, 310.0f, 304.0f);
                if(done == 0) {
                    lbl_1_bss_D0.mode++;
                }
            } else {
                done += fn_1_18E8(&lbl_1_bss_8->center.x, speed, -211.0f, 229.0f);
                done += fn_1_18E8(&lbl_1_bss_8->center.z, speed, 0.0f, -115.0f);
                done += fn_1_18E8(&lbl_1_bss_8->rot.y, speed, -29.0f, -28.0f);
                done += fn_1_18E8(&lbl_1_bss_8->zoom, speed, 310.0f, 314.0f);
                if(done == 0) {
                    lbl_1_bss_D0.mode++;
                }
            }
            break;

        case 4:
            result = 1;
            lbl_1_bss_D0.slideSeMode++;
            break;
    }
    return result;
}

/* asm 4593-4617, 21 insns. */
void fn_1_86BC(void)
{
    int i;

    for(i=0; i<4; i++) {
        memset(&lbl_1_bss_828[i], 0, sizeof(M544_THROW));
    }
}

/* asm 4620-4792, 167 insns. Aim throw `slot` from player's hand at the other duellist's head. */
void fn_1_8710(int player, int slot)
{
    char *hook;

    if(slot < 4) {
        memset(&lbl_1_bss_828[slot], 0, sizeof(M544_THROW));
        lbl_1_bss_828[slot].activeF = 1;
        lbl_1_bss_828[slot].player = player;
        lbl_1_bss_828[slot].alpha = 1.0f;
        hook = CharModelItemHookGet(lbl_1_bss_914->chr[player].charNo, 1, 0);
        Hu3DModelObjPosGet(lbl_1_bss_914->models[player+32].modelId, hook, &lbl_1_bss_828[slot].from);
        hook = CharModelItemHookGet(lbl_1_bss_914->chr[player^1].charNo, 1, 4);
        Hu3DModelObjPosGet(lbl_1_bss_914->models[(player^1)+32].modelId, hook, &lbl_1_bss_828[slot].to);
        if(lbl_1_bss_914->chr[player^1].charNo == 6) {
            lbl_1_bss_828[slot].to.y = 180.0f;
            if(player^1) {
                lbl_1_bss_828[slot].to.x -= 30.0f;
            } else {
                lbl_1_bss_828[slot].to.x += 30.0f;
            }
        }
        lbl_1_bss_828[slot].to.y += 20.0f;
        if(player^1) {
            lbl_1_bss_828[slot].to.x -= 50.0f;
        } else {
            lbl_1_bss_828[slot].to.x += 45.0f;
        }
    }
}

/* asm 4795-5122, 315 insns. The throw object: fly, hit, dazzle the target, recover. */
void fn_1_89AC(OMOBJ *obj)
{
    DS_PLAYER *pl;
    int i;

    for(i=0; i<4; i++) {
        if(lbl_1_bss_828[i].activeF == 0) {
            continue;
        }
        switch(lbl_1_bss_828[i].mode) {
            case 0:
                fn_1_8E98(i, 0);
                lbl_1_bss_828[i].mode++;
                break;

            case 1:
                pl = &lbl_1_bss_914->player[lbl_1_bss_828[i].player^1];
                lbl_1_bss_828[i].timer++;
                fn_1_91B4(i, lbl_1_bss_828[i].timer);
                if(lbl_1_bss_828[i].timer >= 10) {
                    fn_1_8E98(i, 1);
                    lbl_1_bss_828[i].mode++;
                    lbl_1_bss_828[i].timer = 0;
                    pl->shiftMode = 1;
                    pl->shiftMotNo = 1;
                    pl->shiftTime = 0.0f;
                    pl->shiftSpeed = 10.0f;
                    pl->shiftAttr = 0;
                    pl->attrReset = 0;
                    lbl_1_bss_828[i].timer = 0;
                    fn_1_6F38(lbl_1_bss_828[i].player^1, 1);
                    omVibrate(lbl_1_bss_914->chr[lbl_1_bss_828[i].player^1].no, 12, 12, 0);
                }
                break;

            case 2:
                pl = &lbl_1_bss_914->player[lbl_1_bss_828[i].player^1];
                if(lbl_1_bss_828[i].timer++ == 45) {
                    pl->shiftMode = 1;
                    pl->shiftMotNo = 0;
                    pl->shiftTime = 0.0f;
                    pl->shiftSpeed = 10.0f;
                    pl->shiftAttr = HU3D_MOTATTR_LOOP;
                    pl->attrReset = 0;
                    lbl_1_bss_828[i].activeF = 0;
                }
                fn_1_9364(i, 0);
                break;

            case 3:
                pl = &lbl_1_bss_914->player[lbl_1_bss_828[i].player];
                fn_1_8E98(i, 2);
                pl->shiftMode = 1;
                pl->shiftMotNo = 1;
                pl->shiftTime = 0.0f;
                pl->shiftSpeed = 10.0f;
                pl->shiftAttr = 0;
                pl->attrReset = 0;
                fn_1_6F38(lbl_1_bss_828[i].player, 1);
                lbl_1_bss_828[i].timer = 0;
                lbl_1_bss_828[i].mode++;
                break;

            case 4:
                pl = &lbl_1_bss_914->player[lbl_1_bss_828[i].player];
                if(lbl_1_bss_828[i].timer++ == 45) {
                    pl->shiftMode = 1;
                    pl->shiftMotNo = 0;
                    pl->shiftTime = 0.0f;
                    pl->shiftSpeed = 10.0f;
                    pl->shiftAttr = HU3D_MOTATTR_LOOP;
                    pl->attrReset = 0;
                    lbl_1_bss_828[i].activeF = 0;
                }
                fn_1_9364(i, 1);
                break;
        }
    }
}

/* asm 5125-5334, 199 insns. Show a throw's flying (type 0), impact (1) or backfire (2) model. */
void fn_1_8E98(int slot, int type)
{
    M544_MODEL *mdl;

    switch(type) {
        case 0:
            mdl = &lbl_1_bss_914->models[slot+12];
            Hu3DMotionSpeedSet(mdl->modelId, 10.0f);
            Hu3DMotionTimeSet(mdl->modelId, 0.0f);
            Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
            mdl->pos.x = lbl_1_bss_828[slot].from.x;
            mdl->pos.y = lbl_1_bss_828[slot].from.y;
            mdl->pos.z = lbl_1_bss_828[slot].from.z;
            break;

        case 1:
            mdl = &lbl_1_bss_914->models[slot+12];
            Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
            mdl = &lbl_1_bss_914->models[slot+16];
            Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
            Hu3DMotionSpeedSet(mdl->modelId, 6.0f);
            Hu3DMotionTimeSet(mdl->modelId, 0.0f);
            mdl->pos.x = lbl_1_bss_828[slot].to.x;
            mdl->pos.y = lbl_1_bss_828[slot].to.y;
            mdl->pos.z = lbl_1_bss_828[slot].to.z;
            Hu3DModelPosSetV(mdl->modelId, &mdl->pos);
            if(lbl_1_bss_828[slot].player != 0) {
                mdl->rot.y = -45.0f;
            } else {
                mdl->rot.y = 90.0f;
            }
            Hu3DModelRotSetV(mdl->modelId, &mdl->rot);
            break;

        case 2:
            mdl = &lbl_1_bss_914->models[slot+16];
            Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
            Hu3DMotionSpeedSet(mdl->modelId, 8.0f);
            Hu3DMotionTimeSet(mdl->modelId, 0.0f);
            mdl->pos.x = lbl_1_bss_828[slot].from.x;
            mdl->pos.y = lbl_1_bss_828[slot].from.y;
            mdl->pos.z = lbl_1_bss_828[slot].from.z;
            mdl->pos.y += 20.0f;
            Hu3DModelPosSetV(mdl->modelId, &mdl->pos);
            if(lbl_1_bss_828[slot].player != 0) {
                mdl->rot.y = 90.0f;
            } else {
                mdl->rot.y = -45.0f;
            }
            Hu3DModelRotSetV(mdl->modelId, &mdl->rot);
            break;
    }
}

/* asm 5337-5446, 108 insns. A flying throw at frame `time` of 10. */
void fn_1_91B4(int slot, int time)
{
    M544_MODEL *mdl;

    mdl = &lbl_1_bss_914->models[slot+12];
    mdl->pos.x = lbl_1_bss_828[slot].from.x+((time*(lbl_1_bss_828[slot].to.x-lbl_1_bss_828[slot].from.x))/10.0f);
    mdl->pos.y = lbl_1_bss_828[slot].from.y+((time*(lbl_1_bss_828[slot].to.y-lbl_1_bss_828[slot].from.y))/10.0f);
    mdl->pos.z = lbl_1_bss_828[slot].from.z+((time*(lbl_1_bss_828[slot].to.z-lbl_1_bss_828[slot].from.z))/10.0f);
}

/* asm 5449-5615, 157 insns. Darken the hit duellist's materials as the throw's alpha decays; 1 once it is gone. */
s32 fn_1_9364(int slot, int loserF)
{
    int unused;
    HU3DMODEL *model;
    HSFDATA *hsf;
    HSFMATERIAL *material;
    int i;
    float alpha;

    unused = 1;
    if(loserF) {
        model = &Hu3DData[lbl_1_bss_914->models[lbl_1_bss_828[slot].player+32].modelId];
    } else {
        model = &Hu3DData[lbl_1_bss_914->models[(lbl_1_bss_828[slot].player^1)+32].modelId];
    }
    hsf = model->hsf;
    material = hsf->material;
    lbl_1_bss_828[slot].alpha *= 0.99;
    if(lbl_1_bss_828[slot].alpha < 0.05) {
        lbl_1_bss_828[slot].alpha = 0.0f;
    }
    if((alpha = lbl_1_bss_828[slot].alpha) > 0.865f) {
        for(i=0; i<model->hsf->materialNum; i++, material++) {
            material->color[0] = material->color[0]*alpha;
            material->color[1] = material->color[1]*alpha;
            material->color[2] = material->color[2]*alpha;
        }
    }
    if(0.0f == lbl_1_bss_828[slot].alpha) {
        return 1;
    } else {
        return 0;
    }
}

/* asm 5618-5734, 112 insns. Both duellists throw at once (a slot of -1 skips that duellist). */
void fn_1_95D8(int slotA, int slotB)
{
    int slot[2];
    int unused;
    int i;
    char *hook;

    slot[0] = slotA;
    slot[1] = slotB;
    for(i=0, unused=-1; i<2; i++) {
        if(slot[i] < 0) {
            continue;
        }
        memset(&lbl_1_bss_828[slot[i]], 0, sizeof(M544_THROW));
        lbl_1_bss_828[slot[i]].activeF = 1;
        lbl_1_bss_828[slot[i]].mode = 3;
        lbl_1_bss_828[slot[i]].player = i;
        lbl_1_bss_828[slot[i]].alpha = 1.0f;
        hook = CharModelItemHookGet(lbl_1_bss_914->chr[i].charNo, 1, 0);
        Hu3DModelObjPosGet(lbl_1_bss_914->models[i+32].modelId, hook, &lbl_1_bss_828[slot[i]].from);
        omVibrate(lbl_1_bss_914->chr[i].no, 12, 12, 0);
    }
}

/*
 * asm 5737-6071, 315 insns. A computer duellist's plan for this duel: react
 * normally, press a wrong button, or press early on one of the decoys before
 * the first real item.
 */
void fn_1_9798(s16 player)
{
    s16 dif;
    s16 i;
    s16 decoyCnt;
    s16 r;
    s16 time;

    dif = lbl_1_bss_914->chr[player].dif-1;
    for(i=0, decoyCnt=0; i<10; decoyCnt++, i++) {
        if(lbl_1_bss_8D8[i].kind < 6) {
            break;
        }
    }
    r = frandmod(100);
    if(r > lbl_1_data_3EC[dif][3]-(decoyCnt*5) && lbl_1_bss_80[player].comMode == 0 && decoyCnt != 0) {
        lbl_1_bss_80[player].comMode = 2;
    }
    r = frandmod(100);
    if(r > lbl_1_data_3EC[dif][2] && lbl_1_bss_80[player].comMode == 0) {
        lbl_1_bss_80[player].comMode = 1;
    }
    r = frandmod(100);
    if(r > lbl_1_data_3EC[dif][4] && lbl_1_bss_80[player].comMode == 0) {
        lbl_1_bss_80[player].comMode = 3;
    }
    switch(lbl_1_bss_80[player].comMode) {
        case 0:
        case 1:
            lbl_1_bss_80[player].comTimer = lbl_1_data_3EC[dif][0]+frandmod(lbl_1_data_3EC[dif][1]-lbl_1_data_3EC[dif][0]);
            break;

        case 2:
            if(decoyCnt != 0) {
                lbl_1_bss_80[player].comItem = frandmod(decoyCnt);
            } else {
                lbl_1_bss_80[player].comItem = 0;
            }
            time = lbl_1_bss_8D8[lbl_1_bss_80[player].comItem].hangTime-29;
            if(time > 0) {
                lbl_1_bss_80[player].comTimer = frandmod(time)+30;
            } else {
                lbl_1_bss_80[player].comTimer = 30;
            }
            if(lbl_1_data_3EC[dif][1] < lbl_1_bss_80[player].comTimer) {
                lbl_1_bss_80[player].comTimer = lbl_1_data_3EC[dif][0]+frandmod(lbl_1_data_3EC[dif][1]-lbl_1_data_3EC[dif][0]);
            }
            break;

        case 3:
            if(decoyCnt != 0) {
                lbl_1_bss_80[player].comItem = frandmod(decoyCnt);
            } else {
                lbl_1_bss_80[player].comItem = 0;
            }
            time = lbl_1_bss_8D8[lbl_1_bss_80[player].comItem].waitTime-29;
            if(time > 0) {
                lbl_1_bss_80[player].comTimer = frandmod(time)+30;
            } else {
                lbl_1_bss_80[player].comTimer = 30;
            }
            break;
    }
}

/* asm 6074-6241, 157 insns. A computer duellist's button this frame (0x80 | button), or 0. */
s16 fn_1_9C84(s16 player)
{
    s16 press;
    s16 dif;
    s16 i;

    press = 0;
    dif = lbl_1_bss_914->chr[player].dif-1;
    switch(lbl_1_bss_80[player].comMode) {
        case 0:
            if(lbl_1_bss_D0.realF != 0 && lbl_1_bss_80[player].comTimer-- <= 0) {
                press = lbl_1_bss_8D8[lbl_1_bss_C.itemNo].kind | 0x80;
            }
            break;

        case 1:
            if(lbl_1_bss_D0.realF != 0 && lbl_1_bss_80[player].comTimer-- <= 0) {
                for(i=0; i<=5; i++) {
                    if(i != lbl_1_bss_8D8[lbl_1_bss_C.itemNo].kind) {
                        break;
                    }
                }
                press = i | 0x80;
            }
            break;

        case 2:
            if(lbl_1_bss_C.itemNo == lbl_1_bss_80[player].comItem && lbl_1_bss_C.mode == 1 && lbl_1_bss_80[player].comTimer-- <= 0) {
                press = 0x80;
            }
            break;

        case 3:
            if(lbl_1_bss_C.itemNo == lbl_1_bss_80[player].comItem && lbl_1_bss_C.mode == 0 && lbl_1_bss_80[player].comTimer-- <= 0) {
                press = 0x80;
            }
            break;
    }
    return press;
}
