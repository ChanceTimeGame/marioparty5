/*
 * m510dll ball_path.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m510dll/asm/REL/m510dll/ball_path.s.
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

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x3E8 */ /* s32 lbl_1_rodata_3E8[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x3F4 */ /* float lbl_1_rodata_3F4 = 1.0f; */
/* 0x3F8 */ /* float lbl_1_rodata_3F8 = 0.0f; */
/* 0x400 */ /* double lbl_1_rodata_400 = 4503601774854144; */
/* 0x408 */ /* float lbl_1_rodata_408 = 2.0f; */
/* 0x40C */ /* float lbl_1_rodata_40C = 3.0f; */

/* --- functions (reference order) --- */
/* 12 insns */
void fn_1_C590(M510_BALLPATH *path)
{
    memset(path, 0, sizeof(M510_BALLPATH));
}

/* 12 insns */
void fn_1_C5C0(M510_BALLPATH *path)
{
    memset(path, 0, sizeof(M510_BALLPATH));
}

/* 24 insns */
void fn_1_C5F0(M510_BALLPATH *path)
{
    path->unk000 = 0;
    memset(path->unk004, 0, sizeof(path->unk004));
    memset(path->unk124, 0, sizeof(path->unk124));
    memset(path->unk184, 0, sizeof(path->unk184));
}

/* 47 insns */
void fn_1_C650(M510_BALLPATH *path, HuVecF pos, s32 time)
{
    if (path->unk000 < 24) {
        path->unk004[path->unk000] = pos;
        path->unk124[path->unk000] = time;
        if (path->unk000 != 0) {
            path->unk184[path->unk000] = path->unk184[path->unk000 - 1] + path->unk124[path->unk000];
        }
        else {
            path->unk184[path->unk000] = path->unk124[path->unk000];
        }
        path->unk000++;
    }
}

/* 241 insns */
HuVecF fn_1_C70C(M510_BALLPATH *path, s32 time, float tension)
{
    HuVecF out = (HuVecF) { 0.0f, 0.0f, 0.0f };
    HuVecF p0;
    HuVecF p1;
    HuVecF m0;
    HuVecF m1;
    float t;
    s32 i;
    s32 key;

    time = (time > path->unk184[path->unk000 - 1]) ? path->unk184[path->unk000 - 1] : ((time < 0) ? 0 : time);
    for (i = 0; i < path->unk000; i++) {
        if (time <= path->unk184[i]) {
            if (i == 0) {
                t = (float)time / (float)path->unk184[0];
            }
            else {
                t = (float)(time - path->unk184[i - 1]) / (float)(path->unk184[i] - path->unk184[i - 1]);
            }
            key = i;
            if (key == path->unk000 - 1) {
                key--;
                t = 1.0f;
            }
            p0.x = path->unk004[key].x;
            p0.y = path->unk004[key].y;
            p0.z = path->unk004[key].z;
            p1.x = path->unk004[key + 1].x;
            p1.y = path->unk004[key + 1].y;
            p1.z = path->unk004[key + 1].z;
            m0 = fn_1_CAD0(path, key, tension);
            m1 = fn_1_CAD0(path, key + 1, tension);
            t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
            out = fn_1_CC58(t, p0, p1, m0, m1);
            break;
        }
    }
    return out;
}

/* 98 insns */
HuVecF fn_1_CAD0(M510_BALLPATH *path, s32 idx, float tension)
{
    HuVecF m;

    if (idx <= 0) {
        m.x = path->unk004[1].x - path->unk004[0].x;
        m.y = path->unk004[1].y - path->unk004[0].y;
        m.z = path->unk004[1].z - path->unk004[0].z;
    }
    else if (idx >= path->unk000 - 1) {
        m.x = path->unk004[path->unk000 - 1].x - path->unk004[path->unk000 - 2].x;
        m.y = path->unk004[path->unk000 - 1].y - path->unk004[path->unk000 - 2].y;
        m.z = path->unk004[path->unk000 - 1].z - path->unk004[path->unk000 - 2].z;
    }
    else {
        m.x = tension * (path->unk004[idx + 1].x - path->unk004[idx - 1].x);
        m.y = tension * (path->unk004[idx + 1].y - path->unk004[idx - 1].y);
        m.z = tension * (path->unk004[idx + 1].z - path->unk004[idx - 1].z);
    }
    return m;
}

/* 48 insns */
HuVecF fn_1_CC58(float t, HuVecF p0, HuVecF p1, HuVecF m0, HuVecF m1)
{
    HuVecF out;

    out.x = fn_1_CD18(t, p0.x, p1.x, m0.x, m1.x);
    out.y = fn_1_CD18(t, p0.y, p1.y, m0.y, m1.y);
    out.z = fn_1_CD18(t, p0.z, p1.z, m0.z, m1.z);
    return out;
}

/* 59 insns */
float fn_1_CD18(float t, float p0, float p1, float m0, float m1)
{
    float v;

    v = m1 * ((t - 1.0f) * (t * t)) + (m0 * (t * ((1.0f - t) * (1.0f - t))) + (p0 * ((1.0f + 2.0f * t) * ((t - 1.0f) * (t - 1.0f))) + p1 * ((3.0f - 2.0f * t) * (t * t))));
    return v;
}
