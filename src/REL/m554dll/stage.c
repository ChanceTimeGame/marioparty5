/*
 * m554dll/stage.c -- the arena, the two duellists' models and motions, and
 * three per-frame prop updaters. Written from the reference assembly,
 * functions in reference order; line ranges are into
 * build/mp5-asm/m554dll/asm/REL/m554dll/stage.s.
 *
 * The KETTOU stage framework, REL/duelstage.h, supplies fn_1_62F0, fn_1_6C20,
 * fn_1_6C44, fn_1_6E80, fn_1_733C, fn_1_7490 (with DS_SHIFT_POLL) and
 * fn_1_7F68, included at their reference positions. Against
 * src/REL/m550dll/stage.c the rest is related at most: fn_1_7D74 is m550's
 * M550Unk6B6C with other model numbers, effect base 4 and no clamp (0.93);
 * fn_1_653C, fn_1_6C68 and fn_1_78F4 are loosely related (0.5-0.7).
 * Everything else is this overlay's own.
 */

#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/frand.h"
#include "game/pad.h"
#include "game/audio.h"

#include "datadir_enum.h"

#include "REL/m554dll/m554.h"

#include "dolphin/os.h"

#include "math.h"
#include "humath.h"
#include "string.h"

void fn_1_78F4(void);
void fn_1_7D74(void);
void fn_1_7FCC(void);

/* --- .data --- */

HuVecF lbl_1_data_258[6] = { 0 };   /* [m550 PosTbl] six scratch positions, zeroed */
u32 lbl_1_data_2A0 = 0x00700015;    /* [m550 SubDataTbl] */
HU3DMOTID lbl_1_data_2A4[2] = { 0, 0 };  /* unreferenced; a zero scalar would go to .bss */

/*
 * Joint motions made by fn_1_653C. Its last loop indexes this with a counter
 * the loop before it left at 4, so retail stores and reads element 4, inside
 * the unreferenced table below. The host gives it room for that element.
 */
HU3DMOTID lbl_1_data_2A8[2] = { 0, 0 };

/* The three prop updaters; unreferenced (fn_1_7880 calls them directly). */
void (*lbl_1_data_2AC[3])(void) = { fn_1_78F4, fn_1_7D74, fn_1_7FCC };

/* --- .bss --- */

M554_WORK *lbl_1_bss_1360;          /* [m550 StageWork] set by fn_1_62F0 */

/* --- the duel stage framework (REL/duelstage.h) --- */

#define DS_WORK                 M554_WORK
#define DS_STAGEWORK            lbl_1_bss_1360
#define DS_CHARMDL              0x4E
#define DS_MOTIONEXEC_NUM       2
#define DS_SHIFT_POLL
#define DS_CHARMOTION_NUM       5
#define DS_CHARMOTION_SPEEDCUR  1.0f
#define DS_FN_WorkInit          fn_1_62F0
#define DS_FN_CharMotDataSet    fn_1_6C20
#define DS_FN_CharMotIdSet      fn_1_6C44
#define DS_FN_PadRead           fn_1_6E80
#define DS_FN_CharMotionCreate  fn_1_733C
#define DS_FN_MotionExec        fn_1_7490
#define DS_FN_Effect9Stop       fn_1_7F68
#define DS_EFFECT9STOP_IDX      9

/* asm 9-165, 147 insns. [m550 M550WorkInit] */
#define DS_S_WORKINIT
#include "REL/duelstage.h"

