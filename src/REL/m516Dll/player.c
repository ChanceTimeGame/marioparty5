/*
 * m516dll player.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m516Dll/asm/REL/m516Dll/player.s.
 */

#include "REL/m516Dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0xA0 */ /* float lbl_1_rodata_A0 = 0.0f; */
/* 0xA4 */ /* float lbl_1_rodata_A4 = 1.0f; */
/* 0xA8 */ /* double lbl_1_rodata_A8 = 0.8; */
/* 0xB0 */ /* float lbl_1_rodata_B0 = 40.0f; */
/* 0xB4 */ /* float lbl_1_rodata_B4 = 70.0f; */
/* 0xB8 */ /* double lbl_1_rodata_B8 = 1; */
/* 0xC0 */ /* double lbl_1_rodata_C0 = 180; */
/* 0xC8 */ /* double lbl_1_rodata_C8 = 3.141592653589793; */
/* 0xD0 */ /* double lbl_1_rodata_D0 = 0.01785714365541935; */
/* 0xD8 */ /* double lbl_1_rodata_D8 = 4503601774854144; */
/* 0xE0 */ /* float lbl_1_rodata_E0 = 0.1f; */
/* 0xE4 */ /* float lbl_1_rodata_E4 = 0.3f; */
/* 0xE8 */ /* float lbl_1_rodata_E8 = 0.05f; */
/* 0xF0 */ /* double lbl_1_rodata_F0 = 0.01666666753590107; */
/* 0xF8 */ /* double lbl_1_rodata_F8 = 550; */
/* 0x100 */ /* float lbl_1_rodata_100 = 0.5f; */
/* 0x104 */ /* float lbl_1_rodata_104 = 0.45f; */
/* 0x108 */ /* double lbl_1_rodata_108 = 26.66666805744171; */
/* 0x110 */ /* double lbl_1_rodata_110 = 10; */
/* 0x118 */ /* double lbl_1_rodata_118 = 5.000000260770321; */
/* 0x120 */ /* double lbl_1_rodata_120 = 16.66666753590107; */
/* 0x128 */ /* double lbl_1_rodata_128 = 360; */
/* 0x130 */ /* float lbl_1_rodata_130 = 360.0f; */
/* 0x138 */ /* double lbl_1_rodata_138 = 45; */
/* 0x140 */ /* double lbl_1_rodata_140 = 135; */
/* 0x148 */ /* double lbl_1_rodata_148 = 120; */
/* 0x150 */ /* double lbl_1_rodata_150 = 225; */
/* 0x158 */ /* double lbl_1_rodata_158 = 315; */
/* 0x160 */ /* double lbl_1_rodata_160 = 0.05; */
/* 0x168 */ /* double lbl_1_rodata_168 = 0.98; */
/* 0x170 */ /* double lbl_1_rodata_170 = 0.9166667144745589; */
/* 0x178 */ /* double lbl_1_rodata_178 = 1.6333334185183048; */
/* 0x180 */ /* double lbl_1_rodata_180 = 0.5; */
/* 0x188 */ /* double lbl_1_rodata_188 = 0.1282051282051282; */
/* 0x190 */ /* double lbl_1_rodata_190 = 7.800000000000001; */
/* 0x198 */ /* double lbl_1_rodata_198 = 90; */
/* 0x1A0 */ /* double lbl_1_rodata_1A0 = 0.050505050505050504; */
/* 0x1A8 */ /* double lbl_1_rodata_1A8 = 6.283185307179586; */
/* 0x1B0 */ /* double lbl_1_rodata_1B0 = 1.5; */
/* 0x1B8 */ /* double lbl_1_rodata_1B8 = 19.8; */
/* 0x1C0 */ /* double lbl_1_rodata_1C0 = 0.2; */
/* 0x1C8 */ /* double lbl_1_rodata_1C8 = -1100; */
/* 0x1D0 */ /* double lbl_1_rodata_1D0 = 2200; */
/* 0x1D8 */ /* double lbl_1_rodata_1D8 = 1100; */
/* 0x1E0 */ /* float lbl_1_rodata_1E0 = 350.0f; */
/* 0x1E8 */ /* double lbl_1_rodata_1E8 = 1.666666753590107; */
/* 0x1F0 */ /* float lbl_1_rodata_1F0 = 270.0f; */
/* 0x1F4 */ /* float lbl_1_rodata_1F4 = 90.0f; */
/* 0x1F8 */ /* float lbl_1_rodata_1F8 = 0.6f; */
/* 0x1FC */ /* float lbl_1_rodata_1FC = -100.0f; */
/* 0x200 */ /* float lbl_1_rodata_200 = 0.8f; */
/* 0x208 */ /* double lbl_1_rodata_208 = 60; */
/* 0x210 */ /* double lbl_1_rodata_210 = 1000; */
/* 0x218 */ /* double lbl_1_rodata_218 = 600; */
/* 0x220 */ /* float lbl_1_rodata_220 = -200.0f; */
/* 0x224 */ /* float lbl_1_rodata_224 = 0.4f; */
/* 0x228 */ /* float lbl_1_rodata_228 = 100.0f; */
/* 0x22C */ /* float lbl_1_rodata_22C = 200.0f; */
/* 0x230 */ /* double lbl_1_rodata_230 = -100; */
/* 0x238 */ /* double lbl_1_rodata_238 = 100; */
/* 0x240 */ /* float lbl_1_rodata_240 = -50.0f; */
/* 0x244 */ /* float lbl_1_rodata_244 = 150.0f; */
/* 0x248 */ /* float lbl_1_rodata_248[2] = { 60.0f, 0.0f }; */

