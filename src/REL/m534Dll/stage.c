/*
 * m534dll stage: models, local lights, buttons, sounds and the hand's state
 * machine (fn_1_4A3C). Functions are in reference order. Line ranges are into
 * build/mp5-asm/m534Dll/asm/REL/m534Dll/stage.s.
 *
 * fn_1_3CAC and fn_1_3D58 copy GXColor locals from .rodata:0x14C
 * { 200, 200, 255, 0 } and .rodata:0x160 { 255, 255, 255, 0 }; write them as
 * locals. .data:0x300 "l_han_foot" and 0x30B "l_han_body" are literals in
 * fn_1_4A3C; .data:0x318 is its 13-case jump table.
 */

#include "REL/m534Dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/memory.h"

#include "dolphin/gx.h"
#include "math.h"

/* --- .data --- */

M534_PROP lbl_1_data_190[5] = {
    { 0x005C0001, { -5000.0f, 1900.0f, -4000.0f }, 0.5f, 3.0f },
    { 0x005C0002, { -1000.0f, 1700.0f, -4800.0f }, 0.45f, 2.0f },
    { 0x005C0003, { -4000.0f, 1500.0f, -6000.0f }, 0.4f, 1.5f },
    { 0x005C0004, { -2000.0f, 1300.0f, -6500.0f }, 0.35f, 1.2f },
    { 0x005C0005, { 1000.0f, 1200.0f, -7000.0f }, 0.25f, 0.8f },
};

HuVecF lbl_1_data_208[16] = {
    { -257.24f, 17.81f, 98.81f },
    { -109.67f, 17.81f, 98.81f },
    { 109.67f, 17.81f, 98.81f },
    { 257.24f, 17.81f, 98.81f },
};

/* Button object names. */
char lbl_1_data_2C8[4][8] = { "butt_ll", "butt_lr", "butt_rl", "butt_rr" };

HuVecF lbl_1_data_2E8[2] = {
    { -200.0f, 20.0f, 110.0f },
    { 200.0f, 20.0f, 110.0f },
};

/* --- .bss --- */

OMOBJ *lbl_1_bss_48;              /* stage object; data is M534_STAGE. dtk sizes this 0x8 */

/* Random factors from frand(): signed in [-1, 1) and unsigned in [0, 1). */
#define M534_FRANDS() ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768))
#define M534_FRANDU() ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF))

/* asm 9-44, 34 insns. Stage object and its 0x200 work. */
void fn_1_3360(OMOBJMAN *objman)
{
    OMOBJ *obj;
    M534_STAGE *work;

    obj = omAddObjEx(objman, 20, 28, 0, -1, fn_1_33EC);
    lbl_1_bss_48 = obj;
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M534_STAGE), HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M534_STAGE));
}

/* asm 47-49, 1 insn. Empty. */
void fn_1_33E8(void)
{
}

/* asm 52-195, 142 insns. Stage object init. */
void fn_1_33EC(OMOBJ *obj)
{
    HU3DMODELID mdlId;

    mdlId = Hu3DModelCreateData(0x5C0000);
    obj->mdlId[0] = mdlId;
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    Hu3DModelClusterAttrSet(mdlId, 0, HU3D_CLUSTER_ATTR_LOOP);
    Hu3DModelShadowMapSet(mdlId);
    Hu3DModelLayerSet(mdlId, 0);
    mdlId = Hu3DModelCreateData(0x5C000B);
    obj->mdlId[1] = mdlId;
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    Hu3DModelClusterAttrSet(mdlId, 0, HU3D_CLUSTER_ATTR_LOOP);
    Hu3DModelLayerSet(mdlId, 2);
    mdlId = Hu3DModelCreateData(0x5C0006);
    obj->mdlId[2] = mdlId;
    Hu3DModelShadowMapSet(mdlId);
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(mdlId, 0);
    mdlId = Hu3DModelCreateData(0x5C0007);
    obj->mdlId[3] = mdlId;
    Hu3DModelLayerSet(mdlId, 0);
    fn_1_3674(mdlId, 1);
    mdlId = Hu3DModelCreateData(0x5C0008);
    obj->mdlId[4] = mdlId;
    Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(mdlId, 0);
    fn_1_3AC8(obj);
    mdlId = Hu3DHookFuncCreate(fn_1_3CAC);
    obj->mdlId[26] = mdlId;
    Hu3DModelLayerSet(mdlId, 1);
    mdlId = Hu3DHookFuncCreate(fn_1_3D58);
    obj->mdlId[27] = mdlId;
    Hu3DModelLayerSet(mdlId, 3);
    fn_1_4450(obj);
    fn_1_3E04(obj);
    fn_1_3FA0(obj);
    fn_1_426C(obj);
    obj->objFunc = fn_1_3624;
}

