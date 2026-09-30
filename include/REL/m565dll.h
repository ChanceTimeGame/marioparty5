#ifndef M565DLL_H
#define M565DLL_H

/*
 * m565dll (overlay #76): types and prototypes shared by its eleven translation
 * units (m565 main object back stage player puku2 com opening ending light).
 *
 * Offsets are GameCube ones from build/mp5-asm/m565dll. No upstream names exist,
 * so functions keep reference addresses and globals keep lbl_1_* labels.
 */

#include "dolphin/types.h"
#include "game/object.h"
#include "game/hu3d.h"
#include "math.h"
#include "humath.h"

#include "game/mg/seqman.h"
#include "game/mg/actman.h"

/* Work structs. Name every field by hex offset (unk050, unk0B4). m565 is an m510-engine
 * overlay, with one extra level: the heap work block (lbl_1_bss_0, M565_WORK) holds the
 * sequencing state and one M565_OBJECT at 0x18; the object holds the per-subsystem
 * structs, each starting with a back pointer to the OBJECT (not the work).
 * Pointers change size on the host: never hard-code a GC stride or sizeof in C.
 * Pads after a pointer are GC-layout pads. */
/* Host-only hardening of retail hazards (NOTES.md "Host-only divergences"). On GC every
 * M565_PC_OK() folds to 1 and the matching build is unchanged; on the host it is the
 * condition, which makes an out-of-bounds or uninitialised access a no-op. */
#define M565_PC_OK(cond) 1

typedef struct M565_WORK_s M565_WORK;
typedef struct M565_OBJECT_s M565_OBJECT;
typedef struct M565_LIST_s M565_LIST;
typedef struct M565_LISTNODE_s M565_LISTNODE;
typedef struct M565_PLAYER_s M565_PLAYER;
typedef struct M565_STAGEGRID_s M565_STAGEGRID;
typedef struct M565_PUKU2OBJ_s M565_PUKU2OBJ;

/* m565 fn_1_0/30/A0/E4: a doubly linked list (stage keeps two at 0x30E0/0x30EC). */
struct M565_LISTNODE_s {
    void *unk000;          /* payload (fn_1_A0 a2; stage reads payload->unk014 as s16, object 0x2724) */
    M565_LISTNODE *unk004; /* next (fn_1_30 0x54, fn_1_A0 0xC0) */
    M565_LISTNODE *unk008; /* prev (fn_1_A0 0xC8) */
    M565_LIST *unk00C;     /* owning list (fn_1_A0 0xD0) */
}; /* size 0x10 (GC): fn_1_30 memset 0x10 */

struct M565_LIST_s {
    s32 unk000;            /* node count (fn_1_A0 0xD8 ++, fn_1_E4 0x174 --) */
    M565_LISTNODE *unk004; /* head */
    M565_LISTNODE *unk008; /* tail */
}; /* size 0xC (GC): fn_1_0 memset 0xC */

typedef struct M565_LIGHT_s {
    M565_OBJECT *unk000; /* back pointer: object fn_1_25B4 0x25EC passes the OBJECT (r30) as a1 */
    s16 unk004;          /* HU3DLIGHTID (lha, cmpwi) */
    u8 pad006[0x2];
} M565_LIGHT; /* size 0x8 on GC */

typedef struct {
    u16 unk00; /* lhz: 100 = cell present */
    u16 unk02;
    s32 unk04; /* lwz: data num */
    s32 unk08; /* lwz: data num */
    u16 unk0C; /* lhz */
    s16 unk0E; /* lha */
    float unk10; /* lfs */
    float unk14; /* lfs */
} M565_STAGECELL; /* stage lbl_1_data_58[10][10], 0x18 each */

