#ifndef M515DLL_H
#define M515DLL_H

/*
 * m515dll (overlay #29): types and prototypes for its single translation
 * unit (m515).
 *
 * Offsets are GameCube ones from build/mp5-asm/m515Dll. No upstream names exist,
 * so functions keep reference addresses and globals keep lbl_1_* labels.
 */

#include "dolphin/types.h"
#include "game/object.h"
#include "game/hu3d.h"
#include "humath.h"

#include "game/mg/seqman.h"
#include "game/mg/actman.h"

/* TODO: work structs. Name every field by hex offset (unk050, unk0B4). */

/* merged by structmerge.py from forks ABCDEFGHIJK: owner fields + every other fork's fields by offset */

typedef struct M515_CAMMOVE_s M515_CAMMOVE;
typedef struct M515_MOVER_s M515_MOVER;
typedef struct M515_NODE_s M515_NODE;
typedef struct M515_SEQ_s M515_SEQ;
typedef struct M515_SPLIT_s M515_SPLIT;
typedef struct M515_WORK_s M515_WORK;
typedef struct M515_AI_s M515_AI;
typedef struct M515_CELL_s M515_CELL;
typedef struct M515_LANE_s M515_LANE;
typedef struct M515_PLAYERMDL_s M515_PLAYERMDL;
typedef struct M515_PSUB_s M515_PSUB;
typedef struct M515_PLAYER_s M515_PLAYER;
typedef struct M515_ITEM_s M515_ITEM;
typedef struct M515_LAYOUT_s M515_LAYOUT;

typedef s32 (*M515_PLAYERFUNC)(M515_SEQ *seq, M515_PLAYER *p);

struct M515_CAMMOVE_s {
    HuVecF unk00;  /* lfs/stfs 0x0,0x4,0x8   -- interpolated eye */
    HuVecF unk0C;  /* lfs/stfs 0xc,0x10,0x14 -- interpolated target */
    HuVecF unk18;  /* lwz/stw 12-byte struct copy of unk0C */
    s16 unk24;  /* lha + cmpwi          -- s16 */
    s16 unk26;  /* lha + cmpwi          -- s16 */
    s16 unk28;  /* fF */
    s16 unk2A;  /* fF */
    s32 unk2C;  /* fF */
}; /* size 0x30 (f?) */

struct M515_MOVER_s {
    s32 unk00;  /* lwz/stw + cmpwi 0/1/3 in fn_1_D0D8 -> s32 */
    s32 unk04;  /* lwz + cmpw against unk08 -> s32 */
    s32 unk08;  /* lwz/stw, ++ -> s32 */
    HU3DMODELID unk0C;  /* lhax then Hu3DModelAttrSet/PosSet -> s16 */
    u8 unk0E[0x10 - 0x0E];  /* fA */
    float unk10;  /* lfsx/stfsx */
    float unk14;  /* not reached in fork A's range */
    float unk18;  /* lfsx/stfsx */
    HuVecF unk1C;  /* 0x1C/0x20/0x24, 3-word copy in fn_1_CE98 */
}; /* size 0x28 (f?) */

struct M515_NODE_s {
    HU3DMODELID unk000;
    HU3DMOTID unk002;
    s16 unk004;
    s16 unk006;
    s32 (*unk008)(M515_NODE *node);
    M515_NODE * unk00C;
    M515_NODE * unk010;
}; /* size 0x14 (f?) */

struct M515_SEQ_s {
    s16 state;  /* lha + cmplwi 0x13 switch, sth: s16 */
    s16 timer;  /* lha/sth: s16 */
    M515_CAMMOVE * owner;  /* stw, passed as func's only argument */
    s32 (*func)(M515_CAMMOVE *);  /* stw/lwz + bctrl, result tested with cmpwi */
    s32 index;  /* stw (4 bytes) of fn_1_29D0's s32 loop counter: s32 */
}; /* size 0x10 (f?) */

struct M515_SPLIT_s {
    s16 unk00;  /* lha before espKill/espPosSet: s16 espId */
    s16 unk02;  /* lha: s16 espId */
    float unk04;  /* lfs/stfs: float (split X) */
    float unk08;  /* lfs/stfs: float (split Y) */
    float unk0C;  /* stfs only: float */
}; /* size 0x10 (f?) */

