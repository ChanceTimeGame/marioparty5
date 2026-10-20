/*
 * m570dll's player half. COMPLETE: 22 of its 24 functions are exact against
 * the original object and the file is +2 instructions net.
 *
 * The two that differ are the same difference twice, and it is deliberate:
 * M570CrowdCreate and M570CrowdIdleSet each pass Hu3DMotionMaxTimeGet's
 * result to frandmod, and the original emits no float-to-int conversion at
 * all -- see the note on M570CrowdIdleSet. One other cosmetic difference has
 * no size: M570PlayerMain's CharModelVoicePanSet argument is sign-extended
 * here because charman.h declares the pan s16, where the original passed it
 * straight through.
 *
 * The second of the overlay's two translation units, exactly as upstream's
 * configure.py declares them. Nothing here is shared with m524dll; the whole
 * file is this minigame's own.
 *
 * Four players, one of whom is on their own: M570PlayerCreate splits them by
 * GwPlayerConf grp into SoloPlayer and ChaserObj[3], and the side number it
 * assigns indexes every per-player table below.
 *
 * HOW TO WORK ON IT:
 *   ./games/mp5/gen_asm.sh m570Dll
 *   ./games/mp5/verify_obj.sh m570Dll REL/m570Dll/player
 *
 * Compare per function rather than trusting the headline number -- see
 * NOTES.md. Line ranges below are into
 * build/mp5-asm/m570Dll/asm/REL/m570Dll/player.s.
 */

#include "REL/m570Dll/m570.h"

#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/memory.h"
#include "game/audio.h"
#include "game/frand.h"
#include "game/pad.h"

#include "datadir_enum.h"
#include "datanum/charmot.h"
#include "datanum/char.h"

#include "game/hsfformat.h"

#include "math.h"

typedef struct M570Motion_s {
    float shiftTime;
    u32 attr;
    int resetLockF;
} M570_MOTION;

/*
 * Forty of these ring the stage -- one per position in EdgePosTbl. They are
 * the crowd: M570CrowdReactSet sets them all going with a random stagger.
 */
typedef struct M570Crowd_s {
    /* 0x00 */ s16 no;
    /* 0x02 */ s16 pad02;
    /* 0x04 */ OMOBJ *obj;
    /* 0x08 */ int delay;
    /* 0x0C */ int reactNum;
    /* 0x10 */ int mode;
} M570_CROWD;

static void M570PlayerInit(OMOBJ *obj);
static void M570CrowdCheerSet(void);
static void M570PlayerInput(M570_PLAYER *player);
static BOOL M570PlayerHandSameCheck(M570_PLAYER *player);
static void M570PlayerParManCreate(M570_PLAYER *player);
static void M570PlayerPropSet(M570_PLAYER *player);
static void M570StageMain(OMOBJ *obj);
static void M570CrowdMain(OMOBJ *obj);
static void M570CrowdFinishSet(void);
static void M570PlayerMain(OMOBJ *obj);

/* --- .data --- */

/* Ten motions plus the terminator CharModelMotListCreate stops on. */
static unsigned int PlayerMotDataTbl[] = {
    CHARMOT_HSF_c000m1_300,
    CHARMOT_HSF_c000m1_301,
    CHARMOT_HSF_c000m1_302,
    DATANUM(DATA_mario, 0xCA),
    CHARMOT_HSF_c000m1_431,
    DATANUM(DATA_mario, 0xBF),
    CHARMOT_HSF_c000m1_315,
    CHARMOT_HSF_c000m1_381,
    CHARMOT_HSF_c000m1_306,
    CHARMOT_HSF_c000m1_307,
    0
};

/* One row per motion above: blend time, the attribute to set, and a flag. */
static M570_MOTION MotionTbl[10] = {
    { 10.0f, HU3D_MOTATTR_LOOP, 0 },
    { 10.0f, HU3D_MOTATTR_LOOP, 0 },
    { 10.0f, HU3D_MOTATTR_LOOP, 0 },
    { 10.0f, HU3D_MOTATTR_LOOP, 1 },
    { 10.0f, HU3D_MOTATTR_LOOP, 1 },
    { 10.0f, HU3D_MOTATTR_LOOP, 1 },
    { 10.0f, HU3D_MOTATTR_NONE, 0 },
    { 10.0f, HU3D_MOTATTR_LOOP, 0 },
    { 10.0f, HU3D_MOTATTR_NONE, 0 },
    { 10.0f, HU3D_MOTATTR_NONE, 0 }
};

