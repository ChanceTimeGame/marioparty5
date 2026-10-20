/*
 * m523dll's player half. SKELETON (W1): every function is an empty stub in
 * reference order; the bodies are W2 work. Do not reorder.
 *
 * Line ranges are into build/mp5-asm/m523Dll/asm/REL/m523Dll/player.s. Calls
 * to fn_1_3178/3244/3368/34D8 are the framework's MgPlayerConfSet,
 * MgVecApproach, MgAngleApproach and MgVecOrbit (declared in REL/m523Dll.h).
 *
 * Unreferenced in both units (nothing calls, stores or takes their address):
 * fn_1_3914, fn_1_40BC, fn_1_4110, fn_1_41F8, fn_1_427C, fn_1_43A4, fn_1_4590,
 * fn_1_4700, fn_1_59F0, fn_1_61E0, fn_1_7198, fn_1_7654. They are still
 * written, not stubbed (plan pitfall 7).
 */

#include "REL/m523Dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"

#include "datadir_enum.h"

#include "math.h"


/* --- .rodata tables --- */

/* Indexed by character number: which UFO model set a player gets. */
const s16 lbl_1_rodata_F0[14] = { 1, 1, 0, 1, 1, 0, 0, 2, 2, 2, 2, 2, 2, 0 };

/* UFO model, then its three joint motions, per UFO set. */
const s32 lbl_1_rodata_10C[3] = {
    DATANUM(DATA_m523, 0x06), DATANUM(DATA_m523, 0x07), DATANUM(DATA_m523, 0x08)
};
const s32 lbl_1_rodata_118[3] = {
    DATANUM(DATA_m523, 0x09), DATANUM(DATA_m523, 0x0A), DATANUM(DATA_m523, 0x0B)
};
const s32 lbl_1_rodata_124[3] = {
    DATANUM(DATA_m523, 0x0C), DATANUM(DATA_m523, 0x0D), DATANUM(DATA_m523, 0x0E)
};
const s32 lbl_1_rodata_130[3] = {
    DATANUM(DATA_m523, 0x0F), DATANUM(DATA_m523, 0x10), DATANUM(DATA_m523, 0x11)
};

const s32 lbl_1_rodata_13C[3] = {
    DATANUM(DATA_m523, 0x15), DATANUM(DATA_m523, 0x16), DATANUM(DATA_m523, 0x17)
};

/*
 * fn_1_85A8 and fn_1_90EC copy four-int tables from .rodata:0x240
 * { 0, 0, 35, 25 } and .rodata:0x260 { 10, 15, 20, 20 } into locals on entry;
 * write those as local initialized arrays, not globals.
 */

/* --- .data --- */

/* Solo player's motions, terminated for CharModelMotListCreate. */
u32 lbl_1_data_208[9] = {
    0x008C0000, 0x008C0001, 0x008C0002, 0x008C001B, 0x008C0019, 0x008C002B, 0x008C0051, 0x008C0006, 0
};

/* Team players' motions, terminated; the trailing word is part of dtk's object. */
u32 lbl_1_data_22C[7] = { 0x008C004D, 0x008C0017, 0x008C002F, 0x008C0000, 0x008C003F, 0, 0x00080005 };

HuVecF lbl_1_data_248[4] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, -300.0f },
    { -350.0f, 0.0f, 200.0f },
    { 350.0f, 0.0f, 200.0f },
};

HuVecF lbl_1_data_278[4] = {
    { 0.0f, 0.0f, 150.0f },
    { -350.0f, 0.0f, -300.0f },
    { 0.0f, 0.0f, -300.0f },
    { 350.0f, 0.0f, -300.0f },
};

HuVecF lbl_1_data_2A8[3] = {
    { 0.0f, 0.0f, 200.0f },
    { -350.0f, 0.0f, -250.0f },
    { 350.0f, 0.0f, -250.0f },
};

/* Row per M523_PLAYER.motNo; motNo[0] for the solo player, [1] for the team. */
M523_MOTION lbl_1_data_2CC[11] = {
    { { 0, 0 }, 10.0f, HU3D_MOTATTR_LOOP },
    { { 1, -1 }, 10.0f, HU3D_MOTATTR_LOOP },
    { { 2, -1 }, 10.0f, HU3D_MOTATTR_LOOP },
    { { 3, -1 }, 10.0f, HU3D_MOTATTR_NONE },
    { { 4, -1 }, 10.0f, HU3D_MOTATTR_LOOP },
    { { 5, -1 }, 10.0f, HU3D_MOTATTR_LOOP },
    { { 6, -1 }, 10.0f, HU3D_MOTATTR_LOOP },
    { { -1, 1 }, 10.0f, HU3D_MOTATTR_LOOP },
    { { 7, 2 }, 10.0f, HU3D_MOTATTR_NONE },
    { { -1, 3 }, 10.0f, HU3D_MOTATTR_LOOP },
    { { -1, 4 }, 10.0f, HU3D_MOTATTR_NONE },
};

/*
 * .data:0x350 "itemhook_ufo" and .data:0x394 "cyl10" are string literals in
 * fn_1_39DC and fn_1_9978; .data:0x360 is fn_1_6294's switch jump table.
 */

/* --- .bss --- */

M523_NODE lbl_1_bss_E8;                          /* list tail sentinel */
M523_NODE lbl_1_bss_10C;                         /* list head sentinel */
int lbl_1_bss_130[M523_TEAM_MAX];                /* slot-in-use flags */
M523_PLAYER *lbl_1_bss_13C;                      /* the solo player */
M523_PLAYER *lbl_1_bss_140[M523_PLAYER_MAX];
HuVecF lbl_1_bss_150[10];

/* asm 9-62, 50 insns. Unreferenced: create one player object and its 0xB0 work. */
OMOBJ *fn_1_3914(s16 no)
{
    OMOBJ *obj;

    if (no == 0) {
        obj = omAddObjEx(objman, (s16)(no + 0x1000), 3, 5, OM_GRP_NONE, fn_1_4900);
    } else {
        obj = omAddObjEx(objman, (s16)(no + 0x1000), 3, 8, OM_GRP_NONE, fn_1_5CB8);
    }

    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M523_PLAYER), HU_MEMNUM_OVL);
    memset(obj->data, 0, sizeof(M523_PLAYER));
    return obj;
}

/* asm 65-431, 355 insns. Called by fn_1_12C: create all four players. */
void fn_1_39DC(void)
{
    OMOBJ *obj;
    M523_PLAYER *player;
    HU3DMODELID modelId, ufoModelId, extraModelId;
    s16 grp;
    s16 ufoSet;
    s16 teamSide = 1;
    int i;

    for (i = 0; i < 4; i++) {
        grp = GwPlayerConf[i].grp;

        if (grp == 0) {
            obj = omAddObjEx(objman, (s16)(grp + 0x1000), 3, 5, OM_GRP_NONE, fn_1_4900);
        } else {
            obj = omAddObjEx(objman, (s16)(grp + 0x1000), 3, 8, OM_GRP_NONE, fn_1_5CB8);
        }

        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M523_PLAYER), HU_MEMNUM_OVL);
        memset(obj->data, 0, sizeof(M523_PLAYER));

        player = obj->data;
        lbl_1_bss_140[i] = player;

        MgPlayerConfSet((MGFPLAYER *)player, (s16)i);
        player->obj = obj;
        player->targetNo = -1;
        player->node = NULL;
        player->unk80 = 0;
        player->unk82 = 0;
        player->unk84 = 0;
        player->seNo = -1;
        player->unk54 = 0;
        player->unk9C = 0;
        player->unk74.x = player->unk74.y = player->unk74.z = 0.0f;
        player->vel.x = player->vel.y = player->vel.z = 0.0f;
        player->comTarget.x = player->comTarget.y = player->comTarget.z = 0.0f;

        if (player->grp == 0) {
            lbl_1_bss_13C = player;
            player->side = 0;
            player->radius = 50.0f;
            player->pos = lbl_1_data_248[1];
            player->mode = 0xE;
            player->comMode = 0;
            player->unk9C = 0;

            modelId = CharModelMotListCreate(player->charNo, 2, (unsigned int *)lbl_1_data_208, obj->mtnId);
            obj->mdlId[0] = modelId;
            CharMotionSet(player->charNo, obj->mtnId[0]);
            Hu3DModelLayerSet(modelId, 4);
            Hu3DModelShadowSet(modelId);
        } else {
            omSetStatBit(obj, OM_STAT_MODELPAUSE);
            player->side = teamSide;
            teamSide++;
            player->radius = 150.0f;

            fn_1_5AFC(player);

            player->startPos = player->pos;
            player->mode = 0x13;
            player->comMode = 0;
            player->unk9C = 0x1E;

            modelId = CharModelMotListCreate(player->charNo, 2, (unsigned int *)lbl_1_data_22C, obj->mtnId);
            obj->mdlId[0] = modelId;
            CharMotionSet(player->charNo, obj->mtnId[0]);
            Hu3DModelLayerSet(modelId, 4);
            Hu3DModelShadowSet(modelId);
            CharMotionVoiceOnSet(player->charNo, (s16)lbl_1_data_22C[4], FALSE);

            ufoSet = lbl_1_rodata_F0[player->charNo];
            ufoModelId = Hu3DModelCreateData(lbl_1_rodata_10C[ufoSet]);
            Hu3DModelAttrSet(ufoModelId, HU3D_MOTATTR_LOOP);
            obj->mdlId[1] = ufoModelId;
            Hu3DModelLayerSet(ufoModelId, 4);
            Hu3DModelShadowSet(ufoModelId);
            Hu3DModelHookSet(ufoModelId, "itemhook_ufo", obj->mdlId[0]);
            player->ufoMdlId = ufoModelId;
            player->ufoMotId[0] = Hu3DMotionIDGet(ufoModelId);
            player->ufoMotId[1] = Hu3DJointMotionData(ufoModelId, lbl_1_rodata_118[ufoSet]);
            player->ufoMotId[2] = Hu3DJointMotionData(ufoModelId, lbl_1_rodata_124[ufoSet]);
            player->ufoMotId[3] = Hu3DJointMotionData(ufoModelId, lbl_1_rodata_130[ufoSet]);
            Hu3DModelPosSetV(obj->mdlId[1], &player->pos);
            Hu3DModelRotSetV(obj->mdlId[1], &player->rot);

            extraModelId = Hu3DModelCreateData(DATANUM(DATA_m523, 0x12));
            Hu3DModelAttrSet(extraModelId, HU3D_MOTATTR_PAUSE);
            obj->mdlId[2] = extraModelId;
            Hu3DModelLayerSet(extraModelId, 4);
            Hu3DModelPosSetV(obj->mdlId[2], &player->pos);
            Hu3DModelRotSetV(obj->mdlId[2], &player->rot);
        }

        player->motNo = -1;
        fn_1_3F68(obj, 0);
    }

    CharEffectLayerSet(5);
    fn_1_9574();

    for (i = 0; i < 3; i++) {
        lbl_1_bss_130[i] = 0;
    }

    for (i = 0; i < 10; i++) {
        lbl_1_bss_150[i].x = 0.0f;
        lbl_1_bss_150[i].y = 0.0f;
        lbl_1_bss_150[i].z = 0.0f;
    }
}

