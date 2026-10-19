/*
 * sdroomdll machine.c -- part flags, the machine model set (body/tires/character/hook),
 * the fade layer hook and the pad helpers shared by the room units.
 */

#include "REL/sdroomdll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "math.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_E0 = 5.0f; /* 0xE0 */
static const float lbl_1_rodata_E4 = 0.0f; /* 0xE4 */
/* 0xE8 lbl_1_rodata_E8: fn_1_484C's GXColor initialiser */
static const float lbl_1_rodata_EC = 255.0f; /* 0xEC */
static const float lbl_1_rodata_F0 = -100.0f; /* 0xF0 */
static const float lbl_1_rodata_F4 = 1.0f; /* 0xF4 */
static const double lbl_1_rodata_F8 = 1.2000000476837158; /* 0xF8 */
static const float lbl_1_rodata_100 = 0.5f; /* 0x100 */
static const double lbl_1_rodata_108 = 0.8333333134651184; /* 0x108 */
static const double lbl_1_rodata_110 = 0.5; /* 0x110 */
static const double lbl_1_rodata_118 = 10.0; /* 0x118 */
/* 0x120 lbl_1_rodata_120 = 4503601774854144: int->float conversion constant, compiler-generated */
static const double lbl_1_rodata_128 = 1.0; /* 0x128 */

/* --- functions (reference order), .data placed before its first user --- */
void fn_1_3E8C(s16 type, s16 no)
{
    GwSdCommon.partFlag[type] |= 1 << no;
}

s32 fn_1_3EC0(s16 type, s16 no)
{
    if(type == 4) {
        return 1;
    }
    return GwSdCommon.partFlag[type] & (1 << no);
}

void fn_1_3F00(void)
{
    GWSDCOMMON *sdCommon = &GwSdCommon;
    lbl_1_bss_5C8[0] = -1;
    lbl_1_bss_5C8[1] = -1;
    lbl_1_bss_5C8[2] = -1;
    lbl_1_bss_5C8[3] = -1;
    if(!sdCommon->extCharSelF) {
        lbl_1_bss_5C8[0] &= ~0x100;
        lbl_1_bss_5C8[1] &= ~0x100;
        lbl_1_bss_5C8[2] &= ~0x100;
        lbl_1_bss_5C8[3] &= ~0x100;
    }
    if(!sdCommon->battleEasyWinF || !sdCommon->battleNormalWinF || !sdCommon->battleHardWinF
        || !sdCommon->flagEasyWinF || !sdCommon->flagNormalWinF || !sdCommon->flagHardWinF
        || !sdCommon->rabbitEasyWinF || !sdCommon->rabbitNormalWinF || !sdCommon->rabbitHardWinF) {
        lbl_1_bss_5C8[0] &= ~0x400;
        lbl_1_bss_5C8[1] &= ~0x400;
        lbl_1_bss_5C8[2] &= ~0x400;
        lbl_1_bss_5C8[3] &= ~0x400;
    }
    if((sdCommon->partFlag[0] & 0x7FF) != 0x7FF || (sdCommon->partFlag[1] & 0x7FF) != 0x7FF
        || (sdCommon->partFlag[2] & 0x7FF) != 0x7FF || (sdCommon->partFlag[3] & 0x7FF) != 0x7FF) {
        lbl_1_bss_5C8[3] &= ~0x1800;
    }
}

/* 0x150 */ SDPARTDATA lbl_1_data_150[11] = {
    { 0x001A0017, 0x001A0046, DATANUM(DATA_sd00, 52), 0, { 0, 0, 0 } },
    { 0x001A0018, 0x001A0047, DATANUM(DATA_sd00, 53), 5, { 2, -2, 0 } },
    { 0x001A0019, 0x001A0048, DATANUM(DATA_sd00, 54), 5, { 0, 4, 0 } },
    { 0x001A001A, 0x001A0049, DATANUM(DATA_sd00, 55), 5, { 3, 1, 0 } },
    { 0x001A001B, 0x001A004A, DATANUM(DATA_sd00, 56), 7, { 0, 2, 1 } },
    { 0x001A001C, 0x001A004B, DATANUM(DATA_sd00, 57), 7, { -3, 1, 3 } },
    { 0x001A001D, 0x001A004C, DATANUM(DATA_sd00, 58), 10, { 4, -4, 0 } },
    { 0x001A001E, 0x001A004D, DATANUM(DATA_sd00, 59), 10, { 2, -1, 1 } },
    { 0x001A001F, 0x001A004E, DATANUM(DATA_sd00, 60), 15, { -4, 3, 4 } },
    { 0x001A0020, 0x001A004F, DATANUM(DATA_sd00, 61), 15, { 2, 2, 2 } },
    { 0x001A0021, 0x001A0050, DATANUM(DATA_sd00, 62), 20, { -1, 1, 2 } },
};

