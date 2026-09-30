#ifndef M564DLL_H
#define M564DLL_H

/*
 * m564dll (MG_TYPE_4P, overlay #75): types, globals and prototypes shared by its
 * four translation units (m564, player, bomb, com), in link order.
 *
 * Offsets are GameCube ones from build/mp5-asm/m564Dll. No upstream names exist,
 * so functions keep reference addresses and globals keep lbl_1_* labels; work-struct
 * fields are named by hex offset. Pointer-bearing structs are wider on the host:
 * allocate them with sizeof, never with the byte count in the assembly.
 */

#include "dolphin/types.h"
#include "game/object.h"
#include "game/hu3d.h"
#include "humath.h"
#include "game/mg/actman.h"
#include "game/charman.h"

/*
 * The minigame framework (REL/mgframe.h), compiled into m564.c as m523dll does.
 * player/bomb call MgPlayerConfSet (fn_1_36E0), MgVecApproach (fn_1_37AC) and
 * MgAngleApproach (fn_1_38D0) and read objman (lbl_1_bss_F8), so those are
 * external.
 */
#define MGF_LINK_PLAYERCONFSET
#define MGF_LINK_VECAPPROACH
#define MGF_LINK_ANGLEAPPROACH
#define MGF_LINK_VECORBIT
#define MGF_LINK_OBJMAN
#define MGF_S_DECL
#include "REL/mgframe.h"

/* m564.c defines it through its own .bss block (lbl_1_bss_F8). */
extern OMOBJMAN *objman;

/*
 * The player work: obj->data of the four player objects and lbl_1_bss_100[no].
 * 0x74 bytes (fn_1_3E7C's allocation literal); written sizeof(M564_PLAYER).
 * No field is unsigned: every s16 is lha + cmpwi, and 0x64/0x68 take fctiwz.
 */
typedef struct M564Player_s {
    MGF_PLAYER_HEAD;               /* 0x00..0x2B; mode (0x28) doubles as the "press A" request */
    /* 0x2C */ MGPLAYER *unk02C;   /* MgPlayerCreate */
    /* 0x30 */ char *unk030;       /* CharModelItemHookGet(charNo, 2, 0): bomb hold hook */
    /* 0x34 */ s32 unk034;         /* holding a bomb (== 0 tests only) */
    /* 0x38 */ s16 unk038;         /* held bomb, index into lbl_1_bss_1E8, -1 none */
    /* 0x3A */ s16 unk03A;         /* blast spin timer (cmpwi 0x46, xoris) */
    /* 0x3C */ s32 unk03C;         /* blast pending */
    /* 0x40 */ HuVecF unk040;      /* com steering target */
    /* 0x4C */ u8 unk04C[0xC];
    /* 0x58 */ s16 unk058;         /* com mode 0..4 */
    /* 0x5A */ s16 unk05A;
    /* 0x5C */ s16 unk05C;         /* com target bomb, -1 none */
    /* 0x5E */ s16 unk05E;         /* com target player, -1 none */
    /* 0x60 */ s16 unk060;         /* com mode timer */
    /* 0x62 */ u8 unk062[2];
    /* 0x64 */ s32 unk064;         /* pad stick x, for MgPlayerPadSet */
    /* 0x68 */ s32 unk068;         /* pad stick y */
    /* 0x6C */ s32 unk06C;         /* pad btnDown (0x100 = A) */
    /* 0x70 */ s32 unk070;         /* times blasted */
} M564_PLAYER;

/*
 * A bomb: obj->data of the 15 bomb objects (fn_1_76D8) and lbl_1_bss_1E8[i].
 * 0x5C bytes (fn_1_60E8 malloc + memset); written sizeof(M564_BOMB). No unsigned field.
 */
