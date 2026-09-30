#ifndef M576DLL_H
#define M576DLL_H

/*
 * m576dll (overlay #87): types and prototypes shared by its three translation
 * units (m576, stage, score).
 *
 * Offsets are GameCube ones from build/mp5-asm/m576Dll. No upstream names exist,
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

/* TODO: work structs. Name every field by hex offset (unk050, unk0B4). */

typedef struct M576_SCOREPL_s {
    s32 unk000;         /* score value; lwzx + cmpwi 99 (signed) */
    HUSPRGRPID unk004;  /* MgScoreWin group */
    HUSPRGRPID unk006;  /* icon sprite group (1 member) */
    MGSCORE *unk008;  /* pointer: host stride differs */
} M576_SCOREPL; /* size 0xC (GC) */

typedef struct M576_SCORE_s {
    s32 unk000;  /* fade state */
    float unk004;  /* fade level 0..1 */
    M576_SCOREPL unk008[4];
} M576_SCORE; /* size 0x38 (GC) -- same layout as m503's */

typedef struct M576_SCOREPOS_s {
    float unk000;
    float unk004;
} M576_SCOREPOS;

typedef struct {
    s8 unk00[0x20]; /* lbz + extsb at C9B0, CA5C, CA94, CADC: signed (fork I) */
    float unk20[4];
} M576_STAGEDEF; /* stage lbl_1_data_3D4: lbz flags + lfs floats */

/*
 * m576 helpers called from stage.c (fork D pins these; do not change them).
 * "slot no" 8..12 names one of the five slot actors lbl_1_bss_2D8[no - 8];
 * 0..3 is a player. lbl_1_bss_2A0[slot] holds the owning player no, -1 = free.
 * MGPLAYER **playerP is the first field of a stage work struct (pass &work->unk000).
 */
s32 fn_1_174(s32 no, HuVecF *pos);          /* *pos = data_DC point[no] if pos; returns its colmap triNo (bss_254[no]) */
BOOL fn_1_1BC(HuVecF *pos);                 /* *pos = bss_23C[0]; returns bss_C <= 71.42857f */
BOOL fn_1_234(HuVecF *pos);                 /* *pos = bss_23C[1]; returns bss_10 <= 100.0f */
s32 fn_1_424(s32 playerNo);                 /* returns bss_2FC[playerNo]->stunType (s8, sign-extended) */
s32 fn_1_59C(void);                         /* number of free slots (bss_2A0[i] == -1) */
s32 fn_1_5F4(s32 no, HuVecF *pos);          /* slot no 8..12: *pos = slot actor pos if pos; returns slot owner (-1 free) */
s32 fn_1_668(MGPLAYER **playerP, HuVecF *pos, float *dist); /* nearest free slot to the player: no 8..12 or -1; optional pos, squared dist */
s32 fn_1_798(MGPLAYER **playerP);           /* number of slots owned by (*playerP)->actor->param */
s32 fn_1_854(s32 playerNo);                 /* number of slots owned by playerNo (same body as fn_1_7FC) */
s32 fn_1_8AC(s32 *playerNoOut, HuVecF *pos); /* player owning most slots (random tie-break): returns count; if >0, optional no + actor pos */
void fn_1_9A4(s32 playerNo, HuVecF *pos);   /* MgActorPosGet(bss_2FC[playerNo]->actor, pos) */
s32 fn_1_9EC(s32 playerNo);                 /* team: 1 if in bss_2B4[0..1], 2 if in bss_2B4[2..3], else 0 */
u32 fn_1_A54(s32 no);                       /* colGroundAttr of player 0..3 or slot actor 8..12; else 0 */

/* DOL: defined in actman.c, not declared by game/mg/actman.h */
void MgActorPosGet(MGACTOR *actorP, HuVecF *pos);

/*
 * stage navigation map (_NaviMapInit): one M576_NAVINODE per walkable triangle
 * of the stage model, linked to its edge neighbours, plus an A* open list
 * (M576_NAVIOPEN pool) searched per player slot (M576_NAVISLOT).
 */
