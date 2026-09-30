/*
 * m552dll/com.c -- the computer duellists: pick a piece that fits, steer the
 * cursor to it, grab it, turn it and drop it. Written from the reference
 * assembly, functions in reference order; line ranges are into
 * build/mp5-asm/m552dll/asm/REL/m552dll/com.s.
 */

#include "game/object.h"
#include "game/frand.h"
#include "game/pad.h"

#include "REL/m552dll/m552.h"

#include "string.h"

int fn_1_92BC(int player, int type);
int fn_1_9460(int player, int cell, int kind);
int fn_1_9718(int player, int unused);
int fn_1_9EE8(int player, int step);
void fn_1_A7AC(int player);
void fn_1_A8F4(int player);
void fn_1_B2C0(int player);

/* --- .data --- */

int lbl_1_data_550[2][2] = { { 0, 0 }, { 0, 0 } };
int lbl_1_data_560[2] = { 0, 0 };

/* --- .bss (CodeWarrior lays it out in reverse definition order) --- */

M552_COM lbl_1_bss_4930[2];
float lbl_1_bss_4928[2];            /* each computer's held cursor step */

/* asm 1-32, 31 insns. */
void fn_1_91BC(void)
{
    int i;

    for(i=0; i<2; i++) {
        memset(&lbl_1_bss_4930[i], 0, sizeof(M552_COM));
        lbl_1_bss_4930[i].dif = lbl_1_bss_4794.chr[i].dif;
    }
}

/* asm 33-71, 33 insns. One computer duellist's frame. */
void fn_1_9238(int player)
{
    switch(lbl_1_bss_4930[player].mode) {
        case 0:
            fn_1_A7AC(player);
            break;

        case 1:
            fn_1_A8F4(player);
            break;

        case 3:
            fn_1_B2C0(player);
            break;
    }
}

/* asm 72-172, 105 insns. How long the computer waits, by difficulty. */
int fn_1_92BC(int player, int type)
{
    int grabTbl[4] = { 75, 30, 10, 0 };
    int moveTbl[4] = { 75, 15, 10, 0 };
    int dropTbl[4] = { 75, 5, 1, 1 };
    int wait;

    wait = 0;
    switch(type) {
        case 0:
            wait = grabTbl[lbl_1_bss_4930[player].dif-1];
            wait += rand8()%10;
            break;

        case 1:
            wait = moveTbl[lbl_1_bss_4930[player].dif-1];
            wait += rand8()%10;
            break;

        case 2:
            wait = dropTbl[lbl_1_bss_4930[player].dif-1];
            wait += 2;
            break;
    }
    return wait;
}

/*
 * asm 173-362, 174 insns. Does a piece fit with its corner at cell? kind < 0:
 * a bit per kind (1-5) that fits either way round. Otherwise the first
 * orientation that fits, or 2 for neither.
 */
int fn_1_9460(int player, int cell, int kind)
{
    int x;
    int y;
    int bit;
    int k;
    int result;
    int rot;
    int sum;
    int yy;
    int xx;
    int w;
    int h;

    x = cell%5;
    y = cell/5;
    result = 0;
    if(kind < 0) {
        for(k=1, bit=2; k<6; k++, bit<<=1) {
            for(rot=0; rot<2; rot++) {
                if(rot == 0) {
                    w = lbl_1_data_410[k*2];
                    h = lbl_1_data_410[(k*2)+1];
                } else {
                    w = lbl_1_data_410[(k*2)+1];
                    h = lbl_1_data_410[k*2];
                }
                sum = 1;
                if(x+w > 5 || y+h > 7) {
                    continue;
                }
                sum = 0;
                for(yy=y; yy<y+h; yy++) {
                    for(xx=x; xx<x+w; xx++) {
                        sum += lbl_1_bss_3700.board[player].grid[xx+(yy*5)];
                    }
                }
                if(sum == 0) {
                    break;
                }
            }
            if(sum == 0) {
                result += bit;
            }
        }
    } else {
        k = kind;
        for(rot=0; rot<2; rot++) {
            if(rot == 0) {
                w = lbl_1_data_410[k*2];
                h = lbl_1_data_410[(k*2)+1];
            } else {
                w = lbl_1_data_410[(k*2)+1];
                h = lbl_1_data_410[k*2];
            }
            if(x+w > 5 || y+h > 7) {
                continue;
            }
            sum = 0;
            for(yy=y; yy<y+h; yy++) {
                for(xx=x; xx<x+w; xx++) {
                    sum += lbl_1_bss_3700.board[player].grid[xx+(yy*5)];
                }
            }
            if(sum == 0) {
                break;
            }
        }
        return rot;
    }
    return result;
}

