/*
 * m550dll/stage.c -- the arena, the two duellists' models and motions, and
 * seven per-frame prop updaters.
 *
 * The functions every duel shares -- WorkInit, the two motion-table setters,
 * PadRead, CharMotionCreate, MotionExec and the effect-9 stop -- come from
 * REL/duelstage.h, included at the points the reference object has them. The
 * rest is m550's own. See NOTES.md beside this file.
 */

#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/frand.h"
#include "game/pad.h"

#include "datadir_enum.h"

#include "REL/m550dll/m550.h"

void M550MatAlphaSet(int mdlNo, float alpha);   /* m550.c, fn_1_984 */

#include "dolphin/os.h"

#include "math.h"
#include "humath.h"
#include "string.h"

/* --- forward declarations, asm address order --- */

void M550WorkInit(M550_WORK *work, M550_MODEL *models, unsigned int *dataTbl);
void M550StageModelCreate(s16 stageNo);
void M550CharMotDataSet(unsigned int *dataA, unsigned int *dataB);
void M550CharMotIdSet(HU3DMOTID *idA, HU3DMOTID *idB);
void M550CharModelCreate(void);
void M550PadRead(OMOBJ *obj);
void M550CharMotionCreate(void);
void M550StageMain(OMOBJ *obj);
static void M550Unk6600(void);
static void M550Unk6B6C(void);
void M550Unk6D8C(void);
static void M550Unk6DA4(void);
static void M550Unk719C(void);
void M550Unk7C00(void);
static void M550Unk7C4C(void);
void M550Unk7E94(void);
static void M550Unk7EE0(void);
void M550Unk8190(void);
static void M550Unk8350(void);

/* --- .data --- */

/* data_3D8 -- six scratch positions, zeroed. */
static HuVecF PosTbl[6] = {
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }
};

/* data_0 -- the two extra motions the last pair of models gets. */
static unsigned int SubDataTbl[2] = { DATANUM(DATA_m550, 0x3C), DATANUM(DATA_m550, 0x3D) };

static HU3DMOTID MotIdTbl[2] = { 0, 0 };        /* data_420 */

/* data_424 -- the seven prop updaters M550StageMain runs every frame. */
static void (*StageFuncTbl[7])(void) = {
    M550Unk6600,
    M550Unk6B6C,
    M550Unk6DA4,
    M550Unk719C,
    M550Unk7C4C,
    M550Unk7EE0,
    M550Unk8350
};

/* --- .bss --- */

static M550_WORK *StageWork;                         /* bss_1FC0 */

/* --- the duel stage framework (REL/duelstage.h) --- */

#define DS_WORK                 M550_WORK
#define DS_STAGEWORK            StageWork
#define DS_CHARMDL              2
#define DS_MOTIONEXEC_NUM       2
#define DS_CHARMOTION_NUM       5
#define DS_CHARMOTION_SPEEDCUR  1.0f
#define DS_FN_WorkInit          M550WorkInit
#define DS_FN_CharMotDataSet    M550CharMotDataSet
#define DS_FN_CharMotIdSet      M550CharMotIdSet
#define DS_FN_PadRead           M550PadRead
#define DS_FN_CharMotionCreate  M550CharMotionCreate
#define DS_FN_MotionExec        M550MotionExec
#define DS_FN_Effect9Stop       M550Unk6D8C
#define DS_EFFECT9STOP_IDX      9
#define DS_PROPTBL              StageFuncTbl
#define DS_PROPEXEC_NUM         7
#define DS_FN_PropExec          M550StageMain

/* ===== decoded functions, asm address order ===== */

/* fn_1_4E8C */
#define DS_S_WORKINIT
#include "REL/duelstage.h"

/*
 * fn_1_50D8 -- the arena. Six runs of models off StageWork->stageDataTbl, most of
 * them created once and linked for the repeats, and all of them parked with
 * DISPOFF for the prop updaters to bring in.
 *
 * The last run sets DISPOFF on models[179 + k*2 + j] BEFORE creating it, so
 * on the first pass through each pair it reads a model id that has not been
 * written yet. That is what the object does.
 */