/* 0x200 */ SDPARTDATA lbl_1_data_200[11] = {
    { 0x001A0001, 0x001A0030, DATANUM(DATA_sd00, 30), 0, { 0, 0, 0 } },
    { 0x001A0002, 0x001A0031, DATANUM(DATA_sd00, 32), 5, { 3, 3, -1 } },
    { 0x001A0003, 0x001A0032, DATANUM(DATA_sd00, 36), 5, { -3, -3, 0 } },
    { 0x001A0004, 0x001A0033, DATANUM(DATA_sd00, 38), 5, { 0, 1, -4 } },
    { 0x001A0005, 0x001A0034, DATANUM(DATA_sd00, 40), 7, { 0, -1, -2 } },
    { 0x001A0006, 0x001A0035, DATANUM(DATA_sd00, 42), 7, { 4, 4, -1 } },
    { 0x001A0007, 0x001A0036, DATANUM(DATA_sd00, 44), 10, { -4, 4, -1 } },
    { 0x001A0008, 0x001A0037, DATANUM(DATA_sd00, 46), 10, { -1, -2, 3 } },
    { 0x001A0009, 0x001A0038, DATANUM(DATA_sd00, 47), 15, { -100, -100, -100 } },
    { 0x001A000A, 0x001A0039, DATANUM(DATA_sd00, 49), 15, { -1, -1, 2 } },
    { 0x001A000B, 0x001A003A, DATANUM(DATA_sd00, 50), 20, { 0, 1, 1 } },
};

/* 0x2B0 */ SDPARTDATA lbl_1_data_2B0[11] = {
    { 0x001A000C, 0x001A003B, DATANUM(DATA_sdroom, 6), 0, { 0, 0, 0 } },
    { 0x001A000D, 0x001A003C, DATANUM(DATA_sdroom, 7), 5, { 3, 3, -1 } },
    { 0x001A000E, 0x001A003D, DATANUM(DATA_sdroom, 8), 5, { -3, -3, 0 } },
    { 0x001A000F, 0x001A003E, DATANUM(DATA_sdroom, 9), 5, { 0, 1, -3 } },
    { 0x001A0010, 0x001A003F, DATANUM(DATA_sdroom, 10), 7, { -1, -2, -2 } },
    { 0x001A0011, 0x001A0040, DATANUM(DATA_sdroom, 11), 7, { 4, 4, -1 } },
    { 0x001A0012, 0x001A0041, DATANUM(DATA_sdroom, 12), 10, { -4, -4, -1 } },
    { 0x001A0013, 0x001A0042, DATANUM(DATA_sdroom, 13), 10, { 1, 1, -4 } },
    { 0x001A0014, 0x001A0043, DATANUM(DATA_sdroom, 14), 15, { -100, -100, -100 } },
    { 0x001A0015, 0x001A0044, DATANUM(DATA_sdroom, 15), 15, { -2, 2, -1 } },
    { 0x001A0016, 0x001A0045, DATANUM(DATA_sdroom, 16), 20, { 1, 2, -3 } },
};

