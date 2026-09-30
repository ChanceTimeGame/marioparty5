#ifndef M505DLL_H
#define M505DLL_H

/*
 * m505dll (overlay #19): types and prototypes for its one translation
 * unit (m505).
 *
 * Offsets are GameCube ones from build/mp5-asm/m505dll. No upstream names exist,
 * so functions keep reference addresses and globals keep lbl_1_* labels.
 */

#include "dolphin/types.h"
#include "game/object.h"
#include "game/hu3d.h"
#include "math.h"
#include "humath.h"

#include "game/mg/seqman.h"

#include "dolphin/gx.h"
#include "game/sprite.h"

/* Record types (fork S). Offsets are GameCube ones; every field comment cites
 * the access evidence (op, and one reference address). Widths/signedness are
 * measured by following the base register through the whole reference asm
 * (all functions), not only the owner's. Pointer-free records keep their GC
 * size on the host; index the typed arrays, never a hard-coded stride. */

/* Player object work: obj->data of the four player objects (ObjectSetup
 * 0x11F98 HuMemDirectMallocNum(0, 0x68)); objects in lbl_1_bss_2ED38[4].
 * Initialised by fn_1_11650 (memset 0x68), updated by fn_1_1828. */
typedef struct M505_PWORK_s {
    /* 0x00 */ s32 unk000;   /* player number = obj->work[0] (lwz/stw 0x11700; cmpw vs loop idx 0x1E8C) */
    /* 0x04 */ s32 unk004;   /* player number: GwPlayerConf/GwPlayer index (0x11714; EF6C 0xF940 mgCoinBonus); omVibrate(extsh) 0x3850 */
    /* 0x08 */ s32 unk008;   /* character, clamped <= 9 (0x11760); index of the 10-entry tables 0x3720 */
    /* 0x0C */ s32 unk00C;   /* charNo: CharFXPlay/CharModelVoicePanSet (extsh) 0x3960, 0x4ED0 */
    /* 0x10 */ s32 unk010;   /* pad number, -1 = COM (0x117A4; cmpwi -1 0x198C) */
    /* 0x14 */ s32 unk014;   /* COM difficulty (0x117D4); table index 0x1BF8 */
    /* 0x18 */ s32 unk018;   /* not accessed (memset only) */
    /* 0x1C */ s32 unk01C;   /* current motion slot (stw 0x3FF4, cmpw 0x3F50) */
    /* 0x20 */ s32 unk020;   /* forced motion slot, -1 = none (0x11874, lwz 0x3F2C) */
    /* 0x24 */ s32 unk024;   /* mode: 1 run, 2 fall/out, 3 ... (cmpwi 0x1970, stw 0x3630) */
    /* 0x28 */ s32 unk028;   /* mode timer (lwz 0x26B4, stw 0x3644, ++ 0x370C) */
    /* 0x2C */ float unk02C; /* lfs/stfs 0x2684, 0x3868 */
    /* 0x30 */ float unk030; /* stfs 0x29B0 (stick magnitude) */
    /* 0x34 */ float unk034; /* velocity x (stfs 0x1968, 0x2960; lfs 0x2A40) */
    /* 0x38 */ float unk038; /* velocity y (lfs/stfs 0x3740) */
    /* 0x3C */ float unk03C; /* velocity z (stfs 0x1964, lfs 0x2A50) */
    /* 0x40 */ float unk040; /* head angle (stfs 0x4994, 0x4A80) */
    /* 0x44 */ float unk044; /* previous trans.x (stfs 0x1954; other player 0x4E60) */
    /* 0x48 */ s32 unk048;   /* last motion id (lwz 0x4140, stw 0x47A4) */
    /* 0x4C */ float unk04C; /* last motion time (lfs 0x4460, stfs 0x47AC) */
    /* 0x50 */ s32 unk050;   /* COM stick x (stw 0x2490, lwz 0x2440) */
    /* 0x54 */ s32 unk054;   /* COM stick y (stw 0x24F0, lwz 0x24A0) */
    /* 0x58 */ s32 unk058;   /* COM steer direction -1/0/1 (lwz 0x2108, stw 0x2670) */
    /* 0x5C */ s32 unk05C;   /* COM reaction delay, rand8()%64 (0x1180C; lwz 0x1A20) */
    /* 0x60 */ s32 unk060;   /* COM dodge direction (stw 0x2198, lwz 0x1F84) */
    /* 0x64 */ s32 unk064;   /* COM dodge timer (stw 0x21AC, lwz 0x1F78) */
} M505_PWORK; /* size 0x68 (GC) */

