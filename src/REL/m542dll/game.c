/*
 * m542dll/game.c -- the duel itself: the main and pre-winner sub-states, the
 * two clocks, the duellists' jumps, the COM and the spark emitters. Written
 * from the reference assembly, functions in reference order; line ranges are
 * into build/mp5-asm/m542dll/asm/REL/m542dll/game.s. See NOTES.md for the
 * per-function result.
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
#include "game/gamemes.h"
#include "game/flag.h"

#include "datadir_enum.h"

#include "REL/m542dll/m542.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"
#include "dolphin/gx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

void fn_1_2FD8(s32 no, s32 value);
void fn_1_3178(void);
void fn_1_328C(void);
void fn_1_3700(void);
void fn_1_37B0(s32 player);
void fn_1_39E0(void);
void fn_1_4008(s32 player);
void fn_1_4994(void);
s32 fn_1_4B50(s32 player);
void fn_1_4D48(s32 player);
void fn_1_771C(s32 group);
void fn_1_7778(s32 group);
void fn_1_77EC(void);
void fn_1_7848(s32 group);
void fn_1_7E90(s32 group);
s32 fn_1_800C(s32 group);
void fn_1_8180(s32 group);
s32 fn_1_835C(s32 group);

/* --- .data --- */

s32 lbl_1_data_330 = -1;
s32 lbl_1_data_334[2] = { -1, -1 };

/*
 * Texture-cell offsets for the counter board (fn_1_2FD8, fn_1_3178, fn_1_328C), cell 10 blank.
 * The unreferenced zero float after it shares the symbol: CodeWarrior would put a separate
 * zero-initialised global in .bss.
 */
struct {
    float cell[14][2];
    float unused;
} lbl_1_data_33C = {
    {
        { 0.0f, 0.0f },
        { 0.0f, 0.25f },
        { 0.0f, 0.5f },
        { 0.0f, 0.75f },
        { 0.25f, 0.0f },
        { 0.25f, 0.25f },
        { 0.25f, 0.5f },
        { 0.25f, 0.75f },
        { 0.5f, 0.0f },
        { 0.5f, 0.25f },
        { 0.5f, 0.5f },
        { 0.0f, 0.0f },
        { 0.25f, 0.0f },
        { 0.75f, 0.75f }
    },
    0.0f
};

HuVecF lbl_1_data_3B0[6] = {
    { 0.0f, -100.0f, 0.0f },
    { 0.0f, -100.0f, 0.0f },
    { 0.0f, -100.0f, 0.0f },
    { 0.0f, -100.0f, 0.0f },
    { 0.0f, -100.0f, 0.0f },
    { 0.0f, -100.0f, 0.0f }
};

/* --- .bss --- */

M542_PARTICLE lbl_1_bss_E8[4][30];
M542_MODEL lbl_1_bss_1588[M542_MODEL_MAX];
s16 lbl_1_bss_1940[2][5];
M542_WORK lbl_1_bss_1954;
M542_EMITTER lbl_1_bss_1AA8[4];
s16 lbl_1_bss_1B28[8];              /* [0] is a GameMes id */

/* asm 9-83, 72 insns. Main sub-state 0: once the wipe ends, reset both counters, start the props and the music. */
void fn_1_2858(void)
{
    if(!WipeCheckEnd()) {
        fn_1_3178();
        Hu3DMotionSpeedSet(lbl_1_bss_1954.models[7].modelId, 2.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_1954.models[8].modelId, 2.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_1954.models[9].modelId, 2.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_1954.models[10].modelId, 2.0f);
        HuAudFXPlay(2069);
        HuAudFXPlay(2070);
        lbl_1_data_330 = HuAudBGMPlay(62);
        lbl_1_bss_1954.mode[0]++;
        lbl_1_bss_1954.mode[1] = 0;
        CharModelVoicePanSet(lbl_1_bss_1954.chr[0].charNo, 48);
        CharModelVoicePanSet(lbl_1_bss_1954.chr[1].charNo, 80);
    }
}

/* asm 86-127, 39 insns. */
void fn_1_2978(void)
{
    if(lbl_1_bss_1954.mode[1]++ >= 45) {
        lbl_1_bss_1954.mode[0]++;
        lbl_1_bss_1954.mode[1] = 0;
        Hu3DMotionSpeedSet(lbl_1_bss_1954.models[15].modelId, 1.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_1954.models[16].modelId, 1.0f);
    }
}

/* asm 130-180, 47 insns. */
void fn_1_2A14(void)
{
    lbl_1_bss_1954.mode[1]++;
    if(lbl_1_bss_1954.mode[1] >= 10) {
        Hu3DMotionSpeedSet(lbl_1_bss_1954.models[15].modelId, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_1954.models[16].modelId, 0.0f);
    }
    if(lbl_1_bss_1954.mode[1] >= 20) {
        omCameraViewMoveSimple(lbl_1_bss_78, 60);
        lbl_1_bss_1954.mode[0]++;
    }
}

/* asm 183-252, 67 insns. */
void fn_1_2AD0(void)
{
    if(omCameraViewCheck(1)) {
        lbl_1_bss_1954.mode[0] = 0;
        MgSeqModeNext();
        fn_1_3178();
        lbl_1_bss_1954.sparkDelay[0] = ((rand8()%3)*30)+((rand8()%60)+60);
        lbl_1_bss_1954.sparkDelay[1] = ((rand8()%3)*30)+((rand8()%60)+60);
    }
}

