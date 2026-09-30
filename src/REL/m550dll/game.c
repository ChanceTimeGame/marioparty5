/*
 * m550dll/game.c -- the duel itself.
 *
 * NOT STARTED. Twenty-six functions, 3,202 instructions. Eleven of them are
 * entry points: m550.c's fadeIn, main and preWinner hooks each index one of
 * the three tables below by Work->subMode and call through it, so this is a
 * set of small state machines rather than a monolith. See ../NOTES.md.
 *
 * Every function here is a stub carrying the fn_1_XXXX it has to reproduce
 * and that function's reference instruction count, in the object's own order.
 */

#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/wipe.h"
#include "game/pad.h"
#include "game/audio.h"
#include "game/frand.h"
#include "game/mg/seqman.h"
#include "game/mg/timer.h"
#include "game/hsfex.h"
#include "game/gamemes.h"
#include "game/flag.h"

#include "REL/m550dll/m550.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"

/* Forward declarations, in the order the object needs them. */
static int M550GameUnk4308(int player);
static void M550GameUnk4D94(void);
static void M550GameUnk3904(int player);
static int M550GameUnk3BB0(int player);
static void M550GameUnk3DD8(int player);
static void M550GameUnk4494(int player);
static void M550GameUnk4898(int player, int no);
static void M550GameUnk4688(int player);
static void M550GameUnk49F0(int player, int no);
static void M550GameUnk4C00(void);

/* --- .data --- */

/*
 * data_250 -- the thirty sockets an item can be stuck on, in the duellist's
 * own space: a column from y=120 up to y=260, filled in the order they are
 * scored. M550GameUnk49F0 translates the hand matrix by one of these.
 */
static HuVecF ItemPosTbl[30] = {
    {    -35.0f,  220.0f,   75.0f },
    {     80.0f,  145.0f,    0.0f },
    {    -80.0f,  145.0f,    0.0f },
    {    -29.0f,  165.0f,   90.0f },
    {     29.0f,  165.0f,   90.0f },
    {     70.0f,  190.0f,   55.0f },
    {     50.0f,  190.0f,  -50.0f },
    {    -50.0f,  190.0f,  -50.0f },
    {    -70.0f,  190.0f,   55.0f },
    {      0.0f,  260.0f,    0.0f },
    {     30.0f,  235.0f,  -28.0f },
    {    -30.0f,  235.0f,  -28.0f },
    {    -30.0f,  235.0f,   28.0f },
    {     30.0f,  235.0f,   28.0f },
    {     60.0f,  190.0f,    0.0f },
    {      0.0f,  200.0f,  -60.0f },
    {    -60.0f,  190.0f,    0.0f },
    {      0.0f,  200.0f,   60.0f },
    {      0.0f,  210.0f,    0.0f },
    {     29.0f,  180.0f,   28.0f },
    {     29.0f,  180.0f,  -28.0f },
    {    -29.0f,  180.0f,  -28.0f },
    {    -29.0f,  180.0f,   28.0f },
    {     50.0f,  135.0f,   30.0f },
    {     50.0f,  135.0f,  -30.0f },
    {      0.0f,  135.0f,  -55.0f },
    {    -50.0f,  135.0f,  -30.0f },
    {    -50.0f,  135.0f,   30.0f },
    {      0.0f,  135.0f,   55.0f },
    {      0.0f,  120.0f,    0.0f },
};

/* data_3B8 -- the duel's BGM handle, -1 until M550FadeIn2 starts it. */
static s32 BgmHandle = -1;

/* --- .bss --- */

static int GameUnk1EC0[2];       /* bss_1EC0 */
static GAMEMESID GameUnk1EC8;    /* bss_1EC8 -- the winner banner */
static int GameUnk1ECC[2][30];   /* bss_1ECC */
static int GameUnk1FBC;

/*
 * fn_1_1C84 -- fadeIn sub-state 0. Hands each computer duellist its plan,
 * clears both thirty-slot tables and swings the camera in over three seconds.
 */
