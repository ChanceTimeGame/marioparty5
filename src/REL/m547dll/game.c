/*
 * m547dll/game.c -- the duel itself: the descent, the ten-second mash, the
 * rise, the result and its messages. Written from the reference assembly,
 * functions in reference order; line ranges are into
 * build/mp5-asm/m547dll/asm/REL/m547dll/game.s.
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

#include "datadir_enum.h"

#include "REL/m547dll/m547.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

void fn_1_490C(void);
void fn_1_56D0(void);
void fn_1_670C(s32 no);
void fn_1_6A88(s32 no);

/* --- .data --- */

/* Camera 2 (the split screen): pos, up, target. */
HuVecF lbl_1_data_280 = { 0.0f, 200.0f, 200.0f };
HuVecF lbl_1_data_28C = { 0.0f, 1.0f, 0.0f };
HuVecF lbl_1_data_298 = { 0.0f, 200.0f, 0.0f };

/* [0] the winner, [1] the loser; -1 until decided. */
s32 lbl_1_data_2A4[2] = { -1, -1 };

/* Per duellist: [i*2] the press count last seen, [i*2+1] frames it has held (negative once the pose was dropped). */
s32 lbl_1_data_2AC[4] = { 0, 0, 0, 0 };

/* The parachute's texture-scroll cell per character, in charNo order. */
float lbl_1_data_2BC[13][2] = {
    { 0.0f, 0.0f },
    { 0.25f, 0.0f },
    { 0.5f, 0.0f },
    { 0.75f, 0.0f },
    { 0.0f, 0.25f },
    { 0.25f, 0.25f },
    { 0.5f, 0.25f },
    { 0.75f, 0.25f },
    { 0.0f, 0.5f },
    { 0.25f, 0.5f },
    { 0.25f, 0.5f },
    { 0.25f, 0.5f },
    { 0.25f, 0.5f }
};

s32 lbl_1_data_324 = -1;            /* the stream playing */
s32 lbl_1_data_328[2] = { 0, 0 };   /* press count at the last pump sound */
s16 lbl_1_data_330[2] = { 0, 0 };   /* the pump sound's pitch */
s32 lbl_1_data_334[2] = { 0, 0 };   /* frames since the last pump sound */
float lbl_1_data_33C = 5.0f;        /* the loser's fall speed */
s32 lbl_1_data_340 = -1;            /* the fall's sound emitter */
HuVecF lbl_1_data_344 = { 0.0f, 0.0f, 0.0f }; /* the loser's drift: z, its speed, the fall speed */

/* --- .bss --- */

float lbl_1_bss_698;                /* the sky's texture scroll */
float lbl_1_bss_69C;                /* its wrap */
s32 lbl_1_bss_6A0;                  /* fn_1_6A88's parachute timer */
s16 lbl_1_bss_6A4;                  /* the result message */
MGTIMER *lbl_1_bss_6A8;
float lbl_1_bss_6AC[4];             /* model 20's swing: angle, speed, x and y radius */
s16 lbl_1_bss_6BC[4];               /* [0] frames before the swing starts */
s32 lbl_1_bss_6C4[4];               /* the winner's parachute: state, delay, frames */
s32 lbl_1_bss_6D4[4];               /* the loser's fall: state, unused */

/* asm 9-83, 71 insns. Push models 1-8's pos and rot at Hu3D. */
void fn_1_4094(void)
{
    s16 i;

    for(i=1; i<9; i++) {
        Hu3DModelPosSet(lbl_1_bss_488.models[i].modelId, lbl_1_bss_488.models[i].pos.x, lbl_1_bss_488.models[i].pos.y, lbl_1_bss_488.models[i].pos.z);
        Hu3DModelRotSet(lbl_1_bss_488.models[i].modelId, lbl_1_bss_488.models[i].rot.x, lbl_1_bss_488.models[i].rot.y, lbl_1_bss_488.models[i].rot.z);
    }
}

/* asm 86-217, 124 insns. Fade-in step 0: lower both duellists onto the stage over 30 frames. */
void fn_1_41B0(void)
{
    int i;
    int j;

    lbl_1_bss_488.count[0]++;
    for(i=0; i<2; i++) {
        lbl_1_bss_488.pos[i].y = 800.0f-((600.0f*lbl_1_bss_488.count[0])/30.0f);
        if(lbl_1_bss_488.count[0] == 30) {
            lbl_1_bss_488.pos[i].y = 200.0f;
            lbl_1_bss_488.player[i].speed = 1.0f;
            if(i != 0) {
                lbl_1_bss_488.mode[0]++;
                lbl_1_bss_488.mode[1] = 0;
                lbl_1_bss_488.count[0] = 0;
                omCameraViewMoveSimpleMulti(1, lbl_1_bss_78, 60);
                HuAudFXPlay(2101);
                for(j=0; j<4; j++) {
                    lbl_1_bss_6C4[j] = 0;
                    lbl_1_bss_6D4[j] = 0;
                }
            }
        }
    }
    if(!WipeCheckEnd() && lbl_1_data_324 < 0) {
        lbl_1_data_324 = HuAudBGMPlay(59);
    }
}

