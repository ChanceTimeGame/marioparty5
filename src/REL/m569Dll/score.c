/*
 * m569dll score.c -- decompiled from the reference assembly; functions are in reference
 * order. Line ranges are into build/mp5-asm/m569dll/asm/REL/m569dll/score.s.
 */

#include "REL/m569dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/hsfex.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x208 */ /* float lbl_1_rodata_208 = 15.0f; */
/* 0x20C */ /* float lbl_1_rodata_20C = 700.0f; */
/* 0x210 */ /* float lbl_1_rodata_210 = 8.0f; */
/* 0x214 */ /* float lbl_1_rodata_214 = 350.0f; */
/* 0x218 */ /* float lbl_1_rodata_218 = 0.0f; */
/* 0x21C */ /* float lbl_1_rodata_21C = 0.017453292f; */
/* 0x220 */ /* float lbl_1_rodata_220 = -90.0f; */
/* 0x224 */ /* float lbl_1_rodata_224 = 0.1f; */
/* 0x228 */ /* float lbl_1_rodata_228 = 100.0f; */
/* 0x230 */ /* double lbl_1_rodata_230 = 3.141592653589793; */
/* 0x238 */ /* double lbl_1_rodata_238 = 180; */
/* 0x240 */ /* float lbl_1_rodata_240 = 0.8f; */
/* 0x244 */ /* float lbl_1_rodata_244 = -6.5f; */
/* 0x248 */ /* float lbl_1_rodata_248 = -2.6000001f; */
/* 0x24C */ /* float lbl_1_rodata_24C = 0.5f; */
/* 0x250 */ /* float lbl_1_rodata_250 = 14.0f; */
/* 0x258 */ /* double lbl_1_rodata_258 = 4503601774854144; */
/* 0x260 */ /* float lbl_1_rodata_260 = 1.96f; */

/* --- .data --- */
/* 0x3C0 */ HuVecF lbl_1_data_3C0[4] = { { -3e+02f, 3.5e+02f, -5e+01f }, { -1e+02f, 3.5e+02f, -5e+01f }, { 1e+02f, 3.5e+02f, -5e+01f }, { 3e+02f, 3.5e+02f, -5e+01f } };
/* 0x3F0 */ GXColor lbl_1_data_3F0[4] = { { 255, 192, 204, 255 }, { 255, 255, 153, 255 }, { 178, 255, 255, 255 }, { 153, 255, 192, 255 } }; /* lbz x4 per entry */
/* 0x400 */ HU3DPARMANPARAM lbl_1_data_400 = {
    50, 0,
    2e+01f, 1e+02f, 0.0f,
    { 0.0f, 0.0f, 0.0f },
    1.0f, 0.0f, 1e+02f, 0.97f,
    1,
    { { 255, 255, 255, 255 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 255, 255, 255, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }
};
/* 0x450 */ char lbl_1_data_450[] = "m569_ef2";
/* 0x459 */ char lbl_1_data_459[] = "coin-coin_1";

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x56B0 */ M569_COINDROP *lbl_1_bss_56B0[4];
/* 0x56A8 */ M569_SCOREDISP *lbl_1_bss_56A8[2];
/* 0x27C8 */ M569_CONFETTI lbl_1_bss_27C8[200];
/* 0x27BC */ M569_CONFETTIMAN lbl_1_bss_27BC;
/* 0x17C */ M569_COIN lbl_1_bss_17C[144];
/* 0x17A gap_05_0000017A_bss (0x2) -- dtk filler */
/* 0x178 */ HU3DMODELID lbl_1_bss_178;   /* coin model 0x990000 (fn_1_9B2C) */
/* 0x174 */ s32 lbl_1_bss_174;           /* coins ever spawned (fn_1_9C38); gates fn_1_9A20 */
/* 0x172 gap_05_00000172_bss (0x2) -- dtk filler */
/* 0x170 */ HU3DMODELID lbl_1_bss_170;   /* Hu3DHookFuncCreate(fn_1_986C) */
/* 0x16C */ s32 lbl_1_bss_16C;           /* roll SE 0x1D (fn_1_8978) */
/* 0x168 */ s32 lbl_1_bss_168;           /* unreferenced */

/* --- functions (reference order) --- */
void fn_1_87D4(void)
{
    int i;
    MGSCORE *score;
    OMOBJ *obj;
    HuVecF pos;

    for (i = 0; i < 2; i++) {
        score = MgScoreCreate(0x960034, -1, 1);
        MgScoreMaxDigitSet(score, 2);
        Hu3D3Dto2D(&lbl_1_data_D8[i + 2], lbl_1_bss_34.no, &pos);
        MgScorePosSet(score, pos.x - 15.0f, pos.y);
        MgScoreColorSet(score, 255, 255, 255);
        HuSprGrpDrawNoSet(score->grpId, 64);
        obj = omAddObjEx(objman, 0x2000, 0, 0, -1, fn_1_8978);
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M569_SCOREDISP), HU_MEMNUM_OVL);
        lbl_1_bss_56A8[i] = obj->data;
        lbl_1_bss_56A8[i]->unk004 = i;
        lbl_1_bss_56A8[i]->unk000 = score;
        lbl_1_bss_56A8[i]->unk008 = 0;
        lbl_1_bss_56A8[i]->unk00C = 0;
    }
    HuSprExecLayerSet(64, 2);
}

