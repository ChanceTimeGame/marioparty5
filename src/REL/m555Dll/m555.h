/*
 * The types m555.c, game.c and stage.c all need.
 *
 * m555dll is a KETTOU duel (overlay #69) on work head D of the duel stage
 * framework, REL/duelstage.h: m541's work layout (three chr/motion slots, the
 * DS_CHAR262 pad block, stageDataTbl at 0x170). The work is 0x2E8.
 *
 * Offsets come from every access in the reference assembly (NOTES.md). Names
 * that say unkNNN are unexplained, not unallocated.
 */
#ifndef M555_H
#define M555_H

#include "game/object.h"
#include "game/hu3d.h"
#include "game/mg/timer.h"
#include "game/mg/actman.h"
#include "humath.h"

/* The duel stage framework's types; stage.c includes its functions. */
#include "REL/duelstage.h"

/* One entry of the retained-mode model table (bss_1A84, 0x12B4 = 171 of them). */
typedef DS_MODEL M555_MODEL;        /* 0x1C */

#define M555_MODEL_MAX 171

typedef DS_CHAR262 M555_CHAR;       /* 0x1C */

typedef struct M555Work_s {
    /* 0x000 */ OMOBJMAN *objman;
    /* 0x004 */ M555_CHAR chr[3];
    /* 0x058 */ M555_MODEL *models;
    /* 0x05C */ unsigned int *charMotData[3];
    /* 0x068 */ HU3DMOTID *motId[3];
    /* 0x074 */ DS_PLAYER player[3];
    /* 0x170 */ unsigned int *stageDataTbl;
    /* 0x174 */ s16 stageNo;
    /* 0x176 */ s16 pad176;
    /* 0x178 */ int mode[4];
    /* 0x188 */ u8 unk188[0x160];
} M555_WORK;                        /* 0x2E8 */


/* The cameras' state (bss_8, four allocated plus eight bytes), from lbl_1_data_150. */
typedef struct M555Camera_s {
    /* 0x00 */ int no;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ HuVecF rot;
    /* 0x1C */ HuVecF center;
    /* 0x28 */ HuVecF up;
    /* 0x34 */ float zoom;
    /* 0x38 */ float aspect;
    /* 0x3C */ float vpX;
    /* 0x40 */ float vpY;
    /* 0x44 */ float vpW;
    /* 0x48 */ float vpH;
    /* 0x4C */ float fov;
} M555_CAMERA;                      /* 0x50 */

typedef struct M555CameraInit_s {
    /* 0x00 */ HuVecF center;
    /* 0x0C */ HuVecF rot;
    /* 0x18 */ float zoom;
    /* 0x1C */ float aspect;
    /* 0x20 */ float vpX;
    /* 0x24 */ float vpY;
    /* 0x28 */ float vpW;
    /* 0x2C */ float vpH;
    /* 0x30 */ float fov;
} M555_CAMERAINIT;                  /* 0x34 */

/* The global light (bss_4). */
typedef struct M555Light_s {
    /* 0x00 */ HU3DLIGHTID id;
    /* 0x02 */ s16 pad02;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ HuVecF rot;
    /* 0x1C */ HuVecF target;
    /* 0x28 */ HuVecF dir;
    /* 0x34 */ float dist;
    /* 0x38 */ GXColor color;
} M555_LIGHT;                       /* 0x3C */

/* The shadow camera (bss_0). */
typedef struct M555Shadow_s {
    /* 0x00 */ HuVecF pos;
    /* 0x0C */ HuVecF rot;
    /* 0x18 */ HuVecF target;
    /* 0x24 */ HuVecF unk24;
    /* 0x30 */ HuVecF up;
    /* 0x3C */ HuVecF unk3C;
    /* 0x48 */ float dist;
    /* 0x4C */ float tpLvl;
} M555_SHADOW;                      /* 0x50 */

/* lbl_1_bss_C: fn_1_CFB8's background props. Offset-named; only fn_1_CFB8 uses it. */
typedef struct M555Unk0C1C_s {
    /* 0x00 */ s16 unk00;           /* active */
    /* 0x02 */ s16 unk02;           /* mode */
    /* 0x04 */ float unk04;
    /* 0x08 */ float unk08;
} M555_UNK0C1C;                     /* 0x0C */

typedef struct M555Unk0C114_s {
    /* 0x00 */ s16 unk00;           /* active */
    /* 0x02 */ s16 unk02;           /* mode */
} M555_UNK0C114;                    /* 0x04 */

