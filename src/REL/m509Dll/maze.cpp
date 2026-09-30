#include "REL/m509Dll/maze.h"
#include "REL/m509Dll/mazedata.h"
#include "REL/m509Dll/random.h"

namespace m509 {

/* the GX state every maze pass starts from ("setup S", sheet §3); 9540/ABC4/AEF8 insert a GXSetZMode */
static inline void SetupGX()
{
    GXSetNumTevStages(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetCullMode(GX_CULL_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetLineWidth(6, GX_TO_ZERO);
}

CMaze::CMaze()
{
    m_seed = m_seedSaved = 0x368B9170;
    m_state = 0;
    m_darkAlpha = 0;
    m_frame = 0;
    m_wallGrow = 0;
    m_clearing = false;
    m_wallsChanged = false;
    m_floorHook = Hu3DHookFuncCreate(HookFloor);
    Hu3DModelLayerSet(m_floorHook, 3);
    Hu3DModelCameraSet(m_floorHook, 1);
    m_wallHook = Hu3DHookFuncCreate(HookWall);
    Hu3DModelLayerSet(m_wallHook, 4);
    Hu3DModelCameraSet(m_wallHook, 1);
    clearCells();
    for (int i = 0; i < 3; i++) {
        m_walker[i].respawn = 1;
    }
    m_sfx = HuAudFXPlay(0x690);
}

/* does not stop m_sfx (sheet R2: only on_new_mode(3) does) */
CMaze::~CMaze()
{
    Hu3DModelKill(m_floorHook);
    Hu3DModelKill(m_wallHook);
}

void CMaze::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    switch (mode) {
    case 0:
    case 5:
        break;
    case 3:
        HuAudFXStop(m_sfx);
        m_sfx = -1;
        break;
    }
}

/* per frame: the tile lights, then the intro state machine (jumptable data_323C: write all 7 cases) */
void CMaze::on_update()
{
    if (m_sfx >= 0) {
        /* retail: the test is computed and dropped (sheet R3); CW still emits lwz/srwi/xori */
    }
    if ((m_frame & 1) == 0) {
        m_seedSaved = m_seed;
    }
    if (m_clearing) {
        clearStep();
    }
    for (int y = 0; y < 12; y++) {
        for (int x = 0; x < 16; x++) {
            int l;
            m_cell[x][y].flags &= 0xEF;
            if (m_cell[x][y].flags & 0x80) {
                l = (u8)m_cell[x][y].light; /* the (u8) is retail's extra clrlwi (O0) */
                l += 16;
                if (l > 255) {
                    m_cell[x][y].flags &= 0x7F; /* 0x7F, not ~0x80: clrlwi 25 */
                    l = 255;
                }
                m_cell[x][y].light = l;
            } else {
                l = m_cell[x][y].light;
                if (l != 0) {
                    l -= m_clearing ? 8 : 2;
                    if (l < 0) {
                        l = 0;
                    }
                    m_cell[x][y].light = l;
                }
            }
        }
    }
    switch (m_state) {
    case 0:
        if ((float)m_frame > 150.0f) {
            m_state++;
            HuAudFXPlayVol(0x68F, 0x48);
        }
        m_darkAlpha = 0xC0;
        break;
    case 1:
        if ((float)m_frame > 156.0f) {
            m_state++;
            HuAudFXPlayVol(0x68F, 0x48);
        }
        m_darkAlpha = 192.0f * ((float)m_frame - 150.0f) / 6.0;
        break;
    case 2:
        if ((float)m_frame > 162.0f) {
            m_state++;
        }
        m_darkAlpha = 192.0f * ((float)m_frame - 156.0f) / 6.0;
        break;
    case 3:
        if ((float)m_frame > 174.0f) {
            m_state++;
            HuAudFXPlayVol(0x68F, 0x48);
        }
        m_darkAlpha = 0xC0;
        break;
    case 4:
        if ((float)m_frame > 180.0f) {
            m_state++;
        }
        m_darkAlpha = 192.0f * ((float)m_frame - 174.0f) / 6.0;
        break;
    case 5:
        m_darkAlpha = 0;
        reset();
        m_state++;
        break;
    case 6:
        break;
    }
    if (m_state < 5) {
        stepWalls(m_state);
    }
    m_frame++;
    if (m_wallGrow > 0) {
        m_wallGrow--;
    }
}

void CMaze::reset()
{
    int x;
    int y;
    for (y = 0; y < 12; y++) {
        for (x = 0; x < 16; x++) {
            m_cell[x][y].wall = 0;
            m_cell[x][y].flags = 0;
            m_cell[x][y].vLife = 0;
            m_cell[x][y].hLife = 0;
            m_cell[x][y].light = 0;
        }
    }
    for (x = 0; x < MAZE_W; x++) {
        m_cell[x][0].wall |= 0x40;
        m_cell[x][MAZE_H].wall |= 0x40;
    }
    for (y = 0; y < MAZE_H; y++) {
        m_cell[0][y].wall |= 0x80;
        m_cell[MAZE_W][y].wall |= 0x80;
    }
    m_wallGrow = 20;
}

#define WALKER_WALL(x, y) m_cell[x][y].wall

bool CMaze::blockedUp(int prev, int x, int y)
{
    if (y <= 0) {
        return true;
    }
    switch (prev) {
    case 0:
        if (WALKER_WALL(x, y) & 0x40) {
            return true;
        }
        if (x > 0 && (WALKER_WALL(x - 1, y) & 0x40)) {
            return true;
        }
        break;
    case 2:
        if (WALKER_WALL(x, y) & 0x80) {
            return true;
        }
        if (WALKER_WALL(x, y - 1) & 0x80) {
            return true;
        }
        break;
    case 3:
        if (WALKER_WALL(x + 1, y) & 0x80) {
            return true;
        }
        if (WALKER_WALL(x + 1, y - 1) & 0x80) {
            return true;
        }
        break;
    }
    return false;
}

bool CMaze::blockedDown(int prev, int x, int y)
{
    if (y >= 10) {
        return true;
    }
    switch (prev) {
    case 1:
        if (WALKER_WALL(x, y + 1) & 0x40) {
            return true;
        }
        if (x > 0 && (WALKER_WALL(x - 1, y + 1) & 0x40)) {
            return true;
        }
        break;
    case 2:
        if (WALKER_WALL(x, y) & 0x80) {
            return true;
        }
        if (WALKER_WALL(x, y - 1) & 0x80) {
            return true;
        }
        break;
    case 3:
        if (WALKER_WALL(x + 1, y) & 0x80) {
            return true;
        }
        if (WALKER_WALL(x + 1, y - 1) & 0x80) {
            return true;
        }
        break;
    }
    return false;
}

bool CMaze::blockedLeft(int prev, int x, int y)
{
    if (x <= 0) {
        return true;
    }
    switch (prev) {
    case 2:
        if (WALKER_WALL(x, y) & 0x80) {
            return true;
        }
        if (y > 0 && (WALKER_WALL(x, y - 1) & 0x80)) {
            return true;
        }
        break;
    case 0:
        if (WALKER_WALL(x, y) & 0x40) {
            return true;
        }
        if (WALKER_WALL(x - 1, y) & 0x40) {
            return true;
        }
        break;
    case 1:
        if (WALKER_WALL(x, y + 1) & 0x40) {
            return true;
        }
        if (WALKER_WALL(x - 1, y + 1) & 0x40) {
            return true;
        }
        break;
    }
    return false;
}

bool CMaze::blockedRight(int prev, int x, int y)
{
    if (x >= 14) {
        return true;
    }
    switch (prev) {
    case 3:
        if (WALKER_WALL(x + 1, y) & 0x80) {
            return true;
        }
        if (y > 0 && (WALKER_WALL(x + 1, y - 1) & 0x80)) {
            return true;
        }
        break;
    case 0:
        if (WALKER_WALL(x, y) & 0x40) {
            return true;
        }
        if (WALKER_WALL(x - 1, y) & 0x40) {
            return true;
        }
        break;
    case 1:
        if (WALKER_WALL(x, y + 1) & 0x40) {
            return true;
        }
        if (WALKER_WALL(x - 1, y + 1) & 0x40) {
            return true;
        }
        break;
    case 2:
        break;
    }
    return false;
}

#undef WALKER_WALL

/* the three intro walkers: respawn at random, turn by s_turn (never reverses), stop (respawn) at a wall in
 * front, else move and leave a wall of lifetime 8 behind. s_turn: data_3258, emitted after the jumptable */
void CMaze::walk()
{
    static u8 s_turn[4][4] = { { 0, 0, 2, 3 }, { 1, 1, 2, 3 }, { 0, 1, 2, 2 }, { 0, 1, 3, 3 } };
    int i;
    for (i = 0; i < 3; i++) {
        if (m_walker[i].respawn == 1) {
            m_walker[i].respawn = 0;
            m_walker[i].dir = CRandom::irandom() & 3;
            m_walker[i].x = CRandom::irandom() % 15;
            m_walker[i].y = CRandom::irandom() % 11;
        }
    }
    for (i = 0; i < 3; i++) {
        int prev = m_walker[i].dir;
        int dir = m_walker[i].dir = s_turn[prev][CRandom::irandom() & 3];
        int x = m_walker[i].x;
        int y = m_walker[i].y;
        switch (dir) {
        case 0:
            if (blockedUp(prev, x, y)) {
                m_walker[i].respawn = 1;
            } else {
                y--;
                if (prev == 3) {
                    x++;
                }
            }
            break;
        case 1:
            if (blockedDown(prev, x, y)) {
                m_walker[i].respawn = 1;
            } else {
                if (prev == 1) {
                    y++;
                }
                if (prev == 3) {
                    x++;
                }
            }
            break;
        case 2:
            if (blockedLeft(prev, x, y)) {
                m_walker[i].respawn = 1;
            } else {
                x--;
                if (prev == 1) {
                    y++;
                }
            }
            break;
        case 3:
            if (blockedRight(prev, x, y)) {
                m_walker[i].respawn = 1;
            } else {
                if (prev == 1) {
                    y++;
                }
                if (prev == 3) {
                    x++;
                }
            }
            break;
        }
        m_walker[i].x = x;
        m_walker[i].y = y;
        if (m_walker[i].respawn == 0) {
            if (dir < 2) {
                m_cell[x][y].vLife = 8;
            } else {
                m_cell[x][y].hLife = 8;
            }
        }
    }
}

void CMaze::stepWalls(int mode)
{
    if (mode == 0) {
        walk();
    }
    int x;
    int y;
    m_wallsChanged = false;
    for (y = 0; y <= MAZE_H; y++) {
        for (x = 0; x <= MAZE_W; x++) {
            m_cell[x][y].wall &= 0x3F;
            if (m_cell[x][y].hLife != 0) {
                m_cell[x][y].hLife--;
                m_cell[x][y].wall |= 0x40;
                m_wallsChanged = true;
            }
            if (m_cell[x][y].vLife != 0) {
                m_cell[x][y].vLife--;
                m_cell[x][y].wall |= 0x80;
                m_wallsChanged = true;
            }
        }
    }
}

void CMaze::startClear(u8 chr)
{
    if (!m_clearing) {
        m_clearing = true;
        m_clearTimer = 0;
        m_clearChar = chr;
    }
}

/* a goal-coloured, wall-less cell */
void CMaze::openCell(u8 chr, int x, int y)
{
    if (x < 0 || x >= MAZE_W || y < 0 || y >= MAZE_H) {
        return;
    }
    m_cell[x][y].wall = 5;
    m_cell[x + 1][y].wall &= ~0x80;
    m_cell[x][y + 1].wall &= ~0x40;
    m_cell[x][y].flags = chr | 0x80;
    m_cell[x][y].light = 0;
}

/* every 8 frames, open the square ring of radius timer/8 around the goal (7,5); the timer is unbounded */
void CMaze::clearStep()
{
    if ((m_clearTimer & 7) == 0) {
        int r = m_clearTimer >> 3;
        int x;
        int y;
        int cx = 7;
        int cy = 5;
        for (x = cx - r; x <= cx + r; x++) {
            openCell(m_clearChar, x, cy - r);
            openCell(m_clearChar, x, cy + r);
        }
        for (y = cy - r; y <= cy + r; y++) {
            openCell(m_clearChar, cx - r, y);
            openCell(m_clearChar, cx + r, y);
        }
    }
    m_clearTimer++;
}

void CMaze::HookFloor(HU3DMODEL* model, Mtx* mtx)
{
    Hu3DModelObjDrawInit();
    CMaze* maze = CSingleton<CMaze>::GetInstancePtr();
    maze->drawFloorPass(mtx);
}

void CMaze::HookWall(HU3DMODEL* model, Mtx* mtx)
{
    Hu3DModelObjDrawInit();
    CMaze* maze = CSingleton<CMaze>::GetInstancePtr();
    maze->drawWallPass(mtx);
}

/* a lightning bolt along the top edge of (x,y): two 4-vertex fans through three jittered points (and two
 * points at 0.6 of the jitter) from the edge's start to its end; the jitter's height amplitude grows while new
 * walls grow in (m_wallGrow) */
void CMaze::drawBoltH(int x, int y)
{
    Vec pts[5];
    Vec base;
    base.x = 220.0f * x - 1650.0f;
    base.y = 100.0f * (2.0f + frand());
    base.z = 220.0f * y - 1210.0f;
    float amp = 0.8f + m_wallGrow / 10.0f;
    float half = amp / 2.0f;
    int i;
    for (i = 0; i < 3; i++) {
        pts[i].x = 100.0f * (0.6f * frand() - 0.3f);
        pts[i].y = 100.0f * (0.6f * frand() - 0.3f);
        pts[i].z = 100.0f * (amp * frand() - half);
    }
    pts[3].x = 0.6f * pts[0].x;
    pts[3].y = 0.6f * pts[0].y;
    pts[3].z = 0.6f * pts[0].z;
    pts[4].x = 0.6f * pts[2].x;
    pts[4].y = 0.6f * pts[2].y;
    pts[4].z = 0.6f * pts[2].z;
    for (i = 0; i < 5; i++) {
        pts[i].y += base.y;
        pts[i].z += base.z;
    }
    pts[0].x += 55.0f + base.x;
    pts[1].x += 110.0f + base.x;
    pts[2].x += 165.0f + base.x;
    pts[3].x += 55.0f + base.x;
    pts[4].x += 165.0f + base.x;
    GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 4);
    GXPosition3f32(pts[0].x, pts[0].y, pts[0].z);
    GXColor4u8(0, 255, 255, 255);
    GXPosition3f32(base.x, base.y, base.z);
    GXColor4u8(0, 0, 255, 255);
    GXPosition3f32(pts[3].x, pts[3].y, pts[3].z);
    GXColor4u8(0, 0, 255, 255);
    GXPosition3f32(pts[1].x, pts[1].y, pts[1].z);
    GXColor4u8(255, 255, 255, 255);
    GXEnd();
    GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 4);
    GXPosition3f32(pts[2].x, pts[2].y, pts[2].z);
    GXColor4u8(0, 255, 255, 255);
    GXPosition3f32(pts[1].x, pts[1].y, pts[1].z);
    GXColor4u8(255, 255, 255, 255);
    GXPosition3f32(pts[4].x, pts[4].y, pts[4].z);
    GXColor4u8(0, 0, 255, 255);
    GXPosition3f32(base.x + 220.0f, base.y, base.z);
    GXColor4u8(0, 0, 255, 255);
    GXEnd();
}

