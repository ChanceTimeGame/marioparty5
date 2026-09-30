/*
 * m548dll -- a KETTOU duel (overlay #62): the sequence hooks, the model
 * table, the camera and object bring-up. Written from the reference
 * assembly, functions in reference order; line ranges are into
 * build/mp5-asm/m548dll/asm/REL/m548dll/m548.s.
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

void ObjectSetup(void);
void fn_1_15C(s16 mode, s16 frameNo);
void fn_1_8C0(s16 mode, s16 frameNo);
void fn_1_934(s16 mode, s16 frameNo);
void fn_1_9B4(s16 mode, s16 frameNo);
void fn_1_9FC(s16 mode, s16 frameNo);
void fn_1_A54(s16 mode, s16 frameNo);
void fn_1_A78(s16 mode, s16 frameNo);
void fn_1_A9C(s16 mode, s16 frameNo);
void fn_1_AD0(s16 mode, s16 frameNo);
void fn_1_AD4(s16 padNo);
void fn_1_D6C(void);
void fn_1_1204(OMOBJ *obj);
void fn_1_1264(s16 padNo);
void fn_1_167C(void);
void fn_1_19A4(OMOBJ *obj);
void fn_1_1CB4(void);

/* --- .data --- */

/* Two vectors per character, in charNo order; fn_1_15C copies a duellist's pair to bss_384. */
HuVecF lbl_1_data_0[13][2] = {
    { { 148.03f, 173.65f, 138.69f }, { 182.5f, 125.0f, 207.0f } },
    { { 154.95f, 180.53f, 142.9f }, { 190.31f, 141.0f, 217.0f } },
    { { 126.02f, 206.1f, 101.54f }, { 218.15f, 127.0f, 233.0f } },
    { { 131.71f, 199.45f, 90.45f }, { 191.7f, 130.0f, 210.0f } },
    { { 151.55f, 240.86f, 116.39f }, { 246.55f, 144.0f, 228.0f } },
    { { 124.06f, 202.75f, 100.98f }, { 214.31f, 126.0f, 227.0f } },
    { { 130.47f, 206.43f, 117.83f }, { 236.28f, 138.5f, 228.2f } },
    { { 126.35f, 195.32f, 111.63f }, { 202.39f, 126.0f, 196.0f } },
    { { 83.79f, 228.14f, 62.16f }, { 227.45f, 130.0f, 276.0f } },
    { { 122.57f, 164.46f, 108.48f }, { 208.13f, 109.0f, 181.0f } },
    { { 122.57f, 164.46f, 108.48f }, { 208.13f, 109.0f, 181.0f } },
    { { 122.57f, 164.46f, 108.48f }, { 208.13f, 109.0f, 181.0f } },
    { { 122.57f, 164.46f, 108.48f }, { 208.13f, 109.0f, 181.0f } }
};

/* files/data/m548.bin: the arena (passed to fn_1_6104). */
unsigned int lbl_1_data_138[12] = {
    0x006A0000, 0x006A0001, 0x006A0002, 0x006A0003, 0x006A0004, 0x006A0005, 0x006A0006, 0x006A0007, 0x006A0008, 0x006A0009, 0x006A000A, 0x006A000B
};

/* fn_1_167C's model data; the last entry repeats five times. */
unsigned int lbl_1_data_168[7] = {
    0x006A000C, 0x006A000D, 0x006A000E, 0x006A000E, 0x006A000E, 0x006A000E, 0x006A000E
};