/*
 * asm 363-851, 500 insns. Choose the falling piece to go for: the nearest of a
 * kind that fits somewhere, and the board cell to put it in (com.cell); -1 when
 * nothing useful is falling.
 */
int fn_1_9718(int player, int unused)
{
    float limit;
    float bestDist = -1.0f;
    int mask[7] = { 1, 2, 4, 8, 16, 32, 64 };
    s8 cand[8];
    int fit;
    float dx;
    float dy;
    int i;
    int c;
    int best;
    s8 n;
    int fits;
    int kinds;
    int kind;

    limit = lbl_1_bss_3700.board[player].cursor.y-350.0f;
    if(limit < -400.0f) {
        limit = -400.0f;
    }
    for(i=0, kinds=0, n=0; i<20; i++) {
        if(lbl_1_bss_3700.piece[i].activeF != 0 && lbl_1_bss_3700.piece[i].y > limit && lbl_1_bss_3700.piece[i].y < 300.0f) {
            cand[n] = i;
            n++;
            kinds |= mask[lbl_1_bss_3700.piece[i].kind];
            if(n >= 8) {
                break;
            }
        }
    }
    if(n == 0) {
        return -1;
    }
    for(i=0, best=-1, fits=0; i<35; i++) {
        if(player != 0) {
            c = i;
        } else {
            c = (4-(i%5))+((i/5)*5);
        }
        if(lbl_1_bss_3700.board[player].grid[c] == 0) {
            best = c;
            fits |= fn_1_9460(player, c, -1);
        }
    }
    if(fits & kinds) {
        best = -1;
    }
    if(best < 0) {
        fits &= kinds;
        for(i=0, best=2; i<5; i++, best<<=1) {
            if(fits & best) {
                kind = i+1;
            }
        }
        for(i=0, best=0; i<n; i++) {
            if(kind == lbl_1_bss_3700.piece[cand[i]].kind) {
                dx = lbl_1_bss_3700.piece[cand[i]].x-lbl_1_bss_3700.board[player].cursor.x;
                dy = lbl_1_bss_3700.piece[cand[i]].y-lbl_1_bss_3700.board[player].cursor.y;
                limit = (dy*dy)+(dx*dx);
                if(-1.0 == bestDist || bestDist > limit) {
                    bestDist = limit;
                    best = i;
                }
            }
        }
        for(i=0; i<35; i++) {
            if(player != 0) {
                if(i < 21) {
                    c = (i%3)+((i/3)*5);
                } else {
                    c = (((i-21)%7)*5)+3+((i-21)/7);
                }
            } else {
                if(i < 21) {
                    c = (((i/3)*5)+4)-(i%3);
                } else {
                    c = ((((i-21)%7)*5)+1)-((i-21)/7);
                }
            }
            if((fit = fn_1_9460(player, c, kind)) != 2) {
                break;
            }
        }
        lbl_1_bss_4930[player].cell = c;
        return cand[best];
    } else {
        for(i=0; i<35; i++) {
            if(player != 0) {
                if(i < 21) {
                    c = (i%3)+((i/3)*5);
                } else {
                    c = (((i-21)%7)*5)+3+((i-21)/7);
                }
            } else {
                if(i < 21) {
                    c = (((i/3)*5)+4)-(i%3);
                } else {
                    c = ((((i-21)%7)*5)+1)-((i-21)/7);
                }
            }
            if(lbl_1_bss_3700.board[player].grid[c] == 0) {
                break;
            }
        }
        lbl_1_bss_4930[player].cell = c;
        best = n;
        for(i=0; i<n; i++) {
            if(lbl_1_bss_3700.piece[cand[i]].kind == 0) {
                dx = lbl_1_bss_3700.piece[cand[i]].x-lbl_1_bss_3700.board[player].cursor.x;
                dy = lbl_1_bss_3700.piece[cand[i]].y-lbl_1_bss_3700.board[player].cursor.y;
                limit = (dy*dy)+(dx*dx);
                if(-1.0 == bestDist || bestDist > limit) {
                    bestDist = limit;
                    best = i;
                }
            }
        }
        if(best < n) {
            return cand[best];
        } else {
            return -1;
        }
    }
}