/* --- .data --- */
/* 0x98 */ s32 lbl_1_data_98[8] = { 0x008C0000, 0x008C0001, 0x008C0002, 0x008C0006, 0x008C0031, 0x008C0003, 0x008C0004, 0x008C0016 };
/* 0xB8 */ M516_MOTION lbl_1_data_B8[8] = {
    { 0, 0.2f, HU3D_MOTATTR_LOOP },
    { 1, 0.2f, HU3D_MOTATTR_LOOP },
    { 2, 0.2f, HU3D_MOTATTR_LOOP },
    { 3, 0.2f, HU3D_MOTATTR_NONE },
    { 4, 0.2f, HU3D_MOTATTR_NONE },
    { 5, 0.2f, HU3D_MOTATTR_NONE },
    { 6, 0.2f, HU3D_MOTATTR_NONE },
    { 7, 0.2f, HU3D_MOTATTR_LOOP },
};
/* 0x118 */ float lbl_1_data_118[4] = { 0.0f, -0.02f, 0.02f, 0.05f };
/* 0x128 */ s32 lbl_1_data_128[4] = { 0x0000001B, 0x00000012, 0x0000000C, 0x00000006 };

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x28 */ OMOBJ *lbl_1_bss_28[4];

/* --- functions (reference order) --- */
/* 45 insns */
void fn_1_254C(OMOBJMAN *objman)
{
    OMOBJ *obj;
    s32 i;

    omMakeGroupEx(objman, 0, 4);
    for (i = 0; i < 4; i++) {
        obj = lbl_1_bss_28[i] = omAddObjEx(objman, 30, 1, 8, 0, fn_1_2624);
        obj->work[0] = i;
        obj->work[1] = GwPlayerConf[i].grp;
        obj->work[2] = i;
    }
}

/* 9 insns */
void fn_1_2600(void)
{
    CharModelKill(-1);
}