/* asm 434-499, 61 insns. Set a lbl_1_data_2CC motion row. */
void fn_1_3F68(OMOBJ *obj, s16 motNo)
{
    M523_PLAYER *player = obj->data;
    s16 idx;

    if (player->motNo != motNo) {
        if (player->side == 0) {
            idx = lbl_1_data_2CC[motNo].motNo[0];
        } else {
            idx = lbl_1_data_2CC[motNo].motNo[1];
        }

        CharMotionShiftSet(player->charNo, obj->mtnId[idx], 0.0f, lbl_1_data_2CC[motNo].shift, lbl_1_data_2CC[motNo].attr);
        player->motNo = motNo;
    }
}

/* asm 502-529, 24 insns. Called by fn_1_674. */
void fn_1_405C(void)
{
    int i;

    for (i = 0; i < 4; i++) {
        lbl_1_bss_140[i]->mode = 1;
        lbl_1_bss_140[i]->unk54 = 0;
    }
}

/* asm 532-556, 21 insns. Unreferenced: dispatch fn_1_4CCC / fn_1_6294 by side. */
void fn_1_40BC(OMOBJ *obj)
{
    M523_PLAYER *player = obj->data;

    if (player->side == 0) {
        fn_1_4CCC(obj);
    } else {
        fn_1_6294(obj);
    }
}

/* asm 559-621, 58 insns. Unreferenced. */
void fn_1_4110(M523_PLAYER *player)
{
    float limit;
    HuVecF dir;

    if (player->side == 0) {
        limit = player->radius;
    } else {
        limit = player->radius - 50.0f;
    }

    PSVECAdd(&player->pos, &player->vel, &dir);
    dir.y = 0.0f;

    if (PSVECMag(&dir) > 800.0f - limit) {
        PSVECNormalize(&dir, &dir);
        PSVECScale(&dir, &dir, 800.0f - limit);
        PSVECSubtract(&dir, &player->pos, &player->vel);
        player->vel.y = 0.0f;
    }
}

/* asm 624-659, 33 insns. Unreferenced. */
void fn_1_41F8(HuVecF *vec, float max)
{
    if (PSVECMag(vec) > 800.0f - max) {
        PSVECNormalize(vec, vec);
        PSVECScale(vec, vec, 800.0f - max);
    }
}

/* asm 662-741, 74 insns. Unreferenced. */
void fn_1_427C(M523_PLAYER *player)
{
    HuVecF diff;
    int i;
    M523_PLAYER *other;

    PSVECSubtract(&player->unk5C, &player->pos, &diff);

    if (PSVECMag(&diff) < 0.01f) {
        return;
    }

    for (i = 0; i < 4; i++) {
        other = lbl_1_bss_140[i];

        if (player == other) {
            continue;
        }
        if (other == lbl_1_bss_13C) {
            continue;
        }
        if (other->mode == 6) {
            continue;
        }

        PSVECSubtract(&player->pos, &other->pos, &diff);

        if (PSVECMag(&diff) >= player->radius + other->radius) {
            continue;
        }

        PSVECNormalize(&diff, &diff);
        PSVECScale(&diff, &diff, player->radius + other->radius);
        PSVECAdd(&other->pos, &diff, &player->pos);
        player->pos.y = 0.0f;
    }
}

/* asm 744-847, 100 insns. Unreferenced: stick read into stkX/stkY, returns a magnitude. */
float fn_1_43A4(M523_PLAYER *player)
{
    float sum;
    float mag;

    player->stkX = HuPadStkX[player->padNo];
    player->stkY = -HuPadStkY[player->padNo];

    sum = (float)(HuSquare(player->stkX) + HuSquare(player->stkY));
    mag = sqrtf(sum);

    return mag;
}

/* asm 850-875, 23 insns. Effect object: kill when its motion ends. */
void fn_1_4534(OMOBJ *obj)
{
    if (Hu3DMotionEndCheck(obj->mdlId[0])) {
        Hu3DModelKill(obj->mdlId[0]);
        omDelObjEx(objman, obj);
    }
}

/* asm 878-928, 49 insns. Unreferenced: effect at pos (fn_1_4534). */
void fn_1_4590(HuVecF *pos)
{
    OMOBJ *obj;
    HU3DMODELID modelId;

    modelId = Hu3DModelCreateData(DATANUM(DATA_m523, 0x14));
    Hu3DModelLayerSet(modelId, 5);

    obj = omAddObjEx(objman, 0x1400, 1, 0, OM_GRP_NONE, fn_1_4534);
    obj->mdlId[0] = modelId;

    pos->y = 530.0f;
    omSetTra(obj, pos->x, pos->y, pos->z);

    fn_1_F34(pos, 0x74D);
}

/* asm 931-976, 43 insns. Effect object: follow bss_140[work[0]], free bss_130[work[1]] at the end. */
void fn_1_4654(OMOBJ *obj)
{
    M523_PLAYER *target;

    if (Hu3DMotionEndCheck(obj->mdlId[0])) {
        lbl_1_bss_130[obj->work[1]] = 0;
        Hu3DModelKill(obj->mdlId[0]);
        omDelObjEx(objman, obj);
    }

    target = lbl_1_bss_140[obj->work[0]];
    omSetTra(obj, target->pos.x, target->pos.y, target->pos.z);
}

/* asm 979-1071, 86 insns. Unreferenced: effect on a free bss_130 slot (fn_1_4654). */
void fn_1_4700(M523_PLAYER *player)
{
    OMOBJ *obj;
    HU3DMODELID modelId;
    s16 freeList[3];
    s16 freeCount;
    s16 i;
    s16 slot;

    freeCount = 0;
    for (i = 0; i < 3; i++) {
        if (lbl_1_bss_130[i] == 0) {
            freeList[freeCount++] = i;
        }
    }

    if (freeCount == 0) {
        slot = 0;
    } else {
        slot = freeList[frandmod(freeCount)];
    }

    lbl_1_bss_130[slot] = 1;

    modelId = Hu3DModelCreateData(lbl_1_rodata_13C[slot]);
    Hu3DModelLayerSet(modelId, 5);

    obj = omAddObjEx(objman, 0x1400, 1, 0, OM_GRP_NONE, fn_1_4654);
    obj->mdlId[0] = modelId;
    obj->work[0] = player->no;
    obj->work[1] = slot;

    omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
}

/* asm 1074-1121, 42 insns. Called by fn_1_714. */
void fn_1_4858(void)
{
    int i;

    if (lbl_1_bss_1C == 0) {
        for (i = 0; i < 4; i++) {
            lbl_1_bss_140[i]->targetPos = lbl_1_data_278[lbl_1_bss_140[i]->side];
        }
    } else {
        fn_1_7488();
    }
}