/* com fn_1_9EAC(player + 0x20, player). Owner: com fork. */
typedef struct M565_COM_s {
    M565_PLAYER *unk000; /* stw r4, 0(r3) in fn_1_9EAC */
    s32 unk004;          /* GwPlayerConf[].type: nonzero = COM (fn_1_9EAC; player 0x7E00) */
    u16 unk008;          /* COM level 0..3 from GwPlayerConf[].dif (clrlwi/sth, lhz) */
    u8 pad00A[0x2];
    M565_PLAYER *unk00C; /* target player: = player->unk080 (A050 0xA1EC stw), B600 lwz/->unk090 0xB664, ->unk088 0xB6C4 */
    u8 pad010[0x2];
    s16 unk012;          /* action-button countdown: sth B28[level] + frand() % (B28[level]/2); B600 0xB8AC lha/post-dec */
    u16 unk014;          /* action 0..6: A050 switch 0xA8B8 lhz, cmplwi 6 (jumptable_1_data_B88) */
    u16 unk016;          /* action sub-step: AB14 0xAB3C lhz, cmpwi 1 (switch), lhz/addi/sth ++ */
    u16 unk018;          /* move state 0/1/2: lhz switch at fn_1_CE68 0xD04C, lhz/cmplwi 0xE3B0; fn_1_A024 sth 0; fn_1_E714 sth 1 (fork H) */
    u8 pad01A[0x2];
    s32 unk01C;          /* action timer: stw 60 + 30*rand, A050 0xA9A4 lwz/-- while != 0 */
    s16 unk020;          /* mode 0..4 (A050 lha 0xA0F0, cmpwi 0..3); fn_1_A024 sth 4 */
    s16 unk022;          /* target column: = cell->unk00E (A9D4 0xAA4C sth), = player->unk088 + dx*3 (AC18 0xAE48) */
    s16 unk024;          /* target row: = cell->unk010 (A9D4 0xAA58 sth) */
    s16 unk026;          /* jump target column = cell->unk00E (fn_1_E714 0xE718; fn_1_CE68 0xDDFC) */
    s16 unk028;          /* jump target row = cell->unk010 (fn_1_E714 0xE720) */
    u8 pad02A[0x2];
    s32 unk02C;          /* jump started (fn_1_E714 stw 0 at 0xE730; fn_1_CE68 0xDFE8/0xE008) */
    s32 unk030;          /* debug: source line of the last fn_1_E714 call (0xE734) */
    s32 unk034;          /* debug: source line of the last fn_1_E534 call (0xE56C) */
    float unk038;        /* smoothed stick X (fn_1_CE68 0xE3F8/0xE418) */
    float unk03C;        /* smoothed stick Z (fn_1_CE68 0xE428/0xE448) */
    s32 unk040;          /* in-range flag: B600 0xB8A8 stw 1; CE68 0xE4A4 stw 0 */
    s32 unk044;          /* MgPlayerPadSet btnDown (player 0x7E2C); B600 0xB8C8 |= PAD_BUTTON_B */
    s32 unk048;          /* MgPlayerPadSet stkX */
    s32 unk04C;          /* MgPlayerPadSet stkY */
    s32 unk050;          /* MgPlayerPadSet btn */
} M565_COM; /* size 0x54 (GC): memset 0x54 in fn_1_9EAC/9FF4 */

/* player fn_1_78BC(&obj->unk008[i], i, obj). Owner: player fork. */
struct M565_PLAYER_s {
    M565_OBJECT *unk000;   /* the object block (fn_1_78BC a2); ->unk000 is the M565_WORK */
    MGPLAYER *unk004;      /* MgPlayerCreate result (also lbl_1_bss_7820[playerNo]) */
    s16 unk008;            /* playerNo (sth, lha) */
    u8 pad00A[0x2];
    s32 unk00C;            /* GwPlayerConf[playerNo].charNo (lwz, extsh to Char*) */
    s16 unk010;            /* model id: (s16)unk004->actor->mdlId */
    s16 unk012[7];         /* CharMotionCreate(charNo, lbl_1_data_9B8[charNo][i]); [4] = fall */
    M565_COM unk020;       /* COM AI state (fn_1_9EAC) */
    HuVecF *unk074;        /* &Hu3DData[unk010].pos */
    HuVecF *unk078;        /* &Hu3DData[unk010].rot (read in com.s 0xB410, ending.s 0xF208) */
    float unk07C;          /* rot Y (seen in ending.s 0xF430, opening.s 0xEB68; not in player.c) */
    M565_PLAYER *unk080;   /* nearest other live player, or NULL */
    float unk084;          /* XZ distance to unk080 (0 if none) */
    s16 unk088;            /* stage column (0..9) of the nearest block */
    s16 unk08A;            /* stage row (0..9) */
    float unk08C;          /* XZ distance to that block's centre */
    s32 unk090;            /* fell off: nonzero once y < -300 */
    s32 unk094;            /* control enabled (MgPlayerPadSet zeroed when 0); m565.s 0x640 clears */
    s32 unk098;            /* survivor flag (seen in ending.s 0xF0EC; not in player.c) */
    float unk09C;          /* fall speed: actor->velY / 100, clamped <= 0, -1.5/frame to -225 */
    s16 unk0A0;            /* effect model (data 0x78007D motion) */
    s16 unk0A2;            /* its joint motion */
    s32 unk0A4;            /* effect model playing (fn_1_89D4 sets, 7BDC clears at motion end) */
    u8 pad0A8[0x4];
}; /* size 0xAC (GC) */

/* back fn_1_3690(obj + 0x2B8, obj). Owner: back fork. */
typedef struct M565_BACK_s {
    M565_OBJECT *unk000; /* back pointer (36C0) */
    s32 unk004;          /* frame counter: orbit phase = unk004 % 600 (3F60 lwz, 4504 ++) */
    s16 unk008;          /* HU3DMODELID data 0x780000 (36DC), motion unk012 */
    s16 unk00A;          /* HU3DMODELID data 0x780001 (37B8), motion unk014 */
    s16 unk00C;          /* HU3DMODELID data 0x780002 (3894), orbits at phase 0 (4058) */
    s16 unk00E;          /* HU3DMODELID data 0x78006D (3970), orbits with unk00C, rot +90 (4190) */
    s16 unk010;          /* HU3DMODELID data 0x78006E (3A4C), orbits at phase +300 (43C4) */
    s16 unk012;          /* HU3DMOTID data 0x780074 (377C) */
    s16 unk014;          /* HU3DMOTID data 0x780075 (3858) */
    s16 unk016;          /* HU3DMOTID data 0x780076 (3934) */
    s16 unk018;          /* HU3DMOTID data 0x78007E (3A10) */
    s16 unk01A;          /* HU3DMOTID data 0x78007F (3AEC) */
    s16 unk01C;          /* HU3DMODELID data 0x78006F, created hidden (3B28) */
    s16 unk01E;          /* HU3DMODELID data 0x780070, hidden (3C04) */
    s16 unk020;          /* HU3DMODELID data 0x780071, hidden (3CE0), shape motion unk028 */
    s16 unk022;          /* HU3DMODELID data 0x780072, hidden, no motion (3DBC) */
    s16 unk024;          /* HU3DMOTID data 0x78007A (3BC8) */
    s16 unk026;          /* HU3DMOTID data 0x78007B (3CA4) */
    s16 unk028;          /* HU3DMOTID data 0x78007C, Hu3DMotionShapeSet (3D80) */
    u8 pad02A[0x2];
} M565_BACK; /* size 0x2C (GC): fn_1_3690 memset 0x2C */