struct M515_WORK_s {
    s16 unk000;  /* sth 0 in fn_1_2B6C */
    s16 unk002[3];  /* sthx rand8()/26 in fn_1_2F3C */
    HU3DMODELID unk008;  /* fD */
    HU3DMODELID unk00A;  /* fD */
    HU3DMODELID unk00C;  /* fD */
    HU3DMODELID unk00E[4];  /* fD */
    HU3DMODELID unk016[4];  /* fD */
    HU3DMODELID unk01E[4];  /* fD */
    HU3DMODELID unk026[4];  /* fD */
    HU3DMODELID unk02E[4];  /* fD */
    HU3DMODELID unk036[4];  /* fD */
    HU3DMODELID unk03E[4];  /* fD */
    HU3DMODELID unk046[4];  /* fD */
    HU3DMODELID unk04E[4];  /* fD */
    HU3DMODELID unk056[4];  /* fD */
    HU3DMODELID unk05E[4][2];  /* fD */
    HU3DMODELID unk06E[4];  /* fD */
    HU3DMODELID unk076[4][4];  /* fD */
    HU3DMODELID unk096[4][2];  /* fD */
    HU3DMODELID unk0A6[4];  /* fD */
    HU3DMODELID unk0AE[4];  /* fD */
    HU3DMODELID unk0B6[4][3];  /* fD */
    HU3DMODELID unk0CE[4];  /* fD */
    HU3DMODELID unk0D6;  /* fD */
    HU3DMODELID unk0D8;  /* fD */
    HU3DMODELID unk0DA;  /* fD */
    s16 unk0DC;  /* sth -1 in fn_1_2F3C */
    s16 unk0DE;  /* sth -1 */
    s16 unk0E0[8];  /* sthx -1, i < 8 */
    s16 unk0F0[14];  /* lha/sth pairs in fn_1_32C4 */
    s16 unk10C[17];  /* sthx -1, i < 0x11 */
    u8 unk12E[0x130 - 0x12E];
    M515_MOVER unk130[4];
    s16 unk1D0;  /* lha + switch, ++ -> s16 */
    s16 unk1D2;  /* lha + cmpwi, ++ -> s16 */
    s16 unk1D4;  /* sth 0/1 */
    s16 unk1D6;  /* lha + cmpwi 0 (signed, -1) -> s16 */
    s16 unk1D8;  /* sth 0 in fn_1_2F3C */
    s16 unk1DA;  /* lha + cmplwi 6 switch, ++ -> s16 */
    s16 unk1DC[4][3];  /* sthx 0, i<4 (x6) j<3 (x2) */
    s32 unk1F4;  /* stw 0 / stw 1 -> s32 */
    s16 unk1F8[6];  /* lhax/sthx shuffle in fn_1_2F3C */
    s16 unk204[6];
    s16 unk210[6];
    s16 unk21C;  /* lha/sth */
    s16 unk21E;
    s16 unk220;
    u8 unk222[0x224 - 0x222];
    M515_PLAYER * player[4];  /* the four player works */
    M515_CAMMOVE unk234[4];
    M515_SEQ unk2F4[4];  /* fB */
    M515_SPLIT unk334;
    M515_NODE * unk344;  /* fE */
    M515_NODE * unk348;  /* fE */
    M515_NODE unk34C[120];  /* fE */
    s16 unkCAC;  /* sth 0/1, lha in fn_1_7878 */
    u8 unkCAE[0xCB0 - 0xCAE];
}; /* size 0xCB0 (f?) */

struct M515_AI_s {
    s16 unk00;  /* fH */
    s16 unk02;  /* fH */
    s16 unk04;  /* fH */
    s16 unk06;  /* fH */
    s16 unk08;  /* fH */
    u8 pad00A[0x2];
    u16 * unk0C;  /* fH */
}; /* size 0x10 (f?) */

struct M515_CELL_s {
    M515_CELL * unk000;  /* +col neighbour */  /* fC */
    M515_CELL * unk004;  /* -col neighbour */  /* fC */
    M515_CELL * unk008;  /* +row neighbour */  /* fC */
    M515_CELL * unk00C;  /* -row neighbour */  /* fC */
    s32 unk010;  /* fC */
    M515_PSUB * unk014;  /* lwz */  /* fC */
    HuVecF unk018;  /* position */  /* fC */
    u16 unk024;  /* lhz + cmplwi -> unsigned */  /* fC */
    u16 unk026;  /* fC */
}; /* size 0x28 (f?) */

struct M515_LANE_s {
    HU3DMODELID unk000[25];  /* lha/lhax + cmpwi 0 / blt: signed */  /* fH */
}; /* size 0x32 (f?) */

