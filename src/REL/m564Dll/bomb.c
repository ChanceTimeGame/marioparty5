/*
 * m564dll bomb.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m564Dll/asm/REL/m564Dll/bomb.s.
 */

#include "REL/m564Dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x188 */ /* float lbl_1_rodata_188 = 0.55f; */
/* 0x18C */ /* float lbl_1_rodata_18C = 0.1f; */
/* 0x190 */ /* float lbl_1_rodata_190 = 130.0f; */
/* 0x194 */ /* float lbl_1_rodata_194 = 0.0f; */
/* 0x198 */ /* float lbl_1_rodata_198 = 2.4f; */
/* 0x19C */ /* float lbl_1_rodata_19C = 100.0f; */
/* 0x1A0 */ /* float lbl_1_rodata_1A0 = 1.0f; */
/* 0x1A8 */ /* double lbl_1_rodata_1A8 = 4503601774854144; */
/* 0x1B0 */ /* float lbl_1_rodata_1B0 = -195.0f; */
/* 0x1B4 */ /* float lbl_1_rodata_1B4 = 45.0f; */
/* 0x1B8 */ /* double lbl_1_rodata_1B8 = 180; */
/* 0x1C0 */ /* double lbl_1_rodata_1C0 = 3.141592653589793; */
/* 0x1C8 */ /* float lbl_1_rodata_1C8 = 440.0f; */
/* 0x1CC */ /* float lbl_1_rodata_1CC = 5.0f; */
/* 0x1D0 */ /* double lbl_1_rodata_1D0 = 90; */
/* 0x1D8 */ /* float lbl_1_rodata_1D8 = 180.0f; */
/* 0x1DC */ /* float lbl_1_rodata_1DC = 360.0f; */
/* 0x1E0 */ /* double lbl_1_rodata_1E0 = 50; */
/* 0x1E8 */ /* float lbl_1_rodata_1E8 = 15.0f; */
/* 0x1EC */ /* float lbl_1_rodata_1EC = 20.0f; */
/* 0x1F0 */ /* float lbl_1_rodata_1F0 = 200.0f; */
/* 0x1F4 */ /* float lbl_1_rodata_1F4 = 400.0f; */
/* 0x1F8 */ /* float lbl_1_rodata_1F8 = 50.0f; */
/* 0x200 */ /* double lbl_1_rodata_200 = 0.10000000149011612; */
/* 0x208 */ /* float lbl_1_rodata_208 = 9999.0f; */
/* 0x20C */ /* float lbl_1_rodata_20C = 120.0f; */
/* 0x210 */ /* float lbl_1_rodata_210 = 40.0f; */
/* 0x214 */ /* float lbl_1_rodata_214 = 70.0f; */
/* 0x218 */ /* float lbl_1_rodata_218 = 90.0f; */
/* 0x220 */ /* double lbl_1_rodata_220 = 200001; */
/* 0x228 */ /* double lbl_1_rodata_228 = 0.5; */
/* 0x230 */ /* double lbl_1_rodata_230 = 3; */
/* 0x238 */ /* float lbl_1_rodata_238 = -1.0f; */
/* 0x23C */ /* float lbl_1_rodata_23C = 0.5f; */
/* 0x240 */ /* double lbl_1_rodata_240 = 124.07691955566406; */
/* 0x248 */ /* float lbl_1_rodata_248 = 170.0f; */
/* 0x250 */ /* double lbl_1_rodata_250 = 550; */
/* 0x258 */ /* float lbl_1_rodata_258 = 18.0f; */
/* 0x25C */ /* float lbl_1_rodata_25C = 36.0f; */
/* 0x260 */ /* float lbl_1_rodata_260 = 19.0f; */
/* 0x268 */ /* double lbl_1_rodata_268 = 650; */