/*
 * asm 852-1316, 561 insns. Steer the cursor for one step: 0 to the chosen
 * falling piece, 1 over the chosen board cell, 2 to the grab-ready spot, 3 home.
 * Presses A (or L to turn) and returns 1 once there.
 */
int fn_1_9EE8(int player, int step)
{
    float dx;
    float dy;
    int w;
    int h;
    int fit;

    switch(step) {
        case 0:
            w = lbl_1_data_410[lbl_1_bss_3700.board[player].held.kind*2];
            h = lbl_1_data_410[(lbl_1_bss_3700.board[player].held.kind*2)+1];
            if(player != 0) {
                dx = lbl_1_bss_3700.piece[lbl_1_bss_4930[player].piece].x+(w*50);
            } else {
                dx = lbl_1_bss_3700.piece[lbl_1_bss_4930[player].piece].x-(w*50);
            }
            dx -= lbl_1_bss_3700.board[player].cursor.x;
            dy = lbl_1_bss_3700.piece[lbl_1_bss_4930[player].piece].y;
            dy -= lbl_1_bss_3700.board[player].cursor.y;
            if(lbl_1_bss_3700.board[player].cursor.y < 50.0f+lbl_1_bss_3700.piece[lbl_1_bss_4930[player].piece].y
                && lbl_1_bss_3700.board[player].cursor.y > lbl_1_bss_3700.piece[lbl_1_bss_4930[player].piece].y-50.0f) {
                dy = 0.0f;
            }
            if(lbl_1_data_550[player][0] != 0) {
                dy = lbl_1_bss_4928[player];
                lbl_1_data_550[player][0]++;
                if(lbl_1_data_550[player][0] == 5) {
                    lbl_1_data_550[player][0] = 0;
                }
            } else {
                lbl_1_data_550[player][0]++;
                lbl_1_bss_4928[player] = dy;
            }
            break;

        case 1:
            fit = fn_1_9460(player, lbl_1_bss_4930[player].cell, lbl_1_bss_3700.board[player].held.kind);
            if(fit == 1) {
                if(lbl_1_bss_4794.mode[player+2] == 2 && 0.0f == lbl_1_bss_3700.board[player].held.rot) {
                    lbl_1_bss_4794.chr[player].btnDown = PAD_TRIGGER_L;
                }
                w = lbl_1_data_410[(lbl_1_bss_3700.board[player].held.kind*2)+1]-1;
                h = lbl_1_data_410[lbl_1_bss_3700.board[player].held.kind*2]-1;
            } else {
                w = lbl_1_data_410[lbl_1_bss_3700.board[player].held.kind*2]-1;
                h = lbl_1_data_410[(lbl_1_bss_3700.board[player].held.kind*2)+1]-1;
            }
            dx = (50.0f*w)+((-750.0f+(1100.0f*player))+(100.0f*(lbl_1_bss_4930[player].cell%5)));
            dy = (250.0f-(100.0f*(lbl_1_bss_4930[player].cell/5)))-(50.0f*h);
            dx -= lbl_1_bss_3700.board[player].cursor.x;
            dy -= lbl_1_bss_3700.board[player].cursor.y;
            break;

        case 2:
            dx = (-250.0f+(500.0f*player))-lbl_1_bss_3700.board[player].cursor.x;
            dy = 150.0f-lbl_1_bss_3700.board[player].cursor.y;
            break;

        case 3:
            dx = ((player*1200)-600)-lbl_1_bss_3700.board[player].cursor.x;
            dy = -525.0f-lbl_1_bss_3700.board[player].cursor.y;
            break;
    }
    if(dx > 10.0f) {
        lbl_1_bss_4794.chr[player].stkX = 10;
    } else if(dx < -10.0f) {
        lbl_1_bss_4794.chr[player].stkX = -10;
    }
    if(dy > 10.0f) {
        lbl_1_bss_4794.chr[player].stkY = 10;
    } else if(dy < -10.0f) {
        lbl_1_bss_4794.chr[player].stkY = -10;
    }
    if(dx > -12.0f && dx < 12.0f && dy > -11.5 && dy < 11.5) {
        if(step != 2) {
            if(lbl_1_bss_4794.count[player+2] == 0) {
                lbl_1_bss_4794.chr[player].btnDown = PAD_BUTTON_A;
                return 1;
            }
        } else {
            return 1;
        }
    }
    return 0;
}

