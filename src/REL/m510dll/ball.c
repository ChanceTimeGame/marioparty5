/*
 * m510dll ball.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m510dll/asm/REL/m510dll/ball.s.
 */

#include "REL/m510dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"
#include "datadir_enum.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x110 */ /* float lbl_1_rodata_110 = 0.0f; */
/* 0x114 */ /* float lbl_1_rodata_114 = 15.0f; */
/* 0x118 */ /* float lbl_1_rodata_118 = 1.8f; */
/* 0x11C */ /* float lbl_1_rodata_11C = 0.5f; */
/* 0x120 */ /* float lbl_1_rodata_120 = 2.0f; */
/* 0x124 */ /* float lbl_1_rodata_124 = 360.0f; */
/* 0x128 */ /* float lbl_1_rodata_128 = 60.0f; */
/* 0x12C */ /* float lbl_1_rodata_12C = -400.0f; */
/* 0x130 */ /* float lbl_1_rodata_130 = 600.0f; */
/* 0x134 */ /* float lbl_1_rodata_134 = 1.0f; */
/* 0x138 */ /* float lbl_1_rodata_138 = 0.6f; */
/* 0x13C */ /* float lbl_1_rodata_13C = 0.4f; */
/* 0x140 */ /* float lbl_1_rodata_140 = 100.0f; */
/* 0x144 */ /* float lbl_1_rodata_144 = 1300.0f; */
/* 0x148 */ /* float lbl_1_rodata_148 = 80.0f; */
/* 0x150 */ /* double lbl_1_rodata_150 = 4503601774854144; */
/* 0x158 */ /* s32 lbl_1_rodata_158[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x164 */ /* float lbl_1_rodata_164 = 62.0f; */
/* 0x168 */ /* float lbl_1_rodata_168 = -250.0f; */
/* 0x16C */ /* float lbl_1_rodata_16C = 2200.0f; */
/* 0x170 */ /* float lbl_1_rodata_170 = 23.0f; */
/* 0x174 */ /* float lbl_1_rodata_174 = 300.0f; */
/* 0x178 */ /* float lbl_1_rodata_178 = 550.0f; */
/* 0x17C */ /* float lbl_1_rodata_17C = 1250.0f; */
/* 0x180 */ /* float lbl_1_rodata_180 = 950.0f; */
/* 0x188 */ /* double lbl_1_rodata_188 = 3.141592653589793; */
/* 0x190 */ /* float lbl_1_rodata_190 = 90.0f; */
/* 0x198 */ /* double lbl_1_rodata_198 = 180; */
/* 0x1A0 */ /* float lbl_1_rodata_1A0 = 30.0f; */
/* 0x1A4 */ /* float lbl_1_rodata_1A4 = 1700.0f; */
/* 0x1A8 */ /* float lbl_1_rodata_1A8 = 450.0f; */
/* 0x1AC */ /* float lbl_1_rodata_1AC = 0.1f; */
/* 0x1B0 */ /* float lbl_1_rodata_1B0 = 0.9f; */
/* 0x1B4 */ /* float lbl_1_rodata_1B4 = 1000.0f; */
/* 0x1B8 */ /* s32 lbl_1_rodata_1B8[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x1C4 */ /* s32 lbl_1_rodata_1C4[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x1D0 */ /* s32 lbl_1_rodata_1D0[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x1DC */ /* float lbl_1_rodata_1DC = 3.0f; */
/* 0x1E0 */ /* float lbl_1_rodata_1E0 = -1.0f; */
/* 0x1E4 */ /* float lbl_1_rodata_1E4 = 0.8f; */
/* 0x1E8 */ /* float lbl_1_rodata_1E8 = 0.2f; */
/* 0x1EC */ /* float lbl_1_rodata_1EC = 10000.0f; */
/* 0x1F0 */ /* float lbl_1_rodata_1F0 = 20.833334f; */
/* 0x1F4 */ /* float lbl_1_rodata_1F4 = 380.0f; */
/* 0x1F8 */ /* float lbl_1_rodata_1F8 = 50.0f; */
/* 0x1FC */ /* float lbl_1_rodata_1FC = 2500.0f; */
/* 0x200 */ /* float lbl_1_rodata_200 = -200.0f; */
/* 0x204 */ /* float lbl_1_rodata_204 = 40.0f; */
/* 0x208 */ /* double lbl_1_rodata_208 = 150; */
/* 0x210 */ /* float lbl_1_rodata_210 = 180.0f; */
/* 0x218 */ /* double lbl_1_rodata_218 = 100; */
/* 0x220 */ /* double lbl_1_rodata_220 = 4503599627370496; */
/* 0x228 */ /* s32 lbl_1_rodata_228[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x234 */ /* float lbl_1_rodata_234 = 1150.0f; */
/* 0x238 */ /* float lbl_1_rodata_238 = 1450.0f; */
/* 0x23C */ /* float lbl_1_rodata_23C = 146.0f; */
/* 0x240 */ /* double lbl_1_rodata_240 = 360; */
/* 0x248 */ /* double lbl_1_rodata_248 = -180; */
/* 0x250 */ /* float lbl_1_rodata_250 = -180.0f; */
/* 0x254 */ /* float lbl_1_rodata_254 = 0.017453292f; */

