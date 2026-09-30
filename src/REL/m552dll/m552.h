/*
 * The types m552.c, game.c, cube.c, com.c and stage.c all need.
 *
 * m552dll is a KETTOU duel (overlay #66) on work head A of the duel stage
 * framework, REL/duelstage.h, like m550dll and m554dll: DS_WORK_HEAD, then the
 * overlay's own 0x60 bytes. The work is 0x170.
 *
 * A falling-block duel: pieces of one to six cells in a 5x5 mask fall down
 * the middle (M552_FIELD.piece); each duellist grabs one (A), turns it (L/R),
 * drops it onto their own 5x7 board or throws it in their bin. A full board
 * clears colour by colour for points; the higher score when time is up wins.
 *
 * Offsets come from every access in the reference assembly (NOTES.md). Names
 * that say unkNN are unexplained, not unallocated.
 */
#ifndef M552_H
#define M552_H

#include "game/object.h"
#include "game/hu3d.h"
#include "game/sprite.h"
#include "game/mg/score.h"
#include "game/mg/timer.h"
#include "humath.h"

/* The duel stage framework's types; stage.c includes its functions. */
#include "REL/duelstage.h"

typedef DS_MODEL M552_MODEL;        /* 0x1C */
typedef DS_CHAR M552_CHAR;          /* 0x1C */
typedef DS_PLAYER M552_PLAYER;      /* 0x54 */

#define M552_MODEL_MAX 37

typedef struct M552Work_s {
    DS_WORK_HEAD;                   /* mode[0] sub-state, [1] winner step, [2] the winner, [2+i] each duellist's state */
    /* 0x110 */ int count[12];      /* [0] the sub-state's timer and [i] a duellist's move timer, [2+i] their turn timer */
    /* 0x140 */ HuVecF pos[4];      /* [i] a duellist's move step (x, y) and turn step (z) */
} M552_WORK;                        /* 0x170 */

/* A block model and its state (bss_490, 530, 710, 1200, 1340). */
typedef struct M552Slot_s {
    /* 0x00 */ int mode;            /* 0 free; 1340: 1 animating, 3 paused; 710: 1 lit, 2 fading */
    /* 0x04 */ int timer;
    /* 0x08 */ int unk08;
    /* 0x0C */ HU3DMODELID modelId;
    /* 0x0E */ s16 pad0E;
    /* 0x10 */ HuVecF pos;
    /* 0x1C */ HuVecF rot;
} M552_SLOT;                        /* 0x28 */

/* One piece: its kind, where it is, and the models of its cells. */
typedef struct M552Piece_s {
    /* 0x00 */ int activeF;
    /* 0x04 */ int kind;            /* 0-5, -1 none */
    /* 0x08 */ float x;
    /* 0x0C */ float y;
    /* 0x10 */ float z;
    /* 0x14 */ float rot;           /* degrees, quarter turns */
    /* 0x18 */ s8 cell[25];         /* 5x5 mask, colour+1 */
    /* 0x31 */ u8 pad31[3];
    /* 0x34 */ int slot[25];        /* bss_1340 index of each cell's model */
} M552_PIECE;                       /* 0x98 */

/* A score popup over a board: up to five digit sprites. */
typedef struct M552Popup_s {
    /* 0x00 */ int activeF;
    /* 0x04 */ int value;
    /* 0x08 */ float x;
    /* 0x0C */ float y;
    /* 0x10 */ int unk10;
    /* 0x14 */ int unk14;
    /* 0x18 */ int timer;
    /* 0x1C */ int mode;
    /* 0x20 */ int spr[5];          /* bss_33C2[player] index, -1 hidden */
} M552_POPUP;                       /* 0x34 */

/* One duellist's cursor, held piece and board. */
typedef struct M552Board_s {
    /* 0x000 */ HuVecF cursor;
    /* 0x00C */ M552_PIECE held;
    /* 0x0A4 */ int dropCell[2];    /* fn_1_462C's whole-grid and half-grid cells for the drop */
    /* 0x0AC */ s8 grid[35];        /* 5 wide, 7 high, colour+1 */
    /* 0x0CF */ u8 padCF;
    /* 0x0D0 */ int gridSlot[35];
    /* 0x15C */ s8 line[4];         /* cells of each colour */
    /* 0x160 */ int timer;
    /* 0x164 */ int idx;
    /* 0x168 */ int mode;
    /* 0x16C */ int score;          /* shown */
    /* 0x170 */ int scoreTarget;
    /* 0x174 */ M552_POPUP popup[4];
    /* 0x244 */ int blinkF;
    /* 0x248 */ int blinkPrevF;
    /* 0x24C */ int blinkTimer;
    /* 0x250 */ int blinkOn;
} M552_BOARD;                       /* 0x254 */

