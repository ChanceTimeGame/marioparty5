#ifndef M569DLL_H
#define M569DLL_H

/*
 * m569dll (overlay #80): types and prototypes shared by its five translation
 * units (m569 player kuribo block score).
 *
 * Offsets are GameCube ones from build/mp5-asm/m569dll. No upstream names exist,
 * so functions keep reference addresses and globals keep lbl_1_* labels.
 */

#include "dolphin/types.h"
#include "game/object.h"
#include "game/hu3d.h"
#include "math.h"
#include "humath.h"

#include "game/mg/seqman.h"
#include "game/mg/actman.h"
#include "game/mg/score.h"
#include "game/hu3d.h"

/*
 * The minigame framework (REL/mgframe.h), compiled into m569.c as m523dll and
 * m564dll do. player/kuribo call MgPlayerConfSet (fn_1_32AC), MgVecApproach
 * (fn_1_3378), MgAngleApproach (fn_1_349C) and MgVecOrbit (fn_1_360C), and all
 * four other units read objman (lbl_1_bss_D4), so those five are external.
 * Call them by their framework names: map.txt renames every framework symbol
 * to its reference label (fn_1_1148 MgObjManInit .. fn_1_3900 MgPlaneCrossGet;
 * DebugCameraStart = lbl_1_bss_88, MgMusicId = lbl_1_bss_D0, objman =
 * lbl_1_bss_D4). m569's object carries no debug-camera format strings, so
 * MGF_DEBUG_READOUT stays undefined.
 */
#define MGF_LINK_PLAYERCONFSET
#define MGF_LINK_VECAPPROACH
#define MGF_LINK_ANGLEAPPROACH
#define MGF_LINK_VECORBIT
#define MGF_LINK_OBJMAN
#define MGF_S_DECL
#include "REL/mgframe.h"


/* lbl_1_bss_D4: m569.c defines it (hand-declared .bss, as m564 does). */
extern OMOBJMAN *objman;

/*
 * One team's round result: lbl_1_bss_D8[2], indexed by the round (fn_1_9C4:
 * 0 for game phase 3..6, 1 for 7..11). player fn_1_4D74 memsets a row
 * (0x10 bytes) and sets the three player numbers to -1.
 */
typedef struct M569Round_s {
    /* 0x00 */ int unk000;            /* fn_1_86C4's result (block); > 0 wakes the kuribo (fn_1_9C4 0xC38) */
    /* 0x04 */ int unk004[3];         /* player numbers, -1 = empty (fn_1_9C4 0xA6C) */
} M569_ROUND; /* size 0x10 (GC) */

/*
 * The player work (fork P): obj->data of the four player objects in
 * lbl_1_bss_F8. HuMemDirectMallocNum(HEAP_HEAP, 0x70) in fn_1_3A48, not
 * memset; MgPlayerConfSet fills the framework head.
 */
typedef struct M569Player_s {
    MGF_PLAYER_HEAD;                  /* 0x00..0x2B; mode (0x28, fn_1_4EB4/4EE4): 0 idle, 1 walk in, 2 play, 3 walk (->0), 4 walk (->5), 5 turn to unk05C.y */
    /* 0x2C */ int unk02C;            /* slot: 0 the solo player, 1..3 the team (fn_1_4D74 0x4E30/0x4E84); score fn_1_8ADC 0x8B8C indexes lbl_1_data_3C0[4] */
    /* 0x30 */ int unk030;            /* current motion: row of lbl_1_data_170 / obj->mtnId; -1 before the first (fn_1_4B8C) */
    /* 0x34 */ u8 pad034[2];          /* not accessed in player.c */
    /* 0x36 */ HU3DMOTID unk036[8];   /* the reflection model's (obj->mdlId[1]) joint motions, one per lbl_1_data_170 row */
    /* 0x46 */ s16 unk046;            /* block index 0..2 (lbl_1_data_32C, fn_1_848C/839C) the player stands under */
    /* 0x48 */ int unk048;            /* play sub-state (fn_1_454C): 0 idle, 1 turning back, 2 hitting, 4 step left, 5 step right */
    /* 0x4C */ int unk04C;            /* coins: player fn_1_454C 0x45C4 stores fn_1_86C4(); score fn_1_8ADC 0x8D20 stores it to GwPlayer[no].mgCoin; m569 fn_1_E20 0xEC0: nonzero -> fn_1_4B8C(obj, 4) */
    /* 0x50 */ HuVecF unk050;         /* walk target */
    /* 0x5C */ HuVecF unk05C;         /* facing: MgVecApproach's rot; .y the target yaw */
    /* 0x68 */ s16 unk068;            /* COM: block to hit, -1 none */
    /* 0x6A */ s16 unk06A;            /* COM: frames before hitting */
    /* 0x6C */ int unk06C;            /* 1 (fn_1_3A48): motions 4..7 spawn the fn_1_49DC SE object; m569 fn_1_E20 0xEF8/0xF04 rewrites it */
} M569_PLAYER; /* size 0x70 (GC) */

