/*
 * m567dll -- a 1-vs-3 minigame (MG_TYPE_1VS3, overlay #78).
 *
 * Every function is written from the reference assembly, in reference order.
 * Do not reorder: CodeWarrior inlines only what it has already seen.
 * Line ranges are into build/mp5-asm/m567Dll/asm/REL/m567Dll/m567.s.
 *
 * Shape: one translation unit, no REL/mgframe.h. ObjectSetup creates the
 * OMOBJMAN (lbl_1_bss_8), a main object (lbl_1_bss_4) whose data is the
 * single 0xD8C M567_WORK, four player objects (data M567_PLAYER, 0x44), then
 * MgSeqCreate(&lbl_1_data_0). Game state is split into two M567_SIDE records:
 * side[0] the solo player, side[1] the team of three.
 *
 * A small task list lives in the work (list + 100-node pool): fn_1_4704 adds
 * a BOOL (*)(M567_NODE *) callback with a data pointer, fn_1_47D0 runs them
 * and frees each node whose callback returns TRUE. Several callers inline the
 * insert instead of calling fn_1_4704. Callback data by function:
 *   fn_1_979C, fn_1_988C  M567_BODY *        fn_1_9828  M567_ELEM *
 *   fn_1_98F0             M567_COLOR *       fn_1_9470  M567_PLAYER *
 *
 * Retail layout quirk: M567_SIDE.grid is 11 rows of 5 (0x0C..0x7A) followed by
 * result[3] (0x7A..0x80) and body (0x80), but fn_1_60F8 and fn_1_6094 copy 12
 * rows of 5. The twelfth row writes result[] and the first four bytes of
 * body.pos; fn_1_60F8 rewrites body.pos afterwards. Keep the 12-row loops
 * (plan pitfall 6) and flag them for the W4 host audit.
 *
 * Every table under .rodata except lbl_1_rodata_10 is a function-local
 * initializer (copied onto the stack at function entry); write those as
 * locals. The .data strings are literals in the functions that use them.
 */

#include "game/audio.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/flag.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/mg/seqman.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/wipe.h"

#include "math.h"
#include "humath.h"

#define M567_SIDE_MAX 2
#define M567_SIDE_PLAYER_MAX 3
#define M567_NODE_MAX 100

struct M567Node_s;
typedef BOOL (*M567_TASKFUNC)(struct M567Node_s *node);

/* 0x14 bytes. */
typedef struct M567Node_s {
    /* 0x00 */ struct M567Node_s *prev;
    /* 0x04 */ struct M567Node_s *next;
    /* 0x08 */ struct M567List_s *list;
    /* 0x0C */ M567_TASKFUNC func;
    /* 0x10 */ void *data;
} M567_NODE;

/* 0x8 bytes: the active list and the free list. */
typedef struct M567List_s {
    /* 0x00 */ M567_NODE *head;
    /* 0x04 */ M567_NODE *free;
} M567_LIST;

struct M567Side_s;
struct M567Elem_s;

/* 0x44 bytes, one per player object. */
typedef struct M567Player_s {
    /* 0x00 */ HuVecF pos;
    /* 0x0C */ HuVecF rot;
    /* 0x18 */ OMOBJ *obj;
    /* 0x1C */ struct M567Elem_s *elem;  /* side->ui.elem[slot] */
    /* 0x20 */ struct M567Side_s *side;
    /* 0x24 */ HU3DMODELID mdlId;
    /* 0x26 */ s16 no;
    /* 0x28 */ s16 charNo;
    /* 0x2A */ s16 grp;
    /* 0x2C */ s16 padNo;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 comF;                /* GwPlayerConf type */
    /* 0x34 */ s16 dif;
    /* 0x36 */ s16 slot;                /* index within its side */
    /* 0x38 */ s16 mode;
    /* 0x3A */ HU3DMODELID linkMdlId;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ s16 unk3E;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ s16 unk42;
} M567_PLAYER;

/* 0x38 bytes, two in the work (one camera per side). */
typedef struct M567Cam_s {
    /* 0x00 */ HuVecF target;
    /* 0x0C */ float angleX;
    /* 0x10 */ float angleY;
    /* 0x14 */ float dist;
    /* 0x18 */ u8 unk18[0x1C];          /* unreferenced */
    /* 0x34 */ s16 bit;                 /* Hu3D camera bit (lbl_1_rodata_10) */
    /* 0x36 */ s16 unk36;
} M567_CAM;

/* 0xC bytes: the split-screen divider. */
typedef struct M567View_s {
    /* 0x00 */ float x;
    /* 0x04 */ float y;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 mode;
} M567_VIEW;

/* 0x48 bytes at M567_SIDE+0x80. */
typedef struct M567Body_s {
    /* 0x00 */ HuVecF pos;
    /* 0x0C */ HuVecF rot;
    /* 0x18 */ float unk18;
    /* 0x1C */ float unk1C;
    /* 0x20 */ float unk20;
    /* 0x24 */ float unk24;
    /* 0x28 */ float unk28;
    /* 0x2C */ float unk2C;
    /* 0x30 */ HU3DMODELID mdlId;
    /* 0x32 */ s16 motNo;
    /* 0x34 */ HU3DMOTID motId;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ HU3DMODELID miniMdlId[3]; /* hooked to "m567-*_mini" */
    /* 0x40 */ HU3DMODELID pumMdlId[3];  /* hooked to "m567-pum*" */
    /* 0x46 */ HU3DMODELID unk46;
} M567_BODY;

/* 0x8 bytes: a material colour being animated (fn_1_98F0 writes bytes 0xE..0x10 through ptr). */
typedef struct M567Color_s {
    /* 0x00 */ HSFMATERIAL *ptr;
    /* 0x04 */ s16 time;
    /* 0x06 */ s16 mode;
} M567_COLOR;

/* 0x20 bytes. */
typedef struct M567Elem_s {
    /* 0x00 */ HSFMATERIAL *ptr;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ HU3DMODELID unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ HU3DMODELID unkE;
    /* 0x10 */ HU3DMODELID unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 mode;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 type;
} M567_ELEM;

/* 0xD8 bytes at M567_SIDE+0xCC. */
typedef struct M567Ui_s {
    /* 0x00 */ M567_CAM *cam;
    /* 0x04 */ M567_COLOR color[3];
    /* 0x1C */ HuVecF pos2d;
    /* 0x28 */ HuVecF objPos[3];
    /* 0x4C */ HuVecF rot;
    /* 0x58 */ M567_ELEM elem[3];
    /* 0xB8 */ s16 type;                /* 0 solo, 1 team */
    /* 0xBA */ s16 unkBA;
    /* 0xBC */ HU3DMODELID mdlId;
    /* 0xBE */ HU3DMODELID mdlA[3];
    /* 0xC4 */ HU3DMODELID mdlB[3];
    /* 0xCA */ HU3DMODELID mdlC[3];
    /* 0xD0 */ s16 unkD0;
    /* 0xD2 */ s16 unkD2;
    /* 0xD4 */ s16 mode;
    /* 0xD6 */ s16 unkD6;
} M567_UI;

/* 0x1B4 bytes, two in the work. */
typedef struct M567Side_s {
    /* 0x000 */ M567_PLAYER *player[M567_SIDE_PLAYER_MAX];
    /* 0x00C */ s16 grid[11][5];
    /* 0x07A */ s16 result[3];
    /* 0x080 */ M567_BODY body;
    /* 0x0C8 */ M567_CAM *cam;
    /* 0x0CC */ M567_UI ui;
    /* 0x1A4 */ s16 unk1A4;
    /* 0x1A6 */ s16 unk1A6;
    /* 0x1A8 */ s16 unk1A8;
    /* 0x1AA */ s16 unk1AA;
    /* 0x1AC */ s16 unk1AC;
    /* 0x1AE */ s16 unk1AE;
    /* 0x1B0 */ s16 unk1B0;
    /* 0x1B2 */ s16 unk1B2;
} M567_SIDE;

/* 0xD8C bytes on the GameCube; allocate with sizeof. */
typedef struct M567Work_s {
    /* 0x000 */ M567_PLAYER *player[4];
    /* 0x010 */ M567_SIDE side[M567_SIDE_MAX];
    /* 0x378 */ M567_LIST list;
    /* 0x380 */ M567_NODE node[M567_NODE_MAX];
    /* 0xB50 */ M567_CAM cam[M567_SIDE_MAX];
    /* 0xBC0 */ M567_VIEW view;
    /* 0xBCC */ u8 unkBCC[0x78];        /* unreferenced */
    /* 0xC44 */ HU3DMODELID mdlC44[32];
    /* 0xC84 */ HU3DMODELID mdlC84[8][3];
    /* 0xCB4 */ HU3DMODELID mdlCB4[8][3];
    /* 0xCE4 */ s16 unkCE4[3];
    /* 0xCEA */ s16 unkCEA;
    /* 0xCEC */ s16 mode;
    /* 0xCEE */ s16 unkCEE;
    /* 0xCF0 */ s16 time;
    /* 0xCF2 */ s16 unkCF2;
    /* 0xCF4 */ s16 unkCF4;
    /* 0xCF6 */ s16 unkCF6;
    /* 0xCF8 */ HU3DMODELID mdl[65];    /* from lbl_1_data_12C */
    /* 0xD7A */ HU3DMODELID mdl2[9];    /* from lbl_1_data_230 */
} M567_WORK;

/* 0x18 bytes: a side camera's starting target and angle/distance. */
typedef struct M567CamParam_s {
    HuVecF target;
    HuVecF rot;
} M567_CAMPARAM;

void ObjectSetup(void);
void fn_1_1FC(s16 mode, s16 frameNo);
void fn_1_32C(s16 mode, s16 frameNo);
void fn_1_FB8(s16 mode, s16 frameNo);
void fn_1_108C(s16 mode, s16 frameNo);
void fn_1_1160(s16 mode, s16 frameNo);
void fn_1_1474(s16 mode, s16 frameNo);
void fn_1_32CC(s16 mode, s16 frameNo);
void fn_1_362C(s16 mode, s16 frameNo);
void fn_1_371C(s16 mode, s16 frameNo);
void fn_1_3758(OMOBJ *obj);
void fn_1_3908(OMOBJ *obj);
void fn_1_3990(void);
void fn_1_3994(OMOBJ *obj);
void fn_1_39F8(OMOBJ *obj);
void fn_1_3B74(void);
void fn_1_3B78(M567_WORK *work);
void fn_1_3BF8(M567_WORK *work);
void fn_1_3C80(M567_WORK *work);
void fn_1_3E94(M567_VIEW *view);
void fn_1_3EEC(M567_VIEW *view);
void fn_1_4164(M567_VIEW *view);
void fn_1_4168(M567_WORK *work);
void fn_1_42A8(M567_WORK *work, s32 unused);
void fn_1_439C(M567_CAM *cam, s16 bit);
void fn_1_4404(M567_CAM *cam, HuVecF *pos);
void fn_1_4680(M567_LIST *list, M567_NODE *pool, s32 num);
M567_NODE *fn_1_4704(M567_LIST *list, M567_TASKFUNC func, void *data);
void fn_1_4758(M567_NODE *node);
void fn_1_47D0(M567_LIST *list);
void fn_1_48B0(M567_WORK *work);
void fn_1_5BD4(s16 (*grid)[5]);
s32 fn_1_5F04(s32 prev);
s32 fn_1_5FC0(s32 prev);
void fn_1_6094(s16 (*dst)[5], s16 (*src)[5]);
void fn_1_60F8(M567_WORK *work);
void fn_1_69B4(M567_BODY *body, s32 side);
s32 fn_1_7084(M567_SIDE *side);
void fn_1_7DB4(M567_UI *ui, M567_CAM *cam, s16 type);
void fn_1_8330(M567_UI *ui, HuVecF *pos);
void fn_1_8794(M567_ELEM *elem, s32 type);
void fn_1_89F4(M567_ELEM *elem);
void fn_1_8DE0(M567_ELEM *elem);
void fn_1_8EC8(M567_PLAYER *player);
void fn_1_8F1C(M567_PLAYER *player);
void fn_1_92B0(M567_PLAYER *player);
BOOL fn_1_9470(M567_NODE *node);
void fn_1_959C(s16 (*grid)[5], s16 row, s16 col);
s32 fn_1_9694(s16 (*grid)[5], s16 row, s16 col);
BOOL fn_1_979C(M567_NODE *node);
BOOL fn_1_9828(M567_NODE *node);
BOOL fn_1_988C(M567_NODE *node);
BOOL fn_1_98F0(M567_NODE *node);

/* --- .rodata --- */

/* Hu3D camera bits, one per side. */
const u16 lbl_1_rodata_10[4] = { 1, 2, 4, 8 };

/* --- .data --- */

MGSEQ_PARAM lbl_1_data_0 = {
    300, MGSEQ_TIMER_TOP,
    fn_1_1FC,
    fn_1_32C,
    fn_1_FB8,
    fn_1_108C,
    fn_1_1160,
    fn_1_1474,
    fn_1_32CC,
    fn_1_362C,
    fn_1_371C
};

/* Five character motions per character number. */
u32 lbl_1_data_28[13][5] = {
    { 0x008C0000, 0x008C006A, 0x008C003F, 0x008C0006, 0x008C0017 },
    { 0x00330000, 0x0033006A, 0x0033003F, 0x00330006, 0x00330017 },
    { 0x00B70000, 0x00B7006A, 0x00B7003F, 0x00B70006, 0x00B70017 },
    { 0x00ED0000, 0x00ED006A, 0x00ED003F, 0x00ED0006, 0x00ED0017 },
    { 0x00E60000, 0x00E6006A, 0x00E6003F, 0x00E60006, 0x00E60017 },
    { 0x00170000, 0x0017006A, 0x0017003F, 0x00170006, 0x00170017 },
    { 0x00E00000, 0x00E0006A, 0x00E0003F, 0x00E00006, 0x00E00017 },
    { 0x002D0000, 0x002D006A, 0x002D003F, 0x002D0006, 0x002D0017 },
    { 0x00C90000, 0x00C9006A, 0x00C9003F, 0x00C90006, 0x00C90017 },
    { 0x00B00000, 0x00B0006A, 0x00B0003F, 0x00B00006, 0x00B00017 },
    { 0x00B00000, 0x00B0006A, 0x00B0003F, 0x00B00006, 0x00B00017 },
    { 0x00B00000, 0x00B0006A, 0x00B0003F, 0x00B00006, 0x00B00017 },
    { 0x00B00000, 0x00B0006A, 0x00B0003F, 0x00B00006, 0x00B00017 },
};

/* Model files for M567_WORK.mdl[]; files/data/m567.bin carries no names. */
u32 lbl_1_data_12C[65] = {
    0x007A000B, 0x007A000C, 0x007A000D, 0x007A000E, 0x007A000F, 0x007A0010,
    0x007A0011, 0x007A0012, 0x007A0013, 0x007A0014, 0x007A0015, 0x007A0016,
    0x007A0017, 0x007A0018, 0x007A0019, 0x007A001A, 0x007A001B, 0x007A001C,
    0x007A0009, 0x007A000A, 0x007A001D, 0x007A001E, 0x007A001F, 0x007A0020,
    0x007A0021, 0x007A0022, 0x007A0023, 0x007A0024, 0x007A0025, 0x007A0026,
    0x007A0027, 0x007A0028, 0x007A0029, 0x007A002A, 0x007A002B, 0x007A002C,
    0x007A002D, 0x007A002E, 0x007A002F, 0x007A0030, 0x007A0031, 0x007A0032,
    0x007A0033, 0x007A0034, 0x007A0035, 0x007A0036, 0x007A0037, 0x007A0038,
    0x007A0039, 0x007A003A, 0x007A003B, 0x007A003C, 0x007A003D, 0x007A003E,
    0x007A003F, 0x007A0040, 0x007A0041, 0x007A0042, 0x007A0043, 0x007A0044,
    0x007A0045, 0x007A0046, 0x007A0047, 0x007A0048, 0x007A0049,
};

/* Model files for M567_WORK.mdl2[]. */
u32 lbl_1_data_230[9] = {
    0x007A0000, 0x007A0001, 0x007A0002, 0x007A0003, 0x007A0004, 0x007A0005, 0x007A0006, 0x007A0007, 0x007A0008
};

M567_CAMPARAM lbl_1_data_254[10] = {
    { { 0.0f, 0.0f, 2600.0f }, { 90.0f, 41.0f, 1890.0f } },
    { { 0.0f, 0.0f, -2150.0f }, { 270.0f, 41.0f, 1890.0f } },
    { { 0.0f, 0.0f, -2400.0f }, { 90.0f, 41.0f, 1400.0f } },
    { { 0.0f, 500.0f, 2150.0f }, { 90.0f, 50.0f, 1700.0f } },
    { { 0.0f, 0.0f, 2150.0f }, { 90.0f, 41.0f, 1890.0f } },
    { { 0.0f, 500.0f, -2150.0f }, { 270.0f, 50.0f, 1700.0f } },
    { { 0.0f, 0.0f, -2150.0f }, { 270.0f, 41.0f, 1890.0f } },
    { { 0.0f, 0.0f, 2000.0f }, { 90.0f, 31.0f, 1730.0f } },
    { { 0.0f, 0.0f, -2000.0f }, { 270.0f, 31.0f, 1730.0f } },
    { { 0.0f, 0.0f, -781.0f }, { 90.0f, 21.0f, 2120.0f } },
};