/* --- .data --- */
/* 0x200 */ MGACTOR_PARAM lbl_1_data_200 = { 30.0f, 30.0f, 4, 5, (COL_NARROW_HOOK)fn_1_75A4, 0, 0, (MGACTOR_CORRECT_HOOK)fn_1_7674 };
/* 0x220 */ s32 lbl_1_data_220[3] = { 0x00770011, 0x00770012, 0x00770013 };
/* 0x22C */ HuVecF lbl_1_data_22C = { 0.0f, -10.0f, 0.0f };
/* 0x238 */ /* jumptable_1_data_238: fn_1_76D8's switch */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x1E8 */ M564_BOMB *lbl_1_bss_1E8[15];
/* 0x1E6 */ s16 lbl_1_bss_1E6;
/* 0x1E4 */ s16 lbl_1_bss_1E4;
/* 0x11C */ M564_BLAST lbl_1_bss_11C[10];
/* 0x11A gap_05_0000011A_bss (0x2) -- dtk filler */
/* 0x118 */ s16 lbl_1_bss_118;

/* --- functions (reference order) --- */
/* fn_1_60E8 (bomb, 199 insns): create the 15 bomb objects, called by m564's init hook */
void fn_1_60E8(void)
{
    M564_BOMB *work;
    s32 i;
    s32 j;
    OMOBJ *obj;
    HU3DMOTID motId;

    lbl_1_bss_118 = Hu3DModelCreateData(0x770015);
    Hu3DModelAttrSet(lbl_1_bss_118, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_118, 0x40000002);
    for (i = 0; i < 15; i++) {
        obj = omAddObjEx(objman, (s16)(i + 0x1100), 0, 0, OM_GRP_NONE, (OMOBJFUNC)fn_1_76D8);
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M564_BOMB), HU_MEMNUM_OVL);
        work = obj->data;
        lbl_1_bss_1E8[i] = work;
        memset(work, 0, sizeof(M564_BOMB));
        work->unk010 = i;
        work->unk004 = Hu3DModelCreateData(0x770010);
        for (j = 0; j < 3; j++) {
            motId = Hu3DJointMotion(work->unk004, HuDataSelHeapReadNum(lbl_1_data_220[j], HU_MEMNUM_OVL, HEAP_MODEL));
            work->unk008[j] = motId;
        }
        work->unk00E = -1;
        fn_1_74C4(work, 0);
        Hu3DModelLayerSet(work->unk004, 2);
        Hu3DModelAttrSet(work->unk004, 0x40000001);
        Hu3DModelAttrSet(work->unk004, HU3D_ATTR_DISPOFF);
        Hu3DModelScaleSet(work->unk004, 0.55f, 0.55f, 0.55f);
        work->unk006 = Hu3DModelLink(lbl_1_bss_118);
        Hu3DModelLayerSet(work->unk006, 1);
        Hu3DModelScaleSet(work->unk006, 0.55f, 0.55f, 0.55f);
        Hu3DModelAttrSet(work->unk006, 0x40000002);
        Hu3DModelAttrSet(work->unk006, HU3D_ATTR_DISPOFF);
        work->unk000 = MgActorCreate(&lbl_1_data_200, work->unk004);
        MgActorPauseOn(work->unk000);
        lbl_1_data_200.param++;
        MgActorColAttrSet(work->unk000, 0x40);
        work->unk020 = 0;
        work->unk058 = 0;
        work->unk01A = -1;
    }
    lbl_1_bss_1E4 = 0;
    lbl_1_bss_1E6 = Hu3DModelCreateData(0x770014);
    Hu3DModelAttrSet(lbl_1_bss_1E6, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_1E6, 0x40000002);
    Hu3DModelLayerSet(lbl_1_bss_1E6, 5);
    fn_1_95D4();
    Hu3DLayerHookSet(1, fn_1_64B8);
}

/* fn_1_6404 (bomb, 45 insns): is the field full? (live count at or above the time-scaled cap) */
s32 fn_1_6404(void)
{
    s32 max;
    u32 time;

    time = MgSeqTimerValueGet();
    if (time < 1800) {
        max = 15;
    } else if (time < 2100) {
        max = 13;
    } else if (time < 2400) {
        max = 12;
    } else if (time < 2700) {
        max = 11;
    } else if (time < 3000) {
        max = 10;
    } else if (time < 3300) {
        max = 8;
    } else {
        max = 6;
    }
    return lbl_1_bss_1E4 >= max;
}

/* fn_1_64B8 (bomb, 33 insns): layer-1 hook, keeps each live bomb's shadow under it */
void fn_1_64B8(s16 layerNo)
{
    M564_BOMB *work;
    s32 i;

    for (i = 0; i < 15; i++) {
        work = lbl_1_bss_1E8[i];
        if (work->unk020 != 0) {
            fn_1_6A14(work);
            Hu3DModelPosSet(work->unk006, work->unk040.x, 0.1f, work->unk040.z);
        }
    }
}