struct M515_PLAYERMDL_s {
    HU3DMODELID unk000;  /* fE */
    s16 unk002;  /* fE */
    HU3DMODELID unk004;  /* fE */
    u8 unk006[0x20 - 0x06];  /* fE */
    s16 unk020;  /* fE */
    u8 unk022[0x28 - 0x22];  /* fE */
    float unk028;  /* fE */
}; /* size 0x2C (f?) */

struct M515_PSUB_s {
    HU3DMODELID unk00;  /* lhax, Hu3DModelCreate result (0x6A2C) */
    HU3DMOTID unk02;
    HU3DMODELID unk04;  /* lhax, Hu3DModelAttrSet target */
    s16 unk06;
    HuVecF unk08;  /* fn_1_6FE8 copies cell->unk018 here */
    HuVecF unk14;  /* fn_1_6FE8 copies cell->unk018 here too */
    s16 unk20;
    s16 unk22;
    s16 unk24;  /* lha; fn_1_1D60 writes rand8()/86 + 1 */
    s16 unk26;
    float unk28;
}; /* size 0x2C (f?) */

struct M515_PLAYER_s {
    s16 unk000;  /* lha; obj->work[0], 0..3 */
    s16 unk002;  /* lha; GwPlayerConf[].charNo */
    s16 unk004;  /* lha; GwPlayerConf[].padNo */
    s16 unk006;
    s16 unk008;
    s16 unk00A;  /* lha; GwPlayerConf[].type */
    s16 unk00C;  /* lha; GwPlayerConf[].dif */
    s16 unk00E;  /* lha; stage index into work->unk002 */
    M515_CELL unk010[5][5];
    M515_CELL * unk3F8;
    M515_CELL unk3FC;  /* spare cell below cell[4][2] */
    M515_CELL unk424;  /* spare cell above cell[0][2] */
    HuVecF unk44C;  /* omSetTra source */
    HuVecF unk458;  /* omSetRot source */
    HuVecF unk464;  /* 2+1 word copy into unk470 */
    HuVecF unk470;
    s16 unk47C;  /* lha + cmpwi: s16 */
    s16 unk47E;  /* sth: s16 */
    s16 unk480;
    s16 unk482;  /* lha + cmpwi -> signed; state */
    s16 unk484;  /* sth 0 */
    s16 unk486;  /* lha + cmpwi: s16 */
    M515_PSUB unk488[8];
    s16 unk5E8;  /* lha; live count of unk488 */
    M515_LANE unk5EA[3];  /* fork J: 3 x 0x32 = 0x5EA..0x67F exactly */  /* fH */
    u16 unk680;  /* lhz + cmplwi -> unsigned */
    s16 unk682;  /* lha + cmpwi -> signed */
    M515_SEQ * unk684;
    M515_PLAYERFUNC unk688;  /* lwz -> mtctr/bctrl */
    OMOBJ * unk68C;  /* lwz -> omSetTra/omSetRot */
    M515_AI unk690;  /* fork K */  /* fH */
}; /* size 0x6A0 (f?) */

struct M515_ITEM_s {
    s16 unk000;  /* fE */
    HU3DMOTID unk002;  /* fE */
    u8 unk004[0x08 - 0x04];  /* fE */
    HuVecF unk008;  /* fE */
    HuVecF unk014;  /* fE */
    s16 unk020;  /* fE */
    u8 unk022[0x24 - 0x22];  /* fE */
    s16 unk024;  /* fE */
}; /* size 0x26 (f?) */

struct M515_LAYOUT_s {
    s16 unk0;  /* fF */
    s16 unk2;  /* fF */
    float unk4;  /* fF */
}; /* size 0x8 (f?) */