/* asm 1124-1387, 243 insns. Solo player object func (installed by fn_1_39DC). */
void fn_1_4900(OMOBJ *obj)
{
    M523_PLAYER *player = obj->data;

    switch (player->mode) {
    case 0xE:
    {
        M523_PLAYER *p;

        obj->work[0]++;

        if (lbl_1_bss_14 == 1) {
            p = obj->data;

            if (p->motNo != 4) {
                s16 idx;

                if (p->side == 0) {
                    idx = lbl_1_data_2CC[4].motNo[0];
                } else {
                    idx = lbl_1_data_2CC[4].motNo[1];
                }

                CharMotionShiftSet(p->charNo, obj->mtnId[idx], 0.0f, lbl_1_data_2CC[4].shift, lbl_1_data_2CC[4].attr);
                p->motNo = 4;
            }

            player->mode = 0xF;
        }
        break;
    }

    case 0xF:
    {
        M523_PLAYER *p;

        CharMotionSpeedSet(player->charNo, 3.0f);

        if (lbl_1_bss_14 == 2) {
            p = obj->data;

            if (p->motNo != 3) {
                s16 idx;

                if (p->side == 0) {
                    idx = lbl_1_data_2CC[3].motNo[0];
                } else {
                    idx = lbl_1_data_2CC[3].motNo[1];
                }

                CharMotionShiftSet(p->charNo, obj->mtnId[idx], 0.0f, lbl_1_data_2CC[3].shift, lbl_1_data_2CC[3].attr);
                p->motNo = 3;
            }

            player->mode = 0x10;
            obj->work[0] = 0;
        }
        break;
    }

    case 0x10:
    {
        M523_PLAYER *p;

        if (++obj->work[0] >= 0x19) {
            (void)(obj->work[0] == 1);

            p = obj->data;

            if (p->motNo != 2) {
                s16 idx;

                if (p->side == 0) {
                    idx = lbl_1_data_2CC[2].motNo[0];
                } else {
                    idx = lbl_1_data_2CC[2].motNo[1];
                }

                CharMotionShiftSet(p->charNo, obj->mtnId[idx], 0.0f, lbl_1_data_2CC[2].shift, lbl_1_data_2CC[2].attr);
                p->motNo = 2;
            }

            player->targetPos = lbl_1_data_248[player->side];
            player->mode = 0x11;
            lbl_1_bss_14 = 3;
        }
        break;
    }

    case 0x11:
    {
        HuVecF diff;

        PSVECSubtract(&player->targetPos, &player->pos, &diff);

        if (PSVECMag(&diff) < 15.0f) {
            M523_PLAYER *p;

            player->pos = player->targetPos;
            player->mode = 0x12;

            p = obj->data;

            if (p->motNo != 6) {
                s16 idx;

                if (p->side == 0) {
                    idx = lbl_1_data_2CC[6].motNo[0];
                } else {
                    idx = lbl_1_data_2CC[6].motNo[1];
                }

                CharMotionShiftSet(p->charNo, obj->mtnId[idx], 0.0f, lbl_1_data_2CC[6].shift, lbl_1_data_2CC[6].attr);
                p->motNo = 6;
            }

            obj->objFunc = fn_1_4CCC;
        } else {
            PSVECNormalize(&diff, &diff);
            PSVECScale(&diff, &diff, 15.0f);
            PSVECAdd(&player->pos, &diff, &player->pos);
        }
        break;
    }
    }

    omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
}

/* asm 1390-1529, 130 insns. */
void fn_1_4CCC(OMOBJ *obj)
{
    M523_PLAYER *player = obj->data;
    s16 vol, pan;

    fn_1_E58(&player->pos, &vol, &pan);
    CharModelVoicePanSet(player->charNo, pan);
    CharModelVoiceVolSet(player->charNo, vol);
    player->vel.x = player->vel.z = 0.0f;

    switch (player->mode) {
    case 1:
        if (lbl_1_bss_18 == 2) {
            M523_PLAYER *p = obj->data;

            if (p->motNo != 2) {
                s16 idx;

                if (p->side == 0) {
                    idx = lbl_1_data_2CC[2].motNo[0];
                } else {
                    idx = lbl_1_data_2CC[2].motNo[1];
                }

                CharMotionShiftSet(p->charNo, obj->mtnId[idx], 0.0f, lbl_1_data_2CC[2].shift, lbl_1_data_2CC[2].attr);
                p->motNo = 2;
            }

            obj->objFunc = fn_1_54A8;
            return;
        }

        fn_1_4ED4(obj);
        break;

    case 2:
    {
        HuVecF tpos = lbl_1_bss_140[player->targetNo]->pos;
        HuVecF dst;

        tpos.y = 200.0f;
        player->rot.y += 4.0f;

        if (MgVecApproach(&player->pos, &tpos, &dst, 3.0f)) {
            player->unk54 = 1;
            player->mode = 7;
            obj->objFunc = fn_1_58A8;
        }
        break;
    }
    }

    omSetRot(obj, player->rot.x, player->rot.y, player->rot.z);
    omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
}

/* asm 1532-1926, 373 insns. */
void fn_1_4ED4(OMOBJ *obj)
{
    M523_PLAYER *player = obj->data;
    float mag;
    float limit;
    HuVecF dir;

    if (player->comF != 0) {
        mag = fn_1_85A8(player);
    } else {
        player->stkX = HuPadStkX[player->padNo];
        player->stkY = -HuPadStkY[player->padNo];
        mag = sqrtf(HuSquare(player->stkX) + HuSquare(player->stkY));
    }

    if (mag >= 10.0f) {
        player->vel.x = 0.26785713f * player->stkX;
        player->vel.z = 0.26785713f * player->stkY;
    }

    mag = PSVECMag(&player->vel);

    if (mag < 0.1f) {
        M523_PLAYER *p = obj->data;

        if (p->motNo != 4) {
            s16 idx;

            if (p->side == 0) {
                idx = lbl_1_data_2CC[4].motNo[0];
            } else {
                idx = lbl_1_data_2CC[4].motNo[1];
            }

            CharMotionShiftSet(p->charNo, obj->mtnId[idx], 0.0f, lbl_1_data_2CC[4].shift, lbl_1_data_2CC[4].attr);
            p->motNo = 4;
        }
    } else if (mag < 7.5f) {
        M523_PLAYER *p = obj->data;

        if (p->motNo != 1) {
            s16 idx;

            if (p->side == 0) {
                idx = lbl_1_data_2CC[1].motNo[0];
            } else {
                idx = lbl_1_data_2CC[1].motNo[1];
            }

            CharMotionShiftSet(p->charNo, obj->mtnId[idx], 0.0f, lbl_1_data_2CC[1].shift, lbl_1_data_2CC[1].attr);
            p->motNo = 1;
        }
    } else {
        M523_PLAYER *p = obj->data;

        if (p->motNo != 2) {
            s16 idx;

            if (p->side == 0) {
                idx = lbl_1_data_2CC[2].motNo[0];
            } else {
                idx = lbl_1_data_2CC[2].motNo[1];
            }

            CharMotionShiftSet(p->charNo, obj->mtnId[idx], 0.0f, lbl_1_data_2CC[2].shift, lbl_1_data_2CC[2].attr);
            p->motNo = 2;
        }
    }

    if (mag >= 0.1f) {
        player->rot.y = (float)((atan2(player->vel.x, player->vel.z) / M_PI) * 180.0);
        fn_1_595C(player);

        if (player->side == 0) {
            limit = player->radius;
        } else {
            limit = player->radius - 50.0f;
        }

        PSVECAdd(&player->pos, &player->vel, &dir);
        dir.y = 0.0f;

        if (PSVECMag(&dir) > 800.0f - limit) {
            PSVECNormalize(&dir, &dir);
            PSVECScale(&dir, &dir, 800.0f - limit);
            PSVECSubtract(&dir, &player->pos, &player->vel);
            player->vel.y = 0.0f;
        }

        PSVECAdd(&player->pos, &player->vel, &player->pos);
    }

    {
        int i;

        for (i = 1; i < 10; i++) {
            lbl_1_bss_150[i - 1] = lbl_1_bss_150[i];
        }

        lbl_1_bss_150[9] = player->vel;
    }
}

/* asm 1929-2201, 256 insns. */
void fn_1_54A8(OMOBJ *obj)
{
    M523_PLAYER *player = obj->data;

    player->vel.x = player->vel.y = player->vel.z = 0.0f;

    switch (player->mode) {
    case 1:
    {
        HuVecF dir;
        float mag;

        PSVECSubtract(&lbl_1_data_278[0], &player->pos, &dir);
        dir.y = 0.0f;
        mag = PSVECMag(&dir);

        if (mag < 15.0f) {
            M523_PLAYER *p = obj->data;

            if (p->motNo != 0) {
                s16 idx;

                if (p->side == 0) {
                    idx = lbl_1_data_2CC[0].motNo[0];
                } else {
                    idx = lbl_1_data_2CC[0].motNo[1];
                }

                CharMotionShiftSet(p->charNo, obj->mtnId[idx], 0.0f, lbl_1_data_2CC[0].shift, lbl_1_data_2CC[0].attr);
                p->motNo = 0;
            }

            player->mode = 4;
            player->vel = dir;
        } else {
            PSVECNormalize(&dir, &dir);
            player->vel.x = 15.0f * dir.x;
            player->vel.z = 15.0f * dir.z;
        }

        player->rot.y = (float)((atan2(player->vel.x, player->vel.z) / M_PI) * 180.0);
        fn_1_595C(player);

        {
            float limit;
            HuVecF dir2;

            if (player->side == 0) {
                limit = player->radius;
            } else {
                limit = player->radius - 50.0f;
            }

            PSVECAdd(&player->pos, &player->vel, &dir2);
            dir2.y = 0.0f;

            if (PSVECMag(&dir2) > 800.0f - limit) {
                PSVECNormalize(&dir2, &dir2);
                PSVECScale(&dir2, &dir2, 800.0f - limit);
                PSVECSubtract(&dir2, &player->pos, &player->vel);
                player->vel.y = 0.0f;
            }

            PSVECAdd(&player->pos, &player->vel, &player->pos);
        }
        break;
    }

    case 4:
        player->rot.y = MgAngleApproach(player->rot.y, 0.0f, 15.0f);

        if (fabs(player->rot.y) <= 1.0) {
            player->unk54 = 1;
            player->mode = 5;
        }
        break;

    case 5:
        if (lbl_1_bss_18 == 4) {
            M523_PLAYER *p;

            player->mode = 6;
            p = obj->data;

            if (p->motNo != 8) {
                s16 idx;

                if (p->side == 0) {
                    idx = lbl_1_data_2CC[8].motNo[0];
                } else {
                    idx = lbl_1_data_2CC[8].motNo[1];
                }

                CharMotionShiftSet(p->charNo, obj->mtnId[idx], 0.0f, lbl_1_data_2CC[8].shift, lbl_1_data_2CC[8].attr);
                p->motNo = 8;
            }
        }
        break;
    }

    omSetRot(obj, player->rot.x, player->rot.y, player->rot.z);
    omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
}