typedef struct M564Bomb_s {
    /* 0x00 */ MGACTOR *unk000;     /* MgActorCreate(&lbl_1_data_200, unk004) */
    /* 0x04 */ HU3DMODELID unk004;  /* bomb model 0x770010 */
    /* 0x06 */ HU3DMODELID unk006;  /* Hu3DModelLink(lbl_1_bss_118): shadow */
    /* 0x08 */ HU3DMOTID unk008[3]; /* motions lbl_1_data_220[3] */
    /* 0x0E */ s16 unk00E;          /* current motion slot, -1 = none (fn_1_74C4) */
    /* 0x10 */ s16 unk010;          /* bomb index 0..14 */
    /* 0x12 */ HU3DMODELID unk012;  /* Hu3DModelLink(lbl_1_bss_1E6): explosion, -1 */
    /* 0x14 */ s16 unk014;          /* chase kind 0/1/2 */
    /* 0x16 */ s16 unk016;          /* target player (fn_1_5FDC) */
    /* 0x18 */ s16 unk018;          /* spawn slot (fn_1_9810), -1 = none */
    /* 0x1A */ s16 unk01A;          /* holding player, -1 = none */
    /* 0x1C */ float unk01C;
    /* 0x20 */ s16 unk020;          /* state: 0 idle,1..7; 7 = exploded */
    /* 0x22 */ s16 unk022;          /* fuse timer */
    /* 0x24 */ s16 unk024;
    /* 0x26 */ s16 unk026;
    /* 0x28 */ float unk028;        /* speed */
    /* 0x2C */ s16 unk02C;          /* counter */
    /* 0x30 */ float unk030;
    /* 0x34 */ HuVecF unk034;       /* explosion position */
    /* 0x40 */ HuVecF unk040;       /* position */
    /* 0x4C */ HuVecF unk04C;       /* target position */
    /* 0x58 */ s32 unk058;
} M564_BOMB;

typedef struct M564PlayerMot_s {
    /* 0x0 */ u16 unk000;   /* index into omObj->mtnId (lhz) */
    /* 0x2 */ s16 unk002;   /* overlay motion index, <0 none (lha/cmpwi) */
    /* 0x4 */ u32 unk004;   /* CharMotionShiftSet attr (and with cmplwi) */
} M564_PLAYERMOT;

typedef struct M564Blast_s {
    /* 0x00 */ HU3DMODELID unk000;    /* lbl_1_bss_8C[6 + i] */
    /* 0x02 */ s16 unk002;            /* state 0..4, 0 = free */
    /* 0x04 */ HuVecF unk004;         /* 650 * (sin, 0, -cos)(18 + 36 i) */
    /* 0x10 */ s16 unk010;            /* bomb no, -1 none */
    /* 0x12 */ s16 unk012;            /* post-blast timer, 45 frames */
} M564_BLAST;


/* .data/.bss shared across units (defined in the unit named). */
extern M564_PLAYER *lbl_1_bss_100[4];  /* m564: player works */
extern HU3DMODELID lbl_1_bss_8C[16];   /* m564: stage models; bomb reads [6..15] */
extern HuVecF lbl_1_data_D8;           /* m564: arena centre, read by bomb and com */
extern MGF_CAMERAVIEW lbl_1_bss_44;    /* m564: the live camera view */
extern int lbl_1_bss_24;               /* m564: game phase, read by player/bomb */
extern M564_BOMB *lbl_1_bss_1E8[15];   /* bomb: bomb works */

/* actman.c has these; no header declares them. */
void MgActorPosGet(MGACTOR *actorP, HuVecF *pos);
void MgActorColMaskSet(MGACTOR *actorP, u32 mask);

/* --- m564.c --- */
void ObjectSetup(void);
void fn_1_EC(s16 mode, s16 frameNo);
void fn_1_9FC(s16 mode, s16 frameNo);
void fn_1_C3C(s16 mode, s16 frameNo);
void fn_1_C50(s16 mode, s16 frameNo);
void fn_1_C98(s16 mode, s16 frameNo);
void fn_1_D00(s16 mode, s16 frameNo);
void fn_1_F24(s16 mode, s16 frameNo);
void fn_1_FEC(s16 mode, s16 frameNo);
void fn_1_10F0(s16 mode, s16 frameNo);
void fn_1_10F4(OMOBJ *obj);
void fn_1_118C(HuVecF *center, float min, float max, HuVecF *out);
float fn_1_12D4(HuVecF *a, HuVecF *b);
float fn_1_1338(float a, float b);
float fn_1_13A4(HuVecF *a, HuVecF *b);
float fn_1_13F0(HuVecF *a, HuVecF *b, HuVecF *out);
s16 fn_1_1448(HuVecF *pos);
void fn_1_14D0(HuVecF *pos, s16 seNo);

