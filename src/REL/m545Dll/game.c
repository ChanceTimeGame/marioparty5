/*
 * m545dll/game.c -- the tower duel: the sequence steps, the block stacks,
 * the press windows and the computer duellists. Written from the reference
 * assembly, functions in reference order; line ranges are into
 * build/mp5-asm/m545Dll/asm/REL/m545Dll/game.s.
 */

#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/audio.h"
#include "game/frand.h"
#include "game/pad.h"
#include "game/flag.h"
#include "game/mg/seqman.h"

#include "REL/m545Dll/m545.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

/* A distance that never goes negative the way retail computes it. */
#define M545_DIST(a, b) ((((a)-(b)) > 0.0f) ? ((a)-(b)) : ((a)-(-1.0f*(b))))

typedef struct M545Block_s {
    /* 0x00 */ s16 kind;            /* the button the block asks for: A, B, X, Y, L, R */
    /* 0x02 */ s16 time;            /* frames left to press it */
} M545_BLOCK;

void fn_1_3654(M545_WORK *work);
void fn_1_373C(M545_WORK *work);
void fn_1_40AC(M545_WORK *work);
void fn_1_41D4(M545_WORK *work, s16 player);
s16 fn_1_4400(M545_WORK *work, s16 player);
void fn_1_44D8(M545_WORK *work);
s16 fn_1_499C(M545_WORK *work, s16 which);
s16 fn_1_4B2C(M545_WORK *work, s16 block, s16 height);
s16 fn_1_5794(M545_WORK *work, s16 player);
s16 fn_1_5BC4(M545_WORK *work, s16 player);
void fn_1_6590(M545_WORK *work);
void fn_1_6668(M545_WORK *work, float speed);
void fn_1_695C(M545_WORK *work, s16 player, float angle);
void fn_1_6BC4(M545_WORK *work, s16 player, float speed);
s32 fn_1_6D40(M545_WORK *work);
s32 fn_1_70E8(M545_WORK *work);
void fn_1_762C(M545_WORK *work, s16 player);

/* --- .data: lbl_1_data_2D8 follows fn_1_3030, whose jumptable comes first --- */

/* --- .bss (CodeWarrior lays it out in reverse definition order) --- */

s16 lbl_1_bss_99C[2][6];            /* each duellist's blocks, as model numbers */
M545_BLOCK lbl_1_bss_980[7];
HuVecF lbl_1_bss_8D8[14];           /* each block's offset */