/* Five motions per character, in charNo order. */
unsigned int lbl_1_data_184[13][5] = {
    { 0x008C0000, 0x008C0023, 0x008C0022, 0x008C0006, 0x008C0079 },
    { 0x00330000, 0x00330023, 0x00330022, 0x00330006, 0x00330079 },
    { 0x00B70000, 0x00B70023, 0x00B70022, 0x00B70006, 0x00B70079 },
    { 0x00ED0000, 0x00ED0023, 0x00ED0022, 0x00ED0006, 0x00ED0079 },
    { 0x00E60000, 0x00E60023, 0x00E60022, 0x00E60006, 0x00E60079 },
    { 0x00170000, 0x00170023, 0x00170022, 0x00170006, 0x00170079 },
    { 0x00E00000, 0x00E00023, 0x00E00022, 0x00E00006, 0x00E00079 },
    { 0x002D0000, 0x002D0023, 0x002D0022, 0x002D0006, 0x002D0079 },
    { 0x00C90000, 0x00C90023, 0x00C90022, 0x00C90006, 0x00C90079 },
    { 0x00B00000, 0x00B00023, 0x00B00022, 0x00B00006, 0x00B00079 },
    { 0x00B00000, 0x00B00023, 0x00B00022, 0x00B00006, 0x00B00079 },
    { 0x00B00000, 0x00B00023, 0x00B00022, 0x00B00006, 0x00B00079 },
    { 0x00B00000, 0x00B00023, 0x00B00022, 0x00B00006, 0x00B00079 }
};

/* A float pair per character (fn_1_1D84). */
float lbl_1_data_288[13][2] = {
    { 0.0f, -0.15f },
    { -5.0f, -0.3f },
    { 10.0f, -0.25f },
    { 0.0f, -0.1f },
    { -5.0f, -0.35f },
    { 10.0f, -0.25f },
    { -10.0f, -0.5f },
    { 0.0f, 0.2f },
    { 0.0f, -0.15f },
    { 0.0f, -0.15f },
    { 0.0f, -0.15f },
    { 0.0f, -0.15f },
    { 0.0f, -0.15f }
};

/* All nine hooks are used. */
MGSEQ_PARAM lbl_1_data_2F0 = {
    0, 0,
    fn_1_15C,
    fn_1_8C0,
    fn_1_934,
    fn_1_9B4,
    fn_1_9FC,
    fn_1_A54,
    fn_1_A78,
    fn_1_A9C,
    fn_1_AD0
};

/* Main-hook sub-states (fn_1_9B4). */
void (*lbl_1_data_318[8])(void) = {
    fn_1_2AD4, fn_1_309C, fn_1_2AD4, fn_1_309C, fn_1_3DCC, fn_1_54C0, fn_1_59FC, fn_1_5D84
};

/*
 * .data:0x338..0x397 are string literals: "test11_tex_we-itemhook-r" and the
 * debug readout's formats (fn_1_D6C), and "m548time" (fn_1_167C).
 */

/* --- .bss --- */

s32 lbl_1_bss_0[2][4];
s32 lbl_1_bss_20[2];
float lbl_1_bss_28[4];              /* only [0] is read */
HuVecF lbl_1_bss_38;
HuVecF lbl_1_bss_44;
s16 lbl_1_bss_50;
MGTIMER *lbl_1_bss_54;
OMCAMERAVIEW lbl_1_bss_58[8];
HU3DMOTID lbl_1_bss_138[14];        /* fn_1_15C passes [0] and [7] to fn_1_660C */
M548_MODEL lbl_1_bss_154[M548_MODEL_MAX];
HuVecF lbl_1_bss_384[2][2];
s16 lbl_1_bss_3B4;
M548_UNK3B8 lbl_1_bss_3B8;
M548_UNK3D0 lbl_1_bss_3D0;
M548_WORK lbl_1_bss_3F0;
s16 lbl_1_bss_5D0;
s16 lbl_1_bss_5D2[3];

/* asm 61-109, 47 insns. */
void ObjectSetup(void)
{
    fn_1_6104(&lbl_1_bss_3F0, lbl_1_bss_154, lbl_1_data_138);
    lbl_1_bss_3F0.objman = omInitObjMan(50, 8192);
    omGameSysInit(lbl_1_bss_3F0.objman);
    omAddObjEx(lbl_1_bss_3F0.objman, 32730, 0, 0, -1, omOutView);
    omAddObjEx(lbl_1_bss_3F0.objman, 32730, 0, 0, -1, fn_1_6890);
    MgSeqCreate(&lbl_1_data_2F0);
}

