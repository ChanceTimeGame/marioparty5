/*
 * m534dll -- a 2-vs-2 minigame (MG_TYPE_2VS2, overlay #48): both teams press A
 * for ten seconds to score; the giant hand in the stage then comes down on the
 * team with fewer presses. Written here from the reference assembly; every
 * function is in reference order (do not reorder), and NOTES.md records the
 * CodeWarrior comparison. Line ranges are into
 * build/mp5-asm/m534Dll/asm/REL/m534Dll/m534.s. Shared types and every
 * prototype are in REL/m534Dll.h.
 *
 * _prolog and _epilog are not reproduced: a port overlay is a host shared
 * library whose only export is ObjectSetup.
 */

#include "REL/m534Dll.h"

#include "game/audio.h"
#include "game/flag.h"
#include "game/gamemes.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/wipe.h"

#include "math.h"

/*
 * ObjectSetup copies two function-local HuVecF initializers from
 * .rodata:0x10 { 0, 0, 0 } and .rodata:0x1C { 0, 0, -1 }; write them as locals.
 */

/* --- .data --- */

HuVecF lbl_1_data_0 = { 100.0f, 800.0f, -100.0f };   /* light position */
HuVecF lbl_1_data_C = { 0.3f, -0.8f, 0.3f };         /* light direction */
HuVecF lbl_1_data_18 = { 40.0f, 45.0f, 1000.0f };    /* light rotation x, y and distance */
GXColor lbl_1_data_24 = { 255, 255, 255, 255 };
HuVecF lbl_1_data_28 = { 200.0f, 3000.0f, 100.0f };  /* shadow position */
HuVecF lbl_1_data_34 = { 0.0f, 1.0f, 0.0f };         /* shadow up */
HuVecF lbl_1_data_40 = { 0.0f, 0.0f, 0.0f };         /* shadow target; dtk sizes it 0x10 */

/* --- .bss --- */

MGTIMER *lbl_1_bss_0;
s16 lbl_1_bss_4;                  /* GameMes id, -1 when none */
s16 lbl_1_bss_6;                  /* HuAudBGMPlay id */
s32 lbl_1_bss_8;                  /* stream id, -1 when none */
s16 lbl_1_bss_C;                  /* global light */
s32 lbl_1_bss_10;
s32 lbl_1_bss_14;
OMOBJ *lbl_1_bss_18;              /* omOutView */
OMOBJ *lbl_1_bss_1C;              /* main object; data is M534_MAIN */
OMOBJMAN *lbl_1_bss_20;           /* dtk sizes this 0x8; only the pointer is referenced */

/* asm 61-241, 179 insns. */
void ObjectSetup(void)
{
    Mtx mtx;
    HuVecF unused0 = { 0.0f, 0.0f, 0.0f };
    HuVecF unused1 = { 0.0f, 0.0f, -1.0f };
    HuVecF target;
    HuVecF pos;
    OMOBJMAN *objman;

    lbl_1_bss_8 = -1;
    lbl_1_bss_0 = NULL;
    lbl_1_bss_C = Hu3DGLightCreateV(&lbl_1_data_0, &lbl_1_data_C, &lbl_1_data_24);
    Hu3DGLightInfinitytSet(lbl_1_bss_C);
    Hu3DGLightStaticSet(lbl_1_bss_C, TRUE);
    target.x = target.y = target.z = 0.0f;
    pos.x = pos.z = 0.0f;
    pos.y = lbl_1_data_18.z;
    mtxRot(mtx, lbl_1_data_18.x, lbl_1_data_18.y, 0.0f);
    PSMTXMultVec(mtx, &pos, &pos);
    Hu3DGLightPosAimSetV(lbl_1_bss_C, &pos, &target);
    Hu3DShadowCreate(80.0f, 20.0f, 10000.0f);
    Hu3DShadowPosSet(&lbl_1_data_28, &lbl_1_data_34, &lbl_1_data_40);
    Hu3DShadowColSet(0, 0, 64);
    objman = omInitObjMan(50, 0x2000);
    lbl_1_bss_20 = objman;
    omGameSysInit(objman);
    lbl_1_bss_14 = 0;
    lbl_1_bss_10 = 0;
    lbl_1_bss_6 = lbl_1_bss_4 = -1;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 10.0f, 20000.0f, 1.2f);
    lbl_1_bss_18 = omAddObjEx(objman, 32730, 0, 0, -1, omOutView);
    lbl_1_bss_1C = omAddObjEx(objman, 10, 0, 0, -1, fn_1_36C);
    fn_1_6BDC(objman);
    fn_1_6314(objman);
    fn_1_3360(objman);
    fn_1_2290(objman);
}

