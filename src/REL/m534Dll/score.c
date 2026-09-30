/*
 * m534dll team score boards. Functions are in reference order. Line ranges
 * are into build/mp5-asm/m534Dll/asm/REL/m534Dll/score.s.
 * .data:0x3B8 "itemhook_sao" is a literal in fn_1_6EE0.
 */

#include "REL/m534Dll.h"

#include "game/data.h"
#include "game/memory.h"

#include "math.h"

/* --- .data --- */

u32 lbl_1_data_350[2] = { 0x005C0010, 0x005C0011 };

/* Hu3DAnimCreate object names for the three digits. */
char lbl_1_data_358[3][8] = { "pos01", "pos02", "pos03" };

HuVecF lbl_1_data_370[2] = { { -800.0f, 800.0f, -600.0f }, { 800.0f, 800.0f, -600.0f } };
HuVecF lbl_1_data_388[2] = { { -250.0f, 280.0f, -100.0f }, { 250.0f, 280.0f, -100.0f } };
HuVecF lbl_1_data_3A0[2] = { { -360.0f, 340.0f, -270.0f }, { 360.0f, 340.0f, -270.0f } };

/* --- .bss --- */

OMOBJ *lbl_1_bss_58;              /* score object; data is M534_SCORE[2] */

/* asm 9-48, 38 insns. Called from ObjectSetup. */
void fn_1_6BDC(OMOBJMAN *objman)
{
    OMOBJ *obj;
    M534_SCORE *work;

    obj = omAddObjEx(objman, 50, 4, 0, -1, fn_1_6C78);
    lbl_1_bss_58 = obj;
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M534_SCORE) * 2, HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M534_SCORE) * 2);
    obj->stat |= OM_STAT_MODELPAUSE;
}

/* asm 51-53, 1 insn. Empty. */
void fn_1_6C74(void)
{
}

/* asm 56-74, 17 insns. Score object init. */
void fn_1_6C78(OMOBJ *obj)
{
    fn_1_6CF4(obj);
    fn_1_6EE0(obj);
    obj->objFunc = fn_1_6CBC;
}

/* asm 77-92, 14 insns. Score object main. */
void fn_1_6CBC(OMOBJ *obj)
{
    fn_1_6DEC(obj);
    fn_1_6FE8(obj);
}

/* asm 95-162, 62 insns. Score board models and their digit animations. */
void fn_1_6CF4(OMOBJ *obj)
{
    M534_SCORE *work = obj->data;
    void *data;
    M534_SCORE *score;
    HU3DMODELID mdlId;
    s32 i;
    s32 j;

    data = HuDataSelHeapReadNum(0x960032, HU_MEMNUM_OVL, HEAP_MODEL);
    for (i = 0; i < 2; i++) {
        score = &work[i];
        mdlId = Hu3DModelCreateData(lbl_1_data_350[i]);
        obj->mdlId[i] = mdlId;
        Hu3DModelLayerSet(mdlId, 0);
        for (j = 0; j < 3; j++) {
            score->animId[j] = Hu3DAnimCreate(data, mdlId, lbl_1_data_358[j]);
            Hu3DAnimAttrSet(score->animId[j], 1);
        }
    }
}

/* asm 165-230, 61 insns. Digits (clamped to 999). */
void fn_1_6DEC(OMOBJ *obj)
{
    M534_SCORE *work = obj->data;
    M534_SCORE *score;
    s32 i;
    s32 value;

    for (i = 0; i < 2; i++) {
        score = &work[i];
        value = score->score;
        if (value > 999) {
            value = 999;
        }
        Hu3DAnimBankSet(score->animId[0], (u16)(value / 100));
        value %= 100;
        Hu3DAnimBankSet(score->animId[1], (u16)(value / 10));
        Hu3DAnimBankSet(score->animId[2], (u16)(value % 10));
    }
}

/* asm 233-304, 66 insns. */
void fn_1_6EE0(OMOBJ *obj)
{
    M534_SCORE *work = obj->data;
    HU3DMODELID linkMdlId;
    HU3DMODELID mdlId;
    HU3DMOTID motId;
    s32 i;

    for (i = 0; i < 2; i++) {
        if (i == 0) {
            linkMdlId = Hu3DModelCreateData(0x5C000E);
            mdlId = linkMdlId;
            motId = Hu3DJointMotionData(mdlId, 0x5C000F);
        } else {
            mdlId = Hu3DModelLink(linkMdlId);
        }
        obj->mdlId[i + 2] = mdlId;
        Hu3DMotionSet(mdlId, motId);
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        Hu3DModelLayerSet(mdlId, 0);
        Hu3DModelHookSet(mdlId, "itemhook_sao", obj->mdlId[i]);
        Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
    }
}

/* asm 307-624, 306 insns. */
void fn_1_6FE8(OMOBJ *obj)
{
    M534_SCORE *work = obj->data;
    HuVecF pos;
    M534_SCORE *score;
    HU3DMODELID mdlId;
    s32 i;
    float t;

    for (i = 0; i < 2; i++) {
        score = &work[i];
        mdlId = obj->mdlId[i + 2];
        switch (score->mode) {
            case 0:
                score->amp = 20.0f;
                score->angle = 90.0f * i;
                score->pos = lbl_1_data_370[i];
                score->mode++;
                break;
            case 1:
                if (fn_1_179C() && fn_1_17C8()) {
                    Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
                    score->t = 0.0f;
                    score->mode++;
                }
                break;
            case 2:
                score->t += 0.02;
                if (score->t > 1.0) {
                    score->t = 1.0f;
                }
                t = sin((M_PI / 2) * score->t);
                score->pos.x = lbl_1_data_370[i].x + t * (lbl_1_data_388[i].x - lbl_1_data_370[i].x);
                score->pos.y = lbl_1_data_370[i].y + t * (lbl_1_data_388[i].y - lbl_1_data_370[i].y);
                score->pos.z = lbl_1_data_370[i].z + t * (lbl_1_data_388[i].z - lbl_1_data_370[i].z);
                if (fn_1_49FC()) {
                    score->t = 0.0f;
                    score->mode++;
                }
                break;
            case 3:
                score->t += 0.02;
                if (score->t > 1.0) {
                    score->t = 1.0f;
                }
                t = score->t;
                score->pos.x = lbl_1_data_388[i].x + t * (lbl_1_data_3A0[i].x - lbl_1_data_388[i].x);
                score->pos.y = lbl_1_data_388[i].y + t * (lbl_1_data_3A0[i].y - lbl_1_data_388[i].y);
                score->pos.z = lbl_1_data_388[i].z + t * (lbl_1_data_3A0[i].z - lbl_1_data_388[i].z);
                break;
        }
        score->angle += 1.0;
        PSVECAdd(&score->pos, &score->vel, &score->pos);
        pos.x = score->pos.x + score->amp * sin(M_PI * score->angle / 180.0);
        pos.y = score->pos.y + score->amp * cos(M_PI * score->angle / 180.0);
        pos.z = score->pos.z;
        Hu3DModelPosSetV(mdlId, &pos);
        Hu3DModelRotSetV(mdlId, &score->rot);
    }
}

/* asm 627-642, 14 insns. */
void fn_1_74B0(s32 team, s32 add)
{
    M534_SCORE *work = lbl_1_bss_58->data;
    work[team].score += add;
}

/* asm 645-658, 12 insns. */
s32 fn_1_74E8(s32 team)
{
    M534_SCORE *work = lbl_1_bss_58->data;
    return work[team].score;
}
