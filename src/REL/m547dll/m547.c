/*
 * m547dll -- a KETTOU duel (overlay #61): the sequence hooks, the models,
 * cameras, sprites and object bring-up. Written from the reference assembly,
 * functions in reference order; line ranges are into
 * build/mp5-asm/m547dll/asm/REL/m547dll/m547.s.
 *
 * _prolog and _epilog are not reproduced.
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
#include "game/esprite.h"
#include "game/mg/seqman.h"
#include "game/mg/score.h"
#include "game/gamemes.h"
#include "game/flag.h"
#include "game/printfunc.h"

#include "datadir_enum.h"

#include "REL/m547dll/m547.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

void ObjectSetup(void);
void fn_1_17C(s16 mode, s16 frameNo);
void fn_1_A84(s16 mode, s16 frameNo);
void fn_1_ACC(s16 mode, s16 frameNo);
void fn_1_B24(s16 mode, s16 frameNo);
void fn_1_C70(s16 mode, s16 frameNo);
void fn_1_CF0(s16 mode, s16 frameNo);
void fn_1_D7C(s16 mode, s16 frameNo);
void fn_1_DA8(s16 mode, s16 frameNo);
void fn_1_DE4(s16 mode, s16 frameNo);
void fn_1_DE8(void);
void fn_1_E88(OMOBJ *obj);
void fn_1_10D0(OMOBJ *obj);
void fn_1_1544(OMOBJ *obj);
void fn_1_162C(void);
void fn_1_1BA8(void);
void fn_1_223C(s16 n);
void fn_1_231C(void);
void fn_1_23A8(void);
void fn_1_243C(s32 no, s16 dif);
void fn_1_2678(OMOBJ *obj);
void fn_1_2CE4(void);
void fn_1_376C(void);
void fn_1_3ADC(OMOBJ *obj);

/* --- .data --- */

/* files/data/m547.bin: the arena (passed to fn_1_86B8). */
unsigned int lbl_1_data_0[13] = {
    0x00690000, 0x00690001, 0x00690002, 0x00690003, 0x00690004, 0x00690005, 0x00690006, 0x00690007,
    0x00690008, 0x00690009, 0x0069000A, 0x0069000B, 0x0069000C
};

/* fn_1_2CE4's models. */
unsigned int lbl_1_data_34[11] = {
    0x0069000D, 0x0069000E, 0x0069000F, 0x00690010, 0x00690011, 0x00690013, 0x00690014, 0x00690015,
    0x00690016, 0x00690017, 0x00690018
};

/* The joint motion fn_1_2CE4 puts on its first hook model. */
unsigned int lbl_1_data_60 = 0x00690012;

/* Seven motions per character, in charNo order. */
unsigned int lbl_1_data_64[13][7] = {
    { 0x008C0000, 0x008C0003, 0x008C0004, 0x008C004E, 0x008C002B, 0x008C004F, 0x008C0007 },
    { 0x00330000, 0x00330003, 0x00330004, 0x0033004E, 0x0033002B, 0x0033004F, 0x00330007 },
    { 0x00B70000, 0x00B70003, 0x00B70004, 0x00B7004E, 0x00B7002B, 0x00B7004F, 0x00B70007 },
    { 0x00ED0000, 0x00ED0003, 0x00ED0004, 0x00ED004E, 0x00ED002B, 0x00ED004F, 0x00ED0007 },
    { 0x00E60000, 0x00E60003, 0x00E60004, 0x00E6004E, 0x00E6002B, 0x00E6004F, 0x00E60007 },
    { 0x00170000, 0x00170003, 0x00170004, 0x0017004E, 0x0017002B, 0x0017004F, 0x00170007 },
    { 0x00E00000, 0x00E00003, 0x00E00004, 0x00E0004E, 0x00E0002B, 0x00E0004F, 0x00E00007 },
    { 0x008C0000, 0x008C0003, 0x008C0004, 0x008C004E, 0x008C002B, 0x008C004F, 0x008C0007 },
    { 0x008C0000, 0x008C0003, 0x008C0004, 0x008C004E, 0x008C002B, 0x008C004F, 0x008C0007 },
    { 0x008C0000, 0x008C0003, 0x008C0004, 0x008C004E, 0x008C002B, 0x008C004F, 0x008C0007 },
    { 0x008C0000, 0x008C0003, 0x008C0004, 0x008C004E, 0x008C002B, 0x008C004F, 0x008C0007 },
    { 0x008C0000, 0x008C0003, 0x008C0004, 0x008C004E, 0x008C002B, 0x008C004F, 0x008C0007 },
    { 0x008C0000, 0x008C0003, 0x008C0004, 0x008C004E, 0x008C002B, 0x008C004F, 0x008C0007 }
};

/* All nine hooks are used. */
MGSEQ_PARAM lbl_1_data_1D0 = {
    0, 0,
    fn_1_17C,
    fn_1_A84,
    fn_1_ACC,
    fn_1_B24,
    fn_1_C70,
    fn_1_CF0,
    fn_1_D7C,
    fn_1_DA8,
    fn_1_DE4
};

/* Sub-states by mode[0]: fade-in, main, pre-winner. */
void (*lbl_1_data_1F8[2])(void) = { fn_1_41B0, fn_1_43A0 };
void (*lbl_1_data_200[5])(void) = { fn_1_47E0, fn_1_4A94, fn_1_5894, fn_1_5DC4, fn_1_6FF4 };
void (*lbl_1_data_214[3])(void) = { fn_1_7A08, fn_1_7DAC, fn_1_7F2C };