s16 lbl_1_data_344[5][24] = {
    { 2, 6, 7, 0, 5, 2, 3, 6, 0, 2, 0, 3, 1, 5, 7, 0, 2, 6, 1, 4, 5, 2, 1, 2 },
    { 0, 2, 7, 7, 6, 1, 5, 4, 2, 0, 7, 6, 5, 1, 4, 7, 5, 7, 3, 0, 2, 0, 7, 5 },
    { 7, 1, 4, 6, 5, 6, 0, 7, 0, 4, 6, 2, 3, 2, 7, 2, 4, 6, 1, 0, 2, 6, 3, 0 },
    { 1, 0, 5, 3, 7, 3, 0, 2, 6, 5, 1, 2, 7, 3, 6, 6, 4, 5, 7, 2, 1, 3, 5, 3 },
    { 4, 6, 4, 5, 3, 7, 0, 1, 5, 7, 4, 0, 6, 5, 6, 4, 2, 4, 1, 0, 2, 0, 6, 3 },
};

/* HuAudFX ids, -1 when idle. */
s32 lbl_1_data_434[2] = { -1, -1 };
s32 lbl_1_data_43C[2] = { -1, -1 };

/* --- .bss --- */

s32 lbl_1_bss_0;                  /* HuAudBGMPlay id */
OMOBJ *lbl_1_bss_4;               /* main object; data is M567_WORK */
OMOBJMAN *lbl_1_bss_8;

/* asm 61-151, 87 insns. */
void ObjectSetup(void)
{
    OMOBJ *obj;
    M567_WORK *work;
    s32 i;

    lbl_1_bss_8 = omInitObjMan(10, 0x2000);
    omGameSysInit(lbl_1_bss_8);

    obj = omAddObjEx(lbl_1_bss_8, 0x65, 0, 0, OM_GRP_NONE, fn_1_3994);
    lbl_1_bss_4 = obj;
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M567_WORK), HU_MEMNUM_OVL);
    work = (M567_WORK *)obj->data;
    work->unkCF4 = 0;
    work->unkCF6 = 0;
    fn_1_3C80(work);
    fn_1_3BF8(work);

    for (i = 0; i < 4; i++) {
        obj = omAddObjEx(lbl_1_bss_8, 0x64, 1, 5, 0, fn_1_3758);
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M567_PLAYER), HU_MEMNUM_OVL);
        obj->work[0] = i;
        work->player[i] = (M567_PLAYER *)obj->data;
    }

    fn_1_3B78(work);
    Hu3DBGColorSet(0, 0, 0);
    Hu3DNoSyncSet(TRUE);
    MgSeqCreate(&lbl_1_data_0);
}

/* asm 154-231, 76 insns. MGSEQ init hook. */
void fn_1_1FC(s16 mode, s16 frameNo)
{
    M567_WORK *work = (M567_WORK *)lbl_1_bss_4->data;

    work->unkCF4 = 0;
    work->unkCF6 = 0;
    work->mode = 0;
    work->unkCF2 = 0;

    fn_1_60F8(work);
    fn_1_48B0(work);
    fn_1_3E94(&work->view);

    work->cam[0].angleX = lbl_1_data_254[2].rot.x;
    work->cam[0].angleY = lbl_1_data_254[2].rot.y;
    work->cam[0].dist = lbl_1_data_254[2].rot.z;
    work->cam[0].target.x = lbl_1_data_254[2].target.x;
    work->cam[0].target.y = lbl_1_data_254[2].target.y;
    work->cam[0].target.z = lbl_1_data_254[2].target.z;

    work->cam[1].angleX = lbl_1_data_254[5].rot.x;
    work->cam[1].angleY = lbl_1_data_254[5].rot.y;
    work->cam[1].dist = lbl_1_data_254[5].rot.z;
    work->cam[1].target.x = lbl_1_data_254[5].target.x;
    work->cam[1].target.y = lbl_1_data_254[5].target.y;
    work->cam[1].target.z = lbl_1_data_254[5].target.z;

    MgSeqModeNext();
}

/* asm 234-1058, 803 insns. MGSEQ fade-in hook; 8-case switch (.data:0x444). */
void fn_1_32C(s16 mode, s16 frameNo)
{
    M567_WORK *work = (M567_WORK *)lbl_1_bss_4->data;
    float frac, ease, invEase;
    float invA, invB, invC;
    float camEase;

    switch (work->mode) {
    case 0:
        MgSeqModeChangeOff();
        HuAudFXPlay(0x8FD);
        work->time = 0;
        work->unkCEE = 0;
        work->mode++;
        /* fall through */
    case 1:
        work->unkCEE++;
        if (work->unkCEE == 150) {
            work->mode++;
        }

        frac = (float)work->unkCEE / 150.0f;
        ease = 1.0 - (0.5 + 0.5 * HuCos(180.0f * frac));
        invEase = 1.0f - ease;

        work->cam[0].angleX = lbl_1_data_254[2].rot.x * invEase + lbl_1_data_254[3].rot.x * ease;
        work->cam[0].angleY = lbl_1_data_254[2].rot.y * invEase + lbl_1_data_254[3].rot.y * ease;
        work->cam[0].dist = lbl_1_data_254[2].rot.z * invEase + lbl_1_data_254[3].rot.z * ease;
        work->cam[0].target.x = lbl_1_data_254[2].target.x * invEase + lbl_1_data_254[3].target.x * ease;
        work->cam[0].target.y = lbl_1_data_254[2].target.y * invEase + lbl_1_data_254[3].target.y * ease;
        work->cam[0].target.z = lbl_1_data_254[2].target.z * invEase + lbl_1_data_254[3].target.z * ease;
        break;

    case 2:
        work->unkCEE = 0;
        work->mode++;
        /* fall through */
    case 3:
        work->unkCEE++;
        if (work->unkCEE == 30) {
            work->mode++;
        }

        frac = (float)work->unkCEE / 30.0f;
        work->view.x = 640.0f * (1.0f - frac) + 320.0f * frac;
        break;

    case 4:
        HuAudFXPlay(0x8EC);
        Hu3DModelAttrSet(work->mdl[12], 1);
        work->unkCEE = 0;
        work->mode++;
        /* fall through */
    case 5:
        work->unkCEE++;
        if (work->unkCEE == 15) {
            HuAudFXPlay(0x8FE);
            Hu3DModelAttrReset(work->side[0].ui.mdlC[0], 0x40000002);
            Hu3DModelAttrReset(work->side[1].ui.mdlC[0], 0x40000002);
            Hu3DModelAttrReset(work->side[1].ui.mdlC[1], 0x40000002);
            Hu3DModelAttrReset(work->side[1].ui.mdlC[2], 0x40000002);
            work->mode++;
        }

        frac = (float)work->unkCEE / 15.0f;
        ease = 1.0 - (0.5 + 0.5 * HuCos(180.0f * frac));

        work->side[0].ui.pos2d.y = 500.0f * (1.0f - ease) + 401.0f * ease;
        work->side[1].ui.pos2d.y = 500.0f * (1.0f - ease) + 401.0f * ease;

        frac = (float)work->unkCEE / 240.0f;
        camEase = 1.0 - (0.5 + 0.5 * HuCos(180.0f * frac));
        invEase = 1.0f - camEase;

        work->cam[0].angleX = lbl_1_data_254[3].rot.x * invEase + lbl_1_data_254[4].rot.x * camEase;
        work->cam[0].angleY = lbl_1_data_254[3].rot.y * invEase + lbl_1_data_254[4].rot.y * camEase;
        work->cam[0].dist = lbl_1_data_254[3].rot.z * invEase + lbl_1_data_254[4].rot.z * camEase;
        work->cam[0].target.x = lbl_1_data_254[3].target.x * invEase + lbl_1_data_254[4].target.x * camEase;
        work->cam[0].target.y = lbl_1_data_254[3].target.y * invEase + lbl_1_data_254[4].target.y * camEase;
        work->cam[0].target.z = lbl_1_data_254[3].target.z * invEase + lbl_1_data_254[4].target.z * camEase;

        invA = 1.0f - camEase;
        work->cam[1].angleX = lbl_1_data_254[5].rot.x * invA + lbl_1_data_254[6].rot.x * camEase;
        work->cam[1].angleY = lbl_1_data_254[5].rot.y * invA + lbl_1_data_254[6].rot.y * camEase;
        work->cam[1].dist = lbl_1_data_254[5].rot.z * invA + lbl_1_data_254[6].rot.z * camEase;
        work->cam[1].target.x = lbl_1_data_254[5].target.x * invA + lbl_1_data_254[6].target.x * camEase;
        work->cam[1].target.y = lbl_1_data_254[5].target.y * invA + lbl_1_data_254[6].target.y * camEase;
        work->cam[1].target.z = lbl_1_data_254[5].target.z * invA + lbl_1_data_254[6].target.z * camEase;
        break;

    case 6:
        work->unkCEE++;

        if (work->unkCEE == 35) {
            Hu3DModelAttrSet(work->side[0].ui.mdlC[0], 0x40000002);
            Hu3DModelAttrSet(work->side[1].ui.mdlC[0], 0x40000002);
            Hu3DModelAttrSet(work->side[1].ui.mdlC[1], 0x40000002);
            Hu3DModelAttrSet(work->side[1].ui.mdlC[2], 0x40000002);
        }
        if (work->unkCEE == 175) {
            Hu3DModelAttrReset(work->side[0].ui.mdlC[0], 0x40000002);
            Hu3DModelAttrReset(work->side[1].ui.mdlC[0], 0x40000002);
        }
        if (work->unkCEE == 185) {
            Hu3DModelAttrReset(work->side[1].ui.mdlC[1], 0x40000002);
        }
        if (work->unkCEE == 195) {
            Hu3DModelAttrReset(work->side[1].ui.mdlC[2], 0x40000002);
        }
        if (work->unkCEE == 190) {
            HuAudFXPlayPan(0x8ED, 0x30);
            HuAudFXPlayPan(0x8EE, 0x48);
            Hu3DModelAttrReset(work->side[0].ui.mdlA[0], 0x40000002);
            Hu3DModelAttrReset(work->side[1].ui.mdlA[0], 0x40000002);

            fn_1_4704(&work->list, fn_1_98F0, &work->side[0].ui.color[0]);
            work->side[0].ui.color[0].time = 2;
            work->side[0].ui.color[0].mode = 0xF;

            fn_1_4704(&work->list, fn_1_98F0, &work->side[0].ui.color[1]);
            work->side[0].ui.color[1].time = 2;
            work->side[0].ui.color[1].mode = 0xF;

            fn_1_4704(&work->list, fn_1_98F0, &work->side[1].ui.color[0]);
            work->side[1].ui.color[0].time = 2;
            work->side[1].ui.color[0].mode = 0xF;
        }
        if (work->unkCEE == 200) {
            HuAudFXPlayPan(0x8EF, 0x50);
            Hu3DModelAttrReset(work->side[1].ui.mdlA[1], 0x40000002);

            fn_1_4704(&work->list, fn_1_98F0, &work->side[1].ui.color[1]);
            work->side[1].ui.color[1].time = 2;
            work->side[1].ui.color[1].mode = 0xF;
        }
        if (work->unkCEE == 210) {
            HuAudFXPlayPan(0x8F0, 0x58);
            Hu3DModelAttrReset(work->side[1].ui.mdlA[2], 0x40000002);

            fn_1_4704(&work->list, fn_1_98F0, &work->side[1].ui.color[2]);
            work->side[1].ui.color[2].time = 2;
            work->side[1].ui.color[2].mode = 0xF;
        }
        if (work->unkCEE == 240) {
            work->mode++;
        }

        frac = (float)work->unkCEE / 240.0f;
        ease = 1.0 - (0.5 + 0.5 * HuCos(180.0f * frac));
        invB = 1.0f - ease;

        work->cam[0].angleX = lbl_1_data_254[3].rot.x * invB + lbl_1_data_254[4].rot.x * ease;
        work->cam[0].angleY = lbl_1_data_254[3].rot.y * invB + lbl_1_data_254[4].rot.y * ease;
        work->cam[0].dist = lbl_1_data_254[3].rot.z * invB + lbl_1_data_254[4].rot.z * ease;
        work->cam[0].target.x = lbl_1_data_254[3].target.x * invB + lbl_1_data_254[4].target.x * ease;
        work->cam[0].target.y = lbl_1_data_254[3].target.y * invB + lbl_1_data_254[4].target.y * ease;
        work->cam[0].target.z = lbl_1_data_254[3].target.z * invB + lbl_1_data_254[4].target.z * ease;

        invC = 1.0f - ease;
        work->cam[1].angleX = lbl_1_data_254[5].rot.x * invC + lbl_1_data_254[6].rot.x * ease;
        work->cam[1].angleY = lbl_1_data_254[5].rot.y * invC + lbl_1_data_254[6].rot.y * ease;
        work->cam[1].dist = lbl_1_data_254[5].rot.z * invC + lbl_1_data_254[6].rot.z * ease;
        work->cam[1].target.x = lbl_1_data_254[5].target.x * invC + lbl_1_data_254[6].target.x * ease;
        work->cam[1].target.y = lbl_1_data_254[5].target.y * invC + lbl_1_data_254[6].target.y * ease;
        work->cam[1].target.z = lbl_1_data_254[5].target.z * invC + lbl_1_data_254[6].target.z * ease;
        break;

    case 7:
        lbl_1_bss_0 = HuAudBGMPlay(0x34);
        MgSeqModeNext();
        break;
    }
}

/* asm 1061-1117, 53 insns. MGSEQ start hook. */
void fn_1_FB8(s16 mode, s16 frameNo)
{
    M567_WORK *work = (M567_WORK *)lbl_1_bss_4->data;

    switch (work->time) {
    case 0:
        Hu3DModelAttrSet(work->side[0].ui.mdlA[0], 1);
        Hu3DModelAttrSet(work->side[1].ui.mdlA[0], 1);
        Hu3DModelAttrSet(work->side[1].ui.mdlA[1], 1);
        Hu3DModelAttrSet(work->side[1].ui.mdlA[2], 1);
        Hu3DModelAttrSet(work->side[0].ui.mdlC[0], 1);
        Hu3DModelAttrSet(work->side[1].ui.mdlC[0], 1);
        Hu3DModelAttrSet(work->side[1].ui.mdlC[1], 1);
        Hu3DModelAttrSet(work->side[1].ui.mdlC[2], 1);
        work->side[0].ui.unkBA = 1;
        work->side[1].ui.unkBA = 1;
        work->mode = 0;
        work->time++;
        break;

    case 1:
        break;
    }
}

/* asm 1120-1179, 53 insns. MGSEQ main hook. */
void fn_1_108C(s16 mode, s16 frameNo)
{
    M567_WORK *work = (M567_WORK *)lbl_1_bss_4->data;

    switch (work->mode) {
    case 0:
        work->side[0].unk1AE = 1;
        work->side[1].unk1AE = 1;
        work->time = 0;
        work->unkCF4 = 1;
        work->unkCF6 = 1;
        work->mode++;
        /* fall through */
    case 1:
        if (work->unkCEA >= 0) {
            work->unkCF4 = 0;
            MgSeqModeChangeOff();
            work->mode++;
        }
        break;

    case 2:
        if (work->side[work->unkCEA].unk1AE == 7) {
            MgSeqModeNext();
        }
        break;
    }
}

/* asm 1182-1393, 197 insns. MGSEQ finish hook. */
void fn_1_1160(s16 mode, s16 frameNo)
{
    M567_WORK *work = (M567_WORK *)lbl_1_bss_4->data;
    float frac, ease;

    switch (work->time) {
    default:
        break;

    case 0:
        if (work->side[0].unk1AE != 4 && work->side[0].unk1AE != 7 && work->side[0].unk1AE != 8) {
            work->side[0].unk1AE = 7;
        }
        if (work->side[1].unk1AE != 4 && work->side[1].unk1AE != 7 && work->side[1].unk1AE != 8) {
            work->side[1].unk1AE = 7;
        }

        if (work->unkCEA < 0) {
            if (work->side[0].unk1AA == 9) {
                work->side[0].unk1AA = work->side[0].unk1A6;
                work->side[0].body.unk2C = work->side[0].body.unk20;
            }
            if (work->side[1].unk1AA == 9) {
                work->side[1].unk1AA = work->side[1].unk1A6;
                work->side[1].body.unk2C = work->side[1].body.unk20;
            }
            MgSeqWinnerSet(CHARNO_NONE, CHARNO_NONE, CHARNO_NONE, CHARNO_NONE);
        } else if (work->unkCEA == 0) {
            MgSeqWinnerSet1(work->side[0].player[0]->charNo);
        } else {
            MgSeqWinnerSet3(work->side[1].player[0]->charNo,
                             work->side[1].player[1]->charNo,
                             work->side[1].player[2]->charNo);
        }

        work->mode = 0;
        work->unkCF4 = 0;
        work->unkCF6 = 0;
        work->unkCEE = 0;
        HuAudSStreamFadeOut(lbl_1_bss_0, 1000);
        work->time++;
        /* fall through */

    case 1:
        work->unkCEE++;
        if (work->unkCEE == 15) {
            work->time++;
        }

        frac = (float)work->unkCEE / 15.0f;
        ease = 1.0 - (0.5 + 0.5 * HuCos(180.0f * frac));

        work->side[0].ui.pos2d.y = 401.0f * (1.0f - ease) + 500.0f * ease;
        work->side[1].ui.pos2d.y = 401.0f * (1.0f - ease) + 500.0f * ease;
        break;

    case 2:
        Hu3DModelAttrSet(work->side[0].ui.mdlId, 1);
        Hu3DModelAttrSet(work->side[1].ui.mdlId, 1);
        work->time++;
        break;

    case 3:
        break;
    }
}

