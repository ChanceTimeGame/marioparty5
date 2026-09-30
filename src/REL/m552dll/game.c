/*
 * m552dll/game.c -- the duel's flow: fade-in, the main state, the winner, and
 * each duellist's state machine (grab, pull, carry, turn, drop, clear, score
 * popups). Written from the reference assembly, functions in reference order;
 * line ranges are into build/mp5-asm/m552dll/asm/REL/m552dll/game.s.
 */

#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/hu3d.h"
#include "game/hsfformat.h"
#include "game/wipe.h"
#include "game/pad.h"
#include "game/audio.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/flag.h"
#include "game/mgdata.h"
#include "game/mg/seqman.h"
#include "game/mg/timer.h"
#include "game/mg/score.h"

#include "REL/m552dll/m552.h"

#include "math.h"
#include "string.h"

/* --- .data --- */

/* Eleven texture-cell offsets, quarter steps. */
float lbl_1_data_360[22] = {
    0.0f, 0.0f, 0.0f, 0.25f, 0.0f, 0.5f, 0.0f, 0.75f,
    0.25f, 0.0f, 0.25f, 0.25f, 0.25f, 0.5f, 0.25f, 0.75f,
    0.5f, 0.0f, 0.5f, 0.25f, 0.5f, 0.5f
};

int lbl_1_data_3B8 = -1;            /* the BGM stream */
int lbl_1_data_3BC = -1;            /* the conveyor loop */
int lbl_1_data_3C0[4] = { 0, 0, 0, 0 };

/* --- .bss (CodeWarrior lays it out in reverse definition order) --- */

HUSPRGRPID lbl_1_bss_4918;          /* the record window */
MGSCORE *lbl_1_bss_4914;            /* the record */
int lbl_1_bss_4910;                 /* the record value */
MGTIMER *lbl_1_bss_490C;
GAMEMESID lbl_1_bss_4908;

/* asm 1-167, 237 insns. Fade-in 0: the record window, the duellists walk in. */
void fn_1_1C40(void)
{
    int i;

    if(lbl_1_bss_4794.count[0] == 0) {
        switch(lbl_1_bss_0) {
            case 0:
                lbl_1_bss_4910 = GWMgRecordGet(8);
                break;

            case 1:
                lbl_1_bss_4910 = GWMgRecordGet(10);
                break;

            case 2:
                lbl_1_bss_4910 = GWMgRecordGet(11);
                break;
        }
        lbl_1_bss_4918 = MgScoreWinCreate(136, 40);
        MgScoreWinPosSet(lbl_1_bss_4918, 288.0f, 420.0f);
        MgScoreWinTPLvlSet(lbl_1_bss_4918, 0.7f);
        lbl_1_bss_4914 = MgScoreInit(0x960030);
        lbl_1_bss_4914->dispLeadZeroF = TRUE;
        MgScoreMaxDigitSet(lbl_1_bss_4914, 6);
        MgScoreValueSet(lbl_1_bss_4914, lbl_1_bss_4910);
        MgScoreColorSet(lbl_1_bss_4914, 66, 255, 122);
        MgScorePosSet(lbl_1_bss_4914, 259.0f, 420.0f);
        espDispOn(lbl_1_bss_33C0);
        espPosSet(lbl_1_bss_33C0, 239.0f, 420.0f);
    }
    for(i=0; i<2; i++) {
        lbl_1_bss_4794.models[i].pos.x += 9.0*cos((M_PI*((i*30)+75))/180.0);
        lbl_1_bss_4794.models[i].pos.z -= 9.0*sin((M_PI*75.0)/180.0);
    }
    if(lbl_1_bss_4794.count[0] == 8) {
        omCameraViewMoveSimpleMulti(HU3D_CAM0, lbl_1_bss_14, 152);
        omCameraViewMoveSimpleMulti(HU3D_CAM1, lbl_1_bss_14, 152);
        omCameraViewMoveSimpleMulti(HU3D_CAM2, lbl_1_bss_14, 152);
    }
    lbl_1_bss_4794.count[0]++;
    if(lbl_1_bss_4794.count[0] >= 65) {
        lbl_1_bss_4794.mode[0]++;
        lbl_1_bss_4794.mode[0]++;
        lbl_1_bss_4794.count[0] = 0;
        WipeColorSet(255, 255, 255);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 55);
    }
    if(lbl_1_bss_4794.count[0] == 30) {
        lbl_1_data_3B8 = HuAudBGMPlay(62);
    }
}

/* asm 168-246, 99 insns. Fade-in 1 (skipped by fn_1_1C40): walk on, then fade out. */
void fn_1_1FF4(void)
{
    int i;

    for(i=0; i<2; i++) {
        if(lbl_1_bss_4794.models[i].pos.z > -380.0f) {
            lbl_1_bss_4794.models[i].pos.x += 8.0*cos((M_PI*((i*30)+75))/180.0);
            lbl_1_bss_4794.models[i].pos.z -= 8.0*sin((M_PI*75.0)/180.0);
        }
    }
    if(lbl_1_bss_4794.count[0]++ >= 10) {
        lbl_1_bss_4794.mode[0]++;
        WipeColorSet(255, 255, 255);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        lbl_1_bss_4794.count[0] = 0;
    }
}

/*
 * asm 247-520, 335 insns. Fade-in 2: once the wipe is out, swap the arena for
 * the boards (models 8-18, the counters, 31-34 and the faces) and fade in.
 */
void fn_1_2180(void)
{
    u8 i;

    for(i=0; i<2; i++) {
        if(lbl_1_bss_4794.models[i].pos.z > -400.0f) {
            lbl_1_bss_4794.models[i].pos.x += 9.0*cos((M_PI*((i*30)+75))/180.0);
            lbl_1_bss_4794.models[i].pos.z -= 9.0*sin((M_PI*75.0)/180.0);
        }
    }
    i = WipeCheckEnd();
    if(i == 0) {
        lbl_1_bss_4794.mode[0]++;
        for(i=0; i<8; i++) {
            Hu3DModelAttrSet(lbl_1_bss_4794.models[i].modelId, HU3D_ATTR_DISPOFF);
        }
        lbl_1_bss_4794.player[0].motNo = 0;
        lbl_1_bss_4794.player[1].motNo = 0;
        for(i=0; i<2; i++) {
            Hu3DModelAttrReset((lbl_1_bss_4794.models+35)[i].modelId, HU3D_ATTR_DISPOFF);
        }
        for(i=0; i<11; i++) {
            Hu3DModelAttrReset((lbl_1_bss_4794.models+8)[i].modelId, HU3D_ATTR_DISPOFF);
            if(i == 0 || i == 1) {
                Hu3DMotionSpeedSet((lbl_1_bss_4794.models+8)[i].modelId, 2.0f);
                Hu3DMotionTimeSet((lbl_1_bss_4794.models+8)[i].modelId, 0.0f);
                Hu3DModelAttrSet((lbl_1_bss_4794.models+8)[i].modelId, HU3D_MOTATTR_LOOP);
            }
            if(i == 8 || i == 9) {
                Hu3DMotionSpeedSet((lbl_1_bss_4794.models+8)[i].modelId, 1.0f);
                Hu3DMotionTimeSet((lbl_1_bss_4794.models+8)[i].modelId, 0.0f);
                Hu3DModelAttrSet((lbl_1_bss_4794.models+8)[i].modelId, HU3D_MOTATTR_LOOP);
            }
        }
        for(i=0; i<12; i++) {
            Hu3DModelAttrReset((lbl_1_bss_4794.models+19)[i].modelId, HU3D_ATTR_DISPOFF);
        }
        for(i=0; i<4; i++) {
            Hu3DModelAttrReset((lbl_1_bss_4794.models+31)[i].modelId, HU3D_ATTR_DISPOFF);
            Hu3DMotionSpeedSet((lbl_1_bss_4794.models+31)[i].modelId, 2.0f);
            Hu3DMotionTimeSet((lbl_1_bss_4794.models+31)[i].modelId, 0.0f);
            Hu3DModelAttrSet((lbl_1_bss_4794.models+31)[i].modelId, HU3D_MOTATTR_LOOP);
        }
        WipeColorSet(255, 255, 255);
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
        omCameraViewMoveSimpleMulti(HU3D_CAM0, &lbl_1_bss_14[1], 1);
        omCameraViewMoveSimpleMulti(HU3D_CAM1, &lbl_1_bss_14[1], 1);
        omCameraViewMoveSimpleMulti(HU3D_CAM2, &lbl_1_bss_14[1], 1);
        lbl_1_bss_3700.board[0].score = -1;
        lbl_1_bss_3700.board[1].score = -1;
        fn_1_6920();
        Hu3DModelAttrSet(lbl_1_bss_4794.models[18].modelId, HU3D_MOTATTR_LOOP);
        Hu3DMotionSpeedSet(lbl_1_bss_4794.models[18].modelId, 2.16f);
        lbl_1_data_3BC = HuAudFXPlay(2153);
    }
}