/* asm 255-374, 116 insns. Start sub-state 0: the clocks start. */
void fn_1_2BDC(void)
{
    int i;

    for(i=0; i<2; i++) {
        Hu3DMotionTimeSet(lbl_1_bss_1954.models[i+7].modelId, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_1954.models[i+7].modelId, 2.0f);
        Hu3DMotionTimeSet(lbl_1_bss_1954.models[i+9].modelId, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_1954.models[i+9].modelId, 2.0f);
        lbl_1_bss_1954.alarmTimer[i] = 0;
        lbl_1_bss_1954.alarmTime[i] = 10.0f;
        lbl_1_bss_1954.wobble[i][0] = (rand8()%2)*180;
        lbl_1_bss_1954.wobble[i][1] = (rand8()%2)*180;
        Hu3DMotionSpeedSet(lbl_1_bss_1954.models[(i*5)+21].modelId, 1.0f);
        fn_1_771C(-1);
    }
    HuAudFXPlay(2069);
    HuAudFXPlay(2070);
    lbl_1_bss_1954.mode[0]++;
    lbl_1_bss_4 = 1;
}

/* asm 377-506, 121 insns. Main sub-state 1: the duel, until both clocks are stopped. */
void fn_1_2DAC(void)
{
    int i;
    int side;

    for(i=0; i<2; i++) {
        if(lbl_1_bss_1954.chr[i].dif != 0) {
            fn_1_4D48(i);
        }
        fn_1_4008(i);
        if(lbl_1_bss_1954.mode[i+2] == 0) {
            if(lbl_1_bss_1954.sparkDelay[i]-- <= 0) {
                side = rand8()%2;
                fn_1_7778(side+(i*2));
                if(rand8()%3 != 0) {
                    fn_1_7778((side^1)+(i*2));
                }
                lbl_1_bss_1954.sparkDelay[i] = ((rand8()%3)*15)+66;
                if(i == 0) {
                    HuAudFXPlay(2067);
                } else {
                    HuAudFXPlay(2068);
                }
            }
        }
    }
    if(lbl_1_bss_1954.mode[2] != 0 && lbl_1_bss_1954.mode[3] != 0) {
        lbl_1_bss_1954.mode[0]++;
        MgSeqModeNext();
        HuAudSStreamFadeOut(lbl_1_data_330, 1000);
        lbl_1_bss_4 = 0;
    }
    fn_1_39E0();
    lbl_1_bss_C++;
}

/* asm 509-528, 18 insns. Main sub-state 2 (the sequence's time-up). */
void fn_1_2F90(void)
{
    lbl_1_bss_1954.mode[0] = 0;
    MgSeqModeNext();
    HuAudSStreamFadeOut(lbl_1_data_330, 100);
    fn_1_39E0();
}

/* asm 531-642, 104 insns. Show a four-digit value on duellist `no`'s counter board; 9999 shows the blank cell. */
void fn_1_2FD8(s32 no, s32 value)
{
    int i;
    s32 digit[4];

    if(value != 9999) {
        digit[0] = value/1000;
        digit[1] = (value%1000)/100;
        digit[2] = (value%100)/10;
        digit[3] = value%10;
    } else {
        for(i=0; i<4; i++) {
            digit[i] = 10;
        }
    }
    for(i=0; i<4; i++) {
        Hu3DTexScrollPosSet(lbl_1_bss_1940[no][i], lbl_1_data_33C.cell[digit[i]][0], lbl_1_data_33C.cell[digit[i]][1], 0.0f);
    }
}

/* asm 645-719, 69 insns. Reset both clocks to 1000. */
void fn_1_3178(void)
{
    int i;

    for(i=0; i<2; i++) {
        fn_1_2FD8(i, 1000);
        lbl_1_bss_1954.mode[i+2] = 0;
        lbl_1_bss_1954.clock[i] = 0;
    }
}

/* asm 722-1030, 285 insns. Run both clocks: 600 frames count the board down from 1000; past that the clock stops itself. */
void fn_1_328C(void)
{
    int i;

    for(i=0; i<2; i++) {
        if(lbl_1_bss_1954.mode[i+2] == 0) {
            lbl_1_bss_1954.clock[i]++;
            if(lbl_1_bss_1954.clock[i] > 600) {
                lbl_1_bss_1954.clock[i] = 601;
                lbl_1_bss_1954.mode[i+2] = 1;
                if(i == 0) {
                    HuAudFXPlay(2062);
                } else {
                    HuAudFXPlay(2063);
                }
                Hu3DMotionSpeedSet(lbl_1_bss_1954.models[(i*5)+21].modelId, 0.0f);
                Hu3DMotionTimeSet(lbl_1_bss_1954.models[(i*5)+21].modelId, 30.0f);
            }
        }
    }
    for(i=0; i<2; i++) {
        if(lbl_1_bss_1954.clock[i] == 600) {
            fn_1_2FD8(i, 1);
        } else if(lbl_1_bss_1954.clock[i] < 600) {
            fn_1_2FD8(i, 1000-((lbl_1_bss_1954.clock[i]*1000)/600));
        } else {
            fn_1_2FD8(i, 9999);
        }
    }
}

/* asm 1033-1082, 44 insns. */
void fn_1_3700(void)
{
    int i;
    M542_MODEL *player;
    M542_MODEL *shadow;

    for(i=0; i<2; i++) {
        player = &lbl_1_bss_1954.models[i+32];
        shadow = &lbl_1_bss_1954.models[i+11];
        if(player->pos.y >= 170.0f) {
            shadow->pos.y = 0.0f;
        } else {
            shadow->pos.y = player->pos.y-170.0f;
        }
    }
}