void fn_1_8978(OMOBJ *obj)
{
    M569_SCOREDISP *work;

    work = obj->data;
    switch (work->unk00C) {
        case 0:
            break;
        case 1:
            MgScoreDispOn(work->unk000);
            work->unk00C = 2;
            work->unk010 = 90;
            lbl_1_bss_16C = HuAudFXPlay(0x1D);
            break;
        case 2:
            MgScoreValueSet(work->unk000, frandmod(100));
            work->unk010--;
            if (work->unk010 == 0) {
                MgScoreValueSet(work->unk000, work->unk008);
                work->unk00C = 3;
                HuAudFXStop(lbl_1_bss_16C);
                if (work->unk004 == 0) {
                    HuAudFXPlay(0x90D);
                } else {
                    HuAudFXPlay(0x90E);
                }
            }
            break;
        case 3:
            break;
    }
}

void fn_1_8A74(int round, int a1)
{
    lbl_1_bss_56A8[round]->unk008 = a1;
    lbl_1_bss_56A8[round]->unk00C = 1;
}

int fn_1_8AAC(int round)
{
    if (lbl_1_bss_56A8[round]->unk00C == 3) {
        return 1;
    } else {
        return 0;
    }
}

void fn_1_8ADC(void)
{
    int i;
    OMOBJ *obj;
    HU3DMODELID modelId;
    M569_PLAYER *player;

    for (i = 0; i < 4; i++) {
        obj = omAddObjEx(objman, 0x2000, 1, 0, -1, fn_1_8D78);
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M569_COINDROP), HU_MEMNUM_OVL);
        lbl_1_bss_56B0[i] = obj->data;
        modelId = Hu3DModelCreateData(0x7C0012);
        obj->mdlId[0] = modelId;
        player = lbl_1_bss_F8[i]->data;
        lbl_1_bss_56B0[i]->unk004 = lbl_1_data_3C0[player->unk02C];
        lbl_1_bss_56B0[i]->unk004.y = 700.0f;
        omSetTra(obj, lbl_1_bss_56B0[i]->unk004.x, lbl_1_bss_56B0[i]->unk004.y, lbl_1_bss_56B0[i]->unk004.z);
        Hu3DModelPosSetV(modelId, &lbl_1_bss_56B0[i]->unk004);
        Hu3DModelAttrSet(modelId, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(modelId, 2);
        lbl_1_bss_56B0[i]->unk018 = player->no;
        lbl_1_bss_56B0[i]->unk000 = modelId;
        lbl_1_bss_56B0[i]->unk002 = -1;
        lbl_1_bss_56B0[i]->unk010 = 0;
        lbl_1_bss_56B0[i]->unk014 = player->unk04C;
        GWMgCoinSet(player->no, player->unk04C);
    }
    fn_1_9290();
    obj = omAddObjEx(objman, 0x2000, 0, 0, -1, fn_1_8F14);
}

