/*
 * m538dll -- MG_TYPE_BATTLE. The cheapest of the six BATTLE minigames and the
 * only path that will ever exercise resultdll's ResultCoinAddBattle, which has
 * had zero coverage since the stub was written.
 *
 * One translation unit, 87 functions, 11,345 instructions. Wired into
 * PB_REL_FILES and RUN on 2026-09-03 (devBootOverlay=7, devForceMinigame=52):
 * it links, plays and returns to instdll with every heap total unchanged.
 * ALL 87 are written; 72 are byte-identical, 7,489 instructions. The fifteen
 * that differ are register allocation, the fabs expansion, a trailing empty
 * switch case, or a hand-inlined helper -- no logic differences. NOTES.md has
 * the breakdown; `python3 tally.py` from games/mp5/ re-measures.
 * CALLMAP.md indexes what is left; regenerate it with callmap.py.
 *
 * FUNCTIONS ARE EMITTED IN THE OBJECT'S ORDER, and that is not cosmetic:
 * CodeWarrior will not inline a static it has not reached, so a helper defined
 * below its caller produces a real call and one defined above it does not.
 * ObjectSetup measured 79 against 87 purely because the generated scaffold put
 * it last. Keep new work in address order; NOTES.md has the measurement.
 *
 * Each entry below carries the fn_1_XXXX it reproduces, that function's
 * reference instruction count, and the line range it occupies in
 *
 *     build/mp5-asm/m538dll/asm/REL/m538Dll/m538.s
 *
 * so a session can open any one of them without re-deriving the map.
 * Regenerate the asm with `./games/mp5/gen_asm.sh m538dll`; nothing under
 * build/ is committed. Note the reference path spells the module **m538Dll**
 * with a capital D -- that is the name on the disc -- while the port directory
 * and ovl_table.h entry are lowercase `m538dll`, which is what the loader
 * searches for.
 *
 * Verify per function, never by the headline number:
 *
 *   ./build/tools/ninja build/GP5E01_00/src/REL/m538dll/m538.o
 *   R=$PWD/games/mp5/build/GP5E01_00/m538Dll/obj/REL/m538Dll/m538.o
 *   O=$PWD/games/mp5/build/GP5E01_00/src/REL/m538dll/m538.o
 *   diff <($PWD/games/mp5/fndiff.py fn $R fn_1_1FC) \
 *        <($PWD/games/mp5/fndiff.py fn $O M538InitHook)
 *
 * fndiff.py needs absolute paths, and gen_asm.sh must have been run first --
 * without the reference object every diff reads as empty rather than erroring.
 *
 * SHAPE: this is the m570dll shape, not m524dll's. ObjectSetup ends in
 * MgSeqCreate(&SeqParam), so the DOL's sequence manager (game/mg/seqman.h)
 * drives the whole minigame through the nine hooks named below, and none of
 * the m524/m570 framework in REL/mgframe.h appears here -- it was checked for
 * and is absent, as it is in every remaining candidate.
 *
 * | function      | insns | asm lines   |
 * | ------------- | ----: | ----------- |
 * | `ObjectSetup ` |    87 |   61-151  |
 * | `M538InitHook` |    26 |  154-181  |
 * | `M538FadeInHook` |   144 |  184-338  |
 * | `M538StartHook` |    21 |  341-363  |
 * | `M538MainHook` |    71 |  366-443  |
 * | `M538FinishHook` |   141 |  446-605  |
 * | `M538PreWinnerHook` |   219 |  608-849  |
 * | `M538WinnerHook` |    67 |  852-928  |
 * | `M538FadeOutHook` |    15 |  931-947  |
 * | `M538CloseHook` |     8 |  950-959  |
 * | `M538PlayerMain` |   173 |  962-1138 |
 * | `M538UnkFD0  ` |   113 | 1141-1262 |
 * | `M538Unk1194 ` |     1 | 1265-1267 |
 * | `M538HostMain` |    86 | 1270-1357 |
 * | `M538Unk12F0 ` |    34 | 1360-1396 |
 * | `M538Unk1378 ` |     1 | 1399-1401 |
 * | `M538Unk137C ` |    23 | 1404-1432 |
 * | `M538Unk13D8 ` |    44 | 1435-1480 |
 * | `M538Unk1488 ` |    59 | 1483-1543 |
 * | `M538Unk1574 ` |    55 | 1546-1602 |
 * | `M538Unk1650 ` |    27 | 1605-1633 |
 * | `M538Unk16BC ` |   167 | 1636-1812 |
 * | `M538Unk1958 ` |   143 | 1815-1964 |
 * | `M538Unk1B94 ` |   141 | 1967-2119 |
 * | `M538Unk1DC8 ` |   752 | 2122-2928 |
 * | `M538Unk2988 ` |    28 | 2931-2963 |
 * | `M538Unk29F8 ` |   176 | 2966-3153 |
 * | `M538Unk2CB8 ` |   387 | 3156-3575 |
 * | `M538Unk32C4 ` |   454 | 3578-4066 |
 * | `M538Unk39DC ` |    84 | 4069-4160 |
 * | `M538Unk3B2C ` |   106 | 4163-4276 |
 * | `M538Unk3CD4 ` |   106 | 4279-4392 |
 * | `M538Unk3E7C ` |    57 | 4395-4457 |
 * | `M538Unk3F60 ` |   306 | 4460-4780 |
 * | `M538Unk4428 ` |    33 | 4783-4819 |
 * | `M538Unk44AC ` |    34 | 4822-4860 |
 * | `M538Unk4534 ` |   120 | 4863-4987 |
 * | `M538Unk4714 ` |   149 | 4990-5149 |
 * | `M538Unk4968 ` |   180 | 5152-5339 |
 * | `M538Unk4C38 ` |   207 | 5342-5559 |
 * | `M538Unk4F74 ` |   405 | 5562-6001 |
 * | `M538Unk55C8 ` |    55 | 6004-6064 |
 * | `M538Unk56A4 ` |   584 | 6067-6674 |
 * | `M538Unk5FC4 ` |   141 | 6677-6827 |
 * | `M538Unk61F8 ` |    47 | 6830-6881 |
 * | `M538Unk62B4 ` |    83 | 6884-6973 |
 * | `M538Unk6400 ` |    86 | 6976-7068 |
 * | `M538Unk6558 ` |    83 | 7071-7160 |
 * | `M538Unk66A4 ` |   157 | 7163-7330 |
 * | `M538Unk6918 ` |    43 | 7333-7380 |
 * | `M538Unk69C4 ` |    72 | 7383-7458 |
 * | `M538Unk6AE4 ` |    80 | 7461-7544 |
 * | `M538Unk6C24 ` |    44 | 7547-7592 |
 * | `M538Unk6CD4 ` |    49 | 7595-7647 |
 * | `M538Unk6D98 ` |    21 | 7650-7674 |
 * | `M538Unk6DEC ` |    25 | 7677-7707 |
 * | `M538Unk6E50 ` |    53 | 7710-7770 |
 * | `M538Unk6F24 ` |   234 | 7773-8021 |
 * | `M538Unk72CC ` |   228 | 8024-8261 |
 * | `M538Unk765C ` |    82 | 8264-8352 |
 * | `M538Unk77A4 ` |    58 | 8355-8418 |
 * | `M538Unk788C ` |   133 | 8421-8559 |
 * | `M538Unk7AA0 ` |   132 | 8562-8699 |
 * | `M538Unk7CB0 ` |   149 | 8702-8856 |
 * | `M538Unk7F04 ` |    42 | 8859-8906 |
 * | `M538Unk7FAC ` |   362 | 8909-9291 |
 * | `M538Unk8554 ` |   164 | 9294-9468 |
 * | `M538Unk87E4 ` |    29 | 9471-9503 |
 * | `M538Unk8858 ` |    20 | 9506-9529 |
 * | `M538Unk88A8 ` |    30 | 9532-9567 |
 * | `M538Unk8920 ` |    56 | 9570-9633 |
 * | `M538Unk8A00 ` |    91 | 9636-9734 |
 * | `M538Unk8B6C ` |    91 | 9737-9835 |
 * | `M538Unk8CD8 ` |   160 | 9838-10002 |
 * | `M538Unk8F58 ` |    51 | 10005-10060 |
 * | `M538Unk9024 ` |   109 | 10063-10177 |
 * | `M538Unk91D8 ` |   123 | 10180-10311 |
 * | `M538Unk93C4 ` |    70 | 10314-10389 |
 * | `M538Unk94DC ` |   458 | 10392-10864 |
 * | `M538Unk9C04 ` |   424 | 10867-11302 |
 * | `M538UnkA2A4 ` |    49 | 11305-11358 |
 * | `M538UnkA368 ` |    47 | 11361-11412 |
 * | `M538UnkA424 ` |   181 | 11415-11609 |
 * | `M538UnkA6F8 ` |   106 | 11612-11723 |
 * | `M538UnkA8A0 ` |   173 | 11726-11919 |
 * | `M538UnkAB54 ` |   351 | 11922-12284 |
 * | `M538UnkB0D0 ` |    69 | 12287-12361 |
 *
 * THE NINE SEQUENCE HOOKS, from the MGSEQ_PARAM at lbl_1_data_0:
 * maxTime 0, timerPos 0, then init/fadeIn/start/main/finish/preWinner/winner/
 * fadeOut/close = M538InitHook, M538FadeInHook, M538StartHook, M538MainHook,
 * M538FinishHook, M538PreWinnerHook, M538WinnerHook, M538FadeOutHook,
 * M538CloseHook.
 *
 * WHAT OBJECTSETUP SAYS ABOUT THE DATA, read off the disassembly:
 *   omInitObjMan(10, 0x2000) -> bss_10
 *   omGameSysInit(objman)
 *   host  = omAddObjEx(objman, 0x65, 0, 0, OM_GRP_NONE, M538HostMain) -> bss_C
 *   host->data = HuMemDirectMallocNum(0, 0x1920, 0x10000000)   6,432 bytes
 *   host->data->unk18DC = 0  (s16)
 *   M538Unk1488(work); M538Unk13D8(work); M538Unk1574(work)
 *   for(i=0;i<4;i++) {
 *       obj = omAddObjEx(objman, 0x64, 1, 11, 0, M538PlayerMain);
 *       obj->data = HuMemDirectMallocNum(0, 0x104, 0x10000000) 260 bytes
 *       obj->work[0] = i;                     (OMOBJ offset 0x4C)
 *       work->player[i] = obj->data;          so the work block STARTS with a
 *   }                                          four-entry pointer array
 *   M538Unk137C(work);
 *
 * The player objects take one model and eleven motions each (mdlcnt 1,
 * mtncnt 11) and share group 0; the host takes none and no group. Note the
 * host is added FIRST and at the LOWER priority number (0x65 against 0x64),
 * so it runs after the four players each frame.
 *   Hu3DBGColorSet(0,0,0); Hu3DNoSyncSet(1);
 *   MgSeqCreate(&SeqParam);
 *
 * _prolog and _epilog are not reproduced: they are REL bootstrap the port
 * replaces, exactly as in every other overlay here.
 */

#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/hsfex.h"
#include "game/hsfformat.h"
#include "game/memory.h"
#include "game/wipe.h"
#include "game/pad.h"
#include "game/audio.h"
#include "game/frand.h"
#include "game/esprite.h"
#include "game/flag.h"
#include "game/pad.h"
#include "game/mg/seqman.h"
#include "game/mg/timer.h"
#include "game/mg/score.h"

#include "datadir_enum.h"

#include "dolphin/os.h"
#include "dolphin/pad.h"

#include "math.h"
#include "humath.h"

/* Sizes are the originals; the port widens pointer-bearing structs, so
 * sizeof() here legitimately differs from the byte counts in the comments.
 * Everything but the two fields ObjectSetup touches is still unknown -- the
 * padding is a placeholder to be replaced as the init functions are read. */

/* The player's current target, at player+0xD0. Its first word is a pointer to
 * something whose x and z are read, so the whole block is addressed through its
 * own base register rather than off the player. */
/* M538Unk69C4 is unreferenced dead code and nothing names its argument, so it
 * gets a type of its own rather than a guess at an existing one. */
typedef struct M538Unk69C4_s {
    u8 unk00[0x48];
    HU3DMODELID modelId;           /* 0x48 */
} M538_UNK69C4;

typedef struct M538Target_s {
    Vec *pos;                      /* 0x00 */
    s16 unk04;                     /* 0x04 */
    s16 unk06;                     /* 0x06 */
    s16 unk08;                     /* 0x08 */
    s16 unk0A;                     /* 0x0A */
    int fxNo;                      /* 0x0C (player 0xDC) */
} M538_TARGET;                     /* 0x10 */

typedef struct M538Player_s M538_PLAYER;

typedef int (*M538_PLAYERPROC)(M538_PLAYER *player);

/* Two blocks whose extent is known (the offsets on either side) but whose
 * contents are not yet read by anything written here. */
typedef struct M538Unk294_s {
    u8 unk00[0x18];
    float unk18;                   /* 0x18 */
    float unk1C;                   /* 0x1C */
    float unk20;                   /* 0x20 */
    s16 unk24;                     /* 0x24 */
    s16 unk26;                     /* 0x26 */
    HU3DMODELID unk28;             /* 0x28 */
    HU3DMODELID unk2A;             /* 0x2A, hooked onto unk28 by M538Unk765C */
    HU3DMODELID unk2C;             /* 0x2C, hooked onto unk28 by M538Unk77A4 */
    HU3DMODELID unk2E;             /* 0x2E */
} M538_UNK294;                     /* 0x294, 0x30 */

/* 44AC's argument: a model and a blink counter. It is installed into a
 * player's second proc slot, not into a node. */
typedef struct M538Hud_s {
    HU3DMODELID modelId;           /* 0x00 */
    s16 unk02;                     /* 0x02 */
} M538_HUD;

typedef int (*M538_HUDPROC)(M538_HUD *hud);

/* The other mini-node payload: a thrown thing that spins away, shrinks over 60
 * frames and then retires. M538Unk7FAC allocates it. Its extent past 0x2C is
 * not yet read by anything matched. */
typedef struct M538Throw_s {
    Vec pos;                       /* 0x00 */
    Vec rot;                       /* 0x0C */
    float unk18;                   /* 0x18, rot.z at launch */
    float unk1C;                   /* 0x1C, rot.y at launch */
    u8 unk20[0x28 - 0x20];
    HU3DMODELID modelId;           /* 0x28 */
    s16 unk2A;                     /* 0x2A */
    s16 unk2C;                     /* 0x2C */
    u8 unk2E[0x30 - 0x2E];
} M538_THROW;                      /* 0x30 */

typedef struct M538Unk17E0_s {
    u8 unk00[0x4];
    HU3DMODELID modelId;           /* 0x04 */
    s16 unk06;                     /* 0x06 */
    s16 unk08;                     /* 0x08 */
    u8 unk0A[0x10 - 0x0A];
} M538_UNK17E0;                    /* 0x17E0, 0x10 */

typedef struct M538Unk17DC_s M538_UNK17DC;

/* The proc in work->unk17F0 is handed this, not the work block. */
typedef int (*M538_UNK17DCPROC)(M538_UNK17DC *p);

struct M538Unk17DC_s {
    s16 unk00;                     /* 0x17DC */
    s16 unk02;                     /* 0x17DE */
    M538_UNK17E0 unk04;            /* 0x17E0 */
};                                 /* 0x14 */

/* Four of these live inside the 0x17F4 block, and their extent is what fixes
 * the block's own layout: M538UnkA6F8 writes element i's model at
 * work+0x182C+i*0x30, and M538UnkA8A0 -- which is handed &work->unk17F4 --
 * reads a state pair at the block's +0xD0/+0xD2 and passes the block's +0x10 to
 * a node. Base 0x1804, four 0x30 elements, then the pair, is the only split
 * that satisfies all three and ends exactly at the light id. */
typedef struct M538Unk17F4_s {
    u8 unk00[0x10];
    M538_THROW unk10[4];           /* 0x1804 -- the same 0x30 record the mini
                                    * pool carries, four of them inline */
    s16 unkD0;                     /* 0x18C4 */
    s16 unkD2;                     /* 0x18C6 */
} M538_UNK17F4;                    /* 0x17F4, 0xD4 */

typedef struct M538Camera_s {
    Vec unk00;                     /* 0x00, six floats written from data_2E4 */
    Vec unk0C;                     /* 0x0C */
    Vec unk18;                     /* 0x18, a snapshot of unk00 */
    Vec unk24;                     /* 0x24, a snapshot of unk0C */
    s16 unk30;                     /* 0x30 */
    s16 unk32;                     /* 0x32 */
} M538_CAMERA;                     /* 0x34 -- extent inferred from the next
                                    * known offset, not yet from a load */

typedef struct M538Unit_s M538_UNIT;

/* The per-unit function is called with the unit itself and its return value is
 * used, so it is not an ordinary object proc. */
typedef int (*M538_UNITFUNC)(M538_UNIT *unit);

struct M538Unit_s {
    float unk00;                   /* 0x00, 750.0f at init */
    int unk04;                     /* 0x04, 1 at init; cleared at a mode change */
    M538_UNITFUNC func;            /* 0x08 */
    s16 unk0C;                     /* 0x0C, bumped once in the pre-start branch */
    s16 unk0E;                     /* 0x0E */
    s16 no;                        /* 0x10, the unit's own index */
    HU3DMODELID model[3];          /* 0x12 */
};                                 /* 0x18 */

typedef struct M538NodeList_s M538_NODELIST;
typedef struct M538Node_s M538_NODE;

/* Returning non-zero retires the node to its list's free chain. */
typedef int (*M538_NODEFUNC)(M538_NODE *node);

struct M538Node_s {
    M538_NODE *prev;               /* 0x00 */
    M538_NODE *next;               /* 0x04 */
    M538_NODELIST *list;           /* 0x08 */
    M538_NODEFUNC func;            /* 0x0C */
    Vec unk10;                     /* 0x10 */
    Vec unk1C;                     /* 0x1C */
    float unk28;                   /* 0x28 */
    float unk2C;                   /* 0x2C */
    s16 unk30;                     /* 0x30 */
    s16 unk32;                     /* 0x32 */
    HU3DMODELID modelId;           /* 0x34 */
    s16 unk36;                     /* 0x36 */
};                                 /* 0x38 */

/* A second, smaller pool, embedded directly in the work block rather than
 * behind a M538_NODELIST: 32 nodes of 0x10 with the head pair at work+0x10.
 * Its proc sits at +0x08 where M538_NODE's is at +0x0C, so the two are not
 * interchangeable despite the identical unlink logic. */
typedef struct M538MiniNode_s M538_MININODE;

typedef int (*M538_MINIFUNC)(M538_MININODE *node);

struct M538MiniNode_s {
    M538_MININODE *prev;           /* 0x00 */
    M538_MININODE *next;           /* 0x04 */
    M538_MINIFUNC func;            /* 0x08 */
    void *unk0C;                   /* 0x0C -- whatever its proc needs */
};                                 /* 0x10 */

struct M538NodeList_s {
    M538_NODE *active;             /* 0x00 */
    M538_NODE *free;               /* 0x04 */
};                                 /* 0x08 */