/* --- player.c --- */
void fn_1_3E7C(void);
void fn_1_411C(OMOBJ *obj);
void fn_1_4204(MGPLAYER *player, s16 motNo);
void fn_1_43E0(MGPLAYER *player, s16 mode);
int fn_1_4428(COL_NARROW_PARAM *a, COL_NARROW_PARAM *b);
void fn_1_44A0(MGPLAYER *player);
void fn_1_4D2C(MGPLAYER *player);
void fn_1_4E84(MGPLAYER *player);
void fn_1_4FA4(MGPLAYER *player);
void fn_1_50CC(MGPLAYER *player);
void fn_1_52AC(MGPLAYER *player);
int fn_1_5600(M564_PLAYER *work);
void fn_1_57C4(M564_PLAYER *work);
int fn_1_5930(M564_PLAYER *work);
void fn_1_5D5C(MGPLAYER *player, s16 bombNo);
void fn_1_5DF4(MGPLAYER *player);
int fn_1_5E5C(s16 no);
void fn_1_5EA8(s16 no, HuVecF *pos);
void fn_1_5F08(s16 no);
s16 fn_1_5FDC(HuVecF *pos);

/* --- bomb.c --- */
void fn_1_60E8(void);
s32 fn_1_6404(void);
void fn_1_64B8(s16 layerNo);
void fn_1_653C(void);
void fn_1_6858(void);
void fn_1_6990(M564_BOMB *work);
void fn_1_6A14(M564_BOMB *work);
void fn_1_6A78(M564_BOMB *work);
void fn_1_6B04(M564_BOMB *work);
void fn_1_6BA0(M564_BOMB *work);
void fn_1_6CA8(M564_BOMB *work);
void fn_1_6EB4(M564_BOMB *work);
void fn_1_7154(M564_BOMB *work);
void fn_1_7210(M564_BOMB *work, s32 seF);
void fn_1_7404(M564_BOMB *work);
void fn_1_7430(M564_BOMB *work);
void fn_1_74C4(M564_BOMB *work, s16 motNo);
int fn_1_75A4(COL_NARROW_PARAM *a, COL_NARROW_PARAM *b);
void fn_1_7674(MGACTOR *actorP, int param);
void fn_1_76D8(OMOBJ *obj);
s16 fn_1_8340(HuVecF *pos, float angle);
s32 fn_1_84E8(HuVecF *a0, HuVecF *a1, float b0);
s32 fn_1_8558(HuVecF *pos, float b0, float b1);
void fn_1_86D8(s16 no, s16 playerNo);
void fn_1_87B4(s16 no, s16 playerNo);
void fn_1_89EC(s16 no);
int fn_1_8D60(s16 no);
void fn_1_8DEC(void);
int fn_1_8EC8(void);
void fn_1_8F6C(void);
int fn_1_902C(HuVecF *pos, HuVecF *out);
void fn_1_91FC(s32 no, HuVecF *out);
void fn_1_9344(OMOBJ *obj);
void fn_1_95D4(void);
s16 fn_1_9810(void);
void fn_1_98AC(s16 blastNo, s16 bombNo);

/* --- com.c --- */
void fn_1_9AC0(M564_PLAYER *player);
void fn_1_9ADC(M564_PLAYER *player);
void fn_1_9C00(M564_PLAYER *player, s16 mode);
void fn_1_9C20(M564_PLAYER *player);
void fn_1_9D28(M564_PLAYER *player);
void fn_1_9D90(M564_PLAYER *player);
void fn_1_9E30(M564_PLAYER *player);
void fn_1_9EB8(M564_PLAYER *player);
void fn_1_A008(M564_PLAYER *player);
int fn_1_A218(M564_PLAYER *player, s16 bombNo);
s16 fn_1_A38C(M564_PLAYER *player);
s16 fn_1_A594(M564_PLAYER *player);
int fn_1_A678(M564_PLAYER *player);
float fn_1_A6C0(M564_PLAYER *player);
void fn_1_A780(M564_PLAYER *player, s16 no);
void fn_1_A830(M564_PLAYER *player, s16 no);
int fn_1_A8D8(M564_PLAYER *player, int turnF);
int fn_1_AB2C(M564_PLAYER *player, M564_PLAYER *other);
int fn_1_AD38(M564_PLAYER *player);
int fn_1_B00C(M564_PLAYER *player);
int fn_1_B2DC(M564_PLAYER *player);
float fn_1_B380(HuVecF *a, HuVecF *b, HuVecF *c, HuVecF *d);

#endif