/* 175 insns */
void fn_1_2624(OMOBJ *obj)
{
    M516_PLAYER *work;
    M516_HIT *hit;
    s32 i;
    s32 no;
    s32 slot;
    s32 charNo;
    HU3DMODELID mdlId;
    HU3DMOTID motId;

    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M516_PLAYER), HU_MEMNUM_OVL);
    work = obj->data;
    memset(work, 0, sizeof(M516_PLAYER));
    obj->stat |= OM_STAT_MODELPAUSE;
    work->unk000 = no = obj->work[0];
    work->unk004 = obj->work[1];
    slot = work->unk008 = obj->work[2];
    charNo = GwPlayerConf[no].charNo;
    work->unk00C = charNo;
    fn_1_19E0(no, work->unk004, work->unk00C);
    work->unk028 = GwPlayerConf[no].dif & 3;
    work->unk024 = GwPlayerConf[no].type;
    work->unk034 = 0;
    work->unk038 = 0;
    work->unk03C = 0;
    mdlId = CharModelCreate(charNo, 2);
    obj->mdlId[0] = mdlId;
    Hu3DModelLayerSet(mdlId, 5);
    CharEffectLayerSet(6);
    for (i = 0; i < 8; i++) {
        motId = CharMotionCreate(charNo, lbl_1_data_98[i]);
        obj->mtnId[i] = motId;
    }
    CharMotionDataClose(charNo);
    work->unk010 = -1;
    fn_1_4558(obj, 0);
    obj->trans.x = work->unk04C.x = obj->trans.y = work->unk04C.y = obj->trans.z = work->unk04C.z = 0.0f;
    work->unk058.x = work->unk058.y = work->unk058.z = 0.0f;
    work->unk070 = 0.0f;
    work->unk088 = 0;
    work->unk08C = 0;
    work->unk094 = 1.0f;
    work->unk098 = 1.0f;
    work->unk090 = 0;
    hit = &work->unk09C;
    hit->unk000 = 0;
    hit->unk004 = 0;
    hit->unk008 = no;
    hit->unk00C = 0;
    hit->unk010 = obj;
    hit->unk014 = fn_1_3BBC;
    hit->unk018 = &work->unk04C;
    hit->unk01C = &work->unk058;
    hit->unk020 = work->unk074 = 0.8 * CharModelHeightGet(charNo);
    hit->unk024 = 40.0f;
    fn_1_8D88((M516_ACTOR *)hit);
    work->unk0D0.unk00 = 1;
    work->unk0D0.unk04 = 70.0f;
    work->unk0D0.unk08 = &work->unk064;
    fn_1_796C(&work->unk0D0);
    work->unk040 = 0;
    obj->objFunc = fn_1_28E0;
}

/* 226 insns */
void fn_1_28E0(OMOBJ *obj)
{
    M516_PLAYER *work = obj->data;
    HuVecF pos;
    s32 padNo;
    float stkX;
    float stkY;

    work->unk014 = 0;
    work->unk018 = 0;
    work->unk01C = 0.0f;
    work->unk020 = 0.0f;
    switch (work->unk040) {
        case 0:
            pos = work->unk04C;
            if (fn_1_6DEC(work->unk000, &work->unk04C, &work->unk070)) {
                PSVECSubtract(&work->unk04C, &pos, &work->unk058);
                if (work->unk048 == 0 || PSVECMag(&work->unk058) < 1.0) {
                    fn_1_4558(obj, 0);
                } else {
                    fn_1_4558(obj, 2);
                }
                fn_1_2E7C(obj);
                return;
            }
            work->unk09C.unk000 |= 1;
            work->unk040++;
        case 1:
            if (fn_1_1850() != 2) {
                break;
            }
            work->unk040++;
        case 2:
            if (fn_1_1850() != 2) {
                work->unk040++;
                work->unk044 = 0;
                work->unk07C = 1;
                break;
            }
            if (work->unk024) {
                fn_1_3D40(obj);
                break;
            }
            padNo = GwPlayerConf[work->unk000].padNo;
            stkX = HuPadStkX[padNo];
            stkY = -HuPadStkY[padNo];
            work->unk018 = HuPadBtn[padNo];
            work->unk014 = HuPadBtnDown[padNo];
            work->unk01C = 180.0 * (atan2(stkX, stkY) / 3.141592653589793);
            work->unk020 = (1.0f / 56.0f) * fabs(stkX);
            if (work->unk020 > 1.0f) {
                work->unk020 = 1.0f;
            }
            break;
        case 3:
            if (++work->unk044 < 20) {
                break;
            }
            work->unk040++;
            fn_1_4558(obj, 0);
        case 4:
            if (fn_1_1850() == 3 && fn_1_1940()) {
                work->unk040 = 0;
                obj->objFunc = fn_1_2C68;
            }
            break;
    }
    fn_1_3110(obj);
    fn_1_2F08(obj);
    PSVECAdd(&work->unk04C, &work->unk058, &work->unk04C);
    fn_1_2E7C(obj);
}

