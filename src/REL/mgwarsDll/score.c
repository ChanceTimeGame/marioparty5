/*
 * mgwarsDll score.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/mgwarsDll/asm/REL/mgwarsDll/score.s.
 */

#include "REL/mgwarsDll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "math.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_108 = 10.0f; /* 0x108 */
static const float lbl_1_rodata_10C = 6.0f; /* 0x10C */
static const float lbl_1_rodata_110 = 60.0f; /* 0x110 */
static const double lbl_1_rodata_118 = 3.141592653589793; /* 0x118 */
static const double lbl_1_rodata_120 = 0.5; /* 0x120 */
/* 0x128 lbl_1_rodata_128 = 4503601774854144: int->float conversion constant, compiler-generated */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x418 */ MGWARS_SCORE lbl_1_bss_418; /* fn_1_F068 memsets 0x34 bytes. HOST: MGWARS_SCOREPLAYER holds a pointer */

/* --- functions (reference order), .data placed before its first user --- */
/* 62 insns */
void fn_1_EF70(s32 playerNo, HuVec2f *pos)
{
    HuSprGrpPosSet(lbl_1_bss_418.player[playerNo].grpId, pos->x, pos->y);
    switch (playerNo) {
        case 0:
        case 1:
            MgScorePosSet(lbl_1_bss_418.player[playerNo].mgScore, pos->x - 10.0f, 6.0f + pos->y);
            break;
        case 2:
        case 3:
            MgScorePosSet(lbl_1_bss_418.player[playerNo].mgScore, pos->x - 10.0f, pos->y - 6.0f);
            break;
    }
}

