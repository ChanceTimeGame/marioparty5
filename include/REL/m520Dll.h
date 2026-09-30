#ifndef M520DLL_H
#define M520DLL_H

/*
 * m520Dll (overlay #34): types and prototypes shared by its one translation
 * units (m520).
 *
 * Offsets are GameCube ones from build/mp5-asm/m520Dll. No upstream names exist,
 * so functions keep reference addresses and globals keep lbl_1_* labels.
 */

#include "dolphin/types.h"
#include "game/object.h"
#include "game/hu3d.h"
#include "math.h"
#include "humath.h"

#include "game/mg/seqman.h"
#include "game/mg/actman.h"
#include "game/armem.h"
#include "game/charman.h"
#include "game/gamemes.h"
#include "game/printfunc.h"
#include "game/hu3d.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/init.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "game/audio.h"

#include "dolphin/gx.h"
#include "dolphin/mtx.h"
#include "dolphin/os.h"

/* TODO: work structs. Name every field by hex offset (unk050, unk0B4). */

/* shared structs are defined by the forks (see BRIEF.md ownership table) */

/* lbl_1_bss_1D0[8]: a 3-deep pending sound-effect queue per slot (m535's M535_SE).
 * Slots used at record offsets: [1] fn_1_43BC 0x569C, [4] fn_1_43BC 0x4C6C (+ HuAudFXStop [4].unk010 0x4CF0),
 * [2]/[3] fn_1_43BC 0x5CDC (i == 0 ? 3 : 2),
 * [5] fn_1_90C 0x9A0, [6] fn_1_43BC 0x56F0, [7] fn_1_B70 0x22E8, [0] fn_1_43BC 0x5494;
 * fn_1_5F90 walks all 8 by mulli 0x14; fn_1_7ED8 memsets 0xA0. */
typedef struct m520Se_s {
    /* 0x00 */ s32 unk000; /* pending count; producers push only while < 3 */
    /* 0x04 */ float unk004[3]; /* one float per pending play (stfs 0x68+4*n in fn_1_90C) */
    /* 0x10 */ s32 unk010; /* HuAudFX handle; -1 = none (fn_1_5F90 0x6468, fn_1_43BC 0x4CD4) */
} M520_SE; /* size 0x14 (GC) */

/* lbl_1_bss_270[2]: fn_1_43BC 0x5BDC..0x5E78, fn_1_7ED8 0x86FC..0x87E0. */
typedef struct m520Pair_s {
    /* 0x00 */ s32 unk000; /* lwz/cmpwi 0, stw */
    /* 0x04 */ s32 unk004; /* countdown: lwz, subi 1, stw */
} M520_PAIR; /* size 0x8 (GC) */

/* lbl_1_bss_280[30]: particles. fn_1_43BC spawns (0x58D0..0x5BB4: pos, vel,
 * unk018 = 1 .. 0x21), fn_1_6640 draws (0x6964..0x6F0C), fn_1_B70 tests
 * (0x38A0..0x3900), fn_1_7ED8 memsets 0x348. */
typedef struct m520Particle_s {
    /* 0x00 */ HuVecF unk000; /* position (lfs/stfs 0x0/0x4/0x8) */
    /* 0x0C */ HuVecF unk00C; /* velocity, added to unk000 each frame (fn_1_43BC 0x5B04..0x5B78) */
    /* 0x18 */ s32 unk018; /* 0 = free, else age 1..0x21 (cmpwi 0x21 at 0x5B94) */
} M520_PARTICLE; /* size 0x1C (GC) */

/* lbl_1_bss_5C8: the game state block, memset 0x200 by fn_1_7ED8 (0x860C). */
typedef struct m520Work_s {
    /* 0x000 */ float unk000; /* height offset: fn_1_43BC 0x4DC0/0x4FB8, model Y = 500 + unk000 (0x520C) */
    /* 0x004 */ float unk004; /* no instruction references it */
    /* 0x008 */ float unk008; /* lfs, fn_1_B70 / fn_1_43BC / fn_1_7ED8 (angle, compared to +-180; fn_1_43BC 0x587C particle ring base, degrees) */
    /* 0x00C */ float unk00C; /* lfs, fn_1_698 motion speed 10 + 10 * unk00C; stfs fn_1_B70 */
    /* 0x010 */ s32 unk010; /* frame counter: ++ every fn_1_43BC frame (0x4C0C); % 32 picks particle-spawn frames (0x5788) */
    /* 0x014 */ s32 unk014; /* timer: fn_1_90C 0x970 starts it at 1; fn_1_43BC 0x4D4C += (>0), wraps to 0 at >= 120 */
    /* 0x018 */ s32 unk018; /* timer: fn_1_90C 0x994 starts it at 1; fn_1_43BC 0x4C38 += (>0), wraps to 0 at >= 480; read 45x by fn_1_B70 */
    /* 0x01C */ float unk01C[60]; /* ring written by fn_1_B70 0x203C (stfs 0x1C + 4*unk1FC) */
    /* 0x10C */ float unk10C[60]; /* ring written by fn_1_B70 0x2068 (stfs 0x10C + 4*unk1FC) */
    /* 0x1FC */ s32 unk1FC; /* ring index, ++ then % 60 (fn_1_B70 0x2078..0x208C) */
} M520_WORK; /* size 0x200 (GC) */

/* obj->data of the four lbl_1_bss_1B8 objects: HuMemDirectMallocNum(HEAP_HEAP, 0x54)
 * in fn_1_9CE0 0x9D7C, memset + filled by fn_1_8A98 0x8ADC..0x8C5C, driven by
 * fn_1_B70 (r31). fn_1_43BC/5F90/7ED8 copy the four pointers to a stack array.
 * Fields marked "unmeasured" had no base+offset access found by fork A. */