/* drawBoltH's twin along the left edge of (x,y) (z steps; the jitter's amplitude is on x) */
void CMaze::drawBoltV(int x, int y)
{
    Vec pts[5];
    Vec base;
    base.x = 220.0f * x - 1650.0f;
    base.y = 100.0f * (2.0f + frand());
    base.z = 220.0f * y - 1210.0f;
    float amp = 0.8f + m_wallGrow / 10.0f;
    float half = amp / 2.0f;
    int i;
    for (i = 0; i < 3; i++) {
        pts[i].z = 100.0f * (amp * frand() - half); /* retail: the amplitude is along the edge here */
        pts[i].y = 100.0f * (0.6f * frand() - 0.3f);
        pts[i].x = 100.0f * (0.6f * frand() - 0.3f);
    }
    pts[3].x = 0.6f * pts[0].x;
    pts[3].y = 0.6f * pts[0].y;
    pts[3].z = 0.6f * pts[0].z;
    pts[4].x = 0.6f * pts[2].x;
    pts[4].y = 0.6f * pts[2].y;
    pts[4].z = 0.6f * pts[2].z;
    for (i = 0; i < 5; i++) {
        pts[i].x += base.x;
        pts[i].y += base.y;
    }
    pts[0].z += 55.0f + base.z;
    pts[1].z += 110.0f + base.z;
    pts[2].z += 165.0f + base.z;
    pts[3].z += 55.0f + base.z;
    pts[4].z += 165.0f + base.z;
    GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 4);
    GXPosition3f32(pts[0].x, pts[0].y, pts[0].z);
    GXColor4u8(255, 255, 255, 255);
    GXPosition3f32(base.x, base.y, base.z);
    GXColor4u8(0, 0, 255, 255);
    GXPosition3f32(pts[3].x, pts[3].y, pts[3].z);
    GXColor4u8(0, 0, 255, 255);
    GXPosition3f32(pts[1].x, pts[1].y, pts[1].z);
    GXColor4u8(255, 255, 255, 255);
    GXEnd();
    GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 4);
    GXPosition3f32(pts[2].x, pts[2].y, pts[2].z);
    GXColor4u8(255, 255, 255, 255);
    GXPosition3f32(pts[1].x, pts[1].y, pts[1].z);
    GXColor4u8(255, 255, 255, 255);
    GXPosition3f32(pts[4].x, pts[4].y, pts[4].z);
    GXColor4u8(0, 0, 255, 255);
    GXPosition3f32(base.x, base.y, base.z + 220.0f);
    GXColor4u8(0, 0, 255, 255);
    GXEnd();
}

