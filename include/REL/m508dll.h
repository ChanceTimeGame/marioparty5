#ifndef M508DLL_H
#define M508DLL_H

/*
 * m508dll (overlay #22): types and prototypes shared by its two translation
 * units (m508 object).
 *
 * Offsets are GameCube ones from build/mp5-asm/m508Dll. No upstream names exist,
 * so functions keep reference addresses and globals keep lbl_1_* labels.
 */

#include "dolphin/types.h"
#include "game/object.h"
#include "game/hu3d.h"
#include "humath.h"

#include "game/mg/seqman.h"
#include "game/mg/actman.h"

#include <stddef.h>
#include "game/animdata.h"
#include "game/charman.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/process.h"
#include "game/window.h"
#include "game/wipe.h"
#include "messdir_enum.h"

/* TODO: work structs. Name every field by hex offset (unk050, unk0B4). */

/* ===========================================================================
 * The shared object library (src/objlib.c).
 *
 * These declarations are games/mp5/src/REL/m540dll/m540.h's, renamed M540_ ->
 * M508_; m540dll's copy of this library is function-for-function m508Dll's, so
 * the layouts are the same ones its eight forks reconciled by hex offset.
 * ==========================================================================*/
typedef struct m508_obj M508_OBJ;
typedef void (*M508_OBJFUNC)(M508_OBJ *obj);

struct m508_obj {
    /* 0x000 */ HUPROCESS *unk000;
    /* 0x004 */ s32 unk004;
    /* 0x008 */ s32 unk008;
    /* 0x00C */ s32 unk00C;
    /* 0x010 */ M508_OBJFUNC *unk010;
    /* 0x014 */ s32 unk014;
    /* 0x018 */ u8 unk018[0x140];
    /* 0x158 */ s32 unk158;
    /* 0x15C */ s32 unk15C;
    /* 0x160 */ HuVecF unk160;
    /* 0x16C */ HuVecF unk16C;
    /* 0x178 */ HuVecF unk178;
    /* 0x184 */ s16 unk184;
    /* 0x186 */ s16 unk186;
    /* 0x188 */ s32 unk188;
    /* 0x18C */ s32 unk18C;
    /* 0x190 */ s16 *unk190;
    /* 0x194 */ u8 unk194[0x1C];
    /* 0x1B0 */ f32 unk1B0;
    /* 0x1B4 */ f32 unk1B4;
    /* 0x1B8 */ s32 unk1B8;
    /* 0x1BC */ s32 unk1BC;
    /* 0x1C0 */ s32 unk1C0;
    /* 0x1C4 */ s32 unk1C4;
    /* 0x1C8 */ s32 unk1C8;
};

/* Three allocation sizes, one layout: fn_1_7848 0x158 (header only), fn_1_7A3C
 * 0x1B8 (header + model), fn_1_8308 0x1CC (header + model + character).  Retail
 * spells those prefixes as literals; a host pointer is 8 bytes where the
 * console's is 4, and M508_OBJ has three pointer fields (unk000, unk010,
 * unk190), so the literal under-allocates on the host and every later write
 * walks into the next block's HuMem header.  offsetof names the same
 * boundaries; CodeWarrior keeps the literals, so the matching object is
 * unchanged.  See m540dll/NOTES.md, which diagnosed this from a corrupt
 * `MEM:ea549e20` heap total. */
#define M508_OBJ_SIZE 0x158
#define M508_MDLOBJ_SIZE 0x1B8
#define M508_CHROBJ_SIZE 0x1CC

