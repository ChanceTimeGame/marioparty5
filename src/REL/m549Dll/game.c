/*
 * m549dll/game.c -- W2 DRAFT, written outside games/ (m553's workflow).
 *
 * The duel: two actor-manager duellists on a round arena, ten moving objects
 * and ten stage objects they can be knocked into, the charge/strike/fall state
 * machines, the computer duellists' target search, and the sequence steps.
 * Written from the reference assembly, functions in reference order.
 *
 * Unlike m549.c this unit is original decompilation: 36 of its 42 functions
 * have no xmatch twin anywhere.
 */

#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/audio.h"
#include "game/frand.h"
#include "game/pad.h"
#include "game/flag.h"
#include "game/printfunc.h"
#include "game/mg/seqman.h"
#include "game/mg/timer.h"
#include "game/mg/actman.h"

#include "REL/m549Dll/m549.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

void fn_1_3B74(M549_WORK *work);
s16 fn_1_4EE0(M549_WORK *work);
s16 fn_1_4FFC(void);
s16 fn_1_50A4(void);
s16 fn_1_5184(void);
s16 fn_1_569C(void);
s16 fn_1_5788(void);
s16 fn_1_57D8(void);
s16 fn_1_5A00(void);
s16 fn_1_5A40(void);
void fn_1_5A98(void);
void fn_1_5CD4(void);
s16 fn_1_6048(s16 player);
s16 fn_1_67E0(s16 player);
s16 fn_1_71B4(s16 player);
s16 fn_1_762C(s16 player);
void fn_1_7CC0(s16 player);
void fn_1_8570(void);
void fn_1_9324(HuVecF *pos, s16 no);
void fn_1_98F0(void);
s16 fn_1_99E8(s16 player);
void fn_1_9DBC(void);
s16 fn_1_9FF4(s16 player, s16 count);
/* fn_1_A18C and fn_1_A898 are `int`: their callers store the result into an
 * s16 with extsh, which CW only emits when the callee is wider. */
int fn_1_A18C(void);
int fn_1_A898(void);
int fn_1_AD78(COL_NARROW_PARAM *a, COL_NARROW_PARAM *b);
void fn_1_ADC8(MGACTOR *actor, int param);
void fn_1_ADDC(void);
void fn_1_BF34(s16 player);
s16 fn_1_C360(s16 player);
s16 fn_1_C418(s16 player);
void fn_1_C64C(s16 player);
void fn_1_CA38(s16 player, s16 no);
s16 fn_1_CDD8(s16 player);
s16 fn_1_D0C4(s16 player, s16 wait);
s16 fn_1_D9E0(s16 player);
s16 fn_1_E160(s16 player, s16 no);
void fn_1_E880(s16 player);
s16 fn_1_E90C(s16 player, s16 no);
void fn_1_F0C8(s16 player);
s16 fn_1_F4A0(s16 player, s16 no);
s16 fn_1_FDB0(s16 player);

/* --- .data --- */

/* The duellists' seventeen motions, handed to MgPlayerCreate. */
unsigned int lbl_1_data_440[17] = {
    0x008700A7, 0x008C007A, 0x008C007B, 0x008C0003, 0x008C0004, 0x008C0005,
    0x008C0050, 0x008C0008, 0x008C000A, 0x008C0009, 0x008C000F, 0x008C0010,
    0x008C0012, 0x008C0013, 0x008C0017, 0x008C0018, 0x00000000
};

/* How much of the stick a duellist keeps at each charge level. */
float lbl_1_data_484[5] = { 1.0f, 0.9f, 0.8f, 0.6f, 0.4f };

/* The radius every "is anything in the way" test in this unit uses. */
float lbl_1_data_498 = 525.0f;

/* The three duellist drivers fn_1_762C dispatches on. */
s16 (*lbl_1_data_49C[3])(s16 player) = { fn_1_6048, fn_1_67E0, fn_1_71B4 };

/* --- .bss (CodeWarrior lays it out in reverse definition order) --- */

M549_WORK *lbl_1_bss_15F4;          /* set by fn_1_3B74 */
/* unreferenced; they give lbl_1_bss_15E0 its 0x14 bytes */
u32 lbl_1_bss_15F0;
u32 lbl_1_bss_15EC;
u32 lbl_1_bss_15E8;
u32 lbl_1_bss_15E4;
u32 lbl_1_bss_15E0;

/*
 * 1243 insns. The duel's init: clear the overlay state, publish the work
 * pointer, build all sixty-eight stage models, create the two duellists'
 * actors and hook their item models, seed both computer duellists and start
 * the timer.
 */
void fn_1_3B74(M549_WORK *work)
{
    MGACTOR_PARAM param;
    s16 i;
    s16 j;

    memset(&lbl_1_bss_580, 0, sizeof(M549_GAME));
    memset(lbl_1_bss_3B0, 0, sizeof(lbl_1_bss_3B0));
    memset(&lbl_1_bss_0, 0, sizeof(M549_ACTORS));
    memset(lbl_1_bss_158, 0, sizeof(lbl_1_bss_158));
    memset(lbl_1_bss_18, 0, sizeof(lbl_1_bss_18));
    lbl_1_bss_15F4 = work;
    for(i=0; i<11; i++) {
        lbl_1_bss_580.seF[i] = -1;
    }
    lbl_1_bss_3B0[0].idleCnt = 100;
    lbl_1_bss_3B0[1].idleCnt = 100;
    for(i=0, j=0; i<=2; i++, j++) {
        lbl_1_bss_15F4->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_15F4->stageDataTbl[j], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_15F4->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_15F4->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_15F4->models[i].modelId, 2);
        lbl_1_bss_15F4->models[i].pos.x = 0.0f;
        lbl_1_bss_15F4->models[i].pos.y = 0.0f;
        lbl_1_bss_15F4->models[i].pos.z = 0.0f;
        lbl_1_bss_15F4->models[i].rot.x = 0.0f;
        lbl_1_bss_15F4->models[i].rot.y = 0.0f;
        lbl_1_bss_15F4->models[i].rot.z = 0.0f;
        Hu3DModelAttrReset(lbl_1_bss_15F4->models[i].modelId, HU3D_ATTR_DISPOFF);
        if(i == 1) {
            lbl_1_bss_15F4->models[i].rot.x = 0.0f;
            lbl_1_bss_15F4->models[i].rot.y = 22.5f;
            lbl_1_bss_15F4->models[i].rot.z = 0.0f;
            Hu3DModelAttrSet(lbl_1_bss_15F4->models[i].modelId, HU3D_MOTATTR_LOOP);
            Hu3DMotionSpeedSet(lbl_1_bss_15F4->models[i].modelId, 0.25f);
            Hu3DMotionTimeSet(lbl_1_bss_15F4->models[i].modelId, 0.0f);
        }
        if(i == 2) {
            Hu3DModelShadowMapSet(lbl_1_bss_15F4->models[i].modelId);
            Hu3DModelAttrSet(lbl_1_bss_15F4->models[i].modelId, HU3D_MOTATTR_LOOP);
            Hu3DMotionSpeedSet(lbl_1_bss_15F4->models[i].modelId, 0.25f);
            Hu3DMotionTimeSet(lbl_1_bss_15F4->models[i].modelId, 0.0f);
            Hu3DModelScaleSet(lbl_1_bss_15F4->models[i].modelId, 0.85f, 0.85f, 0.85f);
            Hu3DModelLayerSet(lbl_1_bss_15F4->models[i].modelId, 0);
        }
    }
    for(i=3, j=3; i<=4; i++, j++) {
        lbl_1_bss_15F4->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_15F4->stageDataTbl[j], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_15F4->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_15F4->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_15F4->models[i].modelId, 0);
        lbl_1_bss_15F4->models[i].pos.x = 0.0f;
        lbl_1_bss_15F4->models[i].pos.y = 0.0f;
        lbl_1_bss_15F4->models[i].pos.z = 0.0f;
        lbl_1_bss_15F4->models[i].rot.x = 0.0f;
        lbl_1_bss_15F4->models[i].rot.y = 0.0f;
        lbl_1_bss_15F4->models[i].rot.z = 0.0f;
        Hu3DModelAttrReset(lbl_1_bss_15F4->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(lbl_1_bss_15F4->models[i].modelId, HU3D_MOTATTR_LOOP);
        Hu3DMotionTimeSet(lbl_1_bss_15F4->models[i].modelId, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_15F4->models[i].modelId, 0.0f);
    }
    for(i=5; i<=14; i++) {
        lbl_1_bss_15F4->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_15F4->stageDataTbl[5], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_15F4->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_15F4->models[i].modelId, 2);
        Hu3DModelLayerSet(lbl_1_bss_15F4->models[i].modelId, 1);
        lbl_1_bss_15F4->models[i].pos.x = 0.0f;
        lbl_1_bss_15F4->models[i].pos.y = 0.0f;
        lbl_1_bss_15F4->models[i].pos.z = 0.0f;
        lbl_1_bss_15F4->models[i].rot.x = 0.0f;
        lbl_1_bss_15F4->models[i].rot.y = 0.0f;
        lbl_1_bss_15F4->models[i].rot.z = 0.0f;
    }
    for(i=0x1a; i<=0x23; i++) {
        lbl_1_bss_15F4->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_15F4->stageDataTbl[8], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_15F4->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_15F4->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_15F4->models[i].modelId, 1);
        lbl_1_bss_15F4->models[i].pos.x = 0.0f;
        lbl_1_bss_15F4->models[i].pos.y = 0.0f;
        lbl_1_bss_15F4->models[i].pos.z = 0.0f;
        lbl_1_bss_15F4->models[i].rot.x = 0.0f;
        lbl_1_bss_15F4->models[i].rot.y = 0.0f;
        lbl_1_bss_15F4->models[i].rot.z = 0.0f;
    }
    for(i=0xf; i<=0x18; i++) {
        lbl_1_bss_15F4->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_15F4->stageDataTbl[6], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_15F4->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_15F4->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_15F4->models[i].modelId, 3);
        lbl_1_bss_15F4->models[i].pos.x = 0.0f;
        lbl_1_bss_15F4->models[i].pos.y = 0.0f;
        lbl_1_bss_15F4->models[i].pos.z = 0.0f;
        lbl_1_bss_15F4->models[i].rot.x = 0.0f;
        lbl_1_bss_15F4->models[i].rot.y = 0.0f;
        lbl_1_bss_15F4->models[i].rot.z = 0.0f;
        Hu3DModelScaleSet(lbl_1_bss_15F4->models[i].modelId, 1.0f, 1.0f, 1.0f);
        Hu3DModelAttrReset(lbl_1_bss_15F4->models[i].modelId, HU3D_MOTATTR_LOOP);
        Hu3DMotionTimeSet(lbl_1_bss_15F4->models[i].modelId, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_15F4->models[i].modelId, 0.0f);
    }
    lbl_1_bss_15F4->models[25].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_15F4->stageDataTbl[7], HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_15F4->models[25].modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(lbl_1_bss_15F4->models[25].modelId, 1);
    lbl_1_bss_15F4->models[25].pos.x = 0.0f;
    lbl_1_bss_15F4->models[25].pos.y = -15.0f;
    lbl_1_bss_15F4->models[25].pos.z = 0.0f;
    lbl_1_bss_15F4->models[25].rot.x = 0.0f;
    lbl_1_bss_15F4->models[25].rot.y = 0.0f;
    lbl_1_bss_15F4->models[25].rot.z = 0.0f;
    lbl_1_bss_0.colMdlId[0] = lbl_1_bss_15F4->models[25].modelId;
    MgActorColMapInit(lbl_1_bss_0.colMdlId, 1, 10);
    param.height = 150.0f;
    param.radius = 45.0f;
    param.param = 0;
    param.type = 0;
    param.attr = 0x8000;
    param.narrowHook = fn_1_AD78;
    param.correctHookParam = 0;
    param.correctHook = fn_1_ADC8;
    lbl_1_bss_0.player[0] = MgPlayerCreate(lbl_1_bss_15F4->chr[0].no, &param, 1, 1, ~(MGPLAYER_ACTFLAG_JUMP|MGPLAYER_ACTFLAG_PUNCH|MGPLAYER_ACTFLAG_KICK|MGPLAYER_ACTFLAG_HIPDROP|MGPLAYER_ACTFLAG_STUN), lbl_1_data_440);
    lbl_1_bss_0.player[0]->actor->pos.x = -400.0f;
    lbl_1_bss_0.player[0]->actor->pos.y = 120.0f;
    lbl_1_bss_0.player[0]->actor->pos.z = 0.0f;
    lbl_1_bss_0.player[0]->actor->rotY = 90.0f;
    Hu3DModelLayerSet(lbl_1_bss_0.player[0]->actor->mdlId, 0);
    Hu3DModelShadowSet(lbl_1_bss_0.player[0]->actor->mdlId);
    Hu3DModelShadowDispOn(lbl_1_bss_0.player[0]->actor->mdlId);
    lbl_1_bss_15F4->models[68].modelId = lbl_1_bss_0.player[0]->actor->mdlId;
    param.param = 1;
    lbl_1_bss_0.player[1] = MgPlayerCreate(lbl_1_bss_15F4->chr[1].no, &param, 1, 1, ~(MGPLAYER_ACTFLAG_JUMP|MGPLAYER_ACTFLAG_PUNCH|MGPLAYER_ACTFLAG_KICK|MGPLAYER_ACTFLAG_HIPDROP|MGPLAYER_ACTFLAG_STUN), lbl_1_data_440);
    lbl_1_bss_0.player[1]->actor->pos.x = 400.0f;
    lbl_1_bss_0.player[1]->actor->pos.y = 120.0f;
    lbl_1_bss_0.player[1]->actor->pos.z = 0.0f;
    lbl_1_bss_0.player[1]->actor->rotY = -90.0f;
    Hu3DModelLayerSet(lbl_1_bss_0.player[1]->actor->mdlId, 0);
    Hu3DModelShadowSet(lbl_1_bss_0.player[1]->actor->mdlId);
    Hu3DModelShadowDispOn(lbl_1_bss_0.player[1]->actor->mdlId);
    lbl_1_bss_15F4->models[69].modelId = lbl_1_bss_0.player[1]->actor->mdlId;
    CharModelStepFxSet(lbl_1_bss_15F4->chr[0].charNo, 2);
    CharModelStepFxSet(lbl_1_bss_15F4->chr[1].charNo, 2);
    CharEffectLayerSet(0);
    lbl_1_bss_3B0[0].itemHook = CharModelItemHookGet(lbl_1_bss_15F4->chr[0].charNo, 1, 0);
    Hu3DModelHookSet(lbl_1_bss_15F4->models[68].modelId, lbl_1_bss_3B0[0].itemHook, lbl_1_bss_15F4->models[3].modelId);
    lbl_1_bss_3B0[1].itemHook = CharModelItemHookGet(lbl_1_bss_15F4->chr[1].charNo, 1, 0);
    Hu3DModelHookSet(lbl_1_bss_15F4->models[69].modelId, lbl_1_bss_3B0[1].itemHook, lbl_1_bss_15F4->models[4].modelId);
    fn_1_BF34(0);
    fn_1_BF34(1);
    fn_1_128AC();
    fn_1_23FC();
    fn_1_5CD4();
    lbl_1_bss_580.mgTimer = fn_1_1AEC(0, 60, 0, 292.0f, 64.0f);
}