/* stage grid cell: stage + 0x4 + row*0x4D8 + col*0x7C, memset 0x7C each in fn_1_4554 (4610). Owner: stage fork. */
struct M565_STAGEGRID_s {
    struct M565_STAGE_s *unk000; /* back pointer to the stage (stage 0x4614) */
    u16 unk004;          /* cell kind = lbl_1_data_58[row][col].unk00 (4634); 100 = solid, 101 = shaking/about to drop (4BCC 0x4C1C), 102 = handled by fn_1_6540 (4E30); 100/101 = standable (m565 0x66C/0x678, 57E4 0x585C) */
    s16 unk006;          /* = (s16)lbl_1_data_58[][].unk0C (4658); 1 selects the 6.49 threshold in fn_1_5284 (0x5680 lha, switch) */
    u8 pad008[0x4];
    s16 unk00C;          /* drop countdown: lha/sth 4BCC 0x4C30..0x4E10 (-- while != 0), = 60 at 0x5080 */
    s16 unk00E;          /* column (4660) */
    s16 unk010;          /* row (4668) */
    s16 unk012;          /* HU3DMODELID (46A8); 0 for absent cells (4808) */
    s16 unk014;          /* second HU3DMODELID (4760); object 0x2724 reads payload->unk014 of stage list nodes */
    u8 pad016[0x2];
    HuVecF unk018;       /* cell position (object 0x27AC: stage + 0x1C); x/z summed per column/row in 4554 */
    float unk024;        /* lfs/stfs: height, eased toward a sinking player (player 0x7D84); 4BCC 0x4ED8 -= unk028, floor -10000 */
    float unk028;        /* fall speed: 4BCC 0x4E80 (< 200: += 0.1 + 0.2 * speed) */
    s16 unk02C;          /* standable-neighbour count, 3x3 incl. self (fn_1_5998 lha/sth 0x5A5C); COM desirability sort key (com BD0C 0xBE04, BE54 0xBFB4) */
    u8 pad02E[0x2];
    s32 unk030;          /* flood-fill visited (fn_1_5700 0x5724/0x5744); cleared each frame 4BCC 0x4E60 */
    s32 unk034;          /* object stw 1 (fork B) */
    M565_PUKU2OBJ *unk038; /* object stw puku (fork B) */
    M565_LISTNODE unk03C; /* node in stage unk30D4 (4BCC fn_1_E4 0x4F18) */
    M565_LISTNODE unk04C; /* node in stage unk30E0 (4554 fn_1_A0 0x47E4) */
    M565_LISTNODE unk05C; /* node in stage unk30EC (4554 0x47F4; object fn_1_351C, fork B) */
    M565_LISTNODE unk06C; /* node in one stage unk30F8[] group (fn_1_5700 0x5734); memset 0x10 each frame (4BCC 0x4E4C) */
}; /* size 0x7C (GC): mulli 0x7C, row mulli 0x4D8 = 10 * 0x7C */

/* stage fn_1_4554(obj + 0x2E4, obj). Owner: stage fork. */
typedef struct M565_STAGEFX_s {
    s32 unk000;          /* active (fn_1_7624 0x7658 lwz, cmpwi) */
    s16 unk004;          /* HU3DMODELID (4554 0x4A98) */
    s16 unk006;          /* HU3DMOTID (4554 0x4B58) */
} M565_STAGEFX; /* size 0x8 (GC): memset 8 in fn_1_4554/4AE0 */typedef struct M565_STAGE_s {
    M565_OBJECT *unk000;          /* back pointer (4584) */
    M565_STAGEGRID unk004[10][10]; /* [row][col] (m565 0x654..0x668) */
    M565_STAGEFX unk3074[10];     /* 4554 0x4A64 (slwi 3, addi 0x3074) */
    M565_STAGEGRID *unk30C4;      /* cmplwi, passed to object fn_1_3020 (0x2C40), which reads ->unk018 (0x3088); picked by fn_1_5284 (4BCC 0x5118) */
    M565_STAGEGRID *unk30C8;      /* same (0x2CA8); second pick, >3 cols and >4 rows from unk30C4 (4BCC 0x5130..0x5200) */
    s32 unk30CC;                  /* regroup request: 4BCC 0x4F50 lwz/cmpwi, cleared at 0x5250 */
    s32 unk30D0;                  /* = 1 when a kind-102 cell was handled this frame (4BCC 0x4F28) */
    M565_LIST unk30D4;            /* falling cells (node cell+0x3C; head 4BCC 0x4E70, fn_1_E4 0x4F1C) */
    M565_LIST unk30E0;            /* fn_1_0 (4590); object walks its head (0x2718) */
    M565_LIST unk30EC;            /* fn_1_0 (4598); all live cells, count read at 4BCC 0x4E14/0x5020 */
    M565_LIST unk30F8[50];        /* connected groups (flood fill fn_1_5700): memset 0x258 (4BCC 0x4F80), mulli 0xC */
    u16 unk3350;                  /* group count (lhz/sth 4BCC 0x4F70/0x4FE0) */
    u16 unk3352;                  /* largest group size (lhz/sth 4BCC 0x4F6C/0x4FD4) */
    s32 unk3354;                  /* sound handle, -1 = none (4588; m565 0x7D8 fn_1_C40) */
    s32 unk3358;                  /* SE cooldown frames: = 10 at 4BCC 0x4CCC, -- at 0x5248 */
} M565_STAGE; /* size 0x335C (GC): fn_1_4554 memset 0x335C */