typedef struct M555Unk0C144_s {
    /* 0x00 */ s16 unk00;           /* active */
    /* 0x02 */ s16 unk02;           /* mode */
    /* 0x04 */ u8 pad04[0x04];
    /* 0x08 */ float unk08;
    /* 0x0C */ float unk0C;
    /* 0x10 */ float unk10;
    /* 0x14 */ float unk14;
    /* 0x18 */ u8 pad18[0x18];
} M555_UNK0C144;                    /* 0x30 */

typedef struct M555Unk0C_s {
    /* 0x000 */ u8 pad000[0x08];
    /* 0x008 */ s16 unk008;
    /* 0x00A */ s16 unk00A;
    /* 0x00C */ s16 unk00C[3];
    /* 0x012 */ s16 unk012[4];
    /* 0x01A */ u8 pad01A[0x02];
    /* 0x01C */ M555_UNK0C1C unk01C[12];
    /* 0x0AC */ u8 pad0AC[0x60];
    /* 0x10C */ s16 unk10C;
    /* 0x10E */ s16 unk10E;
    /* 0x110 */ u8 pad110[0x04];
    /* 0x114 */ M555_UNK0C114 unk114[4];
    /* 0x124 */ s16 unk124;
    /* 0x126 */ u8 pad126[0x02];
    /* 0x128 */ s16 unk128;
    /* 0x12A */ s16 unk12A;
    /* 0x12C */ u8 pad12C[0x10];
    /* 0x13C */ s16 unk13C[4];
    /* 0x144 */ M555_UNK0C144 unk144[4];
    /* 0x204 */ s16 unk204;
    /* 0x206 */ u8 pad206[0x02];
} M555_UNK0C;                       /* 0x208 */

/* lbl_1_bss_214 [100]. Offset-named from the reference accesses; see NOTES.md. */
typedef struct M555Unk214_s {
    /* 0x000 */ s16 unk000;
    /* 0x002 */ s16 unk002;
    /* 0x004 */ s16 unk004;
    /* 0x006 */ s16 unk006;
    /* 0x008 */ s16 unk008;
    /* 0x00A */ s16 unk00A;
    /* 0x00C */ float unk00C;
    /* 0x010 */ float unk010;
    /* 0x014 */ float unk014;
} M555_UNK214;             /* 0x18 */

/* lbl_1_bss_B74. Offset-named from the reference accesses; see NOTES.md. */
typedef struct M555Unkb74_s {
    /* 0x000 */ s16 unk000[3];
    /* 0x006 */ s16 unk006[6];
    /* 0x012 */ s16 unk012;
} M555_UNKB74;             /* 0x14 */

/* lbl_1_bss_B88 [50]. Offset-named from the reference accesses; see NOTES.md. */
typedef struct M555Unkb88_s {
    /* 0x000 */ s16 unk000;
    /* 0x002 */ s16 unk002;
    /* 0x004 */ u8 pad004[0x08];
    /* 0x00C */ float unk00C;
    /* 0x010 */ float unk010;
    /* 0x014 */ float unk014;
    /* 0x018 */ u8 pad018[0x04];
    /* 0x01C */ float unk01C;
} M555_UNKB88;             /* 0x20 */

/* lbl_1_bss_11C8. Offset-named from the reference accesses; see NOTES.md. */
typedef struct M555Unk11C8_s {
    /* 0x000 */ s16 unk000;
    /* 0x002 */ s16 unk002;
    /* 0x004 */ s16 unk004;
    /* 0x006 */ s16 unk006;
    /* 0x008 */ s16 unk008;
    /* 0x00A */ s16 unk00A;
    /* 0x00C */ s16 unk00C[6];
    /* 0x018 */ s16 unk018;
} M555_UNK11C8;            /* 0x1A */

/* lbl_1_bss_11E4. Offset-named from the reference accesses; see NOTES.md. */
typedef struct M555Unk11E4_s {
    /* 0x000 */ s16 unk000;
    /* 0x002 */ u8 pad002[0x02];
    /* 0x004 */ s16 unk004;
    /* 0x006 */ u8 pad006[0x02];
    /* 0x008 */ s16 unk008;
    /* 0x00A */ u8 pad00A[0x02];
    /* 0x00C */ float unk00C;
    /* 0x010 */ float unk010;
    /* 0x014 */ float unk014;
    /* 0x018 */ u8 pad018[0x04];
    /* 0x01C */ float unk01C;
    /* 0x020 */ float unk020;
    /* 0x024 */ u8 pad024[0x04];
} M555_UNK11E4;            /* 0x28 */

