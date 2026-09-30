/*
 * m530dll m530.c (fork A) -- the seqman hooks of this 2VS2 minigame (#44), the
 * team scoreboard, the winner/coin payout, two positional-sound helpers, and
 * the REL/mgframe.h framework compiled in as m523dll/m569dll do. Functions are
 * in reference order; definition order decides inlining.
 *
 * map.txt renames each framework name to its reference label (fn_1_1CA0
 * MgObjManInit .. fn_1_4458 MgPlaneCrossGet; MgCameraMoveEntry, MgFlowSet and
 * MgFlowNext keep their names). m530Dll.h aliases the six framework functions
 * the other units call by address (fn_1_342C, 3FF4, 4164, 439C, 4414, 4458).
 */

#include "REL/m530Dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/flag.h"
#include "game/frand.h"
#include "game/gamemes.h"
#include "game/gamework.h"
#include "game/hsfex.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "game/mg/score.h"
#include "game/mg/seqman.h"
#include "datadir_enum.h"

#include "math.h"

/* --- .data --- */

/* the framework's OSReport strings (.data:0x0..0x6C) */
#define MGF_S_DATA
#include "REL/mgframe.h"

/*
 * 0x6C: the camera. fn_1_1DC reads the Hu3D camera back into it (pos/up/target,
 * fov/near/far) and derives angle/dist; it is never moved afterwards.
 */
MGF_CAMERAVIEW lbl_1_data_6C = {
    1, 1, 0.0f, 0.0f, 0.0f,
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f
};
/* 0xB4: Hu3DShadowPosSet target (position is the stage light's, up the camera's). */
HuVecF lbl_1_data_B4 = { 0.0f, 0.0f, 0.0f };
/* 0xC0: character motions (player.c's CharMotionCreate list; fn_1_FB0 indexes it by obj->work[1]). */
unsigned int lbl_1_data_C0[15] = { 0x008C0000, 0x008C0001, 0x008C0002, 0x008C0040, 0x008C0021, 0x008C0041, 0x00870058, 0x008C004A, 0x008C004B, 0x00870056, 0x00870057, 0x008C000E, 0x008C0006, 0x008C0007, 0x00000000 };
/* 0xFC: the two team scoreboards' screen positions, x/y pairs (fn_1_11DC). */
s32 lbl_1_data_FC[4] = { 70, 60, 502, 60 };
/* 0x10C */ MGSEQ_PARAM lbl_1_data_10C = { 30, 0, fn_1_1DC, fn_1_C00, NULL, fn_1_CE0, fn_1_D00, fn_1_DAC, fn_1_DDC, NULL, fn_1_F48 };
/* 0x134 */ char lbl_1_data_134[] = "light1";
/* 0x13B */ char lbl_1_data_13B[] = "planet";
/* 0x142 */ char lbl_1_data_142[] = "%d : %f\n";

/* --- .rodata tables --- */
/* stage models: 0 the stage (light1, planet shadow object), 1 the rotating backdrop, 2 shadow-mapped */
const s32 lbl_1_rodata_8C[3] = { DATANUM(DATA_m530, 0x00), DATANUM(DATA_m530, 0x03), DATANUM(DATA_m530, 0x04) };

/*
 * --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) ---
 *
 * The framework's three .bss objects are declared by hand, not through
 * MGF_S_BSS (as m564/m569): DebugCameraStart 0x6C, MgMusicId 0xB4, objman 0xB8.
 */
OMOBJMAN *objman;                   /* bss_B8 */
static s16 MgMusicId;               /* bss_B4 */
static MGF_CAMERAVIEW DebugCameraStart; /* bss_6C */
M530_TEAM lbl_1_bss_4C[2];          /* the two teams: players and score */
HU3DMODELID lbl_1_bss_44[4];        /* stage models (three used) */
OMOBJ **lbl_1_bss_40;               /* the four player objects (omGetGroupMemberListEx) */
s16 lbl_1_bss_3C;                   /* HuAudSStreamPlay id, -1 none */
float lbl_1_bss_34[2];              /* [0] backdrop z rotation (fn_1_16D8); dtk sizes it 8, [1] unreferenced */
HUSPRGRPID lbl_1_bss_30[2];         /* MgScoreWinCreate windows */
s16 lbl_1_bss_2C[2];                /* espEntry ids (team icons) */
MGSCORE *lbl_1_bss_24[2];           /* team score counters */
HUSPRGRPID lbl_1_bss_20[2];         /* the "x" sprite groups */
MGF_STAGELIGHT lbl_1_bss_4;         /* "light1" (Hu3DGLightParamGet) */
int lbl_1_bss_0;                    /* nonzero once a team won (fn_1_1768) */