/* asm 1085-1226, 140 insns. Wobble duellist `player`'s board. Retail quirk kept: the z tilt reads the x angle. */
void fn_1_37B0(s32 player)
{
    lbl_1_bss_1954.wobble[player][0] = (lbl_1_bss_1954.wobble[player][0]+((rand8()%10)+2))%360;
    lbl_1_bss_1954.models[player+15].rot.x = 2.0*sin((M_PI*lbl_1_bss_1954.wobble[player][0])/180.0);
    lbl_1_bss_1954.wobble[player][1] = (lbl_1_bss_1954.wobble[player][1]+((rand8()%10)+2))%360;
    lbl_1_bss_1954.models[player+15].rot.z = 2.0*sin((M_PI*lbl_1_bss_1954.wobble[player][0])/180.0);
}

/* asm 1229-1634, 394 insns. The per-frame arena update while the clocks run. */
void fn_1_39E0(void)
{
    int i;

    fn_1_3700();
    fn_1_328C();
    fn_1_37B0(0);
    fn_1_37B0(1);
    fn_1_77EC();
    for(i=0; i<2; i++) {
        if(lbl_1_bss_1954.alarmTimer[i]++ >= 50) {
            lbl_1_bss_1954.alarmTimer[i] = 0;
            if(lbl_1_bss_1954.mode[i+2] == 0) {
                Hu3DMotionTimeSet(lbl_1_bss_1954.models[i+7].modelId, 0.0f);
                Hu3DMotionTimeSet(lbl_1_bss_1954.models[i+9].modelId, 0.0f);
                if(i == 0) {
                    HuAudFXPlay(2069);
                } else {
                    HuAudFXPlay(2070);
                }
            }
        }
        if((lbl_1_bss_1954.mode[i+2] == 0) | (lbl_1_bss_1954.clock[i] < 600)) {
            lbl_1_bss_1954.alarmTime[i] += 0.1;
            if(lbl_1_bss_1954.alarmTime[i] > 85.0f) {
                lbl_1_bss_1954.alarmTime[i] = 85.0f;
            }
            Hu3DMotionTimeSet(lbl_1_bss_1954.models[i+15].modelId, lbl_1_bss_1954.alarmTime[i]);
        }
    }
}

/* asm 1637-2267, 611 insns. Duellist `player`'s jump: A jumps (held, higher), A or L in the air dives; landing the dive stops the clock. Case 4 falls into 5 as in retail. */
void fn_1_4008(s32 player)
{
    M542_MODEL *model = &lbl_1_bss_1954.models[player+32];

    switch(lbl_1_bss_1954.jump[player][0]) {
        case 0:
            if(lbl_1_bss_1954.mode[player+2] == 0 && (lbl_1_bss_1954.chr[player].btnDown & PAD_BUTTON_A)) {
                lbl_1_bss_1954.jump[player][0] = 1;
                lbl_1_bss_1954.jump[player][1] = 0;
                Hu3DMotionShiftSet(model->modelId, lbl_1_bss_1954.motId[player][1], 0.0f, 2.0f, 0);
                lbl_1_bss_1954.jumpSpeed[player].x = 25.0f;
            }
            break;

        case 1:
            lbl_1_bss_1954.jump[player][1]++;
            model->pos.y += lbl_1_bss_1954.jumpSpeed[player].x;
            lbl_1_bss_1954.jumpSpeed[player].x *= 0.85;
            if(lbl_1_bss_1954.jumpSpeed[player].x < 1.0f) {
                lbl_1_bss_1954.jumpSpeed[player].x = 1.0f;
            }
            if(!((s32)lbl_1_bss_1954.chr[player].btn & PAD_BUTTON_A) && lbl_1_bss_1954.jump[player][1] > 4) {
                lbl_1_bss_1954.jump[player][0] = 2;
                lbl_1_bss_1954.jumpSpeed[player].x *= 0.5f;
            }
            if(lbl_1_bss_1954.jump[player][1] > 16) {
                lbl_1_bss_1954.jump[player][0] = 2;
                lbl_1_bss_1954.jumpSpeed[player].x *= 0.5f;
            }
            if(lbl_1_bss_1954.jump[player][1] > 3 && lbl_1_bss_1954.mode[player+2] == 0 && ((lbl_1_bss_1954.chr[player].btnDown & PAD_BUTTON_A) || (lbl_1_bss_1954.chr[player].btnDown & PAD_TRIGGER_L))) {
                lbl_1_bss_1954.jump[player][0] = 3;
                Hu3DMotionShiftSet(model->modelId, lbl_1_bss_1954.motId[player][3], 0.0f, 8.0f, 0);
                lbl_1_bss_1954.jump[player][1] = 0;
                lbl_1_bss_1954.jumpSpeed[player].x *= 0.5f;
            }
            break;

        case 2:
            model->pos.y -= lbl_1_bss_1954.jumpSpeed[player].x;
            lbl_1_bss_1954.jumpSpeed[player].x *= 1.1764705f;
            if(lbl_1_bss_1954.jumpSpeed[player].x > 30.0f) {
                lbl_1_bss_1954.jumpSpeed[player].x = 30.0f;
            }
            if(model->pos.y <= 170.0f) {
                model->pos.y = 170.0f;
                lbl_1_bss_1954.jump[player][0] = 0;
                Hu3DMotionShiftSet(model->modelId, lbl_1_bss_1954.motId[player][0], 0.0f, 5.0f, 0);
                lbl_1_bss_1954.jumpSpeed[player].x = 25.0f;
                lbl_1_bss_1954.jump[player][1] = 0;
                CharModelLandDustCreate(lbl_1_bss_1954.chr[player].charNo, &model->pos);
            } else if(lbl_1_bss_1954.mode[player+2] == 0 && ((lbl_1_bss_1954.chr[player].btnDown & PAD_BUTTON_A) || (lbl_1_bss_1954.chr[player].btnDown & PAD_TRIGGER_L))) {
                lbl_1_bss_1954.jump[player][0] = 3;
                Hu3DMotionShiftSet(model->modelId, lbl_1_bss_1954.motId[player][3], 0.0f, 8.0f, 0);
                lbl_1_bss_1954.jump[player][1] = 0;
                lbl_1_bss_1954.jumpSpeed[player].x *= 0.5f;
            }
            break;

        case 3:
            if(lbl_1_bss_1954.jump[player][1]++ > 15) {
                model->pos.y -= lbl_1_bss_1954.jumpSpeed[player].x;
                lbl_1_bss_1954.jumpSpeed[player].x *= 1.1764705f;
                if(lbl_1_bss_1954.jumpSpeed[player].x > 45.0f) {
                    lbl_1_bss_1954.jumpSpeed[player].x = 45.0f;
                }
                if(model->pos.y <= 150.0f) {
                    model->pos.y = 150.0f;
                    if(lbl_1_bss_1954.mode[player+2] == 0) {
                        if(player == 0) {
                            HuAudFXPlay(2060);
                        } else {
                            HuAudFXPlay(2061);
                        }
                    }
                    Hu3DMotionShiftSet(model->modelId, lbl_1_bss_1954.motId[player][5], 0.0f, 4.0f, 0);
                    lbl_1_bss_1954.mode[player+2] = 1;
                    Hu3DMotionSpeedSet(lbl_1_bss_1954.models[(player*5)+21].modelId, 0.0f);
                    Hu3DMotionTimeSet(lbl_1_bss_1954.models[(player*5)+21].modelId, 30.0f);
                    lbl_1_bss_1954.jump[player][0] = 4;
                    lbl_1_bss_1954.jump[player][1] = 0;
                    omVibrate(lbl_1_bss_1954.chr[player].no, 20, 4, 2);
                }
            }
            break;

        case 4:
            if(lbl_1_bss_1954.jump[player][1]++ > 15) {
                Hu3DMotionShiftSet(model->modelId, lbl_1_bss_1954.motId[player][4], 0.0f, 4.0f, 0);
                lbl_1_bss_1954.jump[player][0] = 5;
                lbl_1_bss_1954.jump[player][1] = 0;
            }
        case 5:
            if(lbl_1_bss_1954.jump[player][1]++ > 30) {
                Hu3DMotionShiftSet(model->modelId, lbl_1_bss_1954.motId[player][0], 0.0f, 2.0f, HU3D_MOTATTR_LOOP);
                lbl_1_bss_1954.jump[player][0] = 6;
            }
            break;
    }
}

