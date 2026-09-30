/*
 * m548dll/game.c -- the duel itself: two duellists take turns spending
 * presses from a shared count of nine, and the one who has to take the last
 * press is launched off the stage. Written from the reference assembly,
 * functions in reference order; line ranges are into
 * build/mp5-asm/m548dll/asm/REL/m548dll/game.s.
 * No other built duel's game.c is related; this file is the overlay's own.
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
#include "game/mg/timer.h"
#include "game/gamemes.h"
#include "game/flag.h"
#include "game/printfunc.h"

#include "datadir_enum.h"

#include "REL/m548dll/m548.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

void fn_1_2148(void);
void fn_1_2894(void);
void fn_1_2908(void);
s32 fn_1_4658(s16 shakeF);
void fn_1_4AA0(OMOBJ *obj);
void fn_1_4FC4(HuVecF pos);
void fn_1_5098(OMOBJ *obj);

/* --- .data --- */

s32 lbl_1_data_398 = -1;            /* fn_1_934 and fn_1_3DCC */

/* Seventeen texture-scroll offsets (fn_1_23A4, fn_1_3DCC, fn_1_54C0, fn_1_59FC). */
float lbl_1_data_39C[17][2] = {
    { -0.75f, -0.125f },
    { -0.75f, 0.125f },
    { -0.75f, 0.375f },
    { -0.75f, 0.625f },
    { -0.5f, 0.0f },
    { -0.5f, 0.25f },
    { -0.5f, 0.5f },
    { -0.25f, -0.125f },
    { -0.25f, 0.0f },
    { -0.25f, 0.125f },
    { -0.25f, 0.25f },
    { -0.25f, 0.375f },
    { -0.25f, 0.5f },
    { -0.25f, 0.625f },
    { -0.25f, 0.75f },
    { 0.0f, -0.125f },
    { 0.0f, 0.0f }
};

float lbl_1_data_424[13] = {
    24.0f, 24.0f, 24.0f, 20.0f, 28.0f, 24.0f, 24.0f, 28.0f, 28.0f, 28.0f, 28.0f, 28.0f, 28.0f
};

HuVecF lbl_1_data_458[3] = {
    { 0.0f, 185.0f, 0.0f },
    { -85.0f, 185.0f, 0.0f },
    { 85.0f, 185.0f, 0.0f }
};

HuVecF lbl_1_data_47C[3] = {
    { -20.0f, 0.0f, 0.0f },
    { -20.0f, -21.0f, 0.0f },
    { -20.0f, 21.0f, 0.0f }
};

float lbl_1_data_4A0[3] = { 550.0f, 420.0f, 420.0f };

/*
 * .data:0x4AC "test11_tex_we-itemhook-r" is a literal in fn_1_309C; fn_1_5098's
 * four tables follow it, so they are defined just before that function.
 */

/* --- .bss --- */

float lbl_1_bss_5D8;
s32 lbl_1_bss_5DC[4];
u8 lbl_1_bss_5EC;
s32 lbl_1_bss_5F0[2];

/* asm 9-189, 170 insns. Object main: while a duellist plays motion 1 between frames 24 and 80, puff 6-7 cry effects at a rhythm. */
void fn_1_1D84(OMOBJ *obj)
{
    int i;
    int j;

    if(lbl_1_bss_3D0.unk4 == 9) {
        return;
    }
    for(i=0; i<2; i++) {
        if((i != 0 || lbl_1_bss_3D0.unk0 != 0) && lbl_1_bss_3F0.player[i].motNo == 1 && lbl_1_bss_3F0.player[i].time >= 24.0f && lbl_1_bss_3F0.player[i].time < 80.0f) {
            lbl_1_bss_0[i][1]++;
            if(lbl_1_bss_0[i][1] == lbl_1_bss_0[i][2]) {
                lbl_1_bss_0[i][1] = 0;
                for(j=0; j<lbl_1_bss_0[i][3]; j++) {
                    CharModelCryCreate(lbl_1_bss_3F0.chr[i].charNo, lbl_1_data_288[lbl_1_bss_3F0.chr[i].charNo][0], lbl_1_data_288[lbl_1_bss_3F0.chr[i].charNo][1]);
                }
                if(lbl_1_bss_0[i][0] != 0) {
                    lbl_1_bss_0[i][2] = (rand8()%10)+60;
                    lbl_1_bss_0[i][0] = 0;
                } else {
                    lbl_1_bss_0[i][2] = 10;
                    lbl_1_bss_0[i][0]++;
                }
                lbl_1_bss_0[i][3] = (rand8()%2)+6;
            }
        }
    }
}

/* asm 192-266, 71 insns. Push arena models 1-11's pos and rot at Hu3D; every hook calls it. */
void fn_1_202C(void)
{
    s16 i;

    for(i=1; i<12; i++) {
        Hu3DModelPosSet(lbl_1_bss_3F0.models[i].modelId, lbl_1_bss_3F0.models[i].pos.x, lbl_1_bss_3F0.models[i].pos.y, lbl_1_bss_3F0.models[i].pos.z);
        Hu3DModelRotSet(lbl_1_bss_3F0.models[i].modelId, lbl_1_bss_3F0.models[i].rot.x, lbl_1_bss_3F0.models[i].rot.y, lbl_1_bss_3F0.models[i].rot.z);
    }
}