/* --- the framework helpers the game code inlines, so defined first (as m523/m569) --- */
#define MGF_S_CAMERAMOVECHECK
#include "REL/mgframe.h"
#define MGF_S_OBJMAN
#include "REL/mgframe.h"

/*
 * MgPlayerConfSet's body, inlined into fn_1_1DC. The out-of-line
 * MgPlayerConfSet (fn_1_3E04) comes later in the object, so the retail source
 * carried its own copy here.
 */
static inline void fn_1_PlayerConfSet(M530_PLAYER *work, s16 no)
{
    work->no = no;
    work->charNo = GwPlayerConf[no].charNo;
    work->padNo = GwPlayerConf[no].padNo;
    work->grp = GwPlayerConf[no].grp;
    work->comF = GwPlayerConf[no].type;
    work->dif = GwPlayerConf[no].dif;
    work->mode = 0;
    work->pos.x = work->pos.y = work->pos.z = 0.0f;
    work->rot.x = work->rot.y = work->rot.z = 0.0f;
}

/* --- functions (reference order) --- */
/* ObjectSetup (32 insns): MgObjManInit inlined, then the sequence manager. */
void ObjectSetup(void)
{
    MgObjManInit();
    MgSeqCreate(&lbl_1_data_10C);
    MgSeqModeHookAdd(MGSEQ_MODE_PREMAIN, fn_1_C58);
    lbl_1_bss_3C = -1;
}

/*
 * fn_1_120 (47 insns; also inlined into fn_1_1DC): the 2VS2 teams. grp is
 * read as a 0..3 colour index: bit 0 is the slot in the team, grp / 2 the
 * team; grp is then overwritten with the team number. No fallback grouping.
 */
void fn_1_120(void)
{
    int i;
    M530_PLAYER *work;

    for (i = 0; i < 4; i++) {
        work = lbl_1_bss_40[i]->data;
        work->unk02C = work->grp & 1;
        lbl_1_bss_4C[work->grp / 2].unk000[work->unk02C] = i;
        work->grp = work->grp / 2;
    }
    lbl_1_bss_4C[0].unk008 = 0;
    lbl_1_bss_4C[1].unk008 = 0;
}

