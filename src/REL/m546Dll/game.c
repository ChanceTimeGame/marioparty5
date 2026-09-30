/*
 * m546dll/game.c -- the lane duel: the sequence steps, the three lanes and
 * their boxes, the duellists' walks and jumps, and the computer duellists.
 * Written from the reference assembly, functions in reference order; line
 * ranges are into build/mp5-asm/m546Dll/asm/REL/m546Dll/game.s.
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

#include "REL/m546Dll/m546.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

void fn_1_6F24(void);
void fn_1_7190(void);
s16 fn_1_743C(s16 no);
s16 fn_1_765C(s16 no);
void fn_1_7C60(s16 no);
s16 fn_1_7D70(s16 no);
s16 fn_1_8750(s16 no);
s16 fn_1_8CE4(s16 no);
s16 fn_1_9044(void);
s16 fn_1_9178(void);
s32 fn_1_9250(s16 no);
s32 fn_1_9920(s16 no);
s32 fn_1_9B7C(s16 no);
void fn_1_9F78(void);
s16 fn_1_A0BC(s16 type, s8 lane);
s16 fn_1_A2E4(s16 no, float frames);
s16 fn_1_A4EC(void);
s16 fn_1_AC58(void);
void fn_1_AE14(s16 no);

/* --- .data --- */

/* Where each character stands in its lane box: x, z. */
float lbl_1_data_450[13][2] = {
    { 34.0f, -42.0f }, { 34.0f, -42.0f }, { 34.0f, -42.0f }, { 34.0f, -42.0f }, { 34.0f, -42.0f },
    { 34.0f, -42.0f }, { 34.0f, -42.0f }, { 34.0f, -42.0f }, { 34.0f, -42.0f }, { 34.0f, -42.0f },
    { 34.0f, -42.0f }, { 34.0f, -42.0f }, { 34.0f, -42.0f }
};

HuVecF lbl_1_data_4B8 = { 34.0f, 0.0f, 60.0f };
float lbl_1_data_4C4 = 50.0f;

/* --- .bss (CodeWarrior lays it out in reverse definition order) --- */

int lbl_1_bss_15294;                /* PropSlide has run once (stage.c) */
int lbl_1_bss_15290;                /* PropRoll has run once (stage.c, DS_PROPROLL_PASSED) */
int lbl_1_bss_1528C;                /* unreferenced */
M546_WORK *lbl_1_bss_15288;         /* the work fn_1_58D0 was given */