/* asm 220-501, 272 insns. Fade-in step 1: the landing bounce, four damped cosines over 60 frames. */
void fn_1_43A0(void)
{
    int i;

    lbl_1_bss_488.count[0]++;
    for(i=0; i<2; i++) {
        if(lbl_1_bss_488.count[0] <= 15) {
            lbl_1_bss_488.pos[i].y = 180.0+(20.0*cos((M_PI*((lbl_1_bss_488.count[0]*360)/15))/180.0));
        } else if(lbl_1_bss_488.count[0] <= 30) {
            lbl_1_bss_488.pos[i].y = 185.0+(15.0*cos((M_PI*(((lbl_1_bss_488.count[0]-15)*360)/15))/180.0));
        } else if(lbl_1_bss_488.count[0] <= 45) {
            lbl_1_bss_488.pos[i].y = 195.0+(5.0*cos((M_PI*(((lbl_1_bss_488.count[0]-30)*360)/15))/180.0));
        } else if(lbl_1_bss_488.count[0] <= 60) {
            lbl_1_bss_488.pos[i].y = 198.0+(2.0*cos((M_PI*(((lbl_1_bss_488.count[0]-45)*360)/15))/180.0));
        }
        if(lbl_1_bss_488.count[0] == 60) {
            Hu3DMotionShiftSet(lbl_1_bss_488.models[i+13].modelId, lbl_1_bss_488.motId[i][0], 0.0f, 20.0f, HU3D_MOTATTR_LOOP);
            if(i != 0) {
                lbl_1_bss_488.mode[0] = 0;
                lbl_1_bss_488.mode[1] = 0;
                lbl_1_bss_488.count[0] = 0;
                MgSeqModeNext();
            }
        }
    }
    if(!WipeCheckEnd() && lbl_1_data_324 < 0) {
        lbl_1_data_324 = HuAudBGMPlay(59);
    }
}

/* asm 504-580, 75 insns. Main step 0: the ten-second timer, and model 20's swing. */
void fn_1_47E0(void)
{
    lbl_1_bss_6A8 = MgTimerCreate(0);
    MgTimerParamSet(lbl_1_bss_6A8, 600, 0, 0);
    MgTimerPosSet(lbl_1_bss_6A8, 288.0f, 416.0f);
    MgTimerModeOnSet(lbl_1_bss_6A8, 1);
    lbl_1_bss_488.count[0] = 1;
    lbl_1_bss_488.mode[0]++;
    lbl_1_bss_6BC[0] = 0;
    lbl_1_bss_6BC[1] = 0;
    lbl_1_bss_6AC[0] = 0.0f;
    lbl_1_bss_6AC[1] = 3.0f;
    lbl_1_bss_6AC[2] = 600.0f;
    lbl_1_bss_6AC[3] = 200.0f;
}

/* asm 583-682, 98 insns. Model 20's damped swing. Inlined by fn_1_4A94. */
void fn_1_490C(void)
{
    lbl_1_bss_6AC[0] = lbl_1_bss_6AC[0]+lbl_1_bss_6AC[1];
    lbl_1_bss_6AC[1] *= 0.985;
    lbl_1_bss_6AC[2] *= 0.985;
    lbl_1_bss_6AC[3] *= 0.985;
    lbl_1_bss_464.x = -100.0+(lbl_1_bss_6AC[2]*cos((M_PI*lbl_1_bss_6AC[0])/180.0));
    lbl_1_bss_464.y = 300.0-(lbl_1_bss_6AC[3]*sin((M_PI*lbl_1_bss_6AC[0])/180.0));
    lbl_1_bss_464.z = -500.0f;
}

