/* player.cpp -- m509::CPlayer (the four maze racers). CStage is stage.cpp (its own TU: see stage.h). Bodies
 * marked STUB are the function forks' (the sheet's behaviour is in the comment); the rest are from
 * player_random_startspr.md §C (m536/m512 shapes where marked EXACT). Lines in stubs that set a PTMF or pass a
 * string are retail's and place the .data constants in retail order.
 * The ctor's assert is on line 148 (its __LINE__ is an immediate; "player.cpp" is in .data): a #line holds it. */
#include "REL/mgcpp/minigame.h"
#include "REL/mgcpp/random.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/m509Dll/player.h"
#include "REL/m509Dll/camera.h"
#include "REL/m509Dll/maze.h"
#include "REL/m509Dll/startspr.h"

namespace m509 {

/* .bss after the header triple, in definition order: s_winner 94, then the list A4 (its chain 98) */
static CPlayer* s_winner; /* lbl_1_bss_94: the only goal player (CheckGoal), else 0 */
TLinkList<CPlayer> CPlayer::list;

/* EXACT m536 9B50 */
float CPlayer::SubAngle(float a, float b)
{
    int ia = DegToAngle(a);
    int ib = DegToAngle(b);
    int d = AngleSub(ia, ib);
    return AngleToDeg(d);
}

/* EXACT m536 9C08 */
float CPlayer::SubAngleMax(float a, float b, float max)
{
    float d = SubAngle(a, b);
    float ret;
    if (d < -max) {
        ret = -max;
    } else if (d > max) {
        ret = max;
    } else {
        ret = d;
    }
    return ret;
}

/* the four corners: 0 (-1540,125,-1100), 1 (1540,125,-1100), 2 (-1540,125,1100), 3+ (1540,125,1100) */
void CPlayer::GetStartPos(Vec* pos, int idx)
{
    float x = 1540.0f;
    float z = 1100.0f;
    switch (idx) {
    case 0:
        z = -z;
        x = -x;
        break;
    case 1:
        z = -z;
        break;
    case 2:
        x = -x;
        break;
    }
    SetVec(pos, x, 125.0f, z);
}

/* EXACT m536 A3A0 (the implicit ~CPlayer inlines: vector free, ~CModel, ~CLinkNode) */
void CPlayer::Close()
{
    while (!list.isEmpty()) {
        CPlayer* p = list.last();
        delete p;
    }
}

/* DRAFT from player.s F1FC (219 insns); the fork verifies it */
CPlayer::CPlayer(int idx) : m_state(0), m_model(GwPlayerConf[idx].charNo, 1)
{
    insertBack(&list);
    m_idx = idx;
    m_charNo = GwPlayerConf[idx].charNo;
    m_dif = GwPlayerConf[idx].dif;
    m_padNo = (GwPlayerConf[idx].type != 0) ? -1 : GwPlayerConf[idx].padNo;
    m_yaw = m_targetYaw = 0.0f;
    m_unk20 = false;
    m_motion = -1;
    m_pushTimer = 0;
    m_stun = 0;
    m_cell = -1;
    m_goal = false;
    m_blinkOff = false;
    m_frame = 0;
    m_comWait = 0;
    m_mot_id.clear();
    m_mot_id.reserve(NUMBEROF_MOTION);
    addMotion(0x8C0000);           /* 0 idle */
    s16 mot = addMotion(0x8C0001); /* 1 walk */
    CharNpcDustVoiceOffSet(m_model.id(), mot, 0);
    mot = addMotion(0x8C0002); /* 2 run */
    CharNpcDustVoiceOffSet(m_model.id(), mot, 1);
    addMotion(0x8C0006); /* 3 win pose */
    addMotion(0x8C0031); /* 4 lose pose */
    addMotion(0x8C0024); /* 5 stunned */
    /* retail's player.cpp:148 (its __LINE__ is an immediate): CStage's move to stage.cpp took 40 lines above */
#line 148
    assert(m_mot_id.size() == NUMBEROF_MOTION);
    CharMotionDataClose(m_charNo);
    Hu3DModelLayerSet(m_model.id(), 3);
    Hu3DModelCameraSet(m_model.id(), 1);
    GetStartPos(&m_pos, idx);
    m_model.setPos(&m_pos);
    setProc(&CPlayer::procInit);
}

s16 CPlayer::addMotion(u32 dataNum)
{
    s16 id = CharMotionCreate(m_charNo, dataNum);
    m_mot_id.push_back(id);
    return id;
}

/* EXACT m536 AB28 minus the rotate SE: update every player, then rotate the list (update order changes) */
void CPlayer::UpdateAll()
{
    TLinkList<CPlayer>::exec(&list, Update);
    CPlayer* p = list.begin();
    if (p != list.end()) {
        p->unlink();
        p->insertBack(&list);
    }
}

bool CPlayer::CheckGoal()
{
    CPlayer* p = list.begin();
    CLinkNode* e = list.end();
    s_winner = 0;
    int n = 0;
    for (; p != e; p = p->next()) {
        if (p->m_goal) {
            CMinigameCore::AddWinner(p->m_idx);
            s_winner = p;
            n++;
        }
    }
    if (n == 0) {
        return false;
    }
    if (n != 1) {
        s_winner = 0;
    }
    return true;
}

void CPlayer::StartWin()
{
    if (s_winner) {
        CSingleton<CCameraObj>::GetInstance()->startFinish();
    }
    CPlayer* p = list.begin();
    CLinkNode* e = list.end();
    for (; p != e; p = p->next()) {
        HU3DMODELID id = p->m_model.id();
        Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
        p->m_blinkOff = false;
        p->setProc(&CPlayer::procWin);
        p->m_state = 1;
    }
}

void CPlayer::ResetCells()
{
    CPlayer* p = list.begin();
    CLinkNode* e = list.end();
    for (; p != e; p = p->next()) {
        p->m_cell = -1;
    }
}

/* after the goal: the single winner walks back to the centre (0, 125, 0); then everyone turns to yaw 0 */
void CPlayer::procWin()
{
    if (s_winner && m_goal) {
        Vec target = { 0.0f, 125.0f, 0.0f };
        Vec dir;
        PSVECSubtract(&target, &m_pos, &dir);
        float dist = PSVECMag(&dir);
        m_speed = 0.6f;
        if (dist > 10.0f) {
            PSVECScale(&dir, &dir, 1.0f / dist);
            move(&dir);
            setMotion(2, false);
            return;
        }
        m_pos.x = 0.0f;
        m_pos.z = 0.0f;
    }
    float d = SubAngleMax(0.0f, m_yaw, 13.666667f);
    m_yaw += d;
    if (HuAbs(d) < 0.01f) {
        setMotion(0, false);
    } else {
        int state = 18; /* a register variable in retail (li r30,0x12 at FD28; m501 DAD8 the same) */
        m_state = state;
    }
    m_speed = 0.0f;
}

bool CPlayer::SetResult()
{
    CPlayer* p = list.begin();
    CLinkNode* e = list.end();
    s16 chars[4];
    bool draw = true;
    int i = 0;
    for (; p != e; p = p->next()) {
        chars[i++] = p->m_charNo;
        HU3DMODELID id = p->m_model.id();
        Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
        p->m_blinkOff = false;
        p->m_stun = 0;
        if (p->m_goal) {
            p->setProc(&CPlayer::procWinPose);
            draw = false;
        } else {
            p->setProc(&CPlayer::procLosePose);
        }
    }
    if (draw) {
        CharLoseVoicePlay(chars[0], chars[1], chars[2], chars[3]);
    }
    return draw;
}

void CPlayer::procWinPose()
{
    setMotion(3, true);
}

void CPlayer::procLosePose()
{
    setMotion(4, true);
}

void CPlayer::CreateStartSpr()
{
    CPlayer* p = list.begin();
    CLinkNode* e = list.end();
    int chars[4];
    int i = 0;
    for (; p != e; p = p->next()) {
        chars[i++] = p->m_charNo;
    }
    new CStartSpr(chars);
}

/* the camera's framing box: x in [-770, 770], z in [-1100, 880], widened to every player's pos.x +-550,
 * pos.z +660 / -880; out.x / out.z = the box centre, out.y = the larger extent */
void CPlayer::GetBounds(Vec* out)
{
    CPlayer* p = list.begin();
    CLinkNode* e = list.end();
    float maxX = 770.0f;
    float minX = -770.0f;
    float maxZ = 880.0f;
    float minZ = -1100.0f;
    for (; p != e; p = p->next()) {
        float x = p->m_pos.x;
        float z = p->m_pos.z;
        float t;
        t = x + 550.0;
        if (t > maxX) {
            maxX = t;
        }
        t = x - 550.0;
        if (t < minX) {
            minX = t;
        }
        t = z + 660.0f;
        if (t > maxZ) {
            maxZ = t;
        }
        t = z - 880.0f;
        if (t < minZ) {
            minZ = t;
        }
    }
    out->x = (maxX + minX) / 2.0f;
    out->z = (maxZ + minZ) / 2.0f;
    float w = maxX - minX;
    float d = maxZ - minZ;
    if (w > d) {
        out->y = w;
    } else {
        out->y = d;
    }
}

void CPlayer::Update(CPlayer* p)
{
    p->m_prevPos = p->m_pos;
    (p->*(p->m_proc))();
    p->m_frame++;
    p->PushPlayers();
    p->Collide();
    Vec rot;
    SetVec(&rot, 0.0f, p->m_yaw, 0.0f);
    p->m_model.setRot(&rot);
    p->m_model.setPos(&p->m_pos);
    CharModelVoicePanSet(p->m_charNo, CCameraObj::GetSePan(&p->m_pos));
    CharModelVoiceVolSet(p->m_charNo, CCameraObj::GetSeVol(&p->m_pos));
}

void CPlayer::PushPlayers()
{
    Vec pos = m_pos; /* retail: a dead copy (102F8) */
    if (m_pushTimer > 0) {
        m_pushTimer--;
    }
    CPlayer* p = list.begin();
    CLinkNode* e = list.end();
    for (; p != e; p = p->next()) {
        if (this == p) {
            continue;
        }
        Vec old = p->m_pos;
        Vec d;
        PSVECSubtract(&p->m_pos, &m_pos, &d);
        float dist = PSVECMag(&d);
        if (dist >= 120.0f) {
            continue;
        }
        float half = 0.5f;
        float other = 1.0f - half;
        PSVECScale(&d, &d, (120.0f - dist) / dist);
        Vec mine;
        PSVECScale(&d, &mine, 1.05f * -half);
        Vec theirs;
        PSVECScale(&d, &theirs, 1.05f * other);
        PSVECAdd(&mine, &m_pos, &m_pos);
        PSVECAdd(&theirs, &p->m_pos, &p->m_pos);
        p->m_pushTimer = (other >= 0.5f) ? 5 : 0;
        float ox = (1650.0f + old.x) / 100.0f;
        float oz = (1210.0f + old.z) / 100.0f;
        int oix = ox / 2.2f;
        int oiz = oz / 2.2f;
        float nx = (1650.0f + p->m_pos.x) / 100.0f;
        float nz = (1210.0f + p->m_pos.z) / 100.0f;
        int nix = nx / 2.2f;
        int niz = nz / 2.2f;
        if (oix != nix) {
            p->m_pos.x = old.x;
        }
        if (oiz != niz) {
            p->m_pos.z = old.z;
        }
    }
}

void CPlayer::setMotion(int no, bool once)
{
    HU3DMODELID id = m_model.id();
    s16& ref = m_mot_id.at(no);
    s16 mot = ref;
    if (m_motion != no) {
        Hu3DModelAttrReset(id, 0x40000002);
        CharMotionShiftSet(m_charNo, mot, 0.0f, 8.0f, !once ? HU3D_MOTATTR_LOOP : 0);
        m_motion = no;
    }
}

/* on: hidden on odd frames (m_blinkOff = 1); off: shown again */
void CPlayer::setBlink(bool on)
{
    HU3DMODELID id = m_model.id();
    if (on) {
        if (m_frame & 1) {
            Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
        } else {
            Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
        }
        m_blinkOff = true;
    } else if (m_blinkOff) {
        Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
        m_blinkOff = false;
    }
}

void CPlayer::procInit()
{
    setMotion(0, false);
    setProc(&CPlayer::procPlay);
}

/* stunned: the input is the pull to the cell centre, applied directly (no turning); blinks and rumbles */
void CPlayer::procPlay()
{
    Vec dir;
    GetInput(&dir);
    if (m_stun > 0) {
        setMotion(5, false);
        if (m_stun > 15.0) {
            omVibrate(m_idx, 12, 12, 0);
        }
        m_pos.x += dir.x;
        m_pos.z += dir.z;
        setBlink(true);
    } else {
        setBlink(false);
        if (move(&dir)) {
            if (m_stun == 0) {
                setMotion(m_speed > 0.5f ? 2 : 1, false);
            }
        } else {
            setMotion(0, false);
        }
    }
}

void CPlayer::setMotionWin()
{
    setMotion(3, true);
}

/* turn towards dir (41/3 degrees a frame at most) and walk along the facing; false when there is no input */
bool CPlayer::move(Vec* dir)
{
    if (m_speed < 0.01f) {
        Hu3DMotionSpeedSet(m_model.id(), 1.0f);
        return false;
    }
    Hu3DMotionSpeedSet(m_model.id(), 0.75 * (1.5f * m_speed));
    m_targetYaw = 180.0 * (atan2(dir->x, dir->z) / M_PI);
    m_yaw += SubAngleMax(m_targetYaw, m_yaw, 13.666667f);
    float rad = M_PI * m_yaw / 180.0;
    Vec fwd;
    SetVec(&fwd, sin(rad), 0.0f, cos(rad));
    float dot = PSVECDotProduct(&fwd, dir);
    if (dot < 0.0f) {
        return true;
    }
    float speed = 6.75f;
    speed *= 1.6666666666666667 * dot;
    Vec step;
    PSVECScale(&fwd, &step, speed * m_speed);
    PSVECAdd(&step, &m_pos, &m_pos);
    return true;
}

/* the 220-unit grid cell id ix + 256 * iz; true (and stored) when it changed */
bool CPlayer::updateCell(float x, float z)
{
    int ix = (x + 1650.0f) / 220.0f;
    int iz = (z + 1210.0f) / 220.0f;
    int cell;
    bool changed = false;
    cell = ix + (iz << 8);
    if (cell != m_cell) {
        m_cell = cell;
        changed = true;
    }
    return changed;
}

/* COM: the maze's route code of the current cell; at a cell with fewer than two walls, hesitate (by level) */
u8 CPlayer::queryMaze()
{
    u8 code = CSingleton<CMaze>::GetInstance()->getCell(m_pos.x, m_pos.z);
    u8 walls = CSingleton<CMaze>::GetInstance()->getWalls(m_pos.x, m_pos.z);
    int n = ((walls & 0x80) > 0) + ((walls & 0x40) > 0) + ((walls & 8) > 0) + ((walls & 4) > 0);
    if (n < 2) {
        switch (m_dif) {
        case 0:
            m_comWait = 60;
            break;
        case 1:
            m_comWait = 36;
            break;
        case 2:
            m_comWait = 18;
            break;
        case 3:
            m_comWait = 0;
            break;
        }
    }
    return code;
}

/* where in its cell a point lies: 1 / 2 = more than 0.2 cell right / left of the centre, 4 / 8 = the same in z */
u8 CPlayer::GetCellEdge(float x, float z)
{
    float fx = x + 1650.0f;
    float fz = z + 1210.0f;
    int ix = fx / 220.0f;
    int iz = fz / 220.0f;
    u8 edge = 0;
    fx = (fx - 220.0f * ix) / 220.0f - 0.5;
    fz = (fz - 220.0f * iz) / 220.0f - 0.5;
    if (fx > 0.2) {
        edge |= 1;
    }
    if (fx < -0.2) {
        edge |= 2;
    }
    if (fz > 0.2) {
        edge |= 4;
    }
    if (fz < -0.2) {
        edge |= 8;
    }
    return edge;
}

/* update mode 2 only: a human steers with the stick; a COM follows the maze's route code of its cell (queried on
 * each cell change) and at a junction waits steering to the cell centre. Touching a wall stuns (60 frames): the
 * input becomes the pull to the cell centre. dir = (x, 0, -z); m_speed = |dir| */
void CPlayer::GetInput(Vec* dir)
{
    m_speed = 0.0f;
    dir->x = 0.0f;
    dir->y = 0.0f;
    dir->z = 0.0f;
    if (CGameObject::GetUpdateMode() == 2) {
        float x = 0.0f;
        float z = 0.0f;
        if (m_padNo < 0) {
            if (updateCell(m_pos.x, m_pos.z)) {
                m_comDir = queryMaze();
            }
            switch (m_comDir & 7) {
            case 1:
                x = 0.0f;
                z = 1.0f;
                break;
            case 2:
                x = 0.0f;
                z = -1.0f;
                break;
            case 3:
                x = -1.0f;
                z = 0.0f;
                break;
            case 4:
                x = 1.0f;
                z = 0.0f;
                break;
            case 5:
                if (m_pos.x > 30.0) {
                    x = -1.0f;
                }
                if (m_pos.x < -30.0) {
                    x = 1.0f;
                }
                if (m_pos.z > 30.0) {
                    z = 1.0f;
                }
                if (m_pos.z < -30.0) {
                    z = -1.0f;
                }
                break;
            }
            if (m_comWait > 0) {
                m_comWait--;
                x = z = 0.0f;
                u8 edge = GetCellEdge(m_pos.x, m_pos.z);
                if (edge & 1) {
                    x = -1.0f;
                }
                if (edge & 2) {
                    x = 1.0f;
                }
                if (edge & 4) {
                    z = 1.0f;
                }
                if (edge & 8) {
                    z = -1.0f;
                }
            }
        } else {
            x = (1.0f / 56.0f) * HuPadStkX[m_padNo];
            z = (1.0f / 56.0f) * HuPadStkY[m_padNo];
        }
        if (m_stun == 0) {
            if (CSingleton<CMaze>::GetInstance()->nearWall(m_pos.x, m_pos.z)) {
                m_stun = 60;
                m_cell = -1;
                HuAudFXPlayVolPan(0x691, CCameraObj::GetSeVol(&m_pos), CCameraObj::GetSePan(&m_pos));
            }
        }
        if (m_stun > 0) {
            m_stun--;
            float fx = m_pos.x + 1650.0f;
            float fz = m_pos.z + 1210.0f;
            int ix = fx / 220.0f;
            int iz = fz / 220.0f;
            fx = (fx - 220.0f * ix) / 220.0f;
            fz = (fz - 220.0f * iz) / 220.0f;
            fx -= 0.5f;
            fz -= 0.5f;
            x = 4.0f * -fx;
            z = 4.0f * fz;
        }
        SetVec(dir, x, 0.0f, -z);
        m_speed = PSVECMag(dir);
    }
}

/* stunned players stay in their cell: undo each axis of this frame's move that changed the (100-unit, /2.2) cell */
void CPlayer::keepInCell()
{
    float px = (m_prevPos.x + 1650.0f) / 100.0f;
    float pz = (m_prevPos.z + 1210.0f) / 100.0f;
    int pix = px / 2.2f;
    int piz = pz / 2.2f;
    float cx = (m_pos.x + 1650.0f) / 100.0f;
    float cz = (m_pos.z + 1210.0f) / 100.0f;
    int ix = cx / 2.2f;
    int iz = cz / 2.2f;
    if (pix != ix) {
        m_pos.x = m_prevPos.x;
    }
    if (piz != iz) {
        m_pos.z = m_prevPos.z;
    }
}

/* stunned: stay in the cell; clamp to the arena; push out of the four corner pillars of the cell; the goal box
 * |x|, |z| < 80 sets m_goal and starts the maze's clear; the maze marks the player's cell every frame */
void CPlayer::Collide()
{
    float fx;
    float fz;
    if (m_stun > 0) {
        keepInCell();
    }
    if (m_pos.x < -1630.0f) {
        m_pos.x = -1630.0f;
    }
    if (m_pos.x > 1630.0f) {
        m_pos.x = 1630.0f;
    }
    if (m_pos.z < -1190.0f) {
        m_pos.z = -1190.0f;
    }
    if (m_pos.z > 1190.0f) {
        m_pos.z = 1190.0f;
    }
    float cx = (m_pos.x + 1650.0f) / 100.0f;
    float cz = (m_pos.z + 1210.0f) / 100.0f;
    int ix = cx / 2.2f;
    int iz = cz / 2.2f;
    fx = cx - 2.2f * ix;
    fz = cz - 2.2f * iz;
    pushOut(0.0f, 0.0f, fx, fz, ix, iz);
    pushOut(2.2f, 0.0f, fx, fz, ix, iz);
    pushOut(0.0f, 2.2f, fx, fz, ix, iz);
    pushOut(2.2f, 2.2f, fx, fz, ix, iz);
    if (m_pos.x < 80.0 && m_pos.x > -80.0 && m_pos.z < 80.0 && m_pos.z > -80.0) {
        m_goal = true;
        CSingleton<CMaze>::GetInstance()->startClear(m_charNo);
    }
    CSingleton<CMaze>::GetInstance()->markCell(m_charNo, m_pos.x, m_pos.z);
}

/* push out of the round pillar (radius 1 in cell units of 100) at corner (cx, cz) of cell (ix, iz); (fx, fz) is
 * the position in the cell */
void CPlayer::pushOut(float cx, float cz, float fx, float fz, int ix, int iz)
{
    float dx = fx - cx;
    float dz = fz - cz;
    float len = sqrt(dx * dx + dz * dz); /* CW: libc math.h's inline (frsqrte + 4 Newton steps); host: libm */
    if (len < 1.0f && len > 0.001f) {
        dx = cx + dx / len;
        dx += 2.2f * ix;
        dz = cz + dz / len;
        dz += 2.2f * iz;
        m_pos.x = 100.0f * (dx - 16.5f);
        m_pos.z = 100.0f * (dz - 12.1f);
    }
}

} // namespace m509
