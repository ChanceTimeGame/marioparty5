/*
 * m554dll/game.c -- the duel itself. Written from the reference assembly,
 * functions in reference order; line ranges are into
 * build/mp5-asm/m554dll/asm/REL/m554dll/game.s. Nothing here matches
 * m550dll's game.c (best normalized similarity 0.43, apart from the empty
 * fn_1_2800): this file is the overlay's own game.
 *
 * The two duellists stand on a circle round the storm (run[].dist from the
 * centre at z = -600). Every frame each one's distance changes by a step
 * from a table: pressing L and R alternately keeps them out, not pressing
 * lets them drift in, and the table gets harsher as count rises. The first
 * one inside 280 loses the clash (mode[3] is the other one); both inside on
 * the same frame is a draw.
 */

#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/wipe.h"
#include "game/pad.h"
#include "game/audio.h"
#include "game/frand.h"
#include "game/mg/seqman.h"
#include "game/hsfex.h"
#include "game/gamemes.h"
#include "game/flag.h"

#include "REL/m554dll/m554.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

void fn_1_3210(s32 no);
void fn_1_3518(void);
void fn_1_3578(s32 player);
s32 fn_1_38D4(s32 player);
void fn_1_3AC8(s32 player);
s32 fn_1_3B58(s32 player);
void fn_1_3D6C(s32 player);
void fn_1_4050(s32 player);
void fn_1_4D60(s32 player);
s32 fn_1_514C(s32 time);
void fn_1_53B0(OMOBJ *obj);
void fn_1_5A5C(void);
s32 fn_1_5AB0(void);
void fn_1_5CCC(s32 endF);

/* --- .data --- */

s32 lbl_1_data_238 = -1;           /* the BGM stream */
s32 lbl_1_data_23C[2] = { -1, -1 };  /* two looping sound effects */
s16 lbl_1_data_244 = 127;           /* data_23C[1]'s volume */
s16 lbl_1_data_246[3] = { 0, 0, 0 };  /* data_23C[1]'s pitch, and the pitch it slides to */
s32 lbl_1_data_24C[2] = { 0, 0 };   /* per-duellist step-sound flag */
s32 lbl_1_data_254 = -1;            /* the trigger pressed last, shared by both duellists */

/* --- .bss --- */

s32 lbl_1_bss_1330[3];              /* unreferenced */
GAMEMESID lbl_1_bss_133C;
s32 lbl_1_bss_1340[2];
s32 lbl_1_bss_1348;
s32 lbl_1_bss_134C;
s32 lbl_1_bss_1350;
s32 lbl_1_bss_1354;
s32 lbl_1_bss_1358[2];

/* asm 9-151, 134 insns. Fade-in sub-state 0. */
void fn_1_1F00(void)
{
    int i;

    fn_1_3210(0);
    fn_1_5A5C();
    if(lbl_1_data_23C[0] == -1) {
        lbl_1_data_23C[0] = HuAudFXPlay(2192);
        lbl_1_data_23C[1] = HuAudFXPlay(2194);
        HuAudFXVolSet(lbl_1_data_23C[1], lbl_1_data_244);
    }
    if(!WipeCheckEnd()) {
        lbl_1_data_238 = HuAudBGMPlay(54);
        lbl_1_bss_B1C.mode[0]++;
        lbl_1_bss_B1C.mode[1] = 0;
        omCameraViewMoveSimple(&lbl_1_bss_98[0], 60);
        for(i=0; i<2; i++) {
            if(lbl_1_bss_B1C.chr[i].dif != 0) {
                fn_1_3AC8(i);
            }
        }
        for(i=0; i<5; i++) {
            lbl_1_bss_B1C.press[0][(i+1)*10] = 1;
            lbl_1_bss_B1C.press[1][(i+1)*10] = 1;
        }
        lbl_1_bss_134C = lbl_1_bss_1358[0] = lbl_1_bss_1354 = lbl_1_bss_1350 = 0;
        lbl_1_bss_1348 = 0;
        lbl_1_bss_1340[0] = (rand8()%20)+20;
        lbl_1_bss_1340[1] = (rand8()%20)+20;
    }
}

/* asm 154-265, 109 insns. Fade-in sub-state 1: spin model 2 round once. */
void fn_1_2118(void)
{
    M554_MODEL *mdl = &lbl_1_bss_B1C.models[2];

    mdl->rot.y -= 5.0f;
    if(mdl->rot.y <= -360.0f) {
        mdl->rot.y = 0.0f;
        lbl_1_bss_B1C.player[0].shiftMode = 1;
        lbl_1_bss_B1C.player[0].shiftMotNo = 2;
        lbl_1_bss_B1C.player[0].shiftTime = 0.0f;
        lbl_1_bss_B1C.player[0].shiftSpeed = 20.0f;
        lbl_1_bss_B1C.player[0].shiftAttr = 0;
        lbl_1_bss_B1C.player[1].shiftMode = 1;
        lbl_1_bss_B1C.player[1].shiftMotNo = 2;
        lbl_1_bss_B1C.player[1].shiftTime = 0.0f;
        lbl_1_bss_B1C.player[1].shiftSpeed = 20.0f;
        lbl_1_bss_B1C.player[1].shiftAttr = 0;
        lbl_1_bss_B1C.mode[0]++;
        omVibrate(lbl_1_bss_B1C.chr[0].no, 15, 12, 0);
        omVibrate(lbl_1_bss_B1C.chr[1].no, 15, 12, 0);
        CharFXPlayPan(lbl_1_bss_B1C.chr[0].charNo, 508, 48);
        CharFXPlayPan(lbl_1_bss_B1C.chr[1].charNo, 508, 80);
    }
}

