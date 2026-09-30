/* player.cpp -- m536::CPlayer. SKELETON: bodies marked STUB are the function forks'. Lines in stubs that
 * set a PTMF or pass a string are retail's and place the .data constants in retail order.
 * The ctor's assert must stay on line 243 (its __LINE__ is an immediate; "player.cpp" is in .data). */
#include "REL/mgcpp/minigame.h"
#include "REL/mgcpp/random.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/m536Dll/player.h"
#include "REL/m536Dll/camera.h"
#include "REL/m536Dll/score.h"
#include "REL/m536Dll/killer.h"
#include "REL/m536Dll/gun.h"
#include <vector>

namespace m536 {

/* .bss after the header triple (definition order): the list (+ DestructorChain), then the file statics */
TLinkList<CPlayer> CPlayer::playerList;
static bool s_fastRotate;   /* lbl_1_bss_AA0 some cannon turns faster than 1 degree/frame (UpdateAll clears) */
static bool s_rotSePlay;    /* lbl_1_bss_AA1 rotate-loop SE playing */
static int s_counter;       /* lbl_1_bss_AA4 ++ per player update (4x per frame); the dead players' rank key */
static bool s_hitEnable;    /* lbl_1_bss_AA8 damage armed (CheckGameEnd sets, SetRank clears) */
static CPlayer* s_winner;   /* lbl_1_bss_AAC the sole survivor, else 0 */

/* .data 3C8..3E3 (non-const) */
static int s_rotSe = -1;                          /* lbl_1_data_3C8 rotate-loop SE handle */
static Vec s_bodyOfs = { 0.0f, 10.0f, -150.0f };  /* lbl_1_data_3CC player offset from the cannon centre */
static Vec s_muzzleOfs = { 0.0f, 50.0f, 140.0f }; /* lbl_1_data_3D8 */

float CPlayer::SubAngle(float a, float b)
{
    int ia = DegToAngle(a);
    int ib = DegToAngle(b);
    int d = AngleSub(ia, ib);
    return AngleToDeg(d);
}

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

/* the rotate-loop SE follows s_fastRotate (inlined into UpdateAll) */
void CPlayer::UpdateRotateSE()
{
    if (s_fastRotate) {
        if (!s_rotSePlay) {
            s_rotSePlay = true;
            s_rotSe = HuAudFXPlay(0x7CF);
        }
    } else if (s_rotSePlay) {
        s_rotSePlay = false;
        HuAudFXStop(s_rotSe);
    }
}

/* cannon corner by player (default: retail leaves the corner uninitialised; idx is always 0..3), the
 * auto-rotation speed control, the sole survivor's slide to the centre, then the gun and the two points */
void CPlayer::updateRotate()
{
    float c = 417.99997f;
    float y = 7.0f;
    float x;
    float z;
    switch (m_idx) {
    case 0:
        x = -c;
        z = -c;
        break;
    case 1:
        x = c;
        z = -c;
        break;
    case 2:
        x = -c;
        z = c;
        break;
    case 3:
        x = c;
        z = c;
        break;
    }
    float fps = 60.0f;
    if (--m_holdTimer < 0) {
        m_holdTimer = 0;
        if (m_finish) {
            /* game over: turn to about -20 degrees and stop */
            float d = SubAngle(-20.0f, m_yaw);
            float speed = 120.0f / fps;
            if (d < 0.0f || d > 5.0f) {
                if (m_yawSpeed > speed) {
                    m_yawSpeed -= 14.0f / fps;
                    if (m_yawSpeed < speed) {
                        m_yawSpeed = speed;
                    }
                } else {
                    m_yawSpeed += 7.0f / fps;
                    if (m_yawSpeed > speed) {
                        m_yawSpeed = speed;
                    }
                }
            } else {
                m_yawSpeed = 0.0f;
            }
        } else {
            /* degrees per second: a damaged cannon turns slower */
            float max = 200.0f + 100.0f * m_life;
            if (m_yawSpeed < (max - 7.0f) / fps) {
                m_yawSpeed += 7.0f / fps;
            }
            if (m_yawSpeed > (max + 7.0f) / fps) {
                m_yawSpeed -= 7.0f / fps;
            }
        }
        if ((m_yaw += m_yawSpeed) > 180.0f) {
            m_yaw -= 360.0f;
        }
    }
    if (m_yawSpeed > 1.0f) {
        s_fastRotate = true;
    }
    Vec pos;
    pos.x = x;
    pos.y = y;
    pos.z = z;
    if (m_winner) {
        int max = 120;
        if (++m_slideTimer > max) {
            m_slideTimer = max;
            if (m_slideSePlay) {
                m_slideSePlay = false;
                HuAudFXStop(m_slideSe);
            }
        } else if (!m_slideSePlay) {
            m_slideSePlay = true;
            m_slideSe = HuAudFXPlay(0x7D6);
        }
        float t = (float)m_slideTimer / (float)max;
        pos.x -= x * t;
        pos.z -= z * t;
    }
    if (m_gunReady) {
        CGun::SetPos(m_idx, &pos);
        CGun::SetRot(m_idx, m_yaw);
    }
    m_gunReady = true;
    Mtx m;
    PSMTXRotRad(m, 'y', 0.017453292f * m_yaw);
    PSMTXTransApply(m, m, pos.x, pos.y, pos.z);
    PSMTXMultVec(m, &s_bodyOfs, &m_pos);
    PSMTXMultVec(m, &s_muzzleOfs, &m_muzzle);
}

void CPlayer::Close()
{
    while (!playerList.isEmpty()) {
        CPlayer* p = playerList.last();
        delete p;
    }
}

/* retail order (W0 player.md §7); verified by fork P1 (259 = retail, masked 0; raw residue = .data labels only) */
CPlayer::CPlayer(int idx) : m_winner(false), m_slideTimer(0), m_slideSePlay(false), m_model(GwPlayerConf[idx].charNo, 1)
{
    s_counter = 0;
    insertBack(&playerList);
    m_idx = idx;
    m_charNo = GwPlayerConf[idx].charNo;
    printf("m_char_id %d\n", m_charNo);
    m_dif = GwPlayerConf[idx].dif;
    m_padNo = (GwPlayerConf[idx].type != 0) ? -1 : GwPlayerConf[idx].padNo;
    m_finish = false;
    m_gunReady = false;
    m_yaw = 360.0f * CRandom::randomMantissa() - 180.0f;
    m_yawSpeed = 0.0f;
    m_holdTimer = 240;
    s_fastRotate = false;
    s_rotSePlay = false;
    updateRotate();
    m_force = 0.0f;
    m_dead = false;
    m_stamp = 0;
    m_life = 3;
    m_stun = 0;
    m_cooldown = 0;
    m_fireReq = false;
    m_motion = -1;
    m_mot_id.clear();
    m_mot_id.reserve(NUMBEROF_MOTION);
    createMotion(0x870028); /* 0 idle (loop) */
    createMotion(0x8C002F); /* 1 win */
    createMotion(0x8C0031); /* 2 lose / draw */
    createMotion(0x8C003F); /* 3 blown away */
    createMotion(0x8C001A); /* 4 hit */
    createMotion(0x8C0005); /* 5 shoot */
    /* line padding: the assert below is retail's player.cpp:243 */





































    assert(m_mot_id.size() == NUMBEROF_MOTION);
    CharModelFxFlagSet(m_charNo, 0);
    CharMotionDataClose(m_charNo);
    Hu3DModelLayerSet(m_model.id(), 2);
    Hu3DModelCameraSet(m_model.id(), 1);
    Vec rot;
    SetVec(&rot, 0.0f, m_yaw, 0.0f);
    m_model.setRot(&rot);
    m_model.setPos(&m_pos);
    setProc(&CPlayer::proc_start);
    CSingleton<CScore>::GetInstance()->initPlayer(m_idx, m_charNo);
    CSingleton<CScore>::GetInstance()->setValue(m_idx, m_life);
}

void CPlayer::createMotion(int dataNum)
{
    s16 mot = CharMotionCreate(m_charNo, dataNum);
    m_mot_id.push_back(mot);
}

void CPlayer::UpdateAll()
{
    s_fastRotate = false;
    TLinkList<CPlayer>::exec(&playerList, UpdatePlayer);
    UpdateRotateSE();
    /* rotate the list: the first player moves to the back (hit/update order changes every frame) */
    CPlayer* p = playerList.begin();
    if (p != playerList.end()) {
        p->unlink();
        p->insertBack(&playerList);
    }
}

bool CPlayer::CheckGameEnd()
{
    s_hitEnable = true;
    CPlayer* p = playerList.begin();
    CLinkNode* e = playerList.end();
    int dead = 0;
    for (; p != e; p = p->next()) {
        if (p->m_dead) {
            dead++;
        }
    }
    if (dead < 3) {
        return false;
    }
    return true;
}

void CPlayer::SetRank()
{
    s_hitEnable = false;
    CPlayer* p = playerList.begin();
    CLinkNode* e = playerList.end();
    CPlayer* player[4];
    int score[4];
    int order[4] = { 0, 1, 2, 3 };
    int alive = 0;
    int i = 0;
    for (; p != e; p = p->next()) {
        player[i] = p;
        if (!p->m_dead) {
            s_winner = p;
            alive++;
            p->m_holdTimer = 0;
            p->m_finish = true;
            score[i] = p->m_life * 100000;
        } else {
            score[i] = p->m_stamp;
        }
        i++;
    }
    if (alive != 1) {
        s_winner = 0;
    } else {
        s_winner->m_winner = true;
        CSingleton<CCameraObj>::GetInstance()->startWinnerZoom();
        CGun::PlayWin(s_winner->m_idx);
    }
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            if (score[k] < score[k + 1]) {
                int a = score[k];
                int b = score[k + 1];
                score[k] = b;
                score[k + 1] = a;
                a = order[k];
                b = order[k + 1];
                order[k] = b;
                order[k + 1] = a;
            }
        }
    }
    int rank = 0;
    for (i = 0; i < 4; i++) {
        GWMgCoinBonusSet(player[order[i]]->m_idx, rank);
        printf("player %d rank %d test %d\n", player[order[i]]->m_idx, rank, score[i]);
        if (i < 3 && score[i] != score[i + 1]) {
            rank++;
        }
    }
}