/* asm 198-219, 20 insns. Stage object main. */
void fn_1_3624(OMOBJ *obj)
{
    fn_1_3B1C(obj);
    fn_1_3F04(obj);
    fn_1_406C(obj);
    fn_1_4A3C(obj);
    fn_1_430C(obj);
}

/* asm 222-512, 277 insns. Local lights from a model's light objects. */
void fn_1_3674(s16 mdlId, s16 staticF)
{
    Mtx mtx;
    HuVecF aim;
    HuVecF pos;
    HuVecF dir;
    HU3DMODEL *model;
    HSFDATA *hsf;
    HSFOBJECT *objTop;
    HSFOBJECT *object;
    HU3DLLIGHTID lightId;
    s16 i;
    float rotX;
    float rotY;

    model = &Hu3DData[mdlId];
    hsf = model->hsf;
    if (model->lLightId[0] == -1) {
        objTop = hsf->object;
        for (i = 0; i < hsf->objectNum; i++, objTop++) {
            object = objTop;
            if (object->type == HSF_OBJ_LIGHT) {
                dir.x = object->light.target.x - object->light.pos.x;
                dir.y = object->light.target.y - object->light.pos.y;
                dir.z = object->light.target.z - object->light.pos.z;
                lightId = Hu3DLLightCreate(mdlId, object->light.pos.x, object->light.pos.y, object->light.pos.z, dir.x, dir.y, dir.z,
                    object->light.r, object->light.g, object->light.b);
                Hu3DLLightStaticSet(mdlId, lightId, staticF);
                switch (object->light.type) {
                    case 0:
                        Hu3DLLightSpotSet(mdlId, lightId, GX_SP_COS, object->light.cutoff);
                        break;
                    case 1:
                        Hu3DLLightPointSet(mdlId, lightId, object->light.refBrightness - object->light.refDistance, 1.0f, GX_DA_MEDIUM);
                        rotX = atan2(dir.y, sqrtf(dir.x * dir.x + dir.z * dir.z));
                        rotY = atan2(-dir.x, -dir.z);
                        aim.x = aim.y = aim.z = 0.0f;
                        pos.x = pos.z = 0.0f;
                        pos.y = sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
                        mtxRot(mtx, 57.29578f * rotX, 57.29578f * rotY, 0.0f);
                        PSMTXMultVec(mtx, &pos, &pos);
                        Hu3DLLightPosAimSetV(mdlId, lightId, &pos, &aim);
                        break;
                    case 2:
                        Hu3DLLightInfinitytSet(mdlId, lightId);
                        break;
                }
            }
        }
    }
}

/* asm 515-539, 21 insns. Clear the sound slots. */
void fn_1_3AC8(OMOBJ *obj)
{
    M534_STAGE *work = obj->data;
    M534_SOUND *sound = work->sound;
    s32 i;

    for (i = 0; i < 32; i++, sound++) {
        sound->seNo = -1;
        sound->seId = -1;
    }
}

/* asm 542-581, 35 insns. Free the slots of sounds that stopped. */
void fn_1_3B1C(OMOBJ *obj)
{
    M534_STAGE *work = obj->data;
    M534_SOUND *sound = work->sound;
    s32 i;

    for (i = 0; i < 32; i++, sound++) {
        if (sound->seId != -1 && HuAudFXStatusGet(sound->seId) != 2) {
            sound->seNo = -1;
            sound->seId = -1;
        }
    }
}