/* Indexed by side number: the solo player faces the other way. */
static HuVecF PlayerRotTbl[4] = {
    { 0.0f,  90.0f, 0.0f },
    { 0.0f, -90.0f, 0.0f },
    { 0.0f, -90.0f, 0.0f },
    { 0.0f, -90.0f, 0.0f }
};

static HuVecF PlayerPosTbl[4] = {
    { -300.0f, 0.0f,   50.0f },
    {  220.0f, 0.0f, -100.0f },
    {  280.0f, 0.0f,   50.0f },
    {  340.0f, 0.0f,  200.0f }
};

static HuVecF PlayerPosTbl2[4] = {
    { -200.0f, 0.0f,   50.0f },
    {  150.0f, 0.0f, -100.0f },
    {  175.0f, 0.0f,   50.0f },
    {  200.0f, 0.0f,  200.0f }
};

static HuVecF PlayerPosTbl3[4] = {
    {    0.0f, 0.0f, 300.0f },
    { -200.0f, 0.0f, 300.0f },
    {    0.0f, 0.0f, 300.0f },
    {  200.0f, 0.0f, 300.0f }
};

/* Three props per player, hidden until they are wanted. */
static int SubMdlDataTbl[3] = {
    DATANUM(DATA_m570, 0x0B), DATANUM(DATA_m570, 0x0C), DATANUM(DATA_m570, 0x0D)
};

static char StageHookName[] = "itemhook_R";   /* .data:0x6D0 */

/* The three hands, and the button that picks each. */
static u16 ButtonTbl[4] = { PAD_BUTTON_A, PAD_BUTTON_B, PAD_BUTTON_X, 0 };

/*
 * .data:0x4C8 -- forty positions at y = -50, laid out around the edge of the
 * stage in four runs. Not yet wired up to a caller.
 */
static HuVecF EdgePosTbl[40] = {
    { -350.0f, -50.0f, -600.0f }, { -250.0f, -50.0f, -600.0f }, { -150.0f, -50.0f, -600.0f },
    {  350.0f, -50.0f, -600.0f }, {  250.0f, -50.0f, -600.0f }, {  150.0f, -50.0f, -600.0f },
    { -450.0f, -50.0f, -700.0f }, { -350.0f, -50.0f, -700.0f }, { -250.0f, -50.0f, -700.0f },
    { -150.0f, -50.0f, -700.0f }, {  450.0f, -50.0f, -700.0f }, {  350.0f, -50.0f, -700.0f },
    {  250.0f, -50.0f, -700.0f }, {  150.0f, -50.0f, -700.0f }, { -600.0f, -50.0f, -450.0f },
    { -600.0f, -50.0f, -325.0f }, { -600.0f, -50.0f, -200.0f }, { -600.0f, -50.0f,  -75.0f },
    { -600.0f, -50.0f,   50.0f }, { -600.0f, -50.0f,  175.0f }, { -600.0f, -50.0f,  300.0f },
    { -600.0f, -50.0f,  425.0f }, { -775.0f, -50.0f, -525.0f }, { -775.0f, -50.0f, -325.0f },
    { -800.0f, -50.0f, -225.0f }, { -925.0f, -50.0f, -350.0f }, { -925.0f, -50.0f, -150.0f },
    {  600.0f, -50.0f, -450.0f }, {  600.0f, -50.0f, -325.0f }, {  600.0f, -50.0f, -200.0f },
    {  600.0f, -50.0f,  -75.0f }, {  600.0f, -50.0f,   50.0f }, {  600.0f, -50.0f,  175.0f },
    {  600.0f, -50.0f,  300.0f }, {  600.0f, -50.0f,  425.0f }, {  750.0f, -50.0f, -650.0f },
    {  750.0f, -50.0f, -450.0f }, {  750.0f, -50.0f, -175.0f }, {  925.0f, -50.0f, -275.0f },
    {  900.0f, -50.0f, -475.0f }
};

/* --- .rodata --- */

/* The stage host's four joint motions. */
static int StageMotDataTbl[4] = {
    DATANUM(DATA_m570, 0x0F), DATANUM(DATA_m570, 0x10),
    DATANUM(DATA_m570, 0x11), DATANUM(DATA_m570, 0x12)
};