/* asm 521-567, 62 insns. Fade-in 3: once the wipe is in, start; party modes get a timer. */
void fn_1_26BC(void)
{
    u8 endF;

    if((endF = WipeCheckEnd()) == 0) {
        lbl_1_bss_4794.mode[0] = 0;
        MgSeqModeNext();
        if(lbl_1_bss_0 != 0) {
            lbl_1_bss_490C = MgTimerCreate(3);
            if(lbl_1_bss_0 == 1) {
                MgTimerParamSet(lbl_1_bss_490C, 10800, 0, 0);
            } else {
                MgTimerParamSet(lbl_1_bss_490C, 18000, 0, 0);
            }
            MgTimerPosSet(lbl_1_bss_490C, 294.0f, 64.0f);
            MgTimerModeOnSet(lbl_1_bss_490C, FALSE);
        }
    }
}

/* asm 568-609, 55 insns. Main 0: start the timer. */
void fn_1_27B4(void)
{
    switch(lbl_1_bss_0) {
        case 0:
            lbl_1_bss_490C = MgTimerCreate(0);
            MgTimerParamSet(lbl_1_bss_490C, 3600, 0, 0);
            MgTimerPosSet(lbl_1_bss_490C, 288.0f, 64.0f);
            MgTimerModeOnSet(lbl_1_bss_490C, TRUE);
            break;

        case 1:
        case 2:
            MgTimerModeOnSet(lbl_1_bss_490C, TRUE);
            break;
    }
    lbl_1_bss_4794.mode[0]++;
    fn_1_88EC();
}

/* asm 610-650, 40 insns. Main 1: both duellists and the queue until the time is up. */
void fn_1_2890(void)
{
    int i;

    fn_1_BADC();
    for(i=0; i<2; i++) {
        if(lbl_1_bss_4794.chr[i].dif != 0) {
            fn_1_9238(i);
        }
        fn_1_3374(i);
    }
    fn_1_88EC();
    if(MgTimerDoneCheck(lbl_1_bss_490C)) {
        lbl_1_bss_4794.mode[0]++;
    }
    fn_1_6920();
    fn_1_6DE0();
}

/* asm 651-737, 92 insns. Main 2: let clears finish, then the winner. */
void fn_1_2930(void)
{
    int count;
    int i;
    int popupF;

    count = 0;
    for(i=0, popupF=0; i<2; i++) {
        if(lbl_1_bss_4794.mode[i+2] == 4 || lbl_1_bss_4794.mode[i+2] == 5 || lbl_1_bss_4794.mode[i+2] == 6) {
            if(fn_1_5A34(i)) {
                lbl_1_bss_4794.mode[i+2] = 0;
            }
        } else {
            count++;
        }
    }
    i = fn_1_6920();
    popupF = fn_1_6DE0();
    if(i != 0 && popupF == 0 && count == 2) {
        lbl_1_bss_4794.mode[0] = 0;
        MgSeqModeNext();
        Hu3DMotionSpeedSet(lbl_1_bss_4794.models[18].modelId, 0.0f);
        HuAudSStreamFadeOut(lbl_1_data_3B8, 1000);
        HuAudFXFadeOut(lbl_1_data_3BC, 20);
    } else {
        fn_1_88EC();
    }
}

/* asm 738-744, 9 insns. */
void fn_1_2AA0(void)
{
    lbl_1_bss_4794.mode[0] = 0;
    lbl_1_bss_4794.mode[1] = 0;
}

/* asm 745-883, 225 insns. Object main: pulse the new record's digits. */
void fn_1_2AC4(OMOBJ *obj)
{
    if(lbl_1_data_3C0[2] == 0) {
        lbl_1_data_3C0[3]++;
        MgScoreDigitScaleSet(lbl_1_bss_4914, 1.0f+(0.02f*lbl_1_data_3C0[3]), 1.0f+(0.02f*lbl_1_data_3C0[3]));
        espScaleSet(lbl_1_bss_33C0, 1.0f+(0.02f*lbl_1_data_3C0[3]), 1.0f+(0.02f*lbl_1_data_3C0[3]));
        if(lbl_1_data_3C0[3] == 10) {
            lbl_1_data_3C0[2] = 1;
            lbl_1_data_3C0[3] = 0;
        }
    } else {
        lbl_1_data_3C0[3]++;
        MgScoreDigitScaleSet(lbl_1_bss_4914, 1.2f-(0.04f*lbl_1_data_3C0[3]), 1.2f-(0.04f*lbl_1_data_3C0[3]));
        espScaleSet(lbl_1_bss_33C0, 1.2f-(0.04f*lbl_1_data_3C0[3]), 1.2f-(0.04f*lbl_1_data_3C0[3]));
        if(lbl_1_data_3C0[3] == 5) {
            lbl_1_data_3C0[2] = 0;
            lbl_1_data_3C0[3] = 0;
        }
    }
}