/* asm 584-618, 29 insns. Play a sound in the first free slot. */
void fn_1_3BA8(OMOBJ *obj, s32 seNo)
{
    M534_STAGE *work = obj->data;
    M534_SOUND *sound = work->sound;
    s32 i;

    for (i = 0; i < 32; i++, sound++) {
        if (sound->seId == -1) {
            sound->seNo = seNo;
            sound->seId = HuAudFXPlay(seNo);
            break;
        }
    }
}

/* asm 621-661, 36 insns. Fade out every playing instance of a sound. */
void fn_1_3C1C(OMOBJ *obj, s32 seNo, s32 time)
{
    M534_STAGE *work = obj->data;
    M534_SOUND *sound = work->sound;
    s32 i;

    for (i = 0; i < 32; i++, sound++) {
        if (sound->seId != -1 && sound->seNo == seNo) {
            HuAudFXFadeOut(sound->seId, time);
        }
    }
}

/* asm 664-708, 43 insns. Hook: fog on. */
void fn_1_3CAC(HU3DMODEL *model, Mtx *mtx)
{
    GXColor color = { 200, 200, 255, 0 };
    GXSetFog(GX_FOG_PERSP_LIN, 1000.0f, 8000.0f, 10.0f, 20000.0f, color);
}

/* asm 711-755, 43 insns. Hook: fog off. */
void fn_1_3D58(HU3DMODEL *model, Mtx *mtx)
{
    GXColor color = { 255, 255, 255, 0 };
    GXSetFog(GX_FOG_NONE, 1000.0f, 8000.0f, 10.0f, 20000.0f, color);
}

/* asm 758-825, 64 insns. Background props (lbl_1_data_190). */
void fn_1_3E04(OMOBJ *obj)
{
    M534_STAGE *work = obj->data;
    M534_PROP *prop;
    HU3DMODELID mdlId;
    s32 i;
    float scale;

    for (prop = lbl_1_data_190, i = 0; i < 5; i++, prop++) {
        mdlId = Hu3DModelCreateData(prop->dataNum);
        obj->mdlId[i + 5] = mdlId;
        work->propPos[i] = prop->pos;
        work->propSpeed[i] = prop->speed;
        scale = prop->scale;
        Hu3DModelPosSetV(mdlId, &prop->pos);
        Hu3DModelScaleSet(mdlId, scale, scale, scale);
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        Hu3DModelLayerSet(mdlId, 0);
    }
}

/* asm 828-870, 39 insns. Drift the props. */
void fn_1_3F04(OMOBJ *obj)
{
    M534_STAGE *work = obj->data;
    HU3DMODELID mdlId;
    s32 i;

    for (i = 0; i < 5; i++) {
        work->propPos[i].x += work->propSpeed[i];
        mdlId = obj->mdlId[i + 5];
        Hu3DModelPosSetV(mdlId, &work->propPos[i]);
    }
}

/* asm 873-927, 51 insns. Press effect models. */
void fn_1_3FA0(OMOBJ *obj)
{
    M534_STAGE *work = obj->data;
    HU3DMODELID mdlId;
    s32 i;

    for (i = 0; i < 16; i++) {
        mdlId = Hu3DModelCreateData(0x5C000A);
        obj->mdlId[i + 10] = mdlId;
        Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_LOOP);
        Hu3DModelLayerSet(mdlId, 6);
        work->effectActive[i] = 0;
    }
}

/* asm 930-976, 42 insns. Hide press effects whose motion ended. */
void fn_1_406C(OMOBJ *obj)
{
    M534_STAGE *work = obj->data;
    HU3DMODELID mdlId;
    s32 i;

    for (i = 0; i < 16; i++) {
        if (work->effectActive[i]) {
            mdlId = obj->mdlId[i + 10];
            if (Hu3DMotionEndCheck(mdlId)) {
                Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
                work->effectActive[i] = 0;
            }
        }
    }
}