/* 20 insns */
void fn_1_F068(void)
{
    memset(&lbl_1_bss_418, 0, sizeof(lbl_1_bss_418));
    HuPrcChildCreate(fn_1_F0B8, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 0x670 */ MGWARS_SCORELAYOUT lbl_1_data_670 = { /* one dtk object: positions (slwi 4 rows) + sprite files */
    { { { 100.0f, 130.0f }, { -220.0f, 130.0f } }, { { 480.0f, 130.0f }, { 800.0f, 130.0f } },
      { { 100.0f, 255.0f }, { -220.0f, 255.0f } }, { { 480.0f, 255.0f }, { 800.0f, 255.0f } } },
    { DATANUM(DATA_mgwars, 47), DATANUM(DATA_mgwars, 48), DATANUM(DATA_mgwars, 49), DATANUM(DATA_mgwars, 50), DATANUM(DATA_mgwars, 51), DATANUM(DATA_mgwars, 52), DATANUM(DATA_mgwars, 53), DATANUM(DATA_mgwars, 54), DATANUM(DATA_mgwars, 55), DATANUM(DATA_mgwars, 56), DATANUM(DATA_mgwars, 57), DATANUM(DATA_mgwars, 58), DATANUM(DATA_mgwars, 59), DATANUM(DATA_mgwars, 56), DATANUM(DATA_mgwars, 56) }
};
/* 0x6EC */ u32 lbl_1_data_6EC[4] = { DATANUM(DATA_mgwars, 43), DATANUM(DATA_mgwars, 44), DATANUM(DATA_mgwars, 45), DATANUM(DATA_mgwars, 46) };

/* 468 insns */
void fn_1_F0B8(void)
{
    MGWARS_SCORE *score;
    s32 i;
    s32 playerNo;
    s32 j;
    MGSCORE *mgScore;
    s32 value;
    HUSPRGRPID grpId;
    ANIMDATA *anim;
    MGSCORE *valueScore;
    float t;
    float t2;
    HuVec2f posIn;
    HuVec2f posOut;
    HUSPRGRPID valueGrpId;

    score = &lbl_1_bss_418;
    while (TRUE) {
        switch (lbl_1_bss_418.unk2) {
            case 0:
                for (playerNo = 0; playerNo < 4; playerNo++) {
                    grpId = HuSprGrpCreate(1);
                    score->player[playerNo].grpId = grpId;
                    mgScore = MgScoreCreate(MGCONST_ANM_scoreMedium, -1, TRUE);
                    score->player[playerNo].mgScore = mgScore;
                    MgScoreMaxDigitSet(mgScore, 2);
                    MgScoreDispOn(mgScore);
                    MgScoreColorSet(mgScore, 255, 216, 21);
                    anim = HuSprAnimRead(HuDataSelHeapReadNum(lbl_1_data_6EC[playerNo], HU_MEMNUM_OVL, HEAP_MODEL));
                    HuSprGrpMemberSet(grpId, 0, HuSprCreate(anim, 100, 0));
                    for (j = 0; j < 1; j++) {
                        HuSprAttrSet(grpId, j, HUSPR_ATTR_NOANIM);
                    }
                    HuSprGrpPosSet(lbl_1_bss_418.player[playerNo].grpId, lbl_1_data_670.pos[playerNo][1].x, lbl_1_data_670.pos[playerNo][1].y);
                    switch (playerNo) {
                        case 0:
                        case 1:
                            MgScorePosSet(lbl_1_bss_418.player[playerNo].mgScore, lbl_1_data_670.pos[playerNo][1].x - 10.0f, 6.0f + lbl_1_data_670.pos[playerNo][1].y);
                            break;
                        case 2:
                        case 3:
                            MgScorePosSet(lbl_1_bss_418.player[playerNo].mgScore, lbl_1_data_670.pos[playerNo][1].x - 10.0f, lbl_1_data_670.pos[playerNo][1].y - 6.0f);
                            break;
                    }
                }
                lbl_1_bss_418.unk3 = 2;
                lbl_1_bss_418.unk2 = 1;
                break;
            case 1:
                switch (score->unk3) {
                    case 1:
                        t = score->mode / 60.0f;
                        t = sin(M_PI * t / 2.0);
                        t = sin(M_PI * t / 2.0);
                        if (score->mode > 60) {
                            score->mode = 0;
                            score->unk3 = 2;
                            break;
                        }
                        for (i = 4; i--;) {
                            posIn.x = lbl_1_data_670.pos[i][0].x + t * (lbl_1_data_670.pos[i][1].x - lbl_1_data_670.pos[i][0].x);
                            posIn.y = lbl_1_data_670.pos[i][0].y + t * (lbl_1_data_670.pos[i][1].y - lbl_1_data_670.pos[i][0].y);
                            HuSprGrpPosSet(lbl_1_bss_418.player[i].grpId, posIn.x, posIn.y);
                            switch (i) {
                                case 0:
                                case 1:
                                    MgScorePosSet(lbl_1_bss_418.player[i].mgScore, posIn.x - 10.0f, 6.0f + posIn.y);
                                    break;
                                case 2:
                                case 3:
                                    MgScorePosSet(lbl_1_bss_418.player[i].mgScore, posIn.x - 10.0f, posIn.y - 6.0f);
                                    break;
                            }
                        }
                        score->mode++;
                        break;
                    case 0:
                        t2 = score->mode / 60.0f;
                        t2 = sin(M_PI * t2 / 2.0);
                        t2 = sin(M_PI * t2 / 2.0);
                        if (score->mode > 60) {
                            score->mode = 0;
                            score->unk3 = 2;
                            break;
                        }
                        for (i = 4; i--;) {
                            posOut.x = lbl_1_data_670.pos[i][1].x + t2 * (lbl_1_data_670.pos[i][0].x - lbl_1_data_670.pos[i][1].x);
                            posOut.y = lbl_1_data_670.pos[i][1].y + t2 * (lbl_1_data_670.pos[i][0].y - lbl_1_data_670.pos[i][1].y);
                            HuSprGrpPosSet(lbl_1_bss_418.player[i].grpId, posOut.x, posOut.y);
                            switch (i) {
                                case 0:
                                case 1:
                                    MgScorePosSet(lbl_1_bss_418.player[i].mgScore, posOut.x - 10.0f, 6.0f + posOut.y);
                                    break;
                                case 2:
                                case 3:
                                    MgScorePosSet(lbl_1_bss_418.player[i].mgScore, posOut.x - 10.0f, posOut.y - 6.0f);
                                    break;
                            }
                        }
                        score->mode++;
                        break;
                    case 2:
                        break;
                }
                for (i = 0; i < 4; i++) {
                    valueGrpId = score->player[i].grpId;
                    value = score->player[i].score;
                    if (value > 99) {
                        value = 99;
                    }
                    valueScore = score->player[i].mgScore;
                    MgScoreValueSet(valueScore, value);
                }
                break;
        }
        HuPrcVSleep();
    }
}

/* 8 insns */
void fn_1_F808(s32 playerNo)
{
    lbl_1_bss_418.player[playerNo].score++;
}

/* 8 insns */
void fn_1_F828(s32 playerNo)
{
    lbl_1_bss_418.player[playerNo].score--;
}

/* 6 insns */
void fn_1_F848(s32 playerNo, s32 score)
{
    lbl_1_bss_418.player[playerNo].score = score;
}

/* 9 insns */
void fn_1_F860(void)
{
    lbl_1_bss_418.unk3 = 0;
    lbl_1_bss_418.mode = 0;
}

/* 9 insns */
void fn_1_F884(void)
{
    lbl_1_bss_418.unk3 = 1;
    lbl_1_bss_418.mode = 0;
}