/*
 * The big kuribo's work (obj->data of the fn_1_582C object; lbl_1_bss_C).
 * OWNED BY FORK K. 0x40 bytes (fn_1_582C's HuMemDirectMallocNum literal).
 * Its object has mdlcnt 1 but uses mdlId[0] (the kuribo) AND mdlId[1] (a
 * y-mirrored reflection model): see the hazard note at fn_1_582C.
 */
typedef struct M569Kuribo_s {
    /* 0x00 */ int unk000;            /* state: 0 entering, 1 idle (fn_1_6418 0x69B0), 2 stomp requested (fn_1_6D9C), 3 stomping (fn_1_6A48) */
    /* 0x04 */ HuVecF unk004;         /* position (omSetTra, MgVecApproach pos) */
    /* 0x10 */ HuVecF unk010;         /* rotation (omSetRot, MgVecApproach rot) */
    /* 0x1C */ u8 pad01C[0x10];
    /* 0x2C */ int unk02C;            /* motion number now set (fn_1_5A9C 0x5AF0), 0..2 */
    /* 0x30 */ float unk030;          /* last frame's motion time (fn_1_5C54 0x5D38) */
    /* 0x34 */ int unk034[3];         /* reflection model's motions, extsh'd (fn_1_582C 0x599C stwx) */
} M569_KURIBO; /* size 0x40 (GC) */

/*
 * One of the 17 background kuribo (lbl_1_bss_108[i], obj->data of a
 * fn_1_6DB4 object). OWNED BY FORK K. 0x40 bytes malloc'd, 0x24 used.
 */
typedef struct M569Crowd_s {
    /* 0x00 */ int unk000;            /* 0 still, 1 bob for 90 frames (fn_1_735C), 2 bob until stopped (fn_1_741C) */
    /* 0x04 */ int unk004;            /* bob phase in degrees, += 8 per frame, used % 180 (fn_1_702C 0x7064) */
    /* 0x08 */ int unk008;            /* nonzero: bob in x, else in y (frandmod(2)) */
    /* 0x0C */ HuVecF unk00C;         /* home position (lbl_1_data_250[i]) */
    /* 0x18 */ HuVecF unk018;         /* bob offset; z unused (fn_1_702C 0x72F4) */
    /* 0x24 */ u8 pad024[0x1C];
} M569_CROWD; /* size 0x40 (GC) */

/*
 * One of the three dice blocks (obj->data of the objects fn_1_7DC0 creates;
 * lbl_1_bss_158[3] holds the three works). fn_1_7DC0's HuMemDirectMallocNum
 * literal is 0x30. Blocks 0 and 2 are number dice (type 0), block 1 is the
 * operator die (type 1); fn_1_86C4 combines their faces.
 */
typedef struct M569Block_s {
    /* 0x00 */ u8 unk000;             /* type: 0 number die, 1 operator die (lbl_1_data_350); indexes lbl_1_rodata_198 and lbl_1_data_320 rows */
    /* 0x01 */ u8 pad001[3];
    /* 0x04 */ int unk004;            /* mode, fn_1_77D8's switch: 0 intro spin/grow, 1 idle (hittable), 2 hit, 3 fade + particle, 4 shown, 5 fade out, 6 kill */
    /* 0x08 */ HuVecF unk008;         /* position (lbl_1_data_32C[i]); y bobs around 270 in mode 1 */
    /* 0x14 */ s16 unk014;            /* rotation y, +25 per frame in mode 0 up to 1080 (lha/sth, fn_1_75F8) */
    /* 0x16 */ u8 pad016[2];
    /* 0x18 */ float unk018;          /* uniform scale */
    /* 0x1C */ float unk01C;          /* bob angle, degrees (mode 1: +4, wraps at 360) */
    /* 0x20 */ u8 unk020[6];          /* face sequence, copied from lbl_1_data_320[unk000] */
    /* 0x26 */ u8 unk026;             /* current face index 0..5 (frandmod(6), wraps at 6) */
    /* 0x27 */ u8 unk027;             /* face change delay, 0..2 */
    /* 0x28 */ int unk028;            /* timer */
    /* 0x2C */ HU3DPARMANID unk02C;   /* hit particle manager, -1 = none */
    /* 0x2E */ u8 pad02E[2];
} M569_BLOCK; /* size 0x30 (GC) */