/* 71 insns. Init hook: build, park both pads and latch the duellists' start positions. */
s16 fn_1_4EE0(M549_WORK *work)
{
    s16 result;
    HU3DMODEL *model;

    result = 1;
    fn_1_3B74(work);
    MgPlayerPadSet(lbl_1_bss_0.player[0], 0, 0, 0, 0);
    MgPlayerPadSet(lbl_1_bss_0.player[1], 0, 0, 0, 0);
    MgActorExec();
    model = &Hu3DData[lbl_1_bss_15F4->models[68].modelId];
    lbl_1_bss_3B0[0].pos = model->pos;
    model = &Hu3DData[lbl_1_bss_15F4->models[69].modelId];
    lbl_1_bss_3B0[1].pos = model->pos;
    fn_1_115A8(work);
    return result;
}

/* 42 insns. Fade-in hook. */
s16 fn_1_4FFC(void)
{
    s16 result;
    int i;

    result = 0;
    for(i=0; i<2; i++) {
        lbl_1_bss_15F4->chr[i].btn = 0;
        lbl_1_bss_15F4->chr[i].btnDown = 0;
    }
    result = fn_1_A18C();
    fn_1_762C(0);
    fn_1_762C(1);
    fn_1_8570();
    fn_1_98F0();
    fn_1_ADDC();
    fn_1_5CD4();
    return result;
}

/* 56 insns. Start hook. */
s16 fn_1_50A4(void)
{
    s16 result;
    int i;

    result = 0;
    lbl_1_bss_580.mode = 0;
    lbl_1_bss_580.unk02 = 0;
    lbl_1_bss_580.unk04 = 0;
    lbl_1_bss_580.timer = 0;
    for(i=0; i<2; i++) {
        lbl_1_bss_15F4->chr[i].btn = 0;
        lbl_1_bss_15F4->chr[i].btnDown = 0;
    }
    fn_1_762C(0);
    fn_1_762C(1);
    fn_1_8570();
    fn_1_98F0();
    fn_1_ADDC();
    fn_1_5CD4();
    return result;
}

/*
 * 326 insns. The main hook: run each computer duellist and push its pad, drive
 * both duellists, then take the actors round the collision and put them back
 * where it left them.
 */
s16 fn_1_5184(void)
{
    s16 result;
    s16 endF;
    s16 i;
    int playerNo;
    HuVecF pos;

    result = 0;
    endF = 0;
    switch(lbl_1_bss_580.mode) {
        case 0:
            fn_1_1B60(lbl_1_bss_580.mgTimer);
            lbl_1_bss_580.mode++;

        case 1:
            for(i=0; i<2; i++) {
                if(lbl_1_bss_580.unk20 == 0 && lbl_1_bss_3B0[i].comF != 0) {
                    fn_1_C360(i);
                    MgPlayerPadSet(lbl_1_bss_0.player[i], lbl_1_bss_3B0[i].stkX, lbl_1_bss_3B0[i].stkY, lbl_1_bss_3B0[i].btnDown, lbl_1_bss_3B0[i].btn);
                    lbl_1_bss_15F4->chr[i].btn = lbl_1_bss_3B0[i].btn;
                    lbl_1_bss_15F4->chr[i].btnDown = lbl_1_bss_3B0[i].btnDown;
                }
                fn_1_762C(i);
            }
            if(lbl_1_bss_580.unk20 != 0) {
                lbl_1_bss_580.mode++;
            }
            break;

        case 2:
            fn_1_1BB4(lbl_1_bss_580.mgTimer);
            if(lbl_1_bss_580.winner != 0) {
                MgSeqWinnerSet(lbl_1_bss_15F4->chr[lbl_1_bss_580.winner&1].charNo, CHARNO_NONE, CHARNO_NONE, CHARNO_NONE);
                playerNo = lbl_1_bss_15F4->chr[lbl_1_bss_580.winner&1].no;
                if(!_CheckFlag(FLAG_MG_PRACTICE)) {
                    GwPlayer[playerNo].mgCoinBonus = 10;
                }
            } else {
                MgSeqWinnerSet(CHARNO_NONE, CHARNO_NONE, CHARNO_NONE, CHARNO_NONE);
            }
            fn_1_35DC(1, 100);
            result = 1;
            break;
    }
    for(i=0; i<2; i++) {
        if(lbl_1_bss_3B0[i].padOffF != 0) {
            MgPlayerPadSet(lbl_1_bss_0.player[i], 0, 0, 0, 0);
        }
    }
    MgActorPosGet(lbl_1_bss_0.player[0]->actor, &pos);
    lbl_1_bss_3B0[0].posOld.x = pos.x;
    lbl_1_bss_3B0[0].posOld.y = pos.y;
    lbl_1_bss_3B0[0].posOld.z = pos.z;
    MgActorPosGet(lbl_1_bss_0.player[1]->actor, &pos);
    lbl_1_bss_3B0[1].posOld.x = pos.x;
    lbl_1_bss_3B0[1].posOld.y = pos.y;
    lbl_1_bss_3B0[1].posOld.z = pos.z;
    MgActorExec();
    MgActorPosGet(lbl_1_bss_0.player[0]->actor, &pos);
    lbl_1_bss_3B0[0].pos.x = pos.x;
    lbl_1_bss_3B0[0].pos.y = pos.y;
    lbl_1_bss_3B0[0].pos.z = pos.z;
    MgActorPosGet(lbl_1_bss_0.player[1]->actor, &pos);
    lbl_1_bss_3B0[1].pos.x = pos.x;
    lbl_1_bss_3B0[1].pos.y = pos.y;
    lbl_1_bss_3B0[1].pos.z = pos.z;
    fn_1_8570();
    fn_1_98F0();
    fn_1_ADDC();
    pos.x = lbl_1_bss_3B0[0].pos.x;
    pos.y = lbl_1_bss_3B0[0].pos.y;
    pos.z = lbl_1_bss_3B0[0].pos.z;
    MgActorPosUpdate(lbl_1_bss_0.player[0]->actor, &pos);
    pos.x = lbl_1_bss_3B0[1].pos.x;
    pos.y = lbl_1_bss_3B0[1].pos.y;
    pos.z = lbl_1_bss_3B0[1].pos.z;
    MgActorPosUpdate(lbl_1_bss_0.player[1]->actor, &pos);
    fn_1_9DBC();
    fn_1_5CD4();
    return result;
}

/* 59 insns. Finish hook. */
s16 fn_1_569C(void)
{
    s16 result;

    result = 0;
    lbl_1_bss_580.mode = 0;
    lbl_1_bss_580.unk02 = 0;
    lbl_1_bss_580.unk04 = 0;
    lbl_1_bss_580.timer = 0;
    lbl_1_bss_3B0[0].seqMode = 0;
    lbl_1_bss_3B0[1].seqMode = 0;
    fn_1_762C(0);
    fn_1_762C(1);
    fn_1_8570();
    fn_1_98F0();
    MgPlayerPadSet(lbl_1_bss_0.player[0], 0, 0, 0, 0);
    MgPlayerPadSet(lbl_1_bss_0.player[1], 0, 0, 0, 0);
    MgActorExec();
    fn_1_5CD4();
    return result;
}

/* 20 insns. Pre-winner hook. */
s16 fn_1_5788(void)
{
    s16 result;

    result = 0;
    result = fn_1_A898();
    fn_1_762C(0);
    fn_1_762C(1);
    fn_1_8570();
    fn_1_98F0();
    fn_1_5CD4();
    return result;
}

/*
 * 138 insns. Winner hook: pose the winner and the loser once. On a draw both
 * duellists take the lose pose, and the lose voice plays only if neither is
 * already down. Every index is winner&1 or a literal, so no path reaches
 * player[-1].
 */
s16 fn_1_57D8(void)
{
    s16 result;
    DS_PLAYER *pl;

    result = 0;
    if(lbl_1_bss_15F4->mode[0] == 0) {
        if(lbl_1_bss_580.winner != 0) {
            pl = &lbl_1_bss_15F4->player[lbl_1_bss_580.winner&1];
            pl->motNo = 3;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
        } else {
            pl = &lbl_1_bss_15F4->player[0];
            pl->motNo = 4;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            pl = &lbl_1_bss_15F4->player[1];
            pl->motNo = 4;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            if(lbl_1_bss_3B0[0].loseF == 0 && lbl_1_bss_3B0[1].loseF == 0) {
                CharLoseVoicePlay(lbl_1_bss_15F4->chr[0].charNo, lbl_1_bss_15F4->chr[1].charNo, CHARNO_NONE, CHARNO_NONE);
            }
        }
        lbl_1_bss_15F4->mode[0] = 1;
    }
    fn_1_762C(0);
    fn_1_762C(1);
    fn_1_8570();
    fn_1_98F0();
    fn_1_5CD4();
    if(lbl_1_bss_580.winner != 0) {
        CharModelVoicePanSet(lbl_1_bss_15F4->chr[lbl_1_bss_580.winner&1].charNo, 64);
    }
    return result;
}

/* 16 insns. Fade-out hook. */
s16 fn_1_5A00(void)
{
    s16 result;

    result = 1;
    fn_1_762C(0);
    fn_1_762C(1);
    fn_1_5CD4();
    return result;
}

/* 22 insns. Close hook. */
s16 fn_1_5A40(void)
{
    s16 result;

    result = 1;
    fn_1_3B54();
    MgActorKill(lbl_1_bss_0.player[0]->actor);
    MgActorKill(lbl_1_bss_0.player[1]->actor);
    return result;
}

/*
 * 143 insns. Unreferenced: push all sixty-eight stage models at Hu3D, then pan
 * each duellist's voice from its model's x.
 */
void fn_1_5A98(void)
{
    HU3DMODEL *modelA;
    HU3DMODEL *modelB;
    s16 i;
    float panF;
    s16 pan;

    modelA = &Hu3DData[lbl_1_bss_15F4->models[68].modelId];
    modelB = &Hu3DData[lbl_1_bss_15F4->models[69].modelId];
    for(i=0; i<0x44; i++) {
        Hu3DModelPosSet(lbl_1_bss_15F4->models[i].modelId, lbl_1_bss_15F4->models[i].pos.x, lbl_1_bss_15F4->models[i].pos.y, lbl_1_bss_15F4->models[i].pos.z);
        Hu3DModelRotSet(lbl_1_bss_15F4->models[i].modelId, lbl_1_bss_15F4->models[i].rot.x, lbl_1_bss_15F4->models[i].rot.y, lbl_1_bss_15F4->models[i].rot.z);
    }
    panF = 0.053333335f*modelA->pos.x;
    pan = 64.0f+panF;
    CharModelVoicePanSet(lbl_1_bss_15F4->chr[0].charNo, pan);
    panF = 0.053333335f*modelB->pos.x;
    pan = 64.0f+panF;
    CharModelVoicePanSet(lbl_1_bss_15F4->chr[1].charNo, pan);
}

/*
 * 221 insns. The per-frame push: park the sky model on camera 2, push all
 * sixty-eight stage models at Hu3D, pan both duellists' voices, then re-place
 * the cameras, the light and the shadow.
 */
void fn_1_5CD4(void)
{
    HU3DMODEL *modelB;
    HU3DMODEL *modelA;
    s16 i;
    float panF;
    s16 pan;

    fontcolor = 0;
    Hu3DModelCameraSet(lbl_1_bss_15F4->models[51].modelId, 2);
    Hu3DModelAttrSet(lbl_1_bss_15F4->models[51].modelId, HU3D_ATTR_ZCMP_OFF);
    Hu3DModelLayerSet(lbl_1_bss_15F4->models[51].modelId, 7);
    lbl_1_bss_15F4->models[51].pos.x = -1100.0f+lbl_1_bss_14->pos.x;
    lbl_1_bss_15F4->models[51].pos.y = 1150.0f+(lbl_1_bss_14->pos.y-953.0f);
    lbl_1_bss_15F4->models[51].pos.z = -800.0f+(lbl_1_bss_14->pos.z-1556.0f);
    modelA = &Hu3DData[lbl_1_bss_15F4->models[68].modelId];
    modelB = &Hu3DData[lbl_1_bss_15F4->models[69].modelId];
    for(i=0; i<0x44; i++) {
        Hu3DModelPosSet(lbl_1_bss_15F4->models[i].modelId, lbl_1_bss_15F4->models[i].pos.x, lbl_1_bss_15F4->models[i].pos.y, lbl_1_bss_15F4->models[i].pos.z);
        Hu3DModelRotSet(lbl_1_bss_15F4->models[i].modelId, lbl_1_bss_15F4->models[i].rot.x, lbl_1_bss_15F4->models[i].rot.y, lbl_1_bss_15F4->models[i].rot.z);
    }
    panF = 0.053333335f*modelA->pos.x;
    pan = 64.0f+panF;
    CharModelVoicePanSet(lbl_1_bss_15F4->chr[0].charNo, pan);
    panF = 0.053333335f*modelB->pos.x;
    pan = 64.0f+panF;
    CharModelVoicePanSet(lbl_1_bss_15F4->chr[1].charNo, pan);
    fn_1_97C(0);
    fn_1_97C(1);
    fn_1_1124();
    fn_1_1524();
}

/*
 * 486 insns. One duellist's charge: A winds the item up (0), holding it spins
 * the pitch up to the 120-frame cap (1), releasing it throws an object and
 * poses the swing (2), and 3 hands control back.
 */