typedef struct M576_NAVISLOT_s {
    u8 unk000;      /* flags: bit0 visited, bit1 in open list (0x7A60 ori 3, 0x7CF8 &2, 0x7F8C &~2) */
    float unk004;   /* extra cost (penalty); 0x7928 lfsx/stfsx +=, 0x7214 = 0 */
    s8 unk008;      /* arrival edge 0..2; 0x7EB4 stb, 0x7FB4 lbz+extsb */
    float unk00C;   /* cost so far (g); 0x7AB0 stfs, 0x72B0 lfs */
    float unk010;   /* heuristic (h); 0x7AA0 stfs, 0x72B4 lfs */
} M576_NAVISLOT; /* size 0x14 (GC) */

typedef struct M576_NAVINODE_s {
    HSFFACE *unk000;                    /* triangle; 0x82D0 stw, 0x84FC lwz + lha 0(r) */
    s32 unk004;                         /* face index; 0x82D4 stw, 0x7260 lwz + cmpw */
    HuVecF unk008;                      /* centroid; 0x8314/0x8360/0x83AC stfs */
    HuVecF unk014;                      /* midpoint of edge v0-v1; 0x83CC PSVECAdd dst */
    HuVecF unk020;                      /* midpoint of edge v1-v2 */
    HuVecF unk02C;                      /* midpoint of edge v2-v0 */
    float unk038[3];                    /* midpoint distances; 0x8470.. stfs, 0x7FCC lfsx (abs idx) */
    struct M576_NAVINODE_s *unk044[3];  /* neighbour per edge; 0x84B0 stw, 0x7FA8 lwzx */
    M576_NAVISLOT unk050[4];            /* per search slot; 0x7130 mulli 0x14 + 0x50 */
} M576_NAVINODE; /* size 0xA0 (GC) -- pointers: host stride differs */

typedef struct M576_NAVIOPEN_s {
    struct M576_NAVIOPEN_s *unk000;     /* prev; 0x7320 stw, 0x72FC lwz */
    struct M576_NAVIOPEN_s *unk004;     /* next; 0x7324 stw, 0x7350 lwz */
    s8 unk008;                          /* in use; 0x7564 lbz+extsb, 0x76A8 stb */
    s16 unk00A;                         /* own pool index; 0x81CC sthx, 0x7310 lha */
    float unk00C;                       /* sort key f = g + h; 0x769C stfs, 0x72EC lfs */
    M576_NAVINODE *unk010;              /* node; 0x76A0 stw, 0x73CC lwz + cmplw */
} M576_NAVIOPEN; /* size 0x14 (GC) -- pointers: host stride differs */

typedef struct M576_STAGEPL_s {
    MGPLAYER *unk000;   /* 0xC244 stw, MgPlayerAttrSet arg; 0xC394 lwz 0x3c(unk000) = actor */
    s8 unk004;          /* search slot (from lbl_1_bss_358); 0xC260 stb, 0x7124 lbz+extsb */
    HuVecF *unk008;     /* path points; 0xC288 stw of HuMemDirectMallocNum(unk00E * 0xC) */
    s16 unk00C;         /* path point count; 0xC268 sth, lha */
    s16 unk00E;         /* path point capacity (30); 0xC270 sth, 0xC278 lha */
    HuVecF unk010;      /* stw x3 (struct copy) in C31C/BB0C/CB9C; addi 0x10 as vec arg */
    HuVecF unk01C;      /* stw x3 in C31C; 0xBCD8 addi 0x1c as vec arg */
    float unk028;       /* stfs/lfs */
    s16 unk02C;         /* 0xC2A0 sth -1; lha */
    s16 unk02E;         /* 0xC298 sth -1; lha */
    s16 unk030;         /* 0xC2A8 sth; lha */
    s16 unk032;         /* 0xC2B0 sth; lha */
    s16 unk034;         /* 0xC2B8 sth; 0xC36C lha (countdown in C31C) */
    s16 unk036;         /* 0xC2C0 sth; lha */
    s8 unk038;          /* 0xC2E0 stb of GwPlayerConf[].dif; lbz+extsb */
    s32 unk03C;         /* 0xC290 stw 1; 0xC3C0 lwz + cmpwi 4 */
    s8 unk040;          /* stb/lbz+extsb (869C, BD94, CB9C) */
    s8 unk041;          /* stb/lbz+extsb (CB9C..E494) */
} M576_STAGEPL; /* size 0x44 (GC) -- pointers: host stride differs */