/* asm 269-425, 151 insns. Reset the duel state and the three camera views. Inlined into fn_1_257C; no call of its own. */
void fn_1_2148(void)
{
    int i;

    lbl_1_bss_3D0.unk0 = 0;
    lbl_1_bss_3D0.unk2 = 0;
    lbl_1_bss_3D0.unk4 = 9;
    lbl_1_bss_3D0.unk6 = 0;
    lbl_1_bss_3D0.unk8 = 0;
    lbl_1_bss_3D0.unkA = 0;
    lbl_1_bss_3D0.unkC = 0;
    for(i=0; i<2; i++) {
        lbl_1_bss_3D0.unk10[i] = lbl_1_data_424[lbl_1_bss_3F0.chr[i].charNo]-8.0f;
        lbl_1_bss_3D0.unk18[i] = lbl_1_data_424[lbl_1_bss_3F0.chr[i].charNo]-8.0f;
    }
    for(i=0; i<3; i++) {
        lbl_1_bss_58[i].center.x = lbl_1_data_458[i].x;
        lbl_1_bss_58[i].center.y = lbl_1_data_458[i].y;
        lbl_1_bss_58[i].center.z = lbl_1_data_458[i].z;
        lbl_1_bss_58[i].rot.x = lbl_1_data_47C[i].x;
        lbl_1_bss_58[i].rot.y = lbl_1_data_47C[i].y;
        lbl_1_bss_58[i].rot.z = lbl_1_data_47C[i].z;
        lbl_1_bss_58[i].zoom = lbl_1_data_4A0[i];
    }
}

/* asm 428-550, 118 insns. Fade-in sub-state 0: roll the timer board's digit every fourth frame for two seconds, then settle it. */
void fn_1_23A4(void)
{
    u8 no;

    no = rand8()%10;
    if(lbl_1_bss_5EC == no) {
        no = (no+1)%10;
    }
    lbl_1_bss_5EC = no;
    no += 7;
    if((lbl_1_bss_3F0.unkB0++)%4 == 0) {
        Hu3DTexScrollPosSet(lbl_1_bss_3B4, lbl_1_data_39C[no][0], lbl_1_data_39C[no][1], 0.0f);
        HuAudFXPlay(2107);
    }
    if(!WipeCheckEnd() && lbl_1_bss_3F0.unkB0 > 120) {
        lbl_1_bss_3F0.unkB0 = 0;
        lbl_1_bss_3F0.mode[0]++;
        no = 6;
        Hu3DTexScrollPosSet(lbl_1_bss_3B4, lbl_1_data_39C[no][0], lbl_1_data_39C[no][1], 0.0f);
        HuAudFXPlay(2108);
        lbl_1_bss_5F0[0] = 0;
    }
}

/* asm 553-731, 172 insns. Fade-in sub-state 1. */
void fn_1_257C(void)
{
    if(fn_1_4658(0)) {
        fn_1_2148();
        lbl_1_bss_3F0.mode[0]++;
        lbl_1_bss_3F0.unkB0 = 0;
        omCameraViewMoveSimple(lbl_1_bss_58, 60);
    }
}

/* asm 734-762, 26 insns. Fade-in sub-state 2. */
void fn_1_282C(void)
{
    if(omCameraViewCheck(1)) {
        lbl_1_bss_3F0.mode[0]++;
        lbl_1_bss_3F0.mode[1] = 0;
        omCameraViewMoveSimple(&lbl_1_bss_58[1], 60);
        MgSeqModeNext();
    }
}

/* asm 765-795, 29 insns. The five-second press timer. Inlined into fn_1_2AD4. */
void fn_1_2894(void)
{
    lbl_1_bss_54 = MgTimerCreate(0);
    MgTimerParamSet(lbl_1_bss_54, 300, 0, 0);
    MgTimerPosSet(lbl_1_bss_54, 288.0f, 64.0f);
}

/* asm 798-919, 115 insns. A computer duellist's press: wait 30-149 frames, then press A or B (two to one). Inlined into fn_1_2AD4. */
void fn_1_2908(void)
{
    if(lbl_1_bss_5DC[0] == 0) {
        lbl_1_bss_5DC[2] = ((rand8()%4)*30)+((rand8()%30)+30);
        lbl_1_bss_5DC[0]++;
    } else if(lbl_1_bss_5DC[2]-- <= 0) {
        if(lbl_1_bss_3D0.unk2 != 0) {
            if(rand8()%3 != 0) {
                lbl_1_bss_3F0.chr[lbl_1_bss_3D0.unk6].btnDown = PAD_BUTTON_A;
            } else {
                lbl_1_bss_3F0.chr[lbl_1_bss_3D0.unk6].btnDown = PAD_BUTTON_B;
            }
        } else {
            if(rand8()%3 != 0) {
                lbl_1_bss_3F0.chr[lbl_1_bss_3D0.unk6].btnDown = PAD_BUTTON_B;
            } else {
                lbl_1_bss_3F0.chr[lbl_1_bss_3D0.unk6].btnDown = PAD_BUTTON_A;
            }
        }
    }
}