/* asm 2270-2386, 111 insns. COM setup: the clock value each difficulty aims to stop at, less some noise. */
void fn_1_4994(void)
{
    s32 stopTbl[4] = { 438, 504, 528, 540 };
    int i;

    for(i=0; i<2; i++) {
        memset(&lbl_1_bss_14[i], 0, sizeof(M542_COM));
        lbl_1_bss_14[i].dif = lbl_1_bss_1954.chr[i].dif-1;
        lbl_1_bss_14[i].stopClock = stopTbl[lbl_1_bss_14[i].dif];
        if(lbl_1_bss_14[i].dif == 3) {
            lbl_1_bss_14[i].stopClock -= rand8()%3;
        } else {
            lbl_1_bss_14[i].stopClock -= rand8()%18;
        }
        lbl_1_bss_14[i].hopDelay = (rand8()%120)+120;
    }
}

/* asm 2389-2518, 126 insns. COM: whether to jump now. At the target it plans a jump with a dive; well before it, an idle hop now and then. */
s32 fn_1_4B50(s32 player)
{
    s32 result = 0;

    if(lbl_1_bss_1954.clock[player] >= lbl_1_bss_14[player].stopClock) {
        lbl_1_bss_14[player].holdTime = 15-(rand8()%6);
        lbl_1_bss_14[player].diveTime = lbl_1_bss_14[player].holdTime+((rand8()%3)+5);
        result = 1;
    } else if(lbl_1_bss_1954.clock[player] < lbl_1_bss_14[player].stopClock-45) {
        lbl_1_bss_14[player].hopDelay--;
        if(lbl_1_bss_14[player].hopDelay <= 0) {
            lbl_1_bss_14[player].holdTime = (rand8()%6)+10;
            lbl_1_bss_14[player].diveTime = 0;
            lbl_1_bss_14[player].hopDelay = (rand8()%60)+60;
            result = 1;
        }
    }
    return result;
}

/* asm 2521-2776, 246 insns. COM pad: press and hold A for unkC frames, then press it again at unk10 to dive. */
void fn_1_4D48(s32 player)
{
    switch(lbl_1_bss_14[player].mode) {
        case 0:
            if(fn_1_4B50(player)) {
                lbl_1_bss_14[player].timer = 0;
                lbl_1_bss_14[player].mode++;
                lbl_1_bss_1954.chr[player].btnDown = PAD_BUTTON_A;
                lbl_1_bss_1954.chr[player].btn = PAD_BUTTON_A;
            }
            break;

        case 1:
            lbl_1_bss_1954.chr[player].btn = PAD_BUTTON_A;
            lbl_1_bss_14[player].timer++;
            if(lbl_1_bss_14[player].timer >= lbl_1_bss_14[player].holdTime) {
                if(lbl_1_bss_14[player].diveTime != 0) {
                    lbl_1_bss_14[player].mode++;
                } else {
                    lbl_1_bss_14[player].mode = 0;
                }
            }
            break;

        case 2:
            lbl_1_bss_14[player].timer++;
            if(lbl_1_bss_14[player].timer == lbl_1_bss_14[player].diveTime) {
                lbl_1_bss_1954.chr[player].btnDown = PAD_BUTTON_A;
                lbl_1_bss_14[player].mode++;
            }
            break;
    }
}