/* asm 112-590, 473 insns. Init hook: the arena, both duellists and their motions, the camera, light and shadow, and the objects. */
void fn_1_15C(s16 mode, s16 frameNo)
{
    HuVecF pos;
    HuVecF up;
    HuVecF target;
    HU3DLIGHTID lightId;
    int i;

    lbl_1_bss_3D0.unk4 = 9;
    fn_1_6350(1);
    fn_1_65E8(lbl_1_data_184[lbl_1_bss_3F0.chr[0].charNo], lbl_1_data_184[lbl_1_bss_3F0.chr[1].charNo]);
    fn_1_660C(&lbl_1_bss_138[0], &lbl_1_bss_138[7]);
    fn_1_6630();
    for(i=0; i<2; i++) {
        lbl_1_bss_384[i][0].x = lbl_1_data_0[lbl_1_bss_3F0.chr[i].charNo][0].x;
        lbl_1_bss_384[i][0].y = lbl_1_data_0[lbl_1_bss_3F0.chr[i].charNo][0].y;
        lbl_1_bss_384[i][0].z = lbl_1_data_0[lbl_1_bss_3F0.chr[i].charNo][0].z;
        lbl_1_bss_384[i][1].x = lbl_1_data_0[lbl_1_bss_3F0.chr[i].charNo][1].x;
        lbl_1_bss_384[i][1].y = lbl_1_data_0[lbl_1_bss_3F0.chr[i].charNo][1].y;
        lbl_1_bss_384[i][1].z = lbl_1_data_0[lbl_1_bss_3F0.chr[i].charNo][1].z;
    }
    fn_1_167C();
    fn_1_6D4C();
    omAddObjEx(lbl_1_bss_3F0.objman, 32730, 0, 0, -1, fn_1_6EA0);
    for(i=0; i<2; i++) {
        CharMotionUpdateSet(lbl_1_bss_3F0.chr[i].charNo, lbl_1_data_184[lbl_1_bss_3F0.chr[i].charNo][1], FALSE);
    }
    lbl_1_bss_58[0].center.x = Center.x = -lbl_1_bss_384[0][1].y;
    lbl_1_bss_58[0].center.y = Center.y = lbl_1_bss_384[0][1].z;
    lbl_1_bss_58[0].center.z = Center.z = 0.0f;
    lbl_1_bss_58[0].rot.x = CRot.x = -20.0f;
    lbl_1_bss_58[0].rot.y = CRot.y = 0.0f;
    lbl_1_bss_58[0].rot.z = CRot.z = 0.0f;
    lbl_1_bss_58[0].zoom = CZoom = 200.0f;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 20.0f, 30000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    lightId = Hu3DGLightCreate(0.0f, 1000.0f, 1000.0f, 0.0f, -1.0f, -1.0f, 255, 255, 255);
    Hu3DGLightInfinitytSet(lightId);
    Hu3DGLightStaticSet(lightId, 1);
    omAddObjEx(lbl_1_bss_3F0.objman, 32730, 0, 0, -1, fn_1_1204);
    fn_1_1CB4();
    omAddObjEx(lbl_1_bss_3F0.objman, 32730, 0, 0, -1, fn_1_1D84);
    fn_1_4F44();
    Hu3DBGColorSet(186, 245, 255);
    Hu3DShadowCreate(45.0f, 20.0f, 10000.0f);
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
    Hu3DShadowPosSet(&pos, &up, &target);
    Hu3DShadowSizeSet(200);
    Hu3DModelShadowSet(lbl_1_bss_3F0.models[12].modelId);
    Hu3DModelShadowSet(lbl_1_bss_3F0.models[13].modelId);
    Hu3DModelShadowSet(lbl_1_bss_3F0.models[14].modelId);
    lbl_1_bss_3F0.player[0].motNo = 1;
    lbl_1_bss_3F0.player[0].speed = 0.0f;
    lbl_1_bss_3F0.player[0].time = 50.0f;
    lbl_1_bss_3F0.player[0].attrReset = HU3D_MOTATTR_LOOP;
    lbl_1_bss_3F0.player[1].motNo = 0;
    lbl_1_bss_3F0.player[1].speed = 1.0f;
    lbl_1_bss_3F0.player[1].time = 0.0f;
    lbl_1_bss_3F0.player[1].attr = HU3D_MOTATTR_LOOP;
    omAddObjEx(lbl_1_bss_3F0.objman, 32730, 0, 0, -1, fn_1_19A4);
    lbl_1_bss_20[0] = lbl_1_bss_20[1] = 0;
    omAddObjEx(lbl_1_bss_3F0.objman, 32730, 0, 0, -1, fn_1_70B0);
    lbl_1_bss_54 = NULL;
    MgSeqModeDelaySet(mode+1, -1);
    MgSeqModeNext();
}