/* asm 884-1147, 331 insns. Winner: the higher score wins; a draw is a draw. A new record is shown first. */
void fn_1_2E48(void)
{
    int player;
    s32 no;

    switch(lbl_1_bss_4794.mode[1]) {
        case 0:
            espDispOn(lbl_1_bss_33C0);
            espTPLvlSet(lbl_1_bss_33C0, 1.0f);
            lbl_1_bss_4794.count[0] = 0;
            if(lbl_1_bss_3700.board[0].score == lbl_1_bss_3700.board[1].score) {
                lbl_1_bss_4908 = GameMesCreate(2, 2);
                HuAudJinglePlay(123);
                CharFXPlayPan(lbl_1_bss_4794.chr[0].charNo, 512, 48);
                CharFXPlayPan(lbl_1_bss_4794.chr[1].charNo, 512, 80);
                fn_1_7800(0, 2);
                fn_1_7800(1, 2);
            } else {
                player = 0;
                if(lbl_1_bss_3700.board[0].score < lbl_1_bss_3700.board[1].score) {
                    player = 1;
                }
                no = lbl_1_bss_4794.chr[player].no;
                if(!_CheckFlag(FLAG_MG_PRACTICE)) {
                    GwPlayer[no].mgCoinBonus = 10;
                }
                if(lbl_1_bss_3700.board[player].score > lbl_1_bss_4910 && lbl_1_bss_4794.chr[player].dif == 0) {
                    lbl_1_bss_4908 = GameMesCreate(14, lbl_1_bss_3700.board[player].score);
                    switch(lbl_1_bss_0) {
                        case 0:
                            GWMgRecordSet(8, lbl_1_bss_3700.board[player].score);
                            break;

                        case 1:
                            GWMgRecordSet(10, lbl_1_bss_3700.board[player].score);
                            break;

                        case 2:
                            GWMgRecordSet(11, lbl_1_bss_3700.board[player].score);
                            break;
                    }
                    MgScoreValueSet(lbl_1_bss_4914, lbl_1_bss_3700.board[player].score);
                    lbl_1_bss_4794.mode[1]++;
                    lbl_1_bss_4794.mode[2] = player;
                    omAddObjEx(lbl_1_bss_4794.objman, 0x7FDA, 0, 0, OM_GRP_NONE, fn_1_2AC4);
                    if(!_CheckFlag(FLAG_MG_PRACTICE)) {
                        HuAudJinglePlay(134);
                    } else {
                        lbl_1_bss_4794.count[0] = 150;
                    }
                } else {
                    lbl_1_bss_4908 = GameMesCreate(4, 3, lbl_1_bss_4794.chr[player].charNo, -1, -1, -1);
                    HuAudJinglePlay(121);
                    CharFXPlayPan(lbl_1_bss_4794.chr[player].charNo, 506, (player*32)+48);
                }
                fn_1_7800(player, 1);
                fn_1_7800(player^1, 2);
            }
            lbl_1_bss_4794.mode[1]++;
            break;

        case 1:
            lbl_1_bss_4794.count[0]++;
            if(GameMesStatGet(lbl_1_bss_4908) == 0 && lbl_1_bss_4794.count[0] >= 208) {
                GameMesKill(lbl_1_bss_4908);
                MgSeqModeNext();
            }
            break;

        case 2:
            lbl_1_bss_4794.count[0]++;
            if(GameMesStatGet(lbl_1_bss_4908) == 0 && lbl_1_bss_4794.count[0] >= 150) {
                GameMesKill(lbl_1_bss_4908);
                lbl_1_bss_4908 = GameMesCreate(4, 3, lbl_1_bss_4794.chr[lbl_1_bss_4794.mode[2]].charNo, -1, -1, -1);
                lbl_1_bss_4794.mode[1]--;
                lbl_1_bss_4794.count[0] = 0;
                HuAudJinglePlay(121);
                CharFXPlayPan(lbl_1_bss_4794.chr[lbl_1_bss_4794.mode[2]].charNo, 506, (lbl_1_bss_4794.mode[2]*32)+48);
            }
            break;
    }
}

/* asm 1148-1458, 314 insns. One duellist's state (jumptable data_3D0). */
void fn_1_3374(int player)
{
    M552_BOARD *board = &lbl_1_bss_3700.board[player];

    if(lbl_1_bss_4794.count[player+2] != 0) {
        fn_1_4534(player);
    }
    switch(lbl_1_bss_4794.mode[player+2]) {
        case 0:
            fn_1_385C(player, 0);
            if(fn_1_3B98(player)) {
                lbl_1_bss_4794.mode[player+2] = 1;
            }
            board->blinkF = 0;
            board->blinkPrevF = 0;
            break;

        case 1:
            fn_1_385C(player, 1);
            if(fn_1_41C0(player)) {
                lbl_1_bss_4794.mode[player+2] = 2;
            }
            break;

        case 2:
            lbl_1_bss_3700.board[player].timer++;
            fn_1_385C(player, 2);
            if(fn_1_4E94(player) && lbl_1_bss_4794.count[player+2] == 0) {
                lbl_1_bss_4794.mode[player+2] = 3;
            }
            if(lbl_1_bss_4794.count[player+2] == 0) {
                if(fn_1_7134(player)) {
                    lbl_1_bss_4794.mode[player+2] = 7;
                }
            } else {
                fn_1_4DA4(player);
            }
            if(lbl_1_bss_4794.mode[player+2] == 2) {
                fn_1_4C50(player);
                if(lbl_1_bss_4794.chr[player].btnDown & PAD_BUTTON_A) {
                    if(player != 0) {
                        HuAudFXPlay(2159);
                    } else {
                        HuAudFXPlay(2158);
                    }
                }
            } else {
                fn_1_8644(player, 1);
            }
            break;

        case 3:
            if(fn_1_57D4(player)) {
                if(fn_1_6650(player)) {
                    lbl_1_bss_4794.mode[player+2] = 4;
                } else {
                    lbl_1_bss_4794.mode[player+2] = 0;
                }
            }
            break;

        case 4:
            fn_1_385C(player, 0);
            if(fn_1_5A34(player)) {
                lbl_1_bss_4794.mode[player+2] = 0;
            }
            if(fn_1_3B98(player)) {
                if(lbl_1_bss_4794.mode[player+2] == 0) {
                    lbl_1_bss_4794.mode[player+2] = 1;
                } else {
                    lbl_1_bss_4794.mode[player+2] = 5;
                }
            }
            break;

        case 5:
            fn_1_385C(player, 1);
            if(fn_1_5A34(player)) {
                lbl_1_bss_4794.mode[player+2] = 1;
            }
            if(fn_1_41C0(player)) {
                if(lbl_1_bss_4794.mode[player+2] == 1) {
                    lbl_1_bss_4794.mode[player+2] = 2;
                } else {
                    lbl_1_bss_4794.mode[player+2] = 6;
                }
            }
            break;

        case 6:
            lbl_1_bss_3700.board[player].timer++;
            fn_1_385C(player, 2);
            if(fn_1_5A34(player)) {
                lbl_1_bss_4794.mode[player+2] = 2;
            }
            break;

        case 7:
            if(fn_1_7400(player)) {
                lbl_1_bss_4794.mode[player+2] = 8;
            }
            break;

        case 8:
            fn_1_385C(player, 0);
            if(fn_1_7574(player)) {
                lbl_1_bss_4794.mode[player+2] = 0;
            }
            break;
    }
    fn_1_6834(player);
}

/*
 * asm 1459-1643, 207 insns. Move the cursor by the stick at the difficulty's
 * speed, inside the duellist's half; type 2 carries the held piece, 1 and 2
 * turn it on L/R.
 */