/* asm 268-350, 80 insns. Fade-in sub-state 2. */
void fn_1_22CC(void)
{
    if(lbl_1_bss_B1C.player[0].shiftMode == 0 && lbl_1_bss_B1C.player[0].maxTime == lbl_1_bss_B1C.player[0].time) {
        lbl_1_bss_B1C.player[0].shiftMode = 1;
        lbl_1_bss_B1C.player[0].shiftMotNo = 1;
        lbl_1_bss_B1C.player[0].shiftTime = 0.0f;
        lbl_1_bss_B1C.player[0].shiftSpeed = 30.0f;
        lbl_1_bss_B1C.player[0].shiftAttr = HU3D_MOTATTR_LOOP;
        lbl_1_bss_B1C.player[1].shiftMode = 1;
        lbl_1_bss_B1C.player[1].shiftMotNo = 1;
        lbl_1_bss_B1C.player[1].shiftTime = 0.0f;
        lbl_1_bss_B1C.player[1].shiftSpeed = 30.0f;
        lbl_1_bss_B1C.player[1].shiftAttr = HU3D_MOTATTR_LOOP;
        omCameraViewMoveSimple(&lbl_1_bss_98[1], 120);
        lbl_1_bss_134C = 1;
        MgSeqModeNext();
    }
}

/* asm 353-511, 146 insns. Main sub-state 0: run until one of them is inside 280. */
void fn_1_240C(void)
{
    int i;

    fn_1_3518();
    for(i=0; i<2; i++) {
        if(lbl_1_bss_B1C.chr[i].dif != 0) {
            fn_1_3D6C(i);
        }
        fn_1_3578(i);
    }
    fn_1_3210(0);
    if(lbl_1_bss_B1C.run[0].dist < 280.0f || lbl_1_bss_B1C.run[1].dist < 280.0f) {
        lbl_1_bss_B1C.mode[0]++;
        lbl_1_bss_B1C.mode[1] = 0;
        lbl_1_bss_B1C.mode[2] = 0;
        lbl_1_bss_B1C.mode[3] = 0;
        if(lbl_1_bss_B1C.run[0].dist < lbl_1_bss_B1C.run[1].dist) {
            lbl_1_bss_B1C.mode[3] = 1;
        }
        if(lbl_1_bss_B1C.run[0].dist < 280.0f && lbl_1_bss_B1C.run[1].dist < 280.0f) {
            lbl_1_bss_B1C.mode[3] = 2;
            lbl_1_bss_134C = 3;
        }
        if(lbl_1_bss_B1C.mode[3] == 2) {
            omVibrate(lbl_1_bss_B1C.chr[0].no, 60, 12, 0);
            omVibrate(lbl_1_bss_B1C.chr[1].no, 60, 12, 0);
        } else {
            omVibrate(lbl_1_bss_B1C.chr[lbl_1_bss_B1C.mode[3]^1].no, 60, 12, 0);
        }
        for(i=0; i<4; i++) {
            lbl_1_bss_B1C.timer[i] = 0;
        }
        fn_1_7F84();
        HuAudFXPlay(2191);
    }
    fn_1_5CCC(0);
}

/* asm 514-632, 107 insns. Main sub-state 1: the clash. */
void fn_1_2654(void)
{
    int i;
    int doneF;

    for(i=0, doneF=0; i<2; i++) {
        if(lbl_1_bss_B1C.mode[3] == 2 || (lbl_1_bss_B1C.mode[3]^1) == i) {
            fn_1_4050(i);
        } else {
            fn_1_4D60(i);
        }
        if(lbl_1_bss_B1C.timer[i] >= 120 && doneF == 0) {
            doneF++;
        }
    }
    if(lbl_1_bss_B1C.mode[3] == 2 && lbl_1_bss_B1C.timer[0] >= 20) {
        lbl_1_bss_134C = 3;
        MgSeqModeNext();
        HuAudSStreamFadeOut(lbl_1_data_238, 100);
        lbl_1_bss_B1C.mode[0] = 0;
        lbl_1_bss_B1C.mode[1] = 0;
    }
    if(doneF != 0) {
        if(lbl_1_bss_B1C.mode[3] != 2) {
            lbl_1_bss_134C = 2;
        } else {
            lbl_1_bss_134C = 3;
        }
        MgSeqModeNext();
        HuAudSStreamFadeOut(lbl_1_data_238, 100);
        lbl_1_bss_B1C.mode[0] = 0;
        lbl_1_bss_B1C.mode[1] = 0;
        lbl_1_bss_B1C.timer[0] = 0;
    }
    fn_1_5CCC(0);
}