/* asm 593-628, 29 insns. Fade-in hook. */
void fn_1_8C0(s16 mode, s16 frameNo)
{
    if(!WipeCheckEnd()) {
        switch(lbl_1_bss_3F0.mode[0]) {
            case 0:
                fn_1_23A4();
                break;

            case 1:
                fn_1_257C();
                break;

            case 2:
                fn_1_282C();
                break;
        }
    }
    fn_1_202C();
}

/* asm 631-665, 32 insns. Start hook. */
void fn_1_934(s16 mode, s16 frameNo)
{
    lbl_1_bss_3F0.mode[0] = 0;
    lbl_1_bss_3F0.mode[1] = 0;
    MgSeqModeDelaySet(mode+1, -1);
    fn_1_202C();
    if(lbl_1_data_398 < 0) {
        lbl_1_data_398 = HuAudBGMPlay(59);
    }
}

/* asm 668-687, 18 insns. Main hook: runs data_318 by mode. */
void fn_1_9B4(s16 mode, s16 frameNo)
{
    lbl_1_data_318[lbl_1_bss_3F0.mode[0]]();
    fn_1_202C();
}

/* asm 690-713, 22 insns. Finish hook. */
void fn_1_9FC(s16 mode, s16 frameNo)
{
    MgSeqModeDelaySet(mode+1, -1);
    lbl_1_bss_3F0.mode[0] = 0;
    lbl_1_bss_3F0.mode[1] = 0;
    fn_1_202C();
}

/* asm 716-726, 9 insns. Pre-winner hook. */
void fn_1_A54(s16 mode, s16 frameNo)
{
    fn_1_5DF4();
    fn_1_202C();
}

/* asm 729-739, 9 insns. Winner hook. */
void fn_1_A78(s16 mode, s16 frameNo)
{
    fn_1_202C();
    MgSeqModeNext();
}

/* asm 742-757, 13 insns. Fade-out hook. */
void fn_1_A9C(s16 mode, s16 frameNo)
{
    fn_1_202C();
    if(!WipeCheckEnd()) {
        MgSeqModeNext();
    }
}

/* asm 760-762, 1 insns. Close hook. */
void fn_1_AD0(s16 mode, s16 frameNo)
{
}

/* asm 765-954, 166 insns. Unreferenced debug control: pad padNo's buttons nudge bss_44. Its sticks are read and deadzoned but unused. */
void fn_1_AD4(s16 padNo)
{
    s32 btn;
    s32 btnDown;
    s8 stkX;
    s8 stkY;
    s8 subStkX;
    s8 subStkY;

    btn = HuPadBtn[padNo];
    btnDown = HuPadBtnDown[padNo];
    stkX = (s8)HuPadStkX[padNo];
    stkX = (((stkX >= 0) ? stkX : -stkX) < 10) ? 0 : stkX;
    stkY = (s8)HuPadStkY[padNo];
    stkY = (((stkY >= 0) ? stkY : -stkY) < 10) ? 0 : stkY;
    subStkX = (s8)HuPadSubStkX[padNo];
    subStkX = (((subStkX >= 0) ? subStkX : -subStkX) < 8) ? 0 : subStkX;
    subStkY = (s8)HuPadSubStkY[padNo];
    subStkY = (((subStkY >= 0) ? subStkY : -subStkY) < 8) ? 0 : subStkY;
    if(btnDown & PAD_BUTTON_X) {
        lbl_1_bss_44.z += 10.0f;
    }
    if(btnDown & PAD_BUTTON_Y) {
        lbl_1_bss_44.z -= 10.0f;
    }
    if(btnDown & PAD_BUTTON_UP) {
        lbl_1_bss_44.y += 1.0f;
    }
    if(btnDown & PAD_BUTTON_DOWN) {
        lbl_1_bss_44.y -= 1.0f;
    }
    if(btnDown & PAD_BUTTON_LEFT) {
        lbl_1_bss_44.x -= 1.0f;
    }
    if(btnDown & PAD_BUTTON_RIGHT) {
        lbl_1_bss_44.x += 1.0f;
    }
}

