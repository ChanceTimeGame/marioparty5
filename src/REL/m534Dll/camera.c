/*
 * m534dll camera and result phases. Functions are in reference order. Line
 * ranges are into build/mp5-asm/m534Dll/asm/REL/m534Dll/camera.s.
 * The camera is driven through the DOL's Center, CRot and CZoom.
 */

#include "REL/m534Dll.h"

#include "game/audio.h"
#include "game/flag.h"
#include "game/gamemes.h"
#include "game/gamework.h"

#include "math.h"

/* --- .data --- */

M534_CAMVIEW lbl_1_data_50[6] = {
    { { 0.0f, 0.0f, -800.0f }, { -60.0f, 0.0f, 3200.0f } },
    { { 0.0f, 0.0f, -170.0f }, { -25.0f, 0.0f, 1000.0f } },
    { { 0.0f, 0.0f, -520.0f }, { -45.0f, 0.0f, 800.0f } },
    { { 0.0f, 200.0f, 0.0f }, { -2.5f, 0.0f, 810.0f } },
    { { -170.0f, 100.0f, 0.0f }, { -2.5f, 0.0f, 450.0f } },
    { { 170.0f, 100.0f, 0.0f }, { -2.5f, 0.0f, 450.0f } },
};

/* --- .bss --- */

s32 lbl_1_bss_28;                 /* opening camera sound, -1 when none */
s32 lbl_1_bss_2C;                 /* result GameMes id */

/* asm 9-35, 23 insns. Unreferenced in every unit: screen x to pan. */
s32 fn_1_1840(float x)
{
    s32 pan;
    x *= (64.0f / 576.0f);
    pan = 32.0f + x;
    if (pan < 32) {
        pan = 32;
    }
    if (pan > 96) {
        pan = 96;
    }
    return pan;
}

/* asm 38-78, 37 insns. Pan for a 3D position. */
s32 fn_1_189C(HuVecF *pos)
{
    HuVecF out;
    Hu3D3Dto2D(pos, 1, &out);
    return fn_1_1840(out.x);
}

/* asm 81-130, 46 insns. Unreferenced in every unit: positional HuAudFXPlayPan. */
s32 fn_1_1930(s32 seNo, HuVecF *pos)
{
    return HuAudFXPlayPan(seNo, fn_1_189C(pos));
}

/* asm 133-169, 35 insns. Opening camera; objman is not read. Returns fn_1_1A74. */
OMOBJFUNC fn_1_19E8(OMOBJMAN *objman)
{
    M534_CAMVIEW *view = &lbl_1_data_50[0];

    Center = view->center;
    CRot.x = view->rot.x;
    CRot.y = view->rot.y;
    CRot.z = 0.0f;
    CZoom = view->rot.z;
    return fn_1_1A74;
}

/* asm 172-414, 224 insns. Opening camera object function; 8-case switch (.data:0xE0). */
void fn_1_1A74(OMOBJ *obj)
{
    M534_MAIN *work = obj->data;
    s32 from = -1;
    s32 to = -1;
    u32 time = 0;
    float speed = 1.0f;
    u32 next = 7;
    float shake = 0.0f;
    float t;

    fn_1_444(obj);
    switch (work->camMode) {
        case 0:
            lbl_1_bss_28 = -1;
        case 1:
            from = 1;
            to = 1;
            time = 60;
            next = 2;
            break;
        case 2:
            next = 3;
            break;
        case 3:
            from = 1;
            to = 2;
            time = 30;
            speed = 24.0f;
            next = 4;
            break;
        case 4:
            from = to = 2;
            shake = (float)work->camMode * 1.0;
            if (shake > 10.0) {
                shake = 10.0f;
            }
            time = 42;
            next = 5;
            if (lbl_1_bss_28 == -1) {
                lbl_1_bss_28 = HuAudFXPlay(1979);
            }
            break;
        case 5:
            from = to = 2;
            shake = 20.0f;
            time = 12;
            next = 6;
            if (lbl_1_bss_28 != -1) {
                HuAudFXFadeOut(lbl_1_bss_28, 30);
                lbl_1_bss_28 = -1;
            }
            break;
        case 6:
            from = 2;
            to = 3;
            time = 12;
            speed = 60.0f;
            next = 7;
            break;
        case 7:
            fn_1_518(obj);
        default:
            return;
    }
    if (work->camTime < time) {
        t = 0.0f;
    } else {
        t = (1.0f / speed) * (work->camTime - time);
        if (t >= 1.0) {
            t = 1.0f;
        } else {
            t = sin((M_PI / 2) * t);
        }
    }
    if (t >= 1.0) {
        work->camMode = next;
        work->camTime = 0;
    }
    if (from >= 0) {
        fn_1_2130(from, to, t);
    }
    if (shake > 0.0f) {
        t = (M_PI / 2) * (float)(work->camTime & 3);
        Center.x += shake * sin(t);
        Center.z += shake * cos(t);
    }
}

