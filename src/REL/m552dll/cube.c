/*
 * m552dll/cube.c -- the pieces: the shared falling queue, choosing and
 * spawning kinds and colours, the block models each piece's cells use, and
 * placing those models. Written from the reference assembly, functions in
 * reference order; line ranges are into build/mp5-asm/m552dll/asm/REL/m552dll/cube.s.
 *
 * The compiler inlines fn_1_78EC into fn_1_7A40, fn_1_7A40 and fn_1_879C into
 * fn_1_88EC, and fn_1_7CBC into fn_1_7DE4, so the order below matters.
 */

#include "game/hu3d.h"
#include "game/frand.h"

#include "REL/m552dll/m552.h"

#include "string.h"

/* --- .data --- */

/* Each kind's width and height in cells, either way round. */
int lbl_1_data_410[22] = {
    1, 1, 1, 2, 1, 3, 1, 4, 2, 2, 2, 3,
    2, 4, 3, 3, 3, 4, 4, 4, 5, 5
};

/* Each kind's offset from its 5x5 grid centre. */
float lbl_1_data_468[12] = {
    0.0f, 0.0f, 0.0f, 50.0f, 0.0f, 0.0f, 0.0f, 50.0f, 50.0f, 50.0f, 50.0f, 0.0f
};

/* Each kind's height, for spacing the queue. */
float lbl_1_data_498[6] = { 100.0f, 200.0f, 300.0f, 400.0f, 200.0f, 300.0f };

/* Each kind's cells in a 5x5 grid. */
s8 lbl_1_data_4B0[6][25] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 }
};

/* The last kind chosen and how many times running. */
int lbl_1_data_548[2] = { -1, 0 };

/* --- .bss --- */

int lbl_1_bss_4920;                 /* how many double spawns running */

/* asm 1-26. Clear the field; no piece has a kind. */
void fn_1_7888(void)
{
    int i;

    memset(&lbl_1_bss_3700, 0, sizeof(M552_FIELD));
    for(i=0; i<20; i++) {
        lbl_1_bss_3700.piece[i].kind = -1;
    }
}

/* asm 27-104. A weighted random kind, never the same one three times running. */
int fn_1_78EC(void)
{
    u8 rand = rand8()%128;
    u8 weight[6] = { 37, 30, 30, 10, 11, 10 };
    u8 kind;
    u8 sum;

    for(kind=0, sum=0; kind<6; kind++) {
        sum += weight[kind];
        if(sum > rand) {
            break;
        }
    }
    if(kind == lbl_1_data_548[0]) {
        lbl_1_data_548[1]++;
        if(lbl_1_data_548[1] == 3) {
            kind = (kind+1)%3;
        }
    } else {
        lbl_1_data_548[0] = kind;
        lbl_1_data_548[1] = 0;
    }
    return kind;
}

/*
 * asm 105-235. Choose the next queue slot's kind if it has none, and say
 * whether the piece ahead has fallen far enough to spawn it: its kind+1, or 0.
 */
int fn_1_7A40(void)
{
    M552_PIECE *piece;
    int prev;
    int result;

    result = 0;
    piece = &lbl_1_bss_3700.piece[lbl_1_bss_3700.next];
    if(piece->kind < 0) {
        piece->kind = fn_1_78EC();
    }
    prev = lbl_1_bss_3700.next-1;
    if(prev < 0) {
        prev = 19;
    }
    if(lbl_1_bss_3700.piece[prev].activeF == 0) {
        lbl_1_bss_3700.piece[prev].y -= 8.5f;
    }
    if(lbl_1_bss_3700.piece[prev].y < 1050.0f-(155.0f+((lbl_1_data_498[lbl_1_bss_3700.piece[prev].kind]+lbl_1_data_498[piece->kind])/2.0f))) {
        result = piece->kind+1;
    }
    return result;
}

/*
 * asm 236-320. Are there enough free block models of this colour for a piece
 * of this kind, counting the cells both held pieces of that colour use?
 */