/* asm 1-435, 499 insns. Init step: the stacks, the block kinds and models, then the particles. */
s32 fn_1_26BC(M545_WORK *work)
{
    s32 result;
    s16 i;
    s16 j;
    s16 n;
    s16 rotY;

    result = 1;
    memset(&lbl_1_bss_19C, 0, sizeof(lbl_1_bss_19C));
    memset(lbl_1_bss_C, 0, sizeof(lbl_1_bss_C));
    for(i=0; i<12; i++) {
        lbl_1_bss_19C.seF[i] = -1;
    }
    lbl_1_bss_C[0].scale.x = 1.0f;
    lbl_1_bss_C[0].scale.y = 1.0f;
    lbl_1_bss_C[0].scale.z = 1.0f;
    lbl_1_bss_C[1].scale.x = 1.0f;
    lbl_1_bss_C[1].scale.y = 1.0f;
    lbl_1_bss_C[1].scale.z = 1.0f;
    lbl_1_bss_C[0].aliveF = 1;
    lbl_1_bss_C[1].aliveF = 1;
    lbl_1_bss_C[0].mode = 1;
    lbl_1_bss_C[1].mode = 1;
    for(i=0; i<2; i++) {
        for(j=0; j<2; j++) {
            lbl_1_bss_C[i].hookName[j] = CharModelItemHookGet(work->chr[i].charNo, 1, 0);
        }
    }
    for(i=0; i<7; i++) {
        lbl_1_bss_980[i].kind = -1;
        lbl_1_bss_980[i].time = 0;
    }
    for(i=1; i<7; i++) {
        do {
            lbl_1_bss_980[i].kind = frandmod(6);
            for(j=1, n=0; j<7; j++) {
                if(lbl_1_bss_980[i].kind == lbl_1_bss_980[j].kind) {
                    n++;
                }
            }
        } while(n > 1);
    }
    for(i=0; i<7; i++) {
        lbl_1_bss_980[i].time = frandmod(121)+60;
    }
    for(i=0; i<6; i++) {
        n = lbl_1_bss_980[i+1].kind*2;
        lbl_1_bss_99C[0][i] = n;
        lbl_1_bss_99C[1][i] = n+1;
    }
    for(i=0, n=0, j=12; i<12; i++, n++, j++) {
        work->models[n].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(work->stageDataTbl[i/2], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(work->models[n].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(work->models[n].modelId, 1);
        Hu3DModelLayerSet(work->models[n].modelId, 1);
        rotY = frandmod(15)-7;
        work->models[n].rot.x = 0.0f;
        work->models[n].rot.y = rotY;
        work->models[n].rot.z = 0.0f;
        work->models[j].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(work->stageDataTbl[6], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(work->models[j].modelId, HU3D_ATTR_DISPOFF|HU3D_ATTR_MOTION_OFF);
        Hu3DModelCameraSet(work->models[j].modelId, 1);
        Hu3DModelLayerSet(work->models[j].modelId, 5);
        Hu3DModelShadowSet(work->models[j].modelId);
        Hu3DModelShadowDispOn(work->models[j].modelId);
        work->models[j].rot = work->models[n].rot;
        lbl_1_bss_19C.tpLvl[i] = 0.0f;
        Hu3DModelTPLvlSet(work->models[j].modelId, lbl_1_bss_19C.tpLvl[i]);
    }
    for(i=0; i<6; i++) {
        lbl_1_bss_8D8[lbl_1_bss_99C[0][i]].x = 0.0f;
        lbl_1_bss_8D8[lbl_1_bss_99C[0][i]].y = 600.0f+(100.0f*i);
        lbl_1_bss_8D8[lbl_1_bss_99C[0][i]].z = -70.0f;
        lbl_1_bss_8D8[lbl_1_bss_99C[1][i]].x = 0.0f;
        lbl_1_bss_8D8[lbl_1_bss_99C[1][i]].y = 600.0f+(100.0f*i);
        lbl_1_bss_8D8[lbl_1_bss_99C[1][i]].z = -70.0f;
    }
    fn_1_40AC(work);
    fn_1_17EC();
    return result;
}

/* asm 438-526, 88 insns. Fade-in step: the music, a wait, the camera pull, then the duellists' idle. */
s32 fn_1_2E88(M545_WORK *work)
{
    M545_PLAYER *pl;
    s16 i;
    s32 result;

    result = 0;
    switch(work->count[1]) {
        case 0:
            if(lbl_1_bss_19C.bgmF == 0) {
                fn_1_2368();
                lbl_1_bss_19C.bgmF = 1;
            }
            if(work->count[0]++ > 100) {
                work->count[1]++;
            }
            break;

        case 1:
            if(fn_1_6D40(work)) {
                work->count[1]++;
            }
            break;

        case 2:
            for(i=0; i<2; i++) {
                pl = &work->player[i];
                pl->shiftMode = 1;
                pl->shiftMotNo = 1;
                pl->shiftTime = 0.0f;
                pl->shiftSpeed = 30.0f;
                pl->shiftAttr = HU3D_MOTATTR_LOOP;
            }
            work->count[1]++;
            break;

        case 3:
            result = 1;
            break;
    }
    fn_1_40AC(work);
    return result;
}

/* asm 529-546, 18 insns. Start step. */
s32 fn_1_2FE8(M545_WORK *work)
{
    s32 result;

    result = 0;
    work->count[0] = 0;
    fn_1_40AC(work);
    return result;
}

/* asm 549-799, 276 insns. Main step: drop a block, open a press window, sway, and settle the loser. */
s32 fn_1_3030(M545_WORK *work)
{
    s32 unkC;
    s32 unk8;
    s16 i;
    s32 result;

    result = 0;
    unkC = 0;
    unk8 = 0;
    switch(work->mode[0]) {
        case 0:
            if(fn_1_4B2C(work, lbl_1_bss_C[0].height, lbl_1_bss_C[0].height)) {
                work->mode[0] = 4;
            }
            break;

        case 1:
            fn_1_44D8(work);
            fn_1_6590(work);
            if(--lbl_1_bss_980[lbl_1_bss_C[0].height].time <= 0 && lbl_1_bss_C[0].inputF == 1 && lbl_1_bss_C[0].height < 6) {
                work->mode[0] = 2;
            }
            if(lbl_1_bss_C[0].aliveF == 0 || lbl_1_bss_C[1].aliveF == 0) {
                work->mode[0] = 5;
                lbl_1_bss_19C.winner = -1;
                if(lbl_1_bss_C[0].aliveF == 1) {
                    lbl_1_bss_19C.winner = 0;
                } else if(lbl_1_bss_C[1].aliveF == 1) {
                    lbl_1_bss_19C.winner = 1;
                }
            }
            break;

        case 2:
            fn_1_6590(work);
            if(fn_1_499C(work, 0)) {
                work->mode[0] = 3;
            }
            break;

        case 3:
            if(fn_1_4B2C(work, lbl_1_bss_C[0].height, lbl_1_bss_C[0].height)) {
                work->mode[0] = 4;
            }
            fn_1_6590(work);
            break;

        case 4:
            if(lbl_1_bss_19C.waitTimer++ > 30) {
                lbl_1_bss_19C.waitTimer = 0;
                work->mode[0] = 1;
            }
            fn_1_6590(work);
            break;

        case 5:
            if(fn_1_499C(work, 1)) {
                for(i=0; i<2; i++) {
                    if(lbl_1_bss_C[i].aliveF == 0) {
                        CharFXPlayVolPan(work->chr[i].charNo, 0x202, 127, (i*32)+48);
                    }
                }
                work->mode[0] = 6;
            }
            break;

        case 6:
            for(i=0; i<2; i++) {
                if(lbl_1_bss_C[i].aliveF == 0 && fn_1_5794(work, i)) {
                    work->mode[0] = 7;
                }
            }
            break;

        case 7:
            if(lbl_1_bss_C[0].aliveF == 0 && lbl_1_bss_C[1].aliveF == 0) {
                MgSeqWinnerSet(CHARNO_NONE, CHARNO_NONE, CHARNO_NONE, CHARNO_NONE);
            } else if(lbl_1_bss_C[0].aliveF == 0) {
                s32 no;
                MgSeqWinnerSet(work->chr[1].charNo, CHARNO_NONE, CHARNO_NONE, CHARNO_NONE);
                no = work->chr[1].no;
                if(!_CheckFlag(FLAG_MG_PRACTICE)) {
                    GwPlayer[no].mgCoinBonus = 10;
                }
            } else if(lbl_1_bss_C[1].aliveF == 0) {
                s32 no;
                MgSeqWinnerSet(work->chr[0].charNo, CHARNO_NONE, CHARNO_NONE, CHARNO_NONE);
                no = work->chr[0].no;
                if(!_CheckFlag(FLAG_MG_PRACTICE)) {
                    GwPlayer[no].mgCoinBonus = 10;
                }
            }
            lbl_1_bss_19C.bgmF = 0;
            work->mode[0] = 0;
            result = 1;
            break;
    }
    fn_1_40AC(work);
    return result;
}

/* A computer duellist's chance (of 100) to press a block right, by difficulty and height. */
s16 lbl_1_data_2D8[4][7] = {
    { 100, 80, 40, 0, 0, 0, 0 },
    { 100, 100, 80, 60, 40, 20, 0 },
    { 100, 100, 100, 80, 60, 40, 20 },
    { 100, 100, 100, 100, 80, 60, 40 }
};

/* asm 802-825, 27 insns. Finish step: fade the music. */
s32 fn_1_3480(M545_WORK *work)
{
    s32 result;

    result = 0;
    if(lbl_1_bss_19C.bgmF == 0) {
        fn_1_2398(1, 100);
        lbl_1_bss_19C.bgmF = 1;
    }
    fn_1_40AC(work);
    result = 1;
    return result;
}

/* asm 828-846, 19 insns. Pre-winner step. */
s32 fn_1_34EC(M545_WORK *work)
{
    s32 result;

    result = 0;
    result = fn_1_70E8(work);
    fn_1_40AC(work);
    return result;
}

/* asm 849-891, 50 insns. Winner step: the winner's pose (and, after a draw, retail's player[-1]). */
s32 fn_1_3538(M545_WORK *work)
{
    M545_PLAYER *pl;
    s32 result;

    result = 0;
    pl = &work->player[lbl_1_bss_19C.winner];
    if(work->mode[1] == 0) {
        pl = &work->player[lbl_1_bss_19C.winner];
        {
            pl->motNo = 4;
            pl->speed = 1.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            pl->time = 0.0f;
        }
        work->mode[1] = 1;
    }
    fn_1_40AC(work);
    return result;
}

/* asm 894-907, 14 insns. Fade-out step. */
s32 fn_1_3600(M545_WORK *work)
{
    s32 result;

    result = 1;
    fn_1_40AC(work);
    return result;
}

/* asm 910-916, 7 insns. Close step. */
s32 fn_1_3638(void)
{
    s32 result;

    result = 1;
    return result;
}

/* asm 919-978, 58 insns. Push every model's position and rotation at Hu3D. */
void fn_1_3654(M545_WORK *work)
{
    s16 i;

    for(i=0; i<M545_MODEL_MAX; i++) {
        Hu3DModelPosSet(work->models[i].modelId, work->models[i].pos.x, work->models[i].pos.y, work->models[i].pos.z);
        Hu3DModelRotSet(work->models[i].modelId, work->models[i].rot.x, work->models[i].rot.y, work->models[i].rot.z);
    }
}

/* asm 981-1523, 604 insns. Hang each duellist's blocks off their hook, by stack mode. */
void fn_1_373C(M545_WORK *work)
{
    s16 i;
    s16 j;
    HU3DMODEL *model;

    for(i=0; i<2; i++) {
        Hu3DModelObjMtxGet(work->models[i+36].modelId, lbl_1_bss_C[i].hookName[0], lbl_1_bss_C[i].hookMtx);
        lbl_1_bss_C[i].hookPos.x = lbl_1_bss_C[i].hookMtx[0][3];
        lbl_1_bss_C[i].hookPos.y = lbl_1_bss_C[i].hookMtx[1][3];
        lbl_1_bss_C[i].hookPos.z = lbl_1_bss_C[i].hookMtx[2][3];
    }
    for(i=0; i<2; i++) {
        for(j=0; j<6; j++) {
            model = &Hu3DData[work->models[lbl_1_bss_99C[i][j]].modelId];
            switch(lbl_1_bss_C[i].mode) {
                case 0:
                    if(j < lbl_1_bss_C[i].height) {
                        PSMTXCopy(lbl_1_bss_C[i].hookMtx, model->mtx);
                    } else {
                        PSMTXIdentity(model->mtx);
                        work->models[lbl_1_bss_99C[i][j]].pos.x = lbl_1_bss_C[i].hookPos.x;
                        work->models[lbl_1_bss_99C[i][j]].pos.y = lbl_1_bss_C[i].hookPos.y;
                        work->models[lbl_1_bss_99C[i][j]].pos.z = lbl_1_bss_C[i].hookPos.z;
                        if(work->models[lbl_1_bss_99C[i][j]].pos.y <= 150.0f) {
                            work->models[lbl_1_bss_99C[i][j]].pos.y = 150.0f;
                        }
                    }
                    break;

                case 1:
                    PSMTXIdentity(model->mtx);
                    work->models[lbl_1_bss_99C[i][j]].pos.x = lbl_1_bss_C[i].hookPos.x;
                    work->models[lbl_1_bss_99C[i][j]].pos.y = lbl_1_bss_C[i].hookPos.y;
                    work->models[lbl_1_bss_99C[i][j]].pos.z = lbl_1_bss_C[i].hookPos.z;
                    if(work->models[lbl_1_bss_99C[i][j]].pos.y <= 150.0f) {
                        work->models[lbl_1_bss_99C[i][j]].pos.y = 150.0f;
                    }
                    break;

                case 2:
                    PSMTXIdentity(model->mtx);
                    work->models[lbl_1_bss_99C[i][j]].pos.x = 0.0f;
                    work->models[lbl_1_bss_99C[i][j]].pos.z = 0.0f;
                    work->models[lbl_1_bss_99C[i][j]].pos.y = lbl_1_bss_C[i].hookPos.y;
                    if(work->models[lbl_1_bss_99C[i][j]].pos.y <= 150.0f) {
                        work->models[lbl_1_bss_99C[i][j]].pos.y = 150.0f;
                    }
                    break;

                case 3:
                    PSMTXIdentity(model->mtx);
                    work->models[lbl_1_bss_99C[i][j]].pos.x = 0.0f;
                    work->models[lbl_1_bss_99C[i][j]].pos.y = 0.0f;
                    work->models[lbl_1_bss_99C[i][j]].pos.z = 0.0f;
                    break;
            }
            work->models[lbl_1_bss_99C[i][j]].pos.x += lbl_1_bss_8D8[lbl_1_bss_99C[i][j]].x;
            work->models[lbl_1_bss_99C[i][j]].pos.y += lbl_1_bss_8D8[lbl_1_bss_99C[i][j]].y;
            work->models[lbl_1_bss_99C[i][j]].pos.z += lbl_1_bss_8D8[lbl_1_bss_99C[i][j]].z;
            work->models[lbl_1_bss_99C[i][j]+12].pos = work->models[lbl_1_bss_99C[i][j]].pos;
            work->models[lbl_1_bss_99C[i][j]+12].pos.y = 101.0f;
        }
    }
}

/* asm 1526-1597, 74 insns. Every step ends here: blocks, models, camera, light, shadow. */
void fn_1_40AC(M545_WORK *work)
{
    fn_1_373C(work);
    fn_1_3654(work);
    fn_1_8C4(0);
    fn_1_106C();
    fn_1_1474();
    lbl_1_bss_C[0].frame++;
    lbl_1_bss_C[1].frame++;
}

/* asm 1600-1732, 139 insns. Count a human's presses this frame. */
void fn_1_41D4(M545_WORK *work, s16 player)
{
    if(work->chr[player].btnDown & PAD_BUTTON_A) {
        lbl_1_bss_C[player].press[0]++;
        lbl_1_bss_C[player].pressTotal[0]++;
    }
    if(work->chr[player].btnDown & PAD_BUTTON_B) {
        lbl_1_bss_C[player].press[1]++;
        lbl_1_bss_C[player].pressTotal[1]++;
    }
    if(work->chr[player].btnDown & PAD_BUTTON_Y) {
        lbl_1_bss_C[player].press[3]++;
        lbl_1_bss_C[player].pressTotal[3]++;
    }
    if(work->chr[player].btnDown & PAD_BUTTON_X) {
        lbl_1_bss_C[player].press[2]++;
        lbl_1_bss_C[player].pressTotal[2]++;
    }
    if(work->chr[player].btnDown & PAD_TRIGGER_L) {
        lbl_1_bss_C[player].press[4]++;
        lbl_1_bss_C[player].pressTotal[4]++;
    }
    if(work->chr[player].btnDown & PAD_TRIGGER_R) {
        lbl_1_bss_C[player].press[5]++;
        lbl_1_bss_C[player].pressTotal[5]++;
    }
}

/* asm 1735-1789, 54 insns. Did the window press every block's button twice? Clears the window. */
s16 fn_1_4400(M545_WORK *work, s16 player)
{
    s16 result;
    s16 j;

    result = 1;
    for(j=1; j<=lbl_1_bss_C[player].height; j++) {
        if(lbl_1_bss_C[player].press[lbl_1_bss_980[j].kind] < 2) {
            result = 0;
        }
    }
    for(j=0; j<6; j++) {
        lbl_1_bss_C[player].press[j] = 0;
    }
    return result;
}

/* asm 1792-2091, 305 insns. The press windows: a second each, vibrating while a block is short. */
void fn_1_44D8(M545_WORK *work)
{
    s16 i;
    s16 j;
    s16 missF;

    missF = 0;
    for(i=0; i<2; i++) {
        if(work->chr[i].dif == 0) {
            fn_1_41D4(work, i);
        }
        for(j=1, missF=0; j<=lbl_1_bss_C[i].height; j++) {
            if(lbl_1_bss_C[i].press[lbl_1_bss_980[j].kind] < 2) {
                missF = 1;
            }
        }
        if(missF == 1) {
            omVibrate(work->chr[i].no, 1, 12, 0);
        }
        if(++lbl_1_bss_C[i].timer >= 60) {
            if(work->chr[i].dif != 0) {
                fn_1_762C(work, i);
            }
            lbl_1_bss_C[i].aliveF = fn_1_4400(work, i);
            lbl_1_bss_C[i].inputF = 1;
            lbl_1_bss_C[i].timer = 0;
            lbl_1_bss_C[i].unkA0 = 0;
        } else {
            lbl_1_bss_C[i].inputF = 0;
        }
    }
}

/* asm 2094-2189, 100 insns. Wait for the duellists' swing to reach its catch frames (or 600 frames). */
s16 fn_1_499C(M545_WORK *work, s16 which)
{
    float range[2];
    M545_PLAYER *pl;
    s16 i;
    s16 result;

    result = 0;
    pl = &work->player[0];
    switch(pl->motNo) {
        case 2:
            if(which == 0) {
                range[0] = 13.0f;
                range[1] = 13.9f;
            } else if(which == 1) {
                range[0] = 1.0f;
                range[1] = 1.9f;
            }
            if((pl->time >= range[0] && pl->time <= range[1]) || lbl_1_bss_19C.checkTimer++ > 600) {
                lbl_1_bss_19C.checkTimer = 0;
                result = 1;
            }
            break;

        default:
            lbl_1_bss_19C.checkTimer = 0;
            result = 1;
            break;
    }
    if(which == 1 && result == 1) {
        for(i=0; i<2; i++) {
            if(lbl_1_bss_C[i].aliveF == 0) {
                omVibrate(work->chr[i].no, 64, 12, 0);
            }
        }
    }
    return result;
}

/* asm 2192-2817, 794 insns. Drop the next block onto both stacks, dust, squash and recover. */
s16 fn_1_4B2C(M545_WORK *work, s16 block, s16 height)
{
    M545_MODEL *mdlA;
    M545_MODEL *mdlB;
    HuVecF pos;
    float a;
    float b;
    float c;
    float frames;
    M545_PLAYER *pl;
    s16 result;

    result = 0;
    frames = 30.0f;
    switch(work->mode[2]) {
        case 0:
            Hu3DModelAttrReset(work->models[lbl_1_bss_99C[0][block]].modelId, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(work->models[lbl_1_bss_99C[1][block]].modelId, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(work->models[lbl_1_bss_99C[0][block]+12].modelId, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(work->models[lbl_1_bss_99C[1][block]+12].modelId, HU3D_ATTR_DISPOFF);
            lbl_1_bss_19C.dropSpeed = -8.259f;
            fn_1_2460(0);
            work->mode[2]++;
            break;

        case 1:
            mdlA = &work->models[lbl_1_bss_99C[0][block]];
            mdlB = &work->models[lbl_1_bss_99C[1][block]];
            a = 600.0f+(100.0f*height);
            b = 100.0f*height;
            lbl_1_bss_19C.dropSpeed -= 0.753f;
            lbl_1_bss_8D8[lbl_1_bss_99C[0][block]].y += lbl_1_bss_19C.dropSpeed;
            lbl_1_bss_8D8[lbl_1_bss_99C[1][block]].y += lbl_1_bss_19C.dropSpeed;
            c = M545_DIST(a, b);
            a = M545_DIST(a, lbl_1_bss_8D8[lbl_1_bss_99C[0][block]].y);
            if(c <= a) {
                lbl_1_bss_8D8[lbl_1_bss_99C[0][block]].y = b;
                lbl_1_bss_8D8[lbl_1_bss_99C[1][block]].y = b;
                work->mode[2]++;
                lbl_1_bss_C[0].height++;
                lbl_1_bss_C[1].height++;
            }
            a = 250.0f;
            b = 430.0f;
            c = (b-a)/(6.0f*frames);
            lbl_1_bss_8->center.y += c;
            a = 800.0f;
            b = 1400.0f;
            c = (b-a)/(6.0f*frames);
            lbl_1_bss_8->zoom += c;
            work->models[lbl_1_bss_99C[0][block]+12].pos = work->models[lbl_1_bss_99C[0][block]].pos;
            work->models[lbl_1_bss_99C[1][block]+12].pos = work->models[lbl_1_bss_99C[1][block]].pos;
            work->models[lbl_1_bss_99C[0][block]+12].pos.y = 101.0f;
            work->models[lbl_1_bss_99C[1][block]+12].pos.y = 101.0f;
            lbl_1_bss_19C.tpLvl[lbl_1_bss_99C[0][block]] += 0.034f;
            lbl_1_bss_19C.tpLvl[lbl_1_bss_99C[1][block]] += 0.034f;
            if(lbl_1_bss_19C.tpLvl[lbl_1_bss_99C[0][block]] >= 1.0f) {
                lbl_1_bss_19C.tpLvl[lbl_1_bss_99C[0][block]] = 1.0f;
                lbl_1_bss_19C.tpLvl[lbl_1_bss_99C[1][block]] = 1.0f;
            }
            Hu3DModelTPLvlSet(work->models[lbl_1_bss_99C[0][block]+12].modelId, lbl_1_bss_19C.tpLvl[lbl_1_bss_99C[0][block]]);
            Hu3DModelTPLvlSet(work->models[lbl_1_bss_99C[1][block]+12].modelId, lbl_1_bss_19C.tpLvl[lbl_1_bss_99C[1][block]]);
            if(work->mode[2] == 2) {
                omVibrate(work->chr[0].no, 12, 12, 0);
                omVibrate(work->chr[1].no, 12, 12, 0);
                if(height != 0) {
                    pos = work->models[36].pos;
                    pos.y = (lbl_1_bss_C[0].hookPos.y-60.0f)+(height*100);
                    pos.z = lbl_1_bss_C[0].hookPos.z-110.0f;
                    fn_1_1980(&pos);
                    pos.x += -50.0f;
                    fn_1_1980(&pos);
                    pos.x += 100.0f;
                    fn_1_1980(&pos);
                    pos = work->models[37].pos;
                    pos.y = (lbl_1_bss_C[1].hookPos.y-60.0f)+(height*100);
                    pos.z = lbl_1_bss_C[1].hookPos.z-110.0f;
                    fn_1_1980(&pos);
                    pos.x += -50.0f;
                    fn_1_1980(&pos);
                    pos.x += 100.0f;
                    fn_1_1980(&pos);
                    fn_1_2460(height+1);
                } else {
                    fn_1_2460(1);
                }
                pl = &work->player[0];
                pl->speed = 0.0f;
                pl = &work->player[1];
                pl->speed = 0.0f;
                lbl_1_bss_C[0].mode = 1;
                lbl_1_bss_C[1].mode = 1;
            }
            break;

        case 2:
            lbl_1_bss_C[0].scale.y -= 0.016f;
            lbl_1_bss_C[1].scale.y -= 0.016f;
            if(lbl_1_bss_C[0].scale.y <= 0.92f) {
                work->mode[2]++;
            }
            Hu3DModelScaleSetV(work->models[36].modelId, &lbl_1_bss_C[0].scale);
            Hu3DModelScaleSetV(work->models[37].modelId, &lbl_1_bss_C[1].scale);
            break;

        case 3:
            lbl_1_bss_C[0].scale.y += 0.016f;
            lbl_1_bss_C[1].scale.y += 0.016f;
            if(lbl_1_bss_C[0].scale.y >= 1.0f) {
                lbl_1_bss_19C.dropSpeed = 0.0f;
                work->mode[2] = 0;
                pl = &work->player[0];
                pl->speed = 1.0f;
                pl = &work->player[1];
                pl->speed = 1.0f;
                lbl_1_bss_C[0].mode = 1;
                lbl_1_bss_C[1].mode = 1;
                result = 1;
            }
            Hu3DModelScaleSetV(work->models[36].modelId, &lbl_1_bss_C[0].scale);
            Hu3DModelScaleSetV(work->models[37].modelId, &lbl_1_bss_C[1].scale);
            break;
    }
    return result;
}

/* asm 2820-3045, 268 insns. The loser shrinks away and drops their blocks. */
s16 fn_1_5794(M545_WORK *work, s16 player)
{
    HuVecF pos;
    float div;
    s16 j;
    s16 result;

    result = 0;
    div = 10.0f;
    lbl_1_bss_C[player].mode = 1;
    lbl_1_bss_C[player].scale.y -= 1.0f/div;
    if(lbl_1_bss_C[player].scale.y <= 0.1f) {
        lbl_1_bss_C[player].scale.x = 0.1f;
        lbl_1_bss_C[player].scale.y = 0.1f;
        lbl_1_bss_C[player].scale.z = 0.1f;
        result = 1;
    }
    Hu3DModelScaleSetV(work->models[player+36].modelId, &lbl_1_bss_C[player].scale);
    if(result == 1) {
        pos = work->models[player+36].pos;
        pos.z = lbl_1_bss_C[player].hookPos.z-40.0f;
        fn_1_1980(&pos);
        pos.x += -50.0f;
        fn_1_1980(&pos);
        pos.x += 100.0f;
        fn_1_1980(&pos);
        lbl_1_bss_C[player].mode = 3;
        fn_1_24D8(9, 127, (player*32)+48);
        for(j=0; j<lbl_1_bss_C[player].height; j++) {
            lbl_1_bss_8D8[lbl_1_bss_99C[player][j]].x = lbl_1_bss_C[player].hookPos.x+lbl_1_bss_8D8[lbl_1_bss_99C[player][j]].x;
            lbl_1_bss_8D8[lbl_1_bss_99C[player][j]].y = 150.0f+(100.0f*j);
            lbl_1_bss_8D8[lbl_1_bss_99C[player][j]].z = lbl_1_bss_C[player].hookPos.z+lbl_1_bss_8D8[lbl_1_bss_99C[player][j]].z;
        }
    }
    return result;
}

/* asm 3048-3592, 627 insns. The winner throws their tower up and catches it. */
s16 fn_1_5BC4(M545_WORK *work, s16 player)
{
    float unk8;
    float a;
    float b;
    float c;
    M545_PLAYER *pl;
    s16 j;
    s16 result;

    result = 0;
    unk8 = 50.0f;
    switch(work->mode[3]) {
        case 0:
            lbl_1_bss_19C.dropSpeed = 35.0f;
            pl = &work->player[player];
            pl->shiftMode = 1;
            pl->shiftMotNo = 3;
            pl->shiftTime = 0.0f;
            pl->shiftSpeed = 10.0f;
            pl->shiftAttr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            lbl_1_bss_C[player].mode = 2;
            for(j=0; j<lbl_1_bss_C[player].height; j++) {
                lbl_1_bss_8D8[lbl_1_bss_99C[player][j]].x = lbl_1_bss_C[player].hookPos.x+lbl_1_bss_8D8[lbl_1_bss_99C[player][j]].x;
                lbl_1_bss_8D8[lbl_1_bss_99C[player][j]].y += 10.0f;
                lbl_1_bss_8D8[lbl_1_bss_99C[player][j]].z = lbl_1_bss_C[player].hookPos.z+lbl_1_bss_8D8[lbl_1_bss_99C[player][j]].z;
            }
            fn_1_2460(player+10);
            work->mode[3]++;
            break;

        case 1:
            pl = &work->player[player];
            if(pl->shiftMode == 0) {
                pl->motNoCur = pl->motNo = 3;
                pl->speed = 0.0f;
                lbl_1_bss_C[player].mode = 3;
                for(j=0; j<lbl_1_bss_C[player].height; j++) {
                    lbl_1_bss_8D8[lbl_1_bss_99C[player][j]].y = lbl_1_bss_C[player].hookPos.y+lbl_1_bss_8D8[lbl_1_bss_99C[player][j]].y;
                }
                work->mode[3]++;
            }
            break;

        case 3:
            pl = &work->player[player];
            pl->speed = 1.0f;
            pl->shiftMode = 1;
            pl->shiftMotNo = 0;
            pl->shiftTime = 0.0f;
            pl->shiftSpeed = 10.0f;
            pl->shiftAttr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            work->mode[3]++;
            break;

        case 4:
            pl = &work->player[player];
            if(pl->shiftMode == 0) {
                pl = &work->player[player];
                pl->motNo = 0;
                pl->attr = HU3D_MOTATTR_LOOP;
                result = 1;
            }
            break;
    }
    if(work->mode[3] == 2) {
        for(j=0; j<lbl_1_bss_C[player].height; j++) {
            lbl_1_bss_8D8[lbl_1_bss_99C[player][j]].y += lbl_1_bss_19C.dropSpeed;
            a = 250.0f+(j*100);
            b = 1300.0f+(j*100);
            if(j != 0) {
                if(j%2) {
                    lbl_1_bss_8D8[lbl_1_bss_99C[player][j]].x += 4.0f+(3.0f*(j/2));
                } else {
                    lbl_1_bss_8D8[lbl_1_bss_99C[player][j]].x -= 4.0f+(3.0f*(j/2));
                }
            }
            c = M545_DIST(a, b);
            a = M545_DIST(a, lbl_1_bss_8D8[lbl_1_bss_99C[player][j]].y);
            if(c <= a) {
                lbl_1_bss_8D8[lbl_1_bss_99C[player][j]].y = b;
                work->mode[3] = 3;
            }
            if((lbl_1_bss_19C.tpLvl[lbl_1_bss_99C[player][j]] -= 0.034f) <= 0.0f) {
                lbl_1_bss_19C.tpLvl[lbl_1_bss_99C[player][j]] = 0.0f;
            }
            Hu3DModelTPLvlSet(work->models[lbl_1_bss_99C[player][j]+12].modelId, lbl_1_bss_19C.tpLvl[lbl_1_bss_99C[player][j]]);
        }
        lbl_1_bss_19C.dropSpeed -= 0.4f;
    }
    return result;
}

/* asm 3595-3643, 54 insns. The sway speeds up with the stack. */
void fn_1_6590(M545_WORK *work)
{
    switch(lbl_1_bss_C[0].height) {
        case 2:
            fn_1_6668(work, 0.7f);
            break;

        case 3:
            fn_1_6668(work, 0.8f);
            break;

        case 4:
            fn_1_6668(work, 0.9f);
            break;

        case 5:
            fn_1_6668(work, 1.0f);
            break;

        case 6:
            fn_1_6668(work, 1.1f);
            break;
    }
}

/* asm 3646-3822, 189 insns. Start the duellists swaying, then keep the towers swinging at speed. */
void fn_1_6668(M545_WORK *work, float speed)
{
    M545_PLAYER *pl;
    s16 i;
    s16 j;

    switch(lbl_1_bss_19C.swingMode) {
        case 0:
            for(i=0; i<2; i++) {
                pl = &work->player[i];
                pl->shiftMode = 1;
                pl->shiftMotNo = 2;
                pl->shiftTime = 0.0f;
                pl->shiftSpeed = 14.0f;
                pl->shiftAttr = 0;
                pl->attrReset = HU3D_MOTATTR_LOOP;
                lbl_1_bss_C[i].mode = 1;
                for(j=0; j<6; j++) {
                    lbl_1_bss_C[i].angle[j] = (30.0f*j)+(180.0f*i);
                }
            }
            lbl_1_bss_19C.swingMode++;
            break;

        case 1:
            for(i=0; i<2; i++) {
                pl = &work->player[i];
                if(pl->shiftMode == 0) {
                    pl = &work->player[i];
                    pl->motNo = 2;
                    pl->speed = speed;
                    pl->time = 7.0f*i;
                    pl->attr = HU3D_MOTATTR_LOOP;
                    lbl_1_bss_19C.swingMode = 2;
                }
                lbl_1_bss_C[i].mode = 1;
            }
            break;

        case 2:
            for(i=0; i<2; i++) {
                pl = &work->player[i];
                pl->speed = speed;
                lbl_1_bss_C[i].mode = 1;
                fn_1_6BC4(work, i, pl->speed);
            }
            break;
    }
}

/* asm 3825-3948, 154 insns. Unreferenced: fan a stack out along an angle. */
void fn_1_695C(M545_WORK *work, s16 player, float angle)
{
    HuVecF pos;
    M545_MODEL *mdl;
    s16 j;

    angle += 90.0f;
    for(j=0; j<lbl_1_bss_C[player].height; j++) {
        mdl = &work->models[lbl_1_bss_99C[player][j]];
        pos = mdl->pos;
        pos.x = 100.0*(j*cos(1.5707963267948966));
        pos.y = 100.0*(j*sin(1.5707963267948966));
        mdl->pos.x = 100.0*(j*cos((M_PI*angle)/180.0));
        mdl->pos.y = 100.0*(j*sin((M_PI*angle)/180.0));
        PSVECSubtract(&mdl->pos, &pos, &pos);
    }
}

/* asm 3951-4034, 95 insns. Swing a stack: each block's sideways offset, then advance the angles. */
void fn_1_6BC4(M545_WORK *work, s16 player, float speed)
{
    s16 j;

    for(j=0; j<lbl_1_bss_C[player].height; j++) {
        lbl_1_bss_8D8[lbl_1_bss_99C[player][j]].x = 1.5*((float)j*sin((M_PI*lbl_1_bss_C[player].angle[j])/180.0));
    }
    for(j=0; j<6; j++) {
        lbl_1_bss_C[player].angle[j] += 20.0f*speed;
    }
}

/* asm 4037-4217, 234 insns. The opening camera: pull back and tilt over 100 frames. */
s32 fn_1_6D40(M545_WORK *work)
{
    float a;
    float b;
    float c;
    float frames;
    s32 result;

    result = 0;
    frames = 100.0f;
    a = 430.0f;
    b = 250.0f;
    c = (b-a)/frames;
    lbl_1_bss_8->center.y += c;
    c = M545_DIST(a, b);
    a = M545_DIST(a, lbl_1_bss_8->center.y);
    if(c <= a) {
        lbl_1_bss_8->center.y = b;
    }
    a = 1400.0f;
    b = 800.0f;
    c = (b-a)/frames;
    lbl_1_bss_8->zoom += c;
    c = M545_DIST(a, b);
    a = M545_DIST(a, lbl_1_bss_8->zoom);
    if(c <= a) {
        lbl_1_bss_8->zoom = b;
    }
    a = -20.0f;
    b = 0.0f;
    c = (b-a)/frames;
    lbl_1_bss_8->rot.x += c;
    c = M545_DIST(a, b);
    a = M545_DIST(a, lbl_1_bss_8->rot.x);
    if(c <= a) {
        lbl_1_bss_8->rot.x = b;
        result = 1;
    }
    return result;
}

/* asm 4220-4490, 337 insns. Pre-winner: wait, the winner's lift, then the camera onto the winner. */
s32 fn_1_70E8(M545_WORK *work)
{
    float a;
    float b;
    float c;
    float frames;
    s16 wait;
    s32 result;

    result = 0;
    frames = 30.0f;
    switch(work->mode[0]) {
        case 0:
            if(lbl_1_bss_19C.winner == -1) {
                wait = 180;
            } else {
                wait = 60;
            }
            if(lbl_1_bss_19C.endTimer++ > wait) {
                work->mode[0]++;
            }
            break;

        case 1:
            if(lbl_1_bss_19C.winner == -1) {
                work->mode[0] = 999;
            } else if(fn_1_5BC4(work, lbl_1_bss_19C.winner)) {
                work->mode[0]++;
                lbl_1_bss_19C.camCenterY = lbl_1_bss_8->center.y;
                lbl_1_bss_19C.camZoom = lbl_1_bss_8->zoom;
            }
            break;

        case 2:
            a = lbl_1_bss_19C.camCenterY;
            b = 250.0f;
            c = (b-a)/frames;
            lbl_1_bss_8->center.y += c;
            c = M545_DIST(a, b);
            a = M545_DIST(a, lbl_1_bss_8->center.y);
            if(c <= a) {
                lbl_1_bss_8->center.y = b;
            }
            a = 0.0f;
            b = -150.0f+(300.0f*lbl_1_bss_19C.winner);
            c = (b-a)/frames;
            lbl_1_bss_8->center.x += c;
            c = M545_DIST(a, b);
            a = M545_DIST(a, lbl_1_bss_8->center.x);
            if(c <= a) {
                lbl_1_bss_8->center.x = b;
                work->mode[0]++;
                result = 1;
            }
            a = lbl_1_bss_19C.camZoom;
            b = 550.0f;
            c = (b-a)/frames;
            lbl_1_bss_8->zoom += c;
            c = M545_DIST(a, b);
            a = M545_DIST(a, lbl_1_bss_8->zoom);
            if(c <= a) {
                lbl_1_bss_8->zoom = b;
            }
            break;

        case 3:
            work->mode[0] = 999;
            work->mode[1] = 0;
            result = 1;
            break;

        default:
            result = 1;
            break;
    }
    return result;
}

/* asm 4493-4604, 112 insns. A computer duellist's window: press every button three times, or none. */
void fn_1_762C(M545_WORK *work, s16 player)
{
    s32 roll;
    s16 dif;
    s16 h;

    dif = work->chr[player].dif-1;
    roll = frandmod(101);
    h = lbl_1_bss_C[player].height;
    if(h >= 6) {
        lbl_1_bss_C[player].missCnt++;
    }
    if(dif == 0 && h >= 3 && lbl_1_bss_980[h].time < 60) {
        roll = 101;
    }
    if(lbl_1_data_2D8[dif][lbl_1_bss_C[player].height-1] >= roll && lbl_1_bss_C[player].missCnt < 20) {
        for(h=0; h<=5; h++) {
            lbl_1_bss_C[player].press[h] = 3;
        }
    } else {
        for(h=0; h<=5; h++) {
            lbl_1_bss_C[player].press[h] = 0;
        }
    }
}
