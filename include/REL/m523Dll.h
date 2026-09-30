#ifndef M523DLL_H
#define M523DLL_H

/*
 * m523dll (MG_TYPE_1VS3, overlay #37): the types, globals and prototypes that
 * m523.c and player.c share. The original compiles the two as separate
 * translation units, and each calls into and reads globals from the other.
 *
 * Offsets in the comments are the GameCube ones from the reference assembly
 * (build/mp5-asm/m523Dll). Pointer-bearing structs are wider on the host:
 * allocate them with sizeof, never with the byte count in the assembly.
 *
 * No upstream names exist for this overlay, so functions keep their reference
 * addresses and globals their lbl_1_* labels.
 */

#include "game/object.h"
#include "game/hu3d.h"
#include "humath.h"

/*
 * The minigame framework, compiled into m523.c exactly as m570dll compiles it.
 * player.c calls MgPlayerConfSet (fn_1_3178), MgVecApproach (fn_1_3244),
 * MgAngleApproach (fn_1_3368) and MgVecOrbit (fn_1_34D8), and reads objman
 * (lbl_1_bss_E4), so those five are external. m523's object carries no debug
 * camera format strings, so MGF_DEBUG_READOUT stays undefined.
 */
#define MGF_LINK_PLAYERCONFSET
#define MGF_LINK_VECAPPROACH
#define MGF_LINK_ANGLEAPPROACH
#define MGF_LINK_VECORBIT
#define MGF_LINK_OBJMAN
#define MGF_S_DECL
#include "REL/mgframe.h"

/* m523.c defines it through mgframe.h's MGF_S_BSS section. */
extern OMOBJMAN *objman;

#define M523_PLAYER_MAX 4
#define M523_TEAM_MAX 3

/*
 * 0x24 bytes. A doubly linked list of these is drawn by fn_1_9978:
 * lbl_1_bss_10C is the head sentinel and lbl_1_bss_E8 the tail sentinel
 * (both mdlId -1). fn_1_9798 allocates a node as an object's data and links
 * it in front of the tail; fn_1_98E8 unlinks one and fn_1_992C renumbers the
 * rest.
 */
typedef struct M523Node_s {
    /* 0x00 */ struct M523Node_s *next;
    /* 0x04 */ struct M523Node_s *prev;
    /* 0x08 */ HU3DMODELID mdlId;
    /* 0x0C */ HuVecF pos;
    /* 0x18 */ s16 no;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 mode;
    /* 0x20 */ int unk20;
} M523_NODE;

/*
 * 0xB0 bytes per player, memset to zero, then MgPlayerConfSet fills the
 * framework header. side 0 is the solo player (lbl_1_bss_13C), 1..3 the team.
 */
typedef struct M523Player_s {
    MGF_PLAYER_HEAD;                /* 0x00..0x2B */
    /* 0x2C */ OMOBJ *obj;
    /* 0x30 */ s16 side;
    /* 0x32 */ s16 motNo;           /* row of lbl_1_data_2CC; -1 before the first set */
    /* 0x34 */ float radius;        /* 50 for the solo player, 150 for the team */
    /* 0x38 */ s8 stkX;
    /* 0x39 */ s8 stkY;
    /* 0x3C */ HuVecF vel;
    /* 0x48 */ HuVecF targetPos;
    /* 0x54 */ int unk54;
    /* 0x58 */ s16 targetNo;        /* index into lbl_1_bss_140; -1 when none */
    /* 0x5C */ HuVecF unk5C;
    /* 0x68 */ HuVecF startPos;
    /* 0x74 */ HuVecF unk74;
    /* 0x80 */ s16 unk80;
    /* 0x82 */ s16 unk82;
    /* 0x84 */ int unk84;
    /* 0x88 */ int seNo;            /* -1 when idle */
    /* 0x8C */ M523_NODE *node;
    /* 0x90 */ HU3DMODELID ufoMdlId;
    /* 0x92 */ HU3DMOTID ufoMotId[4]; /* Hu3DMotionIDGet, then three Hu3DJointMotion */
    /* 0x9C */ int unk9C;
    /* 0xA0 */ s16 unkA0;
    /* 0xA2 */ s16 comMode;
    /* 0xA4 */ HuVecF comTarget;
} M523_PLAYER;

/* 0xC bytes: the motion to use for the solo player and for the team. */
typedef struct M523Motion_s {
    /* 0x00 */ s16 motNo[2];
    /* 0x04 */ float shift;
    /* 0x08 */ u32 attr;
} M523_MOTION;