/* lbl_1_bss_120C [2]. Offset-named from the reference accesses; see NOTES.md. */
typedef struct M555Duellist_s {
    /* 0x000 */ u8 pad000[0x02];
    /* 0x002 */ s16 unk002;
    /* 0x004 */ u8 pad004[0x04];
    /* 0x008 */ s16 unk008;
    /* 0x00A */ s16 unk00A;
    /* 0x00C */ s16 unk00C;
    /* 0x00E */ s16 unk00E;
    /* 0x010 */ s16 unk010;
    /* 0x012 */ s16 unk012;
    /* 0x014 */ s16 unk014;
    /* 0x016 */ s16 unk016;
    /* 0x018 */ s16 unk018;
    /* 0x01A */ s16 unk01A;
    /* 0x01C */ u8 pad01C[0x04];
    /* 0x020 */ float unk020;
    /* 0x024 */ float unk024;
    /* 0x028 */ u8 pad028[0x08];
    /* 0x030 */ float unk030;
    /* 0x034 */ float unk034;
    /* 0x038 */ u8 pad038[0x04];
    /* 0x03C */ float unk03C;
    /* 0x040 */ float unk040;
    /* 0x044 */ HuVecF unk044;
    /* 0x050 */ s16 unk050;
    /* 0x052 */ s16 unk052;
    /* 0x054 */ s16 unk054;
    /* 0x056 */ s16 unk056;
    /* 0x058 */ u8 pad058[0x04];
    /* 0x05C */ s16 unk05C;
    /* 0x05E */ s16 unk05E;
    /* 0x060 */ HuVecF unk060[36];
    /* 0x210 */ float unk210[36];
    /* 0x2A0 */ s16 unk2A0[36];
    /* 0x2E8 */ s16 unk2E8;
    /* 0x2EA */ s16 unk2EA;
    /* 0x2EC */ u8 pad2EC[0x04];
    /* 0x2F0 */ HuVecF unk2F0;
    /* 0x2FC */ s16 unk2FC;
    /* 0x2FE */ s16 unk2FE;
    /* 0x300 */ u8 pad300[0x02];
    /* 0x302 */ s16 unk302;
    /* 0x304 */ s16 unk304;
    /* 0x306 */ u8 pad306[0x02];
    /* 0x308 */ HuVecF unk308;
    /* 0x314 */ HuVecF unk314;
    /* 0x320 */ float unk320;
    /* 0x324 */ float unk324;
    /* 0x328 */ float unk328;
    /* 0x32C */ s16 unk32C;
    /* 0x32E */ s16 unk32E;
    /* 0x330 */ s16 unk330;
    /* 0x332 */ u8 pad332[0x02];
    /* 0x334 */ int unk334;
    /* 0x338 */ int unk338;
    /* 0x33C */ int unk33C;
    /* 0x340 */ int unk340;
} M555_DUELLIST;           /* 0x344 */

/* lbl_1_bss_1894's four-entry array at 0x084 (fn_1_11DFC), 0x30 each. */
typedef struct M555Game084_s {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ float unk08;
    /* 0x0C */ float unk0C;
    /* 0x10 */ float unk10;
    /* 0x14 */ float unk14;
    /* 0x18 */ float unk18;
    /* 0x1C */ float unk1C;
    /* 0x20 */ float unk20;
    /* 0x24 */ float unk24;
    /* 0x28 */ float unk28;
    /* 0x2C */ float unk2C;
} M555_GAME084;             /* 0x30 */