/* asm 9-1174, 1136 insns. Init step: clear the state, pick the lanes' order, create the boxes and place the duellists. */
s32 fn_1_58D0(M546_WORK *work)
{
    s16 i;
    s16 j;
    s16 count;
    s16 boxLane;
    s32 result = 1;
    s16 bombLane;

    memset(&lbl_1_bss_14C40, 0, sizeof(M546_GAME));
    memset(lbl_1_bss_14B60, 0, sizeof(lbl_1_bss_14B60));
    memset(&lbl_1_bss_14AB8, 0, sizeof(M546_PIECESET));
    memset(&lbl_1_bss_14A10, 0, sizeof(M546_PIECESET));
    memset(lbl_1_bss_1F0, 0, sizeof(lbl_1_bss_1F0));
    memset(lbl_1_bss_4C, 0, sizeof(lbl_1_bss_4C));
    lbl_1_bss_15288 = work;
    for(i=0; i<7; i++) {
        lbl_1_bss_14C40.seF[i] = -1;
    }
    for(i=0; i<2; i++) {
        lbl_1_bss_14B60[i].lane = 0;
    }
    lbl_1_bss_14B60[0].scale.x = 1.0f;
    lbl_1_bss_14B60[0].scale.y = 1.0f;
    lbl_1_bss_14B60[0].scale.z = 1.0f;
    lbl_1_bss_14B60[1].scale.x = 1.0f;
    lbl_1_bss_14B60[1].scale.y = 1.0f;
    lbl_1_bss_14B60[1].scale.z = 1.0f;
    for(i=0; i<2; i++) {
        lbl_1_bss_14B60[i].hookName = CharModelItemHookGet(lbl_1_bss_15288->chr[i].charNo, 1, 0);
    }
    lbl_1_bss_14C40.waitTimer = frandmod(4);
    for(i=0; i<2; i++) {
        if(lbl_1_bss_15288->chr[i].dif != 0) {
            lbl_1_bss_14B60[i].comMoves = frandmod(4)+1;
            lbl_1_bss_14B60[i].comChance = frandmod(45)+50;
        }
    }
    for(i=0; i<3; i++) {
        lbl_1_bss_14C40.order[i] = -1;
    }
    for(i=0; i<3; i++) {
        do {
            lbl_1_bss_14C40.order[i] = frandmod(3);
            for(j=0, count=0; j<3; j++) {
                if(lbl_1_bss_14C40.order[i] == lbl_1_bss_14C40.order[j]) {
                    count++;
                }
            }
        } while(count > 1);
        if(lbl_1_bss_14C40.order[i] == 0) {
            boxLane = i;
        }
        if(lbl_1_bss_14C40.order[i] == 2) {
            bombLane = i;
        }
    }
    lbl_1_bss_15288->models[0].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_15288->stageDataTbl[4], HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_15288->models[0].modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(lbl_1_bss_15288->models[0].modelId, 1);
    Hu3DModelLayerSet(lbl_1_bss_15288->models[0].modelId, 1);
    lbl_1_bss_15288->models[0].pos.x = -300.0f+(300.0f*boxLane);
    lbl_1_bss_15288->models[0].pos.y = 1000.0f;
    lbl_1_bss_15288->models[0].pos.z = 0.0f;
    lbl_1_bss_15288->models[0].rot.x = 0.0f;
    lbl_1_bss_15288->models[0].rot.y = 0.0f;
    lbl_1_bss_15288->models[0].rot.z = 0.0f;
    lbl_1_bss_15288->models[11].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_15288->stageDataTbl[7], HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_15288->models[11].modelId, HU3D_ATTR_DISPOFF|HU3D_ATTR_MOTION_OFF);
    Hu3DModelCameraSet(lbl_1_bss_15288->models[11].modelId, 1);
    Hu3DModelLayerSet(lbl_1_bss_15288->models[11].modelId, 6);
    lbl_1_bss_15288->models[11].pos.x = -300.0f+(300.0f*boxLane);
    lbl_1_bss_15288->models[11].pos.y = 1000.0f;
    lbl_1_bss_15288->models[11].pos.z = 0.0f;
    lbl_1_bss_15288->models[11].rot.x = 0.0f;
    lbl_1_bss_15288->models[11].rot.y = 0.0f;
    lbl_1_bss_15288->models[11].rot.z = 0.0f;
    Hu3DModelShadowSet(lbl_1_bss_15288->models[11].modelId);
    Hu3DModelShadowDispOff(lbl_1_bss_15288->models[11].modelId);
    Hu3DModelAttrReset(lbl_1_bss_15288->models[11].modelId, HU3D_ATTR_DISPOFF);
    lbl_1_bss_14C40.boxTpLvl = 0.0f;
    Hu3DModelTPLvlSet(lbl_1_bss_15288->models[11].modelId, lbl_1_bss_14C40.boxTpLvl);
    for(i=1, j=0; i<=3; i++, j++) {
        lbl_1_bss_15288->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_15288->stageDataTbl[5], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_15288->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_15288->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_15288->models[i].modelId, 1);
        lbl_1_bss_15288->models[i].pos.x = -300.0f+(300.0f*j);
        lbl_1_bss_15288->models[i].pos.y = 1000.0f;
        lbl_1_bss_15288->models[i].pos.z = 0.0f;
        lbl_1_bss_15288->models[i].rot.x = 0.0f;
        lbl_1_bss_15288->models[i].rot.y = 0.0f;
        lbl_1_bss_15288->models[i].rot.z = 0.0f;
        Hu3DModelAttrReset(lbl_1_bss_15288->models[i].modelId, HU3D_ATTR_DISPOFF);
    }
    for(i=12, j=0; i<=14; i++, j++) {
        lbl_1_bss_15288->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_15288->stageDataTbl[8], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_15288->models[i].modelId, HU3D_ATTR_DISPOFF|HU3D_ATTR_MOTION_OFF);
        Hu3DModelCameraSet(lbl_1_bss_15288->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_15288->models[i].modelId, 2);
        lbl_1_bss_15288->models[i].pos.x = -300.0f+(300.0f*j);
        lbl_1_bss_15288->models[i].pos.y = 101.0f;
        lbl_1_bss_15288->models[i].pos.z = 0.0f;
        lbl_1_bss_15288->models[i].rot.x = 0.0f;
        lbl_1_bss_15288->models[i].rot.y = 0.0f;
        lbl_1_bss_15288->models[i].rot.z = 0.0f;
        Hu3DModelShadowSet(lbl_1_bss_15288->models[i].modelId);
        Hu3DModelShadowDispOn(lbl_1_bss_15288->models[i].modelId);
        Hu3DModelAttrReset(lbl_1_bss_15288->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelTPLvlSet(lbl_1_bss_15288->models[i].modelId, 0.0f);
        lbl_1_bss_14C40.laneTpLvl[j] = 0.0f;
    }
    for(i=8, j=0; i<=10; i++, j++) {
        lbl_1_bss_15288->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_15288->stageDataTbl[6], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_15288->models[i].modelId, HU3D_ATTR_DISPOFF|HU3D_MOTATTR_LOOP);
        Hu3DModelCameraSet(lbl_1_bss_15288->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_15288->models[i].modelId, 1);
        lbl_1_bss_15288->models[i].pos.x = -50.0f+(50.0f*j);
        lbl_1_bss_15288->models[i].pos.y = 700.0f;
        lbl_1_bss_15288->models[i].pos.z = -42.0f;
        lbl_1_bss_15288->models[i].rot.x = 0.0f;
        lbl_1_bss_15288->models[i].rot.y = 0.0f;
        lbl_1_bss_15288->models[i].rot.z = 0.0f;
        Hu3DModelAttrReset(lbl_1_bss_15288->models[i].modelId, HU3D_ATTR_DISPOFF);
        lbl_1_bss_14C40.bombTpLvl[j] = 0.0f;
        Hu3DModelTPLvlSet(lbl_1_bss_15288->models[i].modelId, lbl_1_bss_14C40.bombTpLvl[j]);
        Hu3DMotionTimeSet(lbl_1_bss_15288->models[i].modelId, 20.0f*j);
    }
    for(i=4, j=0; i<=7; i++, j++) {
        lbl_1_bss_15288->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_15288->stageDataTbl[j], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_15288->models[i].modelId, HU3D_ATTR_DISPOFF);
        lbl_1_bss_15288->models[i].pos.x = -300.0f+(300.0f*bombLane);
        lbl_1_bss_15288->models[i].pos.y = 1000.0f;
        lbl_1_bss_15288->models[i].pos.z = 0.0f;
    }
    for(i=0; i<2; i++) {
        lbl_1_bss_15288->models[i+27].pos.x = (-150.0f+(300.0f*i))+lbl_1_data_4B8.x;
        lbl_1_bss_15288->models[i+27].pos.y = 100.0f;
        lbl_1_bss_15288->models[i+27].pos.z = -200.0f;
    }
    fn_1_7190();
    fn_1_19DC();
    return result;
}

/* asm 1177-1191, 13 insns. Fade-in step. */
s32 fn_1_6A90(void)
{
    s32 result = 0;

    fn_1_A4EC();
    fn_1_7190();
    return result;
}

/* asm 1194-1222, 26 insns. Start step: the music. */
s32 fn_1_6AC4(void)
{
    s32 result = 1;

    lbl_1_bss_14C40.camMode = 0;
    if(lbl_1_bss_14C40.bgmF == 0) {
        fn_1_557C();
        lbl_1_bss_14C40.bgmF = 1;
    }
    fn_1_7190();
    return result;
}

/* asm 1225-1340, 106 insns. Main step: both duellists pick a lane, then the lanes open, then the winner. */
s32 fn_1_6B2C(void)
{
    s16 i;
    s32 ok;
    s32 result;
    s32 no;

    result = 0;
    ok = 1;
    switch(lbl_1_bss_15288->mode[0]) {
        case 0:
            for(i=0; i<2; i++) {
                ok *= fn_1_743C(i);
            }
            if(ok) {
                lbl_1_bss_14B60[0].subMode = 0;
                lbl_1_bss_14B60[1].subMode = 0;
                lbl_1_bss_15288->mode[0] = 1;
            }
            break;

        case 1:
            if(fn_1_9044()) {
                lbl_1_bss_15288->mode[0] = 2;
            }
            break;

        case 2:
            MgSeqWinnerSet(lbl_1_bss_15288->chr[lbl_1_bss_14C40.winner].charNo, CHARNO_NONE, CHARNO_NONE, CHARNO_NONE);
            no = lbl_1_bss_15288->chr[lbl_1_bss_14C40.winner].no;
            if(!_CheckFlag(FLAG_MG_PRACTICE)) {
                GwPlayer[no].mgCoinBonus = 10;
            }
            lbl_1_bss_14C40.bgmF = 0;
            result = 1;
            break;
    }
    fn_1_7190();
    return result;
}