/* asm 979-1070, 86 insns. Start a free press effect at a player slot. */
void fn_1_4114(s32 slot)
{
    OMOBJ *obj = lbl_1_bss_48;
    M534_STAGE *work = obj->data;
    HU3DMODELID mdlId;
    s32 i;

    for (i = 0; i < 16; i++) {
        if (work->effectActive[i] == 0) {
            work->effectActive[i] = 1;
            mdlId = obj->mdlId[i + 10];
            Hu3DModelPosSetV(mdlId, &lbl_1_data_208[slot]);
            Hu3DModelRotSet(mdlId, 0.0f, 360.0 * M534_FRANDU(), 0.0f);
            Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_PAUSE);
            Hu3DMotionTimeSet(mdlId, 0.0f);
            break;
        }
    }
}

/* asm 1073-1117, 40 insns. Remember the buttons' rest heights. */
void fn_1_426C(OMOBJ *obj)
{
    M534_STAGE *work = obj->data;
    HU3DMODELID mdlId = obj->mdlId[0];
    HSFOBJECT *object;
    s32 i;

    for (i = 0; i < 4; i++) {
        object = Hu3DModelObjPtrGet(mdlId, lbl_1_data_2C8[i]);
        if (object != NULL) {
            work->buttonY[i] = object->mesh.base.pos.y;
        }
        work->buttonOfs[i] = 0.0f;
    }
}

/* asm 1120-1174, 50 insns. Buttons spring back. */
void fn_1_430C(OMOBJ *obj)
{
    M534_STAGE *work = obj->data;
    HU3DMODELID mdlId = obj->mdlId[0];
    HSFOBJECT *object;
    s32 i;
    float y;

    for (i = 0; i < 4; i++) {
        y = work->buttonOfs[i];
        y *= 0.5;
        work->buttonOfs[i] = y;
        y += work->buttonY[i];
        object = Hu3DModelObjPtrGet(mdlId, lbl_1_data_2C8[i]);
        if (object != NULL) {
            object->mesh.base.pos.y = y;
        }
    }
}

/* asm 1177-1211, 31 insns. Push a player's button down. */
void fn_1_43D4(s32 slot)
{
    OMOBJ *obj = lbl_1_bss_48;
    M534_STAGE *work = obj->data;

    work->buttonOfs[slot] = -12.0f;
    if (slot < 2) {
        HuAudFXPlay(1981);
    } else {
        HuAudFXPlay(1982);
    }
}

/* asm 1214-1234, 19 insns. */
void fn_1_4450(OMOBJ *obj)
{
    M534_STAGE *work = obj->data;

    work->mode = 0;
    work->pressCount = 12;
    work->rate = 0.5f;
    work->targetY = work->curY = -710.0f;
}

/* asm 1237-1345, 98 insns. A press by a player of team: score it and lift the target. */
void fn_1_449C(s32 team)
{
    OMOBJ *obj = lbl_1_bss_48;
    M534_STAGE *work = obj->data;
    s32 lead;

    if (work->mode == 4) {
        fn_1_74B0(team, 1);
        if (--work->pressCount <= 0) {
            work->pressCount = 60;
            if (work->targetY < 0.0f) {
                work->targetY += 60.0;
            }
            fn_1_5CB0(8);
            work->spray = 20;
            work->footAmp = 3.0f;
            work->bodyAmp = 0.2f;
            work->bodyAngle = 0.0f;
            lead = fn_1_4624();
            if (lead != -1) {
                fn_1_3BA8(obj, 1983);
            }
            if (lead != 1) {
                fn_1_3BA8(obj, 1984);
            }
        }
    }
}

/* asm 1348-1385, 33 insns. Compare the two teams' scores. */
s32 fn_1_4624(void)
{
    OMOBJ *obj = lbl_1_bss_48;
    M534_STAGE *work = obj->data;
    s32 score0 = fn_1_74E8(0);
    s32 score1 = fn_1_74E8(1);

    if (score0 > score1) {
        return 1;
    } else if (score0 < score1) {
        return -1;
    } else {
        return 0;
    }
}