float lbl_1_data_220 = 1.0f;        /* unreferenced */

/* --- .bss --- */

HU3DMOTID lbl_1_bss_0;              /* the hook model's joint motion */
s16 lbl_1_bss_2;                    /* result timeline, counts to 100 */
s32 lbl_1_bss_4;                    /* fn_1_3ADC: its step timer */
s32 lbl_1_bss_8;                    /* fn_1_3ADC: its state */
s32 lbl_1_bss_C;                    /* fn_1_3ADC: frames to the next flash */
s32 lbl_1_bss_10;                   /* fn_1_3ADC: flashes, mod 5 */
s32 lbl_1_bss_14;                   /* fn_1_3ADC: sway angle */
MGSCORE *lbl_1_bss_18;              /* this game's presses */
MGSCORE *lbl_1_bss_1C;              /* the record */
HUSPRGRPID lbl_1_bss_20;            /* the score window */
s32 lbl_1_bss_24[4];                /* the score window's state, the press count shown, and a pulse state and timer */
s32 lbl_1_bss_34;                   /* the saved record */
HuVecF lbl_1_bss_38[3];             /* camera 1: pos, up, target */
HU3DMOTID lbl_1_bss_5C[14];         /* seven motions per duellist */
OMCAMERAVIEW lbl_1_bss_78[4];
M547_MODEL lbl_1_bss_E8[M547_MODEL_MAX];
s32 lbl_1_bss_430[4];               /* [0] [1] a falling prop is live, [2] frames to the next */
HuVecF lbl_1_bss_440[2];            /* the falling props */
HuVecF lbl_1_bss_458;               /* model 20's rotation */
HuVecF lbl_1_bss_464;               /* model 20's position */
s16 lbl_1_bss_470[8];               /* sprites: four frame edges, two split-screen marks, 6 the A button, 7 the record label */
s16 lbl_1_bss_480[2];               /* texture scrolls: [0] the sky, [1] the parachute */
OMOBJ *lbl_1_bss_484;               /* omOutViewMulti */
M547_WORK lbl_1_bss_488;

/* asm 61-117, 55 insns. */
void ObjectSetup(void)
{
    fn_1_86B8(&lbl_1_bss_488, lbl_1_bss_E8, lbl_1_data_0);
    lbl_1_bss_488.objman = omInitObjMan(50, 8192);
    omGameSysInit(lbl_1_bss_488.objman);
    lbl_1_bss_484 = omAddObjEx(lbl_1_bss_488.objman, 32730, 0, 0, -1, omOutViewMulti);
    lbl_1_bss_484->work[0] = 2;
    omAddObjEx(lbl_1_bss_488.objman, 32730, 0, 0, -1, fn_1_8D2C);
    MgSeqCreate(&lbl_1_data_1D0);
}