/* asm 635-637, 1 insn. Main sub-state 2. */
void fn_1_2800(void)
{
}

/* asm 640-671, 27 insns. Called from m554.c's finish hook. */
void fn_1_2804(void)
{
    int i;

    if(lbl_1_bss_B1C.mode[3] == 2) {
        for(i=0; i<2; i++) {
            fn_1_4050(i);
        }
        lbl_1_bss_B1C.mode[0] = 0;
    }
    fn_1_5CCC(0);
}

/* asm 674-935, 257 insns. Pre-winner sub-state 0: the result banner and the winner's pose. */
void fn_1_2870(void)
{
    Mtx mtx;
    HuVecF pos;
    HuVecF rot;
    M554_MODEL *mdlChar;
    M554_MODEL *mdlItem;
    int no;

    if(lbl_1_bss_B1C.mode[3] == 2) {
        lbl_1_bss_133C = GameMesCreate(2, 2);
        lbl_1_bss_134C = 3;
        lbl_1_bss_B1C.timer[0] = 0;
        HuAudJinglePlay(123);
    } else {
        mdlChar = &lbl_1_bss_B1C.models[lbl_1_bss_B1C.mode[3]+78];
        mdlItem = &lbl_1_bss_B1C.models[lbl_1_bss_B1C.mode[3]+3];
        no = lbl_1_bss_B1C.chr[lbl_1_bss_B1C.mode[3]].no;
        if(_CheckFlag(FLAG_MG_PRACTICE) == 0) {
            GwPlayer[no].mgCoinBonus = 10;
        }
        lbl_1_bss_133C = GameMesCreate(4, 3, lbl_1_bss_B1C.chr[lbl_1_bss_B1C.mode[3]].charNo, -1, -1, -1);
        HuAudJinglePlay(121);
        lbl_1_bss_98[2].center.x = mdlChar->pos.x;
        lbl_1_bss_98[2].center.y = 150.0f+mdlChar->pos.y;
        lbl_1_bss_98[2].center.z = 350.0f+mdlChar->pos.z;
        lbl_1_bss_98[2].rot.x = -32.0f;
        lbl_1_bss_98[2].rot.y = 0.0f;
        lbl_1_bss_98[2].rot.z = 0.0f;
        lbl_1_bss_98[2].zoom = 495.0f;
        omCameraViewMoveSimple(&lbl_1_bss_98[2], 60);
        lbl_1_bss_134C = 0;
        lbl_1_bss_B1C.player[lbl_1_bss_B1C.mode[3]].shiftMode = 1;
        lbl_1_bss_B1C.player[lbl_1_bss_B1C.mode[3]].shiftMotNo = 3;
        lbl_1_bss_B1C.player[lbl_1_bss_B1C.mode[3]].shiftTime = 0.0f;
        lbl_1_bss_B1C.player[lbl_1_bss_B1C.mode[3]].shiftSpeed = 45.0f;
        lbl_1_bss_B1C.player[lbl_1_bss_B1C.mode[3]].shiftAttr = 0;
        Hu3DModelObjMtxGet(mdlChar->modelId, CharModelItemHookGet(lbl_1_bss_B1C.chr[lbl_1_bss_B1C.mode[3]].charNo, 1, 0), mtx);
        Hu3DModelHookReset(mdlChar->modelId);
        Hu3DMtxRotGet(mtx, &rot);
        pos.x = mtx[0][3];
        pos.y = mtx[1][3];
        pos.z = mtx[2][3];
        Hu3DModelPosSetV(mdlItem->modelId, &pos);
        Hu3DModelRotSetV(mdlItem->modelId, &rot);
        mdlItem->pos.x = pos.x;
        mdlItem->pos.y = pos.y;
        mdlItem->pos.z = pos.z;
        mdlItem->rot.x = rot.x;
        mdlItem->rot.y = rot.y;
        mdlItem->rot.z = rot.z;
        fn_1_78A8();
        lbl_1_bss_B1C.timer[0] = 0;
        lbl_1_data_246[0] = lbl_1_data_246[1];
    }
    lbl_1_bss_B1C.mode[0]++;
    fn_1_5CCC(1);
}