/* 0x360 */ SDPARTDATA lbl_1_data_360[13] = {
    { 0x001A0022, 0x001A0051, DATANUM(DATA_sd00, 63), 0, { -1, 1, 0 } },
    { 0x001A0023, 0x001A0052, DATANUM(DATA_sd00, 64), 5, { -1, 3, 0 } },
    { 0x001A0024, 0x001A0053, DATANUM(DATA_sd00, 65), 5, { 2, -2, 0 } },
    { 0x001A0025, 0x001A0054, DATANUM(DATA_sd00, 66), 7, { 0, -1, 0 } },
    { 0x001A0026, 0x001A0055, DATANUM(DATA_sd00, 67), 7, { 1, 0, 0 } },
    { 0x001A0027, 0x001A0056, DATANUM(DATA_sd00, 68), 7, { 2, 0, 0 } },
    { 0x001A0028, 0x001A0057, DATANUM(DATA_sd00, 69), 10, { 3, -1, 0 } },
    { 0x001A0029, 0x001A0058, DATANUM(DATA_sd00, 70), 10, { 2, 2, 0 } },
    { 0x001A002A, 0x001A0059, DATANUM(DATA_sd00, 71), 15, { 4, -3, 0 } },
    { 0x001A002B, 0x001A005A, DATANUM(DATA_sd00, 72), 15, { 1, 0, 0 } },
    { 0x001A002C, 0x001A005B, DATANUM(DATA_sd00, 73), 20, { 3, -3, 0 } },
    { 0x001A002D, 0x001A005C, DATANUM(DATA_sd00, 74), 30, { 4, -1, 0 } },
    { 0x001A002E, 0x001A005D, DATANUM(DATA_sd00, 75), 30, { 2, 2, 0 } },
};

/* 0x430 */ SDPARTDATA lbl_1_data_430[11] = {
    { 0x00000000, 0x00000000, 0x00000000, 0, { 0, 0, 0 } },
    { 0x00000001, 0x00000000, 0x00000000, 0, { 0, 0, 0 } },
    { 0x00000002, 0x00000000, 0x00000000, 0, { 0, 0, 0 } },
    { 0x00000003, 0x00000000, 0x00000000, 0, { 0, 0, 0 } },
    { 0x00000004, 0x00000000, 0x00000000, 0, { 0, 0, 0 } },
    { 0x00000005, 0x00000000, 0x00000000, 0, { 0, 0, 0 } },
    { 0x00000006, 0x00000000, 0x00000000, 0, { 0, 0, 0 } },
    { 0x00000007, 0x00000000, 0x00000000, 0, { 0, 0, 0 } },
    { 0x00000008, 0x00000000, 0x00000000, 0, { 0, 0, 0 } },
    { 0x00000009, 0x00000000, 0x00000000, 0, { 0, 0, 0 } },
    { 0x00190060, 0x00000000, 0x00000000, 0, { 0, 0, 0 } },
};
/* 0x4E0 */ SDPARTDATA *lbl_1_data_4E0[5] = { lbl_1_data_150, lbl_1_data_200, lbl_1_data_2B0, lbl_1_data_360, lbl_1_data_430 };

s16 fn_1_414C(s16 type, s16 no)
{
    if(!((1 << no) & lbl_1_bss_5C8[type])) {
        return 1;
    }
    if(fn_1_3EC0(type, no)) {
        return 2;
    }
    if(lbl_1_data_4E0[type][no].point > GwCommon.sdPoint[type]) {
        return 3;
    }
    return 0;
}

void fn_1_4238(s16 evtno)
{
    OMOVLHIS *his;
    if(!WipeCheck()) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        HuAudFadeOut(1000);
    }
    WipeWait();
    HuDataDirClose(DATA_sdd1);
    HuDataDirClose(DATA_sdroom);
    HuDataDirClose(DATA_sd00);
    his = omOvlHisGet(0);
    omOvlHisChg(0, his->ovl, evtno, his->stat);
    omOvlCallEx(DLL_sd00dll, 1, 0, 0);
    while(1) {
        HuPrcVSleep();
    }
}

