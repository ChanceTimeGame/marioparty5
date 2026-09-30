#ifndef M540_H
#define M540_H

#include <stddef.h>

/* ===========================================================================
 * m540dll -- merged type declarations.
 *
 * Reconciled from the eight forks' deliverables.  Every struct is matched by
 * hex offset; where two forks spelled the same layout with different type
 * names the extra names are typedef aliases of the one definition.
 * ==========================================================================*/

#include "game/animdata.h"
#include "game/esprite.h"
#include "game/window.h"
#include "messdir_enum.h"

/* ---------------------------------------------------------------------------
 * The object.
 *
 * One layout, three allocation sizes:
 *   fn_1_12F80 0x158 (header only), fn_1_13174 0x1B8 (header + model),
 *   fn_1_13A40 0x1CC (header + model + character).
 * Fork D spelled it M540OBJ, fork F split it into M540_OBJ/M540_OBJMDL/
 * M540_OBJCHAR, fork B called the character flavour M540_CHAR.  All agree
 * offset for offset, so the extras are aliases.
 * -------------------------------------------------------------------------*/
typedef struct m540_obj M540_OBJ;
typedef void (*M540_OBJFUNC)(M540_OBJ *obj);

struct m540_obj {
    /* 0x000 */ HUPROCESS *unk000;
    /* 0x004 */ s32 unk004;
    /* 0x008 */ s32 unk008;
    /* 0x00C */ s32 unk00C;
    /* 0x010 */ M540_OBJFUNC *unk010;
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

typedef M540_OBJ M540OBJ;      /* fork D */
typedef M540_OBJ M540_OBJMDL;  /* fork F */
typedef M540_OBJ M540_OBJCHAR; /* fork F */
typedef M540_OBJ M540_CHAR;    /* fork B */

/* The three object flavours allocate prefixes of one struct, and retail spells
 * those prefixes as literals. A host pointer is 8 bytes where the console's is
 * 4, so M540_OBJ has three fields (unk000, unk010, unk190) that make the host
 * struct longer than the literal -- allocating 0x158 there under-allocates and
 * every later write walks off the block into the HuMem header of the next one.
 * That is what a corrupt `MCB:207(206/1) MEM:ea549e20` dump and
 * `process> malloc error size 256` were. offsetof names the same boundaries
 * exactly; CodeWarrior keeps the literals so the matching object is unchanged. */
#define M540_OBJ_SIZE 0x158
#define M540_MDLOBJ_SIZE 0x1B8
#define M540_CHROBJ_SIZE 0x1CC

/* ---------------------------------------------------------------------------
 * The +0x18 work area of a model object (fn_1_13174 family).
 * Fork C called it M540_ACTOR, fork D M540WORK, fork E M540_MDLWORK,
 * fork B M540_CHARSUB, fork F M540_PLAYER_SUB.  One layout.
 * -------------------------------------------------------------------------*/
typedef struct m540_mdlwork {
    /* 0x000 */ M540_OBJ *unk000;
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
} M540_MDLWORK;

typedef M540_MDLWORK M540WORK;        /* fork D */
typedef M540_MDLWORK M540_ACTOR;      /* fork C */
typedef M540_MDLWORK M540_CHARSUB;    /* fork B */
typedef M540_MDLWORK M540_PLAYER_SUB; /* fork F */

/* The +0x18 work area of a character object (fn_1_13A40 family). */
typedef struct m540_charwork {
    /* 0x000 */ HuVecF unk000;
    /* 0x00C */ s32 unk00C;
    /* 0x010 */ s32 unk010;
    /* 0x014 */ f32 unk014;
    /* 0x018 */ f32 unk018;
    /* 0x01C */ f32 unk01C;
    /* 0x020 */ M540_OBJ *unk020;
} M540_CHARWORK;

/* These three function-like macros deliberately share a name with the typedef
 * above (fork D's M540_OBJWORK, fork E's M540_MDLWORK / M540_CHARWORK): a
 * function-like macro only expands when followed by "(", so "M540_MDLWORK *w"
 * still names the type. */
#define M540_OBJWORK(o) ((M540WORK *)(o)->unk018)
#define M540_MDLWORK(o) ((M540_MDLWORK *)(o)->unk018)
#define M540_CHARWORK(o) ((M540_CHARWORK *)(o)->unk018)

#define M540_CUROBJ ((M540_OBJ *)HuPrcCurrentGet()->property)
#define M540_CUR M540_CUROBJ
#define M540_OBJCUR M540_CUROBJ

/* ---------------------------------------------------------------------------
 * The camera.  0x34-byte view record x3 inside a 0xB0 work.
 * Fork C spelled the view M540_CAMWORK and the work M540_CAM; fork F spelled
 * them M540_VIEW / M540_CAMERA; fork H M540_CAMERAVIEW / M540_CAMERA; fork G
 * saw only the float at +0x10 and called the work M540_WORK.
 * -------------------------------------------------------------------------*/
typedef struct m540_cameraview {
    /* 0x000 */ HuVecF unk000; /* eye */
    /* 0x00C */ HuVecF unk00C; /* up */
    /* 0x018 */ HuVecF unk018; /* center */
    /* 0x024 */ HuVecF unk024; /* rot, degrees */
    /* 0x030 */ f32 unk030;    /* zoom */
} M540_CAMERAVIEW;

typedef M540_CAMERAVIEW M540_VIEW;    /* fork F */
typedef M540_CAMERAVIEW M540_CAMWORK; /* fork C */

typedef struct m540_camera {
    /* 0x000 */ s32 unk000;
    /* 0x004 */ s32 unk004;
    /* 0x008 */ s16 unk008;
    /* 0x00A */ s16 unk00A;
    /* 0x00C */ HUPROCESS *unk00C;
    /* 0x010 */ M540_CAMERAVIEW unk010[3];
    /* 0x0AC */ s32 unk0AC;
} M540_CAMERA;

typedef M540_CAMERA M540_CAM;  /* fork C */
typedef M540_CAMERA M540_WORK; /* fork G */

/* The shape of lbl_1_data_7C -- a mutable camera parameter record. */
typedef struct m540_camparam {
    /* 0x00 */ HuVecF unk00; /* center */
    /* 0x0C */ HuVecF unk0C; /* rot */
    /* 0x18 */ f32 unk18;    /* zoom */
} M540_CAMPARAM;

/* ---------------------------------------------------------------------------
 * The 0x14 message window object (fn_1_15548).  Fork B called it M540_MESWIN,
 * fork F M540_ITEMWIN, fork H M540_WIN.
 * -------------------------------------------------------------------------*/
typedef struct m540_win {
    /* 0x000 */ s16 unk000; /* HUWINID */
    /* 0x004 */ f32 unk004;
    /* 0x008 */ f32 unk008;
    /* 0x00C */ s32 unk00C;
    /* 0x010 */ HUPROCESS *unk010;
} M540_WIN;

typedef M540_WIN M540_MESWIN; /* fork B */
typedef M540_WIN M540_ITEMWIN; /* fork F */

/* ---------------------------------------------------------------------------
 * Small per-family +0x18 work areas.
 * -------------------------------------------------------------------------*/

/* lbl_1_bss_F4 -- the score panel and its EFB-to-texture mirror (fork C).
 * Fork F saw the first four words of the same record as M540_STAGE_SUB. */
typedef struct m540_screen {
    /* 0x00 */ s16 *unk000;
    /* 0x04 */ HuVecF *unk004;
    /* 0x08 */ s32 unk008;
    /* 0x0C */ s32 unk00C;
    /* 0x10 */ s16 unk010;
    /* 0x12 */ s16 unk012;
    /* 0x14 */ s32 unk014;
    /* 0x18 */ s32 unk018;
    /* 0x1C */ s32 unk01C;
    /* 0x20 */ s32 unk020;
    /* 0x24 */ void *unk024;
} M540_SCREEN;

typedef M540_SCREEN M540_STAGE_SUB; /* fork F */

/* the three lbl_1_bss_F8[] objects (fork C) */
typedef struct m540_prop {
    /* 0x00 */ s32 unk000;
} M540_PROP;

/* +0x18 of the fn_1_D4A0 work -- the item announce windows (fork F) */
typedef struct m540_item_sub {
    /* 0x00 */ s16 unk000[19];
    /* 0x28 */ M540_WIN *unk028[5];
} M540_ITEM_SUB;

/* +0x18 of the fn_1_DDF8 work (fork F) */
typedef struct m540_sub1 {
    /* 0x00 */ s32 unk000;
} M540_SUB1;

/* +0x18 of the fn_1_E124 work (fork F) */
typedef struct m540_sub2 {
    /* 0x00 */ s32 unk000;
    /* 0x04 */ s16 unk004[2];
} M540_SUB2;

/* +0x18 of the fn_1_E5F8 work (fork F) */
typedef struct m540_sub3 {
    /* 0x00 */ s16 unk000;
} M540_SUB3;

/* the lbl_1_bss_0[] smoke particles (fork G) */
typedef struct m540_smoke {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s16 unk04;
    /* 0x08 */ ANIMDATA *unk08;
    /* 0x0C */ HuVecF unk0C;
    /* 0x18 */ f32 unk18;
} M540_SMOKE;

/* fork E's hand-written collision shapes */
typedef struct m540_sphere {
    /* 0x00 */ HuVecF center;
    /* 0x0C */ f32 radius;
} M540_SPHERE;

typedef struct m540_circle {
    /* 0x00 */ HuVec2f center;
    /* 0x08 */ f32 radius;
} M540_CIRCLE;

/* ---------------------------------------------------------------------------
 * The object library's coroutine macros.  Five forks derived the same body
 * under five names; all five are kept because the merged bodies spell them
 * differently and the expansion is identical.
 * -------------------------------------------------------------------------*/
#define M540_OBJWAIT(frame)                                   \
    {                                                         \
        s32 waitMax = (frame);                                \
        s32 waitCnt;                                          \
        for (waitCnt = 0; waitCnt < waitMax; waitCnt++) {     \
            HuPrcVSleep();                                    \
            if (M540_CUROBJ->unk008 != M540_CUROBJ->unk004) { \
                M540_CUROBJ->unk008 = M540_CUROBJ->unk004;    \
                return;                                       \
            }                                                 \
            M540_CUROBJ->unk008 = M540_CUROBJ->unk004;        \
        }                                                     \
    }

#define M540_WAIT(n) M540_OBJWAIT(n)
#define M540_SLEEP(n) M540_OBJWAIT(n)

#define M540_OBJSLEEP_VARS s32 _i; s32 _n

#define M540_OBJSLEEP(t)                                  \
    {                                                     \
        _n = (t);                                         \
        for (_i = 0; _i < _n; _i++) {                     \
            HuPrcVSleep();                                \
            if (M540_OBJCUR->unk008 != M540_OBJCUR->unk004) { \
                M540_OBJCUR->unk008 = M540_OBJCUR->unk004;    \
                return;                                   \
            }                                             \
            M540_OBJCUR->unk008 = M540_OBJCUR->unk004;    \
        }                                                 \
    }

#define M540_POSGET(o, px, py, pz)        \
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

#define M540_OBJPOSGET(o, X, Y, Z) M540_POSGET(o, X, Y, Z)

#define M540_OBJPOSSET(o, X, Y, Z)                                         \
    Hu3DModelPosSet((o)->unk184, (o)->unk160.x = (X), (o)->unk160.y = (Y), \
                    (o)->unk160.z = (Z))

#define M540_POSSET(o, X, Y, Z) M540_OBJPOSSET(o, X, Y, Z)

#define M540_OBJROTSET(o, X, Y, Z)                                         \
    Hu3DModelRotSet((o)->unk184, (o)->unk16C.x = (X), (o)->unk16C.y = (Y), \
                    (o)->unk16C.z = (Z))

/* a positioned sound effect.  fn_1_10F44 / fn_1_110A8 / fn_1_111B8 take the
 * position BY VALUE: the GC ABI copies the caller's vector into the caller's
 * frame and passes a pointer, which is the copy fork G's macros made by hand
 * and the copy fork D's and fork E's call sites rely on (the callee subtracts
 * the camera x from it in place). */
#define M540_SEPAN(se, v) HuAudFXPanning((se), fn_1_110A8(v))
#define M540_SEVOL(se, v) HuAudFXVolSet((se), fn_1_10F44(v))
#define M540_SEPLAY(se, v) fn_1_111B8((se), (v))

/* fork H's camera-specific sleep: it applies the live view through fn_1_1432C
 * on every tick, which is why none of the three mode handlers calls it. */
#define CAMERA_SLEEP_MODECHG(tick) \
do { \
    int mode; \
    int i; \
    int num; \
    num = tick; \
    for(i=0; i<num; i++) { \
        mode = ((M540_CAMERA *)HuPrcCurrentGet()->property)->unk000; \
        fn_1_1432C(HuPrcCurrentGet()->property); \
        HuPrcVSleep(); \
        if(mode != ((M540_CAMERA *)HuPrcCurrentGet()->property)->unk000) { \
            return; \
        } \
    } \
} while(0)

#endif /* M540_H */