/*
 * score.c: one round's result counter (lbl_1_bss_56A8[2], obj->data of the
 * fn_1_8978 object fn_1_87D4 creates; HuMemDirectMallocNum 0x14 at 0x88BC).
 */
typedef struct M569ScoreDisp_s {
    /* 0x00 */ MGSCORE *unk000;       /* MgScoreCreate result (0x8908 stw) */
    /* 0x04 */ int unk004;            /* round: 0 -> SE 0x90D, else 0x90E (fn_1_8978 0x8A3C) */
    /* 0x08 */ int unk008;            /* final value (fn_1_8A74 stw; MgScoreValueSet at 0x8A20) */
    /* 0x0C */ int unk00C;            /* mode 0 idle, 1 start, 2 rolling, 3 done (fn_1_8AAC) */
    /* 0x10 */ int unk010;            /* roll timer, 90 frames (0x89D0) */
} M569_SCOREDISP; /* size 0x14 (GC) */

/*
 * score.c: one player's coin drop (lbl_1_bss_56B0[4], obj->data of the
 * fn_1_8D78 object fn_1_8ADC creates; HuMemDirectMallocNum 0x1C at 0x8B30).
 */
typedef struct M569CoinDrop_s {
    /* 0x00 */ HU3DMODELID unk000;    /* model 0x7C0012 (sth 0x8CAC) */
    /* 0x02 */ HU3DPARMANID unk002;   /* fn_1_8F38 particle, -1 = none (lha/sth 0x8E48) */
    /* 0x04 */ HuVecF unk004;         /* position (lbl_1_data_3C0[player->unk02C], y 700 -> 350) */
    /* 0x10 */ int unk010;            /* mode 0 fall, 1 wait/open, 2 done (fn_1_8D78) */
    /* 0x14 */ int unk014;            /* coins: player work unk04C (0x8D00) */
    /* 0x18 */ s16 unk018;            /* player number (lha player+0x00, sth 0x8C94); indexes lbl_1_bss_F8 at 0x8E84 */
} M569_COINDROP; /* size 0x1C (GC) */

/* score.c: lbl_1_bss_27BC, the confetti hook model (0xC). */
typedef struct M569ConfettiMan_s {
    /* 0x00 */ HU3DMODELID unk000;    /* model 0x7C0013 (sth 0x92C0) */
    /* 0x02 */ HU3DMODELID unk002;    /* Hu3DHookFuncCreate(fn_1_9014) (sth 0x92EC) */
    /* 0x04 */ float unk004;          /* floor y, 0.1 (stfs 0x9318; lfs fn_1_91A0) */
    /* 0x08 */ int unk008;            /* live-piece count, only ever incremented (fn_1_9384 0x9418) */
} M569_CONFETTIMAN; /* size 0xC (GC) */

/* score.c: lbl_1_bss_27C8[200], one confetti piece (stride 0x3C). */
typedef struct M569Confetti_s {
    /* 0x00 */ int unk000;            /* active */
    /* 0x04 */ int unk004;            /* landed (fn_1_91A0 0x9268) */
    /* 0x08 */ HuVecF unk008;         /* position */
    /* 0x14 */ HuVecF unk014;         /* velocity */
    /* 0x20 */ HuVecF unk020;         /* rotation (degrees) */
    /* 0x2C */ HuVecF unk02C;         /* rotation speed */
    /* 0x38 */ GXColor unk038;        /* lbl_1_data_3F0[frandmod(4)] (lbz/stb 0x9800); fn_1_9014 copies rgb into every material */
} M569_CONFETTI; /* size 0x3C (GC) */

/* score.c: lbl_1_bss_17C[144], one flying coin (stride 0x44). */
typedef struct M569Coin_s {
    /* 0x00 */ int unk000;            /* active */
    /* 0x04 */ int unk004;            /* 1 for the first coin: drawn during its delay (fn_1_986C 0x98E0) */
    /* 0x08 */ int unk008;            /* 0 (fn_1_9B2C); nonzero skips the update (fn_1_9A20 0x9A6C) -- never set */
    /* 0x0C */ HuVecF unk00C;         /* position */
    /* 0x18 */ HuVecF unk018;         /* velocity (y -= 1.96 per frame) */
    /* 0x24 */ HuVecF unk024;         /* rotation (degrees) */
    /* 0x30 */ HuVecF unk030;         /* rotation speed (y 15) */
    /* 0x3C */ float unk03C;          /* landing y: CharModelHeightGet(player->charNo) */
    /* 0x40 */ int unk040;            /* start delay, 4 * n + 15 frames */
} M569_COIN; /* size 0x44 (GC) */