struct M538Player_s {
    Vec unk00;                     /* 0x00, position */
    Vec unk0C;                     /* 0x0C, rotation */
    Vec unk18;                     /* 0x18, cleared every frame */
    Vec unk24;                     /* 0x24, a velocity: damped 0.9 and snapped
                                    * to zero below 0.01 */
    Vec unk30;                     /* 0x30, the hook's world translation */
    Vec unk3C;                     /* 0x3C, the hook's world rotation */
    M538_THROW throwWork;          /* 0x48 -- handed to a mini node running
                                    * M538Unk6F24 when the player is knocked
                                    * out */
    HU3DMODELID itemModelId;       /* 0x78, hooked to the character's item slot */
    u8 unk7A[0x7C - 0x7A];
    M538_HUD hud;                  /* 0x7C -- what the second proc slot is
                                    * called with, not the player itself */
    M538_HUDPROC unk80;            /* 0x80 */
    M538_PLAYERPROC proc;          /* 0x84 */
    int unk88;                     /* 0x88 */
    u8 unk8C[0xA4 - 0x8C];
    float unkA4;                   /* 0xA4, spiral angle */
    float unkA8;                   /* 0xA8, spiral radius */
    u8 unkAC[0xBC - 0xAC];
    float unkBC;                   /* 0xBC, the facing angle */
    float unkC0;                   /* 0xC0, 30.0f */
    OMOBJ *obj;                    /* 0xC4 */
    M538_NODELIST *listA;          /* 0xC8, &work->list[0] */
    M538_NODELIST *listB;          /* 0xCC, &work->list[1] */
    M538_TARGET target;            /* 0xD0 */
    s16 unkE0;                     /* 0xE0, sound pan */
    s16 unkE2;                     /* 0xE2, sound volume */
    s16 unkE4;                     /* 0xE4 */
    s16 unkE6;                     /* 0xE6 */
    s16 unkE8;                     /* 0xE8 */
    s16 unkEA;                     /* 0xEA, 3 */
    s16 unkEC;                     /* 0xEC, 1 */
    HU3DMODELID modelId;           /* 0xEE */
    s16 playerNo;                  /* 0xF0 */
    s16 charNo;                    /* 0xF2, from GwPlayerConf */
    s16 grp;                       /* 0xF4 */
    s16 padNo;                     /* 0xF6 */
    u8 unkF8[0xFC - 0xF8];
    s16 type;                      /* 0xFC */
    s16 dif;                       /* 0xFE */
    s16 unk100;                    /* 0x100 */
    s16 unk102;                    /* 0x102 */
};                                 /* 0x104 */

typedef struct M538Work_s {
    M538_PLAYER *player[4];        /* 0x0000 */
    M538_MININODE *miniActive;     /* 0x0010 */
    M538_MININODE *miniFree;       /* 0x0014 */
    M538_MININODE mini[32];        /* 0x0018 */
    M538_CAMERA camera;            /* 0x0218 */
    M538_UNIT unit[3];             /* 0x024C, 0x0264, 0x027C */
    M538_UNK294 unk294;            /* 0x0294 -- M538Unk72CC / M538Unk765C */
    M538_NODELIST list[3];         /* 0x02C4, 0x02CC, 0x02D4 */
    M538_NODE poolA[16];           /* 0x02DC */
    M538_NODE poolB[16];           /* 0x065C */
    M538_NODE poolC[64];           /* 0x09DC */
    M538_UNK17DC unk17DC;          /* 0x17DC */
    M538_UNK17DCPROC unk17F0;      /* 0x17F0 -- installed by the fade-in and
                                    * pre-winner hooks, cleared when it
                                    * reports done */
    M538_UNK17F4 unk17F4;          /* 0x17F4 -- M538UnkA8A0 every frame */
    HU3DLIGHTID lightId;           /* 0x18C8 */
    s16 unk18CA;                   /* 0x18CA */
    float unk18CC;                 /* 0x18CC */
    s16 unk18D0;                   /* 0x18D0 */
    s16 unk18D2;                   /* 0x18D2 -- non-zero means everybody lost */
    s16 unk18D4;                   /* 0x18D4 */
    s16 unk18D6;                   /* 0x18D6 */
    s16 unk18D8;                   /* 0x18D8 */
    s16 unk18DA;                   /* 0x18DA */
    s16 unk18DC;                   /* 0x18DC */
    s16 modelId[29];               /* 0x18DE, all -1 at startup */
    HU3DMOTID motId[3];            /* 0x1918, all -1 at startup */
    s16 unk191E;                   /* 0x191E */
} M538_WORK;                       /* 0x1920 */

/* --- forward declarations --- */

void ObjectSetup(void);
static void M538InitHook(s16 mode, s16 frameNo); /* fn_1_1FC: 26 instructions, m538.s:154-181 */
static void M538FadeInHook(s16 mode, s16 frameNo); /* fn_1_264: 144 instructions, m538.s:184-338 */
static void M538StartHook(s16 mode, s16 frameNo); /* fn_1_4A4: 21 instructions, m538.s:341-363 */
static void M538MainHook(s16 mode, s16 frameNo); /* fn_1_4F8: 71 instructions, m538.s:366-443 */
static void M538FinishHook(s16 mode, s16 frameNo); /* fn_1_614: 141 instructions, m538.s:446-605 */
static void M538PreWinnerHook(s16 mode, s16 frameNo); /* fn_1_848: 219 instructions, m538.s:608-849 */
static void M538WinnerHook(s16 mode, s16 frameNo); /* fn_1_BB4: 67 instructions, m538.s:852-928 */
static void M538FadeOutHook(s16 mode, s16 frameNo); /* fn_1_CC0: 15 instructions, m538.s:931-947 */
static void M538CloseHook(s16 mode, s16 frameNo); /* fn_1_CFC: 8 instructions, m538.s:950-959 */
static void M538PlayerMain(OMOBJ *obj); /* fn_1_D1C: 173 instructions, m538.s:962-1138 */
static void M538UnkFD0(OMOBJ *obj); /* fn_1_FD0: 113 instructions, m538.s:1141-1262 */
static void M538Unk1194(void); /* fn_1_1194: 1 instructions, m538.s:1265-1267 */
static void M538HostMain(OMOBJ *obj); /* fn_1_1198: 86 instructions, m538.s:1270-1357 */
static void M538Unk12F0(OMOBJ *obj); /* fn_1_12F0: 34 instructions, m538.s:1360-1396 */
static void M538Unk1378(void); /* fn_1_1378: 1 instructions, m538.s:1399-1401 */
static void M538Unk137C(M538_WORK *work); /* fn_1_137C: 23 instructions, m538.s:1404-1432 */
static void M538Unk13D8(M538_WORK *work); /* fn_1_13D8: 44 instructions, m538.s:1435-1480 */
static void M538Unk1488(M538_WORK *work); /* fn_1_1488: 59 instructions, m538.s:1483-1543 */
static void M538Unk1574(M538_WORK *work); /* fn_1_1574: 55 instructions, m538.s:1546-1602 */
static void M538Unk1650(M538_CAMERA *camera); /* fn_1_1650: 27 instructions, m538.s:1605-1633 */
static void M538Unk16BC(M538_CAMERA *camera); /* fn_1_16BC: 167 instructions, m538.s:1636-1812 */
static void M538Unk1958(M538_WORK *work); /* fn_1_1958: 143 instructions, m538.s:1815-1964 */
static int M538Unk1B94(M538_PLAYER *player); /* fn_1_1B94: 141 instructions, m538.s:1967-2119 */
static int M538Unk1DC8(M538_PLAYER *player); /* fn_1_1DC8: 752 instructions, m538.s:2122-2928 */
static int M538Unk2988(M538_PLAYER *player); /* fn_1_2988: 28 instructions, m538.s:2931-2963 */
static int M538Unk29F8(M538_PLAYER *player); /* fn_1_29F8: 176 instructions, m538.s:2966-3153 */
static int M538Unk2CB8(M538_PLAYER *player); /* fn_1_2CB8: 387 instructions, m538.s:3156-3575 */
static int M538Unk32C4(M538_PLAYER *player); /* fn_1_32C4: 454 instructions, m538.s:3578-4066 */
static int M538Unk39DC(M538_PLAYER *player); /* fn_1_39DC: 84 instructions, m538.s:4069-4160 */
static int M538Unk3B2C(M538_PLAYER *player); /* fn_1_3B2C: 106 instructions, m538.s:4163-4276 */
static int M538Unk3CD4(M538_PLAYER *player); /* fn_1_3CD4: 106 instructions, m538.s:4279-4392 */
static int M538Unk3E7C(M538_PLAYER *player); /* fn_1_3E7C: 57 instructions, m538.s:4395-4457 */
static int M538Unk3F60(M538_PLAYER *player); /* fn_1_3F60: 306 instructions, m538.s:4460-4780 */
static int M538Unk4428(M538_PLAYER *player); /* fn_1_4428: 33 instructions, m538.s:4783-4819 */
static int M538Unk44AC(M538_HUD *hud); /* fn_1_44AC: 34 instructions, m538.s:4822-4860 */
static void M538Unk4534(M538_PLAYER *player); /* fn_1_4534: 120 instructions, m538.s:4863-4987 */
static void M538Unk4714(M538_WORK *work); /* fn_1_4714: 149 instructions, m538.s:4990-5149 */
static void M538Unk4968(M538_WORK *work); /* fn_1_4968: 180 instructions, m538.s:5152-5339 */
static void M538Unk4C38(M538_WORK *work); /* fn_1_4C38: 207 instructions, m538.s:5342-5559 */
static void M538Unk4F74(M538_WORK *work); /* fn_1_4F74: 405 instructions, m538.s:5562-6001 */
static int M538Unk55C8(Vec *pos, float *xs, float *zs); /* fn_1_55C8: 55 instructions, m538.s:6004-6064 */
static void M538Unk56A4(M538_WORK *work); /* fn_1_56A4: 584 instructions, m538.s:6067-6674 */
static void M538Unk5FC4(M538_UNIT *unit, s16 no); /* fn_1_5FC4: 141 instructions, m538.s:6677-6827 */
static int M538Unk61F8(M538_UNIT *unit); /* fn_1_61F8: 47 instructions, m538.s:6830-6881 */
static int M538Unk62B4(M538_UNIT *unit); /* fn_1_62B4: 83 instructions, m538.s:6884-6973 */
static int M538Unk6400(M538_UNIT *unit); /* fn_1_6400: 86 instructions, m538.s:6976-7068 */
static int M538Unk6558(M538_UNIT *unit); /* fn_1_6558: 83 instructions, m538.s:7071-7160 */
static int M538Unk66A4(M538_UNIT *unit); /* fn_1_66A4: 157 instructions, m538.s:7163-7330 */
static int M538Unk6918(M538_UNIT *unit); /* fn_1_6918: 43 instructions, m538.s:7333-7380 */
static void M538Unk69C4(M538_UNK69C4 *p); /* fn_1_69C4: 72 instructions, m538.s:7383-7458 */
static void M538Unk6AE4(M538_PLAYER *player); /* fn_1_6AE4: 80 instructions, m538.s:7461-7544 */
static void M538Unk6C24(M538_PLAYER *player); /* fn_1_6C24: 44 instructions, m538.s:7547-7592 */
static void M538Unk6CD4(M538_WORK *work); /* fn_1_6CD4: 49 instructions, m538.s:7595-7647 */
static M538_MININODE *M538Unk6D98(M538_WORK *work, M538_MINIFUNC func, void *arg); /* fn_1_6D98: 21 instructions, m538.s:7650-7674 */
static void M538Unk6DEC(M538_WORK *work, M538_MININODE *node); /* fn_1_6DEC: 25 instructions, m538.s:7677-7707 */
static void M538Unk6E50(M538_WORK *work); /* fn_1_6E50: 53 instructions, m538.s:7710-7770 */
static int M538Unk6F24(M538_MININODE *node); /* fn_1_6F24: 234 instructions, m538.s:7773-8021 */
static void M538Unk72CC(M538_UNK294 *p); /* fn_1_72CC: 228 instructions, m538.s:8024-8261 */
static void M538Unk765C(M538_UNK294 *p); /* fn_1_765C: 82 instructions, m538.s:8264-8352 */
static void M538Unk77A4(M538_UNK294 *p); /* fn_1_77A4: 58 instructions, m538.s:8355-8418 */
static int M538Unk788C(M538_CAMERA *camera); /* fn_1_788C: 133 instructions, m538.s:8421-8559 */
static int M538Unk7AA0(M538_CAMERA *camera); /* fn_1_7AA0: 132 instructions, m538.s:8562-8699 */
static int M538Unk7CB0(M538_CAMERA *camera); /* fn_1_7CB0: 149 instructions, m538.s:8702-8856 */
static int M538Unk7F04(M538_PLAYER *player); /* fn_1_7F04: 42 instructions, m538.s:8859-8906 */
static int M538Unk7FAC(M538_PLAYER *player); /* fn_1_7FAC: 362 instructions, m538.s:8909-9291 */
static int M538Unk8554(M538_PLAYER *player); /* fn_1_8554: 164 instructions, m538.s:9294-9468 */
static void M538Unk87E4(M538_NODELIST *list, M538_NODE *node, int count); /* fn_1_87E4: 29 instructions, m538.s:9471-9503 */
static M538_NODE *M538Unk8858(M538_NODELIST *list, M538_NODEFUNC func); /* fn_1_8858: 20 instructions, m538.s:9506-9529 */
static void M538Unk88A8(M538_NODE *node); /* fn_1_88A8: 30 instructions, m538.s:9532-9567 */
static void M538Unk8920(M538_NODELIST *list); /* fn_1_8920: 56 instructions, m538.s:9570-9633 */
static void M538Unk8A00(M538_WORK *work); /* fn_1_8A00: 91 instructions, m538.s:9636-9734 */
static void M538Unk8B6C(M538_WORK *work); /* fn_1_8B6C: 91 instructions, m538.s:9737-9835 */
static int M538Unk8CD8(M538_NODE *node); /* fn_1_8CD8: 160 instructions, m538.s:9838-10002 */
static int M538Unk8F58(M538_NODE *node); /* fn_1_8F58: 51 instructions, m538.s:10005-10060 */
static int M538Unk9024(M538_MININODE *node); /* fn_1_9024: 109 instructions, m538.s:10063-10177 */
static int M538Unk91D8(Vec *pos); /* fn_1_91D8: 123 instructions, m538.s:10180-10311 */
static void M538Unk93C4(M538_WORK *work); /* fn_1_93C4: 70 instructions, m538.s:10314-10389 */
static int M538Unk94DC(M538_NODE *node); /* fn_1_94DC: 458 instructions, m538.s:10392-10864 */
static int M538Unk9C04(M538_NODE *node); /* fn_1_9C04: 424 instructions, m538.s:10867-11302 */
static void M538UnkA2A4(M538_WORK *work); /* fn_1_A2A4: 49 instructions, m538.s:11305-11358 */
static void M538UnkA368(M538_WORK *work); /* fn_1_A368: 47 instructions, m538.s:11361-11412 */
static int M538UnkA424(M538_UNK17DC *p); /* fn_1_A424: 181 instructions, m538.s:11415-11609 */
static void M538UnkA6F8(M538_WORK *work); /* fn_1_A6F8: 106 instructions, m538.s:11612-11723 */
static void M538UnkA8A0(M538_UNK17F4 *p); /* fn_1_A8A0: 173 instructions, m538.s:11726-11919 */
static int M538UnkAB54(M538_MININODE *node); /* fn_1_AB54: 351 instructions, m538.s:11922-12284 */
static int M538UnkB0D0(M538_MININODE *node); /* fn_1_B0D0: 69 instructions, m538.s:12287-12361 */

/* --- data --- */

/* lbl_1_data_0 -- the MGSEQ_PARAM ObjectSetup hands to MgSeqCreate. maxTime 0
 * and timerPos 0 are the first word of the object; the nine pointers follow in
 * seqman.h's declaration order. */
static MGSEQ_PARAM SeqParam = {
    0,                              /* maxTime */
    0,                              /* timerPos */
    M538InitHook,
    M538FadeInHook,
    M538StartHook,
    M538MainHook,
    M538FinishHook,
    M538PreWinnerHook,
    M538WinnerHook,
    M538FadeOutHook,
    M538CloseHook,
};

/* lbl_1_rodata_10 -- the four Hu3D camera bits. Only [0] is used so far; the
 * table is read with lhz, so it is u16. */
static u16 CameraBit[4] = { 1, 2, 4, 8 };

/* lbl_1_data_394 -- one knockout effect per character. */
static int KnockFx[13] = {
    0x1F9, 0x1E5, 0x25D, 0x2AD, 0x285, 0x1BD, 0x299,
    0x1D1, 0x271, 0x235, 0x249, 0x221, 0x20D,
};

/* lbl_1_data_3C8 -- one voice effect per character, same charNo order as
 * MotionData[]. */
static int VoiceFx[13] = {
    0x1FD, 0x1E9, 0x261, 0x2B1, 0x289, 0x1C1, 0x29D,
    0x1D5, 0x275, 0x239, 0x24D, 0x225, 0x211,
};

/* lbl_1_data_418 */
static char ObjName_tsumu[] = "m538_tsumu";

/* lbl_1_data_264 -- the 29 model files this overlay loads, indexed by the same
 * number as work->modelId[]. Note [0] is file 9 and [1] onward are 0,1,2,...,
 * so the table is not the identity and must not be replaced by arithmetic. */
static s32 ModelDataNum[29] = {
    DATANUM(DATA_m538, 0x09), DATANUM(DATA_m538, 0x00), DATANUM(DATA_m538, 0x01),
    DATANUM(DATA_m538, 0x02), DATANUM(DATA_m538, 0x03), DATANUM(DATA_m538, 0x04),
    DATANUM(DATA_m538, 0x05), DATANUM(DATA_m538, 0x06), DATANUM(DATA_m538, 0x07),
    DATANUM(DATA_m538, 0x08), DATANUM(DATA_m538, 0x0A), DATANUM(DATA_m538, 0x0B),
    DATANUM(DATA_m538, 0x0C), DATANUM(DATA_m538, 0x0D), DATANUM(DATA_m538, 0x0E),
    DATANUM(DATA_m538, 0x0F), DATANUM(DATA_m538, 0x10), DATANUM(DATA_m538, 0x11),
    DATANUM(DATA_m538, 0x13), DATANUM(DATA_m538, 0x15), DATANUM(DATA_m538, 0x16),
    DATANUM(DATA_m538, 0x17), DATANUM(DATA_m538, 0x19), DATANUM(DATA_m538, 0x1A),
    DATANUM(DATA_m538, 0x1B), DATANUM(DATA_m538, 0x1C), DATANUM(DATA_m538, 0x1D),
    DATANUM(DATA_m538, 0x1E), DATANUM(DATA_m538, 0x1F),
};

/* lbl_1_data_28 -- eleven motions per character, indexed by GwPlayerConf's
 * charNo. Characters 9-12 all repeat minikoopa's set, which is the table's own
 * data and not a transcription slip. */
/* lbl_1_data_2D8 -- the three joint-motion files, cached in work->motId[]
 * beside the model cache and linked the same create-once way. */
static u32 JointMotionData[3] = {
    DATANUM(DATA_m538, 0x12),
    DATANUM(DATA_m538, 0x14),
    DATANUM(DATA_m538, 0x18),
};