/* asm 685-1501, 783 insns. Main step 1: mash A for ten seconds. Poses and pump sounds follow the presses; at time up, compare. */
void fn_1_4A94(void)
{
    int i;
    int n;
    int se;
    int interval;

    for(i=0; i<2; i++) {
        if(lbl_1_bss_488.count[i+1] == 1) {
            lbl_1_bss_488.count[i+1] = 2;
            Hu3DMotionShiftSet((lbl_1_bss_488.models+13)[i].modelId, lbl_1_bss_488.motId[i][3], 0.0f, 20.0f, HU3D_MOTATTR_LOOP);
        }
        if(lbl_1_bss_488.chr[i].dif == 0 && lbl_1_bss_488.count[i+1] >= 2) {
            if(lbl_1_data_2AC[(i*2)+1] < 0) {
                lbl_1_data_2AC[(i*2)+1]--;
            }
            if(lbl_1_bss_488.count[i+1] == lbl_1_data_2AC[i*2]) {
                if(lbl_1_data_2AC[(i*2)+1] >= 0) {
                    lbl_1_data_2AC[(i*2)+1]++;
                }
                if(lbl_1_data_2AC[(i*2)+1] >= 30 && MgTimerValueGet(lbl_1_bss_6A8) >= 45) {
                    Hu3DMotionShiftSet((lbl_1_bss_488.models+13)[i].modelId, lbl_1_bss_488.motId[i][0], 0.0f, 20.0f, HU3D_MOTATTR_LOOP);
                    lbl_1_data_2AC[(i*2)+1] = -1;
                    lbl_1_data_2AC[i*2] = lbl_1_bss_488.count[i+1];
                }
            } else if(lbl_1_data_2AC[(i*2)+1] >= 0) {
                lbl_1_data_2AC[i*2] = lbl_1_bss_488.count[i+1];
                lbl_1_data_2AC[(i*2)+1] = 0;
            } else if(lbl_1_data_2AC[(i*2)+1] < -20) {
                Hu3DMotionShiftSet((lbl_1_bss_488.models+13)[i].modelId, lbl_1_bss_488.motId[i][3], 0.0f, 20.0f, HU3D_MOTATTR_LOOP);
                lbl_1_data_2AC[i*2] = lbl_1_bss_488.count[i+1];
                lbl_1_data_2AC[(i*2)+1] = 0;
            }
        }
    }
    for(i=0; i<2; i++) {
        if(lbl_1_bss_488.count[i+1] >= 80) {
            lbl_1_bss_488.pos[i].y = 150.0f;
            lbl_1_data_330[i] = 0x2000;
            interval = 3;
        } else {
            lbl_1_bss_488.pos[i].y = 200-((lbl_1_bss_488.count[i+1]*50)/80);
            lbl_1_data_330[i] = (lbl_1_bss_488.count[i+1]*8192)/80;
            interval = 3;
        }
        if(lbl_1_bss_488.count[i+1]-lbl_1_data_328[i] >= interval) {
            lbl_1_data_328[i] = lbl_1_bss_488.count[i+1];
            se = HuAudFXPlay(2106);
            HuAudFXPanning(se, (i*32)+48);
            HuAudFXPitchSet(se, lbl_1_data_330[i]);
            lbl_1_data_334[i] = 0;
        } else {
            lbl_1_data_334[i]++;
            if(lbl_1_bss_488.chr[i].dif != 0 && lbl_1_data_334[i] >= 15) {
                lbl_1_data_328[i] = lbl_1_bss_488.count[i+1];
                se = HuAudFXPlay(2106);
                HuAudFXPanning(se, (i*32)+48);
                HuAudFXPitchSet(se, lbl_1_data_330[i]);
                lbl_1_data_334[i] = 0;
            }
        }
    }
    if(lbl_1_bss_6BC[0] < 180) {
        lbl_1_bss_6BC[0]++;
    } else {
        fn_1_490C();
    }
    if(MgTimerDoneCheck(lbl_1_bss_6A8)) {
        for(i=0; i<2; i++) {
            if(lbl_1_bss_488.count[i+1] != 0) {
                lbl_1_bss_488.count[i+1]--;
            }
        }
        for(i=0, n=0; i<2; i++) {
            if(lbl_1_bss_488.chr[i].dif != 0) {
                fn_1_2648(i);
            }
        }
        lbl_1_bss_488.count[0] = 0;
        if(lbl_1_bss_488.count[1]+lbl_1_bss_488.count[1] != 0 && lbl_1_bss_488.count[1] == lbl_1_bss_488.count[2]) {
            lbl_1_bss_488.count[(rand8()%2)+1]--;
        }
        lbl_1_bss_488.mode[0]++;
        lbl_1_bss_488.mode[1] = 0;
        lbl_1_bss_488.pos[3].z = 30.0f;
        for(i=0, n=0; i<2; i++) {
            if(lbl_1_bss_488.count[i+1] != 0) {
                lbl_1_bss_488.pos[i+2].y = 10000.0f;
            } else {
                lbl_1_bss_488.pos[i+2].y = 0.0f;
                n++;
            }
            Hu3DMotionShiftSet((lbl_1_bss_488.models+13)[i].modelId, lbl_1_bss_488.motId[i][1], 0.0f, 10.0f, 0);
            lbl_1_bss_488.player[i].attrReset = HU3D_MOTATTR_LOOP;
        }
        HuAudSStreamFadeOut(lbl_1_data_324, 100);
        if(n == 2) {
            lbl_1_bss_488.mode[0] = 4;
            lbl_1_bss_488.mode[1] = 0;
            lbl_1_bss_488.count[1] = 0;
            lbl_1_bss_488.count[2] = 0;
        } else {
            HuAudFXPlay(2102);
            lbl_1_bss_24[0] = 1;
            lbl_1_bss_484->work[0] = 0;
            Hu3DCameraPosGet(1, &lbl_1_bss_38[0], &lbl_1_bss_38[1], &lbl_1_bss_38[2]);
            for(i=0; i<4; i++) {
                lbl_1_bss_6BC[i] = 0;
                lbl_1_bss_6AC[i] = 0.0f;
            }
            lbl_1_bss_6AC[1] = 9.0f;
            if(n == 1) {
                if(lbl_1_bss_488.count[1] != 0) {
                    lbl_1_bss_488.pos[3].y = 10000.0f;
                } else {
                    lbl_1_bss_488.pos[2].y = 10000.0f;
                }
            }
        }
    }
}