/* every wall as lightning (unreferenced copy; inlined twice in drawWallPass) */
void CMaze::drawBolts()
{
    int x;
    int y;
    u8 wall;
    SetupGX();
    for (y = 0; y <= MAZE_H; y++) {
        for (x = 0; x <= MAZE_W; x++) {
            wall = m_cell[x][y].wall;
            if (x < MAZE_W && (wall & 0x40)) {
                drawBoltH(x, y);
            }
            if (y < MAZE_H && (wall & 0x80)) {
                drawBoltV(x, y);
            }
        }
    }
}

void CMaze::drawGlowH(int x, int y)
{
    float fx = 220.0f * x - 1650.0f;
    float fz = 220.0f * y - 1210.0f;
    float g = (float)(20 - m_wallGrow) / 20.0f;
    if (y <= 0 || y >= MAZE_H) {
        g = 1.0f;
    }
    float x0 = fx;
    float x1 = fx + 220.0f * g;
    float y0 = 280.0f;
    float y1 = 170.0f;
    float z0 = fz;
    float z1 = fz;
    float t = 7.0f;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(x0, y0, z0 + t);
    GXColor4u8(0, 255, 255, 128);
    GXPosition3f32(x1, y0, z0 + t);
    GXColor4u8(0, 255, 255, 128);
    GXPosition3f32(x1, y1, z1 + t);
    GXColor4u8(0, 0, 255, 0);
    GXPosition3f32(x0, y1, z1 + t);
    GXColor4u8(0, 0, 255, 0);
    GXEnd();
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(x0, y0, z0 - t);
    GXColor4u8(0, 255, 255, 128);
    GXPosition3f32(x1, y0, z0 - t);
    GXColor4u8(0, 255, 255, 128);
    GXPosition3f32(x1, y0, z1 + t);
    GXColor4u8(0, 255, 255, 128);
    GXPosition3f32(x0, y0, z1 + t);
    GXColor4u8(0, 255, 255, 128);
    GXEnd();
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(x1, y0, z0 - t);
    GXColor4u8(0, 255, 255, 128);
    GXPosition3f32(x0, y0, z0 - t);
    GXColor4u8(0, 255, 255, 128);
    GXPosition3f32(x0, y1, z1 - t);
    GXColor4u8(0, 0, 255, 0);
    GXPosition3f32(x1, y1, z1 - t);
    GXColor4u8(0, 0, 255, 0);
    GXEnd();
}