void fn_1_42E0(SDMACHINEMDL *machine, s16 body, s16 tire, s16 chr, s16 hook)
{
    s16 i;
    machine->partNo[0] = body;
    machine->partNo[1] = tire;
    machine->partNo[2] = chr;
    machine->partNo[3] = (hook == -1) ? 0x40 : hook;
    HuDataDirClose(DATA_sdroom);
    HuDataDirClose(DATA_win);
    if(body != -1) {
        fn_1_51C4(body, &machine->bodyMdl);
        Hu3DModelAttrSet(machine->bodyMdl, HU3D_MOTATTR_PAUSE|HU3D_MOTATTR_SHAPE_PAUSE);
    }
    if(tire != -1) {
        fn_1_521C(tire, machine->tireMdl);
        for(i=0; i<4; i++) {
            if(machine->tireMdl[i] != -1) {
                Hu3DModelAttrSet(machine->tireMdl[i], HU3D_MOTATTR_PAUSE|HU3D_MOTATTR_SHAPE_PAUSE);
            }
        }
    }
    if(chr != -1) {
        fn_1_52E0(chr, &machine->charMdl);
        Hu3DModelAttrSet(machine->charMdl, HU3D_MOTATTR_PAUSE|HU3D_MOTATTR_SHAPE_PAUSE);
    } else {
        machine->charMdl = -1;
    }
    if(hook != -1 && hook != 0x40) {
        fn_1_5338(hook, &machine->hookMdl);
        Hu3DModelAttrSet(machine->hookMdl, HU3D_MOTATTR_PAUSE|HU3D_MOTATTR_SHAPE_PAUSE);
    } else {
        machine->hookMdl = -1;
    }
    if(tire != -1) {
        machine->ofsY = fn_1_5390(tire, machine->bodyMdl, machine->tireMdl, machine->charMdl, machine->hookMdl);
        if(tire == 5) {
            machine->ofsY += 5.0f;
        }
        if(body == 3) {
            machine->ofsY += 5.0f;
        }
    }
    Hu3DModelAttrReset(machine->bodyMdl, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(machine->bodyMdl, HU3D_ATTR_NOCULL);
}

void fn_1_44E4(SDMACHINEMDL *machine, s16 body, s16 tire, s16 chr, s16 hook)
{
    fn_1_42E0(machine, body, tire, chr, hook);
    HuDataDirClose(DATA_sd00);
}

void fn_1_4534(SDMACHINEMDL *machine, float posX, float posY, float posZ)
{
    if(machine->partNo[0] != -1) {
        Hu3DModelPosSet(machine->bodyMdl, posX, posY+machine->ofsY, posZ);
    }
}

void fn_1_4590(SDMACHINEMDL *machine, float rotX, float rotY, float rotZ)
{
    if(machine->partNo[0] != -1) {
        Hu3DModelRotSet(machine->bodyMdl, rotX, rotY, rotZ);
    }
}

void fn_1_45E4(SDMACHINEMDL *machine, float scaleX, float scaleY, float scaleZ)
{
    if(machine->partNo[0] != -1) {
        Hu3DModelScaleSet(machine->bodyMdl, scaleX, scaleY, scaleZ);
    }
}

void fn_1_4638(SDMACHINEMDL *machine, s16 cameraBit)
{
    if(machine->partNo[0] != -1) {
        Hu3DModelCameraSet(machine->bodyMdl, cameraBit);
    }
}

void fn_1_4680(SDMACHINEMDL *machine, s16 layerNo)
{
    if(machine->partNo[0] != -1) {
        Hu3DModelLayerSet(machine->bodyMdl, layerNo);
    }
}

void fn_1_46C4(SDMACHINEMDL *machine, s32 dispF)
{
    if(machine->partNo[0] != -1) {
        if(dispF) {
            Hu3DModelDispOn(machine->bodyMdl);
        } else {
            Hu3DModelDispOff(machine->bodyMdl);
        }
    }
}

void fn_1_4724(SDMACHINEMDL *machine)
{
    s16 i;
    if(machine->partNo[0] != -1) {
        Hu3DModelKill(machine->bodyMdl);
    }
    if(machine->partNo[1] != -1) {
        for(i=0; i<4; i++) {
            if(machine->tireMdl[i] != -1) {
                Hu3DModelKill(machine->tireMdl[i]);
            }
        }
    }
    if(machine->partNo[2] != -1) {
        Hu3DModelKill(machine->charMdl);
    }
    if(machine->partNo[3] != -1
    ) {
        Hu3DModelKill(machine->hookMdl);
    }
    for(i=0; i<4; i++) {
        machine->partNo[i] = -1;
    }
}

void fn_1_480C(SDMACHINEMDL *machine)
{
    s16 i;
    for(i=0; i<4; i++) {
        machine->partNo[i] = -1;
    }
}

void fn_1_484C(s16 layerNo)
{
    HU3DCAMERA *camera = &Hu3DCamera[Hu3DCameraNo];
    GXColor color = { 0, 0, 0, 0 };
    Mtx44 proj;
    Mtx lookAt;
    Vec pos;
    Vec target;
    Vec up;
    float z;
    if(Hu3DCameraNo == 2) {
        C_MTXPerspective(proj, camera->fov, camera->aspect, camera->near, camera->far);
        GXSetProjection(proj, GX_PERSPECTIVE);
        GXSetViewport(camera->viewportX, camera->viewportY, camera->viewportW, camera->viewportH, camera->viewportNear, camera->viewportFar);
        GXSetScissor(camera->scissorX, camera->scissorY, camera->scissorW, camera->scissorH);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        color.a = 255.0f*lbl_1_bss_5B8;
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
        GXSetTevColor(GX_TEVREG0, color);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_A0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetNumTexGens(0);
        GXSetNumTevStages(1);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        GXSetCullMode(GX_CULL_NONE);
        GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
        GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
        GXSetColorUpdate(GX_TRUE);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
        GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
        pos.x = pos.y = pos.z = 0.0f;
        target.x = target.y = 0.0f;
        target.z = -100.0f;
        up.x = up.z = 0.0f;
        up.y = 1.0f;
        C_MTXLookAt(lookAt, &pos, &up, &target);
        GXLoadPosMtxImm(lookAt, GX_PNMTX0);
        z = camera->far-1.0f;
        pos.x = 1.2000000476837158*(z*-sin(camera->fov/2.0f));
        pos.y = 0.8333333134651184*(z*-sin(camera->fov/2.0f));
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(-pos.x, -pos.y, -z);
        GXPosition3f32(pos.x, -pos.y, -z);
        GXPosition3f32(pos.x, pos.y, -z);
        GXPosition3f32(-pos.x, pos.y, -z);
    }
}

void fn_1_4D0C(s16 layerNo)
{
    s16 i;
    lbl_1_bss_5C6++;
    if(lbl_1_bss_5C6 == 1) {
        Hu3DLayerHookSet(layerNo, fn_1_484C);
        lbl_1_bss_5C4 = layerNo;
        lbl_1_bss_5B8 = 0.0f;
        for(i=1; i<=10; i++) {
            lbl_1_bss_5B8 = 0.5*(i/10.0);
            HuPrcVSleep();
        }
    }
}

void fn_1_4E14(void)
{
    s16 i;
    lbl_1_bss_5C6--;
    if(lbl_1_bss_5C6 < 0) {
        lbl_1_bss_5C6 = 0;
    } else if(lbl_1_bss_5C6 == 0) {
        for(i=1; i<=10; i++) {
            lbl_1_bss_5B8 = 0.5*(1.0-(i/10.0));
            HuPrcVSleep();
        }
        Hu3DLayerHookReset(lbl_1_bss_5C4);
    }
}

u16 fn_1_4F24(u16 padBit)
{
    s16 btn;
    s16 i;
    for(i = btn = 0; i<4; i++) {
        if((1 << i) & padBit) {
            btn |= HuPadBtn[i];
        }
        lbl_1_bss_5BC[i] = HuPadBtn[i];
    }
    return btn;
}

u16 fn_1_4FD0(u16 padBit)
{
    s16 btn;
    s16 i;
    for(i = btn = 0; i<4; i++) {
        if((1 << i) & padBit) {
            btn |= HuPadBtnDown[i];
        }
        lbl_1_bss_5BC[i] = HuPadBtnDown[i];
    }
    return btn;
}

u16 fn_1_507C(u16 padBit)
{
    s16 btn;
    s16 i;
    for(i = btn = 0; i<4; i++) {
        if((1 << i) & padBit) {
            btn |= HuPadDStkRep[i];
        }
        lbl_1_bss_5BC[i] = HuPadDStkRep[i];
    }
    return btn;
}

u16 fn_1_5118(u16 padBit)
{
    s16 btn;
    s16 i;
    for(i = btn = 0; i<4; i++) {
        if((1 << i) & padBit) {
            btn |= HuPadBtnRep[i];
        }
        lbl_1_bss_5BC[i] = HuPadBtnRep[i];
    }
    return btn;
}

/* 0x4F4 */ s16 lbl_1_data_4F4[6] = { 11, 11, 11, 13, 10, 0 };
/* 0x500 */ SDTIREDATA lbl_1_data_500[11] = {
    { { DATANUM(DATA_sd00, 30), DATANUM(DATA_sd00, 31), DATANUM(DATA_sd00, 30), DATANUM(DATA_sd00, 31) }, 0, 0, 0, 50.0f, 50.0f, 50.0f, 30.0f, 0.0f, 0.0f, 0 },
    { { DATANUM(DATA_sd00, 32), DATANUM(DATA_sd00, 33), DATANUM(DATA_sd00, 34), DATANUM(DATA_sd00, 35) }, 3, 3, -1, 50.0f, 40.0f, 60.0f, 35.0f, 0.0f, 0.0f, 0 },
    { { DATANUM(DATA_sd00, 36), DATANUM(DATA_sd00, 37), DATANUM(DATA_sd00, 36), DATANUM(DATA_sd00, 37) }, -3, -3, 0, 56.0f, 56.0f, 56.0f, 50.0f, 0.0f, 80.0f, 1 },
    { { DATANUM(DATA_sd00, 38), DATANUM(DATA_sd00, 39), DATANUM(DATA_sd00, 38), DATANUM(DATA_sd00, 39) }, 0, 1, -4, 50.0f, 50.0f, 50.0f, 20.0f, 0.0f, 0.0f, 0 },
    { { DATANUM(DATA_sd00, 40), DATANUM(DATA_sd00, 41), DATANUM(DATA_sd00, 40), DATANUM(DATA_sd00, 41) }, 0, -1, -2, 50.0f, 50.0f, 50.0f, 28.0f, 0.0f, 0.0f, 16 },
    { { DATANUM(DATA_sd00, 42), DATANUM(DATA_sd00, 43), DATANUM(DATA_sd00, 42), DATANUM(DATA_sd00, 43) }, 4, 4, -1, 40.0f, 40.0f, 40.0f, 40.0f, 0.0f, 110.0f, 1 },
    { { DATANUM(DATA_sd00, 44), DATANUM(DATA_sd00, 45), DATANUM(DATA_sd00, 44), DATANUM(DATA_sd00, 45) }, -4, -4, -1, 56.0f, 56.0f, 56.0f, 50.0f, 0.0f, 80.0f, 1 },
    { { DATANUM(DATA_sd00, 46), DATANUM(DATA_sd00, 46), DATANUM(DATA_sd00, 46), DATANUM(DATA_sd00, 46) }, -1, -2, 3, 30.0f, 90.0f, 90.0f, 80.0f, 0.0f, 80.0f, 82 },
    { { DATANUM(DATA_sd00, 47), DATANUM(DATA_sd00, 48), DATANUM(DATA_sd00, 47), DATANUM(DATA_sd00, 48) }, 0, 0, 0, 50.0f, 50.0f, 50.0f, 40.0f, 0.0f, 0.0f, 128 },
    { { DATANUM(DATA_sd00, 49), DATANUM(DATA_sd00, 49), DATANUM(DATA_sd00, 49), DATANUM(DATA_sd00, 49) }, -1, -1, 2, 70.0f, 50.0f, 50.0f, 100.0f, 0.0f, 100.0f, 82 },
    { { DATANUM(DATA_sd00, 50), DATANUM(DATA_sd00, 51), DATANUM(DATA_sd00, 50), DATANUM(DATA_sd00, 51) }, 0, 1, 1, 50.0f, 50.0f, 50.0f, 28.0f, 0.0f, 0.0f, 32 },
};
/* 0x768 */ SDBODYDATA lbl_1_data_768[11] = {
    { DATANUM(DATA_sd00, 52), 0, 0, 0, 120.0f, 180.0f, 2 },
    { DATANUM(DATA_sd00, 53), 2, -2, 0, 130.0f, 220.0f, 4 },
    { DATANUM(DATA_sd00, 54), 0, 4, 0, 125.0f, 180.0f, 1 },
    { DATANUM(DATA_sd00, 55), 3, 1, 0, 90.0f, 240.0f, 2 },
    { DATANUM(DATA_sd00, 56), 0, 2, 1, 90.0f, 180.0f, 1 },
    { DATANUM(DATA_sd00, 57), -3, 1, 3, 120.0f, 170.0f, 2 },
    { DATANUM(DATA_sd00, 58), 4, -4, 0, 90.0f, 160.0f, 2 },
    { DATANUM(DATA_sd00, 59), 2, -1, 1, 90.0f, 200.0f, 2 },
    { DATANUM(DATA_sd00, 60), -4, 3, 4, 80.0f, 180.0f, 2 },
    { DATANUM(DATA_sd00, 61), 2, 2, 2, 90.0f, 185.0f, 4 },
    { DATANUM(DATA_sd00, 62), -1, 1, 2, 80.0f, 190.0f, 2 },
};

void fn_1_51C4(s32 bodyNo, HU3DMODELID *modelId)
{
    *modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_768[bodyNo].dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
}

void fn_1_521C(s32 tireNo, HU3DMODELID *modelId)
{
    s32 i;
    s32 flag = lbl_1_data_500[tireNo].unk34;
    s32 type = flag & 0xF;
    for(i=0; i<4; i++) {
        modelId[i] = -1;
        if(type == 1) {
            if(i >= 2) {
                continue;
            }
        } else if(type == 2) {
            if(i >= 1) {
                continue;
            }
        }
        modelId[i] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_500[tireNo].dataNum[i], HU_MEMNUM_OVL, HEAP_MODEL));
    }
}