/* asm 2204-2250, 45 insns. */
void fn_1_58A8(OMOBJ *obj)
{
    M523_PLAYER *player = obj->data;

    player->pos = lbl_1_bss_140[player->targetNo]->pos;
    player->pos.y = 200.0f;
    player->rot.y += 4.0f;

    omSetRot(obj, player->rot.x, player->rot.y, player->rot.z);
    omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
}

/* asm 2253-2293, 37 insns. */
void fn_1_595C(M523_PLAYER *player)
{
    int i;

    for (i = 0; i < 3; i++) {
        HuVecF pos;

        PSVECAdd(&player->pos, &player->vel, &pos);
        MgVecOrbit(&player->pos, &pos, &lbl_1_data_1E4[i], 50.0f + player->radius);
        PSVECSubtract(&pos, &player->pos, &player->vel);
    }
}

/* asm 2296-2367, 67 insns. Unreferenced. */
void fn_1_59F0(void)
{
    OMOBJ *obj;
    M523_PLAYER *player;

    omVibrate(lbl_1_bss_13C->no, 0x3c, 0xc, 0);

    obj = lbl_1_bss_13C->obj;
    player = obj->data;

    if (player->motNo != 5) {
        s16 idx;

        if (player->side == 0) {
            idx = lbl_1_data_2CC[5].motNo[0];
        } else {
            idx = lbl_1_data_2CC[5].motNo[1];
        }

        CharMotionShiftSet(player->charNo, obj->mtnId[idx], 0.0f, lbl_1_data_2CC[5].shift, lbl_1_data_2CC[5].attr);
        player->motNo = 5;
    }

    lbl_1_bss_13C->mode = 2;
    fn_1_F34(&lbl_1_bss_13C->pos, 0x74E);
}

/* asm 2370-2482, 111 insns. Called by fn_1_39DC to place a team player on its entry spiral. */
void fn_1_5AFC(M523_PLAYER *player)
{
    HuVecF pos;
    float k;

    pos.x = lbl_1_data_248[1].x + 300.0 * sin(2.9670597283903604);
    pos.z = lbl_1_data_248[1].z + 300.0 * cos(2.9670597283903604);

    player->targetPos.x = pos.x;
    player->targetPos.z = pos.z;
    player->targetPos.y = 0.0f;

    k = 628.31854f;
    pos.x = pos.x + (1500.0f + k * (player->side - 1)) * sin(4.537856055185257);
    pos.z = pos.z + (1500.0f + k * (player->side - 1)) * cos(4.537856055185257);

    player->pos.x = pos.x;
    player->pos.z = pos.z;
    player->pos.y = 0.0f;
}

/* asm 2485-2833, 330 insns. Team player object func (installed by fn_1_39DC). */
void fn_1_5CB8(OMOBJ *obj)
{
    M523_PLAYER *player = obj->data;

    switch (player->mode) {
    case 19:
    {
        HuVecF dir;

        PSVECSubtract(&player->targetPos, &player->pos, &dir);

        if (PSVECMag(&dir) < 30.0f) {
            obj->work[0] = 300;
            obj->work[1] = 0;
            player->pos = player->targetPos;
            player->mode = 20;
            player->rot.y = 170.0f;
            lbl_1_bss_14 = 1;
        } else {
            PSVECNormalize(&dir, &dir);
            PSVECScale(&dir, &dir, 30.0f);
            PSVECAdd(&player->pos, &dir, &player->pos);
        }
        break;
    }

    case 20:
    {
        float t;
        float d = 5.729578f;

        player->rot.y -= d;
        player->rot.x += d;

        if (player->rot.x >= 495.0f - 65.0f * (player->side - 2)) {
            if (player->side >= 2) {
                player->mode = 21;
            } else if (obj->work[0] > 5) {
                obj->work[0] -= 5;

                if (obj->work[0] < 0x6e && obj->work[1] == 0) {
                    lbl_1_bss_14 = 2;
                    obj->work[1] = 1;
                }
            } else {
                obj->work[0] = 0;
                player->mode = 22;
            }
        }

        t = (float)obj->work[0];

        if (t == 0.0f) {
            t = 0.0f;
        }

        player->pos.x = lbl_1_data_248[1].x + t * sin(M_PI * player->rot.y / 180.0);
        player->pos.z = lbl_1_data_248[1].z + t * cos(M_PI * player->rot.y / 180.0);
        break;
    }

    case 21:
    {
        HuVecF dir;

        PSVECSubtract(&lbl_1_data_248[player->side], &player->pos, &dir);

        if (PSVECMag(&dir) < 30.0f) {
            player->pos = lbl_1_data_248[player->side];
            player->mode = 25;
        } else {
            PSVECNormalize(&dir, &dir);
            PSVECScale(&dir, &dir, 30.0f);
            PSVECAdd(&player->pos, &dir, &player->pos);
        }
        break;
    }

    case 22:
        if (obj->work[0] == 0) {
            omVibrate(player->no, 0x5a, 6, 6);
            Hu3DMotionTimeSet(obj->mdlId[2], 0.0f);
            Hu3DModelAttrReset(obj->mdlId[2], 0x40000002);
            player->seNo = fn_1_F34(&player->pos, 0x74c);
        } else if (obj->work[0] == 0xe) {
            fn_1_9798(&player->pos);
            Hu3DModelAttrSet(obj->mdlId[2], 0x40000002);
        } else if (obj->work[0] == 0x4a) {
            Hu3DModelAttrReset(obj->mdlId[2], 0x40000002);
        } else if (obj->work[0] == 0x59) {
            player->mode = 25;
            Hu3DMotionTimeSet(obj->mdlId[2], 0.0f);
            Hu3DModelAttrSet(obj->mdlId[2], 0x40000002);
            HuAudFXStop(player->seNo);
        }

        obj->work[0]++;
        break;

    case 25:
        obj->objFunc = fn_1_6294;
        player->rot.x = player->rot.y = 0.0f;
        Hu3DModelRotSetV(player->obj->mdlId[1], &player->rot);
        Hu3DModelRotSetV(player->obj->mdlId[2], &player->rot);
        break;
    }

    Hu3DModelPosSetV(player->obj->mdlId[1], &player->pos);
    Hu3DModelPosSetV(player->obj->mdlId[2], &player->pos);
}

/* asm 2836-2884, 45 insns. Unreferenced. */
void fn_1_61E0(M523_PLAYER *player)
{
    Hu3DMotionTimeSet(player->obj->mdlId[2], 0.0f);
    Hu3DModelAttrSet(player->obj->mdlId[2], 0x40000002);

    player->unk84 = 0;
    player->unk82 = 0;

    if (player->seNo != -1) {
        HuAudFXStop(player->seNo);
        player->seNo = -1;
    }

    HuPadRumbleStop(player->padNo);

    if (player->node != NULL) {
        player->node->unk20 = 1;
        player->node = NULL;
    }
}