/* asm 1504-1620, 113 insns. Model 20 swings up and away over the stage. Inlined by fn_1_5894. */
void fn_1_56D0(void)
{
    lbl_1_bss_6AC[0] = lbl_1_bss_6AC[0]+lbl_1_bss_6AC[1];
    if(lbl_1_bss_6AC[0] > 180.0f) {
        lbl_1_bss_6AC[0] = 180.0f;
    }
    lbl_1_bss_464.x = -100.0+(500.0*sin((M_PI*lbl_1_bss_6AC[0])/180.0));
    if(lbl_1_bss_6AC[0] >= 90.0f && lbl_1_bss_464.x < 0.0f) {
        lbl_1_bss_464.x = 0.0f;
    }
    lbl_1_bss_464.y += lbl_1_bss_488.pos[3].z;
    lbl_1_bss_464.z = -500.0*cos((M_PI*lbl_1_bss_6AC[0])/180.0);
    lbl_1_bss_458.y = -lbl_1_bss_6AC[0];
}

/* asm 1623-1966, 332 insns. Main step 2: the duellists rise to their targets, camera 1 follows, and the split screen starts once both arrive. */
void fn_1_5894(void)
{
    int i;
    int n;

    for(i=0, n=0; i<2; i++) {
        if(lbl_1_bss_488.pos[i+2].y > lbl_1_bss_488.pos[i].y+lbl_1_bss_488.pos[3].z) {
            lbl_1_bss_488.pos[i].y += lbl_1_bss_488.pos[3].z;
        } else {
            lbl_1_bss_488.pos[i].y = lbl_1_bss_488.pos[i+2].y;
            n++;
        }
    }
    lbl_1_bss_488.pos[3].z *= 1.06;
    fn_1_56D0();
    if(lbl_1_bss_488.mode[1]++ >= 5 && lbl_1_bss_38[2].y < 4000.0f) {
        lbl_1_bss_38[2].y += 25.0f;
    }
    if(lbl_1_bss_488.mode[1] >= 10) {
        lbl_1_bss_38[0].z -= 20.0f;
        if(lbl_1_bss_38[0].z < 0.0f) {
            lbl_1_bss_38[0].z = 0.1f;
        }
        lbl_1_bss_38[0].y -= 4.0f;
        if(lbl_1_bss_38[0].y < 250.0f) {
            lbl_1_bss_38[0].y = 250.0f;
        }
    }
    lbl_1_bss_38[1].y = lbl_1_bss_38[2].y;
    lbl_1_bss_38[1].z = lbl_1_bss_38[2].z;
    Hu3DCameraPosSetV(1, &lbl_1_bss_38[0], &lbl_1_bss_38[1], &lbl_1_bss_38[2]);
    if(n == 2) {
        memcpy(&lbl_1_bss_488.pos[2], &lbl_1_bss_488.pos[0], sizeof(HuVecF));
        memcpy(&lbl_1_bss_488.pos[3], &lbl_1_bss_488.pos[1], sizeof(HuVecF));
        lbl_1_bss_488.mode[0]++;
        lbl_1_bss_488.mode[1] = 0;
        Hu3DModelAttrSet(lbl_1_bss_488.models[13].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_488.models[14].modelId, HU3D_ATTR_DISPOFF);
        Hu3DCameraPosSetV(2, &lbl_1_data_280, &lbl_1_data_28C, &lbl_1_data_298);
        lbl_1_bss_488.frame = 0;
        lbl_1_bss_488.mode[2] = 0;
        lbl_1_bss_488.mode[3] = 3;
        HuAudFXPlay(2105);
        lbl_1_data_324 = HuAudBGMPlay(75);
    }
}