/* asm 1396-3382, 1942 insns. MGSEQ pre-winner hook; 9-case switch (.data:0x490). */
void fn_1_1474(s16 mode, s16 frameNo)
{
    s16 panTbl[3] = { 0x20, 0x40, 0x60 };
    Mtx mtx;
    M567_WORK *work = (M567_WORK *)lbl_1_bss_4->data;
    M567_BODY *body;
    float time;
    s32 i;
    s32 j;

    switch (work->mode) {
    case 0:
        MgSeqModeChangeOff();
        work->time = 0;
        work->unkCEE = 0;
        work->mode++;
        break;

    case 1:
        if (work->unkCEA < 0) {
            Hu3DMotionShiftSet(work->side[0].body.mdlId, work->side[0].body.unk36, 0.0f, 5.0f, 0);
            Hu3DMotionShiftSet(work->side[1].body.mdlId, work->side[1].body.unk36, 0.0f, 5.0f, 0);
        } else {
            Hu3DMotionShiftSet(work->side[work->unkCEA ^ 1].body.mdlId, work->side[work->unkCEA ^ 1].body.unk36, 0.0f, 5.0f, 0);
        }
        work->mode++;
        break;

    case 2:
        work->unkCEE++;
        if (work->unkCEE == 40) {
            if (work->unkCEA != 0) {
                Hu3DModelObjMtxGet(work->side[0].body.mdlId, "m567-play0", mtx);
                Hu3DMtxTransGet(mtx, &work->side[0].player[0]->pos);
                Hu3DMtxRotGet(mtx, &work->side[0].player[0]->rot);
                Hu3DModelPosSetV(work->side[0].player[0]->mdlId, &work->side[0].player[0]->pos);
                omSetTra(work->side[0].player[0]->obj, work->side[0].player[0]->pos.x, work->side[0].player[0]->pos.y, work->side[0].player[0]->pos.z);
                Hu3DModelRotSetV(work->side[0].player[0]->mdlId, &work->side[0].player[0]->rot);
                omSetRot(work->side[0].player[0]->obj, work->side[0].player[0]->rot.x, work->side[0].player[0]->rot.y, work->side[0].player[0]->rot.z);
                Hu3DModelHookObjReset(work->side[0].body.mdlId, "m567-play0");
                omVibrate(work->side[0].player[0]->no, 25, 12, 0);
                HuAudFXPlayPan(0x8FB, panTbl[work->side[0].unk1AC - 1]);
            }
            if (work->unkCEA != 1) {
                Hu3DModelObjMtxGet(work->side[1].body.mdlId, "m567-play3", mtx);
                Hu3DMtxTransGet(mtx, &work->side[1].player[0]->pos);
                Hu3DMtxRotGet(mtx, &work->side[1].player[0]->rot);
                Hu3DModelPosSetV(work->side[1].player[0]->mdlId, &work->side[1].player[0]->pos);
                omSetTra(work->side[1].player[0]->obj, work->side[1].player[0]->pos.x, work->side[1].player[0]->pos.y, work->side[1].player[0]->pos.z);
                Hu3DModelRotSetV(work->side[1].player[0]->mdlId, &work->side[1].player[0]->rot);
                omSetRot(work->side[1].player[0]->obj, work->side[1].player[0]->rot.x, work->side[1].player[0]->rot.y, work->side[1].player[0]->rot.z);
                Hu3DModelHookObjReset(work->side[1].body.mdlId, "m567-play3");
                Hu3DModelObjMtxGet(work->side[1].body.mdlId, "m567-play1", mtx);
                Hu3DMtxTransGet(mtx, &work->side[1].player[1]->pos);
                Hu3DMtxRotGet(mtx, &work->side[1].player[1]->rot);
                Hu3DModelPosSetV(work->side[1].player[1]->mdlId, &work->side[1].player[1]->pos);
                omSetTra(work->side[1].player[1]->obj, work->side[1].player[1]->pos.x, work->side[1].player[1]->pos.y, work->side[1].player[1]->pos.z);
                Hu3DModelRotSetV(work->side[1].player[1]->mdlId, &work->side[1].player[1]->rot);
                omSetRot(work->side[1].player[1]->obj, work->side[1].player[1]->rot.x, work->side[1].player[1]->rot.y, work->side[1].player[1]->rot.z);
                Hu3DModelHookObjReset(work->side[1].body.mdlId, "m567-play1");
                Hu3DModelObjMtxGet(work->side[1].body.mdlId, "m567-play2", mtx);
                Hu3DMtxTransGet(mtx, &work->side[1].player[2]->pos);
                Hu3DMtxRotGet(mtx, &work->side[1].player[2]->rot);
                Hu3DModelPosSetV(work->side[1].player[2]->mdlId, &work->side[1].player[2]->pos);
                omSetTra(work->side[1].player[2]->obj, work->side[1].player[2]->pos.x, work->side[1].player[2]->pos.y, work->side[1].player[2]->pos.z);
                Hu3DModelRotSetV(work->side[1].player[2]->mdlId, &work->side[1].player[2]->rot);
                omSetRot(work->side[1].player[2]->obj, work->side[1].player[2]->rot.x, work->side[1].player[2]->rot.y, work->side[1].player[2]->rot.z);
                Hu3DModelHookObjReset(work->side[1].body.mdlId, "m567-play2");
                omVibrate(work->side[1].player[0]->no, 35, 12, 0);
                omVibrate(work->side[1].player[1]->no, 35, 12, 0);
                omVibrate(work->side[1].player[2]->no, 35, 12, 0);
                HuAudFXPlayPan(0x8FC, panTbl[work->side[1].unk1AC - 1]);
            }
            work->mode++;
        }
        break;

    case 3:
        work->unkCEE++;
        if (work->unkCEE == 50) {
            work->mode++;
        }
        if (work->unkCEA != 0) {
            work->side[0].player[0]->pos.y += 50.0f;
            Hu3DModelPosSetV(work->side[0].player[0]->mdlId, &work->side[0].player[0]->pos);
            omSetTra(work->side[0].player[0]->obj, work->side[0].player[0]->pos.x, work->side[0].player[0]->pos.y, work->side[0].player[0]->pos.z);
        }
        if (work->unkCEA != 1) {
            work->side[1].player[0]->pos.y += 50.0f;
            work->side[1].player[0]->pos.x += 5.0f;
            Hu3DModelPosSetV(work->side[1].player[0]->mdlId, &work->side[1].player[0]->pos);
            omSetTra(work->side[1].player[0]->obj, work->side[1].player[0]->pos.x, work->side[1].player[0]->pos.y, work->side[1].player[0]->pos.z);
            work->side[1].player[1]->pos.y += 50.0f;
            Hu3DModelPosSetV(work->side[1].player[1]->mdlId, &work->side[1].player[1]->pos);
            omSetTra(work->side[1].player[1]->obj, work->side[1].player[1]->pos.x, work->side[1].player[1]->pos.y, work->side[1].player[1]->pos.z);
            work->side[1].player[2]->pos.y += 50.0f;
            work->side[1].player[2]->pos.x -= 5.0f;
            Hu3DModelPosSetV(work->side[1].player[2]->mdlId, &work->side[1].player[2]->pos);
            omSetTra(work->side[1].player[2]->obj, work->side[1].player[2]->pos.x, work->side[1].player[2]->pos.y, work->side[1].player[2]->pos.z);
        }
        break;

    case 4:
        WipeColorSet(255, 255, 255);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        work->mode++;
        if (work->unkCEA != 0) {
            work->side[0].player[0]->pos.y += 50.0f;
            Hu3DModelPosSetV(work->side[0].player[0]->mdlId, &work->side[0].player[0]->pos);
            omSetTra(work->side[0].player[0]->obj, work->side[0].player[0]->pos.x, work->side[0].player[0]->pos.y, work->side[0].player[0]->pos.z);
        }
        if (work->unkCEA != 1) {
            work->side[1].player[0]->pos.y += 50.0f;
            work->side[1].player[0]->pos.x += 5.0f;
            Hu3DModelPosSetV(work->side[1].player[0]->mdlId, &work->side[1].player[0]->pos);
            omSetTra(work->side[1].player[0]->obj, work->side[1].player[0]->pos.x, work->side[1].player[0]->pos.y, work->side[1].player[0]->pos.z);
            work->side[1].player[1]->pos.y += 50.0f;
            Hu3DModelPosSetV(work->side[1].player[1]->mdlId, &work->side[1].player[1]->pos);
            omSetTra(work->side[1].player[1]->obj, work->side[1].player[1]->pos.x, work->side[1].player[1]->pos.y, work->side[1].player[1]->pos.z);
            work->side[1].player[2]->pos.y += 50.0f;
            work->side[1].player[2]->pos.x -= 5.0f;
            Hu3DModelPosSetV(work->side[1].player[2]->mdlId, &work->side[1].player[2]->pos);
            omSetTra(work->side[1].player[2]->obj, work->side[1].player[2]->pos.x, work->side[1].player[2]->pos.y, work->side[1].player[2]->pos.z);
        }
        break;

    case 5:
        if (work->unkCEA != 0) {
            work->side[0].player[0]->pos.y += 50.0f;
            Hu3DModelPosSetV(work->side[0].player[0]->mdlId, &work->side[0].player[0]->pos);
            omSetTra(work->side[0].player[0]->obj, work->side[0].player[0]->pos.x, work->side[0].player[0]->pos.y, work->side[0].player[0]->pos.z);
        }
        if (work->unkCEA != 1) {
            work->side[1].player[0]->pos.y += 50.0f;
            work->side[1].player[0]->pos.x += 5.0f;
            Hu3DModelPosSetV(work->side[1].player[0]->mdlId, &work->side[1].player[0]->pos);
            omSetTra(work->side[1].player[0]->obj, work->side[1].player[0]->pos.x, work->side[1].player[0]->pos.y, work->side[1].player[0]->pos.z);
            work->side[1].player[1]->pos.y += 50.0f;
            Hu3DModelPosSetV(work->side[1].player[1]->mdlId, &work->side[1].player[1]->pos);
            omSetTra(work->side[1].player[1]->obj, work->side[1].player[1]->pos.x, work->side[1].player[1]->pos.y, work->side[1].player[1]->pos.z);
            work->side[1].player[2]->pos.y += 50.0f;
            work->side[1].player[2]->pos.x -= 5.0f;
            Hu3DModelPosSetV(work->side[1].player[2]->mdlId, &work->side[1].player[2]->pos);
            omSetTra(work->side[1].player[2]->obj, work->side[1].player[2]->pos.x, work->side[1].player[2]->pos.y, work->side[1].player[2]->pos.z);
        }
        if (!WipeCheckEnd()) {
            work->mode++;
        }
        break;

    case 6:
        for (i = 0; i < 32; i++) {
            if (work->mdlC44[i] >= 0) {
                Hu3DModelAttrSet(work->mdlC44[i], 1);
            }
        }
        if (work->unkCEA != 0) {
            Hu3DModelAttrSet(work->side[0].body.mdlId, 1);
            Hu3DModelAttrReset(work->mdl[63], 1);
            CharMotionSet(work->side[0].player[0]->charNo, work->side[0].player[0]->obj->mtnId[4]);
            CharModelAttrReset(work->side[0].player[0]->charNo, 0x40000002);
            CharModelAttrSet(work->side[0].player[0]->charNo, 0x40000001);
        }
        if (work->unkCEA != 1) {
            Hu3DModelAttrSet(work->side[1].body.mdlId, 1);
            Hu3DModelAttrReset(work->mdl[64], 1);
            CharMotionSet(work->side[1].player[0]->charNo, work->side[1].player[0]->obj->mtnId[4]);
            CharMotionSet(work->side[1].player[1]->charNo, work->side[1].player[1]->obj->mtnId[4]);
            CharMotionSet(work->side[1].player[2]->charNo, work->side[1].player[2]->obj->mtnId[4]);
            CharModelAttrReset(work->side[1].player[0]->charNo, 0x40000002);
            CharModelAttrReset(work->side[1].player[1]->charNo, 0x40000002);
            CharModelAttrReset(work->side[1].player[2]->charNo, 0x40000002);
            CharModelAttrSet(work->side[1].player[0]->charNo, 0x40000001);
            CharModelAttrSet(work->side[1].player[1]->charNo, 0x40000001);
            CharModelAttrSet(work->side[1].player[2]->charNo, 0x40000001);
        }

        if (work->unkCEA >= 0) {
            work->view.x = 640.0f;
            fn_1_42A8(work, work->unkCEA);
            work->cam[0].angleX = lbl_1_data_254[9].rot.x;
            work->cam[0].angleY = lbl_1_data_254[9].rot.y;
            work->cam[0].dist = lbl_1_data_254[9].rot.z;
            work->cam[0].target.x = lbl_1_data_254[9].target.x;
            work->cam[0].target.y = lbl_1_data_254[9].target.y;
            work->cam[0].target.z = lbl_1_data_254[9].target.z;
            Hu3DModelAttrReset(work->mdl[11], 1);
            Hu3DModelCameraSet(work->side[0].player[0]->mdlId, lbl_1_rodata_10[0]);
            Hu3DModelCameraSet(work->side[1].player[0]->mdlId, lbl_1_rodata_10[0]);
            Hu3DModelCameraSet(work->side[1].player[1]->mdlId, lbl_1_rodata_10[0]);
            Hu3DModelCameraSet(work->side[1].player[2]->mdlId, lbl_1_rodata_10[0]);
            for (i = 0; i < 7; i++) {
                for (j = 0; j < 3; j++) {
                    Hu3DModelAttrSet(work->mdlC84[i][j], 1);
                    Hu3DModelCameraSet(work->mdlCB4[i][j], lbl_1_rodata_10[0]);
                }
            }
            Hu3DModelCameraSet(work->mdlC84[7][0], lbl_1_rodata_10[0]);
            Hu3DModelCameraSet(work->mdlC84[7][1], lbl_1_rodata_10[0]);
            Hu3DModelCameraSet(work->mdlC84[7][2], lbl_1_rodata_10[0]);
            Hu3DModelAttrReset(work->mdl[8], 1);
            Hu3DModelAttrSet(work->mdl[9], 1);
            work->side[work->unkCEA].body.pos.x = 0.0f;
            work->side[work->unkCEA].body.pos.y = 0.0f;
            work->side[work->unkCEA].body.pos.z = -300.0f;
            work->side[work->unkCEA].body.rot.x = 0.0f;
            work->side[work->unkCEA].body.rot.y = 0.0f;
            work->side[work->unkCEA].body.rot.z = 0.0f;
            work->side[work->unkCEA ^ 1].body.pos.x = 150.0f;
            work->side[work->unkCEA ^ 1].body.pos.y = 0.0f;
            work->side[work->unkCEA ^ 1].body.pos.z = -900.0f;
            work->side[work->unkCEA ^ 1].body.rot.x = 0.0f;
            work->side[work->unkCEA ^ 1].body.rot.y = 0.0f;
            work->side[work->unkCEA ^ 1].body.rot.z = 0.0f;
            Hu3DModelPosSetV(work->side[work->unkCEA].body.mdlId, &work->side[work->unkCEA].body.pos);
            Hu3DModelRotSetV(work->side[work->unkCEA].body.mdlId, &work->side[work->unkCEA].body.rot);
            for (i = 0; i < 3; i++) {
                Hu3DModelShadowMapSet(work->mdlCB4[7][i]);
                Hu3DModelShadowMapSet(work->unkCE4[i]);
            }
            work->side[work->unkCEA].body.unk46 = work->mdl[29];
            if (work->unkCEA == 0) {
                Hu3DModelHookObjReset(work->side[0].body.mdlId, "m567-play0");
                work->side[0].player[0]->pos.x = 0.0f;
                work->side[0].player[0]->pos.y = 0.0f;
                work->side[0].player[0]->pos.z = 0.0f;
                work->side[0].player[0]->rot.x = 0.0f;
                work->side[0].player[0]->rot.y = 0.0f;
                work->side[0].player[0]->rot.z = 0.0f;
                work->side[1].player[0]->pos.x = -300.0f;
                work->side[1].player[0]->pos.y = 0.0f;
                work->side[1].player[0]->pos.z = -200.0f;
                work->side[1].player[0]->rot.x = 0.0f;
                work->side[1].player[0]->rot.y = 0.0f;
                work->side[1].player[0]->rot.z = 0.0f;
                work->side[1].player[1]->pos.x = 225.0f;
                work->side[1].player[1]->pos.y = 0.0f;
                work->side[1].player[1]->pos.z = -200.0f;
                work->side[1].player[1]->rot.x = 0.0f;
                work->side[1].player[1]->rot.y = 0.0f;
                work->side[1].player[1]->rot.z = 0.0f;
                work->side[1].player[2]->pos.x = 375.0f;
                work->side[1].player[2]->pos.y = 0.0f;
                work->side[1].player[2]->pos.z = -200.0f;
                work->side[1].player[2]->rot.x = 0.0f;
                work->side[1].player[2]->rot.y = 0.0f;
                work->side[1].player[2]->rot.z = 0.0f;
                Hu3DModelPosSetV(work->mdl[64], &work->side[1].body.pos);
                Hu3DModelRotSetV(work->mdl[64], &work->side[1].body.rot);
                CharMotionSet(work->side[0].player[0]->charNo, work->side[0].player[0]->obj->mtnId[3]);
                Hu3DMotionSet(work->side[0].body.mdlId, work->side[0].body.unk38);
                Hu3DModelAttrSet(work->side[0].body.mdlId, 0x40000001);
                Hu3DModelCameraSet(work->side[0].body.mdlId, lbl_1_rodata_10[0]);
            } else {
                Hu3DModelHookObjReset(work->side[1].body.mdlId, "m567-play3");
                Hu3DModelHookObjReset(work->side[1].body.mdlId, "m567-play1");
                Hu3DModelHookObjReset(work->side[1].body.mdlId, "m567-play2");
                work->side[0].player[0]->pos.x = -300.0f;
                work->side[0].player[0]->pos.y = 0.0f;
                work->side[0].player[0]->pos.z = -200.0f;
                work->side[0].player[0]->rot.x = 0.0f;
                work->side[0].player[0]->rot.y = 0.0f;
                work->side[0].player[0]->rot.z = 0.0f;
                work->side[1].player[0]->pos.x = -200.0f;
                work->side[1].player[0]->pos.y = 0.0f;
                work->side[1].player[0]->pos.z = 0.0f;
                work->side[1].player[0]->rot.x = 0.0f;
                work->side[1].player[0]->rot.y = 0.0f;
                work->side[1].player[0]->rot.z = 0.0f;
                work->side[1].player[1]->pos.x = 0.0f;
                work->side[1].player[1]->pos.y = 0.0f;
                work->side[1].player[1]->pos.z = 0.0f;
                work->side[1].player[1]->rot.x = 0.0f;
                work->side[1].player[1]->rot.y = 0.0f;
                work->side[1].player[1]->rot.z = 0.0f;
                work->side[1].player[2]->pos.x = 200.0f;
                work->side[1].player[2]->pos.y = 0.0f;
                work->side[1].player[2]->pos.z = 0.0f;
                work->side[1].player[2]->rot.x = 0.0f;
                work->side[1].player[2]->rot.y = 0.0f;
                work->side[1].player[2]->rot.z = 0.0f;
                Hu3DModelPosSetV(work->mdl[63], &work->side[0].body.pos);
                Hu3DModelRotSetV(work->mdl[63], &work->side[0].body.rot);
                CharMotionSet(work->side[1].player[0]->charNo, work->side[1].player[0]->obj->mtnId[3]);
                CharMotionSet(work->side[1].player[1]->charNo, work->side[1].player[1]->obj->mtnId[3]);
                CharMotionSet(work->side[1].player[2]->charNo, work->side[1].player[2]->obj->mtnId[3]);
                Hu3DModelRotSet(work->mdl[23], 0.0f, 180.0f, 0.0f);
                Hu3DModelRotSet(work->unkCE4[0], 0.0f, 180.0f, 0.0f);
                Hu3DModelRotSet(work->unkCE4[1], 0.0f, 180.0f, 0.0f);
                Hu3DModelRotSet(work->unkCE4[2], 0.0f, 180.0f, 0.0f);
                Hu3DMotionSet(work->side[1].body.mdlId, work->side[1].body.unk38);
                Hu3DModelAttrSet(work->side[1].body.mdlId, 0x40000001);
                Hu3DModelCameraSet(work->side[1].body.mdlId, lbl_1_rodata_10[0]);
            }
        } else {
            fn_1_4168(work);
            work->side[0].body.pos.x = 0.0f;
            work->side[0].body.pos.y = 0.0f;
            work->side[0].body.pos.z = 2100.0f;
            work->side[0].body.rot.x = 0.0f;
            work->side[0].body.rot.y = 0.0f;
            work->side[0].body.rot.z = 0.0f;
            work->side[0].player[0]->pos.x = 0.0f;
            work->side[0].player[0]->pos.y = 0.0f;
            work->side[0].player[0]->pos.z = 2400.0f;
            work->side[0].player[0]->rot.x = 0.0f;
            work->side[0].player[0]->rot.y = 0.0f;
            work->side[0].player[0]->rot.z = 0.0f;
            work->side[1].body.pos.x = 0.0f;
            work->side[1].body.pos.y = 0.0f;
            work->side[1].body.pos.z = -2100.0f;
            work->side[1].body.rot.x = 0.0f;
            work->side[1].body.rot.y = 180.0f;
            work->side[1].body.rot.z = 0.0f;
            work->side[1].player[0]->pos.x = 200.0f;
            work->side[1].player[0]->pos.y = 0.0f;
            work->side[1].player[0]->pos.z = -2400.0f;
            work->side[1].player[0]->rot.x = 0.0f;
            work->side[1].player[0]->rot.y = 180.0f;
            work->side[1].player[0]->rot.z = 0.0f;
            work->side[1].player[1]->pos.x = 0.0f;
            work->side[1].player[1]->pos.y = 0.0f;
            work->side[1].player[1]->pos.z = -2400.0f;
            work->side[1].player[1]->rot.x = 0.0f;
            work->side[1].player[1]->rot.y = 180.0f;
            work->side[1].player[1]->rot.z = 0.0f;
            work->side[1].player[2]->pos.x = -200.0f;
            work->side[1].player[2]->pos.y = 0.0f;
            work->side[1].player[2]->pos.z = -2400.0f;
            work->side[1].player[2]->rot.x = 0.0f;
            work->side[1].player[2]->rot.y = 180.0f;
            work->side[1].player[2]->rot.z = 0.0f;
            work->cam[0].angleX = lbl_1_data_254[7].rot.x;
            work->cam[0].angleY = lbl_1_data_254[7].rot.y;
            work->cam[0].dist = lbl_1_data_254[7].rot.z;
            work->cam[0].target.x = lbl_1_data_254[7].target.x;
            work->cam[0].target.y = lbl_1_data_254[7].target.y;
            work->cam[0].target.z = lbl_1_data_254[7].target.z;
            work->cam[1].angleX = lbl_1_data_254[8].rot.x;
            work->cam[1].angleY = lbl_1_data_254[8].rot.y;
            work->cam[1].dist = lbl_1_data_254[8].rot.z;
            work->cam[1].target.x = lbl_1_data_254[8].target.x;
            work->cam[1].target.y = lbl_1_data_254[8].target.y;
            work->cam[1].target.z = lbl_1_data_254[8].target.z;
            Hu3DModelCameraSet(work->side[0].player[0]->mdlId, lbl_1_rodata_10[0]);
            Hu3DModelCameraSet(work->side[1].player[0]->mdlId, lbl_1_rodata_10[1]);
            Hu3DModelCameraSet(work->side[1].player[1]->mdlId, lbl_1_rodata_10[1]);
            Hu3DModelCameraSet(work->side[1].player[2]->mdlId, lbl_1_rodata_10[1]);
            Hu3DModelPosSetV(work->mdl[63], &work->side[0].body.pos);
            Hu3DModelPosSetV(work->mdl[64], &work->side[1].body.pos);
            Hu3DModelRotSetV(work->mdl[63], &work->side[0].body.rot);
            Hu3DModelRotSetV(work->mdl[64], &work->side[1].body.rot);
            for (i = 0; i < 3; i++) {
                Hu3DModelCameraSet(work->mdlC84[0][i], lbl_1_rodata_10[0]);
                Hu3DModelShadowMapSet(work->mdlC84[0][i]);
                Hu3DModelCameraSet(work->mdlCB4[0][i], lbl_1_rodata_10[1]);
                Hu3DModelShadowMapSet(work->mdlCB4[0][i]);
            }
            for (i = 0; i < 8; i++) {
                for (j = 0; j < 3; j++) {
                    Hu3DModelAttrReset(work->mdlC84[i][j], 1);
                    Hu3DModelAttrReset(work->mdlCB4[i][j], 1);
                }
            }
        }

        Hu3DModelPosSetV(work->side[0].player[0]->mdlId, &work->side[0].player[0]->pos);
        omSetTra(work->side[0].player[0]->obj, work->side[0].player[0]->pos.x, work->side[0].player[0]->pos.y, work->side[0].player[0]->pos.z);
        Hu3DModelRotSetV(work->side[0].player[0]->mdlId, &work->side[0].player[0]->rot);
        omSetRot(work->side[0].player[0]->obj, work->side[0].player[0]->rot.x, work->side[0].player[0]->rot.y, work->side[0].player[0]->rot.z);
        Hu3DModelPosSetV(work->side[1].player[0]->mdlId, &work->side[1].player[0]->pos);
        omSetTra(work->side[1].player[0]->obj, work->side[1].player[0]->pos.x, work->side[1].player[0]->pos.y, work->side[1].player[0]->pos.z);
        Hu3DModelRotSetV(work->side[1].player[0]->mdlId, &work->side[1].player[0]->rot);
        omSetRot(work->side[1].player[0]->obj, work->side[1].player[0]->rot.x, work->side[1].player[0]->rot.y, work->side[1].player[0]->rot.z);
        Hu3DModelPosSetV(work->side[1].player[1]->mdlId, &work->side[1].player[1]->pos);
        omSetTra(work->side[1].player[1]->obj, work->side[1].player[1]->pos.x, work->side[1].player[1]->pos.y, work->side[1].player[1]->pos.z);
        Hu3DModelRotSetV(work->side[1].player[1]->mdlId, &work->side[1].player[1]->rot);
        omSetRot(work->side[1].player[1]->obj, work->side[1].player[1]->rot.x, work->side[1].player[1]->rot.y, work->side[1].player[1]->rot.z);
        Hu3DModelPosSetV(work->side[1].player[2]->mdlId, &work->side[1].player[2]->pos);
        omSetTra(work->side[1].player[2]->obj, work->side[1].player[2]->pos.x, work->side[1].player[2]->pos.y, work->side[1].player[2]->pos.z);
        Hu3DModelRotSetV(work->side[1].player[2]->mdlId, &work->side[1].player[2]->rot);
        omSetRot(work->side[1].player[2]->obj, work->side[1].player[2]->rot.x, work->side[1].player[2]->rot.y, work->side[1].player[2]->rot.z);
        Hu3DModelShadowSet(work->side[0].player[0]->mdlId);
        Hu3DModelShadowSet(work->side[1].player[0]->mdlId);
        Hu3DModelShadowSet(work->side[1].player[1]->mdlId);
        Hu3DModelShadowSet(work->side[1].player[2]->mdlId);
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
        work->mode++;
        break;

    case 7:
        if (!WipeCheckEnd()) {
            work->mode++;
        }
        if (work->unkCEA >= 0) {
            body = &work->side[work->unkCEA].body;
            time = Hu3DMotionTimeGet(body->mdlId);
            if (time >= 40.0f && time < 41.0f) {
                fn_1_4704(&work->list, fn_1_988C, body);
                Hu3DModelAttrReset(body->unk46, 1);
                Hu3DModelAttrReset(body->unk46, 0x40000002);
                Hu3DMotionTimeSet(body->unk46, 0.0f);
                Hu3DModelPosSet(body->unk46, body->pos.x, body->pos.y, body->pos.z);
                if (work->unkCEA == 0) {
                    lbl_1_data_43C[0] = HuAudFXPlay(0x8F6);
                }
                if (work->unkCEA == 1) {
                    lbl_1_data_43C[1] = HuAudFXPlay(0x8F8);
                }
            }
        }
        break;

    case 8:
        if (work->unkCEA >= 0) {
            body = &work->side[work->unkCEA].body;
            time = Hu3DMotionTimeGet(body->mdlId);
            if (time >= 40.0f && time < 41.0f) {
                fn_1_4704(&work->list, fn_1_988C, body);
                Hu3DModelAttrReset(body->unk46, 1);
                Hu3DModelAttrReset(body->unk46, 0x40000002);
                Hu3DMotionTimeSet(body->unk46, 0.0f);
                Hu3DModelPosSet(body->unk46, body->pos.x, body->pos.y, body->pos.z);
                if (work->unkCEA == 0) {
                    lbl_1_data_43C[0] = HuAudFXPlay(0x8F6);
                }
                if (work->unkCEA == 1) {
                    lbl_1_data_43C[1] = HuAudFXPlay(0x8F8);
                }
            }
        }
        MgSeqModeNext();
        break;
    }
}