/* The falling queue and both boards (bss_3700). */
typedef struct M552Field_s {
    /* 0x000 */ int unk00;
    /* 0x004 */ int next;           /* the queue slot the next piece spawns in */
    /* 0x008 */ int unk08;
    /* 0x00C */ M552_PIECE piece[20];
    /* 0xBEC */ M552_BOARD board[2];
} M552_FIELD;                       /* 0x1094 */

/* A computer duellist (bss_4930). */
typedef struct M552Com_s {
    /* 0x00 */ int dif;
    /* 0x04 */ int mode;
    /* 0x08 */ int step;
    /* 0x0C */ int unk0C;
    /* 0x10 */ int nextMode;
    /* 0x14 */ int wait;
    /* 0x18 */ u8 unk18[0x0C];
    /* 0x24 */ int piece;
    /* 0x28 */ int cell;
    /* 0x2C */ u8 unk2C[0x40];
    /* 0x6C */ int kind;
    /* 0x70 */ u8 unk70[0x0C];
} M552_COM;                         /* 0x7C */

/* m552.c */
extern unsigned int lbl_1_data_0[48];
extern char *lbl_1_data_240[4];
extern char *lbl_1_data_320[13];
extern int lbl_1_bss_0;
extern OMOBJ *lbl_1_bss_4;
extern HU3DMODELID lbl_1_bss_8;
extern u8 lbl_1_bss_A;
extern HU3DMOTID lbl_1_bss_C[2][2];
extern OMCAMERAVIEW lbl_1_bss_14[4];
extern M552_MODEL lbl_1_bss_84[M552_MODEL_MAX];
extern M552_SLOT lbl_1_bss_490[4];
extern M552_SLOT lbl_1_bss_530[12];
extern M552_SLOT lbl_1_bss_710[70];
extern M552_SLOT lbl_1_bss_1200[8];
extern M552_SLOT lbl_1_bss_1340[208];
extern HUSPRID lbl_1_bss_33C0;
extern HUSPRID lbl_1_bss_33C2[2][200];
extern HU3DTEXSCRID lbl_1_bss_36E2[2][7];
extern M552_FIELD lbl_1_bss_3700;
extern M552_WORK lbl_1_bss_4794;

void fn_1_1810(int mdlNo, float alpha);
void fn_1_188C(void);
void fn_1_18E8(void);

/* game.c */
extern float lbl_1_data_360[22];
extern int lbl_1_data_3B8;
extern int lbl_1_data_3BC;
extern int lbl_1_bss_4910;
extern MGSCORE *lbl_1_bss_4914;
extern MGTIMER *lbl_1_bss_490C;

void fn_1_1C40(void);
void fn_1_1FF4(void);
void fn_1_2180(void);
void fn_1_26BC(void);
void fn_1_27B4(void);
void fn_1_2890(void);
void fn_1_2930(void);
void fn_1_2AA0(void);
void fn_1_2AC4(OMOBJ *obj);
void fn_1_2E48(void);
void fn_1_3374(int player);
void fn_1_385C(int player, int type);
int fn_1_3B98(int player);
int fn_1_41C0(int player);
void fn_1_4450(int player, int dir);
void fn_1_4534(int player);
int fn_1_462C(int player, int halfF);
int fn_1_4A78(int axis, int cell, int size);
void fn_1_4C50(int player);
void fn_1_4DA4(int player);
int fn_1_4E94(int player);
int fn_1_57D4(int player);
int fn_1_5A34(int player);
void fn_1_5EBC(int player);
void fn_1_63A0(int player);
int fn_1_6650(int player);
int fn_1_6758(int player, int color);
void fn_1_6834(int player);
int fn_1_6920(void);
void fn_1_6B58(int player, int no, int value);
int fn_1_6DE0(void);
int fn_1_7134(int player);
int fn_1_7400(int player);
int fn_1_7574(int player);
void fn_1_7800(int player, int face);

/* cube.c */
extern int lbl_1_data_410[22];     /* [kind*2] width, [kind*2+1] height */

void fn_1_7888(void);
int fn_1_78EC(void);
int fn_1_7A40(void);
int fn_1_7CBC(s16 kind, s8 color);
void fn_1_7DE4(s16 kind);
void fn_1_82BC(int player);
void fn_1_8644(int player, int onF);
void fn_1_879C(int no, int boardF);
void fn_1_88EC(void);
int fn_1_8C88(int no);
int fn_1_8D4C(int color, int boardF, float time);
void fn_1_8F2C(int no, int boardF);

/* com.c */
void fn_1_91BC(void);
void fn_1_9238(int player);

/* stage.c */
void fn_1_B33C(M552_WORK *work, M552_MODEL *models, unsigned int *dataTbl);
void fn_1_B588(s16 stageNo);
void fn_1_B810(unsigned int *dataA, unsigned int *dataB);
void fn_1_B834(HU3DMOTID *idA, HU3DMOTID *idB);
void fn_1_B858(void);
void fn_1_BADC();                   /* PadRead; game.c's fn_1_2890 calls it with no object */
void fn_1_BF98(void);
void fn_1_C14C(OMOBJ *obj);

#endif
