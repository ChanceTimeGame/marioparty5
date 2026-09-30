/*
 * m574Dll ball.c -- decompiled from the reference assembly; functions are in reference
 * order. Line ranges are into build/mp5-asm/m574Dll/asm/REL/m574Dll/ball.s.
 */

#include "REL/m574Dll.h"

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
/* 0x278 */ /* float lbl_1_rodata_278 = 40.0f; */
/* 0x280 */ /* double lbl_1_rodata_280 = 20; */
/* 0x288 */ /* float lbl_1_rodata_288 = 0.0f; */
/* 0x290 */ /* double lbl_1_rodata_290 = 1550; */
/* 0x298 */ /* double lbl_1_rodata_298 = 1600; */
/* 0x2A0 */ /* double lbl_1_rodata_2A0 = 0.98; */
/* 0x2A8 */ /* double lbl_1_rodata_2A8 = 1.666666753590107; */
/* 0x2B0 */ /* double lbl_1_rodata_2B0 = -200; */
/* 0x2B8 */ /* double lbl_1_rodata_2B8 = -170; */
/* 0x2C0 */ /* double lbl_1_rodata_2C0 = 170; */
/* 0x2C8 */ /* double lbl_1_rodata_2C8 = 598; */
/* 0x2D0 */ /* double lbl_1_rodata_2D0 = 817; */
/* 0x2D8 */ /* float lbl_1_rodata_2D8 = 100000.0f; */
/* 0x2E0 */ /* double lbl_1_rodata_2E0 = 180; */
/* 0x2E8 */ /* double lbl_1_rodata_2E8 = 3.141592653589793; */
/* 0x2F0 */ /* double lbl_1_rodata_2F0 = 360; */
/* 0x2F8 */ /* float lbl_1_rodata_2F8 = 360.0f; */
/* 0x300 */ /* double lbl_1_rodata_300 = 0.5; */
/* 0x308 */ /* double lbl_1_rodata_308 = 3; */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x50 */ OMOBJ *lbl_1_bss_50[2]; /* dtk sizes this 0x8; only slot 0 (the ball object) is used */

/* --- functions (reference order) --- */
/* 40 insns. Called from ObjectSetup. */
void fn_1_6650(OMOBJMAN *objman)
{
    OMOBJ *obj;
    M574_BALL *work;

    obj = omAddObjEx(objman, 30, 80, 0, -1, fn_1_66F4);
    lbl_1_bss_50[0] = obj;
    obj->stat |= OM_STAT_MODELPAUSE;
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M574_BALL) * 80, HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M574_BALL) * 80);
    obj->work[0] = 0;
}

/* 1 insns */
void fn_1_66F0(void)
{
}

/* 15 insns */
void fn_1_66F4(OMOBJ *obj)
{
    fn_1_6758(obj);
    obj->objFunc = fn_1_6730;
}

/* 10 insns */
void fn_1_6730(OMOBJ *obj)
{
    fn_1_686C(obj);
}