/* fn_1_1DC (649 insns) MGSEQ init hook: stage, camera, light, shadow, players, scoreboards. */
void fn_1_1DC(s16 mode, s16 frameNo)
{
    int i;
    int k;
    int j;
    HU3DLIGHTID lightId;
    float dz, dy, dx;
    float magSq;
    float angle;
    float ty, tx, tz;
    float mtx[4][4];
    OMOBJ *obj;
    M530_PLAYER *work;

    for (i = 0; i < 3; i++) {
        lbl_1_bss_44[i] = Hu3DModelCreateData(lbl_1_rodata_8C[i]);
        Hu3DModelLayerSet(lbl_1_bss_44[i], 0);
        Hu3DModelAttrSet(lbl_1_bss_44[i], HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(lbl_1_bss_44[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(lbl_1_bss_44[i], 0.0f, 0.0f, 0.0f);
        if (i == 0) {
            Hu3DModelAttrSet(lbl_1_bss_44[0], HU3D_MOTATTR_PAUSE);
        } else {
            Hu3DModelAttrSet(lbl_1_bss_44[i], HU3D_MOTATTR_LOOP);
        }
        Hu3DModelAttrReset(lbl_1_bss_44[i], HU3D_ATTR_DISPOFF);
    }
    Hu3DMotionCalc(lbl_1_bss_44[0]);
    PSMTXTrans(Hu3DData[lbl_1_bss_44[1]].mtx, 0.0f, 2000.0f, 0.0f);
    Hu3DModelPosSet(lbl_1_bss_44[1], 0.0f, -2000.0f, 0.0f);

    Hu3DCameraCreate(lbl_1_data_6C.no);
    Hu3DCameraViewportSet(lbl_1_data_6C.no, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DModelCameraInfoSet(lbl_1_bss_44[0], lbl_1_data_6C.no);
    Hu3DCameraPosGet(lbl_1_data_6C.no, &lbl_1_data_6C.pos, &lbl_1_data_6C.up, &lbl_1_data_6C.target);
    Hu3DCameraPerspectiveGet(lbl_1_data_6C.no, &lbl_1_data_6C.fov, &lbl_1_data_6C.near, &lbl_1_data_6C.far);
    dx = lbl_1_data_6C.pos.x - lbl_1_data_6C.target.x;
    dy = lbl_1_data_6C.pos.y - lbl_1_data_6C.target.y;
    dz = lbl_1_data_6C.pos.z - lbl_1_data_6C.target.z;
    magSq = (dz * dz) + ((dx * dx) + (dy * dy));
    lbl_1_data_6C.dist = sqrtf(magSq);
    angle = (atan2(dz, dx) / M_PI) * 180.0;
    lbl_1_data_6C.angle.y = -(angle - 90.0f);
    for (j = 0; j < 4; j++) {
        for (k = 0; k < 4; k++) {
            mtx[j][k] = 0.0f;
        }
    }
    mtx[0][0] = mtx[2][2] = cos(M_PI * -angle / 180.0);
    mtx[2][0] = -sin(M_PI * -angle / 180.0);
    mtx[0][2] = sin(M_PI * -angle / 180.0);
    mtx[1][1] = mtx[3][3] = 1.0f;
    tx = (dz * mtx[2][0]) + ((dx * mtx[0][0]) + (dy * mtx[1][0]));
    ty = (dz * mtx[2][1]) + ((dx * mtx[0][1]) + (dy * mtx[1][1]));
    tz = (dz * mtx[2][3]) + ((dx * mtx[0][3]) + (dy * mtx[1][3])); /* retail: column 3, not 2; tz is dead (m569 twin) */
    lbl_1_data_6C.angle.x = -((atan2(ty, tx) / M_PI) * 180.0);
    lbl_1_data_6C.angle.z = 0.0f;
    MgCameraViewSet(&lbl_1_data_6C);

    Hu3DModelLightInfoSet(lbl_1_bss_44[0], 1);
    lightId = Hu3DModelLightIdGet(lbl_1_bss_44[0], lbl_1_data_134);
    Hu3DGLightParamGet(lightId, &lbl_1_bss_4.pos, &lbl_1_bss_4.target, &lbl_1_bss_4.color);
    Hu3DShadowCreate(lbl_1_data_6C.fov, lbl_1_data_6C.near, lbl_1_data_6C.far);
    Hu3DShadowTPLvlSet(0.35f);
    Hu3DShadowPosSet(&lbl_1_bss_4.pos, &lbl_1_data_6C.up, &lbl_1_data_B4);
    Hu3DModelShadowMapObjSet(lbl_1_bss_44[0], lbl_1_data_13B);
    Hu3DModelShadowMapSet(lbl_1_bss_44[2]);

    omMakeGroupEx(objman, 0, 4);
    lbl_1_bss_40 = omGetGroupMemberListEx(objman, 0);
    for (i = 0; i < 4; i++) {
        obj = omAddObjEx(objman, 0x2000, 3, 14, 0, fn_1_F4C);
        lbl_1_bss_40[i] = obj;
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M530_PLAYER), HU_MEMNUM_OVL);
        work = obj->data;
        fn_1_PlayerConfSet(work, i);
        work->unk030 = 0;
        work->unk054 = -1;
    }
    CharEffectLayerSet(1);
    fn_1_120();
    fn_1_45A0();
    lbl_1_bss_34[0] = 0.0f;
    obj = omAddObjEx(objman, 0x2000, 0, 0, -1, fn_1_16D8);
    obj->work[0] = 0;
    fn_1_11DC();
    MgSeqModeNext();
}

/* fn_1_C00 (22 insns) MGSEQ fade-in hook: the stream once the wipe is done. */
void fn_1_C00(s16 mode, s16 frameNo)
{
    if (!WipeCheckEnd() && lbl_1_bss_3C == -1) {
        lbl_1_bss_3C = HuAudSStreamPlay(0x4D);
    }
}

/* fn_1_C58 (34 insns) MGSEQ_MODE_PREMAIN hook added by ObjectSetup. */
void fn_1_C58(s16 mode, s16 frameNo)
{
    int i;
    M530_PLAYER *work;

    Hu3DModelAttrReset(lbl_1_bss_44[0], HU3D_MOTATTR_PAUSE);
    fn_1_1524();
    for (i = 0; i < 4; i++) {
        work = lbl_1_bss_40[i]->data;
        if (work->unk054 != -1) {
            espDispOn(work->unk054);
        }
    }
}

/* fn_1_CE0 (8 insns) MGSEQ main hook. */
void fn_1_CE0(s16 mode, s16 frameNo)
{
    fn_1_6740();
}

/* fn_1_D00 (43 insns) MGSEQ finish hook: stream fade, player icons off, winners. */
void fn_1_D00(s16 mode, s16 frameNo)
{
    int i;
    M530_PLAYER *work;

    if (frameNo == 0) {
        if (lbl_1_bss_3C != -1) {
            HuAudSStreamFadeOut(lbl_1_bss_3C, 100);
        }
        fn_1_69B4();
        for (i = 0; i < 4; i++) {
            work = lbl_1_bss_40[i]->data;
            if (work->unk054 != -1) {
                espKill(work->unk054);
            }
        }
        fn_1_1768();
    }
}

/* fn_1_DAC (12 insns) MGSEQ pre-winner hook. */
void fn_1_DAC(s16 mode, s16 frameNo)
{
    if (frameNo == 120) {
        MgSeqModeNext();
    }
}

/* fn_1_DDC (91 insns) MGSEQ winner hook: win/lose motions; the lose voice when nobody won. */
void fn_1_DDC(s16 mode, s16 frameNo)
{
    int i;
    M530_PLAYER *work;
    OMOBJ *obj;

    if (frameNo == 0) {
        for (i = 0; i < 4; i++) {
            work = lbl_1_bss_40[i]->data;
            CharModelAttrReset(work->charNo, HU3D_MOTATTR_LOOP);
            CharModelAttrReset(work->charNo, HU3D_MOTATTR_PAUSE);
            if (work->unk030 != 0) {
                CharMotionSet(work->charNo, lbl_1_bss_40[i]->mtnId[12]);
            } else {
                CharMotionSet(work->charNo, lbl_1_bss_40[i]->mtnId[13]);
                if (lbl_1_bss_0 == 0) {
                    obj = omAddObjEx(objman, 0x2000, 0, 0, -1, fn_1_FB0);
                    obj->work[0] = work->no;
                    obj->work[1] = 13;
                }
            }
        }
    }
    if (lbl_1_bss_0 != 0) {
        if (frameNo == 0) {
            HuAudFXPlay(0x7A1);
        }
        fn_1_6868();
    }
}

/* fn_1_F48 (1 insn) MGSEQ close hook. */
void fn_1_F48(s16 mode, s16 frameNo)
{
}

/* fn_1_F4C (25 insns): the player object; slot 0 and slot 1 run different mains. */
void fn_1_F4C(OMOBJ *obj)
{
    M530_PLAYER *work = obj->data;

    switch (work->unk02C) {
        case 0:
            fn_1_6D7C(obj);
            break;
        case 1:
            fn_1_8434(obj);
            break;
    }
}

/*
 * fn_1_FB0 (78 insns): waits for the lose motion's extra time, then plays the
 * character voice 0x200 panned to the player and deletes itself.
 * work[0] player number, work[1] lbl_1_data_C0 row.
 */
void fn_1_FB0(OMOBJ *obj)
{
    M530_PLAYER *work;
    s16 time;
    s16 seNo;
    HU3DMODELID mdlId;
    s16 vol;
    s16 pan;

    work = lbl_1_bss_40[obj->work[0]]->data;
    seNo = 0x200;
    time = CharMotionExtraTimeGet(work->charNo, lbl_1_data_C0[obj->work[1]]);
    mdlId = lbl_1_bss_40[obj->work[0]]->mdlId[0];
    OSReport(lbl_1_data_142, work->no, Hu3DMotionTimeGet(mdlId));
    if (Hu3DMotionTimeGet(mdlId) >= time && Hu3DMotionShiftIDGet(mdlId) < 0) {
        fn_1_1A50(&work->pos, &vol, &pan);
        CharFXPlayVolPan(work->charNo, seNo, vol, pan);
        omDelObjEx(objman, obj);
    }
}

/* fn_1_10E8 (61 insns): shift a player to motion motNo (obj->mtnId row); 3/4/5 set unk074. */
void fn_1_10E8(OMOBJ *obj, s32 motNo)
{
    M530_PLAYER *work;
    s16 charNo;
    float start;
    float end;
    u32 attr;

    work = obj->data;
    charNo = work->charNo;
    start = 0.0f;
    end = 10.0f;
    attr = HU3D_MOTATTR_LOOP;
    switch (motNo) {
        case 6:
        case 8:
            attr = 0;
            break;
        case 3:
            work->unk074 = 0;
            break;
        case 4:
            work->unk074 = 1;
            break;
        case 5:
            work->unk074 = 2;
            break;
    }
    CharMotionShiftSet(charNo, obj->mtnId[motNo], start, end, attr);
}

/* fn_1_11DC (210 insns): the two team scoreboards (window, counter, "x", team icon). */
void fn_1_11DC(void)
{
    int i;
    MGSCORE *score;
    HUSPRID sprId;
    ANIMDATA *anim;
    float x;
    float y;

    for (i = 0; i < 2; i++) {
        x = lbl_1_data_FC[i * 2];
        y = lbl_1_data_FC[i * 2 + 1];
        lbl_1_bss_30[i] = MgScoreWinCreate(112, 40);
        MgScoreWinPosSet(lbl_1_bss_30[i], x, y);
        MgScoreWinDispSet(lbl_1_bss_30[i], FALSE);
        score = MgScoreCreate(0x960031, -1, TRUE);
        MgScoreColorSet(score, 255, 216, 21);
        MgScoreMaxDigitSet(score, 2);
        MgScoreValueSet(score, 0);
        MgScorePosSet(score, 14.0f + x, y);
        MgScoreDispOff(score);
        lbl_1_bss_24[i] = score;
        anim = score->digitAnim; /* retail dead store */
        score = MgScoreCreate(0x960030, -1, TRUE); /* retail: never killed (fn_1_15C8 kills only bss_24) */
        anim = score->digitAnim;
        MgScoreDispOff(score);
        sprId = HuSprCreate(anim, 16, 15);
        lbl_1_bss_20[i] = HuSprGrpCreate(1);
        HuSprGrpMemberSet(lbl_1_bss_20[i], 0, sprId);
        HuSprAttrSet(lbl_1_bss_20[i], 0, HUSPR_ATTR_DISPOFF);
        HuSprColorSet(lbl_1_bss_20[i], 0, 255, 255, 255);
        HuSprPosSet(lbl_1_bss_20[i], 0, -8.0f + x, y);
        sprId = espEntry(DATANUM(DATA_m530, 0x0F), 16, 0);
        espDrawNoSet(sprId, 0);
        espPosSet(sprId, -32.0f + x, y);
        espDispOff(sprId);
        lbl_1_bss_2C[i] = sprId;
    }
    MgScoreWinColorSet(lbl_1_bss_30[0], 250, 0, 30);
    MgScoreWinColorSet(lbl_1_bss_30[1], 0, 50, 250);
}

/* fn_1_1524 (41 insns): show the scoreboards. */
void fn_1_1524(void)
{
    int i;

    for (i = 0; i < 2; i++) {
        MgScoreWinDispSet(lbl_1_bss_30[i], TRUE);
        espDispOn(lbl_1_bss_2C[i]);
        HuSprAttrReset(lbl_1_bss_20[i], 0, HUSPR_ATTR_DISPOFF);
        MgScoreDispOn(lbl_1_bss_24[i]);
    }
}

/* fn_1_15C8 (32 insns): kill the scoreboards. */
void fn_1_15C8(void)
{
    int i;

    for (i = 0; i < 2; i++) {
        espKill(lbl_1_bss_2C[i]);
        HuSprGrpKill(lbl_1_bss_20[i]);
        MgScoreKill(lbl_1_bss_24[i]);
    }
}

/* fn_1_1648 (36 insns, called from effect.c): show a team's score, clamped to 99. */
void fn_1_1648(s32 team)
{
    if (lbl_1_bss_4C[team].unk008 <= 99) {
        MgScoreValueSet(lbl_1_bss_24[team], lbl_1_bss_4C[team].unk008);
    } else {
        MgScoreValueSet(lbl_1_bss_24[team], 99);
    }
}

/* fn_1_16D8 (36 insns): the backdrop's spin object. */
void fn_1_16D8(OMOBJ *obj)
{
    obj->work[0]++;
    lbl_1_bss_34[0] -= 0.09615385f;
    Hu3DModelRotSet(lbl_1_bss_44[1], 0.0f, 0.0f, lbl_1_bss_34[0]);
}

/*
 * fn_1_1768 (186 insns, from the finish hook): the higher team score wins;
 * both its players get unk030 = 1, MgSeqWinnerSet and mgCoinBonus 10 unless
 * practice. A tie pays nothing.
 */
void fn_1_1768(void)
{
    int i;
    s16 no;
    M530_PLAYER *work;
    s16 charNo[4];

    for (i = 0; i < 4; i++) {
        charNo[i] = CHARNO_NONE;
    }
    if (lbl_1_bss_4C[0].unk008 > lbl_1_bss_4C[1].unk008) {
        no = lbl_1_bss_4C[0].unk000[0];
        work = lbl_1_bss_40[no]->data;
        work->unk030 = 1;
        charNo[no] = work->charNo;
        GWMgCoinBonusSet(no, 10);
        no = lbl_1_bss_4C[0].unk000[1];
        work = lbl_1_bss_40[no]->data;
        work->unk030 = 1;
        charNo[no] = work->charNo;
        GWMgCoinBonusSet(no, 10);
    } else if (lbl_1_bss_4C[0].unk008 < lbl_1_bss_4C[1].unk008) {
        no = lbl_1_bss_4C[1].unk000[0];
        work = lbl_1_bss_40[no]->data;
        work->unk030 = 1;
        charNo[no] = work->charNo;
        GWMgCoinBonusSet(no, 10);
        no = lbl_1_bss_4C[1].unk000[1];
        work = lbl_1_bss_40[no]->data;
        work->unk030 = 1;
        charNo[no] = work->charNo;
        GWMgCoinBonusSet(no, 10);
    }
    MgSeqWinnerSet(charNo[0], charNo[1], charNo[2], charNo[3]);
    lbl_1_bss_0 = 0;
    for (i = 0; i < 4; i++) {
        work = lbl_1_bss_40[i]->data;
        if (work->unk030 != 0) {
            lbl_1_bss_0 = 1;
        }
    }
}


/*
 * fn_1_1A50 (74 insns, called from player/effect): volume and pan for a world
 * position. pan = 32 + 64 * screen.x / 576, vol = 96 + 31 * 2 * (550 + z) / 550,
 * vol capped at 127 only. RETAIL HAZARD: neither is floored and pan is not
 * capped (see OUT.txt).
 */
void fn_1_1A50(HuVecF *pos, s16 *vol, s16 *pan)
{
    HuVecF screen;
    float z;

    Hu3D3Dto2D(pos, (s16)lbl_1_data_6C.no, &screen);
    *pan = 32.0f + 64.0f * (screen.x / 576.0f);
    z = 550.0f + pos->z;
    *vol = 96.0f + 31.0f * (2.0f * (z / 550.0f));
    if (*vol > 127) {
        *vol = 127;
    }
}

/* fn_1_1B78 (74 insns, called from player/effect/kinomi): fn_1_1A50's formula, then HuAudFXPlayVolPan. */
s32 fn_1_1B78(HuVecF *pos, s16 seNo)
{
    HuVecF screen;
    float z;
    s16 pan;
    s16 vol;

    Hu3D3Dto2D(pos, (s16)lbl_1_data_6C.no, &screen);
    pan = 32.0f + 64.0f * (screen.x / 576.0f);
    z = 550.0f + pos->z;
    vol = 96.0f + 31.0f * (2.0f * (z / 550.0f));
    if (vol > 127) {
        vol = 127;
    }
    return HuAudFXPlayVolPan(seNo, vol, pan);
}

/*
 * ===========================================================================
 * The framework, from REL/mgframe.h, in m523dll's include order.
 * ===========================================================================
 */
#define MGF_S_CAMERA
#include "REL/mgframe.h"

#define MGF_S_PAD
#include "REL/mgframe.h"

#define MGF_S_FLOWMAIN
#include "REL/mgframe.h"

#define MGF_S_FLOWENTRY
#include "REL/mgframe.h"
#define MGF_S_FLOWCTL
#include "REL/mgframe.h"

#define MGF_S_FLOWSTEP
#include "REL/mgframe.h"

#define MGF_S_PLAYERCONF
#include "REL/mgframe.h"

#define MGF_S_MATH
#include "REL/mgframe.h"