typedef struct M576_STAGEPLTBL_s {
    M576_STAGEPL unk000[4];  /* 0xC234 mulli 0x44 on lbl_1_bss_358 */
    u8 unk110[4];            /* never accessed: dtk sized the object to the section end */
} M576_STAGEPLTBL; /* size 0x114 (GC): stage lbl_1_bss_35C */

/* the lbl_1_data_3B0 state table entry type (fork I) */
typedef void (*M576_COMFUNC)(M576_STAGEPL *work);

/* --- m576.c --- */
/* extern lbl_1_data_0; */
/* extern lbl_1_data_28; */
/* extern lbl_1_data_58; */
/* extern lbl_1_data_88; */
/* extern lbl_1_data_C4; */
/* extern lbl_1_data_DC; */
/* extern lbl_1_data_184; */
/* extern lbl_1_data_1B4; */
/* extern lbl_1_data_204; */
/* extern lbl_1_data_254; */
/* extern lbl_1_data_27C; */
/* extern lbl_1_data_2AC; */
/* extern lbl_1_data_2F7; */
/* extern lbl_1_data_326; */
/* extern lbl_1_data_371; */
/* extern lbl_1_data_3A2; */
/* extern lbl_1_data_3A6; */
/* extern lbl_1_rodata_10; */
/* extern lbl_1_rodata_18; */
/* extern lbl_1_rodata_1C; */
/* extern lbl_1_rodata_20; */
/* extern lbl_1_rodata_28; */
/* extern lbl_1_rodata_2C; */
/* extern lbl_1_rodata_30; */
/* extern lbl_1_rodata_38; */
/* extern lbl_1_rodata_40; */
/* extern lbl_1_rodata_44; */
/* extern lbl_1_rodata_48; */
/* extern lbl_1_rodata_4C; */
/* extern lbl_1_rodata_50; */
/* extern lbl_1_rodata_54; */
/* extern lbl_1_rodata_58; */
/* extern lbl_1_rodata_5C; */
/* extern lbl_1_rodata_60; */
/* extern lbl_1_rodata_6C; */
/* extern lbl_1_rodata_78; */
/* extern lbl_1_rodata_84; */
/* extern lbl_1_rodata_90; */
/* extern lbl_1_rodata_94; */
/* extern lbl_1_rodata_98; */
/* extern lbl_1_rodata_9C; */
/* extern lbl_1_rodata_A0; */
/* extern lbl_1_rodata_A4; */
/* extern lbl_1_rodata_A8; */
/* extern lbl_1_rodata_AC; */
/* extern lbl_1_rodata_B0; */
/* extern lbl_1_rodata_B4; */
/* extern lbl_1_rodata_B8; */
/* extern lbl_1_rodata_BC; */
/* extern lbl_1_rodata_C0; */
/* extern lbl_1_rodata_C4; */
/* extern lbl_1_rodata_C8; */
/* extern lbl_1_rodata_D0; */
/* extern lbl_1_rodata_D8; */
/* extern lbl_1_rodata_E0; */
/* extern lbl_1_rodata_E8; */
/* extern lbl_1_rodata_F0; */
/* extern lbl_1_rodata_F8; */
/* extern lbl_1_rodata_FC; */
/* extern lbl_1_rodata_100; */
/* extern lbl_1_rodata_104; */
/* extern lbl_1_rodata_108; */
/* extern lbl_1_rodata_10C; */
/* extern lbl_1_rodata_110; */
/* extern lbl_1_rodata_114; */
/* extern lbl_1_rodata_118; */
/* extern lbl_1_rodata_120; */
/* extern lbl_1_rodata_128; */
/* extern lbl_1_rodata_12C; */
/* extern lbl_1_rodata_130; */
/* extern lbl_1_rodata_134; */
/* extern lbl_1_rodata_138; */
/* extern lbl_1_rodata_13C; */
/* extern lbl_1_rodata_140; */
/* extern lbl_1_rodata_144; */
/* extern lbl_1_rodata_148; */
/* extern lbl_1_rodata_14C; */
/* extern lbl_1_rodata_150; */
float fn_1_A0(float a, float b);
/* fn_1_174: see "helpers called from stage.c" above */
/* fn_1_1BC: see "helpers called from stage.c" above */
/* fn_1_234: see "helpers called from stage.c" above */
void fn_1_2AC(HuVecF *pos, s32 range);
/* fn_1_424: see "helpers called from stage.c" above */
BOOL fn_1_444(HuVecF *in, HuVecF *out);
/* fn_1_59C: see "helpers called from stage.c" above */
/* fn_1_5F4: see "helpers called from stage.c" above */
/* fn_1_668: see "helpers called from stage.c" above */
/* fn_1_798: see "helpers called from stage.c" above */
s32 fn_1_7FC(s32 playerNo);
/* fn_1_854: see "helpers called from stage.c" above */
/* fn_1_8AC: see "helpers called from stage.c" above */
/* fn_1_9A4: see "helpers called from stage.c" above */
/* fn_1_9EC: see "helpers called from stage.c" above */
/* fn_1_A54: see "helpers called from stage.c" above */
void fn_1_AC4(void);
void fn_1_C24(void);
void ObjectSetup(void);
void fn_1_FA0(MGACTOR *actor, int param); /* MGACTOR_CORRECT_HOOK */
MGACTOR *fn_1_1194(s32 playerNo, HuVecF pos); /* pos by value: its inlined copies in fn_1_1550 copy it */
int fn_1_1550(COL_NARROW_PARAM *a, COL_NARROW_PARAM *b); /* players' MGACTOR_PARAM narrowHook (fn_1_32CC 0x3BA0) */
void fn_1_32CC(OMOBJ *obj);
void fn_1_4100(void);
void fn_1_43A8(s8 *a, s8 *b, s8 num); /* = decathlonDll DecaSortChar */
void fn_1_4448(void);
void fn_1_48A0(s16 mode, s16 frameNo);
void fn_1_4920(s16 mode, s16 frameNo);
void fn_1_5288(s16 mode, s16 frameNo);
void fn_1_55C8(s16 mode, s16 frameNo);
void fn_1_5C04(s16 mode, s16 frameNo);
s32 fn_1_5D88(MGPLAYER *player, s32 seNo); /* voice SE, pan from actor x; only inlined into fn_1_5EAC */
void fn_1_5EAC(s16 mode, s16 frameNo);
void fn_1_6730(s16 mode, s16 frameNo);
void fn_1_6734(s16 mode, s16 frameNo);
void fn_1_6764(s16 mode, s16 frameNo);