/* asm 417-502, 74 insns. Decide the winners into M534_MAIN; returns fn_1_1F1C. */
OMOBJFUNC fn_1_1DF4(OMOBJMAN *objman, OMOBJ *obj)
{
    M534_MAIN *work = obj->data;
    s32 i;

    switch (fn_1_4624()) {
        case 1:
            work->winTeam = 1;
            break;
        case -1:
            work->winTeam = 2;
            break;
        case 0:
        default:
            work->winTeam = 0;
            break;
    }
    for (i = 0; i < 4; i++) {
        work->winner[i] = -1;
        if ((work->winTeam == 1 && work->team[i] == 0) || (work->winTeam == 2 && work->team[i] == 1)) {
            work->winner[i] = work->charNo[i];
        }
    }
    work->resultMode = 1;
    work->resultTime = 0;
    lbl_1_bss_2C = -1;
    return fn_1_1F1C;
}

/* asm 505-649, 133 insns. Result object function. */
void fn_1_1F1C(OMOBJ *obj)
{
    M534_MAIN *work = obj->data;
    s32 i;
    s16 coin;

    fn_1_444(obj);
    switch (work->resultMode) {
        case 1:
            if (fn_1_49BC()) {
                work->resultTime = 0;
                if (work->winTeam == 0) {
                    lbl_1_bss_2C = GameMesCreate(GAMEMES_MES_MG, GAMEMES_MG_TYPE_DRAW);
                    work->resultMode = 4;
                    HuAudJinglePlay(123);
                } else {
                    work->resultMode = 2;
                }
            }
            break;
        case 2:
            work->resultMode = 3;
            work->resultTime = 0;
            break;
        case 3:
            if (!(work->resultTime < 12.0)) {
                lbl_1_bss_2C = GameMesCreate(GAMEMES_MES_MG_WINNER, GAMEMES_MG_TYPE_WIN, work->winner[0], work->winner[1],
                    work->winner[2], work->winner[3]);
                work->resultMode = 4;
                work->resultTime = 0;
                for (i = 0; i < 4; i++) {
                    if (work->winner[i] >= 0) {
                        GWMgCoinBonusSet(i, GWMgCoinBonusGet(i) + 10);
                    }
                }
                HuAudJinglePlay(121);
            }
            break;
        case 4:
            if (!(work->resultTime < 210.0)) {
                work->resultMode = 5;
                fn_1_518(obj);
            }
            break;
    }
}

/* asm 652-744, 88 insns. Interpolate between lbl_1_data_50 rows. */
void fn_1_2130(s32 from, s32 to, float t)
{
    M534_CAMVIEW *a;
    M534_CAMVIEW *b;
    HuVecF v;

    if (from < 0) {
        if (to < 0) {
            return;
        }
        from = to;
    }
    if (to < 0) {
        to = from;
    }
    a = &lbl_1_data_50[from];
    b = &lbl_1_data_50[to];
    PSVECSubtract(&b->center, &a->center, &v);
    PSVECScale(&v, &v, t);
    PSVECAdd(&a->center, &v, &v);
    Center = v;
    PSVECSubtract(&b->rot, &a->rot, &v);
    PSVECScale(&v, &v, t);
    PSVECAdd(&a->rot, &v, &v);
    CRot.x = v.x;
    CRot.y = v.y;
    CRot.z = 0.0f;
    CZoom = v.z;
}