/* --- m515.c --- */
void ObjectSetup(void);
void fn_1_1FC(void);
void fn_1_26C(void);
void fn_1_928(void);
void fn_1_968(void);
void fn_1_B08(void);
void fn_1_D30(void);
void fn_1_1B58(void);
void fn_1_1D20(void);
void fn_1_1D24(void);
void fn_1_1D60(OMOBJ *obj);
void fn_1_2684(OMOBJ *obj);
void fn_1_29CC(void);
void fn_1_29D0(OMOBJ *obj);
void fn_1_2AC0(OMOBJ *obj);
void fn_1_2B68(void);
void fn_1_2B6C(M515_WORK *work);
void fn_1_2EB4(M515_WORK *work);
void fn_1_2F3C(M515_WORK *work);
void fn_1_32C4(M515_WORK *work);
void fn_1_5C40(M515_WORK *work);
M515_NODE *fn_1_5CE4(M515_WORK *work);
void fn_1_5D48(M515_WORK *work, M515_NODE *task);
void fn_1_5DB0(M515_WORK *work);
void fn_1_5E88(HU3DMODELID model, HuVecF pos, HuVecF rot, s16 layer, u16 camBit);
void fn_1_5F2C(HU3DMODELID model, HuVecF pos, HuVecF rot, s16 layer, u16 camBit);
s32 fn_1_5FD0(M515_PLAYER *p);
void fn_1_60E8(M515_PLAYER *p, M515_CELL *cell);
s32 fn_1_611C(M515_PLAYER *p);
void fn_1_62FC(M515_PLAYER *p, s16 dir);
void fn_1_6318(M515_PLAYER *p);
s32 fn_1_6324(M515_PLAYER *p, M515_WORK *work);
s16 fn_1_66D0(M515_PLAYER *p);
void fn_1_6980(M515_PLAYER *p);
void fn_1_69B8(M515_PLAYER *p, M515_WORK *work);
void fn_1_6FE8(M515_PLAYER *player);
void fn_1_72E4(M515_PLAYER *player);
void fn_1_73B0(M515_PLAYER *player, s32 idx);
void fn_1_7768(M515_PLAYER *player, s32 idx);
void fn_1_77F0(M515_PLAYER *player, s32 idx);
s32 fn_1_7878(M515_PLAYER *player);
u16 fn_1_7924(M515_PLAYER *player);
void fn_1_7BE8(M515_PSUB *psub, M515_WORK *work);
void fn_1_7E5C(M515_CAMMOVE *cam, s16 no);
void fn_1_7EE0(M515_CAMMOVE *cam);
void fn_1_81A8(M515_CAMMOVE *cam, M515_PLAYER *player);
s32 fn_1_83E8(M515_CAMMOVE *cam);
s32 fn_1_86F4(M515_CAMMOVE *cam);
s32 fn_1_8964(M515_CAMMOVE *cam);
s32 fn_1_8BD4(M515_CAMMOVE *cam);
s32 fn_1_8E44(M515_CAMMOVE *cam);
s32 fn_1_90B4(M515_CAMMOVE *cam);
s32 fn_1_9324(M515_CAMMOVE *cam);
s32 fn_1_9594(M515_CAMMOVE *cam);
void fn_1_9804(M515_SEQ *seq, M515_CAMMOVE *cam, s32 idx);
void fn_1_9828(M515_SPLIT *split);
void fn_1_9920(M515_SPLIT *split);
void fn_1_9958(M515_SPLIT *split);
s32 fn_1_9DF8(M515_SEQ *seq, M515_PLAYER *player);
s32 fn_1_B0B8(M515_SEQ *seq, M515_PLAYER *p);
s32 fn_1_B5D8(M515_SEQ *seq, M515_PLAYER *p);
s32 fn_1_BA64(M515_SEQ *seq, M515_PLAYER *p);
float fn_1_BD10(HU3DMODELID modelId, s32 idx, float t);
void fn_1_BE78(M515_WORK *work, HU3DMODELID modelId, s16 flag);
void fn_1_BF24(M515_WORK *work, HU3DMODELID modelId, s16 flag);
s32 fn_1_BFD0(M515_NODE *node);
s32 fn_1_C0D0(M515_NODE *node);
s32 fn_1_C150(M515_NODE *node);
s32 fn_1_C26C(M515_NODE *node);
void fn_1_C2B0(M515_PLAYER *pl);
void fn_1_C83C(void);
void fn_1_C958(s32 idx, HuVecF *pos, s32 mode);
void fn_1_CAF0(M515_WORK *work, s32 idx);
void fn_1_CB60(M515_WORK *work, s32 idx);
void fn_1_CC20(void);
void fn_1_CE98(M515_WORK *work);
void fn_1_D0D8(M515_WORK *work);
void fn_1_D384(M515_PLAYER *player);
s32 fn_1_D928(M515_SEQ *seq, M515_PLAYER *player);
u16 fn_1_DD18(M515_PLAYER *player);
void fn_1_E274(M515_AI *ai, s16 kind, s16 level);
void fn_1_E548(M515_PLAYER *player);

#endif