/* asm 938-1288, 341 insns. Pre-winner sub-state 1. */
void fn_1_2C74(void)
{
    M554_MODEL *mdl;

    lbl_1_bss_B1C.timer[0]++;
    if(lbl_1_bss_B1C.mode[3] != 2) {
        mdl = &lbl_1_bss_B1C.models[lbl_1_bss_B1C.mode[3]+78];
        if(lbl_1_bss_B1C.mode[3] != 0) {
            mdl->rot.y += 8.0f;
            if(mdl->rot.y > 360.0f) {
                mdl->rot.y = 360.0f;
            }
        } else {
            mdl->rot.y -= 8.0f;
            if(mdl->rot.y < 0.0f) {
                mdl->rot.y = 0.0f;
            }
        }
        mdl = &lbl_1_bss_B1C.models[lbl_1_bss_B1C.mode[3]+3];
        if(lbl_1_bss_B1C.timer[0] <= 90) {
            mdl->pos.y += 8.0*cos((M_PI*((lbl_1_bss_B1C.timer[0]*90)/90))/180.0);
            mdl->pos.z -= 8.0*sin((M_PI*((lbl_1_bss_B1C.timer[0]*90)/90))/180.0);
            mdl->rot.x += 10.0f;
            Hu3DModelScaleSet(mdl->modelId, (90.0f-lbl_1_bss_B1C.timer[0])/90.0f, (90.0f-lbl_1_bss_B1C.timer[0])/90.0f, (90.0f-lbl_1_bss_B1C.timer[0])/90.0f);
        }
        mdl = &lbl_1_bss_B1C.models[lbl_1_bss_B1C.mode[3]+5];
        if(lbl_1_bss_B1C.mode[3] != 0) {
            mdl->rot.y -= 0.6428571428571429;
            if(mdl->rot.y < 0.0f) {
                mdl->rot.y = 0.0f;
            }
        } else {
            mdl->rot.y += 0.6428571428571429;
            if(mdl->rot.y > 0.0f) {
                mdl->rot.y = 0.0f;
            }
        }
        if(lbl_1_bss_B1C.timer[0]%3 == 0) {
            lbl_1_data_244--;
            if(lbl_1_data_244 >= 64) {
                HuAudFXVolSet(lbl_1_data_23C[1], lbl_1_data_244);
            }
        }
    } else if(lbl_1_bss_B1C.timer[0] == 180) {
        HuAudFXFadeOut(lbl_1_data_23C[0], 20);
        HuAudFXFadeOut(lbl_1_data_23C[1], 20);
    }
    if(!GameMesStatGet(lbl_1_bss_133C) && lbl_1_bss_B1C.timer[0] >= 210) {
        GameMesKill(lbl_1_bss_133C);
        MgSeqModeNext();
    }
    fn_1_5CCC(1);
    fn_1_514C(lbl_1_bss_B1C.timer[0]);
}

/* asm 1291-1310, 18 insns. Pre-winner sub-state 2; also the winner and fade-out hooks. */
void fn_1_31C8(void)
{
    lbl_1_bss_B1C.timer[0]++;
    fn_1_514C(lbl_1_bss_B1C.timer[0]);
    fn_1_5CCC(1);
}

/* asm 1313-1511, 194 insns. Place duellist no-1 (or both, for 0) and their item on the circle. */
void fn_1_3210(s32 no)
{
    float scale;
    M554_MODEL *mdlChar;
    M554_MODEL *mdlItem;
    int i;
    int end;

    if(no == 0) {
        i = 0;
        end = 2;
    } else {
        i = no-1;
        end = no;
    }
    for(; i<end; i++) {
        mdlChar = &lbl_1_bss_B1C.models[i+78];
        mdlItem = &lbl_1_bss_B1C.models[i+5];
        mdlChar->pos.x = lbl_1_bss_B1C.run[i].dist*sin((M_PI*lbl_1_bss_B1C.run[i].angle)/180.0);
        mdlChar->pos.z = -600.0+(lbl_1_bss_B1C.run[i].dist*cos((M_PI*lbl_1_bss_B1C.run[i].angle)/180.0));
        mdlChar->rot.y = 180.0f+lbl_1_bss_B1C.run[i].angle;
        mdlItem->pos.x = (lbl_1_bss_B1C.run[i].dist-40.0f)*sin((M_PI*lbl_1_bss_B1C.run[i].angle)/180.0);
        mdlItem->pos.z = -600.0+((lbl_1_bss_B1C.run[i].dist-40.0f)*cos((M_PI*lbl_1_bss_B1C.run[i].angle)/180.0));
        mdlItem->rot.y = mdlChar->rot.y-180.0f;
        scale = 0.6f+((0.9*(lbl_1_bss_B1C.run[i].dist-280.0f))/700.0);
        mdlItem->pos.y = mdlChar->pos.y-80.0f;
        Hu3DModelScaleSet(mdlItem->modelId, scale, 1.0f, scale);
    }
}

/* asm 1514-1540, 24 insns. The main-phase clock: count goes up every 30 frames. */
void fn_1_3518(void)
{
    M554_MODEL *mdl = &lbl_1_bss_B1C.models[2];

    if(lbl_1_bss_B1C.timer[0]++ >= 30) {
        lbl_1_bss_B1C.timer[0] = 0;
        lbl_1_bss_B1C.count++;
    }
}