/* asm 922-1307, 370 insns. Main sub-states 0 and 2: the press. The duellist whose turn it is (bss_3D0.unk6) presses A to count down one, B for two, inside five seconds. */
void fn_1_2AD4(void)
{
    s16 count = lbl_1_bss_3D0.unk4;
    int modeTbl[4] = { 1, 3, 5, 6 };

    if(omCameraViewCheck(1)) {
        if(lbl_1_bss_3F0.mode[1] == 0) {
            fn_1_2894();
            MgTimerModeOnSet(lbl_1_bss_54, 1);
            lbl_1_bss_3F0.mode[1]++;
            lbl_1_bss_5DC[0] = 0;
        } else {
            if(lbl_1_bss_3F0.chr[lbl_1_bss_3D0.unk6].dif != 0) {
                fn_1_2908();
            }
            if(lbl_1_bss_3F0.chr[lbl_1_bss_3D0.unk6].btnDown & PAD_BUTTON_A) {
                lbl_1_bss_3D0.unk4 -= 1;
            } else if(lbl_1_bss_3F0.chr[lbl_1_bss_3D0.unk6].btnDown & PAD_BUTTON_B) {
                lbl_1_bss_3D0.unk4 -= 2;
            }
            if(count != lbl_1_bss_3D0.unk4) {
                lbl_1_bss_3F0.mode[1] = 0;
                MgTimerKill(lbl_1_bss_54);
                lbl_1_bss_54 = NULL;
                if(lbl_1_bss_3D0.unk4 > 0) {
                    lbl_1_bss_3D0.unkC = 0;
                    if(lbl_1_bss_3D0.unk2 != 0) {
                        lbl_1_bss_3F0.mode[0] = modeTbl[lbl_1_bss_3D0.unk6];
                        lbl_1_bss_3D0.unkA = 0;
                        lbl_1_bss_3D0.unk8 = 0;
                        if(lbl_1_bss_3F0.mode[2] > 3 && rand8()%2 != 0) {
                            lbl_1_bss_3F0.mode[0] = modeTbl[2];
                        } else {
                            HuAudFXPlay(2111);
                            if(fn_1_196C() != 0) {
                                lbl_1_bss_3F0.mode[0] = 7;
                            }
                        }
                    } else {
                        if(lbl_1_bss_3F0.mode[2] >= 2) {
                            lbl_1_bss_3D0.unk2 = 1;
                        }
                        HuAudFXPlay(2110);
                        lbl_1_bss_3D0.unk8 = count-lbl_1_bss_3D0.unk4;
                        lbl_1_bss_3D0.unkA = 0;
                        lbl_1_bss_3F0.mode[0] = modeTbl[3];
                        lbl_1_bss_3F0.mode[1] = 0;
                    }
                } else {
                    lbl_1_bss_3D0.unk4 = 0;
                    lbl_1_bss_3F0.mode[0] = 4;
                    lbl_1_bss_3D0.unkA = 0;
                    lbl_1_bss_3D0.unk8 = 0;
                }
            } else if(MgTimerDoneCheck(lbl_1_bss_54)) {
                lbl_1_bss_3D0.unk4 = 0;
                lbl_1_bss_3F0.mode[0] = 4;
                lbl_1_bss_3F0.mode[1] = 0;
                lbl_1_bss_3D0.unkA = 0;
                lbl_1_bss_3D0.unk8 = 0;
            }
        }
    }
}

