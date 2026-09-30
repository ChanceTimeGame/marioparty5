/*
 * m534dll players: teams from GwPlayerConf, pressing A (or the CPU timer), and
 * the squash when the hand lands. Functions are in reference order. Line
 * ranges are into build/mp5-asm/m534Dll/asm/REL/m534Dll/player.s.
 *
 * fn_1_2290 copies two int[2] locals from .rodata:0xA0 { 0, 0 } and
 * .rodata:0xA8 { 0, 2 }; fn_1_245C copies a float[4] local from .rodata:0xB0
 * { 6.5, 5.8, 4.8, 4.0 }. Write those as locals.
 */

#include "REL/m534Dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"

#include "math.h"

/* --- .data --- */

u32 lbl_1_data_100[4] = { 0x008C0000, 0x008C0006, 0x008C0044, 0x008C0045 };

M534_MOTION lbl_1_data_110[4] = {
    { 0, 0, 0.2f, 0.0f, -1.0f, HU3D_MOTATTR_LOOP },
    { 1, 0, 0.2f, 0.0f, -1.0f, HU3D_MOTATTR_NONE },
    { 2, 0, 0.2f, 0.0f, -1.0f, HU3D_MOTATTR_LOOP },
    { 3, 0, 0.1f, 0.0f, -1.0f, HU3D_MOTATTR_NONE },
};

HuVecF lbl_1_data_160[4] = {
    { -257.24f, 0.0f, -40.0f },
    { -109.67f, 0.0f, -40.0f },
    { 109.67f, 0.0f, -40.0f },
    { 257.24f, 0.0f, -40.0f },
};

/* --- .bss --- */

s16 lbl_1_bss_30;
OMOBJ *lbl_1_bss_34[4];           /* dtk sizes this 0x14; four slots are referenced */

/* asm 9-127, 106 insns. Called from ObjectSetup: group and player objects. */
void fn_1_2290(OMOBJMAN *objman)
{
    s32 teams[4];
    s32 count[2] = { 0, 0 };
    s32 slot[2] = { 0, 2 };
    OMOBJ *obj;
    s32 i;
    s32 team;
    s32 invalid;

    invalid = FALSE;
    for (i = 0; i < 4; i++) {
        team = GwPlayerConf[i].grp;
        teams[i] = team;
        if (team >= 2) {
            invalid = TRUE;
        } else {
            count[team]++;
        }
    }
    if (count[0] != 2 || count[1] != 2) {
        invalid = TRUE;
    }
    if (invalid) {
        for (i = 0; i < 4; i++) {
            teams[i] = i >> 1;
        }
    }
    omMakeGroupEx(objman, 0, 4);
    lbl_1_bss_30 = -1;
    for (i = 0; i < 4; i++) {
        obj = lbl_1_bss_34[i] = omAddObjEx(objman, 30, 1, 4, 0, fn_1_245C);
        obj->work[0] = i;
        team = teams[i];
        obj->work[1] = team;
        obj->work[2] = slot[team];
        slot[team]++;
    }
}

/* asm 130-140, 9 insns. */
void fn_1_2438(void)
{
    CharModelKill(-1);
}