int fn_1_7CBC(s16 kind, s8 color)
{
    int cellNum[6] = { 1, 2, 3, 4, 4, 6 };
    int i;
    int num;
    M552_PIECE *held;

    for(i=0, num=0; i<40; i++) {
        if(lbl_1_bss_1340[i+(color*40)].mode == 0) {
            num++;
        }
    }
    for(i=0; i<2; i++) {
        held = &lbl_1_bss_3700.board[i].held;
        if(held->activeF != 0 && held->cell[12] == color+1) {
            num -= cellNum[held->kind];
        }
    }
    num -= cellNum[kind];
    if(num >= 0) {
        return 1;
    } else {
        return 0;
    }
}

/*
 * asm 321-630. Spawn a piece of this kind, sometimes two side by side, each in
 * a colour with enough free block models.
 */
void fn_1_7DE4(s16 kind)
{
    M552_PIECE *piece;
    int j;
    int count;
    s8 color;
    int i;
    int unused;

    count = 1;
    unused = 0;
    color = rand8()%4;
    for(;;) {
        if(fn_1_7CBC(kind, color)) {
            break;
        }
        color = (color+1)%4;
    }
    if(kind == 0 && rand8() < 128) {
        count++;
    }
    if(kind == 1 && rand8() < 96) {
        count++;
    }
    if(kind == 2 && rand8() < 64) {
        count++;
    }
    if(kind == 3 && rand8() < 32) {
        count++;
    }
    if(count == 2) {
        lbl_1_bss_4920++;
    } else {
        lbl_1_bss_4920 = 0;
    }
    for(i=0; i<count; i++) {
        piece = &lbl_1_bss_3700.piece[lbl_1_bss_3700.next];
        piece->activeF = 1;
        piece->kind = kind;
        for(j=0; j<25; j++) {
            piece->cell[j] = lbl_1_data_4B0[piece->kind][j];
            if(piece->cell[j] != 0) {
                piece->cell[j] = color+1;
            }
        }
        piece->y = 1050.0f;
        if(count > 1) {
            piece->x = (i*200)-100;
            color = (color+1)%4;
            for(;;) {
                if(fn_1_7CBC(kind, color)) {
                    break;
                }
                color = (color+1)%4;
            }
        } else {
            piece->x = 0.0f;
        }
        fn_1_8C88(lbl_1_bss_3700.next);
        fn_1_8F2C(lbl_1_bss_3700.next, 0);
        lbl_1_bss_3700.next = (lbl_1_bss_3700.next+1)%20;
    }
}

/*
 * asm 631-838. Give the held piece's cells linked shadow models (up to six),
 * posed and timed like the cells.
 */
void fn_1_82BC(int player)
{
    float time;
    int i;
    int n;
    M552_SLOT *slot;
    int color;

    time = -1.0f;
    for(i=0, n=0; i<25; i++) {
        if(lbl_1_bss_3700.board[player].held.cell[i] != 0) {
            slot = &lbl_1_bss_1340[lbl_1_bss_3700.board[player].held.slot[i]];
            if(n == 0) {
                time = Hu3DMotionTimeGet(slot->modelId);
                color = lbl_1_bss_3700.board[player].held.cell[i]-1;
            }
            if(lbl_1_bss_530[n+(player*6)].mode != 0) {
                Hu3DModelKill(lbl_1_bss_530[n+(player*6)].modelId);
            }
            lbl_1_bss_530[n+(player*6)].mode = 1;
            lbl_1_bss_530[n+(player*6)].modelId = Hu3DModelLink(lbl_1_bss_490[color].modelId);
            Hu3DModelAttrSet(lbl_1_bss_530[n+(player*6)].modelId, HU3D_ATTR_DISPOFF);
            Hu3DModelPosSetV(lbl_1_bss_530[n+(player*6)].modelId, &lbl_1_bss_1340[lbl_1_bss_3700.board[player].held.slot[i]].pos);
            lbl_1_bss_530[n+(player*6)].pos.x = lbl_1_bss_1340[lbl_1_bss_3700.board[player].held.slot[i]].pos.x;
            lbl_1_bss_530[n+(player*6)].pos.y = lbl_1_bss_1340[lbl_1_bss_3700.board[player].held.slot[i]].pos.y;
            lbl_1_bss_530[n+(player*6)].pos.z = lbl_1_bss_1340[lbl_1_bss_3700.board[player].held.slot[i]].pos.z;
            Hu3DMotionTimeSet(lbl_1_bss_530[n+(player*6)].modelId, time);
            Hu3DMotionSpeedSet(lbl_1_bss_530[n+(player*6)].modelId, 2.0f);
            Hu3DModelAttrReset(lbl_1_bss_530[n+(player*6)].modelId, HU3D_MOTATTR_LOOP);
            slot->timer = 0;
            Hu3DModelCameraSet(lbl_1_bss_530[n+(player*6)].modelId, 2);
            n++;
        }
        if(n >= 6) {
            break;
        }
    }
}