/* asm 3385-3614, 216 insns. MGSEQ winner hook. */
void fn_1_32CC(s16 mode, s16 frameNo)
{
    M567_WORK *work = (M567_WORK *)lbl_1_bss_4->data;
    M567_BODY *body;
    float time;

    switch (work->time) {
    case 0:
        if (work->unkCEA == 0) {
            GWMgCoinBonusSet(work->side[0].player[0]->no, 10);
            CharModelAttrReset(work->side[0].player[0]->charNo, 0x40000002);
        }
        if (work->unkCEA == 1) {
            GWMgCoinBonusSet(work->side[1].player[0]->no, 10);
            GWMgCoinBonusSet(work->side[1].player[1]->no, 10);
            GWMgCoinBonusSet(work->side[1].player[2]->no, 10);
            CharModelAttrReset(work->side[1].player[0]->charNo, 0x40000002);
            CharModelAttrReset(work->side[1].player[1]->charNo, 0x40000002);
            CharModelAttrReset(work->side[1].player[2]->charNo, 0x40000002);
        }
        if (work->unkCEA < 0) {
            CharModelVoicePanSet(work->side[0].player[0]->charNo, 48);
            CharModelVoicePanSet(work->side[1].player[0]->charNo, 80);
            CharModelVoicePanSet(work->side[1].player[1]->charNo, 80);
            CharModelVoicePanSet(work->side[1].player[2]->charNo, 80);
            CharLoseVoicePlay(work->player[0]->charNo, work->player[1]->charNo,
                             work->player[2]->charNo, work->player[3]->charNo);
        }
        work->time++;
        /* fall through */

    case 1:
        if (work->unkCEA >= 0) {
            work->unkCF2++;
            body = &work->side[work->unkCEA].body;
            time = Hu3DMotionTimeGet(body->mdlId);
            if (time >= 40.0f && time < 41.0f) {
                fn_1_4704(&work->list, fn_1_988C, body);
                Hu3DModelAttrReset(body->unk46, 1);
                Hu3DModelAttrReset(body->unk46, 0x40000002);
                Hu3DMotionTimeSet(body->unk46, 0.0f);
                Hu3DModelPosSetV(body->unk46, &body->pos);
                if (work->unkCF2 < 180) {
                    if (work->unkCEA == 0) {
                        lbl_1_data_43C[0] = HuAudFXPlay(0x8F6);
                    }
                    if (work->unkCEA == 1) {
                        lbl_1_data_43C[1] = HuAudFXPlay(0x8F8);
                    }
                } else if (HuAudFXStatusGet(lbl_1_data_43C[work->unkCEA]) == 2) {
                    HuAudFXFadeOut(lbl_1_data_43C[work->unkCEA], 1000);
                }
            }
        }
        break;
    }
}

/* asm 3617-3679, 60 insns. MGSEQ fade-out hook. */
void fn_1_362C(s16 mode, s16 frameNo)
{
    M567_WORK *work = (M567_WORK *)lbl_1_bss_4->data;
    M567_BODY *body;
    float time;

    if (work->unkCEA >= 0) {
        body = &work->side[work->unkCEA].body;
        time = Hu3DMotionTimeGet(body->mdlId);
        if (time >= 40.0f && time < 41.0f) {
            fn_1_4704(&work->list, fn_1_988C, body);
            Hu3DModelAttrReset(body->unk46, 1);
            Hu3DModelAttrReset(body->unk46, 0x40000002);
            Hu3DMotionTimeSet(body->unk46, 0.0f);
            Hu3DModelPosSetV(body->unk46, &body->pos);
        }
    }
}

/* asm 3682-3698, 15 insns. MGSEQ close hook. */
void fn_1_371C(s16 mode, s16 frameNo)
{
    M567_WORK *work = (M567_WORK *)lbl_1_bss_4->data;

    fn_1_4164(&work->view);
}

/* asm 3701-3812, 108 insns. Player object init (installed by ObjectSetup). */
void fn_1_3758(OMOBJ *obj)
{
    M567_PLAYER *player = (M567_PLAYER *)obj->data;
    M567_WORK *work = (M567_WORK *)lbl_1_bss_4->data;
    s32 i;

    player->no = obj->work[0];
    player->charNo = GwPlayerConf[player->no].charNo;
    player->grp = GwPlayerConf[player->no].grp;
    player->padNo = GwPlayerConf[player->no].padNo;
    player->comF = GwPlayerConf[player->no].type;
    player->dif = GwPlayerConf[player->no].dif;
    player->obj = obj;
    work->player[player->no] = player;

    obj->mdlId[0] = CharModelCreate(player->charNo, 8);
    player->mdlId = obj->mdlId[0];
    for (i = 0; i < 5; i++) {
        obj->mtnId[i] = CharMotionCreate(player->charNo, lbl_1_data_28[player->charNo][i]);
    }
    CharMotionSet(player->charNo, obj->mtnId[1]);
    CharModelAttrSet(player->charNo, 0x40000002);
    Hu3DModelLayerSet(obj->mdlId[0], 2);
    CharEffectLayerSet(4);
    CharMotionDataClose(player->charNo);
    obj->objFunc = fn_1_3908;
}