/* asm 1343-1361, 16 insns. Finish step. */
s32 fn_1_6CD4(void)
{
    s32 result = 0;

    if(lbl_1_bss_14C40.bgmF == 0) {
        lbl_1_bss_14C40.bgmF = 1;
    }
    return result;
}

/* asm 1364-1379, 14 insns. Pre-winner step: the camera moves to the winner. */
s32 fn_1_6D14(void)
{
    s32 result = 0;

    result = fn_1_AC58();
    fn_1_7190();
    return result;
}

/* asm 1382-1466, 82 insns. Winner step: the winner and the loser pose. */
s32 fn_1_6D4C(void)
{
    M546_PLAYER *pl;
    s32 result = 0;

    if(lbl_1_bss_14C40.poseF == 0) {
        pl = &lbl_1_bss_15288->player[lbl_1_bss_14C40.winner];
        pl->attrReset = HU3D_MOTATTR_LOOP|HU3D_MOTATTR_PAUSE|HU3D_MOTATTR_SHIFT_PAUSE;
        pl->motNo = 7;
        pl->speed = 1.0f;
        pl->time = 0.0f;
        pl->attr = HU3D_MOTATTR_NONE;
        pl = &lbl_1_bss_15288->player[lbl_1_bss_14C40.loser];
        pl->attrReset = HU3D_MOTATTR_LOOP;
        pl->motNo = 8;
        pl->speed = 1.0f;
        pl->time = 0.0f;
        pl->attr = HU3D_MOTATTR_NONE;
        lbl_1_bss_14C40.poseF = 1;
    }
    fn_1_7190();
    CharModelVoicePanSet(lbl_1_bss_15288->chr[lbl_1_bss_14C40.winner].charNo, 64);
    return result;
}

/* asm 1469-1482, 12 insns. Fade-out step. */
s32 fn_1_6E94(void)
{
    s32 result = 1;

    fn_1_7190();
    return result;
}

/* asm 1485-1512, 24 insns. Close step: stop the sound and the piece hooks. */
s32 fn_1_6EC4(void)
{
    s32 result = 1;

    fn_1_58B0();
    if(lbl_1_bss_14AB8.activeF) {
        fn_1_301C();
    }
    if(lbl_1_bss_14A10.activeF) {
        fn_1_4010();
    }
    return result;
}

/* asm 1515-1674, 155 insns. fn_1_7190 without the pieces or the camera. Unreferenced. */
void fn_1_6F24(void)
{
    s16 i;
    s16 pan;
    HU3DMODEL *modelA;
    HU3DMODEL *modelB;
    float x;

    modelA = &Hu3DData[lbl_1_bss_15288->models[27].modelId];
    modelB = &Hu3DData[lbl_1_bss_15288->models[28].modelId];
    for(i=0; i<M546_MODEL_MAX; i++) {
        if(i == 4 || i == 5 || i == 6 || i == 7) {
            continue;
        }
        Hu3DModelPosSet(lbl_1_bss_15288->models[i].modelId, lbl_1_bss_15288->models[i].pos.x, lbl_1_bss_15288->models[i].pos.y, lbl_1_bss_15288->models[i].pos.z);
        Hu3DModelRotSet(lbl_1_bss_15288->models[i].modelId, lbl_1_bss_15288->models[i].rot.x, lbl_1_bss_15288->models[i].rot.y, lbl_1_bss_15288->models[i].rot.z);
    }
    x = 0.10666667f*modelA->pos.x;
    pan = 64.0f+x;
    CharModelVoicePanSet(lbl_1_bss_15288->chr[0].charNo, pan);
    x = 0.10666667f*modelB->pos.x;
    pan = 64.0f+x;
    CharModelVoicePanSet(lbl_1_bss_15288->chr[1].charNo, pan);
}

/* asm 1677-1854, 171 insns. Every step: the pieces, the model table, the voices' pan, the camera, light and shadow. */
void fn_1_7190(void)
{
    s16 i;
    s16 pan;
    HU3DMODEL *modelB;
    HU3DMODEL *modelA;
    float x;

    if(lbl_1_bss_14AB8.activeF) {
        fn_1_38A0();
    }
    if(lbl_1_bss_14A10.activeF) {
        fn_1_487C();
    }
    modelA = &Hu3DData[lbl_1_bss_15288->models[27].modelId];
    modelB = &Hu3DData[lbl_1_bss_15288->models[28].modelId];
    for(i=0; i<M546_MODEL_MAX; i++) {
        if(i == 4 || i == 5 || i == 6 || i == 7) {
            continue;
        }
        Hu3DModelPosSet(lbl_1_bss_15288->models[i].modelId, lbl_1_bss_15288->models[i].pos.x, lbl_1_bss_15288->models[i].pos.y, lbl_1_bss_15288->models[i].pos.z);
        Hu3DModelRotSet(lbl_1_bss_15288->models[i].modelId, lbl_1_bss_15288->models[i].rot.x, lbl_1_bss_15288->models[i].rot.y, lbl_1_bss_15288->models[i].rot.z);
    }
    x = 0.10666667f*modelA->pos.x;
    pan = 64.0f+x;
    CharModelVoicePanSet(lbl_1_bss_15288->chr[0].charNo, pan);
    x = 0.10666667f*modelB->pos.x;
    pan = 64.0f+x;
    CharModelVoicePanSet(lbl_1_bss_15288->chr[1].charNo, pan);
    fn_1_884(0);
    fn_1_102C();
    fn_1_1434();
}