/* one puku2 actor: puku2 + 0x4 + i*0x5C, i < 5. Owner: puku2 fork. */
struct M565_PUKU2OBJ_s {
    struct M565_PUKU2_s *unk000; /* back pointer to the puku2 block (8E50) */
    s32 unk004;          /* active (m565 0x750; fn_1_8C70 lwz 4, cmpwi) */
    s16 unk008;          /* HU3DMODELID, flag != 0 kind (8E78; data 0x78006B) */
    s16 unk00A;          /* HU3DMODELID, flag == 0 kind (8F70; data 0x78006C) */
    s16 unk00C[1];       /* HU3DMOTID (8F44/903C; 907C kills [0..1) with lhax) */
    u8 pad00E[0x2];
    HuVecF unk010;       /* position (object 0x2C58 passes +0x10 to fn_1_A10; 90F0 0x9868) */
    HuVecF unk01C;       /* rotation: x pitch (90F0 0x990C), y yaw (0x98DC); fn_1_8C70 zeroes */
    s32 unk028;          /* fn_1_8C70 flag: nonzero = big (scale 3.0, hit range 150), else 1.3 / 65 */
    s32 unk02C;          /* m565 0x760 = 1: frozen (90F0 stops moving, blinks with unk058) */
    s16 unk030;          /* flight frames per half: fn_1_8C70 sth 40; object 0x3188 = 60 */
    s16 unk032;          /* fn_1_8C70 sth 100; flight total = unk032 + 2 * unk030 (90F0 0x91E8) */
    M565_STAGEGRID *unk034; /* target cell or NULL (object 3020/3284 stw, fork B) */
    HuVecF unk038;       /* start (fn_1_8C70 a1, fork B) */
    HuVecF unk044;       /* end (fn_1_8C70 a2, fork B) */
    float unk050;        /* fn_1_8C70 f1: apex height (90F0 0x9458) */
    s32 unk054;          /* frame counter: 8C70 = 0, 90F0 ++ (0x9A04) */
    s32 unk058;          /* m565 0x768 = 60; frozen blink countdown, 90F0 returns 1 at 0 (0x99EC) */
}; /* size 0x5C (GC): fn_1_8E10 memset 0x5C */

/* puku2 fn_1_8AD0(obj + 0x3648, obj). Owner: puku2 fork. */
typedef struct M565_PUKU2_s {
    M565_OBJECT *unk000;        /* back pointer (8B00) */
    M565_PUKU2OBJ unk004[5];    /* fn_1_8E10 loop (8B0C) */
    s16 unk1D0;                 /* active count (8C70 ++, 8BA8 --); obj+0x3818: opening/ending lha work+0x3830 */
    s16 unk1D2;                 /* active with flag != 0 (8DB8 ++, 8C2C --); object lha, cmpwi 2 (0x2C2C) */
    s16 unk1D4;                 /* active with flag == 0 (8DC8 ++, 8C3C --) */
    s16 unk1D6;                 /* total spawned (8DD4 ++, never decremented) */
} M565_PUKU2; /* size 0x1D8 (GC): fn_1_8AD0 memset 0x1D8 */

/* object fn_1_25B4(work + 0x18, work). Owner: object fork (fields); layout pinned by fork A. */
struct M565_OBJECT_s {
    M565_WORK *unk000;          /* back pointer to the work (25E8); obj->unk000->unk010 read at 0x2BB4 */
    u8 pad004[0x4];
    M565_PLAYER unk008[4];      /* fn_1_78BC (0x2760: mulli 0xAC, addi 0x8) */
    M565_BACK unk2B8;           /* fn_1_3690 (0x25F8) */
    M565_STAGE unk2E4;          /* fn_1_4554 (0x2604) */
    M565_LIGHT unk3640;         /* fn_1_FCBC (0x25EC) */
    M565_PUKU2 unk3648;         /* fn_1_8AD0 (0x2610) */
    s16 unk3820;                /* HU3DMODELID (0x2638) */
    s16 unk3822;                /* HU3DMOTID (0x26D4) */
    s32 unk3824;                /* = 1 (0x2A0C); opening lwz work+0x383C */
    s32 unk3828;                /* = 1 (0x2A14), cleared when the motion ends (0x2F14); opening lwz work+0x3840 */
    HuVecF unk382C;             /* camera Center base (0x2A6C) */
    HuVecF unk3838;             /* camera shake offset (0x2A4C, 0x2FA8) */
    s32 unk3844;                /* shake frames left (0x2F18) */
    float unk3848;              /* shake amplitude */
    float unk384C;              /* amplitude decay */
    float unk3850;              /* phase step */
    float unk3854;              /* phase */
}; /* size 0x3858 (GC): fn_1_25B4/2A94 memset 0x3858 */

