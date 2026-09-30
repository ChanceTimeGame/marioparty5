/*
 * m533dll pillar particles: the spray columns along the course and at the
 * goal, written from the reference assembly in reference order.
 * Line ranges are into build/mp5-asm/m533dll/asm/REL/m533dll/pillar.s.
 *
 * The helper block at fn_1_7390..fn_1_8274 is REL/m563dll/math.c, included
 * first; this unit's copy of its .bss is bss_2D8..bss_4E0. .data:0x70C is
 * the OSReport literal in fn_1_6590.
 */

#include "REL/m563dll/math.c"

#include "REL/m533Dll.h"

#include "game/sprite.h"

/* --- .data --- */

/* Pillar spawn points; the zero entry ends the list. */
HuVecF lbl_1_data_670[13] = {
    { -800.0f, -700.0f, 600.0f },
    { 1100.0f, -700.0f, 420.0f },
    { 2000.0f, -600.0f, -700.0f },
    { 2900.0f, -700.0f, 220.0f },
    { 3900.0f, -600.0f, 350.0f },
    { 5600.0f, -700.0f, -750.0f },
    { 6800.0f, -500.0f, 220.0f },
    { 7600.0f, -700.0f, -700.0f },
    { 8600.0f, -700.0f, 700.0f },
    { 10300.0f, -700.0f, -700.0f },
    { 12400.0f, -700.0f, -700.0f },
    { 14000.0f, -700.0f, 350.0f },
    { 0.0f, 0.0f, 0.0f },
};

/* --- .bss --- */

ANIMDATA *lbl_1_bss_2C8;
void *lbl_1_bss_2CC;              /* dtk sizes this 0x8; only the pointer is referenced */
s32 lbl_1_bss_2D4;

/* asm 9-36, 26 insns. Called from ObjectSetup. */
void fn_1_6528(void)
{
    lbl_1_bss_2CC = HuDataSelHeapReadNum(0x5B000F, HU_MEMNUM_OVL, HEAP_MODEL);
    lbl_1_bss_2C8 = HuSprAnimRead(lbl_1_bss_2CC);
    lbl_1_bss_2D4 = 0;
}

/* asm 39-166, 120 insns. Called from ObjectSetup. */
void fn_1_6590(OMOBJ *obj)
{
    HuVecF pos;
    s32 i;
    float size;

    for (i = 0; i < 12; i++) {
        if (0.0f == lbl_1_data_670[lbl_1_bss_2D4].x && 0.0f == lbl_1_data_670[lbl_1_bss_2D4].y && 0.0f == lbl_1_data_670[lbl_1_bss_2D4].z) {
            OSReport("******* No entry PillarPoint *********\n");
            break;
        }
        pos.x = lbl_1_data_670[lbl_1_bss_2D4].x;
        pos.y = 300.0f + lbl_1_data_670[lbl_1_bss_2D4].y;
        pos.z = lbl_1_data_670[lbl_1_bss_2D4].z;
        if (pos.z < 0.0f) {
            size = 15.0f;
        } else {
            size = 25.0f;
        }
        fn_1_6984(obj, &pos, 0, size, 3);
        lbl_1_bss_2D4++;
    }
}

/* asm 169-303, 133 insns. */
void fn_1_6770(OMOBJ *obj, s32 cameraBit)
{
    HuVecF pos;

    pos.x = 11400.0f;
    pos.y = -400.0f;
    pos.z = -600.0f;
    fn_1_6984(obj, &pos, 1, 50.0f, cameraBit);
    pos.x = 11500.0f;
    pos.y = -400.0f;
    pos.z = -600.0f;
    fn_1_6984(obj, &pos, 1, 50.0f, cameraBit);
    pos.x = 11600.0f;
    pos.y = -400.0f;
    pos.z = -600.0f;
    fn_1_6984(obj, &pos, 1, 50.0f, cameraBit);
    pos.x = 11400.0f;
    pos.y = -400.0f;
    pos.z = 1000.0f;
    fn_1_6984(obj, &pos, 1, 50.0f, cameraBit);
    pos.x = 11500.0f;
    pos.y = -400.0f;
    pos.z = 1000.0f;
    fn_1_6984(obj, &pos, 1, 50.0f, cameraBit);
    pos.x = 11600.0f;
    pos.y = -400.0f;
    pos.z = 1000.0f;
    fn_1_6984(obj, &pos, 1, 50.0f, cameraBit);
}