/* The +0x18 work area of a model object (fn_1_7A3C family). */
typedef struct m508_mdlwork {
    /* 0x000 */ M508_OBJ *unk000;
    /* 0x004 */ s32 unk004;
    /* 0x008 */ s32 unk008;
    /* 0x00C */ s32 unk00C;
    /* 0x010 */ s32 unk010;
    /* 0x014 */ HuVecF unk014;
    /* 0x020 */ HuVecF unk020;
    /* 0x02C */ s32 unk02C;
    /* 0x030 */ f32 unk030;
    /* 0x034 */ HuVecF unk034[4];
    /* 0x064 */ s16 unk064[4];
    /* 0x06C */ s32 unk06C;
    /* 0x070 */ s32 unk070;
    /* 0x074 */ s32 unk074;
    /* 0x078 */ s32 unk078;
    /* 0x07C */ s32 unk07C;
    /* 0x080 */ s32 unk080;
    /* 0x084 */ s32 unk084;
    /* 0x088 */ s32 unk088;
    /* 0x08C */ s16 unk08C;
    /* 0x08E */ s16 unk08E;
    /* 0x090 */ s32 unk090;
    /* 0x094 */ s16 unk094;
    /* 0x096 */ s16 unk096;
} M508_MDLWORK;

/* The +0x18 work area of a character object (fn_1_8308 family). */
typedef struct m508_charwork {
    /* 0x000 */ HuVecF unk000;
    /* 0x00C */ s32 unk00C;
    /* 0x010 */ s32 unk010;
    /* 0x014 */ f32 unk014;
    /* 0x018 */ f32 unk018;
    /* 0x01C */ f32 unk01C;
    /* 0x020 */ M508_OBJ *unk020;
} M508_CHARWORK;

/* Function-like macros deliberately sharing the typedef names above: a
 * function-like macro only expands when followed by "(", so "M508_MDLWORK *w"
 * still names the type. */
#define M508_MDLWORK(o) ((M508_MDLWORK *)(o)->unk018)
#define M508_CHARWORK(o) ((M508_CHARWORK *)(o)->unk018)

#define M508_CUROBJ ((M508_OBJ *)HuPrcCurrentGet()->property)
#define M508_OBJCUR M508_CUROBJ

/* The camera: a 0x34-byte view record x3 inside a 0xB0 work. */
typedef struct m508_cameraview {
    /* 0x000 */ HuVecF unk000; /* eye */
    /* 0x00C */ HuVecF unk00C; /* up */
    /* 0x018 */ HuVecF unk018; /* center */
    /* 0x024 */ HuVecF unk024; /* rot, degrees */
    /* 0x030 */ f32 unk030;    /* zoom */
} M508_CAMERAVIEW;

typedef struct m508_camera {
    /* 0x000 */ s32 unk000;
    /* 0x004 */ s32 unk004;
    /* 0x008 */ s16 unk008;
    /* 0x00A */ s16 unk00A;
    /* 0x00C */ HUPROCESS *unk00C;
    /* 0x010 */ M508_CAMERAVIEW unk010[3];
    /* 0x0AC */ s32 unk0AC;
} M508_CAMERA;

/* The 0x14 message window object (fn_1_9E10). */
typedef struct m508_win {
    /* 0x000 */ s16 unk000; /* HUWINID */
    /* 0x004 */ f32 unk004;
    /* 0x008 */ f32 unk008;
    /* 0x00C */ s32 unk00C;
    /* 0x010 */ HUPROCESS *unk010;
} M508_WIN;

#define M508_OBJWAIT(frame)                                   \
    {                                                         \
        s32 waitMax = (frame);                                \
        s32 waitCnt;                                          \
        for (waitCnt = 0; waitCnt < waitMax; waitCnt++) {     \
            HuPrcVSleep();                                    \
            if (M508_CUROBJ->unk008 != M508_CUROBJ->unk004) { \
                M508_CUROBJ->unk008 = M508_CUROBJ->unk004;    \
                return;                                       \
            }                                                 \
            M508_CUROBJ->unk008 = M508_CUROBJ->unk004;        \
        }                                                     \
    }

#define M508_POSGET(o, px, py, pz)        \
    {                                     \
        if ((px) != NULL) {               \
            *(px) = (o)->unk160.x;        \
        }                                 \
        if ((py) != NULL) {               \
            *(py) = (o)->unk160.y;        \
        }                                 \
        if ((pz) != NULL) {               \
            *(pz) = (o)->unk160.z;        \
        }                                 \
    }

#define M508_OBJPOSGET(o, X, Y, Z) M508_POSGET(o, X, Y, Z)