/* lbl_1_bss_1894. Offset-named from the reference accesses; see NOTES.md. */
typedef struct M555Game_s {
    /* 0x000 */ s16 unk000;
    /* 0x002 */ s16 unk002;
    /* 0x004 */ s16 unk004;
    /* 0x006 */ s16 unk006;
    /* 0x008 */ int unk008;
    /* 0x00C */ s16 unk00C;
    /* 0x00E */ u8 pad00E[0x18];
    /* 0x026 */ s16 unk026;
    /* 0x028 */ s16 unk028;
    /* 0x02A */ s16 unk02A;
    /* 0x02C */ s16 unk02C;
    /* 0x02E */ s16 unk02E;
    /* 0x030 */ s16 unk030;
    /* 0x032 */ s16 unk032;
    /* 0x034 */ s16 unk034;
    /* 0x036 */ s16 unk036;
    /* 0x038 */ s16 unk038;
    /* 0x03A */ u8 pad03A[0x02];
    /* 0x03C */ float unk03C;
    /* 0x040 */ s16 unk040;
    /* 0x042 */ u8 pad042[0x42];
    /* 0x084 */ M555_GAME084 unk084[4];
    /* 0x144 */ s16 unk144;
    /* 0x146 */ s16 unk146;
    /* 0x148 */ s16 unk148;
    /* 0x14A */ s16 unk14A;
    /* 0x14C */ u8 pad14C[0x08];
    /* 0x154 */ HuVecF unk154;
    /* 0x160 */ s16 unk160;
    /* 0x162 */ u8 pad162[0x02];
    /* 0x164 */ float unk164;
    /* 0x168 */ HuVecF unk168;
    /* 0x174 */ u8 pad174[0x04];
    /* 0x178 */ s16 unk178;
    /* 0x17A */ u8 pad17A[0x02];
    /* 0x17C */ float unk17C;
    /* 0x180 */ s16 unk180;
    /* 0x182 */ s16 unk182;
    /* 0x184 */ float unk184;
    /* 0x188 */ float unk188;
    /* 0x18C */ u8 unk18C;
    /* 0x18D */ u8 unk18D;
    /* 0x18E */ u8 unk18E;
    /* 0x18F */ u8 pad18F[0x05];
    /* 0x194 */ int bgmNo;
    /* 0x198 */ int jingleNo;
    /* 0x19C */ u8 pad19C[0x04];
    /* 0x1A0 */ int seNo[12];
    /* 0x1D0 */ s16 seF[12];
} M555_GAME;               /* 0x1E8 */

/* m555.c */
extern M555_SHADOW *lbl_1_bss_0;
extern M555_LIGHT *lbl_1_bss_4;
extern M555_CAMERA *lbl_1_bss_8;
extern M555_UNK0C lbl_1_bss_C;
extern M555_UNK214 lbl_1_bss_214[100];
extern M555_UNKB74 lbl_1_bss_B74;
extern M555_UNKB88 lbl_1_bss_B88[50];
extern M555_UNK11C8 lbl_1_bss_11C8;
extern M555_UNK11E4 lbl_1_bss_11E4;
extern M555_DUELLIST lbl_1_bss_120C[2];
extern M555_GAME lbl_1_bss_1894;
extern HU3DMOTID lbl_1_bss_1A7C[2][2];
extern M555_MODEL lbl_1_bss_1A84[M555_MODEL_MAX];
extern M555_WORK lbl_1_bss_2D38;
extern M555_CAMERAINIT lbl_1_data_150[4];

void fn_1_964(s16 no);
void fn_1_110C(void);
void fn_1_150C(void);
s16 fn_1_1898(float *value, float div, float start, float end);
MGTIMER *fn_1_1AD4(int type, int maxTime, int endTime, float x, float y);
void fn_1_1B48(MGTIMER *timer);
BOOL fn_1_1B74(MGTIMER *timer);
void fn_1_1B9C(MGTIMER *timer);
void fn_1_247C(void);
void fn_1_25D8(HuVecF *pos);
void fn_1_29E8(void);
void fn_1_2A18(void);
void fn_1_2A48(s16 bgmF, s16 speed);
void fn_1_2AB0(s16 bgmF);
void fn_1_2B10(s16 no);
void fn_1_2BD8(s16 no, s16 vol, s16 pan);
void fn_1_2CB0(s16 no, s16 pan);
void fn_1_2D40(s16 no, s16 pitch);
void fn_1_2DD0(s16 no, s16 vol);
void fn_1_2E60(s16 no, s16 speed);
void fn_1_2F28(s16 no);
void fn_1_2FF0(void);

/* game.c */
extern M555_WORK *lbl_1_bss_3030;

/* stage.c */
void fn_1_1A9A4(M555_WORK *work, M555_MODEL *models, unsigned int *dataTbl);
void fn_1_1ABF0(s16 stageNo);
void fn_1_1AC04(s16 no, unsigned int *data);
void fn_1_1AC24(s16 no, HU3DMOTID *id);
void fn_1_1AC44(void);
void fn_1_1AF38(OMOBJ *obj);
void fn_1_1B2F8(void);
void fn_1_1B4B0(OMOBJ *obj);

#endif