void fn_1_385C(int player, int type)
{
    M552_BOARD *board = &lbl_1_bss_3700.board[player];
    float speed[5] = { 11.5f, 10.5f, 11.5f, 12.8f, 13.5f };

    if(lbl_1_bss_4794.chr[player].stkX > 0) {
        board->cursor.x += speed[lbl_1_bss_4794.chr[player].dif];
    }
    if(lbl_1_bss_4794.chr[player].stkX < 0) {
        board->cursor.x -= speed[lbl_1_bss_4794.chr[player].dif];
    }
    if(lbl_1_bss_4794.chr[player].stkY > 0) {
        board->cursor.y += speed[lbl_1_bss_4794.chr[player].dif];
    }
    if(lbl_1_bss_4794.chr[player].stkY < 0) {
        board->cursor.y -= speed[lbl_1_bss_4794.chr[player].dif];
    }
    if(board->cursor.y > 300.0f) {
        board->cursor.y = 300.0f;
    }
    if(board->cursor.y < -525.0f) {
        board->cursor.y = -525.0f;
    }
    if(player != 0) {
        if(board->cursor.x > 750.0f) {
            board->cursor.x = 750.0f;
        }
        if(board->cursor.x < -150.0f) {
            board->cursor.x = -150.0f;
        }
    } else {
        if(board->cursor.x > 150.0f) {
            board->cursor.x = 150.0f;
        }
        if(board->cursor.x < -750.0f) {
            board->cursor.x = -750.0f;
        }
    }
    if(type == 2) {
        board->held.x = board->cursor.x;
        board->held.y = board->cursor.y;
    }
    if(type != 0) {
        if((lbl_1_bss_4794.chr[player].btnDown & PAD_TRIGGER_L) && board->held.activeF != 0) {
            fn_1_4450(player, 0);
        }
        if((lbl_1_bss_4794.chr[player].btnDown & PAD_TRIGGER_R) && board->held.activeF != 0) {
            fn_1_4450(player, 1);
        }
    }
}

/*
 * asm 1644-1988, 394 insns. On A, grab the first falling piece under the
 * cursor: copy it to the held piece with board block models, free the queue
 * piece, and start the pull (count[player] 8).
 */
int fn_1_3B98(int player)
{
    float xMin;
    float xMax;
    float time;
    float dy;
    float absDy;
    int i;
    int w;
    int h;
    int j;
    M552_SLOT *slot;

    time = -1.0f;
    if(lbl_1_bss_4794.chr[player].btnDown & PAD_BUTTON_A) {
        for(i=0; i<20; i++) {
            if(lbl_1_bss_3700.piece[i].activeF == 0) {
                continue;
            }
            if(0.0f == lbl_1_bss_3700.piece[i].rot || 180.0f == lbl_1_bss_3700.piece[i].rot) {
                w = lbl_1_data_410[lbl_1_bss_3700.piece[i].kind*2];
                h = lbl_1_data_410[(lbl_1_bss_3700.piece[i].kind*2)+1];
            } else {
                w = lbl_1_data_410[(lbl_1_bss_3700.piece[i].kind*2)+1];
                h = lbl_1_data_410[lbl_1_bss_3700.piece[i].kind*2];
            }
            xMax = 15.0f+(lbl_1_bss_3700.piece[i].x+((100.0f*w)/2.0f));
            xMin = (lbl_1_bss_3700.piece[i].x-((100.0f*w)/2.0f))-15.0f;
            if(player == 0) {
                xMax += 40.0f;
            } else {
                xMin -= 40.0f;
            }
            if(lbl_1_bss_3700.board[player].cursor.x > xMax) {
                continue;
            }
            if(lbl_1_bss_3700.board[player].cursor.x < xMin) {
                continue;
            }
            if(lbl_1_bss_3700.piece[i].y-lbl_1_bss_3700.board[player].cursor.y >= 0.0f) {
                dy = lbl_1_bss_3700.piece[i].y-lbl_1_bss_3700.board[player].cursor.y;
            } else {
                dy = -(lbl_1_bss_3700.piece[i].y-lbl_1_bss_3700.board[player].cursor.y);
            }
            absDy = dy;
            if(absDy > ((h*100)/2)+25) {
                continue;
            }
            lbl_1_bss_4794.pos[player].x = lbl_1_bss_3700.piece[i].x-lbl_1_bss_3700.board[player].cursor.x;
            lbl_1_bss_4794.pos[player].y = lbl_1_bss_3700.piece[i].y-lbl_1_bss_3700.board[player].cursor.y;
            memcpy(&lbl_1_bss_3700.board[player].held, &lbl_1_bss_3700.piece[i], sizeof(M552_PIECE));
            for(j=0; j<25; j++) {
                if(lbl_1_bss_3700.board[player].held.cell[j] != 0) {
                    if(time < 0.0f) {
                        time = Hu3DMotionTimeGet(lbl_1_bss_3700.piece[i].slot[j]);
                    }
                    lbl_1_bss_3700.board[player].held.slot[j] = fn_1_8D4C(lbl_1_bss_3700.board[player].held.cell[j], 1, time);
                }
            }
            fn_1_8F2C(player, 1);
            for(j=0; j<25; j++) {
                if(lbl_1_bss_3700.board[player].held.cell[j] != 0) {
                    slot = &lbl_1_bss_1340[lbl_1_bss_3700.board[player].held.slot[j]];
                    Hu3DModelPosSetV(slot->modelId, &slot->pos);
                }
            }
            fn_1_879C(i, 0);
            fn_1_82BC(player);
            lbl_1_bss_4794.count[player] = 8;
            return 1;
        }
    }
    return 0;
}

/* asm 1989-2129, 164 insns. The pull: the held piece comes to the cursor over 8 frames. */
int fn_1_41C0(int player)
{
    lbl_1_bss_4794.count[player]--;
    lbl_1_bss_3700.board[player].held.x = lbl_1_bss_3700.board[player].cursor.x+((lbl_1_bss_4794.pos[player].x*lbl_1_bss_4794.count[player])/8.0f);
    lbl_1_bss_3700.board[player].held.y = lbl_1_bss_3700.board[player].cursor.y+((lbl_1_bss_4794.pos[player].y*lbl_1_bss_4794.count[player])/8.0f);
    if(player == 0) {
        lbl_1_bss_3700.board[player].held.z += 15.0f;
    } else {
        lbl_1_bss_3700.board[player].held.z += 14.65;
    }
    Hu3DMotionTimeSet((lbl_1_bss_4794.models+12)[player].modelId, (5-lbl_1_bss_4794.count[player])*10);
    if(lbl_1_bss_4794.count[player] == 0) {
        lbl_1_bss_3700.board[player].timer = 0;
        return 1;
    }
    if(lbl_1_bss_4794.count[player] == 7) {
        if(player != 0) {
            HuAudFXPlay(2155);
        } else {
            HuAudFXPlay(2154);
        }
    }
    return 0;
}

/* asm 2130-2184, 57 insns. Start a quarter turn (dir 0 one way, 1 the other) over 15 frames. */
void fn_1_4450(int player, int dir)
{
    if(lbl_1_bss_4794.count[player+2] == 0) {
        lbl_1_bss_4794.count[player+2] = 15;
        lbl_1_bss_4794.pos[player].z = (90-(dir*180))/15;
        if(player != 0) {
            HuAudFXPlay(2167);
        } else {
            HuAudFXPlay(2166);
        }
    }
}