#define M508_OBJPOSSET(o, X, Y, Z)                                         \
    Hu3DModelPosSet((o)->unk184, (o)->unk160.x = (X), (o)->unk160.y = (Y), \
                    (o)->unk160.z = (Z))

#define M508_OBJROTSET(o, X, Y, Z)                                         \
    Hu3DModelRotSet((o)->unk184, (o)->unk16C.x = (X), (o)->unk16C.y = (Y), \
                    (o)->unk16C.z = (Z))

/* The camera-specific sleep: it applies the live view through fn_1_8BF4 on
 * every tick, which is why none of the three mode handlers calls it. */
#define CAMERA_SLEEP_MODECHG(tick) \
do { \
    int mode; \
    int i; \
    int num; \
    num = tick; \
    for(i=0; i<num; i++) { \
        mode = ((M508_CAMERA *)HuPrcCurrentGet()->property)->unk000; \
        fn_1_8BF4(HuPrcCurrentGet()->property); \
        HuPrcVSleep(); \
        if(mode != ((M508_CAMERA *)HuPrcCurrentGet()->property)->unk000) { \
            return; \
        } \
    } \
} while(0)

/* merged by structmerge.py from forks ABCDE: owner fields + every other fork's fields by offset */

typedef struct M508_SPAWN_s M508_SPAWN;
typedef struct M508_CHARWK_s M508_CHARWK;
typedef struct M508_LIGHTWK_s M508_LIGHTWK;
typedef struct M508_MDLWK_s M508_MDLWK;
typedef struct M508_PLAYERWK_s M508_PLAYERWK;
typedef struct M508_HUDWK_s M508_HUDWK;
typedef struct M508_SCOREWK_s M508_SCOREWK;

struct M508_SPAWN_s {
    s32 unk000;  /* lwz, passed on as an int */
    f32 unk004;
    f32 unk008;
    f32 unk00C;
}; /* size 0x10 (f?) */

struct M508_CHARWK_s {
    s32 unk000;
    f32 unk004;
    f32 unk008;
    f32 unk00C;
    HU3DLLIGHTID unk010;
}; /* size 0x12 (f?) */

struct M508_LIGHTWK_s {
    HU3DLLIGHTID unk000;
    u8 pad002[0x2];
    s32 unk004;
}; /* size 0x8 (f?) */

struct M508_MDLWK_s {
    HU3DMODELID unk000;  /* lha 0x0(work); = Hu3DModelCreate(...) */
    HU3DLLIGHTID unk002;  /* lha 0x2(work); light on obj->unk184 */
    HU3DLLIGHTID unk004;  /* lha 0x4(work); light on work->unk000 */
}; /* size 0x6 (f?) */

struct M508_PLAYERWK_s {
    s32 unk000;  /* stw 0 */
    s32 unk004;  /* stw -1 */
}; /* size 0x8 (f?) */

struct M508_HUDWK_s {
    s32 unk000;  /* stw 57B0; lwz + cmpwi 0/1/5 at 58F8 -> signed word */
}; /* size 0x4 (f?) */

struct M508_SCOREWK_s {
    s16 unk000;  /* HUSPRGRPID; sth at 4C84, lha at 4D7C */
    s16 unk002[7];  /* HUSPRID;    sthx at 4D34, lhax at 4D48 */
    f32 unk010;  /* stfs/lfs 4F74/4F88 */
    f32 unk014;  /* stfs/lfs 4F7C/4F8C */
    s32 unk018;  /* lwz + cmpwi 3 at 5138 -> signed word */
    s16 unk01C;  /* HUSPRGRPID; sth 4C94, lha 4D5C/4EE8 */
}; /* size 0x1E (f?) */

#define M508_LIGHTWK(o) ((M508_LIGHTWK *)(o)->unk018)
#define M508_CHARWK(o) ((M508_CHARWK *)(o)->unk018)
#define M508_MDLWK(o) ((M508_MDLWK *)(o)->unk018)
#define M508_PLAYERWK(o) ((M508_PLAYERWK *)(o)->unk018)
#define M508_SCOREWK(o) ((M508_SCOREWK *)(o)->unk018)
#define M508_HUDWK(o) ((M508_HUDWK *)(o)->unk018)