bool CPlayer::StartPlayerWin()
{
    CPlayer* p = playerList.begin();
    CLinkNode* e = playerList.end();
    bool draw = true;
    int alive = 0;
    int n = 0;
    s16 chars[4];
    for (; p != e; p = p->next()) {
        if (!p->m_dead) {
            alive++;
        }
    }
    p = playerList.begin();
    e = playerList.end();
    if (alive < 4) {
        for (; p != e; p = p->next()) {
            chars[n++] = p->m_charNo;
            if (!p->m_dead) {
                p->setProc(&CPlayer::proc_win);
                CharFXPlayPan(p->m_charNo, 0x1FA, CCameraObj::GetSePan(&p->m_pos));
                draw = false;
            }
        }
    } else {
        for (; p != e; p = p->next()) {
            chars[n++] = p->m_charNo;
            p->setProc(&CPlayer::proc_lose);
        }
    }
    if (draw) {
        CharLoseVoicePlay(chars[0], chars[1], chars[2], chars[3]);
    }
    return draw;
}

void CPlayer::UpdatePlayer(CPlayer* p)
{
    (p->*(p->m_proc))();
    s_counter++;
    if (!p->m_dead) {
        p->m_stamp = s_counter;
    }
    if (--p->m_stun < 0) {
        p->m_stun = 0;
    } else if ((float)p->m_stun > 30.0f) {
        omVibrate(p->m_idx, 12, 12, 0);
    }
    Vec rot;
    SetVec(&rot, 0.0f, p->m_yaw, 0.0f);
    p->m_model.setRot(&rot);
    p->m_model.setPos(&p->m_pos);
    CharModelVoicePanSet(p->m_charNo, CCameraObj::GetSePan(&p->m_pos));
    CharModelVoiceVolSet(p->m_charNo, CCameraObj::GetSeVol(&p->m_pos));
}

