/* maze.h -- the maze (maze.cpp): a 15x11 grid of electric walls over a floor of lit tiles, re-patterned from
 * mazedata every 2 s, drawn by two Hu3D hook models with immediate-mode GX.
 *
 * m509::CMaze: GC size 0x418 (gamemaster `li r3,0x418`; 8-aligned: u64 members). CGameObject +0x00 (vptr +8,
 * m_execFlags +0xC), empty CSingleton<CMaze> at +0x10 (shares the offset with m_floorHook). Vtable data_3268
 * {~, on_new_mode, on_update}; ms_pointer bss_34.
 * m509::CMazeSelector: the empty 1-byte singleton gamemaster creates (`new(1)`, inline ctor there) and never
 * frees; its only method setLayout is maze.cpp's (C224); ms_pointer bss_30 (maze.cpp defines both pointers,
 * selector first). maze.cpp does not include minigame.h. */
#ifndef M509_MAZE_H
#define M509_MAZE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"

namespace m509 {

enum { MAZE_W = 15, MAZE_H = 11 }; /* real cells; the arrays have one phantom column/row (16 x 12) */

class CMaze : public CGameObject, public CSingleton<CMaze> {
public:
    /* one cell (5 bytes; stride y 5, x 0x3C) */
    struct Cell {
        u8 wall;   /* +0 0x80 left-edge wall, 0x40 top-edge wall, 0x30 unused, 0x0F direction to the goal */
        u8 flags;  /* +1 0x80 flash rising, 0x10 touched this frame, low nibble character colour (0xF = two) */
        u8 light;  /* +2 tile light 0..255 */
        u8 hLife;  /* +3 intro walker: top-wall lifetime */
        u8 vLife;  /* +4 intro walker: left-wall lifetime */
    };
    /* an intro "snake" (5 bytes) */
    struct Walker {
        u8 respawn; /* +0 */
        u8 dir;     /* +1 0 -y, 1 +y, 2 -x, 3 +x */
        u8 unused;  /* +2 never read or written */
        u8 x;       /* +3 */
        u8 y;       /* +4 */
    };

    CMaze();                                   /* fn_1_5A7C */
    virtual ~CMaze();                          /* fn_1_5D8C kills both hooks; does not stop m_sfx (sheet R2) */
    virtual void on_new_mode(int mode);        /* fn_1_5E68 mode 3: stop m_sfx */
    virtual void on_update();                  /* fn_1_5EDC the state switch (jumptable data_323C) */
    void reset();                              /* fn_1_63D8 clear every cell, border walls, m_wallGrow 20 */
    bool blockedUp(int prev, int x, int y);
    bool blockedDown(int prev, int x, int y);
    bool blockedLeft(int prev, int x, int y);
    bool blockedRight(int prev, int x, int y);
    void walk();                               /* fn_1_6A58 move the three intro walkers */
    void stepWalls(int mode);                  /* fn_1_7244 walker lifetimes -> wall bits */
    void startClear(u8 chr);                   /* fn_1_73A4 a player reached the goal (player.cpp) */
    void openCell(u8 chr, int x, int y);       /* fn_1_73C8 unreferenced copy (inlined 4x in clearStep) */
    void clearStep();                          /* fn_1_7484 open a square ring around (7,5) every 8 frames */
    static void HookFloor(HU3DMODEL* model, Mtx* mtx); /* fn_1_785C layer 3 (reads ms_pointer, no assert) */
    static void HookWall(HU3DMODEL* model, Mtx* mtx);  /* fn_1_78AC layer 4 */
    void drawBoltH(int x, int y);              /* fn_1_78FC lightning along a top edge */
    void drawBoltV(int x, int y);              /* fn_1_8094 lightning along a left edge */
    void drawBolts();                          /* fn_1_8828 unreferenced copy (inlined twice in drawWallPass) */
    void drawGlowH(int x, int y);              /* fn_1_89C0 */
    void drawGlowV(int x, int y);              /* fn_1_8F80 */
    void drawGlowWalls();                      /* fn_1_9540 */
    void drawTile(float x, float z, u8 r, u8 g, u8 b, u8 a); /* fn_1_96E8 beveled tile (this unused) */
    void drawFloor();                          /* fn_1_A100 */
    void drawArrow(float cx, float cz, u8 cell); /* fn_1_A3C0 unreferenced copy (inlined in drawArrows) */
    void drawArrows();                         /* fn_1_A6EC debug flow-field view: dead (no caller) */
    void drawDarkness(int alpha);              /* fn_1_ABC4 unreferenced copy (inlined in drawWallPass) */
    void drawFloorPass(Mtx* mtx);              /* fn_1_AEAC */
    void drawWallPass(Mtx* mtx);               /* fn_1_AEF8 */
    void mirrorX();                            /* fn_1_B524 unreferenced copy (inlined in loadLayout) */
    void mirrorZ();                            /* fn_1_B6C8 unreferenced copy (inlined in loadLayout) */
    void loadLayout(u8* data, int mirror);     /* fn_1_B86C ignored while clearing; bit0 X-, bit1 Z-mirror */
    float frand();                             /* fn_1_BCAC u64 LCG, [0,1] */
    void markCell(u8 chr, float x, float z);   /* fn_1_BD44 player.cpp, every frame */
    u8 getCell(float x, float z);              /* fn_1_BE30 the cell byte (COM route code), 0 outside */
    u8 getWalls(float x, float z);             /* fn_1_BEE8 the four walls of a cell (0x80/0x40/8/4) */
    bool nearWall(float x, float z);           /* fn_1_C000 within 0.1 cell of a wall (retail R1 kept) */