/* One element of M505_HAZARD.unk03C[]: only +0x15 is ever accessed (stb 0 in
 * fn_1_FADC 0x11044, `mulli 0x18` over 96 elements). */
typedef struct M505_HAZARDSUB_s {
    /* 0x00 */ u8 unk000[0x15]; /* not accessed */
    /* 0x15 */ u8 unk015;       /* stb 0x11044 */
    /* 0x16 */ u8 unk016[2];    /* not accessed */
} M505_HAZARDSUB; /* size 0x18 (GC) */

/* lbl_1_bss_9D1C[64] (was M505_R940): moving objects the players avoid (the
 * COM steers around them, fn_1_1828 pushes players out of radius 50+40/150).
 * Name is a guess; layout is measured. */
typedef struct M505_HAZARD_s {
    /* 0x000 */ float unk000;  /* pos x: lfs x38 stfs x9 (0x1CA8) */
    /* 0x004 */ float unk004;  /* pos y: lfs x8 stfs x3 (0x76C8) */
    /* 0x008 */ float unk008;  /* pos z: lfs x21 stfs x5 (0x1B0C) */
    /* 0x00C */ float unk00C;  /* lfs x26 stfs x13 (0x5260) */
    /* 0x010 */ float unk010;  /* lfs x11 stfs x5 (0x524C) */
    /* 0x014 */ float unk014;  /* lfs x3 stfs x3 (0x5238) */
    /* 0x018 */ float unk018;  /* copy of pos x (FADC 0x10FB4) */
    /* 0x01C */ float unk01C;  /* copy of pos y (FADC 0x10FDC) */
    /* 0x020 */ float unk020;  /* copy of pos z (FADC 0x11004) */
    /* 0x024 */ float unk024;  /* lfs x12 stfs x3 (0x7FF0) */
    /* 0x028 */ s32 unk028;    /* state, < 0 = unused: lwz x15 stw x5, cmpwi (0x1AE4) */
    /* 0x02C */ u8 unk02C;     /* kind 0/1 (size; texture set): lbz x69 stb x2, cmplwi (0x1B44) */
    /* 0x02D */ u8 unk02D;     /* lbz x1 stb x2 (0xA048) */
    /* 0x02E */ u8 unk02E;     /* texture index: lbz x29 stb x5 (0x51C8, 0xCF10) */
    /* 0x02F */ u8 pad02F;
    /* 0x030 */ s16 unk030;    /* lha x24 sth x9 (0x5200, 0xD490) */
    /* 0x032 */ s16 unk032;    /* lha x5 sth x8 (0x5218) */
    /* 0x034 */ s16 unk034;    /* sth x1 (0x10D98) */
    /* 0x036 */ s8 unk036;     /* lbz+extsb x18, stb x3 (0x528C) */
    /* 0x037 */ u8 unk037;     /* lbz x6 stb x8 (0x5278) */
    /* 0x038 */ u8 unk038;     /* stb x1 (0x1101C) */
    /* 0x039 */ u8 pad039[3];
    /* 0x03C */ M505_HAZARDSUB unk03C[96]; /* stride 0x18 (0x1103C) */
    /* 0x93C */ u8 unk93C;     /* lbz x2 stb x3 (0xA100, 0xCF88) */
    /* 0x93D */ u8 pad93D[3];
} M505_HAZARD; /* size 0x940 (GC) */

/* lbl_1_bss_1F7C[640] (was M505_R30): dust particles spawned at a player's feet
 * (fn_1_1828 0x4178..0x4404, 0x44B4..0x4790). */
typedef struct M505_PARTICLE_s {
    /* 0x00 */ float unk000;  /* pos x: stfs 0x4230 */
    /* 0x04 */ float unk004;  /* not accessed */
    /* 0x08 */ float unk008;  /* pos z: stfs 0x42A4 */
    /* 0x0C */ float unk00C;  /* stfs 0x4374 */
    /* 0x10 */ float unk010;  /* stfs 0x4398 */
    /* 0x14 */ float unk014;  /* stfs 0x43CC */
    /* 0x18 */ float unk018;  /* stfs 0x42C8 */
    /* 0x1C */ float unk01C;  /* stfs 0x42EC */
    /* 0x20 */ float unk020;  /* stfs 0x4310 */
    /* 0x24 */ float unk024;  /* stfs 0x4334 */
    /* 0x28 */ u8 unk028;     /* stb x4 lbz x3 (0x4404) */
    /* 0x29 */ u8 unk029;     /* stb x3 lbz x4 (0x43EC) */
    /* 0x2A */ u8 pad02A[2];
    /* 0x2C */ s32 unk02C;    /* type, -1 = free: lwz x8 stw x6, cmpwi -1 (0x4188) */
} M505_PARTICLE; /* size 0x30 (GC) */

