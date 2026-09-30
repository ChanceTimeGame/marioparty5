#ifndef M530DLL_H
#define M530DLL_H

/*
 * m530Dll (overlay #44): types and prototypes shared by its four translation
 * units (m530 kinomi player effect).
 *
 * Offsets are GameCube ones from build/mp5-asm/m530Dll. No upstream names exist,
 * so functions keep reference addresses and globals keep lbl_1_* labels.
 */

#include "dolphin/types.h"
#include "game/object.h"
#include "game/hu3d.h"
#include "math.h"
#include "humath.h"

#include "game/mg/seqman.h"
#include "game/mg/actman.h"
#include "game/hu3d.h"

/*
 * The minigame framework (REL/mgframe.h), compiled into m530.c as m523dll and
 * m569dll do. Other units call MgPadStkMagGet (fn_1_342C, effect),
 * MgAngleApproach (fn_1_3FF4, effect), MgVecOrbit (fn_1_4164, effect),
 * MgPlaneNormalGet (fn_1_439C, kinomi), MgPlaneDistGet (fn_1_4414, player) and
 * MgPlaneCrossGet (fn_1_4458, player), and read objman (lbl_1_bss_B8), so those
 * are external. MgPadStkMagGet and the three MgPlane* helpers need the four
 * MGF_LINK_* knobs this overlay adds to mgframe.h (no other overlay calls them
 * across units). map.txt renames every framework symbol to its reference label
 * (fn_1_1CA0 MgObjManInit .. fn_1_4458 MgPlaneCrossGet; DebugCameraStart =
 * lbl_1_bss_6C, MgMusicId = lbl_1_bss_B4, objman = lbl_1_bss_B8). m530's object
 * carries no debug-camera format strings, so MGF_DEBUG_READOUT stays undefined.
 */
#define MGF_LINK_PLAYERCONFSET
#define MGF_LINK_VECAPPROACH
#define MGF_LINK_ANGLEAPPROACH
#define MGF_LINK_VECORBIT
#define MGF_LINK_OBJMAN
#define MGF_LINK_PADSTKMAGGET
#define MGF_LINK_PLANENORMALGET
#define MGF_LINK_PLANEDISTGET
#define MGF_LINK_PLANECROSSGET
#define MGF_S_DECL
#include "REL/mgframe.h"

/* The address names the other units' reference assembly calls, for the host link. */
#define fn_1_342C MgPadStkMagGet
#define fn_1_3FF4 MgAngleApproach
#define fn_1_4164 MgVecOrbit
#define fn_1_439C MgPlaneNormalGet
#define fn_1_4414 MgPlaneDistGet
#define fn_1_4458 MgPlaneCrossGet
#define lbl_1_bss_B8 objman

/* lbl_1_bss_B8: m530.c defines it (hand-declared .bss, as m564/m569 do). */
extern OMOBJMAN *objman;

/*
 * One 2VS2 team: lbl_1_bss_4C[2], indexed by the team number (GwPlayerConf
 * grp / 2, fn_1_120). OWNED BY FORK A.
 */
typedef struct M530Team_s {
    /* 0x00 */ int unk000[2];         /* player numbers, by slot (grp & 1) (fn_1_120 0x178 stw) */
    /* 0x08 */ int unk008;            /* team score: effect +1 (0x9050) / +3 (0x9080); fn_1_1648 shows it capped at 99; fn_1_1768 compares the two */
    /* 0x0C */ u8 pad00C[4];          /* not accessed */
} M530_TEAM; /* size 0x10 (GC) */

/*
 * player.c: the thrown projectile, obj->data of the fn_1_7DD0 object
 * (HuMemDirectMallocNum(HEAP_HEAP, sizeof) in fn_1_7304). No pointers.
 * OWNED BY FORK P.
 */