/* asm 143-343, 195 insns. Player object init. */
void fn_1_245C(OMOBJ *obj)
{
    float comDelay[4] = { 6.5f, 5.8f, 4.8f, 4.0f };
    M534_PLAYER *work;
    char *hook;
    s32 motId;
    HU3DMODELID mdlId;
    s32 slot;
    s32 charNo;
    s32 no;
    s32 i;

    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M534_PLAYER), HU_MEMNUM_OVL);
    work = obj->data;
    memset(work, 0, sizeof(M534_PLAYER));
    obj->stat |= OM_STAT_MODELPAUSE;
    no = obj->work[0];
    work->no = no;
    work->team = obj->work[1];
    slot = obj->work[2];
    work->slot = slot;
    charNo = GwPlayerConf[no].charNo;
    work->charNo = charNo;
    fn_1_1800(no, work->team, work->charNo);
    work->comDelay = comDelay[GwPlayerConf[no].dif & 3];
    work->com = GwPlayerConf[no].type;
    work->comTime = 2.0f + (s32)(frand() & 3);
    obj->mdlId[0] = CharModelCreate(charNo, 2);
    Hu3DModelLayerSet(obj->mdlId[0], 4);
    Hu3DModelShadowSet(obj->mdlId[0]);
    for (i = 0; i < 4; i++) {
        motId = CharMotionCreate(charNo, lbl_1_data_100[i]);
        obj->mtnId[i] = motId;
    }
    CharMotionDataClose(charNo);
    work->motNo = -1;
    fn_1_2F88(obj, 2);
    if (lbl_1_bss_30 < 0) {
        mdlId = lbl_1_bss_30 = Hu3DModelCreateData(0x5C0009);
    } else {
        mdlId = Hu3DModelLink(lbl_1_bss_30);
    }
    hook = CharModelItemHookGet(charNo, 2, 0);
    Hu3DModelHookSet(obj->mdlId[0], hook, mdlId);
    obj->trans.x = work->pos.x = lbl_1_data_160[slot].x;
    obj->trans.y = work->pos.y = lbl_1_data_160[slot].y;
    obj->trans.z = work->pos.z = lbl_1_data_160[slot].z;
    work->rotY = 0.0f;
    work->scaleY = work->scaleXZ = 1.0f;
    work->squashed = 0;
    work->fxPlayed = 0;
    work->pressed = 0;
    work->speed = 1.0f;
    work->mode = 0;
    obj->objFunc = fn_1_2768;
}

/* asm 346-484, 128 insns. */
void fn_1_2768(OMOBJ *obj)
{
    M534_PLAYER *work = obj->data;
    char *hook;
    s32 no;

    work->btnDown = 0;
    work->btn = 0;
    switch (work->mode) {
        case 0:
            if (fn_1_16AC() != 2) {
                break;
            }
            work->btnDown = PAD_BUTTON_A;
            work->mode++;
        case 1:
            if (fn_1_16C4() != 2) {
                break;
            }
            work->mode++;
            work->pressTime = 0;
        case 2:
            if (fn_1_16C4() != 2) {
                work->mode++;
                work->time = 20;
            } else if (work->com) {
                fn_1_2EB8(obj);
            } else {
                no = work->no;
                work->btn = HuPadBtn[GwPlayerConf[no].padNo];
                work->btnDown = HuPadBtnDown[GwPlayerConf[no].padNo];
            }
            break;
        case 3:
            if (--work->time != 0) {
                break;
            }
            work->mode++;
            hook = CharModelItemHookGet(work->charNo, 2, 0);
            CharModelHookDustCreate(work->charNo, hook);
            fn_1_2F88(obj, 0);
        case 4:
            if (fn_1_16C4() == 3 && fn_1_17C8()) {
                work->mode = 0;
                obj->objFunc = fn_1_2968;
            }
            break;
    }
    fn_1_2CB8(obj);
    fn_1_2CB4(obj);
    fn_1_2C50(obj);
    fn_1_2E4C(obj);
}

/* asm 487-687, 186 insns. */
void fn_1_2968(OMOBJ *obj)
{
    M534_PLAYER *work = obj->data;
    float t;
    float limit;

    work->btnDown = 0;
    work->btn = 0;
    switch (work->mode) {
        case 0:
            fn_1_173C(work->no);
            work->mode++;
            break;
        case 1:
            if (fn_1_16DC() != 0) {
                if (fn_1_170C(work->no) < 0) {
                    work->mode = 4;
                    work->time = 8;
                } else {
                    work->mode++;
                }
            }
            break;
        case 2:
            if (fn_1_16DC() == 4) {
                fn_1_2F88(obj, 1);
                work->mode++;
            }
            break;
        case 3:
            if (fn_1_3118(obj)) {
                fn_1_176C(work->no);
            }
            break;
        case 4:
            t = fn_1_4848();
            limit = 0.75f;
            if (t >= limit) {
                t = (1.0 - t) * (1.0 / (1.0 - limit));
                if (work->fxPlayed == 0) {
                    CharFXPlayPan(work->charNo, 514, fn_1_189C(&work->pos));
                    work->fxPlayed = 1;
                }
                if (t < 0.1 && work->squashed == 0) {
                    t = 0.1f;
                    work->squashed = 1;
                    omVibrate(work->no, 40, 12, 0);
                    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_PAUSE);
                    fn_1_176C(work->no);
                }
                if (t < work->scaleY) {
                    work->scaleY = t;
                }
                if (work->scaleY <= 0.1) {
                    if (--work->time < 0) {
                        work->scaleXZ *= 0.8;
                    }
                }
                if (work->scaleXZ < 0.1) {
                    Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
                } else {
                    t = work->scaleY;
                    limit = work->scaleXZ;
                    Hu3DModelScaleSet(obj->mdlId[0], limit, t, limit);
                }
            }
            break;
    }
    fn_1_2CB8(obj);
    fn_1_2CB4(obj);
    fn_1_2C50(obj);
    fn_1_2E4C(obj);
}