void fn_1_8D78(OMOBJ *obj)
{
    M569_COINDROP *work;
    M569_PLAYER *player;

    work = obj->data;
    switch (work->unk010) {
        case 0:
            obj->work[0] = 0;
            work->unk004.y -= 8.0f;
            if (work->unk004.y <= 350.0f) {
                work->unk004.y = 350.0f;
                work->unk010 = 1;
                HuAudFXPlay(0x90F);
            }
            break;
        case 1:
            if (obj->work[0]++ == 10) {
                Hu3DModelAttrReset(obj->mdlId[0], HU3D_MOTATTR_PAUSE);
                if (work->unk002 == -1) {
                    work->unk002 = fn_1_8F38(&work->unk004);
                }
                if (work->unk014 != 0) {
                    fn_1_9384(&work->unk004, 50);
                    player = lbl_1_bss_F8[work->unk018]->data;
                    fn_1_9C38(&work->unk004, player);
                }
                work->unk010 = 2;
                obj->work[0] = 0;
            }
        case 2:
            obj->work[0]++;
            if (obj->work[0] == 50 && work->unk002 != -1) {
                Hu3DParManKill(work->unk002);
                work->unk002 = -1;
            }
            break;
        case 3:
            break;
    }
    omSetTra(obj, work->unk004.x, work->unk004.y, work->unk004.z);
}

void fn_1_8F14(OMOBJ *obj)
{
    fn_1_91A0();
    fn_1_9A20();
}

HU3DPARMANID fn_1_8F38(HuVecF *pos)
{
    void *data;
    ANIMDATA *anim;
    HU3DPARMANID parManId;

    data = HuDataSelHeapReadNum(0x210002, HU_MEMNUM_OVL, HEAP_MODEL);
    anim = HuSprAnimRead(data);
    parManId = Hu3DParManCreate(anim, 20, &lbl_1_data_400);
    Hu3DParManRotSet(parManId, 0.0f, 0.0f, 0.0f);
    Hu3DParManPosSet(parManId, pos->x, pos->y, pos->z);
    Hu3DModelLayerSet(Hu3DParManModelIDGet(parManId), 5);
    Hu3DParManTimeLimitSet(parManId, 50);
    return parManId;
}

void fn_1_9014(HU3DMODEL *model, Mtx *mtx)
{
    Mtx mtx2;
    Mtx rot;
    HU3DMODEL *confModel;
    int i;
    HSFDATA *hsf;
    M569_CONFETTI *p;
    int j;
    HSFMATERIAL *mat;

    Hu3DModelObjDrawInit();
    confModel = &Hu3DData[lbl_1_bss_27BC.unk000];
    hsf = confModel->hsf;
    for (i = 0; i < 200; i++) {
        p = &lbl_1_bss_27C8[i];
        if (p->unk000 != 0) {
            PSMTXRotRad(rot, 'z', 0.017453292f * p->unk020.z);
            PSMTXRotRad(mtx2, 'x', 0.017453292f * p->unk020.x);
            PSMTXConcat(rot, mtx2, mtx2);
            PSMTXRotRad(rot, 'y', 0.017453292f * p->unk020.y);
            PSMTXConcat(rot, mtx2, mtx2);
            PSMTXTrans(rot, p->unk008.x, p->unk008.y, p->unk008.z);
            PSMTXConcat(rot, mtx2, mtx2);
            PSMTXConcat(*mtx, mtx2, mtx2);
            Hu3DModelObjDraw(lbl_1_bss_27BC.unk000, lbl_1_data_450, mtx2);
            for (j = 0, mat = hsf->material; j < hsf->materialNum; j++, mat++) {
                mat->color[0] = p->unk038.r;
                mat->color[1] = p->unk038.g;
                mat->color[2] = p->unk038.b;
            }
        }
    }
}