typedef struct M530Shot_s {
    /* 0x00 */ s16 unk000;            /* owner player number (copied from M530_PLAYER.no, 0x7384) */
    /* 0x02 */ u8 pad002[2];
    /* 0x04 */ HuVecF unk004;         /* position (Hu3DModelObjPosGet "itemhook_b" 0x7598; PSVECAdd 0x7EF4) */
    /* 0x10 */ HuVecF unk010;         /* velocity: 30 * normalize(aim - pos) (PSVECScale 0x75F8) */
    /* 0x1C */ u8 pad01C[0xC];
    /* 0x28 */ s32 unk028;            /* kinomi hit index, -1 none (0x7380, 0x7F48) */
    /* 0x2C */ s32 unk02C;            /* frame counter (0x7DE4 == 100 kill, > 60 shrink) */
    /* 0x30 */ s32 unk030;            /* 1 = still held by the thrower, 0 = in flight (0x7388, 0x74D4) */
    /* 0x34 */ s16 unk034;            /* model id (HU3DMODELID; lha 0x7654) */
    /* 0x36 */ u8 pad036[2];
} M530_SHOT; /* size 0x38 (GC) */

/*
 * The player work: obj->data of the four player objects (lbl_1_bss_40,
 * fn_1_F4C). OWNED BY FORK P; effect.c's fields (fork E) merged in by offset.
 * m530.c fn_1_1DC allocates it (HuMemDirectMallocNum(HEAP_HEAP, 0x9C) on GC;
 * sizeof on the host: unk034 and unk070 are pointers) and fills the MGF head
 * inline; fn_1_120 sets unk02C = grp & 1 (role) and rewrites grp to grp / 2
 * (team 0/1).
 */
typedef struct M530Player_s {
    MGF_PLAYER_HEAD;                  /* 0x00..0x2B; grp = team 0/1 after fn_1_120; dif indexes 4-entry COM tables (effect 0x94A8, player 0x7A18); mode: player 0 wind-up/1 aim/2 throw, effect 1 hit/2 blink/3 end/4 walk home/5 turn */
    /* 0x2C */ s32 unk02C;            /* role: 0 thrower (fn_1_6D7C), 1 catcher (fn_1_8434) -- fn_1_F4C 0xF60; effect fn_1_8E2C skips 0 (0x8E74) */
    /* 0x30 */ s32 unk030;            /* won: 0 (fn_1_1DC 0xA84), 1 for the winning team (fn_1_1768); fn_1_DDC win/lose motion */
    /* 0x34 */ char *unk034;          /* CharModelItemHookGet(charNo, 2, 1|0) (player 0x6E90, 0x8568); effect hook name (0x9068, 0x919C) */
    /* 0x38 */ s32 unk038;            /* frame counter (player 0x6FC4, 0x7704, 0x7754; effect 0x89FC) */
    /* 0x3C */ s32 unk03C;            /* COM state (player fn_1_7900 switch; effect 0x9400) */
    /* 0x40 */ s32 unk040;            /* COM wait counter (player 0x79FC; effect 0x9494) */
    /* 0x44 */ s32 unk044;            /* COM target: lbl_1_bss_DC index, -1 none (player 0x7910; effect 0x93A0) */
    /* 0x48 */ HuVecF unk048;         /* COM target position (player 0x7A70; effect 0x9540) */
    /* 0x54 */ s16 unk054;            /* espEntry id of the thrower cursor, -1 none (m530 0xA8C; player 0x6F34, 0x71F4) */
    /* 0x56 */ u8 pad056[2];
    /* 0x58 */ HuVecF unk058;         /* cursor position on screen (x 90..490, y 50..214) (0x70A4) */
    /* 0x64 */ HuVecF unk064;         /* aim point in 3D, fn_1_8398's output (0x6F3C) */
    /* 0x70 */ M530_SHOT *unk070;     /* the held projectile's work (fn_1_7304 0x73A0) */
    /* 0x74 */ s32 unk074;            /* motion class 0/1/2 for motions 3/4/5 (m530 fn_1_10E8; effect 0x8D00) */
    /* 0x78 */ HuVecF unk078;         /* catcher velocity (effect 0x8AE8) */
    /* 0x84 */ float unk084;          /* catcher target yaw (player 0x84E8; effect 0x8D78) */
    /* 0x88 */ s32 unk088;            /* catcher walking-home flag (player 0x84F0; effect 0x9244) */
    /* 0x8C */ HuVecF unk08C;         /* home position = lbl_1_data_360[team] (effect 0x926C) */
    /* 0x98 */ float unk098;          /* walk-home speed 7.5 (effect 0x9278) */
} M530_PLAYER; /* size 0x9C (GC) */