/* the heap work block, lbl_1_bss_0 (m565 fn_1_3C8 HuMemDirectMallocNum 0x3880) */
struct M565_WORK_s {
    OMOBJMAN *unk000;   /* main fn_1_E48 0xE74 (a1 = lbl_1_bss_4) */
    u8 pad004[0x4];
    s32 unk008;         /* frame counter: main fn_1_FA8 0x1024 ++; stage lwz 0x4CEC */
    u8 pad00C[0x2];
    u16 unk00E;         /* opening/ending step: lhz, cmplwi 8 (opening 0xE7A0); m565 0x794 = 0 */
    s32 unk010;         /* game timer, 3600 (main 0xE7C), -- while != 0 (0x100C); object /60 at 0x2BB4 */
    s32 unk014;         /* opening/ending step timer (opening 0xEAC0, ending 0xFB34) */
    M565_OBJECT unk018; /* main 0xE98 fn_1_25B4(work + 0x18, work) */
    s32 unk3870;        /* main-play flag: m565 0x5BC = 1, 0x7F8 = 0; player 0x7F94, puku2 0x9D54, stage 0x4C24 read */
    s32 unk3874;        /* GAMEMESID, -1 = none (main 0xE84; extsh for GameMesKill 0xF74; ending 0xFB2C) */
    s32 unk3878;        /* BGM/jingle stream number, -1 = none (main 0xE8C; m565 0x524, 0x7C4) */
    s32 unk387C;        /* = -1 (main 0xE94); no other access in m565/main */
}; /* size 0x3880 (GC): fn_1_3C8 malloc + memset 0x3880, fn_1_E48/F48 memset 0x3880 */

/* .data/.bss shared across units (m565.c) */
extern s32 lbl_1_data_0;
extern HuVecF lbl_1_data_30;
extern HuVecF lbl_1_data_3C;
extern HuVecF lbl_1_data_48;
extern OMOBJMAN *lbl_1_bss_4;
extern M565_WORK *lbl_1_bss_0;

/* --- m565.c --- */
/* extern lbl_1_data_0; */
/* extern lbl_1_data_4; */
/* extern lbl_1_data_30; */
/* extern lbl_1_data_3C; */
/* extern lbl_1_data_48; */
/* extern lbl_1_rodata_10; */
/* extern lbl_1_rodata_14; */
/* extern lbl_1_rodata_18; */
/* extern lbl_1_rodata_1C; */
/* extern lbl_1_rodata_20; */
/* extern lbl_1_rodata_24; */
/* extern lbl_1_rodata_28; */
/* extern lbl_1_rodata_2C; */
/* extern lbl_1_rodata_30; */
/* extern lbl_1_rodata_34; */
/* extern lbl_1_rodata_38; */
/* extern lbl_1_rodata_3C; */
/* extern lbl_1_rodata_40; */
/* extern lbl_1_rodata_48; */
/* extern lbl_1_rodata_4C; */
/* extern lbl_1_rodata_50; */
/* extern lbl_1_rodata_54; */
/* extern lbl_1_rodata_58; */
/* extern lbl_1_rodata_5C; */
/* extern lbl_1_rodata_60; */
/* extern lbl_1_rodata_64; */
/* extern lbl_1_rodata_68; */
/* extern lbl_1_rodata_6C; */
/* extern lbl_1_rodata_70; */
/* extern lbl_1_rodata_74; */
void fn_1_0(M565_LIST *list);
void fn_1_30(M565_LIST *list);
void fn_1_A0(M565_LIST *list, M565_LISTNODE *node, void *data);
void fn_1_E4(M565_LIST *list, M565_LISTNODE *node);
void ObjectSetup(void);
void fn_1_3C8(s16 mode, s16 frameNo);
void fn_1_43C(s16 mode, s16 frameNo);
void fn_1_498(s16 mode, s16 frameNo);
void fn_1_4EC(s16 mode, s16 frameNo);
void fn_1_548(s16 mode, s16 frameNo);
void fn_1_59C(s16 mode, s16 frameNo);
void fn_1_5EC(s16 mode, s16 frameNo);
void fn_1_820(s16 mode, s16 frameNo);
void fn_1_864(s16 mode, s16 frameNo);
void fn_1_8B8(s16 mode, s16 frameNo);
float fn_1_8F4(float cur, float target, float rate);
void fn_1_A10(HuVecF *pos, float *vol, float *pan);
int fn_1_C18(int seId);
void fn_1_C40(int seNo);
void fn_1_C68(int seNo, s32 speed);
void fn_1_C98(int seNo, s16 pan);
void fn_1_CC8(int seNo, s16 vol);
void fn_1_CF8(Vec *pos, Vec *heading, float sndDist, float sndSpeed, float startDis, float frontSurDis, float backSurDis);
int fn_1_D50(s16 streamId);
void fn_1_D78(int streamNo, s32 speed);
void fn_1_DA8(void);
int fn_1_DC8(s16 streamId);
int fn_1_DF0(s16 streamId);
int fn_1_E18(s16 streamId, s16 chanNo);