/* --- .data --- */
/* 0x370 */ float lbl_1_data_370[13] = { 80.0f, 90.0f, 90.0f, 80.0f, 90.0f, 100.0f, 90.0f, 60.0f, 70.0f, 50.0f, 50.0f, 50.0f, 50.0f };
/* 0x3A4 */ s16 lbl_1_data_3A4[4] = { 30, 70, 35, 23 };
/* 0x3AC */ float lbl_1_data_3AC[4] = { 300.0f, 300.0f, 250.0f, 200.0f };
/* 0x3BC */ s16 lbl_1_data_3BC[4] = { 20, 30, 25, 20 };

/* --- functions (reference order) --- */
/* fn_1_509C (ball, 70 insns) */
void fn_1_509C(M510_BALL *ball, M510_PLAYER *player)
{
    s32 i;
    HU3DMODELID modelId;

    memset(ball, 0, sizeof(M510_BALL));
    ball->unk000 = player;
    modelId = Hu3DModelCreateData(DATANUM(DATA_m510, 0x03));
    ball->unk6F6 = modelId;
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    modelId = Hu3DModelCreateData(DATANUM(DATA_m510, 0x04));
    ball->unk6F8 = modelId;
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    ball->unk6FA = Hu3DJointMotionData(modelId, DATANUM(DATA_m510, 0x18));
    Hu3DMotionSet(modelId, ball->unk6FA);
    Hu3DModelAttrReset(modelId, HU3D_MOTATTR_LOOP);
    for (i = 0; i < 3; i++) {
        fn_1_53E0(&ball->unk004[i], i, ball);
    }
}

/* fn_1_51B4 (ball, 31 insns) */
void fn_1_51B4(M510_BALL *ball)
{
    s32 i;

    for (i = 0; i < 3; i++) {
        fn_1_557C(&ball->unk004[i]);
    }
    Hu3DMotionKill(ball->unk6FA);
    Hu3DModelKill(ball->unk6F8);
    Hu3DModelKill(ball->unk6F6);
    memset(ball, 0, sizeof(M510_BALL));
}

/* fn_1_5230 (ball, 32 insns) */
void fn_1_5230(M510_BALL *ball)
{
    s32 i;
    M510_BALLOBJ *obj;

    ball->unk6F4 = 0;
    for (i = 0; i < 3; i++) {
        obj = &ball->unk004[i];
        fn_1_55C4(obj);
        if (obj->unk00C != 0) {
            ball->unk6F4++;
        }
    }
}