/* asm 1969-2589, 594 insns. Main step 3: in the split screen both climb; each fourth frame a press is spent, and the first to run out falls. */
void fn_1_5DC4(void)
{
    float scroll;
    int i;

    if(lbl_1_bss_2 < 100) {
        lbl_1_bss_2++;
    }
    switch(lbl_1_bss_488.mode[1]) {
        case 0:
            if(lbl_1_bss_2 == 10) {
                for(i=0; i<2; i++) {
                    Hu3DModelCameraSet((lbl_1_bss_488.models+13)[i].modelId, 2);
                    Hu3DModelAttrReset((lbl_1_bss_488.models+13)[i].modelId, HU3D_ATTR_DISPOFF);
                    lbl_1_bss_488.pos[i].x = (i*240)-120;
                    lbl_1_bss_488.pos[i].y = 80.0f;
                    lbl_1_bss_488.pos[i].z = -400.0f;
                }
                lbl_1_bss_488.mode[1]++;
            }
            break;

        case 1:
            lbl_1_bss_488.frame++;
            if(lbl_1_bss_488.frame%4 == 0) {
                for(i=0; i<2; i++) {
                    lbl_1_bss_488.count[i+1]--;
                    if(lbl_1_bss_488.count[i+1] < 0) {
                        lbl_1_bss_488.mode[3] -= i+1;
                        lbl_1_bss_488.mode[1]++;
                        lbl_1_data_2A4[1] = i;
                        Hu3DMotionShiftSet((lbl_1_bss_488.models+13)[i].modelId, lbl_1_bss_488.motId[i][4], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
                    }
                }
            }
            break;

        case 2:
            lbl_1_bss_488.frame++;
            if(lbl_1_bss_488.frame%4 == 0) {
                for(i=0; i<2; i++) {
                    if(lbl_1_bss_488.count[i+1] >= 0) {
                        lbl_1_bss_488.count[i+1]--;
                        if(lbl_1_bss_488.count[i+1] <= 0) {
                            lbl_1_bss_488.mode[3] -= i+1;
                            lbl_1_data_2A4[0] = i;
                            Hu3DTexScrollPosSet(lbl_1_bss_480[1], lbl_1_data_2BC[lbl_1_bss_488.chr[i].charNo][0], lbl_1_data_2BC[lbl_1_bss_488.chr[i].charNo][1], 0.0f);
                            lbl_1_bss_488.mode[2] = 1;
                            lbl_1_bss_488.mode[1]++;
                            lbl_1_bss_24[3] = 1;
                        }
                    }
                }
            }
            break;

        case 3:
            break;
    }
    if(lbl_1_bss_488.mode[2] == 0) {
        scroll = lbl_1_bss_488.frame%25;
        scroll = 0.5f-((0.5f*scroll)/25.0f);
        Hu3DTexScrollPosSet(lbl_1_bss_480[0], 0.0f, scroll, 0.0f);
    }
    for(i=0; i<2; i++) {
        if(i != lbl_1_data_2A4[1] && lbl_1_bss_488.pos[i+2].y < 23000.0f) {
            lbl_1_bss_488.pos[i+2].y += 80.0f;
        }
    }
    if(lbl_1_bss_488.mode[1] < 3 && lbl_1_bss_464.y < 23000.0f) {
        lbl_1_bss_464.y += 80.0f;
    }
    if(lbl_1_bss_488.mode[3] & 1) {
        lbl_1_bss_488.pos[0].y = 80.0+(15.0*sin((M_PI*(((lbl_1_bss_488.frame%80)*360)/80))/180.0));
        lbl_1_bss_488.pos[0].z = -400.0+(35.0*sin((M_PI*(((lbl_1_bss_488.frame%160)*360)/160))/180.0));
    }
    if(lbl_1_bss_488.mode[3] & 2) {
        lbl_1_bss_488.pos[1].y = 80.0-(15.0*sin((M_PI*(((lbl_1_bss_488.frame%80)*360)/80))/180.0));
        lbl_1_bss_488.pos[1].z = -400.0-(35.0*sin((M_PI*(((lbl_1_bss_488.frame%160)*360)/160))/180.0));
    }
    for(i=0; i<2; i++) {
        if(lbl_1_data_2A4[i] >= 0) {
            if(i != 0) {
                fn_1_670C(lbl_1_data_2A4[1]);
            } else {
                fn_1_6A88(lbl_1_data_2A4[0]);
            }
        }
    }
}

/* asm 2592-2820, 223 insns. The loser drops out of the split screen into camera 1, whistling down past the stage. */
void fn_1_670C(s32 no)
{
    float t;
    Vec dir;

    switch(lbl_1_bss_6D4[0]) {
        case 0:
            lbl_1_bss_488.pos[no].y -= lbl_1_data_33C;
            lbl_1_data_33C *= 1.05;
            if(lbl_1_bss_488.pos[no].y < -250.0f) {
                lbl_1_bss_6D4[0]++;
                t = (lbl_1_bss_488.pos[no+2].y-11040.0f)/12000.0f;
                Hu3DModelCameraSet((lbl_1_bss_488.models+13)[no].modelId, 1);
                Hu3DModelLayerSet((lbl_1_bss_488.models+13)[no].modelId, 6);
                memcpy(&lbl_1_bss_488.pos[no], &lbl_1_bss_488.pos[no+2], sizeof(HuVecF));
                lbl_1_bss_6D4[1] = 0;
                lbl_1_data_344.x = 0.0f;
                lbl_1_data_344.y = 0.5+(0.5*t);
                lbl_1_data_344.z = 75.0f+(75.0f*t);
                PSVECSubtract(&lbl_1_bss_38[2], &lbl_1_bss_38[0], &dir);
                PSVECNormalize(&dir, &dir);
                HuAudFXListnerSet(&lbl_1_bss_38[0], &dir, 30000.0f, 1000.0f);
                lbl_1_data_340 = HuAudFXEmiterPlay(2103, &lbl_1_bss_488.pos[no]);
            }
            break;

        case 1:
            if(lbl_1_bss_488.pos[no].y > -2000.0f) {
                lbl_1_data_344.x = lbl_1_data_344.x+lbl_1_data_344.y;
                lbl_1_bss_488.pos[no].y -= lbl_1_data_344.z;
                lbl_1_bss_488.pos[no].z = lbl_1_data_344.x;
                HuAudFXEmiterUpDate(lbl_1_data_340, &lbl_1_bss_488.pos[no]);
            } else {
                lbl_1_bss_6D4[0]++;
            }
            break;
    }
}

/* asm 2823-3179, 347 insns. The winner opens the parachute and drifts; once the loser has landed, end the step. */
void fn_1_6A88(s32 no)
{
    float scroll;

    switch(lbl_1_bss_6C4[0]) {
        case 0:
            Hu3DModelAttrReset(lbl_1_bss_488.models[22].modelId, HU3D_ATTR_DISPOFF);
            lbl_1_bss_6C4[0]++;
            lbl_1_bss_698 = lbl_1_bss_488.frame%25;
            lbl_1_bss_698 += 1.0f;
            lbl_1_bss_69C = 25.0f;
            lbl_1_bss_6C4[1] = 0;
            lbl_1_bss_6C4[2] = 0;
            break;

        case 1:
            lbl_1_bss_6A0++;
            lbl_1_bss_698 += cos((M_PI*((lbl_1_bss_6A0*90)/60))/180.0);
            if(lbl_1_bss_6A0 >= 60) {
                Hu3DMotionSpeedSet(lbl_1_bss_488.models[22].modelId, 2.0f);
                Hu3DMotionShiftSet((lbl_1_bss_488.models+13)[no].modelId, lbl_1_bss_488.motId[no][5], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
                lbl_1_bss_6C4[0]++;
                HuAudSStreamFadeOut(lbl_1_data_324, 100);
            }
            break;

        case 2:
            lbl_1_bss_698 = lbl_1_bss_698-0.046875004f;
            if(lbl_1_bss_698 < 0.0f) {
                lbl_1_bss_698 = lbl_1_bss_698+lbl_1_bss_69C;
            }
            if(lbl_1_bss_6C4[2]++ == 25) {
                Hu3DMotionSpeedSet(lbl_1_bss_488.models[22].modelId, 6.0f);
                HuAudFXPlay(2104);
            }
            if(lbl_1_bss_6D4[0] >= 2) {
                lbl_1_bss_6C4[1]++;
                if(lbl_1_bss_6C4[1] >= 100) {
                    MgSeqModeNext();
                }
            }
            break;
    }
    lbl_1_bss_488.frame++;
    if(lbl_1_bss_698 >= lbl_1_bss_69C) {
        lbl_1_bss_698 = lbl_1_bss_698-lbl_1_bss_69C;
    }
    scroll = 0.5f-((0.5f*lbl_1_bss_698)/lbl_1_bss_69C);
    Hu3DTexScrollPosSet(lbl_1_bss_480[0], 0.0f, scroll, 0.0f);
    lbl_1_bss_488.pos[no].z = -400.0+((35-(no*70))*sin((M_PI*(((lbl_1_bss_488.frame%160)*360)/160))/180.0));
}

/* asm 3182-3524, 326 insns. Main step 4: a draw. Models 23 and 24 play, models 15 and 16 hide, and the duellists bounce back down to the stage. */
void fn_1_6FF4(void)
{
    int i;

    switch(lbl_1_bss_488.mode[1]) {
        case 0:
            for(i=0; i<2; i++) {
                Hu3DMotionSpeedSet((lbl_1_bss_488.models+23)[i].modelId, 1.0f);
                Hu3DModelAttrReset((lbl_1_bss_488.models+23)[i].modelId, HU3D_ATTR_DISPOFF);
            }
            lbl_1_bss_488.mode[1]++;
            break;

        case 1:
            lbl_1_bss_488.count[0]++;
            lbl_1_bss_488.pos[0].y += 20.0*cos((M_PI*((lbl_1_bss_488.count[0]*90)/12))/180.0);
            lbl_1_bss_488.pos[1].y += 20.0*cos((M_PI*((lbl_1_bss_488.count[0]*90)/12))/180.0);
            if(lbl_1_bss_488.count[0] == 12) {
                for(i=0; i<2; i++) {
                    Hu3DModelAttrSet((lbl_1_bss_488.models+15)[i].modelId, HU3D_ATTR_DISPOFF);
                }
                lbl_1_bss_488.mode[1]++;
            }
            break;

        case 2:
            lbl_1_bss_488.count[0]++;
            if(lbl_1_bss_488.count[0] > 24) {
                lbl_1_bss_488.count[0] = 24;
            }
            lbl_1_bss_488.pos[0].y += 20.0*cos((M_PI*((lbl_1_bss_488.count[0]*90)/12))/180.0);
            lbl_1_bss_488.pos[1].y += 20.0*cos((M_PI*((lbl_1_bss_488.count[0]*90)/12))/180.0);
            if(lbl_1_bss_488.pos[0].y < 100.0f) {
                for(i=0; i<2; i++) {
                    lbl_1_bss_488.pos[i].y = 100.0f;
                    lbl_1_bss_488.player[i].motNo = 2;
                    lbl_1_bss_488.player[i].motNoCur = 0;
                }
                lbl_1_bss_488.count[0] = 0;
                lbl_1_bss_488.mode[1]++;
            }
            break;

        case 3:
            lbl_1_bss_488.count[0]++;
            if(lbl_1_bss_488.count[0] >= 24) {
                for(i=0; i<2; i++) {
                    Hu3DMotionShiftSet((lbl_1_bss_488.models+13)[i].modelId, lbl_1_bss_488.motId[i][0], 0.0f, 30.0f, HU3D_MOTATTR_LOOP);
                }
                MgSeqModeNext();
            }
            break;
    }
}

/* asm 3527-3663, 134 insns. The sky keeps scrolling and the winner keeps drifting. Inlined by fn_1_7724, 7A08 and 7F2C. */
void fn_1_750C(void)
{
    float scroll;

    lbl_1_bss_698 = lbl_1_bss_698-0.046875004f;
    if(lbl_1_bss_698 < 0.0f) {
        lbl_1_bss_698 = lbl_1_bss_698+lbl_1_bss_69C;
    }
    scroll = 0.5f-((0.5f*lbl_1_bss_698)/lbl_1_bss_69C);
    Hu3DTexScrollPosSet(lbl_1_bss_480[0], 0.0f, scroll, 0.0f);
    lbl_1_bss_488.frame++;
    lbl_1_bss_488.pos[lbl_1_data_2A4[0]].z = -400.0+((35-(lbl_1_data_2A4[0]*70))*sin((M_PI*(((lbl_1_bss_488.frame%160)*360)/160))/180.0));
}

/* asm 3666-3855, 185 insns. Finish: pick the pre-winner step (0 win, 1 draw, 2 a new record by a human winner). */
void fn_1_7724(void)
{
    if(lbl_1_data_2A4[0] >= 0) {
        fn_1_750C();
        lbl_1_bss_2++;
        lbl_1_bss_488.mode[0] = 0;
        if(lbl_1_bss_488.chr[lbl_1_data_2A4[0]].dif == 0 && lbl_1_bss_24[1] > lbl_1_bss_34) {
            lbl_1_bss_488.mode[0] = 2;
        }
    } else {
        lbl_1_bss_488.mode[0] = 1;
    }
    lbl_1_bss_488.mode[1] = 0;
    lbl_1_bss_488.count[0] = 0;
}

/* asm 3858-4095, 233 insns. Pre-winner step 0: the winner's message, voice and ten coins. */
void fn_1_7A08(void)
{
    s32 playerNo;

    fn_1_750C();
    lbl_1_bss_2++;
    lbl_1_bss_488.count[0]++;
    if(lbl_1_bss_488.mode[1] == 0 && lbl_1_bss_488.count[0] > 30) {
        lbl_1_bss_6A4 = GameMesCreate(4, 3, lbl_1_bss_488.chr[lbl_1_data_2A4[0]].charNo, -1, -1, -1);
        HuAudJinglePlay(121);
        CharFXPlay(lbl_1_bss_488.chr[lbl_1_data_2A4[0]].charNo, 506);
        lbl_1_bss_488.mode[1] = 1;
        lbl_1_bss_488.count[0] = 0;
        playerNo = lbl_1_bss_488.chr[lbl_1_data_2A4[0]].no;
        if(!_CheckFlag(FLAG_MG_PRACTICE)) {
            GwPlayer[playerNo].mgCoinBonus = 10;
        }
    } else if(!GameMesStatGet(lbl_1_bss_6A4) && lbl_1_bss_488.count[0] >= 210) {
        GameMesKill(lbl_1_bss_6A4);
        MgSeqModeNext();
    }
}

/* asm 4098-4199, 96 insns. Pre-winner step 1: the draw message. */
void fn_1_7DAC(void)
{
    int i;

    lbl_1_bss_488.count[0]++;
    if(lbl_1_bss_488.mode[1] == 0 && lbl_1_bss_488.count[0] > 30) {
        for(i=0; i<2; i++) {
            lbl_1_bss_488.player[i].motNo = 6;
            lbl_1_bss_488.player[i].motNoCur = 0;
            lbl_1_bss_488.player[i].attrReset = HU3D_MOTATTR_LOOP;
        }
        lbl_1_bss_6A4 = GameMesCreate(2, 2);
        HuAudJinglePlay(123);
        lbl_1_bss_488.mode[1]++;
        lbl_1_bss_488.count[0] = 0;
        CharFXPlayPan(lbl_1_bss_488.chr[0].charNo, 512, 48);
        CharFXPlayPan(lbl_1_bss_488.chr[1].charNo, 512, 80);
    } else if(!GameMesStatGet(lbl_1_bss_6A4) && lbl_1_bss_488.count[0] >= 210) {
        GameMesKill(lbl_1_bss_6A4);
        MgSeqModeNext();
    }
}

/* asm 4202-4426, 219 insns. Pre-winner step 2: the new-record message, then on to step 0. */
void fn_1_7F2C(void)
{
    lbl_1_bss_488.count[0]++;
    fn_1_750C();
    lbl_1_bss_2++;
    if(lbl_1_bss_488.mode[1] == 0 && lbl_1_bss_488.count[0] > 30) {
        lbl_1_bss_6A4 = GameMesCreate(14, lbl_1_bss_24[1]);
        GWMgRecordSet(7, lbl_1_bss_24[1]);
        lbl_1_bss_488.mode[1]++;
        lbl_1_bss_24[0]++;
        if(!_CheckFlag(FLAG_MG_PRACTICE)) {
            HuAudJinglePlay(134);
        } else {
            lbl_1_bss_488.count[0] = 150;
        }
    } else if(!GameMesStatGet(lbl_1_bss_6A4) && lbl_1_bss_488.count[0] >= 150) {
        GameMesKill(lbl_1_bss_6A4);
        lbl_1_bss_488.mode[0] = 0;
        lbl_1_bss_488.mode[1] = 0;
    }
}

/* asm 4429-4703, 264 insns. The two falling props: while either duellist has more than ten presses, drop one every 100-149 frames. */
void fn_1_8298(void)
{
    float scale;
    int i;
    int n;

    for(i=0, n=0; i<2; i++) {
        if(lbl_1_bss_488.count[i+1] > 10) {
            n++;
        }
    }
    for(i=0; i<2; i++) {
        if(lbl_1_bss_430[i] == 0) {
            if(lbl_1_bss_430[2] <= 0) {
                lbl_1_bss_430[2] = (rand8()%50)+100;
                lbl_1_bss_440[i].y = 1000.0f;
                Hu3DModelAttrReset((lbl_1_bss_488.models+27)[i].modelId, HU3D_ATTR_DISPOFF);
                lbl_1_bss_440[i].z = -40-(rand8()%20);
                lbl_1_bss_430[i] = 1;
                scale = rand8()%10;
                Hu3DModelScaleSet((lbl_1_bss_488.models+27)[i].modelId, 0.5+((0.5*scale)/10.0), 0.5+((0.5*scale)/10.0), 0.5+((0.5*scale)/10.0));
                if(i != 0) {
                    lbl_1_bss_440[i].x = (rand8()%40)+60;
                } else {
                    lbl_1_bss_440[i].x = -60-(rand8()%40);
                }
            } else if(n != 0) {
                lbl_1_bss_430[2]--;
            }
        } else {
            lbl_1_bss_440[i].y -= 40.0f;
            if(lbl_1_bss_440[i].y < -600.0f) {
                lbl_1_bss_430[i] = 0;
                Hu3DModelAttrSet((lbl_1_bss_488.models+27)[i].modelId, HU3D_ATTR_DISPOFF);
            }
        }
    }
}