/* drawGlowH's twin on the left edge of (x,y) (the border test on x) */
void CMaze::drawGlowV(int x, int y)
{
    float fx = 220.0f * x - 1650.0f;
    float fz = 220.0f * y - 1210.0f;
    float x0 = fx;
    float x1 = fx;
    float g = (float)(20 - m_wallGrow) / 20.0f;
    if (x <= 0 || x >= MAZE_W) {
        g = 1.0f;
    }
    float y0 = 280.0f;
    float y1 = 170.0f;
    float z0 = fz;
    float z1 = fz + 220.0f * g;
    float t = 7.0f;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(x0 - t, y0, z0);
    GXColor4u8(0, 255, 255, 128);
    GXPosition3f32(x1 - t, y0, z1);
    GXColor4u8(0, 255, 255, 128);
    GXPosition3f32(x1 - t, y1, z1);
    GXColor4u8(0, 0, 255, 0);
    GXPosition3f32(x0 - t, y1, z0);
    GXColor4u8(0, 0, 255, 0);
    GXEnd();
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(x0 - t, y0, z0);
    GXColor4u8(0, 255, 255, 128);
    GXPosition3f32(x1 + t, y0, z0);
    GXColor4u8(0, 255, 255, 128);
    GXPosition3f32(x1 + t, y0, z1);
    GXColor4u8(0, 255, 255, 128);
    GXPosition3f32(x0 - t, y0, z1);
    GXColor4u8(0, 255, 255, 128);
    GXEnd();
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(x1 + t, y0, z1);
    GXColor4u8(0, 255, 255, 128);
    GXPosition3f32(x0 + t, y0, z0);
    GXColor4u8(0, 255, 255, 128);
    GXPosition3f32(x0 + t, y1, z0);
    GXColor4u8(0, 0, 255, 0);
    GXPosition3f32(x1 + t, y1, z1);
    GXColor4u8(0, 0, 255, 0);
    GXEnd();
}