/* asm 2185-2235, 62 insns. One frame of the turn, rot kept in [0, 360). */
void fn_1_4534(int player)
{
    lbl_1_bss_3700.board[player].held.rot += lbl_1_bss_4794.pos[player].z;
    lbl_1_bss_4794.count[player+2]--;
    if(lbl_1_bss_3700.board[player].held.rot >= 360.0f) {
        lbl_1_bss_3700.board[player].held.rot -= 360.0f;
    }
    if(lbl_1_bss_3700.board[player].held.rot < 0.0f) {
        lbl_1_bss_3700.board[player].held.rot += 360.0f;
    }
}

/*
 * asm 2236-2466, 275 insns. The board cell under the cursor: the whole-cell
 * grid (5x7, index x+y*5) or, halfF, the grid offset half a cell (4x6, index
 * x+y*4); -1 off the board.
 */
int fn_1_462C(int player, int halfF)
{
    float pos;
    int x;
    int y;

    if(halfF == 0) {
        if(lbl_1_bss_3700.board[player].cursor.x < -800.0f+(1100.0f*player)) {
            return -1;
        }
        if(lbl_1_bss_3700.board[player].cursor.x > -300.0f+(1100.0f*player)) {
            return -1;
        }
        if(lbl_1_bss_3700.board[player].cursor.y < -400.0f) {
            return -1;
        }
        if(lbl_1_bss_3700.board[player].cursor.y > 300.0f) {
            return -1;
        }
        pos = -700.0f+(1100.0f*player);
        for(x=0; x<4; x++, pos+=100.0f) {
            if(lbl_1_bss_3700.board[player].cursor.x < pos) {
                break;
            }
        }
        pos = 200.0f;
        for(y=0; y<6; y++, pos-=100.0f) {
            if(lbl_1_bss_3700.board[player].cursor.y > pos) {
                break;
            }
        }
    } else {
        if(lbl_1_bss_3700.board[player].cursor.x < -780.0f+(1100.0f*player)) {
            return -1;
        }
        if(lbl_1_bss_3700.board[player].cursor.x > -320.0f+(1100.0f*player)) {
            return -1;
        }
        if(lbl_1_bss_3700.board[player].cursor.y < -390.0f) {
            return -1;
        }
        if(lbl_1_bss_3700.board[player].cursor.y > 290.0f) {
            return -1;
        }
        pos = -650.0f+(1100.0f*player);
        for(x=0; x<3; x++, pos+=100.0f) {
            if(lbl_1_bss_3700.board[player].cursor.x < pos) {
                break;
            }
        }
        pos = 150.0f;
        for(y=0; y<5; y++, pos-=100.0f) {
            if(lbl_1_bss_3700.board[player].cursor.y > pos) {
                break;
            }
        }
        return x+(y*4);
    }
    return x+(y*5);
}

/*
 * asm 2467-2587, 118 insns. Where a piece size cells long along an axis (0
 * across, 1 down) starts when centred on a cell: odd sizes on the whole-cell
 * grid, even on the half grid; -1 if it would leave the board. Inlined into
 * fn_1_4E94.
 */
int fn_1_4A78(int axis, int cell, int size)
{
    int result = -1;
    int maxTbl[2] = { 4, 6 };
    int min;
    int max;

    if(size%2 != 0) {
        if(axis != 0) {
            min = (cell/5)-(size/2);
            max = (cell/5)+(size/2);
        } else {
            min = (cell%5)-(size/2);
            max = (cell%5)+(size/2);
        }
    } else {
        if(cell < 0) {
            return result;
        }
        if(axis != 0) {
            min = ((cell/4)-(size/2))+1;
            max = (cell/4)+(size/2);
        } else {
            min = ((cell%4)-(size/2))+1;
            max = (cell%4)+(size/2);
        }
    }
    if(min >= 0 && maxTbl[axis] >= max) {
        result = min;
    }
    return result;
}

/* asm 2588-2677, 85 insns. Blink the held piece while it cannot be dropped (blinkF). */
void fn_1_4C50(int player)
{
    M552_BOARD *board = &lbl_1_bss_3700.board[player];
    int i;
    int mode;

    if(board->blinkF != board->blinkPrevF) {
        board->blinkPrevF = board->blinkF;
        board->blinkTimer = 3;
        if(board->blinkF == 1) {
            fn_1_8644(player, 0);
            mode = 3;
        } else {
            fn_1_8644(player, 1);
            mode = 1;
        }
        for(i=0; i<25; i++) {
            if(lbl_1_bss_3700.board[player].held.cell[i] != 0) {
                lbl_1_bss_1340[lbl_1_bss_3700.board[player].held.slot[i]].mode = mode;
            }
        }
    } else if(board->blinkF == 1) {
        board->blinkTimer++;
        if(board->blinkTimer >= 6) {
            board->blinkTimer = 0;
            board->blinkOn ^= 1;
            fn_1_8644(player, board->blinkOn);
        }
    }
}

/* asm 2678-2734, 60 insns. Over the bin while turning: blink. */
void fn_1_4DA4(int player)
{
    int unused = 0;
    M552_BOARD *board = &lbl_1_bss_3700.board[player];

    if(board->cursor.x < (player*1200)-800 || board->cursor.x > (player*1200)-400) {
        return;
    }
    if(board->cursor.y < -625.0f || board->cursor.y > -425.0f) {
        return;
    }
    lbl_1_bss_3700.board[player].blinkF = 1;
}

/*
 * asm 2735-3314, 592 insns. Can the held piece go where the cursor is? If it
 * fits on empty cells, blink; on A, start the drop (count[player] 5) toward
 * that place and return 1.
 */
int fn_1_4E94(int player)
{
    int result;
    int cell[2];
    int w;
    int h;
    int x;
    int y;
    int i;
    int j;

    result = 0;
    lbl_1_bss_3700.board[player].blinkF = 0;
    if((cell[0] = fn_1_462C(player, 0)) < 0) {
        return result;
    }
    cell[1] = fn_1_462C(player, 1);
    if(0.0f == lbl_1_bss_3700.board[player].held.rot || 180.0f == lbl_1_bss_3700.board[player].held.rot) {
        w = lbl_1_data_410[lbl_1_bss_3700.board[player].held.kind*2];
        h = lbl_1_data_410[(lbl_1_bss_3700.board[player].held.kind*2)+1];
    } else {
        w = lbl_1_data_410[(lbl_1_bss_3700.board[player].held.kind*2)+1];
        h = lbl_1_data_410[lbl_1_bss_3700.board[player].held.kind*2];
    }
    if(w%2 != 0) {
        if((x = fn_1_4A78(0, cell[0], w)) == -1) {
            return result;
        }
    } else {
        if((x = fn_1_4A78(0, cell[1], w)) == -1) {
            return result;
        }
    }
    if(h%2 != 0) {
        if((y = fn_1_4A78(1, cell[0], h)) == -1) {
            return result;
        }
    } else {
        if((y = fn_1_4A78(1, cell[1], h)) == -1) {
            return result;
        }
    }
    for(i=0; i<h; i++) {
        for(j=0; j<w; j++) {
            if(lbl_1_bss_3700.board[player].grid[(x+j)+((y+i)*5)] != 0) {
                return result;
            }
        }
    }
    j = x+(w/2);
    i = y+(h/2);
    if(w%2 != 0) {
        lbl_1_bss_4794.pos[player].x = (((player*1100)-750)+(j*100))-lbl_1_bss_3700.board[player].cursor.x;
    } else {
        lbl_1_bss_4794.pos[player].x = (((player*1100)-800)+(j*100))-lbl_1_bss_3700.board[player].cursor.x;
    }
    if(h%2 != 0) {
        lbl_1_bss_4794.pos[player].y = (250-(i*100))-lbl_1_bss_3700.board[player].cursor.y;
    } else {
        lbl_1_bss_4794.pos[player].y = (300-(i*100))-lbl_1_bss_3700.board[player].cursor.y;
    }
    lbl_1_bss_4794.count[player] = 5;
    lbl_1_bss_3700.board[player].dropCell[0] = cell[0];
    lbl_1_bss_3700.board[player].dropCell[1] = cell[1];
    result = 1;
    lbl_1_bss_3700.board[player].blinkF = 1;
    if(!(lbl_1_bss_4794.chr[player].btnDown & PAD_BUTTON_A)) {
        result = 0;
        return result;
    }
    return result;
}