/* fn_1_653C (bomb, 199 insns): spawn one bomb in a free slot, if the cap allows */
void fn_1_653C(void)
{
    M564_BOMB *work;
    s32 max;
    u32 time;
    s32 i;

    time = MgSeqTimerValueGet();
    if (time < 1800) {
        max = 15;
    } else if (time < 2100) {
        max = 13;
    } else if (time < 2400) {
        max = 12;
    } else if (time < 2700) {
        max = 11;
    } else if (time < 3000) {
        max = 10;
    } else if (time < 3300) {
        max = 8;
    } else {
        max = 6;
    }
    if (lbl_1_bss_1E4 < max) {
        work = NULL;
        for (i = 0; i < 15; i++) {
            if (lbl_1_bss_1E8[i]->unk020 == 0) {
                work = lbl_1_bss_1E8[i];
                break;
            }
        }
        if (work != NULL) {
            work->unk018 = fn_1_9810();
            if (work->unk018 != -1) {
                fn_1_98AC(work->unk018, work->unk010);
                MgActorPosUpdate(work->unk000, &work->unk040);
                Hu3DModelAttrReset(work->unk004, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(work->unk006, HU3D_ATTR_DISPOFF);
                MgActorPauseOff(work->unk000, &work->unk040);
                MgActorColMaskSet(work->unk000, 2);
                work->unk000->gravity = 130.0f;
                work->unk000->velY = 0.0f;
                fn_1_7430(work);
                work->unk04C.x = 0.0f;
                work->unk04C.z = 0.0f;
                work->unk020 = 1;
                work->unk00E = -1;
                fn_1_74C4(work, 1);
                work->unk022 = (s16)(frandmod(180) + 420);
                work->unk012 = -1;
                work->unk02C = 0;
                work->unk01A = -1;
                work->unk058 = 0;
                if ((s32)frandmod(100) < 20 && (u32)MgSeqTimerValueGet() < 40) {
                    if ((s32)frandmod(100) < 50) {
                        work->unk014 = 1;
                    } else {
                        work->unk014 = 2;
                    }
                    work->unk028 = 2.4f + (s32)frandmod(59) / 100.0f;
                } else {
                    work->unk014 = 0;
                    work->unk028 = 1.0f + (s32)frandmod(200) / 100.0f;
                }
                lbl_1_bss_1E4++;
            }
        }
    }
}

/* fn_1_6858 (bomb, 78 insns): place bomb 0 at (-195, 0, -195) with a long fuse, called by m564's init hook */
void fn_1_6858(void)
{
    M564_BOMB *work;

    work = lbl_1_bss_1E8[0];
    work->unk040.x = -195.0f;
    work->unk040.y = 0.0f;
    work->unk040.z = -195.0f;
    MgActorPosUpdate(work->unk000, &work->unk040);
    Hu3DModelAttrReset(work->unk004, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(work->unk006, HU3D_ATTR_DISPOFF);
    MgActorPauseOff(work->unk000, &work->unk040);
    MgActorColMaskSet(work->unk000, 3);
    work->unk000->gravity = 130.0f;
    work->unk000->velY = 0.0f;
    work->unk000->rotY = 45.0f;
    work->unk024 = 999;
    work->unk020 = 3;
    work->unk00E = -1;
    fn_1_74C4(work, 0);
    work->unk022 = 999;
    work->unk012 = -1;
    work->unk02C = 0;
    work->unk01A = -1;
    lbl_1_bss_1E4++;
}

/* fn_1_6990 (bomb, 33 insns): retire a bomb */
void fn_1_6990(M564_BOMB *work)
{
    Hu3DModelAttrSet(work->unk004, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(work->unk006, HU3D_ATTR_DISPOFF);
    MgActorPauseOn(work->unk000);
    work->unk020 = 0;
    work->unk040.x = work->unk040.y = work->unk040.z = 0.0f;
    lbl_1_bss_1E4--;
}

/* fn_1_6A14 (bomb, 25 insns): current position, from the holder while carried (state 5) */
void fn_1_6A14(M564_BOMB *work)
{
    if (work->unk020 == 5) {
        fn_1_5EA8(work->unk01A, &work->unk040);
        PSVECAdd(&work->unk040, &lbl_1_data_22C, &work->unk040);
    } else {
        MgActorPosGet(work->unk000, &work->unk040);
    }
}

/* fn_1_6A78 (bomb, 35 insns): landed: start chasing, or stop if motion slot 2 */
void fn_1_6A78(M564_BOMB *work)
{
    if (work->unk00E == 2) {
        work->unk020 = 3;
        work->unk024 = 999;
    } else {
        work->unk020 = 2;
        fn_1_74C4(work, 1);
        MgActorColMaskSet(work->unk000, 3);
        if (work->unk014 == 0) {
            fn_1_7430(work);
        } else {
            work->unk016 = fn_1_5FDC(&work->unk040);
        }
    }
}

/* fn_1_6B04 (bomb, 39 insns): fuse countdown */
void fn_1_6B04(M564_BOMB *work)
{
    if (lbl_1_bss_24 != 3 && work->unk022 > 0) {
        work->unk022--;
        if (work->unk022 == 120) {
            if (work->unk020 == 2) {
                work->unk020 = 3;
            }
            work->unk024 = 999;
            fn_1_74C4(work, 2);
        }
        if (work->unk022 == 0) {
            fn_1_7404(work);
        }
    }
}

/* fn_1_6BA0 (bomb, 66 insns): walk toward the target point, switch mode on arrival */
void fn_1_6BA0(M564_BOMB *work)
{
    HuVecF dir;
    float dist;

    dist = fn_1_13F0(&work->unk040, &work->unk04C, &dir);
    work->unk000->rotY = 180.0 * (atan2(dir.x, dir.z) / M_PI);
    work->unk000->vel.z = work->unk028;
    if (dist < 440.0f) {
        fn_1_6A78(work);
    }
}

/* fn_1_6CA8 (bomb, 131 insns): chase a player */
void fn_1_6CA8(M564_BOMB *work)
{
    HuVecF dir;
    float dist;
    float step;

    switch (work->unk014) {
        case 0:
            break;
        case 2:
            work->unk016 = fn_1_5FDC(&work->unk040);
        case 1:
            if (fn_1_5E5C(work->unk016)) {
                fn_1_6A78(work);
                break;
            }
            MgActorPosGet(lbl_1_bss_100[work->unk016]->unk02C->actor, &work->unk04C);
            break;
    }
    dist = fn_1_13F0(&work->unk040, &work->unk04C, &dir);
    if (0.0f == dist) {
        step = 0.0f;
    } else {
        PSVECNormalize(&dir, &dir);
        PSVECScale(&dir, &dir, work->unk028);
        step = PSVECMag(&dir);
    }
    if (step >= dist) {
        work->unk020 = 3;
        work->unk024 = (s16)(frandmod(120) + 60);
        fn_1_74C4(work, 0);
    } else {
        work->unk000->rotY = MgAngleApproach(work->unk000->rotY, 180.0 * (atan2(dir.x, dir.z) / M_PI), 5.0f);
        work->unk000->vel.z = work->unk028;
    }
}

/* fn_1_6EB4 (bomb, 168 insns): carried by a player: follow 50 in front of them */
void fn_1_6EB4(M564_BOMB *work)
{
    HuVecF target;
    HuVecF pos;
    HuVecF dir;
    float rot;
    float playerRot;
    float diff;

    if (fn_1_5E5C(work->unk01A)) {
        work->unk01A = -1;
        fn_1_6A78(work);
        return;
    }
    rot = work->unk000->rotY;
    playerRot = lbl_1_bss_100[work->unk01A]->unk02C->actor->rotY;
    diff = fn_1_1338(rot, playerRot);
    if (fabs(diff) > 90.0) {
        playerRot += 180.0f;
        if (playerRot > 180.0f) {
            playerRot -= 360.0f;
        }
    }
    work->unk000->rotY = MgAngleApproach(rot, playerRot, 5.0f);
    MgActorPosGet(lbl_1_bss_100[work->unk01A]->unk02C->actor, &target);
    MgActorPosGet(work->unk000, &pos);
    playerRot = lbl_1_bss_100[work->unk01A]->unk02C->actor->rotY;
    target.x += 50.0 * sin(M_PI * playerRot / 180.0);
    target.z += 50.0 * cos(M_PI * playerRot / 180.0);
    target.y = pos.y;
    MgVecApproach(&pos, &target, &dir, 15.0f);
    MgActorPosSet(work->unk000, &pos);
}

/* fn_1_7154 (bomb, 47 insns): knocked back */
void fn_1_7154(M564_BOMB *work)
{
    float speed;

    if (work->unk058 != 0) {
        speed = 5.0f;
    } else {
        speed = 20.0f;
    }
    if (0.0f == work->unk01C) {
        work->unk000->vel.z = speed;
    } else {
        work->unk000->vel.z = -speed;
    }
    work->unk02C++;
    if (work->unk058 != 0 && work->unk02C == 10) {
        fn_1_7404(work);
    }
}

/* fn_1_7210 (bomb, 125 insns): explode, rumble nearby players */
void fn_1_7210(M564_BOMB *work, s32 seF)
{
    HuVecF pos;
    float dist;
    s32 i;

    if (work->unk020 != 7) {
        if (work->unk020 == 5) {
            fn_1_5F08(work->unk01A);
        }
        Hu3DModelAttrSet(work->unk004, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(work->unk006, HU3D_ATTR_DISPOFF);
        MgActorPauseOn(work->unk000);
        work->unk012 = Hu3DModelLink(lbl_1_bss_1E6);
        Hu3DModelAttrReset(work->unk012, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(work->unk012, 0x40000002);
        Hu3DModelLayerSet(work->unk012, 5);
        Hu3DModelPosSetV(work->unk012, &work->unk040);
        Hu3DModelScaleSet(work->unk012, 0.55f, 0.55f, 0.55f);
        work->unk034 = work->unk040;
        work->unk020 = 7;
        work->unk026 = 0;
        work->unk022 = 0;
        work->unk01A = -1;
        if (seF) {
            fn_1_14D0(&work->unk040, 0x8D8);
        }
        for (i = 0; i < 4; i++) {
            if (!fn_1_5E5C(i)) {
                MgActorPosGet(lbl_1_bss_100[i]->unk02C->actor, &pos);
                dist = fn_1_13A4(&work->unk034, &pos);
                if (dist < 200.0f) {
                    omVibrate(i, 20, 4, 2);
                } else if (dist < 400.0f) {
                    omVibrate(i, 12, 6, 6);
                }
            }
        }
    }
}

/* 11 insns */
void fn_1_7404(M564_BOMB *work)
{
    fn_1_7210(work, 1);
}

/* 37 insns */
void fn_1_7430(M564_BOMB *work)
{
    int i;

    for (i = 0; i < 10; i++) {
        fn_1_118C(&lbl_1_data_D8, 50.0f, 440.0f, &work->unk04C);
        work->unk04C.y = work->unk040.y;
        if (fn_1_13A4(&work->unk04C, &work->unk040) > 200.0f) {
            break;
        }
    }
}

/* 56 insns */
void fn_1_74C4(M564_BOMB *work, s16 motNo)
{
    if (work->unk00E == motNo) {
        return;
    }
    if (work->unk00E == 2 && motNo == 0) {
        return;
    }
    work->unk00E = motNo;
    Hu3DModelAttrReset(work->unk004, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(work->unk004, HU3D_MOTATTR_LOOP);
    Hu3DMotionSet(work->unk004, work->unk008[motNo]);
    if (motNo == 0) {
        Hu3DMotionTimeSet(work->unk004, (s32)frandmod(50) + 10);
    }
}

/* 52 insns */
int fn_1_75A4(COL_NARROW_PARAM *a, COL_NARROW_PARAM *b)
{
    M564_BOMB *work = lbl_1_bss_1E8[a->paramB - 4];

    if (work->unk01A != -1 && work->unk01A == b->paramB) {
        return 0;
    }
    if (work->unk020 == 6) {
        if (b->paramB < 4) {
            MgPlayerAttrSet(lbl_1_bss_100[b->paramB]->unk02C, MGPLAYER_ATTR_ANGLELOCK | MGPLAYER_ATTR_MOVEOFF);
        }
        fn_1_7210(work, 1);
        return 0;
    }
    return 1;
}

/* 25 insns */
void fn_1_7674(MGACTOR *actorP, int param)
{
    M564_BOMB *work = lbl_1_bss_1E8[actorP->param - 4];

    if (work->unk020 == 6) {
        fn_1_7210(work, 1);
    }
}

/* 794 insns */
void fn_1_76D8(OMOBJ *obj)
{
    M564_BOMB *work = obj->data;

    if (work->unk020 == 0) {
        return;
    }
    fn_1_6A14(work);
    fn_1_6B04(work);
    switch (work->unk020) {
    case 1:
        fn_1_6BA0(work);
        break;
    case 2:
        fn_1_6CA8(work);
        break;
    case 3:
        if (work->unk024-- == 0) {
            fn_1_6A78(work);
        }
        break;
    case 4:
        fn_1_6EB4(work);
        break;
    case 6:
        fn_1_7154(work);
        break;
    case 7:
        work->unk026++;
        if (Hu3DMotionEndCheck(work->unk012)) {
            fn_1_6990(work);
            Hu3DModelKill(work->unk012);
            work->unk012 = -1;
        }
        break;
    case 8:
        work->unk000->rotY = MgAngleApproach(work->unk000->rotY, 0.0f, 15.0f);
        if (fabs(work->unk000->rotY) < 0.1f) {
            fn_1_74C4(work, 0);
        }
        break;
    }
}

/* 106 insns */
s16 fn_1_8340(HuVecF *pos, float angle)
{
    HuVecF dir;
    float best;
    float a;
    float dist;
    int bestNo;
    int i;

    best = 9999.0f;
    bestNo = -1;
    for (i = 0; i < 15; i++) {
        if (lbl_1_bss_1E8[i]->unk020 == 0) {
            continue;
        }
        if (lbl_1_bss_1E8[i]->unk020 > 3) {
            continue;
        }
        dist = fn_1_13F0(pos, &lbl_1_bss_1E8[i]->unk040, &dir);
        if (dist > 120.0f) {
            continue;
        }
        a = (atan2(dir.x, dir.z) / M_PI) * 180.0;
        a = fabs(fn_1_1338(angle, a));
        if (a < 40.0f && dist < best) {
            best = dist;
            bestNo = i;
        }
    }
    return bestNo;
}

/* 28 insns */
s32 fn_1_84E8(HuVecF *a0, HuVecF *a1, float b0)
{
    float dist = fn_1_13A4(a1, a0);

    if (dist < 70.0f + b0) {
        return 1;
    } else {
        return 0;
    }
}

/* 96 insns */
s32 fn_1_8558(HuVecF *pos, float radius, float height)
{
    int i;

    for (i = 0; i < 15; i++) {
        if (lbl_1_bss_1E8[i]->unk020 != 7) {
            continue;
        }
        if (lbl_1_bss_1E8[i]->unk026 > 20) {
            continue;
        }
        if (lbl_1_bss_1E8[i]->unk034.y > 70.0f + (pos->y + height)) {
            continue;
        }
        if (lbl_1_bss_1E8[i]->unk034.y < pos->y - 70.0f) {
            continue;
        }
        if (fn_1_84E8(&lbl_1_bss_1E8[i]->unk034, pos, radius)) {
            return 1;
        }
    }
    return 0;
}

/* fn_1_86D8 bomb 55 insns -- a player picks the bomb up. */
void fn_1_86D8(s16 no, s16 playerNo)
{
    M564_BOMB *bomb = lbl_1_bss_1E8[no];

    bomb->unk020 = 4;
    bomb->unk01A = playerNo;
    fn_1_74C4(bomb, 0);
}

/* fn_1_87B4 bomb 142 insns -- the bomb is carried by a player. */
void fn_1_87B4(s16 no, s16 playerNo)
{
    M564_BOMB *bomb = lbl_1_bss_1E8[no];
    float diff;
    float playerRot;
    float bombRot;

    MgActorPauseOn(bomb->unk000);
    bomb->unk020 = 5;
    bomb->unk01A = playerNo;
    Hu3DModelPosSetV(bomb->unk004, &lbl_1_data_22C);
    playerRot = lbl_1_bss_100[playerNo]->unk02C->actor->rotY;
    bombRot = bomb->unk000->rotY;
    diff = playerRot - bombRot;
    diff = fabs(fn_1_1338(playerRot, bombRot));
    if (diff <= 90.0f) {
        bomb->unk01C = 0.0f;
        Hu3DModelRotSet(bomb->unk004, 0.0f, 0.0f, 0.0f);
    } else {
        bomb->unk01C = 180.0f;
        Hu3DModelRotSet(bomb->unk004, 0.0f, 180.0f, 0.0f);
    }
    fn_1_74C4(bomb, 0);
}

/* fn_1_89EC bomb 221 insns -- the carried bomb is thrown. */
void fn_1_89EC(s16 no)
{
    M564_BOMB *bomb = lbl_1_bss_1E8[no];
    HuVecF pos;
    float rot;

    bomb->unk020 = 6;
    if (bomb->unk058 != 0) {
        bomb->unk000->velY = 20.0f + 20.0f * ((-1.0f + sqrtf(200001.0f)) / 2.0f);
    } else {
        bomb->unk000->velY = 130.0f + 130.0f * ((-1.0f + sqrtf(124.07692f)) / 2.0f);
    }
    rot = lbl_1_bss_100[bomb->unk01A]->unk02C->actor->rotY;
    bomb->unk030 = rot;
    rot += bomb->unk01C;
    if (rot > 180.0f) {
        rot -= 360.0f;
    }
    bomb->unk000->rotY = rot;
    fn_1_5EA8(bomb->unk01A, &pos);
    PSVECAdd(&pos, &lbl_1_data_22C, &pos);
    MgActorPauseOff(bomb->unk000, &pos);
    MgActorColMaskSet(bomb->unk000, 6);
}

/* fn_1_8D60 bomb 35 insns -- is the bomb in state 1, 2 or 3? */
int fn_1_8D60(s16 no)
{
    if (lbl_1_bss_1E8[no]->unk020 == 2) {
        return 1;
    }
    if (lbl_1_bss_1E8[no]->unk020 == 3) {
        return 1;
    }
    if (lbl_1_bss_1E8[no]->unk020 == 1) {
        return 1;
    }
    return 0;
}

/* fn_1_8DEC bomb 55 insns -- time up: every loose bomb goes to state 8. */
void fn_1_8DEC(void)
{
    s32 i;

    for (i = 0; i < 15; i++) {
        if (fn_1_8D60(i)) {
            lbl_1_bss_1E8[i]->unk020 = 8;
        }
    }
}

/* fn_1_8EC8 bomb 41 insns -- no bomb in flight or held? */
int fn_1_8EC8(void)
{
    s32 i;

    for (i = 0; i < 15; i++) {
        if (lbl_1_bss_1E8[i]->unk020 == 6) {
            return 0;
        }
        if (lbl_1_bss_1E8[i]->unk020 == 7) {
            return 0;
        }
        if (lbl_1_bss_1E8[i]->unk020 == 4) {
            return 0;
        }
    }
    return 1;
}

/* fn_1_8F6C bomb 48 insns -- state-8 bombs play motion 2. */
void fn_1_8F6C(void)
{
    M564_BOMB *bomb;
    s32 i;

    for (i = 0; i < 15; i++) {
        if (lbl_1_bss_1E8[i]->unk020 == 8) {
            bomb = lbl_1_bss_1E8[i];
            fn_1_74C4(bomb, 2);
        }
    }
}

/* fn_1_902C bomb 116 insns -- CPU: a point 100 away from nearby live bombs. */
int fn_1_902C(HuVecF *pos, HuVecF *out)
{
    HuVecF dir;
    HuVecF sum;
    s32 i;
    HuVecF *bombPos;
    float dist;

    sum.x = sum.y = sum.z = 0.0f;
    for (i = 0; i < 15; i++) {
        if (lbl_1_bss_1E8[i]->unk020 == 0) {
            continue;
        }
        if (lbl_1_bss_1E8[i]->unk020 == 5) {
            continue;
        }
        if (lbl_1_bss_1E8[i]->unk022 > 120) {
            continue;
        }
        bombPos = &lbl_1_bss_1E8[i]->unk040;
        dist = fn_1_13A4(pos, bombPos);
        if ((dist < 170.0f) ? 1 : 0) {
            PSVECSubtract(pos, &lbl_1_bss_1E8[i]->unk040, &dir);
            dir.y = 0.0f;
            PSVECAdd(&sum, &dir, &sum);
        }
    }
    if (PSVECMag(&sum) < 1.0f) {
        return 0;
    }
    PSVECNormalize(&sum, &sum);
    PSVECScale(&sum, &sum, 100.0f);
    PSVECAdd(pos, &sum, out);
    return 1;
}

/* fn_1_91FC bomb 82 insns -- position of blast pad no on the 550 ring. */
void fn_1_91FC(s32 no, HuVecF *out)
{
    out->x = 550.0 * HuSin(18.0f + 36.0f * no);
    out->z = 550.0 * -HuCos(18.0f + 36.0f * no);
    out->y = 0.0f;
}

/* fn_1_9344 bomb 164 insns -- blast pad object. */
void fn_1_9344(OMOBJ *obj)
{
    M564_BLAST *blast;
    s32 i;
    HuVecF pos;

    for (i = 0; i < 10; i++) {
        blast = &lbl_1_bss_11C[i];
        switch (blast->unk002) {
        case 0:
            break;
        case 1:
            if (Hu3DMotionEndCheck(blast->unk000)) {
                blast->unk002 = 2;
            }
            break;
        case 2:
            if (lbl_1_bss_1E8[blast->unk010]->unk020 == 2 || lbl_1_bss_1E8[blast->unk010]->unk020 == 5) {
                fn_1_91FC(i, &pos);
                fn_1_14D0(&pos, 0x8D7);
                blast->unk002 = 3;
                Hu3DMotionTimeSet(blast->unk000, 19.0f);
                Hu3DMotionStartEndSet(blast->unk000, 19.0f, Hu3DMotionMaxTimeGet(blast->unk000));
            }
            break;
        case 3:
            if (Hu3DMotionEndCheck(blast->unk000)) {
                blast->unk012 = 0;
                blast->unk010 = -1;
                blast->unk002 = 4;
            }
            break;
        case 4:
            if (blast->unk012++ == 45) {
                blast->unk002 = 0;
            }
            break;
        }
    }
}

/* fn_1_95D4 bomb 143 insns -- blast pad init. */
void fn_1_95D4(void)
{
    s32 i;

    for (i = 0; i < 10; i++) {
        lbl_1_bss_11C[i].unk000 = ((HU3DMODELID *)lbl_1_bss_8C)[i + 6];
        lbl_1_bss_11C[i].unk002 = 0;
        lbl_1_bss_11C[i].unk010 = -1;
        lbl_1_bss_11C[i].unk004.x = 650.0 * HuSin(18.0f + 36.0f * i);
        lbl_1_bss_11C[i].unk004.z = 650.0 * -HuCos(18.0f + 36.0f * i);
        lbl_1_bss_11C[i].unk004.y = 0.0f;
        lbl_1_bss_11C[i].unk012 = 0;
        Hu3DMotionSpeedSet(lbl_1_bss_11C[i].unk000, 0.5f);
    }
    omAddObjEx(objman, 0x1200, 0, 0, -1, fn_1_9344);
}

/* fn_1_9810 bomb 39 insns -- a random free blast pad, or -1. */
s16 fn_1_9810(void)
{
    s32 list[10];
    s32 i;
    s32 num;

    num = 0;
    for (i = 0; i < 10; i++) {
        if (lbl_1_bss_11C[i].unk002 == 0) {
            list[num++] = i;
        }
    }
    if (num == 0) {
        return -1;
    }
    return list[frandmod(num)];
}

/* fn_1_98AC bomb 133 insns -- drop bomb bombNo onto blast pad blastNo. */
void fn_1_98AC(s16 blastNo, s16 bombNo)
{
    M564_BLAST *blast = &lbl_1_bss_11C[blastNo];
    HuVecF pos;

    if (blast->unk010 == -1) {
        lbl_1_bss_1E8[bombNo]->unk040 = blast->unk004;
        blast->unk010 = bombNo;
        Hu3DModelAttrReset(blast->unk000, HU3D_MOTATTR_LOOP);
        Hu3DModelAttrReset(blast->unk000, HU3D_MOTATTR_PAUSE);
        Hu3DMotionTimeSet(blast->unk000, 0.0f);
        Hu3DMotionStartEndSet(blast->unk000, 0.0f, 19.0f);
        blast->unk002 = 1;
        fn_1_91FC(blastNo, &pos);
        fn_1_14D0(&pos, 0x8D6);
    }
}