s16 fn_1_6048(s16 player)
{
    DS_PLAYER *pl;
    s16 result;
    s16 mdlNo;
    s16 pan;
    s16 pitch;
    s16 no;
    float panF;
    float time;

    pl = &lbl_1_bss_15F4->player[player];
    result = 0;
    mdlNo = player+3;
    switch(lbl_1_bss_3B0[player].actMode) {
        case 0:
            if(lbl_1_bss_580.unk22 != 0) {
                break;
            }
            time = Hu3DMotionTimeGet(lbl_1_bss_15F4->models[mdlNo].modelId);
            if(0.0f != time) {
                break;
            }
            if(!(lbl_1_bss_15F4->chr[player].btnDown & PAD_BUTTON_A)) {
                break;
            }
            if(lbl_1_bss_3B0[player].hitWait != 0) {
                break;
            }
            Hu3DModelAttrReset(lbl_1_bss_15F4->models[mdlNo].modelId, HU3D_MOTATTR_REV);
            Hu3DMotionTimeSet(lbl_1_bss_15F4->models[mdlNo].modelId, 0.0f);
            Hu3DMotionSpeedSet(lbl_1_bss_15F4->models[mdlNo].modelId, 0.24166666f);
            panF = 0.026666667f*lbl_1_bss_15F4->models[player+0x44].pos.x;
            pan = 64.0f+panF;
            fn_1_3754((int)player, 127, pan);
            fn_1_38A4((int)player, -8000);
            lbl_1_bss_3B0[player].chargeCnt = 1;
            lbl_1_bss_3B0[player].actMode++;
            break;

        case 1:
            if(lbl_1_bss_580.unk22 == 0) {
            if((int)lbl_1_bss_15F4->chr[player].btn & PAD_BUTTON_A) {
                if(++lbl_1_bss_3B0[player].chargeCnt >= 120) {
                    Hu3DMotionTimeSet(lbl_1_bss_15F4->models[mdlNo].modelId, 29.0f);
                    Hu3DMotionSpeedSet(lbl_1_bss_15F4->models[mdlNo].modelId, 0.0f);
                    lbl_1_bss_3B0[player].chargeCnt = 120;
                } else {
                    Hu3DMotionSpeedSet(lbl_1_bss_15F4->models[mdlNo].modelId, 0.24166666f);
                }
                panF = 0.026666667f*lbl_1_bss_3B0[player].pos.x;
                pan = 64.0f+panF;
                pitch = (lbl_1_bss_3B0[player].chargeCnt*133)-8000;
                fn_1_3814((int)player, pan);
                fn_1_38A4((int)player, pitch);
            } else {
                Hu3DModelAttrSet(lbl_1_bss_15F4->models[mdlNo].modelId, HU3D_MOTATTR_REV);
                Hu3DMotionSpeedSet(lbl_1_bss_15F4->models[mdlNo].modelId, 1.5f);
                pl->motNo = 6;
                pl->speed = 1.0f;
                pl->time = 0.0f;
                pl->attr = 0;
                pl->attrReset = HU3D_MOTATTR_LOOP;
                fn_1_7CC0(player);
                no = lbl_1_bss_3B0[player].chargeCnt/30;
                switch(no) {
                    case 0:
                    case 1:
                        no = 0;
                        break;
                    case 2:
                    case 3:
                        no = 1;
                        break;
                    case 4:
                        no = 2;
                }
                no += 2;
                panF = 0.026666667f*lbl_1_bss_3B0[player].pos.x;
                pan = 64.0f+panF;
                fn_1_3754(no, 127, pan);
                fn_1_39C4(player, 100);
                lbl_1_bss_3B0[player].hitWait = 10;
                lbl_1_bss_3B0[player].chargeCnt = 0;
                lbl_1_bss_3B0[player].padOffF = 1;
                lbl_1_bss_3B0[player].actMode++;
            }
            } else {
                Hu3DModelAttrSet(lbl_1_bss_15F4->models[mdlNo].modelId, HU3D_MOTATTR_REV);
                Hu3DMotionSpeedSet(lbl_1_bss_15F4->models[mdlNo].modelId, 1.5f);
                fn_1_39C4(player, 100);
                lbl_1_bss_3B0[player].actMode = 3;
            }
            break;

        case 2:
            if(pl->endF != 0 || pl->time >= 20.0f) {
                Hu3DModelAttrReset(lbl_1_bss_15F4->models[mdlNo].modelId, HU3D_MOTATTR_REV);
                Hu3DMotionSpeedSet(lbl_1_bss_15F4->models[mdlNo].modelId, 0.0f);
                pl->motNo = 5;
                pl->speed = 1.0f;
                pl->time = 0.0f;
                pl->attr = HU3D_MOTATTR_LOOP;
                pl->attrReset = 0;
                lbl_1_bss_3B0[player].actMode++;
            }
            break;

        case 3:
            if(lbl_1_bss_580.unk22 == 0) {
                lbl_1_bss_3B0[player].padOffF = 0;
            }
            lbl_1_bss_3B0[player].actMode = 0;
            result = 0;
            break;
    }
    return result;
}

/*
 * 629 insns. One duellist's knock-back: face the hit (0), wait for the shift to
 * finish (1), slide along the hit vector until the motion ends (2), land (3)
 * and report done (4). The tail blinks the duellist's model while it is down
 * and keeps the charge sound in step with the A button.
 */
s16 fn_1_67E0(s16 player)
{
    DS_PLAYER *pl;
    s16 result;
    s16 mdlNo;
    s16 motNo;
    s16 vol;
    s16 pan;
    float mag;
    float angle;
    float rotY;
    float dy;
    float panF;

    pl = &lbl_1_bss_15F4->player[player];
    result = 0;
    mdlNo = player+3;
    switch(lbl_1_bss_3B0[player].motMode) {
        case 0:
            mag = 2.5f+(2.5f*lbl_1_bss_3B0[player].hitType);
            lbl_1_bss_3B0[player].vel.x = mag*sin((M_PI*lbl_1_bss_3B0[player].angle)/180.0);
            lbl_1_bss_3B0[player].vel.z = mag*cos((M_PI*lbl_1_bss_3B0[player].angle)/180.0);
            angle = lbl_1_bss_3B0[player].angle;
            rotY = lbl_1_bss_0.player[player]->actor->rotY;
            dy = angle-rotY;
            if(dy >= -90.0f && dy <= 90.0f) {
                motNo = 8;
            } else {
                motNo = 7;
            }
            pl->shiftMode = 1;
            pl->shiftMotNo = motNo;
            pl->shiftTime = 0.0f;
            pl->shiftSpeed = 4.0f;
            pl->shiftAttr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            Hu3DMotionSpeedSet(lbl_1_bss_15F4->models[mdlNo].modelId, 0.0f);
            if(lbl_1_bss_3B0[player].hitObjF != 0) {
                switch(lbl_1_bss_3B0[player].hitType) {
                    case 0:
                        omVibrate(lbl_1_bss_15F4->chr[player].no, 20, 6, 6);
                        break;
                    case 1:
                        omVibrate(lbl_1_bss_15F4->chr[player].no, 30, 6, 6);
                        break;
                    case 2:
                        omVibrate(lbl_1_bss_15F4->chr[player].no, 20, 4, 2);
                        break;
                    case 3:
                        omVibrate(lbl_1_bss_15F4->chr[player].no, 30, 4, 2);
                        break;
                    case 4:
                        omVibrate(lbl_1_bss_15F4->chr[player].no, 30, 12, 0);
                        break;
                }
            }
            switch(lbl_1_bss_3B0[player].hitType) {
                case 0:
                    vol = 84;
                    break;
                case 1:
                    vol = 96;
                    break;
                case 2:
                    vol = 108;
                    break;
                case 3:
                    vol = 120;
                    break;
                case 4:
                    vol = 127;
                    break;
            }
            panF = 0.026666667f*lbl_1_bss_3B0[player].pos.x;
            pan = 64.0f+panF;
            fn_1_3754(8, vol, pan);
            lbl_1_bss_3B0[player].unk00A = 0;
            lbl_1_bss_3B0[player].motMode++;

        case 1:
            if(pl->shiftMode != 3) {
                break;
            }
            pl->speed = 1.5f;
            lbl_1_bss_3B0[player].motMode++;
            break;

        case 2:
            lbl_1_bss_3B0[player].pos.x += lbl_1_bss_3B0[player].vel.x;
            lbl_1_bss_3B0[player].pos.z += lbl_1_bss_3B0[player].vel.z;
            MgActorPosUpdate(lbl_1_bss_0.player[player]->actor, &lbl_1_bss_3B0[player].pos);
            if(pl->endF == 0) {
                break;
            }
            lbl_1_bss_3B0[player].velOld = lbl_1_bss_3B0[player].vel;
            lbl_1_bss_3B0[player].vel.x = 0.0f;
            lbl_1_bss_3B0[player].vel.z = 0.0f;
            pl->motNo = 9;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            lbl_1_bss_3B0[player].motMode++;
            break;

        case 3:
            if(pl->endF == 0) {
                break;
            }
            pl->motNo = 5;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = HU3D_MOTATTR_LOOP;
            pl->attrReset = 0;
            lbl_1_bss_3B0[player].motMode++;
            break;

        case 4:
            lbl_1_bss_3B0[player].motMode = 0;
            result = 1;
            break;
    }
    if(result == 0) {
        if(Hu3DModelAttrGet(lbl_1_bss_15F4->models[player+0x44].modelId) & HU3D_ATTR_DISPOFF) {
            Hu3DModelAttrReset(lbl_1_bss_15F4->models[player+0x44].modelId, HU3D_ATTR_DISPOFF);
        } else {
            Hu3DModelAttrSet(lbl_1_bss_15F4->models[player+0x44].modelId, HU3D_ATTR_DISPOFF);
        }
    }
    if(lbl_1_bss_3B0[player].actMode == 1) {
        if((int)lbl_1_bss_15F4->chr[player].btn & PAD_BUTTON_A) {
            panF = 0.026666667f*lbl_1_bss_3B0[player].pos.x;
            pan = 64.0f+panF;
            fn_1_3814((int)player, pan);
        } else {
            fn_1_39C4(player, 100);
            Hu3DModelAttrSet(lbl_1_bss_15F4->models[mdlNo].modelId, HU3D_MOTATTR_REV);
            Hu3DMotionSpeedSet(lbl_1_bss_15F4->models[mdlNo].modelId, 1.5f);
            lbl_1_bss_3B0[player].chargeCnt = 0;
            lbl_1_bss_3B0[player].actMode = 0;
        }
    } else if(lbl_1_bss_3B0[player].actMode == 0) {
        Hu3DModelAttrSet(lbl_1_bss_15F4->models[mdlNo].modelId, HU3D_MOTATTR_REV);
        Hu3DMotionSpeedSet(lbl_1_bss_15F4->models[mdlNo].modelId, 1.5f);
    }
    return result;
}

/*
 * 286 insns. One duellist's fall off the arena: the fall sound and a stop to
 * the charge (0), pause the actor (1), shift the falling motion in (2), then
 * accelerate down past the shadow cut-off until y reaches -4000 (3).
 */
s16 fn_1_71B4(s16 player)
{
    HU3DMODEL *model;
    DS_PLAYER *pl;
    s16 result;
    s16 vol;
    float panF;

    model = &Hu3DData[lbl_1_bss_15F4->models[player+0x44].modelId];
    pl = &lbl_1_bss_15F4->player[player];
    result = 0;
    switch(lbl_1_bss_3B0[player].fallMode) {
        case 0:
            panF = 0.026666667f*lbl_1_bss_3B0[player].pos.x;
            vol = 64.0f+panF;
            if(vol > 80) {
                vol = 80;
            } else if(vol < 48) {
                vol = 48;
            }
            fn_1_3754(9, 127, vol);
            if(lbl_1_bss_3B0[player].chargeCnt != 0) {
                fn_1_39C4(player, 100);
            }
            lbl_1_bss_3B0[player].fallMode++;

        case 1:
            Hu3DModelAttrReset(lbl_1_bss_15F4->models[player+0x44].modelId, HU3D_ATTR_DISPOFF);
            model->pos.x += lbl_1_bss_3B0[player].vel.x;
            model->pos.z += lbl_1_bss_3B0[player].vel.z;
            MgPlayerPauseOn(lbl_1_bss_0.player[player]);
            lbl_1_bss_3B0[player].vel.y = 0.0f;
            lbl_1_bss_3B0[player].fallMode++;
            break;

        case 2:
            model->pos.x += lbl_1_bss_3B0[player].vel.x;
            model->pos.z += lbl_1_bss_3B0[player].vel.z;
            pl->shiftMode = 1;
            pl->shiftMotNo = 2;
            pl->shiftTime = 0.0f;
            pl->shiftSpeed = 16.0f;
            pl->shiftAttr = HU3D_MOTATTR_LOOP;
            pl->attrReset = 0;
            lbl_1_bss_3B0[player].fallMode++;
            break;

        case 3:
            model->pos.x += lbl_1_bss_3B0[player].vel.x;
            model->pos.z += lbl_1_bss_3B0[player].vel.z;
            if(lbl_1_bss_3B0[player].vel.y >= 20.0f && lbl_1_bss_3B0[player].vel.y <= 30.0f) {
                Hu3DModelShadowDispOff(lbl_1_bss_0.player[player]->actor->mdlId);
            }
            lbl_1_bss_3B0[player].vel.y += 0.5f;
            if((model->pos.y -= lbl_1_bss_3B0[player].vel.y) <= -4000.0f) {
                lbl_1_bss_3B0[player].fallMode++;
            }
            break;

        case 4:
            break;
    }
    return result;
}

/*
 * 421 insns. The per-duellist driver: a duellist that has been hit switches to
 * the knock-back machine, the three machines run through lbl_1_data_49C, the
 * model blinks while it is invulnerable, and a human duellist's stick is scaled
 * down by its charge level before the actor manager sees it.
 */