/* setup S with the depth test on and back faces culled (retail sets them in place of GXSetCullMode(NONE)), then
 * every wall's glow */
void CMaze::drawGlowWalls()
{
    GXSetNumTevStages(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetLineWidth(6, GX_TO_ZERO);
    int x, y;
    for (y = 0; y <= MAZE_H; y++) {
        for (x = 0; x <= MAZE_W; x++) {
            u8 wall = m_cell[x][y].wall;
            if (x < MAZE_W && (wall & 0x40)) {
                drawGlowH(x, y);
            }
            if (y < MAZE_H && (wall & 0x80)) {
                drawGlowV(x, y);
            }
        }
    }
}

/* one beveled floor tile at (x, z) (`this` unused): the inner top (inset 11) in alpha a, then the four bevel
 * sides down to y 115 in alpha a*6/8, 5/8, 4/8, 3/8. Corners 0..3 outer, 4..7 inner */
void CMaze::drawTile(float x, float z, u8 r, u8 g, u8 b, u8 a)
{
    float px[8];
    float pz[8];
    px[0] = x;
    px[1] = 220.0f + x;
    px[2] = px[1];
    px[3] = x;
    px[4] = 11.0f + px[0];
    px[5] = px[1] - 11.0f;
    px[6] = px[5];
    px[7] = px[4];
    pz[0] = z;
    pz[1] = pz[0];
    pz[2] = 220.0f + z;
    pz[3] = pz[2];
    pz[4] = 11.0f + pz[0];
    pz[5] = pz[4];
    pz[6] = pz[2] - 11.0f;
    pz[7] = pz[6];
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(px[4], 124.0f, pz[4]);
    GXColor4u8(r, g, b, a);
    GXPosition3f32(px[5], 124.0f, pz[5]);
    GXColor4u8(r, g, b, a);
    GXPosition3f32(px[6], 124.0f, pz[6]);
    GXColor4u8(r, g, b, a);
    GXPosition3f32(px[7], 124.0f, pz[7]);
    GXColor4u8(r, g, b, a);
    GXEnd();
    float yb = 115.0f;
    int ia = a;
    int alpha = ia * 6 / 8;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(px[0], yb, pz[0]);
    GXColor4u8(r, g, b, alpha);
    GXPosition3f32(px[1], yb, pz[1]);
    GXColor4u8(r, g, b, alpha);
    GXPosition3f32(px[5], 124.0f, pz[5]);
    GXColor4u8(r, g, b, alpha);
    GXPosition3f32(px[4], 124.0f, pz[4]);
    GXColor4u8(r, g, b, alpha);
    GXEnd();
    alpha = ia * 5 / 8;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(px[0], yb, pz[0]);
    GXColor4u8(r, g, b, alpha);
    GXPosition3f32(px[4], 124.0f, pz[4]);
    GXColor4u8(r, g, b, alpha);
    GXPosition3f32(px[7], 124.0f, pz[7]);
    GXColor4u8(r, g, b, alpha);
    GXPosition3f32(px[3], yb, pz[3]);
    GXColor4u8(r, g, b, alpha);
    GXEnd();
    alpha = ia * 4 / 8;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(px[5], 124.0f, pz[5]);
    GXColor4u8(r, g, b, alpha);
    GXPosition3f32(px[1], yb, pz[1]);
    GXColor4u8(r, g, b, alpha);
    GXPosition3f32(px[2], yb, pz[2]);
    GXColor4u8(r, g, b, alpha);
    GXPosition3f32(px[6], 124.0f, pz[6]);
    GXColor4u8(r, g, b, alpha);
    GXEnd();
    alpha = ia * 3 / 8;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(px[7], 124.0f, pz[7]);
    GXColor4u8(r, g, b, alpha);
    GXPosition3f32(px[6], 124.0f, pz[6]);
    GXColor4u8(r, g, b, alpha);
    GXPosition3f32(px[2], yb, pz[2]);
    GXColor4u8(r, g, b, alpha);
    GXPosition3f32(px[3], yb, pz[3]);
    GXColor4u8(r, g, b, alpha);
    GXEnd();
}

/* lbl_1_rodata_FC: the character colours by CHARNO_* (0..12; 13 spare; only rgb read) */
static const GXColor s_charColor[14] = {
    { 0xFE, 0x00, 0x00, 0xFF }, { 0x00, 0x00, 0xFE, 0xFF }, { 0xFF, 0x7B, 0xDE, 0xFF }, { 0x00, 0xFF, 0x00, 0xFF },
    { 0x7D, 0x00, 0xBE, 0xFF }, { 0xFF, 0xFF, 0x00, 0xFF }, { 0x3F, 0x43, 0x8C, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0x00, 0xFF, 0xFF, 0xFF }, { 0xFF, 0x60, 0x16, 0xFF }, { 0xFF, 0x50, 0x50, 0xFF }, { 0x50, 0xFF, 0x50, 0xFF },
    { 0x50, 0x50, 0xFF, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF },
};

/* every lit tile in its character colour (0xF: two players this frame -> a yellow flicker) */
/* setup S written out: through SetupGX() CW auto-inlines this body into drawFloorPass, retail calls it */
void CMaze::drawFloor()
{
    GXSetNumTevStages(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetCullMode(GX_CULL_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetLineWidth(6, GX_TO_ZERO);
    int x, y;
    for (y = 0; y < MAZE_H; y++) {
        for (x = 0; x < MAZE_W; x++) {
            u8 light = m_cell[x][y].light;
            u8 idx = m_cell[x][y].flags & 0xF;
            if (light != 0) {
                float x0 = 220.0f * x - 1650.0f;
                float z0 = 220.0f * y - 1210.0f;
                if (idx != 0xF) {
                    drawTile(x0, z0, s_charColor[idx].r, s_charColor[idx].g, s_charColor[idx].b, light >> 1);
                } else {
                    u8 blue = (m_frame & 0xF) << 4;
                    drawTile(x0, z0, 255, 255, blue, light >> 1);
                }
            }
        }
    }
}

/* lbl_1_rodata_134: 4 arrows (route codes 1..4) x 4 fan vertices */
static const Vec s_arrow[16] = {
    { 0.0f, 0.0f, -80.0f }, { -40.0f, 0.0f, 80.0f }, { 0.0f, 0.0f, 40.0f }, { 40.0f, 0.0f, 80.0f },
    { 0.0f, 0.0f, 80.0f }, { -40.0f, 0.0f, -80.0f }, { 0.0f, 0.0f, -40.0f }, { 40.0f, 0.0f, -80.0f },
    { -80.0f, 0.0f, 0.0f }, { 80.0f, 0.0f, 40.0f }, { 40.0f, 0.0f, 0.0f }, { 80.0f, 0.0f, -40.0f },
    { 80.0f, 0.0f, 0.0f }, { -80.0f, 0.0f, 40.0f }, { -40.0f, 0.0f, 0.0f }, { -80.0f, 0.0f, -40.0f },
};

/* one route arrow (the low 3 bits of a cell byte, 1..4) as a fan at y 300 around (cx, cz) (unreferenced copy;
 * inlined in drawArrows) */
void CMaze::drawArrow(float cx, float cz, u8 cell)
{
    int t = cell & 7;
    if (t > 4 || t == 0) {
        return;
    }
    t--;
    t *= 4;
    GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 4);
    GXPosition3f32(cx + s_arrow[t].x, 300.0f, cz + s_arrow[t].z);
    GXColor4u8(255, 255, 0, 128);
    GXPosition3f32(cx + s_arrow[t + 1].x, 300.0f, cz + s_arrow[t + 1].z);
    GXColor4u8(255, 0, 0, 128);
    GXPosition3f32(cx + s_arrow[t + 2].x, 300.0f, cz + s_arrow[t + 2].z);
    GXColor4u8(255, 0, 0, 128);
    GXPosition3f32(cx + s_arrow[t + 3].x, 300.0f, cz + s_arrow[t + 3].z);
    GXColor4u8(255, 0, 0, 128);
    GXEnd();
}

/* STUB (fn_1_A6EC, 310 insns; dead debug view): setup S; every 15x11 cell's drawArrow at its centre (+110) */

/* debug view of the route codes: every cell's arrow at its centre (dead: nothing calls it) */
void CMaze::drawArrows()
{
    SetupGX();
    int x, y;
    for (y = 0; y < MAZE_H; y++) {
        for (x = 0; x < MAZE_W; x++) {
            float cx = 110.0f + (220.0f * x - 1650.0f);
            float cz = 110.0f + (220.0f * y - 1210.0f);
            drawArrow(cx, cz, m_cell[x][y].wall);
        }
    }
}

void CMaze::drawDarkness(int alpha)
{
    if (alpha > 0) {
        GXSetNumTevStages(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetNumChans(1);
        GXSetNumTexGens(0);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        GXSetCullMode(GX_CULL_NONE);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
        GXSetZMode(GX_TRUE, GX_GREATER, GX_FALSE);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetLineWidth(6, GX_TO_ZERO);
        int black = 0;
        GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 4);
        GXPosition3f32(-3000.0f, -200.0f, -3000.0f);
        GXColor4u8(black, black, black, alpha);
        GXPosition3f32(3000.0f, -200.0f, -3000.0f);
        GXColor4u8(black, black, black, alpha);
        GXPosition3f32(3000.0f, -200.0f, 3000.0f);
        GXColor4u8(black, black, black, alpha);
        GXPosition3f32(-3000.0f, -200.0f, 3000.0f);
        GXColor4u8(black, black, black, alpha);
        GXEnd();
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    }
}

void CMaze::drawFloorPass(Mtx* mtx)
{
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    if (!m_wallsChanged) {
        drawFloor();
    }
}

/* the same seed for both passes and two consecutive frames: the lightning holds still for 2 frames */
void CMaze::drawWallPass(Mtx* mtx)
{
    m_seed = m_seedSaved;
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    drawDarkness(m_darkAlpha);
    if (m_wallsChanged) {
        drawBolts();
    } else {
        drawBolts();
        drawGlowWalls();
    }
}

/* lbl_1_rodata_204 / 20A: the direction nibble under an X / a Z mirror */
static const u8 s_mirrorX[6] = { 0, 1, 2, 4, 3, 5 };
static const u8 s_mirrorZ[6] = { 0, 2, 1, 3, 4, 5 };

/* mirror the layout left-right (unreferenced copy; inlined in loadLayout): pass 1 swaps the cells x <-> 14-x with
 * their route nibbles mirrored and top walls; pass 2 swaps the left walls x <-> 15-x (a wall is on the left edge) */
void CMaze::mirrorX()
{
    int x, y;
    u8 a, b, na, nb;
    for (y = 0; y < MAZE_H; y++) {
        for (x = 0; x < 8; x++) {
            a = m_cell[x][y].wall;
            b = m_cell[14 - x][y].wall;
            na = (a & 0xB0) | (s_mirrorX[b & 0xF] | (b & 0x40));
            nb = (b & 0xB0) | (s_mirrorX[a & 0xF] | (a & 0x40));
            m_cell[x][y].wall = na;
            m_cell[14 - x][y].wall = nb;
        }
    }
    for (y = 0; y < MAZE_H; y++) {
        for (x = 0; x < 8; x++) {
            a = m_cell[x][y].wall;
            b = m_cell[15 - x][y].wall;
            na = (b & 0x80) | (a & ~0x80);
            nb = (a & 0x80) | (b & ~0x80);
            m_cell[x][y].wall = na;
            m_cell[15 - x][y].wall = nb;
        }
    }
}

/* mirror the layout front-back (unreferenced copy; inlined in loadLayout): y <-> 10-y with the nibbles and left
 * walls, then the top walls y <-> 11-y */
void CMaze::mirrorZ()
{
    int x, y;
    u8 a, b, na, nb;
    for (y = 0; y < 6; y++) {
        for (x = 0; x < MAZE_W; x++) {
            a = m_cell[x][y].wall;
            b = m_cell[x][10 - y].wall;
            na = (a & 0x70) | (s_mirrorZ[b & 0xF] | (b & 0x80));
            nb = (b & 0x70) | (s_mirrorZ[a & 0xF] | (a & 0x80));
            m_cell[x][y].wall = na;
            m_cell[x][10 - y].wall = nb;
        }
    }
    for (y = 0; y < 6; y++) {
        for (x = 0; x < MAZE_W; x++) {
            a = m_cell[x][y].wall;
            b = m_cell[x][11 - y].wall;
            na = (b & 0x40) | (a & ~0x40);
            nb = (a & 0x40) | (b & ~0x40);
            m_cell[x][y].wall = na;
            m_cell[x][11 - y].wall = nb;
        }
    }
}

/* ignored while the goal ring opens; 192 bytes y-major into the wall bytes, mirrors, border, regrow */
void CMaze::loadLayout(u8* data, int mirror)
{
    if (m_clearing) {
        return;
    }
    u8* p = data;
    int x, y;
    for (y = 0; y <= MAZE_H; y++) {
        for (x = 0; x <= MAZE_W; x++) {
            m_cell[x][y].wall = *p++;
        }
    }
    if (mirror & 1) {
        mirrorX();
    }
    if (mirror & 2) {
        mirrorZ();
    }
    for (x = 0; x < MAZE_W; x++) {
        m_cell[x][0].wall |= 0x40;
        m_cell[x][MAZE_H].wall |= 0x40;
    }
    for (y = 0; y < MAZE_H; y++) {
        m_cell[0][y].wall |= 0x80;
        m_cell[MAZE_W][y].wall |= 0x80;
    }
    m_wallGrow = 20;
}

float CMaze::frand()
{
    m_seed = m_seed * 0x41C64E6D + 1234;
    int r = ((u32)m_seed >> 16) & 0x7FFF;
    return (float)r / 32767.0f;
}

/* a player's tile lights in its colour; a second player on it in the same frame -> 0xF (yellow flicker) */
void CMaze::markCell(u8 chr, float x, float z)
{
    if (!m_clearing && m_state >= 5) {
        int cx = (x + 1650.0f) / 220.0f;
        int cz = (z + 1210.0f) / 220.0f;
        if (cx >= 0 && cx < MAZE_W && cz >= 0 && cz < MAZE_H) {
            if (m_cell[cx][cz].flags & 0x10) {
                chr = 0xF;
            }
            m_cell[cx][cz].flags = chr | 0x90;
        }
    }
}

/* the cell byte under (x, z) (walls + the COM route nibble), 0 outside */
u8 CMaze::getCell(float x, float z)
{
    int cx = (x + 1650.0f) / 220.0f;
    int cz = (z + 1210.0f) / 220.0f;
    u8 ret = 0;
    if (cx >= 0 && cx < MAZE_W && cz >= 0 && cz < MAZE_H) {
        ret = m_cell[cx][cz].wall;
    }
    return ret;
}

/* the four walls of the cell under (x, z): its own left/top (0x80/0x40), the right (8) and bottom (4) ones from its
 * neighbours; 0 outside */
u8 CMaze::getWalls(float x, float z)
{
    u8 ret;
    int cx = (x + 1650.0f) / 220.0f;
    int cz = (z + 1210.0f) / 220.0f;
    ret = 0;
    if (cx >= 0 && cx < MAZE_W && cz >= 0 && cz < MAZE_H) {
        ret = m_cell[cx][cz].wall & 0xC0;
        if (m_cell[cx + 1][cz].wall & 0x80) {
            ret |= 8;
        }
        if (m_cell[cx][cz + 1].wall & 0x40) {
            ret |= 4;
        }
    }
    return ret;
}

/* within 0.1 cell of one of the cell's walls. Retail bug R1 kept: fx > 0.9 ASSIGNS the right wall, dropping the
 * left/top results */
bool CMaze::nearWall(float x, float z)
{
    float fx = 1650.0f + x;
    float fz = 1210.0f + z;
    int cx = fx / 220.0f;
    int cz = fz / 220.0f;
    int w = 0;
    if (cx < 0 || cx >= MAZE_W || cz < 0 || cz >= MAZE_H) {
        return false;
    }
    fx = (fx - 220.0f * cx) / 220.0f;
    fz = (fz - 220.0f * cz) / 220.0f;
    if (fx < 0.1f) {
        w = m_cell[cx][cz].wall & 0x80;
    }
    if (fz < 0.1f) {
        w |= m_cell[cx][cz].wall & 0x40;
    }
    if (fx > 0.9f) {
        w = m_cell[cx + 1][cz].wall & 0x80;
    }
    if (fz > 0.9f) {
        w |= m_cell[cx][cz + 1].wall & 0x40;
    }
    return w > 0;
}

void CMazeSelector::setLayout(int n)
{
    n %= MAZE_LAYOUTS;
    CSingleton<CMaze>::GetInstance()->loadLayout(mazeData[n][0], CRandom::irandom() & 3);
}

} // namespace m509

/* bss_30 / bss_34: both singleton pointers at the end of maze's .bss, the selector's first (sheet §4). The
 * selector's is referenced only by gamemaster; maze.cpp precedes it in the link order. */
template <> m509::CMazeSelector* CSingleton<m509::CMazeSelector>::ms_pointer = 0;
template <> m509::CMaze* CSingleton<m509::CMaze>::ms_pointer = 0;