/* --- m508.c --- */
void ObjectSetup(void);
void fn_1_538(void);
M508_OBJ *fn_1_5B0(void);
void fn_1_6FC(M508_OBJ *obj);
void fn_1_A3C(M508_OBJ *obj);
void fn_1_10D4(M508_OBJ *obj);
void fn_1_15B4(M508_OBJ *obj);
void fn_1_1BB4(void);
M508_OBJ *fn_1_1D88(void);
void fn_1_1E58(M508_OBJ *obj);
M508_OBJ *fn_1_1E64(void);
M508_OBJ *fn_1_1F34(void);
void fn_1_1FD0(M508_OBJ *obj);
void fn_1_1FDC(M508_OBJ *obj);
void fn_1_2084(M508_OBJ *obj, s32 pattern);
void fn_1_20A8(M508_OBJ *obj);
void fn_1_21C8(M508_OBJ *obj, s32 mot);
M508_OBJ *fn_1_2260(void);
void fn_1_22B4(M508_OBJ *obj);
void fn_1_22C0(M508_OBJ *obj);
void fn_1_2388(M508_OBJ *obj);
void fn_1_2394(M508_OBJ *obj);
M508_OBJ *fn_1_24DC(void);
void fn_1_25A8(M508_OBJ *obj);
void fn_1_25B4(M508_OBJ *obj);
void fn_1_265C(M508_OBJ *obj, s32 mot, f32 rotY, f32 shift, f32 speed);
void fn_1_268C(M508_OBJ *obj);
void fn_1_2838(M508_OBJ *obj);
void fn_1_2844(M508_OBJ *obj);
void fn_1_2C7C(M508_OBJ *obj);
void fn_1_2C88(M508_OBJ *obj);
void fn_1_2F80(M508_OBJ *obj);
float fn_1_2F8C(float cur, float target, float rate);
void fn_1_3090(M508_OBJ *obj);
void fn_1_33D8(M508_OBJ *obj);
void fn_1_33E4(M508_OBJ *obj);
M508_OBJ *fn_1_37E0(s32 no);
void fn_1_38CC(M508_OBJ *obj, float x, float y, float z);
M508_OBJ *fn_1_3958(s32 playerNo);
void fn_1_3A38(M508_OBJ *obj);
void fn_1_3A44(M508_OBJ *obj);
void fn_1_3B8C(M508_OBJ *obj);
void fn_1_3B98(M508_OBJ *obj);
void fn_1_4150(M508_OBJ *obj);
void fn_1_415C(M508_OBJ *obj);
void fn_1_4374(M508_OBJ *obj);
void fn_1_4380(M508_OBJ *obj);
s32 fn_1_4654(M508_OBJ *obj);
void fn_1_469C(M508_OBJ *obj);
void fn_1_46A8(M508_OBJ *obj);
void fn_1_4790(M508_OBJ *obj);
void fn_1_479C(M508_OBJ *obj);
void fn_1_4884(M508_OBJ *obj);
void fn_1_4890(M508_OBJ *obj);
void fn_1_49EC(M508_OBJ *obj);
void fn_1_49F8(M508_OBJ *obj);
M508_OBJ *fn_1_4B54(s32 playerNo);
void fn_1_4F48(M508_OBJ *obj, float posX, float posY);
void fn_1_4FA8(M508_OBJ *obj);
void fn_1_5010(M508_OBJ *obj);
void fn_1_5078(M508_OBJ *obj);
void fn_1_5084(M508_OBJ *obj);
void fn_1_512C(M508_OBJ *obj);
void fn_1_5164(M508_OBJ *obj);
M508_OBJ *fn_1_5394(s32 idx);
M508_OBJ *fn_1_5414(s32 unused);
void fn_1_5464(M508_OBJ *obj);
void fn_1_5470(M508_OBJ *obj);
void fn_1_5518(M508_OBJ *obj);
void fn_1_5524(M508_OBJ *obj);
M508_OBJ *fn_1_560C(void);
M508_OBJ *fn_1_5758(s32 idx);
void fn_1_57D4(M508_OBJ *obj);
void fn_1_57E0(M508_OBJ *obj);
void fn_1_58B8(M508_OBJ *obj);
void fn_1_58C4(M508_OBJ *obj);
void fn_1_5C7C(s32 playerNo, s32 type, s32 duration);

