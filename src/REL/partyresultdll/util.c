/*
 * partyresultdll util.c -- PORTED (hand-written, not a generated skeleton).
 * Reference: build/mp5-asm/partyresultdll/asm/REL/partyresultdll/util.s.
 *
 * Small helpers shared by result.c and stat.c: the team-name message of a character pair,
 * "wait for A unless every player is a COM", and "let the COMs page through a message".
 */

#include "REL/partyresultdll.h"

#include "game/pad.h"

#define PRES_TEAMNAME_NONE 0x8002D /* mess 8 #0x2D: no pair name */

/*
 * Team-name message index of a character pair, [lower charNo*10 + higher charNo] (retail indexes
 * it flat; rows of 10); -1 = no pair
 * (a character with itself). Same bytes as resultDll team.c TeamNoTbl.
 */
static s8 teamNoTbl[9*10] = {
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8,
    -1, -1, 9, 10, 11, 12, 13, 14, 15, 16,
    -1, -1, -1, 17, 18, 19, 20, 21, 22, 23,
    -1, -1, -1, -1, 24, 25, 26, 27, 28, 29,
    -1, -1, -1, -1, -1, 30, 31, 32, 33, 34,
    -1, -1, -1, -1, -1, -1, 35, 36, 37, 38,
    -1, -1, -1, -1, -1, -1, -1, 39, 40, 41,
    -1, -1, -1, -1, -1, -1, -1, -1, 42, 43,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, 44
};

/*
 * RETAIL BUG (transcribed): charNo1 == charNo2 == 9 passes the `> 9` guard and reads
 * teamNoTbl[99], past the 90-byte table (no playable character is 9; equal charNo 0..8 read
 * the -1 diagonal).
 */
u32 PResTeamNameMesGet(s16 charNo1, s16 charNo2)
{
    s32 teamNo;
    if(charNo1 > 9 || charNo2 > 9) {
        return PRES_TEAMNAME_NONE;
    }
    if(charNo1 < charNo2) {
        teamNo = teamNoTbl[(charNo1*10)+charNo2];
    } else {
        teamNo = teamNoTbl[(charNo2*10)+charNo1];
    }
    if(teamNo == -1) {
        return PRES_TEAMNAME_NONE;
    }
    return teamNo+0x80000;
}

/* Wait for A on pad 0; if every player is a COM, just sleep 30 frames. */
void PResBtnAWait(void)
{
    s16 i;
    for(i=0; i<GW_PLAYER_MAX; i++) {
        if(GwPlayerConf[i].type == GW_TYPE_MAN) {
            break;
        }
    }
    if(i == GW_PLAYER_MAX) {
        HuPrcSleep(30);
    } else {
        while(1) {
            if(HuPadBtnDown[0] & PAD_BUTTON_A) {
                break;
            }
            HuPrcVSleep();
        }
    }
}

/* If every player is a COM, auto-advance the message window (5 key presses). winId is unused. */
void PResComInputWait(HUWINID winId)
{
    s16 i;
    for(i=0; i<GW_PLAYER_MAX; i++) {
        if(GwPlayerConf[i].type == GW_TYPE_MAN) {
            return;
        }
    }
    HuWinComKeyWait(PAD_BUTTON_A, PAD_BUTTON_A, PAD_BUTTON_A, PAD_BUTTON_A, 30);
    HuWinComKeyWait(PAD_BUTTON_A, PAD_BUTTON_A, PAD_BUTTON_A, PAD_BUTTON_A, 30);
    HuWinComKeyWait(PAD_BUTTON_A, PAD_BUTTON_A, PAD_BUTTON_A, PAD_BUTTON_A, 30);
    HuWinComKeyWait(PAD_BUTTON_A, PAD_BUTTON_A, PAD_BUTTON_A, PAD_BUTTON_A, 30);
    HuWinComKeyWait(PAD_BUTTON_A, PAD_BUTTON_A, PAD_BUTTON_A, PAD_BUTTON_A, 30);
}