/* asm 3815-3852, 34 insns. Player object main. */
void fn_1_3908(OMOBJ *obj)
{
    M567_PLAYER *player = (M567_PLAYER *)obj->data;
    M567_WORK *work = (M567_WORK *)lbl_1_bss_4->data;

    if (work->unkCF4 != 0 && player->elem->unk4 == 15) {
        if (player->comF != 0) {
            fn_1_8F1C(player);
        } else {
            fn_1_8EC8(player);
        }
    }
}

/* asm 3855-3857, 1 insn. Unreferenced, empty. */
void fn_1_3990(void)
{
}

/* asm 3860-3886, 25 insns. Main object init (installed by ObjectSetup). */
void fn_1_3994(OMOBJ *obj)
{
    M567_WORK *work = (M567_WORK *)lbl_1_bss_4->data;

    fn_1_4680(&work->list, work->node, 100);
    work->unkCEA = -1;
    obj->objFunc = fn_1_39F8;
}

/* asm 3889-3992, 95 insns. Main object main. */
void fn_1_39F8(OMOBJ *obj)
{
    M567_WORK *work = (M567_WORK *)lbl_1_bss_4->data;
    M567_SIDE *side;
    HuVecF pos;
    s32 active1, active0;

    active0 = fn_1_7084(&work->side[0]);
    active1 = fn_1_7084(&work->side[1]);
    if (active0 != 0 || active1 != 0) {
        if (active0 != 0) {
            if (active1 != 0) {
                work->unkCEA = frandmod(2);
            } else {
                work->unkCEA = 0;
            }
        } else if (active1 != 0) {
            work->unkCEA = 1;
        }

        /* A side has reached row 9: stop both, and pull the loser back if it got there too. */
        if (work->side[0].unk1AE != 4 && work->side[0].unk1AE != 7 && work->side[0].unk1AE != 8) {
            work->side[0].unk1AE = 7;
        }
        if (work->side[1].unk1AE != 4 && work->side[1].unk1AE != 7 && work->side[1].unk1AE != 8) {
            work->side[1].unk1AE = 7;
        }

        side = &work->side[work->unkCEA ^ 1];
        if (side->unk1AA == 9) {
            side->unk1AA = side->unk1A6;
            side->body.unk2C = side->body.unk20;
        }
    }

    fn_1_4404(&work->cam[0], &pos);
    fn_1_8330(&work->side[0].ui, &pos);
    fn_1_4404(&work->cam[1], &pos);
    fn_1_8330(&work->side[1].ui, &pos);
    fn_1_3EEC(&work->view);
    fn_1_47D0(&work->list);
}

/* asm 3995-3997, 1 insn. Unreferenced, empty. */
void fn_1_3B74(void)
{
}

/* asm 4000-4039, 32 insns. Clear mdl[], mdl2[] and mdlC44[] to -1. */
void fn_1_3B78(M567_WORK *work)
{
    s32 i;

    for (i = 0; i < 65; i++) {
        work->mdl[i] = -1;
    }
    for (i = 0; i < 9; i++) {
        work->mdl2[i] = -1;
    }
    for (i = 0; i < 32; i++) {
        work->mdlC44[i] = -1;
    }
}

/* asm 4042-4077, 34 insns. Stage light; work is not read. */
void fn_1_3BF8(M567_WORK *work)
{
    HU3DLIGHTID light;

    light = Hu3DGLightCreate(0.0f, 4000.0f, 0.0f, 0.0f, -1.0f, -1.0f, 127, 127, 127);
    Hu3DGLightInfinitytSet(light);
}

/* asm 4080-4216, 133 insns. Both Hu3D cameras and the two M567_CAMs. */
void fn_1_3C80(M567_WORK *work)
{
    s32 i;

    for (i = 0; i < 2; i++) {
        Hu3DCameraCreate(lbl_1_rodata_10[i]);
        Hu3DCameraPerspectiveSet(lbl_1_rodata_10[i], 45.0f, 20.0f, 20000.0f, 0.6f);
        Hu3DCameraPosSet(lbl_1_rodata_10[i],
            0.0f, 300.0f, 1000.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 150.0f, 0.0f);
        fn_1_439C(&work->cam[i], lbl_1_rodata_10[i]);
        work->cam[i].angleX = lbl_1_data_254[i].rot.x;
        work->cam[i].angleY = lbl_1_data_254[i].rot.y;
        work->cam[i].dist = lbl_1_data_254[i].rot.z;
        work->cam[i].target.x = lbl_1_data_254[i].target.x;
        work->cam[i].target.y = lbl_1_data_254[i].target.y;
        work->cam[i].target.z = lbl_1_data_254[i].target.z;
    }
}

/* asm 4219-4242, 22 insns. */
void fn_1_3E94(M567_VIEW *view)
{
    view->x = 640.0f;
    view->y = 0.0f;
    view->mode = 0;
    fn_1_3EEC(view);
}

/* asm 4245-4405, 158 insns. Viewports and scissors from view->x. */
void fn_1_3EEC(M567_VIEW *view)
{
    float aspect;
    s32 i;
    u32 scissorX;

    i = 0;
    Hu3DCameraViewportSet(lbl_1_rodata_10[i],
        0.0f, 0.0f, 16.0f + view->x, 480.0f, 0.0f, 1.0f);
    i++;
    Hu3DCameraViewportSet(lbl_1_rodata_10[i],
        view->x - 16.0f, 0.0f, 16.0f + (640.0f - view->x), 480.0f, 0.0f, 1.0f);

    i = 0;
    Hu3DCameraScissorSet(lbl_1_rodata_10[i], 0, 0, (u32)(view->x - 1.0f), 480);
    i++;
    scissorX = (u32)(640.0f - view->x - 1.0f);
    Hu3DCameraScissorSet(lbl_1_rodata_10[i], scissorX, 0, (u32)(1.0f + view->x), 480);

    i = 0;
    aspect = 0.9f * view->x / 480.0f;
    if (aspect < 0.0f) {
        aspect = 0.0f;
    }
    Hu3DCameraPerspectiveSet(lbl_1_rodata_10[i], 45.0f, 20.0f, 20000.0f, aspect);
    i++;
}

/* asm 4408-4410, 1 insn. Empty (called from the close hook). */
void fn_1_4164(M567_VIEW *view)
{
}

/* asm 4413-4494, 80 insns. Multi-shadow setup; work is not read. */
void fn_1_4168(M567_WORK *work)
{
    s16 cameraBit;
    HuVecF up = { 0.0f, 1.0f, 0.0f };
    HuVecF pos = { 0.0f, 2000.0f, 2000.0f };
    HuVecF target = { 0.1f, 0.0f, 2000.0f };

    cameraBit = lbl_1_rodata_10[0] | lbl_1_rodata_10[1];
    Hu3DShadowMultiCreate(45.0f, 20.0f, 20000.0f, cameraBit);
    Hu3DShadowMultiPosSet(&pos, &up, &target, lbl_1_rodata_10[0]);

    pos.z *= -1.0f;
    target.z *= -1.0f;
    Hu3DShadowMultiPosSet(&pos, &up, &target, lbl_1_rodata_10[1]);
}

/* asm 4497-4560, 61 insns. Shadow setup; the second parameter is stored and never read. */
void fn_1_42A8(M567_WORK *work, s32 unused)
{
    HuVecF up = { 0.0f, 1.0f, 0.0f };
    HuVecF pos = { 0.0f, 2000.0f, -300.0f };
    HuVecF target = { 0.1f, 0.0f, -300.0f };

    Hu3DShadowCreate(45.0f, 20.0f, 20000.0f);
    if (unused != 0) {
        pos.z *= -1.0f;
        target.z *= -1.0f;
    }
    Hu3DShadowPosSet(&pos, &up, &target);
}

/* asm 4563-4590, 26 insns. */
void fn_1_439C(M567_CAM *cam, s16 bit)
{
    cam->target.x = 0.0f;
    cam->target.y = 0.0f;
    cam->target.z = 0.0f;
    cam->angleX = 0.0f;
    cam->angleY = 0.0f;
    cam->dist = 3000.0f;
    cam->bit = bit;
}

/* asm 4593-4761, 159 insns. Wrap angles, compute the eye into pos, Hu3DCameraPosSet. */
void fn_1_4404(M567_CAM *cam, HuVecF *pos)
{
    while (cam->angleX > 360.0f) {
        cam->angleX -= 360.0f;
    }
    while (cam->angleX < 0.0f) {
        cam->angleX += 360.0f;
    }
    while (cam->angleY > 360.0f) {
        cam->angleY -= 360.0f;
    }
    while (cam->angleY < 0.0f) {
        cam->angleY += 360.0f;
    }

    pos->x = cam->target.x + cam->dist * HuCos(cam->angleY) * HuCos(cam->angleX);
    pos->y = cam->target.y + cam->dist * HuSin(cam->angleY);
    pos->z = cam->target.z + cam->dist * HuCos(cam->angleY) * HuSin(cam->angleX);
    Hu3DCameraPosSet(cam->bit,
        pos->x, pos->y, pos->z,
        0.0f, 1.0f, 0.0f,
        cam->target.x, cam->target.y, cam->target.z);
}

/* asm 4764-4800, 33 insns. Link num pool nodes into the free list. */
void fn_1_4680(M567_LIST *list, M567_NODE *pool, s32 num)
{
    s32 i;

    list->head = NULL;
    list->free = pool;
    for (i = 0; i < num - 1; i++, pool++) {
        pool->prev = NULL;
        pool->next = pool + 1;
        pool->func = NULL;
        pool->data = NULL;
        pool->list = list;
    }
    pool->prev = NULL;
    pool->next = NULL;
    pool->func = NULL;
    pool->data = NULL;
    pool->list = list;
}

/* asm 4803-4827, 21 insns. Take a free node, set func/data, push on the active list. */
M567_NODE *fn_1_4704(M567_LIST *list, M567_TASKFUNC func, void *data)
{
    M567_NODE *node;

    node = list->free;
    if (node) {
        list->free = node->next;
        node->func = func;
        node->data = data;
        node->next = list->head;
        if (node->next) {
            node->next->prev = node;
        }
        list->head = node;
    }
    return node;
}

/* asm 4830-4865, 30 insns. Unreferenced: return a node to the free list. */
void fn_1_4758(M567_NODE *node)
{
    M567_LIST *list;

    if (node) {
        list = node->list;
        if (node->prev) {
            node->prev->next = node->next;
        } else {
            list->head = node->next;
        }
        if (node->next) {
            node->next->prev = node->prev;
        }
        node->prev = NULL;
        node->next = list->free;
        node->func = NULL;
        list->free = node;
    }
}

/* asm 4868-4931, 56 insns. Run every task; free those whose func returns TRUE. */
void fn_1_47D0(M567_LIST *list)
{
    M567_NODE *node;
    M567_NODE *next;

    node = list->head;
    while (node) {
        next = node->next;
        if (node->func && node->func(node) && node) {
            M567_LIST *nodeList = node->list;

            if (node->prev) {
                node->prev->next = node->next;
            } else {
                nodeList->head = node->next;
            }
            if (node->next) {
                node->next->prev = node->prev;
            }
            node->prev = NULL;
            node->next = nodeList->free;
            node->func = NULL;
            nodeList->free = node;
        }
        node = next;
    }
}

/* asm 4934-6204, 1225 insns. Stage models. */
void fn_1_48B0(M567_WORK *work)
{
    s16 kind[8][3];
    s16 (*grid)[5];
    HU3DMODELID modelId;
    s32 unused;
    s32 count;
    s32 pattern;
    s32 idx;
    s32 row;
    s32 col;

    if (work->mdl[8] < 0) {
        modelId = work->mdl[8] = Hu3DModelCreateData(lbl_1_data_12C[8]);
    } else {
        modelId = Hu3DModelLink(work->mdl[8]);
    }
    Hu3DModelAttrSet(modelId, 1);
    Hu3DModelAttrSet(modelId, 0x40000002);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_rodata_10[0]);
    if (work->mdl[9] < 0) {
        modelId = work->mdl[9] = Hu3DModelCreateData(lbl_1_data_12C[9]);
    } else {
        modelId = Hu3DModelLink(work->mdl[9]);
    }
    Hu3DModelAttrSet(modelId, 1);
    Hu3DModelAttrSet(modelId, 0x40000002);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(modelId, 1);
    if (work->mdl[10] < 0) {
        modelId = work->mdl[10] = Hu3DModelCreateData(lbl_1_data_12C[10]);
    } else {
        modelId = Hu3DModelLink(work->mdl[10]);
    }
    Hu3DModelAttrSet(modelId, 1);
    Hu3DModelAttrSet(modelId, 0x40000002);
    Hu3DModelLayerSet(modelId, 1);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(modelId, 1);
    if (work->mdl[11] < 0) {
        modelId = work->mdl[11] = Hu3DModelCreateData(lbl_1_data_12C[11]);
    } else {
        modelId = Hu3DModelLink(work->mdl[11]);
    }
    Hu3DModelAttrSet(modelId, 1);
    Hu3DModelAttrSet(modelId, 0x40000001);
    Hu3DModelLayerSet(modelId, 1);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_rodata_10[0]);
    if (work->mdl[12] < 0) {
        modelId = work->mdl[12] = Hu3DModelCreateData(lbl_1_data_12C[12]);
    } else {
        modelId = Hu3DModelLink(work->mdl[12]);
    }
    Hu3DModelAttrSet(modelId, 1);
    Hu3DModelAttrSet(modelId, 0x40000002);
    Hu3DModelLayerSet(modelId, 1);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_rodata_10[0]);
    Hu3DModelAttrReset(modelId, 1);
    if (work->mdl[23] < 0) {
        modelId = work->mdl[23] = Hu3DModelCreateData(lbl_1_data_12C[23]);
    } else {
        modelId = Hu3DModelLink(work->mdl[23]);
    }
    Hu3DModelAttrSet(modelId, 1);
    Hu3DModelAttrSet(modelId, 0x40000002);
    Hu3DModelLayerSet(modelId, 1);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(modelId, 1);
    if (work->mdl[25] < 0) {
        modelId = work->mdl[25] = Hu3DModelCreateData(lbl_1_data_12C[25]);
    } else {
        modelId = Hu3DModelLink(work->mdl[25]);
    }
    Hu3DModelAttrSet(modelId, 1);
    Hu3DModelAttrSet(modelId, 0x40000002);
    Hu3DModelLayerSet(modelId, 1);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(modelId, 1);
    if (work->mdl[26] < 0) {
        modelId = work->mdl[26] = Hu3DModelCreateData(lbl_1_data_12C[26]);
    } else {
        modelId = Hu3DModelLink(work->mdl[26]);
    }
    Hu3DModelAttrSet(modelId, 1);
    Hu3DModelAttrSet(modelId, 0x40000002);
    Hu3DModelLayerSet(modelId, 1);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 180.0f, 0.0f);
    Hu3DModelAttrReset(modelId, 1);
    if (work->mdl[63] < 0) {
        modelId = work->mdl[63] = Hu3DModelCreateData(lbl_1_data_12C[63]);
    } else {
        modelId = Hu3DModelLink(work->mdl[63]);
    }
    Hu3DModelAttrSet(modelId, 1);
    Hu3DModelAttrSet(modelId, 0x40000002);
    Hu3DModelLayerSet(modelId, 2);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    if (work->mdl[64] < 0) {
        modelId = work->mdl[64] = Hu3DModelCreateData(lbl_1_data_12C[64]);
    } else {
        modelId = Hu3DModelLink(work->mdl[64]);
    }
    Hu3DModelAttrSet(modelId, 1);
    Hu3DModelAttrSet(modelId, 0x40000002);
    Hu3DModelLayerSet(modelId, 2);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    if (work->mdl[29] < 0) {
        modelId = work->mdl[29] = Hu3DModelCreateData(lbl_1_data_12C[29]);
    } else {
        modelId = Hu3DModelLink(work->mdl[29]);
    }
    Hu3DModelAttrSet(modelId, 1);
    Hu3DModelAttrSet(modelId, 0x40000002);
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_rodata_10[0]);

    grid = work->side[0].grid;
    count = 0;
    pattern = frandmod(5);
    idx = 0;
    unused = 0;
    for (row = 1; row < 9; row++) {
        for (col = 1; col < 4; col++) {
            if (grid[row][col] == -1) {
                kind[row - 1][col - 1] = frandmod(4);
                if (work->mdl[kind[row - 1][col - 1] + 13] < 0) {
                    modelId = work->mdl[kind[row - 1][col - 1] + 13] = Hu3DModelCreateData(lbl_1_data_12C[kind[row - 1][col - 1] + 13]);
                } else {
                    modelId = Hu3DModelLink(work->mdl[kind[row - 1][col - 1] + 13]);
                }
                work->mdlC44[count] = modelId;
                count++;
                Hu3DModelAttrSet(modelId, 1);
                Hu3DModelAttrSet(modelId, 0x40000002);
                Hu3DModelLayerSet(modelId, 0);
                Hu3DModelPosSet(modelId, 300.0f * (col - 2), 0.0f, 2700.0f - 300.0f * row);
                Hu3DModelRotSet(modelId, 0.0f, 180.0f, 0.0f);
                Hu3DModelAttrReset(modelId, 1);
            }
            if (work->mdl[lbl_1_data_344[pattern][idx]] < 0) {
                modelId = work->mdl[lbl_1_data_344[pattern][idx]] = Hu3DModelCreateData(lbl_1_data_12C[lbl_1_data_344[pattern][idx]]);
            } else {
                modelId = Hu3DModelLink(work->mdl[lbl_1_data_344[pattern][idx]]);
            }
            idx++;
            Hu3DModelAttrSet(modelId, 1);
            Hu3DModelAttrSet(modelId, 0x40000002);
            Hu3DModelLayerSet(modelId, 0);
            Hu3DModelPosSet(modelId, 300.0f * (col - 2), 0.0f, 2700.0f - 300.0f * row);
            Hu3DModelRotSet(modelId, 0.0f, 180.0f, 0.0f);
            Hu3DModelAttrReset(modelId, 1);
            work->mdlC84[row - 1][col - 1] = modelId;
        }
    }

    for (col = 1; col < 4; col++) {
        if (work->mdl[17] < 0) {
            modelId = work->mdl[17] = Hu3DModelCreateData(lbl_1_data_12C[17]);
        } else {
            modelId = Hu3DModelLink(work->mdl[17]);
        }
        Hu3DModelAttrSet(modelId, 1);
        Hu3DModelAttrSet(modelId, 0x40000002);
        Hu3DModelLayerSet(modelId, 0);
        Hu3DModelPosSet(modelId, 300.0f * (col - 2), 0.0f, 0.0f);
        Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrReset(modelId, 1);
        work->unkCE4[col - 1] = modelId;
    }

    idx = 0;
    for (row = 1; row < 9; row++) {
        for (col = 1; col < 4; col++) {
            if (grid[row][col] == -1) {
                if (work->mdl[kind[row - 1][col - 1] + 13] < 0) {
                    modelId = work->mdl[kind[row - 1][col - 1] + 13] = Hu3DModelCreateData(lbl_1_data_12C[kind[row - 1][col - 1] + 13]);
                } else {
                    modelId = Hu3DModelLink(work->mdl[kind[row - 1][col - 1] + 13]);
                }
                work->mdlC44[count] = modelId;
                count++;
                Hu3DModelAttrSet(modelId, 1);
                Hu3DModelAttrSet(modelId, 0x40000002);
                Hu3DModelLayerSet(modelId, 0);
                Hu3DModelPosSet(modelId, 300.0f * -(col - 2), 0.0f, -2700.0f + 300.0f * row);
                Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
                Hu3DModelAttrReset(modelId, 1);
            }
            if (work->mdl[lbl_1_data_344[pattern][idx]] < 0) {
                modelId = work->mdl[lbl_1_data_344[pattern][idx]] = Hu3DModelCreateData(lbl_1_data_12C[lbl_1_data_344[pattern][idx]]);
            } else {
                modelId = Hu3DModelLink(work->mdl[lbl_1_data_344[pattern][idx]]);
            }
            idx++;
            Hu3DModelAttrSet(modelId, 1);
            Hu3DModelAttrSet(modelId, 0x40000002);
            Hu3DModelLayerSet(modelId, 0);
            Hu3DModelPosSet(modelId, 300.0f * -(col - 2), 0.0f, -2700.0f + 300.0f * row);
            Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
            Hu3DModelAttrReset(modelId, 1);
            work->mdlCB4[row - 1][col - 1] = modelId;
        }
    }
}

