/*
 * sd00dll machine.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/sd00dll/asm/REL/sd00dll/machine.s.
 */

#include "REL/sd00dll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "math.h"
#include "game/esprite.h"
#include "humath.h"
#include "string.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x518 lbl_1_rodata_518 (0xC): 0x461C4000 0x461C4000 0x461C4000 -- an aggregate initialiser, write it as a local */
/* 0x524 lbl_1_rodata_524 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_530 = 0.0f; /* 0x530 */
static const float lbl_1_rodata_534 = 20.0f; /* 0x534 */
static const float lbl_1_rodata_538 = -20.0f; /* 0x538 */
static const float lbl_1_rodata_53C = 1.5f; /* 0x53C */
static const float lbl_1_rodata_540 = 1.0f; /* 0x540 */
static const float lbl_1_rodata_544 = 0.4f; /* 0x544 */
static const float lbl_1_rodata_548 = 2.0f; /* 0x548 */
static const float lbl_1_rodata_54C = 100.0f; /* 0x54C */
/* 0x550 lbl_1_rodata_550 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_55C = 0.5f; /* 0x55C */
static const double lbl_1_rodata_560 = 180.0; /* 0x560 */
static const double lbl_1_rodata_568 = 3.141592653589793; /* 0x568 */
static const float lbl_1_rodata_570 = 0.6f; /* 0x570 */
static const float lbl_1_rodata_574 = 32.0f; /* 0x574 */
static const float lbl_1_rodata_578 = 316.0f; /* 0x578 */
static const float lbl_1_rodata_57C = 28.0f; /* 0x57C */
static const float lbl_1_rodata_580 = 56.0f; /* 0x580 */
static const float lbl_1_rodata_584 = 0.25f; /* 0x584 */
static const float lbl_1_rodata_588 = 288.0f; /* 0x588 */
static const float lbl_1_rodata_58C = 240.0f; /* 0x58C */
/* 0x590 lbl_1_rodata_590 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_598 = 360.0f; /* 0x598 */
/* 0x59C lbl_1_rodata_59C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_5A8 = 2.5f; /* 0x5A8 */
static const float lbl_1_rodata_5AC = 0.1f; /* 0x5AC */
static const double lbl_1_rodata_5B0 = 288.0; /* 0x5B0 */
static const float lbl_1_rodata_5B8 = 64.0f; /* 0x5B8 */
static const double lbl_1_rodata_5C0 = 2400.0; /* 0x5C0 */
static const double lbl_1_rodata_5C8 = 360.0; /* 0x5C8 */
static const float lbl_1_rodata_5D0 = 3540.0f; /* 0x5D0 */
static const float lbl_1_rodata_5D4 = 72.0f; /* 0x5D4 */
/* 0x5D8 lbl_1_rodata_5D8 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x5E4 lbl_1_rodata_5E4 (0x30): 0x00000001 0x00000000 0x00000000 0x00000000 0x00000001 0x00000001 0x00000001 0x00000000 0x00000000 0x00000001 0x00000001 0x00000001 -- an aggregate initialiser, write it as a local */
/* 0x614 lbl_1_rodata_614 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_620 = 0.8f; /* 0x620 */
static const float lbl_1_rodata_624 = 10.0f; /* 0x624 */
static const float lbl_1_rodata_628 = 127.0f; /* 0x628 */
static const float lbl_1_rodata_62C = 0.75f; /* 0x62C */
/* 0x630 lbl_1_rodata_630 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x63C lbl_1_rodata_63C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x648 lbl_1_rodata_648 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x654 lbl_1_rodata_654 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x660 lbl_1_rodata_660 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x66C lbl_1_rodata_66C (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_678 = 555.55554f; /* 0x678 */
static const float lbl_1_rodata_67C = 144.0f; /* 0x67C */
static const float lbl_1_rodata_680 = 576.0f; /* 0x680 */
static const float lbl_1_rodata_684 = 480.0f; /* 0x684 */
static const float lbl_1_rodata_688 = -1.0f; /* 0x688 */
static const float lbl_1_rodata_68C = 96.0f; /* 0x68C */
static const float lbl_1_rodata_690 = 63.0f; /* 0x690 */
static const float lbl_1_rodata_694 = 8400.0f; /* 0x694 */
static const float lbl_1_rodata_698 = 5.0f; /* 0x698 (+4 bytes: section tail alignment) */

extern SDBODYDATA sdMachineBodyTbl[11];
extern SDGUNDATA sdMachineGunTbl[13];
extern s32 lbl_1_data_DB4[11][5];
extern char *sdMachineTireHookTbl[3];
static SDBULLETPARAM sdBulletParam[13];
static float machineYOfsTbl[11];

static void MapSprCreate(void);
static void MapSprKill(void);
static HuVecF ScoreSprPosGet(HuVecF pos);
static void SdMachinePartcleHook(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx);
static void SdImpactSet(s32 seNo, HuVecF pos, float vol, s32 a3, float a4);

/* --- functions (reference order), .data placed before its first user --- */
/* 147 insns */
void SdMachineParamSet(SDMACHINE *machine, s32 tireNo, s32 bodyNo, s32 partNo3, s32 gunNo)
{
    machine->unk3C8 = sdMachineTireTbl[tireNo].unk10 + 5 + lbl_1_data_DB4[partNo3][1];
    machine->unk3CC = sdMachineTireTbl[tireNo].unk14 + 5 + sdMachineBodyTbl[bodyNo].unk4 + lbl_1_data_DB4[partNo3][2] + sdMachineGunTbl[gunNo].unk8;
    machine->unk3D0 = sdMachineTireTbl[tireNo].unk18 + 5 + lbl_1_data_DB4[partNo3][3];
    machine->unk3D4 = sdMachineBodyTbl[bodyNo].unkC + 4 + sdMachineGunTbl[gunNo].unkC;
    machine->unk3D8 = sdMachineBodyTbl[bodyNo].unk8 + 5;
    machine->unk3C8 = (machine->unk3C8 > 8) ? 8 : ((machine->unk3C8 < 1) ? 1 : machine->unk3C8);
    machine->unk3CC = (machine->unk3CC > 8) ? 8 : ((machine->unk3CC < 1) ? 1 : machine->unk3CC);
    machine->unk3D0 = (machine->unk3D0 > 8) ? 8 : ((machine->unk3D0 < 1) ? 1 : machine->unk3D0);
    machine->unk3D4 = (machine->unk3D4 > 8) ? 8 : ((machine->unk3D4 < 1) ? 1 : machine->unk3D4);
    machine->unk3D8 = (machine->unk3D8 > 8) ? 8 : ((machine->unk3D8 < 1) ? 1 : machine->unk3D8);
}

/* 0x108 */ static u32 effectFileTbl[12] = { DATANUM(DATA_sd00, 140), DATANUM(DATA_sd00, 143), DATANUM(DATA_sd00, 146), DATANUM(DATA_sd00, 139), DATANUM(DATA_sd00, 140), DATANUM(DATA_sd00, 141), DATANUM(DATA_sd00, 142), DATANUM(DATA_sd00, 144), DATANUM(DATA_sd00, 145), DATANUM(DATA_sd00, 147), DATANUM(DATA_sd00, 139), DATANUM(DATA_sd00, 148) };
/* 0x138 */ static s32 randomTireTbl[7] = { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0xA };
/* 0x154 */ s32 lbl_1_data_154[9] = { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x9, 0xA };