/* The crowd's two joint motions. */
static int CrowdMotDataTbl[2] = {
    DATANUM(DATA_m570, 0x15), DATANUM(DATA_m570, 0x16)
};

/* --- .bss --- */

static M570_CROWD *CrowdObj[40]; /* bss_110 */
static OMOBJ *StageObj;        /* bss_1B0 */
M570_PLAYER *ChaserObj[3];     /* bss_1B4 */
M570_PLAYER *SoloPlayer;       /* bss_1C0 */
M570_PLAYER *PlayerObj[4];     /* bss_1C4 */

/*
 * fn_1_4210  asm    9- 156  146 insns -- build the four players.
 *
 * grp 0 is the odd one out, so it becomes SoloPlayer with side number 0 and
 * the other three become ChaserObj[0..2] with side numbers 1..3. Everything
 * per-player is indexed by that side number, not by the player number.
 */
void M570PlayerCreate(void)
{
    OMOBJ *obj;
    M570_PLAYER *work;
    HU3DMODELID modelId;
    int chaserNo;
    int i;
    int j;

    chaserNo = 0;
    for(i=0; i<4; i++) {
        obj = omAddObjEx(objman, (s16)(i+0x1000), 4, 10, OM_GRP_NONE, M570PlayerInit);
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M570_PLAYER), HU_MEMNUM_OVL);
        memset(obj->data, 0, sizeof(M570_PLAYER));
        work = obj->data;
        work->obj = obj;
        MgPlayerConfSet((MGFPLAYER *)work, (s16)i);
        if(work->grp == 0) {
            work->sideNo = 0;
            SoloPlayer = work;
        } else {
            work->sideNo = chaserNo+1;
            ChaserObj[chaserNo++] = work;
        }
        PlayerObj[i] = work;
        work->pos = PlayerPosTbl[work->sideNo];
        work->rot = PlayerRotTbl[work->sideNo];
        work->mode = 0;
        work->caughtF = 0;
        work->motNo = -1;
        modelId = CharModelMotListCreate(work->charNo, 2, PlayerMotDataTbl, obj->mtnId);
        obj->mdlId[0] = modelId;
        CharMotionSet(work->charNo, obj->mtnId[0]);
        Hu3DModelLayerSet(modelId, 2);
        Hu3DModelShadowSet(modelId);
        M570PlayerMotionSet(work, 0);
        for(j=0; j<3; j++) {
            obj->mdlId[j+1] = modelId = Hu3DModelCreateData(SubMdlDataTbl[j]);
            Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
        }
    }
    CharEffectLayerSet(3);
}

/* fn_1_457C  asm  247- 274   26 insns -- first frame: place, then hand over. */
static void M570PlayerInit(OMOBJ *obj)
{
    M570_PLAYER *work = obj->data;
    obj->objFunc = M570PlayerMain;
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
}

/*
 * fn_1_4440  asm  159- 244   84 insns -- change a player's motion.
 *
 * The 5 -> 4 transition starts 75 frames in rather than at 0, which is what
 * makes the caught animation continue out of the chase rather than restart.
 */
void M570PlayerMotionSet(M570_PLAYER *player, s16 motNo)
{
    OMOBJ *obj;
    float start;

    if(player->motNo == motNo) {
        return;
    }
    obj = player->obj;
    if(player->motNo == 5 && motNo == 4) {
        start = 75.0f;
    } else {
        start = 0.0f;
    }
    CharMotionShiftSet(player->charNo, obj->mtnId[motNo], start,
                       MotionTbl[motNo].shiftTime, MotionTbl[motNo].attr);
    if(MotionTbl[motNo].resetLockF) {
        Hu3DMotionAttrSet(obj->mtnId[motNo], HU3D_ATTR_MOT_RESET_LOCK);
    } else {
        Hu3DMotionAttrReset(obj->mtnId[motNo], HU3D_ATTR_MOT_RESET_LOCK);
    }
    player->motNo = motNo;
}

/*
 * fn_1_45E4  asm  277- 619  341 insns -- every player, every frame.
 *
 * The voice pan is recomputed from the world position each frame, so a
 * player's grunts follow them across the stage. The rest is a ten-way state
 * machine; modes 0, 3 and 6 are holds with nothing to do.
 */