/* asm 1543-1765, 215 insns. One duellist's step: pace from presses, then distance and speed. */
void fn_1_3578(s32 player)
{
    int stepTbl[8][6] = {
        { -3, -2, 0, 1, 2, 3 },
        { -3, -1, -1, 0, 2, 2 },
        { -4, -2, -2, -1, 1, 1 },
        { -5, -3, -3, -2, -1, 0 },
        { -6, -4, -4, -3, -2, -1 },
        { -7, -5, -5, -4, -3, -2 },
        { -8, -6, -6, -5, -4, -3 },
        { -9, -7, -7, -6, -5, -4 }
    };
    float speedTbl[6] = { 0.5f, 0.75f, 1.0f, 1.25f, 1.5f, 1.75f };
    M554_MODEL *mdl;
    HuVecF pos2D;
    int row;
    s16 pan;

    mdl = &lbl_1_bss_B1C.models[player+78];
    lbl_1_bss_B1C.pace[player].level = fn_1_38D4(player);
    row = lbl_1_bss_B1C.count/5;
    if(row > 7) {
        row = 7;
    }
    lbl_1_bss_B1C.pace[player].step = stepTbl[row][lbl_1_bss_B1C.pace[player].level];
    lbl_1_bss_B1C.run[player].dist += lbl_1_bss_B1C.pace[player].step;
    if(lbl_1_bss_B1C.run[player].dist >= 1000.0f) {
        lbl_1_bss_B1C.run[player].dist = 1000.0f;
    }
    lbl_1_bss_B1C.player[player].speed = speedTbl[lbl_1_bss_B1C.pace[player].level];
    if(lbl_1_bss_B1C.player[player].time >= 10.0f && lbl_1_data_24C[player] == 0) {
        lbl_1_data_24C[player] = 0;
        Hu3D3Dto2D(&lbl_1_bss_B1C.models[player+78].pos, 1, &pos2D);
        pan = 32.0f+((64.0f*pos2D.x)/576.0f);
        if(player != 0) {
            HuAudFXPlayPan(2189, pan);
        } else {
            HuAudFXPlayPan(2190, pan);
        }
    }
    if(lbl_1_data_24C[player] != 0 && lbl_1_bss_B1C.player[player].time < 2.0f) {
        lbl_1_data_24C[player] = 0;
    }
}

/* asm 1768-1903, 125 insns. Record this frame's press and rate the last second, 0..6. */
s32 fn_1_38D4(s32 player)
{
    int levelTbl[6] = { 0, 2, 5, 7, 10, 61 };
    int i;
    int frame;
    int num;

    lbl_1_bss_B1C.press[player][lbl_1_bss_B1C.timer[0]] = 0;
    if((lbl_1_bss_B1C.chr[player].btnDown & PAD_TRIGGER_L) && lbl_1_data_254 != 0) {
        lbl_1_data_254 = 0;
        lbl_1_bss_B1C.press[player][lbl_1_bss_B1C.timer[0]] = 1;
    } else if((lbl_1_bss_B1C.chr[player].btnDown & PAD_TRIGGER_R) && lbl_1_data_254 != 1) {
        lbl_1_data_254 = 1;
        lbl_1_bss_B1C.press[player][lbl_1_bss_B1C.timer[0]] = 1;
    }
    for(i=0, num=0; i<60; i++) {
        frame = lbl_1_bss_B1C.timer[0]-i;
        if(frame < 0) {
            frame += 60;
        }
        if(lbl_1_bss_B1C.press[player][frame] != 0) {
            num++;
        }
    }
    for(i=0; i<6; i++) {
        if(num <= levelTbl[i]) {
            break;
        }
    }
    return i;
}

/* asm 1906-1943, 36 insns. Set up one computer duellist. */
void fn_1_3AC8(s32 player)
{
    memset(&lbl_1_bss_6C[player], 0, sizeof(M554_COM));
    lbl_1_bss_6C[player].level = lbl_1_bss_B1C.chr[player].dif-1;
    lbl_1_bss_6C[player].wait = fn_1_3B58(player);
}

/* asm 1946-2088, 133 insns. A computer duellist's frames between presses. */
s32 fn_1_3B58(s32 player)
{
    int wait;

    if(lbl_1_bss_6C[player].level == 0) {
        if(lbl_1_bss_B1C.count >= 6) {
            wait = (rand8()%8)+25;
        } else {
            wait = (rand8()%5)+20;
        }
    } else if(lbl_1_bss_6C[player].level == 1) {
        if(lbl_1_bss_B1C.count >= 18) {
            wait = (rand8()%8)+6;
        } else {
            wait = (rand8()%4)+6;
        }
    } else if(lbl_1_bss_6C[player].level == 2) {
        if(lbl_1_bss_B1C.count >= 20) {
            wait = (rand8()%3)+6;
        } else {
            wait = (rand8()%3)+5;
        }
    } else if(lbl_1_bss_6C[player].level == 3) {
        if(lbl_1_bss_B1C.count >= 25) {
            wait = (rand8()%4)+4;
        } else {
            wait = (rand8()%3)+3;
        }
    }
    return wait;
}