/* lbl_1_bss_11FC[96] (was M505_R24): used by fn_1_4FB4/fn_1_D9E0/fn_1_FADC. */
typedef struct M505_R24_s {
    /* 0x00 */ float unk000;  /* lfs x4 stfs x4 (0x6BE0) */
    /* 0x04 */ float unk004;  /* lfs x9 stfs x5 (0x6C00) */
    /* 0x08 */ float unk008;  /* lfs x5 stfs x3 (0x6C6C) */
    /* 0x0C */ float unk00C;  /* lfs x4 stfs x3 (0x6C8C) */
    /* 0x10 */ s8 unk010;     /* lbz(+extsb x3) x4 stb x3 (0x6CC4, 0x6F34) */
    /* 0x11 */ u8 pad011[3];
    /* 0x14 */ float unk014;  /* lfs x2 stfs x2 (0x6CE4) */
    /* 0x18 */ u8 unk018;     /* lbz x1 stb x3 (0x6CFC); vertex alpha in fn_1_D9E0 (lbz 0xE878) */
    /* 0x19 */ u8 unk019;     /* lbz x4 stb x4 (0x6DD8); frame in bss_11AC[2 + unk01A] (x bss_11EC, D9E0 lbz 0xE8C8) */
    /* 0x1A */ u8 unk01A;     /* lbz x11 stb x2 (0x6D2C); size kind: 0 = 40x40 tex / half 20, else 24x24 / 12 (D9E0 lbz 0xE750) */
    /* 0x1B */ u8 pad01B;
    /* 0x1C */ s32 unk01C;    /* state, < 0 = free: lwz x4 stw x5, cmpwi 0 (0xE6CC) */
    /* 0x20 */ s8 unk020;     /* lbz+extsb x7 stb x3 (0x6DF0, 0xE6E8); drawn by fn_1_D9E0 only while < 0 */
    /* 0x21 */ u8 pad021[3];
} M505_R24; /* size 0x24 (GC) */

/* lbl_1_bss_977C[72] (was M505_R14): landing marks spawned by fn_1_1828 0x37A0. */
typedef struct M505_MARK_s {
    /* 0x00 */ float unk000;  /* pos x: lfs x3 stfs x2 (0x37FC) */
    /* 0x04 */ float unk004;  /* lfs x1 (0xDF30) */
    /* 0x08 */ float unk008;  /* pos z: lfs x3 stfs x2 (0x3814) */
    /* 0x0C */ u8 unk00C;     /* lbz x6 stb x2 (0x382C) */
    /* 0x0D */ u8 pad00D[3];
    /* 0x10 */ s32 unk010;    /* type, -1 = free: lwz x8 stw x5 (0x37B0); texture row 0xE108 */
} M505_MARK; /* size 0x14 (GC) */

/* lbl_1_bss_2ED50[11] (was s32[88]): per-sound-effect request slots (fork B's M505_SE, drained by fn_1_EF6C). unk000
 * indexes the two parallel arrays (fn_1_1828 0x38F0: [10].unk004[n] = x,
 * [10].unk010[n] = 1, n++; fn_1_EF6C plays and pans them). Name is a guess. */
typedef struct M505_SE_s {
    /* 0x00 */ s32 unk000;    /* count: lwz x10 stw x3 (0x85C0, 0x38F8) */
    /* 0x04 */ float unk004[3]; /* stfs/lfs [n] (0x3924, 0x8674) */
    /* 0x10 */ s32 unk010[3];   /* stw/lwz [n] (0x3948, 0x8710) */
    /* 0x1C */ s32 unk01C;    /* stw x1 (0xF0A8) */
} M505_SE; /* size 0x20 (GC) */

/* lbl_1_bss_18[72] / lbl_1_bss_918[64] (were M505_R20): GXTexObj (0x20), passed to
 * GXInitTexObj/GXLoadTexObj (0xCF4C, 0xE12C). lbl_1_bss_1158[4][4] /
 * lbl_1_bss_11AC[4][4] (were M505_R10): texture buffers from HuMemDirectMallocNum
 * (stw 0x108CC, 0x10924) -- pointers, `u8 *[4][4]` (fork B). */