/* m523.c */
extern int lbl_1_bss_14;
extern int lbl_1_bss_18;
extern int lbl_1_bss_1C;
extern HuVecF lbl_1_data_1E4[3];

void ObjectSetup(void);
void fn_1_12C(s16 mode, s16 frameNo);
void fn_1_524(s16 mode, s16 frameNo);
void fn_1_634(s16 mode, s16 frameNo);
void fn_1_674(s16 mode, s16 frameNo);
void fn_1_6CC(s16 mode, s16 frameNo);
void fn_1_714(s16 mode, s16 frameNo);
void fn_1_76C(s16 mode, s16 frameNo);
void fn_1_8C0(s16 mode, s16 frameNo);
void fn_1_8D4(s16 mode, s16 frameNo);
void fn_1_8E8(OMOBJ *obj);
void fn_1_BB0(void);
float fn_1_C88(HuVecF *a, HuVecF *b);
float fn_1_CEC(float a, float b);
float fn_1_D58(HuVecF *a, HuVecF *b, HuVecF *c, HuVecF *d);
void fn_1_E58(HuVecF *pos, s16 *outA, s16 *outB);
int fn_1_F34(HuVecF *pos, s16 seNo);

/* player.c */
extern M523_NODE lbl_1_bss_E8;
extern M523_NODE lbl_1_bss_10C;
extern int lbl_1_bss_130[M523_TEAM_MAX];
extern M523_PLAYER *lbl_1_bss_13C;
extern M523_PLAYER *lbl_1_bss_140[M523_PLAYER_MAX];
extern HuVecF lbl_1_bss_150[10];

OMOBJ *fn_1_3914(s16 no);
void fn_1_39DC(void);
void fn_1_3F68(OMOBJ *obj, s16 motNo);
void fn_1_405C(void);
void fn_1_40BC(OMOBJ *obj);
void fn_1_4110(M523_PLAYER *player);
void fn_1_41F8(HuVecF *vec, float max);
void fn_1_427C(M523_PLAYER *player);
float fn_1_43A4(M523_PLAYER *player);
void fn_1_4534(OMOBJ *obj);
void fn_1_4590(HuVecF *pos);
void fn_1_4654(OMOBJ *obj);
void fn_1_4700(M523_PLAYER *player);
void fn_1_4858(void);
void fn_1_4900(OMOBJ *obj);
void fn_1_4CCC(OMOBJ *obj);
void fn_1_4ED4(OMOBJ *obj);
void fn_1_54A8(OMOBJ *obj);
void fn_1_58A8(OMOBJ *obj);
void fn_1_595C(M523_PLAYER *player);
void fn_1_59F0(void);
void fn_1_5AFC(M523_PLAYER *player);
void fn_1_5CB8(OMOBJ *obj);
void fn_1_61E0(M523_PLAYER *player);
void fn_1_6294(OMOBJ *obj);
void fn_1_6800(OMOBJ *obj);
void fn_1_6DA4(OMOBJ *obj);
void fn_1_7198(M523_PLAYER *player);
BOOL fn_1_7358(M523_PLAYER *player);
BOOL fn_1_73D4(M523_PLAYER *player);
void fn_1_7488(void);
void fn_1_7654(void);
void fn_1_76E4(OMOBJ *obj);
void fn_1_7898(OMOBJ *obj);
void fn_1_7C84(OMOBJ *obj);
float fn_1_85A8(M523_PLAYER *player);
void fn_1_8874(M523_PLAYER *player);
void fn_1_8A80(M523_PLAYER *player, s16 no);
void fn_1_8B60(M523_PLAYER *player, int flag, float unused);   /* fn_1_85A8 passes 15.0f; never read */
int fn_1_8D14(M523_PLAYER *player);
float fn_1_8DF0(M523_PLAYER *player);
BOOL fn_1_90EC(M523_PLAYER *player);
int fn_1_9218(void);
void fn_1_92F4(M523_PLAYER *player);
void fn_1_9440(M523_PLAYER *player);
void fn_1_9574(void);
void fn_1_962C(OMOBJ *obj);
M523_NODE *fn_1_9798(HuVecF *pos);
void fn_1_98E8(M523_NODE *node);
void fn_1_992C(void);
void fn_1_9978(HU3DMODEL *model, Mtx *mtx);

#endif