static u32 MotionData[13][11] = {
    {
        DATANUM(DATA_mario, 0x7A),
        DATANUM(DATA_mario, 0x7C),
        DATANUM(DATA_mario, 0x7D),
        DATANUM(DATA_mariomot, 0x5C),
        DATANUM(DATA_mariomot, 0x5D),
        DATANUM(DATA_mario, 0x7E),
        DATANUM(DATA_mariomot, 0x2B),
        DATANUM(DATA_mariomot, 0x01),
        DATANUM(DATA_mariomot, 0x06),
        DATANUM(DATA_mariomot, 0x17),
        DATANUM(DATA_mariomot, 0x00),
    },
    {
        DATANUM(DATA_luigi, 0x7A),
        DATANUM(DATA_luigi, 0x7C),
        DATANUM(DATA_luigi, 0x7D),
        DATANUM(DATA_luigimot, 0x5C),
        DATANUM(DATA_luigimot, 0x5D),
        DATANUM(DATA_luigi, 0x7E),
        DATANUM(DATA_luigimot, 0x2B),
        DATANUM(DATA_luigimot, 0x01),
        DATANUM(DATA_luigimot, 0x06),
        DATANUM(DATA_luigimot, 0x17),
        DATANUM(DATA_luigimot, 0x00),
    },
    {
        DATANUM(DATA_peach, 0x7A),
        DATANUM(DATA_peach, 0x7C),
        DATANUM(DATA_peach, 0x7D),
        DATANUM(DATA_peachmot, 0x5C),
        DATANUM(DATA_peachmot, 0x5D),
        DATANUM(DATA_peach, 0x7E),
        DATANUM(DATA_peachmot, 0x2B),
        DATANUM(DATA_peachmot, 0x01),
        DATANUM(DATA_peachmot, 0x06),
        DATANUM(DATA_peachmot, 0x17),
        DATANUM(DATA_peachmot, 0x00),
    },
    {
        DATANUM(DATA_yoshi, 0x7A),
        DATANUM(DATA_yoshi, 0x7C),
        DATANUM(DATA_yoshi, 0x7D),
        DATANUM(DATA_yoshimot, 0x5C),
        DATANUM(DATA_yoshimot, 0x5D),
        DATANUM(DATA_yoshi, 0x7E),
        DATANUM(DATA_yoshimot, 0x2B),
        DATANUM(DATA_yoshimot, 0x01),
        DATANUM(DATA_yoshimot, 0x06),
        DATANUM(DATA_yoshimot, 0x17),
        DATANUM(DATA_yoshimot, 0x00),
    },
    {
        DATANUM(DATA_wario, 0x7A),
        DATANUM(DATA_wario, 0x7C),
        DATANUM(DATA_wario, 0x7D),
        DATANUM(DATA_wariomot, 0x5C),
        DATANUM(DATA_wariomot, 0x5D),
        DATANUM(DATA_wario, 0x7E),
        DATANUM(DATA_wariomot, 0x2B),
        DATANUM(DATA_wariomot, 0x01),
        DATANUM(DATA_wariomot, 0x06),
        DATANUM(DATA_wariomot, 0x17),
        DATANUM(DATA_wariomot, 0x00),
    },
    {
        DATANUM(DATA_daisy, 0x7A),
        DATANUM(DATA_daisy, 0x7C),
        DATANUM(DATA_daisy, 0x7D),
        DATANUM(DATA_daisymot, 0x5C),
        DATANUM(DATA_daisymot, 0x5D),
        DATANUM(DATA_daisy, 0x7E),
        DATANUM(DATA_daisymot, 0x2B),
        DATANUM(DATA_daisymot, 0x01),
        DATANUM(DATA_daisymot, 0x06),
        DATANUM(DATA_daisymot, 0x17),
        DATANUM(DATA_daisymot, 0x00),
    },
    {
        DATANUM(DATA_waluigi, 0x7A),
        DATANUM(DATA_waluigi, 0x7C),
        DATANUM(DATA_waluigi, 0x7D),
        DATANUM(DATA_waluigimot, 0x5C),
        DATANUM(DATA_waluigimot, 0x5D),
        DATANUM(DATA_waluigi, 0x7E),
        DATANUM(DATA_waluigimot, 0x2B),
        DATANUM(DATA_waluigimot, 0x01),
        DATANUM(DATA_waluigimot, 0x06),
        DATANUM(DATA_waluigimot, 0x17),
        DATANUM(DATA_waluigimot, 0x00),
    },
    {
        DATANUM(DATA_kinopio, 0x7A),
        DATANUM(DATA_kinopio, 0x7C),
        DATANUM(DATA_kinopio, 0x7D),
        DATANUM(DATA_kinopiomot, 0x5C),
        DATANUM(DATA_kinopiomot, 0x5D),
        DATANUM(DATA_kinopio, 0x7E),
        DATANUM(DATA_kinopiomot, 0x2B),
        DATANUM(DATA_kinopiomot, 0x01),
        DATANUM(DATA_kinopiomot, 0x06),
        DATANUM(DATA_kinopiomot, 0x17),
        DATANUM(DATA_kinopiomot, 0x00),
    },
    {
        DATANUM(DATA_teresa, 0x7A),
        DATANUM(DATA_teresa, 0x7C),
        DATANUM(DATA_teresa, 0x7D),
        DATANUM(DATA_teresamot, 0x5C),
        DATANUM(DATA_teresamot, 0x5D),
        DATANUM(DATA_teresa, 0x7E),
        DATANUM(DATA_teresamot, 0x2B),
        DATANUM(DATA_teresamot, 0x01),
        DATANUM(DATA_teresamot, 0x06),
        DATANUM(DATA_teresamot, 0x17),
        DATANUM(DATA_teresamot, 0x00),
    },
    {
        DATANUM(DATA_minikoopa, 0x7A),
        DATANUM(DATA_minikoopa, 0x7C),
        DATANUM(DATA_minikoopa, 0x7D),
        DATANUM(DATA_minikoopamot, 0x5C),
        DATANUM(DATA_minikoopamot, 0x5D),
        DATANUM(DATA_minikoopa, 0x7E),
        DATANUM(DATA_minikoopamot, 0x2B),
        DATANUM(DATA_minikoopamot, 0x01),
        DATANUM(DATA_minikoopamot, 0x06),
        DATANUM(DATA_minikoopamot, 0x17),
        DATANUM(DATA_minikoopamot, 0x00),
    },
    {
        DATANUM(DATA_minikoopa, 0x7A),
        DATANUM(DATA_minikoopa, 0x7C),
        DATANUM(DATA_minikoopa, 0x7D),
        DATANUM(DATA_minikoopamot, 0x5C),
        DATANUM(DATA_minikoopamot, 0x5D),
        DATANUM(DATA_minikoopa, 0x7E),
        DATANUM(DATA_minikoopamot, 0x2B),
        DATANUM(DATA_minikoopamot, 0x01),
        DATANUM(DATA_minikoopamot, 0x06),
        DATANUM(DATA_minikoopamot, 0x17),
        DATANUM(DATA_minikoopamot, 0x00),
    },
    {
        DATANUM(DATA_minikoopa, 0x7A),
        DATANUM(DATA_minikoopa, 0x7C),
        DATANUM(DATA_minikoopa, 0x7D),
        DATANUM(DATA_minikoopamot, 0x5C),
        DATANUM(DATA_minikoopamot, 0x5D),
        DATANUM(DATA_minikoopa, 0x7E),
        DATANUM(DATA_minikoopamot, 0x2B),
        DATANUM(DATA_minikoopamot, 0x01),
        DATANUM(DATA_minikoopamot, 0x06),
        DATANUM(DATA_minikoopamot, 0x17),
        DATANUM(DATA_minikoopamot, 0x00),
    },
    {
        DATANUM(DATA_minikoopa, 0x7A),
        DATANUM(DATA_minikoopa, 0x7C),
        DATANUM(DATA_minikoopa, 0x7D),
        DATANUM(DATA_minikoopamot, 0x5C),
        DATANUM(DATA_minikoopamot, 0x5D),
        DATANUM(DATA_minikoopa, 0x7E),
        DATANUM(DATA_minikoopamot, 0x2B),
        DATANUM(DATA_minikoopamot, 0x01),
        DATANUM(DATA_minikoopamot, 0x06),
        DATANUM(DATA_minikoopamot, 0x17),
        DATANUM(DATA_minikoopamot, 0x00),
    },
};

/* The first eighteen floats of lbl_1_data_2E4, which dtk merges with the
 * unrelated 177/0 pairs that follow it. Only [0] is read so far -- M538HostMain
 * copies its six floats into work->camera field by field. */
typedef struct M538CamPreset_s {
    Vec unk00;
    Vec unk0C;
} M538_CAMPRESET;

static M538_CAMPRESET CameraInit[3] = {
    { { 0.0f, 190.0f, -44.0f }, { 90.0f, 7.0f, 3900.0f } },
    { { 0.0f, 0.0f, -44.0f }, { 90.0f, 60.0f, 6700.0f } },
    { { 0.0f, 0.0f, -44.0f }, { 90.0f, 60.0f, 3000.0f } },
};

/* --- .bss --- */

/* Declared in the object's own .bss order. */
static int FxNo0;                   /* lbl_1_bss_0 */
static int FxNo1;                   /* lbl_1_bss_4 */
static int StreamNo;                /* lbl_1_bss_8 */
static OMOBJ *HostObj;              /* lbl_1_bss_C */
static OMOBJMAN *ObjMan;            /* lbl_1_bss_10 */

/* --- stubs --- */

/* ObjectSetup -- 87 instructions, m538.s:61-151 */
void ObjectSetup(void)
{
    OMOBJ *obj;
    M538_WORK *work;
    int i;

    ObjMan = omInitObjMan(10, 0x2000);
    omGameSysInit(ObjMan);
    obj = omAddObjEx(ObjMan, 0x65, 0, 0, OM_GRP_NONE, M538HostMain);
    HostObj = obj;
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M538_WORK), HU_MEMNUM_OVL);
    work = obj->data;
    work->unk18DC = 0;
    M538Unk1488(work);
    M538Unk13D8(work);
    M538Unk1574(work);
    for(i=0; i<4; i++) {
        obj = omAddObjEx(ObjMan, 0x64, 1, 11, 0, M538PlayerMain);
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M538_PLAYER), HU_MEMNUM_OVL);
        obj->work[0] = i;
        work->player[i] = obj->data;
    }
    M538Unk137C(work);
    Hu3DBGColorSet(0, 0, 0);
    Hu3DNoSyncSet(1);
    MgSeqCreate(&SeqParam);
}

/* fn_1_1FC -- 26 instructions, m538.s:154-181 */
static void M538InitHook(s16 mode, s16 frameNo)
{
    M538_WORK *work = HostObj->data;

    M538Unk1958(work);
    work->unk18DC = 0;
    work->unk18D6 = 0;
    work->unk18DA = 0;
    work->unk18D0 = 0;
    work->unk191E = 0;
    MgSeqModeNext();
}