/* asm 1310-2173, 844 insns. Main sub-states 1 and 3: the throw. The item leaves the thrower's hook (case 1), arcs over (2), drops into the catcher's hand over unk10 frames (3), and the catcher's motion carries it back (4) before the turn passes. */
void fn_1_309C(void)
{
    int modeTbl[2] = { 0, 2 };
    HuVecF pos;

    switch(lbl_1_bss_3F0.mode[1]) {
        case 0:
            fn_1_194C();
            lbl_1_bss_3F0.player[lbl_1_bss_3D0.unk6].speed = 1.0f;
            lbl_1_bss_3F0.player[lbl_1_bss_3D0.unk6].attrReset = HU3D_MOTATTR_LOOP;
            lbl_1_bss_3F0.mode[1]++;
            lbl_1_bss_3D0.unkC = 0;
            break;

        case 1:
            lbl_1_bss_3D0.unkC++;
            Hu3DModelObjPosGet(lbl_1_bss_3F0.models[lbl_1_bss_3D0.unk6+12].modelId, "test11_tex_we-itemhook-r", &pos);
            pos.y = pos.y-lbl_1_bss_384[lbl_1_bss_3D0.unk6][0].y;
            lbl_1_bss_44.y = pos.y+lbl_1_bss_384[lbl_1_bss_3D0.unk6][1].z;
            if(lbl_1_bss_3D0.unk6 != 0) {
                lbl_1_bss_44.x = pos.x+(lbl_1_bss_384[1][1].y-lbl_1_bss_384[1][0].x);
            } else {
                lbl_1_bss_44.x = pos.x+(-(lbl_1_bss_384[0][1].y-lbl_1_bss_384[0][0].x));
            }
            if(lbl_1_bss_3D0.unkC == 20) {
                lbl_1_bss_3F0.mode[1]++;
                lbl_1_bss_3D0.unkC = 0;
                lbl_1_bss_38.y = 300.0f-lbl_1_bss_44.y;
                lbl_1_bss_38.z = lbl_1_bss_44.y;
                lbl_1_bss_38.x = lbl_1_bss_44.x;
                omCameraViewMoveSimple(&lbl_1_bss_58[(lbl_1_bss_3D0.unk6^1)+1], 24);
                HuAudFXPanning(HuAudFXPlay(2114), 80-(lbl_1_bss_3D0.unk6*32));
            }
            break;

        case 2:
            lbl_1_bss_3D0.unkC++;
            if(lbl_1_bss_3D0.unkC == 4) {
                lbl_1_bss_3F0.player[(lbl_1_bss_3D0.unk6^1)].motNo = 1;
                lbl_1_bss_3F0.player[(lbl_1_bss_3D0.unk6^1)].time = 1.0f;
                lbl_1_bss_3F0.player[(lbl_1_bss_3D0.unk6^1)].speed = 1.0f;
            }
            lbl_1_bss_44.x = lbl_1_bss_44.x-(lbl_1_bss_38.x/12.0f);
            lbl_1_bss_44.y = lbl_1_bss_38.z+(lbl_1_bss_38.y*sin((M_PI*((lbl_1_bss_3D0.unkC*90)/12))/180.0));
            if(lbl_1_bss_3D0.unkC == 12) {
                lbl_1_bss_3F0.mode[1]++;
                lbl_1_bss_44.x = 0.0f;
                lbl_1_bss_44.y = 300.0f;
                lbl_1_bss_3D0.unkC = 0;
                lbl_1_bss_38.x = lbl_1_bss_384[(lbl_1_bss_3D0.unk6^1)][0].z+(lbl_1_bss_384[(lbl_1_bss_3D0.unk6^1)][1].y-lbl_1_bss_384[(lbl_1_bss_3D0.unk6^1)][0].x);
                lbl_1_bss_38.y = (300.0f-lbl_1_bss_384[(lbl_1_bss_3D0.unk6^1)][1].x)-(lbl_1_bss_384[(lbl_1_bss_3D0.unk6^1)][1].z-lbl_1_bss_384[(lbl_1_bss_3D0.unk6^1)][0].y);
            }
            break;

        case 3:
            lbl_1_bss_3D0.unkC++;
            if(lbl_1_bss_3D0.unk6 != 0) {
                lbl_1_bss_44.x = lbl_1_bss_44.x-(lbl_1_bss_38.x/lbl_1_bss_3D0.unk10[(lbl_1_bss_3D0.unk6^1)]);
            } else {
                lbl_1_bss_44.x = lbl_1_bss_44.x+(lbl_1_bss_38.x/lbl_1_bss_3D0.unk10[(lbl_1_bss_3D0.unk6^1)]);
            }
            lbl_1_bss_44.y = (lbl_1_bss_384[(lbl_1_bss_3D0.unk6^1)][1].z-lbl_1_bss_384[(lbl_1_bss_3D0.unk6^1)][0].y)+(lbl_1_bss_384[(lbl_1_bss_3D0.unk6^1)][1].x+(lbl_1_bss_38.y*sin((M_PI*(90.0f+((lbl_1_bss_3D0.unkC*90)/lbl_1_bss_3D0.unk10[(lbl_1_bss_3D0.unk6^1)])))/180.0)));
            if(lbl_1_bss_3D0.unkC == lbl_1_bss_3D0.unk18[(lbl_1_bss_3D0.unk6^1)]) {
                lbl_1_bss_3D0.unkC = 0;
                lbl_1_bss_3F0.mode[1]++;
                if(lbl_1_bss_3D0.unk6 != 0) {
                    lbl_1_bss_44.x = -lbl_1_bss_38.x;
                } else {
                    lbl_1_bss_44.x = lbl_1_bss_38.x;
                }
                lbl_1_bss_44.y = lbl_1_bss_384[(lbl_1_bss_3D0.unk6^1)][1].x+(lbl_1_bss_384[(lbl_1_bss_3D0.unk6^1)][1].z-lbl_1_bss_384[(lbl_1_bss_3D0.unk6^1)][0].y);
                HuAudFXPlay(2113);
            }
            break;

        case 4:
            lbl_1_bss_3D0.unkC++;
            Hu3DModelObjPosGet(lbl_1_bss_3F0.models[(lbl_1_bss_3D0.unk6^1)+12].modelId, "test11_tex_we-itemhook-r", &pos);
            if(lbl_1_bss_3D0.unk6 != 0) {
                lbl_1_bss_44.x = pos.x-(lbl_1_bss_384[0][1].y-lbl_1_bss_384[0][0].x);
                lbl_1_bss_44.y = pos.y+(lbl_1_bss_384[0][1].z-lbl_1_bss_384[0][0].y);
            } else {
                lbl_1_bss_44.x = pos.x+(lbl_1_bss_384[1][1].y-lbl_1_bss_384[1][0].x);
                lbl_1_bss_44.y = pos.y+(lbl_1_bss_384[1][1].z-lbl_1_bss_384[1][0].y);
            }
            if(49.0f == lbl_1_bss_3F0.player[(lbl_1_bss_3D0.unk6^1)].time) {
                lbl_1_bss_3F0.player[(lbl_1_bss_3D0.unk6^1)].speed = 0.0f;
            }
            if(lbl_1_bss_3F0.player[(lbl_1_bss_3D0.unk6^1)].time >= 50.0f) {
                lbl_1_bss_3F0.mode[1]++;
                lbl_1_bss_3F0.mode[0] = modeTbl[(lbl_1_bss_3D0.unk6^1)];
                lbl_1_bss_3F0.mode[1] = 0;
                lbl_1_bss_3F0.mode[2]++;
                lbl_1_bss_3F0.player[(lbl_1_bss_3D0.unk6^1)].time = 50.0f;
                lbl_1_bss_3D0.unk6 = (lbl_1_bss_3D0.unk6^1);
            }
            if(110.0f == lbl_1_bss_3F0.player[lbl_1_bss_3D0.unk6].time) {
                lbl_1_bss_3D0.unk0 = 1;
                lbl_1_bss_3F0.player[lbl_1_bss_3D0.unk6].motNo = 0;
                lbl_1_bss_3F0.player[lbl_1_bss_3D0.unk6].motNoCur = 0;
                lbl_1_bss_3F0.player[lbl_1_bss_3D0.unk6].speed = 1.0f;
                lbl_1_bss_3F0.player[lbl_1_bss_3D0.unk6].attr = HU3D_MOTATTR_LOOP;
                lbl_1_bss_3F0.player[lbl_1_bss_3D0.unk6].attrCur = HU3D_MOTATTR_LOOP;
                Hu3DMotionShiftSet(lbl_1_bss_3F0.models[lbl_1_bss_3D0.unk6+12].modelId, lbl_1_bss_3F0.motId[lbl_1_bss_3D0.unk6][0], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
            }
            break;
    }
}

/* asm 2176-2738, 547 insns. Main sub-state 4: the duellist ran out of presses. Zoom in, drop them, flash the board and knock them off into the sky. */
void fn_1_3DCC(void)
{
    switch(lbl_1_bss_3F0.mode[1]) {
        case 0:
            memcpy(lbl_1_bss_58, &lbl_1_bss_58[lbl_1_bss_3D0.unk6+1], sizeof(OMCAMERAVIEW));
            if(lbl_1_bss_3D0.unk6 != 0) {
                lbl_1_bss_58[0].center.x = lbl_1_bss_384[lbl_1_bss_3D0.unk6][1].y;
            } else {
                lbl_1_bss_58[0].center.x = -lbl_1_bss_384[lbl_1_bss_3D0.unk6][1].y;
            }
            lbl_1_bss_58[0].zoom = 250.0f;
            if(lbl_1_bss_3F0.chr[lbl_1_bss_3D0.unk6].charNo == 8) {
                lbl_1_bss_58[0].zoom = 400.0f;
            }
            lbl_1_bss_58[0].rot.y = 0.0f;
            omCameraViewMoveSimple(lbl_1_bss_58, 15);
            lbl_1_bss_3F0.mode[1]++;
            break;

        case 1:
            if(omCameraViewCheck(1)) {
                lbl_1_bss_3F0.mode[1]++;
                lbl_1_bss_3F0.unkB0 = 0;
                lbl_1_bss_3F0.player[(lbl_1_bss_3D0.unk6^1)].motNo = 4;
                lbl_1_bss_3F0.player[(lbl_1_bss_3D0.unk6^1)].attrReset = HU3D_MOTATTR_LOOP;
                Hu3DModelRotSet((lbl_1_bss_3F0.models+12)[(lbl_1_bss_3D0.unk6^1)].modelId, 0.0f, 0.0f, 0.0f);
            }
            break;

        case 2:
            if(lbl_1_bss_3F0.unkB0++ > 20) {
                lbl_1_bss_3F0.mode[1]++;
                lbl_1_bss_3F0.unkB0 = 0;
                lbl_1_bss_5F0[0] = 0;
                Hu3DTexScrollPosMoveSet(lbl_1_bss_3B4, 0.0f, -0.015625f, 0.0f);
            }
            break;

        case 3:
            lbl_1_bss_3F0.unkB0++;
            if(lbl_1_bss_3F0.unkB0 == 8) {
                Hu3DTexScrollPosSet(lbl_1_bss_3B4, lbl_1_data_39C[0][0], 0.0f, 0.0f);
                Hu3DTexScrollPosMoveSet(lbl_1_bss_3B4, 0.0f, -0.015625f, 0.0f);
            }
            if(lbl_1_bss_3F0.unkB0 == 16) {
                Hu3DTexScrollPosSet(lbl_1_bss_3B4, lbl_1_data_39C[0][0], lbl_1_data_39C[0][1], 0.0f);
                HuAudFXPlay(2109);
                HuAudSStreamFadeOut(lbl_1_data_398, 100);
            }
            if(lbl_1_bss_3F0.unkB0 >= 12 && fn_1_4658(0)) {
                lbl_1_bss_3F0.mode[1]++;
                lbl_1_bss_58[0].zoom = 750.0f;
                lbl_1_bss_58[0].rot.x = -25.0f;
                lbl_1_bss_3F0.unkCC = (lbl_1_bss_3D0.unk6*300)-150;
                lbl_1_bss_3F0.unkD0 = 100.0+(0.85*(750.0*sin((M_PI*25.0)/180.0)));
                lbl_1_bss_3F0.unkD4 = 0.85*(750.0*cos((M_PI*25.0)/180.0));
                lbl_1_bss_3F0.unkD8 = 0.0f;
                lbl_1_bss_3F0.unkB0 = 0;
                lbl_1_bss_3F0.unkB4 = 0;
                {
                    HuVecF pos = { 0.0f, 50.0f, 70.0f };
                    HuVecF *posP;

                    pos.x = -120.0f+(lbl_1_bss_3D0.unk6*240);
                    posP = &pos;
                    fn_1_4FC4(*posP);
                }
                omCameraViewMoveSimple(lbl_1_bss_58, 20);
                omVibrate(lbl_1_bss_3F0.chr[lbl_1_bss_3D0.unk6].no, 40, 4, 2);
            }
            break;

        case 4:
            if(omCameraViewCheck(1)) {
                lbl_1_bss_3F0.unkB0++;
                if(lbl_1_bss_3F0.unkB0 == 20) {
                    omAddObjEx(lbl_1_bss_3F0.objman, 32730, 0, 0, -1, fn_1_5098);
                    HuAudFXPanning(HuAudFXPlay(2115), 80-(lbl_1_bss_3D0.unk6*32));
                }
                if(lbl_1_bss_3F0.unkB0 == 26) {
                    omVibrate(lbl_1_bss_3F0.chr[lbl_1_bss_3D0.unk6].no, 120, 12, 0);
                    Hu3DModelAttrSet(lbl_1_bss_3F0.models[14].modelId, HU3D_ATTR_DISPOFF);
                    omAddObjEx(lbl_1_bss_3F0.objman, 32730, 0, 0, -1, fn_1_4AA0);
                    lbl_1_bss_3F0.unkC0 = 1.0f;
                    lbl_1_bss_3F0.player[lbl_1_bss_3D0.unk6].motNo = 2;
                    lbl_1_bss_3F0.player[lbl_1_bss_3D0.unk6].speed = 0.0f;
                    lbl_1_bss_3F0.player[lbl_1_bss_3D0.unk6].time = 0.0f;
                    lbl_1_bss_3F0.player[lbl_1_bss_3D0.unk6].attrReset = HU3D_MOTATTR_LOOP;
                    Hu3DModelRotSet((lbl_1_bss_3F0.models+12)[lbl_1_bss_3D0.unk6].modelId, 0.0f, 0.0f, 0.0f);
                }
                if(lbl_1_bss_3F0.unkB0 > 120) {
                    MgSeqModeNext();
                    lbl_1_bss_3F0.mode[0] = 0;
                    lbl_1_bss_3F0.mode[1] = 0;
                }
            }
            break;
    }
}

/* asm 2741-3030, 274 insns. Camera shake: copy view 0 into views 1-7 with the zoom jittered (and tilted when shakeF), step through them one frame each, and return TRUE once back at view 0. */
s32 fn_1_4658(s16 shakeF)
{
    float tblA[7] = { 5.0f, 0.0f, -5.0f, 0.0f, 5.0f, 0.0f, -5.0f };
    float tblB[7] = { -5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f, 5.0f };
    int i;

    switch(lbl_1_bss_5F0[0]) {
        case 0:
            for(i=0; i<7; i++) {
                memcpy(&lbl_1_bss_58[i+1], lbl_1_bss_58, sizeof(OMCAMERAVIEW));
                if(shakeF != 0) {
                    lbl_1_bss_58[i+1].zoom += 5.0f*tblB[i];
                    lbl_1_bss_58[0].rot.z = (lbl_1_bss_3D0.unk6*50)-25;
                    if(i == 3) {
                        lbl_1_bss_58[i+1].rot.z = (lbl_1_bss_3D0.unk6*80)-45;
                    }
                    if(i == 4) {
                        lbl_1_bss_58[i+1].rot.z = (lbl_1_bss_3D0.unk6*50)-25;
                    }
                    if(i == 5) {
                        lbl_1_bss_58[i+1].rot.z = (lbl_1_bss_3D0.unk6*70)-35;
                    }
                    if(i >= 6) {
                        lbl_1_bss_58[i+1].rot.z = (lbl_1_bss_3D0.unk6*50)-25;
                    }
                } else {
                    lbl_1_bss_58[i+1].zoom += 3.0f*tblB[i];
                }
            }
            lbl_1_bss_5F0[0]++;
            lbl_1_bss_3F0.unkB4 = 0;
            break;

        case 1:
            omCameraViewMoveSimple(&lbl_1_bss_58[lbl_1_bss_3F0.unkB4], 1);
            lbl_1_bss_3F0.unkB4 = (lbl_1_bss_3F0.unkB4+1)&7;
            lbl_1_bss_5F0[0]++;
            break;

        case 2:
            if(omCameraViewCheck(1)) {
                if(lbl_1_bss_3F0.unkB4 != 0) {
                    omCameraViewMoveSimple(&lbl_1_bss_58[lbl_1_bss_3F0.unkB4], 1);
                    lbl_1_bss_3F0.unkB4 = (lbl_1_bss_3F0.unkB4+1)&7;
                } else {
                    return TRUE;
                }
            }
            break;
    }
    return FALSE;
}

/* asm 3033-3341, 297 insns. Object main: the loser's flight. While unkC0 fades, dim the model's material colours; then fly it out over 25 frames, shake the camera, and sink it until hidden. */
void fn_1_4AA0(OMOBJ *obj)
{
    s16 player = lbl_1_bss_3D0.unk6;
    int unused = 1;
    HU3DMODEL *modelP = &Hu3DData[(lbl_1_bss_3F0.models+12)[player].modelId];
    HSFDATA *hsf = modelP->hsf;
    HSFMATERIAL *mat = hsf->material;
    int timer;
    int i;
    float scale;

    if(0.0f == lbl_1_bss_3F0.unkC0) {
        lbl_1_bss_3F0.unkB8++;
        timer = lbl_1_bss_3F0.unkB8;
        if(timer == 25) {
            HuAudFXPlay(2116);
        }
        if(timer <= 25) {
            lbl_1_bss_5F0[0] = 0;
            lbl_1_bss_3F0.player[lbl_1_bss_3D0.unk6].time = (10.0f*timer)/25.0f;
            Hu3DModelPosSet((lbl_1_bss_3F0.models+12)[player].modelId, lbl_1_bss_3F0.unkCC, (lbl_1_bss_3F0.unkD0*timer)/25.0f, (lbl_1_bss_3F0.unkD4*timer)/25.0f);
        } else {
            if(0.0f == lbl_1_bss_3F0.unkD8) {
                if(fn_1_4658(1)) {
                    lbl_1_bss_3F0.unkD8 = 1.0f;
                }
            } else if(lbl_1_bss_3F0.unkD8 < 60.0f) {
                lbl_1_bss_3F0.unkD0 -= 10.0*sin((M_PI*lbl_1_bss_3F0.unkD8)/180.0);
                Hu3DModelPosSet((lbl_1_bss_3F0.models+12)[player].modelId, lbl_1_bss_3F0.unkCC, lbl_1_bss_3F0.unkD0, lbl_1_bss_3F0.unkD4);
                lbl_1_bss_3F0.unkD8 += 1.0f;
            } else {
                lbl_1_bss_3F0.player[lbl_1_bss_3D0.unk6].attr = HU3D_ATTR_DISPOFF;
            }
        }
    } else {
        lbl_1_bss_3F0.unkC0 -= 0.2;
        if(lbl_1_bss_3F0.unkC0 < 0.0f) {
            lbl_1_bss_3F0.unkC0 = 0.0f;
        }
        scale = lbl_1_bss_3F0.unkC0;
        if(scale >= 0.4) {
            for(i=0; i<modelP->hsf->materialNum; i++, mat++) {
                mat->color[0] = mat->color[0]*scale;
                mat->color[1] = mat->color[1]*scale;
                mat->color[2] = mat->color[2]*scale;
            }
        }
    }
}

/* asm 3344-3377, 32 insns. Reset bss_3B8, the landing-dust effect. */
void fn_1_4F44(void)
{
    HuVecF zero = { 0.0f, 0.0f, 0.0f };
    HuVecF *zeroP = &zero;

    lbl_1_bss_3B8.vec = *zeroP;
    lbl_1_bss_3B8.unk0 = lbl_1_bss_3B8.unk4 = lbl_1_bss_3B8.unk8 = 0;
}

/* asm 3380-3401, 20 insns. Start the landing-dust effect at pos (passed by value). */
void fn_1_4FC4(HuVecF pos)
{
    lbl_1_bss_3B8.unk0 = 1;
    lbl_1_bss_3B8.unk4 = lbl_1_bss_3B8.unk8 = 0;
    lbl_1_bss_3B8.vec = pos;
}

/* asm 3404-3442, 33 insns. Clear (dispF) or set attribute 0x400000 on dust models 15-18. */
void fn_1_5014(s32 dispF)
{
    int i;
    HU3DMODELID id;

    for(i=0; i<4; i++) {
        id = lbl_1_bss_3F0.models[i+15].modelId;
        if(dispF != 0) {
            Hu3DModelAttrReset(id, 0x400000);
        } else {
            Hu3DModelAttrSet(id, 0x400000);
        }
    }
}

/* fn_1_5098's four tables. */
float lbl_1_data_4C8[4] = { 0.0f, 80.0f, -80.0f, 0.0f };
float lbl_1_data_4D8[4] = { 240.0f, 160.0f, 240.0f, 200.0f };
float lbl_1_data_4E8[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
float lbl_1_data_4F8[4] = { 2.0f, 2.0f, 1.5f, 1.0f };

/* asm 3445-3724, 266 insns. Object main: the landing dust. One big puff, four small ones round it, then hide each model when its motion ends. */
void fn_1_5098(OMOBJ *obj)
{
    HU3DMODELID id;
    int i;
    float time;
    float maxTime;

    switch(lbl_1_bss_3B8.unk0) {
        case 0:
            return;

        case 1:
            id = lbl_1_bss_3F0.models[15].modelId;
            Hu3DModelPosSet(id, lbl_1_bss_3B8.vec.x, lbl_1_bss_3B8.vec.y, lbl_1_bss_3B8.vec.z);
            Hu3DModelScaleSet(id, 1.5f, 1.5f, 1.0f);
            Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(id, 0.0f);
            lbl_1_bss_3B8.unk8 = 0;
            lbl_1_bss_3B8.unk0++;
            break;

        case 2:
            id = lbl_1_bss_3F0.models[(lbl_1_bss_3B8.unk8%4)+16].modelId;
            Hu3DModelPosSet(id, lbl_1_bss_3B8.vec.x+lbl_1_data_4C8[lbl_1_bss_3B8.unk8%4], lbl_1_bss_3B8.vec.y+lbl_1_data_4D8[lbl_1_bss_3B8.unk8%4], lbl_1_bss_3B8.vec.z+lbl_1_data_4E8[lbl_1_bss_3B8.unk8%4]);
            Hu3DModelScaleSet(id, 1.25f, 1.25f, 1.0f);
            Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(id, 0.0f);
            Hu3DMotionSpeedSet(id, lbl_1_data_4F8[lbl_1_bss_3B8.unk8%4]);
            lbl_1_bss_3B8.unk4 = 0;
            lbl_1_bss_3B8.unk0++;
            break;

        case 3:
            if(++lbl_1_bss_3B8.unk4 >= 6) {
                lbl_1_bss_3B8.unk8++;
                if(lbl_1_bss_3B8.unk8 == 4) {
                    lbl_1_bss_3B8.unk0++;
                } else {
                    lbl_1_bss_3B8.unk0--;
                }
            }
            break;

        case 4:
            time = Hu3DMotionTimeGet(lbl_1_bss_3F0.models[19].modelId);
            maxTime = Hu3DMotionMaxTimeGet(lbl_1_bss_3F0.models[19].modelId);
            if(!(time < maxTime)) {
                lbl_1_bss_3B8.unk0 = 0;
            }
            break;
    }
    for(i=0; i<4; i++) {
        id = lbl_1_bss_3F0.models[i+15].modelId;
        time = Hu3DMotionTimeGet(id);
        maxTime = Hu3DMotionMaxTimeGet(id);
        if(!(time < maxTime)) {
            Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
        }
    }
}

/* asm 3727-4078, 335 insns. Main sub-state 5: a feint. Pick one of four short scenes (a pause, a shudder, a close-up, a board flicker), then return to the press. */
void fn_1_54C0(void)
{
    int modeTbl[3] = { 1, 3, 0 };
    int subTbl[4] = { 1, 3, 4, 7 };

    switch(lbl_1_bss_3F0.mode[1]) {
        case 0:
            lbl_1_bss_3F0.mode[1] = subTbl[rand8()%4];
            HuAudFXPlay(2112);
            lbl_1_bss_3F0.unkB0 = 0;
            break;

        case 1:
            lbl_1_bss_3F0.mode[1]++;
            lbl_1_bss_3F0.unkB0 = -30;
            break;

        case 2:
            if(lbl_1_bss_3F0.unkB0++ > 30) {
                lbl_1_bss_3F0.mode[1] = 0;
            }
            break;

        case 3:
            omVibrate(lbl_1_bss_3F0.chr[lbl_1_bss_3D0.unk6].no, 20, 12, 0);
            lbl_1_bss_3F0.unkB0 = -30;
            lbl_1_bss_3F0.mode[1] = 2;
            break;

        case 4:
            memcpy(lbl_1_bss_58, &lbl_1_bss_58[lbl_1_bss_3D0.unk6+1], sizeof(OMCAMERAVIEW));
            if(lbl_1_bss_3D0.unk6 != 0) {
                lbl_1_bss_58[0].center.x = lbl_1_bss_384[lbl_1_bss_3D0.unk6][1].y;
            } else {
                lbl_1_bss_58[0].center.x = -lbl_1_bss_384[lbl_1_bss_3D0.unk6][1].y;
            }
            lbl_1_bss_58[0].zoom = 250.0f;
            lbl_1_bss_58[0].rot.y = 0.0f;
            if(lbl_1_bss_3F0.chr[lbl_1_bss_3D0.unk6].charNo == 8) {
                lbl_1_bss_58[0].zoom = 400.0f;
            }
            omCameraViewMoveSimple(lbl_1_bss_58, 15);
            lbl_1_bss_3F0.mode[1]++;
            break;

        case 5:
            if(omCameraViewCheck(1)) {
                if(lbl_1_bss_3F0.unkB0++ > 20) {
                    memcpy(lbl_1_bss_58, &lbl_1_bss_58[lbl_1_bss_3D0.unk6+1], sizeof(OMCAMERAVIEW));
                    omCameraViewMoveSimple(lbl_1_bss_58, 15);
                    lbl_1_bss_3F0.mode[1]++;
                }
            }
            break;

        case 6:
            if(omCameraViewCheck(1)) {
                lbl_1_bss_3F0.mode[1] = 0;
            }
            break;

        case 7:
            Hu3DTexScrollPosMoveSet(lbl_1_bss_3B4, 0.0f, -0.0078125f, 0.0f);
            lbl_1_bss_3F0.mode[1]++;
            lbl_1_bss_3F0.unkB0 = 0;
            break;

        case 8:
            if(lbl_1_bss_3F0.unkB0++ > 14) {
                Hu3DTexScrollPosSet(lbl_1_bss_3B4, lbl_1_data_39C[1][0], 0.125f+lbl_1_data_39C[1][1], 0.0f);
                Hu3DTexScrollPosMoveSet(lbl_1_bss_3B4, 0.0f, -0.0078125f, 0.0f);
                lbl_1_bss_3F0.mode[1]++;
                lbl_1_bss_3F0.unkB0 = 0;
            }
            break;

        case 9:
            if(lbl_1_bss_3F0.unkB0++ > 14) {
                Hu3DTexScrollPosSet(lbl_1_bss_3B4, lbl_1_data_39C[1][0], lbl_1_data_39C[1][1], 0.0f);
                lbl_1_bss_3F0.unkB0 = 0;
                lbl_1_bss_3F0.mode[1] = 2;
            }
            break;
    }
    if(lbl_1_bss_3F0.mode[1] == 0) {
        lbl_1_bss_3F0.mode[0] = modeTbl[lbl_1_bss_3D0.unk6];
        lbl_1_bss_3F0.unkB0 = 0;
    }
}

/* asm 4081-4319, 226 insns. Main sub-state 6: roll the timer board down by the presses just spent (unk8), then hand the turn over. */
void fn_1_59FC(void)
{
    int modeTbl[2] = { 1, 3 };
    int unused = 0;

    switch(lbl_1_bss_3F0.mode[1]) {
        case 0:
            lbl_1_bss_3F0.mode[1]++;
            lbl_1_bss_5D2[1] = lbl_1_bss_3D0.unk8*16;
            lbl_1_bss_5D2[0] = -1;
            if(lbl_1_bss_3D0.unk4 == 6) {
                if(lbl_1_bss_3D0.unk8 == 1) {
                    lbl_1_bss_5D2[0] = 8;
                } else {
                    lbl_1_bss_5D2[0] = 24;
                }
            }
            if(lbl_1_bss_3D0.unk4 == 5 && lbl_1_bss_3D0.unk8 == 2) {
                lbl_1_bss_5D2[0] = 8;
            }
            if(lbl_1_bss_3D0.unk4 == 3) {
                lbl_1_bss_5D2[1] = 16;
            }
            if(lbl_1_bss_3D0.unk2 != 0) {
                lbl_1_bss_5D2[0] = 8;
                lbl_1_bss_5D2[1] = 16;
            }
            lbl_1_bss_5D8 = -0.015625f;
            Hu3DTexScrollPosMoveSet(lbl_1_bss_3B4, 0.0f, lbl_1_bss_5D8, 0.0f);
            break;

        case 1:
            lbl_1_bss_3D0.unkA++;
            if(lbl_1_bss_3D0.unkA == lbl_1_bss_5D2[0]) {
                if(lbl_1_bss_3D0.unk2 != 0) {
                    Hu3DTexScrollPosSet(lbl_1_bss_3B4, lbl_1_data_39C[1][0], 0.125f+lbl_1_data_39C[1][1], 0.0f);
                } else {
                    Hu3DTexScrollPosSet(lbl_1_bss_3B4, lbl_1_data_39C[3][0], 0.125f+lbl_1_data_39C[3][1], 0.0f);
                }
                Hu3DTexScrollPosMoveSet(lbl_1_bss_3B4, 0.0f, lbl_1_bss_5D8, 0.0f);
            }
            if(lbl_1_bss_3D0.unkA == lbl_1_bss_5D2[1]) {
                Hu3DTexScrollPosMoveSet(lbl_1_bss_3B4, 0.0f, 0.0f, 0.0f);
                lbl_1_bss_3F0.mode[0] = modeTbl[lbl_1_bss_3D0.unk6];
                lbl_1_bss_3F0.mode[1] = 0;
                lbl_1_bss_3D0.unkA = 0;
                lbl_1_bss_3D0.unk8 = 0;
            }
            break;
    }
}

/* asm 4322-4352, 28 insns. Main sub-state 7: wait for the squash cycle to finish its beat, then go back to the press. */
void fn_1_5D84(void)
{
    int modeTbl[2] = { 1, 3 };
    s32 result;

    result = fn_1_196C();
    if(result == 0) {
        lbl_1_bss_3F0.mode[0] = modeTbl[lbl_1_bss_3D0.unk6];
    }
}

/* asm 4355-4558, 196 insns. Pre-winner hook body: frame the winner, play their win motion and banner, pay ten coins unless practising. */
void fn_1_5DF4(void)
{
    s32 winner = lbl_1_bss_3D0.unk6^1;
    s32 playerNo;

    switch(lbl_1_bss_3F0.mode[1]) {
        case 0:
            lbl_1_bss_58[0].zoom = 400.0f;
            lbl_1_bss_58[0].center.x = (winner*300)-150;
            lbl_1_bss_58[0].rot.x = -25.0f;
            lbl_1_bss_58[0].rot.y = 0.0f;
            lbl_1_bss_58[0].center.y = 200.0f;
            omCameraViewMoveSimple(lbl_1_bss_58, 30);
            lbl_1_bss_3F0.mode[1]++;
            break;

        case 1:
            if(omCameraViewCheck(1)) {
                lbl_1_bss_3F0.player[winner].motNo = 3;
                lbl_1_bss_3F0.player[winner].motNoCur = 3;
                lbl_1_bss_3F0.player[lbl_1_bss_3D0.unk6].attr = 0;
                lbl_1_bss_3F0.player[lbl_1_bss_3D0.unk6].attrCur = 0;
                Hu3DMotionShiftSet(lbl_1_bss_3F0.models[winner+12].modelId, lbl_1_bss_3F0.motId[winner][3], 0.0f, 10.0f, 0);
                lbl_1_bss_5D0 = GameMesCreate(4, 3, lbl_1_bss_3F0.chr[winner].charNo, -1, -1, -1);
                lbl_1_bss_3F0.mode[1]++;
                HuAudJinglePlay(121);
                playerNo = lbl_1_bss_3F0.chr[winner].no;
                if(!_CheckFlag(FLAG_MG_PRACTICE)) {
                    GwPlayer[playerNo].mgCoinBonus = 10;
                }
                lbl_1_bss_5D2[0] = 0;
            }
            break;

        case 2:
            lbl_1_bss_5D2[0]++;
            if(!GameMesStatGet(lbl_1_bss_5D0) && lbl_1_bss_5D2[0] >= 208) {
                GameMesKill(lbl_1_bss_5D0);
                MgSeqModeNext();
            }
            break;
    }
}