/* asm 2887-3254, 347 insns. Has a 13-case switch (.data:0x360). */
void fn_1_6294(OMOBJ *obj)
{
    M523_PLAYER *player = obj->data;
    s16 vol, pan;

    fn_1_E58(&player->pos, &vol, &pan);
    CharModelVoicePanSet(player->charNo, pan);
    CharModelVoiceVolSet(player->charNo, vol);

    player->unk74 = player->vel;
    player->vel.x = player->vel.y = player->vel.z = 0.0f;

    if (lbl_1_bss_18 == 2 && player->unk84 != 0 && player->mode != 2) {
        Hu3DMotionTimeSet(player->obj->mdlId[2], 0.0f);
        Hu3DModelAttrSet(player->obj->mdlId[2], 0x40000002);
        player->unk84 = 0;
        player->unk82 = 0;

        if (player->seNo != -1) {
            HuAudFXStop(player->seNo);
            player->seNo = -1;
        }

        HuPadRumbleStop(player->padNo);

        if (player->node != NULL) {
            player->node->unk20 = 1;
            player->node = NULL;
        }

        player->mode = 3;
        obj->objFunc = fn_1_6800;
        return;
    }

    switch (player->mode) {
    case 1:
        if (lbl_1_bss_18 == 2) {
            player->mode = 3;
            obj->objFunc = fn_1_6800;
            return;
        }

        fn_1_6DA4(obj);
        break;

    case 2:
        if (lbl_1_bss_18 == 2) {
            if (lbl_1_bss_13C->mode == 7) {
                player->mode = 3;
                obj->objFunc = fn_1_6800;
            }
            return;
        }
        break;

    case 8:
        omVibrate(player->no, 0x5a, 6, 6);
        Hu3DMotionTimeSet(obj->mdlId[2], 0.0f);
        Hu3DModelAttrReset(obj->mdlId[2], 0x40000002);
        player->mode = 9;
        player->unk84 = 1;
        player->seNo = fn_1_F34(&player->pos, 0x74c);
        break;

    case 9:
        if (Hu3DMotionTimeGet(obj->mdlId[2]) >= 14.0f) {
            Hu3DModelAttrSet(obj->mdlId[2], 0x40000002);
            player->node = fn_1_9798(&player->pos);
            player->mode = 10;
            player->unk82 = 0;
        }
        break;

    case 10:
        player->unk82++;

        if (player->unk82 == 0x3c) {
            player->node = NULL;
            Hu3DModelAttrReset(obj->mdlId[2], 0x40000002);
            player->mode = 0xb;
        }

        if (!fn_1_73D4(player)) {
            break;
        }

        player->unk82 = 0;
        omVibrate(lbl_1_bss_13C->no, 0x3c, 0xc, 0);

        {
            OMOBJ *tobj = lbl_1_bss_13C->obj;
            M523_PLAYER *tplayer = tobj->data;

            if (tplayer->motNo != 5) {
                s16 idx;

                if (tplayer->side == 0) {
                    idx = lbl_1_data_2CC[5].motNo[0];
                } else {
                    idx = lbl_1_data_2CC[5].motNo[1];
                }

                CharMotionShiftSet(tplayer->charNo, tobj->mtnId[idx], 0.0f, lbl_1_data_2CC[5].shift, lbl_1_data_2CC[5].attr);
                tplayer->motNo = 5;
            }
        }

        lbl_1_bss_13C->mode = 2;
        fn_1_F34(&lbl_1_bss_13C->pos, 0x74e);

        player->mode = 2;
        lbl_1_bss_13C->targetNo = player->no;
        break;

    case 11:
        if (Hu3DMotionEndCheck(obj->mdlId[2])) {
            player->mode = 1;
            Hu3DMotionTimeSet(obj->mdlId[2], 0.0f);
            Hu3DModelAttrSet(obj->mdlId[2], 0x40000002);
            player->unk82 = 0;
            HuPadRumbleStop(player->padNo);
            player->unk84 = 0;

            if (player->seNo != -1) {
                HuAudFXStop(player->seNo);
                player->seNo = -1;
            }
        }
        break;

    case 12:
        if (player->unk84 != 0 && lbl_1_bss_13C->targetNo == -1) {
            Hu3DMotionTimeSet(obj->mdlId[2], 0.0f);
            Hu3DModelAttrSet(obj->mdlId[2], 0x40000002);
            player->unk82 = 0;
            player->unk84 = 0;

            if (player->seNo != -1) {
                HuAudFXStop(player->seNo);
                player->seNo = -1;
            }
        }

        player->unk80--;

        if (player->unk80 == 0) {
            player->mode = 1;
            Hu3DMotionSet(player->ufoMdlId, player->ufoMotId[0]);
        }
        break;
    }

    PSVECScale(&player->vel, &player->vel, 0.2f);
    PSVECScale(&player->unk74, &player->unk74, 0.8f);
    PSVECAdd(&player->vel, &player->unk74, &player->vel);
}

/* asm 3257-3636, 361 insns. */
void fn_1_6800(OMOBJ *obj)
{
    M523_PLAYER *player = obj->data;

    player->stkX = player->stkY = 0;
    player->vel.x = player->vel.y = player->vel.z = 0.0f;

    if (player->unk54 != 0) {
        player->mode = 5;

        if (lbl_1_bss_1C == 0) {
            obj->work[0] = (3 - player->side) * 20;
            obj->objFunc = fn_1_7898;
        } else {
            obj->objFunc = fn_1_76E4;
        }
    } else {
        HuVecF dir, diff;
        float mag;
        float limit;
        int i, j;

        PSVECSubtract(&player->targetPos, &player->pos, &dir);
        dir.y = 0.0f;
        mag = PSVECMag(&dir);

        if (mag < 15.0f) {
            player->unk54 = 1;
            player->vel = dir;
        } else {
            PSVECNormalize(&dir, &dir);
            player->stkX = (s8)(56.0f * dir.x);
            player->stkY = (s8)(56.0f * dir.z);

            mag = sqrtf(HuSquare(player->stkX) + HuSquare(player->stkY));

            player->vel.x = 0.26785713f * player->stkX;
            player->vel.z = 0.26785713f * player->stkY;
            player->vel.y = 0.0f;
        }

        if (player->side == 0) {
            limit = player->radius;
        } else {
            limit = player->radius - 50.0f;
        }

        PSVECAdd(&player->pos, &player->vel, &dir);
        dir.y = 0.0f;

        if (PSVECMag(&dir) > 800.0f - limit) {
            PSVECNormalize(&dir, &dir);
            PSVECScale(&dir, &dir, 800.0f - limit);
            PSVECSubtract(&dir, &player->pos, &player->vel);
            player->vel.y = 0.0f;
        }

        for (i = 0; i < 4; i++) {
            lbl_1_bss_140[i]->unk5C = lbl_1_bss_140[i]->pos;
        }

        PSVECAdd(&player->pos, &player->vel, &player->pos);
        PSVECSubtract(&player->unk5C, &player->pos, &diff);

        if (PSVECMag(&diff) < 0.01f) {
            /* barely moved: skip the collision check */
        } else {
            M523_PLAYER *other;

            for (j = 0; j < 4; j++) {
                other = lbl_1_bss_140[j];

                if (player == other) {
                    continue;
                }
                if (other == lbl_1_bss_13C) {
                    continue;
                }
                if (other->mode == 6) {
                    continue;
                }

                PSVECSubtract(&player->pos, &other->pos, &diff);

                if (PSVECMag(&diff) >= player->radius + other->radius) {
                    continue;
                }

                PSVECNormalize(&diff, &diff);
                PSVECScale(&diff, &diff, player->radius + other->radius);
                PSVECAdd(&other->pos, &diff, &player->pos);
                player->pos.y = 0.0f;
            }
        }

        Hu3DModelPosSetV(player->obj->mdlId[1], &player->pos);
        Hu3DModelRotSetV(player->obj->mdlId[1], &player->rot);
        Hu3DModelPosSetV(player->obj->mdlId[2], &player->pos);
        Hu3DModelRotSetV(player->obj->mdlId[2], &player->rot);
    }
}

/* asm 3639-3901, 253 insns. */
void fn_1_6DA4(OMOBJ *obj)
{
    M523_PLAYER *player = obj->data;
    float mag;

    if (fn_1_7358(player)) {
        player->unk82 = 0;
        player->mode = 8;
        return;
    }

    if (player->comF != 0) {
        mag = fn_1_8DF0(player);
    } else {
        player->stkX = HuPadStkX[player->padNo];
        player->stkY = -HuPadStkY[player->padNo];
        mag = sqrtf(HuSquare(player->stkX) + HuSquare(player->stkY));
    }

    if (mag > 30.0f) {
        player->stkX = (s8)(player->stkX * 30 / mag);
        player->stkY = (s8)(player->stkY * 30 / mag);
        mag = 30.0f;
    }

    if (mag >= 15.0f) {
        player->vel.x = 1.6666666f * player->stkX;
        player->vel.z = 1.6666666f * player->stkY;
    } else if (mag > 0.0f) {
        player->vel.x = 0.16666667f * player->stkX;
        player->vel.z = 0.16666667f * player->stkY;
    }
}

/* asm 3904-4024, 112 insns. Unreferenced: send the solo player back to its wait
 * pose and spawn one fn_1_4654 sparkle effect (inlines fn_1_4700's body). */
void fn_1_7198(M523_PLAYER *player)
{
    player->unk80 = 0x28;
    Hu3DMotionSet(player->ufoMdlId, player->ufoMotId[3]);
    omVibrate(player->no, 0xc, 0xc, 0);
    player->comMode = 0;

    if (player->mode != 0xc) {
        player->mode = 0xc;

        if (player->node != NULL) {
            player->node->unk20 = 1;
            player->node = NULL;
        }

        {
            OMOBJ *obj;
            HU3DMODELID modelId;
            s16 freeList[3];
            s16 freeCount;
            s16 i;
            s16 slot;

            freeCount = 0;
            for (i = 0; i < 3; i++) {
                if (lbl_1_bss_130[i] == 0) {
                    freeList[freeCount++] = i;
                }
            }

            if (freeCount == 0) {
                slot = 0;
            } else {
                slot = freeList[frandmod(freeCount)];
            }

            lbl_1_bss_130[slot] = 1;

            modelId = Hu3DModelCreateData(lbl_1_rodata_13C[slot]);
            Hu3DModelLayerSet(modelId, 5);

            obj = omAddObjEx(objman, 0x1400, 1, 0, OM_GRP_NONE, fn_1_4654);
            obj->mdlId[0] = modelId;
            obj->work[0] = player->no;
            obj->work[1] = slot;

            omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
        }
    }
}