/* 0x89C */ SDCHARDATA lbl_1_data_89C[13] = {
    { DATANUM(DATA_sd00, 63), DATANUM(DATA_sd00, 76), 0, -1, 1, 5, 24 },
    { DATANUM(DATA_sd00, 64), DATANUM(DATA_sd00, 77), 3, -1, 1, 9, 6 },
    { DATANUM(DATA_sd00, 65), DATANUM(DATA_sd00, 78), -2, 2, 1, 3, 1 },
    { DATANUM(DATA_sd00, 66), DATANUM(DATA_sd00, 79), -1, 0, 1, 4, 30 },
    { DATANUM(DATA_sd00, 67), DATANUM(DATA_sd00, 80), 0, 1, 2, 4, 18 },
    { DATANUM(DATA_sd00, 68), HU_DATANUM_NONE, 0, 2, 1, 2, 1 },
    { DATANUM(DATA_sd00, 69), HU_DATANUM_NONE, -1, 3, 1, 1, 1 },
    { DATANUM(DATA_sd00, 70), DATANUM(DATA_sd00, 81), 2, 2, 1, 3, 40 },
    { DATANUM(DATA_sd00, 71), DATANUM(DATA_sd00, 82), -3, 4, 1, 2, 60 },
    { DATANUM(DATA_sd00, 72), DATANUM(DATA_sd00, 83), 0, 1, 1, 4, 18 },
    { DATANUM(DATA_sd00, 73), DATANUM(DATA_sd00, 84), -3, 4, 1, 1, 60 },
    { DATANUM(DATA_sd00, 74), HU_DATANUM_NONE, -3, 4, 1, 1, 1 },
    { DATANUM(DATA_sd00, 75), DATANUM(DATA_sd00, 85), -2, 2, 1, 4, 30 },
};
/* 0xA08 */ s32 lbl_1_data_A08[328] = { 1, 5, 5, 0x45160000, 0, 0x41F00000, 0, 0, 0x42C80000, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 8, 0x44E10000, 0, 0x41F00000, 0, 0, 0x42C80000, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 2, 3, 3, 0x44D20000, 0x42700000, 0x42200000, 0x43C80000, 0, 0x42C80000, 0, 0, 0, 64, 25, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0x43340000, 0, 0x41F00000, 0x43480000, 0x42B40000, 0x42C80000, 0, 0, 0, 64, 25, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0x45160000, 0, 0x41F00000, 0, 0, 0x44160000, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 6, 6, 0x45610000, 0, 0x428C0000, 0, 0, 0x42C80000, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0x41F00000, 0, 0, 0x42C80000, 0, 0, 0, 0, 0, 30, 0, 0, 0, 0, 0, 0, 0, 3, 15, 0x45610000, 0, 0x41F00000, 0, 0, 0x42C80000, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 2, 4, 0x45340000, 0, 0x41F00000, 0x43C80000, 0, 0x42C80000, 0, 0, 0, 64, 25, 0, 0, 0, 0, 0, 0, 0, 0, 7, 4, 0x43960000, 0, 0x41F00000, 0x43960000, 0x42700000, 0x42C80000, 0, 0, 0, 64, 25, 0, 0, 0, 0, 0, 20, 0, 0, 2, 3, 0x45340000, 0, 0x41F00000, 0x44160000, 0, 0x42C80000, 0, 0, 0, 64, 25, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 0x45340000, 0, 0x42200000, 0, 0, 0x42C80000, 0, 0, 0, 8, 0, 0, 0, 0, 12, 0, 0, 0, 1, 5, 5, 0x42DC0000, 0x42700000, 0x42200000, 0x43C80000, 0, 0x42C80000, 0, 0, 0, 64, 25, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 3, 3, -1, 0, -1, -3, -3, 0, 0, -1, 0, 1, -3, 0, -1, -1, -2, -2, 0, -1, 4, 4, -1, 0, -1, -4, -4, -1, 0, -1, 1, 1, -4, 0, -1, 0, 0, 0, 0, -1, -2, 2, -1, 0, -1, 1, 2, -3, 1 };