void fn_1_91A0(void)
{
    int i;
    M569_CONFETTI *p;

    if (lbl_1_bss_27BC.unk008 != 0) {
        for (i = 0; i < 200; i++) {
            p = &lbl_1_bss_27C8[i];
            if (p->unk000 != 0 && p->unk004 == 0) {
                PSVECAdd(&p->unk008, &p->unk014, &p->unk008);
                PSVECAdd(&p->unk020, &p->unk02C, &p->unk020);
                if (p->unk008.y <= lbl_1_bss_27BC.unk004) {
                    p->unk008.y = lbl_1_bss_27BC.unk004;
                    p->unk020.x = -90.0f;
                    p->unk020.z = 0.0f;
                    p->unk004 = 1;
                }
            }
        }
    }
}

void fn_1_9290(void)
{
    int i;

    lbl_1_bss_27BC.unk000 = Hu3DModelCreateData(0x7C0013);
    Hu3DModelAttrSet(lbl_1_bss_27BC.unk000, HU3D_ATTR_DISPOFF);
    lbl_1_bss_27BC.unk002 = Hu3DHookFuncCreate(fn_1_9014);
    Hu3DModelLayerSet(lbl_1_bss_27BC.unk002, 4);
    lbl_1_bss_27BC.unk004 = 0.1f;
    lbl_1_bss_27BC.unk008 = 0;
    for (i = 0; i < 200; i++) {
        lbl_1_bss_27C8[i].unk000 = 0;
        lbl_1_bss_27C8[i].unk004 = 0;
    }
}

void fn_1_9384(HuVecF *pos, int num)
{
    int n;
    int i;
    M569_CONFETTI *p;
    float angX;
    float radius;
    float angY;

    n = 0;
    for (i = 0; i < 200; i++) {
        if (n == num) {
            break;
        }
        p = &lbl_1_bss_27C8[i];
        if (p->unk000 == 0) {
            p->unk000 = 1;
            n++;
            lbl_1_bss_27BC.unk008++;
            radius = (s32)frandmod(4800) / 100.0f;
            angX = (s32)frandmod(360);
            angY = (s32)frandmod(360);
            p->unk008.x = pos->x + radius * (sin(3.141592653589793 * angY / 180.0) * cos(3.141592653589793 * angX / 180.0));
            p->unk008.y = pos->y + radius * -sin(3.141592653589793 * angX / 180.0);
            p->unk008.z = pos->z + radius * (cos(3.141592653589793 * angY / 180.0) * cos(3.141592653589793 * angX / 180.0));
            p->unk014.x = 0.8f * (((s32)frandmod(201) - 100) / 100.0f);
            p->unk014.y = -6.5f * ((s32)frandmod(100) / 100.0f);
            if (p->unk014.y > -2.6000001f) {
                p->unk014.y = -2.6000001f;
            }
            p->unk014.z = 0.5f * (((s32)frandmod(201) - 100) / 100.0f);
            p->unk020.x = p->unk020.y = p->unk020.z = 0.0f;
            p->unk02C.x = 14.0f * (((s32)frandmod(201) - 100) / 100.0f);
            p->unk02C.y = 14.0f * (((s32)frandmod(201) - 100) / 100.0f);
            p->unk02C.z = 14.0f * (((s32)frandmod(201) - 100) / 100.0f);
            p->unk038 = lbl_1_data_3F0[frandmod(4)];
        }
    }
}