/* asm 244-299, 54 insns. Main object init: allocate and clear M534_MAIN, install fn_1_648. */
void fn_1_36C(OMOBJ *obj)
{
    M534_MAIN *work;

    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M534_MAIN), HU_MEMNUM_OVL);
    work = obj->data;
    memset(work, 0, sizeof(M534_MAIN));
    work->mode = 0;
    work->time = 0;
    work->camMode = 0;
    work->camTime = 0;
    work->playMode = 0;
    work->playTime = 0;
    work->resultMode = 0;
    work->resultTime = 0;
    work->flag = 0;
    work->winTeam = 3;
    work->winner[0] = work->winner[1] = work->winner[2] = work->winner[3] = -1;
    work->bits58 = 0;
    work->bits5C = 0;
    obj->objFunc = fn_1_648;
}

/* asm 302-358, 53 insns. Tick the counters; on a system exit request, fade out and close. */
void fn_1_444(OMOBJ *obj)
{
    M534_MAIN *work = obj->data;

    work->time++;
    work->camTime++;
    work->playTime++;
    work->resultTime++;
    if (omSysExitReq && work->mode != 5U) {
        work->mode = 4;
        if (lbl_1_bss_8 != -1) {
            HuAudSStreamFadeOut(lbl_1_bss_8, 1000);
            lbl_1_bss_8 = -1;
        }
        HuAudFadeOut(1000);
        fn_1_518(obj);
    }
}

/* asm 361-446, 76 insns. Advance to the next mode and install its object function. */
void fn_1_518(OMOBJ *obj)
{
    M534_MAIN *work = obj->data;

    if (work->flag == 0) {
        switch (work->mode) {
            case 0:
                WipeCreate(1, 5, 60);
                work->mode = 1;
                work->camTime = 0;
                obj->objFunc = fn_1_19E8(lbl_1_bss_20);
                break;
            case 1:
                work->mode = 2;
                work->playTime = 0;
                obj->objFunc = fn_1_E28;
                break;
            case 2:
                work->mode = 3;
                work->resultTime = 0;
                obj->objFunc = fn_1_1DF4(lbl_1_bss_20, obj);
                break;
            case 3:
            case 4:
                work->flag = 1;
                work->mode = 5;
                obj->objFunc = fn_1_924;
                break;
            case 5:
            default:
                work->mode = 5;
                obj->objFunc = fn_1_C1C;
                break;
        }
        work->time = 0;
    }
}

/* asm 449-650, 183 insns. */
void fn_1_648(OMOBJ *obj)
{
    fn_1_444(obj);
    fn_1_518(obj);
}

/* asm 653-861, 190 insns. Wait for the wipe, then wipe out and move on. */
void fn_1_924(OMOBJ *obj)
{
    M534_MAIN *work = obj->data;

    fn_1_444(obj);
    if (!WipeCheckEnd()) {
        WipeCreate(2, 6, 60);
        work->flag = 0;
        fn_1_518(obj);
    }
}