void fn_1_52E0(s32 charNo, HU3DMODELID *modelId)
{
    *modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_89C[charNo].dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
}

/* 0xF28 */ u32 lbl_1_data_F28[12] = { DATANUM(DATA_sd00, 18), DATANUM(DATA_sd00, 19), DATANUM(DATA_sd00, 20), DATANUM(DATA_sd00, 21), DATANUM(DATA_sd00, 22), DATANUM(DATA_sd00, 23), DATANUM(DATA_sd00, 24), DATANUM(DATA_sd00, 25), DATANUM(DATA_sd00, 26), DATANUM(DATA_sd00, 27), DATANUM(DATA_sd00, 28), DATANUM(DATA_sd00, 29) };

void fn_1_5338(s32 hookNo, HU3DMODELID *modelId)
{
    *modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_F28[hookNo], HU_MEMNUM_OVL, HEAP_MODEL));
}

/* 0x101C */ char *lbl_1_data_101C[17] = {
    "itemhook_a",
    "itemhook_b",
    "itemhook_e",
    "itemhook_f",
    "itemhook_m",
    "itemhook_n",
    "itemhook_gf",
    "itemhook_v",
    "itemhook_w",
    "itemhook_x",
    "itemhook_w2",
    "itemhook_x2",
    "itemhook_z",
    "itemhook_t1",
    "itemhook_t2",
    "itemhook_t3",
    "itemhook_t4"
};