/* asm 4027-4061, 31 insns. */
BOOL fn_1_7358(M523_PLAYER *player)
{
    BOOL result = FALSE;

    if (player->comF != 0) {
        result = fn_1_90EC(player);
    } else if (HuPadBtnDown[player->padNo] & PAD_BUTTON_A) {
        result = TRUE;
    }

    return result;
}

/* asm 4064-4114, 45 insns. True when the solo player (bss_13C) is in mode 1
 * and within 100 units of the given player's position. */
BOOL fn_1_73D4(M523_PLAYER *player)
{
    HuVecF diff;

    if (lbl_1_bss_13C->mode != 1) {
        return FALSE;
    }

    if (lbl_1_bss_18 == 2) {
        return FALSE;
    }

    PSVECSubtract(&lbl_1_bss_13C->pos, &player->pos, &diff);
    diff.y = 0.0f;

    if (PSVECMag(&diff) < 100.0f) {
        return TRUE;
    }

    return FALSE;
}

/* asm 4117-4242, 115 insns. */
void fn_1_7488(void)
{
    s16 order[3];
    M523_PLAYER *cand[3];
    s16 count;
    int i;

    for (i = 0; i < 3; i++) {
        order[i] = -1;
    }

    order[0] = lbl_1_bss_13C->targetNo;

    count = 0;
    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_140[i]->side == 0) {
            continue;
        }
        if (i == lbl_1_bss_13C->targetNo) {
            continue;
        }

        cand[count++] = lbl_1_bss_140[i];
    }

    {
        HuVecF diffA, diffB;
        float magB;

        PSVECSubtract(&cand[0]->pos, &lbl_1_data_2A8[1], &diffA);
        PSVECSubtract(&cand[1]->pos, &lbl_1_data_2A8[1], &diffB);

        magB = PSVECMag(&diffB);

        if (PSVECMag(&diffA) < magB) {
            order[1] = cand[0]->no;
            order[2] = cand[1]->no;
        } else {
            order[1] = cand[1]->no;
            order[2] = cand[0]->no;
        }
    }

    for (i = 0; i < 3; i++) {
        lbl_1_bss_140[order[i]]->targetPos = lbl_1_data_2A8[i];
    }
}

/* asm 4245-4285, 36 insns. Unreferenced. */
void fn_1_7654(void)
{
    int i;

    for (i = 0; i < 4; i++) {
        M523_PLAYER *p = lbl_1_bss_140[i];

        if (p->side != 0) {
            lbl_1_bss_140[i]->targetPos = lbl_1_data_278[p->side];
        }
    }
}

/* asm 4288-4408, 109 insns. */
void fn_1_76E4(OMOBJ *obj)
{
    M523_PLAYER *player = obj->data;

    if (lbl_1_bss_18 == 4) {
        switch (player->mode) {
        case 0:
            break;

        case 5:
        {
            M523_PLAYER *p = obj->data;

            if (p->motNo != 9) {
                s16 idx;

                if (p->side == 0) {
                    idx = lbl_1_data_2CC[9].motNo[0];
                } else {
                    idx = lbl_1_data_2CC[9].motNo[1];
                }

                CharMotionShiftSet(p->charNo, obj->mtnId[idx], 0.0f, lbl_1_data_2CC[9].shift, lbl_1_data_2CC[9].attr);
                p->motNo = 9;
            }

            Hu3DMotionSet(player->ufoMdlId, player->ufoMotId[2]);
            Hu3DModelAttrReset(player->ufoMdlId, 0x40000001);
            player->mode = 6;
            fn_1_F34(&player->pos, 0x74f);
            break;
        }

        case 6:
            if (Hu3DMotionEndCheck(player->ufoMdlId)) {
                M523_PLAYER *p = obj->data;

                if (p->motNo != 8) {
                    s16 idx;

                    if (p->side == 0) {
                        idx = lbl_1_data_2CC[8].motNo[0];
                    } else {
                        idx = lbl_1_data_2CC[8].motNo[1];
                    }

                    CharMotionShiftSet(p->charNo, obj->mtnId[idx], 0.0f, lbl_1_data_2CC[8].shift, lbl_1_data_2CC[8].attr);
                    p->motNo = 8;
                }

                player->mode = 0;
            }
            break;
        }
    }
}

/* asm 4411-4679, 251 insns. */
void fn_1_7898(OMOBJ *obj)
{
    M523_PLAYER *player = obj->data;

    if (lbl_1_bss_18 != 4) {
        return;
    }

    if (obj->work[0] != 0) {
        obj->work[0]--;

        if (obj->work[0] != 0) {
            return;
        }
    }

    switch (player->mode) {
    case 0:
        break;

    case 5:
    {
        M523_PLAYER *p = obj->data;

        if (p->motNo != 9) {
            s16 idx;

            if (p->side == 0) {
                idx = lbl_1_data_2CC[9].motNo[0];
            } else {
                idx = lbl_1_data_2CC[9].motNo[1];
            }

            CharMotionShiftSet(p->charNo, obj->mtnId[idx], 0.0f, lbl_1_data_2CC[9].shift, lbl_1_data_2CC[9].attr);
            p->motNo = 9;
        }

        Hu3DMotionSet(player->ufoMdlId, player->ufoMotId[1]);
        Hu3DModelAttrReset(player->ufoMdlId, 0x40000001);
        player->mode = 0xd;
        omVibrate(player->no, 0x3c, 0xc, 0);
        fn_1_F34(&player->pos, 0x750);
        obj->work[1] = 0;
        break;
    }

    case 0xd:
        if (Hu3DMotionTimeGet(player->ufoMdlId) >= 49.0f) {
            M523_PLAYER *p;

            Hu3DModelObjPosGet(player->ufoMdlId, "itemhook_ufo", &player->pos);
            omResetStatBit(obj, 0x100);
            Hu3DModelHookReset(player->ufoMdlId);
            player->mode = 6;
            player->vel.x = player->vel.y = player->vel.z = 0.0f;

            p = obj->data;

            if (p->motNo != 0xa) {
                s16 idx;

                if (p->side == 0) {
                    idx = lbl_1_data_2CC[0xa].motNo[0];
                } else {
                    idx = lbl_1_data_2CC[0xa].motNo[1];
                }

                CharMotionShiftSet(p->charNo, obj->mtnId[idx], 0.0f, lbl_1_data_2CC[0xa].shift, lbl_1_data_2CC[0xa].attr);
                p->motNo = 0xa;
            }

            omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
            obj->work[1] = 0;
        }
        break;

    case 6:
    {
        HuVecF local;

        obj->work[1]++;

        player->vel.y = 1000.0 * sin(M_PI * (2.8f * obj->work[1]) / 180.0);
        player->vel.z += 3.5f;

        PSVECAdd(&player->pos, &player->vel, &local);

        if (local.y < 0.0f) {
            M523_PLAYER *p = obj->data;

            if (p->motNo != 7) {
                s16 idx;

                if (p->side == 0) {
                    idx = lbl_1_data_2CC[7].motNo[0];
                } else {
                    idx = lbl_1_data_2CC[7].motNo[1];
                }

                CharMotionShiftSet(p->charNo, obj->mtnId[idx], 0.0f, lbl_1_data_2CC[7].shift, lbl_1_data_2CC[7].attr);
                p->motNo = 7;
            }

            player->vel.x = player->vel.y = player->vel.z = 0.0f;
            local.y = 0.0f;
            player->mode = 0;
        }

        omSetTra(obj, local.x, local.y, local.z);
        break;
    }
    }
}