/* fn_1_264 -- 144 instructions, m538.s:184-338 */
static void M538FadeInHook(s16 mode, s16 frameNo)
{
    M538_WORK *work = HostObj->data;

    switch(work->unk18D6) {
        case 0:
            MgSeqModeChangeOff();
            work->unk18D8 = 0;
            work->unk18D6++;
            /* fallthrough */

        case 1:
            work->unk18D8++;
            if(work->unk18D8 == 60) {
                work->unk18D8 = 0;
                work->unk18D6++;
            }
            break;

        case 2:
            HuAudFXPlay(2013);
            work->unk294.unk24 = 0;
            work->unk18D6++;
            /* fallthrough */

        case 3:
            work->unk18D8++;
            M538Unk765C(&work->unk294);
            if(work->unk18D8 == 180) {
                work->unk18D8 = 0;
                work->unk18D6++;
            }
            break;

        case 4:
            work->unit[0].func = M538Unk61F8;
            work->unit[0].unk0C = 0;
            work->unit[1].func = M538Unk61F8;
            work->unit[1].unk0C = 0;
            work->unit[2].func = M538Unk61F8;
            work->unit[2].unk0C = 0;
            work->unk17DC.unk00 = 0;
            work->unk17F0 = M538UnkA424;
            work->camera.unk30 = 0;
            HuAudFXPlay(2014);
            FxNo1 = HuAudFXPlay(2015);
            FxNo0 = HuAudFXPlay(2017);
            work->unk18D6++;
            /* fallthrough */

        case 5:
            M538Unk765C(&work->unk294);
            if(M538Unk788C(&work->camera)) {
                Hu3DModelAttrSet(work->modelId[13], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(work->modelId[14], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(work->modelId[15], HU3D_ATTR_DISPOFF);
                work->camera.unk30 = 0;
                work->unk18D6++;
            }
            break;

        case 6:
            M538Unk765C(&work->unk294);
            StreamNo = HuAudBGMPlay(55);
            work->unk18D8 = 0;
            work->unk18D6 = 0;
            MgSeqModeNext();
            break;
    }
    M538Unk6918(&work->unit[0]);
    if(work->unk17F0 && work->unk17F0(&work->unk17DC)) {
        work->unk17F0 = NULL;
    }
}

/* fn_1_4A4 -- 21 instructions, m538.s:341-363 */
static void M538StartHook(s16 mode, s16 frameNo)
{
    M538_WORK *work = HostObj->data;

    M538Unk765C(&work->unk294);
    M538Unk6918(&work->unit[0]);
    work->unk18D6 = 0;
    work->unk18DA = 0;
}

/* fn_1_4F8 -- 71 instructions, m538.s:366-443 */
static void M538MainHook(s16 mode, s16 frameNo)
{
    M538_WORK *work = HostObj->data;

    switch(work->unk18DA) {
        case 0:
            work->unk18DC = 1;
            work->unk18DA++;
            work->unk18D6 = 0;
            if(work->unk17F0) {
                work->unk17F0 = NULL;
            }
            work->unit[0].unk0C++;
            work->unit[1].unk0C++;
            work->unit[2].unk0C++;
            break;

        case 1:
            break;
    }
    M538Unk7AA0(&work->camera);
    if(work->unk18D0 >= 3) {
        MgSeqModeNext();
        work->unk18DC = 0;
        work->unit[0].unk04 = 0;
        work->unit[1].unk04 = 0;
        work->unit[2].unk04 = 0;
    } else if(M538Unk6918(&work->unit[0])) {
        MgSeqModeNext();
        work->unk18DC = 0;
        work->unit[0].unk04 = 0;
        work->unit[1].unk04 = 0;
        work->unit[2].unk04 = 0;
    }
    M538UnkA8A0(&work->unk17F4);
}

/* fn_1_614 -- 141 instructions, m538.s:446-605 */
static void M538FinishHook(s16 mode, s16 frameNo)
{
    M538_WORK *work = HostObj->data;
    M538_PLAYER *player;
    s16 rank[4];
    int i;
    s16 total;
    s32 no;
    s16 score;
    s16 rk;
    s16 num;

    switch(work->unk18D6) {
        case 0:
            total = 0;
            for(i=0; i<4; i++) {
                player = work->player[i];
                total += player->unkEA;
            }
            if(total == 0) {
                for(i=0; i<4; i++) {
                    player = work->player[i];
                    rank[i] = 3;
                }
                work->unk18D2 = 1;
            } else {
                num = 0;
                score = 3;
                while(num < 4) {
                    rk = num;
                    for(i=0; i<4; i++) {
                        player = work->player[i];
                        if(player->unkEA == score) {
                            rank[i] = rk;
                            num++;
                        }
                    }
                    score--;
                }
                work->unk18D2 = 0;
            }
            for(i=0; i<4; i++) {
                player = work->player[i];
                rk = rank[i];
                no = player->playerNo;
                GWMgCoinBonusSet(no, rk);
                if(player->unkEC) {
                    player->proc = M538Unk7FAC;
                    player->unk88 = 0;
                }
            }
            work->unk18D6++;
            work->unk18DA = 0;
            work->unit[0].func = M538Unk66A4;
            work->unit[0].unk0C = 0;
            work->unit[1].func = M538Unk66A4;
            work->unit[1].unk0C = 0;
            work->unit[2].func = M538Unk66A4;
            work->unit[2].unk0C = 0;
            HuAudSStreamFadeOut(StreamNo, 1000);
            HuAudFXStop(FxNo1);
            HuAudFXStop(FxNo0);
            HuAudFXPlay(2016);
            break;

        case 1:
            break;
    }
    M538Unk6918(&work->unit[0]);
}

/* fn_1_848 -- 219 instructions, m538.s:608-849 */
static void M538PreWinnerHook(s16 mode, s16 frameNo)
{
    M538_WORK *work = HostObj->data;
    M538_PLAYER *player;
    int i;
    int n;

    switch(work->unk18DA) {
        case 0:
            MgSeqModeChangeOff();
            work->unk18D8 = 0;
            work->unk18D6 = 0;
            work->unk17F0 = M538UnkA424;
            work->unk17DC.unk00 = 2;
            if(M538Unk6D98(work, M538UnkB0D0, &work->unk17DC.unk04)) {
                work->unk17DC.unk04.modelId = work->modelId[24];
                work->unk17DC.unk04.unk06 = 0;
            }
            work->unk18DA++;
            work->camera.unk30 = 0;
            /* fallthrough */

        case 1:
            for(i=0; i<4; i++) {
                player = work->player[i];
                if(player->unkEC) {
                    if(player->proc != M538Unk7F04) {
                        break;
                    }
                } else {
                    if(player->proc != M538Unk4428) {
                        break;
                    }
                }
            }
            if(i != 4) {
                break;
            }
            Hu3DModelAttrReset(work->modelId[13], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(work->modelId[14], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(work->modelId[15], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(work->modelId[28], HU3D_ATTR_DISPOFF);
            work->unk294.unk24 = 0;
            work->unk18DA++;
            break;

        case 2:
            work->unk18D8++;
            M538Unk77A4(&work->unk294);
            M538Unk7CB0(&work->camera);
            if(work->unk18D8 == 120) {
                work->unk18D8 = 0;
                work->unk18DA++;
            }
            break;

        case 3:
            M538UnkA368(work);
            M538Unk77A4(&work->unk294);
            if(M538Unk7CB0(&work->camera)) {
                work->unk18DA++;
            }
            break;

        case 4:
            M538UnkA368(work);
            M538Unk77A4(&work->unk294);
            for(i=0; i<4; i++) {
                player = work->player[i];
                if(!player->unkEC) {
                    player->proc = M538Unk8554;
                    player->unk88 = 0;
                    player->unk102 = player->unkEA * 20 + 30;
                }
            }
            Hu3DModelAttrReset(work->modelId[13], HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrReset(work->modelId[14], HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrReset(work->modelId[16], HU3D_MOTATTR_PAUSE);
            Hu3DMotionSpeedSet(work->modelId[13], 0.5f);
            Hu3DMotionSpeedSet(work->modelId[14], 0.5f);
            Hu3DMotionSpeedSet(work->modelId[16], 0.5f);
            work->unk18DA++;
            /* fallthrough */

        case 5:
            M538UnkA368(work);
            M538Unk77A4(&work->unk294);
            n = 0;
            for(i=0; i<4; i++) {
                if(work->player[i]->proc == NULL) {
                    n++;
                }
            }
            if(n >= 3) {
                work->unk18D6 = 0;
                work->unk18DA = 0;
                MgSeqModeNext();
            }
            break;
    }
    M538Unk6918(&work->unit[0]);
    if(work->unk17F0 && work->unk17F0(&work->unk17DC)) {
        work->unk17F0 = NULL;
    }
}

/* fn_1_BB4 -- 67 instructions, m538.s:852-928 */
static void M538WinnerHook(s16 mode, s16 frameNo)
{
    M538_WORK *work = HostObj->data;
    M538_PLAYER *player;
    int i;

    switch(work->unk18D6) {
        case 0:
            work->unk191E = 1;
            for(i=0; i<4; i++) {
                player = work->player[i];
                if(player->unkEC) {
                    player->unk88++;
                }
                CharModelVoicePanSet(player->charNo, 64);
                CharModelVoiceVolSet(player->charNo, 115);
            }
            if(work->unk18D2) {
                HuAudJinglePlay(123);
                CharLoseVoicePlay(work->player[0]->charNo, work->player[1]->charNo,
                                  work->player[2]->charNo, work->player[3]->charNo);
            } else {
                HuAudJinglePlay(121);
            }
            work->unk18D6++;
            /* fallthrough */

        case 1:
            M538UnkA368(work);
            break;
    }
}

/* fn_1_CC0 -- 15 instructions, m538.s:931-947 */
static void M538FadeOutHook(s16 mode, s16 frameNo)
{
    M538_WORK *work = HostObj->data;

    M538UnkA368(work);
}

/* fn_1_CFC -- 8 instructions, m538.s:950-959 */
static void M538CloseHook(s16 mode, s16 frameNo)
{
    /* The original keeps this local and never reads it -- eight instructions
     * that only make sense as a leftover. Removing it changes the object. */
    M538_WORK *work = HostObj->data;
}

/* fn_1_D1C -- 173 instructions, m538.s:962-1138 */
static void M538PlayerMain(OMOBJ *obj)
{
    M538_PLAYER *player = obj->data;
    M538_WORK *work = HostObj->data;
    int i;

    player->playerNo = obj->work[0];
    player->charNo = GwPlayerConf[player->playerNo].charNo;
    player->grp = GwPlayerConf[player->playerNo].grp;
    player->padNo = GwPlayerConf[player->playerNo].padNo;
    player->type = GwPlayerConf[player->playerNo].type;
    player->dif = GwPlayerConf[player->playerNo].dif;
    player->obj = obj;
    work->player[player->playerNo] = player;
    player->unk24.x = 0.0f;
    player->unk24.y = 0.0f;
    player->unk24.z = 0.0f;
    M538Unk4534(player);
    player->proc = M538Unk2CB8;
    player->unk88 = 0;
    player->unkE4 = 0;
    player->unkE6 = 0;
    player->unkEC = 1;
    player->unkC0 = 30.0f;
    obj->mdlId[0] = CharModelCreate(player->charNo, 8);
    player->modelId = obj->mdlId[0];
    player->unk80 = NULL;
    player->hud.modelId = player->modelId;
    player->hud.unk02 = 0;
    player->unkEA = 3;
    for(i=0; i<11; i++) {
        obj->mtnId[i] = CharMotionCreate(player->charNo, MotionData[player->charNo][i]);
    }
    CharMotionSet(player->charNo, obj->mtnId[0]);
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(obj->mdlId[0], 2);
    Hu3DModelShadowSet(obj->mdlId[0]);
    CharEffectLayerSet(4);
    CharMotionDataClose(player->charNo);
    M538Unk6AE4(player);
    player->listA = &work->list[0];
    player->listB = &work->list[1];
    player->target.unk04 = 0;
    player->target.unk0A = 0;
    player->target.pos = NULL;
    CharMotionVoiceOnSet(player->charNo, 0x2B, FALSE);
    CharMotionVoiceOnSet(player->charNo, 0x5C, FALSE);
    CharMotionVoiceOnSet(player->charNo, 0x5D, FALSE);
    obj->objFunc = M538UnkFD0;
}

/* fn_1_FD0 -- 113 instructions, m538.s:1141-1262 */
static void M538UnkFD0(OMOBJ *obj)
{
    M538_PLAYER *player;
    M538_WORK *work;
    float range;
    float pan;
    float vol;

    work = HostObj->data;
    player = obj->data;
    range = work->unit[1].unk00;
    if(work->unk191E == 0) {
        pan = 64.0f + 32.0f * (player->unk00.x / range);
        vol = 115.5f + 11.5f * (player->unk00.z / range);
        player->unkE0 = pan;
        player->unkE2 = vol;
        if(player->unkE0 < 32) {
            player->unkE0 = 32;
        }
        if(player->unkE0 > 96) {
            player->unkE0 = 96;
        }
        if(player->unkE2 < 104) {
            player->unkE2 = 104;
        }
        if(player->unkE2 > 127) {
            player->unkE2 = 127;
        }
        CharModelVoicePanSet(player->charNo, player->unkE0);
        CharModelVoiceVolSet(player->charNo, player->unkE2);
    }
    M538Unk4534(player);
    if(player->proc && player->proc(player)) {
        player->proc = NULL;
    }
    if(player->unk80 && player->unk80(&player->hud)) {
        player->unk80 = NULL;
    }
}

/* fn_1_1194 -- 1 instructions, m538.s:1265-1267 */
static void M538Unk1194(void)
{
}

/* fn_1_1198 -- 86 instructions, m538.s:1270-1357 */
static void M538HostMain(OMOBJ *obj)
{
    M538_WORK *work = HostObj->data;

    M538Unk56A4(work);
    M538Unk5FC4(&work->unit[0], 0);
    M538Unk5FC4(&work->unit[1], 1);
    M538Unk5FC4(&work->unit[2], 2);
    M538Unk1650(&work->camera);
    M538Unk72CC(&work->unk294);
    work->camera.unk00.x = CameraInit[0].unk00.x;
    work->camera.unk00.y = CameraInit[0].unk00.y;
    work->camera.unk00.z = CameraInit[0].unk00.z;
    work->camera.unk0C.x = CameraInit[0].unk0C.x;
    work->camera.unk0C.y = CameraInit[0].unk0C.y;
    work->camera.unk0C.z = CameraInit[0].unk0C.z;
    M538Unk6CD4(work);
    M538Unk8A00(work);
    M538Unk8B6C(work);
    M538Unk93C4(work);
    M538Unk87E4(&work->list[0], work->poolA, 16);
    M538Unk87E4(&work->list[1], work->poolB, 16);
    M538Unk87E4(&work->list[2], work->poolC, 64);
    work->unk18D4 = 0;
    work->unk17DC.unk00 = 0;
    work->unk17F0 = NULL;
    M538UnkA6F8(work);
    obj->objFunc = M538Unk12F0;
}

/* fn_1_12F0 -- 34 instructions, m538.s:1360-1396 */
static void M538Unk12F0(OMOBJ *obj)
{
    M538_WORK *work = HostObj->data;

    M538Unk16BC(&work->camera);
    M538Unk4C38(work);
    M538Unk4F74(work);
    if(work->unit[1].unk04) {
        M538Unk4968(work);
    }
    M538Unk4714(work);
    M538Unk6E50(work);
    M538Unk8920(&work->list[0]);
    M538Unk8920(&work->list[1]);
    M538Unk8920(&work->list[2]);
}

/* fn_1_1378 -- 1 instructions, m538.s:1399-1401 */
static void M538Unk1378(void)
{
}

/* fn_1_137C -- 23 instructions, m538.s:1404-1432 */
static void M538Unk137C(M538_WORK *work)
{
    int i;

    for(i=0; i<29; i++) {
        work->modelId[i] = -1;
    }
    for(i=0; i<3; i++) {
        work->motId[i] = -1;
    }
}

/* fn_1_13D8 -- 44 instructions, m538.s:1435-1480 */
static void M538Unk13D8(M538_WORK *work)
{
    HU3DLIGHTID lightId;

    lightId = Hu3DGLightCreate(0.0f, 4800.0f, 3600.0f, 0.0f, -1.0f, -1.0f, 127, 127, 127);
    Hu3DGLightInfinitytSet(lightId);
    work->lightId = lightId;
    Hu3DGLightColorSet(work->lightId, 127, 127, 127, 0);
}

/* fn_1_1488 -- 59 instructions, m538.s:1483-1543 */
static void M538Unk1488(M538_WORK *work)
{
    Hu3DCameraCreate(CameraBit[0]);
    Hu3DCameraPerspectiveSet(CameraBit[0], 15.0f, 20.0f, 20000.0f, 1.2f);
    Hu3DCameraPosSet(CameraBit[0], 0.0f, 300.0f, 1000.0f, 0.0f, 1.0f, 0.0f, 0.0f, 150.0f, 0.0f);
}

/* fn_1_1574 -- 55 instructions, m538.s:1546-1602 */
static void M538Unk1574(M538_WORK *work)
{
    HuVecF up = { 0.0f, 1.0f, 0.0f };
    HuVecF pos = { 0.0f, 4800.0f, 751.0f };
    HuVecF target = { 0.0f, 0.0f, 0.0f };

    Hu3DShadowCreate(15.0f, 20.0f, 20000.0f);
    Hu3DShadowTPLvlSet(0.4f);
    Hu3DShadowPosSet(&pos, &up, &target);
    Hu3DShadowSizeSet(128);
    Hu3DShadowColSet(15, 15, 15);
}

/* fn_1_1650 -- 27 instructions, m538.s:1605-1633 */
static void M538Unk1650(M538_CAMERA *camera)
{
    camera->unk0C.x = 0.0f;
    camera->unk0C.y = 0.0f;
    camera->unk0C.z = 1000.0f;
    camera->unk00.x = 0.0f;
    camera->unk00.y = 0.0f;
    camera->unk00.z = 0.0f;
    camera->unk30 = 0;
}

/* fn_1_16BC -- 167 instructions, m538.s:1636-1812 */
static void M538Unk16BC(M538_CAMERA *camera)
{
    float x;
    float y;
    float z;

    while(camera->unk0C.x > 360.0f) {
        camera->unk0C.x -= 360.0f;
    }
    while(camera->unk0C.x < 0.0f) {
        camera->unk0C.x += 360.0f;
    }
    while(camera->unk0C.y > 360.0f) {
        camera->unk0C.y -= 360.0f;
    }
    while(camera->unk0C.y < 0.0f) {
        camera->unk0C.y += 360.0f;
    }
    x = camera->unk00.x + camera->unk0C.z * HuCos(camera->unk0C.y) * HuCos(camera->unk0C.x);
    y = camera->unk00.y + camera->unk0C.z * HuSin(camera->unk0C.y);
    z = camera->unk00.z + camera->unk0C.z * HuCos(camera->unk0C.y) * HuSin(camera->unk0C.x);
    Hu3DCameraPosSet(CameraBit[0], x, y, z, 0.0f, 1.0f, 0.0f,
                     camera->unk00.x, camera->unk00.y, camera->unk00.z);
}

/* fn_1_1958 -- 143 instructions, m538.s:1815-1964 */
static void M538Unk1958(M538_WORK *work)
{
    M538_PLAYER *player;
    int i;
    int col;
    int row;
    float nx;
    float nz;
    float ang;
    float a;
    float deg;

    for(i=0; i<4; i++) {
        player = work->player[i];
        col = i % 2;
        row = i / 2;
        player->unk00.x = 300.0f * col - 150.0f;
        player->unk00.y = 0.0f;
        player->unk00.z = 300.0f * row - 150.0f;
        nz = -player->unk00.z;
        nx = -player->unk00.x;
        if(0.0f == nz) {
            if(nx >= 0.0f) {
                ang = 1.5707964f;
            } else {
                ang = -1.5707964f;
            }
        } else {
            /* The extra local is not cosmetic: without it the atan2 result is
             * rounded straight into ang and the function comes out nine
             * instructions short. Same for deg below. */
            a = atan2(nx, nz);
            ang = a;
        }
        deg = 180.0f * ang / M_PI;
        player->unkBC = deg;
        player->unk0C.x = 0.0f;
        player->unk0C.y = deg;
        player->unk0C.z = 0.0f;
        omSetTra(player->obj, player->unk00.x, player->unk00.y, player->unk00.z);
        omSetRot(player->obj, player->unk0C.x, player->unk0C.y, player->unk0C.z);
    }
}

/* fn_1_1B94 -- 141 instructions, m538.s:1967-2119 */
static int M538Unk1B94(M538_PLAYER *player)
{
    int ret;
    M538_WORK *work;
    float x;
    float y;
    float ang;
    float ay;
    float ax;
    float mag;
    float a;

    ret = 0;
    work = HostObj->data;
    if(work->unk18DC == 0) {
        return 0;
    }
    x = HuPadStkX[player->padNo];
    y = -HuPadStkY[player->padNo];
    if(y < 0.0f) {
        ay = -y;
    } else {
        ay = y;
    }
    if(x < 0.0f) {
        ax = -x;
    } else {
        ax = x;
    }
    mag = ax + ay;
    if(mag > 32.0f) {
        if(0.0f == y) {
            if(x >= 0.0f) {
                ang = 1.5707964f;
            } else {
                ang = -1.5707964f;
            }
        } else {
            a = atan2(x, y);
            ang = a;
        }
        player->unkBC = 180.0f * ang / M_PI;
        ret = 1;
    }
    return ret;
}

/* fn_1_1DC8 -- 752 instructions, m538.s:2122-2928 */
static int M538Unk1DC8(M538_PLAYER *player)
{
    int ret = 0;
    s16 fleeProb[4] = { 80, 90, 95, 0 };
    s16 chaseProb[4] = { 20, 50, 60, 80 };
    s16 wanderProb[4] = { 60, 40, 10, 0 };
    s16 edgeProb[4] = { 0, 0, 30, 50 };
    M538_WORK *work;
    M538_TARGET *t;
    M538_PLAYER *q;
    int i;
    int n;
    int k;
    int m;
    float d;
    float best;
    float dd;
    float dx;
    float dz;
    float bx;
    float bz;
    float cx;
    float cz;
    float ex;
    float ez;
    float fx;
    float fz;
    float gx;
    float gz;
    float r;
    float a0;
    float a1;
    float a2;
    float a3;
    float a4;
    float a5;

    work = HostObj->data;
    if(work->unk18DC == 0) {
        return 0;
    }
    t = &player->target;
    switch(t->unk04) {
        case 0:
            t->pos = NULL;
            t->unk0A = 0;
            t->unk04++;
            /* fallthrough */

        case 1:
            d = player->unk00.x * player->unk00.x
              + player->unk00.z * player->unk00.z;
            r = (work->unk18CC - 200.0f) * (work->unk18CC - 200.0f);
            if(d > r && (int)frandmod(100) < fleeProb[player->dif]) {
                dz = -player->unk00.z;
                dx = -player->unk00.x;
                if(0.0f == dz) {
                    if(dx >= 0.0f) {
                        a0 = 1.5707964f;
                    } else {
                        a0 = -1.5707964f;
                    }
                } else {
                    a0 = atan2(dx, dz);
                }
                player->unkBC = 180.0f * a0 / M_PI
                              + 20.0f * ((s32)frandmod(10001) / 10000.0f - 0.5f);
                t->unk06 = 0;
                t->unk08 = frandmod(10) + 10;
                t->unk04 = 2;
                ret = 1;
                break;
            }
            best = 2250000.0f;
            q = NULL;
            for(i=0; i<4; i++) {
                if(i == player->playerNo) {
                    continue;
                }
                if(work->player[i]->unkEC == 0) {
                    continue;
                }
                if(work->player[i]->unkE6 != 0) {
                    continue;
                }
                dx = player->unk00.x - work->player[i]->unk00.x;
                dz = player->unk00.z - work->player[i]->unk00.z;
                dd = dx * dx + dz * dz;
                if(dd < best) {
                    best = dd;
                    q = work->player[i];
                }
            }
            if(best < 160000.0f && q) {
                if((int)frandmod(100) < chaseProb[player->dif]) {
                    t->unk0A = 1;
                    t->pos = &q->unk00;
                    bz = q->unk00.z - player->unk00.z;
                    bx = q->unk00.x - player->unk00.x;
                    if(0.0f == bz) {
                        if(bx >= 0.0f) {
                            a1 = 1.5707964f;
                        } else {
                            a1 = -1.5707964f;
                        }
                    } else {
                        a1 = atan2(bx, bz);
                    }
                    player->unkBC = 180.0f * a1 / M_PI;
                    t->unk06 = 0;
                    t->unk08 = frandmod(10) + 10;
                    t->unk04 = 3;
                    ret = 1;
                } else {
                    t->pos = &q->unk00;
                    cz = player->unk00.z - q->unk00.z;
                    cx = player->unk00.x - q->unk00.x;
                    if(0.0f == cz) {
                        if(cx >= 0.0f) {
                            a2 = 1.5707964f;
                        } else {
                            a2 = -1.5707964f;
                        }
                    } else {
                        a2 = atan2(cx, cz);
                    }
                    ez = -player->unk00.z;
                    ex = -player->unk00.x;
                    if(0.0f == ez) {
                        if(ex >= 0.0f) {
                            a3 = 1.5707964f;
                        } else {
                            a3 = -1.5707964f;
                        }
                    } else {
                        a3 = atan2(ex, ez);
                    }
                    player->unkBC = 180.0f * a2 / M_PI + 180.0f * a3 / M_PI;
                    t->unk06 = 0;
                    t->unk08 = frandmod(10) + 10;
                    t->unk04 = 2;
                    ret = 1;
                }
            } else if((int)frandmod(100) < edgeProb[player->dif]) {
                if(d > 40000.0f) {
                    fz = -player->unk00.z;
                    fx = -player->unk00.x;
                    if(0.0f == fz) {
                        if(fx >= 0.0f) {
                            a4 = 1.5707964f;
                        } else {
                            a4 = -1.5707964f;
                        }
                    } else {
                        a4 = atan2(fx, fz);
                    }
                    player->unkBC = 180.0f * a4 / M_PI
                                  + 20.0f * ((s32)frandmod(10001) / 10000.0f - 0.5f);
                    t->unk06 = 0;
                    t->unk08 = frandmod(10) + 10;
                    t->unk04 = 5;
                    ret = 1;
                } else if(q) {
                    t->unk0A = 1;
                    t->pos = &q->unk00;
                    t->unk06 = 0;
                    t->unk08 = frandmod(3) + 3;
                    t->unk04 = 3;
                } else {
                    t->unk06 = 0;
                    t->unk08 = frandmod(3) + 3;
                    t->unk04 = 4;
                }
            } else if((int)frandmod(100) < wanderProb[player->dif]) {
                t->unk06 = 0;
                t->unk08 = frandmod(10) + 10;
                t->unk04 = 4;
            } else {
                n = 0;
                for(i=0; i<4; i++) {
                    if(i == player->playerNo) {
                        continue;
                    }
                    if(work->player[i]->unkEC == 0) {
                        continue;
                    }
                    n++;
                }
                if(n > 1) {
                    k = frandmod(n);
                } else {
                    k = 0;
                }
                m = 0;
                for(i=0; i<4; i++) {
                    if(i == player->playerNo) {
                        continue;
                    }
                    if(work->player[i]->unkEC == 0) {
                        continue;
                    }
                    if(k == m) {
                        q = work->player[i];
                        break;
                    }
                    m++;
                }
                t->unk0A = 1;
                t->pos = &q->unk00;
                gz = q->unk00.z - player->unk00.z;
                gx = q->unk00.x - player->unk00.x;
                if(0.0f == gz) {
                    if(gx >= 0.0f) {
                        a5 = 1.5707964f;
                    } else {
                        a5 = -1.5707964f;
                    }
                } else {
                    a5 = atan2(gx, gz);
                }
                player->unkBC = 180.0f * a5 / M_PI;
                t->unk06 = 0;
                t->unk08 = frandmod(10) + 10;
                t->unk04 = 3;
                ret = 1;
            }
            break;

        case 2:
            t->unk06++;
            if(t->unk06 == t->unk08) {
                t->unk04 = 0;
            }
            ret = 1;
            break;

        case 3:
            t->unk06++;
            if(t->unk06 == t->unk08 || t->unk0A == 0) {
                t->unk04 = 0;
            }
            ret = 1;
            break;

        case 4:
            t->unk06++;
            if(t->unk06 == t->unk08) {
                t->unk04 = 0;
            }
            break;

        case 5:
            d = player->unk00.x * player->unk00.x
              + player->unk00.z * player->unk00.z;
            t->unk06++;
            if(t->unk06 == t->unk08 || d < 40000.0f) {
                t->unk04 = 0;
            }
            ret = 1;
            break;
    }
    return ret;
}

/* fn_1_2988 -- 28 instructions, m538.s:2931-2963 */
static int M538Unk2988(M538_PLAYER *player)
{
    int ret;
    M538_WORK *work;

    ret = 0;
    work = HostObj->data;
    if(work->unk18DC == 0) {
        return 0;
    }
    if(HuPadBtnDown[player->padNo] & PAD_BUTTON_A) {
        ret = 1;
    }
    return ret;
}

/* fn_1_29F8 -- 176 instructions, m538.s:2966-3153 */
static int M538Unk29F8(M538_PLAYER *player)
{
    int ret = 0;
    float range[4] = { 26244.0f, 24964.0f, 23716.0f, 22500.0f };
    int prob[4] = { 50, 70, 90, 100 };
    M538_WORK *work;
    M538_TARGET *t;
    float dx;
    float dz;
    float ang;
    float d;
    float diff;
    float a;

    work = HostObj->data;
    if(work->unk18DC == 0) {
        return 0;
    }
    t = &player->target;
    if(t->unk0A != 0 && t->pos) {
        dx = t->pos->x - player->unk00.x;
        dz = t->pos->z - player->unk00.z;
        d = dx * dx + dz * dz;
        if(d < range[player->dif]) {
            if(0.0f == dz) {
                if(dx >= 0.0f) {
                    ang = 1.5707964f;
                } else {
                    ang = -1.5707964f;
                }
            } else {
                a = atan2(dx, dz);
                ang = a;
            }
            diff = 180.0f * ang / M_PI - player->unkBC;
            while(diff > 180.0f) {
                diff -= 360.0f;
            }
            while(diff < -180.0f) {
                diff += 360.0f;
            }
            if(fabsf(diff) < 90.0f) {
                if((int)frandmod(100) < prob[player->dif]) {
                    t->unk0A = 0;
                    ret = 1;
                }
            }
        }
    }
    return ret;
}

/* fn_1_2CB8 -- 387 instructions, m538.s:3156-3575 */
static int M538Unk2CB8(M538_PLAYER *player)
{
    int r;

    switch(player->unk88) {
        case 0:
            player->unkE6 = 0;
            CharMotionShiftSet(player->charNo, player->obj->mtnId[0], 0.0f, 5.0f,
                               HU3D_MOTATTR_LOOP);
            player->unk88++;
            /* fallthrough */

        case 1:
            if(player->type) {
                /* M538Unk29F8 written out longhand: at 176 instructions it is
                 * past this compiler's auto-inline threshold, and marking it
                 * `inline` would drop the out-of-line copy the object has. It
                 * is unreferenced for exactly that reason. */
                int ret2 = 0;
                float range[4] = { 26244.0f, 24964.0f, 23716.0f, 22500.0f };
                int prob[4] = { 50, 70, 90, 100 };
                M538_WORK *w;
                M538_TARGET *t;
                float dx;
                float dz;
                float ang;
                float d;
                float diff;
                float a2;

                w = HostObj->data;
                if(w->unk18DC == 0) {
                    ret2 = 0;
                } else {
                    t = &player->target;
                    if(t->unk0A != 0 && t->pos) {
                        dx = t->pos->x - player->unk00.x;
                        dz = t->pos->z - player->unk00.z;
                        d = dx * dx + dz * dz;
                        if(d < range[player->dif]) {
                            if(0.0f == dz) {
                                if(dx >= 0.0f) {
                                    ang = 1.5707964f;
                                } else {
                                    ang = -1.5707964f;
                                }
                            } else {
                                a2 = atan2(dx, dz);
                                ang = a2;
                            }
                            diff = 180.0f * ang / M_PI - player->unkBC;
                            while(diff > 180.0f) {
                                diff -= 360.0f;
                            }
                            while(diff < -180.0f) {
                                diff += 360.0f;
                            }
                            if(fabsf(diff) < 90.0f) {
                                if((int)frandmod(100) < prob[player->dif]) {
                                    t->unk0A = 0;
                                    ret2 = 1;
                                }
                            }
                        }
                    }
                }
                r = ret2;
            } else {
                r = M538Unk2988(player);
            }
            if(r) {
                player->proc = M538Unk39DC;
                player->unk88 = 0;
            } else {
                if(player->type) {
                    r = M538Unk1DC8(player);
                } else {
                    r = M538Unk1B94(player);
                }
                if(r) {
                    player->proc = M538Unk32C4;
                    player->unk88 = 0;
                }
            }
            break;
    }
    return 0;
}

/* fn_1_32C4 -- 454 instructions, m538.s:3578-4066 */
static int M538Unk32C4(M538_PLAYER *player)
{
    M538_NODE *node;
    int r;
    float t;

    switch(player->unk88) {
        case 0:
            player->unkE6 = 0;
            CharMotionShiftSet(player->charNo, player->obj->mtnId[1], 0.0f, 5.0f,
                               HU3D_MOTATTR_LOOP);
            player->unk88++;
            /* fallthrough */

        case 1:
            if(player->type) {
                /* M538Unk29F8 written out longhand: at 176 instructions it is
                 * past this compiler's auto-inline threshold, and marking it
                 * `inline` would drop the out-of-line copy the object has. It
                 * is unreferenced for exactly that reason. */
                int ret2 = 0;
                float range[4] = { 26244.0f, 24964.0f, 23716.0f, 22500.0f };
                int prob[4] = { 50, 70, 90, 100 };
                M538_WORK *w;
                M538_TARGET *t;
                float dx;
                float dz;
                float ang;
                float d;
                float diff;
                float a2;

                w = HostObj->data;
                if(w->unk18DC == 0) {
                    ret2 = 0;
                } else {
                    t = &player->target;
                    if(t->unk0A != 0 && t->pos) {
                        dx = t->pos->x - player->unk00.x;
                        dz = t->pos->z - player->unk00.z;
                        d = dx * dx + dz * dz;
                        if(d < range[player->dif]) {
                            if(0.0f == dz) {
                                if(dx >= 0.0f) {
                                    ang = 1.5707964f;
                                } else {
                                    ang = -1.5707964f;
                                }
                            } else {
                                a2 = atan2(dx, dz);
                                ang = a2;
                            }
                            diff = 180.0f * ang / M_PI - player->unkBC;
                            while(diff > 180.0f) {
                                diff -= 360.0f;
                            }
                            while(diff < -180.0f) {
                                diff += 360.0f;
                            }
                            if(fabsf(diff) < 90.0f) {
                                if((int)frandmod(100) < prob[player->dif]) {
                                    t->unk0A = 0;
                                    ret2 = 1;
                                }
                            }
                        }
                    }
                }
                r = ret2;
            } else {
                r = M538Unk2988(player);
            }
            if(r) {
                player->proc = M538Unk39DC;
                player->unk88 = 0;
            } else {
                if(player->type) {
                    r = M538Unk1DC8(player);
                } else {
                    r = M538Unk1B94(player);
                }
                if(r) {
                    player->unk18.x += 7.5 * HuSin(player->unkBC);
                    player->unk18.z += 7.5 * HuCos(player->unkBC);
                    t = Hu3DMotionTimeGet(player->modelId);
                    if(15.0f == t || 30.0f == t) {
                        node = M538Unk8858(player->listA, M538Unk8CD8);
                        if(node) {
                            node->unk10 = player->unk00;
                            node->unk30 = 0;
                        }
                    }
                } else {
                    player->proc = M538Unk2CB8;
                    player->unk88 = 0;
                }
            }
            break;
    }
    return 0;
}

/* fn_1_39DC -- 84 instructions, m538.s:4069-4160 */
static int M538Unk39DC(M538_PLAYER *player)
{
    switch(player->unk88) {
        case 0:
            player->unkE6 = 0;
            CharMotionShiftSet(player->charNo, player->obj->mtnId[2], 0.0f, 5.0f, 0);
            HuAudFXPlayVolPan(2018, player->unkE2, player->unkE0);
            player->unkE8 = 0;
            player->unk88++;
            /* fallthrough */

        case 1:
            if(player->obj->mtnId[2] == Hu3DMotionIDGet(player->modelId)) {
                CharMotionSpeedSet(player->charNo, 1.2f);
                player->unk88++;
            }
            break;

        case 2:
            player->unkE8++;
            if(player->unkE8 >= 9 && player->unkE4 <= 5) {
                player->unkE4++;
            }
            if(Hu3DMotionEndCheck(player->modelId)) {
                player->proc = M538Unk2CB8;
                player->unk88 = 0;
                player->unkE4 = 0;
            }
            break;
    }
    return 0;
}

/* fn_1_3B2C -- 106 instructions, m538.s:4163-4276 */
static int M538Unk3B2C(M538_PLAYER *player)
{
    M538_NODE *node;

    switch(player->unk88) {
        case 0:
            player->target.unk04 = 0;
            player->unkE4 = 0;
            player->unkE6 = 1;
            CharMotionShiftSet(player->charNo, player->obj->mtnId[3], 0.0f, 5.0f, 0);
            node = M538Unk8858(player->listB, M538Unk8F58);
            if(node) {
                node->unk10 = player->unk00;
                node->unk30 = 0;
            }
            HuAudFXPlayVolPan(2019, player->unkE2, player->unkE0);
            HuAudFXPlayVolPan(VoiceFx[player->charNo], player->unkE2, player->unkE0);
            player->unk88++;
            /* fallthrough */

        case 1:
            player->unk18.x = player->unk24.x;
            player->unk18.z = player->unk24.z;
            if(player->obj->mtnId[3] == Hu3DMotionIDGet(player->modelId)) {
                CharMotionSpeedSet(player->charNo, 2.0f);
                player->unk88++;
            }
            break;

        case 2:
            player->unk18.x = player->unk24.x;
            player->unk18.z = player->unk24.z;
            if(Hu3DMotionEndCheck(player->modelId)) {
                player->proc = M538Unk3E7C;
                player->unk88 = 0;
            }
            break;
    }
    return 0;
}

/* fn_1_3CD4 -- 106 instructions, m538.s:4279-4392 */
static int M538Unk3CD4(M538_PLAYER *player)
{
    M538_NODE *node;

    switch(player->unk88) {
        case 0:
            player->target.unk04 = 0;
            player->unkE4 = 0;
            player->unkE6 = 1;
            CharMotionShiftSet(player->charNo, player->obj->mtnId[4], 0.0f, 5.0f, 0);
            node = M538Unk8858(player->listB, M538Unk8F58);
            if(node) {
                node->unk10 = player->unk00;
                node->unk30 = 0;
            }
            HuAudFXPlayVolPan(2019, player->unkE2, player->unkE0);
            HuAudFXPlayVolPan(VoiceFx[player->charNo], player->unkE2, player->unkE0);
            player->unk88++;
            /* fallthrough */

        case 1:
            player->unk18.x = player->unk24.x;
            player->unk18.z = player->unk24.z;
            if(player->obj->mtnId[4] == Hu3DMotionIDGet(player->modelId)) {
                CharMotionSpeedSet(player->charNo, 2.0f);
                player->unk88++;
            }
            break;

        case 2:
            player->unk18.x = player->unk24.x;
            player->unk18.z = player->unk24.z;
            if(Hu3DMotionEndCheck(player->modelId)) {
                player->proc = M538Unk3E7C;
                player->unk88 = 0;
            }
            break;
    }
    return 0;
}

/* fn_1_3E7C -- 57 instructions, m538.s:4395-4457 */
static int M538Unk3E7C(M538_PLAYER *player)
{
    M538_NODE *node;

    switch(player->unk88) {
        case 0:
            player->target.unk04 = 0;
            CharMotionSet(player->charNo, player->obj->mtnId[5]);
            node = M538Unk8858(player->listA, M538Unk8CD8);
            if(node) {
                node->unk10 = player->unk00;
                node->unk30 = 0;
            }
            player->unk88++;
            /* fallthrough */

        case 1:
            if(Hu3DMotionEndCheck(player->modelId)) {
                player->unk80 = M538Unk44AC;
                player->proc = M538Unk32C4;
                player->unk88 = 0;
            }
            break;
    }
    return 0;
}

/* fn_1_3F60 -- 306 instructions, m538.s:4460-4780 */
static int M538Unk3F60(M538_PLAYER *player)
{
    M538_WORK *work;
    float x;
    float z;
    float ang;
    float d;
    float sx;
    float sz;
    float a;

    work = HostObj->data;
    switch(player->unk88) {
        case 0:
            M538Unk6C24(player);
            CharMotionShiftSet(player->charNo, player->obj->mtnId[6], 0.0f, 5.0f,
                               HU3D_MOTATTR_LOOP);
            z = player->unk00.z;
            x = player->unk00.x;
            if(0.0f == z) {
                if(x >= 0.0f) {
                    ang = 1.5707964f;
                } else {
                    ang = -1.5707964f;
                }
            } else {
                a = atan2(x, z);
                ang = a;
            }
            player->unkA4 = 180.0f * ang / M_PI;
            d = player->unk00.x * player->unk00.x
              + player->unk00.z * player->unk00.z;
            player->unkA8 = sqrtf(d);
            player->unk0C.y = player->unkBC;
            if(M538Unk6D98(work, M538Unk6F24, &player->throwWork)) {
                player->throwWork.pos = player->unk30;
                player->throwWork.rot = player->unk3C;
                player->throwWork.modelId = player->itemModelId;
                player->throwWork.unk2A = 0;
            }
            player->unk100 = 0;
            omVibrate(player->playerNo, 30, 12, 0);
            player->target.fxNo = HuAudFXPlay(KnockFx[player->charNo]);
            player->unk88++;
            /* fallthrough */

        case 1:
            HuAudFXPanning(player->target.fxNo, player->unkE0);
            HuAudFXVolSet(player->target.fxNo, player->unkE2);
            player->unkA4 -= 6.3f;
            player->unk18.y = 2.0f;
            player->unkA8 += 4.3f;
            sx = player->unkA8 * HuSin(player->unkA4);
            sz = player->unkA8 * HuCos(player->unkA4);
            player->unk00.x = sx;
            player->unk00.z = sz;
            player->unkBC += 1.0f;
            while(player->unkBC > 180.0f) {
                player->unkBC -= 360.0f;
            }
            player->unk0C.y += 3.0f;
            while(player->unk0C.y > 180.0f) {
                player->unk0C.y -= 360.0f;
            }
            player->unk100++;
            if(player->unk100 == 180) {
                player->proc = M538Unk4428;
                player->unk88 = 0;
            }
            break;
    }
    return 0;
}

/* fn_1_4428 -- 33 instructions, m538.s:4783-4819 */
static int M538Unk4428(M538_PLAYER *player)
{
    switch(player->unk88) {
        case 0:
            CharMotionSet(player->charNo, player->obj->mtnId[10]);
            CharModelAttrSet(player->charNo, HU3D_ATTR_DISPOFF);
            CharModelAttrSet(player->charNo, HU3D_MOTATTR_PAUSE);
            player->unk88++;
            break;

        case 1:
            break;
    }
    return 0;
}

/* fn_1_44AC -- 34 instructions, m538.s:4822-4860 */
static int M538Unk44AC(M538_HUD *hud)
{
    int ret;

    ret = 0;
    hud->unk02++;
    if(hud->unk02 == 60) {
        hud->unk02 = 0;
        ret = 1;
    }
    if(hud->unk02 & 1) {
        Hu3DModelAttrSet(hud->modelId, HU3D_ATTR_DISPOFF);
    } else {
        Hu3DModelAttrReset(hud->modelId, HU3D_ATTR_DISPOFF);
    }
    return ret;
}

/* fn_1_4534 -- 120 instructions, m538.s:4863-4987 */
static void M538Unk4534(M538_PLAYER *player)
{
    float x;
    float y;
    float z;

    player->unk18.x = 0.0f;
    player->unk18.y = 0.0f;
    player->unk18.z = 0.0f;
    player->unk24.x *= 0.9f;
    player->unk24.y *= 0.9f;
    player->unk24.z *= 0.9f;
    x = player->unk24.x;
    if(fabsf2(x) < 0.01f) {
        player->unk24.x = 0.0f;
    }
    y = player->unk24.y;
    if(fabsf2(y) < 0.01f) {
        player->unk24.y = 0.0f;
    }
    z = player->unk24.z;
    if(fabsf2(z) < 0.01f) {
        player->unk24.z = 0.0f;
    }
}

/* fn_1_4714 -- 149 instructions, m538.s:4990-5149 */
static void M538Unk4714(M538_WORK *work)
{
    M538_PLAYER *player;
    int i;
    float target;
    float d;

    for(i=0; i<4; i++) {
        player = work->player[i];
        player->unk00.x += player->unk18.x;
        player->unk00.y += player->unk18.y;
        player->unk00.z += player->unk18.z;
        target = player->unkBC;
        d = player->unk0C.y - player->unkBC;
        if(fabsf2(d) > 180.0f) {
            if(player->unk0C.y < player->unkBC) {
                target = player->unkBC - 360.0f;
            } else if(player->unk0C.y > player->unkBC) {
                target = 360.0f + player->unkBC;
            }
        }
        if(player->unk0C.y < target) {
            player->unk0C.y += player->unkC0;
            if(player->unk0C.y > target) {
                player->unk0C.y = target;
            }
        } else if(player->unk0C.y > target) {
            player->unk0C.y -= player->unkC0;
            if(player->unk0C.y < target) {
                player->unk0C.y = target;
            }
        }
        while(player->unk0C.y > 180.0f) {
            player->unk0C.y -= 360.0f;
        }
        while(player->unk0C.y < -180.0f) {
            player->unk0C.y += 360.0f;
        }
        Hu3DModelPosSetV(player->modelId, &player->unk00);
        omSetTra(player->obj, player->unk00.x, player->unk00.y, player->unk00.z);
        Hu3DModelRotSetV(player->modelId, &player->unk0C);
        omSetRot(player->obj, player->unk0C.x, player->unk0C.y, player->unk0C.z);
    }
}

/* fn_1_4968 -- 180 instructions, m538.s:5152-5339 */
static void M538Unk4968(M538_WORK *work)
{
    M538_PLAYER *player;
    int i;
    s16 n;
    float r;
    float d;

    r = work->unit[1].unk00;
    work->unk18CC = r;
    n = 0;
    for(i=0; i<4; i++) {
        player = work->player[i];
        if(player->proc != M538Unk3F60 && player->proc != M538Unk4428
           && player->unkEC != 0) {
            d = player->unk00.x * player->unk00.x
              + player->unk00.z * player->unk00.z;
            if(d > r * r) {
                M538Unk4534(player);
                player->proc = M538Unk3F60;
                player->unk88 = 0;
                player->unkEC = 0;
                player->unkEA = work->unk18D0;
                n++;
            }
        }
    }
    work->unk18D0 += n;
}

/* fn_1_4C38 -- 207 instructions, m538.s:5342-5559 */
static void M538Unk4C38(M538_WORK *work)
{
    M538_PLAYER *p;
    M538_PLAYER *q;
    int i;
    int j;
    float dx;
    float dz;
    float d;
    float ang;
    float deg;
    float a;

    for(i=0; i<3; i++) {
        p = work->player[i];
        if(p->proc == M538Unk3F60 || p->proc == M538Unk4428 || p->unkEC == 0) {
            continue;
        }
        for(j=i+1; j<4; j++) {
            q = work->player[j];
            if(q->proc == M538Unk3F60 || q->proc == M538Unk4428 || q->unkEC == 0) {
                continue;
            }
            dx = p->unk00.x - q->unk00.x;
            dz = p->unk00.z - q->unk00.z;
            d = dx * dx + dz * dz;
            if(d < 12100.0f) {
                if(0.0f == dz) {
                    if(dx >= 0.0f) {
                        ang = 1.5707964f;
                    } else {
                        ang = -1.5707964f;
                    }
                } else {
                    a = atan2(dx, dz);
                    ang = a;
                }
                deg = 180.0f * ang / M_PI;
                p->unk18.x = 0.5f * p->unk18.x + 3.75 * HuSin(deg);
                p->unk18.z = 0.5f * p->unk18.z + 3.75 * HuCos(deg);
                q->unk18.x = 0.5f * q->unk18.x - 3.75 * HuSin(deg);
                q->unk18.z = 0.5f * q->unk18.z - 3.75 * HuCos(deg);
            }
        }
    }
}

/* fn_1_4F74 -- 405 instructions, m538.s:5562-6001 */
static void M538Unk4F74(M538_WORK *work)
{
    float qx[4] = { -100.0f, -100.0f, 100.0f, 100.0f };
    float qz[4] = { 0.0f, 150.0f, 150.0f, 0.0f };
    float hx[4];
    float hz[4];
    M538_PLAYER *p;
    M538_PLAYER *q;
    int i;
    int j;
    float ang;
    float sn;
    float cs;
    float dx;
    float dz;
    float a;
    float hit;
    float diff;

    for(i=0; i<4; i++) {
        p = work->player[i];
        if(p->unkE4 == 0) {
            continue;
        }
        ang = (p->unk0C.y - 60.0f) + 120.0f * p->unkE4 / 5.0f;
        while(ang > 180.0f) {
            ang -= 360.0f;
        }
        while(ang < -180.0f) {
            ang += 360.0f;
        }
        sn = HuSin(ang);
        cs = HuCos(ang);
        for(j=0; j<4; j++) {
            hx[j] = p->unk00.x + (cs * qx[j] + sn * qz[j]);
            hz[j] = p->unk00.z + (sn * -qx[j] + cs * qz[j]);
        }
        for(j=0; j<4; j++) {
            if(i == j) {
                continue;
            }
            q = work->player[j];
            if(q->unkE6) {
                continue;
            }
            if(q->unk80) {
                continue;
            }
            if(!M538Unk55C8(&q->unk00, hx, hz)) {
                continue;
            }
            omVibrate(p->playerNo, 12, 6, 6);
            omVibrate(q->playerNo, 12, 12, 0);
            dx = p->unk00.x - q->unk00.x;
            dz = p->unk00.z - q->unk00.z;
            if(0.0f == dz) {
                if(dx >= 0.0f) {
                    a = 1.5707964f;
                } else {
                    a = -1.5707964f;
                }
            } else {
                diff = atan2(dx, dz);
                a = diff;
            }
            hit = 180.0 + 180.0f * a / M_PI;
            while(hit > 180.0f) {
                hit -= 360.0f;
            }
            while(hit < -180.0f) {
                hit += 360.0f;
            }
            q->unk24.x = 35.0 * HuSin(hit);
            q->unk24.z = 35.0 * HuCos(hit);
            diff = q->unk0C.y - hit;
            while(diff > 180.0f) {
                diff -= 360.0f;
            }
            while(diff < -180.0f) {
                diff += 360.0f;
            }
            diff = fabsf2(diff);
            if(diff < 90.0f) {
                q->unkBC = hit;
                while(q->unkBC > 180.0f) {
                    q->unkBC -= 360.0f;
                }
                while(q->unkBC < -180.0f) {
                    q->unkBC += 360.0f;
                }
                q->proc = M538Unk3B2C;
            } else {
                q->unkBC = 180.0f + hit;
                while(q->unkBC > 180.0f) {
                    q->unkBC -= 360.0f;
                }
                while(q->unkBC < -180.0f) {
                    q->unkBC += 360.0f;
                }
                q->proc = M538Unk3CD4;
            }
            q->unk88 = 0;
        }
    }
}

/* fn_1_55C8 -- 55 instructions, m538.s:6004-6064 */
static int M538Unk55C8(Vec *pos, float *xs, float *zs)
{
    int i;
    float d;

    for(i=0; i<4; i++) {
        d = (pos->x - xs[i]) * (zs[(i + 1) % 4] - zs[i])
          - (pos->z - zs[i]) * (xs[(i + 1) % 4] - xs[i]);
        if(d < 0.0f) {
            return FALSE;
        }
    }
    return TRUE;
}

/* fn_1_56A4 -- 584 instructions, m538.s:6067-6674 */
static void M538Unk56A4(M538_WORK *work)
{
    HU3DMODELID model;
    HU3DMOTID mot;
    int i;
    float ang;
    float x;
    float z;

    if(work->modelId[11] < 0) {
        model = work->modelId[11] = Hu3DModelCreateData(ModelDataNum[11]);
    } else {
        model = Hu3DModelLink(work->modelId[11]);
    }
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(model, 0);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelShadowMapSet(model);
    Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
    Hu3DMotionSpeedSet(model, 0.0f);
    if(work->modelId[12] < 0) {
        model = work->modelId[12] = Hu3DModelCreateData(ModelDataNum[12]);
    } else {
        model = Hu3DModelLink(work->modelId[12]);
    }
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(model, 3);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelShadowMapSet(model);
    Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
    Hu3DMotionSpeedSet(model, 0.0f);
    if(work->modelId[13] < 0) {
        model = work->modelId[13] = Hu3DModelCreateData(ModelDataNum[13]);
    } else {
        model = Hu3DModelLink(work->modelId[13]);
    }
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(model, 0);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
    if(work->modelId[14] < 0) {
        model = work->modelId[14] = Hu3DModelCreateData(ModelDataNum[14]);
    } else {
        model = Hu3DModelLink(work->modelId[14]);
    }
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(model, 0);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
    if(work->modelId[15] < 0) {
        model = work->modelId[15] = Hu3DModelCreateData(ModelDataNum[15]);
    } else {
        model = Hu3DModelLink(work->modelId[15]);
    }
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(model, 0);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
    if(work->modelId[16] < 0) {
        model = work->modelId[16] = Hu3DModelCreateData(ModelDataNum[16]);
    } else {
        model = Hu3DModelLink(work->modelId[16]);
    }
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(model, 0);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
    if(work->modelId[24] < 0) {
        model = work->modelId[24] = Hu3DModelCreateData(ModelDataNum[24]);
    } else {
        model = Hu3DModelLink(work->modelId[24]);
    }
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(model, 3);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
    if(work->modelId[28] < 0) {
        model = work->modelId[28] = Hu3DModelCreateData(ModelDataNum[28]);
    } else {
        model = Hu3DModelLink(work->modelId[28]);
    }
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(model, 3);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    for(i=0; i<24; i++) {
        if(work->modelId[17] < 0) {
            model = work->modelId[17] = Hu3DModelCreateData(ModelDataNum[17]);
        } else {
            model = Hu3DModelLink(work->modelId[17]);
        }
        if(work->motId[0] < 0) {
            mot = work->motId[0] = Hu3DJointMotion(model,
                HuDataSelHeapReadNum(JointMotionData[0], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            mot = work->motId[0];
        }
        Hu3DMotionSet(model, mot);
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(model, 1);
        ang = M_PI * (15.0f * i) / 180.0;
        x = 750.0 * sin(ang);
        z = 750.0 * cos(ang);
        Hu3DModelPosSet(model, x, 0.0f, z);
        Hu3DModelRotSet(model, 0.0f, 15.0f * i, 0.0f);
        Hu3DModelShadowMapSet(model);
        Hu3DMotionSpeedSet(model, 0.0f);
        Hu3DMotionTimeSet(model, (s32)frandmod(16));
        Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
    }
}

/* fn_1_5FC4 -- 141 instructions, m538.s:6677-6827 */
static void M538Unk5FC4(M538_UNIT *unit, s16 no)
{
    s16 modelBase[3] = { 1, 4, 7 };
    float y;
    M538_WORK *work;
    HU3DMODELID model;
    int i;

    if(no == 1) {
        y = 50.0f;
    } else {
        y = 0.0f;
    }
    work = HostObj->data;
    for(i=0; i<3; i++) {
        if(work->modelId[modelBase[no] + i] < 0) {
            model = work->modelId[modelBase[no] + i] =
                Hu3DModelCreateData(ModelDataNum[modelBase[no] + i]);
        } else {
            model = Hu3DModelLink(work->modelId[modelBase[no] + i]);
        }
        unit->model[i] = model;
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
        if(no == 1) {
            Hu3DModelLayerSet(model, 7);
        } else {
            Hu3DModelLayerSet(model, 6);
        }
        Hu3DModelPosSet(model, 0.0f, y, 0.0f);
        Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    }
    unit->unk00 = 750.0f;
    unit->unk0C = 0;
    unit->unk0E = 0;
    unit->unk04 = 1;
    unit->func = NULL;
    unit->no = no;
}

/* fn_1_61F8 -- 47 instructions, m538.s:6830-6881 */
static int M538Unk61F8(M538_UNIT *unit)
{
    M538_UNITFUNC next[3] = { M538Unk62B4, M538Unk6400, M538Unk6558 };

    switch(unit->unk0C) {
        case 0:
            Hu3DModelAttrReset(unit->model[0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(unit->model[0], HU3D_MOTATTR_PAUSE);
            unit->unk0C++;
            /* fallthrough */

        case 1:
            if(Hu3DMotionEndCheck(unit->model[0])) {
                unit->func = next[unit->no];
                unit->unk0C = 0;
            }
            break;
    }
    return 0;
}

/* fn_1_62B4 -- 83 instructions, m538.s:6884-6973 */
static int M538Unk62B4(M538_UNIT *unit)
{
    int ret;
    float y;

    ret = 0;
    switch(unit->unk0C) {
        case 0:
            Hu3DModelAttrReset(unit->model[1], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(unit->model[1], HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(unit->model[1], HU3D_MOTATTR_LOOP);
            Hu3DModelAttrSet(unit->model[0], HU3D_ATTR_DISPOFF);
            unit->unk0C++;
            break;

        case 1:
            break;

        case 2:
            unit->unk0E++;
            if(unit->unk0E == 1800) {
                unit->unk0C++;
                ret = 1;
            }
            y = 630.0f * unit->unk0E / 1800.0f;
            Hu3DModelPosSet(unit->model[1], 0.0f, y, 0.0f);
            break;
    }
    return ret;
}

/* fn_1_6400 -- 86 instructions, m538.s:6976-7068 */
static int M538Unk6400(M538_UNIT *unit)
{
    int ret;
    float scale;

    ret = 0;
    switch(unit->unk0C) {
        case 0:
            Hu3DModelAttrReset(unit->model[1], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(unit->model[1], HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(unit->model[1], HU3D_MOTATTR_LOOP);
            Hu3DModelAttrSet(unit->model[0], HU3D_ATTR_DISPOFF);
            unit->unk0C++;
            break;

        case 1:
            break;

        case 2:
            unit->unk0E++;
            if(unit->unk0E == 1800) {
                unit->unk0C++;
                ret = 1;
            }
            scale = 1.0f - unit->unk0E / 1800.0f;
            unit->unk00 = 750.0f * scale;
            Hu3DModelScaleSet(unit->model[1], scale, 1.0f, scale);
            break;
    }
    return ret;
}

/* fn_1_6558 -- 83 instructions, m538.s:7071-7160 */
static int M538Unk6558(M538_UNIT *unit)
{
    int ret;
    float y;

    ret = 0;
    switch(unit->unk0C) {
        case 0:
            Hu3DModelAttrReset(unit->model[1], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(unit->model[1], HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(unit->model[1], HU3D_MOTATTR_LOOP);
            Hu3DModelAttrSet(unit->model[0], HU3D_ATTR_DISPOFF);
            unit->unk0C++;
            break;

        case 1:
            break;

        case 2:
            unit->unk0E++;
            if(unit->unk0E == 1800) {
                unit->unk0C++;
                ret = 1;
            }
            y = 270.0f * unit->unk0E / 1800.0f;
            Hu3DModelPosSet(unit->model[1], 0.0f, y, 0.0f);
            break;
    }
    return ret;
}

/* fn_1_66A4 -- 157 instructions, m538.s:7163-7330 */
static int M538Unk66A4(M538_UNIT *unit)
{
    float y;
    float scale;

    switch(unit->unk0C) {
        case 0:
            Hu3DModelAttrReset(unit->model[1], HU3D_MOTATTR_LOOP);
            unit->unk0C++;
            /* fallthrough */

        case 1:
            if(Hu3DMotionEndCheck(unit->model[1])) {
                unit->unk0C++;
            }
            break;

        case 2:
            Hu3DModelAttrReset(unit->model[2], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(unit->model[2], HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(unit->model[1], HU3D_ATTR_DISPOFF);
            if(unit->no == 0) {
                y = 630.0f * unit->unk0E / 1800.0f;
                Hu3DModelPosSet(unit->model[2], 0.0f, y, 0.0f);
            }
            if(unit->no == 1) {
                scale = 1.0f - unit->unk0E / 1800.0f;
                Hu3DModelScaleSet(unit->model[2], scale, 1.0f, scale);
            }
            if(unit->no == 2) {
                y = 270.0f * unit->unk0E / 1800.0f;
                Hu3DModelPosSet(unit->model[2], 0.0f, y, 0.0f);
            }
            unit->unk0C++;
            /* fallthrough */

        case 3:
            if(Hu3DMotionEndCheck(unit->model[2])) {
                Hu3DModelAttrSet(unit->model[2], HU3D_ATTR_DISPOFF);
                unit->func = NULL;
                unit->unk0C = 0;
            }
            break;
    }
    return 0;
}

/* fn_1_6918 -- 43 instructions, m538.s:7333-7380 */
static int M538Unk6918(M538_UNIT *unit)
{
    M538_WORK *work;
    int ret;

    ret = 0;
    work = HostObj->data;
    if(work->unit[0].func) {
        work->unit[0].func(&work->unit[0]);
    }
    if(work->unit[1].func) {
        ret = work->unit[1].func(&work->unit[1]);
    }
    if(work->unit[2].func) {
        work->unit[2].func(&work->unit[2]);
        M538UnkA2A4(work);
    }
    ret &= work->unit[1].unk04;
    return ret;
}

/* fn_1_69C4 -- 72 instructions, m538.s:7383-7458 */
static void M538Unk69C4(M538_UNK69C4 *p)
{
    M538_WORK *work;
    HU3DMODELID model;

    work = HostObj->data;
    if(work->modelId[0] < 0) {
        model = work->modelId[0] = Hu3DModelCreateData(ModelDataNum[0]);
    } else {
        model = Hu3DModelLink(work->modelId[0]);
    }
    p->modelId = model;
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(model, 2);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelShadowSet(model);
    Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
}

/* fn_1_6AE4 -- 80 instructions, m538.s:7461-7544 */
static void M538Unk6AE4(M538_PLAYER *player)
{
    M538_WORK *work;
    HU3DMODELID model;

    work = HostObj->data;
    if(work->modelId[0] < 0) {
        model = work->modelId[0] = Hu3DModelCreateData(ModelDataNum[0]);
    } else {
        model = Hu3DModelLink(work->modelId[0]);
    }
    player->itemModelId = model;
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(model, 2);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelShadowSet(model);
    Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
    Hu3DModelHookSet(player->modelId, CharModelItemHookGet(player->charNo, 8, 0),
                     player->itemModelId);
}

/* fn_1_6C24 -- 44 instructions, m538.s:7547-7592 */
static void M538Unk6C24(M538_PLAYER *player)
{
    Mtx mtx;
    Vec trans;
    Vec rot;

    Hu3DModelObjMtxGet(player->modelId, CharModelItemHookGet(player->charNo, 8, 0), mtx);
    Hu3DMtxTransGet(mtx, &trans);
    Hu3DMtxRotGet(mtx, &rot);
    Hu3DModelHookReset(player->modelId);
    player->unk30 = trans;
    player->unk3C = rot;
    Hu3DModelPosSetV(player->itemModelId, &trans);
    Hu3DModelRotSetV(player->itemModelId, &rot);
}

/* fn_1_6CD4 -- 49 instructions, m538.s:7595-7647 */
static void M538Unk6CD4(M538_WORK *work)
{
    int i;

    for(i=0; i<31; i++) {
        work->mini[i].prev = NULL;
        work->mini[i].next = &work->mini[i + 1];
        work->mini[i].func = NULL;
        work->mini[i].unk0C = 0;
    }
    work->mini[i].prev = NULL;
    work->mini[i].next = NULL;
    work->mini[i].func = NULL;
    work->mini[i].unk0C = 0;
    work->miniActive = NULL;
    work->miniFree = &work->mini[0];
}

/* fn_1_6D98 -- 21 instructions, m538.s:7650-7674 */
static M538_MININODE *M538Unk6D98(M538_WORK *work, M538_MINIFUNC func, void *arg)
{
    M538_MININODE *node;

    node = work->miniFree;
    if(node) {
        work->miniFree = node->next;
        node->func = func;
        node->unk0C = arg;
        node->next = work->miniActive;
        if(node->next) {
            node->next->prev = node;
        }
        work->miniActive = node;
    }
    return node;
}

/* fn_1_6DEC -- 25 instructions, m538.s:7677-7707 */
static void M538Unk6DEC(M538_WORK *work, M538_MININODE *node)
{
    if(node) {
        if(node->prev) {
            node->prev->next = node->next;
        } else {
            work->miniActive = node->next;
        }
        if(node->next) {
            node->next->prev = node->prev;
        }
        node->prev = NULL;
        node->next = work->miniFree;
        node->func = NULL;
        work->miniFree = node;
    }
}

/* fn_1_6E50 -- 53 instructions, m538.s:7710-7770 */
static void M538Unk6E50(M538_WORK *work)
{
    M538_MININODE *node;
    M538_MININODE *next;

    node = work->miniActive;
    while(node) {
        next = node->next;
        if(node->func && node->func(node)) {
            M538Unk6DEC(work, node);
        }
        node = next;
    }
}

/* fn_1_6F24 -- 234 instructions, m538.s:7773-8021 */
static int M538Unk6F24(M538_MININODE *node)
{
    M538_THROW *p;
    int ret;
    float x;
    float z;
    float ang;
    float d;
    float a;

    ret = 0;
    p = node->unk0C;
    switch(p->unk2A) {
        case 0:
            z = p->pos.z;
            x = p->pos.x;
            if(0.0f == z) {
                if(x >= 0.0f) {
                    ang = 1.5707964f;
                } else {
                    ang = -1.5707964f;
                }
            } else {
                a = atan2(x, z);
                ang = a;
            }
            p->unk18 = 180.0f * ang / M_PI;
            d = p->pos.x * p->pos.x + p->pos.z * p->pos.z;
            p->unk1C = sqrtf(d);
            p->unk2C = 0;
            p->unk2A++;
            /* fallthrough */

        case 1:
            p->unk2C++;
            if(p->unk2C == 240) {
                Hu3DModelAttrSet(p->modelId, HU3D_ATTR_DISPOFF);
                ret = 1;
            }
            p->unk18 -= 6.1f;
            p->unk1C += 4.1f;
            p->pos.x = p->unk1C * HuSin(p->unk18);
            p->pos.z = p->unk1C * HuCos(p->unk18);
            p->rot.y += 4.0f;
            while(p->rot.y > 180.0f) {
                p->rot.y -= 360.0f;
            }
            while(p->rot.y < -180.0f) {
                p->rot.y += 360.0f;
            }
            Hu3DModelPosSetV(p->modelId, &p->pos);
            Hu3DModelRotSetV(p->modelId, &p->rot);
            break;
    }
    return ret;
}

/* fn_1_72CC -- 228 instructions, m538.s:8024-8261 */
static void M538Unk72CC(M538_UNK294 *p)
{
    M538_WORK *work;
    HU3DMODELID model;

    work = HostObj->data;
    if(work->modelId[10] < 0) {
        model = work->modelId[10] = Hu3DModelCreateData(ModelDataNum[10]);
    } else {
        model = Hu3DModelLink(work->modelId[10]);
    }
    p->unk28 = model;
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(model, 7);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    if(work->modelId[19] < 0) {
        model = work->modelId[19] = Hu3DModelCreateData(ModelDataNum[19]);
    } else {
        model = Hu3DModelLink(work->modelId[19]);
    }
    p->unk2A = model;
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(model, 2);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    if(work->modelId[20] < 0) {
        model = work->modelId[20] = Hu3DModelCreateData(ModelDataNum[20]);
    } else {
        model = Hu3DModelLink(work->modelId[20]);
    }
    p->unk2C = model;
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(model, 2);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    if(work->modelId[23] < 0) {
        model = work->modelId[23] = Hu3DModelCreateData(ModelDataNum[23]);
    } else {
        model = Hu3DModelLink(work->modelId[23]);
    }
    p->unk2E = model;
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(model, 7);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    p->unk18 = 0.0f;
    p->unk20 = 150.0f;
    p->unk1C = 0.0f;
    p->unk24 = 0;
}

/* fn_1_765C -- 82 instructions, m538.s:8264-8352 */
static void M538Unk765C(M538_UNK294 *p)
{
    switch(p->unk24) {
        case 0:
            p->unk26 = 0;
            p->unk18 = 30.0f;
            Hu3DModelAttrReset(p->unk28, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(p->unk2A, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(p->unk2A, HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrReset(p->unk2E, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(p->unk2E, HU3D_MOTATTR_PAUSE);
            Hu3DMotionSpeedSet(p->unk2E, 0.6f);
            Hu3DModelHookSet(p->unk2A, ObjName_tsumu, p->unk28);
            p->unk24++;
            /* fallthrough */

        case 1:
            if(Hu3DMotionEndCheck(p->unk2A)) {
                Hu3DModelHookReset(p->unk2A);
                Hu3DModelAttrSet(p->unk28, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(p->unk2A, HU3D_ATTR_DISPOFF);
                p->unk24++;
            }
            break;

        case 2:
            if(Hu3DMotionEndCheck(p->unk2E)) {
                Hu3DModelAttrSet(p->unk2E, HU3D_ATTR_DISPOFF);
                p->unk24++;
            }
            break;

        case 3:
        case 4:
            break;
    }
}

/* fn_1_77A4 -- 58 instructions, m538.s:8355-8418 */
static void M538Unk77A4(M538_UNK294 *p)
{
    switch(p->unk24) {
        case 0:
            p->unk26 = 0;
            p->unk24++;
            p->unk18 = 30.0f;
            Hu3DModelAttrReset(p->unk28, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(p->unk2C, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(p->unk2C, HU3D_MOTATTR_PAUSE);
            Hu3DModelHookSet(p->unk2C, ObjName_tsumu, p->unk28);
            /* fallthrough */

        case 1:
            if(Hu3DMotionEndCheck(p->unk2C)) {
                Hu3DModelHookReset(p->unk2C);
                Hu3DModelAttrSet(p->unk28, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(p->unk2C, HU3D_ATTR_DISPOFF);
                p->unk24++;
            }
            break;

        case 2:
        case 3:
            break;
    }
}

/* fn_1_788C -- 133 instructions, m538.s:8421-8559 */
static int M538Unk788C(M538_CAMERA *camera)
{
    int ret;
    float t;
    float u;

    ret = 0;
    switch(camera->unk30) {
        case 0:
            camera->unk32 = 0;
            camera->unk30++;
            /* fallthrough */

        case 1:
            camera->unk32++;
            if(camera->unk32 == 180) {
                ret = 1;
            }
            t = HuSin(90.0f * camera->unk32 / 180.0f);
            u = 1.0f - t;
            camera->unk0C.x = CameraInit[0].unk0C.x * u + CameraInit[1].unk0C.x * t;
            camera->unk0C.y = CameraInit[0].unk0C.y * u + CameraInit[1].unk0C.y * t;
            camera->unk0C.z = CameraInit[0].unk0C.z * u + CameraInit[1].unk0C.z * t;
            camera->unk00.x = CameraInit[0].unk00.x * u + CameraInit[1].unk00.x * t;
            camera->unk00.y = CameraInit[0].unk00.y * u + CameraInit[1].unk00.y * t;
            camera->unk00.z = CameraInit[0].unk00.z * u + CameraInit[1].unk00.z * t;
            break;
    }
    return ret;
}

/* fn_1_7AA0 -- 132 instructions, m538.s:8562-8699 */
static int M538Unk7AA0(M538_CAMERA *camera)
{
    int ret;
    float t;
    float u;

    ret = 0;
    switch(camera->unk30) {
        case 0:
            camera->unk32 = 0;
            camera->unk30++;
            /* fallthrough */

        case 1:
            if(camera->unk32 < 1800) {
                camera->unk32++;
            }
            t = HuSin(90.0f * camera->unk32 / 1800.0f);
            u = 1.0f - t;
            camera->unk0C.x = CameraInit[1].unk0C.x * u + CameraInit[2].unk0C.x * t;
            camera->unk0C.y = CameraInit[1].unk0C.y * u + CameraInit[2].unk0C.y * t;
            camera->unk0C.z = CameraInit[1].unk0C.z * u + CameraInit[2].unk0C.z * t;
            camera->unk00.x = CameraInit[1].unk00.x * u + CameraInit[2].unk00.x * t;
            camera->unk00.y = CameraInit[1].unk00.y * u + CameraInit[2].unk00.y * t;
            camera->unk00.z = CameraInit[1].unk00.z * u + CameraInit[2].unk00.z * t;
            break;
    }
    return ret;
}

/* fn_1_7CB0 -- 149 instructions, m538.s:8702-8856 */
static int M538Unk7CB0(M538_CAMERA *camera)
{
    int ret;
    float t;

    ret = 0;
    switch(camera->unk30) {
        case 0:
            camera->unk32 = 0;
            camera->unk24.x = camera->unk0C.x;
            camera->unk24.y = camera->unk0C.y;
            camera->unk24.z = camera->unk0C.z;
            camera->unk18.x = camera->unk00.x;
            camera->unk18.y = camera->unk00.y;
            camera->unk18.z = camera->unk00.z;
            camera->unk30++;
            /* fallthrough */

        case 1:
            camera->unk32++;
            if(camera->unk32 == 150) {
                ret = 1;
            }
            t = HuSin(90.0f * camera->unk32 / 150.0f);
            camera->unk0C.x = camera->unk24.x * (1.0f - t) + CameraInit[0].unk0C.x * t;
            camera->unk0C.y = camera->unk24.y * (1.0f - t) + CameraInit[0].unk0C.y * t;
            camera->unk0C.z = camera->unk24.z * (1.0f - t) + CameraInit[0].unk0C.z * t;
            camera->unk00.x = camera->unk18.x * (1.0f - t) + CameraInit[0].unk00.x * t;
            camera->unk00.y = camera->unk18.y * (1.0f - t) + CameraInit[0].unk00.y * t;
            camera->unk00.z = camera->unk18.z * (1.0f - t) + CameraInit[0].unk00.z * t;
            break;
    }
    return ret;
}

/* fn_1_7F04 -- 42 instructions, m538.s:8859-8906 */
static int M538Unk7F04(M538_PLAYER *player)
{
    int ret;

    ret = 0;
    switch(player->unk88) {
        case 0:
            player->unk88++;
            break;

        case 2:
            CharMotionShiftSet(player->charNo, player->obj->mtnId[8], 0.0f, 5.0f, 0);
            player->unk88++;
            break;

        case 3:
        case 4:
            break;
    }
    return ret;
}

/* fn_1_7FAC -- 362 instructions, m538.s:8909-9291 */
static int M538Unk7FAC(M538_PLAYER *player)
{
    M538_WORK *work;
    M538_NODE *node;
    Mtx mtx;
    Vec rot;
    Vec trans;
    int ret;
    float nx;
    float nz;
    float ang;
    float d;
    float t;
    float a;

    ret = 0;
    work = HostObj->data;
    switch(player->unk88) {
        case 0:
            nz = -player->unk00.z;
            nx = -player->unk00.x;
            if(0.0f == nz) {
                if(nx >= 0.0f) {
                    ang = 1.5707964f;
                } else {
                    ang = -1.5707964f;
                }
            } else {
                a = atan2(nx, nz);
                ang = a;
            }
            player->unkBC = 180.0f * ang / M_PI;
            CharMotionShiftSet(player->charNo, player->obj->mtnId[0], 0.0f, 5.0f,
                               HU3D_MOTATTR_LOOP);
            player->unk88++;
            /* fallthrough */

        case 1:
            if(player->obj->mtnId[0] == Hu3DMotionIDGet(player->modelId)
               && Hu3DMotionShiftIDGet(player->modelId) == -1) {
                player->unk88++;
            }
            break;

        case 2:
            CharMotionSet(player->charNo, player->obj->mtnId[1]);
            player->unk88++;
            /* fallthrough */

        case 3:
            d = player->unk00.x * player->unk00.x
              + player->unk00.z * player->unk00.z;
            if(d < 225.0f) {
                player->unk88++;
                break;
            }
            player->unk18.x = 7.5 * HuSin(player->unkBC);
            player->unk18.z = 7.5 * HuCos(player->unkBC);
            t = Hu3DMotionTimeGet(player->modelId);
            if(15.0f == t || 30.0f == t) {
                node = M538Unk8858(player->listA, M538Unk8CD8);
                if(node) {
                    node->unk10 = player->unk00;
                    node->unk30 = 0;
                }
            }
            break;

        case 4:
            player->unkBC = 0.0f;
            player->unkC0 = 5.0f;
            player->unk88++;
            /* fallthrough */

        case 5:
            t = Hu3DMotionTimeGet(player->modelId);
            if(15.0f == t || 30.0f == t) {
                node = M538Unk8858(player->listA, M538Unk8CD8);
                if(node) {
                    node->unk10 = player->unk00;
                    node->unk30 = 0;
                }
            }
            a = player->unk0C.y;
            if(fabsf2(a) < 1.0f) {
                player->unk88++;
            }
            break;

        case 6:
            Hu3DModelObjMtxGet(player->modelId,
                               CharModelItemHookGet(player->charNo, 8, 0), mtx);
            Hu3DMtxTransGet(mtx, &trans);
            Hu3DMtxRotGet(mtx, &rot);
            Hu3DModelHookReset(player->modelId);
            player->unk30 = trans;
            player->unk3C = rot;
            Hu3DModelPosSetV(player->itemModelId, &trans);
            Hu3DModelRotSetV(player->itemModelId, &rot);
            if(M538Unk6D98(work, M538Unk9024, &player->throwWork)) {
                player->throwWork.pos = player->unk30;
                player->throwWork.rot = player->unk3C;
                player->throwWork.modelId = player->itemModelId;
                player->throwWork.unk2A = 0;
            }
            CharMotionShiftSet(player->charNo, player->obj->mtnId[10], 0.0f, 5.0f,
                               HU3D_MOTATTR_LOOP);
            player->unk88++;
            /* fallthrough */

        case 7:
            player->proc = M538Unk7F04;
            player->unk88 = 0;
            break;
    }
    return ret;
}

/* fn_1_8554 -- 164 instructions, m538.s:9294-9468 */
static int M538Unk8554(M538_PLAYER *player)
{
    int ret = 0;
    float x[4] = { -400.0f, -200.0f, 200.0f, 400.0f };
    M538_NODE *node;

    switch(player->unk88) {
        case 0:
            Hu3DModelShadowReset(player->obj->mdlId[0]);
            player->unk100 = 0;
            player->unk88++;
            /* fallthrough */

        case 1:
            player->unk100++;
            if(player->unk100 == player->unk102) {
                player->unk100 = 0;
                player->unk102 = 0;
                player->unk88++;
            }
            break;

        case 2:
            CharModelAttrReset(player->charNo, HU3D_ATTR_DISPOFF);
            CharMotionSet(player->charNo, player->obj->mtnId[9]);
            CharModelAttrSet(player->charNo, HU3D_MOTATTR_LOOP);
            CharModelAttrReset(player->charNo, HU3D_MOTATTR_PAUSE);
            player->unk00.x = x[player->playerNo];
            player->unk00.y = 800.0f;
            player->unk00.z = 0.0f;
            player->unk88++;
            /* fallthrough */

        case 3:
            if(player->unk00.y < 600.0f) {
                Hu3DModelShadowSet(player->obj->mdlId[0]);
                player->unk88++;
            }
            /* fallthrough */

        case 4:
            player->unk100++;
            player->unk00.y -= 1.3f * player->unk100;
            if(player->unk00.y <= 10.0f) {
                node = M538Unk8858(player->listA, M538Unk8CD8);
                if(node) {
                    node->unk10 = player->unk00;
                    node->unk30 = 0;
                }
                player->unk00.y = 0.0f;
                player->unk88++;
            }
            break;

        case 5:
            player->proc = NULL;
            player->unk88 = 0;
            break;
    }
    return ret;
}

/* fn_1_87E4 -- 29 instructions, m538.s:9471-9503 */
static void M538Unk87E4(M538_NODELIST *list, M538_NODE *node, int count)
{
    int i;

    list->active = NULL;
    list->free = node;
    for(i=0; i<count-1; i++, node++) {
        node->prev = NULL;
        node->next = node + 1;
        node->func = NULL;
        node->list = list;
    }
    node->prev = NULL;
    node->next = NULL;
    node->func = NULL;
    node->list = list;
}

/* fn_1_8858 -- 20 instructions, m538.s:9506-9529 */
static M538_NODE *M538Unk8858(M538_NODELIST *list, M538_NODEFUNC func)
{
    M538_NODE *node;

    node = list->free;
    if(node) {
        list->free = node->next;
        node->func = func;
        node->next = list->active;
        if(node->next) {
            node->next->prev = node;
        }
        list->active = node;
    }
    return node;
}

/* fn_1_88A8 -- 30 instructions, m538.s:9532-9567 */
static void M538Unk88A8(M538_NODE *node)
{
    M538_NODELIST *list;

    if(node) {
        list = node->list;
        if(node->prev) {
            node->prev->next = node->next;
        } else {
            list->active = node->next;
        }
        if(node->next) {
            node->next->prev = node->prev;
        }
        node->prev = NULL;
        node->next = list->free;
        node->func = NULL;
        list->free = node;
    }
}

/* fn_1_8920 -- 56 instructions, m538.s:9570-9633 */
static void M538Unk8920(M538_NODELIST *list)
{
    M538_NODE *node;
    M538_NODE *next;

    node = list->active;
    while(node) {
        next = node->next;
        if(node->func && node->func(node)) {
            M538Unk88A8(node);
        }
        node = next;
    }
}

/* fn_1_8A00 -- 91 instructions, m538.s:9636-9734 */
static void M538Unk8A00(M538_WORK *work)
{
    int i;
    HU3DMODELID model;
    HU3DMOTID mot;

    for(i=0; i<16; i++) {
        if(work->modelId[21] < 0) {
            model = work->modelId[21] = Hu3DModelCreateData(ModelDataNum[21]);
        } else {
            model = Hu3DModelLink(work->modelId[21]);
        }
        if(work->motId[2] < 0) {
            mot = work->motId[2] = Hu3DJointMotion(model,
                HuDataSelHeapReadNum(JointMotionData[2], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            mot = work->motId[2];
        }
        Hu3DMotionSet(model, mot);
        work->poolA[i].modelId = model;
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(model, 4);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    }
}

/* fn_1_8B6C -- 91 instructions, m538.s:9737-9835 */
static void M538Unk8B6C(M538_WORK *work)
{
    int i;
    HU3DMODELID model;
    HU3DMOTID mot;

    for(i=0; i<16; i++) {
        if(work->modelId[18] < 0) {
            model = work->modelId[18] = Hu3DModelCreateData(ModelDataNum[18]);
        } else {
            model = Hu3DModelLink(work->modelId[18]);
        }
        if(work->motId[1] < 0) {
            mot = work->motId[1] = Hu3DJointMotion(model,
                HuDataSelHeapReadNum(JointMotionData[1], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            mot = work->motId[1];
        }
        Hu3DMotionSet(model, mot);
        work->poolB[i].modelId = model;
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(model, 4);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    }
}

/* fn_1_8CD8 -- 160 instructions, m538.s:9838-10002 */
static int M538Unk8CD8(M538_NODE *node)
{
    int ret = 0;
    u8 col[8][3] = {
        { 0xD9, 0x99, 0x52 }, { 0xB3, 0xCC, 0x00 },
        { 0xE0, 0x99, 0x52 }, { 0xE6, 0x66, 0x33 },
        { 0x99, 0x66, 0x99 }, { 0xBF, 0x33, 0x99 },
        { 0xFF, 0xB3, 0xCC }, { 0xE6, 0x7F, 0x99 },
    };
    HSFMATERIAL *mat;
    int n;

    switch(node->unk30) {
        case 0:
            Hu3DModelAttrReset(node->modelId, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(node->modelId, HU3D_MOTATTR_PAUSE);
            Hu3DModelPosSetV(node->modelId, &node->unk10);
            Hu3DMotionTimeSet(node->modelId, 0.0f);
            mat = Hu3DData[node->modelId].hsf->material;
            n = M538Unk91D8(&node->unk10) * 2;
            mat->color[0] = col[n][0];
            mat->color[1] = col[n][1];
            mat->color[2] = col[n][2];
            mat++;
            mat->color[0] = col[n][0];
            mat->color[1] = col[n][1];
            mat->color[2] = col[n][2];
            mat++;
            n++;
            mat->color[0] = col[n][0];
            mat->color[1] = col[n][1];
            mat->color[2] = col[n][2];
            node->unk30++;
            /* fallthrough */

        case 1:
            if(Hu3DMotionEndCheck(node->modelId)) {
                Hu3DModelAttrSet(node->modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(node->modelId, HU3D_MOTATTR_PAUSE);
                ret = 1;
            }
            break;
    }
    return ret;
}

/* fn_1_8F58 -- 51 instructions, m538.s:10005-10060 */
static int M538Unk8F58(M538_NODE *node)
{
    int ret;

    ret = 0;
    switch(node->unk30) {
        case 0:
            Hu3DModelAttrReset(node->modelId, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(node->modelId, HU3D_MOTATTR_PAUSE);
            Hu3DModelPosSetV(node->modelId, &node->unk10);
            Hu3DMotionTimeSet(node->modelId, 0.0f);
            node->unk30++;
            /* fallthrough */

        case 1:
            if(Hu3DMotionEndCheck(node->modelId)) {
                Hu3DModelAttrSet(node->modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(node->modelId, HU3D_MOTATTR_PAUSE);
                ret = 1;
            }
            break;
    }
    return ret;
}

/* fn_1_9024 -- 109 instructions, m538.s:10063-10177 */
static int M538Unk9024(M538_MININODE *node)
{
    M538_THROW *p;
    int ret;
    float t;

    ret = 0;
    p = node->unk0C;
    switch(p->unk2A) {
        case 0:
            p->unk2C = 0;
            p->unk1C = p->rot.y;
            p->unk18 = p->rot.z;
            p->rot.x = 0.0f;
            p->rot.y = 0.0f;
            p->rot.z = 0.0f;
            p->unk2A++;
            /* fallthrough */

        case 1:
            p->rot.x -= 40.0f;
            p->pos.y += 3.0f;
            p->pos.z -= 6.0f;
            p->unk2C++;
            if(p->unk2C == 60) {
                ret = 1;
            }
            t = 1.0f - p->unk2C / 60.0f;
            p->rot.y = p->unk1C * t;
            p->rot.z = p->unk18 * t;
            Hu3DModelScaleSet(p->modelId, t, t, t);
            Hu3DModelPosSetV(p->modelId, &p->pos);
            Hu3DModelRotSetV(p->modelId, &p->rot);
            break;
    }
    return ret;
}

/* fn_1_91D8 -- 123 instructions, m538.s:10180-10311 */
static int M538Unk91D8(Vec *pos)
{
    int ret;
    float d;
    float ang;
    float a;
    float x;
    float z;
    float t;

    ret = -1;
    d = pos->x * pos->x + pos->z * pos->z;
    if(d < 62500.0f) {
        ret = 0;
    } else if(d < 250000.0f) {
        z = pos->z;
        x = pos->x;
        if(0.0f == z) {
            if(x >= 0.0f) {
                ang = 1.5707964f;
            } else {
                ang = -1.5707964f;
            }
        } else {
            t = atan2(x, z);
            ang = t;
        }
        ang = 180.0f * ang / M_PI;
        a = fabsf2(ang);
        if(a >= 45.0f && a < 135.0f) {
            ret = 2;
        } else {
            ret = 1;
        }
    } else {
        ret = 3;
    }
    return ret;
}

/* fn_1_93C4 -- 70 instructions, m538.s:10314-10389 */
static void M538Unk93C4(M538_WORK *work)
{
    int i;
    HU3DMODELID model;

    for(i=0; i<64; i++) {
        if(work->modelId[22] < 0) {
            model = work->modelId[22] = Hu3DModelCreateData(ModelDataNum[22]);
        } else {
            model = Hu3DModelLink(work->modelId[22]);
        }
        work->poolC[i].modelId = model;
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(model, 4);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    }
}

/* fn_1_94DC -- 458 instructions, m538.s:10392-10864 */
static int M538Unk94DC(M538_NODE *node)
{
    int ret = 0;
    u8 col[16][3] = {
        { 0xFF, 0xB3, 0x00 }, { 0xE5, 0xFF, 0x66 }, { 0xFF, 0xE5, 0x4D },
        { 0xCC, 0xB3, 0x00 }, { 0xCC, 0x66, 0x33 }, { 0xFF, 0xE5, 0x4D },
        { 0xFF, 0xA6, 0x4D }, { 0x7F, 0x33, 0x00 }, { 0xB3, 0x4D, 0xB3 },
        { 0xE5, 0xB3, 0xE5 }, { 0xCC, 0x7F, 0xE5 }, { 0x7F, 0x33, 0x7F },
        { 0xCC, 0x66, 0x7F }, { 0xFF, 0xBF, 0xCC }, { 0xFF, 0x7F, 0x99 },
        { 0xA6, 0x4D, 0x7F },
    };
    HSFMATERIAL *mat;
    int n;
    int i;
    float s;

    switch(node->unk30) {
        case 0:
            node->unk2C = 360.0f * ((s32)frandmod(10001) / 10000.0f);
            node->unk10.x = node->unk28 * HuSin(node->unk2C);
            node->unk10.y = 0.0f;
            node->unk10.z = node->unk28 * HuCos(node->unk2C);
            node->unk1C.x = 50.0f * ((s32)frandmod(10001) / 10000.0f);
            node->unk1C.y = 360.0f + ((s32)frandmod(10001) / 10000.0f);
            node->unk1C.z = 0.0f;
            Hu3DModelAttrReset(node->modelId, HU3D_ATTR_DISPOFF);
            mat = Hu3DData[node->modelId].hsf->material;
            n = M538Unk91D8(&node->unk10) * 4;
            for(i=0; i<4; i++, mat++, n++) {
                mat->color[0] = col[n][0];
                mat->color[1] = col[n][1];
                mat->color[2] = col[n][2];
            }
            node->unk32 = 0;
            node->unk30++;
            /* fallthrough */

        case 1:
            node->unk32++;
            if(node->unk32 == 180) {
                Hu3DModelAttrSet(node->modelId, HU3D_ATTR_DISPOFF);
                ret = 1;
            }
            s = 1.0f + node->unk32 / 240.0f;
            node->unk2C -= 5.3f;
            node->unk28 += 1.1f;
            node->unk10.x = node->unk28 * HuSin(node->unk2C);
            node->unk10.y += 4.1f;
            node->unk10.z = node->unk28 * HuCos(node->unk2C);
            node->unk1C.y -= 1.1f;
            Hu3DModelPosSetV(node->modelId, &node->unk10);
            Hu3DModelRotSetV(node->modelId, &node->unk1C);
            Hu3DModelScaleSet(node->modelId, s, s, s);
            break;
    }
    return ret;
}

/* fn_1_9C04 -- 424 instructions, m538.s:10867-11302 */
static int M538Unk9C04(M538_NODE *node)
{
    int ret = 0;
    u8 col[16][3] = {
        { 0xFF, 0xB3, 0x00 }, { 0xE5, 0xFF, 0x66 }, { 0xFF, 0xE5, 0x4D },
        { 0xCC, 0xB3, 0x00 }, { 0xCC, 0x66, 0x33 }, { 0xFF, 0xE5, 0x4D },
        { 0xFF, 0xA6, 0x4D }, { 0x7F, 0x33, 0x00 }, { 0xB3, 0x4D, 0xB3 },
        { 0xE5, 0xB3, 0xE5 }, { 0xCC, 0x7F, 0xE5 }, { 0x7F, 0x33, 0x7F },
        { 0xCC, 0x66, 0x7F }, { 0xFF, 0xBF, 0xCC }, { 0xFF, 0x7F, 0x99 },
        { 0xA6, 0x4D, 0x7F },
    };
    M538_WORK *work;
    HSFMATERIAL *mat;
    int n;
    int i;
    float ang;
    float r;

    work = HostObj->data;
    switch(node->unk30) {
        case 0:
            ang = 180.0f * ((s32)frandmod(10001) / 10000.0f) - 90.0f;
            r = 500.0f * ((s32)frandmod(10001) / 10000.0f);
            node->unk10.x = r * HuSin(ang);
            node->unk10.y = 700.0f;
            node->unk10.z = r * HuCos(ang);
            node->unk28 = 2.0f * (2.0f + ((s32)frandmod(10001) / 10000.0f));
            node->unk2C = 0.0f;
            node->unk1C.x = 50.0f * ((s32)frandmod(10001) / 10000.0f);
            node->unk1C.y = 360.0f + ((s32)frandmod(10001) / 10000.0f);
            node->unk1C.z = 0.0f;
            Hu3DModelAttrReset(node->modelId, HU3D_ATTR_DISPOFF);
            Hu3DModelScaleSet(node->modelId, 1.0f, 1.0f, 1.0f);
            mat = Hu3DData[node->modelId].hsf->material;
            if(work->unk18CC < 250.0f) {
                n = frandmod(4) * 4;
            } else if(work->unk18CC < 500.0f) {
                n = (frandmod(3) + 1) * 4;
            } else {
                n = 12;
            }
            for(i=0; i<4; i++, mat++, n++) {
                mat->color[0] = col[n][0];
                mat->color[1] = col[n][1];
                mat->color[2] = col[n][2];
            }
            node->unk32 = 0;
            node->unk30++;
            /* fallthrough */

        case 1:
            node->unk2C += 15.0f;
            if(node->unk2C > 180.0f) {
                node->unk2C -= 360.0f;
            }
            ang = HuSin(node->unk2C);
            node->unk10.y -= node->unk28 + 0.3 * HuSin(node->unk2C);
            node->unk10.x += 0.5f * node->unk28 * ang;
            node->unk1C.y -= 2.0f * node->unk28;
            if(node->unk10.y < 0.0f) {
                Hu3DModelAttrSet(node->modelId, HU3D_ATTR_DISPOFF);
                ret = 1;
            }
            Hu3DModelPosSetV(node->modelId, &node->unk10);
            Hu3DModelRotSetV(node->modelId, &node->unk1C);
            break;
    }
    return ret;
}

/* fn_1_A2A4 -- 49 instructions, m538.s:11305-11358 */
static void M538UnkA2A4(M538_WORK *work)
{
    M538_NODE *node;

    work->unk18D4++;
    work->unk18D4 %= 6;
    if(work->unk18D4 == 0) {
        node = M538Unk8858(&work->list[2], M538Unk94DC);
        if(node) {
            node->unk28 = work->unk18CC;
            node->unk30 = 0;
        }
    }
}

/* fn_1_A368 -- 47 instructions, m538.s:11361-11412 */
static void M538UnkA368(M538_WORK *work)
{
    M538_NODE *node;

    work->unk18D4++;
    work->unk18D4 %= 3;
    if(work->unk18D4 == 0) {
        node = M538Unk8858(&work->list[2], M538Unk9C04);
        if(node) {
            node->unk30 = 0;
        }
    }
}

/* fn_1_A424 -- 181 instructions, m538.s:11415-11609 */
static int M538UnkA424(M538_UNK17DC *p)
{
    M538_WORK *work;
    int ret;
    int i;
    float speed;

    ret = 0;
    work = HostObj->data;
    switch(p->unk00) {
        case 0:
            for(i=0; i<24; i++) {
                Hu3DModelAttrReset(work->modelId[17] + i, HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrSet(work->modelId[17] + i, HU3D_MOTATTR_LOOP);
            }
            Hu3DModelAttrReset(work->modelId[11], HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(work->modelId[11], HU3D_MOTATTR_LOOP);
            Hu3DModelAttrReset(work->modelId[12], HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(work->modelId[12], HU3D_MOTATTR_LOOP);
            Hu3DModelAttrReset(work->modelId[24], HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(work->modelId[24], HU3D_MOTATTR_LOOP);
            p->unk02 = 0;
            p->unk00++;
            /* fallthrough */

        case 1:
            p->unk02++;
            speed = 1.5f * p->unk02 / 120.0f;
            for(i=0; i<24; i++) {
                Hu3DMotionSpeedSet(work->modelId[17] + i, speed);
            }
            Hu3DMotionSpeedSet(work->modelId[11], speed);
            Hu3DMotionSpeedSet(work->modelId[12], speed);
            Hu3DMotionSpeedSet(work->modelId[24], speed);
            if(p->unk02 == 120) {
                ret = 1;
            }
            break;

        case 2:
            p->unk02 = 0;
            p->unk00++;
            /* fallthrough */

        case 3:
            p->unk02++;
            speed = 1.5f * (1.0f - p->unk02 / 180.0f);
            for(i=0; i<24; i++) {
                Hu3DMotionSpeedSet(work->modelId[17] + i, speed);
            }
            Hu3DMotionSpeedSet(work->modelId[11], speed);
            Hu3DMotionSpeedSet(work->modelId[12], speed);
            Hu3DMotionSpeedSet(work->modelId[24], speed);
            if(p->unk02 == 180) {
                ret = 1;
            }
            break;
    }
    return ret;
}

/* fn_1_A6F8 -- 106 instructions, m538.s:11612-11723 */
static void M538UnkA6F8(M538_WORK *work)
{
    int no[4] = { 26, 26, 25, 27 };
    int i;
    HU3DMODELID model;

    work->unk17F4.unkD0 = 0;
    for(i=0; i<4; i++) {
        if(work->modelId[no[i]] < 0) {
            model = work->modelId[no[i]] = Hu3DModelCreateData(ModelDataNum[no[i]]);
        } else {
            model = Hu3DModelLink(work->modelId[no[i]]);
        }
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(model, 2);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
        work->unk17F4.unk10[i].modelId = model;
        work->unk17F4.unk10[i].unk2A = 0;
    }
}

/* fn_1_A8A0 -- 173 instructions, m538.s:11726-11919 */
static void M538UnkA8A0(M538_UNK17F4 *p)
{
    M538_WORK *work = HostObj->data;
    M538_THROW *e;

    switch(p->unkD0) {
        case 0:
            p->unkD2 = 0;
            p->unkD0++;
            /* fallthrough */

        case 1:
            p->unkD2++;
            if(p->unkD2 == 360) {
                e = &p->unk10[0];
                if(M538Unk6D98(work, M538UnkAB54, e)) {
                    e->unk1C = work->unk18CC;
                    e->unk2A = 0;
                }
                p->unkD0++;
            }
            break;

        case 2:
            p->unkD2++;
            if(p->unkD2 == 720) {
                e = &p->unk10[1];
                if(M538Unk6D98(work, M538UnkAB54, e)) {
                    e->unk1C = work->unk18CC;
                    e->unk2A = 0;
                }
                p->unkD0++;
            }
            break;
        case 3:
            p->unkD2++;
            if(p->unkD2 == 1080) {
                e = &p->unk10[2];
                if(M538Unk6D98(work, M538UnkAB54, e)) {
                    e->unk1C = work->unk18CC;
                    e->unk2A = 0;
                }
                p->unkD0++;
            }
            break;
        case 4:
            p->unkD2++;
            if(p->unkD2 == 1440) {
                e = &p->unk10[3];
                if(M538Unk6D98(work, M538UnkAB54, e)) {
                    e->unk1C = 250.0f + work->unk18CC;
                    e->unk2A = 0;
                }
                p->unkD0++;
            }
            break;

        case 5:
            break;
    }
}

/* fn_1_AB54 -- 351 instructions, m538.s:11922-12284 */
static int M538UnkAB54(M538_MININODE *node)
{
    M538_THROW *p;
    int ret;
    float r;
    float t;

    ret = 0;
    p = node->unk0C;
    switch(p->unk2A) {
        case 0:
            Hu3DModelAttrReset(p->modelId, HU3D_ATTR_DISPOFF);
            p->unk2C = 0;
            p->rot.x = 0.0f;
            p->rot.y = 0.0f;
            p->rot.z = 0.0f;
            p->unk18 = 360.0f * ((s32)frandmod(10001) / 10000.0f);
            p->pos.x = p->unk1C * HuSin(p->unk18);
            p->pos.y = 300.0f;
            p->pos.z = p->unk1C * HuCos(p->unk18);
            p->unk2A++;
            /* fallthrough */

        case 1:
            p->unk2C++;
            if(p->unk2C == 60) {
                p->unk2A++;
            }
            p->unk18 -= 4.9f;
            p->rot.x += 5.0f;
            p->rot.y += 5.0f;
            t = 1.0f - p->unk2C / 60.0f;
            r = p->unk1C + p->unk1C * (0.5f * t * t);
            p->pos.x = r * HuSin(p->unk18);
            p->pos.z = r * HuCos(p->unk18);
            Hu3DModelPosSetV(p->modelId, &p->pos);
            Hu3DModelRotSetV(p->modelId, &p->rot);
            break;

        case 2:
            p->unk2C = 0;
            p->unk2A++;
            /* fallthrough */

        case 3:
            p->unk2C++;
            if(p->unk2C == 60) {
                p->unk2A++;
            }
            p->unk18 -= 4.9f;
            p->rot.x += 5.0f;
            p->rot.y += 5.0f;
            p->pos.x = p->unk1C * HuSin(p->unk18);
            p->pos.z = p->unk1C * HuCos(p->unk18);
            Hu3DModelPosSetV(p->modelId, &p->pos);
            Hu3DModelRotSetV(p->modelId, &p->rot);
            break;

        case 4:
            p->unk18 -= 90.0f;
            p->unk1C = M_PI * (2.0f * p->unk1C) / 72.0;
            p->unk2C = 0;
            p->unk2A++;
            /* fallthrough */

        case 5:
            p->pos.x += p->unk1C * HuSin(p->unk18);
            p->pos.z += p->unk1C * HuCos(p->unk18);
            p->rot.x += 5.0f;
            p->rot.y += 5.0f;
            Hu3DModelPosSetV(p->modelId, &p->pos);
            Hu3DModelRotSetV(p->modelId, &p->rot);
            p->unk2C++;
            if(p->unk2C == 60) {
                Hu3DModelAttrSet(p->modelId, HU3D_ATTR_DISPOFF);
                ret = 1;
            }
            break;
    }
    return ret;
}

/* fn_1_B0D0 -- 69 instructions, m538.s:12287-12361 */
static int M538UnkB0D0(M538_MININODE *node)
{
    M538_UNK17E0 *p;
    int ret;
    float scale;

    ret = 0;
    p = node->unk0C;
    switch(p->unk06) {
        case 0:
            p->unk08 = 0;
            p->unk06++;
            /* fallthrough */

        case 1:
            p->unk08++;
            if(p->unk08 == 60) {
                ret = 1;
            }
            scale = 1.0f + 3.0f * p->unk08 / 60.0f;
            Hu3DModelScaleSet(p->modelId, scale, 1.0f, scale);
            break;
    }
    return ret;
}