/* asm 839-928. Show or hide the held piece: cells on, shadows the other way. */
void fn_1_8644(int player, int onF)
{
    int i;
    M552_SLOT *slot;

    for(i=0; i<25; i++) {
        if(lbl_1_bss_3700.board[player].held.cell[i] != 0) {
            slot = &lbl_1_bss_1340[lbl_1_bss_3700.board[player].held.slot[i]];
            if(onF) {
                Hu3DModelAttrReset(slot->modelId, HU3D_ATTR_DISPOFF);
            } else {
                Hu3DModelAttrSet(slot->modelId, HU3D_ATTR_DISPOFF);
            }
        }
    }
    for(i=0; i<6; i++) {
        if(lbl_1_bss_530[i+(player*6)].mode != 0) {
            if(onF) {
                Hu3DModelAttrSet(lbl_1_bss_530[i+(player*6)].modelId, HU3D_ATTR_DISPOFF);
            } else {
                Hu3DModelAttrReset(lbl_1_bss_530[i+(player*6)].modelId, HU3D_ATTR_DISPOFF);
            }
        }
    }
}

/* asm 929-1017. Free a queue piece or a held piece and its block models. */
void fn_1_879C(int no, int boardF)
{
    int i;
    M552_PIECE *piece;
    M552_SLOT *slot;

    if(boardF == 0) {
        piece = &lbl_1_bss_3700.piece[no];
        piece->kind = -1;
    } else {
        piece = &lbl_1_bss_3700.board[no].held;
    }
    piece->activeF = 0;
    for(i=0; i<25; i++) {
        if(piece->cell[i] != 0) {
            slot = &lbl_1_bss_1340[piece->slot[i]];
            slot->mode = 0;
            Hu3DModelAttrSet(slot->modelId, HU3D_ATTR_DISPOFF);
        }
    }
    if(boardF) {
        for(i=0; i<6; i++) {
            if(lbl_1_bss_530[i+(no*6)].mode != 0) {
                Hu3DModelKill(lbl_1_bss_530[i+(no*6)].modelId);
                lbl_1_bss_530[i+(no*6)].mode = 0;
            }
        }
    }
}

/* asm 1018-1225. The queue's frame: fall, free what left the screen, spawn. */
void fn_1_88EC(void)
{
    int i;

    for(i=0; i<20; i++) {
        if(lbl_1_bss_3700.piece[i].activeF != 0) {
            lbl_1_bss_3700.piece[i].y -= 8.5f;
            fn_1_8F2C(i, 0);
            if(lbl_1_bss_3700.piece[i].y < -1050.0f) {
                fn_1_879C(i, 0);
            }
        }
    }
    i = fn_1_7A40();
    if(i != 0) {
        fn_1_7DE4(i-1);
    }
}