/* asm 2779-2978, 192 insns. Finish: let both jumps settle. */
void fn_1_5120(void)
{
    int i;

    for(i=0; i<2; i++) {
        fn_1_4008(i);
        fn_1_37B0(i);
        fn_1_3700();
    }
    lbl_1_bss_1954.mode[0] = 0;
    fn_1_77EC();
}

/* asm 2981-3578, 580 insns. Pre-winner sub-state 0: once both jumps settle, judge. Nearest 600 without passing it wins (mode[1]); the loser's clock alarm rings. Equal clocks go to sub-state 2. */
void fn_1_5420(void)
{
    int i;
    int settled;

    for(i=0, settled=0; i<2; i++) {
        fn_1_4008(i);
        if(lbl_1_bss_1954.jump[i][0] == 0) {
            settled++;
        }
        if(lbl_1_bss_1954.jump[i][0] == 6) {
            settled++;
        }
    }
    if(settled == 2) {
        if(lbl_1_bss_1954.clock[0] == lbl_1_bss_1954.clock[1]) {
            lbl_1_bss_1954.mode[0] = 2;
            lbl_1_bss_1954.mode[1] = 0;
            if(lbl_1_bss_1954.clock[0] > 600) {
                lbl_1_bss_1954.mode[1] = 1;
            }
            for(i=0; i<2; i++) {
                lbl_1_bss_1954.alarmTimer[i] = 0;
                Hu3DMotionTimeSet(lbl_1_bss_1954.models[i+7].modelId, 0.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_1954.models[i+7].modelId, 3.0f);
                Hu3DMotionTimeSet(lbl_1_bss_1954.models[i+9].modelId, 0.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_1954.models[i+9].modelId, 3.0f);
                lbl_1_bss_1954.mode[i+2] = 0;
                Hu3DMotionSpeedSet(lbl_1_bss_1954.models[(i*5)+21].modelId, 2.0f);
                Hu3DMotionShiftSet(lbl_1_bss_1954.models[i+32].modelId, lbl_1_bss_1954.motId[i][8], 0.0f, 10.0f, 0);
            }
            HuAudFXPlay(2069);
            HuAudFXPlay(2070);
            lbl_1_data_334[0] = HuAudFXPlay(2071);
            lbl_1_data_334[1] = HuAudFXPlay(2072);
            HuAudFXPlay(29);
        } else {
            lbl_1_bss_1954.mode[0] = 1;
            if(lbl_1_bss_1954.clock[0] > lbl_1_bss_1954.clock[1]) {
                if(lbl_1_bss_1954.clock[0] > 600) {
                    lbl_1_bss_1954.mode[1] = 1;
                } else {
                    lbl_1_bss_1954.mode[1] = 0;
                }
            } else {
                if(lbl_1_bss_1954.clock[1] > 600) {
                    lbl_1_bss_1954.mode[1] = 0;
                } else {
                    lbl_1_bss_1954.mode[1] = 1;
                }
            }
            lbl_1_bss_1954.alarmTimer[(lbl_1_bss_1954.mode[1]^1)] = 0;
            Hu3DMotionTimeSet(lbl_1_bss_1954.models[(lbl_1_bss_1954.mode[1]^1)+7].modelId, 0.0f);
            Hu3DMotionSpeedSet(lbl_1_bss_1954.models[(lbl_1_bss_1954.mode[1]^1)+7].modelId, 3.0f);
            Hu3DMotionTimeSet(lbl_1_bss_1954.models[(lbl_1_bss_1954.mode[1]^1)+9].modelId, 0.0f);
            Hu3DMotionSpeedSet(lbl_1_bss_1954.models[(lbl_1_bss_1954.mode[1]^1)+9].modelId, 3.0f);
            if(lbl_1_bss_1954.mode[1] == 0) {
                HuAudFXPlay(2070);
                lbl_1_data_334[1] = HuAudFXPlay(2072);
            } else {
                HuAudFXPlay(2069);
                lbl_1_data_334[0] = HuAudFXPlay(2071);
            }
            HuAudFXPlay(29);
            lbl_1_bss_1954.mode[(lbl_1_bss_1954.mode[1]^1)+2] = 0;
            Hu3DMotionSpeedSet(lbl_1_bss_1954.models[((lbl_1_bss_1954.mode[1]^1)*5)+21].modelId, 2.0f);
            Hu3DMotionShiftSet(lbl_1_bss_1954.models[(lbl_1_bss_1954.mode[1]^1)+32].modelId, lbl_1_bss_1954.motId[(lbl_1_bss_1954.mode[1]^1)][8], 0.0f, 10.0f, 0);
        }
        lbl_1_bss_1954.winMode = 0;
    }
    fn_1_37B0(0);
    fn_1_37B0(1);
}