/* asm 1317-1389, 82 insns. Start: wait, then plan. */
void fn_1_A7AC(int player)
{
    lbl_1_bss_4930[player].mode = 3;
    lbl_1_bss_4930[player].wait = fn_1_92BC(player, 0);
    lbl_1_bss_4930[player].nextMode = 1;
}

/* asm 1390-1948, 627 insns. The plan: choose, go and grab, place, back off. */
void fn_1_A8F4(int player)
{
    int result;

    switch(lbl_1_bss_4930[player].step) {
        case 0:
            if(lbl_1_bss_4794.mode[player+2] == 4 || lbl_1_bss_4794.mode[player+2] == 5 || lbl_1_bss_4794.mode[player+2] == 6) {
                lbl_1_bss_4930[player].step = 3;
                lbl_1_bss_4930[player].piece = -1;
            } else if(lbl_1_bss_4794.mode[player+2] == 0) {
                lbl_1_bss_4930[player].piece = fn_1_9718(player, 0);
            } else {
                if(lbl_1_bss_4794.mode[player+2] == 3) {
                    break;
                }
                lbl_1_bss_4930[player].step = 5;
                break;
            }
            lbl_1_data_560[player] = 0;
            if(lbl_1_bss_4930[player].piece < 0) {
                lbl_1_bss_4930[player].step = 3;
                break;
            }
            lbl_1_bss_4930[player].step++;
            lbl_1_bss_4930[player].kind = lbl_1_bss_3700.piece[lbl_1_bss_4930[player].piece].kind;
            break;

        case 1:
            if(lbl_1_bss_4794.mode[player+2] == 0 && (lbl_1_bss_3700.piece[lbl_1_bss_4930[player].piece].activeF == 0 || lbl_1_bss_3700.piece[lbl_1_bss_4930[player].piece].y < -525.0f)) {
                lbl_1_bss_4930[player].mode = 3;
                lbl_1_bss_4930[player].nextMode = 1;
                lbl_1_bss_4930[player].wait = fn_1_92BC(player, 1);
                break;
            }
            result = fn_1_9EE8(player, 0);
            if(result == 0) {
                if(lbl_1_bss_4794.mode[player+2] == 4 || lbl_1_bss_4794.mode[player+2] == 5 || lbl_1_bss_4794.mode[player+2] == 6) {
                    lbl_1_bss_4930[player].step = 3;
                    lbl_1_bss_4930[player].piece = -1;
                }
            } else {
                lbl_1_bss_4930[player].step++;
            }
            break;

        case 2:
            if(lbl_1_bss_4794.mode[player+2] == 1 || lbl_1_bss_4794.mode[player+2] == 2) {
                if(lbl_1_bss_3700.board[player].held.kind != lbl_1_bss_4930[player].kind) {
                    lbl_1_bss_4930[player].step = 5;
                    break;
                }
                result = fn_1_9EE8(player, 1);
                if(result) {
                    lbl_1_bss_4930[player].mode = 3;
                    lbl_1_bss_4930[player].nextMode = 1;
                    lbl_1_bss_4930[player].wait = fn_1_92BC(player, 2);
                }
            } else if(lbl_1_bss_4930[player].wait++ > 20) {
                lbl_1_bss_4930[player].mode = 3;
                lbl_1_bss_4930[player].nextMode = 1;
                lbl_1_bss_4930[player].wait = fn_1_92BC(player, 1);
            }
            break;

        case 3:
            result = fn_1_9EE8(player, 2);
            if(result) {
                lbl_1_bss_4930[player].step++;
                lbl_1_bss_4930[player].wait = fn_1_92BC(player, 2);
            }
            break;

        case 4:
            lbl_1_bss_4930[player].wait--;
            if(lbl_1_bss_4930[player].wait <= 0) {
                lbl_1_bss_4930[player].step = 0;
            }
            break;

        case 5:
            result = fn_1_9EE8(player, 3);
            if(result) {
                lbl_1_bss_4930[player].step = 0;
                lbl_1_bss_4930[player].wait = fn_1_92BC(player, 1);
            }
            break;
    }
}

/* asm 1949-1977, 31 insns. Wait out the delay, then go on. */
void fn_1_B2C0(int player)
{
    lbl_1_bss_4930[player].wait--;
    if(lbl_1_bss_4930[player].wait <= 0) {
        lbl_1_bss_4930[player].mode = lbl_1_bss_4930[player].nextMode;
        lbl_1_bss_4930[player].step = 0;
    }
}