/* asm 1226-1276. Give a queue piece's cells block models; 1 if any ran out. */
int fn_1_8C88(int no)
{
    int i;
    M552_PIECE *piece;
    int failF;

    failF = 0;
    piece = &lbl_1_bss_3700.piece[no];
    for(i=0; i<25; i++) {
        if(piece->cell[i] != 0) {
            piece->slot[i] = fn_1_8D4C(piece->cell[i], 0, -1.0f);
            if(piece->slot[i] < 0) {
                failF = 1;
            }
        }
    }
    return failF;
}

/*
 * asm 1277-1394. Take a free block model of a colour (1-4) from the queue's 40
 * or the boards' 12 and show it; its bss_1340 index, or -1.
 */
int fn_1_8D4C(int color, int boardF, float time)
{
    M552_SLOT *slot;
    int i;
    HU3DMODEL *modelP;
    HSFMATERIAL *material;
    int j;
    int num;
    HSFDATA *hsf;

    if(boardF != 0) {
        num = 12;
        slot = &lbl_1_bss_1340[((color-1)*12)+160];
    } else {
        num = 40;
        slot = &lbl_1_bss_1340[(color-1)*40];
    }
    for(i=0; i<num; i++, slot++) {
        if(slot->mode == 0) {
            break;
        }
    }
    if(i == num) {
        return -1;
    }
    slot->mode = 1;
    Hu3DModelPosSet(slot->modelId, 0.0f, 0.0f, -500.0f);
    Hu3DModelAttrReset(slot->modelId, HU3D_ATTR_DISPOFF);
    if(time < 0.0f) {
        Hu3DMotionTimeSet(slot->modelId, 0.0f);
    } else {
        Hu3DMotionTimeSet(slot->modelId, time);
    }
    Hu3DMotionSpeedSet(slot->modelId, 2.0f);
    Hu3DModelAttrReset(slot->modelId, HU3D_MOTATTR_LOOP);
    slot->timer = 0;
    modelP = &Hu3DData[slot->modelId];
    hsf = modelP->hsf;
    material = hsf->material;
    for(j=0; j<modelP->hsf->materialNum; j++, material++) {
        material->invAlpha = 0.0f;
    }
    if(boardF != 0) {
        i = i+((color-1)*12)+160;
    } else {
        i += (color-1)*40;
    }
    return i;
}

/*
 * asm 1395-1546. Place a queue or held piece's cell models: each cell's offset
 * from the grid centre, turned by the piece's rot, plus the piece's position.
 * A held piece's shadows follow.
 */
void fn_1_8F2C(int no, int boardF)
{
    Mtx trans;
    Mtx rot;
    M552_SLOT *slot;
    M552_PIECE *piece;
    int x;
    int y;
    int n;

    if(boardF == 0) {
        piece = &lbl_1_bss_3700.piece[no];
    } else {
        piece = &lbl_1_bss_3700.board[no].held;
    }
    MTXRotRad(rot, 'z', 0.017453292f*piece->rot);
    n = 0;
    for(y=0; y<5; y++) {
        for(x=0; x<5; x++) {
            if(piece->cell[x+(y*5)] != 0) {
                slot = &lbl_1_bss_1340[piece->slot[x+(y*5)]];
                slot->pos.x = (-200.0f+(100.0f*x))-lbl_1_data_468[piece->kind*2];
                slot->pos.y = (-200.0f+(100.0f*y))+lbl_1_data_468[(piece->kind*2)+1];
                MTXTrans(trans, slot->pos.x, slot->pos.y, piece->z);
                MTXConcat(rot, trans, trans);
                slot->pos.x = trans[0][3];
                slot->pos.y = trans[1][3];
                slot->pos.z = trans[2][3];
                slot->pos.x += piece->x;
                slot->pos.y += piece->y;
                if(boardF != 0) {
                    lbl_1_bss_530[n+(no*6)].pos.x = slot->pos.x;
                    lbl_1_bss_530[n+(no*6)].pos.y = slot->pos.y;
                    lbl_1_bss_530[n+(no*6)].pos.z = slot->pos.z;
                    n++;
                }
            }
        }
    }
}