/* --- main.c --- */
/* extern lbl_1_rodata_78; */
/* extern lbl_1_rodata_7C; */
/* extern lbl_1_rodata_80; */
/* extern lbl_1_rodata_84; */
/* extern lbl_1_rodata_88; */
/* extern lbl_1_rodata_8C; */
/* extern lbl_1_rodata_90; */
/* extern lbl_1_rodata_98; */
/* extern lbl_1_rodata_A0; */
void fn_1_E48(M565_WORK *work, OMOBJMAN *objman);
void fn_1_F48(M565_WORK *work);
s32 fn_1_FA8(M565_WORK *work, s32 arg1);
s32 fn_1_104C(M565_WORK *work);
s32 fn_1_1074(M565_WORK *work);
s32 fn_1_10E0(M565_WORK *work);
s32 fn_1_1108(M565_WORK *work);
void fn_1_1110(HU3DMODEL *modelP, Mtx *mtx);
void fn_1_1F20(HuVecF *start, HuVecF *end, GXColor *color);
void fn_1_1FF8(HuVecF *p0, HuVecF *p1, HuVecF *p2, GXColor *color);
void fn_1_2104(HuVecF *p0, HuVecF *p1, HuVecF *p2, HuVecF *p3, GXColor *color);
void fn_1_2244(Quaternion *out, HuVecF *from, HuVecF *to);

/* --- object.c --- */
/* extern lbl_1_rodata_A8; */
/* extern lbl_1_rodata_B4; */
/* extern lbl_1_rodata_B8; */
/* extern lbl_1_rodata_BC; */
/* extern lbl_1_rodata_C0; */
/* extern lbl_1_rodata_C8; */
/* extern lbl_1_rodata_D0; */
/* extern lbl_1_rodata_D8; */
/* extern lbl_1_rodata_E0; */
/* extern lbl_1_rodata_E8; */
/* extern lbl_1_rodata_EC; */
/* extern lbl_1_rodata_F0; */
/* extern lbl_1_rodata_F4; */
/* extern lbl_1_rodata_F8; */
/* extern lbl_1_rodata_FC; */
/* extern lbl_1_rodata_100; */
void fn_1_25B4(M565_OBJECT *obj, M565_WORK *work);
void fn_1_2A94(M565_OBJECT *obj);
s32 fn_1_2B20(M565_OBJECT *obj);
M565_PUKU2OBJ *fn_1_3020(M565_OBJECT *obj, M565_STAGEGRID *cell, s32 flag);
M565_PUKU2OBJ *fn_1_3284(M565_OBJECT *obj, float angle, float scale, s32 flag);
void fn_1_351C(M565_OBJECT *obj);
void fn_1_366C(M565_OBJECT *obj, s32 time, float amp, float decay, float speed);

/* --- back.c --- */
/* extern lbl_1_rodata_108; */
/* extern lbl_1_rodata_10C; */
/* extern lbl_1_rodata_110; */
/* extern lbl_1_rodata_118; */
/* extern lbl_1_rodata_120; */
/* extern lbl_1_rodata_128; */
/* extern lbl_1_rodata_12C; */
/* extern lbl_1_rodata_130; */
/* extern lbl_1_rodata_134; */
/* extern lbl_1_rodata_138; */
/* extern lbl_1_rodata_140; */
void fn_1_3690(M565_BACK *back, M565_OBJECT *obj);
void fn_1_3E54(M565_BACK *back);
void fn_1_3F14(M565_BACK *back);

/* --- stage.c --- */
/* extern lbl_1_data_58; */
/* extern lbl_1_rodata_148; */
/* extern lbl_1_rodata_14C; */
/* extern lbl_1_rodata_150; */
/* extern lbl_1_rodata_158; */
/* extern lbl_1_rodata_160; */
/* extern lbl_1_rodata_164; */
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
/* extern lbl_1_rodata_198; */
/* extern lbl_1_rodata_1A0; */
/* extern lbl_1_rodata_1A4; */
/* extern lbl_1_rodata_1A8; */
/* extern lbl_1_rodata_1AC; */
/* extern lbl_1_rodata_1B0; */
/* extern lbl_1_rodata_1B4; */
/* extern lbl_1_rodata_1B8; */
/* extern lbl_1_rodata_1BC; */
/* extern lbl_1_rodata_1C8; */
void fn_1_4554(M565_STAGE *stage, M565_OBJECT *obj);
void fn_1_4AE0(M565_STAGE *stage);
void fn_1_4BCC(M565_STAGE *stage);
void fn_1_5284(M565_STAGE *stage, M565_STAGEGRID **out);
void fn_1_5700(M565_STAGE *stage, M565_STAGEGRID *cell, M565_LIST *list);
void fn_1_57E4(M565_STAGE *stage, M565_STAGEGRID *from, s16 col, s16 row, M565_LIST *list);
void fn_1_5998(M565_STAGE *stage);
void fn_1_5EB0(M565_STAGE *stage, HuVecF *pos, s32 flag, M565_STAGEGRID **out);
void fn_1_5F24(M565_STAGE *stage, HuVecF *pos, M565_STAGEGRID **out);
void fn_1_6140(M565_STAGE *stage, HuVecF *pos, M565_STAGEGRID **out);
void fn_1_6474(M565_STAGE *stage, M565_STAGEGRID *cell);
void fn_1_6540(M565_STAGE *stage, M565_STAGEGRID *cell);
void fn_1_66D4(M565_STAGE *stage, M565_STAGEGRID *cell);
void fn_1_677C(M565_STAGE *stage, M565_STAGEGRID *cell);
void fn_1_68A0(M565_STAGE *stage, M565_STAGEGRID *cell);
void fn_1_7578(M565_STAGE *stage, HuVecF *pos);
void fn_1_7624(M565_STAGE *stage);
void fn_1_76C0(M565_STAGEGRID *cell);