/* asm 864-1006, 131 insns. Close: kills player/stage/effect/score, omOvlReturnEx. */
void fn_1_C1C(OMOBJ *obj)
{
    fn_1_444(obj);
    if (!WipeCheckEnd()) {
        fn_1_33E8();
        fn_1_2438();
        fn_1_6338();
        fn_1_6C74();
        GameMesClose();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

/* asm 1009-1200, 178 insns. "Start": GameMes, BGM, timer. */
void fn_1_E28(OMOBJ *obj)
{
    M534_MAIN *work = obj->data;

    fn_1_444(obj);
    switch (work->playMode) {
        case 0:
            lbl_1_bss_6 = GameMesCreate(GAMEMES_MES_MG, GAMEMES_MG_TYPE_START);
            lbl_1_bss_8 = HuAudBGMPlay(55);
            work->playMode = 1;
            work->playTime = 0;
            break;
        case 1:
            if (!GameMesStatGet(lbl_1_bss_6) && work->flag == 0) {
                lbl_1_bss_0 = MgTimerCreate(0);
                MgTimerParamSet(lbl_1_bss_0, 600, 0, 0);
                MgTimerModeOnSet(lbl_1_bss_0, 1);
                work->playMode = 2;
                work->playTime = 0;
                obj->objFunc = fn_1_10F0;
            }
            break;
    }
}

/* asm 1203-1373, 157 insns. Main play; timer. */
void fn_1_10F0(OMOBJ *obj)
{
    M534_MAIN *work = obj->data;
    s32 done = FALSE;

    fn_1_444(obj);
    if (MgTimerDoneCheck(lbl_1_bss_0)) {
        done = TRUE;
    }
    if (done) {
        lbl_1_bss_4 = GameMesCreate(GAMEMES_MES_MG, GAMEMES_MG_TYPE_FINISH);
        if (lbl_1_bss_8 != -1) {
            HuAudSStreamFadeOut(lbl_1_bss_8, 100);
            lbl_1_bss_8 = -1;
        }
        work->playMode = 3;
        work->playTime = 0;
        if (work->flag == 0) {
            obj->objFunc = fn_1_1364;
        }
    }
}

/* asm 1376-1599, 204 insns. Finish. */
void fn_1_1364(OMOBJ *obj)
{
    M534_MAIN *work = obj->data;

    if (lbl_1_bss_0 != NULL) {
        MgTimerKill(lbl_1_bss_0);
        lbl_1_bss_0 = NULL;
    }
    fn_1_444(obj);
    if (fn_1_17C8() && work->bits58 == 0x1111) {
        work->playMode = 4;
        work->playTime = 0;
        fn_1_518(obj);
    }
}

/* asm 1602-1609, 6 insns. Called from stage.c. */
u32 fn_1_1694(void)
{
    return ((M534_MAIN *)lbl_1_bss_1C->data)->mode;
}

/* asm 1612-1619, 6 insns. Called from player.c and stage.c. */
u32 fn_1_16AC(void)
{
    return ((M534_MAIN *)lbl_1_bss_1C->data)->camMode;
}

/* asm 1622-1629, 6 insns. */
u32 fn_1_16C4(void)
{
    return ((M534_MAIN *)lbl_1_bss_1C->data)->playMode;
}

/* asm 1632-1639, 6 insns. */
u32 fn_1_16DC(void)
{
    return ((M534_MAIN *)lbl_1_bss_1C->data)->resultMode;
}

/* asm 1642-1649, 6 insns. Unreferenced in every unit. */
void fn_1_16F4(s32 winTeam)
{
    ((M534_MAIN *)lbl_1_bss_1C->data)->winTeam = winTeam;
}

/* asm 1652-1665, 12 insns. */
s32 fn_1_170C(s32 no)
{
    M534_MAIN *work = lbl_1_bss_1C->data;
    return work->winner[no];
}

/* asm 1668-1681, 12 insns. */
void fn_1_173C(s32 no)
{
    ((M534_MAIN *)lbl_1_bss_1C->data)->bits58 |= 1 << ((no & 3) * 4);
}

/* asm 1684-1697, 12 insns. */
void fn_1_176C(s32 no)
{
    ((M534_MAIN *)lbl_1_bss_1C->data)->bits5C |= 1 << ((no & 3) * 4);
}

/* asm 1700-1712, 11 insns. */
BOOL fn_1_179C(void)
{
    return lbl_1_bss_4 != (s16)GAMEMES_ID_NONE;
}

/* asm 1715-1730, 14 insns. */
BOOL fn_1_17C8(void)
{
    return !GameMesStatGet(lbl_1_bss_4);
}

/* asm 1733-1750, 16 insns. */
void fn_1_1800(s32 no, s32 team, s32 charNo)
{
    M534_MAIN *work = lbl_1_bss_1C->data;
    no &= 3;
    work->team[no] = team;
    work->charNo[no] = charNo;
}