/*
 * kinomi.c: one nut on the tree, lbl_1_bss_DC[21] (defined in player.c).
 * OWNED BY FORK K. No pointers: host size = GC size.
 */
typedef struct M530Kinomi_s {
    /* 0x00 */ s16 unk000;            /* own index (fn_1_45A0 sth 0x0) */
    /* 0x02 */ u8 pad002[2];
    /* 0x04 */ HuVecF unk004;         /* hook position from Hu3DModelObjPosGet(tree, "itemhook_fN"); record 0's is the plane point for fn_1_4414/4458 */
    /* 0x10 */ HuVecF unk010;         /* unk004 projected by Hu3D3Dto2D; COM cursor target (player 0x7A70) */
    /* 0x1C */ s16 unk01C;            /* nut model */
    /* 0x1E */ s16 unk01E;            /* "itemhook_ef" effect model hooked on unk01C, -1 = none */
    /* 0x20 */ s16 unk020;            /* ground shadow model (data 2, placed at y 0), -1 = none */
    /* 0x22 */ u8 pad022[2];
    /* 0x24 */ HuVecF unk024;         /* current position (reset to unk004; falls in fn_1_5E50, floor y 25) */
    /* 0x30 */ HuVecF unk030;         /* velocity; only .y (fall speed, +0.4/frame) is used */
    /* 0x3C */ s32 unk03C;            /* state: 0 off, 1 spawn, 2 on tree, 3 shaken, 4 swing, 5 fall, 6 burst, 7 landed, 8 blink, 9 remove, 10 blink+remove (guess) */
    /* 0x40 */ s32 unk040;            /* growth sub state 1..6 (fn_1_57A4); >= 4 ripe; effect: 4 score item, 6 bad */
    /* 0x44 */ s32 unk044;            /* 1 = special nut (effect +3 instead of +1) */
    /* 0x48 */ s32 unk048;            /* growth timer (fn_1_57A4) */
    /* 0x4C */ s32 unk04C;            /* state timer (fn_1_5360 and callees) */
} M530_KINOMI; /* size 0x50 (GC) */

/* --- m530.c .bss/.data read by the other units --- */
extern OMOBJ **lbl_1_bss_40;          /* the four player objects (omGetGroupMemberListEx) */
extern HU3DMODELID lbl_1_bss_44[4];   /* stage models; [0] the tree/stage (kinomi hooks its nuts on it) */
extern M530_TEAM lbl_1_bss_4C[2];
extern MGF_CAMERAVIEW lbl_1_data_6C;  /* the camera: .no is the camera bit, .pos the eye */
extern unsigned int lbl_1_data_C0[15]; /* character motion data numbers (CharModelMotListCreate) */

/* --- player.c globals --- */
extern HuVecF lbl_1_bss_D0;           /* plane normal (kinomi fn_1_439C writes it) */
extern M530_KINOMI lbl_1_bss_DC[21];
extern HuVecF lbl_1_data_348[2];      /* catcher start position by team */
extern HuVecF lbl_1_data_360[2];      /* team home positions */

/* --- m530.c --- */
void ObjectSetup(void);
void fn_1_120(void);
void fn_1_1DC(s16 mode, s16 frameNo);
void fn_1_C00(s16 mode, s16 frameNo);
void fn_1_C58(s16 mode, s16 frameNo);
void fn_1_CE0(s16 mode, s16 frameNo);
void fn_1_D00(s16 mode, s16 frameNo);
void fn_1_DAC(s16 mode, s16 frameNo);
void fn_1_DDC(s16 mode, s16 frameNo);
void fn_1_F48(s16 mode, s16 frameNo);
void fn_1_F4C(OMOBJ *obj);
void fn_1_FB0(OMOBJ *obj);
void fn_1_10E8(OMOBJ *obj, s32 motNo);
void fn_1_11DC(void);
void fn_1_1524(void);
void fn_1_15C8(void);
void fn_1_1648(s32 team);
void fn_1_16D8(OMOBJ *obj);
void fn_1_1768(void);
void fn_1_1A50(HuVecF *pos, s16 *vol, s16 *pan);
s32 fn_1_1B78(HuVecF *pos, s16 seNo);
/* fn_1_1CA0..fn_1_4458 (and MgCameraMoveEntry/MgFlowSet/MgFlowNext): the
 * framework, declared by MGF_S_DECL above under its own names. */