/* --- stage.c --- */
/* extern lbl_1_data_3B0; */
/* extern lbl_1_data_3D4; */
/* extern lbl_1_data_494; */
/* extern lbl_1_data_4DB; */
/* extern lbl_1_rodata_158; */
/* extern lbl_1_rodata_15C; */
/* extern lbl_1_rodata_160; */
/* extern lbl_1_rodata_168; */
/* extern lbl_1_rodata_16C; */
/* extern lbl_1_rodata_170; */
/* extern lbl_1_rodata_174; */
/* extern lbl_1_rodata_178; */
/* extern lbl_1_rodata_17C; */
/* extern lbl_1_rodata_180; */
/* extern lbl_1_rodata_184; */
/* extern lbl_1_rodata_188; */
/* extern lbl_1_rodata_18C; */
/* extern lbl_1_rodata_190; */
/* extern lbl_1_rodata_194; */
/* extern lbl_1_rodata_198; */
/* extern lbl_1_rodata_19C; */
/* extern lbl_1_rodata_1A0; */
/* extern lbl_1_rodata_1A4; */
/* extern lbl_1_rodata_1A8; */
/* extern lbl_1_rodata_1B0; */
/* extern lbl_1_rodata_1B8; */
/* extern lbl_1_rodata_1BC; */
/* extern lbl_1_rodata_1C0; */
/* extern lbl_1_rodata_1C4; */
/* extern lbl_1_rodata_1C8; */
/* extern lbl_1_rodata_1CC; */
/* extern lbl_1_rodata_1D0; */
/* extern lbl_1_rodata_1D8; */
/* extern lbl_1_rodata_1DC; */
/* extern lbl_1_rodata_1E0; */
/* extern lbl_1_rodata_1E4; */
/* extern lbl_1_rodata_1E8; */
/* extern lbl_1_rodata_1EC; */
/* extern lbl_1_rodata_1F0; */
s32 fn_1_6784(HSFOBJECT *obj, HSFFACE *face);
void fn_1_67A4(s32 *idx, HSFFACE *face, s32 no);
BOOL fn_1_6868(HuVecF *a, HuVecF *b);
BOOL fn_1_693C(M576_NAVINODE *node, M576_NAVINODE *from, HuVecF *vtx, s32 vtx0, s32 vtx1);
void fn_1_70AC(M576_NAVISLOT *slot);
void fn_1_70E8(M576_STAGEPL *pl);
void fn_1_71D0(M576_STAGEPL *pl);
M576_NAVINODE *fn_1_7238(s32 faceNo);
BOOL fn_1_7298(void);
float fn_1_72B0(M576_NAVISLOT *slot);
void fn_1_72C0(M576_NAVIOPEN *open);
BOOL fn_1_7368(M576_NAVINODE *node, s32 slotNo);
void fn_1_751C(M576_NAVINODE *node, s32 slotNo);
M576_NAVINODE *fn_1_778C(void);
void fn_1_7828(M576_STAGEPL *pl, s32 *faceNo, s32 num, float cost, float radius);
float fn_1_7994(M576_NAVINODE *node, HuVecF *pos);
BOOL fn_1_79D4(M576_NAVINODE *node, M576_NAVINODE *from, float cost, HuVecF *goal, s32 slotNo);
void fn_1_7F44(M576_NAVINODE *node, s32 slotNo, HuVecF *goal);
void _NaviMapInit(s32 mdlId);
s32 fn_1_869C(M576_STAGEPL *work); /* COM plan: returns zone 1..4 (no replan) or 0 */
void fn_1_AB24(M576_STAGEPL *work, HuVecF *pos);   /* append pos to path unk008, grow by 10 (inlined everywhere) */
void fn_1_ABEC(M576_STAGEPL *work, M576_NAVINODE *goal, HuVecF *goalPos); /* A* to goal node, heuristic to goalPos */
s32 fn_1_B328(M576_STAGEPL *work, M576_NAVINODE **nodes, HuVecF *points, s32 num); /* A* to first reached of nodes[num]; unk010 = points[hit]; returns hit or -1 */
void fn_1_BAD8(M576_STAGEPL *work, s32 state);     /* unk000->work[0] = state, work[1] = 0 (inlined everywhere) */
void fn_1_BAF4(s32 no, s32 face); /* = m571 fn_1_8478(int, int); lbl_1_bss_324[no] = face; called by fn_1_FA0 */
BOOL fn_1_BB0C(M576_STAGEPL *work, s32 playerNo, float range); /* player within sqrt(range): chase it (state 1); inlined everywhere */
BOOL fn_1_BC74(M576_STAGEPL *work, HuVecF *target, float radius); /* MgPlayerVecChase(.., 10.0f, radius) + stuck jump; inlined everywhere */
s32 fn_1_BD94(M576_STAGEPL *work);     /* COM decision for fn_1_C31C: 0 / 5 / uninitialised (see OUT.txt) */
void fn_1_C16C(s32 mdlId); /* caller passes obj->mdlId[2]; then _NaviMapInit */
M576_STAGEPL *fn_1_C1EC(MGPLAYER *player); /* &lbl_1_bss_35C.unk000[n] or NULL; stored in m576 bss_2EC */
void fn_1_C31C(M576_STAGEPL *work);    /* per-frame COM update; dispatches lbl_1_data_3B0 at 0xC65C */
void fn_1_C6E4(M576_STAGEPL *work);
void fn_1_C6E8(M576_STAGEPL *work);
void fn_1_CB9C(M576_STAGEPL *work);
void fn_1_D1D8(M576_STAGEPL *work);
void fn_1_D54C(M576_STAGEPL *work);
void fn_1_D8E0(M576_STAGEPL *work);
void fn_1_DBE0(M576_STAGEPL *work);
void fn_1_DF40(M576_STAGEPL *work);
void fn_1_E494(M576_STAGEPL *work);

/* --- score.c --- */
/* extern lbl_1_data_538; */
/* extern lbl_1_data_558; */
/* extern lbl_1_rodata_1F8; */
/* extern lbl_1_rodata_1FC; */
/* extern lbl_1_rodata_200; */
/* extern lbl_1_rodata_208; */
/* extern lbl_1_rodata_210; */
/* extern lbl_1_rodata_218; */
void fn_1_EA08(OMOBJMAN *objman);
void fn_1_EA90(OMOBJ *obj);
void fn_1_ECC4(OMOBJ *obj);
void fn_1_EEC0(s32 no);
void fn_1_EEF8(s32 no);

#endif