/* asm 690-716, 25 insns. */
void fn_1_2C50(OMOBJ *obj)
{
    M534_PLAYER *work = obj->data;

    work->frame++;
    work->pressTime++;
    CharModelVoicePanSet(work->charNo, fn_1_189C(&work->pos));
}

/* asm 719-721, 1 insn. Empty. */
void fn_1_2CB4(OMOBJ *obj)
{
}

/* asm 724-831, 101 insns. */
void fn_1_2CB8(OMOBJ *obj)
{
    M534_PLAYER *work = obj->data;
    float speed;

    if (work->btnDown & PAD_BUTTON_A) {
        fn_1_449C(work->team);
        speed = (1.0f / 60.0f) * work->pressTime;
        if (0.0f == speed) {
            speed = 1.0f;
        }
        work->pressTime = 0;
        speed = ((1.0f / 60.0f) * 10.0) / speed;
        if (speed < 1.0) {
            speed = 1.0f;
        }
        work->speed = speed;
        work->motNo = -1;
        fn_1_2F88(obj, 3);
        work->pressed = 0;
    }
    if (work->motNo == 3) {
        if (fn_1_3118(obj)) {
            fn_1_2F88(obj, 2);
        } else {
            CharMotionSpeedSet(work->charNo, work->speed);
            if (work->pressed == 0) {
                if (CharMotionTimeGet(work->charNo) >= 4.0) {
                    work->pressed = 1;
                    fn_1_43D4(work->slot);
                    fn_1_4114(work->slot);
                }
            }
        }
    }
}

/* asm 834-862, 27 insns. */
void fn_1_2E4C(OMOBJ *obj)
{
    M534_PLAYER *work = obj->data;

    Hu3DModelPosSetV(obj->mdlId[0], &work->pos);
    Hu3DModelRotSet(obj->mdlId[0], 0.0f, work->rotY, 0.0f);
}

/* asm 865-919, 52 insns. CPU press timing. */
void fn_1_2EB8(OMOBJ *obj)
{
    M534_PLAYER *work = obj->data;

    if ((work->comTime -= 1.0) <= 0.0f) {
        work->btnDown |= PAD_BUTTON_A;
        work->comTime = work->comDelay + 2.5 * ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF));
    }
}

/* asm 922-1026, 100 insns. Set a lbl_1_data_110 motion. */
void fn_1_2F88(OMOBJ *obj, u32 motNo)
{
    M534_PLAYER *work = obj->data;
    float shift;

    if (work->motNo != motNo && motNo < 4) {
        if (work->motNo < 0) {
            shift = 0.0f;
        } else {
            shift = 60.0f * lbl_1_data_110[motNo].shift;
        }
        work->motNo = motNo;
        CharMotionShiftSet(work->charNo, obj->mtnId[lbl_1_data_110[motNo].motNo], 60.0f * lbl_1_data_110[motNo].start, shift,
            lbl_1_data_110[motNo].attr);
        if (lbl_1_data_110[motNo].end >= 0.0f) {
            Hu3DMotionShiftStartEndSet(obj->mdlId[0], 60.0f * lbl_1_data_110[motNo].start, 60.0f * lbl_1_data_110[motNo].end);
        }
    }
}

/* asm 1029-1060, 29 insns. */
BOOL fn_1_3118(OMOBJ *obj)
{
    M534_PLAYER *work = obj->data;
    BOOL ret = FALSE;

    if (CharMotionEndCheck(work->charNo) && CharMotionShiftIDGet(work->charNo) < 0) {
        ret = TRUE;
    }
    return ret;
}

/* asm 1063-1186, 117 insns. Unreferenced in every unit. */
BOOL fn_1_318C(OMOBJ *obj, u32 motNo)
{
    BOOL ret = FALSE;

    if (fn_1_3118(obj)) {
        fn_1_2F88(obj, motNo);
        ret = TRUE;
    }
    return ret;
}