void M550FadeIn0(void)
{
    int i;

    Work.mode[0]++;
    Work.mode[1] = 0;
    Work.timer = 16200;
    Unk0 = 0;
    for(i=0; i<2; i++) {
        if(Work.chr[i].dif != 0) {
            M550GameUnk4494(i);
        }
    }
    for(i=0; i<30; i++) {
        GameUnk1ECC[0][i] = 0;
        GameUnk1ECC[1][i] = 0;
    }
    omCameraViewMoveSimple(&CameraView[1], 180);
    HuAudFXPlay(0x860);
    M550ItemPosUpdate();
}

/* fn_1_1D88 -- fadeIn sub-state 1: wait for the wipe. */
void M550FadeIn1(void)
{
    M550ItemPosUpdate();
    if(WipeCheckEnd() == 0) {
        Work.mode[0]++;
    }
}

/* fn_1_1DCC -- fadeIn sub-state 2: wait for the camera, then start the music. */
void M550FadeIn2(void)
{
    if(omCameraViewCheck(1) != 0) {
        Work.mode[0] = 0;
        Work.mode[1] = 0;
        MgSeqModeNext();
        BgmHandle = HuAudBGMPlay(75);
    }
    M550ItemPosUpdate();
}

/* fn_1_1E34 -- 1. */
static void M550GameUnk1E34(void)
{
}

/*
 * fn_1_1E38 -- main sub-state 0, and the duel proper: run both duellists,
 * decide when one of them has finished, then play the loser's item away.
 */
void M550Main0(void)
{
    M550_MODEL *mdl;
    int i;
    int loser;

    for(i=0; i<2; i++) {
        if(Work.chr[i].dif != 0) {
            M550GameUnk4688(i);
        }
        M550GameUnk3904(i);
    }
    if(Work.winner == 0) {
        if(Work.count[0] >= 30 || Work.count[1] >= 30) {
            if(Work.count[0] == Work.count[1]) {
                i = rand8() % 2;
                Work.count[i]--;
            }
            i = 0;
            if(Work.count[1] >= 30) {
                i = 1;
            }
            Work.winner = i+1;
            if(Unk0 != 0) {
                MgTimerKill(Unk0);
                Unk0 = 0;
            }
        }
        if(Work.timer > 0) {
            Work.timer--;
        } else if(Unk0 != 0) {
            if(MgTimerDoneCheck(Unk0) != 0) {
                Work.mode[0] = 1;
                Work.count[0] = Work.count[2];
                Work.count[1] = Work.count[3];
                MgSeqModeNext();
                HuAudSStreamFadeOut(BgmHandle, 1000);
            }
        } else if(Work.timer == 0) {
            Unk0 = MgTimerCreate(0);
            MgTimerParamSet(Unk0, 1800, 0, 0);
            MgTimerPosSet(Unk0, 288.0f, 64.0f);
            MgTimerModeOnSet(Unk0, 1);
            Work.timer--;
        }
    }
    if(Work.winner != 0) {
        loser = (Work.winner-1) ^ 1;
        switch(Work.winMode) {
        case 0:
            if(Work.count[Work.winner-1] == Work.count[Work.winner+1]) {
                Work.winMode++;
            }
            break;
        case 1:
            if(Work.mode[Work.winner] == 0) {
                Work.winMode++;
                Work.hookVec[0].y = 1.0f;
                Work.hookVec[0].z = 0.0f;
            }
            break;
        case 2:
            break;
        case 3:
            mdl = &Work.models[loser+4];
            mdl->rot.z += (float)((loser*40)-20);
            mdl->pos.x -= Work.hookVec[0].y * (float)(3-(loser*6));
            mdl->pos.y += 6.0f * Work.hookVec[0].y;
            Work.hookVec[0].y *= 0.95;
            Hu3DModelScaleSet(Work.models[loser+4].modelId, Work.hookVec[0].y, Work.hookVec[0].y, Work.hookVec[0].y);
            break;
        }
    }
    for(i=0; i<2; i++) {
        M550GameUnk3DD8(i);
    }
    M550GameUnk4C00();
    M550ItemPosUpdate();
}

/* fn_1_235C -- 1. main sub-state 1. */
void M550Main1(void)
{
}