static void M570PlayerMain(OMOBJ *obj)
{
    M570_PLAYER *work = obj->data;
    HuVecF rot;

    CharModelVoicePanSet(work->charNo, M570PanGet(&work->pos));
    switch(work->mode) {
        case 7:
            if(MgVecApproach(&work->pos, &work->targetPos, &rot, 5.0f)) {
                work->mode = 0;
                M570PlayerMotionSet(work, 0);
            }
            break;

        case 8:
            if(MgVecApproach(&work->pos, &work->targetPos, &work->rot, 10.0f)) {
                work->mode = 9;
            }
            break;

        case 9:
            work->rot.y = MgAngleApproach(work->rot.y, 0.0f, 10.0f);
            if(work->rot.y <= 0.1f) {
                M570PlayerMotionSet(work, 0);
                work->mode = 0;
            }
            break;

        case 1:
            M570PlayerInput(work);
            break;

        case 2:
            if(work->unk44++ == 15) {
                M570PlayerPropSet(work);
            }
            if(work->unk44 == 20) {
                M570PlayerParManCreate(work);
                work->mode = 0;
            }
            break;

        case 4:
            work->unk44++;
            if(work->unk44 == 20) {
                M570PlayerMotionSet(work, 4);
                work->unk44 = 0;
                work->mode = 0;
            }
            break;

        case 5:
            if(work->unk44 == 0) {
                omVibrate(work->no, 30, 12, 0);
                M570SePlay(&work->pos, 0x913);
            }
            if(work->grp == 0) {
                work->pos.x -= 3.0f;
            } else {
                work->pos.x += 3.0f;
            }
            if(work->unk44++ == 35) {
                work->caughtF = 1;
                M570PlayerMotionSet(work, 7);
                work->mode = 6;
            }
            break;
    }
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
}

/*
 * fn_1_5538  asm 1379-1405   25 insns -- have all three chasers finished?
 * This is what ends the minigame early: m570.c's main hook asks every round.
 */
BOOL M570PlayerCaughtCheck(void)
{
    int i;
    for(i=0; i<3; i++) {
        if(ChaserObj[i]->caughtF == 0) {
            return FALSE;
        }
    }
    return TRUE;
}

/*
 * fn_1_58EC  asm 1642-1748  105 insns -- one member of the crowd.
 *
 * Mode 1 waits out the random stagger and starts the reaction; mode 2 plays
 * it reactNum times, stepping the count each time the motion reaches its last
 * frame; 3 and 4 are the two ways back to idle.
 */
static void M570CrowdMain(OMOBJ *obj)
{
    M570_CROWD *work = obj->data;
    HU3DMODELID modelId = obj->mdlId[0];

    switch(work->mode) {
        case 0:
            break;

        case 1:
            work->delay--;
            if(work->delay > 0) {
                break;
            }
            Hu3DMotionSet(modelId, obj->mtnId[1]);
            work->mode = 2;
            break;

        case 2:
            if(Hu3DMotionTimeGet(modelId) != Hu3DMotionMaxTimeGet(modelId)-1.0f) {
                break;
            }
            work->reactNum--;
            if(work->reactNum != 0) {
                break;
            }
            Hu3DMotionSet(modelId, obj->mtnId[0]);
            Hu3DMotionTimeSet(modelId, 0.0f);
            work->mode = 0;
            break;

        case 3:
            Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
            Hu3DMotionSet(modelId, obj->mtnId[0]);
            work->mode = 0;
            break;

        case 4:
            if(!Hu3DMotionEndCheck(modelId)) {
                break;
            }
            Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
            Hu3DMotionSet(modelId, obj->mtnId[0]);
            work->mode = 0;
            break;
    }
}

/*
 * fn_1_5A78  asm 1751-1952  200 insns -- build the forty-strong crowd.
 *
 * Each gets a random point in its idle loop and faces inward: the runs down
 * the far left and right of EdgePosTbl are turned to look across the stage.
 * Their materials are then tinted flat grey so they read as background rather
 * than competing with the players.
 *
 * Carries the same missing conversion on frandmod's argument as
 * M570CrowdIdleSet below -- see the note there.
 */