/* --- player.c --- */
/* extern lbl_1_data_9B8; */
/* extern lbl_1_rodata_1D0; */
/* extern lbl_1_rodata_1D4; */
/* extern lbl_1_rodata_1D8; */
/* extern lbl_1_rodata_1DC; */
/* extern lbl_1_rodata_1E0; */
/* extern lbl_1_rodata_1E4; */
/* extern lbl_1_rodata_1E8; */
/* extern lbl_1_rodata_1EC; */
/* extern lbl_1_rodata_1F0; */
/* extern lbl_1_rodata_1F4; */
/* extern lbl_1_rodata_1F8; */
/* extern lbl_1_rodata_1FC; */
/* extern lbl_1_rodata_200; */
/* extern lbl_1_rodata_208; */
/* extern lbl_1_rodata_210; */
/* extern lbl_1_rodata_218; */
void fn_1_78BC(M565_PLAYER *player, s32 playerNo, M565_OBJECT *obj);
void fn_1_7B8C(M565_PLAYER *player);
s32 fn_1_7BDC(M565_PLAYER *player);
void fn_1_8024(M565_PLAYER *player);
void fn_1_8984(M565_PLAYER *player, s32 pauseOff);
void fn_1_89D4(M565_PLAYER *player, float angle, s32 knockback);

/* --- puku2.c --- */
/* extern lbl_1_rodata_220; */
/* extern lbl_1_rodata_22C; */
/* extern lbl_1_rodata_230; */
/* extern lbl_1_rodata_234; */
/* extern lbl_1_rodata_238; */
/* extern lbl_1_rodata_240; */
/* extern lbl_1_rodata_248; */
/* extern lbl_1_rodata_250; */
/* extern lbl_1_rodata_258; */
/* extern lbl_1_rodata_25C; */
/* extern lbl_1_rodata_260; */
/* extern lbl_1_rodata_264; */
/* extern lbl_1_rodata_268; */
/* extern lbl_1_rodata_270; */
/* extern lbl_1_rodata_278; */
/* extern lbl_1_rodata_280; */
/* extern lbl_1_rodata_288; */
void fn_1_8AD0(M565_PUKU2 *puku2, M565_OBJECT *obj);
void fn_1_8B44(M565_PUKU2 *puku2);
void fn_1_8BA8(M565_PUKU2 *puku2);
M565_PUKU2OBJ *fn_1_8C70(M565_PUKU2 *puku2, HuVecF *start, HuVecF *end, float b0, s32 flag);
void fn_1_8E10(M565_PUKU2OBJ *puku, M565_PUKU2 *puku2);
void fn_1_907C(M565_PUKU2OBJ *puku);
s32 fn_1_90F0(M565_PUKU2OBJ *puku);
void fn_1_9AC8(M565_PUKU2OBJ *puku);