void CPlayer::setMotion(int motion, bool once)
{
    s16 model = m_model.id();
    s16 mot = m_mot_id[motion];
    if (m_motion != motion) {
        Hu3DModelAttrReset(model, 0x40000002);
        CharMotionShiftSet(m_charNo, mot, 0.0f, 8.0f, !once ? 0x40000001 : 0);
        m_motion = motion;
    }
}

void CPlayer::proc_start()
{
    setMotion(0, false);
    setProc(&CPlayer::proc_main);
}

/* the bill of `owner` at pos: true when it is within 200 (XZ) of another live, unstunned player. Before
 * CheckGameEnd arms damage (s_hitEnable) a hit only stops the bill. */
bool CPlayer::CheckHit(int owner, Vec* pos)
{
    CPlayer* p = playerList.begin();
    CLinkNode* e = playerList.end();
    int unused = 0; /* retail: a dead 4-byte local, stored 0 once (B4F8; also BE94, killer F1CC) */
    for (; p != e; p = p->next()) {
        if (p->m_idx == owner || p->m_stun != 0 || p->m_life <= 0) {
            continue;
        }
        /* float differences squared in double (fsubs, then fmul/fadd against the double 40000.0) */
        double dx = p->m_pos.x - pos->x;
        double dz = p->m_pos.z - pos->z;
        if (dx * dx + dz * dz < 40000.0) {
            if (s_hitEnable) {
                if (--p->m_life <= 0) {
                    p->m_vel.x = 0.0f;
                    p->m_vel.y = 50.0f;
                    p->m_vel.z = 0.0f;
                    p->setProc(&CPlayer::proc_blow);
                    p->m_dead = true;
                    CharFXPlayPan(p->m_charNo, 0x1F9, CCameraObj::GetSePan(&p->m_pos));
                    s16 model = p->m_model.id();
                    Hu3DModelAttrReset(model, 1);
                } else {
                    CharFXPlayPan(p->m_charNo, 0x1FD, CCameraObj::GetSePan(&p->m_pos));
                    CGun::SetDamage(p->m_idx, p->m_life);
                    p->m_stun = 90;
                    p->m_fireReq = false;
                }
                CSingleton<CScore>::GetInstance()->setValue(p->m_idx, p->m_life);
            }
            return true;
        }
    }
    return false;
}