/* 1339 insns */
void SdMachineCreate(SDMACHINE *machine)
{
    Mtx hookMtx;
    Mtx tireMtx;
    HuVecF ofs;
    s32 tireNo;
    s32 partNo3;
    s32 type;
    s32 i;
    SDMACHINEEXHAUST *exhaust;
    SDGUN *gun;
    s32 j;
    SDBULLET *bullet;
    float radius;
    float shadowScale;
    SdMachineBodyCreate(machine->bodyNo, &machine->bodyMdl);
    SdMachineTireCreate(machine->tireNo, machine->tireMdl);
    SdMachineGunCreate(machine->gunNo, &machine->gunMdl);
    SdMachineCharCreate(machine->charNo, &machine->charMdl);
    SdMachineHookSet(machine->tireNo, machine->bodyMdl, machine->tireMdl, machine->gunMdl, machine->charMdl);
    machine->enemy = &sys->machine[machine->playerNo ^ 1];
    tireNo = machine->tireNo;
    if(tireNo == 8) {
        if(rand8() % 100 < 30) {
            tireNo = 0;
        } else {
            tireNo = randomTireTbl[rand8() % 7];
        }
    }
    partNo3 = machine->unk3C0;
    if(partNo3 == 8) {
        if(rand8() % 100 < 25) {
            partNo3 = 0;
        } else {
            partNo3 = lbl_1_data_154[rand8() % 9];
        }
    }
    SdMachineParamSet(machine, tireNo, machine->bodyNo, partNo3, machine->gunNo);
    machine->unkE4 = machine->unk3D8 * 4;
    machine->unk360 = sdMachineTireTbl[machine->tireNo].unk20;
    machine->unk364 = sdMachineTireTbl[machine->tireNo].unk24;
    machine->unk368 = sdMachineTireTbl[machine->tireNo].unk34;
    machine->unk39C = lbl_1_data_DB4[machine->unk3C0][4];
    if(machine->tireNo == 8) {
        if(tireNo == 4) {
            machine->unk368 = 16;
        }
        if(tireNo == 10) {
            machine->unk368 = 32;
        }
    }
    if(machine->unk3C0 == 8 && partNo3 == 10) {
        machine->unk39C = 1;
    }
    type = machine->unk368 & 0xF;
    machine->unk358 = sdMachineBodyTbl[machine->bodyNo].unk10;
    machine->unk354 = sdMachineTireTbl[machine->tireNo].unk1C;
    if(type == 2) {
        machine->unk354 -= machineYOfsTbl[machine->bodyNo];
    }
    machine->unk35C = sdMachineBodyTbl[machine->bodyNo].unk14;
    machine->unk208 = sdMachineBodyTbl[machine->bodyNo].unk18;
    machine->gunNum = sdMachineGunTbl[machine->gunNo].unk10;
    machine->bulletNum = sdMachineGunTbl[machine->gunNo].unk14;
    machine->unk20C = sdMachineGunTbl[machine->gunNo].unk18;
    Hu3DModelCameraSet(machine->bodyMdl, 3);
    Hu3DModelLayerSet(machine->bodyMdl, 1);
    Hu3DModelAttrSet(machine->bodyMdl, HU3D_MOTATTR_LOOP | HU3D_MOTATTR_SHAPE_LOOP);
    if(machine->bodyNo == 6 || machine->bodyNo == 4 || machine->bodyNo == 1 || machine->bodyNo == 7 || machine->bodyNo == 0) {
        Hu3DModelAttrReset(machine->bodyMdl, HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_SHAPE_PAUSE);
        Hu3DMotionSpeedSet(machine->bodyMdl, 0.0f);
        Hu3DMotionShapeSpeedSet(machine->bodyMdl, 0.0f);
    }
    machine->unk36C[0] = machine->unk36C[1] = machine->unk36C[2] = machine->unk36C[3] = (HuVecF){ 10000.0f, 10000.0f, 10000.0f };
    machine->unk33C = HuMemDirectMallocNum(HEAP_HEAP, machine->unk208 * sizeof(SDMACHINEEXHAUST), HU_MEMNUM_OVL);
    memset(machine->unk33C, 0, machine->unk208 * sizeof(SDMACHINEEXHAUST));
    machine->unk340 = HuMemDirectMallocNum(HEAP_HEAP, 0x110, HU_MEMNUM_OVL);
    memset(machine->unk340, 0, 0x110);
    for(i = 0; i < machine->unk208; i++) {
        exhaust = &machine->unk33C[i];
        Hu3DModelObjPosGet(machine->bodyMdl, sdMachineHookTbl[i + 8], &exhaust->unk4);
        PSVECSubtract(&exhaust->unk4, &machine->pos, &exhaust->unk4);
    }
    for(i = 0; i < 4; i++) {
        machine->unk170[i] = 0.0f;
        if(type == 0) {
            machine->unk294[i] = Hu3DModelObjPtrGet(machine->tireMdl[i], sdMachineTireHookTbl[i % 2]);
            Hu3DModelObjMtxGet(machine->bodyMdl, sdMachineHookTbl[i], hookMtx);
            Hu3DModelObjMtxGet(machine->tireMdl[i], sdMachineTireHookTbl[i % 2], tireMtx);
            if(machine->tireNo == 6) {
                Hu3DModelAttrSet(machine->tireMdl[i], HU3D_MOTATTR_SHAPE_LOOP);
            }
        } else if(type == 1) {
            if(i >= 2) {
                continue;
            }
            Hu3DModelAttrSet(machine->tireMdl[i], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_SHAPE_LOOP);
            Hu3DMotionShapeSpeedSet(machine->tireMdl[i], 0.0f);
            Hu3DMotionSpeedSet(machine->tireMdl[i], 0.0f);
            Hu3DModelObjMtxGet(machine->bodyMdl, sdMachineHookTbl[i + 4], hookMtx);
            if(machine->tireNo != 5) {
                Hu3DModelObjMtxGet(machine->tireMdl[i], sdMachineTireHookTbl[i % 2], tireMtx);
            } else {
                PSMTXIdentity(tireMtx);
            }
        } else {
            if(i >= 1) {
                continue;
            }
            Hu3DModelAttrSet(machine->tireMdl[i], HU3D_MOTATTR_SHAPE_LOOP);
            Hu3DModelObjMtxGet(machine->bodyMdl, sdMachineHookTbl[7], hookMtx);
            Hu3DModelObjMtxGet(machine->tireMdl[i], sdMachineTireHookTbl[2], tireMtx);
        }
        Hu3DModelCameraSet(machine->tireMdl[i], 3);
        Hu3DModelLayerSet(machine->tireMdl[i], 1);
        if(machine->tireNo == 9) {
            Hu3DModelAttrSet(machine->tireMdl[i], HU3D_MOTATTR_LOOP);
        }
        PSMTXConcat(hookMtx, tireMtx, hookMtx);
        machine->unk36C[i] = (HuVecF){ hookMtx[0][3], hookMtx[1][3], hookMtx[2][3] };
        if(machine->unk36C[i].x < 20.0f && machine->unk36C[i].x > -20.0f) {
            if(i % 2) {
                machine->unk36C[i].x = -20.0f;
            } else {
                machine->unk36C[i].x = 20.0f;
            }
        }
    }
    if(type == 0) {
        machine->unk36C[1].x -= sdMachineTireTbl[machine->tireNo].unk28;
        machine->unk36C[0].x = -machine->unk36C[1].x;
        machine->unk36C[2].x = machine->unk36C[0].x;
        machine->unk36C[3].x = machine->unk36C[1].x;
        machine->unk36C[0].y = machine->unk36C[1].y;
        machine->unk36C[2].y = machine->unk36C[3].y;
    } else if(type == 1) {
        machine->unk36C[0].y = machine->unk36C[1].y;
        machine->unk36C[2] = machine->unk36C[0];
        machine->unk36C[3] = machine->unk36C[1];
        machine->unk36C[0].x += sdMachineTireTbl[machine->tireNo].unk28;
        machine->unk36C[0].z = sdMachineTireTbl[machine->tireNo].unk30;
        machine->unk36C[1].x -= sdMachineTireTbl[machine->tireNo].unk28;
        machine->unk36C[1].z = sdMachineTireTbl[machine->tireNo].unk30;
        machine->unk36C[2].x += sdMachineTireTbl[machine->tireNo].unk28;
        machine->unk36C[2].z = -sdMachineTireTbl[machine->tireNo].unk30;
        machine->unk36C[3].x -= sdMachineTireTbl[machine->tireNo].unk28;
        machine->unk36C[3].z = -sdMachineTireTbl[machine->tireNo].unk30;
    } else if(type == 2) {
        machine->unk36C[1] = machine->unk36C[2] = machine->unk36C[3] = machine->unk36C[0];
        machine->unk36C[0].x = sdMachineTireTbl[machine->tireNo].unk28;
        machine->unk36C[0].z = sdMachineTireTbl[machine->tireNo].unk30;
        machine->unk36C[1].x = -sdMachineTireTbl[machine->tireNo].unk28;
        machine->unk36C[1].z = sdMachineTireTbl[machine->tireNo].unk30;
        machine->unk36C[2].x = sdMachineTireTbl[machine->tireNo].unk28;
        machine->unk36C[2].z = -sdMachineTireTbl[machine->tireNo].unk30;
        machine->unk36C[3].x = -sdMachineTireTbl[machine->tireNo].unk28;
        machine->unk36C[3].z = -sdMachineTireTbl[machine->tireNo].unk30;
    }
    ofs = machine->unk36C[0];
    ofs.y = 0.0f;
    radius = PSVECMag(&ofs);
    if(radius > machine->unk358) {
        machine->unk358 = radius;
    }
    Hu3DModelObjMtxGet(machine->bodyMdl, sdMachineHookTbl[6], hookMtx);
    Hu3DModelAttrSet(machine->gunMdl, HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_SHAPE_PAUSE);
    Hu3DModelLayerSet(machine->gunMdl, 1);
    Hu3DModelCameraSet(machine->gunMdl, 3);
    if(machine->gunNo == 10 || machine->gunNo == 4) {
        Hu3DModelAttrReset(machine->gunMdl, HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrSet(machine->gunMdl, HU3D_MOTATTR_LOOP);
    }
    machine->unk3AC = -1;
    Hu3DModelCameraSet(machine->charMdl, 3);
    Hu3DModelLayerSet(machine->charMdl, 1);
    machine->gun = HuMemDirectMallocNum(HEAP_HEAP, machine->gunNum * sizeof(SDGUN), HU_MEMNUM_OVL);
    memset(machine->gun, 0, machine->gunNum * sizeof(SDGUN));
    for(i = 0; i < machine->gunNum; i++) {
        gun = &machine->gun[i];
        if(machine->gunNo != 11) {
            Hu3DModelObjMtxGet(machine->gunMdl, sdMachineHookTbl[i + 13], tireMtx);
        } else {
            PSMTXIdentity(tireMtx);
        }
        PSMTXConcat(hookMtx, tireMtx, gun->mtx);
        gun->bullet = HuMemDirectMallocNum(HEAP_HEAP, machine->bulletNum * sizeof(SDBULLET), HU_MEMNUM_OVL);
        memset(gun->bullet, 0, machine->bulletNum * sizeof(SDBULLET));
        for(j = 0; j < machine->bulletNum; j++) {
            bullet = &gun->bullet[j];
            bullet->mdlId[0] = bullet->mdlId[1] = bullet->mdlId[2] = -1;
            bullet->mdlId[3] = bullet->mdlId[4] = -1;
            bullet->machine = machine;
            bullet->gun = gun;
            bullet->param = &sdBulletParam[machine->gunNo];
            if(machine->gunNo == 6 || machine->gunNo == 11) {
                continue;
            }
            if(sdMachineGunTbl[machine->gunNo].unk4 != HU_DATANUM_NONE) {
                if(machine->gunNo == 4 || machine->gunNo == 1) {
                    if(i == 0 && j == 0) {
                        bullet->mdlId[0] = Hu3DModelCreate(HuDataSelHeapReadNum(sdMachineGunTbl[machine->gunNo].unk4, HU_MEMNUM_OVL, HEAP_MODEL));
                    }
                } else {
                    bullet->mdlId[0] = Hu3DModelCreate(HuDataSelHeapReadNum(sdMachineGunTbl[machine->gunNo].unk4, HU_MEMNUM_OVL, HEAP_MODEL));
                }
                if(bullet->mdlId[0] != -1) {
                    Hu3DModelCameraSet(bullet->mdlId[0], 3);
                    Hu3DModelLayerSet(bullet->mdlId[0], 3);
                    Hu3DModelAttrSet(bullet->mdlId[0], HU3D_ATTR_DISPOFF);
                }
                if(machine->gunNo == 2 || machine->gunNo == 12) {
                    Hu3DModelAttrSet(bullet->mdlId[0], HU3D_MOTATTR_LOOP);
                    bullet->mdlId[2] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sd00, 108), HU_MEMNUM_OVL, HEAP_MODEL));
                    Hu3DModelHookSet(bullet->mdlId[0], "itemhook_c", bullet->mdlId[2]);
                    Hu3DModelAttrSet(bullet->mdlId[2], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(bullet->mdlId[2], HU3D_MOTATTR_LOOP);
                    Hu3DModelLayerSet(bullet->mdlId[2], 3);
                    Hu3DModelCameraSet(bullet->mdlId[2], 3);
                    if(machine->gunNo == 2) {
                        Hu3DModelScaleSet(bullet->mdlId[2], 1.5f, 1.5f, 1.5f);
                        bullet->mdlId[3] = Hu3DJointMotion(bullet->mdlId[0], HuDataSelHeapReadNum(DATANUM(DATA_sd00, 86), HU_MEMNUM_OVL, HEAP_MODEL));
                        bullet->mdlId[4] = Hu3DJointMotion(bullet->mdlId[0], HuDataSelHeapReadNum(DATANUM(DATA_sd00, 87), HU_MEMNUM_OVL, HEAP_MODEL));
                    } else {
                        Hu3DModelScaleSet(bullet->mdlId[2], 1.0f, 1.0f, 1.0f);
                        bullet->mdlId[3] = Hu3DJointMotion(bullet->mdlId[0], HuDataSelHeapReadNum(DATANUM(DATA_sd00, 88), HU_MEMNUM_OVL, HEAP_MODEL));
                        bullet->mdlId[4] = Hu3DJointMotion(bullet->mdlId[0], HuDataSelHeapReadNum(DATANUM(DATA_sd00, 89), HU_MEMNUM_OVL, HEAP_MODEL));
                    }
                    Hu3DMotionSet(bullet->mdlId[0], bullet->mdlId[3]);
                }
            }
            if(machine->gunNo != 7) {
                bullet->mdlId[1] = Hu3DModelLink(sys->unk1E4[4]);
                Hu3DModelShadowSet(bullet->mdlId[1]);
                Hu3DModelCameraSet(bullet->mdlId[1], 3);
                Hu3DModelScaleSet(bullet->mdlId[1], 0.4f, 0.4f, 0.4f);
                Hu3DModelLayerSet(bullet->mdlId[1], 3);
                Hu3DModelAttrSet(bullet->mdlId[1], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(bullet->mdlId[1], HU3D_ATTR_MOTION_OFF);
            }
        }
    }
    shadowScale = (2.0f * machine->unk358) / 100.0f;
    machine->unk3B4 = Hu3DModelLink(sys->unk1E4[4]);
    Hu3DModelShadowSet(machine->unk3B4);
    Hu3DModelScaleSet(machine->unk3B4, shadowScale, 1.0f, shadowScale);
    Hu3DModelLayerSet(machine->unk3B4, 3);
    Hu3DModelCameraSet(machine->unk3B4, 3);
    Hu3DModelAttrReset(machine->unk3B4, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(machine->unk3B4, HU3D_ATTR_MOTION_OFF);
    if(sys->unk1E4[5] == -1) {
        if(machine->gunNo == 4 || machine->enemy->gunNo == 4 || machine->gunNo == 1 || machine->enemy->gunNo == 1) {
            sys->unk1E4[5] = Hu3DHookFuncCreate(SdBulletDraw);
            Hu3DModelCameraSet(sys->unk1E4[5], 3);
            Hu3DModelLayerSet(sys->unk1E4[5], 3);
        }
    } else if(machine->gunNo != 4 && machine->enemy->gunNo != 4 && machine->gunNo != 1 && machine->enemy->gunNo != 1) {
        Hu3DModelKill(sys->unk1E4[5]);
        sys->unk1E4[5] = -1;
    }
    Hu3DData[machine->bodyMdl].pos.y = machine->unk354;
    SdMachineFxStart(machine);
}

/* 0x184 */ static s32 configPartTbl[13][5] = { { 0x8, 0x8, 0x8, 0x8, 0xA }, { 0x8, 0x8, 0x8, 0x8, 0xA }, { 0x2, 0x4, 0x9, 0x6, 0xB }, { 0x6, 0x9, 0x3, 0x1, 0x1 }, { 0x3, 0x1, 0x6, 0x9, 0x0 }, { 0x9, 0x7, 0x5, 0x3, 0x2 }, { 0x2, 0x6, 0x5, 0x5, 0x4 }, { 0x7, 0x5, 0x4, 0x7, 0x8 }, { 0x4, 0x1, 0x2, 0x4, 0x3 }, { 0x5, 0x1, 0x3, 0x2, 0x6 }, { 0x1, 0x2, 0x7, 0x3, 0x5 }, { 0x0, 0x0, 0x0, 0x0, 0x7 }, { 0x1, 0x2, 0x6, 0x1, 0x9 } };
/* 0x288 */ static s32 engineSeIdTbl[11] = { 0x533, 0x533, 0x533, 0x533, 0x533, 0x535, 0x539, 0x539, 0x533, 0x537, 0x533 };
/* 0x2B4 */ s32 lbl_1_data_2B4[11] = { 0x525, 0x525, 0x531, 0x525, 0x0, 0x527, 0x531, 0x0, 0x52D, 0x0, 0x527 };
/* 0x2E0 */ static s32 gunSeIdTbl[13] = { 0x53B, 0x53D, 0x53F, 0x541, 0x543, 0x545, 0x547, 0x549, 0x54B, 0x54D, 0x54F, 0x551, 0x553 };
/* 0x314 */ static s32 impactSeIdTbl[13] = { 0x555, 0x555, 0x559, 0x557, 0x555, 0x555, 0x0, 0x555, 0x559, 0x557, 0x55B, 0x0, 0x559 };
/* 0x348 */ static s32 playerSeIdTbl[12][6] = { 0x1FF, 0x1F9, 0x1F8, 0x200, 0x1F8, 0x1FA, 0x1EB, 0x1E5, 0x1E4, 0x1EC, 0x1E4, 0x1E6, 0x263, 0x25D, 0x25C, 0x264, 0x25C, 0x25E, 0x2B3, 0x2AD, 0x2AC, 0x2B4, 0x2AC, 0x2AE, 0x28B, 0x285, 0x284, 0x28C, 0x284, 0x286, 0x1C3, 0x1BD, 0x1BC, 0x1C4, 0x1BC, 0x1BE, 0x29F, 0x299, 0x298, 0x2A0, 0x298, 0x29A, 0x1D7, 0x1D1, 0x1D0, 0x1D8, 0x1D0, 0x1D2, 0x277, 0x271, 0x270, 0x278, 0x270, 0x272, 0x23B, 0x235, 0x234, 0x23C, 0x234, 0x236, 0x2DD, 0x2DD, 0x2DB, 0x2DD, 0x2DB, 0x2DB, 0x2CB, 0x2CA, 0x2C9, 0x2CA, 0x2C9, 0x2C9 };
/* 0x468 */ SDTIREDATA sdMachineTireTbl[11] = {
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
/* 0x6D0 */ SDBODYDATA sdMachineBodyTbl[11] = {
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
/* 0x804 */ SDGUNDATA sdMachineGunTbl[13] = {
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
/* 0x970 */ static SDBULLETPARAM sdBulletParam[13] = {
    { 1, 5, 5, 2400.0f, 0.0f, 30.0f, 0.0f, 0.0f, 100.0f, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 10, 8, 1800.0f, 0.0f, 30.0f, 0.0f, 0.0f, 100.0f, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0 },
    { 2, 3, 3, 1680.0f, 60.0f, 40.0f, 400.0f, 0.0f, 100.0f, 0, 0, 0, 64, 25, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 4, 5, 180.0f, 0.0f, 30.0f, 200.0f, 90.0f, 100.0f, 0, 0, 0, 64, 25, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 4, 4, 2400.0f, 0.0f, 30.0f, 0.0f, 0.0f, 600.0f, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 2, 6, 6, 3600.0f, 0.0f, 70.0f, 0.0f, 0.0f, 100.0f, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 6, 6, 0.0f, 0.0f, 30.0f, 0.0f, 0.0f, 100.0f, 0, 0, 0, 0, 0, 30, 0, 0, 0, 0, 0, 0 },
    { 0, 3, 15, 3600.0f, 0.0f, 30.0f, 0.0f, 0.0f, 100.0f, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0 },
    { 0, 2, 4, 2880.0f, 0.0f, 30.0f, 400.0f, 0.0f, 100.0f, 0, 0, 0, 64, 25, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 7, 4, 300.0f, 0.0f, 30.0f, 300.0f, 60.0f, 100.0f, 0, 0, 0, 64, 25, 0, 0, 0, 0, 0, 20, 0 },
    { 0, 2, 3, 2880.0f, 0.0f, 30.0f, 600.0f, 0.0f, 100.0f, 0, 0, 0, 64, 25, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 2, 4, 2880.0f, 0.0f, 40.0f, 0.0f, 0.0f, 100.0f, 0, 0, 0, 8, 0, 0, 0, 0, 12, 0, 0, 0 },
    { 1, 5, 5, 110.0f, 60.0f, 40.0f, 400.0f, 0.0f, 100.0f, 0, 0, 0, 64, 25, 0, 0, 0, 0, 0, 0, 0 },
};
/* 0xDB4 */ s32 lbl_1_data_DB4[11][5] = { { -1, 0, 0, 0, 0 }, { -1, 3, 3, -1, 0 }, { -1, -3, -3, 0, 0 }, { -1, 0, 1, -3, 0 }, { -1, -1, -2, -2, 0 }, { -1, 4, 4, -1, 0 }, { -1, -4, -4, -1, 0 }, { -1, 1, 1, -4, 0 }, { -1, 0, 0, 0, 0 }, { -1, -2, 2, -1, 0 }, { -1, 1, 2, -3, 1 } };
/* 0xE90 */ static u32 playerModelTbl[12] = { DATANUM(DATA_sd00, 18), DATANUM(DATA_sd00, 19), DATANUM(DATA_sd00, 20), DATANUM(DATA_sd00, 21), DATANUM(DATA_sd00, 22), DATANUM(DATA_sd00, 23), DATANUM(DATA_sd00, 24), DATANUM(DATA_sd00, 25), DATANUM(DATA_sd00, 26), DATANUM(DATA_sd00, 27), DATANUM(DATA_sd00, 28), DATANUM(DATA_sd00, 29) };
/* 0xF84 */ char *sdMachineHookTbl[17] = {
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
/* 0xFC8 */ static float machineYOfsTbl[11] = { -22.0f, -38.0f, -26.0f, -33.0f, 0.0f, 0.0f, 0.0f, -16.0f, -15.0f, -38.0f, -22.0f };
/* 0x100C */ char *sdMachineTireHookTbl[3] = {
    "chn_tl",
    "chn_tr",
    "chn_hover"
};

/* 62 insns */
void SdMachineKill(SDMACHINE *machine)
{
    s32 i;
    SdMachineFxStop(machine);
    SdMachineParticleKill();
    SdSprKill(machine);
    if(machine->unk33C != 0) {
        HuMemDirectFree(machine->unk33C);
    }
    if(machine->unk340 != 0) {
        HuMemDirectFree(machine->unk340);
    }
    machine->unk33C = NULL;
    machine->unk340 = NULL;
    Hu3DModelKill(machine->unk3B4);
    Hu3DModelHookReset(machine->bodyMdl);
    Hu3DModelKill(machine->bodyMdl);
    for(i = 0; i < 4; i++) {
        if(machine->tireMdl[i] != -1) {
            Hu3DModelKill(machine->tireMdl[i]);
        }
    }
    if(machine->unk3AC != -1) {
        Hu3DModelKill(machine->unk3AC);
    }
    Hu3DModelKill(machine->gunMdl);
    Hu3DModelKill(machine->charMdl);
    SdMachineDestroy(machine);
}

/* 71 insns */
void SdMachineDestroy(SDMACHINE *machine)
{
    s32 i;
    s32 j;
    SDBULLET *bullet;
    for(i = 0; i < machine->gunNum; i++) {
        for(j = 0; j < machine->bulletNum; j++) {
            bullet = &machine->gun[i].bullet[j];
            if(bullet->mdlId[3] != -1) {
                Hu3DMotionSet(bullet->mdlId[0], -1);
                Hu3DMotionKill(bullet->mdlId[3]);
                Hu3DMotionKill(bullet->mdlId[4]);
                bullet->mdlId[3] = bullet->mdlId[4] = -1;
            }
            if(bullet->mdlId[2] != -1) {
                Hu3DModelHookReset(bullet->mdlId[0]);
                Hu3DModelKill(bullet->mdlId[2]);
            }
            if(bullet->mdlId[0] != -1) {
                Hu3DModelKill(bullet->mdlId[0]);
            }
            if(bullet->mdlId[1] != -1) {
                Hu3DModelKill(bullet->mdlId[1]);
            }
        }
        HuMemDirectFree(machine->gun[i].bullet);
    }
    HuMemDirectFree(machine->gun);
}

/* 397 insns */
void SdSprCreate(void)
{
    SDSPRWORK *spr = &sys->spr;
    s32 i;
    SDMACHINE *machine;
    s32 playerNo;
    s32 j;
    s32 hp;
    s32 k;
    s16 *sprId;
    HuVecF pos;
    spr->unk0 = spr->unkB8 = 0;
    for(i = 0; i < 2; i++) {
        machine = &sys->machine[i];
        playerNo = machine->playerNo;
        spr->unk26[playerNo] = espEntry(DATANUM(DATA_sd00, 149), 0, 0);
        espDrawNoSet(spr->unk26[playerNo], 0);
        espBankSet(spr->unk26[playerNo], playerNo * 2);
        espScaleSet(spr->unk26[playerNo], 0.5f, 0.5f);
        espPriSet(spr->unk26[playerNo], 0x1D0);
        pos = ScoreSprPosGet(machine->pos);
        espPosSet(spr->unk26[playerNo], pos.x, pos.y);
        pos = (HuVecF){ machine->mtx[0][2], machine->mtx[1][2], machine->mtx[2][2] };
        espZRotSet(spr->unk26[playerNo], -HuAtan(pos.x, pos.z));
        if(sys->gameType == 0) {
            for(j = 0; j < 8; j++) {
                spr->unk4[playerNo][j] = espEntry(DATANUM(DATA_sd00, 150), 0, 0);
                espDrawNoSet(spr->unk4[playerNo][j], 0);
                hp = machine->unkE4 - j * 4;
                if(hp > 0) {
                    espBankSet(spr->unk4[playerNo][j], 0);
                } else {
                    espBankSet(spr->unk4[playerNo][j], 3);
                    espDispOff(spr->unk4[playerNo][j]);
                }
                espPriSet(spr->unk4[playerNo][j], 0x1E0);
                espScaleSet(spr->unk4[playerNo][j], 0.6f, 0.6f);
                espPosSet(spr->unk4[playerNo][j], 32.0f + 316.0f * playerNo + 28.0f * j, 56.0f);
            }
        }
        spr->unk3C[playerNo] = HuMemDirectMallocNum(HEAP_HEAP, sizeof(s16) * machine->gunNum * machine->bulletNum, HU_MEMNUM_OVL);
        for(j = 0; j < machine->gunNum; j++) {
            for(k = 0; k < machine->bulletNum; k++) {
                sprId = &spr->unk3C[playerNo][k + j * machine->bulletNum];
                *sprId = espEntry(DATANUM(DATA_sd00, 149), 0, 0);
                espDrawNoSet(*sprId, 0);
                espBankSet(*sprId, playerNo * 2 + 1);
                espDispOff(*sprId);
                espPriSet(*sprId, 0x1D0);
                espScaleSet(*sprId, 0.25f, 0.25f);
            }
        }
    }
    spr->unkB2 = espEntry(DATANUM(DATA_sd00, 156), 0, 0);
    espDrawNoSet(spr->unkB2, 0);
    espPriSet(spr->unkB2, 0x1F0);
    espPosSet(spr->unkB2, 288.0f, 240.0f);
    if(sys->gameType == 1) {
        spr->unkB4 = espEntry(DATANUM(DATA_sd00, 154), 0, 0);
        espDrawNoSet(spr->unkB4, 0);
        espScaleSet(spr->unkB4, 0.5f, 0.5f);
        espPriSet(spr->unkB4, 0x1D0);
        pos = ScoreSprPosGet(SdFlagPosGet());
        espPosSet(spr->unkB4, pos.x, pos.y);
        espDispOff(spr->unkB4);
    }
    if(sys->gameType == 2) {
        spr->unkB6 = espEntry(DATANUM(DATA_sd00, 155), 0, 0);
        espDrawNoSet(spr->unkB6, 0);
        espScaleSet(spr->unkB6, 0.5f, 0.5f);
        espPriSet(spr->unkB6, 0x1D0);
        pos = ScoreSprPosGet(SdRabbitPosGet());
        espPosSet(spr->unkB6, pos.x, pos.y);
        espDispOff(spr->unkB6);
    }
    MapSprCreate();
}

/* 67 insns */
static void MapSprCreate(void)
{
    SDSPRWORK *spr = &sys->spr;
    if(sys->stageNo == 0) {
        spr->unk24 = espEntry(DATANUM(DATA_sd00, 152), 0, 0);
    } else if(sys->stageNo == 7) {
        spr->unk24 = espEntry(DATANUM(DATA_sd00, 153), 0, 0);
    } else {
        spr->unk24 = espEntry(DATANUM(DATA_sd00, 151), 0, 0);
    }
    espDrawNoSet(spr->unk24, 0);
    espPriSet(spr->unk24, 0x1E0);
    espPosSet(spr->unk24, 288.0f, 360.0f);
    espScaleSet(spr->unk24, 0.5f, 0.5f);
}

/* 15 insns */
static void MapSprKill(void)
{
    SDSPRWORK *spr = &sys->spr;
    espKill(spr->unk24);
}

/* 331 insns */
void SdHpSprCreate(void)
{
    SDSPRWORK *spr = &sys->spr;
    s32 i;
    SDMACHINE *machine;
    s32 playerNo;
    s32 j;
    s32 hp;
    s32 k;
    HuVecF pos;
    espDispOff(spr->unk24);
    for(i = 0; i < 2; i++) {
        machine = &sys->machine[i];
        playerNo = machine->playerNo;
        espDispOff(spr->unk26[playerNo]);
        for(j = 0; j < 3; j++) {
            spr->unk46[playerNo][j] = espEntry(DATANUM(DATA_sd00, 149), 0, 0);
            espDrawNoSet(spr->unk46[playerNo][j], 0);
            espBankSet(spr->unk46[playerNo][j], playerNo * 2);
            espScaleSet(spr->unk46[playerNo][j], 2.5f, 2.5f);
            espPriSet(spr->unk46[playerNo][j], 0x1D0);
            pos = ScoreSprPosGet(machine->pos);
            espPosSet(spr->unk46[playerNo][j], pos.x, pos.y);
            pos = (HuVecF){ machine->mtx[0][2], machine->mtx[1][2], machine->mtx[2][2] };
            espZRotSet(spr->unk46[playerNo][j], -HuAtan(pos.x, pos.z));
            espDispOff(spr->unk46[playerNo][j]);
            espTPLvlSet(spr->unk46[playerNo][j], 0.1f);
            HuSprAttrSet(espGrpIDGet(), esprite[spr->unk46[playerNo][j]].memberNo, HUSPR_ATTR_ADDCOL);
        }
        if(sys->gameType == 0) {
            for(j = 0; j < 8; j++) {
                espDispOff(spr->unk4[playerNo][j]);
                hp = machine->unkE4 - j * 4;
                for(k = 0; k < 3; k++) {
                    spr->unk52[playerNo][j][k] = espEntry(DATANUM(DATA_sd00, 150), 0, 0);
                    espDrawNoSet(spr->unk52[playerNo][j][k], 0);
                    if(hp > 0) {
                        espBankSet(spr->unk52[playerNo][j][k], 0);
                    } else {
                        espBankSet(spr->unk52[playerNo][j][k], 3);
                        espDispOff(spr->unk52[playerNo][j][k]);
                    }
                    espPriSet(spr->unk52[playerNo][j][k], 0x1E0);
                    espScaleSet(spr->unk52[playerNo][j][k], 2.5f, 2.5f);
                    espPosSet(spr->unk52[playerNo][j][k], 32.0f + 316.0f * playerNo + 28.0f * j, 56.0f);
                    espDispOff(spr->unk52[playerNo][j][k]);
                    HuSprAttrSet(espGrpIDGet(), esprite[spr->unk52[playerNo][j][k]].memberNo, HUSPR_ATTR_ADDCOL);
                }
            }
        }
    }
}

/* 118 insns */
static HuVecF ScoreSprPosGet(HuVecF pos)
{
    HuVecF result;
    HuVecF stagePos;
    s32 type;
    if(sys->stageNo == 0) {
        result.x = 288.0 + (64.0f * pos.x) / 2400.0;
        result.y = 360.0 + (64.0f * pos.z) / 2400.0;
    } else if(sys->stageNo == 7) {
        result.x = 288.0f + (64.0f * pos.x) / 3540.0f;
        result.y = 360.0f + (72.0f * pos.z) / 3540.0f;
    } else {
        SdStageSprPosGet(&type, &stagePos);
        result.x = 288.0f + (64.0f * pos.x) / stagePos.x;
        result.y = 360.0f + (64.0f * pos.z) / stagePos.x;
    }
    return result;
}

/* 98 insns */
void SdSprKill(SDMACHINE *machine)
{
    SDSPRWORK *spr = &sys->spr;
    SDMACHINE *machineP;
    s32 playerNo;
    s32 i;
    s32 j;
    s32 k;
    s16 *sprId;
    if(sys->gameType == 1) {
        espKill(spr->unkB4);
    }
    if(sys->gameType == 2) {
        espKill(spr->unkB6);
    }
    for(i = 0; i < 2; i++) {
        machineP = &sys->machine[i];
        playerNo = machineP->playerNo;
        espKill(spr->unk26[playerNo]);
        if(sys->gameType == 0) {
            for(j = 0; j < 8; j++) {
                espKill(spr->unk4[playerNo][j]);
            }
        }
        for(j = 0; j < machineP->gunNum; j++) {
            for(k = 0; k < machineP->bulletNum; k++) {
                sprId = &spr->unk3C[playerNo][k + j * machineP->bulletNum];
                espKill(*sprId);
            }
        }
        HuMemDirectFree(spr->unk3C[playerNo]);
    }
    MapSprKill();
    espKill(spr->unkB2);
}

/* 76 insns */
void SdHpSprKill(void)
{
    SDSPRWORK *spr = &sys->spr;
    SDMACHINE *machine;
    s32 playerNo;
    s32 i;
    s32 j;
    s32 k;
    for(i = 0; i < 2; i++) {
        machine = &sys->machine[i];
        playerNo = machine->playerNo;
        for(j = 0; j < 3; j++) {
            espKill(spr->unk46[playerNo][j]);
            spr->unk46[playerNo][j] = -1;
        }
        if(sys->gameType == 0) {
            for(j = 0; j < 8; j++) {
                for(k = 0; k < 3; k++) {
                    espKill(spr->unk52[playerNo][j][k]);
                    spr->unk52[playerNo][j][k] = -1;
                }
            }
        }
    }
}

/* 39 insns */
void SdSprScissorUpdate(s16 sprId, s32 cameraNo)
{
    HuSprScissorSet(espGrpIDGet(), esprite[sprId].memberNo, Hu3DCamera[cameraNo].scissorX, Hu3DCamera[cameraNo].scissorY, Hu3DCamera[cameraNo].scissorW, Hu3DCamera[cameraNo].scissorH);
}

/* 679 insns */
void SdSprUpdate(void)
{
    SDSPRWORK *spr = &sys->spr;
    s32 i;
    SDMACHINE *machine;
    s32 playerNo;
    s32 j;
    s32 hp;
    s32 hpFrac;
    s32 k;
    SDBULLET *bullet;
    s16 *sprId;
    HuVecF pos;
    if(MgSeqModeGet() >= 5 && spr->unkB8 == 0) {
        spr->unk0++;
        spr->unk0 %= 600;
        for(i = 0; i < 2; i++) {
            machine = &sys->machine[i];
            playerNo = machine->playerNo;
            pos = ScoreSprPosGet(machine->pos);
            espPosSet(spr->unk26[playerNo], pos.x, pos.y);
            pos = (HuVecF){ machine->mtx[0][2], machine->mtx[1][2], machine->mtx[2][2] };
            espZRotSet(spr->unk26[playerNo], -HuAtan(pos.x, pos.z));
            if(sys->gameType == 0) {
                for(j = 0; j < 8; j++) {
                    hp = machine->unkE4 - j * 4;
                    hpFrac = hp % 4;
                    if(hp > 0) {
                        espDispOn(spr->unk4[playerNo][j]);
                        if(hp >= 4) {
                            espBankSet(spr->unk4[playerNo][j], 0);
                        } else {
                            espBankSet(spr->unk4[playerNo][j], 4 - hpFrac);
                        }
                    } else {
                        espDispOff(spr->unk4[playerNo][j]);
                    }
                }
            }
            for(j = 0; j < machine->gunNum; j++) {
                for(k = 0; k < machine->bulletNum; k++) {
                    bullet = &machine->gun[j].bullet[k];
                    sprId = &spr->unk3C[playerNo][k + j * machine->bulletNum];
                    if(bullet->mode == 0) {
                        espDispOff(*sprId);
                    } else if(machine->gunNo == 6 || machine->gunNo == 11) {
                        espDispOff(*sprId);
                    } else {
                        pos = bullet->pos;
                        espDispOn(*sprId);
                        pos = ScoreSprPosGet(pos);
                        espPosSet(*sprId, pos.x, pos.y);
                    }
                }
            }
        }
        if(sys->gameType == 1) {
            if(SdFlagCheck()) {
                pos = ScoreSprPosGet(SdFlagPosGet());
                espPosSet(spr->unkB4, pos.x, pos.y);
                espDispOn(spr->unkB4);
            } else {
                espDispOff(spr->unkB4);
            }
        }
        if(sys->gameType == 2) {
            if(SdRabbitCheck()) {
                pos = ScoreSprPosGet(SdRabbitPosGet());
                espPosSet(spr->unkB6, pos.x, pos.y);
                espDispOn(spr->unkB6);
            } else {
                espDispOff(spr->unkB6);
            }
        }
    }
}

void SdSprHideAll(void)
{
    s32 i;
    SDSPRWORK *spr = &sys->spr;
    s32 j;
    spr->unkB8 = 1;
    for(i = 0; i < 2; i++) {
        espDispOff(spr->unk26[i]);
    }
    espDispOff(spr->unk24);
    if(sys->gameType == 0) {
        for(i = 0; i < 2; i++) {
            for(j = 0; j < 8; j++) {
                if(spr->unk4[i][j] != -1) {
                    espDispOff(spr->unk4[i][j]);
                }
            }
        }
    } else if(sys->gameType == 1) {
        SdFlagSprDispOff();
    } else {
        SdRabbitSprDispOff();
    }
}

/* 92 insns */
void SdMachineConfigSet(s32 playerNo)
{
    GWSDBATTLE *battle = &GwSdBattle;
    GWSDMACHINE *gwMachine = &battle->machine[playerNo];
    SDMACHINE *machine = &sys->machine[playerNo];
    s32 no;
    if(GwPlayerConf[playerNo].type != 0 && gwMachine->charNo >= 32) {
        no = gwMachine->charNo - 32;
        machine->bodyNo = configPartTbl[no + 1][0];
        machine->tireNo = configPartTbl[no + 1][1];
        machine->unk3C0 = configPartTbl[no + 1][2];
        machine->gunNo = configPartTbl[no + 1][3];
        machine->charNo = configPartTbl[no + 1][4];
        machine->com.unk3C = no;
    } else {
        if(GwPlayerConf[playerNo].type != 0) {
            machine->com.unk3C = -1;
        }
        machine->bodyNo = gwMachine->partNo[0];
        machine->tireNo = gwMachine->partNo[1];
        machine->unk3C0 = gwMachine->partNo[2];
        machine->gunNo = gwMachine->partNo[3];
        machine->charNo = gwMachine->charNo;
    }
}

/* 139 insns */
void SdMachineEffectCreate(void)
{
    sys->unk1E4[4] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sd00, 90), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(sys->unk1E4[4], HU3D_ATTR_DISPOFF);
    sys->unk1E4[0] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sd00, 109), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(sys->unk1E4[0], HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(sys->unk1E4[0], 3);
    Hu3DModelAttrSet(sys->unk1E4[0], HU3D_MOTATTR_LOOP);
    Hu3DMotionAttrSet(Hu3DMotionIDGet(sys->unk1E4[0]), 1);
    sys->unk1E4[1] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sd00, 110), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(sys->unk1E4[1], HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(sys->unk1E4[1], 3);
    sys->unk1E4[2] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sd00, 111), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(sys->unk1E4[2], HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(sys->unk1E4[2], 3);
    Hu3DModelAttrSet(sys->unk1E4[2], HU3D_MOTATTR_LOOP);
    Hu3DMotionAttrSet(Hu3DMotionIDGet(sys->unk1E4[2]), 1);
    sys->unk1E4[3] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sd00, 112), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(sys->unk1E4[3], HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(sys->unk1E4[3], 3);
}

/* 428 insns */
void SdMachineParticleCreate(void)
{
    s32 blendTbl[12] = { 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1 };
    s32 i;
    SDMACHINE *machine;
    s32 j;
    SDSTAGEOBJ *obj;
    HU3DPARTICLEDATA *data;
    s32 l;
    s32 k;
    HU3DPARTICLE *particle;
    SDBULLET *bullet;
    SDMACHINEEXHAUST *exhaust;

    for(i = 0; i < 12; i++) {
        sys->unk16C[i] = HuSprAnimRead(HuDataSelHeapReadNum(effectFileTbl[i], HU_MEMNUM_OVL, HEAP_MODEL));
        sys->particleMdlId[i] = -1;
        sys->unk1B4[i] = 0;
    }
    for(i = 0; i < 2; i++) {
        machine = &sys->machine[i];
        memset(machine->unk340, 0, 0x110);
        for(j = 0; j < 2; j++) {
            machine->unk340->unk0[j][0] = sys->unk1B4[3];
            sys->unk1B4[3] += 30;
            machine->unk340->unk0[j][1] = sys->unk1B4[2];
            sys->unk1B4[2] += 30;
            machine->unk340->unk0[j][2] = sys->unk1B4[9];
            sys->unk1B4[9] += 30;
            machine->unk340->unk0[j][3] = sys->unk1B4[11];
            sys->unk1B4[11] += 30;
        }
        for(j = 0; j < machine->gunNum; j++) {
            for(k = 0; k < machine->bulletNum; k++) {
                bullet = &machine->gun[j].bullet[k];
                for(l = 0; l < 12; l++) {
                    bullet->effectNo[l] = sys->unk1B4[l];
                    sys->unk1B4[l] += (&bullet->param->unk24)[l];
                }
            }
        }
        for(j = 0; j < machine->unk208; j++) {
            exhaust = &machine->unk33C[j];
            if(machine->bodyNo != 1 && machine->bodyNo != 9 && machine->bodyNo != 10) {
                exhaust->unk0 = sys->unk1B4[3];
                sys->unk1B4[3] += 30;
            } else {
                exhaust->unk0 = sys->unk1B4[10];
                sys->unk1B4[10] += 30;
            }
        }
    }
    if(sys->stageObj != 0) {
        for(i = 0; i < 8; i++) {
            obj = &sys->stageObj[i];
            if(obj->mdlId != -1 && (obj->type == 1 || obj->type == 2)) {
                obj->unk20 = sys->unk1B4[3];
                sys->unk1B4[3] += 48;
                obj->unk24 = sys->unk1B4[4];
                sys->unk1B4[4] += 25;
            }
        }
    }
    if(sys->stageNo == 7) {
        sys->unkFE8 = sys->unk1B4[0];
        sys->unk1B4[0] += 510;
    }
    for(i = 0; i < 12; i++) {
        if(sys->unk1B4[i] == 0) {
            sys->unk1B4[i] = 1;
        }
        sys->particleMdlId[i] = Hu3DParticleCreate(sys->unk16C[i], sys->unk1B4[i]);
        particle = Hu3DData[sys->particleMdlId[i]].hookData;
        data = particle->data;
        Hu3DParticleColSet(sys->particleMdlId[i], 255, 255, 255);
        Hu3DParticleBlendModeSet(sys->particleMdlId[i], blendTbl[i]);
        Hu3DParticleHookSet(sys->particleMdlId[i], SdMachinePartcleHook);
        Hu3DModelLayerSet(sys->particleMdlId[i], 3);
        Hu3DModelPosSet(sys->particleMdlId[i], 0.0f, 0.0f, 0.0f);
        Hu3DParticleAnimModeSet(sys->particleMdlId[i], 0);
        for(j = 0; j < particle->maxCnt; j++, data++) {
            data->time = 0;
            data->scale = 0.0f;
            data->cameraBit = 3;
        }
    }
}

/* 50 insns */
void SdMachineParticleKill(void)
{
    s32 i;
    for(i = 0; i < 12; i++) {
        if(sys->particleMdlId[i] != -1) {
            Hu3DModelKill(sys->particleMdlId[i]);
        }
        sys->unk16C[i] = NULL;
        sys->particleMdlId[i] = -1;
        sys->unk1B4[i] = 0;
    }
}

/* 16 insns */
static void SdMachinePartcleHook(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx)
{
    HU3DPARTICLEDATA *data;

    data = particle->data;
    DCStoreRangeNoSync(particle->data, particle->maxCnt * sizeof(HU3DPARTICLEDATA));
}

/* 83 insns */
void SdMachineFxStart(SDMACHINE *machine)
{
    machine->unk3DC = machine->unk3E0 = machine->unk3F4 = machine->unk3F0 = -1;
    machine->unk3DC = HuAudFXPlayVolPan(machine->playerNo + engineSeIdTbl[machine->unk3C0], 127, (machine->playerNo * 32) + 48);
    HuAudFXPitchSet(machine->unk3DC, 0);
    if(lbl_1_data_2B4[machine->tireNo] != 0) {
        machine->unk3E0 = HuAudFXPlayVolPan(machine->playerNo + lbl_1_data_2B4[machine->tireNo], 0, (machine->playerNo * 32) + 48);
    }
    if(machine->gunNo == 6) {
        machine->unk3F4 = HuAudFXPlayVolPan(machine->playerNo + gunSeIdTbl[machine->gunNo], 0, (machine->playerNo * 32) + 48);
    }
    machine->unk3F0 = HuAudFXPlayVolPan(machine->playerNo + 1375, 0, (machine->playerNo * 32) + 48);
}

/* 30 insns */
void SdMachineFxStop(SDMACHINE *machine)
{
    if(machine->unk3DC != -1) {
        HuAudFXStop(machine->unk3DC);
    }
    if(machine->unk3E0 != -1) {
        HuAudFXStop(machine->unk3E0);
    }
    if(machine->unk3F4 != -1) {
        HuAudFXStop(machine->unk3F4);
    }
    if(machine->unk3F0 != -1) {
        HuAudFXStop(machine->unk3F0);
    }
}

/* 154 insns */
void SdMachineFxUpdate(SDMACHINE *machine)
{
    HuVecF dir;
    HuVecF fwd;
    float dot;
    float mag;

    if(lbl_1_data_2B4[machine->tireNo] != 0) {
        if(machine->unk90 != 0) {
            HuAudFXVolSet(machine->unk3E0, 0);
        } else if(machine->unk28 != 1 && machine->unk28 != 2) {
            HuAudFXVolSet(machine->unk3E0, 0);
        } else {
            mag = PSVECMag(&machine->unk160);
            if(mag < 1.0f) {
                HuAudFXVolSet(machine->unk3E0, 0);
            } else {
                PSVECNormalize(&machine->unk160, &dir);
                fwd = (HuVecF){ machine->mtx[0][2], machine->mtx[1][2], machine->mtx[2][2] };
                dot = PSVECDotProduct(&dir, &fwd);
                if(dot > 0.8f) {
                    HuAudFXVolSet(machine->unk3E0, 0);
                } else {
                    if(HuAudFXStatusGet(machine->unk3E0) == 0) {
                        machine->unk3E0 = HuAudFXPlayPan(machine->playerNo + lbl_1_data_2B4[machine->tireNo], (machine->playerNo * 32) + 48);
                    }
                    if(dot < 0.0f) {
                        dot = 0.0f;
                    }
                    if(mag > 10.0f) {
                        mag = 10.0f;
                    }
                    dot = 1.0f - dot;
                    mag = mag / 10.0f;
                    HuAudFXVolSet(machine->unk3E0, 127.0f * ((0.75f * dot) + (0.25f * mag)));
                }
            }
        }
    }
}

/* 30 insns */
void SdMachineFxGunPlay(SDBULLET *bullet)
{
    SDMACHINE *machine = bullet->machine;
    if(machine->gunNo != 6) {
        HuAudFXPlayVolPan(machine->playerNo + gunSeIdTbl[machine->gunNo], 127, (machine->playerNo * 32) + 48);
    }
}

/* 77 insns */
void SdMachineFxImpactPlay(SDBULLET *bullet)
{
    SDMACHINE *machine = bullet->machine;
    if(impactSeIdTbl[machine->gunNo] != 0) {
        if(impactSeIdTbl[machine->gunNo] == 0x555) {
            SdImpactStart(impactSeIdTbl[machine->gunNo], bullet->pos, 1.0f, 0, 100.0f);
        } else {
            SdImpactStart(impactSeIdTbl[machine->gunNo], bullet->pos, 1.0f, 1, bullet->param->unk18);
        }
    }
}

/* 29 insns */
void SdImpactStart(s32 seNo, HuVecF pos, float vol, s32 a3, float a4)
{
    SdImpactSet(seNo, pos, vol, a3, a4);
}

/* 29 insns */
void SdImpactSoundStart(s32 seNo, HuVecF pos, float vol)
{
    SdImpactSet(seNo, pos, vol, 0, 0.0f);
}

/* 569 insns */
static void SdImpactSet(s32 seNo, HuVecF pos, float vol, s32 a3, float a4)
{
    Mtx camMtx[2];
    HuVecF dir;
    HuVecF ofs;
    HuVecF ofs2;
    float dist;
    float speed;
    s32 i;
    s32 j;
    SDIMPACT *impact;

    speed = 555.55554f;
    PSVECSubtract(&Hu3DCamera[0].target, &Hu3DCamera[0].pos, &dir);
    MathPlaneRotMtxGet(&dir, &Hu3DCamera[0].up, 0.0f, camMtx[0]);
    PSVECSubtract(&Hu3DCamera[1].target, &Hu3DCamera[1].pos, &dir);
    MathPlaneRotMtxGet(&dir, &Hu3DCamera[1].up, 0.0f, camMtx[1]);
    for(i = 0; i < 30; i++) {
        impact = &sys->impact[i];
        if(impact->unk0 != 0) {
            continue;
        }
        impact->unk0 = 1;
        impact->time = 0;
        impact->unk18 = a3;
        for(j = 0; j < 2; j++) {
            impact->seNo[j] = 0;
            SdScreenPosGet(&pos, sdCameraBitTbl[j], &dir);
            dir.x = 2.0f * (dir.x - 144.0f);
            if(dir.x < 0.0f || dir.x > 576.0f || dir.y < 0.0f || dir.y > 480.0f || dir.z > 0.0f) {
                if(0.0f == a4) {
                    continue;
                }
                ofs = ofs2 = (HuVecF){ 0.0f, 0.0f, 0.0f };
                if(dir.x < 0.0f) {
                    ofs = (HuVecF){ camMtx[j][0][0], camMtx[j][1][0], camMtx[j][2][0] };
                    PSVECScale(&ofs, &ofs, -1.0f);
                } else if(dir.x > 576.0f) {
                    ofs = (HuVecF){ camMtx[j][0][0], camMtx[j][1][0], camMtx[j][2][0] };
                }
                if(dir.y > 480.0f || dir.z > 0.0f) {
                    ofs2 = (HuVecF){ camMtx[j][0][1], camMtx[j][1][1], camMtx[j][2][1] };
                } else if(dir.y < 0.0f) {
                    ofs2 = (HuVecF){ camMtx[j][0][1], camMtx[j][1][1], camMtx[j][2][1] };
                    PSVECScale(&ofs2, &ofs2, -1.0f);
                }
                PSVECAdd(&ofs, &ofs2, &ofs);
                if(0.0f == PSVECMag(&ofs)) {
                    ofs = (HuVecF){ 1.0f, 1.0f, 1.0f };
                }
                PSVECNormalize(&ofs, &ofs);
                PSVECScale(&ofs, &ofs, a4);
                PSVECAdd(&ofs, &pos, &ofs);
                SdScreenPosGet(&ofs, sdCameraBitTbl[j], &ofs);
                ofs.x = 2.0f * (ofs.x - 144.0f);
                if(ofs.x < 0.0f || ofs.x > 576.0f || ofs.y < 0.0f || ofs.y > 480.0f || ofs.z > 0.0f) {
                    continue;
                }
            }
            dir.x = 0.5f * (dir.x + (576.0f * j));
            dir.x = (dir.x > 576.0f) ? 576.0f : ((dir.x < 0.0f) ? 0.0f : dir.x);
            impact->seNo[j] = seNo + j;
            impact->pan[j] = (127.0f * dir.x) / 576.0f;
            PSVECSubtract(&Hu3DCamera[j].pos, &pos, &dir);
            dist = PSVECMag(&dir);
            impact->delay[j] = dist / speed;
            impact->vol[j] = 32.0f + (96.0f - ((63.0f * dist) / 8400.0f));
            impact->vol[j] = (impact->vol[j] > 127) ? 127 : ((impact->vol[j] < 32) ? 32 : impact->vol[j]);
            impact->vol[j] *= vol;
        }
        break;
    }
}

/* 127 insns */
void SdImpactUpdate(void)
{
    s32 i;
    s32 j;
    SDIMPACT *impact;

    for(i = 0; i < 30; i++) {
        impact = &sys->impact[i];
        if(impact->unk0 == 0) {
            continue;
        }
        if(impact->seNo[0] == 0 && impact->seNo[1] == 0) {
            impact->unk0 = 0;
            continue;
        }
        for(j = 0; j < 2; j++) {
            if(impact->seNo[j] != 0 && impact->time >= impact->delay[j]) {
                HuAudFXPlayVolPan(impact->seNo[j], impact->vol[j], impact->pan[j]);
                if(impact->unk18 != 0) {
                    sys->camera[j].unk84 = 5.0f * (1.0f - MathLerp(1, (127 - impact->vol[j]) / 100.0f));
                    SdVibrate(sys->machine[j].playerNo, 0, 2.0f * sys->camera[j].unk84);
                }
                impact->seNo[j] = 0;
            }
        }
        impact->time++;
    }
}

/* 35 insns */
void SdPlayerSoundPlay(SDMACHINE *machine, s32 seNo)
{
    s16 pan = (seNo == 5) ? 64 : ((machine->playerNo * 32) + 48);
    HuAudFXPlayPan(playerSeIdTbl[machine->charNo][seNo], pan);
}

/* 22 insns */
void SdMachineBodyCreate(s32 bodyNo, HU3DMODELID *modelId)
{
    *modelId = Hu3DModelCreate(HuDataSelHeapReadNum(sdMachineBodyTbl[bodyNo].dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
}

/* 49 insns */
void SdMachineTireCreate(s32 tireNo, HU3DMODELID *modelId)
{
    s32 i;
    s32 flag = sdMachineTireTbl[tireNo].unk34;
    s32 type = flag & 0xF;
    for(i = 0; i < 4; i++) {
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
        modelId[i] = Hu3DModelCreate(HuDataSelHeapReadNum(sdMachineTireTbl[tireNo].dataNum[i], HU_MEMNUM_OVL, HEAP_MODEL));
    }
}

/* 22 insns */
void SdMachineGunCreate(s32 gunNo, HU3DMODELID *modelId)
{
    *modelId = Hu3DModelCreate(HuDataSelHeapReadNum(sdMachineGunTbl[gunNo].dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
}

/* 22 insns */
void SdMachineCharCreate(s32 charNo, HU3DMODELID *modelId)
{
    *modelId = Hu3DModelCreate(HuDataSelHeapReadNum(playerModelTbl[charNo], HU_MEMNUM_OVL, HEAP_MODEL));
}