/* asm 2091-2288, 185 insns. A computer duellist's input: alternate L and R. */
void fn_1_3D6C(s32 player)
{
    lbl_1_bss_6C[player].wait--;
    if(lbl_1_bss_6C[player].wait <= 0) {
        if(lbl_1_bss_6C[player].side != 0) {
            lbl_1_bss_B1C.chr[player].btnDown = PAD_TRIGGER_L;
        } else {
            lbl_1_bss_B1C.chr[player].btnDown = PAD_TRIGGER_R;
        }
        lbl_1_bss_6C[player].side = lbl_1_bss_6C[player].side^1;
        lbl_1_bss_6C[player].wait = fn_1_3B58(player);
    }
}

/* asm 2291-3149, 836 insns. The loser (or both, in a draw): knocked back, item flung. */
void fn_1_4050(s32 player)
{
    Mtx mtx;
    HuVecF pos;
    HuVecF rot;
    float scale;
    M554_MODEL *mdlChar;
    M554_MODEL *mdlItem;
    M554_MODEL *mdlMark;

    mdlChar = &lbl_1_bss_B1C.models[player+78];
    mdlItem = &lbl_1_bss_B1C.models[player+3];
    mdlMark = &lbl_1_bss_B1C.models[player+5];
    if(lbl_1_bss_B1C.timer[player] == 0) {
        Hu3DModelObjMtxGet(mdlChar->modelId, CharModelItemHookGet(lbl_1_bss_B1C.chr[player].charNo, 1, 0), mtx);
        Hu3DModelHookReset(mdlChar->modelId);
        Hu3DMtxRotGet(mtx, &rot);
        pos.x = mtx[0][3];
        pos.y = mtx[1][3];
        pos.z = mtx[2][3];
        Hu3DModelPosSetV(mdlItem->modelId, &pos);
        Hu3DModelRotSetV(mdlItem->modelId, &rot);
        mdlItem->pos.x = pos.x;
        mdlItem->pos.y = pos.y;
        mdlItem->pos.z = pos.z;
        mdlItem->rot.x = rot.x;
        mdlItem->rot.y = rot.y;
        mdlItem->rot.z = rot.z;
        lbl_1_bss_B1C.run[player].dist2 = lbl_1_bss_B1C.run[player].dist;
        lbl_1_bss_B1C.run[player].angle2 = lbl_1_bss_B1C.run[player].angle;
        lbl_1_bss_B1C.player[player].shiftMode = 1;
        lbl_1_bss_B1C.player[player].shiftMotNo = 4;
        lbl_1_bss_B1C.player[player].shiftTime = 0.0f;
        lbl_1_bss_B1C.player[player].shiftSpeed = 10.0f;
        lbl_1_bss_B1C.player[player].shiftAttr = HU3D_MOTATTR_LOOP;
    }
    lbl_1_bss_B1C.timer[player]++;
    if(lbl_1_bss_B1C.timer[player] < 30) {
        lbl_1_bss_B1C.run[player].dist -= 7.5;
        if(lbl_1_bss_B1C.mode[3] == 2) {
            if(player != 0) {
                lbl_1_bss_B1C.run[player].angle -= 17.75f;
            } else {
                lbl_1_bss_B1C.run[player].angle -= 22.25f;
            }
        } else {
            lbl_1_bss_B1C.run[player].angle -= 20.0f;
        }
        mdlChar->pos.y += lbl_1_bss_B1C.timer[player]/4;
        mdlChar->rot.y += 15.0f;
    } else if(lbl_1_bss_B1C.timer[player] < 60) {
        lbl_1_bss_B1C.run[player].dist += 8.5;
        lbl_1_bss_B1C.run[player].angle -= 20.0f;
        mdlChar->pos.y += lbl_1_bss_B1C.timer[player]/4;
        mdlChar->rot.z += 5.0f;
        mdlChar->rot.y += 15.0f;
        mdlChar->rot.x += 5.0f;
    } else {
        lbl_1_bss_B1C.run[player].dist += 30.0+((lbl_1_bss_B1C.timer[player]-60)*4);
        lbl_1_bss_B1C.run[player].angle -= 20.0f;
        mdlChar->pos.y += lbl_1_bss_B1C.timer[player];
        mdlChar->rot.x += 5.0f;
        mdlChar->rot.y += 15.0f;
        mdlChar->rot.z += 5.0f;
    }
    mdlChar->pos.x = lbl_1_bss_B1C.run[player].dist*sin((M_PI*lbl_1_bss_B1C.run[player].angle)/180.0);
    mdlChar->pos.z = -600.0+(lbl_1_bss_B1C.run[player].dist*cos((M_PI*lbl_1_bss_B1C.run[player].angle)/180.0));
    if(lbl_1_bss_B1C.timer[player] < 15) {
        if(lbl_1_bss_B1C.timer[player]%4 != 0) {
            Hu3DModelAttrReset(mdlMark->modelId, HU3D_ATTR_DISPOFF);
        } else {
            Hu3DModelAttrSet(mdlMark->modelId, HU3D_ATTR_DISPOFF);
        }
        scale = 0.6f-(0.02f*lbl_1_bss_B1C.timer[player]);
        Hu3DModelScaleSet(mdlMark->modelId, scale, scale, scale);
    } else if(lbl_1_bss_B1C.timer[player] < 30) {
        if(lbl_1_bss_B1C.timer[player]%2 != 0) {
            Hu3DModelAttrReset(mdlMark->modelId, HU3D_ATTR_DISPOFF);
        } else {
            Hu3DModelAttrSet(mdlMark->modelId, HU3D_ATTR_DISPOFF);
        }
        scale = 0.6f-(0.02f*lbl_1_bss_B1C.timer[player]);
        Hu3DModelScaleSet(mdlMark->modelId, scale, scale, scale);
    } else if(lbl_1_bss_B1C.timer[player] == 30) {
        Hu3DModelAttrSet(mdlMark->modelId, HU3D_ATTR_DISPOFF);
    }
    if(lbl_1_bss_B1C.timer[player] < 30) {
        lbl_1_bss_B1C.run[player].dist2 -= 7.5;
        if(lbl_1_bss_B1C.mode[3] == 2) {
            if(player != 0) {
                lbl_1_bss_B1C.run[player].angle2 -= 12.75f;
            } else {
                lbl_1_bss_B1C.run[player].angle2 -= 17.25;
            }
        } else {
            lbl_1_bss_B1C.run[player].angle2 -= 15.0f;
        }
        mdlItem->pos.y += lbl_1_bss_B1C.timer[player]/6;
    } else if(lbl_1_bss_B1C.timer[player] < 60) {
        lbl_1_bss_B1C.run[player].dist2 += 8.5;
        lbl_1_bss_B1C.run[player].angle2 -= 15.0f;
        mdlItem->pos.y += lbl_1_bss_B1C.timer[player]/6;
    } else if(lbl_1_bss_B1C.timer[player] < 90) {
        lbl_1_bss_B1C.run[player].dist2 += 8.5;
        lbl_1_bss_B1C.run[player].angle2 -= 20.0f;
        mdlItem->pos.y += lbl_1_bss_B1C.timer[player]/4;
    } else {
        lbl_1_bss_B1C.run[player].dist2 += 30.0+((lbl_1_bss_B1C.timer[player]-60)*4);
        lbl_1_bss_B1C.run[player].angle2 -= 20.0f;
        mdlItem->pos.y += lbl_1_bss_B1C.timer[player];
    }
    mdlItem->pos.x = lbl_1_bss_B1C.run[player].dist2*sin((M_PI*lbl_1_bss_B1C.run[player].angle2)/180.0);
    mdlItem->pos.z = -600.0+(lbl_1_bss_B1C.run[player].dist2*cos((M_PI*lbl_1_bss_B1C.run[player].angle2)/180.0));
    mdlItem->rot.x -= 5.0f;
    mdlItem->rot.y += 10.0f;
    mdlItem->rot.z += 5.0f;
}