s16 fn_1_762C(s16 player)
{
    s16 result;
    s16 doneF;
    float stkXf;
    float stkYf;
    s8 stkX;
    s8 stkY;

    result = 0;
    doneF = 0;
    if(lbl_1_bss_3B0[player].idleCnt > 20) {
        if(lbl_1_bss_3B0[player].hitObjF != 0 || lbl_1_bss_3B0[player].hitStgF != 0) {
            lbl_1_bss_3B0[player].padOffF = 1;
            if(lbl_1_bss_3B0[player].actMode != 1) {
                lbl_1_bss_3B0[player].actMode = 0;
            }
            lbl_1_bss_3B0[player].mode = 1;
        }
    }
    doneF = lbl_1_data_49C[lbl_1_bss_3B0[player].mode](player);
    if(doneF != 0) {
        if(lbl_1_bss_3B0[player].hitObjF != 0 || lbl_1_bss_3B0[player].hitStgF != 0) {
            if(lbl_1_bss_580.unk22 == 0) {
                lbl_1_bss_3B0[player].padOffF = 0;
            }
            lbl_1_bss_3B0[player].idleCnt = 0;
            lbl_1_bss_3B0[player].mode = 0;
        }
    }
    if(++lbl_1_bss_3B0[player].idleCnt <= 20 && lbl_1_bss_3B0[player].mode == 0) {
        if(Hu3DModelAttrGet(lbl_1_bss_15F4->models[player+0x44].modelId) & HU3D_ATTR_DISPOFF) {
            Hu3DModelAttrReset(lbl_1_bss_15F4->models[player+0x44].modelId, HU3D_ATTR_DISPOFF);
        } else {
            Hu3DModelAttrSet(lbl_1_bss_15F4->models[player+0x44].modelId, HU3D_ATTR_DISPOFF);
        }
    } else if(lbl_1_bss_3B0[player].mode == 0 && (lbl_1_bss_3B0[player].hitObjF != 0 || lbl_1_bss_3B0[player].hitStgF != 0)) {
        lbl_1_bss_3B0[player].hitObjF = 0;
        lbl_1_bss_3B0[player].hitStgF = 0;
        Hu3DModelAttrReset(lbl_1_bss_15F4->models[player+0x44].modelId, HU3D_ATTR_DISPOFF);
    } else {
        lbl_1_bss_3B0[player].idleCnt = 120;
    }
    if(lbl_1_bss_3B0[player].hitWait-- <= 0) {
        lbl_1_bss_3B0[player].hitWait = 0;
    }
    lbl_1_bss_3B0[player].chargeLv = lbl_1_bss_3B0[player].chargeCnt/30;
    if(lbl_1_bss_3B0[player].comF == 0) {
        stkX = (s8)HuPadStkX[lbl_1_bss_0.player[player]->padNo];
        stkY = (s8)HuPadStkY[lbl_1_bss_0.player[player]->padNo];
        stkXf = stkX*lbl_1_data_484[lbl_1_bss_3B0[player].chargeLv];
        stkYf = stkY*lbl_1_data_484[lbl_1_bss_3B0[player].chargeLv];
        lbl_1_bss_3B0[player].stkXf = stkXf;
        lbl_1_bss_3B0[player].stkYf = stkYf;
        HuPadStkX[lbl_1_bss_0.player[player]->padNo] = stkXf;
        HuPadStkY[lbl_1_bss_0.player[player]->padNo] = stkYf;
    }
    if(lbl_1_bss_3B0[player].mode == 2) {
        fn_1_99E8(player);
    } else if(lbl_1_bss_580.unk20 != 0) {
        fn_1_99E8(player);
    }
    return result;
}

/*
 * 556 insns. Throw one moving object: take the first free slot, seed it from
 * the thrower's facing and charge level, place it and its shadow at the item
 * hook, and show both models.
 */