/*
 * asm 3315-3451, 152 insns. The drop: over 5 frames onto the board; then place
 * the cells, free the held piece, and score 100 less the time it was held.
 */
int fn_1_57D4(int player)
{
    M552_BOARD *board = &lbl_1_bss_3700.board[player];
    int penalty;

    board->cursor.x += lbl_1_bss_4794.pos[player].x/5.0f;
    board->cursor.y += lbl_1_bss_4794.pos[player].y/5.0f;
    board->held.x = board->cursor.x;
    board->held.y = board->cursor.y;
    if(player == 0) {
        board->held.z -= 24.0f;
    } else {
        board->held.z -= 23.65f;
    }
    lbl_1_bss_4794.count[player]--;
    Hu3DMotionTimeSet((lbl_1_bss_4794.models+12)[player].modelId, ((5-lbl_1_bss_4794.count[player])*10)+50);
    if(lbl_1_bss_4794.count[player] == 0) {
        fn_1_879C(player, 1);
        Hu3DMotionTimeSet((lbl_1_bss_4794.models+12)[player].modelId, 0.0f);
        penalty = (board->timer*25)/60;
        if(penalty > 100) {
            penalty = 100;
        }
        board->scoreTarget += 100-penalty;
        fn_1_5EBC(player);
        memset(&board->held, 0, sizeof(M552_PIECE));
        return 1;
    }
    if(lbl_1_bss_4794.count[player] == 4) {
        if(player != 0) {
            HuAudFXPlay(2157);
        } else {
            HuAudFXPlay(2156);
        }
    }
    return 0;
}

/*
 * asm 3452-3741, 290 insns. A full board: light every cell's flash model, then
 * clear one colour at a time (four passes), scoring each through a popup.
 */
int fn_1_5A34(int player)
{
    M552_BOARD *board = &lbl_1_bss_3700.board[player];
    int i;
    M552_SLOT *slot;

    switch(board->mode) {
        case 0:
            board->mode++;
            board->timer = 0;
            board->idx = 0;
            break;

        case 1:
            i = player+((board->grid[board->idx]-1)*2);
            lbl_1_bss_710[board->idx+(player*35)].mode = 1;
            lbl_1_bss_710[board->idx+(player*35)].modelId = Hu3DModelLink(lbl_1_bss_1200[i].modelId);
            Hu3DModelAttrSet(lbl_1_bss_710[board->idx+(player*35)].modelId, HU3D_ATTR_DISPOFF);
            Hu3DModelCameraSet(lbl_1_bss_710[board->idx+(player*35)].modelId, HU3D_CAM0);
            lbl_1_bss_710[board->idx+(player*35)].pos.x = lbl_1_bss_1340[board->gridSlot[board->idx]].pos.x;
            lbl_1_bss_710[board->idx+(player*35)].pos.y = lbl_1_bss_1340[board->gridSlot[board->idx]].pos.y;
            lbl_1_bss_710[board->idx+(player*35)].pos.z = lbl_1_bss_1340[board->gridSlot[board->idx]].pos.z;
            board->idx++;
            if(board->idx == 35) {
                board->mode++;
                board->timer = 20;
                board->idx = 0;
                fn_1_7800(player, 1);
                CharFXPlayPan(lbl_1_bss_4794.chr[player].charNo, 504, (player*32)+48);
            }
            break;

        case 2:
            if(board->timer++ > 20) {
                board->mode++;
            }
            break;

        case 3:
            if(player != 0) {
                HuAudFXPlay(2165);
            } else {
                HuAudFXPlay(2164);
            }
            for(i=0; i<35; i++) {
                if(board->grid[i] == board->idx+1) {
                    slot = &lbl_1_bss_1340[board->gridSlot[i]];
                    slot->mode = 0;
                    Hu3DModelAttrSet(slot->modelId, HU3D_ATTR_DISPOFF);
                    slot->unk08 = 0;
                    slot->timer = 0;
                    board->grid[i] = 0;
                    Hu3DModelAttrReset(lbl_1_bss_710[i+(player*35)].modelId, HU3D_ATTR_DISPOFF);
                    lbl_1_bss_710[i+(player*35)].mode = 2;
                    lbl_1_bss_710[i+(player*35)].timer = 0;
                }
            }
            i = fn_1_6758(player, board->idx);
            fn_1_6B58(player, board->idx, i);
            board->scoreTarget += i;
            if(i != 0) {
                omVibrate(lbl_1_bss_4794.chr[player].no, 15, 12, 0);
            }
            board->idx++;
            if(board->idx > 3) {
                board->mode = 0;
                board->timer = 0;
                board->idx = 0;
                fn_1_7800(player, 0);
                return 1;
            }
            if(i != 0) {
                board->timer = 0;
            } else {
                board->timer = 20;
            }
            board->mode--;
            break;
    }
    return 0;
}

/*
 * asm 3742-4013, 313 insns. Put the dropped piece's cells on the board with
 * block models from the queue colours, turning the cell mask first.
 */