typedef struct esprite_s {
    /* 0x00 */ s16 memberNo;
    /* 0x02 */ s16 animNo;
} ESPRITE;

typedef struct espanim_s {
    /* 0x00 */ unsigned int dataNum;
    /* 0x04 */ u16 useCnt;
    /* 0x08 */ ANIMDATA *anim;
} ESPANIM;

extern ESPRITE esprite[];
extern ESPANIM espanim[];

/* sprite.h has this prototype commented out. */
void HuSprTexLoad(ANIMDATA *anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);

int rand8(void);

/* Host-only hardening of retail hazards (NOTES.md "Host-only divergences"). On GC each
 * macro is the retail expression and the matching build is unchanged; on the host it
 * makes an out-of-bounds read, a divide by zero or an out-of-range pan well-defined. */
#define M505_PC_OK(cond) 1
#define M505_Div(a, b) ((a) / (b))
#define M505_Mod(a, b) ((a) % (b))
#define M505_PanF(pan) (pan)

/* --- m505.c --- */
/* extern lbl_1_data_0; */
/* extern lbl_1_data_3C; */
/* extern lbl_1_data_6C; */
/* extern lbl_1_data_72; */
/* extern lbl_1_data_78; */
/* extern lbl_1_data_7C; */
/* extern lbl_1_data_80; */
/* extern lbl_1_data_84; */
/* extern lbl_1_data_88; */
/* extern lbl_1_data_8C; */
/* extern lbl_1_data_90; */
/* extern lbl_1_data_D0; */
/* extern lbl_1_data_F0; */
/* extern lbl_1_data_108; */
/* extern lbl_1_data_111; */
/* extern lbl_1_data_112; */
/* extern lbl_1_data_115; */
/* extern lbl_1_data_119; */
/* extern lbl_1_data_11C; */
/* extern lbl_1_data_124; */
/* extern lbl_1_data_128; */
/* extern lbl_1_data_12C; */
/* extern lbl_1_data_134; */
/* extern lbl_1_data_14F; */
/* extern lbl_1_rodata_10; */
/* extern lbl_1_rodata_11; */
/* extern lbl_1_rodata_14; */
/* extern lbl_1_rodata_15; */
/* extern lbl_1_rodata_18; */
/* extern lbl_1_rodata_1C; */
/* extern lbl_1_rodata_20; */
/* extern lbl_1_rodata_24; */
/* extern lbl_1_rodata_28; */
/* extern lbl_1_rodata_30; */
/* extern lbl_1_rodata_38; */
/* extern lbl_1_rodata_40; */
/* extern lbl_1_rodata_48; */
/* extern lbl_1_rodata_50; */
/* extern lbl_1_rodata_58; */
/* extern lbl_1_rodata_60; */
/* extern lbl_1_rodata_68; */
/* extern lbl_1_rodata_70; */
/* extern lbl_1_rodata_78; */
/* extern lbl_1_rodata_A0; */
/* extern lbl_1_rodata_D0; */
/* extern lbl_1_rodata_E0; */
/* extern lbl_1_rodata_EC; */
/* extern lbl_1_rodata_F4; */
/* extern lbl_1_rodata_694; */
/* extern lbl_1_rodata_6BC; */
/* extern lbl_1_rodata_6C0; */
/* extern lbl_1_rodata_6C4; */
/* extern lbl_1_rodata_6C8; */
/* extern lbl_1_rodata_6CC; */
/* extern lbl_1_rodata_6D0; */
/* extern lbl_1_rodata_6D4; */
/* extern lbl_1_rodata_6D8; */
/* extern lbl_1_rodata_6E0; */
/* extern lbl_1_rodata_6E8; */
/* extern lbl_1_rodata_6EC; */
/* extern lbl_1_rodata_6F0; */
/* extern lbl_1_rodata_6F4; */
/* extern lbl_1_rodata_6F8; */
/* extern lbl_1_rodata_700; */
/* extern lbl_1_rodata_708; */
/* extern lbl_1_rodata_710; */
/* extern lbl_1_rodata_714; */
/* extern lbl_1_rodata_718; */
/* extern lbl_1_rodata_71C; */
/* extern lbl_1_rodata_720; */
/* extern lbl_1_rodata_724; */
/* extern lbl_1_rodata_728; */
/* extern lbl_1_rodata_72C; */
/* extern lbl_1_rodata_730; */
/* extern lbl_1_rodata_734; */
/* extern lbl_1_rodata_738; */
/* extern lbl_1_rodata_73C; */
/* extern lbl_1_rodata_740; */
/* extern lbl_1_rodata_748; */
/* extern lbl_1_rodata_74C; */
/* extern lbl_1_rodata_750; */
/* extern lbl_1_rodata_754; */
/* extern lbl_1_rodata_758; */
/* extern lbl_1_rodata_75C; */
/* extern lbl_1_rodata_760; */
/* extern lbl_1_rodata_768; */
/* extern lbl_1_rodata_76C; */
/* extern lbl_1_rodata_770; */
/* extern lbl_1_rodata_774; */
/* extern lbl_1_rodata_778; */
/* extern lbl_1_rodata_77C; */
/* extern lbl_1_rodata_780; */
/* extern lbl_1_rodata_784; */
/* extern lbl_1_rodata_788; */
/* extern lbl_1_rodata_78C; */
/* extern lbl_1_rodata_790; */
/* extern lbl_1_rodata_798; */
/* extern lbl_1_rodata_79C; */
/* extern lbl_1_rodata_7A0; */
/* extern lbl_1_rodata_7A8; */
/* extern lbl_1_rodata_7B0; */
/* extern lbl_1_rodata_7C0; */
/* extern lbl_1_rodata_7D8; */
/* extern lbl_1_rodata_7F0; */
/* extern lbl_1_rodata_7F8; */
/* extern lbl_1_rodata_848; */
/* extern lbl_1_rodata_898; */
/* extern lbl_1_rodata_89C; */
/* extern lbl_1_rodata_8A0; */
/* extern lbl_1_rodata_8A4; */
/* extern lbl_1_rodata_8A8; */
/* extern lbl_1_rodata_8AC; */
/* extern lbl_1_rodata_8B0; */
/* extern lbl_1_rodata_8B4; */
/* extern lbl_1_rodata_8B8; */
/* extern lbl_1_rodata_8BC; */
/* extern lbl_1_rodata_8C0; */
/* extern lbl_1_rodata_8C8; */
/* extern lbl_1_rodata_8D0; */
/* extern lbl_1_rodata_8D8; */
/* extern lbl_1_rodata_8E0; */
/* extern lbl_1_rodata_8E4; */
/* extern lbl_1_rodata_8E8; */
/* extern lbl_1_rodata_8EC; */
/* extern lbl_1_rodata_8F0; */
/* extern lbl_1_rodata_8F4; */
/* extern lbl_1_rodata_8F8; */
/* extern lbl_1_rodata_8FC; */
/* extern lbl_1_rodata_900; */
/* extern lbl_1_rodata_904; */
/* extern lbl_1_rodata_908; */
/* extern lbl_1_rodata_90C; */
/* extern lbl_1_rodata_910; */
/* extern lbl_1_rodata_914; */
/* extern lbl_1_rodata_918; */
/* extern lbl_1_rodata_91C; */
/* extern lbl_1_rodata_920; */
/* extern lbl_1_rodata_924; */
/* extern lbl_1_rodata_928; */
/* extern lbl_1_rodata_930; */
/* extern lbl_1_rodata_938; */
/* extern lbl_1_rodata_93C; */
/* extern lbl_1_rodata_940; */
/* extern lbl_1_rodata_948; */
/* extern lbl_1_rodata_94C; */
/* extern lbl_1_rodata_950; */
/* extern lbl_1_rodata_958; */
/* extern lbl_1_rodata_960; */
/* extern lbl_1_rodata_968; */
/* extern lbl_1_rodata_970; */
/* extern lbl_1_rodata_978; */
/* extern lbl_1_rodata_980; */
/* extern lbl_1_rodata_988; */
/* extern lbl_1_rodata_98C; */
/* extern lbl_1_rodata_990; */
/* extern lbl_1_rodata_998; */
/* extern lbl_1_rodata_9A0; */
/* extern lbl_1_rodata_9A8; */
/* extern lbl_1_rodata_9B0; */
/* extern lbl_1_rodata_9B8; */
/* extern lbl_1_rodata_9C0; */
/* extern lbl_1_rodata_9C8; */
/* extern lbl_1_rodata_9D0; */
/* extern lbl_1_rodata_9D8; */
/* extern lbl_1_rodata_9E0; */
/* extern lbl_1_rodata_9E4; */
/* extern lbl_1_rodata_9E8; */
/* extern lbl_1_rodata_9F0; */
/* extern lbl_1_rodata_9F8; */
/* extern lbl_1_rodata_A00; */
/* extern lbl_1_rodata_A08; */
/* extern lbl_1_rodata_A0C; */
/* extern lbl_1_rodata_A0D; */
/* extern lbl_1_rodata_A10; */
/* extern lbl_1_rodata_A14; */
/* extern lbl_1_rodata_A18; */
/* extern lbl_1_rodata_A19; */
/* extern lbl_1_rodata_A1C; */
/* extern lbl_1_rodata_A28; */
/* extern lbl_1_rodata_A2C; */
/* extern lbl_1_rodata_A30; */
/* extern lbl_1_rodata_A34; */
/* extern lbl_1_rodata_A64; */
/* extern lbl_1_rodata_B24; */
/* extern lbl_1_rodata_B44; */
/* extern lbl_1_rodata_B50; */
/* extern lbl_1_rodata_B5C; */
/* extern lbl_1_rodata_B68; */
/* extern lbl_1_rodata_B74; */
/* extern lbl_1_rodata_B78; */
/* extern lbl_1_rodata_B7C; */
/* extern lbl_1_rodata_B80; */
/* extern lbl_1_rodata_B84; */
/* extern lbl_1_rodata_BB4; */
/* extern lbl_1_rodata_BC0; */
/* extern lbl_1_rodata_BCC; */
/* extern lbl_1_rodata_BD0; */
/* extern lbl_1_rodata_BD8; */
/* extern lbl_1_rodata_BE0; */
/* extern lbl_1_rodata_BE8; */
/* extern lbl_1_rodata_BEC; */
/* extern lbl_1_rodata_C18; */
/* extern lbl_1_rodata_C28; */
/* extern lbl_1_rodata_C2C; */
/* extern lbl_1_rodata_C30; */
/* extern lbl_1_rodata_C34; */
/* extern lbl_1_rodata_C40; */
/* extern lbl_1_rodata_C4C; */
/* extern lbl_1_rodata_C54; */
/* extern lbl_1_rodata_C5C; */
/* extern lbl_1_rodata_C64; */
/* extern lbl_1_rodata_C6C; */
/* extern lbl_1_rodata_C74; */
/* extern lbl_1_rodata_C7C; */
/* extern lbl_1_rodata_C84; */
/* extern lbl_1_rodata_C9C; */
/* extern lbl_1_rodata_CAC; */
/* extern lbl_1_rodata_CB4; */
/* extern lbl_1_rodata_CB8; */
/* extern lbl_1_rodata_CBC; */
/* extern lbl_1_rodata_CC0; */
/* extern lbl_1_rodata_CC4; */
/* extern lbl_1_rodata_CC8; */
/* extern lbl_1_rodata_CD0; */
/* extern lbl_1_rodata_CD8; */
/* extern lbl_1_rodata_CDC; */
/* extern lbl_1_rodata_CE0; */
/* extern lbl_1_rodata_CE4; */
/* extern lbl_1_rodata_CE8; */
/* extern lbl_1_rodata_CF8; */
/* extern lbl_1_rodata_D04; */
/* extern lbl_1_rodata_D10; */
/* extern lbl_1_rodata_D11; */
/* extern lbl_1_rodata_D14; */
/* extern lbl_1_rodata_D18; */
/* extern lbl_1_rodata_D1C; */
/* extern lbl_1_rodata_D20; */
/* extern lbl_1_rodata_D28; */
/* extern lbl_1_rodata_D30; */
/* extern lbl_1_rodata_D38; */
/* extern lbl_1_rodata_D3C; */
/* extern lbl_1_rodata_D40; */
void fn_1_0(HU3DMODEL *modelP, Mtx *mtx);
void fn_1_A90(HU3DMODEL *modelP, Mtx *mtx);
void fn_1_1284(void);
void fn_1_1828(OMOBJ *obj);
void fn_1_4FB4(OMOBJ *obj);
void fn_1_B694(HU3DMODEL *modelP, Mtx *mtx);
void fn_1_BD58(HU3DMODEL *modelP, Mtx *mtx);
void fn_1_C0BC(HU3DMODEL *modelP, Mtx *mtx);
void fn_1_D9E0(HU3DMODEL *modelP, Mtx *mtx);
void fn_1_EF6C(OMOBJ *obj);
void fn_1_FADC(OMOBJ *obj);
void fn_1_11650(OMOBJ *obj);
void fn_1_119A0(OMOBJ *obj);
void ObjectSetup(void);
void fn_1_12078(OMOBJ *obj);
void fn_1_120D0(OMOBJ *obj);

#endif
