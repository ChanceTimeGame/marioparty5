#ifndef REL_M535DLL_M535_H
#define REL_M535DLL_M535_H

#include "game/object.h"
#include "game/hu3d.h"
#include "dolphin/mtx.h"

/* ------------------------------------------------------------------------
 * m535dll work structures.
 *
 * Offsets are the reference's, measured from the assembly. Keep every field
 * at its byte offset and keep the unkXXX names until the use is unambiguous,
 * so a fork's OUT.c merges mechanically.
 * ---------------------------------------------------------------------- */

/* obj->data of the four player objects (group 0, prio 100, fn_1_B31C init).
 * HuMemDirectMallocNum(HEAP_HEAP, 0x340, HU_MEMNUM_OVL); memset 0 first. */
typedef struct m535Player_s {
    /* 0x000 */ s32 playerNo;       /* obj->work[0] */
    /* 0x004 */ s32 padIdx;         /* GwPlayerConf pad index; ==4 -> playerNo */
    /* 0x008 */ s32 unk008;         /* min(charNo, 9) */
    /* 0x00C */ s32 charNo;         /* GwPlayerConf[padIdx].character */
    /* 0x010 */ s32 unk010;         /* -1 when GwPlayerConf[].unk8 set, else [].unk2 */
    /* 0x014 */ s32 unk014;
    /* 0x018 */ s32 unk018;
    /* 0x01C */ s32 unk01C;
    /* 0x020 */ s32 unk020;         /* = 2 */
    /* 0x024 */ s32 unk024;
    /* 0x028 */ f32 unk028;
    /* 0x02C */ f32 unk02C;
    /* 0x030 */ f32 unk030;
    /* 0x034 */ f32 unk034;
    /* 0x038 */ s32 unk038;
    /* 0x03C */ s32 unk03C;         /* = 0 */
    /* 0x040 */ s32 unk040;
    /* 0x044 */ f32 unk044;
    /* 0x048 */ f32 unk048;
    /* 0x04C */ s32 unk04C;
    /* 0x050 */ s32 unk050;         /* = -1 */
    /* 0x054 */ s32 unk054;
    /* 0x058 */ s32 unk058;
    /* 0x05C */ s32 unk05C;
    /* 0x060 */ s32 unk060;
    /* 0x064 */ s32 unk064;
    /* 0x068 */ s32 unk068;
    /* 0x06C */ f32 unk06C[30];     /* dust ring: x */
    /* 0x0E4 */ f32 unk0E4[30];     /* dust ring: y */
    /* 0x15C */ f32 unk15C[30];     /* dust ring: z */
    /* 0x1D4 */ f32 unk1D4[30];     /* dust ring: scale */
    /* 0x24C */ s32 unk24C[30];     /* dust ring: alpha */
    /* 0x2C4 */ s32 unk2C4[30];     /* dust ring: age; -1 = free */
    /* 0x33C */ s32 unk33C;         /* dust spawn countdown; = 0 */
} M535_PLAYER;                      /* 0x340 */

/* lbl_1_bss_8284: 12 entries of 0x14. fn_1_A3C4's last loop walks it with a
 * stride of 20 and stores -1 at +0x10, which fixes both the stride and the
 * count (12 * 0x14 == 0xF0). */
typedef struct m535Se_s {
    /* 0x00 */ s32 unk00;           /* pending count, clamped to 3 */
    /* 0x04 */ f32 unk04[3];        /* pan argument of each pending play */
    /* 0x10 */ s32 unk10;           /* the HuAudFXPlay handle */
} M535_SE;                          /* 0x14 */

/* lbl_1_bss_8374: 54 entries of 0x38. */
typedef struct m535Obj_s {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C[3];        /* 0x1C,0x20,0x24 -- the model slot per round */
    /* 0x28 */ s32 unk28;          /* the card's type, 0..11 */
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30[2];       /* the omote/ura Hu3DAnim ids */
} M535_OBJ;                         /* 0x38 */

#endif