void fn_1_5EBC(int player)
{
    float time;
    M552_BOARD *board;
    int cell[2];
    int w;
    int h;
    int x0;
    int y0;
    int y;
    int x;
    M552_SLOT *slot;

    time = -1.0f;
    board = &lbl_1_bss_3700.board[player];
    if(0.0f != board->held.rot) {
        fn_1_63A0(player);
    }
    cell[0] = board->dropCell[0];
    cell[1] = board->dropCell[1];
    if(0.0f == board->held.rot || 180.0f == board->held.rot) {
        w = lbl_1_data_410[board->held.kind*2];
        h = lbl_1_data_410[(board->held.kind*2)+1];
    } else {
        w = lbl_1_data_410[(board->held.kind*2)+1];
        h = lbl_1_data_410[board->held.kind*2];
    }
    if(w%2 != 0) {
        x0 = (cell[0]%5)-2;
    } else {
        x0 = (cell[1]%4)-2;
    }
    if(h%2 != 0) {
        y0 = (cell[0]/5)-2;
    } else {
        y0 = (cell[1]/4)-1;
    }
    for(y=0; y<5; y++) {
        if(y+y0 < 0) {
            continue;
        }
        for(x=0; x<5; x++) {
            if(x+x0 < 0) {
                continue;
            }
            if(board->held.cell[x+(y*5)] == 0) {
                continue;
            }
            if(time < 0.0f) {
                time = Hu3DMotionTimeGet(board->held.slot[x+(y*5)]);
            }
            board->grid[(x+x0)+((y+y0)*5)] = board->held.cell[x+(y*5)];
            board->gridSlot[(x+x0)+((y+y0)*5)] = fn_1_8D4C(board->held.cell[x+(y*5)], 0, time);
            slot = &lbl_1_bss_1340[board->gridSlot[(x+x0)+((y+y0)*5)]];
            Hu3DModelPosSet(slot->modelId, 50.0f+(((1100.0f*player)+(100.0f*(x+x0)))-800.0f), 250.0f-(100.0f*(y+y0)), 0.0f);
            slot->pos.x = 50.0f+(((1100.0f*player)+(100.0f*(x+x0)))-800.0f);
            slot->pos.y = 250.0f-(100.0f*(y+y0));
            slot->pos.z = 0.0f;
        }
    }
}

/* asm 4014-4203, 172 insns. Turn the held piece's cell mask to its rot and pull it into the 5x5 corner. */
void fn_1_63A0(int player)
{
    s8 cells[25];
    int y;
    int x;
    int src;
    int firstX;
    int maxX;
    int firstY;
    int maxY;

    for(y=0; y<5; y++) {
        for(x=0; x<5; x++) {
            if(90.0f == lbl_1_bss_3700.board[player].held.rot) {
                src = (5-(y+1))+(x*5);
            }
            if(270.0f == lbl_1_bss_3700.board[player].held.rot) {
                src = y+(20-(x*5));
            }
            if(180.0f == lbl_1_bss_3700.board[player].held.rot) {
                src = 24-(x+(y*5));
            }
            cells[x+(y*5)] = lbl_1_bss_3700.board[player].held.cell[src];
        }
    }
    firstX = firstY = -1;
    maxX = maxY = 0;
    for(y=0; y<5; y++) {
        for(x=0; x<5; x++) {
            if(cells[x+(y*5)] > 0) {
                if(firstX == -1) {
                    firstX = x;
                }
                if(firstY == -1) {
                    firstY = y;
                }
                if(maxX < x) {
                    maxX = x;
                }
                if(maxY < y) {
                    maxY = y;
                }
            }
        }
    }
    if(2-firstX > maxX-2) {
        for(y=0; y<5; y++) {
            for(x=0; x<4; x++) {
                cells[((y*5)+4)-x] = cells[((y*5)+3)-x];
            }
            cells[y*5] = 0;
        }
    }
    if(2-firstY < maxY-2) {
        for(y=0; y<4; y++) {
            for(x=0; x<5; x++) {
                cells[x+(y*5)] = cells[x+((y+1)*5)];
            }
        }
        for(x=0; x<5; x++) {
            cells[x+20] = 0;
        }
    }
    memcpy(lbl_1_bss_3700.board[player].held.cell, cells, 25);
}

/* asm 4204-4276, 66 insns. Count each colour's cells (line[]); 1 once all 35 are filled. */
int fn_1_6650(int player)
{
    int num;
    int x;
    int y;

    num = 0;
    for(x=0; x<4; x++) {
        lbl_1_bss_3700.board[player].line[x] = 0;
    }
    for(y=0; y<7; y++) {
        for(x=0; x<5; x++) {
            if(lbl_1_bss_3700.board[player].grid[x+(y*5)] != 0) {
                lbl_1_bss_3700.board[player].line[lbl_1_bss_3700.board[player].grid[x+(y*5)]-1]++;
                num++;
            }
        }
    }
    if(num == 35) {
        return 1;
    } else {
        return 0;
    }
}

/* asm 4277-4336, 55 insns. A colour's clear score: 100 a cell, plus a bonus for the biggest colour. */
int fn_1_6758(int player, int color)
{
    int max;
    M552_BOARD *board;
    int i;

    max = 0;
    board = &lbl_1_bss_3700.board[player];
    for(i=0; i<4; i++) {
        if(board->line[i] > max) {
            max = board->line[i];
        }
    }
    if(max == board->line[color]) {
        i = (board->line[color]*100)+((board->line[color]*10000)/35);
    } else {
        i = board->line[color]*100;
    }
    return i;
}

float lbl_1_data_3F4 = 5.0f;        /* the cursor models' depth offset */

/* asm 4337-4395, 59 insns. The cursor's three models follow it; the held piece's cells follow too. */
void fn_1_6834(int player)
{
    M552_BOARD *board = &lbl_1_bss_3700.board[player];
    M552_MODEL *mdl = &(lbl_1_bss_4794.models+12)[player];
    int i;

    for(i=0; i<3; mdl++, mdl++, i++) {
        mdl->pos.x = board->cursor.x;
        mdl->pos.y = board->cursor.y;
        if(player == 0) {
            mdl->pos.z = board->cursor.z+lbl_1_data_3F4;
        } else {
            mdl->pos.z = board->cursor.z-lbl_1_data_3F4;
        }
    }
    if(board->held.activeF != 0) {
        fn_1_8F2C(player, 1);
    }
}

/* asm 4396-4540, 142 insns. Count both scores up to their targets on the six-digit counters; how many are there. */
int fn_1_6920(void)
{
    int digit[6];
    int doneNum;
    int player;
    M552_BOARD *board;
    int i;
    int div;

    for(doneNum=0, player=0; player<2; player++) {
        board = &lbl_1_bss_3700.board[player];
        if(board->score < board->scoreTarget) {
            if(board->score < board->scoreTarget-100) {
                if(board->score < board->scoreTarget-1000) {
                    board->score += 333;
                } else {
                    board->score += 33;
                }
            } else {
                board->score += 3;
            }
            if(board->score > board->scoreTarget) {
                board->score = board->scoreTarget;
            }
            for(i=0, div=100000; i<6; i++, div/=10) {
                digit[i] = (board->score%(div*10))/div;
            }
            for(i=0, div=0; i<6; i++) {
                div += digit[i];
                if(div != 0 || i == 5) {
                    Hu3DTexScrollPosSet(lbl_1_bss_36E2[player][5-i], lbl_1_data_360[digit[i]*2], lbl_1_data_360[(digit[i]*2)+1], 0.0f);
                } else {
                    Hu3DTexScrollPosSet(lbl_1_bss_36E2[player][5-i], lbl_1_data_360[20], lbl_1_data_360[21], 0.0f);
                }
            }
        } else {
            doneNum++;
        }
    }
    return doneNum;
}