/* asm 3581-4425, 832 insns. Pre-winner sub-state 1: the loser's alarm bursts and blasts them off; the camera finds the winner, who gets ten coins unless practising. Retail quirks kept: the loser's board wobbles twice a frame and the clocks run twice. */
void fn_1_5D30(void)
{
    int loser = lbl_1_bss_1954.mode[1]^1;
    s32 playerNo;

    if(lbl_1_bss_1954.alarmTimer[loser]++ >= 33) {
        lbl_1_bss_1954.alarmTimer[loser] = 0;
        Hu3DMotionTimeSet(lbl_1_bss_1954.models[loser+7].modelId, 0.0f);
        Hu3DMotionTimeSet(lbl_1_bss_1954.models[loser+9].modelId, 0.0f);
        if(lbl_1_bss_1954.winMode < 1) {
            if(loser == 0) {
                HuAudFXPlay(2069);
            } else {
                HuAudFXPlay(2070);
            }
        }
    }
    switch(lbl_1_bss_1954.winMode) {
        case 0:
            lbl_1_bss_1954.alarmTime[loser] += 0.2;
            Hu3DMotionTimeSet(lbl_1_bss_1954.models[loser+15].modelId, lbl_1_bss_1954.alarmTime[loser]);
            if(lbl_1_bss_1954.alarmTime[loser] > 99.0f) {
                lbl_1_bss_1954.alarmTime[loser] = 99.0f;
                lbl_1_bss_1954.winMode++;
                Hu3DMotionShiftSet(lbl_1_bss_1954.models[loser+32].modelId, lbl_1_bss_1954.motId[loser][7], 0.0f, 4.0f, 0);
                omVibrate(lbl_1_bss_1954.chr[loser].no, 80, 12, 0);
                Hu3DModelAttrSet(lbl_1_bss_1954.models[loser+15].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_1954.models[loser+27].modelId, HU3D_ATTR_DISPOFF);
                Hu3DMotionTimeSet(lbl_1_bss_1954.models[loser+27].modelId, 0.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_1954.models[loser+27].modelId, 4.0f);
                Hu3DModelAttrReset(lbl_1_bss_1954.models[loser+27].modelId, HU3D_MOTATTR_LOOP);
                Hu3DModelAttrSet(lbl_1_bss_1954.models[loser+15].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_1954.models[loser+30].modelId, HU3D_ATTR_DISPOFF);
                Hu3DMotionTimeSet(lbl_1_bss_1954.models[loser+30].modelId, 0.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_1954.models[loser+30].modelId, 4.0f);
                HuAudFXPlay(30);
                if(loser == 0) {
                    HuAudFXStop(lbl_1_data_334[0]);
                    HuAudFXPlay(2064);
                } else {
                    HuAudFXStop(lbl_1_data_334[1]);
                    HuAudFXPlay(2065);
                }
                fn_1_7778(loser+4);
            }
            break;

        case 1:
            lbl_1_bss_1954.models[loser+32].pos.z += 30.0f;
            lbl_1_bss_1954.models[loser+32].pos.y += 6.0;
            lbl_1_bss_1954.models[loser+32].pos.x += 6-(loser*12);
            if(lbl_1_bss_1954.models[loser+32].pos.z >= 2000.0f) {
                lbl_1_bss_1954.winMode++;
                lbl_1_bss_78[0].center.x = (lbl_1_bss_1954.mode[1]*420)-210;
                lbl_1_bss_78[0].center.z = 254.0f;
                lbl_1_bss_78[0].rot.x = -5.0f;
                lbl_1_bss_78[0].zoom = 600.0f;
                omCameraViewMoveSimple(lbl_1_bss_78, 60);
            }
            break;

        case 2:
            if(omCameraViewCheck(1)) {
                CharModelVoicePanSet(lbl_1_bss_1954.chr[0].charNo, 64);
                CharModelVoicePanSet(lbl_1_bss_1954.chr[1].charNo, 64);
                lbl_1_bss_1B28[0] = GameMesCreate(4, 3, lbl_1_bss_1954.chr[lbl_1_bss_1954.mode[1]].charNo, -1, -1, -1);
                Hu3DMotionShiftSet(lbl_1_bss_1954.models[lbl_1_bss_1954.mode[1]+32].modelId, lbl_1_bss_1954.motId[lbl_1_bss_1954.mode[1]][6], 0.0f, 8.0f, 0);
                playerNo = lbl_1_bss_1954.chr[lbl_1_bss_1954.mode[1]].no;
                if(!_CheckFlag(FLAG_MG_PRACTICE)) {
                    GwPlayer[playerNo].mgCoinBonus = 10;
                }
                HuAudJinglePlay(121);
                lbl_1_bss_1954.winMode++;
                lbl_1_bss_1954.mesTimer = 0;
            }
            break;

        case 3:
            lbl_1_bss_1954.mesTimer++;
            if(!GameMesStatGet(lbl_1_bss_1B28[0]) && lbl_1_bss_1954.mesTimer >= 210) {
                GameMesKill(lbl_1_bss_1B28[0]);
                MgSeqModeNext();
            }
            break;
    }
    fn_1_37B0(0);
    fn_1_37B0(1);
    fn_1_37B0(lbl_1_bss_1954.mode[1]^1);
    fn_1_328C();
    fn_1_328C();
    fn_1_77EC();
}