/* fn_1_52B0 (ball, 76 insns) */
M510_BALLOBJ *fn_1_52B0(M510_BALL *ball, HuVecF *pos, s16 kind)
{
    M510_BALLOBJ *obj = NULL;
    s32 i;

    for (i = 0; i < 3; i++) {
        obj = &ball->unk004[i];
        if (obj->unk00C == 0) {
            fn_1_8060(ball, obj, kind, 1);
            Hu3DModelPosSet(obj->unk05A, pos->x, pos->y, pos->z);
            Hu3DModelPosSet(obj->unk05C, pos->x, pos->y, pos->z);
            Hu3DModelScaleSet(obj->unk05A, 0.0f, 0.0f, 0.0f);
            Hu3DModelScaleSet(obj->unk05C, 0.0f, 0.0f, 0.0f);
            obj->unk010 = *pos;
            return obj;
        }
    }
    return NULL;
}

/* fn_1_53E0 (ball, 103 insns) */
void fn_1_53E0(M510_BALLOBJ *obj, s16 no, M510_BALL *ball)
{
    M510_BALL *owner = ball;
    M510_PLAYER *player = owner->unk000;
    M510_WORK *work = player->unk000;
    M510_CAMERA *camera = &work->unk2474;
    HU3DMODELID modelId;

    memset(obj, 0, sizeof(M510_BALLOBJ));
    obj->unk000 = ball;
    obj->unk00C = 0;
    obj->unk008 = no;
    modelId = Hu3DModelLink(owner->unk6F6);
    obj->unk05A = modelId;
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk004);
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelShadowSet(modelId);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    modelId = Hu3DModelLink(owner->unk6F8);
    obj->unk05C = modelId;
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk004);
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelShadowSet(modelId);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
}

/* fn_1_557C (ball, 18 insns) */
void fn_1_557C(M510_BALLOBJ *obj)
{
    Hu3DModelKill(obj->unk05C);
    Hu3DModelKill(obj->unk05A);
    memset(obj, 0, sizeof(M510_BALLOBJ));
}