/* --- com.c --- */
/* extern lbl_1_data_B28; */
/* extern lbl_1_data_B38; */
/* extern lbl_1_data_B48; */
/* extern lbl_1_data_B58; */
/* extern lbl_1_data_B68; */
/* extern lbl_1_data_B78; */
/* extern jumptable_1_data_B88; */
/* extern jumptable_1_data_BA4; */
/* extern lbl_1_rodata_290; */
/* extern lbl_1_rodata_294; */
/* extern lbl_1_rodata_298; */
/* extern lbl_1_rodata_29C; */
/* extern lbl_1_rodata_2A0; */
/* extern lbl_1_rodata_2A8; */
/* extern lbl_1_rodata_2B0; */
/* extern lbl_1_rodata_2B8; */
/* extern lbl_1_rodata_2C0; */
/* extern lbl_1_rodata_2C8; */
/* extern lbl_1_rodata_2D0; */
/* extern lbl_1_rodata_2D4; */
/* extern lbl_1_rodata_2D8; */
/* extern lbl_1_rodata_2DC; */
/* extern lbl_1_rodata_2E0; */
/* extern lbl_1_rodata_2E4; */
/* extern lbl_1_rodata_2E8; */
/* extern lbl_1_rodata_2EC; */
/* extern lbl_1_rodata_2F0; */
/* extern lbl_1_rodata_2F8; */
/* extern lbl_1_rodata_300; */
/* extern lbl_1_rodata_308; */
/* extern lbl_1_rodata_310; */
/* extern lbl_1_rodata_314; */
/* extern lbl_1_rodata_318; */
/* extern lbl_1_rodata_31C; */
/* extern lbl_1_rodata_320; */
/* extern lbl_1_rodata_324; */
/* extern lbl_1_rodata_330; */
/* extern lbl_1_rodata_338; */
/* extern lbl_1_rodata_33C; */
/* extern lbl_1_rodata_340; */
/* extern lbl_1_rodata_344; */
/* extern lbl_1_rodata_348; */
/* extern lbl_1_rodata_34C; */
/* extern lbl_1_rodata_350; */
/* extern lbl_1_rodata_354; */
void fn_1_9EAC(M565_COM *com, M565_PLAYER *player);
void fn_1_9FF4(M565_COM *com);
void fn_1_A024(M565_COM *com);
void fn_1_A050(M565_COM *com);
s32 fn_1_A9D4(M565_COM *com);
s32 fn_1_AB14(M565_COM *com);
s32 fn_1_AC18(M565_COM *com);
s32 fn_1_AEF4(M565_COM *com);
s32 fn_1_B600(M565_COM *com);
s32 fn_1_B96C(M565_COM *com);
void fn_1_BD0C(M565_COM *com);
void fn_1_BE54(M565_COM *com, s16 *count, M565_STAGEGRID **out);
void fn_1_C1E8(M565_COM *com, s16 kind);
void fn_1_C368(M565_COM *com, s16 x, s16 z, s16 kind); /* x,z bounds-checked 0..9 (0xC3A0) */
void fn_1_C62C(M565_COM *com, M565_STAGEGRID **out); /* no return value (0xC9B0); *out = cell or NULL */
void fn_1_C9C8(s16 dx, s16 dz, s16 *dir);
void fn_1_CAD8(s16 dirNo, s16 *dx, s16 *dz); /* extsh r3, jumptable BA4 on dirNo+7 */
void fn_1_CBB4(float angle, s16 *dirNo); /* callers load f1 before r3 (AC18 0xAE18, B96C 0xB9E8): float first; sth 0(r3) */
M565_PLAYER *fn_1_CDD8(M565_COM *com, M565_STAGEGRID *cell);
s32 fn_1_CE68(M565_COM *com); /* returns r22 (0xE4A8); callers cmpwi r3 */
s32 fn_1_E534(M565_COM *com, M565_STAGEGRID *cell, HuVecF *stick, s32 line);
s32 fn_1_E714(M565_COM *com, M565_STAGEGRID *cell, s32 line);

/* --- opening.c --- */
/* extern jumptable_1_data_BE0; */
/* extern lbl_1_rodata_358; */
/* extern lbl_1_rodata_35C; */
/* extern lbl_1_rodata_360; */
/* extern lbl_1_rodata_364; */
/* extern lbl_1_rodata_368; */
/* extern lbl_1_rodata_36C; */
/* extern lbl_1_rodata_370; */
/* extern lbl_1_rodata_374; */
/* extern lbl_1_rodata_378; */
/* extern lbl_1_rodata_37C; */
/* extern lbl_1_rodata_380; */
/* extern lbl_1_rodata_388; */
/* extern lbl_1_rodata_390; */
/* extern lbl_1_rodata_398; */
/* extern lbl_1_rodata_39C; */
/* extern lbl_1_rodata_3A0; */
/* extern lbl_1_rodata_3A4; */
s32 fn_1_E740(M565_WORK *work);

/* --- ending.c --- */
/* extern jumptable_1_data_C08; */
/* extern lbl_1_rodata_3A8; */
/* extern lbl_1_rodata_3B4; */
/* extern lbl_1_rodata_3C0; */
/* extern lbl_1_rodata_3C4; */
/* extern lbl_1_rodata_3C8; */
/* extern lbl_1_rodata_3CC; */
/* extern lbl_1_rodata_3D0; */
/* extern lbl_1_rodata_3D8; */
/* extern lbl_1_rodata_3E0; */
/* extern lbl_1_rodata_3E8; */
/* extern lbl_1_rodata_3EC; */
/* extern lbl_1_rodata_3F0; */
/* extern lbl_1_rodata_3F4; */
/* extern lbl_1_rodata_3F8; */
/* extern lbl_1_rodata_3FC; */
/* extern lbl_1_rodata_400; */
/* extern lbl_1_rodata_404; */
/* extern lbl_1_rodata_408; */
/* extern lbl_1_rodata_40C; */
/* extern lbl_1_rodata_410; */
/* extern lbl_1_rodata_414; */
/* extern lbl_1_rodata_418; */
/* extern lbl_1_rodata_41C; */
/* extern lbl_1_rodata_420; */
s32 fn_1_EE4C(M565_WORK *work);

/* --- light.c --- */
/* extern lbl_1_data_C40; */
/* extern lbl_1_data_C4C; */
/* extern lbl_1_data_C58; */
void fn_1_FCBC(M565_LIGHT *light, M565_OBJECT *obj);
void fn_1_FD34(M565_LIGHT *light);
void fn_1_FD88(M565_LIGHT *light);

#endif