void M550StageModelCreate(s16 stageNo)
{
    HU3DMODELID id;
    M550_MODEL *mdl;
    s16 no;
    s16 i;
    int j;
    int k;

    StageWork->stageNo = stageNo;
    for(i=0; i<2; i++) {
        no = (s16)i;
        id = StageWork->models[no].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(StageWork->stageDataTbl[i], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(id, 1);
        Hu3DModelPosSetV(id, &PosTbl[i]);
        Hu3DModelRotSet(id, 0.0f, -22.5f, 0.0f);
        StageWork->models[no].pos.x = PosTbl[i].x;
        StageWork->models[no].pos.y = PosTbl[i].y;
        StageWork->models[no].pos.z = PosTbl[i].z;
        StageWork->models[no].rot.x = 0.0f;
        StageWork->models[no].rot.y = 22.5f;
        StageWork->models[no].rot.z = 0.0f;
        Hu3DMotionTimeSet(id, 0.0f);
        Hu3DMotionSpeedSet(id, 0.25f);
        Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
        Hu3DModelLayerSet(id, 1);
        Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    }
    for(k=0; k<3; k++) {
        mdl = &StageWork->models[(k*3)+151];
        for(j=0; j<3; j++, mdl++) {
            if(j == 0) {
                id = mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(StageWork->stageDataTbl[k+47], HU_MEMNUM_OVL, HEAP_MODEL));
            } else {
                mdl->modelId = Hu3DModelLink(id);
            }
            Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(mdl->modelId, 50.0f);
            Hu3DMotionSpeedSet(mdl->modelId, 0.5f);
            Hu3DModelCameraSet(mdl->modelId, 1);
            Hu3DModelLayerSet(mdl->modelId, 1);
        }
    }
    for(k=0; k<2; k++) {
        mdl = &StageWork->models[k+161];
        mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(StageWork->stageDataTbl[k+51], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
        Hu3DMotionSpeedSet(mdl->modelId, 0.5f);
        Hu3DModelCameraSet(mdl->modelId, 1);
        Hu3DMotionTimeSet(mdl->modelId, 0.0f);
        Hu3DModelLayerSet(mdl->modelId, 7);
        mdl = &StageWork->models[(k*2)+163];
        for(j=0; j<2; j++, mdl++) {
            if(j == 0) {
                id = mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(StageWork->stageDataTbl[k+53], HU_MEMNUM_OVL, HEAP_MODEL));
            } else {
                mdl->modelId = Hu3DModelLink(id);
            }
            Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
            Hu3DMotionSpeedSet(mdl->modelId, 0.5f);
            Hu3DModelCameraSet(mdl->modelId, 1);
            Hu3DMotionTimeSet(mdl->modelId, 0.0f);
            Hu3DModelAttrSet(mdl->modelId, HU3D_MOTATTR_LOOP);
            Hu3DModelLayerSet(mdl->modelId, 3);
        }
    }
    for(k=0; k<3; k++) {
        int mdlNo[3] = { 160, 167, 168 };
        int dataNo[3] = { 50, 55, 56 };
        mdl = &StageWork->models[mdlNo[k]];
        mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(StageWork->stageDataTbl[dataNo[k]], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(mdl->modelId, 1);
        if(k < 2) {
            Hu3DModelLayerSet(mdl->modelId, 4);
        } else {
            Hu3DModelLayerSet(mdl->modelId, 1);
        }
    }
    for(k=0; k<10; k++) {
        mdl = &StageWork->models[k+169];
        if(k == 0) {
            id = mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(StageWork->stageDataTbl[57], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            mdl->modelId = Hu3DModelLink(id);
        }
        Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(mdl->modelId, 1);
        Hu3DModelLayerSet(mdl->modelId, 4);
    }
    for(k=0; k<2; k++) {
        mdl = &StageWork->models[(k*2)+179];
        for(j=0; j<2; j++, mdl++) {
            Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
            if(j == 0) {
                id = mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(StageWork->stageDataTbl[k+58], HU_MEMNUM_OVL, HEAP_MODEL));
                MotIdTbl[k] = Hu3DJointMotion(mdl->modelId, HuDataSelHeapReadNum(SubDataTbl[k], HU_MEMNUM_OVL, HEAP_MODEL));
                Hu3DModelScaleSet(mdl->modelId, 2.2f, 2.2f, 2.2f);
            } else {
                mdl->modelId = Hu3DModelLink(id);
                Hu3DModelScaleSet(mdl->modelId, 1.0f, 1.0f, 1.0f);
            }
            Hu3DMotionSet(mdl->modelId, MotIdTbl[k]);
            Hu3DMotionSpeedSet(mdl->modelId, 1.0f);
            Hu3DModelAttrSet(mdl->modelId, HU3D_MOTATTR_LOOP);
            Hu3DModelCameraSet(mdl->modelId, 1);
            Hu3DModelLayerSet(mdl->modelId, 1);
        }
    }
}

/* fn_1_58F4, fn_1_5918 */
#define DS_S_CHARMOT
#include "REL/duelstage.h"

/*
 * fn_1_593C -- the two duellists, dropped in from a thousand units up and
 * facing each other across 420 units.
 */
void M550CharModelCreate(void)
{
    int i;

    for(i=0; i<2; i++) {
        StageWork->models[2+i].modelId = CharModelCreate(StageWork->chr[i].charNo, 1);
        Hu3DModelPosSet(StageWork->models[2+i].modelId, (i*420)-210, 1000.0f, 0.0f);
        StageWork->models[i+2].pos.x = (i*420)-210;
        StageWork->models[i+2].pos.y = 1000.0f;
        StageWork->models[i+2].pos.z = 0.0f;
        StageWork->models[i+2].rot.x = 0.0f;
        StageWork->models[i+2].rot.y = 90.0f+(i*180);
        StageWork->models[i+2].rot.z = 0.0f;
        Hu3DModelAttrSet(StageWork->models[2+i].modelId, HU3D_MOTATTR_LOOP);
        Hu3DModelCameraSet(StageWork->models[2+i].modelId, 1);
        Hu3DModelLayerSet(StageWork->models[2+i].modelId, 4);
    }
}

/* fn_1_5BD8, fn_1_6094, fn_1_61E8 */
#define DS_S_PADREAD
#define DS_S_CHARMOTION
#define DS_S_MOTIONEXEC
#include "REL/duelstage.h"

/* fn_1_65AC -- the stage object: run all seven prop updaters, every frame. */
#define DS_S_PROPEXEC
#include "REL/duelstage.h"

/*
 * fn_1_6600 -- five props orbiting the arena at their own radius and height,
 * each bobbing on a sine. Three independent counters drive them: one advances
 * the orbit a thousandth of a degree every sixteen frames, one restarts the
 * motion every hundred, and one advances the bob a degree every four.
 */
static void M550Unk6600(void)
{
    int mdlNo[5] = { 151, 154, 157, 152, 158 };
    float angle[5] = { 152.0f, 191.0f, 207.0f, 176.0f, 170.0f };
    float radius[5] = { 5000.0f, 3200.0f, 5500.0f, 7000.0f, 6800.0f };
    float height[5] = { -800.0f, -900.0f, -800.0f, -300.0f, -400.0f };
    M550_EFFECT *eff;
    M550_MODEL *mdl;
    int i;
    int j;

    for(i=0; i<5; i++) {
        eff = &StageWork->effect[i];
        mdl = &StageWork->models[mdlNo[i]];
        if(eff->mode == 0) {
            eff->mode = 1;
            eff->timer[0] = 0;
            eff->timer[1] = 0;
            eff->timer[2] = 0;
            eff->f2C = angle[i];
            eff->f30 = radius[i];
            eff->f34 = i*45;
            eff->f38 = height[i];
            mdl->pos.x = eff->f30*sin((M_PI*eff->f2C)/180.0);
            mdl->pos.z = eff->f30*cos((M_PI*eff->f2C)/180.0);
            mdl->pos.y = (1000.0f-(i*200))+(200.0*sin((M_PI*eff->f34)/180.0));
            Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(mdl->modelId, 50.0f);
            Hu3DMotionSpeedSet(mdl->modelId, 0.5f);
            Hu3DModelPosSetV(mdl->modelId, &mdl->pos);
            if(i == 3) {
                Hu3DModelScaleSet(mdl->modelId, 0.75f, 0.75f, 0.75f);
            } else if(i == 4) {
                Hu3DModelScaleSet(mdl->modelId, 1.8f, 1.8f, 1.8f);
            } else {
                Hu3DModelScaleSet(mdl->modelId, 0.9f, 0.9f, 0.9f);
            }
        }
        for(j=0; j<3; j++) {
            eff->timer[j]++;
            switch(j) {
                case 0:
                    if(eff->timer[j] >= 16) {
                        eff->timer[j] = 0;
                        eff->f2C += 0.001;
                    }
                    break;

                case 1:
                    if(eff->timer[j] >= 100) {
                        eff->timer[j] = 0;
                        Hu3DMotionTimeSet(mdl->modelId, 50.0f);
                    }
                    break;

                case 2:
                    if(eff->timer[j] >= 4) {
                        eff->timer[j] = 0;
                        eff->f34 += 1.0f;
                    }
                    break;
            }
        }
        mdl->pos.x = eff->f30*sin((M_PI*eff->f2C)/180.0);
        mdl->pos.z = eff->f30*cos((M_PI*eff->f2C)/180.0);
        mdl->pos.y = (1000.0f+eff->f38)+(200.0*sin((M_PI*eff->f34)/180.0));
    }
}

/*
 * fn_1_6B6C -- four slowly turning props, each started once and then wound
 * back to 75 degrees whenever it passes -45. The first model in the table
 * turns with them, half as fast again.
 */
static void M550Unk6B6C(void)
{
    int mdlNo[4] = { 163, 165, 164, 166 };
    int i;
    M550_EFFECT *eff;
    M550_MODEL *mdl;

    for(i=0; i<4; i++) {
        eff = &StageWork->effect[i+5];
        mdl = &StageWork->models[mdlNo[i]];
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
        if(mdl->rot.y <= -45.0f) {
            mdl->rot.y = 75.0f;
        }
    }
    mdl = StageWork->models;
    mdl->rot.y -= 0.005f;
}

/* fn_1_6D8C -- parks the arena light below. */
#define DS_S_EFFECT9STOP
#include "REL/duelstage.h"

/*
 * fn_1_6DA4 -- the light over the arena. It rocks through two degrees on a
 * 360-frame cycle and flickers: sixteen frames dimming to 0.6, then a
 * randomised 64-123 frame hold at full, and every third and sixth time round
 * a six-frame drop instead. The alpha goes straight into the model's
 * materials through M550MatAlphaSet.
 */
static void M550Unk6DA4(void)
{
    int mdlNo[1] = { 167 };
    M550_EFFECT *eff = &StageWork->effect[9];
    M550_MODEL *mdl = &StageWork->models[mdlNo[0]];

    if(eff->timer[0] < -1) {
        return;
    }
    if(eff->timer[0] == -1) {
        Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
        eff->timer[0]--;
        return;
    }
    if(eff->mode == 0) {
        eff->mode = 1;
        eff->timer[0] = 0;
        eff->timer[1] = 0;
        eff->timer[2] = 0;
        eff->counter = 0;
        eff->subMode = 0;
        mdl->pos.x = -1100.0f;
        mdl->pos.y = 1850.0f;
        mdl->pos.z = -2800.0f;
        mdl->rot.x = 0.0f;
        mdl->rot.z = 0.0f;
        Hu3DModelPosSetV(mdl->modelId, &mdl->pos);
        Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
        Hu3DMotionTimeSet(mdl->modelId, 0.0f);
        Hu3DMotionSpeedSet(mdl->modelId, 1.0f);
        eff->f2C = 1.0f;
        M550MatAlphaSet(167, eff->f2C);
        return;
    }
    eff->timer[0] = (eff->timer[0]+1)%360;
    mdl->rot.z = 2.0*sin((M_PI*eff->timer[0])/180.0);
    switch(eff->subMode) {
        case 0:
            eff->timer[1]++;
            eff->f2C = 1.0-(0.4*sin((M_PI*((eff->timer[1]*90)/16))/180.0));
            M550MatAlphaSet(167, eff->f2C);
            if(eff->timer[1] == 16) {
                eff->timer[1] = 0;
                eff->timer[2] = (rand8()%60)+64;
                eff->subMode++;
            }
            break;

        case 1:
            if(eff->timer[1]++ >= eff->timer[2]) {
                M550MatAlphaSet(167, 1.0f);
                eff->counter = (eff->counter+1)%6;
                if(eff->counter == 1 || eff->counter == 4) {
                    eff->subMode = 0;
                } else {
                    eff->subMode++;
                }
                eff->timer[1] = 0;
            }
            break;

        case 2:
            if(eff->timer[1]++ >= 6) {
                M550MatAlphaSet(167, 0.6f);
                eff->subMode = 0;
                eff->timer[1] = 0;
            }
            break;
    }
}

/*
 * fn_1_719C -- five more orbiting props, and the one piece of real staging in
 * the file. Four of them just circle a fixed centre; the first swings round
 * the arena, and once it passes 180 degrees it hands over to an arc: the code
 * records where it was and what heading it had, then walks it round a
 * 600-unit circle at 1.5 degrees a frame for 240 frames before returning it to
 * the orbit at a tenth of its old speed. Ten trailing models follow it, one
 * released every fifteen frames from a ring buffer.
 */
static void M550Unk719C(void)
{
    int mdlNo[6] = { 168, 179, 181, 180, 182, 169 };
    float radius[5] = { 2900.0f, 700.0f, 700.0f, 300.0f, 300.0f };
    float angle[5] = { 90.0f, 180.0f, 0.0f, 90.0f, 270.0f };
    float speed[5] = { 0.3f, 0.5f, 0.5f, 0.5f, 0.5f };
    HuVecF pos[2] = { { 1000.0f, 1200.0f, -6600.0f }, { -550.0f, 550.0f, -3120.0f } };
    M550_EFFECT *eff;
    M550_MODEL *mdl;
    M550_MODEL *sub;
    int i;

    for(i=0; i<5; i++) {
        eff = &StageWork->effect[i+10];
        mdl = &StageWork->models[mdlNo[i]];
        if(eff->mode == 0) {
            eff->mode = 1;
            eff->timer[0] = 0;
            Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(mdl->modelId, 0.0f);
            if(i == 0) {
                Hu3DMotionSpeedSet(mdl->modelId, 4.0f);
            } else {
                Hu3DMotionSpeedSet(mdl->modelId, 1.0f);
            }
            Hu3DModelAttrSet(mdl->modelId, HU3D_MOTATTR_LOOP);
            eff->f2C = radius[i];
            eff->f30 = angle[i];
            eff->f34 = speed[i];
        }
        eff->f30 += eff->f34;
        if(i == 0) {
            if(eff->f30 > 270.0f) {
                eff->f30 = 0.0f;
                eff->doneF = 0;
            }
            if(eff->f30 > 0.0f && eff->f30 <= 90.0f) {
                eff->f30 -= (3.0f*eff->f34)*0.25f;
            }
        }
        if(eff->f34 >= 0.0f) {
            mdl->rot.y = 90.0f+eff->f30;
        } else {
            mdl->rot.y = 270.0f+eff->f30;
        }
        switch(i) {
            case 0:
                if(eff->subMode == 0) {
                    mdl->pos.x = eff->f2C*sin((M_PI*eff->f30)/180.0);
                    mdl->pos.z = eff->f2C*cos((M_PI*eff->f30)/180.0);
                    mdl->pos.y = 400.0+((5000.0*sin((M_PI*12.0)/180.0))*sin((M_PI*(180.0f+eff->f30))/180.0));
                    mdl->rot.x = 12.0*sin((M_PI*(90.0f+eff->f30))/180.0);
                    if(eff->doneF == 0 && eff->f30 > 180.0f) {
                        eff->subMode++;
                        eff->f3C = mdl->pos.x+(600.0*cos((M_PI*(90.0f+mdl->rot.x))/180.0));
                        eff->f40 = mdl->pos.y+(600.0*sin((M_PI*(90.0f+mdl->rot.x))/180.0));
                        eff->f44 = (90.0f+mdl->rot.x)-180.0f;
                        eff->counter = 0;
                        eff->f34 = 0.0f;
                        eff->doneF = 1;
                    }
                } else {
                    eff->f44 -= 1.5;
                    mdl->rot.x -= 1.5;
                    mdl->pos.x = eff->f3C+(600.0*cos((M_PI*eff->f44)/180.0));
                    mdl->pos.y = eff->f40+(600.0*sin((M_PI*eff->f44)/180.0));
                    if(eff->counter++ >= 239) {
                        eff->f34 = 0.3f;
                        eff->subMode = 0;
                    }
                }
                eff->timer[0]++;
                if(eff->timer[0] >= 15) {
                    eff->timer[0] = 0;
                    sub = &StageWork->models[mdlNo[5]+eff->timer[1]];
                    Hu3DModelAttrReset(sub->modelId, HU3D_ATTR_DISPOFF);
                    Hu3DMotionTimeSet(sub->modelId, 0.0f);
                    Hu3DMotionSpeedSet(sub->modelId, 1.0f);
                    if(eff->subMode == 0) {
                        sub->pos.x = eff->f2C*sin((M_PI*(eff->f30-eff->f34))/180.0);
                        sub->pos.z = eff->f2C*cos((M_PI*(eff->f30-eff->f34))/180.0);
                        sub->pos.y = 400.0+((5000.0*sin((M_PI*12.0)/180.0))*sin((M_PI*(180.0f+(eff->f30-eff->f34)))/180.0));
                    } else {
                        sub->pos.x = eff->f3C+(600.0*cos((M_PI*(1.5f+eff->f44))/180.0));
                        sub->pos.y = eff->f40+(600.0*sin((M_PI*(1.5f+eff->f44))/180.0));
                        sub->pos.z = mdl->pos.z;
                    }
                    Hu3DModelPosSetV(sub->modelId, &sub->pos);
                    eff->timer[1] = (eff->timer[1]+1)%10;
                }
                break;

            case 1:
            case 2:
                mdl->pos.x = pos[0].x+(eff->f2C*sin((M_PI*eff->f30)/180.0));
                mdl->pos.z = pos[0].z+(eff->f2C*cos((M_PI*eff->f30)/180.0));
                mdl->pos.y = pos[0].y;
                break;

            case 3:
            case 4:
                mdl->pos.x = pos[1].x+(eff->f2C*sin((M_PI*eff->f30)/180.0));
                mdl->pos.z = pos[1].z+(eff->f2C*cos((M_PI*eff->f30)/180.0));
                mdl->pos.y = pos[1].y;
                break;
        }
    }
}

/* fn_1_7C00 */
void M550Unk7C00(void)
{
    StageWork->effect[15].timer[0] = -1;
    Hu3DModelAttrSet(StageWork->models[161].modelId, HU3D_ATTR_DISPOFF);
}

/*
 * fn_1_7C4C -- one prop that crosses the sky. It waits 800 frames, appears at
 * the far left, drifts right at 5 a frame with its motion looping by hand from
 * frame 51, and once past 4000 waits a randomised 600-720 frames before coming
 * round again. M550Unk7C00 parks it by setting the timer to -1.
 */
static void M550Unk7C4C(void)
{
    int mdlNo[1] = { 161 };
    M550_EFFECT *prop = &StageWork->effect[15];
    M550_MODEL *mdl = &StageWork->models[161];

    if(prop->timer[0] < -1) {
        return;
    }
    if(prop->timer[0] == -1) {
        Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
        prop->timer[0]--;
    }
    if(prop->mode == 0) {
        if(prop->timer[0]++ > 800) {
            prop->mode = 1;
            prop->timer[0] = 0;
            Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(mdl->modelId, 50.0f);
            Hu3DMotionSpeedSet(mdl->modelId, 0.5f);
            Hu3DModelScaleSet(mdl->modelId, 2.0f, 2.0f, 2.0f);
            mdl->pos.x = -2000.0f;
            mdl->pos.z = 2000.0f;
            mdl->pos.y = 1200.0f;
            Hu3DModelPosSetV(mdl->modelId, &mdl->pos);
        }
    }
    if(prop->mode == 1) {
        prop->timer[0]++;
        if(prop->timer[0] >= 99) {
            Hu3DMotionTimeSet(mdl->modelId, 51.0f);
            prop->timer[0] = 0;
        }
        mdl->pos.x += 5.0f;
        if(mdl->pos.x > 4000.0f) {
            prop->mode = 2;
            prop->timer[0] = 0;
            prop->timer[1] = ((rand8()%5)*30)+600;
        }
    }
    if(prop->mode == 2) {
        if(prop->timer[0]++ >= prop->timer[1]) {
            mdl->pos.x = -2000.0f;
            prop->mode = 1;
        }
    }
}

/* fn_1_7E94 */
void M550Unk7E94(void)
{
    Hu3DModelAttrSet(StageWork->models[162].modelId, HU3D_ATTR_DISPOFF);
    StageWork->effect[16].mode = -1;
}

/*
 * fn_1_7EE0 -- the other prop, on a fixed 22.5-degree heading at 14.85 a
 * frame. It starts 13000 units out, crosses to z = 2000, then waits a
 * randomised 300-510 frames and comes back in at one of four x positions.
 * M550Unk7E94 parks it by setting the mode to -1.
 */
static void M550Unk7EE0(void)
{
    int mdlNo[1] = { 162 };
    M550_EFFECT *prop = &StageWork->effect[16];
    M550_MODEL *mdl = &StageWork->models[mdlNo[0]];

    if(prop->mode < 0) {
        return;
    }
    switch(prop->mode) {
        case 0:
            if(prop->timer[0]++ > 300) {
                prop->timer[0] = -200;
                prop->mode = 1;
                Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
                Hu3DMotionTimeSet(mdl->modelId, 0.0f);
                Hu3DMotionSpeedSet(mdl->modelId, 0.25f);
                mdl->pos.x = -4356.0f;
                mdl->pos.z = -13000.0f;
                mdl->pos.y = 0.0f;
                Hu3DModelPosSetV(mdl->modelId, &mdl->pos);
            }
            break;

        case 1:
            prop->timer[0]++;
            if(prop->timer[0] >= 200) {
                prop->timer[0] = 0;
                Hu3DMotionTimeSet(mdl->modelId, 51.0f);
            }
            mdl->pos.x += 14.85*sin((M_PI*22.5)/180.0);
            mdl->pos.z += 14.85*cos((M_PI*22.5)/180.0);
            if(mdl->pos.z >= 2000.0f) {
                prop->mode = 2;
                prop->timer[0] = 0;
                prop->timer[1] = ((rand8()%8)*30)+300;
            }
            break;

        case 2:
            if(prop->timer[0]++ >= prop->timer[1]) {
                prop->mode = 1;
                Hu3DMotionTimeSet(mdl->modelId, 0.0f);
                mdl->pos.x = ((rand8()%4)*500)-4356;
                mdl->pos.z = -13000.0f;
                prop->timer[0] = -200;
            }
            break;
    }
}

/*
 * fn_1_8190 -- put the four background props back where they start. Their
 * motions all resume from frame 50, which is where M550Unk8350 loops them.
 */
void M550Unk8190(void)
{
    HuVecF pos[4] = {
        { -700.0f, -1600.0f, 1100.0f },
        { 1100.0f, -1100.0f, -500.0f },
        { 800.0f, -2700.0f, 1200.0f },
        { -800.0f, -500.0f, -600.0f }
    };
    float scale[4] = { 1.0f, 1.2f, 0.7f, 1.5f };
    int mdlNo[4] = { 153, 155, 156, 159 };
    M550_MODEL *mdl;
    int i;

    for(i=0; i<4; i++) {
        mdl = &StageWork->models[mdlNo[i]];
        Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
        Hu3DMotionSpeedSet(mdl->modelId, 1.0f);
        Hu3DMotionTimeSet(mdl->modelId, 50.0f);
        mdl->pos.x = pos[i].x;
        mdl->pos.y = pos[i].y;
        mdl->pos.z = pos[i].z;
        Hu3DModelPosSetV(mdl->modelId, &mdl->pos);
        Hu3DModelScaleSet(mdl->modelId, scale[i], scale[i], scale[i]);
    }
}

/*
 * fn_1_8350 -- and loop them by hand: past frame 99 each one goes back to 50,
 * so the four props cycle over a 49-frame window rather than their whole
 * motion.
 */
static void M550Unk8350(void)
{
    int mdlNo[4] = { 153, 155, 156, 159 };
    int i;
    M550_MODEL *mdl;
    float time;

    for(i=0; i<4; i++) {
        mdl = &StageWork->models[mdlNo[i]];
        time = Hu3DMotionTimeGet(mdl->modelId);
        if(time >= 99.0f) {
            Hu3DMotionTimeSet(mdl->modelId, 50.0f);
        }
    }
}