/* 133 insns */
void fn_1_2C68(OMOBJ *obj)
{
    M516_PLAYER *work = obj->data;

    work->unk014 = 0;
    work->unk018 = 0;
    work->unk01C = 0.0f;
    work->unk020 = 0.0f;
    work->unk058.x = work->unk058.y = work->unk058.z = 0.0f;
    switch (work->unk040) {
        case 0:
            fn_1_18E0(work->unk000);
            work->unk07C = 0;
            work->unk080 = 0;
            work->unk040++;
        case 1:
            fn_1_2F08(obj);
            if (fn_1_1868()) {
                work->unk040++;
                work->unk044 = 0;
            }
            break;
        case 2:
            fn_1_2F08(obj);
            work->unk070 = fn_1_1D34(work->unk070, 0.0f, 0.1f);
            if (++work->unk044 < 10) {
                break;
            }
            work->unk040++;
            work->unk044 = 0;
            break;
        case 3:
            fn_1_2F08(obj);
            work->unk070 = fn_1_1D34(work->unk070, 0.0f, 0.1f);
            if (++work->unk044 < 20) {
                break;
            }
            if (fn_1_18B0(work->unk000) >= 0) {
                fn_1_4558(obj, 3);
            } else {
                fn_1_4558(obj, 4);
                fn_1_1A20(work->unk000);
            }
            work->unk040++;
            break;
        case 5:
            if (fn_1_4650(obj)) {
                fn_1_1910(work->unk000);
            }
            break;
    }
    fn_1_3110(obj);
    PSVECAdd(&work->unk04C, &work->unk058, &work->unk04C);
    fn_1_2E7C(obj);
}

/* 35 insns */
void fn_1_2E7C(OMOBJ *obj)
{
    M516_PLAYER *work = obj->data;
    s32 pan;

    work->unk048++;
    pan = fn_1_1AF8(&work->unk04C, 1);
    CharModelVoicePanSet(work->unk00C, pan);
    if (work->unk080 != 0 && fn_1_4650(obj)) {
        work->unk080 = 0;
    }
}

/* 130 insns */
void fn_1_2F08(OMOBJ *obj)
{
    M516_PLAYER *work = obj->data;
    s32 motA;
    s32 motB;
    s32 motC;
    s32 stop;
    float spd;
    float lim;
    float rate;

    spd = work->unk020 * work->unk094;
    motA = 0;
    motB = 1;
    motC = 2;
    if (work->unk084) {
        work->unk070 = fn_1_1D34(work->unk070, work->unk01C, 0.3f);
        return;
    }
    stop = work->unk080;
    if (work->unk010 == 6) {
        stop = 0;
    }
    if (spd > 0.05f && work->unk07C == 0 && stop == 0) {
        work->unk080 = 0;
        work->unk070 = fn_1_1D34(work->unk070, work->unk01C, 0.3f);
        work->unk058.x = (1.0f / 60.0f) * (550.0 * (spd * sin(3.141592653589793 * work->unk01C / 180.0)));
        if (fn_1_46BC(obj)) {
            lim = 0.5f;
            if (work->unk010 == motC) {
                lim = 0.45f;
            }
            if (spd > lim) {
                fn_1_4558(obj, motC);
                rate = spd;
            } else {
                fn_1_4558(obj, motB);
                rate = spd / lim;
            }
            Hu3DMotionSpeedSet(obj->mdlId[0], rate);
        }
    } else {
        if (work->unk080 == 0) {
            fn_1_4558(obj, motA);
        }
        work->unk058.x = 0.0f;
    }
    work->unk058.x = work->unk058.x + work->unk078;
}