void M570CrowdCreate(void)
{
    OMOBJ *obj;
    M570_CROWD *crowd;
    HU3DMODELID modelId;
    HU3DMOTID motId;
    HSFDATA *hsf;
    HSFMATERIAL *material;
    int i;
    int j;

    for(i=0; i<40; i++) {
        obj = omAddObjEx(objman, (s16)(i+0x1200), 1, 2, OM_GRP_NONE, M570CrowdMain);
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M570_CROWD), HU_MEMNUM_OVL);
        memset(obj->data, 0, sizeof(M570_CROWD));
        crowd = obj->data;
        CrowdObj[i] = crowd;
        crowd->no = (s16)i;
        crowd->obj = obj;
        crowd->mode = 0;
        modelId = Hu3DModelCreateData(DATANUM(DATA_m570, 0x14));
        obj->mdlId[0] = modelId;
        for(j=0; j<2; j++) {
            motId = Hu3DJointMotionData(modelId, CrowdMotDataTbl[j]);
            obj->mtnId[j] = motId;
        }
        Hu3DMotionSet(modelId, obj->mtnId[1]);
        Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
        Hu3DMotionTimeSet(modelId, (s32)frandmod((u32)Hu3DMotionMaxTimeGet(modelId)));
        omSetTra(obj, EdgePosTbl[i].x, EdgePosTbl[i].y, EdgePosTbl[i].z);
        if(EdgePosTbl[i].x < -500.0f) {
            omSetRot(obj, 0.0f, 90.0f, 0.0f);
        } else if(EdgePosTbl[i].x > 500.0f) {
            omSetRot(obj, 0.0f, -90.0f, 0.0f);
        } else {
            omSetRot(obj, 0.0f, 0.0f, 0.0f);
        }
        hsf = Hu3DData[modelId].hsf;
        material = hsf->material;
        for(j=0; j<hsf->materialNum; j++) {
            material->color[0] = 178;
            material->color[1] = 178;
            material->color[2] = 178;
            material++;
        }
    }
}

/* fn_1_5D74  asm 1955-1975   19 insns -- put the whole crowd into mode 3. */
static void M570CrowdCheerSet(void)
{
    int i;
    for(i=0; i<40; i++) {
        CrowdObj[i]->mode = 3;
    }
}

/* fn_1_5DB8  asm 1978-2013   34 insns -- and into mode 4, unlooping them. */
static void M570CrowdFinishSet(void)
{
    int i;
    for(i=0; i<40; i++) {
        Hu3DModelAttrReset(CrowdObj[i]->obj->mdlId[0], HU3D_MOTATTR_LOOP);
        CrowdObj[i]->mode = 4;
    }
}

/*
 * fn_1_5F24  asm 2081-2121   39 insns -- the crowd reacts. `no` selects which
 * reaction; the random delay staggers them so they do not move as one.
 */
void M570CrowdReactSet(int no)
{
    int i;
    for(i=0; i<40; i++) {
        CrowdObj[i]->mode = 1;
        CrowdObj[i]->delay = frandmod(60);
        CrowdObj[i]->reactNum = no;
    }
}

/*
 * fn_1_4AC8  asm  622- 666   43 insns -- read a hand off the pad.
 * First of A, B, X wins; the rumble is the confirmation.
 */
static void M570PlayerInput(M570_PLAYER *player)
{
    int i;
    for(i=0; i<3; i++) {
        if(HuPadBtnDown[player->padNo] & ButtonTbl[i]) {
            omVibrate(player->no, 12, 6, 6);
            player->handNo = (s16)i;
            return;
        }
    }
}

/*
 * fn_1_4B64  asm  669- 692   22 insns -- did this chaser match the solo
 * player's hand? The solo player never matches themselves.
 */
static BOOL M570PlayerHandSameCheck(M570_PLAYER *player)
{
    if(SoloPlayer == player) {
        return FALSE;
    }
    if(SoloPlayer->handNo == player->handNo) {
        return TRUE;
    }
    return FALSE;
}

/*
 * fn_1_4CC8  asm  769- 795   25 insns -- burst particles at the player's hand,
 * found through the character model's item hook rather than a fixed offset.
 */
static void M570PlayerParManCreate(M570_PLAYER *player)
{
    char *hookName = CharModelItemHookGet(player->charNo, 2, 0);
    HuVecF pos;
    Hu3DModelObjPosGet(player->obj->mdlId[0], hookName, &pos);
    M570ParManCreate(&pos);
}

/*
 * fn_1_4D2C  asm  798- 840   41 insns -- start a round. Everyone still in it
 * gets a random hand to begin with, which the COM keeps and a human overrides.
 */