/* asm 1388-1499, 104 insns. Unreferenced in every unit (inlined into fn_1_4A3C): lean from the score difference. */
float fn_1_46A8(void)
{
    OMOBJ *obj = lbl_1_bss_48;
    M534_STAGE *work = obj->data;
    float score1 = fn_1_74E8(1);
    float diff = fn_1_74E8(0) - score1;

    if (diff >= 0.0) {
        if (diff <= 4.0) {
            diff = 0.0f;
        } else {
            diff -= 4.0;
        }
    } else {
        if (diff >= -4.0) {
            diff = 0.0f;
        } else {
            diff += 4.0;
        }
    }
    diff *= 5.0;
    if (diff > 20.0) {
        diff = 20.0f;
    }
    if (diff < -20.0) {
        diff = -20.0f;
    }
    return diff;
}

/* asm 1502-1584, 74 insns. How far the tilt has gone, 0 to 1. */
float fn_1_4848(void)
{
    OMOBJ *obj = lbl_1_bss_48;
    M534_STAGE *work = obj->data;
    float t = 0.0f;

    if (fn_1_4624() != 0) {
        t = work->rotX / 76.0;
    } else {
        t = work->rotZ / 90.0;
    }
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        t = 1.0f;
    }
    return t;
}

/* asm 1587-1609, 19 insns. Unreferenced in every unit. */
void fn_1_4970(void)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        omVibrate(i, 40, 12, 0);
    }
}

/* asm 1612-1629, 16 insns. */
BOOL fn_1_49BC(void)
{
    OMOBJ *obj = lbl_1_bss_48;
    M534_STAGE *work = obj->data;
    return work->mode == 12;
}

/* asm 1632-1649, 16 insns. */
BOOL fn_1_49FC(void)
{
    OMOBJ *obj = lbl_1_bss_48;
    M534_STAGE *work = obj->data;
    return work->mode == 8;
}