/* asm 1857-2003, 136 insns. Duellist no's main step. */
s16 fn_1_743C(s16 no)
{
    s16 result = 0;

    switch(lbl_1_bss_14B60[no].mode) {
        case 0:
            if(lbl_1_bss_14C40.turn == no && fn_1_765C(no)) {
                lbl_1_bss_14B60[no].mode = 1;
            }
            break;

        case 1:
            if(fn_1_7D70(no)) {
                lbl_1_bss_14B60[no].mode = 2;
            }
            break;

        case 2:
            if(fn_1_8750(no)) {
                lbl_1_bss_14B60[no].mode = 3;
            }
            break;

        case 3:
            if(no == 0) {
                lbl_1_bss_14C40.turn = 1;
            } else if(no == 1) {
                lbl_1_bss_14B60[0].mode = 4;
                lbl_1_bss_14B60[1].mode = 4;
                fn_1_9F78();
                fn_1_56EC(0, 127, (lbl_1_bss_14C40.seDir*32)+64);
            }
            break;

        case 4:
            if(no == 0 && fn_1_A0BC(1, lbl_1_bss_14C40.seDir)) {
                lbl_1_bss_14B60[0].mode = 5;
                lbl_1_bss_14B60[1].mode = 5;
            }
            break;

        case 5:
            if(fn_1_8CE4(no)) {
                result = 1;
            }
            break;
    }
    return result;
}

/* asm 2006-2407, 385 insns. Duellist no walks round to the front of the stage. */
s16 fn_1_765C(s16 no)
{
    M546_PLAYER *pl;
    s8 mdlNo;
    s16 result;

    pl = &lbl_1_bss_15288->player[no];
    result = 0;
    mdlNo = no+27;
    switch(lbl_1_bss_14B60[no].subMode) {
        case 0:
            lbl_1_bss_14B60[no].baseX = lbl_1_data_4B8.x;
            if(no == 0) {
                lbl_1_bss_14B60[no].angleZ = 180.0f;
            } else if(lbl_1_bss_14B60[0].lane == 0) {
                lbl_1_bss_14B60[no].angleZ = 180.0f;
                lbl_1_bss_14B60[no].baseX += 300.0f;
                lbl_1_bss_14B60[no].lane = 1;
            } else {
                lbl_1_bss_14B60[no].angleZ = 0.0f;
            }
            lbl_1_bss_14B60[no].subMode = 1;
            break;

        case 1:
            lbl_1_bss_15288->models[mdlNo].pos.x = lbl_1_bss_14B60[no].baseX+(150.0*cos((M_PI*lbl_1_bss_14B60[no].angleZ)/180.0));
            lbl_1_bss_15288->models[mdlNo].pos.z = -200.0+((200.0f+lbl_1_data_4B8.z)*sin((M_PI*lbl_1_bss_14B60[no].angleZ)/180.0));
            if(no == 0 || lbl_1_bss_14B60[0].lane == 0) {
                lbl_1_bss_14B60[no].angleZ -= 1.8f;
                lbl_1_bss_15288->models[mdlNo].rot.y += 1.0f;
            } else {
                lbl_1_bss_14B60[no].angleZ += 1.8f;
                lbl_1_bss_15288->models[mdlNo].rot.y -= 1.0f;
            }
            fn_1_A2E4(no, 60.0f);
            if(lbl_1_bss_14B60[no].timer++ >= 50) {
                lbl_1_bss_15288->models[mdlNo].pos.x = lbl_1_bss_14B60[no].baseX;
                lbl_1_bss_15288->models[mdlNo].pos.z = lbl_1_data_4B8.z;
                lbl_1_bss_14B60[no].subMode = 2;
            }
            break;

        case 2:
            if(no == 0 || lbl_1_bss_14B60[0].lane == 0) {
                lbl_1_bss_15288->models[mdlNo].rot.y -= 5.0f;
            } else {
                lbl_1_bss_15288->models[mdlNo].rot.y += 5.0f;
            }
            if(fn_1_A2E4(no, 60.0f)) {
                lbl_1_bss_15288->models[mdlNo].rot.y = 0.0f;
                lbl_1_bss_14B60[no].subMode = 3;
            }
            break;

        case 3:
            lbl_1_bss_14C40.timer = fn_1_18DC(0, 10, 0, 292.0f, 64.0f);
            fn_1_1950(lbl_1_bss_14C40.timer);
            lbl_1_bss_14B60[no].subMode = 0;
            lbl_1_bss_14B60[no].timer = 0;
            result = 1;
            break;
    }
    return result;
}

/* asm 2410-2483, 68 insns. A computer duellist's input once the timer runs out. Only ever inlined. */
void fn_1_7C60(s16 no)
{
    s16 dir;

    if(fn_1_197C(lbl_1_bss_14C40.timer)) {
        if(no == 1 && lbl_1_bss_14B60[0].lane == lbl_1_bss_14B60[1].lane) {
            do {
                dir = frandmod(3)-1;
            } while(lbl_1_bss_14B60[0].lane == dir);
            if(lbl_1_bss_14B60[1].lane > dir) {
                lbl_1_bss_15288->chr[1].stkX = -1;
            } else {
                lbl_1_bss_15288->chr[1].stkX = 1;
            }
        } else {
            lbl_1_bss_15288->chr[no].btnDown = PAD_BUTTON_A;
        }
    }
}