void M570PlayerRoundStart(void)
{
    int i;
    for(i=0; i<4; i++) {
        if(PlayerObj[i]->caughtF == 0) {
            PlayerObj[i]->mode = 1;
            PlayerObj[i]->handNo = (s16)frandmod(3);
        }
    }
}

/*
 * fn_1_4BB0  asm  695- 766   70 insns -- put the chosen hand's prop in the
 * player's hand, hung off the character model's item hook.
 */
static void M570PlayerPropSet(M570_PLAYER *player)
{
    char *hookName = CharModelItemHookGet(player->charNo, 2, 0);
    HU3DMODELID modelId = player->obj->mdlId[player->handNo+1];

    Hu3DModelHookSet(player->obj->mdlId[0], hookName, modelId);
    Hu3DModelLayerSet(modelId, 3);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(modelId, 1.0f, 1.0f, 1.0f);
}

/*
 * fn_1_4DC4  asm  843- 927   83 insns -- end of the opening: everyone walks
 * to their playing position.
 */
void M570PlayerIntroSet(void)
{
    M570_PLAYER *player;
    int i;

    for(i=0; i<4; i++) {
        player = PlayerObj[i];
        player->mode = 7;
        player->targetPos = PlayerPosTbl2[player->sideNo];
        M570PlayerMotionSet(player, 1);
    }
}

/*
 * fn_1_5048  asm 1024-1119   94 insns -- the round's time is up: everyone
 * still in it throws their hand.
 */
void M570PlayerRoundEnd(void)
{
    int i;

    HuAudFXPlay(0x911);
    for(i=0; i<4; i++) {
        if(PlayerObj[i]->caughtF == 0) {
            PlayerObj[i]->mode = 2;
            PlayerObj[i]->unk44 = 0;
            M570PlayerMotionSet(PlayerObj[i], 5);
        }
    }
}

/*
 * fn_1_4EF8  asm  930-1021   90 insns -- the winning side steps forward and
 * takes its pose. WinGrp is set by m570.c before this runs.
 */
void M570PlayerWinPose(void)
{
    M570_PLAYER *player;
    int i;

    for(i=0; i<4; i++) {
        player = PlayerObj[i];
        if(player->grp == WinGrp) {
            player->mode = 8;
            player->targetPos = PlayerPosTbl3[player->sideNo];
            M570PlayerMotionSet(player, 2);
        }
    }
}

/*
 * fn_1_5354  asm 1244-1376  131 insns -- the winners cheer and the losers
 * do not. Both branches inline M570PlayerMotionSet with a constant.
 */
void M570PlayerWinSet(void)
{
    int i;

    for(i=0; i<4; i++) {
        if(WinGrp == PlayerObj[i]->grp) {
            M570PlayerMotionSet(PlayerObj[i], 8);
        } else {
            M570PlayerMotionSet(PlayerObj[i], 9);
        }
    }
}

/*
 * fn_1_558C  asm 1408-1482   73 insns -- the stage host's own object.
 * work[0] is the motion it was put into, work[1] its frame counter, work[2]
 * how many of the five beats it has sounded.
 */
static void M570StageMain(OMOBJ *obj)
{
    HuVecF pos;

    switch(obj->work[0]) {
        case 1:
            obj->work[1]++;
            if(obj->work[1] == 20) {
                HuAudFXPlay(0x910);
            }
            break;
        case 2:
            obj->work[1]++;
            if(obj->work[1] == (obj->work[2]*15)+25 && obj->work[2] < 5) {
                HuAudFXPlay(0x910);
                obj->work[2]++;
            }
            if(Hu3DMotionEndCheck(obj->mdlId[0])
               && Hu3DMotionShiftIDGet(obj->mdlId[0]) < 0) {
                Hu3DModelObjPosGet(obj->mdlId[0], StageHookName, &pos);
                CharEffectSmokeCreate(1, &pos);
                Hu3DModelAttrSet(obj->mdlId[1], HU3D_ATTR_DISPOFF);
                M570StageMotionSet(0);
            }
            break;
    }
}

/*
 * fn_1_56A0  asm 1485-1584   98 insns -- build the stage host: its model, its
 * four joint motions, and the prop hung off its hand hook.
 */
