/*
 * The types and symbols m570.c and player.c both need. The original compiles
 * the two as separate translation units (upstream's configure.py declares them
 * that way), and player.c calls six functions and reads two globals out of
 * m570.c, so those cannot be static.
 */
#ifndef M570_H
#define M570_H

#include "game/object.h"
#include "game/hu3d.h"
#include "humath.h"

/*
 * The minigame framework, in REL/mgframe.h -- the camera, flow, timer and
 * vector block every overlay compiles in. It is pulled in here rather than in
 * m570.c because player.c needs its types and four of its symbols too. Those
 * four are the ones this overlay makes external; everything else stays static.
 * The debug camera prints nothing here: the original object carries no format
 * strings for it, so MGF_DEBUG_READOUT is deliberately not defined.
 */
#define MGF_LINK_PLAYERCONFSET
#define MGF_LINK_VECAPPROACH
#define MGF_LINK_ANGLEAPPROACH
#define MGF_LINK_OBJMAN
#define MGF_S_DECL
#include "REL/mgframe.h"

/*
 * 0x54 bytes, allocated per player and memset to zero before anything is
 * written into it. It opens with the framework's player header -- what
 * MgPlayerConfSet fills in, and where m524dll's player work also starts.
 */
typedef struct M570Player_s {
    MGF_PLAYER_HEAD;           /* 0x00..0x28, what MgPlayerConfSet fills in */
    /* 0x2C */ OMOBJ *obj;
    /* 0x30 */ int unk30;
    /* 0x34 */ s16 sideNo;     /* 0 for the solo player, 1..3 for the chasers */
    /* 0x36 */ s16 motNo;
    /* 0x38 */ HuVecF targetPos;
    /* 0x44 */ int unk44;
    /* 0x48 */ int caughtF;
    /* 0x4C */ s16 handNo;
    /* 0x4E */ s16 unk4E;
    /* 0x50 */ int unk50;
} M570_PLAYER;                 /* 0x54 */

/* m570.c */
extern OMOBJMAN *objman;
extern s16 WinGrp;
HU3DPARMANID M570ParManCreate(HuVecF *pos);
s16 M570PanGet(HuVecF *pos);
void M570SePlay(HuVecF *pos, s16 seId);

/* player.c */
extern M570_PLAYER *ChaserObj[3];
extern M570_PLAYER *SoloPlayer;
extern M570_PLAYER *PlayerObj[4];
void M570PlayerCreate(void);
void M570PlayerMotionSet(M570_PLAYER *player, s16 motNo);
void M570PlayerRoundStart(void);
void M570PlayerIntroSet(void);
void M570PlayerWinPose(void);
void M570PlayerRoundEnd(void);
void M570PlayerScore(void);
void M570PlayerWinSet(void);
BOOL M570PlayerCaughtCheck(void);
void M570PlayerStageSet(void);
void M570StageMotionSet(s16 no);
void M570CrowdCreate(void);
void M570CrowdIdleSet(void);
void M570CrowdReactSet(int no);

#endif