void fn_1_986C(HU3DMODEL *model, Mtx *mtx)
{
    Mtx mtx2;
    Mtx rot;
    HSFDATA *hsf;
    HU3DMODEL *coinModel;
    int i;
    M569_COIN *coin;

    Hu3DModelObjDrawInit();
    coinModel = &Hu3DData[lbl_1_bss_178];
    hsf = coinModel->hsf;
    for (i = 0; i < 144; i++) {
        coin = &lbl_1_bss_17C[i];
        if (coin->unk000 == 0) {
            continue;
        }
        if (coin->unk040 != 0 && coin->unk004 == 0) {
            continue;
        }
        PSMTXRotRad(rot, 'z', 0.017453292f * coin->unk024.z);
        PSMTXRotRad(mtx2, 'x', 0.017453292f * coin->unk024.x);
        PSMTXConcat(rot, mtx2, mtx2);
        PSMTXRotRad(rot, 'y', 0.017453292f * coin->unk024.y);
        PSMTXConcat(rot, mtx2, mtx2);
        PSMTXScale(rot, 0.5f, 0.5f, 0.5f);
        PSMTXConcat(rot, mtx2, mtx2);
        PSMTXTrans(rot, coin->unk00C.x, coin->unk00C.y, coin->unk00C.z);
        PSMTXConcat(rot, mtx2, mtx2);
        PSMTXConcat(*mtx, mtx2, mtx2);
        Hu3DModelObjDraw(lbl_1_bss_178, lbl_1_data_459, mtx2);
    }
}

void fn_1_9A20(void)
{
    int i;
    M569_COIN *coin;

    if (lbl_1_bss_174 != 0) {
        for (i = 0; i < 144; i++) {
            coin = &lbl_1_bss_17C[i];
            if (coin->unk000 != 0 && coin->unk008 == 0) {
                if (coin->unk040 == 0) {
                    coin->unk018.y -= 1.96f;
                    PSVECAdd(&coin->unk00C, &coin->unk018, &coin->unk00C);
                    PSVECAdd(&coin->unk024, &coin->unk030, &coin->unk024);
                    if (coin->unk00C.y <= coin->unk03C) {
                        HuAudFXPlay(7);
                        CharEffectCoinGlowCreate(lbl_1_bss_34.no, &coin->unk00C);
                        coin->unk000 = 0;
                    }
                } else {
                    coin->unk040--;
                }
            }
        }
    }
}

void fn_1_9B2C(void)
{
    int i;

    lbl_1_bss_178 = Hu3DModelCreateData(0x990000);
    Hu3DModelAttrSet(lbl_1_bss_178, HU3D_ATTR_DISPOFF);
    Hu3DModelScaleSet(lbl_1_bss_178, 0.5f, 0.5f, 0.5f);
    lbl_1_bss_170 = Hu3DHookFuncCreate(fn_1_986C);
    Hu3DModelLayerSet(lbl_1_bss_170, 4);
    lbl_1_bss_174 = 0;
    for (i = 0; i < 144; i++) {
        lbl_1_bss_17C[i].unk000 = 0;
        lbl_1_bss_17C[i].unk008 = 0;
    }
}

void fn_1_9C38(HuVecF *pos, M569_PLAYER *player)
{
    int n;
    int i;
    M569_COIN *coin;
    float height;

    height = CharModelHeightGet(player->charNo);
    n = 0;
    for (i = 0; i < 144; i++) {
        if (n == player->unk04C) {
            break;
        }
        coin = &lbl_1_bss_17C[i];
        if (coin->unk000 == 0) {
            coin->unk000 = 1;
            coin->unk040 = n * 4 + 15;
            if (n == 0) {
                coin->unk004 = 1;
            } else {
                coin->unk004 = 0;
            }
            n++;
            lbl_1_bss_174++;
            coin->unk00C = *pos;
            coin->unk018.x = 0.0f;
            coin->unk018.y = 0.0f;
            coin->unk018.z = 0.0f;
            coin->unk024.x = coin->unk024.y = coin->unk024.z = 0.0f;
            coin->unk024.y = (s32)frandmod(360);
            coin->unk030.x = coin->unk030.y = coin->unk030.z = 0.0f;
            coin->unk030.y = 15.0f;
            coin->unk03C = height;
        }
    }
}