/* asm 4682-5305, 585 insns. Object func installed by fn_1_674; obj is unused. */
void fn_1_7C84(OMOBJ *obj)
{
    int collided[4][4];
    int i, j;

    if (lbl_1_bss_18 == 2) {
        omDelObjEx(objman, obj);
        return;
    }

    if (lbl_1_bss_13C->mode == 2) {
        return;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            collided[i][j] = 0;
        }
    }

    for (i = 0; i < 4; i++) {
        M523_PLAYER *player = lbl_1_bss_140[i];
        float limit;
        HuVecF dir;

        if (player == lbl_1_bss_13C) {
            continue;
        }

        if (player->side == 0) {
            limit = player->radius;
        } else {
            limit = player->radius - 50.0f;
        }

        PSVECAdd(&player->pos, &player->vel, &dir);
        dir.y = 0.0f;

        if (PSVECMag(&dir) > 800.0f - limit) {
            PSVECNormalize(&dir, &dir);
            PSVECScale(&dir, &dir, 800.0f - limit);
            PSVECSubtract(&dir, &player->pos, &player->vel);
            player->vel.y = 0.0f;
        }

        PSVECAdd(&player->pos, &player->vel, &player->pos);

        for (j = 0; j < 4; j++) {
            M523_PLAYER *other = lbl_1_bss_140[j];
            HuVecF normal, relVel;
            float dist, dot;

            if (player == other) {
                continue;
            }
            if (other == lbl_1_bss_13C) {
                continue;
            }

            PSVECSubtract(&player->pos, &other->pos, &normal);
            dist = PSVECMag(&normal);

            if (dist > player->radius + other->radius) {
                continue;
            }

            PSVECSubtract(&player->vel, &other->vel, &relVel);
            PSVECNormalize(&normal, &normal);
            dot = PSVECDotProduct(&relVel, &normal);

            player->vel.x += -1.8 * (normal.x * dot) * 0.5;
            player->vel.y += -1.8 * (normal.y * dot) * 0.5;
            player->vel.z += -1.8 * (normal.z * dot) * 0.5;

            other->vel.x += 1.8 * (normal.x * dot) * 0.5;
            other->vel.y += 1.8 * (normal.y * dot) * 0.5;
            other->vel.z += 1.8 * (normal.z * dot) * 0.5;

            collided[i][j] = 1;

            {
                M523_PLAYER *target = lbl_1_bss_140[i];

                target->unk80 = 0x28;
                Hu3DMotionSet(target->ufoMdlId, target->ufoMotId[3]);
                omVibrate(target->no, 0xc, 0xc, 0);
                target->comMode = 0;

                if (target->mode != 0xc) {
                    target->mode = 0xc;

                    if (target->node != NULL) {
                        target->node->unk20 = 1;
                        target->node = NULL;
                    }

                    {
                        OMOBJ *effObj;
                        HU3DMODELID modelId;
                        s16 freeList[3];
                        s16 freeCount;
                        s16 k;
                        s16 slot;

                        freeCount = 0;
                        for (k = 0; k < 3; k++) {
                            if (lbl_1_bss_130[k] == 0) {
                                freeList[freeCount++] = k;
                            }
                        }

                        if (freeCount == 0) {
                            slot = 0;
                        } else {
                            slot = freeList[frandmod(freeCount)];
                        }

                        lbl_1_bss_130[slot] = 1;

                        modelId = Hu3DModelCreateData(lbl_1_rodata_13C[slot]);
                        Hu3DModelLayerSet(modelId, 5);

                        effObj = omAddObjEx(objman, 0x1400, 1, 0, OM_GRP_NONE, fn_1_4654);
                        effObj->mdlId[0] = modelId;
                        effObj->work[0] = target->no;
                        effObj->work[1] = slot;

                        omSetTra(effObj, target->pos.x, target->pos.y, target->pos.z);
                    }
                }
            }

            {
                M523_PLAYER *target = lbl_1_bss_140[j];

                target->unk80 = 0x28;
                Hu3DMotionSet(target->ufoMdlId, target->ufoMotId[3]);
                omVibrate(target->no, 0xc, 0xc, 0);
                target->comMode = 0;

                if (target->mode != 0xc) {
                    target->mode = 0xc;

                    if (target->node != NULL) {
                        target->node->unk20 = 1;
                        target->node = NULL;
                    }

                    {
                        OMOBJ *effObj;
                        HU3DMODELID modelId;
                        s16 freeList[3];
                        s16 freeCount;
                        s16 k;
                        s16 slot;

                        freeCount = 0;
                        for (k = 0; k < 3; k++) {
                            if (lbl_1_bss_130[k] == 0) {
                                freeList[freeCount++] = k;
                            }
                        }

                        if (freeCount == 0) {
                            slot = 0;
                        } else {
                            slot = freeList[frandmod(freeCount)];
                        }

                        lbl_1_bss_130[slot] = 1;

                        modelId = Hu3DModelCreateData(lbl_1_rodata_13C[slot]);
                        Hu3DModelLayerSet(modelId, 5);

                        effObj = omAddObjEx(objman, 0x1400, 1, 0, OM_GRP_NONE, fn_1_4654);
                        effObj->mdlId[0] = modelId;
                        effObj->work[0] = target->no;
                        effObj->work[1] = slot;

                        omSetTra(effObj, target->pos.x, target->pos.y, target->pos.z);
                    }
                }
            }

            PSVECScale(&normal, &normal, 1.0f + (player->radius + other->radius));
            PSVECAdd(&other->pos, &normal, &player->pos);
        }
    }

    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_140[i]->side != 0) {
            M523_PLAYER *player = lbl_1_bss_140[i];

            Hu3DModelPosSetV(player->obj->mdlId[1], &player->pos);
            Hu3DModelRotSetV(player->obj->mdlId[1], &player->rot);
            Hu3DModelPosSetV(player->obj->mdlId[2], &player->pos);
            Hu3DModelRotSetV(player->obj->mdlId[2], &player->rot);
        }
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (collided[i][j] == 1) {
                HuVecF pos;
                OMOBJ *effObj;
                HU3DMODELID modelId;

                PSVECAdd(&lbl_1_bss_140[i]->pos, &lbl_1_bss_140[j]->pos, &pos);
                PSVECScale(&pos, &pos, 0.5f);

                modelId = Hu3DModelCreateData(DATANUM(DATA_m523, 0x14));
                Hu3DModelLayerSet(modelId, 5);

                effObj = omAddObjEx(objman, 0x1400, 1, 0, OM_GRP_NONE, fn_1_4534);
                effObj->mdlId[0] = modelId;

                pos.y = 530.0f;
                omSetTra(effObj, pos.x, pos.y, pos.z);

                fn_1_F34(&pos, 0x74d);
            }
        }
    }
}

/* asm 5308-5497, 179 insns. COM; reads the .rodata:0x240 local table. */
float fn_1_85A8(M523_PLAYER *player)
{
    int table[4] = { 0, 0, 35, 25 };
    HuVecF diff;

    player->stkX = player->stkY = 0;

    PSVECSubtract(&player->comTarget, &player->pos, &diff);
    diff.y = 0.0f;

    if (PSVECMag(&diff) < 15.0f) {
        player->comMode = 0;
    }

    switch (player->comMode) {
    case 0:
        fn_1_8874(player);
        player->comMode = 1;
        player->unk9C = 0x64;
        /* fall through */

    case 1:
    {
        s16 idx;

        if (player->dif >= 2 && (idx = fn_1_8D14(player)) != -1 && (int)frandmod(100) <= table[player->dif]) {
            if (player->dif > 2) {
                fn_1_8A80(player, idx);
            } else {
                player->comMode = 0;
            }
        } else {
            player->unk9C--;

            if (player->unk9C == 0) {
                player->comMode = 0;
            }

            fn_1_8B60(player, 1, 15.0f);
        }
        break;
    }
    }

    {
        float x = player->stkX * player->stkX + player->stkY * player->stkY;
        double mag;

        if (x > 0.0f) {
            double guess = __frsqrte(x);

            guess = 0.5 * guess * (3.0 - guess * guess * x);
            guess = 0.5 * guess * (3.0 - guess * guess * x);
            guess = 0.5 * guess * (3.0 - guess * guess * x);

            mag = x * guess;
        } else {
            mag = x;
        }

        return (float)mag;
    }
}

/* asm 5500-5639, 131 insns. */
void fn_1_8874(M523_PLAYER *player)
{
    int retry;
    int attempt = 0;
    float dist;

    do {
        HuVecF diff;
        float angle;
        int i;

        retry = 0;
        attempt++;

        if (player->dif == 0) {
            dist = 800.0f - player->radius;
        } else {
            dist = (float)(int)frandmod((int)(800.0f - player->radius));
        }

        angle = (float)(int)frandmod(0x168);

        player->comTarget.x = dist * cos(M_PI * angle / 180.0);
        player->comTarget.z = dist * sin(M_PI * angle / 180.0);
        player->comTarget.y = 0.0f;

        for (i = 0; i < 3; i++) {
            PSVECSubtract(&player->comTarget, &lbl_1_data_1E4[i], &diff);

            if (PSVECMag(&diff) < 50.0f + player->radius) {
                retry = 1;
            }
        }

        PSVECSubtract(&player->pos, &player->comTarget, &diff);

        if (PSVECMag(&diff) < 300.0f && attempt <= 10) {
            retry = 1;
        }
    } while (retry != 0);
}

/* asm 5642-5700, 56 insns. */
void fn_1_8A80(M523_PLAYER *player, s16 no)
{
    M523_PLAYER *other = lbl_1_bss_140[no];
    HuVecF diff;
    float limit;

    PSVECSubtract(&player->pos, &other->pos, &diff);
    PSVECScale(&diff, &diff, 200.0f);
    PSVECAdd(&player->pos, &diff, &player->comTarget);

    limit = player->radius;

    if (PSVECMag(&player->comTarget) > 800.0f - limit) {
        PSVECNormalize(&player->comTarget, &player->comTarget);
        PSVECScale(&player->comTarget, &player->comTarget, 800.0f - limit);
    }
}

/* asm 5703-5818, 109 insns. */
void fn_1_8B60(M523_PLAYER *player, int flag, float unused)
{
    HuVecF dir;

    if (flag != 0) {
        float angle = player->rot.y;
        float target = fn_1_C88(&player->pos, &player->comTarget);
        float delta = fn_1_CEC(angle, target);

        if (fabs(delta) < 15.0) {
            angle += delta;
        } else {
            if (delta < 0.0f) {
                angle -= 15.0f;
            } else {
                angle += 15.0f;
            }
        }

        dir.x = sin(M_PI * angle / 180.0);
        dir.z = cos(M_PI * angle / 180.0);
        dir.y = 0.0f;
    } else {
        PSVECNormalize(&dir, &dir);
    }

    player->stkX = (s8)(dir.x * 56.0f);
    player->stkY = (s8)(dir.z * 56.0f);
}