/* --- m569.c .bss/.data read by the other units --- */
extern M569_KURIBO *lbl_1_bss_C;      /* the kuribo fn_1_582C returns */
extern int lbl_1_bss_14;              /* game phase: 0 init, 1/2 fade-in camera, 3..12 main (fn_1_9C4) */
extern MGF_CAMERAVIEW lbl_1_bss_34;   /* live camera view (Hu3DCameraPosGet + angle derivation) */
extern M569_ROUND lbl_1_bss_D8[2];
extern OMOBJ **lbl_1_bss_F8;          /* the four player objects (omGetGroupMemberListEx) */
extern HuVecF lbl_1_data_D8[5];

/* --- block.c .data read by player.c --- */
extern HuVecF lbl_1_data_32C[3];     /* the three block positions */

/* --- m569.c --- */
void ObjectSetup(void);
void fn_1_110(s16 mode, s16 frameNo);
void fn_1_820(s16 mode, s16 frameNo);
void fn_1_94C(s16 mode, s16 frameNo);
void fn_1_9C4(s16 mode, s16 frameNo);
void fn_1_DD0(s16 mode, s16 frameNo);
void fn_1_E20(s16 mode, s16 frameNo);
void fn_1_FA8(s16 mode, s16 frameNo);
void fn_1_1010(s16 mode, s16 frameNo);
s16 fn_1_1014(HuVecF *pos);
void fn_1_109C(HuVecF *pos, s16 seNo);
/* fn_1_1148..fn_1_3900 (and MgCameraMoveEntry/MgFlowSet/MgFlowNext): the
 * framework, declared by MGF_S_DECL above under its own names. */

/* --- player.c --- */
void fn_1_3A48(void);
BOOL fn_1_3D68(OMOBJ *obj);
void fn_1_3E68(OMOBJ *obj);
void fn_1_3F50(OMOBJ *obj);
BOOL fn_1_433C(M569_PLAYER *player);
BOOL fn_1_4404(M569_PLAYER *player);
void fn_1_454C(OMOBJ *obj);
void fn_1_49DC(OMOBJ *obj);
void fn_1_4B8C(OMOBJ *obj, int motNo);
void fn_1_4D74(void);
void fn_1_4EB4(int no, int mode);
int fn_1_4EE4(int no);
void fn_1_4F14(int no);
void fn_1_5138(int no);
void fn_1_52F8(int no);
void fn_1_54A8(int round);

/* --- kuribo.c --- */
M569_KURIBO *fn_1_582C(void);
void fn_1_5A9C(OMOBJ *obj, int motNo);
void fn_1_5C54(OMOBJ *obj);
void fn_1_5D5C(OMOBJ *obj);
void fn_1_5F48(OMOBJ *obj);
void fn_1_60F0(OMOBJ *obj);
void fn_1_6418(OMOBJ *obj);
void fn_1_6A48(OMOBJ *obj);
void fn_1_6D9C(M569_KURIBO *work);
void fn_1_6DB4(void);
void fn_1_702C(OMOBJ *obj);
void fn_1_735C(void);
void fn_1_741C(void);
void fn_1_74B0(void);

/* --- block.c --- */
HU3DPARMANID fn_1_74E0(HuVecF *pos);
void fn_1_75F8(OMOBJ *obj);
void fn_1_77D8(OMOBJ *obj);
OMOBJ *fn_1_7DC0(u8 type, HuVecF *pos);
void fn_1_7F94(OMOBJ *obj);
void fn_1_80AC(void);
void fn_1_80FC(void);
void fn_1_833C(void);
void fn_1_839C(int no);
int fn_1_848C(int no);
int fn_1_84A8(void);
int fn_1_8544(void);
int fn_1_85C0(void);
void fn_1_8614(void);
int fn_1_86C4(void);

/* --- score.c --- */
void fn_1_87D4(void);
void fn_1_8978(OMOBJ *obj);
void fn_1_8A74(int round, int a1);
int fn_1_8AAC(int round);
void fn_1_8ADC(void);
void fn_1_8D78(OMOBJ *obj);
void fn_1_8F14(OMOBJ *obj);
HU3DPARMANID fn_1_8F38(HuVecF *pos);
void fn_1_9014(HU3DMODEL *model, Mtx *mtx);
void fn_1_91A0(void);
void fn_1_9290(void);
void fn_1_9384(HuVecF *pos, int num);
void fn_1_986C(HU3DMODEL *model, Mtx *mtx);
void fn_1_9A20(void);
void fn_1_9B2C(void);
void fn_1_9C38(HuVecF *pos, M569_PLAYER *player);

#endif