/* fn_1_55C4 (ball, 543 insns) */
void fn_1_55C4(M510_BALLOBJ *obj)
{
    M510_BALL *ball = obj->unk000;
    M510_PLAYER *player = ball->unk000;
    M510_WORK *work = player->unk000;
    M510_STAGE *stage = &work->unk221C;
    M510_PLAYERMODEL *model = &player->unk008;
    M510_SCORE *score = &player->unk850;
    M510_PITCH *pitch = &player->unk118;
    M510_BALLPATH *path = &obj->unk060;
    M510_STAGEOBJ *target;
    float t;
    HuVecF hit;
    HuVecF pos;

    if (obj->unk00C == 0) {
        obj->unk004 = 0;
        return;
    }
    switch (obj->unk004) {
    case 0:
        obj->unk24C = NULL;
        obj->unk006 = 0;
        obj->unk004 = 1;
        break;
    case 1:
        obj->unk010 = pitch->unk028;
        if (obj->unk006 <= 15) {
            t = obj->unk006 / 15.0f;
            Hu3DModelScaleSet(obj->unk05A, 1.8f * t, 1.8f * t, 1.8f * t);
            Hu3DModelScaleSet(obj->unk05C, 1.8f * t, 1.8f * t, 1.8f * t);
            obj->unk006++;
        }
        if (pitch->unk004 == 4) {
            fn_1_5E40(obj);
            Hu3DModelScaleSet(obj->unk05A, 1.8f, 1.8f, 1.8f);
            Hu3DModelScaleSet(obj->unk05C, 1.8f, 1.8f, 1.8f);
            if (player->unk004 == 0) {
                if (obj->unk058 == 0) {
                    fn_1_5B4(0x69E);
                } else if (obj->unk058 == 3) {
                    fn_1_5B4(0x69D);
                } else {
                    fn_1_5B4(0x69C);
                }
            }
            obj->unk006 = 0;
            obj->unk004 = 2;
            if (obj->unk058 == 0) {
                Hu3DModelAttrSet(obj->unk05A, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(obj->unk05C, HU3D_ATTR_DISPOFF);
                Hu3DMotionTimeSet(obj->unk05C, 0.0f);
            }
        }
        break;
    case 2:
        obj->unk246 += obj->unk244;
        if (obj->unk246 > path->unk184[path->unk000 - 1]) {
            fn_1_8060(ball, obj, 0, 0);
        } else {
            obj->unk010 = fn_1_C70C(path, obj->unk246, 0.5f);
            if (obj->unk058 != 0) {
                Hu3DModelRotSet(obj->unk05A, 2.0f * (360.0f * ((work->unk008 % 60) / 60.0f)), 0.0f, 0.0f);
            }
        }
        if (obj->unk00C != 0 && fn_1_7038(obj, &hit)) {
            fn_1_64B0(obj, &hit);
            omVibrate(model->unk008, 20, 6, 6);
            if (work->unk00C == 4) {
                score->unk024++;
            }
            obj->unk006 = 0;
            obj->unk004 = 3;
            if (model->unk008 == 0) {
                fn_1_5B4(0x697);
            } else if (model->unk008 == 1) {
                fn_1_5B4(0x698);
            } else if (model->unk008 == 2) {
                fn_1_5B4(0x699);
            } else {
                fn_1_5B4(0x69A);
            }
            if (obj->unk058 == 0) {
                Hu3DModelAttrReset(obj->unk05A, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(obj->unk05C, HU3D_ATTR_DISPOFF);
            }
        }
        break;
    case 3:
        obj->unk246 += obj->unk244;
        if (obj->unk246 > path->unk184[path->unk000 - 1]) {
            fn_1_8060(ball, obj, 0, 0);
            break;
        }
        obj->unk010 = fn_1_C70C(path, obj->unk246, 0.5f);
        if (obj->unk010.z < -400.0f) {
            t = ((-400.0f - obj->unk010.z >= 0.0f) ? (-400.0f - obj->unk010.z) : -(-400.0f - obj->unk010.z)) / 600.0f;
            t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
            t = 1.0f - t;
            t = 0.6f + 0.4f * t;
            Hu3DModelScaleSet(obj->unk05A, 1.8f * t, 1.8f * t, 1.8f * t);
            Hu3DModelScaleSet(obj->unk05C, 1.8f * t, 1.8f * t, 1.8f * t);
        }
        target = obj->unk24C;
        if (target && obj->unk010.z < target->unk014.z && target->unk004 == 0) {
            target->unk004 = 1;
            Hu3DModelPosSet(player->unk878, target->unk014.x, 100.0f + target->unk014.y, 100.0f + target->unk014.z);
            Hu3DModelAttrReset(player->unk878, HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(player->unk878, 0.0f);
            player->unk87C = 1;
        }
        break;
    }
    if (obj->unk00C != 0) {
        pos = obj->unk010;
        if (obj->unk004 == 2) {
            t = obj->unk010.z / 1300.0f;
            t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
            pos.y += t * (lbl_1_data_370[model->unk00C] - 80.0f);
        }
        Hu3DModelPosSet(obj->unk05A, pos.x, pos.y, pos.z);
        Hu3DModelPosSet(obj->unk05C, pos.x, pos.y, pos.z);
        obj->unk01C = obj->unk010;
    }
}

/* fn_1_5E40 (ball, 412 insns) */
void fn_1_5E40(M510_BALLOBJ *obj)
{
    M510_BALL *ball = obj->unk000;
    M510_PLAYER *player = ball->unk000;
    M510_PITCH *pitch = &player->unk118;
    M510_BALLPATH *path = &obj->unk060;
    float height = 62.0f;
    float z;
    float t;
    float w;
    float total;
    float h;
    float len;
    s32 i;
    s32 end;
    HuVecF d;

    fn_1_C5F0(path);
    for (i = 0; i < 24; i++) {
        HuVecF p;
        HuVecF zero = { 0.0f, 0.0f, 0.0f };
        HuVecF *src = &zero;

        p = *src;

        p.z = z = -250.0f + 2200.0f * (i / 23.0f);
        if (z < 300.0f) {
            t = 1.0f - ((z < 300.0f) ? ((z - -250.0f) / 550.0f) : 1.0f);
            w = -pitch->unk034;
            w *= 1.0f - t * t;
            p.x = pitch->unk010.x - w;
            h = height + lbl_1_data_3AC[obj->unk058] - pitch->unk028.y;
            h *= 1.0f - t * t;
            p.y = pitch->unk028.y + h;
        } else if (z < 1250.0f) {
            t = (z < 1250.0f) ? ((z - 300.0f) / 950.0f) : 1.0f;
            w = pitch->unk034;
            p.x = pitch->unk010.x + w * sin(M_PI * (90.0f + 90.0f * t) / 180.0);
            p.y = 30.0f * t + (height + lbl_1_data_3AC[obj->unk058] * sin(M_PI * (90.0f + 90.0f * t) / 180.0));
        } else {
            t = (z < 1700.0f) ? ((z - 1250.0f) / 450.0f) : 1.0f;
            p.x = pitch->unk010.x - 0.5f * (pitch->unk034 * t);
            t = (z < 1700.0f) ? ((z - 1250.0f) / 450.0f) : 1.0f;
            p.y = 0.1f * height + (30.0f * (1.0f - t) + 0.9f * (height * (1.0f - t)));
        }
        fn_1_C650(path, p, 0);
    }
    total = 0.0f;
    for (i = 1; i < path->unk000; i++) {
        PSVECSubtract(&path->unk004[i], &path->unk004[i - 1], &d);
        total += PSVECMag(&d);
    }
    for (i = 1; i < path->unk000; i++) {
        PSVECSubtract(&path->unk004[i], &path->unk004[i - 1], &d);
        len = PSVECMag(&d);
        path->unk124[i - 1] = (s16)(1000.0f * (len / total));
    }
    for (i = 0; i < path->unk000; i++) {
        if (i == 0) {
            path->unk184[0] = path->unk124[0];
        } else {
            path->unk184[i] = path->unk124[i] + path->unk184[i - 1];
        }
    }
    end = path->unk184[path->unk000 - 1];
    obj->unk244 = end / lbl_1_data_3A4[obj->unk058];
    obj->unk246 = 0;
}

/* 738 insns */
void fn_1_64B0(M510_BALLOBJ *slot, HuVecF *pos)
{
    s32 i;
    M510_BALL *ball = slot->unk000;
    M510_PLAYER *player = ball->unk000;
    M510_WORK *work = player->unk000;
    M510_STAGE *stage = &work->unk221C;
    M510_PLAYERMODEL *pm = &player->unk008;
    M510_PITCH *pitch = &player->unk118;
    M510_BALLPATH *path = &slot->unk060;
    float t;
    float rate;
    float z;
    float total;
    float len;
    float ofs;
    float y;
    float step;
    M510_STAGEOBJ *target;
    s32 sum;
    HuVecF d;

    t = (slot->unk248 - 7) / 3.0f;
    t *= -1.0f;
    t = (t > 1.0f) ? 1.0f : ((t < -1.0f) ? -1.0f : t);
    t *= 0.8f + 0.2f * ((frand() % 10000) / 10000.0f);
    step = 20.833334f * t;
    target = NULL;
    if ((frand() & 1) && work->unk00C == 4) {
        if (pm->unk0B8.x < 380.0f && t < 0.0f) {
            target = &stage->unk010[(frand() & 7) + 8];
        }
        else if (pm->unk0B8.x > 380.0f && t > 0.0f) {
            target = &stage->unk010[frand() & 7];
        }
    }
    {
        HuVecF pt;
        HuVecF base = (HuVecF){ 0.0f, 0.0f, 0.0f };
        ofs = 0.0f;
        fn_1_C5F0(path);
        if (!target) {
            for (i = 0; i < 24; i++) {
                pt = (HuVecF){ 0.0f, 0.0f, 0.0f };
                rate = i / 23.0f;
                pt.x = pitch->unk010.x + ofs;
                pt.y = y = pos->y + 50.0f * rate;
                z = pos->z - 2500.0f * rate;
                pt.z = z;
                ofs += step;
                if (z > -200.0f) {
                    t = 1.0f - (z - -200.0f) / (pos->z - -200.0f);
                    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
                    pt.y += lbl_1_data_3AC[slot->unk058] * sin(M_PI * (90.0f * t) / 180.0);
                }
                else {
                    t = 1.0f - (z - (pos->z - 2500.0f)) / (-200.0f - (pos->z - 2500.0f));
                    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
                    pt.y += lbl_1_data_3AC[slot->unk058] * sin(M_PI * (90.0f + 60.0f * t) / 180.0);
                }
                fn_1_C650(path, pt, 0);
            }
        }
        else {
            base = target->unk014;
            base.y += 40.0f;
            base.z += 80.0f;
            for (i = 0; i < 24; i++) {
                pt = (HuVecF){ 0.0f, 0.0f, 0.0f };
                rate = i / 23.0f;
                z = pos->z - 2500.0f * rate;
                if (z > base.z) {
                    t = 1.0f - (z - base.z) / (pos->z - base.z);
                    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
                    pt.x = pitch->unk010.x + t * (base.x - pitch->unk010.x);
                    pt.y = pos->y + t * (base.y - pos->y) + 150.0 * sin(M_PI * (180.0f * t) / 180.0);
                    pt.z = z;
                }
                else {
                    t = 1.0f - (z - (pos->z - 2500.0f)) / (base.z - (pos->z - 2500.0f));
                    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
                    pt.x = pitch->unk010.x + (1.0f + t) * (base.x - pitch->unk010.x);
                    pt.y = base.y + (300.0f * t + 100.0 * cos(M_PI * (90.0f * t) / 180.0));
                    pt.z = z;
                }
                fn_1_C650(path, pt, 0);
            }
        }
    }
    total = 0.0f;
    for (i = 1; i < path->unk000; i++) {
        PSVECSubtract(&path->unk004[i], &path->unk004[i - 1], &d);
        total += PSVECMag(&d);
    }
    for (i = 1; i < path->unk000; i++) {
        PSVECSubtract(&path->unk004[i], &path->unk004[i - 1], &d);
        len = PSVECMag(&d);
        if (!target) {
            path->unk124[i - 1] = (s16)(1000.0f * (len / total));
        }
        else {
            path->unk124[i - 1] = (s16)(1000.0f * (len / total));
        }
    }
    for (i = 0; i < path->unk000; i++) {
        if (i == 0) {
            path->unk184[0] = path->unk124[0];
        }
        else {
            path->unk184[i] = path->unk124[i] + path->unk184[i - 1];
        }
    }
    sum = path->unk184[path->unk000 - 1];
    slot->unk244 = sum / lbl_1_data_3BC[slot->unk058];
    slot->unk246 = 0;
    slot->unk24C = target;
}

/* 1034 insns */
#define M510_WRAP_D(a) ((a) > 180.0 ? (a) - 360.0 : ((a) <= -180.0 ? 360.0 + (a) : (a)))
#define M510_WRAP_F(a) ((a) > 180.0f ? (a) - 360.0f : ((a) <= -180.0f ? 360.0f + (a) : (a)))
#define M510_ABS(a) ((a) >= 0.0f ? (a) : -(a))

/* fn_1_7038, ball.c, 1034 insns. Bat/ball contact test for one ball this frame. */
s32 fn_1_7038(M510_BALLOBJ *obj, HuVecF *hit)
{
    M510_BALL *ball = obj->unk000;
    M510_PLAYER *player = ball->unk000;
    M510_PITCH *pitch = &player->unk118;
    M510_PLAYERMODEL *pm = &player->unk008;
    Mtx rot;
    HuVecF prevPos;
    HuVecF pos;
    HuVecF near;
    HuVecF batPos;
    HuVecF dir;
    HuVecF norm;
    HuVecF zero = { 0.0f, 0.0f, 0.0f };
    HuVecF *zp = &zero;
    float len;
    float dot;
    float angle;
    float prevAngle;
    float swing;
    float prevSwing;
    float ballMid;
    float mid;
    float range;

    *hit = *zp;
    if (pm->unk004 != 1) {
        return 0;
    }
    if (obj->unk058 != 0) {
        if (pm->unk006 < 2 || pm->unk006 > 11) {
            return 0;
        }
    } else {
        if (pm->unk006 < 6 || pm->unk006 > 8) {
            return 0;
        }
    }
    if ((obj->unk010.z > 1150.0f && obj->unk010.z <= 1450.0f)
        || (obj->unk01C.z > 1150.0f && obj->unk01C.z <= 1450.0f)
        || (obj->unk01C.z <= 1150.0f && obj->unk010.z > 1450.0f)) {
        prevPos = obj->unk01C;
        pos = obj->unk010;
        VECSubtract(&pos, &prevPos, &dir);
        dir.y = 0.0f;
        len = VECMag(&dir);
        VECNormalize(&dir, &norm);
        batPos = pm->unk0B8;
        batPos.y = 0.0f;
        VECSubtract(&batPos, &prevPos, &dir);
        dot = VECDotProduct(&dir, &norm);
        if (dot <= 0.0f) {
            near = prevPos;
        } else if (dot > len) {
            near = pos;
        } else {
            VECScale(&norm, &dir, dot);
            VECAdd(&prevPos, &dir, &near);
        }
        VECSubtract(&near, &pm->unk0B8, &dir);
        dir.y = 0.0f;
        len = VECMag(&dir);
        if (len > 146.0f) {
            return 0;
        }
        VECSubtract(&pos, &pm->unk0B8, &dir);
        dir.y = 0.0f;
        if (dir.x || dir.z) {
            VECNormalize(&dir, &dir);
        }
        angle = M510_WRAP_D(HuAtan(dir.x, dir.z));
        VECSubtract(&prevPos, &pm->unk0B8, &dir);
        dir.y = 0.0f;
        if (dir.x || dir.z) {
            VECNormalize(&dir, &dir);
        }
        prevAngle = M510_WRAP_D(HuAtan(dir.x, dir.z));
        prevSwing = pm->unk0E0;
        swing = pm->unk0DC;
        mid = M510_WRAP_F(prevSwing + 0.5f * (swing - prevSwing));
        ballMid = M510_WRAP_F(angle + 0.5f * (prevAngle - angle));
        range = M510_ABS(M510_WRAP_F(0.5f * (swing - prevSwing)) + M510_WRAP_F(0.5f * (prevAngle - angle)));
        if (M510_ABS(M510_WRAP_F(mid - ballMid)) < range) {
            MTXRotRad(rot, 'Y', 0.017453292f * (swing - angle));
            VECSubtract(&pos, &pm->unk0B8, &dir);
            MTXMultVec(rot, &dir, &dir);
            VECAdd(&dir, &pm->unk0B8, hit);
            Hu3DModelPosSet(pm->unk108, pitch->unk010.x, hit->y, hit->z);
            Hu3DModelAttrReset(pm->unk108, HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(pm->unk108, 0.0f);
            pm->unk10C = 1;
            obj->unk248 = pm->unk006;
            return 1;
        }
    }
    return 0;
}

/* 73 insns */
void fn_1_8060(M510_BALL *ball, M510_BALLOBJ *slot, s16 type, s32 on)
{
    M510_PLAYER *player = ball->unk000;
    M510_WORK *work = player->unk000;
    M510_CAMERA *camera = &work->unk2474;

    if (slot->unk00C == 0 && on != 0) {
        Hu3DModelScaleSet(slot->unk05A, 1.8f, 1.8f, 1.8f);
        Hu3DModelScaleSet(slot->unk05C, 1.8f, 1.8f, 1.8f);
        Hu3DModelAttrReset(slot->unk05A, HU3D_ATTR_DISPOFF);
        slot->unk058 = type;
        slot->unk00C = 1;
    }
    else if (slot->unk00C != 0 && on == 0) {
        fn_1_C5F0(&slot->unk060);
        Hu3DModelAttrSet(slot->unk05A, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(slot->unk05C, HU3D_ATTR_DISPOFF);
        slot->unk00C = 0;
        slot->unk006 = 0;
        slot->unk004 = 0;
    }
}