/* fn_1_2360 -- 1. main sub-state 2. */
void M550Main2(void)
{
}

/*
 * fn_1_2364 -- the win animation on its own, for the modes after MAIN that
 * still have to run it. The same five-way switch M550Main0 carries, minus
 * the duel; the loser is computed whether or not there is a winner yet.
 */
void M550GameUnk2364(void)
{
    M550_MODEL *mdl;
    int i;
    int loser;

    loser = (Work.winner-1) ^ 1;
    if(Work.winner != 0) {
        switch(Work.winMode) {
        case 0:
            if(Work.count[Work.winner-1] != Work.count[Work.winner+1]) {
                Work.winMode++;
            }
            break;
        case 1:
            if(Work.mode[Work.winner] == 0) {
                Work.winMode++;
                Work.hookVec[0].y = 1.0f;
                Work.hookVec[0].z = 0.0f;
            }
            break;
        case 2:
            break;
        case 3:
            mdl = &Work.models[loser+4];
            mdl->rot.z += (float)((loser*40)-20);
            mdl->pos.x -= Work.hookVec[0].y * (float)(3-(loser*6));
            mdl->pos.y += 6.0f * Work.hookVec[0].y;
            Work.hookVec[0].y *= 0.95;
            Hu3DModelScaleSet(Work.models[loser+4].modelId, Work.hookVec[0].y, Work.hookVec[0].y, Work.hookVec[0].y);
            break;
        case 4:
            break;
        }
    }
    for(i=0; i<2; i++) {
        M550GameUnk3DD8(i);
    }
    M550GameUnk4C00();
    M550ItemPosUpdate();
}

/* fn_1_2618 -- park both duellists and hand the sequence back to mode 4. */
void M550GameUnk2618(void)
{
    int i;

    for(i=0; i<2; i++) {
        M550GameUnk3DD8(i);
    }
    Work.mode[0] = 4;
    M550GameUnk4C00();
    M550ItemPosUpdate();
}

/*
 * fn_1_2670 -- preWinner sub-state 0: the whole scene jumps 2000 units up
 * to the winner's podium, both duellists are re-placed and re-posed there,
 * and the stage props are reset behind them.
 */