/* asm 168-630, 441 insns. [m550 ?M550StageModelCreate] */
void fn_1_653C(s16 stageNo)
{
    M554_MODEL *model;
    HU3DMODELID id;
    int k;
    s16 i;
    s16 mdlNo;
    int j;

    lbl_1_bss_1360->stageNo = stageNo;
    for(i=0; i<2; i++) {
        mdlNo = (s16)i;
        id = lbl_1_bss_1360->models[mdlNo].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1360->stageDataTbl[i], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(id, 1);
        Hu3DModelPosSetV(id, &lbl_1_data_258[i]);
        lbl_1_bss_1360->models[mdlNo].pos.x = lbl_1_data_258[i].x;
        lbl_1_bss_1360->models[mdlNo].pos.y = lbl_1_data_258[i].y;
        lbl_1_bss_1360->models[mdlNo].pos.z = lbl_1_data_258[i].z;
        if(i != 0) {
            Hu3DModelRotSet(id, 0.0f, -180.0f, 0.0f);
            lbl_1_bss_1360->models[mdlNo].rot.x = 0.0f;
            lbl_1_bss_1360->models[mdlNo].rot.y = -180.0f;
            lbl_1_bss_1360->models[mdlNo].rot.z = 0.0f;
            Hu3DMotionTimeSet(id, 0.0f);
            Hu3DMotionSpeedSet(id, 1.0f);
            Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
        } else {
            Hu3DModelRotSet(id, 0.0f, 0.0f, 0.0f);
            lbl_1_bss_1360->models[mdlNo].rot.x = 0.0f;
            lbl_1_bss_1360->models[mdlNo].rot.y = 0.0f;
            lbl_1_bss_1360->models[mdlNo].rot.z = 0.0f;
        }
        Hu3DModelLayerSet(id, 0);
        Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    }
    for(k=0; k<2; k++) {
        model = &lbl_1_bss_1360->models[k+84];
        model->modelId = Hu3DModelCreate(HuDataSelHeapReadNum((lbl_1_bss_1360->stageDataTbl+15)[k], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(model->modelId, HU3D_ATTR_DISPOFF);
        Hu3DMotionSpeedSet(model->modelId, 0.5f);
        Hu3DModelCameraSet(model->modelId, 1);
        Hu3DMotionTimeSet(model->modelId, 0.0f);
        if(k != 0) {
            Hu3DModelLayerSet(model->modelId, 1);
        } else {
            Hu3DModelLayerSet(model->modelId, 7);
        }
        model = &lbl_1_bss_1360->models[(k*2)+86];
        for(j=0; j<2; j++, model++) {
            if(j == 0) {
                id = model->modelId = Hu3DModelCreate(HuDataSelHeapReadNum((lbl_1_bss_1360->stageDataTbl+17)[k], HU_MEMNUM_OVL, HEAP_MODEL));
            } else {
                model->modelId = Hu3DModelLink(id);
            }
            Hu3DModelAttrSet(model->modelId, HU3D_ATTR_DISPOFF);
            Hu3DMotionSpeedSet(model->modelId, 0.5f);
            Hu3DModelCameraSet(model->modelId, 1);
            Hu3DMotionTimeSet(model->modelId, 0.0f);
            Hu3DModelAttrSet(model->modelId, HU3D_MOTATTR_LOOP);
            Hu3DModelLayerSet(model->modelId, 1);
        }
    }
    for(k=0; k<4; k++) {
        model = &lbl_1_bss_1360->models[k+80];
        if(k == 0) {
            id = model->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1360->stageDataTbl[14], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            model->modelId = Hu3DModelLink(id);
        }
        Hu3DModelAttrSet(model->modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(model->modelId, 1);
        Hu3DModelLayerSet(model->modelId, 2);
        Hu3DMotionTimeSet(model->modelId, 50.0f);
        Hu3DMotionSpeedSet(model->modelId, 0.5f);
    }
    /* Retail quirk: k is still 4 here (see lbl_1_data_2A8). */
    model = &lbl_1_bss_1360->models[90];
    for(j=0; j<2; j++, model++) {
        if(j == 0) {
            id = model->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1360->stageDataTbl[19], HU_MEMNUM_OVL, HEAP_MODEL));
            lbl_1_data_2A8[k] = Hu3DJointMotion(model->modelId, HuDataSelHeapReadNum(lbl_1_data_2A0, HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            model->modelId = Hu3DModelLink(id);
        }
        Hu3DModelScaleSet(model->modelId, 1.0f, 1.0f, 1.0f);
        Hu3DMotionSet(model->modelId, lbl_1_data_2A8[k]);
        Hu3DMotionSpeedSet(model->modelId, 1.0f);
        Hu3DModelAttrSet(model->modelId, HU3D_MOTATTR_LOOP);
        Hu3DModelCameraSet(model->modelId, 1);
        Hu3DModelLayerSet(model->modelId, 1);
        Hu3DModelAttrSet(model->modelId, HU3D_ATTR_DISPOFF);
    }
}

/* asm 633-656, 9 + 9 insns. [m550 M550CharMotDataSet, M550CharMotIdSet] */
#define DS_S_CHARMOT
#include "REL/duelstage.h"

/* asm 659-796, 134 insns. [m550 ?M550CharModelCreate] */
void fn_1_6C68(void)
{
    int i;

    for(i=0; i<2; i++) {
        (lbl_1_bss_1360->models+0x4E)[i].modelId = CharModelCreate(lbl_1_bss_1360->chr[i].charNo, 1);
        lbl_1_bss_1360->models[i+0x4E].pos.x = 0.0f;
        lbl_1_bss_1360->models[i+0x4E].pos.y = 0.0f;
        lbl_1_bss_1360->models[i+0x4E].pos.z = 100.0f-(i*200);
        lbl_1_bss_1360->models[i+0x4E].rot.x = 0.0f;
        lbl_1_bss_1360->models[i+0x4E].rot.y = -90.0f;
        lbl_1_bss_1360->models[i+0x4E].rot.z = 0.0f;
        Hu3DModelAttrSet((lbl_1_bss_1360->models+0x4E)[i].modelId, HU3D_MOTATTR_LOOP);
        Hu3DModelCameraSet((lbl_1_bss_1360->models+0x4E)[i].modelId, 1);
        Hu3DModelLayerSet((lbl_1_bss_1360->models+0x4E)[i].modelId, 0);
    }
}

/*
 * asm 799-1479, 303 + 85 + 252 insns. [m550 M550PadRead, M550CharMotionCreate,
 * M550MotionExec; the last with DS_SHIFT_POLL]
 */
#define DS_S_PADREAD
#define DS_S_CHARMOTION
#define DS_S_MOTIONEXEC
#include "REL/duelstage.h"

/* asm 1482-1493, 10 insns. Runs the three prop updaters. */
void fn_1_7880(OMOBJ *obj)
{
    fn_1_78F4();
    fn_1_7D74();
    fn_1_7FCC();
}

/* asm 1496-1518, 19 insns. Loops over the effect slots at 0x364. */
void fn_1_78A8(void)
{
    M554_EFFECT *eff;
    int i;

    eff = lbl_1_bss_1360->effect;
    for(i=0; i<4; i++, eff++) {
        eff->counter = 1;
    }
}

/* asm 1521-1820, 288 insns. Prop updater. [m550 ?M550Unk6600] */
void fn_1_78F4(void)
{
    float height[5] = { 800.0f, 400.0f, 500.0f, 350.0f, 250.0f };
    float scale[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    M554_EFFECT *eff;
    M554_MODEL *mdl;
    int i;
    int j;

    for(i=0; i<4; i++) {
        eff = &lbl_1_bss_1360->effect[i];
        mdl = &lbl_1_bss_1360->models[i+80];
        if(eff->mode == 0) {
            eff->mode = 1;
            eff->timer[0] = 0;
            eff->timer[1] = 0;
            eff->timer[2] = 0;
            eff->f2C = (i*35)+130-(rand8()%20);
            eff->f30 = 2500+(i*400)+(i*5);
            eff->f34 = 0.125+(0.0165*i);
            eff->f38 = height[i];
            Hu3DModelScaleSet(mdl->modelId, scale[i], scale[i], 1.0f);
            mdl->pos.x = eff->f30*sin((M_PI*eff->f2C)/180.0);
            mdl->pos.z = eff->f30*cos((M_PI*eff->f2C)/180.0);
            mdl->pos.y = 100.0f+eff->f38;
            Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(mdl->modelId, 50.0f);
            Hu3DMotionSpeedSet(mdl->modelId, 0.5f);
            Hu3DModelPosSetV(mdl->modelId, &mdl->pos);
        }
        for(j=0; j<3; j++) {
            eff->timer[j]++;
            switch(j) {
                case 0:
                    eff->f2C += eff->f34;
                    if(eff->f2C >= 240.0f) {
                        eff->f2C = 100.0f;
                    }
                    break;

                case 1:
                    if(eff->timer[j] >= 100) {
                        eff->timer[j] = 0;
                        Hu3DMotionTimeSet(mdl->modelId, 50.0f);
                    }
                    break;

                case 2:
                    if(eff->timer[j+1] != 0) {
                        eff->f30 += 20.0f;
                    }
                    break;
            }
        }
        mdl->pos.x = eff->f30*sin((M_PI*eff->f2C)/180.0);
        mdl->pos.z = eff->f30*cos((M_PI*eff->f2C)/180.0);
        mdl->pos.y = 100.0f+eff->f38;
        mdl->rot.y = 180.0f+eff->f2C;
    }
}

/* asm 1823-1952, 125 insns. Prop updater. [m550 ~M550Unk6B6C] */
void fn_1_7D74(void)
{
    int mdlNo[4] = { 86, 88, 87, 89 };
    int i;
    M554_EFFECT *eff;
    M554_MODEL *mdl;

    for(i=0; i<4; i++) {
        eff = &lbl_1_bss_1360->effect[i+4];
        mdl = &lbl_1_bss_1360->models[mdlNo[i]];
        if(eff->mode == 0) {
            eff->mode = 1;
            eff->timer[0] = 0;
            mdl->pos.x = 0.0f;
            mdl->pos.y = 0.0f;
            mdl->pos.z = 0.0f;
            mdl->rot.y = (i*30)-15;
            Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(mdl->modelId, i*25);
            Hu3DMotionSpeedSet(mdl->modelId, 0.5f);
            Hu3DModelPosSetV(mdl->modelId, &mdl->pos);
            Hu3DModelRotSetV(mdl->modelId, &mdl->rot);
            Hu3DModelAttrSet(mdl->modelId, HU3D_MOTATTR_LOOP);
        }
        eff->timer[0]++;
        mdl->rot.y -= 0.01;
    }
    mdl = lbl_1_bss_1360->models;
    mdl->rot.y -= 0.005f;
}

/* asm 1955-1962, 6 insns. [m550 M550Unk6D8C] */
#define DS_S_EFFECT9STOP
#include "REL/duelstage.h"

/* asm 1965-1967, 1 insn. */
void fn_1_7F80(void)
{
}

/* asm 1970-1991, 18 insns. Called from game.c. */
void fn_1_7F84(void)
{
    int i;

    for(i=0; i<2; i++) {
        lbl_1_bss_1360->effect[i+8].counter = -1;
    }
}

/* asm 1994-2560, 547 insns. Prop updater: the two circling models 90 and 91. */
void fn_1_7FCC(void)
{
    int mdlNo[2] = { 90, 91 };
    int i;
    M554_EFFECT *eff;
    M554_MODEL *mdl;

    for(i=0; i<2; i++) {
        eff = &lbl_1_bss_1360->effect[i+8];
        mdl = &lbl_1_bss_1360->models[mdlNo[i]];
        switch(eff->mode) {
            case 0:
                eff->mode = 1;
                eff->timer[0] = 0;
                eff->counter = 0;
                Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
                Hu3DMotionTimeSet(mdl->modelId, 0.0f);
                Hu3DMotionSpeedSet(mdl->modelId, 1.0f);
                Hu3DModelAttrSet(mdl->modelId, HU3D_MOTATTR_LOOP);
                eff->f2C = 70.0f-(0.3f*(rand8()%10));
                mdl->pos.y = 1352.0f;
                if(i == 0) {
                    eff->timer[0] = 570;
                    eff->f2C = 80.0f;
                } else {
                    eff->timer[0] = 200;
                    eff->f2C = -(0.3f*(rand8()%10));
                }
                eff->f34 = 1.1+(0.1*(rand8()%40));
                eff->f30 = 1770.0f;
                eff->f38 = eff->f30-270.0f;
                mdl->pos.x = eff->f30*sin((M_PI*eff->f2C)/180.0);
                mdl->pos.z = -600.0+(eff->f30*cos((M_PI*eff->f2C)/180.0));
                break;

            case 1:
                if(eff->timer[0]++ > 600) {
                    if(eff->counter == 0) {
                        eff->mode++;
                    }
                    eff->timer[0] = 48;
                }
                mdl->pos.y = 1352.0f;
                mdl->pos.x = eff->f30*sin((M_PI*eff->f2C)/180.0);
                mdl->pos.z = -600.0+(eff->f30*cos((M_PI*eff->f2C)/180.0));
                break;

            case 2:
                eff->timer[0]--;
                mdl->pos.y -= 24.0f;
                eff->f30 -= eff->f38/48.0f;
                eff->f2C -= eff->f34;
                mdl->pos.x = eff->f30*sin((M_PI*eff->f2C)/180.0);
                mdl->pos.z = -600.0+(eff->f30*cos((M_PI*eff->f2C)/180.0));
                mdl->rot.y -= 15.0f;
                if(eff->timer[0] == 0) {
                    eff->mode++;
                    HuAudFXPlay(2193);
                }
                break;

            case 3:
                eff->timer[0]++;
                if(mdl->pos.y >= 520.0f) {
                    mdl->pos.y += 23.0f;
                    eff->f2C -= 10.0;
                    eff->f30 += 15.2f;
                } else {
                    mdl->pos.y += 3.5;
                    eff->f2C -= 6.0;
                    eff->f30 += 1.3f;
                }
                mdl->pos.x = eff->f30*sin((M_PI*eff->f2C)/180.0);
                mdl->pos.z = -600.0+(eff->f30*cos((M_PI*eff->f2C)/180.0));
                mdl->rot.y -= 25.0f;
                if(eff->timer[0] >= 150) {
                    eff->timer[0] = rand8()-400;
                    if(eff->counter == 0) {
                        eff->mode = 1;
                    } else {
                        eff->mode = 4;
                    }
                    if(i != 0) {
                        eff->f2C = 0.5*(rand8()%40);
                    } else {
                        eff->f2C = 55.0+(0.5*(rand8()%35));
                    }
                    eff->f34 = 1.1+(0.1*(rand8()%40));
                    eff->f30 = 1570.0f;
                    eff->f30 += (rand8()%9)*50;
                    eff->f38 = eff->f30-270.0f;
                }
                break;
        }
    }
}