/* asm 4541-4699, 162 insns. Show a colour clear's score as a popup of up to five digits. */
void fn_1_6B58(int player, int no, int value)
{
    int digit[5];
    M552_POPUP *popup = &lbl_1_bss_3700.board[player].popup[no];
    int i;
    int div;

    if(popup->activeF == 0 || value != 0) {
        popup->activeF = 1;
        popup->value = value;
        popup->unk14 = 0;
        popup->timer = 0;
        popup->mode = 0;
        popup->x = 40+((no%2)*40)+(player*320);
        popup->y = (no*48)+228;
        for(i=0, div=10000; i<5; i++, div/=10) {
            digit[i] = (popup->value%(div*10))/div;
        }
        for(i=0, div=0; i<5; i++) {
            div += digit[i];
            if(div != 0) {
                popup->spr[i] = digit[i]+((no*50)+(i*10));
                espPosSet(lbl_1_bss_33C2[player][popup->spr[i]], popup->x+(i*32), popup->y);
                espDispOn(lbl_1_bss_33C2[player][popup->spr[i]]);
                espTPLvlSet(lbl_1_bss_33C2[player][popup->spr[i]], 0.0f);
            } else {
                popup->spr[i] = -1;
            }
        }
    }
}

/* asm 4700-4904, 213 insns. The popups rise, fade in, hold and fade out; how many are live. */
int fn_1_6DE0(void)
{
    float tpLvl;
    int num;
    int player;
    int no;
    M552_POPUP *popup;
    int i;

    for(num=0, player=0; player<2; player++) {
        for(no=0; no<4; no++) {
            popup = &lbl_1_bss_3700.board[player].popup[no];
            tpLvl = 1.0f;
            if(popup->activeF == 0) {
                continue;
            }
            num++;
            switch(popup->mode) {
                case 0:
                    popup->timer++;
                    tpLvl = popup->timer;
                    tpLvl *= 0.125f;
                    popup->y -= 1.5;
                    if(popup->timer == 8) {
                        popup->mode++;
                        popup->timer = 0;
                    }
                    break;

                case 1:
                    popup->timer++;
                    popup->y -= 1.5;
                    if(popup->timer == 32) {
                        popup->mode++;
                        popup->timer = 0;
                    }
                    break;

                case 2:
                    popup->timer++;
                    popup->y -= 1.5;
                    tpLvl = 16-popup->timer;
                    tpLvl *= 0.0625f;
                    if(popup->timer == 16) {
                        popup->mode++;
                        popup->timer = 0;
                    }
                    break;

                case 3:
                    tpLvl = 0.0f;
                    popup->activeF = 0;
                    for(i=0; i<5; i++) {
                        espDispOff(lbl_1_bss_33C2[player][popup->spr[i]]);
                        popup->spr[i] = -1;
                    }
                    espDispOn(lbl_1_bss_33C0);
                    break;
            }
            for(i=0; i<5; i++) {
                if(popup->spr[i] >= 0) {
                    espPosSet(lbl_1_bss_33C2[player][popup->spr[i]], popup->x+(i*32), popup->y);
                    espTPLvlSet(lbl_1_bss_33C2[player][popup->spr[i]], tpLvl);
                }
            }
        }
    }
    return num;
}

/*
 * asm 4905-5066, 179 insns. Over the bin: blink; on A, carry the held piece
 * to the bin (count[player] 15), turning a long piece to lie flat first.
 */
int fn_1_7134(int player)
{
    int result;
    M552_BOARD *board;

    result = 0;
    board = &lbl_1_bss_3700.board[player];
    if(board->cursor.x < (player*1200)-800 || board->cursor.x > (player*1200)-400) {
        return result;
    }
    if(board->cursor.y < -625.0f || board->cursor.y > -425.0f) {
        return result;
    }
    result = 1;
    lbl_1_bss_3700.board[player].blinkF = 1;
    if(!(lbl_1_bss_4794.chr[player].btnDown & PAD_BUTTON_A)) {
        return 0;
    }
    lbl_1_bss_4794.pos[player].x = ((player*1200)-600)-board->cursor.x;
    lbl_1_bss_4794.pos[player].y = -525.0f-board->cursor.y;
    lbl_1_bss_4794.count[player] = 15;
    if(board->held.kind >= 2 && board->held.kind != 4) {
        if(0.0f == board->held.rot || 180.0f == board->held.rot) {
            fn_1_4450(player, player);
        }
    }
    return result;
}

/* asm 5067-5148, 93 insns. The carry to the bin over 15 frames; then open the bin. */
int fn_1_7400(int player)
{
    M552_BOARD *board = &lbl_1_bss_3700.board[player];

    board->cursor.x += lbl_1_bss_4794.pos[player].x/15.0f;
    board->cursor.y += lbl_1_bss_4794.pos[player].y/15.0f;
    board->held.x = board->cursor.x;
    board->held.y = board->cursor.y;
    lbl_1_bss_4794.count[player]--;
    if(lbl_1_bss_4794.count[player] == 0) {
        Hu3DMotionTimeSet((lbl_1_bss_4794.models+10)[player].modelId, 0.0f);
        Hu3DMotionSpeedSet((lbl_1_bss_4794.models+10)[player].modelId, 5.0f);
        board->timer = 0;
        board->mode = 0;
        if(player != 0) {
            HuAudFXPlay(2161);
        } else {
            HuAudFXPlay(2160);
        }
        return 1;
    }
    return 0;
}

/* asm 5149-5290, 163 insns. Throw the held piece in the bin and close it; 1 when done. */
int fn_1_7574(int player)
{
    M552_BOARD *board = &lbl_1_bss_3700.board[player];

    switch(board->mode) {
        case 0:
            if(board->timer++ <= 5) {
                Hu3DMotionTimeSet((lbl_1_bss_4794.models+12)[player].modelId, (board->timer*10)+50);
            }
            if(board->timer >= 10) {
                Hu3DMotionTimeSet((lbl_1_bss_4794.models+10)[player].modelId, 50.0f);
                Hu3DMotionSpeedSet((lbl_1_bss_4794.models+10)[player].modelId, 0.0f);
                board->timer = 0;
                board->mode++;
                Hu3DMotionTimeSet((lbl_1_bss_4794.models+12)[player].modelId, 0.0f);
            }
            break;

        case 1:
            board->held.z -= 50.0f;
            if(board->timer++ >= 10) {
                Hu3DMotionSpeedSet((lbl_1_bss_4794.models+10)[player].modelId, 5.0f);
                board->timer = 0;
                board->mode++;
                if(player != 0) {
                    HuAudFXPlay(2163);
                } else {
                    HuAudFXPlay(2162);
                }
            }
            break;

        case 2:
            if(board->timer++ >= 10) {
                Hu3DMotionTimeSet((lbl_1_bss_4794.models+10)[player].modelId, 0.0f);
                Hu3DMotionSpeedSet((lbl_1_bss_4794.models+10)[player].modelId, 0.0f);
                board->timer = 0;
                board->mode = 0;
                fn_1_879C(player, 1);
                memset(&board->held, 0, sizeof(M552_PIECE));
                return 1;
            }
            break;
    }
    return 0;
}

/* Each face's texture offset: 0 normal, 1 happy, 2 sad. */
float lbl_1_data_3F8[6] = { 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f };

/* asm 5291-5321, 34 insns. Set a duellist's face. */
void fn_1_7800(int player, int face)
{
    Hu3DTexScrollPosSet(lbl_1_bss_36E2[player][6], lbl_1_data_3F8[face*2], lbl_1_data_3F8[(face*2)+1], 0.0f);
}