float fn_1_5390(s32 tireNo, HU3DMODELID bodyMdl, HU3DMODELID *tireMdl, HU3DMODELID charMdl, HU3DMODELID hookMdl)
{
    s32 i;
    s32 flag;
    s32 type;
    float ofsY = 0.0f;
    if(bodyMdl == -1) {
        return ofsY;
    }
    flag = lbl_1_data_500[tireNo].unk34;
    type = flag & 0xF;
    for(i=0; i<4; i++) {
        if(tireMdl[i] == -1) {
            continue;
        }
        if(type == 0) {
            Hu3DModelHookSet(bodyMdl, lbl_1_data_101C[i], tireMdl[i]);
            ofsY = lbl_1_data_500[tireNo].unk1C;
        } else if(type == 1) {
            if(i < 2) {
                Hu3DModelHookSet(bodyMdl, lbl_1_data_101C[i+4], tireMdl[i]);
                ofsY = lbl_1_data_500[tireNo].unk1C;
            }
        } else if(i < 1) {
            Hu3DModelHookSet(bodyMdl, lbl_1_data_101C[7], tireMdl[i]);
            ofsY = lbl_1_data_500[tireNo].unk1C+lbl_1_data_500[tireNo].unk20;
        }
    }
    if(charMdl != -1) {
        Hu3DModelHookSet(bodyMdl, lbl_1_data_101C[6], charMdl);
    }
    if(hookMdl != -1) {
        Hu3DModelHookSet(bodyMdl, lbl_1_data_101C[12], hookMdl);
    }
    return ofsY;
}