/* asm 5821-5881, 55 insns. Returns a player index, -1 for none. */
int fn_1_8D14(M523_PLAYER *player)
{
    int result = -1;
    int i;

    for (i = 0; i < 4; i++) {
        M523_PLAYER *other = lbl_1_bss_140[i];

        if (other == player) {
            continue;
        }
        if (other->unk84 == 0) {
            continue;
        }

        {
            HuVecF closest;
            float dist = fn_1_D58(&other->pos, &player->pos, &player->comTarget, &closest);

            if (dist < 0.0f) {
                continue;
            }
            if (dist < 100.0f) {
                result = (s16)i;
                break;
            }
        }
    }

    return result;
}

/* asm 5884-6089, 191 insns. COM. */
float fn_1_8DF0(M523_PLAYER *player)
{
    HuVecF diff;
    float mag;

    switch (player->comMode) {
    case 1:
        if (player->no == (s16)fn_1_9218()) {
            fn_1_9440(player);
            player->comMode = 2;
        }
        break;

    case 2:
        fn_1_9440(player);
        break;

    case 0:
        if (player->unk9C == 0) {
            fn_1_92F4(player);
            player->comMode = 1;
        } else {
            player->unk9C--;
            return 0.0f;
        }
        break;

    default:
        break;
    }

    PSVECSubtract(&player->comTarget, &player->pos, &diff);
    diff.y = 0.0f;

    if (PSVECMag(&diff) < 50.0f) {
        player->comMode = 0;

        if (player->dif == 0) {
            player->unk9C = frandmod(30) + 45;
        } else if (player->dif == 1) {
            player->unk9C = frandmod(30) + 15;
        } else {
            player->unk9C = 0;
        }

        return 0.0f;
    }

    PSVECNormalize(&diff, &diff);
    player->stkX = (s8)(diff.x * 56.0f);
    player->stkY = (s8)(diff.y * 56.0f);

    mag = sqrtf(HuSquare(player->stkX) + HuSquare(player->stkY));
    return mag;
}

/* asm 6092-6172, 75 insns. COM; reads the .rodata:0x260 local table. */
BOOL fn_1_90EC(M523_PLAYER *player)
{
    const int table[4] = { 10, 15, 20, 20 };
    HuVecF diff;

    PSVECSubtract(&lbl_1_bss_13C->pos, &player->pos, &diff);
    diff.y = 0.0f;

    if (PSVECMag(&diff) < 100.0f) {
        if ((int)frandmod(100) < table[player->dif]) {
            if (player->dif <= 2) {
                return TRUE;
            }

            PSVECSubtract(&player->comTarget, &player->pos, &diff);

            if (PSVECMag(&diff) < 50.0f) {
                return TRUE;
            }
        } else if ((int)frandmod(100) < table[player->dif]) {
            return TRUE;
        }
    }

    return FALSE;
}

/* asm 6175-6234, 55 insns. Returns a player index, -1 for none. */
int fn_1_9218(void)
{
    float bestMag = 9999.9f;
    int best = -1;
    int i;

    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_140[i] == lbl_1_bss_13C) {
            continue;
        }

        {
            HuVecF diff;

            PSVECSubtract(&lbl_1_bss_13C->pos, &lbl_1_bss_140[i]->pos, &diff);

            if (PSVECMag(&diff) < bestMag) {
                bestMag = PSVECMag(&diff);
                best = (s16)i;
            }
        }
    }

    return best;
}

/* asm 6237-6323, 83 insns. */
void fn_1_92F4(M523_PLAYER *player)
{
    float angleDeg;
    HuVecF diff;
    float radius;
    BOOL close;

    do {
        close = FALSE;
        radius = 800.0f - player->radius - 5.0f;

        angleDeg = (float)(s32)frandmod(360);

        player->comTarget.x = (float)(radius * cos(angleDeg * 3.141592653589793 / 180.0));
        player->comTarget.z = (float)(radius * sin(angleDeg * 3.141592653589793 / 180.0));
        player->comTarget.y = 0.0f;

        PSVECSubtract(&player->pos, &player->comTarget, &diff);

        if (PSVECMag(&diff) < 200.0f) {
            close = TRUE;
        }
    } while (close);
}

/* asm 6326-6409, 77 insns. */
void fn_1_9440(M523_PLAYER *player)
{
    float limit;

    if (player->dif < 2) {
        player->comTarget = lbl_1_bss_13C->pos;
    } else {
        HuVecF sum;
        int i;

        sum.x = sum.y = sum.z = 0.0f;

        for (i = 0; i < 10; i++) {
            PSVECAdd(&sum, &lbl_1_bss_150[i], &sum);
        }

        PSVECAdd(&sum, &lbl_1_bss_13C->pos, &player->comTarget);
    }

    limit = player->radius - 50.0f;

    if (PSVECMag(&player->comTarget) > 800.0f - limit) {
        PSVECNormalize(&player->comTarget, &player->comTarget);
        PSVECScale(&player->comTarget, &player->comTarget, 800.0f - limit);
    }
}

/* asm 6412-6459, 46 insns. Link the two sentinels; create the fn_1_9978 draw hook. */
void fn_1_9574(void)
{
    HU3DMODELID hookId;

    lbl_1_bss_10C.next = &lbl_1_bss_E8;
    lbl_1_bss_10C.prev = NULL;
    lbl_1_bss_10C.no = 0;
    lbl_1_bss_10C.mdlId = -1;

    lbl_1_bss_E8.next = NULL;
    lbl_1_bss_E8.prev = &lbl_1_bss_10C;
    lbl_1_bss_E8.mdlId = -1;

    hookId = Hu3DHookFuncCreate(fn_1_9978);
    Hu3DModelLayerSet(hookId, 1);
}

/* asm 6462-6561, 91 insns. Node object func (installed by fn_1_9798). */
void fn_1_962C(OMOBJ *obj)
{
    M523_NODE *node = obj->data;

    switch (node->mode) {
    case 0:
        if (node->unk20 != 0 || Hu3DMotionEndCheck(obj->mdlId[0])) {
            Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_PAUSE);
            node->mode = 1;
            node->unk1A = 180;
        }
        break;

    case 1:
        node->unk1A--;
        if (node->unk1A <= 0) {
            node->mode = 2;
        }
        break;

    case 2:
        node->unk1A++;
        Hu3DModelTPLvlSet(obj->mdlId[0], 1.0f - 0.02f * (float)node->unk1A);
        if (node->unk1A >= 50) {
            node->mode = 3;
        }
        break;

    case 3:
        fn_1_98E8(node);
        Hu3DModelKill(obj->mdlId[0]);
        omDelObjEx(objman, obj);
        break;

    default:
        break;
    }
}

/* asm 6564-6649, 84 insns. Create a node object in front of the tail; returns the node. */
M523_NODE *fn_1_9798(HuVecF *pos)
{
    OMOBJ *obj;
    M523_NODE *node;
    M523_NODE *tail;
    HU3DMODELID modelId;

    obj = omAddObjEx(objman, 0x1200, 1, 0, OM_GRP_NONE, fn_1_962C);

    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M523_NODE), HU_MEMNUM_OVL);
    node = obj->data;

    node->mode = 0;
    node->unk20 = 0;

    tail = &lbl_1_bss_E8;
    tail->prev->next = node;
    node->prev = tail->prev;
    node->next = tail;
    tail->prev = node;

    node->no = (s16)(node->prev->no + 1);

    modelId = Hu3DModelCreateData(DATANUM(DATA_m523, 0x13));
    node->mdlId = modelId;
    obj->mdlId[0] = modelId;
    Hu3DModelLayerSet(modelId, 1);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_ZCMP_OFF);

    omSetTra(obj, 5000.0f, 0.0f, 0.0f);

    node->pos = *pos;
    node->pos.y = 0.0f;

    return node;
}

/* asm 6652-6670, 17 insns. Unlink a node, then renumber. */
void fn_1_98E8(M523_NODE *node)
{
    node->next->prev = node->prev;
    node->prev->next = node->next;
    fn_1_992C();
}

/* asm 6673-6695, 19 insns. Renumber the list from the head. */
void fn_1_992C(void)
{
    s16 no = 0;
    M523_NODE *node = &lbl_1_bss_10C;

    while (node->next != NULL) {
        node->no = no++;
        node = node->next;
    }
}

/* asm 6698-6744, 42 insns. Draw hook: "cyl10" at every node; model is unused. */
void fn_1_9978(HU3DMODEL *model, Mtx *mtx)
{
    M523_NODE *node;
    Mtx local;

    Hu3DModelObjDrawInit();

    for (node = &lbl_1_bss_10C; node->next != NULL; node = node->next) {
        if (node->mdlId == -1) {
            continue;
        }

        {
            HU3DMODEL *unused = &Hu3DData[node->mdlId];
        }

        PSMTXTrans(local, node->pos.x, node->pos.y, node->pos.z);
        PSMTXConcat(*mtx, local, local);
        Hu3DModelObjDraw(node->mdlId, "cyl10", local);
    }
}