/* asm 1652-2824, 1098 insns. Stage state machine; 13-case switch (.data:0x318). */
void fn_1_4A3C(OMOBJ *obj)
{
    M534_STAGE *work = obj->data;
    HuVecF pos;
    HSFOBJECT *object;
    HU3DMODELID mdlId;
    s32 lead;
    s32 done;
    float t;
    float step;

    switch (work->mode) {
        case 0:
            if (fn_1_16AC() == 5) {
                Hu3DModelAttrReset(obj->mdlId[2], HU3D_MOTATTR_PAUSE);
                fn_1_4970();
                work->mode = 1;
            }
            break;
        case 1:
            fn_1_5B64();
            if (fn_1_16AC() == 6) {
                work->mode = 2;
                work->time = 0;
                work->rate = 0.1f;
                work->targetY = -400.0f;
                Hu3DModelAttrReset(obj->mdlId[4], HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrReset(obj->mdlId[4], HU3D_ATTR_DISPOFF);
                work->splashActive = 1;
                HuAudFXPlay(1980);
            }
            break;
        case 2:
            if ((++work->time & 1) == 0) {
                fn_1_5B64();
            }
            if (work->curY < -500.0) {
                Hu3DModelShadowSet(obj->mdlId[3]);
                work->footAmp = 3.0f;
                work->bodyAmp = 0.2f;
                work->bodyAngle = 0.0f;
            }
            if (!(work->curY < -400.1)) {
                work->rate = 0.02f;
                work->mode = 3;
            }
            break;
        case 3:
            work->spray = 5;
            if (fn_1_1694() == 2) {
                work->mode = 4;
                work->time = 0;
            }
            break;
        case 4:
            if (fn_1_1694() != 3) {
                if (!fn_1_179C()) {
                    work->rotY += 0.1 * (fn_1_46A8() - work->rotY);
                }
            } else {
                work->mode = 5;
                work->time = 0;
                work->centerY = Center.y;
                lead = fn_1_4624();
                if (lead != -1) {
                    fn_1_3BA8(obj, 1983);
                }
                if (lead != 1) {
                    fn_1_3BA8(obj, 1984);
                }
            }
            break;
        case 5:
            work->bodyAmp = 0.15f;
            work->bodyAngle = 0.0f;
            if ((++work->time & 3) == 0) {
                fn_1_5CB0(3);
                work->spray = 8;
                work->footAmp = 5.0f;
                work->targetY += 20.0;
                if (!(work->targetY < 0.0f)) {
                    work->targetY = 0.0f;
                    work->mode = 6;
                    work->time = 0;
                    fn_1_3C1C(obj, 1983, 500);
                    fn_1_3C1C(obj, 1984, 500);
                }
            }
            break;
        case 6:
            work->bodyAmp = 0.1f;
            work->mode = 7;
            work->time = 0;
            break;
        case 7:
            work->bodyAmp = 0.1f;
            if (!(++work->time < 42.0)) {
                work->mode = 8;
                work->time = 0;
            }
            break;
        case 8:
            work->speed -= 0.1;
            if (fn_1_4624() != 0) {
                work->rotX += work->speed;
                if (work->rotX > -40.0) {
                    break;
                }
            } else {
                work->rotY += 0.1 * (90.0f - work->rotY);
                work->rotZ += work->speed;
                if (work->rotZ > -40.0) {
                    break;
                }
            }
            work->mode = 9;
            work->time = 0;
            break;
        case 9:
            work->speed += 0.2;
            if (work->speed > 0.0f) {
                work->speed = 0.0f;
            }
            lead = fn_1_4624();
            if (lead != 0) {
                work->rotX += work->speed;
            } else {
                work->rotY += 0.1 * (90.0f - work->rotY);
                work->rotZ += work->speed;
            }
            if (!(work->speed < 0.0f)) {
                if (++work->time >= 15) {
                    work->mode = 10;
                    work->time = 0;
                    work->seId = -1;
                }
            }
            break;
        case 10:
            done = FALSE;
            lead = fn_1_4624();
            work->speed += 0.3;
            if (lead != 0) {
                work->rotX += work->speed;
                if (work->rotX >= 76.0) {
                    work->footAmp = work->bodyAmp = 0.0f;
                    work->rotX = 76.0f;
                    work->speed = 0.5 * -work->speed;
                    if (work->speed < -1.0) {
                        work->shake = -20.0 * work->speed;
                    } else {
                        done = TRUE;
                    }
                }
                if (work->rotX >= 61.0) {
                    if (++work->time < 10) {
                        if (lead == -1) {
                            fn_1_5E20(2, &lbl_1_data_2E8[0]);
                        } else {
                            fn_1_5E20(2, &lbl_1_data_2E8[1]);
                        }
                    }
                }
                t = 20.0f * lead;
                work->rotY += 0.05 * (t - work->rotY);
                if (work->seId == -1 && work->rotX >= 50.0) {
                    if (lead == -1) {
                        work->seId = HuAudFXPlay(1985);
                    }
                    if (lead == 1) {
                        work->seId = HuAudFXPlay(1986);
                    }
                }
            } else {
                work->rotZ += work->speed;
                if (work->rotZ >= 90.0) {
                    work->footAmp = work->bodyAmp = 0.0f;
                    work->rotZ = 90.0f;
                    work->speed = 0.3 * -work->speed;
                    if (work->speed < -1.0) {
                        work->shake = -20.0 * work->speed;
                    } else {
                        done = TRUE;
                    }
                }
                if (work->rotZ >= 75.0) {
                    if (++work->time < 10) {
                        fn_1_5E20(2, &lbl_1_data_2E8[0]);
                        fn_1_5E20(2, &lbl_1_data_2E8[1]);
                    }
                }
                work->rotY += 0.1 * (90.0f - work->rotY);
                if (work->seId == -1 && work->rotZ >= 60.0) {
                    work->seId = HuAudFXPlay(1985);
                    work->seId = HuAudFXPlay(1986);
                }
            }
            if (done) {
                work->mode = 11;
                work->time = 0;
            }
            break;
        case 11:
            if (0.0f == work->shake) {
                work->mode = 12;
                work->time = 0;
                Center.y = work->centerY;
            }
            break;
        case 12:
            break;
    }
    if (work->shake >= 1.0) {
        Center.y = work->centerY + work->shake * sin(M_PI * work->shakeAngle / 180.0);
        work->shakeAngle += 70.0f;
        work->shake *= 0.9;
    } else {
        work->shake = 0.0f;
    }
    work->curY += work->rate * (work->targetY - work->curY);
    work->footAmp = 0.98 * work->footAmp;
    work->footAngle += 70.0f;
    work->bodyAmp = 0.98 * work->bodyAmp;
    work->bodyAngle += 8.0f;
    mdlId = obj->mdlId[3];
    object = Hu3DModelObjPtrGet(mdlId, "l_han_foot");
    if (object != NULL) {
        object->mesh.base.pos.x = work->footAmp * sin(M_PI * work->footAngle / 180.0);
        object->mesh.base.pos.y = work->curY;
        object->mesh.base.rot.y = work->rotY;
    }
    object = Hu3DModelObjPtrGet(mdlId, "l_han_body");
    if (object != NULL) {
        object->mesh.base.rot.x = work->rotX + 2.0 * (work->footAmp * sin(M_PI * work->bodyAngle / 180.0));
        object->mesh.base.rot.z = work->rotZ + work->bodyAmp * sin(M_PI * work->bodyAngle / 180.0);
    }
    if (work->splashActive) {
        mdlId = obj->mdlId[4];
        if (Hu3DMotionEndCheck(mdlId)) {
            Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
            work->splashActive = 0;
        } else {
            pos.x = 0.0f;
            pos.y = work->curY;
            pos.z = 0.0f;
            Hu3DModelPosSetV(mdlId, &pos);
        }
    }
    if (work->spray > 0) {
        step = 2.0f;
        for (t = work->spray; t > 0.0f; t -= step) {
            fn_1_5F94();
        }
        work->spray -= 1.0;
    }
}

/* asm 2827-2911, 83 insns. One dust particle near the stage. */
void fn_1_5B64(void)
{
    HuVecF pos;

    pos.x = 250.0 * M534_FRANDS();
    pos.y = 80.0 + 100.0 * M534_FRANDS();
    pos.z = 250.0 * M534_FRANDS() - 500.0;
    fn_1_6458(&pos);
}

/* asm 2914-3009, 92 insns. */
void fn_1_5CB0(s32 num)
{
    HuVecF pos;
    s32 i;

    for (i = 0; i < num; i++) {
        pos.x = 150.0 * M534_FRANDS();
        pos.y = 50.0 * M534_FRANDS() - 50.0;
        pos.z = 150.0 * M534_FRANDS() - 500.0;
        fn_1_6458(&pos);
    }
}

/* asm 3012-3108, 93 insns. */
void fn_1_5E20(s32 num, HuVecF *base)
{
    HuVecF pos;
    s32 i;

    for (i = 0; i < num; i++) {
        pos.x = base->x + 100.0 * M534_FRANDS();
        pos.y = base->y + 100.0 * M534_FRANDS();
        pos.z = base->z + 100.0 * M534_FRANDS();
        fn_1_6458(&pos);
    }
}

/* asm 3111-3338, 224 insns. Spray a pair of particles off the stage's two sides. */
void fn_1_5F94(void)
{
    M534_STAGE *work = lbl_1_bss_48->data;
    HuVecF pos;
    HuVecF vel;
    float s;
    float c;
    float dist;
    float r;
    float angle;

    pos.y = work->curY + (640.0 + 10.0 * M534_FRANDS());
    vel.y = 0.2 * M534_FRANDU() - 1.5;
    angle = work->rotY;
    s = sin(M_PI * angle / 180.0);
    c = cos(M_PI * angle / 180.0);
    if (fabs(angle) < 8.0) {
        dist = 130.0f;
    } else {
        dist = 140.0f;
    }
    r = 200.0 * M534_FRANDS();
    pos.x = c * -dist + s * r;
    pos.z = s * -dist + c * r - 500.0;
    vel.x = -5.0 * c;
    vel.z = -5.0 * s;
    fn_1_6938(&pos, &vel);
    r = 200.0 * M534_FRANDS();
    pos.x = c * dist + s * r;
    pos.z = s * dist + c * r - 500.0;
    vel.x = 5.0 * c;
    vel.z = 5.0 * s;
    fn_1_6938(&pos, &vel);
}