/* asm 2486-3137, 632 insns. Duellist no steps between the lanes with the stick and confirms with A. */
s16 fn_1_7D70(s16 no)
{
    s16 result;
    s8 mdlNo;
    s8 movedF;
    float speed;
    s8 stkX;

    result = 0;
    mdlNo = no+27;
    movedF = 0;
    speed = 10.0f;
    switch(lbl_1_bss_14B60[no].subMode) {
        case 0:
            fn_1_AE14(no);
            fn_1_7C60(no);
            stkX = lbl_1_bss_15288->chr[no].stkX;
            if(!(lbl_1_bss_15288->chr[no].btnDown & PAD_BUTTON_A)) {
                lbl_1_bss_14B60[no].startPos = lbl_1_bss_15288->models[mdlNo].pos;
                lbl_1_bss_14B60[no].endPos = lbl_1_bss_15288->models[mdlNo].pos;
                lbl_1_bss_14B60[no].startRot = lbl_1_bss_15288->models[mdlNo].rot;
                if(stkX < 0 && lbl_1_bss_14B60[no].lane != -1) {
                    if(no == 0 || lbl_1_bss_14B60[0].lane != lbl_1_bss_14B60[no].lane-1) {
                        lbl_1_bss_14B60[no].endRotY = -90.0f;
                        lbl_1_bss_14B60[no].endPos.x -= 300.0f;
                        lbl_1_bss_14B60[no].speed = 50.0f;
                        lbl_1_bss_14B60[no].lane--;
                        movedF = 1;
                    } else if(lbl_1_bss_14B60[no].lane == 1) {
                        lbl_1_bss_14B60[no].endRotY = -90.0f;
                        lbl_1_bss_14B60[no].endPos.x -= 600.0f;
                        lbl_1_bss_14B60[no].speed = 100.0f;
                        lbl_1_bss_14B60[no].lane = -1;
                        movedF = 1;
                    }
                }
                if(stkX > 0 && lbl_1_bss_14B60[no].lane != 1) {
                    if(no == 0 || lbl_1_bss_14B60[0].lane != lbl_1_bss_14B60[no].lane+1) {
                        lbl_1_bss_14B60[no].endRotY = 90.0f;
                        lbl_1_bss_14B60[no].endPos.x += 300.0f;
                        lbl_1_bss_14B60[no].speed = 50.0f;
                        lbl_1_bss_14B60[no].lane++;
                        movedF = 1;
                    } else if(lbl_1_bss_14B60[no].lane == -1) {
                        lbl_1_bss_14B60[no].endRotY = 90.0f;
                        lbl_1_bss_14B60[no].endPos.x += 600.0f;
                        lbl_1_bss_14B60[no].speed = 100.0f;
                        lbl_1_bss_14B60[no].lane = 1;
                        movedF = 1;
                    }
                }
                if(movedF) {
                    lbl_1_bss_14B60[no].subMode = 1;
                }
            } else if(no == 0 || (no == 1 && lbl_1_bss_14B60[0].lane != lbl_1_bss_14B60[1].lane)) {
                lbl_1_bss_14B60[no].subMode = 0;
                result = 1;
            }
            break;

        case 1:
            fn_1_A2E4(no, 5.0f+lbl_1_bss_14B60[no].speed);
            fn_1_17BC(&lbl_1_bss_15288->models[mdlNo].pos.x, lbl_1_bss_14B60[no].speed, lbl_1_bss_14B60[no].startPos.x, lbl_1_bss_14B60[no].endPos.x);
            if(!fn_1_17BC(&lbl_1_bss_15288->models[mdlNo].rot.y, speed, lbl_1_bss_14B60[no].startRot.y, lbl_1_bss_14B60[no].endRotY)) {
                lbl_1_bss_14B60[no].subMode = 2;
            }
            break;

        case 2:
            fn_1_A2E4(no, 5.0f+lbl_1_bss_14B60[no].speed);
            if(fn_1_17BC(&lbl_1_bss_15288->models[mdlNo].pos.x, lbl_1_bss_14B60[no].speed, lbl_1_bss_14B60[no].startPos.x, lbl_1_bss_14B60[no].endPos.x) <= speed-(speed/2.0f)) {
                lbl_1_bss_14B60[no].subMode = 3;
            }
            break;

        case 3:
            fn_1_17BC(&lbl_1_bss_15288->models[mdlNo].pos.x, lbl_1_bss_14B60[no].speed, lbl_1_bss_14B60[no].startPos.x, lbl_1_bss_14B60[no].endPos.x);
            fn_1_17BC(&lbl_1_bss_15288->models[mdlNo].rot.y, speed, lbl_1_bss_14B60[no].endRotY, 0.0f);
            if(fn_1_A2E4(no, 5.0f+lbl_1_bss_14B60[no].speed)) {
                lbl_1_bss_14B60[no].subMode = 0;
            }
            break;
    }
    return result;
}

/* asm 3140-3504, 357 insns. Duellist no hops into the box of their lane. */
s16 fn_1_8750(s16 no)
{
    float x;
    float zBase;
    float radius;
    float zRadius;
    M546_PLAYER *pl;
    s16 result;
    s8 mdlNo;

    pl = &lbl_1_bss_15288->player[no];
    result = 0;
    mdlNo = no+27;
    switch(lbl_1_bss_14B60[no].subMode) {
        case 0:
            fn_1_19A4(lbl_1_bss_14C40.timer);
            lbl_1_bss_14B60[no].angleZ = 90.0f;
            lbl_1_bss_14B60[no].angleX = 90.0f;
            lbl_1_bss_14B60[no].subMode = 1;
            break;

        case 1:
            radius = lbl_1_data_4C4;
            x = lbl_1_data_450[lbl_1_bss_15288->chr[no].charNo][0]+(300.0f*lbl_1_bss_14B60[no].lane);
            zRadius = lbl_1_data_4B8.z-lbl_1_data_450[lbl_1_bss_15288->chr[no].charNo][1];
            zBase = lbl_1_data_450[lbl_1_bss_15288->chr[no].charNo][1];
            lbl_1_bss_15288->models[mdlNo].pos.x = x+(radius*cos((M_PI*lbl_1_bss_14B60[no].angleX)/180.0));
            lbl_1_bss_15288->models[mdlNo].pos.z = zBase+(zRadius*sin((M_PI*lbl_1_bss_14B60[no].angleZ)/180.0));
            lbl_1_bss_14B60[no].angleZ -= 3.375f;
            lbl_1_bss_14B60[no].angleX -= 2.25f;
            lbl_1_bss_15288->models[mdlNo].rot.y += 4.5f;
            if(fn_1_A2E4(no, 80.0f)) {
                lbl_1_bss_15288->models[mdlNo].pos.x = lbl_1_data_450[lbl_1_bss_15288->chr[no].charNo][0]+(300.0f*lbl_1_bss_14B60[no].lane);
                lbl_1_bss_15288->models[mdlNo].pos.z = lbl_1_data_450[lbl_1_bss_15288->chr[no].charNo][1];
                lbl_1_bss_15288->models[mdlNo].rot.y = 0.0f;
                lbl_1_bss_14B60[no].subMode = 2;
            }
            break;

        case 2:
            pl->shiftMode = 1;
            pl->shiftMotNo = 5;
            pl->shiftTime = 0.0f;
            pl->shiftSpeed = 16.0f;
            pl->shiftAttr = HU3D_MOTATTR_LOOP;
            lbl_1_bss_14B60[no].subMode = 3;
            break;

        case 3:
            lbl_1_bss_14B60[no].subMode = 0;
            result = 1;
            break;
    }
    return result;
}