/* --- object.c --- */
/* extern lbl_1_data_B0; */
/* extern lbl_1_rodata_770; */
/* extern lbl_1_rodata_778; */
/* extern lbl_1_rodata_780; */
/* extern lbl_1_rodata_788; */
/* extern lbl_1_rodata_78C; */
/* extern lbl_1_rodata_790; */
/* extern lbl_1_rodata_798; */
/* extern lbl_1_rodata_7A0; */
/* extern lbl_1_rodata_7A4; */
/* extern lbl_1_rodata_7A8; */
/* extern lbl_1_rodata_7AC; */
/* extern lbl_1_rodata_7B0; */
/* extern lbl_1_rodata_7B4; */
/* extern lbl_1_rodata_7B8; */
/* extern lbl_1_rodata_7C0; */
/* extern lbl_1_rodata_7C8; */
/* extern lbl_1_rodata_7CC; */
/* extern lbl_1_rodata_7D0; */
/* extern lbl_1_rodata_7D8; */
/* extern lbl_1_rodata_7E0; */
/* extern lbl_1_rodata_7E8; */
/* extern lbl_1_rodata_7EC; */
void fn_1_A194(void);
void fn_1_A314(void);
void fn_1_A4DC(void);
void fn_1_A564(void);
void fn_1_A5F4(void);
void fn_1_A65C(void);
void fn_1_A74C(void);
void fn_1_AD98(void);
void fn_1_AF28(void);
void fn_1_B1C0(void);
void fn_1_B274(void);
void fn_1_B514(void);
void fn_1_BC7C(void);
void fn_1_BDB0(void);
void fn_1_BDF0(void);
void fn_1_BE58(void);
void fn_1_BE70(void);
void fn_1_C0F4(void);
void fn_1_C194(void);
void fn_1_C1E8(void);
void fn_1_C228(void);
void fn_1_C27C(void);
void fn_1_C2BC(void);
void fn_1_C310(void);
void fn_1_C350(void);
void fn_1_C38C(void);
void fn_1_C394(void);
void fn_1_C3D0(void);
void fn_1_C40C(void);
void fn_1_C414(void);
void fn_1_C470(void);
void fn_1_C4E8(void);
void fn_1_C520(void);
void fn_1_C570(void);
void fn_1_C5EC(void);
void fn_1_C5F4(void);
void fn_1_C630(void);
void fn_1_C660(void);
void fn_1_C690(void);
void fn_1_C6C0(void);
void fn_1_C6C4(void);
void fn_1_C70C(void);
void fn_1_C73C(void);
void fn_1_CA2C(void);
void fn_1_CACC(void);
void fn_1_CB24(void);
void fn_1_CD14(void);
void fn_1_CD4C(void);
void fn_1_CDB0(void);
void fn_1_D028(void);
void fn_1_D098(void);
void fn_1_D0A4(void);
void fn_1_D158(void);
void fn_1_D164(void);
void fn_1_D22C(void);
void fn_1_D25C(void);
void fn_1_D6A0(void);
void fn_1_D9AC(void);
void fn_1_DA0C(void);
void fn_1_DA5C(void);
void fn_1_DAF0(void);
void fn_1_DF6C(void);
void fn_1_DF70(void);
void fn_1_DFCC(void);
void fn_1_E028(void);
void fn_1_E0B4(void);
void fn_1_E140(void);
void fn_1_E244(void);
void fn_1_E2EC(void);
void fn_1_E32C(void);
void fn_1_E340(void);
void fn_1_E388(void);
void fn_1_E39C(void);
void fn_1_E3D4(void);
void fn_1_E40C(void);
void fn_1_E444(void);
void fn_1_E480(void);
void fn_1_E4B8(void);
void fn_1_E4E8(void);
void fn_1_E518(void);
void fn_1_E548(void);

#endif