typedef struct m520Player_s {
    /* 0x00 */ s32 unk000; /* obj->work[0], 0..3 (fn_1_8A98 0x8B4C); index into lbl_1_bss_1A4 */
    /* 0x04 */ s32 unk004; /* player number: the unk000-th player in GwPlayerConf group order; GwPlayer index (coin, fn_1_5F90 0x6570) */
    /* 0x08 */ s32 unk008; /* min(unk00C, 9) (fn_1_8A98 0x8BB8); fn_1_B70 column of its 1P z-offset table [3][10] (0x3F98, 0x40A4), == 3/4 -> -30 on the win pose (0x3D0C) */
    /* 0x0C */ s32 unk00C; /* GwPlayerConf[unk004].character (0x8B90); extsh'd for MgSeqWinnerSet */
    /* 0x10 */ s32 unk010; /* -1 when GwPlayerConf[].iscom, else [].padNo (0x8C08) */
    /* 0x14 */ s32 unk014; /* 0 for a human, else GwPlayerConf[].dif (0x8C44); fn_1_B70 column of its COM [..][4] tables (0x1488, 0x2890) */
    /* 0x18 */ s32 unk018; /* unmeasured */
    /* 0x1C */ s32 unk01C; /* state: = 2 at init (0x8C4C); 3 tested by fn_1_5F90 0x64B8 (all three out -> 1P wins); fn_1_B70 sets 3 when a runner is knocked out (0x34B4, 0x3878, 0x3948) */
    /* 0x20 */ s32 unk020; /* unmeasured */
    /* 0x24 */ s32 unk024; /* unmeasured */
    /* 0x28 */ s32 unk028; /* unmeasured */
    /* 0x2C */ s32 unk02C; /* unmeasured */
    /* 0x30 */ s32 unk030; /* unmeasured */
    /* 0x34 */ float unk034; /* = 1.0f at init (0x8C5C); knock-out hop: fn_1_B70 y += 50 * unk034, then -= 0.04 (0x3BC8..0x3BF0) */
    /* 0x38 */ s32 unk038; /* fn_1_B70 COM state: 1P switch 0/1,2,4,5/3 (0x13F4), runner switch 0/-1,1 (0x2D24) */
    /* 0x3C */ s32 unk03C; /* fn_1_B70 COM frame count in the current unk038 state (++ 0x14C4, 0x2D18) */
    /* 0x40 */ s32 unk040; /* fn_1_B70 COM frame limit for unk03C (stw 0x14BC, cmp 0x2F50) */
    /* 0x44 */ s32 unk044; /* fn_1_B70 1P COM: consecutive unk038 == 2 count (0x17F0) */
    /* 0x48 */ float unk048; /* fn_1_B70 1P COM target turn rate, +-(0.01|0.5|1.0) (0x1948) */
    /* 0x4C */ float unk04C; /* fn_1_B70 runner COM target angle, degrees (0x2D50, 0x2F4C) */
    /* 0x50 */ float unk050; /* fn_1_B70 runner COM target radius (0x31A0) */
} M520_PLAYER; /* size 0x54 (GC) */

/* lbl_1_bss_48: a 3x4 view matrix (PSMTXIdentity + GXLoadPosMtxImm in fn_1_7830
 * 0x78C4) followed by 0x40 bytes no instruction references. */
typedef struct m520MtxBlk_s {
    /* 0x00 */ Mtx unk000;
    /* 0x30 */ u8 unk030[0x40]; /* unreferenced */
} M520_MTXBLK; /* size 0x70 (GC) */

/* esprite.c keeps ESPRITE/ESPANIM file-local, so the overlay redeclares them (m535). */
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

/* sprite.h has this prototype commented out; actman.h does not declare MgActorPosGet. */
void HuSprTexLoad(ANIMDATA *anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);
void MgActorPosGet(MGACTOR *actorP, HuVecF *pos);

/* DOL: no shared header declares it (fn_1_43BC 0x5E1C, fn_1_B70) */
int rand8(void);

/* --- m520.c --- */
void fn_1_A0(void);
void fn_1_698(MGPLAYER *player);
void fn_1_90C(MGPLAYER *player);
void fn_1_A08(MGPLAYER *player);
void fn_1_A94(MGPLAYER *player);
void fn_1_B04(MGPLAYER *player);
void fn_1_B70(OMOBJ *obj);
float fn_1_41F8(float t, float accel, float flat, float decel);
void fn_1_43BC(OMOBJ *obj);
void fn_1_5F48(s16 mode, s16 frameNo);
void fn_1_5F4C(s16 mode, s16 frameNo);
void fn_1_5F50(s16 mode, s16 frameNo);
void fn_1_5F54(s16 mode, s16 frameNo);
void fn_1_5F58(s16 mode, s16 frameNo);
void fn_1_5F5C(s16 mode, s16 frameNo);
void fn_1_5F60(s16 mode, s16 frameNo);
void fn_1_5F90(OMOBJ *obj);
void fn_1_6640(HU3DMODEL *modelP, Mtx *mtx);
void fn_1_7014(HU3DMODEL *modelP, Mtx *mtx);
void fn_1_7830(HU3DMODEL *modelP, Mtx *mtx);
void fn_1_7ED8(OMOBJ *obj);
void *fn_1_8918(s16 charNo, u32 dataNum);
void fn_1_8A98(OMOBJ *obj);
void fn_1_9860(OMOBJ *obj);
void ObjectSetup(void);
void fn_1_9CE0(s16 mode, s16 frameNo);
void fn_1_9E18(s16 mode, s16 frameNo);

#endif