/* asm 3507-3732, 216 insns. Duellist no's lane opens and they climb out. */
s16 fn_1_8CE4(s16 no)
{
    M546_PLAYER *pl;
    s16 result;
    s16 pan;

    pl = &lbl_1_bss_15288->player[no];
    result = 0;
    switch(lbl_1_bss_14B60[no].subMode) {
        case 0:
            lbl_1_bss_14B60[no].timer = 0;
            lbl_1_bss_14B60[no].subMode = 1;
            break;

        case 1:
            if(lbl_1_bss_14B60[no].timer++ >= 120) {
                pan = (lbl_1_bss_14B60[no].lane*32)+64;
                fn_1_56EC(1, 127, pan);
                fn_1_55AC(1, 1000);
                pl->attrReset = HU3D_MOTATTR_LOOP;
                pl->shiftMode = 1;
                pl->shiftMotNo = 6;
                pl->shiftTime = 0.0f;
                pl->shiftSpeed = 4.0f;
                pl->shiftAttr = HU3D_MOTATTR_NONE;
                lbl_1_bss_14B60[no].subMode = 2;
            }
            break;

        case 2:
            if(pl->shiftMode == 3) {
                lbl_1_bss_14B60[no].subMode = 3;
            }
            break;

        case 3:
            if(fn_1_A0BC(3, lbl_1_bss_14B60[no].lane)) {
                lbl_1_bss_14B60[no].subMode = 4;
            }
            break;

        case 4:
            if(fn_1_A0BC(4, lbl_1_bss_14B60[no].lane)) {
                lbl_1_bss_14B60[no].subMode = 5;
            }
            break;

        case 5:
            if(lbl_1_bss_14B60[no].timer++ >= 30) {
                pl->shiftMode = 1;
                pl->shiftMotNo = 0;
                pl->shiftTime = 0.0f;
                pl->shiftSpeed = 20.0f;
                pl->shiftAttr = HU3D_MOTATTR_LOOP;
                fn_1_56EC(0, 127, (lbl_1_bss_14B60[no].lane*32)+64);
                lbl_1_bss_14B60[no].subMode = 6;
            }
            break;

        case 6:
            if(fn_1_A0BC(2, lbl_1_bss_14B60[no].lane)) {
                result = 1;
            }
            break;
    }
    return result;
}