/* asm 3152-3409, 251 insns. The winner of the clash keeps running. fn_1_3210 is inlined. */
void fn_1_4D60(s32 player)
{
    lbl_1_bss_B1C.run[player].dist += 4.0f;
    if(lbl_1_bss_B1C.run[player].dist > 1000.0f) {
        lbl_1_bss_B1C.run[player].dist = 1000.0f;
    }
    fn_1_3210(player+1);
    lbl_1_bss_B1C.player[player].speed += 0.05f;
    if(lbl_1_bss_B1C.player[player].speed > 1.5f) {
        lbl_1_bss_B1C.player[player].speed = 1.5f;
    }
}

/* asm 3412-3572, 153 insns. Model 2 sinks, or (after a draw) backs away. */
s32 fn_1_514C(s32 time)
{
    float move;
    M554_MODEL *mdl;
    int ret;
    int n;

    ret = 0;
    mdl = &lbl_1_bss_B1C.models[2];
    if(lbl_1_bss_B1C.mode[3] != 2) {
        if(time >= 240) {
            time = 240;
        }
        move = 1.0f+(0.3f*time);
        if(move >= 50.0f) {
            move = 50.0f;
        }
        mdl->pos.y -= 1.0+(6.0*sin((M_PI*((time*90)/240))/180.0));
    } else {
        time -= 125;
        if(time > 0) {
            if(time >= 60) {
                time = 60;
            }
            move = -(1.0+(100.0*sin((M_PI*((time*90)/60))/180.0)));
            n = fn_1_A54();
            if(n > 1) {
                fn_1_A34();
            }
        } else {
            move = 0.0f;
        }
    }
    mdl->pos.z -= move;
    return ret;
}