void CPlayer::Shot(int idx, Vec* pos, float yaw)
{
    /* retail ignores Shoot's result: a refused shot (the player's bill still flying) still recoils */
    CSingleton<CKillerMan>::GetInstance()->Shoot(idx, pos, yaw);
    CGun::Fire(idx);
}

void CPlayer::proc_main()
{
    if (CGameObject::GetUpdateMode() == 2) {
        if (--m_cooldown < 0) {
            m_cooldown = 0;
        }
        updateShot();
    }
    updateDisp();
    if (m_stun != 0) {
        setMotion(4, true);
    } else if (m_cooldown == 0) {
        setMotion(0, false);
    } else {
        setMotion(5, true);
    }
}

void CPlayer::proc_blow()
{
    omVibrate(m_idx, 12, 12, 0);
    setMotion(3, true);
    m_pos.x += m_vel.x;
    m_pos.y += m_vel.y;
    m_pos.z += m_vel.z;
    m_vel.y -= 0.8333333f;
    if ((m_force -= 10.0f) < -180.0f) {
        m_force += 360.0f;
    }
    if (m_vel.y < 0.0f) {
        setProc(&CPlayer::proc_hide);
    }
    char* name = (char*)"root_motion"; /* a local: retail loads the string before the model id (BAF4) */
    Hu3DMotionForceSet(m_model.id(), name, 0x80, m_force);
}

void CPlayer::proc_hide()
{
    s16 model = m_model.id();
    Hu3DModelAttrSet(model, 1);
}

void CPlayer::proc_win()
{
    updateDisp();
    setMotion(1, true);
}

void CPlayer::proc_lose()
{
    updateDisp();
    setMotion(2, true);
}

/* the XZ direction from b to a, degrees */
float CPlayer::GetAngle(Vec* a, Vec* b)
{
    return HuAtan(a->x - b->x, a->z - b->z);
}

/* lbl_1_data_4AC / 4B8: the aim ray (non-const .data; file statics or function-locals of getTargetAngle) */
static Vec s_aimDir = { 0.0f, 0.0f, 1.0f };
static Vec s_aimOrg = { 0.0f, 0.0f, 0.0f };

/* |x| through an inline; the if/else form (a ternary keeps the result in an extra FPR, BD44) */
inline float Abs(float x)
{
    if (x < 0.0f) {
        return -x;
    } else {
        return x;
    }
}

/* The other live, unstunned player nearest the aim: *diff = its signed angle from the aim (0 if none);
 * *noHuman = true when no human player (padNo >= 0) is alive (the count includes this player). True when
 * that player is within 60 degrees. */