/* 69 insns. One linked model and one collide record per ball. */
void fn_1_6758(OMOBJ *obj)
{
    M574_BALL *work;
    HU3DMODELID baseMdl;
    M574_BALL *ball;
    s32 i;
    HU3DMODELID mdlId;
    M574_COLLIDE *col;

    work = obj->data;
    for (i = 0; i < 80; i++) {
        ball = &work[i];
        if (i == 0) {
            mdlId = baseMdl = Hu3DModelCreate(HuDataSelHeapReadNum(0x810007, HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            mdlId = Hu3DModelLink(baseMdl);
        }
        ball->unk014 = mdlId;
        Hu3DModelLayerSet(mdlId, 4);
        Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
        col = &ball->unk03C;
        col->unk00 = 0;
        col->unk04 = 0;
        col->unk08 = i;
        col->unk0C = 0;
        col->unk10 = ball;
        col->unk14 = (void (*)(void *))fn_1_6BD4;
        col->unk18 = &ball->unk018;
        col->unk1C = &ball->unk024;
        col->unk20 = ball->unk018;
        col->unk2C = 40.0f;
        fn_1_8AD0(col);
    }
}

/* 179 insns. Ball physics. */
void fn_1_686C(OMOBJ *obj)
{
    M574_BALL *work;
    s32 i;
    M574_BALL *ball;
    s32 in;
    HU3DMODELID mdlId;
    s32 side;
    s32 side2;

    work = obj->data;
    for (i = 0; i < 80; i++) {
        ball = &work[i];
        mdlId = ball->unk014;
        switch (ball->unk000) {
            case 0:
                break;
            case 1:
                ball->unk000++;
                ball->unk008 = 0;
                Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
                HuAudFXPlay(0x915);
            case 2:
                ball->unk024.z -= 20.0;
                if (ball->unk018.z + ball->unk024.z <= 0.0f) {
                    ball->unk000++;
                    ball->unk018.z = 0.0f;
                    ball->unk024.z = 0.0f;
                    ball->unk03C.unk00 |= 1;
                }
            case 3:
                if (ball->unk03C.unk00 & 2) {
                    break;
                }
                if (ball->unk00C) {
                    if (ball->unk018.y < 1550.0) {
                        ball->unk00C = 0;
                    }
                } else if (ball->unk018.y > 1600.0) {
                    ball->unk00C = 1;
                    if (ball->unk018.x < 0.0f) {
                        side = 0;
                    } else {
                        side = 1;
                    }
                    fn_1_77D4(side, 12);
                }
                ball->unk024.x *= 0.98;
                ball->unk024.y -= 1.666666753590107;
                if (ball->unk024.y < 0.0f && ball->unk018.y < -200.0) {
                    if (ball->unk018.x < 0.0f) {
                        side2 = 0;
                    } else {
                        side2 = 1;
                    }
                    fn_1_1F9C(side2);
                    ball->unk000 = 0;
                    ball->unk03C.unk00 = 0;
                    Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
                    if (ball->unk024.x < 0.0f) {
                        HuAudFXPlay(0x92D);
                    } else {
                        HuAudFXPlay(0x92E);
                    }
                }
                break;
        }
        if (ball->unk000 != 0) {
            PSVECAdd(&ball->unk018, &ball->unk024, &ball->unk018);
            in = fn_1_6B38(ball);
            if (ball->unk010 != in) {
                ball->unk010 = in;
                HuAudFXPlay(0x91D);
            }
        }
    }
}

/* 39 insns. Inside the x -170..170, y 598..817 box. */
s32 fn_1_6B38(M574_BALL *ball)
{
    HuVecF *pos = &ball->unk018;

    if (pos->x < -170.0) {
        return 0;
    }
    if (pos->x > 170.0) {
        return 0;
    }
    if (pos->y < 598.0) {
        return 0;
    }
    if (pos->y > 817.0) {
        return 0;
    }
    return 1;
}

/* 22 insns. Collide callback. */
void fn_1_6BD4(M574_BALL *ball)
{
    HU3DMODELID mdlId = ball->unk014;

    Hu3DModelPosSetV(mdlId, &ball->unk018);
    ball->unk03C.unk20 = ball->unk018;
}

/* 39 insns. Launch the first free ball. */
void fn_1_6C2C(HuVecF *pos, HuVecF *vel)
{
    M574_BALL *work;
    s32 i;
    M574_BALL *ball;

    work = lbl_1_bss_50[0]->data;
    for (i = 0; i < 80; i++) {
        ball = &work[i];
        if (ball->unk000 == 0) {
            ball->unk000++;
            ball->unk018 = *pos;
            ball->unk024 = *vel;
            break;
        }
    }
}

/* 45 insns. Live balls on one side (0: x < 0, else x >= 0). */
s32 fn_1_6CC8(s32 side)
{
    M574_BALL *work;
    s32 num;
    s32 i;
    M574_BALL *ball;

    work = lbl_1_bss_50[0]->data;
    num = 0;
    for (i = 0; i < 80; i++) {
        ball = &work[i];
        if (ball->unk000 != 0) {
            if (side == 0) {
                if (ball->unk018.x < 0.0f) {
                    num++;
                }
            } else if (ball->unk018.x >= 0.0f) {
                num++;
            }
        }
    }
    return num;
}

/* 205 insns. Nearest live ball on a side, within an angle window and distance. */
s32 fn_1_6D7C(s32 side, HuVecF *pos, float angle, float range, float maxDist)
{
    M574_BALL *work;
    s32 best;
    s32 i;
    M574_BALL *ball;
    float dx;
    float dy;
    float ang; /* also the distance */
    float rel;
    float bestDist;

    work = lbl_1_bss_50[0]->data;
    bestDist = 100000.0f;
    best = -1;
    for (i = 0; i < 80; i++) {
        ball = &work[i];
        if (ball->unk000 == 0) {
            continue;
        }
        if (side == 0) {
            if (ball->unk018.x >= 0.0f) {
                continue;
            }
        } else if (ball->unk018.x < 0.0f) {
            continue;
        }
        dx = ball->unk018.x - pos->x;
        dy = ball->unk018.y - pos->y;
        if (range < 180.0) {
            ang = 180.0 * (atan2(dx, dy) / M_PI);
            rel = fmod(ang - angle, 360.0);
            ang = rel;
            if (ang < 0.0f) {
                ang += 360.0f;
            }
            if (ang > range && ang < 360.0f - range) {
                continue;
            }
        }
        ang = sqrtf(dx * dx + dy * dy);
        if (ang > maxDist) {
            continue;
        }
        if (ang < bestDist) {
            bestDist = ang;
            best = i;
        }
    }
    return best;
}

/* 32 insns */
M574_COLLIDE *fn_1_70B0(s32 no, HuVecF *pos, HuVecF *vel)
{
    M574_BALL *work = lbl_1_bss_50[0]->data;
    M574_BALL *ball = &work[no];

    if (pos != NULL) {
        *pos = ball->unk018;
    }
    if (vel != NULL) {
        *vel = ball->unk024;
    }
    return &ball->unk03C;
}