/* asm 4428-5043, 595 insns. Pre-winner sub-state 2, a draw: both alarms burst, both duellists are blasted off, DRAW. Retail quirk kept: the boards wobble four times a frame. */
void fn_1_6A30(void)
{
    int i;
    int burst;

    for(i=0; i<2; i++) {
        if(lbl_1_bss_1954.alarmTimer[i]++ >= 33) {
            lbl_1_bss_1954.alarmTimer[i] = 0;
            Hu3DMotionTimeSet(lbl_1_bss_1954.models[i+7].modelId, 0.0f);
            Hu3DMotionTimeSet(lbl_1_bss_1954.models[i+9].modelId, 0.0f);
            if(lbl_1_bss_1954.winMode < 1) {
                if(i == 0) {
                    HuAudFXPlay(2069);
                } else {
                    HuAudFXPlay(2070);
                }
            }
        }
    }
    switch(lbl_1_bss_1954.winMode) {
        case 0:
            for(i=0, burst=0; i<2; i++) {
                lbl_1_bss_1954.alarmTime[i] += 0.2;
                if(lbl_1_bss_1954.alarmTime[i] > 99.0f) {
                    lbl_1_bss_1954.alarmTime[i] = 99.0f;
                    burst++;
                }
                Hu3DMotionTimeSet(lbl_1_bss_1954.models[i+15].modelId, lbl_1_bss_1954.alarmTime[i]);
            }
            if(burst == 2) {
                lbl_1_bss_1954.winMode++;
                for(i=0; i<2; i++) {
                    Hu3DMotionShiftSet(lbl_1_bss_1954.models[i+32].modelId, lbl_1_bss_1954.motId[i][7], 0.0f, 8.0f, 0);
                    omVibrate(lbl_1_bss_1954.chr[i].no, 80, 12, 0);
                    Hu3DModelAttrSet(lbl_1_bss_1954.models[i+15].modelId, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(lbl_1_bss_1954.models[i+27].modelId, HU3D_ATTR_DISPOFF);
                    Hu3DMotionTimeSet(lbl_1_bss_1954.models[i+27].modelId, 0.0f);
                    Hu3DMotionSpeedSet(lbl_1_bss_1954.models[i+27].modelId, 4.0f);
                    Hu3DModelAttrReset(lbl_1_bss_1954.models[i+27].modelId, HU3D_MOTATTR_LOOP);
                    Hu3DModelAttrReset(lbl_1_bss_1954.models[i+30].modelId, HU3D_ATTR_DISPOFF);
                    Hu3DMotionTimeSet(lbl_1_bss_1954.models[i+30].modelId, 0.0f);
                    Hu3DMotionSpeedSet(lbl_1_bss_1954.models[i+30].modelId, 4.0f);
                    fn_1_7778(i+4);
                }
                HuAudFXPlay(30);
                HuAudFXStop(lbl_1_data_334[0]);
                HuAudFXStop(lbl_1_data_334[1]);
                HuAudFXPlay(2064);
                HuAudFXPlay(2065);
            }
            break;

        case 1:
            for(i=0; i<2; i++) {
                lbl_1_bss_1954.models[i+32].pos.z += 30.0f;
                lbl_1_bss_1954.models[i+32].pos.y += 6.0;
                lbl_1_bss_1954.models[i+32].pos.x += 6-(i*12);
            }
            if(lbl_1_bss_1954.models[32].pos.z >= 2000.0f) {
                lbl_1_bss_1954.winMode++;
            }
            break;

        case 2:
            lbl_1_bss_1B28[0] = GameMesCreate(2, 2);
            HuAudJinglePlay(123);
            lbl_1_bss_1954.winMode++;
            lbl_1_bss_1954.mesTimer = 0;
            break;

        case 3:
            lbl_1_bss_1954.mesTimer++;
            if(!GameMesStatGet(lbl_1_bss_1B28[0]) && lbl_1_bss_1954.mesTimer >= 210) {
                GameMesKill(lbl_1_bss_1B28[0]);
                MgSeqModeNext();
            }
            break;
    }
    for(i=0; i<2; i++) {
        fn_1_37B0(0);
        fn_1_37B0(1);
    }
    fn_1_328C();
    fn_1_328C();
    fn_1_77EC();
}

/* asm 5046-5279, 232 insns. */
void fn_1_737C(void)
{
    fn_1_77EC();
    fn_1_37B0(0);
    fn_1_37B0(1);
}

/* asm 5282-5308, 23 insns. Stop an emitter, or all four for -1. Retail quirk: the loop indexes by `group`, so -1 (its only use) writes bss_1AA8[-1].mode, which on the DOL is work+0x138 (unk128[1].y, never read); the host skips that store. */
void fn_1_771C(s32 group)
{
    s32 i = group;
    s32 end = i+1;

    if(i < 0) {
        i = 0;
        end = 4;
    }
    for(; i<end; i++) {
        lbl_1_bss_1AA8[group].mode = 0;
    }
}

/* asm 5311-5343, 29 insns. Start emitter `group`: 0-3 a stream of counter sparks, 4/5 the alarm burst over duellist 0/1 (emitter 0/1, mode 4/5). */
void fn_1_7778(s32 group)
{
    if(group < 4) {
        lbl_1_bss_1AA8[group].active = 1;
        lbl_1_bss_1AA8[group].mode = 0;
    } else {
        lbl_1_bss_1AA8[group-4].active = 1;
        lbl_1_bss_1AA8[group-4].mode = group;
    }
}

/* asm 5346-5373, 23 insns. */
void fn_1_77EC(void)
{
    int i;

    for(i=0; i<4; i++) {
        if(lbl_1_bss_1AA8[i].active) {
            fn_1_7848(i);
        }
    }
}

/* asm 5376-5794, 402 insns. One emitter's state: a 30-frame stream (spawn one spark a frame, then let them fly out), or the endless alarm burst. */
void fn_1_7848(s32 group)
{
    switch(lbl_1_bss_1AA8[group].mode) {
        case 0:
            lbl_1_bss_1AA8[group].timer = 0;
            lbl_1_bss_1AA8[group].next = 0;
            lbl_1_bss_1AA8[group].mode++;
            switch(group) {
                case 0:
                case 2:
                    lbl_1_bss_1AA8[group].pos.x = -400-((rand8()*16)%6);
                    lbl_1_bss_1AA8[group].pos.y = 170-(rand8()%40);
                    lbl_1_bss_1AA8[group].pos.z = 400.0f;
                    lbl_1_bss_1AA8[group].angle = 50-(rand8()%30);
                    break;

                case 1:
                case 3:
                    lbl_1_bss_1AA8[group].pos.x = -500-((rand8()*16)%6);
                    lbl_1_bss_1AA8[group].pos.y = (rand8()%20)+300;
                    lbl_1_bss_1AA8[group].pos.z = 200.0f;
                    lbl_1_bss_1AA8[group].angle = -(20-(rand8()%10));
                    break;
            }
            if(group >= 2) {
                lbl_1_bss_1AA8[group].pos.x = -lbl_1_bss_1AA8[group].pos.x;
                if(group == 2) {
                    lbl_1_bss_1AA8[group].angle = 180.0f-lbl_1_bss_1AA8[group].angle;
                } else {
                    lbl_1_bss_1AA8[group].angle = -180.0f-lbl_1_bss_1AA8[group].angle;
                }
            }
            break;

        case 1:
            lbl_1_bss_1AA8[group].timer++;
            if(lbl_1_bss_1AA8[group].timer >= 30) {
                lbl_1_bss_1AA8[group].mode++;
            } else {
                fn_1_7E90(group);
                fn_1_800C(group);
            }
            break;

        case 2:
            if(fn_1_800C(group) == 0) {
                lbl_1_bss_1AA8[group].mode++;
            }
            break;

        case 3:
            lbl_1_bss_1AA8[group].active = 0;
            break;

        case 4:
        case 5:
            lbl_1_bss_1AA8[group].timer = 0;
            lbl_1_bss_1AA8[group].next = 0;
            lbl_1_bss_1AA8[group].pos.x = ((lbl_1_bss_1AA8[group].mode-4)*580)-290;
            lbl_1_bss_1AA8[group].pos.y = 132.0f;
            lbl_1_bss_1AA8[group].pos.z = -128.0f;
            lbl_1_bss_1AA8[group].angle = 90.0f;
            lbl_1_bss_1AA8[group].mode = 6;
            break;

        case 6:
            lbl_1_bss_1AA8[group].timer++;
            if((lbl_1_bss_1AA8[group].timer%5) == 0) {
                fn_1_8180(group);
            }
            fn_1_835C(group);
            break;
    }
}

/* asm 5797-5893, 95 insns. Spawn the stream's next spark at the emitter. */
void fn_1_7E90(s32 group)
{
    M542_PARTICLE *part;

    part = &lbl_1_bss_E8[group][lbl_1_bss_1AA8[group].next];
    part->mode++;
    part->angle = ((rand8()%48)-24)/4;
    part->timer = 0;
    Hu3DModelAttrReset(part->modelId, HU3D_ATTR_DISPOFF);
    Hu3DMotionTimeSet(part->modelId, 0.0f);
    Hu3DMotionSpeedSet(part->modelId, 3.33f);
    Hu3DModelPosSetV(part->modelId, &lbl_1_bss_1AA8[group].pos);
    part->pos.x = lbl_1_bss_1AA8[group].pos.x;
    part->pos.y = lbl_1_bss_1AA8[group].pos.y;
    part->pos.z = lbl_1_bss_1AA8[group].pos.z;
    lbl_1_bss_1AA8[group].next++;
}

/* asm 5896-5995, 93 insns. Move group's sparks along the emitter's angle; returns how many were live. */
s32 fn_1_800C(s32 group)
{
    M542_PARTICLE *part;
    s32 i;
    s32 num;
    float speed;

    num = 0;
    speed = 13.5f;
    part = lbl_1_bss_E8[group];
    for(i=0; i<30; i++, part++) {
        if(part->mode != 0) {
            if(part->timer < 29) {
                part->pos.x += speed*cos((M_PI*(part->angle+lbl_1_bss_1AA8[group].angle))/180.0);
                part->pos.y += speed*sin((M_PI*(part->angle+lbl_1_bss_1AA8[group].angle))/180.0);
                part->timer++;
            } else {
                part->mode = 0;
                Hu3DModelAttrSet(part->modelId, HU3D_ATTR_DISPOFF);
            }
            num++;
        }
    }
    return num;
}

/* asm 5998-6118, 119 insns. Spawn a small burst spark, reusing the group's thirty slots in turn. */
void fn_1_8180(s32 group)
{
    M542_PARTICLE *part;

    part = &lbl_1_bss_E8[group][lbl_1_bss_1AA8[group].next];
    part->mode++;
    part->angle = ((rand8()%24)-12)/4;
    part->timer = 0;
    Hu3DModelAttrReset(part->modelId, HU3D_ATTR_DISPOFF);
    Hu3DMotionTimeSet(part->modelId, 0.0f);
    Hu3DMotionSpeedSet(part->modelId, 3.3f);
    Hu3DModelScaleSet(part->modelId, 0.3f, 0.3f, 1.0f);
    Hu3DModelPosSetV(part->modelId, &lbl_1_bss_1AA8[group].pos);
    part->pos.x = lbl_1_bss_1AA8[group].pos.x;
    part->pos.y = lbl_1_bss_1AA8[group].pos.y;
    part->pos.z = lbl_1_bss_1AA8[group].pos.z;
    lbl_1_bss_1AA8[group].next = (lbl_1_bss_1AA8[group].next+1)%30;
}

/* asm 6121-6220, 93 insns. Move the burst's sparks; the count is returned but unused. */
s32 fn_1_835C(s32 group)
{
    M542_PARTICLE *part;
    s32 i;
    s32 num;
    float speed;

    num = 0;
    speed = 4.0f;
    part = lbl_1_bss_E8[group];
    for(i=0; i<30; i++, part++) {
        if(part->mode != 0) {
            if(part->timer < 30) {
                part->pos.x += speed*cos((M_PI*(part->angle+lbl_1_bss_1AA8[group].angle))/180.0);
                part->pos.y += speed*sin((M_PI*(part->angle+lbl_1_bss_1AA8[group].angle))/180.0);
                part->timer++;
            } else {
                part->mode = 0;
                Hu3DModelAttrSet(part->modelId, HU3D_ATTR_DISPOFF);
            }
            num++;
        }
    }
    return num;
}