/* 393 insns */
void fn_1_3110(OMOBJ *obj)
{
    HuVecF pos;
    M516_PLAYER *work = obj->data;
    M516_ACTOR *actor;
    M516_ACTOR *tmp;
    s32 idx;
    float spd;
    float dir;
    float ang;
    float t;

    fn_1_3734(obj);
    work->unk078 = 0.0f;
    spd = (1.0f / 60.0f) * (550.0 * (work->unk020 * sin(M_PI * work->unk01C / 180.0)));
    spd *= work->unk094;
    if (work->unk084 == 0) {
        if (0.0f != work->unk094 && (work->unk014 & PAD_BUTTON_A)) {
            work->unk058.x = spd;
            work->unk058.y = (1.0f / 60.0f) * 1600.0 * work->unk094;
            work->unk084 = 1;
            fn_1_4558(obj, 5);
        } else {
            pos.x = work->unk04C.x;
            pos.y = work->unk04C.y - 10.0;
            pos.z = work->unk04C.z;
            idx = fn_1_89EC(&pos, work->unk09C.unk024);
            if (idx >= 0) {
                actor = tmp = fn_1_8E78(idx);
                if (actor->unk1C != NULL && actor->unk1C->y > 0.0f) {
                    if (work->unk04C.x > actor->unk18->x) {
                        work->unk058.x += (1.0f / 60.0f) * 300.0;
                    } else {
                        work->unk058.x -= (1.0f / 60.0f) * 300.0;
                    }
                    work->unk058.y += (1.0f / 60.0f) * 1000.0;
                    work->unk084 = 1;
                    fn_1_4558(obj, 5);
                    omVibrate(work->unk000, 12, 6, 6);
                }
            }
            while (idx < 0) {
                if (fabs(spd) > (1.0f / 60.0f) * 300.0) {
                    dir = work->unk01C;
                    t = fmodf(dir, 360.0f);
                    ang = t;
                    if (ang < 0.0f) {
                        ang += 360.0f;
                    }
                    if (ang > 45.0 && ang < 135.0) {
                        pos.x += 120.0;
                    }
                    if (ang > 225.0 && ang < 315.0) {
                        pos.x -= 120.0;
                    }
                    idx = fn_1_89EC(&pos, work->unk09C.unk024);
                    if (idx >= 0) {
                        break;
                    }
                }
                work->unk084 = 1;
                if (0.0f != work->unk094) {
                    fn_1_4558(obj, 5);
                }
                break;
            }
            if (idx >= 0) {
                work->unk04C.y = pos.y;
                actor = tmp = fn_1_8E78(idx);
                if (actor->unk1C != NULL) {
                    work->unk078 = actor->unk1C->x;
                }
            }
        }
    } else {
        work->unk058.x += 0.05 * spd;
        work->unk058.x *= 0.98;
        if ((work->unk018 & PAD_BUTTON_A) && work->unk058.y >= 0.0f) {
            work->unk058.y -= (1.0f / 60.0f) * 100.0 * 0.55;
        } else {
            work->unk058.y -= (1.0f / 60.0f) * 100.0 * 0.98;
        }
        pos.x = work->unk04C.x;
        pos.y = work->unk04C.y - 10.0;
        pos.z = work->unk04C.z;
        idx = fn_1_89EC(&pos, work->unk09C.unk024);
        if (work->unk058.y < 0.0f && idx >= 0) {
            work->unk04C.y = pos.y;
            work->unk058.x = work->unk058.y = 0.0f;
            work->unk084 = 0;
            CharModelLandDustCreate(work->unk00C, &work->unk04C);
            if (0.0f != work->unk094) {
                fn_1_4558(obj, 6);
                work->unk080 = 1;
            }
        }
        pos.x = work->unk04C.x;
        pos.y = 10.0 + (work->unk04C.y + work->unk09C.unk020);
        pos.z = work->unk04C.z;
        idx = fn_1_89EC(&pos, work->unk09C.unk024);
        if (work->unk058.y > 0.0f && idx >= 0) {
            actor = tmp = fn_1_8E78(idx);
            if (actor->unk38 == 0) {
                actor->unk38 = 1;
                actor->unk3C = obj;
                actor->unk34 = work->unk000;
            }
            if (work->unk058.y > 0.0f) {
                work->unk058.y = 0.0f;
            }
        }
    }
}

/* 290 insns */
void fn_1_3734(OMOBJ *obj)
{
    HuVecF pos;
    M516_PLAYER *work = obj->data;
    float spd;
    float scale;

    spd = 1.0f;
    scale = 1.0f;
    if (work->unk09C.unk028 != 0) {
        fn_1_4878(work->unk09C.unk030, &pos, 0);
        if (work->unk04C.x > pos.x) {
            work->unk058.x += (1.0f / 60.0f) * 300.0;
        } else {
            work->unk058.x -= (1.0f / 60.0f) * 300.0;
        }
        work->unk058.y += (1.0f / 60.0f) * 1000.0;
        work->unk084 = 1;
        fn_1_4558(obj, 5);
        omVibrate(work->unk000, 12, 6, 6);
    }
    if (work->unk09C.unk02C != 0) {
        if (work->unk088 == 0 && work->unk090 == 0) {
            if (work->unk058.y <= 0.0f) {
                work->unk088 = 1;
                CharFXPlayPan(work->unk00C, 0x202, fn_1_1AF8(&work->unk04C, 1));
            }
            omVibrate(work->unk000, 12, 6, 6);
        }
        work->unk058.x *= 0.5;
    }
    switch (work->unk088) {
        case 0:
            break;
        case 1:
            work->unk088++;
            work->unk08C = 0;
        case 2:
            spd = 0.5f;
            scale = (1.0 / (0.13 * 60.0)) * work->unk08C;
            scale = 1.0 - 0.5 * scale;
            if ((work->unk08C += 1) < 0.13 * 60.0) {
                break;
            }
            work->unk088++;
            work->unk08C = 0;
            break;
        case 3:
            spd = 0.5f;
            scale = 0.5f;
            if ((work->unk08C += 1) < 90.0) {
                break;
            }
            work->unk088++;
            work->unk08C = 0;
            break;
        case 4:
            spd = 0.5f;
            scale = (1.0 / 19.8) * work->unk08C;
            scale = 0.5 * (1.0 + -cos((M_PI * 2.0) * (1.5 * scale)));
            scale = 0.5 + 0.5 * scale;
            if ((work->unk08C += 1) < 19.8) {
                break;
            }
            work->unk088 = 0;
            work->unk090 = 90;
            scale = 1.0f;
            break;
    }
    work->unk094 += 0.2 * (spd - work->unk094);
    work->unk098 = scale;
    work->unk09C.unk020 = work->unk074 * scale;
}