bool CPlayer::getTargetAngle(float* diff, bool* noHuman)
{
    Mtx m;
    Vec dir;
    PSMTXRotRad(m, 'y', 0.017453292f * m_yaw);
    PSMTXMultVec(m, &s_aimDir, &dir);
    float aim = GetAngle(&dir, &s_aimOrg);
    float bestDiff = 0.0f;
    float d = 0.0f;
    float best = 90.0f;
    CPlayer* p = playerList.begin();
    CLinkNode* e = playerList.end();
    float angle;    /* declared here: its stack slot sits below `unused` in the inlined copies (C0FC, C6DC) */
    int unused = 0; /* retail: a dead 4-byte local, stored 0 once (BE94) */
    int humans = 0;
    for (; p != e; p = p->next()) {
        if (p->m_idx != m_idx && p->m_stun == 0 && p->m_life > 0) {
            angle = GetAngle(&p->m_pos, &m_pos);
            d = SubAngle(angle, aim);
            if (Abs(d) < best) {
                bestDiff = d;
                best = Abs(d);
            }
        }
        if (p->m_padNo >= 0 && p->m_life > 0) {
            humans++;
        }
    }
    if (humans == 0) {
        *noHuman = true;
    }
    *diff = bestDiff;
    /* this return form: branchy li r3 (not mfcr), and the body stays under CW's auto-inline limit (it is
     * inlined into comCheckShot); an if/else here stops the inlining */
    if (best >= 60.0f) {
        return false;
    }
    return true;
}

/* COM fire decision: a per-difficulty random roll when a target is in the aim window */
bool CPlayer::comCheckShot()
{
    float diff = 0.0f;
    bool noHuman = false;
    if (getTargetAngle(&diff, &noHuman)) {
        if (noHuman == true) {
            if (Abs(diff) < 7.0f && (CRandom::irandom() & 3) == 0) {
                return true;
            }
            return false;
        }
        switch (m_dif) {
        case 0:
            /* retail: no angle test at difficulty 0 */
            if ((CRandom::irandom() & 0x3F) == 0) {
                return true;
            }
            break;
        case 1:
            if (Abs(diff) < 40.0f && (CRandom::irandom() & 0x1F) == 0) {
                return true;
            }
            break;
        case 2:
            if (Abs(diff) < 25.0f && (CRandom::irandom() & 0x1F) == 0) {
                return true;
            }
            break;
        case 3:
            if (Abs(diff) < 10.0f && (CRandom::irandom() & 0xF) == 0) {
                return true;
            }
            break;
        }
    }
    return false;
}

void CPlayer::updateShot()
{
    if (m_stun != 0) {
        return;
    }
    if (m_cooldown < 120.0f && m_cooldown > 114.0f) {
        omVibrate(m_idx, 12, 12, 0);
    }
    if (m_cooldown == 30.0f) { /* CW loads 30.0f before the conversion here, retail after (masked 6) */
        s16 se = m_pos.x > 0.0f ? 0x7D5 : 0x7D4;
        HuAudFXPlay(se);
    }
    if (m_fireReq && m_cooldown <= 120.0f) {
        Shot(m_idx, &m_muzzle, m_yaw);
        m_fireReq = false;
    }
    if (m_cooldown == 0) {
        /* retail dead store: built and never read */
        Vec top;
        top.x = m_pos.x;
        top.y = 70.0f + m_pos.y;
        top.z = m_pos.z;
        bool fire = false;
        if (m_padNo < 0) {
            if (comCheckShot()) {
                fire = true;
            }
        } else if (HuPadBtnDown[m_padNo] & PAD_BUTTON_A) {
            fire = true;
        }
        if (fire) {
            m_fireReq = true;
            m_cooldown = 129;
            m_holdTimer = 30;
            m_yawSpeed = 0.0f;
        }
    }
}

/* the rotation/position update, then the hit blink (visible below 6 frames of stun or on even frames) */
void CPlayer::updateDisp()
{
    updateRotate();
    s16 model = m_model.id();
    if (m_stun < 6.0f || (m_stun & 1) == 0) {
        Hu3DModelAttrReset(model, 1);
    } else {
        Hu3DModelAttrSet(model, 1);
    }
}

} // namespace m536