void M570PlayerStageSet(void)
{
    OMOBJ *obj;
    HU3DMODELID modelId;
    HU3DMOTID motId;
    int i;

    obj = omAddObjEx(objman, 0x1100, 2, 4, OM_GRP_NONE, M570StageMain);
    modelId = Hu3DModelCreateData(DATANUM(DATA_m570, 0x0E));
    obj->mdlId[0] = modelId;
    for(i=0; i<4; i++) {
        motId = Hu3DJointMotionData(modelId, StageMotDataTbl[i]);
        obj->mtnId[i] = motId;
    }
    Hu3DModelShadowSet(modelId);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DMotionSet(modelId, obj->mtnId[0]);
    modelId = Hu3DModelCreateData(DATANUM(DATA_m570, 0x13));
    Hu3DModelHookSet(obj->mdlId[0], StageHookName, modelId);
    obj->mdlId[1] = modelId;
    Hu3DModelShadowSet(modelId);
    omSetTra(obj, 0.0f, 0.0f, -345.0f);
    StageObj = obj;
}

/*
 * fn_1_5820  asm 1587-1639   51 insns -- drive the stage host's own model
 * through one of its four motions.
 */
void M570StageMotionSet(s16 no)
{
    u32 attrTbl[4];
    OMOBJ *obj;

    attrTbl[0] = HU3D_MOTATTR_LOOP;
    attrTbl[1] = HU3D_MOTATTR_NONE;
    attrTbl[2] = HU3D_MOTATTR_NONE;
    attrTbl[3] = HU3D_MOTATTR_LOOP;
    obj = StageObj;
    obj->work[0] = no;
    obj->work[1] = 0;
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_MOTATTR_LOOP);
    Hu3DMotionShiftSet(obj->mdlId[0], obj->mtnId[no], 0.0f, 10.0f, attrTbl[no]);
}

/*
 * fn_1_5E38  asm 2016-2078   61 insns -- put the crowd back to idle, each at
 * a random point in the loop so they are not in step.
 *
 * NOT byte-identical, and deliberately: this is +1 instruction, the only
 * function in the overlay that is knowingly left different.
 *
 * The original emits NO float-to-int conversion on frandmod's argument. It
 * calls Hu3DMotionMaxTimeGet, which returns in f1, and then calls frandmod
 * with r3 untouched -- so what actually reaches frandmod is the model id,
 * not the motion length. That only compiles if the return type is out of
 * scope, and hu3d.h declares it `float` here, so the cast is unavoidable. It
 * is also what the code plainly meant: a random point in the loop.
 *
 * The signedness on the way back out IS reproduced. The original converts
 * frandmod's result to float as a SIGNED int (`xoris` against 0x8000), so it
 * had frandmod returning s32 where this tree's frand.h says u32; without the
 * (s32) the conversion sequence differs even though the instruction count
 * happens to match, which is worth knowing -- an equal count is not proof.
 */
void M570CrowdIdleSet(void)
{
    HU3DMODELID modelId;
    int i;

    for(i=0; i<40; i++) {
        CrowdObj[i]->mode = 0;
        modelId = CrowdObj[i]->obj->mdlId[0];
        Hu3DMotionSet(modelId, CrowdObj[i]->obj->mtnId[0]);
        Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
        Hu3DMotionTimeSet(modelId, (s32)frandmod((u32)Hu3DMotionMaxTimeGet(modelId)));
    }
}

/*
 * fn_1_51A8  asm 1122-1241  118 insns -- score the round. Everyone still in
 * throws dust off their hand; whoever matched the solo player is out.
 */
void M570PlayerScore(void)
{
    M570_PLAYER *player;
    int i;

    HuAudFXPlay(0x912);
    for(i=0; i<4; i++) {
        player = PlayerObj[i];
        if(player->caughtF == 0) {
            CharModelHookDustCreate(player->charNo,
                                    CharModelItemHookGet(player->charNo, 2, 0));
            if(M570PlayerHandSameCheck(player)) {
                player->caughtF = 1;
                player->mode = 5;
                M570PlayerMotionSet(player, 6);
            } else {
                player->mode = 4;
            }
            player->unk44 = 0;
        }
    }
}


/*
 * ===========================================================================
 * All 24 written. The map below is kept as an index from the original's
 * symbols to the names here, since nothing else records it.
 * ===========================================================================
                *   fn_1_5820   asm 1587-1639   51  M570StageMotionSet
     *   fn_1_5E38   asm 2016-2078   61  M570CrowdIdleSet
  *
 * The names come from m570.c's call sites; the twelve it calls are declared in
 * m570.h, so their signatures are already fixed.
 */