/* asm 3575-4020, 427 insns. Object main added by m554.c's start hook: the stage's pulse. */
void fn_1_53B0(OMOBJ *obj)
{
    int timeTbl[6] = { 300, 600, 900, 1200, 1800, 2400 };
    int shakeTbl[12] = { 0, 1, 3, 2, 0, 2, 3, 1, 0, 1, 3, 1 };
    float time;
    float speed;
    int i;

    if(lbl_1_bss_134C == 0) {
        return;
    }
    lbl_1_bss_1354++;
    switch(lbl_1_bss_134C) {
        case 0:
            return;

        case 1:
            for(i=0; i<6; i++) {
                if(lbl_1_bss_1354 == timeTbl[i]) {
                    lbl_1_bss_1358[0] += 2;
                    Hu3DMotionSpeedSet(lbl_1_bss_B1C.models[77].modelId, 1.0+(0.1*lbl_1_bss_1358[0]));
                    lbl_1_data_246[1] += 500;
                }
            }
            break;

        case 2:
            lbl_1_bss_1350++;
            if(lbl_1_bss_1358[0] > -1 && lbl_1_bss_1350 >= 5) {
                lbl_1_bss_1358[0]--;
                lbl_1_bss_1350 = 0;
            }
            break;

        case 3:
            lbl_1_bss_1350++;
            if(lbl_1_bss_1350 >= 5) {
                if(lbl_1_bss_1358[0] < 18) {
                    lbl_1_bss_1358[0]++;
                }
                lbl_1_bss_1350 = 0;
            }
            break;
    }
    if(shakeTbl[lbl_1_bss_1354%12] == 0) {
        Center.y = 290.0-(0.8*(lbl_1_bss_1358[0]+1));
    }
    if(shakeTbl[lbl_1_bss_1354%12] == 1) {
        Center.y = 290.0f;
    }
    if(shakeTbl[lbl_1_bss_1354%12] == 2) {
        Center.y = 290.0+(0.8*(lbl_1_bss_1358[0]+1));
    }
    if(shakeTbl[lbl_1_bss_1354%12] == 3) {
        Center.y = 290.0+(1.2*(lbl_1_bss_1358[0]+1));
    }
    if(lbl_1_bss_1348 == 0) {
        time = Hu3DMotionTimeGet(lbl_1_bss_B1C.models[77].modelId);
        speed = 1.0+(0.1*lbl_1_bss_1358[0]);
        if(time+speed > 99.0f) {
            Hu3DMotionTimeSet(lbl_1_bss_B1C.models[77].modelId, (50.0f+(time+speed))-99.0f);
        }
    }
    if(lbl_1_data_246[0] != lbl_1_data_246[1]) {
        lbl_1_data_246[0] += 10;
        if(lbl_1_data_246[0] > lbl_1_data_246[1]) {
            lbl_1_data_246[0] = lbl_1_data_246[1];
        }
        HuAudFXPitchSet(lbl_1_data_23C[1], lbl_1_data_246[0]);
    }
}

/* asm 4023-4047, 21 insns. */
void fn_1_5A5C(void)
{
    int i;

    for(i=0; i<7; i++) {
        memset(&lbl_1_bss_14[i], 0, sizeof(M554_SLOT));
    }
}

/* asm 4050-4191, 135 insns. Frames until one of models 7..13 plays again. */
s32 fn_1_5AB0(void)
{
    if(lbl_1_bss_B1C.count <= 15) {
        return ((rand8()%5)*8)+((rand8()%10)+40);
    } else if(lbl_1_bss_B1C.count <= 20) {
        return ((rand8()%5)*7)+((rand8()%9)+35);
    } else if(lbl_1_bss_B1C.count <= 25) {
        return ((rand8()%5)*6)+((rand8()%8)+30);
    } else if(lbl_1_bss_B1C.count <= 30) {
        return ((rand8()%5)*5)+((rand8()%7)+25);
    } else {
        return ((rand8()%5)*4)+((rand8()%6)+20);
    }
}

/*
 * asm 4194-4608, 393 insns. Models 7..13: each waits, plays its motion once,
 * hides, and waits again. endF stops them after the current play.
 */
void fn_1_5CCC(s32 endF)
{
    float time;
    M554_MODEL *mdl;
    int i;

    for(i=0; i<7; i++) {
        mdl = &lbl_1_bss_B1C.models[i+7];
        switch(lbl_1_bss_14[i].mode) {
            case 0:
                lbl_1_bss_14[i].mode = 1;
                lbl_1_bss_14[i].wait = fn_1_5AB0();
                break;

            case 1:
                lbl_1_bss_14[i].wait--;
                if(lbl_1_bss_14[i].wait <= 0) {
                    Hu3DMotionTimeSet(mdl->modelId, 0.0f);
                    Hu3DMotionSpeedSet(mdl->modelId, 1.0f);
                    Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
                    lbl_1_bss_14[i].mode = 2;
                    if(endF != 0) {
                        lbl_1_bss_14[i].mode = 3;
                    }
                    lbl_1_bss_14[i].maxTime = Hu3DMotionMaxTimeGet(mdl->modelId);
                }
                break;

            case 2:
                time = Hu3DMotionTimeGet(mdl->modelId);
                if(time >= lbl_1_bss_14[i].maxTime) {
                    Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
                    lbl_1_bss_14[i].mode = 1;
                    if(endF != 0) {
                        lbl_1_bss_14[i].mode = 3;
                    }
                    lbl_1_bss_14[i].wait = fn_1_5AB0();
                }
                break;
        }
    }
    if(endF != 0) {
        lbl_1_bss_1348 = 1;
    }
}