void M550PreWin0(void)
{
    int winner;
    int loser;

    Center.x = 0.0f;
    Center.y = 2000.0f;
    Center.z = 0.0f;
    CRot.x = -90.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 300.0f;
    omOutView(0);
    winner = Work.winner-1;
    loser = winner^1;
    Hu3DModelHookReset(Work.models[winner+2].modelId);
    Hu3DModelAttrSet(Work.models[winner+4].modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(Work.models[winner+2].modelId, -200.0f+(400.0f*(float)winner), 2300.0f, 300.0f);
    Work.models[winner+2].pos.x = -200.0f+(400.0f*(float)winner);
    Work.models[winner+2].pos.y = 2300.0f;
    Work.models[winner+2].pos.z = 300.0f;
    Hu3DModelRotSet(Work.models[winner+2].modelId, 0.0f, 0.0f, 0.0f);
    Work.models[winner+2].rot.x = 0.0f;
    Work.models[winner+2].rot.y = 0.0f;
    Work.models[winner+2].rot.z = 0.0f;
    CameraView[1].center.x = -200.0f+(400.0f*(float)winner);
    CameraView[1].center.y = 2400.0f;
    CameraView[1].center.z = 300.0f;
    CameraView[1].rot.x = -15.0f;
    CameraView[1].rot.y = 0.0f;
    CameraView[1].rot.z = 0.0f;
    CameraView[1].zoom = 600.0f;
    Hu3DMotionSet(Work.models[winner+2].modelId, Work.motId[winner][2]);
    Hu3DMotionTimeSet(Work.models[winner+2].modelId, 0.0f);
    Hu3DMotionSpeedSet(Work.models[winner+2].modelId, 1.0f);
    Hu3DModelAttrSet(Work.models[winner+2].modelId, 0x40000001);
    Hu3DMotionAttrSet(Work.motId[winner][2], 1);
    Hu3DModelAttrSet(Work.models[loser+4].modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(Work.models[loser+2].modelId, 0.0f, 1900.0f, 0.0f);
    Work.models[loser+2].pos.x = 0.0f;
    Work.models[loser+2].pos.y = 1900.0f;
    Work.models[loser+2].pos.z = 0.0f;
    Hu3DModelRotSet(Work.models[loser+2].modelId, 0.0f, 0.0f, 0.0f);
    Work.models[loser+2].rot.x = 0.0f;
    Work.models[loser+2].rot.y = 0.0f;
    Work.models[loser+2].rot.z = 0.0f;
    Hu3DMotionSet(Work.models[loser+2].modelId, Work.motId[loser][4]);
    Hu3DModelAttrSet(Work.models[loser+2].modelId, 0x40000001);
    Hu3DMotionTimeSet(Work.models[loser+2].modelId, 0.0f);
    Hu3DMotionSpeedSet(Work.models[loser+2].modelId, 1.0f);
    Work.mode[0]++;
    Work.hookVec[0].x = 1.0f;
    M550ItemPosUpdate();
    M550Unk7C00();
    M550Unk7E94();
    M550Unk8190();
}

/*
 * fn_1_2D98 -- preWinner sub-state 1: the loser drops out of shot, flattening
 * as they go, with their own cry on the frame it starts. When they are gone
 * the duel state is cleared and the shared model comes in.
 */
void M550PreWin1(void)
{
    int seTbl[13] = {
        0x85C, 0x85D, 0x85A, 0x856, 0x858, 0x85F, 0x857,
        0x85E, 0x859, 0x85B, 0x85B, 0x85B, 0x85B
    };
    int winner;
    int loser;

    winner = Work.winner-1;
    loser = winner^1;
    if(1.0f == Work.hookVec[0].x) {
        HuAudFXPlay(seTbl[Work.chr[loser].charNo]);
    }
    Work.models[loser+2].pos.y -= 8.0f;
    Work.models[loser+2].rot.y -= 1.0f;
    Work.hookVec[0].x *= 0.96f;
    if(Work.hookVec[0].x < 0.03f) {
        Work.hookVec[0].x = 0.0f;
    }
    Hu3DModelScaleSet(Work.models[loser+2].modelId, Work.hookVec[0].x, 1.0f, Work.hookVec[0].x);
    if(Work.models[loser+2].pos.y < -100.0f || Work.hookVec[0].x <= 0.0f) {
        Hu3DModelAttrSet(Work.models[loser+2].modelId, HU3D_ATTR_DISPOFF);
        Work.mode[0]++;
        Work.mode[1] = 0;
        Work.count[0] = Work.count[1] = 0;
        Work.timer = Work.unk114 = 0;
        M550GameUnk4D94();
        omVibrate(Work.chr[loser].no, 30, 6, 6);
        HuAudFXPlay(0x855);
    }
    M550ItemPosUpdate();
}

/*
 * fn_1_3088 -- preWinner sub-state 2: drift the shared model along one
 * eighth of a turn for a second, then swing the camera back.
 */
void M550PreWin2(void)
{
    M550_MODEL *mdl;

    mdl = &Work.models[148];
    mdl->pos.x += 5.5 * sin(0.39269908169872414);
    mdl->pos.z += 5.5 * cos(0.39269908169872414);
    if(Work.timer++ > 60) {
        omCameraViewMoveSimple(&CameraView[1], 180);
        Work.mode[0]++;
        Work.unk118 = 0;
    }
    M550ItemPosUpdate();
}

/*
 * fn_1_3174 -- preWinner sub-state 3: two seconds after the camera moves,
 * put up the winner banner, pay the ten coins unless this is practice, and
 * wait for the banner to finish.
 */
void M550PreWin3(void)
{
    int winner;
    int no;

    winner = Work.winner-1;
    switch(Work.mode[1]) {
    case 0:
        if(Work.unk118++ > 120) {
            Work.mode[1]++;
            GameUnk1EC8 = GameMesMgWinnerCreate(Work.chr[winner].charNo, -1, -1, -1);
            no = Work.chr[winner].no;
            if(_CheckFlag(FLAG_MG_PRACTICE) == 0) {
                GwPlayer[no].mgCoinBonus = 10;
            }
            Work.timer = 0;
            HuAudJinglePlay(0x79);
            CharFXPlay(Work.chr[winner].charNo, 0x1FA);
        }
        break;
    case 1:
        Work.timer++;
        if(GameMesStatGet(GameUnk1EC8) == 0) {
            if(Work.timer >= 208) {
                GameMesKill(GameUnk1EC8);
                Work.mode[0] = 0;
                MgSeqModeNext();
            }
        }
        break;
    }
    M550ItemPosUpdate();
}

/*
 * fn_1_3324 -- preWinner sub-state 4, the draw: the banner, both pads
 * rumbling, then on frame 8 both items leave both hands at once and from
 * frame 9 both duellists sink while their items spin away.
 */
void M550PreWin4(void)
{
    Mtx mtx;
    HuVecF pos;
    HuVecF rot;
    M550_MODEL *mdl;
    int i;

    switch(Work.mode[1]) {
    case 0:
        GameUnk1EC8 = GameMesMgDrawCreate();
        Work.timer = 0;
        Work.mode[1]++;
        M550Unk10BC(0);
        M550Unk10BC(1);
        omVibrate(Work.chr[0].no, 40, 12, 0);
        omVibrate(Work.chr[1].no, 40, 12, 0);
        HuAudJinglePlay(0x7B);
        break;
    case 1:
        Work.timer++;
        if(GameMesStatGet(GameUnk1EC8) == 0) {
            if(Work.timer >= 208) {
                GameMesKill(GameUnk1EC8);
                MgSeqModeNext();
                Work.mode[0] = 1;
            }
        }
        break;
    }
    if(Work.timer == 8) {
        for(i=0; i<2; i++) {
            Work.player[i].shiftMode = 1;
            Work.player[i].shiftMotNo = 3;
            Work.player[i].shiftTime = 0.0f;
            Work.player[i].shiftSpeed = 8.0f;
            Work.player[i].shiftAttr = 0x40000001;
            Hu3DModelObjMtxGet(Work.models[i+2].modelId, CharModelItemHookGet(Work.chr[i].charNo, 1, 0), mtx);
            Hu3DModelHookReset(Work.models[i+2].modelId);
            mdl = &Work.models[i+4];
            Hu3DMtxRotGet(mtx, &rot);
            pos.x = mtx[0][3];
            pos.y = mtx[1][3];
            pos.z = mtx[2][3];
            Hu3DModelPosSetV(mdl->modelId, &pos);
            Hu3DModelRotSetV(mdl->modelId, &rot);
            mdl->pos.x = pos.x;
            mdl->pos.y = pos.y;
            mdl->pos.z = pos.z;
            mdl->rot.x = rot.x;
            mdl->rot.y = rot.y;
            mdl->rot.z = rot.z;
            M550ItemHookVecGet();
            Work.unk138[0] = 1.0f;
            Work.unk138[1] = 1.0f;
        }
    }
    if(Work.timer > 8) {
        for(i=0; i<2; i++) {
            M550ItemPosSet(i, &Work.hookVec[i*2], &Work.hookVec[(i*2)+1]);
            Work.hookVec[i*2].y += 3.0 + 0.1 * (double)(Work.timer-8);
            Work.hookVec[(i*2)+1].y += 2.0 - (double)(i*4);
            mdl = &Work.models[i+4];
            mdl->rot.z += (float)((i*40)-20);
            mdl->pos.x -= Work.unk138[i] * (float)(3-(i*6));
            mdl->pos.y += 6.0f * Work.unk138[i];
            Work.unk138[i] *= 0.95;
            Hu3DModelScaleSet(Work.models[i+4].modelId, Work.unk138[i], Work.unk138[i], Work.unk138[i]);
            Work.models[i+2].pos.y -= 20.0f;
        }
    } else {
        M550ItemPosUpdate();
    }
}

/*
 * fn_1_3904 -- one duellist's input, and the only place a count goes up.
 * A and B together score at once; A then B, or B then A, scores on the
 * second of the pair. Once there is a winner the loser is capped at 29,
 * so the win itself cannot be taken back.
 */
static void M550GameUnk3904(int player)
{
    Work.chr[player].btnDown &= PAD_BUTTON_A|PAD_BUTTON_B;
    if(Work.chr[player].btnDown == (PAD_BUTTON_A|PAD_BUTTON_B)) {
        GameUnk1EC0[player] = 0;
            if(Work.winner == 0) {
                Work.count[player]++;
            } else if(Work.count[player] < 29) {
                Work.count[player]++;
            }
    } else {
        switch(GameUnk1EC0[player]) {
        case 0:
            if(Work.chr[player].btnDown == PAD_BUTTON_A) {
                GameUnk1EC0[player] = 1;
            }
            if(Work.chr[player].btnDown == PAD_BUTTON_B) {
                GameUnk1EC0[player] = 2;
            }
            break;
        case 1:
            if(Work.chr[player].btnDown == PAD_BUTTON_B) {
                if(Work.winner == 0) {
                    Work.count[player]++;
                } else if(Work.count[player] < 29) {
                    Work.count[player]++;
                }
            }
            GameUnk1EC0[player] = 0;
            break;
        case 2:
            if(Work.chr[player].btnDown == PAD_BUTTON_A) {
                if(Work.winner == 0) {
                    Work.count[player]++;
                } else if(Work.count[player] < 29) {
                    Work.count[player]++;
                }
            }
            GameUnk1EC0[player] = 0;
            break;
        }
    }
}

/*
 * fn_1_3BB0 -- take the item out of the loser's hand and leave it standing
 * where the hand was, so M550Main0's case 3 can spin it away. Returns
 * whether it fired, which is once: winMode moves to 3 here.
 */
static int M550GameUnk3BB0(int player)
{
    Mtx mtx;
    HuVecF pos;
    HuVecF rot;
    M550_MODEL *mdl;
    int done;

    done = 0;
    if(Work.winMode > 1) {
        if(player != Work.winner-1) {
            Work.mode[player+1] = 5;
            Work.player[player].shiftMode = 1;
            Work.player[player].shiftMotNo = 3;
            Work.player[player].shiftTime = 0.0f;
            Work.player[player].shiftSpeed = 8.0f;
            Work.player[player].shiftAttr = 0x40000001;
            Hu3DModelObjMtxGet(Work.models[player+2].modelId, CharModelItemHookGet(Work.chr[player].charNo, 1, 0), mtx);
            Hu3DModelHookReset(Work.models[player+2].modelId);
            mdl = &Work.models[player+4];
            Hu3DMtxRotGet(mtx, &rot);
            pos.x = mtx[0][3];
            pos.y = mtx[1][3];
            pos.z = mtx[2][3];
            Hu3DModelPosSetV(mdl->modelId, &pos);
            Hu3DModelRotSetV(mdl->modelId, &rot);
            mdl->pos.x = pos.x;
            mdl->pos.y = pos.y;
            mdl->pos.z = pos.z;
            mdl->rot.x = rot.x;
            mdl->rot.y = rot.y;
            mdl->rot.z = rot.z;
            Work.winMode = 3;
            done = 1;
            if(player != 0) {
                HuAudFXPlay(0x853);
            } else {
                HuAudFXPlay(0x854);
            }
        }
    }
    return done;
}

/*
 * fn_1_3DD8 -- one duellist's seven-state machine, and the only caller of
 * M550GameUnk3BB0: states 0, 2 and 3 all give the win animation the chance
 * to take over before they do anything else. The two states past the end
 * are the loser sinking out of shot.
 */
static void M550GameUnk3DD8(int player)
{
    M550_MODEL *mdl;

    mdl = &Work.models[player+4];
    switch(Work.mode[player+1]) {
    case 0:
        if(M550GameUnk3BB0(player) != 0) {
            break;
        }
        if(Work.count[player] > Work.count[player+2]) {
            Work.count[player+2]++;
            Work.player[player].shiftMode = 1;
            Work.player[player].shiftMotNo = 1;
            Work.player[player].shiftTime = 0.0f;
            Work.player[player].shiftSpeed = 4.0f;
            Work.player[player].shiftAttr = 0;
            Work.mode[player+1] = 1;
        }
        break;
    case 1:
        if(Work.player[player].shiftMode == 0) {
            Work.mode[player+1] = 2;
        }
        break;
    case 2:
        if(M550GameUnk3BB0(player) != 0) {
            break;
        }
        if(Work.player[player].time >= 8.0f) {
            Work.mode[player+1] = 3;
            Hu3DMotionTimeSet(mdl->modelId, 0.0f);
            if(player != 0) {
                HuAudFXPlay(0x84F);
            } else {
                HuAudFXPlay(0x850);
            }
        }
        break;
    case 3:
        if(M550GameUnk3BB0(player) != 0) {
            break;
        }
        if(Work.player[player].time >= 10.0f) {
            Hu3DMotionSpeedSet(mdl->modelId, 1.0f);
        }
        if(Work.player[player].time >= 14.0f) {
            M550GameUnk4898(player, Work.count[player+2]);
            Hu3DMotionTimeSet(mdl->modelId, 0.0f);
            Hu3DMotionSpeedSet(mdl->modelId, 0.0f);
            if(Work.count[player] != Work.count[player+2]) {
                Work.player[player].time = 8.0f;
                Work.mode[player+1] = 2;
                Work.count[player+2]++;
            } else {
                Work.player[player].shiftMode = 1;
                Work.player[player].shiftMotNo = 0;
                Work.player[player].shiftTime = 0.0f;
                Work.player[player].shiftSpeed = 6.0f;
                Work.player[player].shiftAttr = 0x40000001;
                Work.mode[player+1] = 4;
            }
        }
        break;
    case 4:
        if(Work.player[player].shiftMode == 0) {
            Work.mode[player+1] = 0;
        }
        break;
    case 5:
        if(Work.player[player].shiftMode == 0) {
            Work.mode[player+1] = 6;
        }
        Work.models[player+2].pos.y -= 20.0f;
        break;
    case 6:
        Work.models[player+2].pos.y -= 20.0f;
        break;
    }
}

/*
 * fn_1_4308 -- how long a computer duellist waits before its next press,
 * by difficulty. The hardest two also count their presses, and the very
 * hardest shaves a frame off every fifth.
 */
static int M550GameUnk4308(int player)
{
    int n;

    n = 0;
    switch(Com[player].level) {
    case 0:
        n = 13;
        n += rand8() % 5;
        break;
    case 1:
        n = 9;
        n += rand8() % 4;
        break;
    case 2:
        n = 7;
        Com[player].tick++;
        n += rand8() % 4;
        break;
    case 3:
        n = 4;
        Com[player].tick++;
        if(Com[player].tick % 5 == 0) {
            n--;
        }
        n += rand8() % 3;
        break;
    }
    return n;
}

/* fn_1_4494 -- start one computer duellist. */
static void M550GameUnk4494(int player)
{
    memset(&Com[player], 0, sizeof(M550_COM));
    Com[player].level = Work.chr[player].dif - 1;
    Com[player].wait = M550GameUnk4308(player);
}

/*
 * fn_1_4688 -- a computer duellist's frame: when its wait runs out it
 * presses A and B together, which is the pattern M550GameUnk3904 scores
 * at once, and picks the next wait.
 */
static void M550GameUnk4688(int player)
{
    Com[player].wait--;
    if(Com[player].wait <= 0) {
        Work.chr[player].btnDown = PAD_BUTTON_A|PAD_BUTTON_B;
        Work.chr[player].btn = PAD_BUTTON_A|PAD_BUTTON_B;
        Com[player].wait = M550GameUnk4308(player);
    }
}

/*
 * fn_1_4898 -- score one item for the other duellist: hide the one it came
 * from, start its counterpart moving past twenty, and rumble their pad on
 * the thirtieth.
 */
static void M550GameUnk4898(int player, int no)
{
    M550_MODEL *mdl;

    mdl = &Work.models[6+((player^1)*30)+(29-(no-1))];
    Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
    if(no > 19) {
        mdl = &Work.models[(10-(no-20)+126)+((player^1)*11)];
        Hu3DMotionSpeedSet(mdl->modelId, 1.0f);
    }
    M550GameUnk49F0(player^1, no-1);
    if(no == 30) {
        omVibrate(Work.chr[player^1].no, 50, 12, 0);
    }
}

/* fn_1_4990 -- the first free slot in one duellist's thirty, or -1. */
static int M550GameUnk4990(int player)
{
    int i;

    for(i=0; i<30; i++) {
        if(GameUnk1ECC[player][i] == 0) {
            break;
        }
    }
    if(i == 30) {
        return -1;
    }
    return i;
}

/*
 * fn_1_49F0 -- stick one scored item on the other duellist, at the socket
 * ItemPosTbl names, relative to hook 4 of their model.
 */
static void M550GameUnk49F0(int player, int no)
{
    Mtx trans;
    Mtx hook;
    M550_MODEL *mdl;
    float x;
    float y;
    float z;
    int slot;

    slot = M550GameUnk4990(player);
    if(slot >= 0) {
        GameUnk1ECC[player][slot] = 1;
        Hu3DModelObjMtxGet(Work.models[player+2].modelId, CharModelItemHookGet(Work.chr[player].charNo, 1, 4), hook);
        PSMTXTrans(trans, ItemPosTbl[no].x, ItemPosTbl[no].y, ItemPosTbl[no].z);
        PSMTXConcat(hook, trans, trans);
        x = trans[0][3];
        y = trans[1][3];
        z = trans[2][3];
        mdl = &Work.models[(player*30)+(slot+66)];
        Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(mdl->modelId, x, y, z);
        mdl->pos.x = x;
        mdl->pos.y = y;
        mdl->pos.z = z;
        Hu3DMotionTimeSet(mdl->modelId, 0.0f);
        Hu3DMotionSpeedSet(mdl->modelId, 1.0f);
        if(player != 0) {
            HuAudFXPlay(0x851);
        } else {
            HuAudFXPlay(0x852);
        }
    }
}

/*
 * fn_1_4C00 -- retire each duellist's thirty spent items once their motion
 * passes frame 18, and when a duellist has none left and the other has all
 * thirty, end the duel.
 */
static void M550GameUnk4C00(void)
{
    M550_MODEL *mdl;
    float time;
    int i;
    int j;
    int live;

    time = -1.0f;
    for(i=0; i<2; i++) {
        live = 0;
        for(j=0; j<30; j++) {
            if(GameUnk1ECC[i][j] != 0) {
                mdl = &Work.models[(i*30)+(j+66)];
                time = Hu3DMotionTimeGet(mdl->modelId);
                if(time >= 18.0f) {
                    GameUnk1ECC[i][j] = 0;
                    Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
                }
                live++;
            }
        }
        if(live == 0) {
            if(Work.count[(i^1)+2] == 30) {
                live = MgSeqModeGet();
                if(live == 5) {
                    if(Work.mode[(i^1)+1] == 0) {
                        MgSeqModeNext();
                        HuAudSStreamFadeOut(BgmHandle, 1000);
                    }
                }
            }
        }
    }
}

/* fn_1_4D94 -- bring the shared model in above the arena and start it. */
static void M550GameUnk4D94(void)
{
    M550_MODEL *mdl;

    mdl = &Work.models[148];
    Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
    Hu3DMotionTimeSet(mdl->modelId, 0.0f);
    Hu3DMotionSpeedSet(mdl->modelId, 1.5f);
    Hu3DModelPosSet(mdl->modelId, 0.0f, 20.0f, 0.0f);
    mdl->pos.x = 0.0f;
    mdl->pos.y = 20.0f;
    mdl->pos.z = 0.0f;
    Hu3DModelScaleSet(mdl->modelId, 0.3f, 0.3f, 0.3f);
    M550Unk6D8C();
}

/* fn_1_4E88 -- 1. */
static void M550GameUnk4E88(void)
{
}