/* asm 120-701, 578 insns. Init hook: arena, duellists, props, sprites, both cameras, light and shadow, the objects. */
void fn_1_17C(s16 mode, s16 frameNo)
{
    HuVecF pos;
    HuVecF up;
    HuVecF target;
    HU3DLIGHTID lightId;
    int i;

    fn_1_8904(1);
    fn_1_8B9C(lbl_1_data_64[lbl_1_bss_488.chr[0].charNo], lbl_1_data_64[lbl_1_bss_488.chr[1].charNo]);
    fn_1_8BC0(&lbl_1_bss_5C[0], &lbl_1_bss_5C[7]);
    fn_1_8BE4();
    fn_1_2CE4();
    fn_1_376C();
    Hu3DModelPosSet(lbl_1_bss_488.models[13].modelId, -150.0f, 800.0f, 0.0f);
    Hu3DModelPosSet(lbl_1_bss_488.models[14].modelId, 150.0f, 800.0f, 0.0f);
    lbl_1_bss_488.pos[0].x = -150.0f;
    lbl_1_bss_488.pos[0].y = 800.0f;
    lbl_1_bss_488.pos[0].z = 0.0f;
    lbl_1_bss_488.pos[1].x = 150.0f;
    lbl_1_bss_488.pos[1].y = 800.0f;
    lbl_1_bss_488.pos[1].z = 0.0f;
    fn_1_91E8();
    omAddObjEx(lbl_1_bss_488.objman, 32730, 0, 0, -1, fn_1_933C);
    CenterM[0].x = 0.0f;
    CenterM[0].y = 275.0f;
    CenterM[0].z = 0.0f;
    CRotM[0].x = -40.0f;
    CRotM[0].y = 0.0f;
    CRotM[0].z = 0.0f;
    CZoomM[0] = 1000.0f;
    lbl_1_bss_78[0].center.x = 0.0f;
    lbl_1_bss_78[0].center.y = 275.0f;
    lbl_1_bss_78[0].center.z = 0.0f;
    lbl_1_bss_78[0].rot.x = -20.0f;
    lbl_1_bss_78[0].rot.y = 0.0f;
    lbl_1_bss_78[0].rot.z = 0.0f;
    lbl_1_bss_78[0].zoom = 600.0f;
    CenterM[1].x = 0.0f;
    CenterM[1].y = 100.0f;
    CenterM[1].z = 0.0f;
    CRotM[1].x = 0.0f;
    CRotM[1].y = 0.0f;
    CRotM[1].z = 0.0f;
    CZoomM[1] = 500.0f;
    Hu3DCameraCreate(3);
    Hu3DCameraPerspectiveSet(1, 45.0f, 20.0f, 50000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 640, 480);
    Hu3DCameraPerspectiveSet(2, 45.0f, 20.0f, 30000.0f, 1.2f);
    Hu3DCameraViewportSet(2, 360.0f, 256.0f, 240.0f, 180.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(2, 320, 240, 0, 0);
    lightId = Hu3DGLightCreate(0.0f, 1000.0f, 1000.0f, 0.0f, -1.0f, -1.0f, 255, 255, 255);
    Hu3DGLightInfinitytSet(lightId);
    Hu3DGLightStaticSet(lightId, 1);
    omAddObjEx(lbl_1_bss_488.objman, 32730, 0, 0, -1, fn_1_954C);
    omAddObjEx(lbl_1_bss_488.objman, 32730, 0, 0, -1, fn_1_E88);
    omAddObjEx(lbl_1_bss_488.objman, 32730, 0, 0, -1, fn_1_10D0);
    omAddObjEx(lbl_1_bss_488.objman, 32730, 0, 0, -1, fn_1_1544);
    omAddObjEx(lbl_1_bss_488.objman, 32730, 0, 0, -1, fn_1_2678);
    omAddObjEx(lbl_1_bss_488.objman, 32730, 0, 0, -1, fn_1_3ADC);
    Hu3DBGColorSet(186, 245, 255);
    Hu3DShadowCreate(45.0f, 20.0f, 15000.0f);
    pos.x = 0.0f;
    pos.y = 1500.0f;
    pos.z = 250.0f;
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    target.x = 0.0f;
    target.y = 100.0f;
    target.z = 0.0f;
    Hu3DShadowTPLvlSet(0.25f);
    Hu3DModelShadowSet(lbl_1_bss_488.models[13].modelId);
    Hu3DModelShadowSet(lbl_1_bss_488.models[14].modelId);
    Hu3DModelShadowMapSet(lbl_1_bss_488.models[0].modelId);
    Hu3DModelShadowMapSet(lbl_1_bss_488.models[15].modelId);
    Hu3DModelShadowMapSet(lbl_1_bss_488.models[16].modelId);
    Hu3DShadowPosSet(&pos, &up, &target);
    lbl_1_bss_488.player[0].motNo = 2;
    lbl_1_bss_488.player[0].speed = 0.0f;
    lbl_1_bss_488.player[0].time = 0.0f;
    lbl_1_bss_488.player[0].attrReset = HU3D_MOTATTR_LOOP;
    lbl_1_bss_488.player[1].motNo = 2;
    lbl_1_bss_488.player[1].speed = 0.0f;
    lbl_1_bss_488.player[1].time = 0.0f;
    lbl_1_bss_488.player[1].attrReset = HU3D_MOTATTR_LOOP;
    lbl_1_bss_34 = GWMgRecordGet(7);
    for(i=0; i<4; i++) {
        lbl_1_bss_430[i] = 0;
        lbl_1_bss_24[i] = 0;
    }
    lbl_1_bss_430[2] = (rand8()%50)+100;
    Hu3DZClearLayerSet(14);
    MgSeqModeDelaySet(mode+1, -1);
    MgSeqModeNext();
    fn_1_162C();
}

/* asm 704-723, 18 insns. Fade-in hook. */
void fn_1_A84(s16 mode, s16 frameNo)
{
    lbl_1_data_1F8[lbl_1_bss_488.mode[0]]();
    fn_1_4094();
}

/* asm 726-749, 22 insns. Start hook. */
void fn_1_ACC(s16 mode, s16 frameNo)
{
    lbl_1_bss_488.mode[0] = 0;
    lbl_1_bss_488.mode[1] = 0;
    MgSeqModeDelaySet(mode+1, -1);
    fn_1_4094();
}

/* asm 752-841, 83 insns. Main hook: the sub-state, then the A button sprite blinks and the split screen opens once the result begins. */
void fn_1_B24(s16 mode, s16 frameNo)
{
    lbl_1_data_200[lbl_1_bss_488.mode[0]]();
    if(lbl_1_bss_2 >= 40) {
        if((frameNo/16)%2) {
            espPosSet(lbl_1_bss_470[6], 350.0f, 416.0f);
        } else {
            espPosSet(lbl_1_bss_470[6], -100.0f, 0.0f);
        }
    }
    if(lbl_1_bss_2 < 100) {
        fn_1_162C();
    }
    if(lbl_1_bss_2 > 100) {
        fn_1_1BA8();
        espPosSet(lbl_1_bss_470[6], -100.0f, 0.0f);
    }
    fn_1_231C();
    if(lbl_1_bss_2 != 0) {
        fn_1_23A8();
    }
    fn_1_4094();
}

/* asm 844-878, 32 insns. Finish hook. */
void fn_1_C70(s16 mode, s16 frameNo)
{
    MgSeqModeDelaySet(mode+1, -1);
    fn_1_7724();
    if(lbl_1_bss_2 > 100) {
        fn_1_1BA8();
        espPosSet(lbl_1_bss_470[6], -100.0f, 0.0f);
    }
    fn_1_23A8();
    fn_1_4094();
}

/* asm 881-918, 35 insns. Pre-winner hook. */
void fn_1_CF0(s16 mode, s16 frameNo)
{
    lbl_1_data_214[lbl_1_bss_488.mode[0]]();
    if(lbl_1_bss_2 > 100) {
        fn_1_1BA8();
        espPosSet(lbl_1_bss_470[6], -100.0f, 0.0f);
    }
    fn_1_23A8();
    fn_1_4094();
}

/* asm 921-933, 11 insns. Winner hook. */
void fn_1_D7C(s16 mode, s16 frameNo)
{
    fn_1_750C();
    fn_1_23A8();
    fn_1_4094();
    MgSeqModeNext();
}

/* asm 936-953, 15 insns. Fade-out hook. */
void fn_1_DA8(s16 mode, s16 frameNo)
{
    fn_1_750C();
    fn_1_23A8();
    fn_1_4094();
    if(!WipeCheckEnd()) {
        MgSeqModeNext();
    }
}

/* asm 956-958, 1 insns. Close hook. */
void fn_1_DE4(s16 mode, s16 frameNo)
{
}

/* asm 961-1002, 40 insns. Unreferenced debug readout of both press counts. */
void fn_1_DE8(void)
{
    print8(8, 120, 1.5f, "A BUTTON");
    print8(8, 132, 1.5f, "1P=%04d", lbl_1_bss_488.count[1]);
    print8(8, 144, 1.5f, "2P=%04d", lbl_1_bss_488.count[2]);
}

/* A computer duellist's target presses, and its press interval and timer. */
s32 lbl_1_data_240[2] = { 0, 0 };
s32 lbl_1_data_248[2][2] = { { 0, 0 }, { 0, 0 } };

/* asm 1005-1157, 146 insns. Object main: place the duellists, count presses while the timer runs, and hang the parachute over the winner. */
void fn_1_E88(OMOBJ *obj)
{
    float ofs[13] = { 102.0f, 102.0f, 114.0f, 98.0f, 102.0f, 114.0f, 90.0f, 100.0f, 102.0f, 102.0f, 102.0f, 102.0f, 102.0f };
    int i;

    for(i=0; i<2; i++) {
        Hu3DModelPosSet((lbl_1_bss_488.models+13)[i].modelId, lbl_1_bss_488.pos[i].x, lbl_1_bss_488.pos[i].y, lbl_1_bss_488.pos[i].z);
        if(lbl_1_bss_488.count[0] != 0 && MgSeqModeGet() == 5) {
            if(lbl_1_bss_488.chr[i].dif != 0) {
                fn_1_243C(i, lbl_1_bss_488.chr[i].dif-1);
            }
            if((lbl_1_bss_488.chr[i].btnDown & PAD_BUTTON_A) && lbl_1_bss_488.count[i+1] < 200) {
                lbl_1_bss_488.count[i+1]++;
            }
        }
        if(lbl_1_data_2A4[0] == i) {
            Hu3DModelPosSet(lbl_1_bss_488.models[22].modelId, lbl_1_bss_488.pos[i].x, lbl_1_bss_488.pos[i].y+ofs[lbl_1_bss_488.chr[i].charNo], lbl_1_bss_488.pos[i].z);
        }
    }
}

/* asm 1160-1460, 285 insns. Object main: the balloons over the duellists, shrinking and fading as they rise. */
void fn_1_10D0(OMOBJ *obj)
{
    float scale;
    int i;

    if(MgSeqModeGet() == 5) {
        if(lbl_1_bss_488.mode[0] == 2) {
            for(i=0; i<2; i++) {
                Hu3DModelPosSet((lbl_1_bss_488.models+18)[i].modelId, lbl_1_bss_488.pos[i].x, lbl_1_bss_488.pos[i].y, lbl_1_bss_488.pos[i].z);
                scale = 1.0f;
                if(lbl_1_bss_488.pos[i].y >= 7500.0f) {
                    scale = 1.0-((lbl_1_bss_488.pos[i].y-7500.0f)/2500.0f);
                }
                if(10000.0f == lbl_1_bss_488.pos[i].y) {
                    scale = 0.0f;
                }
                if(scale > 1.0f) {
                    scale = 1.0f;
                }
                if(scale < 0.0f) {
                    scale = 0.0f;
                }
                Hu3DModelScaleSet((lbl_1_bss_488.models+18)[i].modelId, 0.5+(0.30000001192092896*(1.0-scale)), 0.5+(0.30000001192092896*(1.0-scale)), 0.5+(0.30000001192092896*(1.0-scale)));
                fn_1_21BC(i, scale);
            }
        }
        if(lbl_1_bss_488.mode[0] == 3) {
            for(i=0; i<2; i++) {
                if(i != lbl_1_data_2A4[0] && i != lbl_1_data_2A4[1]) {
                    Hu3DModelPosSet((lbl_1_bss_488.models+18)[i].modelId, lbl_1_bss_488.pos[i+2].x, lbl_1_bss_488.pos[i+2].y, lbl_1_bss_488.pos[i+2].z);
                } else if(i == lbl_1_data_2A4[1] && lbl_1_bss_6D4[0] == 1) {
                    Hu3DModelPosSet((lbl_1_bss_488.models+18)[i].modelId, lbl_1_bss_488.pos[i+2].x, lbl_1_bss_488.pos[i].y, lbl_1_bss_488.pos[i].z);
                    scale = 1.0f;
                    if(lbl_1_bss_488.pos[i].y >= 7500.0f) {
                        scale = 1.0-((lbl_1_bss_488.pos[i].y-7500.0f)/2500.0f);
                    }
                    if(lbl_1_bss_488.pos[i].y > 10000.0f) {
                        scale = 0.0f;
                    }
                    fn_1_21BC(i, scale);
                }
            }
        }
    }
}

/* asm 1463-1526, 58 insns. Object main: models 15 and 16 play their motion as far as each duellist is pressed below 200. */
void fn_1_1544(OMOBJ *obj)
{
    float time;
    int i;
    s32 id;

    for(i=0; i<2; i++) {
        id = (lbl_1_bss_488.models+15)[i].modelId;
        if(lbl_1_bss_488.pos[i].y >= 200.0f) {
            Hu3DMotionTimeSet(id, 0.0f);
        } else {
            time = 200.0f-lbl_1_bss_488.pos[i].y;
            Hu3DMotionTimeSet(id, 2.0f*time);
        }
    }
}

/* asm 1529-1895, 351 insns. The split-screen frame while it opens (bss_2 up to 100): edges, marks and their fade. */
void fn_1_162C(void)
{
    float edgeX;
    float edgeY;
    float markX;
    float markY;
    s16 n;
    int i;
    s16 mark;

    fn_1_223C(lbl_1_bss_2);
    if(lbl_1_bss_2 > 10) {
        n = 10;
    } else {
        n = lbl_1_bss_2;
    }
    edgeX = ((n*240)/10)+1;
    markX = (1.5f*n)/10.0f;
    markX = (576.0f*markX)/640.0f;
    if(lbl_1_bss_2 < 10) {
        n = 0;
    } else if(lbl_1_bss_2 > 20) {
        n = 10;
    } else {
        n = lbl_1_bss_2-10;
    }
    edgeY = ((n*180)/10)+3;
    markY = (1.5*n)/10.0;
    if(lbl_1_bss_2 == 0) {
        edgeX = edgeY = markX = markY = 0.0f;
    }
    espPosSet(lbl_1_bss_470[0], 0.9f*(480.0f+(0.5f*edgeX)), 346.0f);
    espPosSet(lbl_1_bss_470[1], 0.9f*(480.0f-(0.5f*edgeX)), 346.0f);
    espPosSet(lbl_1_bss_470[2], 432.0f, 346.0f+(0.5f*edgeY));
    espPosSet(lbl_1_bss_470[3], 432.0f, 346.0f-(0.5f*edgeY));
    for(i=0; i<4; i++) {
        if(i < 2) {
            espScaleSet(lbl_1_bss_470[i], 1.0f, edgeY/480.0f);
        } else {
            espScaleSet(lbl_1_bss_470[i], edgeX/640.0f, 1.0f);
        }
    }
    if(lbl_1_bss_2%2) {
        mark = 5;
    } else {
        mark = 4;
    }
    espPosSet(lbl_1_bss_470[mark], 432.0f, 346.0f);
    espScaleSet(lbl_1_bss_470[mark], markX, markY);
    espScaleSet(lbl_1_bss_470[mark^1], 0.0f, 0.0f);
    if(lbl_1_bss_2 >= 30 && lbl_1_bss_2 <= 90) {
        edgeX = 1.0f-((lbl_1_bss_2-30)/60.0f);
        if(lbl_1_bss_2 > 90) {
            edgeX = 0.0f;
        }
        espTPLvlSet(lbl_1_bss_470[mark], edgeX);
    }
}

/* asm 1898-2293, 389 insns. The split screen once open (bss_2 past 100): grow camera 2's viewport over 60 frames and follow the loser. */
void fn_1_1BA8(void)
{
    s16 n;
    int i;
    u32 x;
    u32 y;
    u32 w;
    u32 h;

    n = lbl_1_bss_2-101;
    if(n > 60) {
        n = 60;
    }
    w = ((n*400)/60)+240;
    h = ((n*300)/60)+180;
    x = 360-((n*360)/60);
    y = 256-((n*256)/60);
    Hu3DCameraScissorSet(2, x, y, w, h);
    Hu3DCameraViewportSet(2, x, y, w, h, 0.0f, 1.0f);
    espPosSet(lbl_1_bss_470[0], 0.9f*(x+w), y+(h/2));
    espPosSet(lbl_1_bss_470[1], 0.9f*x, y+(h/2));
    espPosSet(lbl_1_bss_470[2], 0.9f*(x+(w/2)), y+h);
    espPosSet(lbl_1_bss_470[3], 0.9f*(x+(w/2)), y);
    lbl_1_data_280.x = (n*(120-(lbl_1_data_2A4[1]*240)))/60;
    lbl_1_data_298.x = (n*(120-(lbl_1_data_2A4[1]*240)))/60;
    lbl_1_data_280.y = 200.0f+(((lbl_1_bss_488.pos[lbl_1_data_2A4[0]].y-100.0f)*n)/60.0f);
    lbl_1_data_298.y = 200.0f+(((lbl_1_bss_488.pos[lbl_1_data_2A4[0]].y-100.0f)*n)/60.0f);
    Hu3DCameraPosSetV(2, &lbl_1_data_280, &lbl_1_data_28C, &lbl_1_data_298);
    for(i=0; i<4; i++) {
        if(i < 2) {
            espScaleSet(lbl_1_bss_470[i], 1.0f, h/480.0f);
        } else {
            espScaleSet(lbl_1_bss_470[i], w/640.0f, 1.0f);
        }
    }
}

/* asm 2296-2331, 32 insns. Set every material of balloon `no` (model 18+no) to alpha. Inlined by fn_1_2CE4 and fn_1_3ADC. */
void fn_1_21BC(s32 no, float alpha)
{
    HU3DMODEL *modelP = &Hu3DData[(lbl_1_bss_488.models+18)[no].modelId];
    HSFDATA *hsf = modelP->hsf;
    HSFMATERIAL *material = hsf->material;
    s32 i;

    for(i=0; i<modelP->hsf->materialNum; i++, material++) {
        material->invAlpha = alpha;
    }
}

/* asm 2334-2394, 56 insns. Camera 2's scissor while the split screen opens: a line, then a box. */
void fn_1_223C(s16 n)
{
    u32 x;
    u32 y;
    u32 w;
    u32 h;

    if(n < 10) {
        w = (n*240)/10;
        x = 480-(w/2);
        y = 345;
        h = 2;
    } else if(n < 20) {
        x = 360;
        w = 240;
        h = (((n-10)*180)/10)+2;
        y = 346-(h/2);
    } else {
        x = 360;
        w = 240;
        y = 256;
        h = 180;
    }
    Hu3DCameraScissorSet(2, x, y, w, h);
}

/* asm 2397-2433, 35 insns. */
void fn_1_231C(void)
{
    Hu3DModelPosSet(lbl_1_bss_488.models[20].modelId, lbl_1_bss_464.x, lbl_1_bss_464.y, lbl_1_bss_464.z);
    Hu3DModelRotSet(lbl_1_bss_488.models[20].modelId, lbl_1_bss_458.x, lbl_1_bss_458.y, lbl_1_bss_458.z);
}

/* asm 2436-2476, 37 insns. */
void fn_1_23A8(void)
{
    int i;

    fn_1_8298();
    for(i=0; i<2; i++) {
        Hu3DModelPosSet((lbl_1_bss_488.models+27)[i].modelId, lbl_1_bss_440[i].x, lbl_1_bss_440[i].y, lbl_1_bss_440[i].z);
    }
}

/* asm 2479-2615, 131 insns. A computer duellist presses A at an even rate toward a target count set by difficulty. */
void fn_1_243C(s32 no, s16 dif)
{
    s32 targetTbl[4] = { 40, 50, 85, 110 };
    s32 rnd;

    if(lbl_1_data_240[no] == 0) {
        if(dif == 3) {
            rnd = rand8()%15;
            lbl_1_data_240[no] = rnd+targetTbl[dif];
        } else {
            rnd = rand8()%20;
            lbl_1_data_240[no] = rnd+targetTbl[dif];
        }
        lbl_1_data_248[no][0] = 600/lbl_1_data_240[no];
    }
    lbl_1_data_248[no][1]++;
    if(lbl_1_data_248[no][1] >= lbl_1_data_248[no][0]) {
        lbl_1_data_248[no][1] = 0;
        if(lbl_1_bss_488.count[no+1] < lbl_1_data_240[no]) {
            lbl_1_bss_488.chr[no].btnDown = PAD_BUTTON_A;
        }
    }
}

/* asm 2618-2631, 12 insns. A computer duellist's count jumps to its target when time runs out. */
void fn_1_2648(s32 no)
{
    lbl_1_bss_488.count[no+1] = lbl_1_data_240[no];
}

/* asm 2634-3054, 411 insns. Object main: the record and press-count window, and its pulse on a new record. */
void fn_1_2678(OMOBJ *obj)
{
    switch(lbl_1_bss_24[0]) {
        case 0:
            lbl_1_bss_20 = MgScoreWinCreate(140, 48);
            MgScoreWinPosSet(lbl_1_bss_20, 288.0f, 68.0f);
            MgScoreWinTPLvlSet(lbl_1_bss_20, 0.7f);
            MgScoreWinColorSet(lbl_1_bss_20, 0, 0, 0);
            lbl_1_bss_1C = MgScoreCreate(0x960030, 0x960035, FALSE);
            MgScoreMaxDigitSet(lbl_1_bss_1C, 3);
            MgScoreValueSet(lbl_1_bss_1C, lbl_1_bss_34);
            MgScoreColorSet(lbl_1_bss_1C, 66, 255, 122);
            MgScorePosSet(lbl_1_bss_1C, 259.0f, 60.0f);
            espPosSet(lbl_1_bss_470[7], 238.0f, 60.0f);
            lbl_1_bss_18 = MgScoreCreate(0x960030, 0x960035, FALSE);
            MgScoreMaxDigitSet(lbl_1_bss_18, 3);
            MgScoreValueSet(lbl_1_bss_18, lbl_1_bss_24[1]);
            MgScoreColorSet(lbl_1_bss_18, 255, 255, 255);
            MgScorePosSet(lbl_1_bss_18, 259.0f, 76.0f);
            lbl_1_bss_24[1] = lbl_1_bss_24[2] = 0;
            lbl_1_bss_24[0] = 99;
            break;

        case 1:
            if(lbl_1_bss_24[3] == 0) {
                lbl_1_bss_24[1]++;
            }
            MgScoreValueSet(lbl_1_bss_18, lbl_1_bss_24[1]);
            break;

        case 2:
            MgScoreValueSet(lbl_1_bss_1C, lbl_1_bss_24[1]);
            MgScoreValueSet(lbl_1_bss_18, lbl_1_bss_24[1]);
            lbl_1_bss_24[0] = 3;
            lbl_1_bss_24[2] = 0;
            lbl_1_bss_24[3] = 0;
            break;

        case 3:
            if(lbl_1_bss_24[2] == 0) {
                lbl_1_bss_24[3]++;
                MgScoreDigitScaleSet(lbl_1_bss_1C, 1.0f+(0.02f*lbl_1_bss_24[3]), 1.0f+(0.02f*lbl_1_bss_24[3]));
                espScaleSet(lbl_1_bss_470[7], 1.0f+(0.02f*lbl_1_bss_24[3]), 1.0f+(0.02f*lbl_1_bss_24[3]));
                if(lbl_1_bss_24[3] == 10) {
                    lbl_1_bss_24[2] = 1;
                    lbl_1_bss_24[3] = 0;
                }
            } else {
                lbl_1_bss_24[3]++;
                MgScoreDigitScaleSet(lbl_1_bss_1C, 1.2f-(0.04f*lbl_1_bss_24[3]), 1.2f-(0.04f*lbl_1_bss_24[3]));
                espScaleSet(lbl_1_bss_470[7], 1.2f-(0.04f*lbl_1_bss_24[3]), 1.2f-(0.04f*lbl_1_bss_24[3]));
                if(lbl_1_bss_24[3] == 5) {
                    lbl_1_bss_24[2] = 0;
                    lbl_1_bss_24[3] = 0;
                }
            }
            break;
    }
}

/* asm 3057-3754, 674 insns. The duel's own models 15-28: the pumps, sky, balloons, the hooked prop, parachute, the side models, clouds and the falling props. */
void fn_1_2CE4(void)
{
    HU3DMODELID id;
    int i;

    for(i=0; i<2; i++) {
        id = (lbl_1_bss_488.models+15)[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_34[0], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(id, -150.0f+(300.0f*i), 100.0f, 5.0f);
        Hu3DModelRotSet(id, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(id, 1);
        Hu3DMotionSpeedSet(id, 0.0f);
        Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    }
    id = lbl_1_bss_488.models[17].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_34[1], HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(id, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(id, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(id, 2);
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    lbl_1_bss_480[0] = Hu3DTexScrollCreate(id, "m547sky01");
    for(i=0; i<2; i++) {
        id = (lbl_1_bss_488.models+18)[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_34[i+2], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(id, -150.0f+(300.0f*i), 250.0f, 0.0f);
        Hu3DModelRotSet(id, 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(id, 0.5f, 0.5f, 0.5f);
        Hu3DModelCameraSet(id, 1);
        Hu3DModelLayerSet(id, 7);
        Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
        fn_1_21BC(i, 1.0f);
    }
    for(i=0; i<2; i++) {
        id = (lbl_1_bss_488.models+20)[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_34[i+4], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
        Hu3DModelRotSet(id, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(id, 1);
        if(i != 0) {
            Hu3DModelPosSet(id, 0.0f, 0.0f, 0.0f);
            Hu3DModelHookSet(lbl_1_bss_488.models[20].modelId, "itemhook_sao", id);
        } else {
            lbl_1_bss_464.x = 2000.0f;
            Hu3DModelPosSet(id, 2000.0f, 0.0f, 0.0f);
            lbl_1_bss_0 = Hu3DJointMotion(id, HuDataSelHeapReadNum(lbl_1_data_60, HU_MEMNUM_OVL, HEAP_MODEL));
            Hu3DMotionSet(id, lbl_1_bss_0);
            Hu3DMotionSpeedSet(id, 1.0f);
            Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
        }
        Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    }
    id = lbl_1_bss_488.models[22].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_34[6], HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(id, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(id, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(id, 2);
    Hu3DMotionSpeedSet(id, 0.0f);
    Hu3DMotionTimeSet(id, 0.0f);
    Hu3DModelAttrReset(id, HU3D_MOTATTR_LOOP);
    lbl_1_bss_480[1] = Hu3DTexScrollCreate(id, "m547para01");
    for(i=0; i<2; i++) {
        if(i == 0) {
            id = lbl_1_bss_488.models[23].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_34[7], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            id = lbl_1_bss_488.models[24].modelId = Hu3DModelLink(lbl_1_bss_488.models[23].modelId);
        }
        Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(id, -130.0f+(260.0f*i), 180.0f, 85.0f);
        Hu3DModelRotSet(id, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(id, 1);
        Hu3DMotionSpeedSet(id, 0.0f);
        Hu3DModelAttrReset(id, HU3D_MOTATTR_LOOP);
        Hu3DModelScaleSet(id, 1.9f, 1.6f, 1.5f);
    }
    for(i=0; i<2; i++) {
        id = (lbl_1_bss_488.models+25)[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_34[i+8], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
        if(i != 0) {
            Hu3DModelPosSet(id, -4000.0f, 18000.0f, 3000.0f);
        } else {
            Hu3DModelPosSet(id, -5000.0f, 19000.0f, 4000.0f);
        }
        Hu3DModelRotSet(id, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(id, 1);
        Hu3DModelLayerSet(id, 7);
        Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    }
    for(i=0; i<2; i++) {
        if(i == 0) {
            id = lbl_1_bss_488.models[27].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_34[10], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            id = lbl_1_bss_488.models[28].modelId = Hu3DModelLink(lbl_1_bss_488.models[27].modelId);
        }
        Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(id, 0.0f, 0.0f, -100.0f);
        lbl_1_bss_440[i].x = (i*200)-100;
        lbl_1_bss_440[i].y = (i*100)-50;
        lbl_1_bss_440[i].z = -100.0f;
        Hu3DModelRotSet(id, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(id, 2);
        Hu3DModelLayerSet(id, 3);
    }
}

/* asm 3757-3986, 220 insns. The sprites: four split-screen edges, two marks, the A button and the record label. */
void fn_1_376C(void)
{
    int i;

    for(i=0; i<4; i++) {
        if(i < 2) {
            lbl_1_bss_470[i] = espEntry(0x690019, 210, 0);
        } else {
            lbl_1_bss_470[i] = espEntry(0x69001A, 210, 0);
        }
        espDispOff(lbl_1_bss_470[i]);
        espDrawNoSet(lbl_1_bss_470[i], 0);
        espPosSet(lbl_1_bss_470[i], 288.0f, 240.0f);
        espAttrSet(lbl_1_bss_470[i], HUSPR_ATTR_NOANIM);
        espDispOn(lbl_1_bss_470[i]);
    }
    for(i=0; i<2; i++) {
        if(i != 0) {
            lbl_1_bss_470[i+4] = espEntry(0x69001C, 215, 0);
        } else {
            lbl_1_bss_470[i+4] = espEntry(0x69001B, 215, 0);
        }
        espDispOff(lbl_1_bss_470[i+4]);
        espDrawNoSet(lbl_1_bss_470[i+4], 0);
        espPosSet(lbl_1_bss_470[i+4], 288.0f, 240.0f);
        espAttrSet(lbl_1_bss_470[i+4], HUSPR_ATTR_NOANIM);
        espDispOn(lbl_1_bss_470[i+4]);
    }
    lbl_1_bss_470[6] = espEntry(0x69001D, 15, 0);
    espDispOff(lbl_1_bss_470[6]);
    espDrawNoSet(lbl_1_bss_470[6], 0);
    espPosSet(lbl_1_bss_470[6], -100.0f, 0.0f);
    espAttrSet(lbl_1_bss_470[6], HUSPR_ATTR_NOANIM);
    espDispOn(lbl_1_bss_470[6]);
    lbl_1_bss_470[7] = espEntry(0x69001E, 15, 0);
    espDispOff(lbl_1_bss_470[7]);
    espDrawNoSet(lbl_1_bss_470[7], 0);
    espPosSet(lbl_1_bss_470[7], -100.0f, 0.0f);
    espAttrSet(lbl_1_bss_470[7], HUSPR_ATTR_NOANIM);
    espDispOn(lbl_1_bss_470[7]);
}

/* fn_1_3ADC's flash alpha for balloon model 26. */
float lbl_1_data_27C = 1.0f;

/* asm 3989-4374, 366 insns. Object main: sway model 26 and, once the main game runs, flash it from time to time. */
void fn_1_3ADC(OMOBJ *obj)
{
    lbl_1_bss_14 = (lbl_1_bss_14+1)%360;
    lbl_1_bss_488.models[26].rot.y = 2.0*sin((M_PI*lbl_1_bss_14)/180.0);
    Hu3DModelRotSet(lbl_1_bss_488.models[26].modelId, 0.0f, lbl_1_bss_488.models[26].rot.y, 0.0f);
    switch(lbl_1_bss_8) {
        case 0:
            fn_1_21BC(8, lbl_1_data_27C);
            lbl_1_bss_8++;
            break;

        case 1:
            if(MgSeqModeGet() == 5 && lbl_1_bss_488.mode[0] == 2) {
                if(lbl_1_bss_4++ > 30) {
                    lbl_1_bss_8++;
                    lbl_1_bss_4 = 0;
                }
            }
            break;

        case 2:
            lbl_1_bss_4++;
            lbl_1_data_27C = 1.0-(0.4*sin((M_PI*((lbl_1_bss_4*90)/16))/180.0));
            fn_1_21BC(8, lbl_1_data_27C);
            if(lbl_1_bss_4 == 16) {
                lbl_1_bss_4 = 0;
                lbl_1_bss_8++;
                lbl_1_bss_C = (rand8()%60)+64;
            }
            break;

        case 3:
            if(lbl_1_bss_4++ >= lbl_1_bss_C) {
                fn_1_21BC(8, 1.0f);
                lbl_1_bss_10 = (lbl_1_bss_10+1)%5;
                if(lbl_1_bss_10 == 1 || lbl_1_bss_10 == 4) {
                    lbl_1_bss_8 = 2;
                } else {
                    lbl_1_bss_8++;
                }
                lbl_1_bss_4 = 0;
            }
            break;

        case 4:
            if(lbl_1_bss_4++ >= 6) {
                fn_1_21BC(8, 0.6f);
                lbl_1_bss_8 = 2;
                lbl_1_bss_4 = 0;
            }
            break;
    }
}