/* asm 957-1276, 294 insns. Unreferenced debug readout: both duellists' item-hook positions and bss_44, with fn_1_AD4(2) inlined. */
void fn_1_D6C(void)
{
    HuVecF pos;

    if(lbl_1_bss_3F0.models[12].modelId != 0) {
        Hu3DModelObjPosGet(lbl_1_bss_3F0.models[12].modelId, "test11_tex_we-itemhook-r", &pos);
    }
    print8(8, 144, 1.5f, "POStest");
    print8(8, 156, 1.5f, "X=%.2f", pos.x);
    print8(8, 168, 1.5f, "Y=%.2f", pos.y);
    print8(8, 180, 1.5f, "Z=%.2f", pos.z);
    if(lbl_1_bss_3F0.models[13].modelId != 0) {
        Hu3DModelObjPosGet(lbl_1_bss_3F0.models[13].modelId, "test11_tex_we-itemhook-r", &pos);
    }
    print8(8, 192, 1.5f, "POStest");
    print8(8, 204, 1.5f, "X=%.2f", pos.x);
    print8(8, 216, 1.5f, "Y=%.2f", pos.y);
    print8(8, 228, 1.5f, "Z=%.2f", pos.z);
    fn_1_AD4(2);
    print8(8, 240, 1.5f, "BOM X=%.2f", lbl_1_bss_44.x);
    print8(8, 252, 1.5f, "BOM Y=%.2f", lbl_1_bss_44.y);
    print8(8, 264, 1.5f, "BOM Z=%.2f", lbl_1_bss_44.z);
}

/* asm 1279-1304, 24 insns. Object main: holds model bss_50 at bss_44, raised by bss_28[0]. */
void fn_1_1204(OMOBJ *obj)
{
    Hu3DModelPosSet(lbl_1_bss_50, lbl_1_bss_44.x, lbl_1_bss_44.y+lbl_1_bss_28[0], lbl_1_bss_44.z);
}

/* asm 1307-1600, 262 insns. Unreferenced debug camera on pad padNo. */
void fn_1_1264(s16 padNo)
{
    s32 btn;
    s32 btnDown;
    s8 stkX;
    s8 stkY;
    s8 subStkX;
    s8 subStkY;

    btn = HuPadBtn[padNo];
    btnDown = HuPadBtnDown[padNo];
    stkX = (s8)HuPadStkX[padNo];
    stkX = (((stkX >= 0) ? stkX : -stkX) < 10) ? 0 : stkX;
    stkY = (s8)HuPadStkY[padNo];
    stkY = (((stkY >= 0) ? stkY : -stkY) < 10) ? 0 : stkY;
    subStkX = (s8)HuPadSubStkX[padNo];
    subStkX = (((subStkX >= 0) ? subStkX : -subStkX) < 8) ? 0 : subStkX;
    subStkY = (s8)HuPadSubStkY[padNo];
    subStkY = (((subStkY >= 0) ? subStkY : -subStkY) < 8) ? 0 : subStkY;
    if(btn & PAD_BUTTON_X) {
        CZoom += 20.0f;
    }
    if(btn & PAD_BUTTON_Y) {
        CZoom -= 20.0f;
    }
    if(stkX > 0) {
        Center.x += 10.0f;
    }
    if(stkX < 0) {
        Center.x -= 10.0f;
    }
    if(stkY > 0) {
        Center.y += 10.0f;
    }
    if(stkY < 0) {
        Center.y -= 10.0f;
    }
    if(subStkX > 0) {
        CRot.y += 1.0f;
    }
    if(subStkX < 0) {
        CRot.y -= 1.0f;
    }
    if(subStkY > 0) {
        CRot.x += 1.0f;
    }
    if(subStkY < 0) {
        CRot.x -= 1.0f;
    }
    if(btn & 0x2000) {
        CRot.z += 1.0f;
    }
    if(btn & 0x4000) {
        CRot.z -= 1.0f;
    }
    if(btn & PAD_BUTTON_UP) {
        Center.z += 10.0f;
    }
    if(btn & PAD_BUTTON_DOWN) {
        Center.z -= 10.0f;
    }
}