/* 97 insns */
void fn_1_3BBC(OMOBJ *obj)
{
    M516_PLAYER *work = obj->data;
    HU3DMODELID mdlId = obj->mdlId[0];
    float scale;

    if (work->unk04C.x < -1100.0) {
        work->unk04C.x += 2200.0;
    }
    if (work->unk04C.x > 1100.0) {
        work->unk04C.x -= 2200.0;
    }
    Hu3DModelPosSetV(mdlId, &work->unk04C);
    Hu3DModelRotSet(mdlId, 0.0f, work->unk070, 0.0f);
    scale = 1.0 + 0.5 * (1.0 - work->unk098);
    Hu3DModelScaleSet(mdlId, scale, work->unk098, scale);
    if (work->unk090 > 0) {
        if ((work->unk090 -= 1) & 1) {
            Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
        } else {
            Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
        }
    }
    fn_1_8BF0(&work->unk04C, &work->unk064);
}

/* 342 insns */
void fn_1_3D40(OMOBJ *obj)
{
    M516_PLAYER *work = obj->data;
    M516_ACTOR *actor;
    float slope;
    float lean;
    float diff;
    float diff2;
    double t;
    double t2;

    if (work->unk03C != work->unk084) {
        work->unk03C = work->unk084;
        work->unk034 = 0;
    }
    if (work->unk084 != 0) {
        work->unk018 |= PAD_BUTTON_A;
    } else if (work->unk038 > 0) {
        work->unk038--;
        if (work->unk038 == 0) {
            if (((s32)frand() & 3) != 0) {
                work->unk018 |= PAD_BUTTON_A;
            }
        }
    } else {
        slope = fn_1_6E94(work->unk04C.y);
        actor = fn_1_4298(obj, 0.0f, 350.0f);
        if (actor != NULL) {
            if (actor->unk30.i != 0) {
                if (work->unk034 > lbl_1_data_128[work->unk028]) {
                    work->unk018 |= PAD_BUTTON_A;
                }
                if (fabs(slope) < (1.0f / 60.0f) * 100.0) {
                    work->unk02C = 0.0f;
                    work->unk030 = 0.0f;
                } else {
                    lean = slope * lbl_1_data_118[work->unk028];
                    work->unk030 = fabs(lean);
                    if (lean < 0.0f) {
                        work->unk02C = 270.0f;
                    } else {
                        work->unk02C = 90.0f;
                    }
                }
            } else {
                fn_1_43B8(obj, slope, 0.6f);
            }
        } else if (slope >= 0.0f && fn_1_4298(obj, -100.0f, 350.0f) == NULL) {
            work->unk02C = 270.0f;
            work->unk030 = 0.8f;
            diff = fn_1_1E50(work->unk02C, work->unk070);
            t = fabs(diff);
            if (t > 60.0) {
            } else if (work->unk028 == 0) {
                if (work->unk04C.y < 1000.0) {
                    work->unk018 |= PAD_BUTTON_A;
                }
            } else if (work->unk04C.y < 600.0) {
                if (fn_1_4298(obj, -200.0f, 350.0f) != NULL) {
                    work->unk018 |= PAD_BUTTON_A;
                    work->unk030 = 0.4f;
                }
            }
        } else if (slope <= 0.0f && fn_1_4298(obj, 100.0f, 350.0f) == NULL) {
            work->unk02C = 90.0f;
            work->unk030 = 0.8f;
            diff2 = fn_1_1E50(work->unk02C, work->unk070);
            t2 = fabs(diff2);
            if (t2 > 60.0) {
            } else if (work->unk028 == 0) {
                if (work->unk04C.y < 1000.0) {
                    work->unk018 |= PAD_BUTTON_A;
                }
            } else if (work->unk04C.y < 600.0) {
                if (fn_1_4298(obj, 200.0f, 350.0f) != NULL) {
                    work->unk018 |= PAD_BUTTON_A;
                    work->unk030 = 0.4f;
                }
            }
        } else {
            fn_1_43B8(obj, slope, 0.8f);
        }
    }
    work->unk01C = work->unk02C;
    work->unk020 = work->unk030;
    if (work->unk020 > 1.0) {
        work->unk020 = 1.0f;
    }
    if (work->unk018 & PAD_BUTTON_A) {
        work->unk014 |= PAD_BUTTON_A;
    }
    work->unk034++;
}