/* asm 6207-6438, 204 insns. Build side[0].grid. */
void fn_1_5BD4(s16 (*grid)[5])
{
    s16 rows[9][5] = {
        { -1,  0,  0,  0, -1 },
        { -1, -1,  0,  0, -1 },
        { -1,  0, -1,  0, -1 },
        { -1, -1, -1,  0, -1 },
        { -1,  0,  0, -1, -1 },
        { -1, -1,  0, -1, -1 },
        { -1,  0, -1, -1, -1 },
        { -1,  0,  0,  0, -1 },
        { -1,  2,  2,  2, -1 },
    };
    s16 count[3];
    s16 choices[3] = { 1, 2, 4 };
    s32 row, col, scan;
    s32 prev, forced;

    for (col = 0; col < 5; col++) {
        grid[0][col] = -1;
        grid[10][col] = -1;
    }
    for (col = 0; col < 5; col++) {
        grid[1][col] = rows[7][col];
        grid[9][col] = rows[8][col];
    }

    prev = choices[frandmod(3)];
    for (col = 0; col < 5; col++) {
        grid[2][col] = rows[prev][col];
    }

    for (row = 3; row < 9; row++) {
        count[0] = 0;
        count[1] = 0;
        count[2] = 0;
        if (row >= 5) {
            for (scan = row - 4; scan < row; scan++) {
                count[0] += (grid[scan][1] == 0);
                count[1] += (grid[scan][2] == 0);
                count[2] += (grid[scan][3] == 0);
            }
        }

        forced = 0;
        if (count[0] == 4) {
            forced += 1;
        }
        if (count[1] == 4) {
            forced += 2;
        }
        if (count[2] == 4) {
            forced += 4;
        }

        if (forced != 0 && row < 8) {
            if (prev != 0) {
                prev = 0;
                for (col = 0; col < 5; col++) {
                    grid[row][col] = rows[prev][col];
                }
                row++;
            }
            prev = forced;
            for (col = 0; col < 5; col++) {
                grid[row][col] = rows[prev][col];
            }
        } else {
            if (row == 8) {
                prev = fn_1_5FC0(prev);
            } else {
                prev = fn_1_5F04(prev);
            }
            for (col = 0; col < 5; col++) {
                grid[row][col] = rows[prev][col];
            }
        }
    }
}

/* asm 6441-6495, 47 insns. */
s32 fn_1_5F04(s32 prev)
{
    s32 choices[3] = { 0, 2, 4 };
    s32 next;

    switch (prev) {
    case 0:
        next = frandmod(6) + 1;
        break;
    case 1:
        next = choices[frandmod(3)];
        break;
    case 4:
        next = frandmod(3);
        break;
    case 2:
    case 3:
    case 5:
    case 6:
        next = 0;
        break;
    }
    return next;
}

/* asm 6498-6558, 53 insns. */
s32 fn_1_5FC0(s32 prev)
{
    s32 choices4[2] = { 0, 4 };
    s32 choices1[2] = { 0, 1 };
    s32 next;

    switch (prev) {
    case 0:
        next = frandmod(6) + 1;
        break;
    case 1:
        next = choices4[frandmod(2)];
        break;
    case 4:
        next = choices1[frandmod(2)];
        break;
    case 2:
    case 3:
    case 5:
    case 6:
        next = 0;
        break;
    }
    return next;
}

/* asm 6561-6591, 25 insns. Unreferenced: copy 12 rows of 5 (see the grid note above). */
void fn_1_6094(s16 (*dst)[5], s16 (*src)[5])
{
    s32 row, col;

    for (row = 0; row < 12; row++) {
        for (col = 0; col < 5; col++) {
            dst[row][col] = src[row][col];
        }
    }
}

/* asm 6594-7174, 559 insns. Sides, players, bodies, UIs. */
void fn_1_60F8(M567_WORK *work)
{
    M567_PLAYER *team[3];
    M567_PLAYER *player;
    M567_PLAYER *tmp;
    M567_BODY *body;
    HU3DMODELID modelId;
    s32 i;
    s32 n;
    s32 row;
    s32 col;
    s16 a;
    s16 b;

    work->side[0].unk1A4 = 0;
    work->side[1].unk1A4 = 1;
    work->side[0].unk1A6 = 1;
    work->side[0].unk1A8 = 2;
    work->side[1].unk1A6 = 1;
    work->side[1].unk1A8 = 2;

    n = 0;
    for (i = 0; i < 4; i++) {
        player = work->player[i];
        if (player->grp == 0) {
            work->side[0].player[0] = player;
        } else {
            team[n] = player;
            n++;
        }
    }
    for (i = 0; i < 3; i++) {
        a = frandmod(3);
        b = frandmod(3);
        tmp = team[a];
        team[a] = team[b];
        team[b] = tmp;
    }
    for (i = 0; i < 3; i++) {
        work->side[1].player[i] = team[i];
    }

    work->side[0].player[0]->slot = 0;
    work->side[1].player[0]->slot = 0;
    work->side[1].player[1]->slot = 1;
    work->side[1].player[2]->slot = 2;
    work->side[0].player[0]->side = &work->side[0];
    work->side[1].player[0]->side = &work->side[1];
    work->side[1].player[1]->side = &work->side[1];
    work->side[1].player[2]->side = &work->side[1];
    work->side[0].cam = &work->cam[0];
    work->side[1].cam = &work->cam[1];

    fn_1_5BD4(work->side[0].grid);
    /* Twelve rows into an eleven-row grid: the retail copy runs into result[] and body.pos. */
    for (row = 0; row < 12; row++) {
        for (col = 0; col < 5; col++) {
            work->side[1].grid[row][col] = work->side[0].grid[row][col];
        }
    }

    player = work->side[0].player[0];
    player->pos.x = 0.0f;
    player->pos.y = 0.0f;
    player->pos.z = 0.0f;
    player->rot.x = 0.0f;
    player->rot.y = 0.0f;
    player->rot.z = 0.0f;
    Hu3DModelPosSetV(player->mdlId, &player->pos);
    omSetTra(player->obj, player->pos.x, player->pos.y, player->pos.z);
    Hu3DModelRotSetV(player->mdlId, &player->rot);
    omSetRot(player->obj, player->rot.x, player->rot.y, player->rot.z);
    for (i = 0; i < 3; i++) {
        player = work->side[1].player[i];
        player->pos.x = 0.0f;
        player->pos.y = 0.0f;
        player->pos.z = 0.0f;
        player->rot.x = 0.0f;
        player->rot.y = 0.0f;
        player->rot.z = 0.0f;
        Hu3DModelPosSetV(player->mdlId, &player->pos);
        omSetTra(player->obj, player->pos.x, player->pos.y, player->pos.z);
        Hu3DModelRotSetV(player->mdlId, &player->rot);
        omSetRot(player->obj, player->rot.x, player->rot.y, player->rot.z);
    }

    body = &work->side[0].body;
    fn_1_69B4(body, 0);
    body->pos.x = 0.0f;
    body->pos.y = 0.0f;
    body->pos.z = 2400.0f;
    body->rot.x = 0.0f;
    body->rot.y = 180.0f;
    body->rot.z = 0.0f;
    Hu3DModelPosSetV(body->mdlId, &body->pos);
    Hu3DModelRotSetV(body->mdlId, &body->rot);
    body = &work->side[1].body;
    fn_1_69B4(body, 1);
    body->pos.x = 0.0f;
    body->pos.y = 0.0f;
    body->pos.z = -2400.0f;
    body->rot.x = 0.0f;
    body->rot.y = 0.0f;
    body->rot.z = 0.0f;
    Hu3DModelPosSetV(body->mdlId, &body->pos);
    Hu3DModelRotSetV(body->mdlId, &body->rot);

    work->side[0].ui.elem[0].unk10 = work->side[0].body.miniMdlId[0];
    work->side[1].ui.elem[0].unk10 = work->side[1].body.miniMdlId[0];
    work->side[1].ui.elem[1].unk10 = work->side[1].body.miniMdlId[1];
    work->side[1].ui.elem[2].unk10 = work->side[1].body.miniMdlId[2];
    fn_1_7DB4(&work->side[0].ui, work->side[0].cam, 0);
    fn_1_7DB4(&work->side[1].ui, work->side[1].cam, 1);

    Hu3DModelHookSet(work->side[0].body.mdlId, "m567-play0", work->side[0].player[0]->mdlId);
    Hu3DModelHookSet(work->side[1].body.mdlId, "m567-play3", work->side[1].player[0]->mdlId);
    Hu3DModelHookSet(work->side[1].body.mdlId, "m567-play1", work->side[1].player[1]->mdlId);
    Hu3DModelHookSet(work->side[1].body.mdlId, "m567-play2", work->side[1].player[2]->mdlId);
    Hu3DModelHookSet(work->side[0].body.mdlId, "m567-1pa_mini", work->side[0].body.miniMdlId[0]);
    Hu3DModelHookSet(work->side[1].body.mdlId, "m567-3pa_mini", work->side[1].body.miniMdlId[0]);
    Hu3DModelHookSet(work->side[1].body.mdlId, "m567-3pb_mini", work->side[1].body.miniMdlId[1]);
    Hu3DModelHookSet(work->side[1].body.mdlId, "m567-3pc_mini", work->side[1].body.miniMdlId[2]);
    Hu3DModelHookSet(work->side[0].body.mdlId, "m567-pum0", work->side[0].body.pumMdlId[0]);
    Hu3DModelHookSet(work->side[1].body.mdlId, "m567-pum3", work->side[1].body.pumMdlId[0]);
    Hu3DModelHookSet(work->side[1].body.mdlId, "m567-pum1", work->side[1].body.pumMdlId[1]);
    Hu3DModelHookSet(work->side[1].body.mdlId, "m567-pum2", work->side[1].body.pumMdlId[2]);

    work->side[0].player[0]->elem = &work->side[0].ui.elem[0];
    work->side[1].player[0]->elem = &work->side[1].ui.elem[0];
    work->side[1].player[1]->elem = &work->side[1].ui.elem[1];
    work->side[1].player[2]->elem = &work->side[1].ui.elem[2];
    work->side[0].player[0]->linkMdlId = work->side[0].body.pumMdlId[0];
    work->side[1].player[0]->linkMdlId = work->side[1].body.pumMdlId[0];
    work->side[1].player[1]->linkMdlId = work->side[1].body.pumMdlId[1];
    work->side[1].player[2]->linkMdlId = work->side[1].body.pumMdlId[2];
    work->side[0].unk1AE = 0;
    work->side[1].unk1AE = 0;
    work->side[0].unk1B2 = 20;
    work->side[1].unk1B2 = 30;

    if (work->mdl[work->side[0].player[0]->charNo + 30] < 0) {
        modelId = work->mdl[work->side[0].player[0]->charNo + 30] = Hu3DModelCreateData(lbl_1_data_12C[work->side[0].player[0]->charNo + 30]);
    } else {
        modelId = Hu3DModelLink(work->mdl[work->side[0].player[0]->charNo + 30]);
    }
    work->side[0].ui.mdlA[0] = modelId;
    Hu3DModelAttrSet(modelId, 1);
    Hu3DModelAttrSet(modelId, 0x40000002);
    Hu3DModelLayerSet(modelId, 6);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(modelId, 1);
    for (i = 0; i < 3; i++) {
        if (work->mdl[work->side[1].player[i]->charNo + 43] < 0) {
            modelId = work->mdl[work->side[1].player[i]->charNo + 43] = Hu3DModelCreateData(lbl_1_data_12C[work->side[1].player[i]->charNo + 43]);
        } else {
            modelId = Hu3DModelLink(work->mdl[work->side[1].player[i]->charNo + 43]);
        }
        work->side[1].ui.mdlA[i] = modelId;
        Hu3DModelAttrSet(modelId, 1);
        Hu3DModelAttrSet(modelId, 0x40000002);
        Hu3DModelLayerSet(modelId, 6);
        Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrReset(modelId, 1);
    }
}