/* asm 1603-1786, 180 insns. The timer board (model 14, texture scroll "m548time") and models 15-19. */
void fn_1_167C(void)
{
    HU3DMODELID id;
    int i;

    lbl_1_bss_50 = id = lbl_1_bss_3F0.models[14].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_168[0], HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(id, -140.0f, 215.0f, 0.0f);
    Hu3DModelRotSet(id, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(id, 1);
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    lbl_1_bss_3B4 = Hu3DTexScrollCreate(id, "m548time");
    lbl_1_bss_44.x = -lbl_1_bss_384[0][1].y;
    lbl_1_bss_44.y = lbl_1_bss_384[0][1].z;
    lbl_1_bss_44.z = 0.0f;
    lbl_1_bss_38.x = 0.0f;
    lbl_1_bss_38.y = 0.0f;
    lbl_1_bss_38.z = 0.0f;
    for(i=0; i<5; i++) {
        id = (lbl_1_bss_3F0.models+15)[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_168[i+1], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(id, -500.0f+(1000.0f*i), 500.0f, 200.0f);
        Hu3DModelRotSet(id, 0.0f, 0.0f, 0.0f);
        Hu3DModelLayerSet(id, 7);
        Hu3DModelCameraSet(id, 1);
        Hu3DMotionSpeedSet(id, 1.0f);
        Hu3DMotionTimeSet(id, 0.0f);
    }
    fn_1_5014(1);
}

/* asm 1789-1798, 8 insns. */
void fn_1_194C(void)
{
    lbl_1_bss_20[0] = lbl_1_bss_20[1] = 0;
}

/* asm 1801-1816, 14 insns. */
s32 fn_1_196C(void)
{
    return lbl_1_bss_20[lbl_1_bss_3D0.unk6]%32;
}

/* asm 1819-2022, 196 insns. Object main: while a duellist's motion 1 sits on frame 50-51, squash it on a 64-step cycle and bob bss_28[0]. */
void fn_1_19A4(OMOBJ *obj)
{
    int i;
    float scaleY;

    lbl_1_bss_28[0] = 0.0f;
    for(i=0; i<2; i++) {
        if(50.0f == lbl_1_bss_3F0.player[i].time || 51.0f == lbl_1_bss_3F0.player[i].time) {
            if(lbl_1_bss_3F0.player[i].motNo == 1) {
                lbl_1_bss_20[i] = (lbl_1_bss_20[i]+1)%64;
                scaleY = 1.0-(0.01f*sin((M_PI*((lbl_1_bss_20[i]*360)/64))/180.0));
                Hu3DModelScaleSet((lbl_1_bss_3F0.models+12)[i].modelId, 1.0f, scaleY, 1.0f);
                lbl_1_bss_28[0] = -1.0*sin((M_PI*((lbl_1_bss_20[i]*360)/64))/180.0);
            } else {
                lbl_1_bss_20[i] = 0;
                Hu3DModelScaleSet((lbl_1_bss_3F0.models+12)[i].modelId, 1.0f, 1.0f, 1.0f);
            }
        } else {
            lbl_1_bss_20[i] = 0;
            Hu3DModelScaleSet((lbl_1_bss_3F0.models+12)[i].modelId, 1.0f, 1.0f, 1.0f);
        }
    }
}

/* asm 2025-2080, 52 insns. */
void fn_1_1CB4(void)
{
    int i;

    for(i=0; i<2; i++) {
        lbl_1_bss_0[i][0] = 0;
        lbl_1_bss_0[i][1] = 0;
        lbl_1_bss_0[i][2] = (rand8()%10)+30;
        lbl_1_bss_0[i][3] = (rand8()%2)+6;
    }
}