/* --- kinomi.c --- */
void fn_1_45A0(void);
void fn_1_4980(s32 idx);
s32 fn_1_4A18(void);
void fn_1_4A80(M530_KINOMI *kinomi, float time);
void fn_1_4AF4(M530_KINOMI *kinomi, float start, float end);
void fn_1_4BAC(M530_KINOMI *kinomi, s16 mot);
void fn_1_51E8(M530_KINOMI *kinomi);
void fn_1_525C(M530_KINOMI *kinomi);
void fn_1_52B0(M530_KINOMI *kinomi);
void fn_1_531C(M530_KINOMI *kinomi);
void fn_1_5360(OMOBJ *obj);
void fn_1_57A4(OMOBJ *obj);
void fn_1_5BD4(OMOBJ *obj);
void fn_1_5E50(OMOBJ *obj);
void fn_1_5FE8(OMOBJ *obj);
void fn_1_61A8(OMOBJ *obj);
void fn_1_6280(OMOBJ *obj);
void fn_1_6358(M530_KINOMI *kinomi);
void fn_1_6400(OMOBJ *obj);
s32 fn_1_645C(HuVecF *pos, float range);
s32 fn_1_6518(HuVecF *pos, float range);
s32 fn_1_65D4(HuVecF *pos, float range);
s32 fn_1_66D8(s32 idx);
void fn_1_6740(void);
void fn_1_6868(void);
void fn_1_694C(s32 idx);
void fn_1_6980(s32 idx);
void fn_1_69B4(void);
s32 fn_1_6A44(HuVecF *pos);
s32 fn_1_6B80(HuVecF *pos, s16 dif); /* player 0x7A30 passes both; the body reads neither */
s32 fn_1_6C50(s32 mode, s32 exclude);

/* --- player.c --- */
void fn_1_6D7C(OMOBJ *obj);
void fn_1_6F90(OMOBJ *obj);
void fn_1_6FFC(OMOBJ *obj);
void fn_1_7224(OMOBJ *obj);
void fn_1_7304(OMOBJ *obj);
void fn_1_74B0(OMOBJ *obj);
void fn_1_7674(OMOBJ *obj);
void fn_1_7748(OMOBJ *obj);
void fn_1_7900(OMOBJ *obj);
void fn_1_79D8(OMOBJ *obj);
void fn_1_7AFC(OMOBJ *obj);
void fn_1_7BEC(OMOBJ *obj);
void fn_1_7DD0(OMOBJ *obj);
void fn_1_7FF4(OMOBJ *obj);
s32 fn_1_80C4(HuVecF *from, HuVecF *to);
s32 fn_1_81DC(HuVecF *pos);
void fn_1_825C(OMOBJ *obj);
void fn_1_8398(HuVecF *cursor, HuVecF *out);
void fn_1_8434(OMOBJ *obj);
void fn_1_85D4(OMOBJ *obj);
void fn_1_86DC(OMOBJ *obj);
void fn_1_87FC(OMOBJ *obj);

/* --- effect.c --- */
void fn_1_8848(void);
void fn_1_88FC(OMOBJ *obj);
void fn_1_8958(OMOBJ *obj);
void fn_1_8C30(OMOBJ *obj);
s32 fn_1_8E2C(M530_PLAYER *player, HuVecF *pos);
s32 fn_1_8ED8(HuVecF *pos);
void fn_1_8F64(OMOBJ *obj);
void fn_1_916C(OMOBJ *obj);
void fn_1_91F8(OMOBJ *obj);
void fn_1_92E8(OMOBJ *obj);
void fn_1_9384(OMOBJ *obj);
void fn_1_9388(OMOBJ *obj);
void fn_1_9460(OMOBJ *obj);
void fn_1_95B0(OMOBJ *obj);
void fn_1_96B0(OMOBJ *obj);
s32 fn_1_96F8(OMOBJ *obj);

#endif