    /* in-class inlines with no out-of-line copy (sheet §3): the cell clear and the border walls */
    void clearCells()
    {
        for (int y = 0; y < 12; y++) {
            for (int x = 0; x < 16; x++) {
                m_cell[x][y].wall = 0;
                m_cell[x][y].flags = 0;
                m_cell[x][y].vLife = 0;
                m_cell[x][y].hLife = 0;
                m_cell[x][y].light = 0;
            }
        }
    }
    void setBorder()
    {
        for (int x = 0; x < MAZE_W; x++) {
            m_cell[x][0].wall |= 0x40;
            m_cell[x][MAZE_H].wall |= 0x40;
        }
        for (int y = 0; y < MAZE_H; y++) {
            m_cell[0][y].wall |= 0x80;
            m_cell[MAZE_W][y].wall |= 0x80;
        }
    }

    HU3DMODELID m_floorHook; /* 0x010 Hu3DHookFuncCreate(HookFloor), layer 3, camera 1 */
    HU3DMODELID m_wallHook;  /* 0x012 Hu3DHookFuncCreate(HookWall), layer 4, camera 1 */
    bool m_wallsChanged;     /* 0x014 a walker wall is alive (intro): lightning only, no floor */
    int m_state;             /* 0x018 0..5 intro, 6 play (signed) */
    int m_darkAlpha;         /* 0x01C black overlay alpha (signed) */
    bool m_clearing;         /* 0x020 */
    int m_clearTimer;
    u8 m_clearChar;
    int m_frame;             /* 0x02C signed */
    int m_wallGrow;          /* 0x030 20 -> 0: new walls grow in */
    int m_sfx;               /* 0x034 HuAudFXPlay(0x690) handle, -1 once stopped */
    Cell m_cell[16][12];     /* 0x038 [x][y] */
    Walker m_walker[3];      /* 0x3F8 */
    u64 m_seedSaved;
    u64 m_seed;              /* 0x410 */
};

class CMazeSelector : public CSingleton<CMazeSelector> {
public:
    /* fn_1_C224: load layout n % 64 with a random mirror (n >= 0: irandom) */
    void setLayout(int n);
};

} // namespace m509

#ifndef __MWERKS__
template <> m509::CMazeSelector* CSingleton<m509::CMazeSelector>::ms_pointer; /* defined in maze.cpp */
template <> m509::CMaze* CSingleton<m509::CMaze>::ms_pointer;                 /* defined in maze.cpp */
#endif

#endif