/* asm 7177-7650, 436 insns. */
void fn_1_69B4(M567_BODY *body, s32 side)
{
    M567_WORK *work = (M567_WORK *)lbl_1_bss_4->data;
    HU3DMODELID modelId;
    HU3DMOTID motId;
    s32 n;
    s32 count;
    s32 i;

    if (side == 0) {
        if (work->mdl[18] < 0) {
            modelId = work->mdl[18] = Hu3DModelCreateData(lbl_1_data_12C[18]);
        } else {
            modelId = Hu3DModelLink(work->mdl[18]);
        }
        if (work->mdl2[1] < 0) {
            motId = work->mdl2[1] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(lbl_1_data_230[1], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            motId = work->mdl2[1];
        }
        body->motNo = motId;
        Hu3DMotionSet(modelId, motId);
        if (work->mdl2[2] < 0) {
            motId = work->mdl2[2] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(lbl_1_data_230[2], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            motId = work->mdl2[2];
        }
        body->motId = motId;
        if (work->mdl2[3] < 0) {
            motId = work->mdl2[3] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(lbl_1_data_230[3], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            motId = work->mdl2[3];
        }
        body->unk36 = motId;
        if (work->mdl2[4] < 0) {
            motId = work->mdl2[4] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(lbl_1_data_230[4], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            motId = work->mdl2[4];
        }
        body->unk38 = motId;
    } else {
        if (work->mdl[19] < 0) {
            modelId = work->mdl[19] = Hu3DModelCreateData(lbl_1_data_12C[19]);
        } else {
            modelId = Hu3DModelLink(work->mdl[19]);
        }
        if (work->mdl2[5] < 0) {
            motId = work->mdl2[5] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(lbl_1_data_230[5], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            motId = work->mdl2[5];
        }
        body->motNo = motId;
        Hu3DMotionSet(modelId, motId);
        if (work->mdl2[6] < 0) {
            motId = work->mdl2[6] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(lbl_1_data_230[6], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            motId = work->mdl2[6];
        }
        body->motId = motId;
        if (work->mdl2[7] < 0) {
            motId = work->mdl2[7] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(lbl_1_data_230[7], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            motId = work->mdl2[7];
        }
        body->unk36 = motId;
        if (work->mdl2[8] < 0) {
            motId = work->mdl2[8] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(lbl_1_data_230[8], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            motId = work->mdl2[8];
        }
        body->unk38 = motId;
    }
    body->mdlId = modelId;
    Hu3DModelAttrSet(modelId, 1);
    Hu3DModelAttrSet(modelId, 0x40000001);
    Hu3DModelLayerSet(modelId, 2);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(modelId, 1);

    if (side != 0) {
        n = 3;
    } else {
        n = 1;
    }
    count = n;
    for (i = 0; i < count; i++) {
        if (work->mdl[56] < 0) {
            modelId = work->mdl[56] = Hu3DModelCreateData(lbl_1_data_12C[56]);
        } else {
            modelId = Hu3DModelLink(work->mdl[56]);
        }
        body->miniMdlId[i] = modelId;
        Hu3DModelAttrSet(modelId, 1);
        Hu3DModelAttrSet(modelId, 0x40000002);
        Hu3DModelLayerSet(modelId, 2);
        Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrReset(modelId, 1);

        if (side != 0) {
            if (work->mdl[62] < 0) {
                modelId = work->mdl[62] = Hu3DModelCreateData(lbl_1_data_12C[62]);
            } else {
                modelId = Hu3DModelLink(work->mdl[62]);
            }
        } else {
            if (work->mdl[61] < 0) {
                modelId = work->mdl[61] = Hu3DModelCreateData(lbl_1_data_12C[61]);
            } else {
                modelId = Hu3DModelLink(work->mdl[61]);
            }
        }
        body->pumMdlId[i] = modelId;
        if (work->mdl2[0] < 0) {
            motId = work->mdl2[0] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(lbl_1_data_230[0], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            motId = work->mdl2[0];
        }
        Hu3DMotionSet(modelId, motId);
        Hu3DModelAttrSet(modelId, 1);
        Hu3DModelAttrSet(modelId, 0x40000002);
        Hu3DModelLayerSet(modelId, 2);
        Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrReset(modelId, 1);
    }

    if (work->mdl[28] < 0) {
        modelId = work->mdl[28] = Hu3DModelCreateData(lbl_1_data_12C[28]);
    } else {
        modelId = Hu3DModelLink(work->mdl[28]);
    }
    body->unk46 = modelId;
    Hu3DModelAttrSet(modelId, 1);
    Hu3DModelAttrSet(modelId, 0x40000002);
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
}

/* asm 7653-8557, 844 insns. Per-side update; 11-case switch (.data:0x514). */
s32 fn_1_7084(M567_SIDE *side)
{
    s32 result = 0;
    s16 panTbl[3] = { 0x20, 0x40, 0x60 };
    M567_WORK *work = (M567_WORK *)lbl_1_bss_4->data;
    s32 n1;
    s32 n2;
    s32 n3;
    s32 n4;
    s32 count;
    s32 i;
    float t;
    M567_NODE *node;
    M567_NODE *node2;
    M567_NODE *node3;

    if (work->unkCF6 != 0) {
        if (side->unk1A4 != 0) {
            side->cam->target.x = 0.5f * side->body.pos.x;
            side->cam->target.z = 250.0f + side->body.pos.z;
        } else {
            side->cam->target.x = 0.5f * side->body.pos.x;
            side->cam->target.z = side->body.pos.z - 250.0f;
        }
    }

    switch (side->unk1AE) {
    case 0:
        break;

    case 1:
        side->unk1B0 = 0;
        if (side->unk1A4 != 0) {
            n1 = 3;
        } else {
            n1 = 1;
        }
        count = n1;
        for (i = 0; i < count; i++) {
            side->player[i]->elem->unk4 = 10;
            side->player[i]->unk3C = 0;
        }
        if (work->unkCF4 != 0) {
            if (side->unk1A4 == 0) {
                if (lbl_1_data_434[0] < 0) {
                    lbl_1_data_434[0] = HuAudFXPlayPan(0x8F1, 0x30);
                }
            } else {
                if (lbl_1_data_434[1] < 0) {
                    lbl_1_data_434[1] = HuAudFXPlayPan(0x8F2, 0x50);
                }
            }
        }
        side->ui.mode = 2;
        fn_1_959C(side->grid, side->unk1A6, side->unk1A8);
        side->unk1AE++;
        /* fall through */
    case 2:
        if (side->unk1A4 != 0) {
            n2 = 3;
        } else {
            n2 = 1;
        }
        count = n2;
        for (i = 0; i < count; i++) {
            if (side->player[i]->elem->unk4 != 60) {
                break;
            }
        }
        if (i == count) {
            if (side->unk1A4 == 0) {
                if (lbl_1_data_434[0] >= 0) {
                    HuAudFXStop(lbl_1_data_434[0]);
                    lbl_1_data_434[0] = -1;
                }
            } else {
                if (lbl_1_data_434[1] >= 0) {
                    HuAudFXStop(lbl_1_data_434[1]);
                    lbl_1_data_434[1] = -1;
                }
            }
            side->unk1AE++;
            side->ui.unkD0 = 0;
        }
        break;

    case 3:
        side->unk1AA = side->unk1A6 + side->player[side->ui.unkD0]->elem->unkC;
        side->unk1AC = side->unk1A8 + side->player[side->ui.unkD0]->elem->unkA;
        if (side->grid[side->unk1AA][side->unk1AC] != 0 && side->grid[side->unk1AA][side->unk1AC] != 2) {
            side->unk1AA = side->unk1A6;
            side->unk1AC = side->unk1A8;
            if (side->unk1A4 == 0) {
                omVibrate(side->player[0]->no, 25, 4, 2);
            } else {
                omVibrate(side->player[0]->no, 25, 4, 2);
                omVibrate(side->player[1]->no, 25, 4, 2);
                omVibrate(side->player[2]->no, 25, 4, 2);
            }
            i = side->ui.unkD0;
            Hu3DModelAttrReset(side->ui.mdlB[i], 1);
            Hu3DModelPosSetV(side->ui.mdlB[i], &side->ui.objPos[i]);
            Hu3DModelRotSetV(side->ui.mdlB[i], &side->ui.rot);
            if (side->unk1A4 == 0) {
                HuAudFXPlayPan(0x8F9, 0x30);
            } else {
                HuAudFXPlayPan(0x8FA, 0x50);
            }
        }
        if (side->unk1A4 == 0) {
            side->body.unk18 = 300.0f * side->unk1A8 - 600.0f;
            side->body.unk20 = 2700.0f + 300.0f * -side->unk1A6;
            side->body.unk24 = 300.0f * side->unk1AC - 600.0f;
            side->body.unk2C = 2700.0f + 300.0f * -side->unk1AA;
            HuAudFXPlayPan(0x8F5, panTbl[side->unk1AC - 1]);
        } else {
            side->body.unk18 = 600.0f + 300.0f * -side->unk1A8;
            side->body.unk20 = 300.0f * side->unk1A6 - 2700.0f;
            side->body.unk24 = 600.0 + 300.0 * -side->unk1AC;
            side->body.unk2C = 300.0f * side->unk1AA - 2700.0f;
            HuAudFXPlayPan(0x8F7, panTbl[side->unk1AC - 1]);
        }
        if (side->unk1AA == 9) {
            result = 1;
        }
        side->unk1AE++;
        side->unk1B0 = 0;
        Hu3DMotionShiftSet(side->body.mdlId, side->body.motId, 0.0f, 5.0f, 0);
        node = work->list.free;
        if (node) {
            work->list.free = node->next;
            node->func = fn_1_979C;
            node->data = &side->body;
            node->next = work->list.head;
            if (node->next) {
                node->next->prev = node;
            }
            work->list.head = node;
        }
        break;

    case 4:
        side->unk1B0++;
        if (side->unk1B0 == side->unk1B2) {
            side->unk1A6 = side->unk1AA;
            side->unk1A8 = side->unk1AC;
            if (work->unkCF4 != 0) {
                side->unk1AE++;
            } else {
                side->unk1AE = 7;
            }
            Hu3DModelAttrSet(side->ui.mdlB[side->ui.unkD0], 1);
        }
        if (side->unk1A4 != 0) {
            if (side->unk1B0 < 17) {
                t = 0.0f;
            } else if (side->unk1B0 < 28) {
                t = (side->unk1B0 - 16.0f) / 11.0f;
            } else {
                t = 1.0f;
            }
            if (side->unk1B0 == 28) {
                node2 = work->list.free;
                if (node2) {
                    work->list.free = node2->next;
                    node2->func = fn_1_988C;
                    node2->data = &side->body;
                    node2->next = work->list.head;
                    if (node2->next) {
                        node2->next->prev = node2;
                    }
                    work->list.head = node2;
                }
                Hu3DModelAttrReset(side->body.unk46, 1);
                Hu3DModelAttrReset(side->body.unk46, 0x40000002);
                Hu3DMotionTimeSet(side->body.unk46, 0.0f);
                Hu3DModelPosSetV(side->body.unk46, &side->body.pos);
                HuAudFXPlayPan(0x8F8, panTbl[side->unk1AC - 1]);
            }
            if (side->unk1AA == 9 && side->unk1B0 == 22) {
                Hu3DModelAttrReset(work->mdl[25], 0x40000002);
                Hu3DModelAttrReset(work->mdl[26], 0x40000002);
            }
        } else {
            if (side->unk1B0 < 11) {
                t = 0.0f;
            } else if (side->unk1B0 < 19) {
                t = side->unk1B0 - 10.0f;
                t *= 0.125f;
            } else {
                t = 1.0f;
            }
            if (side->unk1B0 == 19) {
                node3 = work->list.free;
                if (node3) {
                    work->list.free = node3->next;
                    node3->func = fn_1_988C;
                    node3->data = &side->body;
                    node3->next = work->list.head;
                    if (node3->next) {
                        node3->next->prev = node3;
                    }
                    work->list.head = node3;
                }
                Hu3DModelAttrReset(side->body.unk46, 1);
                Hu3DModelAttrReset(side->body.unk46, 0x40000002);
                Hu3DMotionTimeSet(side->body.unk46, 0.0f);
                Hu3DModelPosSetV(side->body.unk46, &side->body.pos);
                HuAudFXPlayPan(0x8F6, panTbl[side->unk1AC - 1]);
            }
            if (side->unk1AA == 9 && side->unk1B0 == 15) {
                Hu3DModelAttrReset(work->mdl[25], 0x40000002);
                Hu3DModelAttrReset(work->mdl[26], 0x40000002);
            }
        }
        side->body.pos.x = side->body.unk18 * (1.0f - t) + side->body.unk24 * t;
        side->body.pos.z = side->body.unk20 * (1.0f - t) + side->body.unk2C * t;
        Hu3DModelPosSetV(side->body.mdlId, &side->body.pos);
        break;

    case 5:
        side->player[side->ui.unkD0]->elem->unk4 = 70;
        side->unk1AE++;
        /* fall through */
    case 6:
        if (side->player[side->ui.unkD0]->elem->unk4 == 1) {
            side->ui.unkD0++;
            if (side->unk1A4 != 0) {
                n3 = 3;
            } else {
                n3 = 1;
            }
            count = n3;
            if (side->ui.unkD0 == count) {
                side->unk1AE = 1;
            } else {
                side->unk1AE = 9;
            }
        }
        break;

    case 7:
        if (side->unk1A4 != 0) {
            n4 = 3;
        } else {
            n4 = 1;
        }
        count = n4;
        for (i = 0; i < count; i++) {
            side->player[i]->elem->unk4 = 70;
        }
        Hu3DMotionShiftSet(side->body.mdlId, side->body.motNo, 0.0f, 5.0f, 0x40000001);
        if (side->unk1A4 == 0) {
            if (lbl_1_data_434[0] >= 0) {
                HuAudFXStop(lbl_1_data_434[0]);
                lbl_1_data_434[0] = -1;
            }
        } else {
            if (lbl_1_data_434[1] >= 0) {
                HuAudFXStop(lbl_1_data_434[1]);
                lbl_1_data_434[1] = -1;
            }
        }
        side->unk1AE++;
        break;

    case 8:
        break;

    case 9:
        side->unk1B0 = 0;
        side->unk1AE++;
        /* fall through */
    case 10:
        side->unk1B0++;
        if (side->unk1B0 == 30) {
            side->unk1AE = 3;
        }
        break;
    }
    return result;
}

/* asm 8560-8930, 351 insns. */
void fn_1_7DB4(M567_UI *ui, M567_CAM *cam, s16 type)
{
    M567_WORK *work = (M567_WORK *)lbl_1_bss_4->data;
    HU3DMODELID modelId;
    s32 n;
    s32 count;
    s32 i;

    ui->cam = cam;
    ui->type = type;
    if (type == 0) {
        if (work->mdl[20] < 0) {
            modelId = work->mdl[20] = Hu3DModelCreateData(lbl_1_data_12C[20]);
        } else {
            modelId = Hu3DModelLink(work->mdl[20]);
        }
    } else {
        if (work->mdl[21] < 0) {
            modelId = work->mdl[21] = Hu3DModelCreateData(lbl_1_data_12C[21]);
        } else {
            modelId = Hu3DModelLink(work->mdl[21]);
        }
    }
    ui->mdlId = modelId;
    Hu3DModelAttrSet(modelId, 1);
    Hu3DModelAttrSet(modelId, 0x40000002);
    Hu3DModelLayerSet(modelId, 6);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, ui->cam->bit);
    Hu3DModelAttrReset(modelId, 1);

    if (type == 0) {
        ui->color[0].ptr = &Hu3DData[modelId].hsf->material[3];
        ui->color[1].ptr = &Hu3DData[modelId].hsf->material[4];
    } else {
        ui->color[0].ptr = &Hu3DData[modelId].hsf->material[6];
        ui->color[1].ptr = &Hu3DData[modelId].hsf->material[5];
        ui->color[2].ptr = &Hu3DData[modelId].hsf->material[7];
    }

    if (type == 0) {
        n = 1;
    } else {
        n = 3;
    }
    count = n;
    for (i = 0; i < count; i++) {
        if (work->mdl[24] < 0) {
            modelId = work->mdl[24] = Hu3DModelCreateData(lbl_1_data_12C[24]);
        } else {
            modelId = Hu3DModelLink(work->mdl[24]);
        }
        ui->mdlB[i] = modelId;
        Hu3DModelAttrSet(modelId, 1);
        Hu3DModelAttrSet(modelId, 0x40000001);
        Hu3DModelLayerSet(modelId, 6);
        Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(modelId, ui->cam->bit);

        if (type == 0) {
            if (work->mdl[57] < 0) {
                modelId = work->mdl[57] = Hu3DModelCreateData(lbl_1_data_12C[57]);
            } else {
                modelId = Hu3DModelLink(work->mdl[57]);
            }
        } else {
            if (work->mdl[i + 58] < 0) {
                modelId = work->mdl[i + 58] = Hu3DModelCreateData(lbl_1_data_12C[i + 58]);
            } else {
                modelId = Hu3DModelLink(work->mdl[i + 58]);
            }
        }
        ui->mdlC[i] = modelId;
        Hu3DModelAttrSet(modelId, 1);
        Hu3DModelAttrSet(modelId, 0x40000002);
        Hu3DModelLayerSet(modelId, 6);
        Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(modelId, ui->cam->bit);
        Hu3DModelAttrReset(modelId, 1);
        fn_1_8794(&ui->elem[i], type);
    }

    if (type == 0) {
        Hu3DModelHookSet(ui->mdlId, "slot04-1pa", ui->elem[0].unk8);
    } else {
        Hu3DModelHookSet(ui->mdlId, "m567-3pa", ui->elem[0].unk8);
        Hu3DModelHookSet(ui->mdlId, "m567-3pb", ui->elem[1].unk8);
        Hu3DModelHookSet(ui->mdlId, "m567-3pc", ui->elem[2].unk8);
    }
    ui->pos2d.x = 288.0f;
    ui->pos2d.y = 500.0f;
    ui->pos2d.z = 494.0f;
    ui->mode = 0;
    ui->unkBA = 0;
}

/* asm 8933-9245, 281 insns. */
void fn_1_8330(M567_UI *ui, HuVecF *pos)
{
    M567_WORK *work = (M567_WORK *)lbl_1_bss_4->data;
    M567_CAM *cam = ui->cam;
    HuVecF pos3d;
    s32 n;
    s32 count;
    s32 i;
    M567_NODE *node;
    M567_NODE *node2;
    M567_NODE *node3;
    M567_NODE *node4;
    M567_NODE *node5;

    Hu3D2Dto3D(&ui->pos2d, cam->bit, &pos3d);
    ui->rot.x = -cam->angleY;
    ui->rot.y = 90.0f - cam->angleX;
    ui->rot.z = 0.0f;
    Hu3DModelPosSetV(ui->mdlId, &pos3d);
    Hu3DModelRotSetV(ui->mdlId, &ui->rot);
    if (ui->type != 0) {
        Hu3DModelObjPosGet(ui->mdlId, "m567-3pa", &ui->objPos[0]);
        Hu3DModelObjPosGet(ui->mdlId, "m567-3pb", &ui->objPos[1]);
        Hu3DModelObjPosGet(ui->mdlId, "m567-3pc", &ui->objPos[2]);
    } else {
        Hu3DModelObjPosGet(ui->mdlId, "slot04-1pa", &ui->objPos[0]);
    }

    if (ui->type != 0) {
        n = 3;
    } else {
        n = 1;
    }
    count = n;
    for (i = 0; i < count; i++) {
        fn_1_89F4(&ui->elem[i]);
    }
    if (ui->unkBA == 0) {
        for (i = 0; i < count; i++) {
            Hu3DModelPosSetV(ui->mdlA[i], &ui->objPos[i]);
            Hu3DModelRotSetV(ui->mdlA[i], &ui->rot);
            Hu3DModelPosSetV(ui->mdlC[i], &ui->objPos[i]);
            Hu3DModelRotSetV(ui->mdlC[i], &ui->rot);
        }
    }

    if (ui->type == 0) {
        switch (ui->mode) {
        case 0:
            ui->unkD2 = 0;
            ui->mode++;
            break;
        case 2:
            node = work->list.free;
            if (node) {
                work->list.free = node->next;
                node->func = fn_1_98F0;
                node->data = &ui->color[0];
                node->next = work->list.head;
                if (node->next) {
                    node->next->prev = node;
                }
                work->list.head = node;
            }
            ui->color[0].time = 0;
            ui->mode++;
            /* fall through */
        case 3:
            ui->unkD2++;
            if (ui->unkD2 == 15) {
                node2 = work->list.free;
                if (node2) {
                    work->list.free = node2->next;
                    node2->func = fn_1_98F0;
                    node2->data = &ui->color[1];
                    node2->next = work->list.head;
                    if (node2->next) {
                        node2->next->prev = node2;
                    }
                    work->list.head = node2;
                }
                ui->color[1].time = 0;
                ui->mode = 0;
            }
            break;
        }
    } else {
        switch (ui->mode) {
        case 0:
            ui->unkD2 = 0;
            ui->mode++;
            break;
        case 2:
            node3 = work->list.free;
            if (node3) {
                work->list.free = node3->next;
                node3->func = fn_1_98F0;
                node3->data = &ui->color[0];
                node3->next = work->list.head;
                if (node3->next) {
                    node3->next->prev = node3;
                }
                work->list.head = node3;
            }
            ui->color[0].time = 0;
            ui->mode++;
            /* fall through */
        case 3:
            ui->unkD2++;
            if (ui->unkD2 == 5) {
                node4 = work->list.free;
                if (node4) {
                    work->list.free = node4->next;
                    node4->func = fn_1_98F0;
                    node4->data = &ui->color[1];
                    node4->next = work->list.head;
                    if (node4->next) {
                        node4->next->prev = node4;
                    }
                    work->list.head = node4;
                }
                ui->color[1].time = 0;
                ui->mode++;
            }
            break;
        case 4:
            ui->unkD2++;
            if (ui->unkD2 == 10) {
                node5 = work->list.free;
                if (node5) {
                    work->list.free = node5->next;
                    node5->func = fn_1_98F0;
                    node5->data = &ui->color[2];
                    node5->next = work->list.head;
                    if (node5->next) {
                        node5->next->prev = node5;
                    }
                    work->list.head = node5;
                }
                ui->color[2].time = 0;
                ui->mode = 0;
            }
            break;
        }
    }
}

/* asm 9248-9405, 152 insns. */
void fn_1_8794(M567_ELEM *elem, s32 type)
{
    M567_WORK *work = (M567_WORK *)lbl_1_bss_4->data;
    HU3DMODELID modelId;

    if (work->mdl[22] < 0) {
        modelId = work->mdl[22] = Hu3DModelCreateData(lbl_1_data_12C[22]);
    } else {
        modelId = Hu3DModelLink(work->mdl[22]);
    }
    elem->unk8 = modelId;
    Hu3DModelAttrSet(modelId, 1);
    Hu3DModelAttrSet(modelId, 0x40000001);
    Hu3DModelAttrSet(modelId, 0x40000002);
    Hu3DModelLayerSet(modelId, 6);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(modelId, 1);

    if (work->mdl[27] < 0) {
        modelId = work->mdl[27] = Hu3DModelCreateData(lbl_1_data_12C[27]);
    } else {
        modelId = Hu3DModelLink(work->mdl[27]);
    }
    elem->unkE = modelId;
    Hu3DModelAttrSet(modelId, 1);
    Hu3DModelLayerSet(modelId, 6);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);

    elem->unk4 = 0;
    elem->unk6 = 0;
    elem->ptr = Hu3DData[elem->unk8].hsf->material;
    elem->ptr->color[0] = 0x7F;
    elem->ptr->color[1] = 0x7F;
    elem->ptr->color[2] = 0x7F;
    elem->mode = 0;
    elem->unk14 = 0;
    elem->unk16 = 60;
    elem->unk1C = 20;
    elem->type = type;
}

/* asm 9408-9676, 251 insns. 82-case switch (.data:0x568). */
void fn_1_89F4(M567_ELEM *elem)
{
    s32 seTbl[2] = { 0x8F3, 0x8F4 };
    s16 panTbl[2] = { 0x30, 0x50 };
    s32 level;
    float t;

    switch (elem->unk4) {
    case 0:
        elem->mode = 0;
        elem->unk4++;
        break;

    case 10:
        elem->ptr->color[0] = 0x7F;
        elem->ptr->color[1] = 0x7F;
        elem->ptr->color[2] = 0x7F;
        elem->unk6 = 0;
        elem->unk4++;
        /* fall through */
    case 11:
        elem->unk6++;
        if (elem->unk6 == 5) {
            elem->unk4++;
        }
        break;

    case 12:
        elem->mode = 1;
        elem->unk6 = 0;
        elem->unk4++;
        /* fall through */
    case 13:
        elem->unk6++;
        if (elem->unk6 == 25) {
            elem->unk4++;
        }
        break;

    case 14:
        elem->ptr->color[0] = 0xFF;
        elem->ptr->color[1] = 0xFF;
        elem->ptr->color[2] = 0xFF;
        elem->unk4++;
        break;

    case 20:
        if (elem->unk14 < elem->unk1C) {
            elem->unk1A = elem->unk1C;
            elem->unk4 = 30;
            elem->unkA = 1;
            elem->unkC = 0;
        } else if (elem->unk14 < elem->unk1C * 2) {
            elem->unk1A = elem->unk1C * 2;
            elem->unk4 = 40;
            elem->unkA = -1;
            elem->unkC = 0;
        } else {
            elem->unk1A = elem->unk1C * 2;
            elem->unk4 = 50;
            elem->unkA = 0;
            elem->unkC = 1;
        }
        break;

    case 30:
    case 40:
        if (elem->unk14 >= elem->unk1A) {
            elem->unk14 = elem->unk1A;
            elem->mode = 0;
            elem->unk4 = 60;
            HuAudFXPlayPan(seTbl[elem->type], panTbl[elem->type]);
        }
        break;

    case 50:
        if (elem->unk14 < elem->unk1A) {
            elem->unk14 = 0;
            elem->mode = 0;
            elem->unk4 = 60;
            HuAudFXPlayPan(seTbl[elem->type], panTbl[elem->type]);
        }
        break;

    case 60:
        break;

    case 70:
        elem->unk6 = 0;
        elem->unk4++;
        /* fall through */
    case 71:
        elem->unk6++;
        if (elem->unk6 == 5) {
            elem->unk4 = 0;
        }
        t = 1.0f - elem->unk6 / 5.0f;
        level = 128.0f * t;
        elem->ptr->color[0] = level + 0x7F;
        elem->ptr->color[1] = level + 0x7F;
        elem->ptr->color[2] = level + 0x7F;
        break;

    case 80:
        elem->ptr->color[0] = 0x7F;
        elem->ptr->color[1] = 0x7F;
        elem->ptr->color[2] = 0x7F;
        elem->unk4++;
        break;

    case 81:
        break;
    }

    fn_1_8DE0(elem);
    t = Hu3DMotionTimeGet(elem->unk8);
    Hu3DMotionTimeSet(elem->unk10, t);
}

/* asm 9679-9740, 58 insns. */
void fn_1_8DE0(M567_ELEM *elem)
{
    float time;

    switch (elem->mode) {
    case 0:
        break;
    case 1:
        elem->unk14++;
        elem->unk14 = elem->unk14 % elem->unk16;
        break;
    }
    time = 60.0f * elem->unk14 / elem->unk16;
    Hu3DMotionTimeSet(elem->unk8, time);
}

/* asm 9743-9766, 21 insns. Human input. */
void fn_1_8EC8(M567_PLAYER *player)
{
    if (HuPadBtnDown[player->padNo] & PAD_BUTTON_A) {
        fn_1_92B0(player);
    }
}

/* asm 9769-10011, 229 insns. COM input. */
void fn_1_8F1C(M567_PLAYER *player)
{
    s32 waitRand[2][4] = { { 50, 30, 20, 10 }, { 60, 40, 25, 15 } };
    s32 waitBase[2][4] = { { 30, 30, 20, 10 }, { 30, 40, 25, 15 } };
    s32 hitRate[4][4] = {
        { 45, 65, 75, 85 },
        { 45, 65, 75, 85 },
        { 45, 60, 75, 80 },
        { 45, 55, 75, 75 },
    };
    s32 row;

    switch (player->unk3C) {
    case 0:
        player->unk40 = waitBase[player->grp][player->dif] + frandmod(waitRand[player->grp][player->dif]);
        player->unk3E = 0;
        player->unk3C++;
        /* fall through */
    case 1:
        player->unk3E++;
        if (player->unk3E == player->unk40) {
            player->unk3C++;
        }
        break;

    case 2:
        row = player->grp + player->slot;
        if ((s32)frandmod(100) < hitRate[row][player->dif]) {
            player->unk42 = player->side->result[player->slot];
        } else {
            player->unk42 = (player->side->result[player->slot] + ((s32)frandmod(2) + 1)) % 3;
        }
        player->unk3C++;
        break;

    case 3:
        switch (player->unk42) {
        case 0:
            if (player->elem->unk14 > player->elem->unk1C * 2) {
                fn_1_92B0(player);
                player->unk3C++;
            }
            break;
        case 1:
            if (player->elem->unk14 <= player->elem->unk1C && player->elem->unk14 > 0) {
                fn_1_92B0(player);
                player->unk3C++;
            }
            break;
        case 2:
            if (player->elem->unk14 <= player->elem->unk1C * 2 && player->elem->unk14 > player->elem->unk1C) {
                fn_1_92B0(player);
                player->unk3C++;
            }
            break;
        }
        break;
    }
}

/* asm 10014-10135, 112 insns. */
void fn_1_92B0(M567_PLAYER *player)
{
    M567_WORK *work = (M567_WORK *)lbl_1_bss_4->data;
    M567_ELEM *elem = player->elem;
    M567_UI *ui = &player->side->ui;
    s32 slot = player->slot;
    M567_NODE *node;
    M567_NODE *node2;

    node = work->list.free;
    if (node) {
        work->list.free = node->next;
        node->func = fn_1_9828;
        node->data = elem;
        node->next = work->list.head;
        if (node->next) {
            node->next->prev = node;
        }
        work->list.head = node;
    }
    if (node) {
        Hu3DModelPosSet(elem->unkE, ui->objPos[slot].x, ui->objPos[slot].y, ui->objPos[slot].z - 2.0f);
        Hu3DModelRotSetV(elem->unkE, &ui->rot);
        Hu3DModelAttrReset(elem->unkE, 1);
        Hu3DModelAttrReset(elem->unkE, 0x40000002);
        Hu3DMotionTimeSet(elem->unkE, 0.0f);
    }

    node2 = work->list.free;
    if (node2) {
        work->list.free = node2->next;
        node2->func = fn_1_9470;
        node2->data = player;
        node2->next = work->list.head;
        if (node2->next) {
            node2->next->prev = node2;
        }
        work->list.head = node2;
    }
    if (node2) {
        player->mode = 0;
    }

    if (player->grp == 0) {
        ui->color[0].time++;
        ui->color[1].time++;
    } else {
        ui->color[slot].time++;
    }
    omVibrate(player->no, 12, 6, 6);
    elem->unk4 = 20;
}

/* asm 10138-10219, 75 insns. Task: data is M567_PLAYER *. */
BOOL fn_1_9470(M567_NODE *node)
{
    BOOL result = FALSE;
    M567_PLAYER *player = (M567_PLAYER *)node->data;

    switch (player->mode) {
    case 0:
        CharModelAttrReset(player->charNo, 0x40000002);
        Hu3DModelAttrReset(player->linkMdlId, 0x40000002);
        player->mode++;
        /* fall through */
    case 1:
        if (CharMotionEndCheck(player->charNo)) {
            CharModelAttrSet(player->charNo, 0x40000004);
            Hu3DModelAttrSet(player->linkMdlId, 0x40000004);
            player->mode++;
        }
        break;
    case 2:
        if (CharMotionEndCheck(player->charNo)) {
            CharModelAttrReset(player->charNo, 0x40000004);
            Hu3DModelAttrReset(player->linkMdlId, 0x40000004);
            CharModelAttrSet(player->charNo, 0x40000002);
            Hu3DModelAttrSet(player->linkMdlId, 0x40000002);
            result = TRUE;
        }
        break;
    }
    return result;
}

/* asm 10222-10292, 62 insns. */
void fn_1_959C(s16 (*grid)[5], s16 row, s16 col)
{
    s32 i;
    s32 dir;
    s32 mark;

    for (i = 0; i < 3; i++) {
        if (grid[row + 1][col] == 0 || grid[row + 1][col] == 2) {
            grid[11][i] = 0;
            if (row < 8) {
                row++;
            }
        } else {
            dir = fn_1_9694(grid, row, col);
            if (dir < 0) {
                mark = 2;
            } else {
                mark = 1;
            }
            grid[11][i] = mark;
            col += dir;
        }
    }
}

/* asm 10295-10371, 66 insns. */
s32 fn_1_9694(s16 (*grid)[5], s16 row, s16 col)
{
    s32 right = col + 1;
    s32 left = col - 1;
    s32 r;
    s32 dir;

    if (grid[row][left] == -1) {
        return 1;
    }
    if (grid[row][right] == -1) {
        return -1;
    }
    for (r = row + 1; r < 9; r++) {
        if (grid[r][left] == -1) {
            return 1;
        }
        if (grid[r][right] == -1) {
            return -1;
        }
    }
    if ((s32)frandmod(2) != 0) {
        dir = 1;
    } else {
        dir = -1;
    }
    return dir;
}

/* asm 10374-10411, 35 insns. Task: data is M567_BODY *. */
BOOL fn_1_979C(M567_NODE *node)
{
    BOOL result = FALSE;
    M567_BODY *body = (M567_BODY *)node->data;

    if (Hu3DMotionIDGet(body->mdlId) == body->motId && Hu3DMotionEndCheck(body->mdlId)) {
        Hu3DMotionSet(body->mdlId, body->motNo);
        Hu3DModelAttrSet(body->mdlId, 0x40000001);
        result = TRUE;
    }
    return result;
}

/* asm 10414-10441, 25 insns. Task: data is M567_ELEM *. */
BOOL fn_1_9828(M567_NODE *node)
{
    BOOL result = FALSE;
    M567_ELEM *elem = (M567_ELEM *)node->data;

    if (Hu3DMotionEndCheck(elem->unkE)) {
        Hu3DModelAttrSet(elem->unkE, 1);
        result = TRUE;
    }
    return result;
}

/* asm 10444-10471, 25 insns. Task: data is M567_BODY *. */
BOOL fn_1_988C(M567_NODE *node)
{
    BOOL result = FALSE;
    M567_BODY *body = (M567_BODY *)node->data;

    if (Hu3DMotionEndCheck(body->unk46)) {
        Hu3DModelAttrSet(body->unk46, 1);
        result = TRUE;
    }
    return result;
}

/* asm 10474-10656, 175 insns. Task: data is M567_COLOR *. */
BOOL fn_1_98F0(M567_NODE *node)
{
    BOOL result = FALSE;
    M567_COLOR *color = (M567_COLOR *)node->data;
    float t;
    float s;
    u8 r;
    u8 g;

    switch (color->time) {
    case 0:
        color->mode = 0;
        color->time++;
        /* fall through */
    case 1:
        color->mode++;
        color->mode = color->mode % 30;
        t = color->mode / 30.0f;
        s = HuSin(180.0f * t);
        r = 150.0f + 94.0f * s;
        g = 100.0f + 100.0f * s;
        color->ptr->color[0] = r;
        color->ptr->color[1] = g;
        color->ptr->color[2] = 0;
        break;
    case 2:
        color->mode++;
        if (color->mode == 30) {
            result = TRUE;
        }
        t = color->mode / 30.0f;
        s = HuSin(180.0f * t);
        r = 150.0f + 94.0f * s;
        g = 100.0f + 100.0f * s;
        color->ptr->color[0] = r;
        color->ptr->color[1] = g;
        color->ptr->color[2] = 0;
        break;
    }
    return result;
}