/* 20 insns */
M516_ACTOR *fn_1_4298(OMOBJ *obj, float dx, float dy)
{
    M516_PLAYER *work = obj->data;

    return fn_1_42E8(obj, dx, dy, work->unk09C.unk024);
}

/* 52 insns */
M516_ACTOR *fn_1_42E8(OMOBJ *obj, float dx, float dy, float range)
{
    M516_PLAYER *work = obj->data;
    HuVecF pos;
    s32 idx;
    M516_ACTOR *actor;

    pos.x = work->unk04C.x + dx;
    pos.y = work->unk04C.y + dy;
    pos.z = work->unk04C.z;
    idx = fn_1_89EC(&pos, range);
    if (idx < 0) {
        return NULL;
    }
    actor = fn_1_8E78(idx);
    if (actor == NULL) {
        return NULL;
    }
    if (actor->unk0C != 0) {
        return NULL;
    }
    return actor;
}

/* 104 insns */
void fn_1_43B8(OMOBJ *obj, float dir, float b1)
{
    M516_PLAYER *work = obj->data;
    float dx;

    dx = dir >= 0.0f ? -100.0 : 100.0;
    if (fn_1_42E8(obj, dx, -50.0f, 150.0f) == NULL) {
        dir = -dir;
        work->unk038 = 12;
    }
    if (dir >= 0.0f) {
        work->unk02C = 270.0f;
        work->unk030 = b1;
    } else {
        work->unk02C = 90.0f;
        work->unk030 = b1;
    }
}

/* 62 insns */
void fn_1_4558(OMOBJ *obj, u32 motNo)
{
    M516_PLAYER *work = obj->data;
    float shift;

    if (work->unk010 != motNo && motNo < 8) {
        if (work->unk010 < 0) {
            shift = 0.0f;
        } else {
            shift = 60.0f * lbl_1_data_B8[motNo].unk04;
        }
        work->unk010 = motNo;
        CharMotionShiftSet(work->unk00C, obj->mtnId[lbl_1_data_B8[motNo].unk00], 0.0f, shift, lbl_1_data_B8[motNo].unk08);
    }
}

/* 27 insns */
BOOL fn_1_4650(OMOBJ *obj)
{
    M516_PLAYER *work = obj->data;

    if (CharMotionEndCheck(work->unk00C) && CharMotionShiftIDGet(work->unk00C) < 0) {
        return TRUE;
    }
    return FALSE;
}

/* 24 insns */
BOOL fn_1_46BC(OMOBJ *obj)
{
    M516_PLAYER *work = obj->data;
    BOOL ret = FALSE;

    if (CharMotionShiftIDGet(work->unk00C) < 0) {
        ret = TRUE;
    }
    return ret;
}

/* 80 insns */
BOOL fn_1_471C(OMOBJ *obj, u32 motNo)
{
    BOOL ret = FALSE;

    if (fn_1_4650(obj)) {
        fn_1_4558(obj, motNo);
        ret = TRUE;
    }
    return ret;
}

/* 7 insns */
s32 fn_1_485C(OMOBJ *obj)
{
    M516_PLAYER *work = obj->data;

    return work->unk000;
}

/* 21 insns */
BOOL fn_1_4878(OMOBJ *obj, HuVecF *pos, float *out)
{
    M516_PLAYER *work = obj->data;

    if (pos != NULL) {
        *pos = work->unk04C;
    }
    if (out != NULL) {
        *out = work->unk070;
    }
    return TRUE;
}