void fn_1_7CC0(s16 no)
{
    HuVecF pos;
    s16 i;
    s16 mdlNo;
    float scale;

    for(i=0; i<10; i++) {
        if(lbl_1_bss_158[i].activeF != 0) {
            continue;
        }
        mdlNo = i+5;
        lbl_1_bss_158[i].activeF = 1;
        lbl_1_bss_158[i].state = lbl_1_bss_158[i].mode = 0;
        lbl_1_bss_158[i].hitF = 0;
        lbl_1_bss_158[i].owner = no;
        lbl_1_bss_158[i].deadF = 0;
        lbl_1_bss_158[i].angle = lbl_1_bss_0.player[no]->actor->rotY;
        lbl_1_bss_158[i].level = lbl_1_bss_3B0[no].chargeCnt/30;
        lbl_1_bss_158[i].charge = lbl_1_bss_3B0[no].chargeCnt;
        lbl_1_bss_158[i].range = 50.0f+(10.0f*lbl_1_bss_158[i].level);
        lbl_1_bss_158[i].scale = 12.5f;
        lbl_1_bss_158[i].zScale = 0.0f;
        lbl_1_bss_158[i].scaleSpeed = 0.05f+(0.05f*lbl_1_bss_158[i].level);
        lbl_1_bss_158[i].vel.x = (15.0f+(5.0f*lbl_1_bss_158[i].level))*sin((M_PI*lbl_1_bss_158[i].angle)/180.0);
        lbl_1_bss_158[i].vel.z = (15.0f+(5.0f*lbl_1_bss_158[i].level))*cos((M_PI*lbl_1_bss_158[i].angle)/180.0);
        Hu3DModelObjPosGet(lbl_1_bss_15F4->models[no+0x44].modelId, lbl_1_bss_3B0[no].itemHook, &pos);
        lbl_1_bss_158[i].pos.x = pos.x+(40.0*sin((M_PI*lbl_1_bss_158[i].angle)/180.0));
        lbl_1_bss_158[i].pos.y = 20.0f+pos.y;
        lbl_1_bss_158[i].pos.z = pos.z+(40.0*cos((M_PI*lbl_1_bss_158[i].angle)/180.0));
        lbl_1_bss_15F4->models[mdlNo].pos = lbl_1_bss_158[i].pos;
        lbl_1_bss_15F4->models[mdlNo].rot.y = 90.0f+lbl_1_bss_158[i].angle;
        scale = lbl_1_bss_158[i].scale/50.0f;
        Hu3DModelScaleSet(lbl_1_bss_15F4->models[mdlNo].modelId, scale, scale, scale);
        Hu3DModelAttrReset(lbl_1_bss_15F4->models[mdlNo].modelId, HU3D_ATTR_DISPOFF);
        mdlNo = i+0x1a;
        lbl_1_bss_15F4->models[mdlNo].pos = lbl_1_bss_158[i].pos;
        lbl_1_bss_15F4->models[mdlNo].pos.y = 130.0f;
        lbl_1_bss_15F4->models[mdlNo].rot.y = lbl_1_bss_158[i].angle;
        Hu3DMotionTimeSet(lbl_1_bss_15F4->models[mdlNo].modelId, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_15F4->models[mdlNo].modelId, 1.0f+(0.25f*lbl_1_bss_158[i].level));
        Hu3DModelAttrReset(lbl_1_bss_15F4->models[mdlNo].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelScaleSet(lbl_1_bss_15F4->models[mdlNo].modelId, 1.0f, 1.0f, lbl_1_bss_158[i].zScale);
        break;
    }
}

/*
 * 877 insns. Step every live moving object: retire it once it is 645 units out
 * or its owner is gone, grow it to its range (state 0) then shrink it away past
 * 695 (state 1), and run its shadow's seven-step grow/hold/shrink through the
 * jumptable.
 */
void fn_1_8570(void)
{
    s16 i;
    s16 shdNo;
    s16 mdlNo;
    float mag;
    float dist;
    float scale;
    float time;

    for(i=0; i<10; i++) {
        if(lbl_1_bss_158[i].activeF == 0) {
            continue;
        }
        shdNo = i+0x1a;
        mdlNo = i+5;
        mag = (lbl_1_bss_158[i].pos.x*lbl_1_bss_158[i].pos.x)+(lbl_1_bss_158[i].pos.z*lbl_1_bss_158[i].pos.z);
        dist = sqrt(mag);
        if(dist >= 645.0f && lbl_1_bss_158[i].hitF == 0) {
            lbl_1_bss_158[i].hitF = 1;
            lbl_1_bss_158[i].mode = 2;
        }
        if(lbl_1_bss_158[i].deadF != 0 && lbl_1_bss_158[i].hitF == 0) {
            Hu3DModelAttrSet(lbl_1_bss_15F4->models[mdlNo].modelId, HU3D_ATTR_DISPOFF);
            lbl_1_bss_158[i].hitF = 1;
            lbl_1_bss_158[i].state = 2;
            lbl_1_bss_158[i].mode = 4;
        }
        switch(lbl_1_bss_158[i].state) {
            case 0:
                lbl_1_bss_158[i].pos.x += lbl_1_bss_158[i].vel.x;
                lbl_1_bss_158[i].pos.z += lbl_1_bss_158[i].vel.z;
                if((lbl_1_bss_158[i].scale += 10.0f) >= lbl_1_bss_158[i].range) {
                    lbl_1_bss_158[i].scale = lbl_1_bss_158[i].range;
                    lbl_1_bss_158[i].state++;
                }
                scale = lbl_1_bss_158[i].scale/50.0f;
                Hu3DModelScaleSet(lbl_1_bss_15F4->models[mdlNo].modelId, scale, scale, scale);
                break;

            case 1:
                lbl_1_bss_158[i].pos.x += lbl_1_bss_158[i].vel.x;
                lbl_1_bss_158[i].pos.z += lbl_1_bss_158[i].vel.z;
                if(dist >= 695.0f) {
                    scale = lbl_1_bss_158[i].scale/50.0f;
                    Hu3DModelScaleSet(lbl_1_bss_15F4->models[mdlNo].modelId, scale, scale, scale);
                    if((lbl_1_bss_158[i].scale -= 1.5f) <= 0.0f) {
                        Hu3DModelAttrSet(lbl_1_bss_15F4->models[mdlNo].modelId, HU3D_ATTR_DISPOFF);
                        lbl_1_bss_158[i].activeF = 0;
                        lbl_1_bss_158[i].scale = 0.0f;
                    }
                }
                break;

            case 2:
                break;
        }
        lbl_1_bss_15F4->models[mdlNo].pos = lbl_1_bss_158[i].pos;
        switch(lbl_1_bss_158[i].mode) {
            case 0:
                lbl_1_bss_15F4->models[shdNo].pos.x = lbl_1_bss_15F4->models[mdlNo].pos.x;
                lbl_1_bss_15F4->models[shdNo].pos.z = lbl_1_bss_15F4->models[mdlNo].pos.z;
                if((lbl_1_bss_158[i].zScale += lbl_1_bss_158[i].scaleSpeed) >= 1.0f) {
                    lbl_1_bss_158[i].zScale = 1.0f;
                }
                Hu3DModelScaleSet(lbl_1_bss_15F4->models[shdNo].modelId, 1.0f, 1.0f, lbl_1_bss_158[i].zScale);
                time = Hu3DMotionTimeGet(lbl_1_bss_15F4->models[shdNo].modelId);
                if(time >= 30.0f) {
                    lbl_1_bss_158[i].mode++;
                }
                break;

            case 1:
                lbl_1_bss_15F4->models[shdNo].pos.x = lbl_1_bss_15F4->models[mdlNo].pos.x;
                lbl_1_bss_15F4->models[shdNo].pos.z = lbl_1_bss_15F4->models[mdlNo].pos.z;
                if((lbl_1_bss_158[i].zScale += lbl_1_bss_158[i].scaleSpeed) >= 1.0f) {
                    lbl_1_bss_158[i].zScale = 1.0f;
                }
                Hu3DModelScaleSet(lbl_1_bss_15F4->models[shdNo].modelId, 1.0f, 1.0f, lbl_1_bss_158[i].zScale);
                time = Hu3DMotionTimeGet(lbl_1_bss_15F4->models[shdNo].modelId);
                if(time >= 60.0f) {
                    Hu3DMotionTimeSet(lbl_1_bss_15F4->models[shdNo].modelId, 30.0f);
                }
                break;

            case 2:
                Hu3DMotionTimeSet(lbl_1_bss_15F4->models[shdNo].modelId, 60.0f);
                lbl_1_bss_158[i].mode++;

            case 3:
                lbl_1_bss_15F4->models[shdNo].pos.x = lbl_1_bss_15F4->models[mdlNo].pos.x;
                lbl_1_bss_15F4->models[shdNo].pos.z = lbl_1_bss_15F4->models[mdlNo].pos.z;
                time = Hu3DMotionTimeGet(lbl_1_bss_15F4->models[shdNo].modelId);
                if(time >= 87.0f) {
                    Hu3DModelAttrSet(lbl_1_bss_15F4->models[shdNo].modelId, HU3D_ATTR_DISPOFF);
                    lbl_1_bss_158[i].mode = 6;
                }
                break;

            case 4:
                Hu3DMotionTimeSet(lbl_1_bss_15F4->models[shdNo].modelId, 60.0f);
                lbl_1_bss_158[i].mode++;

            case 5:
                if((lbl_1_bss_158[i].zScale -= lbl_1_bss_158[i].scaleSpeed) <= 0.0f) {
                    lbl_1_bss_158[i].zScale = 0.0f;
                }
                Hu3DModelScaleSet(lbl_1_bss_15F4->models[shdNo].modelId, 1.0f, 1.0f, lbl_1_bss_158[i].zScale);
                time = Hu3DMotionTimeGet(lbl_1_bss_15F4->models[shdNo].modelId);
                if(time >= 87.0f || 0.0f == lbl_1_bss_158[i].zScale) {
                    Hu3DModelAttrSet(lbl_1_bss_15F4->models[shdNo].modelId, HU3D_ATTR_DISPOFF);
                    lbl_1_bss_158[i].activeF = 0;
                    lbl_1_bss_158[i].mode = 6;
                }
                break;

            case 6:
                break;
        }
    }
}

/*
 * 371 insns. Spawn the impact ring at pos for a hit of strength `no`: the first
 * free stage-object slot, sized and scaled from `no`, both pads buzzed and the
 * matching impact sound panned from the ring's x.
 */
void fn_1_9324(HuVecF *pos, s16 no)
{
    s16 i;
    s16 mdlNo;
    s16 j;
    s16 seNo;
    s16 count;
    s16 pan;
    float panF;

    for(i=0; i<10; i++) {
        if(lbl_1_bss_18[i].activeF != 0) {
            continue;
        }
        mdlNo = i+0xf;
        lbl_1_bss_18[i].activeF = 1;
        lbl_1_bss_18[i].endF = lbl_1_bss_18[i].unk04 = 0;
        lbl_1_bss_18[i].wait = 30;
        lbl_1_bss_18[i].unk08 = 0;
        lbl_1_bss_18[i].no = no;
        lbl_1_bss_18[i].radius = 100.0f+(50.0f*lbl_1_bss_18[i].no);
        lbl_1_bss_18[i].size = 100.0f+(50.0f*lbl_1_bss_18[i].no);
        lbl_1_bss_18[i].pos = *pos;
        lbl_1_bss_18[i].pos.y = 150.0f;
        lbl_1_bss_15F4->models[mdlNo].pos = lbl_1_bss_18[i].pos;
        count = lbl_1_bss_18[i].size/50.0f;
        Hu3DModelAttrReset(lbl_1_bss_15F4->models[mdlNo].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelScaleSet(lbl_1_bss_15F4->models[mdlNo].modelId, count, count, count);
        Hu3DMotionTimeSet(lbl_1_bss_15F4->models[mdlNo].modelId, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_15F4->models[mdlNo].modelId, 1.0f);
        for(j=0; j<2; j++) {
            switch(lbl_1_bss_18[i].no) {
                case 0:
                    omVibrate(lbl_1_bss_15F4->chr[j].no, 20, 6, 6);
                    break;
                case 1:
                    omVibrate(lbl_1_bss_15F4->chr[j].no, 30, 6, 6);
                    break;
                case 2:
                    omVibrate(lbl_1_bss_15F4->chr[j].no, 20, 4, 2);
                    break;
                case 3:
                    omVibrate(lbl_1_bss_15F4->chr[j].no, 30, 4, 2);
                    break;
                case 4:
                    omVibrate(lbl_1_bss_15F4->chr[j].no, 30, 12, 0);
                    break;
            }
        }
        switch(no) {
            case 0:
            case 1:
                seNo = 0;
                break;
            case 2:
            case 3:
                seNo = 1;
                break;
            case 4:
                seNo = 2;
                break;
        }
        seNo += 5;
        panF = 0.026666667f*lbl_1_bss_18[i].pos.x;
        pan = 64.0f+panF;
        fn_1_3754(seNo, 127, pan);
        break;
    }
}

/* 62 insns. Retire every impact ring whose motion has run out. */
void fn_1_98F0(void)
{
    s16 i;
    s16 mdlNo;

    for(i=0; i<10; i++) {
        if(lbl_1_bss_18[i].activeF == 0) {
            continue;
        }
        mdlNo = i+0xf;
        switch(lbl_1_bss_18[i].endF) {
            case 0:
                if(Hu3DMotionEndCheck(lbl_1_bss_15F4->models[mdlNo].modelId)) {
                    lbl_1_bss_18[i].activeF = 0;
                    Hu3DModelAttrSet(lbl_1_bss_15F4->models[mdlNo].modelId, HU3D_ATTR_DISPOFF);
                }
                break;
        }
    }
}

/*
 * 245 insns. Let one duellist's item go: unhook it from the hand and drop the
 * idle motion in (0), then spin and shrink it away (1). 2 reports done.
 */
s16 fn_1_99E8(s16 player)
{
    DS_PLAYER *pl;
    s16 result;

    pl = &lbl_1_bss_15F4->player[player];
    result = 0;
    switch(lbl_1_bss_3B0[player].hookMode) {
        case 0:
            Hu3DModelObjPosGet(lbl_1_bss_15F4->models[player+0x44].modelId, lbl_1_bss_3B0[player].itemHook, &lbl_1_bss_15F4->models[player+3].pos);
            lbl_1_bss_15F4->models[player+3].rot.y = 90.0f-(180.0f*player);
            Hu3DModelHookObjReset(lbl_1_bss_15F4->models[player+0x44].modelId, lbl_1_bss_3B0[player].itemHook);
            if(lbl_1_bss_3B0[player].mode == 0) {
                pl->shiftMode = 1;
                pl->shiftMotNo = 0;
                pl->shiftTime = 0.0f;
                pl->shiftSpeed = 16.0f;
                pl->shiftAttr = HU3D_MOTATTR_LOOP;
                pl->attrReset = 0;
            }
            lbl_1_bss_3B0[player].scale = 1.0f;
            lbl_1_bss_3B0[player].hookMode++;
            break;

        case 1:
            lbl_1_bss_3B0[player].scale -= 0.035f;
            lbl_1_bss_15F4->models[player+3].pos.y += 10.0f;
            lbl_1_bss_15F4->models[player+3].rot.x += 20.0f;
            Hu3DModelScaleSet(lbl_1_bss_15F4->models[player+3].modelId, lbl_1_bss_3B0[player].scale, lbl_1_bss_3B0[player].scale, lbl_1_bss_3B0[player].scale);
            if(lbl_1_bss_3B0[player].scale <= 0.1f) {
                Hu3DModelAttrSet(lbl_1_bss_15F4->models[player+3].modelId, HU3D_ATTR_DISPOFF);
                lbl_1_bss_3B0[player].hookMode++;
            }
            break;

        case 2:
            result = 1;
            break;
    }
    return result;
}

/*
 * 142 insns. The end check: the timer running out or either duellist going off
 * the arena ends the duel and names the other one the winner; the round is over
 * once both duellists are idle or down, and a double knockout is a draw.
 */
void fn_1_9DBC(void)
{
    s16 count;
    s16 doneF;
    s16 i;

    count = 0;
    doneF = fn_1_1B8C(lbl_1_bss_580.mgTimer);
    if(doneF != 0) {
        lbl_1_bss_580.unk22 = 1;
    }
    for(i=0; i<2; i++) {
        if(lbl_1_bss_3B0[i].loseF != 0) {
            lbl_1_bss_3B0[i].hitObjF = 0;
            lbl_1_bss_3B0[i].hitStgF = 0;
            lbl_1_bss_3B0[i].mode = 2;
            lbl_1_bss_580.unk22 = 1;
            lbl_1_bss_580.winner = (i^1)|(i<<1);
        }
        if(lbl_1_bss_580.unk22 != 0) {
            lbl_1_bss_3B0[i].padOffF = 1;
            if(lbl_1_bss_3B0[i].mode != 2) {
                if(lbl_1_bss_3B0[i].mode == 0 && lbl_1_bss_3B0[i].actMode == 0) {
                    count++;
                }
            } else {
                count++;
            }
        }
    }
    if(count >= 2) {
        lbl_1_bss_580.unk20 = 1;
        if((lbl_1_bss_3B0[0].loseF != 0 && lbl_1_bss_3B0[1].loseF != 0) || (lbl_1_bss_3B0[0].loseF == 0 && lbl_1_bss_3B0[1].loseF == 0)) {
            lbl_1_bss_580.winner = 0;
        }
    }
}

/*
 * 102 insns. Unreferenced: hold A for one duellist until its charge reaches
 * `count`, then wait for the swing to finish. fn_1_A18C inlines this three
 * times rather than calling it.
 */
s16 fn_1_9FF4(s16 player, s16 count)
{
    s16 result;

    result = 0;
    switch(lbl_1_bss_3B0[player].seqMode) {
        case 0:
            lbl_1_bss_15F4->chr[player].btnDown |= PAD_BUTTON_A;
            lbl_1_bss_3B0[player].seqMode++;

        case 1:
            if(lbl_1_bss_3B0[player].actMode == 1) {
                lbl_1_bss_15F4->chr[player].btn |= PAD_BUTTON_A;
                if(lbl_1_bss_3B0[player].chargeCnt >= count) {
                    lbl_1_bss_3B0[player].seqMode++;
                }
            } else {
                lbl_1_bss_3B0[player].seqMode = 0;
            }
            break;

        case 2:
            if(lbl_1_bss_3B0[player].actMode != 2) {
                lbl_1_bss_3B0[player].seqMode++;
            }
            break;

        case 3:
            result = 1;
            break;
    }
    return result;
}

/*
 * 451 insns. The fade-in sequence: park both pads and start the loop sound (0),
 * hold 90 frames (1), a scripted full-charge swing from duellist 0 while both
 * cameras ease in (2), a second one over 120 frames (3), then both duellists
 * swing together (4), a 40-frame hold (5) and the BGM (6). Returns 1 on 6.
 */
int fn_1_A18C(void)
{
    int result;
    s16 count;
    s16 doneA;
    s16 doneB;
    s16 doneC;
    s16 doneD;
    s16 doneE;
    float div;

    result = 0;
    count = 0;
    switch(lbl_1_bss_580.mode) {
        case 0:
            lbl_1_bss_15F4->chr[0].btn = 0;
            lbl_1_bss_15F4->chr[0].btnDown = 0;
            fn_1_36A4(10);
            lbl_1_bss_3B0[0].seqMode = 0;
            lbl_1_bss_3B0[1].seqMode = 0;
            lbl_1_bss_580.timer = 0;
            lbl_1_bss_580.mode++;
            break;

        case 1:
            if(lbl_1_bss_580.timer++ >= 90) {
                lbl_1_bss_580.timer = 0;
                lbl_1_bss_580.mode++;
            }
            break;

        case 2:
            doneA = 0;
            switch(lbl_1_bss_3B0[0].seqMode) {
                case 0:
                    lbl_1_bss_15F4->chr[0].btnDown |= PAD_BUTTON_A;
                    lbl_1_bss_3B0[0].seqMode++;

                case 1:
                    if(lbl_1_bss_3B0[0].actMode == 1) {
                        lbl_1_bss_15F4->chr[0].btn |= PAD_BUTTON_A;
                        if(lbl_1_bss_3B0[0].chargeCnt >= 180) {
                            lbl_1_bss_3B0[0].seqMode++;
                        }
                    } else {
                        lbl_1_bss_3B0[0].seqMode = 0;
                    }
                    break;

                case 2:
                    if(lbl_1_bss_3B0[0].actMode != 2) {
                        lbl_1_bss_3B0[0].seqMode++;
                    }
                    break;

                case 3:
                    doneA = 1;
                    break;
            }
            lbl_1_bss_580.timer++;
            div = 50.0f;
            count = fn_1_18B0(&lbl_1_bss_14[0].zoom, div, lbl_1_data_288[0].zoom, lbl_1_data_288[2].zoom);
            count = fn_1_18B0(&lbl_1_bss_14[1].zoom, div, lbl_1_data_288[1].zoom, lbl_1_data_288[2].zoom);
            if(count == 0) {
                lbl_1_bss_580.mode++;
            }
            break;

        case 3:
            doneB = 0;
            switch(lbl_1_bss_3B0[0].seqMode) {
                case 0:
                    lbl_1_bss_15F4->chr[0].btnDown |= PAD_BUTTON_A;
                    lbl_1_bss_3B0[0].seqMode++;

                case 1:
                    if(lbl_1_bss_3B0[0].actMode == 1) {
                        lbl_1_bss_15F4->chr[0].btn |= PAD_BUTTON_A;
                        if(lbl_1_bss_3B0[0].chargeCnt >= 180) {
                            lbl_1_bss_3B0[0].seqMode++;
                        }
                    } else {
                        lbl_1_bss_3B0[0].seqMode = 0;
                    }
                    break;

                case 2:
                    if(lbl_1_bss_3B0[0].actMode != 2) {
                        lbl_1_bss_3B0[0].seqMode++;
                    }
                    break;

                case 3:
                    doneB = 1;
                    break;
            }
            if(lbl_1_bss_580.timer++ >= 120) {
                lbl_1_bss_580.timer = 0;
                lbl_1_bss_580.mode++;
            }
            break;

        case 4:
            if(lbl_1_bss_580.timer++ <= 11) {
                doneC = 0;
                switch(lbl_1_bss_3B0[0].seqMode) {
                    case 0:
                        lbl_1_bss_15F4->chr[0].btnDown |= PAD_BUTTON_A;
                        lbl_1_bss_3B0[0].seqMode++;

                    case 1:
                        if(lbl_1_bss_3B0[0].actMode == 1) {
                            lbl_1_bss_15F4->chr[0].btn |= PAD_BUTTON_A;
                            if(lbl_1_bss_3B0[0].chargeCnt >= 180) {
                                lbl_1_bss_3B0[0].seqMode++;
                            }
                        } else {
                            lbl_1_bss_3B0[0].seqMode = 0;
                        }
                        break;

                    case 2:
                        if(lbl_1_bss_3B0[0].actMode != 2) {
                            lbl_1_bss_3B0[0].seqMode++;
                        }
                        break;

                    case 3:
                        doneC = 1;
                        break;
                }
            } else {
                count = 1;
            }
            doneD = 0;
            switch(lbl_1_bss_3B0[1].seqMode) {
                case 0:
                    lbl_1_bss_15F4->chr[1].btnDown |= PAD_BUTTON_A;
                    lbl_1_bss_3B0[1].seqMode++;

                case 1:
                    if(lbl_1_bss_3B0[1].actMode == 1) {
                        lbl_1_bss_15F4->chr[1].btn |= PAD_BUTTON_A;
                        if(lbl_1_bss_3B0[1].chargeCnt >= 0) {
                            lbl_1_bss_3B0[1].seqMode++;
                        }
                    } else {
                        lbl_1_bss_3B0[1].seqMode = 0;
                    }
                    break;

                case 2:
                    if(lbl_1_bss_3B0[1].actMode != 2) {
                        lbl_1_bss_3B0[1].seqMode++;
                    }
                    break;

                case 3:
                    doneD = 1;
                    break;
            }
            doneE = doneD;
            count += doneE;
            if(count >= 2) {
                lbl_1_bss_580.timer = 0;
                lbl_1_bss_580.mode++;
            }
            break;

        case 5:
            if(lbl_1_bss_580.timer++ >= 40) {
                lbl_1_bss_580.timer = 0;
                lbl_1_bss_580.mode++;
            }
            break;

        case 6:
            fn_1_35AC();
            result = 1;
            break;
    }
    return result;
}

/*
 * 312 insns. The pre-winner sequence: hold 30 frames and turn the winner to
 * face the camera (0), spin it home (1), then swing both cameras onto it (2).
 * Returns 1 from 3. Every index is winner&1, so no path reaches player[-1].
 */
int fn_1_A898(void)
{
    HU3DMODEL *model;
    DS_PLAYER *pl;
    int result;
    s16 count;
    float div;

    model = &Hu3DData[lbl_1_bss_15F4->models[(lbl_1_bss_580.winner&1)+0x44].modelId];
    pl = &lbl_1_bss_15F4->player[lbl_1_bss_580.winner&1];
    result = 0;
    count = 0;
    switch(lbl_1_bss_580.mode) {
        case 0:
            if(lbl_1_bss_580.timer++ >= 30) {
                lbl_1_bss_580.timer = 0;
                if(lbl_1_bss_580.winner != 0) {
                    lbl_1_bss_580.unk08 = lbl_1_bss_0.player[lbl_1_bss_580.winner&1]->actor->rotY;
                    if(lbl_1_bss_580.unk08 <= 1.0f && lbl_1_bss_580.unk08 >= -1.0f) {
                        lbl_1_bss_580.mode = 2;
                        break;
                    }
                    pl->shiftMode = 1;
                    pl->shiftMotNo = 1;
                    pl->shiftTime = 0.0f;
                    pl->shiftSpeed = 4.0f;
                    pl->shiftAttr = HU3D_MOTATTR_LOOP;
                    pl->attrReset = 0;
                }
                lbl_1_bss_580.mode++;
            }
            break;

        case 1:
            if(lbl_1_bss_580.winner != 0) {
                count = fn_1_18B0(&model->rot.y, 30.0f, lbl_1_bss_580.unk08, 0.0f);
                if(count != 0) {
                    break;
                }
                pl->shiftMode = 1;
                pl->shiftMotNo = 0;
                pl->shiftTime = 0.0f;
                pl->shiftSpeed = 8.0f;
                pl->shiftAttr = HU3D_MOTATTR_LOOP;
                pl->attrReset = 0;
                lbl_1_bss_580.mode++;
            } else {
                lbl_1_bss_580.mode++;
            }
            break;

        case 2:
            if(lbl_1_bss_580.winner != 0) {
                div = 30.0f;
                count += fn_1_18B0(&lbl_1_bss_14[0].center.x, div, lbl_1_data_288[2].center.x, model->pos.x);
                count += fn_1_18B0(&lbl_1_bss_14[0].center.y, div, lbl_1_data_288[2].center.y, 70.0f+model->pos.y);
                count += fn_1_18B0(&lbl_1_bss_14[0].center.z, div, lbl_1_data_288[2].center.z, model->pos.z);
                count += fn_1_18B0(&lbl_1_bss_14[0].zoom, div, lbl_1_data_288[2].zoom, 500.0f);
                count += fn_1_18B0(&lbl_1_bss_14[1].center.x, div, lbl_1_data_288[2].center.x, model->pos.x);
                count += fn_1_18B0(&lbl_1_bss_14[1].center.y, div, lbl_1_data_288[2].center.y, 70.0f+model->pos.y);
                count += fn_1_18B0(&lbl_1_bss_14[1].center.z, div, lbl_1_data_288[2].center.z, model->pos.z);
                count += fn_1_18B0(&lbl_1_bss_14[1].zoom, div, lbl_1_data_288[2].zoom, 500.0f);
            }
            if(count == 0) {
                lbl_1_bss_580.mode++;
            }
            break;

        case 3:
            result = 1;
            break;
    }
    return result;
}

/* 20 insns. The actors' narrow-collision hook: count a landing on the duellist. */
int fn_1_AD78(COL_NARROW_PARAM *a, COL_NARROW_PARAM *b)
{
    s16 unused;

    unused = 0;
    switch(b->type) {
        case 0:
            lbl_1_bss_3B0[b->paramB].hitCnt++;
            break;
        case 6:
        default:
            break;
    }
    return 0;
}

/* 5 insns. The actors' correct hook; it reads one field and does nothing. */
void fn_1_ADC8(MGACTOR *actor, int param)
{
    int unused;

    unused = actor->param;
}

/*
 * 1110 insns. The collision pass. Two thrown objects that meet kill each other
 * and raise an impact ring midway, sized by the difference of their charge
 * levels. Then for each duellist: leaving the 525-unit arena starts the fall,
 * an object it did not throw knocks it back along the object's heading, and an
 * impact ring knocks it back along the bearing from the ring.
 */
void fn_1_ADDC(void)
{
    HuVecF hitPos;
    HuVecF pos;
    float rad = 45.0f;
    s16 unusedA = 0;
    s16 unusedB = 0;
    s16 unusedC = 0;
    s16 unusedD = 0;
    s16 unusedE = 0;
    s16 i;
    s16 j;
    s16 lv;
    int no;
    float rotY;
    float pitch;
    float dx;
    float dz;
    float dist;
    float mag;
    HuVecF *posP;

    for(i=0; i<10; i++) {
        if(lbl_1_bss_158[i].activeF == 0) {
            continue;
        }
        if(lbl_1_bss_158[i].deadF != 0) {
            continue;
        }
        for(j=0; j<10; j++) {
            if(lbl_1_bss_158[j].activeF == 0) {
                continue;
            }
            if(lbl_1_bss_158[j].deadF != 0) {
                continue;
            }
            if(i == j) {
                continue;
            }
            dx = lbl_1_bss_158[j].pos.x-lbl_1_bss_158[i].pos.x;
            dz = lbl_1_bss_158[j].pos.z-lbl_1_bss_158[i].pos.z;
            dist = sqrt((dx*dx)+(dz*dz));
            if(dist <= lbl_1_bss_158[i].range+lbl_1_bss_158[j].range) {
                lbl_1_bss_158[i].deadF = 1;
                lbl_1_bss_158[j].deadF = 1;
                dx = dx*0.5f;
                dz = dz*0.5f;
                hitPos.x = dx+lbl_1_bss_158[i].pos.x;
                hitPos.y = 0.0f;
                hitPos.z = dz+lbl_1_bss_158[i].pos.z;
                lv = lbl_1_bss_158[i].level-lbl_1_bss_158[j].level;
                if(lv > 0) {
                    no = lv;
                } else {
                    no = lv*-1;
                }
                lv = no;
                pos = hitPos;
                posP = &pos;
                fn_1_9324(posP, lv);
            }
        }
    }
    for(i=0; i<2; i++) {
        dx = -lbl_1_bss_3B0[i].pos.x;
        dz = -lbl_1_bss_3B0[i].pos.z;
        dist = sqrt((dx*dx)+(dz*dz));
        if(dist > lbl_1_data_498 && lbl_1_bss_3B0[i].loseF == 0) {
            lbl_1_bss_3B0[i].vel.x = lbl_1_bss_3B0[i].pos.x;
            lbl_1_bss_3B0[i].vel.z = lbl_1_bss_3B0[i].pos.z;
            mag = (lbl_1_bss_3B0[i].vel.x*lbl_1_bss_3B0[i].vel.x)+(lbl_1_bss_3B0[i].vel.z*lbl_1_bss_3B0[i].vel.z);
            dist = sqrt(mag);
            lbl_1_bss_3B0[i].vel.x = 10.0f*(lbl_1_bss_3B0[i].vel.x/dist);
            lbl_1_bss_3B0[i].vel.z = 10.0f*(lbl_1_bss_3B0[i].vel.z/dist);
            lbl_1_bss_3B0[i].loseF = 1;
        }
        if(lbl_1_bss_580.unk22 != 0) {
            continue;
        }
        for(j=0; j<10; j++) {
            if(lbl_1_bss_158[j].activeF == 0) {
                continue;
            }
            if(lbl_1_bss_158[j].deadF != 0) {
                continue;
            }
            if(i == lbl_1_bss_158[j].owner) {
                continue;
            }
            dx = lbl_1_bss_158[j].pos.x-lbl_1_bss_3B0[i].pos.x;
            dz = lbl_1_bss_158[j].pos.z-lbl_1_bss_3B0[i].pos.z;
            dist = sqrt((dx*dx)+(dz*dz));
            if(dist <= 45.0f+lbl_1_bss_158[j].range) {
                lbl_1_bss_158[j].deadF = 1;
                if(lbl_1_bss_3B0[i].hitObjF == 0 && lbl_1_bss_3B0[i].hitStgF == 0) {
                    lbl_1_bss_3B0[i].angle = lbl_1_bss_158[j].angle;
                    lbl_1_bss_3B0[i].hitType = lbl_1_bss_158[j].level;
                    lbl_1_bss_3B0[i].hitObjF = 1;
                }
            }
        }
        if(lbl_1_bss_3B0[i].hitObjF != 0) {
            continue;
        }
        if(lbl_1_bss_3B0[i].hitStgF != 0) {
            continue;
        }
        for(j=0; j<10; j++) {
            if(lbl_1_bss_18[j].activeF == 0) {
                continue;
            }
            dx = lbl_1_bss_18[j].pos.x-lbl_1_bss_3B0[i].pos.x;
            dz = lbl_1_bss_18[j].pos.z-lbl_1_bss_3B0[i].pos.z;
            dist = sqrt((dx*dx)+(dz*dz));
            if(dist <= lbl_1_bss_18[j].radius) {
                rotY = 180.0*(acos(dx/(0.1f+dist))/M_PI);
                pitch = -(180.0*(asin(dz/(0.1f+dist))/M_PI));
                if(pitch < 0.0f) {
                    rotY = 360.0f-rotY;
                }
                rotY = rotY-90.0f;
                lbl_1_bss_3B0[i].angle = rotY;
                lbl_1_bss_3B0[i].hitType = lbl_1_bss_18[j].no;
                lbl_1_bss_3B0[i].hitStgF = 1;
            }
        }
    }
}

/*
 * 267 insns. Seed one computer duellist from seven difficulty tables, then give
 * it its first target.
 */
void fn_1_BF34(s16 player)
{
    float speedTbl[4] = { 6.2222223f, 7.0f, 8.0f, 10.0f };
    s16 tblA[4] = { 10, 8, 5, 1 };
    s16 tblB[4] = { 5, 7, 8, 10 };
    s16 tblC[4] = { 20, 30, 70, 100 };
    s16 tblD[4] = { 20, 10, 3, 0 };
    s16 tblE[4] = { 0, 10, 40, 60 };
    s16 tblF[4] = { 20, 50, 80, 100 };
    s16 tblG[4] = { 20, 5, 0, 0 };

    if(lbl_1_bss_15F4->chr[player].dif != 0) {
        lbl_1_bss_3B0[player].comF = 1;
        lbl_1_bss_3B0[player].dif = lbl_1_bss_15F4->chr[player].dif-1;
        lbl_1_bss_3B0[player].speedBase = speedTbl[lbl_1_bss_3B0[player].dif];
        lbl_1_bss_3B0[player].chaseVelZ = speedTbl[lbl_1_bss_3B0[player].dif];
        lbl_1_bss_3B0[player].chaseRadius = 10.0f;
        lbl_1_bss_3B0[player].probA = tblA[lbl_1_bss_3B0[player].dif];
        lbl_1_bss_3B0[player].probB = tblB[lbl_1_bss_3B0[player].dif];
        lbl_1_bss_3B0[player].probC = tblC[lbl_1_bss_3B0[player].dif];
        lbl_1_bss_3B0[player].valD = tblD[lbl_1_bss_3B0[player].dif];
        lbl_1_bss_3B0[player].valE = tblE[lbl_1_bss_3B0[player].dif];
        lbl_1_bss_3B0[player].probF = tblF[lbl_1_bss_3B0[player].dif];
        lbl_1_bss_3B0[player].probG = tblG[lbl_1_bss_3B0[player].dif];
        fn_1_C418(player);
    }
}

/* 46 insns. One computer duellist's outer step: clear its pad, then think. */
s16 fn_1_C360(s16 player)
{
    s16 result;
    s16 unused;

    result = 0;
    unused = 0;
    lbl_1_bss_3B0[player].stkX = 0;
    lbl_1_bss_3B0[player].stkY = 0;
    lbl_1_bss_3B0[player].btnDown = 0;
    lbl_1_bss_3B0[player].btn = 0;
    fn_1_FDB0(player);
    return result;
}

/* 141 insns. Walk one computer duellist to its chosen spot. Returns 1 on arrival. */
s16 fn_1_C418(s16 player)
{
    s16 result;
    s16 doneF;

    result = 0;
    doneF = 0;
    if(lbl_1_bss_3B0[player].hitObjF == 0 && lbl_1_bss_3B0[player].hitStgF == 0) {
        switch(lbl_1_bss_3B0[player].chaseState) {
            case 0:
                MgPlayerComStkOn(lbl_1_bss_0.player[player]);
                lbl_1_bss_3B0[player].chaseState++;
                break;

            case 1:
                if(lbl_1_bss_3B0[player].padOffF == 0) {
                    lbl_1_bss_3B0[player].chaseVelZ = lbl_1_bss_3B0[player].speedBase*lbl_1_data_484[lbl_1_bss_3B0[player].chargeLv];
                    doneF = MgPlayerVecChase(lbl_1_bss_0.player[player], &lbl_1_bss_3B0[player].chasePos, lbl_1_bss_3B0[player].chaseVelZ, lbl_1_bss_3B0[player].chaseRadius);
                    if(doneF != 0) {
                        result = 1;
                    }
                }
                break;

            case 2:
                MgPlayerComStkOff(lbl_1_bss_0.player[player]);
                lbl_1_bss_3B0[player].chaseState = 0;
                result = 1;
                break;
        }
    }
    return result;
}

/*
 * 251 insns. Aim one computer duellist at where the other duellist's stick is
 * taking it, stopping 20 units short.
 */
void fn_1_C64C(s16 player)
{
    HuVecF vec;
    HuVecF pos;
    float mag;
    float dist;

    pos.x = (lbl_1_bss_3B0[player^1].stkXf/5.6f)*lbl_1_bss_3B0[player].speedMul;
    pos.z = -((lbl_1_bss_3B0[player^1].stkYf/5.6f)*lbl_1_bss_3B0[player].speedMul);
    pos.x += lbl_1_bss_3B0[player^1].pos.x;
    pos.z += lbl_1_bss_3B0[player^1].pos.z;
    vec.x = pos.x-lbl_1_bss_3B0[player].pos.x;
    vec.z = pos.z-lbl_1_bss_3B0[player].pos.z;
    mag = (vec.x*vec.x)+(vec.z*vec.z);
    dist = sqrt(mag);
    if(dist) {
        vec.x = lbl_1_bss_3B0[player].pos.x+(20.0f*(vec.x/dist));
        vec.z = lbl_1_bss_3B0[player].pos.z+(20.0f*(vec.z/dist));
    } else {
        vec.x = lbl_1_bss_3B0[player].pos.x;
        vec.z = lbl_1_bss_3B0[player].pos.z;
    }
    lbl_1_bss_3B0[player].chasePos.x = vec.x;
    lbl_1_bss_3B0[player].chasePos.y = lbl_1_bss_3B0[player].pos.y;
    lbl_1_bss_3B0[player].chasePos.z = vec.z;
}

/*
 * 232 insns. Aim one computer duellist at where object `no` will be in five
 * frames, stopping 20 units short.
 */
void fn_1_CA38(s16 player, s16 no)
{
    HuVecF vec;
    s16 i;
    float mag;
    float dist;

    vec.x = lbl_1_bss_158[no].pos.x;
    vec.z = lbl_1_bss_158[no].pos.z;
    for(i=0; i<5; i++) {
        vec.x += lbl_1_bss_158[no].vel.x;
        vec.z += lbl_1_bss_158[no].vel.z;
    }
    vec.x -= lbl_1_bss_3B0[player].pos.x;
    vec.z -= lbl_1_bss_3B0[player].pos.z;
    mag = (vec.x*vec.x)+(vec.z*vec.z);
    dist = sqrt(mag);
    if(dist) {
        vec.x = lbl_1_bss_3B0[player].pos.x+(20.0f*(vec.x/dist));
        vec.z = lbl_1_bss_3B0[player].pos.z+(20.0f*(vec.z/dist));
    } else {
        vec.x = lbl_1_bss_3B0[player].pos.x;
        vec.z = lbl_1_bss_3B0[player].pos.z;
    }
    lbl_1_bss_3B0[player].chasePos.x = vec.x;
    lbl_1_bss_3B0[player].chasePos.y = lbl_1_bss_3B0[player].pos.y;
    lbl_1_bss_3B0[player].chasePos.z = vec.z;
}

/*
 * 187 insns. Roll a random spot inside the arena for one computer duellist,
 * re-rolling until it is inside the 525-unit circle.
 */
s16 fn_1_CDD8(s16 player)
{
    HuVecF pos;
    s16 result;
    float angle;
    float len;
    float mag;

    result = 0;
    pos = lbl_1_bss_3B0[player].pos;
    do {
        angle = frandmod(360);
        len = frandmod(395);
        pos.x = len*cos((M_PI*angle)/180.0);
        pos.z = len*sin((M_PI*angle)/180.0);
        mag = (pos.x*pos.x)+(pos.z*pos.z);
        mag = sqrt(mag);
    } while(!(mag < lbl_1_data_498));
    lbl_1_bss_3B0[player].chasePos = pos;
    result = 1;
    return result;
}


/*
 * 583 insns. The computer's charged swing at where the other duellist is
 * heading: press A (0), hold it until the charge reaches `wait` and then aim
 * (1), keep holding for five frames while walking (2), and wait for the swing
 * to finish (3).
 */
s16 fn_1_D0C4(s16 player, s16 wait)
{
    HuVecF pos;
    HuVecF vec;
    s16 result;
    s16 chaseF;
    s16 doneF;
    float mag;
    float dist;

    result = 0;
    switch(lbl_1_bss_3B0[player].subMode) {
        case 0:
            lbl_1_bss_3B0[player].btnDown |= PAD_BUTTON_A;
            lbl_1_bss_3B0[player].subWait = 0;
            lbl_1_bss_3B0[player].subMode++;

        case 1:
            if(lbl_1_bss_3B0[player].actMode == 1) {
                lbl_1_bss_3B0[player].btn |= PAD_BUTTON_A;
                if(lbl_1_bss_3B0[player].chargeCnt >= wait) {
                    pos.x = (lbl_1_bss_3B0[player^1].stkXf/5.6f)*lbl_1_bss_3B0[player].speedMul;
                    pos.z = -((lbl_1_bss_3B0[player^1].stkYf/5.6f)*lbl_1_bss_3B0[player].speedMul);
                    pos.x += lbl_1_bss_3B0[player^1].pos.x;
                    pos.z += lbl_1_bss_3B0[player^1].pos.z;
                    vec.x = pos.x-lbl_1_bss_3B0[player].pos.x;
                    vec.z = pos.z-lbl_1_bss_3B0[player].pos.z;
                    mag = (vec.x*vec.x)+(vec.z*vec.z);
                    dist = sqrt(mag);
                    if(dist) {
                        vec.x = lbl_1_bss_3B0[player].pos.x+(20.0f*(vec.x/dist));
                        vec.z = lbl_1_bss_3B0[player].pos.z+(20.0f*(vec.z/dist));
                    } else {
                        vec.x = lbl_1_bss_3B0[player].pos.x;
                        vec.z = lbl_1_bss_3B0[player].pos.z;
                    }
                    lbl_1_bss_3B0[player].chasePos.x = vec.x;
                    lbl_1_bss_3B0[player].chasePos.y = lbl_1_bss_3B0[player].pos.y;
                    lbl_1_bss_3B0[player].chasePos.z = vec.z;
                    lbl_1_bss_3B0[player].chasePosSave = lbl_1_bss_3B0[player].chasePos;
                    lbl_1_bss_3B0[player].targetFSave = lbl_1_bss_3B0[player].targetF;
                    lbl_1_bss_3B0[player].subMode++;
                }
            } else {
                lbl_1_bss_3B0[player].subMode = 0;
            }
            break;

        case 2:
            lbl_1_bss_3B0[player].targetF = 0;
            doneF = 0;
            chaseF = 0;
            if(lbl_1_bss_3B0[player].hitObjF == 0 && lbl_1_bss_3B0[player].hitStgF == 0) {
                switch(lbl_1_bss_3B0[player].chaseState) {
                    case 0:
                        MgPlayerComStkOn(lbl_1_bss_0.player[player]);
                        lbl_1_bss_3B0[player].chaseState++;
                        break;

                    case 1:
                        if(lbl_1_bss_3B0[player].padOffF == 0) {
                            lbl_1_bss_3B0[player].chaseVelZ = lbl_1_bss_3B0[player].speedBase*lbl_1_data_484[lbl_1_bss_3B0[player].chargeLv];
                            chaseF = MgPlayerVecChase(lbl_1_bss_0.player[player], &lbl_1_bss_3B0[player].chasePos, lbl_1_bss_3B0[player].chaseVelZ, lbl_1_bss_3B0[player].chaseRadius);
                            if(chaseF != 0) {
                                doneF = 1;
                            }
                        }
                        break;

                    case 2:
                        MgPlayerComStkOff(lbl_1_bss_0.player[player]);
                        lbl_1_bss_3B0[player].chaseState = 0;
                        doneF = 1;
                        break;
                }
            }
            if(lbl_1_bss_3B0[player].subWait++ >= 5) {
                lbl_1_bss_3B0[player].chasePos = lbl_1_bss_3B0[player].chasePosSave;
                lbl_1_bss_3B0[player].targetF = lbl_1_bss_3B0[player].targetFSave;
                lbl_1_bss_3B0[player].subMode++;
            } else {
                lbl_1_bss_3B0[player].btn |= PAD_BUTTON_A;
            }
            break;

        case 3:
            if(lbl_1_bss_3B0[player].actMode != 2) {
                lbl_1_bss_3B0[player].subMode = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/*
 * 480 insns. The computer's uncharged swing: press A (0), and as soon as the
 * charge starts, aim at the other duellist and walk there (1). 2 waits for the
 * swing to finish.
 */
s16 fn_1_D9E0(s16 player)
{
    HuVecF pos;
    HuVecF vec;
    s16 result;
    s16 chaseF;
    s16 doneF;
    float mag;
    float dist;

    result = 0;
    switch(lbl_1_bss_3B0[player].subMode) {
        case 0:
            lbl_1_bss_3B0[player].btnDown |= PAD_BUTTON_A;
            lbl_1_bss_3B0[player].subWait = 0;
            lbl_1_bss_3B0[player].subMode++;

        case 1:
            if(lbl_1_bss_3B0[player].actMode == 1) {
                lbl_1_bss_3B0[player].btn |= PAD_BUTTON_A;
                pos.x = (lbl_1_bss_3B0[player^1].stkXf/5.6f)*lbl_1_bss_3B0[player].speedMul;
                pos.z = -((lbl_1_bss_3B0[player^1].stkYf/5.6f)*lbl_1_bss_3B0[player].speedMul);
                pos.x += lbl_1_bss_3B0[player^1].pos.x;
                pos.z += lbl_1_bss_3B0[player^1].pos.z;
                vec.x = pos.x-lbl_1_bss_3B0[player].pos.x;
                vec.z = pos.z-lbl_1_bss_3B0[player].pos.z;
                mag = (vec.x*vec.x)+(vec.z*vec.z);
                dist = sqrt(mag);
                if(dist) {
                    vec.x = lbl_1_bss_3B0[player].pos.x+(20.0f*(vec.x/dist));
                    vec.z = lbl_1_bss_3B0[player].pos.z+(20.0f*(vec.z/dist));
                } else {
                    vec.x = lbl_1_bss_3B0[player].pos.x;
                    vec.z = lbl_1_bss_3B0[player].pos.z;
                }
                lbl_1_bss_3B0[player].chasePos.x = vec.x;
                lbl_1_bss_3B0[player].chasePos.y = lbl_1_bss_3B0[player].pos.y;
                lbl_1_bss_3B0[player].chasePos.z = vec.z;
                doneF = 0;
                chaseF = 0;
                if(lbl_1_bss_3B0[player].hitObjF == 0 && lbl_1_bss_3B0[player].hitStgF == 0) {
                    switch(lbl_1_bss_3B0[player].chaseState) {
                        case 0:
                            MgPlayerComStkOn(lbl_1_bss_0.player[player]);
                            lbl_1_bss_3B0[player].chaseState++;
                            break;

                        case 1:
                            if(lbl_1_bss_3B0[player].padOffF == 0) {
                                lbl_1_bss_3B0[player].chaseVelZ = lbl_1_bss_3B0[player].speedBase*lbl_1_data_484[lbl_1_bss_3B0[player].chargeLv];
                                chaseF = MgPlayerVecChase(lbl_1_bss_0.player[player], &lbl_1_bss_3B0[player].chasePos, lbl_1_bss_3B0[player].chaseVelZ, lbl_1_bss_3B0[player].chaseRadius);
                                if(chaseF != 0) {
                                    doneF = 1;
                                }
                            }
                            break;

                        case 2:
                            MgPlayerComStkOff(lbl_1_bss_0.player[player]);
                            lbl_1_bss_3B0[player].chaseState = 0;
                            doneF = 1;
                            break;
                    }
                }
                lbl_1_bss_3B0[player].subMode++;
            } else {
                lbl_1_bss_3B0[player].btnDown |= PAD_BUTTON_A;
            }
            break;

        case 2:
            if(lbl_1_bss_3B0[player].actMode != 2) {
                lbl_1_bss_3B0[player].subMode = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/*
 * 456 insns. The computer's swing at where object `no` will be in five frames:
 * press A (0), aim and walk on the first charge frame (1), then wait for the
 * swing to finish (2).
 */
s16 fn_1_E160(s16 player, s16 no)
{
    HuVecF pos;
    s16 result;
    s16 i;
    s16 chaseF;
    s16 doneF;
    float mag;
    float dist;

    result = 0;
    switch(lbl_1_bss_3B0[player].subMode) {
        case 0:
            lbl_1_bss_3B0[player].btnDown |= PAD_BUTTON_A;
            lbl_1_bss_3B0[player].subWait = 0;
            lbl_1_bss_3B0[player].subMode++;

        case 1:
            if(lbl_1_bss_3B0[player].actMode == 1) {
                lbl_1_bss_3B0[player].btn |= PAD_BUTTON_A;
                pos.x = lbl_1_bss_158[no].pos.x;
                pos.z = lbl_1_bss_158[no].pos.z;
                for(i=0; i<5; i++) {
                    pos.x += lbl_1_bss_158[no].vel.x;
                    pos.z += lbl_1_bss_158[no].vel.z;
                }
                pos.x -= lbl_1_bss_3B0[player].pos.x;
                pos.z -= lbl_1_bss_3B0[player].pos.z;
                mag = (pos.x*pos.x)+(pos.z*pos.z);
                dist = sqrt(mag);
                if(dist) {
                    pos.x = lbl_1_bss_3B0[player].pos.x+(20.0f*(pos.x/dist));
                    pos.z = lbl_1_bss_3B0[player].pos.z+(20.0f*(pos.z/dist));
                } else {
                    pos.x = lbl_1_bss_3B0[player].pos.x;
                    pos.z = lbl_1_bss_3B0[player].pos.z;
                }
                lbl_1_bss_3B0[player].chasePos.x = pos.x;
                lbl_1_bss_3B0[player].chasePos.y = lbl_1_bss_3B0[player].pos.y;
                lbl_1_bss_3B0[player].chasePos.z = pos.z;
                doneF = 0;
                chaseF = 0;
                if(lbl_1_bss_3B0[player].hitObjF == 0 && lbl_1_bss_3B0[player].hitStgF == 0) {
                    switch(lbl_1_bss_3B0[player].chaseState) {
                        case 0:
                            MgPlayerComStkOn(lbl_1_bss_0.player[player]);
                            lbl_1_bss_3B0[player].chaseState++;
                            break;

                        case 1:
                            if(lbl_1_bss_3B0[player].padOffF == 0) {
                                lbl_1_bss_3B0[player].chaseVelZ = lbl_1_bss_3B0[player].speedBase*lbl_1_data_484[lbl_1_bss_3B0[player].chargeLv];
                                chaseF = MgPlayerVecChase(lbl_1_bss_0.player[player], &lbl_1_bss_3B0[player].chasePos, lbl_1_bss_3B0[player].chaseVelZ, lbl_1_bss_3B0[player].chaseRadius);
                                if(chaseF != 0) {
                                    doneF = 1;
                                }
                            }
                            break;

                        case 2:
                            MgPlayerComStkOff(lbl_1_bss_0.player[player]);
                            lbl_1_bss_3B0[player].chaseState = 0;
                            doneF = 1;
                            break;
                    }
                }
                lbl_1_bss_3B0[player].subMode++;
            } else {
                lbl_1_bss_3B0[player].btnDown |= PAD_BUTTON_A;
            }
            break;

        case 2:
            if(lbl_1_bss_3B0[player].actMode != 2) {
                lbl_1_bss_3B0[player].subMode = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* 35 insns. Hold A while charging, press it otherwise. */
void fn_1_E880(s16 player)
{
    switch(lbl_1_bss_3B0[player].unk0AC) {
        case 0:
            if(lbl_1_bss_3B0[player].actMode == 1) {
                lbl_1_bss_3B0[player].btn |= PAD_BUTTON_A;
            } else {
                lbl_1_bss_3B0[player].btnDown |= PAD_BUTTON_A;
            }
            break;
    }
}

/*
 * 495 insns. Can this duellist dodge object `no` by stepping along its own aim
 * bearing? Only if the object is within 130 units; then try the spot 200 units
 * behind the bearing, and failing that the one 200 units ahead. Returns 1 for a
 * spot inside the arena, -1 for none.
 */
s16 fn_1_E90C(s16 player, s16 no)
{
    HuVecF posA;
    HuVecF posB;
    s16 result;
    float dist;
    float angle;
    float angleB;
    float distA;

    result = 0;
    posB.x = lbl_1_bss_158[no].pos.x-lbl_1_bss_3B0[player].pos.x;
    posB.z = lbl_1_bss_158[no].pos.z-lbl_1_bss_3B0[player].pos.z;
    dist = sqrt((posB.x*posB.x)+(posB.z*posB.z));
    if(dist <= 130.0f) {
        angle = lbl_1_bss_3B0[player].aimAngle;
        posB.x = lbl_1_bss_3B0[player].pos.x+(200.0*sin((M_PI*angle)/180.0));
        posB.z = lbl_1_bss_3B0[player].pos.z+(200.0*cos((M_PI*angle)/180.0));
        dist = sqrt((posB.x*posB.x)+(posB.z*posB.z));
        angleB = 180.0f+lbl_1_bss_3B0[player].aimAngle;
        posA.x = lbl_1_bss_3B0[player].pos.x+(200.0*sin((M_PI*angleB)/180.0));
        posA.z = lbl_1_bss_3B0[player].pos.z+(200.0*cos((M_PI*angleB)/180.0));
        distA = sqrt((posA.x*posA.x)+(posA.z*posA.z));
        if(distA < lbl_1_data_498) {
            lbl_1_bss_3B0[player].chasePos.x = posA.x;
            lbl_1_bss_3B0[player].chasePos.z = posA.z;
            result = 1;
        } else if(dist < lbl_1_data_498) {
            lbl_1_bss_3B0[player].chasePos.x = posB.x;
            lbl_1_bss_3B0[player].chasePos.z = posB.z;
            result = 1;
        } else {
            result = -1;
        }
    } else {
        result = -1;
    }
    return result;
}

/* 246 insns. Cache this duellist's distance to the other one and to the centre. */
void fn_1_F0C8(s16 player)
{
    HuVecF vec;
    s16 other;
    float mag;
    float dist;

    other = player^1;
    vec.x = lbl_1_bss_3B0[other].pos.x-lbl_1_bss_3B0[player].pos.x;
    vec.z = lbl_1_bss_3B0[other].pos.z-lbl_1_bss_3B0[player].pos.z;
    mag = (vec.x*vec.x)+(vec.z*vec.z);
    dist = sqrt(mag);
    lbl_1_bss_3B0[player].distOther = dist;
    vec.x = lbl_1_bss_3B0[player].pos.x;
    vec.z = lbl_1_bss_3B0[player].pos.z;
    mag = (vec.x*vec.x)+(vec.z*vec.z);
    dist = sqrt(mag);
    lbl_1_bss_3B0[player].distHome = dist;
}

/*
 * 580 insns. Is this duellist standing in object `no`'s path over the next
 * 1190 units? Grow the segment's bounding box by the object's radius, reject
 * anything outside it, then measure the perpendicular distance to the segment;
 * inside the radius it records the bearing to run from and returns 1.
 */
s16 fn_1_F4A0(s16 player, s16 no)
{
    HuVecF min;
    HuVecF max;
    HuVecF pos;
    HuVecF next;
    float cz;
    float dot;
    float tmpA;
    float tmpB;
    float tmpC;
    float tmpD;
    s16 result;
    float mag;
    float dist;
    float dx;
    float dz;
    float len2;
    float t;
    float cx;
    float rotY;
    float pitch;

    result = 0;
    pos = lbl_1_bss_158[no].pos;
    mag = (lbl_1_bss_158[no].vel.x*lbl_1_bss_158[no].vel.x)+(lbl_1_bss_158[no].vel.z*lbl_1_bss_158[no].vel.z);
    dist = sqrt(mag);
    if(dist != 0.0f) {
        next.x = pos.x+((1190.0f/dist)*lbl_1_bss_158[no].vel.x);
        next.z = pos.z+((1190.0f/dist)*lbl_1_bss_158[no].vel.z);
    } else {
        next.x = pos.x;
        next.z = pos.z;
    }
    if(pos.x > next.x) {
        max.x = pos.x;
        min.x = next.x;
        tmpA = min.x;
    } else {
        max.x = next.x;
        min.x = pos.x;
        tmpB = min.x;
    }
    if(pos.z > next.z) {
        max.z = pos.z;
        min.z = next.z;
        tmpC = min.z;
    } else {
        max.z = next.z;
        min.z = pos.z;
        tmpD = min.z;
    }
    max.x = max.x+(45.0f+lbl_1_bss_158[no].range);
    min.x = min.x-(45.0f+lbl_1_bss_158[no].range);
    max.z = max.z+(45.0f+lbl_1_bss_158[no].range);
    min.z = min.z-(45.0f+lbl_1_bss_158[no].range);
    if(lbl_1_bss_3B0[player].pos.x <= max.x && lbl_1_bss_3B0[player].pos.x >= min.x && lbl_1_bss_3B0[player].pos.z <= max.z && lbl_1_bss_3B0[player].pos.z >= min.z) {
        dx = pos.x-next.x;
        dz = pos.z-next.z;
        len2 = (dx*dx)+(dz*dz);
        dot = -1.0f*((dx*(pos.x-lbl_1_bss_3B0[player].pos.x))+(dz*(pos.z-lbl_1_bss_3B0[player].pos.z)));
        if(len2 != 0.0f) {
            t = dot/len2;
        } else {
            t = 0.0f;
        }
        cx = pos.x+(dx*t);
        cz = pos.z+(dz*t);
        dx = lbl_1_bss_3B0[player].pos.x-cx;
        dz = lbl_1_bss_3B0[player].pos.z-cz;
        dist = sqrt((dx*dx)+(dz*dz));
        if(dist < 45.0f+lbl_1_bss_158[no].range) {
            rotY = 180.0*(acos(dx/(0.1f+dist))/M_PI);
            pitch = -(180.0*(asin(dz/(0.1f+dist))/M_PI));
            if(pitch <= 0.0f) {
                rotY = 360.0f-rotY;
            }
            rotY = rotY-90.0f;
            lbl_1_bss_3B0[player].aimAngle = rotY;
            result = 1;
        }
    }
    return result;
}

/*
 * 1534 insns. The computer duellist's think routine. It caches both distances,
 * looks for an incoming object to dodge, then runs an eleven-state machine:
 * state 0 rolls the whole decision (close in and swing, charge a big one, run
 * for the centre, or walk somewhere random), and the rest carry each of those
 * out. The tail walks toward the chosen spot and holds A while charging.
 */
s16 fn_1_FDB0(s16 player)
{
    HuVecF pos;
    HuVecF walkPos;
    HuVecF vec;
    s16 result;
    s16 doneF;
    s16 other;
    s16 other2;
    s16 roll;
    s16 j;
    s16 range;
    s16 foundF;
    s16 foundF2;
    s16 doneF2;
    s16 chaseF;
    s16 chaseEnd;
    float mag;
    float dist;
    float angle;
    float len;
    float angle2;
    float len2;

    result = 0;
    doneF = 0;
    other = player^1;
    other2 = player^1;
    vec.x = lbl_1_bss_3B0[other2].pos.x-lbl_1_bss_3B0[player].pos.x;
    vec.z = lbl_1_bss_3B0[other2].pos.z-lbl_1_bss_3B0[player].pos.z;
    mag = (vec.x*vec.x)+(vec.z*vec.z);
    lbl_1_bss_3B0[player].distOther = sqrt(mag);
    vec.x = lbl_1_bss_3B0[player].pos.x;
    vec.z = lbl_1_bss_3B0[player].pos.z;
    mag = (vec.x*vec.x)+(vec.z*vec.z);
    lbl_1_bss_3B0[player].distHome = sqrt(mag);
    if(lbl_1_bss_3B0[player].motMode == 0) {
        for(j=0; j<10; j++) {
            if(lbl_1_bss_158[j].activeF == 0) {
                continue;
            }
            if((player^1) != lbl_1_bss_158[j].owner) {
                continue;
            }
            doneF = fn_1_F4A0(player, j);
            if(doneF != 0) {
                roll = frandmod(100);
                if(lbl_1_bss_3B0[player].probC > roll) {
                    doneF = fn_1_E90C(player, j);
                    if(doneF == 1) {
                        lbl_1_bss_3B0[player].targetF = 1;
                        lbl_1_bss_3B0[player].chaseEndF = 0;
                    }
                }
            }
        }
    }
    switch(lbl_1_bss_3B0[player].comMode) {
        case 0:
            if(lbl_1_bss_3B0[player].motMode != 0) {
                break;
            }
            lbl_1_bss_3B0[player].hitCnt = 0;
            if(lbl_1_bss_3B0[player].distOther <= 120.0f) {
                roll = frandmod(2);
                if(roll != 0) {
                    if(lbl_1_bss_3B0[other].motMode == 1) {
                        lbl_1_bss_3B0[player].aimParam = 30;
                        lbl_1_bss_3B0[player].targetF = 0;
                        lbl_1_bss_3B0[player].comMode = 7;
                    } else {
                        lbl_1_bss_3B0[player].targetF = 0;
                        lbl_1_bss_3B0[player].comMode = 5;
                    }
                }
                break;
            }
            roll = frandmod(100);
            if(lbl_1_bss_3B0[player].probF > roll && lbl_1_bss_3B0[player].distHome >= 400.0f) {
                lbl_1_bss_3B0[player].targetF = 1;
                lbl_1_bss_3B0[player].waitCnt = 0;
                lbl_1_bss_3B0[player].chasePos.x = 0.0f;
                lbl_1_bss_3B0[player].chasePos.z = 0.0f;
                lbl_1_bss_3B0[player].comMode = 8;
                break;
            }
            roll = frandmod(2);
            if(roll != 0) {
                roll = frandmod(100);
                if(lbl_1_bss_3B0[player].probB > roll) {
                    range = 121-lbl_1_bss_3B0[player].valD;
                    if(range > 0) {
                        roll = lbl_1_bss_3B0[player].valE+frandmod(range);
                    } else {
                        roll = lbl_1_bss_3B0[player].valE;
                    }
                    if(roll >= 120) {
                        roll = 120;
                    }
                    lbl_1_bss_3B0[player].aimParam = roll;
                    lbl_1_bss_3B0[player].targetF = 0;
                    lbl_1_bss_3B0[player].comMode = 7;
                    break;
                }
            } else {
                roll = frandmod(100);
                if(lbl_1_bss_3B0[player].probB > roll) {
                    range = 121-lbl_1_bss_3B0[player].valD;
                    if(range > 0) {
                        roll = lbl_1_bss_3B0[player].valE+frandmod(range);
                    } else {
                        roll = lbl_1_bss_3B0[player].valE;
                    }
                    if(roll >= 120) {
                        roll = 120;
                    }
                    lbl_1_bss_3B0[player].aimParam = roll;
                    foundF = 0;
                    walkPos = lbl_1_bss_3B0[player].pos;
                    do {
                        angle2 = frandmod(360);
                        len2 = frandmod(395);
                        walkPos.x = len2*cos((M_PI*angle2)/180.0);
                        walkPos.z = len2*sin((M_PI*angle2)/180.0);
                        dist = sqrt((walkPos.x*walkPos.x)+(walkPos.z*walkPos.z));
                    } while(dist >= lbl_1_data_498);
                    lbl_1_bss_3B0[player].chasePos = walkPos;
                    foundF = 1;
                    lbl_1_bss_3B0[player].targetF = 1;
                    lbl_1_bss_3B0[player].chaseEndF = 0;
                    lbl_1_bss_3B0[player].comMode = 10;
                    break;
                }
            }
            roll = frandmod(100);
            if(lbl_1_bss_3B0[player].probA > roll) {
                foundF2 = 0;
                pos = lbl_1_bss_3B0[player].pos;
                do {
                    angle = frandmod(360);
                    len = frandmod(395);
                    pos.x = len*cos((M_PI*angle)/180.0);
                    pos.z = len*sin((M_PI*angle)/180.0);
                    dist = sqrt((pos.x*pos.x)+(pos.z*pos.z));
                } while(dist >= lbl_1_data_498);
                lbl_1_bss_3B0[player].chasePos = pos;
                foundF2 = 1;
                lbl_1_bss_3B0[player].targetF = 1;
                lbl_1_bss_3B0[player].chaseEndF = 0;
                lbl_1_bss_3B0[player].comMode = 6;
                break;
            }
            roll = frandmod(100);
            if(lbl_1_bss_3B0[player].probG > roll) {
                lbl_1_bss_3B0[player].comMode = 8;
            }
            break;

        case 5:
            lbl_1_bss_3B0[player].speedMul = 0.0f;
            doneF = fn_1_D9E0(player);
            if(doneF != 0) {
                lbl_1_bss_3B0[player].comMode = 0;
            }
            break;

        case 6:
            if(lbl_1_bss_3B0[player].chaseEndF != 0 || lbl_1_bss_3B0[player].hitObjF != 0 || lbl_1_bss_3B0[player].hitStgF != 0 || lbl_1_bss_3B0[player].hitCnt > 60) {
                lbl_1_bss_3B0[player].targetF = 0;
                lbl_1_bss_3B0[player].comMode = 0;
            }
            break;

        case 7:
            if(lbl_1_bss_3B0[player].distOther <= 150.0f) {
                lbl_1_bss_3B0[player].speedMul = 0.0f;
                lbl_1_bss_3B0[player].aimParam = 0;
            } else if(lbl_1_bss_3B0[player].distHome >= 500.0f) {
                lbl_1_bss_3B0[player].speedMul = 20.0f;
                lbl_1_bss_3B0[player].aimParam = 0;
            } else {
                lbl_1_bss_3B0[player].speedMul = 20.0f;
            }
            doneF = fn_1_D0C4(player, lbl_1_bss_3B0[player].aimParam);
            if(doneF != 0) {
                lbl_1_bss_3B0[player].comMode = 0;
            }
            break;

        case 8:
            if(lbl_1_bss_3B0[player].waitCnt++ > 40) {
                lbl_1_bss_3B0[player].waitCnt = 0;
                lbl_1_bss_3B0[player].comMode = 0;
            }
            break;

        case 9:
            if(lbl_1_bss_3B0[player].chaseEndF != 0 || lbl_1_bss_3B0[player].hitObjF == 0 || lbl_1_bss_3B0[player].hitStgF == 0) {
                lbl_1_bss_3B0[player].waitCnt = 0;
                lbl_1_bss_3B0[player].comMode = 0;
            }
            break;

        case 10:
            if(lbl_1_bss_3B0[player].distOther <= 150.0f) {
                lbl_1_bss_3B0[player].speedMul = 0.0f;
                lbl_1_bss_3B0[player].aimParam = 0;
            } else if(lbl_1_bss_3B0[player].distHome >= 500.0f) {
                lbl_1_bss_3B0[player].speedMul = 20.0f;
                lbl_1_bss_3B0[player].aimParam = 0;
            } else {
                lbl_1_bss_3B0[player].speedMul = 20.0f;
            }
            doneF = fn_1_D0C4(player, lbl_1_bss_3B0[player].aimParam);
            if(doneF != 0) {
                lbl_1_bss_3B0[player].targetF = 0;
                lbl_1_bss_3B0[player].comMode = 0;
            }
            break;
    }
    if(lbl_1_bss_3B0[player].targetF != 0) {
        doneF2 = 0;
        chaseF = 0;
        if(lbl_1_bss_3B0[player].hitObjF == 0 && lbl_1_bss_3B0[player].hitStgF == 0) {
            switch(lbl_1_bss_3B0[player].chaseState) {
                case 0:
                    MgPlayerComStkOn(lbl_1_bss_0.player[player]);
                    lbl_1_bss_3B0[player].chaseState++;
                    break;

                case 1:
                    if(lbl_1_bss_3B0[player].padOffF == 0) {
                        lbl_1_bss_3B0[player].chaseVelZ = lbl_1_bss_3B0[player].speedBase*lbl_1_data_484[lbl_1_bss_3B0[player].chargeLv];
                        chaseF = MgPlayerVecChase(lbl_1_bss_0.player[player], &lbl_1_bss_3B0[player].chasePos, lbl_1_bss_3B0[player].chaseVelZ, lbl_1_bss_3B0[player].chaseRadius);
                        if(chaseF != 0) {
                            doneF2 = 1;
                        }
                    }
                    break;

                case 2:
                    MgPlayerComStkOff(lbl_1_bss_0.player[player]);
                    lbl_1_bss_3B0[player].chaseState = 0;
                    doneF2 = 1;
                    break;
            }
        }
        chaseEnd = doneF2;
        lbl_1_bss_3B0[player].chaseEndF = chaseEnd;
    }
    if(lbl_1_bss_3B0[player].unk0AE != 0) {
        switch(lbl_1_bss_3B0[player].unk0AC) {
            case 0:
                if(lbl_1_bss_3B0[player].actMode == 1) {
                    lbl_1_bss_3B0[player].btn |= PAD_BUTTON_A;
                } else {
                    lbl_1_bss_3B0[player].btnDown |= PAD_BUTTON_A;
                }
                break;
        }
    }
    return result;
}