/* asm 3735-3819, 77 insns. The lanes' reveal: a wait, then each duellist's lane. */
s16 fn_1_9044(void)
{
    s16 result = 0;
    s16 unk = 0;

    switch(lbl_1_bss_15288->mode[1]) {
        case 0:
            lbl_1_bss_14B60[0].timer = 0;
            lbl_1_bss_14B60[1].timer = 0;
            lbl_1_bss_14C40.waitTimer = 10;
            if(lbl_1_bss_14C40.waitTimer == 0) {
                lbl_1_bss_14C40.waitTimer = 180;
            }
            lbl_1_bss_15288->mode[1] = 1;
            break;

        case 1:
            if(lbl_1_bss_14C40.waitTimer-- <= 0) {
                lbl_1_bss_15288->mode[1] = 2;
            }
            break;

        case 2:
            if(fn_1_9178()) {
                lbl_1_bss_15288->mode[1] = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* asm 3822-3884, 54 insns. Run what each duellist's lane holds: the box, the paper, or the confetti. */
s16 fn_1_9178(void)
{
    s16 i;
    s16 ok;

    ok = 1;
    for(i=0; i<2; i++) {
        switch(lbl_1_bss_14C40.order[lbl_1_bss_14B60[i].lane+1]) {
            case 0:
                ok *= fn_1_9250(i);
                break;

            case 1:
                ok *= fn_1_9920(i);
                break;

            case 2:
                ok *= fn_1_9B7C(i);
                break;
        }
    }
    return ok;
}

/* asm 3887-4336, 436 insns. The box drops on duellist no and squashes them. */
s32 fn_1_9250(s16 no)
{
    s32 result = 0;
    s8 mdlNo = no+27;
    float height[13] = { 150.0f, 170.0f, 188.0f, 169.0f, 164.0f, 180.0f, 210.0f, 150.0f, 150.0f, 150.0f, 150.0f, 150.0f, 150.0f };

    switch(lbl_1_bss_14B60[no].subMode) {
        case 0:
            lbl_1_bss_14C40.dropSpeed = -8.259f;
            fn_1_56EC(2, 127, (lbl_1_bss_14B60[no].lane*32)+64);
            lbl_1_bss_14B60[no].timer = 0;
            lbl_1_bss_14B60[no].subMode = 1;
            break;

        case 1:
            if(lbl_1_bss_14B60[no].timer++ >= 60) {
                lbl_1_bss_14B60[no].timer = 0;
                lbl_1_bss_14B60[no].subMode = 2;
            }
            break;

        case 2:
            Hu3DModelAttrReset(lbl_1_bss_15288->models[0].modelId, HU3D_ATTR_DISPOFF);
            Hu3DModelShadowDispOn(lbl_1_bss_15288->models[11].modelId);
            lbl_1_bss_15288->models[0].pos.x = lbl_1_bss_15288->models[mdlNo].pos.x;
            lbl_1_bss_15288->models[0].pos.y = 1000.0f;
            lbl_1_bss_15288->models[0].pos.z = lbl_1_bss_15288->models[mdlNo].pos.z;
            lbl_1_bss_15288->models[11].pos = lbl_1_bss_15288->models[0].pos;
            lbl_1_bss_15288->models[11].pos.y = 101.0f;
            lbl_1_bss_14B60[no].subMode = 3;
            break;

        case 3:
            lbl_1_bss_14C40.dropSpeed -= 0.753f;
            lbl_1_bss_15288->models[0].pos.y += lbl_1_bss_14C40.dropSpeed;
            if(lbl_1_bss_15288->models[0].pos.y <= 100.0f) {
                lbl_1_bss_15288->models[0].pos.y = 100.0f;
                fn_1_1F4C(&lbl_1_bss_15288->models[0].pos);
                fn_1_5804(2);
                fn_1_56EC(3, 127, (lbl_1_bss_14B60[no].lane*32)+64);
                omVibrate(lbl_1_bss_15288->chr[no].no, 32, 12, 0);
                lbl_1_bss_14B60[no].subMode = 4;
            }
            if(100.0f+height[lbl_1_bss_15288->chr[no].charNo] >= lbl_1_bss_15288->models[0].pos.y) {
                if(lbl_1_bss_14B60[no].squashSeF == 0) {
                    CharFXPlayVolPan(lbl_1_bss_15288->chr[no].charNo, 0x202, 127, (lbl_1_bss_14B60[no].lane*32)+64);
                    lbl_1_bss_14B60[no].squashSeF = 1;
                }
                lbl_1_bss_14B60[no].scale.y -= 0.2f;
                if(lbl_1_bss_14B60[no].scale.y <= 0.1f) {
                    lbl_1_bss_14B60[no].scale.x = 0.1f;
                    lbl_1_bss_14B60[no].scale.y = 0.1f;
                    lbl_1_bss_14B60[no].scale.z = 0.1f;
                }
                Hu3DModelScaleSetV(lbl_1_bss_15288->models[mdlNo].modelId, &lbl_1_bss_14B60[no].scale);
            }
            if((lbl_1_bss_14C40.boxTpLvl += 0.025f) >= 1.0f) {
                lbl_1_bss_14C40.boxTpLvl = 1.0f;
            }
            Hu3DModelTPLvlSet(lbl_1_bss_15288->models[11].modelId, lbl_1_bss_14C40.boxTpLvl);
            break;

        case 4:
            if(lbl_1_bss_14B60[no].timer++ >= 60) {
                result = 1;
            }
            break;
    }
    return result;
}

/* asm 4339-4502, 151 insns. Paper is thrown up over duellist no. */
s32 fn_1_9920(s16 no)
{
    s32 result = 0;
    s16 pan;
    HuVecF pos;

    switch(lbl_1_bss_14B60[no].subMode) {
        case 0:
            if(lbl_1_bss_14B60[no].timer++ > 20) {
                lbl_1_bss_14B60[no].subMode = 1;
            }
            break;

        case 1:
            pos = lbl_1_bss_15288->models[no+27].pos;
            pos.y = 700.0f;
            fn_1_3E2C(lbl_1_bss_15288, 4, pos, 5);
            switch(lbl_1_bss_14B60[no].lane) {
                case -1:
                    pan = 40;
                    break;

                case 0:
                    pan = 64;
                    break;

                case 1:
                    pan = 88;
                    break;
            }
            if(lbl_1_bss_14C40.order[lbl_1_bss_14B60[no^1].lane+1] != 2) {
                fn_1_56EC(4, 127, pan);
            }
            lbl_1_bss_14B60[no].timer = 0;
            lbl_1_bss_14B60[no].subMode = 2;
            break;

        case 2:
            if(lbl_1_bss_14B60[no].timer++ > 120) {
                result = 1;
            }
            break;
    }
    return result;
}

/* asm 4505-4775, 255 insns. Confetti falls on duellist no from three party balls. */
s32 fn_1_9B7C(s16 no)
{
    s16 i;
    s32 result = 0;
    s16 pan;
    HuVecF pos;

    switch(lbl_1_bss_14B60[no].subMode) {
        case 0:
            if(lbl_1_bss_14B60[no].timer++ > 20) {
                lbl_1_bss_14B60[no].subMode = 1;
            }
            break;

        case 1:
            pos = lbl_1_bss_15288->models[no+27].pos;
            pos.y = 700.0f;
            lbl_1_bss_15288->models[8].pos.x = pos.x-50.0f;
            lbl_1_bss_15288->models[8].pos.y = 700.0f;
            lbl_1_bss_15288->models[8].pos.z = pos.z;
            lbl_1_bss_15288->models[9].pos.x = pos.x;
            lbl_1_bss_15288->models[9].pos.y = 700.0f;
            lbl_1_bss_15288->models[9].pos.z = pos.z;
            lbl_1_bss_15288->models[10].pos.x = 50.0f+pos.x;
            lbl_1_bss_15288->models[10].pos.y = 700.0f;
            lbl_1_bss_15288->models[10].pos.z = pos.z;
            fn_1_2E18(lbl_1_bss_15288, 4, pos);
            switch(lbl_1_bss_14B60[no].lane) {
                case -1:
                    pan = 40;
                    break;

                case 0:
                    pan = 64;
                    break;

                case 1:
                    pan = 88;
                    break;
            }
            fn_1_56EC(5, 127, pan);
            lbl_1_bss_14B60[no].timer = 0;
            lbl_1_bss_14B60[no].subMode = 2;
            break;

        case 2:
            if(lbl_1_bss_14AB8.activeF & lbl_1_bss_14C40.unk30) {
                for(i=0; i<3; i++) {
                    if((lbl_1_bss_14C40.bombTpLvl[i] += 0.01f) >= 1.0f) {
                        lbl_1_bss_14C40.bombTpLvl[i] = 1.0f;
                    }
                    Hu3DModelTPLvlSet(lbl_1_bss_15288->models[i+8].modelId, lbl_1_bss_14C40.bombTpLvl[i]);
                }
            }
            if(lbl_1_bss_14B60[no].timer++ > 120) {
                result = 1;
            }
            break;
    }
    return result;
}

/* asm 4778-4867, 81 insns. Who won (the better lane), and which way the lanes' sound pans. */
void fn_1_9F78(void)
{
    s16 orderA;
    s16 orderB;

    orderA = lbl_1_bss_14C40.order[lbl_1_bss_14B60[0].lane+1];
    orderB = lbl_1_bss_14C40.order[lbl_1_bss_14B60[1].lane+1];
    if(orderA > orderB) {
        lbl_1_bss_14C40.winner = 0;
        lbl_1_bss_14C40.loser = 1;
    } else if(orderA < orderB) {
        lbl_1_bss_14C40.winner = 1;
        lbl_1_bss_14C40.loser = 0;
    }
    orderA = lbl_1_bss_14B60[0].lane+lbl_1_bss_14B60[1].lane;
    switch(orderA) {
        case -1:
            lbl_1_bss_14C40.seDir = 1;
            break;

        case 0:
            lbl_1_bss_14C40.seDir = 0;
            break;

        case 1:
            lbl_1_bss_14C40.seDir = -1;
            break;
    }
}

/* asm 4870-5012, 138 insns. Move lane's curtain by motion type; 1 once it is there. */
s16 fn_1_A0BC(s16 type, s8 lane)
{
    s16 result = 0;
    s8 mdlNo = lane+2;
    s8 laneMdlNo = lane+13;
    HuVecF param[5] = {
        { 60.0f, 1000.0f, 125.0f },
        { 30.0f, 125.0f, 800.0f },
        { 30.0f, 125.0f, 800.0f },
        { 18.0f, 125.0f, 100.0f },
        { 18.0f, 100.0f, 125.0f }
    };
    float tpLvl;

    if(!fn_1_17BC(&lbl_1_bss_15288->models[mdlNo].pos.y, param[type].x, param[type].y, param[type].z)) {
        result = 1;
    }
    tpLvl = (800.0f-lbl_1_bss_15288->models[mdlNo].pos.y)/675.0f;
    if(tpLvl <= 0.0f) {
        tpLvl = 0.0f;
    }
    if(tpLvl >= 1.0f) {
        tpLvl = 1.0f;
    }
    lbl_1_bss_14C40.laneTpLvl[lane+1] = tpLvl;
    Hu3DModelTPLvlSet(lbl_1_bss_15288->models[laneMdlNo].modelId, lbl_1_bss_14C40.laneTpLvl[lane+1]);
    return result;
}

/* asm 5015-5151, 130 insns. Duellist no's walk cycle: 1 once frames have passed. */
s16 fn_1_A2E4(s16 no, float frames)
{
    s16 result = 0;
    M546_PLAYER *pl = &lbl_1_bss_15288->player[no];

    lbl_1_bss_14B60[no].walkTime += 1.0f;
    switch(lbl_1_bss_14B60[no].walkMode) {
        case 0:
            pl->attrReset = HU3D_MOTATTR_LOOP;
            pl->shiftMode = 1;
            pl->shiftMotNo = 2;
            pl->shiftTime = 0.0f;
            pl->shiftSpeed = 8.0f;
            pl->shiftAttr = HU3D_MOTATTR_LOOP;
            lbl_1_bss_14B60[no].walkTime = 0.0f;
            lbl_1_bss_14B60[no].walkMode = 1;
            break;

        case 1:
            if(10.0f+lbl_1_bss_14B60[no].walkTime >= frames) {
                pl->shiftMode = 1;
                pl->shiftMotNo = 0;
                pl->shiftTime = 0.0f;
                pl->shiftSpeed = 10.0f;
                pl->shiftAttr = HU3D_MOTATTR_LOOP;
                lbl_1_bss_14B60[no].walkMode = 2;
            }
            break;

        case 2:
            if(lbl_1_bss_14B60[no].walkTime >= frames) {
                lbl_1_bss_14B60[no].walkMode = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* asm 5154-5649, 475 insns. The opening: the jingle, the swing's go, the camera pulls in and the curtains come down. */
s16 fn_1_A4EC(void)
{
    s16 result = 0;
    s16 flag = 0;

    switch(lbl_1_bss_14C40.camMode) {
        case 0:
            fn_1_554C();
            lbl_1_bss_14C40.camMode = 1;

        case 1:
            lbl_1_bss_48->rot.x = -2.0f;
            lbl_1_bss_48->zoom = 1800.0f;
            if(lbl_1_bss_15288->count[0] == 60) {
                fn_1_C2A4();
            }
            if(lbl_1_bss_15288->count[0]++ > 200) {
                lbl_1_bss_48->rot.x = -2.0f;
                lbl_1_bss_48->zoom = 1800.0f;
                lbl_1_bss_15288->count[0] = 0;
                lbl_1_bss_14C40.camMode = 2;
            }
            break;

        case 2:
            flag += fn_1_17BC(&lbl_1_bss_48->rot.x, 60.0f, -2.0f, -6.0f);
            flag += fn_1_17BC(&lbl_1_bss_48->zoom, 60.0f, 1800.0f, 830.0f);
            if(flag == 0) {
                lbl_1_bss_14C40.camMode = 3;
            }
            break;

        case 3:
            flag = 1;
            flag *= fn_1_A0BC(0, 0);
            if(lbl_1_bss_14C40.introTimer++ == 30) {
                fn_1_5674(0);
            }
            if(lbl_1_bss_15288->count[0]++ > 20) {
                flag *= fn_1_A0BC(0, -1);
                flag *= fn_1_A0BC(0, 1);
            }
            if(flag) {
                lbl_1_bss_14C40.camMode = 4;
            }
            break;

        case 4:
            lbl_1_bss_15288->count[0] = 0;
            break;
    }
    return result;
}

/* asm 5652-5769, 111 insns. The camera moves in on the winner. */
s16 fn_1_AC58(void)
{
    s16 result = 0;
    s16 sum = 0;
    s8 mdlNo = lbl_1_bss_14C40.winner+27;

    switch(lbl_1_bss_14C40.camMode) {
        case 0:
            if(lbl_1_bss_15288->count[0]++ > 120) {
                lbl_1_bss_15288->count[0] = 0;
                lbl_1_bss_14C40.camMode = 1;
            }
            break;

        case 1:
            sum += fn_1_17BC(&lbl_1_bss_48->center.x, 30.0f, lbl_1_data_450[lbl_1_bss_15288->chr[lbl_1_bss_14C40.winner].charNo][0], lbl_1_bss_15288->models[mdlNo].pos.x);
            sum += fn_1_17BC(&lbl_1_bss_48->zoom, 30.0f, 830.0f, 500.0f);
            if(sum == 0) {
                lbl_1_bss_14C40.camMode = 2;
            }
            break;

        case 2:
            lbl_1_bss_14C40.slideSeMode++;
            result = 1;
            break;
    }
    return result;
}

/* asm 5772-5997, 210 insns. A computer duellist's choice: wait, then maybe move a lane, else confirm. */
void fn_1_AE14(s16 no)
{
    s16 chance;

    switch(lbl_1_bss_14B60[no].comMode) {
        case 0:
            lbl_1_bss_14B60[no].timer = frandmod(60)+30;
            lbl_1_bss_14B60[no].comMode = 1;
            break;

        case 1:
            if(lbl_1_bss_14B60[no].timer-- <= 0) {
                lbl_1_bss_14B60[no].comMode = 2;
            }
            break;

        case 2:
            if(lbl_1_bss_15288->chr[no].dif != 0) {
                chance = frandmod(100);
                if(chance <= lbl_1_bss_14B60[no].comChance && lbl_1_bss_14B60[no].comMoves > 0) {
                    if(no == 0) {
                        if(lbl_1_bss_14B60[no].lane == 0) {
                            if(frandmod(2)) {
                                lbl_1_bss_15288->chr[no].stkX = 1;
                            } else {
                                lbl_1_bss_15288->chr[no].stkX = -1;
                            }
                        } else {
                            lbl_1_bss_15288->chr[no].stkX = lbl_1_bss_14B60[no].lane*-1;
                        }
                    } else {
                        switch(lbl_1_bss_14B60[no].lane) {
                            case -1:
                                lbl_1_bss_15288->chr[no].stkX = 1;
                                break;

                            case 0:
                                lbl_1_bss_15288->chr[no].stkX = lbl_1_bss_14B60[0].lane*-1;
                                break;

                            case 1:
                                lbl_1_bss_15288->chr[no].stkX = -1;
                                break;
                        }
                    }
                    lbl_1_bss_14B60[no].comMoves--;
                    lbl_1_bss_14B60[no].comMode = 0;
                } else {
                    lbl_1_bss_15288->chr[no].btnDown = PAD_BUTTON_A;
                }
            }
            break;
    }
}