/* asm 306-412, 101 insns. The float parameter is passed and never read. */
void fn_1_6984(OMOBJ *obj, HuVecF *pos, s32 type, float unused, u16 cameraBit)
{
    if (type == 0) {
        obj->mdlId[0] = Hu3DParticleCreate(lbl_1_bss_2C8, 50);
    } else {
        obj->mdlId[0] = Hu3DParticleCreate(lbl_1_bss_2C8, 100);
    }
    Hu3DModelCameraSet(obj->mdlId[0], cameraBit);
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(obj->mdlId[0], pos->x, pos->y, pos->z);
    Hu3DModelLayerSet(obj->mdlId[0], 5);
    if (type == 0) {
        Hu3DParticleHookSet(obj->mdlId[0], fn_1_6B18);
    } else {
        Hu3DParticleHookSet(obj->mdlId[0], fn_1_6F54);
    }
    Hu3DParticleBlendModeSet(obj->mdlId[0], 0);
    Hu3DParticleColSet(obj->mdlId[0], 255, 255, 255);
    obj->trans.x = pos->x;
    obj->trans.y = pos->y;
    obj->trans.z = pos->z;
    omSetTra(obj, pos->x, pos->y, pos->z);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
}

/* asm 415-702, 271 insns. Particle hook. */
void fn_1_6B18(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx)
{
    HU3DPARTICLEDATA *data;
    s32 i;
    s32 j;

    if (particle->count == 0) {
        data = particle->data;
        for (i = 0; i < particle->maxCnt; i++, data++) {
            data->color.a = 0;
            data->scale = 0.0f;
        }
        particle->dataCnt = 0;
    }
    if (particle->dataCnt == 0) {
        for (i = 0; i < 2; i++) {
            data = particle->data;
            for (j = 0; j < particle->maxCnt; j++, data++) {
                if (data->color.a == 0) {
                    break;
                }
            }
            if (j != particle->maxCnt) {
                data->vel.x = -50.0f + 0.3921569f * (frand() & 0xFF);
                data->vel.y = 0.058823533f * (frand() & 0xFF);
                data->accel.x = 0.3529412f * (frand() & 0xFF);
                data->accel.y = 5.0f + 0.098039225f * (frand() & 0xFF);
                data->accel.z = 8.0f + (frand() % 10);
                data->pos.z = -5.0f + 0.043137256f * (frand() & 0xFF);
                data->pos.y = -5.0f + (frand() % 31);
                data->scale = 35.0f + data->vel.y;
                data->color.a = 255;
                data->vel.y = 5.0 + 0.2 * data->vel.y;
                particle->dataCnt = frand() % 10 + 10;
            }
        }
    } else {
        particle->dataCnt--;
    }
    data = particle->data;
    for (i = 0; i < particle->maxCnt; i++, data++) {
        if (data->color.a != 0) {
            data->pos.x = data->vel.x + data->accel.z * sin(M_PI * data->accel.x / 180.0);
            data->accel.x += data->accel.y;
            if (data->accel.x >= 360.0f) {
                data->accel.x -= 360.0f;
            }
            data->pos.y += data->vel.y;
            data->color.a--;
        }
    }
}

/* asm 705-992, 271 insns. Particle hook. */
void fn_1_6F54(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx)
{
    HU3DPARTICLEDATA *data;
    s32 i;
    s32 j;

    if (particle->count == 0) {
        data = particle->data;
        for (i = 0; i < particle->maxCnt; i++, data++) {
            data->color.a = 0;
            data->scale = 0.0f;
        }
        particle->dataCnt = 0;
    }
    if (particle->dataCnt == 0) {
        for (i = 0; i < 5; i++) {
            data = particle->data;
            for (j = 0; j < particle->maxCnt; j++, data++) {
                if (data->color.a == 0) {
                    break;
                }
            }
            if (j != particle->maxCnt) {
                data->vel.x = -50.0f + 0.3921569f * (frand() & 0xFF);
                data->vel.y = 0.058823533f * (frand() & 0xFF);
                data->accel.x = 0.3529412f * (frand() & 0xFF);
                data->accel.y = 10.0f + 0.098039225f * (frand() & 0xFF);
                data->accel.z = 8.0f + (frand() % 10);
                data->pos.z = -5.0f + 0.043137256f * (frand() & 0xFF);
                data->pos.y = -5.0f + (frand() % 31);
                data->scale = 45.0f + data->vel.y;
                data->color.a = 255;
                data->vel.y = 15.0 + 0.2 * data->vel.y;
                particle->dataCnt = frand() % 10 + 10;
            }
        }
    } else {
        particle->dataCnt--;
    }
    data = particle->data;
    for (i = 0; i < particle->maxCnt; i++, data++) {
        if (data->color.a != 0) {
            data->pos.x = data->vel.x + data->accel.z * sin(M_PI * data->accel.x / 180.0);
            data->accel.x += data->accel.y;
            if (data->accel.x >= 360.0f) {
                data->accel.x -= 360.0f;
            }
            data->pos.y += data->vel.y;
            data->color.a--;
        }
    }
}
