/* player.cpp -- CPlayer and CRunner (player.h), in retail order; this unit also carries the weak copies retail
 * kept: ~CModelBase (B6C4), CModelBase's vtable (data_394) and the inline empties CPlayerBase::InputCom/Move and
 * CModelBase::UpdateMain (BA5C/BA60/BA64). Includes flow.h, hence minigame.h: the 120/210/210 triple is bss_28..30.
 * The five guarded `static CFlow* s_flow = m_flow;` locals are bss_34..58 (map.player.txt).
 * Behaviour: the W0 sheet (../20260925-m531-w0/game/player_playerbase_polish.md §0, §2). Every function is whole
 * (F4). Base-class members passed to calls go through the inline const accessors in playerbase.h (retail keeps
 * the value in a callee-saved temp); locals such as `int slot = m_slot;`, `Vec& cell = m_comCell;` are retail's. */
#include "REL/m531Dll/player.h"
#include "REL/m531Dll/flow.h"
#include "REL/m531Dll/cleaneff.h"
#include "REL/m531Dll/polish.h"
#include "REL/m531Dll/object.h"
#include "REL/m531Dll/audio.h"
extern "C" {
#include "game/frand.h"
}

namespace m531 {

static s32 s_startDir[4] = { -1, -1, 1, 1 }; /* data_348 by slot: a centred-stick human's first turn direction */
static Vec s_brushDir = { 0.0f, 0.0f, 100.0f }; /* data_358 the brush, 100 in front */

/* PSVECMag's result reaches the caller's variable through a temporary in all three retail call sites */
static inline float VecMag(Vec* v)
{
    return PSVECMag(v);
}

float LerpAngle(float from, float to, float t)
{
    float d = fmod(to - from, 360.0);

    if (d < 0.0f) {
        d += 360.0f;
    }
    if (d > 180.0f) {
        d -= 360.0f;
    }
    float r = fmod(from + t * d, 360.0);
    if (r < 0.0f) {
        r += 360.0f;
    }
    return r;
}

float AngleDiff(float from, float to)
{
    float d = fmod(to - from, 360.0);

    if (d < 0.0f) {
        d += 360.0f;
    }
    if (d > 180.0f) {
        d -= 360.0f;
    }
    return d;
}

CPlayer::CPlayer(CFlow* flow, CCleanEff* floor, const MotionEntry* tbl, int motNum, s16 playerNo, int slot)
    : CPlayerBase(flow->GetOm(), tbl, motNum, playerNo, (u16)1)
{
    m_turnVel = 0.0f;
    m_flow = flow;
    m_floor = floor;
    m_enterTime = 0.0f;
    m_landed = 0;
    m_fallVel = 0.0f;
    m_turnTarget = 0.0f;
    m_hitCount = 0;
    m_bumped = 0;
    m_slot = slot;
    m_comReverse = 0;
    m_comFrame = 0;
    m_comCellLevel = 1.0f;
    m_comThreshold = 0.9f;
    m_team = m_slot >> 1;
    m_comTurnFrames = 0;
    CharModelStepFxSet(GetCharNo(), 0);
    CreateBrush();
    CharEffectLayerSet(4);
    m_brushPos.x = 0.0f;
    m_brushPos.y = 0.0f;
    m_brushPos.z = 0.0f;
    m_brushOfs.x = 0.0f;
    m_brushOfs.y = 0.0f;
    m_brushOfs.z = 0.0f;
    m_sparkle = new CSparkle(32, m_pos, m_rot);
    ComSelectTarget();
}

CPlayer::~CPlayer()
{
    delete m_sparkle;
}

void CPlayer::CreateBrush()
{
    static const u32 brushData[2] = { 0x590008, 0x590009 };

    SetMotion(11);
    m_brush = Hu3DModelCreate(HuDataSelHeapReadNum(brushData[m_team], HU_MEMNUM_OVL, HEAP_MODEL));
    char* hook = CharModelItemHookGet(GetCharNo(), 2, 0);
    Hu3DModelHookSet(GetModel(), hook, m_brush);
    Hu3DModelAttrSet(m_brush, HU3D_MOTATTR_PAUSE);
}

void CPlayer::CreateDust()
{
    char* hook = CharModelItemHookGet(GetCharNo(), 2, 0);
    CharModelHookDustCreate(GetCharNo(), hook);
}

void CPlayer::UpdateEnter()
{
    m_enterTime += 1.0 / 60.0;
    if (m_enterTime > 3.0f) {
        float vel = m_fallVel;

        m_fallVel += 980.665 / 30.0 / 30.0;
        float fall = 0.5f * (vel + m_fallVel);
        m_pos.y -= fall;
        if (m_pos.y < 10.0f) {
            m_pos.y = 10.0f;
            if (!m_landed) {
                new CLandSmoke(m_pos);
                m_landed = 1;
                omVibrate(GetPlayerNo(), 30, 12, 0);
            }
        }
    }
    CPlayerBase::UpdateEnter();
    SetVoicePan(GetCharNo(), m_pos);
}

void CPlayer::UpdateMain()
{
    CPlayerBase::UpdateMain();
    CSparkle* sparkle = m_sparkle;
    sparkle->SetPos(&m_brushPos);
    sparkle->SetRot(&m_rot);
    SetVoicePan(GetCharNo(), m_pos);
}

void CPlayer::UpdateGoal()
{
    u8 arrived = 0;
    Vec dir;

    PSVECSubtract(&m_goalPos, &m_pos, &dir);
    float dist = VecMag(&dir);
    m_rot.y = LerpAngle(m_rot.y, 180.0 * (atan2(dir.x, dir.z) / 3.141592653589793), 0.2f);
    float speed = 0.0f;
    if (dist < 50.0f) {
        speed = 2.0f * ((5.0f / 3.0f) * (1.0f - (50.0f - dist) / 100.0f));
        if (speed < 2.0f) {
            speed = 2.0f;
        }
    } else {
        speed = 5.0f;
    }
    m_reqMotion = 1;
    if (dist < 20.0f) {
        m_pos.x = m_goalPos.x;
        m_pos.y = m_goalPos.y;
        m_pos.z = m_goalPos.z;
        m_rot.y = 0.0f;
        m_reqMotion = 0;
        arrived = 1;
    } else {
        float rad = 3.141592653589793 * m_rot.y / 180.0;
        m_pos.x += speed * sin(rad);
        m_pos.z += speed * cos(rad);
    }
    UpdateModel();
    if (arrived) {
        m_arrived = 1;
    }
    SetVoicePan(GetCharNo(), m_pos);
}

void CPlayer::UpdateResult()
{
    static CFlow* s_flow = m_flow;
    CFlowCamera* camera = s_flow->GetCamera();

    m_rot.y = camera->GetRotY();
    CPlayerBase::UpdateResult();
    SetVoicePan(GetCharNo(), m_pos);
}

void CPlayer::Start()
{
    CPlayerBase::Start();
    m_sparkle->show();
    Hu3DModelAttrReset(m_brush, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(m_brush, HU3D_MOTATTR_LOOP);
    if (HuPadStkX[GetPad()] == 0 && (s16)m_type == 0) {
        m_turnDir = s_startDir[m_slot];
        m_stickX = m_turnDir * 128;
        if (m_stickX < 0.0f) {
            m_turnTarget = 2.0f;
        } else if (m_stickX > 0.0f) {
            m_turnTarget = -2.0f;
        }
    } else {
        m_turnDir = !(frand() & 1) ? -1 : 1;
    }
    s32 seNo[2] = { 0x7A6, 0x7A7 };
    m_seNo = HuAudFXPlay(seNo[m_team]);
}

void CPlayer::Finish()
{
    CreateDust();
    CPlayerBase::Finish();
    delete m_sparkle;
    m_sparkle = 0;
    HuAudFXStop(m_seNo);
}

void CPlayer::InputPad()
{
    CPlayerBase::InputPad();
}

void CPlayer::InputCom()
{
    static CFlow* s_flow = m_flow;
    Vec& cell = m_comCell;
    float& level = m_comCellLevel;
    s16 dif = GetDif();

    level = ComGetCellLevel();
    s_flow->setGrid(m_team, cell.x, cell.z, level);
    ComSteer(dif);
    ComSelectTarget();
    m_comFrame++;
}

void CPlayer::ComSelectTarget()
{
    if (m_comCellLevel < m_comThreshold) {
        return;
    }
    static CFlow* s_flow = m_flow;
    Vec& cell = m_comCell;
    int slot = m_slot;
    bool forward = (slot != 1 && slot != 2) ? true : false;
    if (m_comReverse == 1) {
        forward = (forward == true) ? false : true;
    }
    float level = 1.0f;
    if (forward) {
        for (int z = 0; z < 5; z++) {
            for (int x = 0; x < 5; x++) {
                cell.x = x;
                cell.z = z;
                level = s_flow->getGrid(m_team, cell.x, cell.z);
                if (level < m_comThreshold) {
                    return;
                }
            }
        }
    } else {
        for (int z = 4; z >= 0; z--) {
            for (int x = 4; x >= 0; x--) {
                cell.x = x;
                cell.z = z + 5;
                level = s_flow->getGrid(m_team, cell.x, cell.z);
                if (level < m_comThreshold) {
                    return;
                }
            }
        }
    }
    m_comThreshold += 0.05f;
    if (m_comThreshold > 1.0f) {
        m_comReverse = 1;
        m_comThreshold = 1.0f;
    }
}

void CPlayer::ComSelectTargetExcept(int x, int z)
{
    static CFlow* s_flow = m_flow;
    Vec& cell = m_comCell;
    int slot = m_slot;
    bool forward = (slot != 1 && slot != 2) ? true : false;
    if (m_comReverse == 1) {
        forward = (forward == true) ? false : true;
    }
    float level = 1.0f;
    if (forward) {
        for (int i = 4; i >= 0; i--) {
            if (i == z) {
                continue;
            }
            for (int j = 4; j >= 0; j--) {
                if (j == x) {
                    continue;
                }
                cell.x = j;
                cell.z = i;
                level = s_flow->getGrid(m_team, cell.x, cell.z);
                if (level < m_comThreshold) {
                    return;
                }
            }
        }
    } else {
        for (int i = 0; i < 5; i++) {
            if (i + 5 == z) {
                continue;
            }
            for (int j = 0; j < 5; j++) {
                if (j == x) {
                    continue;
                }
                cell.x = j;
                cell.z = i + 5;
                level = s_flow->getGrid(m_team, cell.x, cell.z);
                if (level < m_comThreshold) {
                    return;
                }
            }
        }
    }
}

float CPlayer::ComGetCellLevel()
{
    Vec& cell = m_comCell;
    Vec& center = m_comCellCenter;
    float level = 0.0f;
    int slot = m_slot;
    float ofs; /* grid column 0: team 0 at x = -615 (+100 per column), team 1 at x = 95 */
    Vec min, max;

    if ((slot >> 1) == 0) {
        ofs = 615.0f;
    } else {
        ofs = -95.0f;
    }

    min.x = 100.0f * cell.x - ofs;
    min.y = 0.0f;
    min.z = -230.0f + 100.0f * cell.z;
    max.x = 100.0f + min.x;
    max.y = 0.0f;
    max.z = 100.0f + min.z;
    level = m_floor->ratioInRect(&min, &max);
    center.x = min.x + 0.5f * (max.x - min.x);
    center.y = 0.0f;
    center.z = min.z + 0.5f * (max.z - min.z);
    return level;
}

void CPlayer::ComSteer(int dif)
{
    static const s32 turnMax[4] = { 54, 42, 30, 24 };
    Vec dir;

    PSVECSubtract(&m_comCellCenter, &m_pos, &dir);
    float dist = VecMag(&dir);
    float diff = AngleDiff(m_rot.y, 180.0 * (atan2(dir.x, dir.z) / 3.141592653589793));
    if (m_bumped) {
        m_turnDir = (diff - m_rot.y > 0.0f) ? 1 : -1;
        m_stickX = m_turnDir * 128;
        return;
    }
    if (dist < 100.0f) {
        if (dist < 50.0f) {
            ComSelectTargetExcept(m_comCell.x, m_comCell.z);
        }
    } else if (m_comFrame > m_comTurnFrames) {
        m_comFrame = 0;
        m_comTurnFrames = (diff < 0.0f) ? -diff : diff;
        m_turnDir = (diff < 0.0f) ? 1 : -1;
        switch (dif) {
        case 0:
        case 1:
            if (m_comTurnFrames < turnMax[dif]) {
                m_comTurnFrames = turnMax[dif];
            }
            break;
        case 2:
        case 3:
            if (dist > 150.0f) {
                if (m_comTurnFrames < turnMax[dif]) {
                    m_comTurnFrames = turnMax[dif];
                }
            }
            break;
        }
    }
    m_stickX = m_turnDir * 128;
}

void CPlayer::Move()
{
    if (!IsDone()) {
        if (m_stickX < 0.0f) {
            m_turnTarget = 2.0f;
        } else if (m_stickX > 0.0f) {
            m_turnTarget = -2.0f;
        }
        m_turnVel += (m_turnTarget - m_turnVel) / 30.0f;
        if (0.0f != m_turnTarget) {
            m_rot.y += m_turnVel;
            float rad = 3.141592653589793 * m_rot.y / 180.0;
            m_pos.x += 0.5 * ((5.0f / 3.0f) * sin(rad));
            m_pos.z += 0.5 * ((5.0f / 3.0f) * cos(rad));
            m_reqMotion = 10;
        } else {
            m_reqMotion = 11;
        }
        if (m_rot.y >= 360.0f) {
            m_rot.y -= 360.0f;
        }
        if (m_rot.y < 0.0f) {
            m_rot.y += 360.0f;
        }
        Mtx rot;
        PSMTXRotRad(rot, 'y', 0.017453292f * m_rot.y);
        PSMTXMultVecSR(rot, &s_brushDir, &m_brushOfs);
        PSVECAdd(&m_pos, &m_brushOfs, &m_brushPos);
        CollidePartner();
        ClampToFloor();
        PSVECAdd(&m_pos, &m_brushOfs, &m_brushPos);
    }
}

void CPlayer::ClampToFloor()
{
    Vec pos = m_pos;
    Vec body = m_pos;
    Vec brush = m_brushPos;
    int team = (m_slot < 2) ? 0 : 1;
    float d;

    if (team == 0) {
        body.x += 555.0f;
        brush.x += 555.0f;
    } else {
        body.x += -95.0f;
        brush.x += -95.0f;
    }
    body.z += 252.0f;
    brush.z += 252.0f;
    if (body.x - 60.000004f < 0.0f) {
        d = body.x - 60.000004f;
        pos.x -= d;
    }
    if (60.000004f + body.x > 460.0f) {
        d = (60.000004f + body.x) - 460.0f;
        pos.x -= d;
    }
    if (body.z - 60.000004f < 0.0f) {
        d = body.z - 60.000004f;
        pos.z -= d;
    }
    if (60.000004f + body.z > 876.0f) {
        d = (60.000004f + body.z) - 876.0f;
        pos.z -= d;
    }
    if (brush.x - 50.0f < 0.0f) {
        d = brush.x - 50.0f;
        pos.x -= d;
    }
    if (50.0f + brush.x > 460.0f) {
        d = (50.0f + brush.x) - 460.0f;
        pos.x -= d;
    }
    if (brush.z - 50.0f < 0.0f) {
        d = brush.z - 50.0f;
        pos.z -= d;
    }
    if (50.0f + brush.z > 876.0f) {
        d = (50.0f + brush.z) - 876.0f;
        pos.z -= d;
    }
    m_pos.x = pos.x;
    m_pos.y = pos.y;
    m_pos.z = pos.z;
}

void CPlayer::CollidePartner()
{
    Vec& pos = m_pos;
    Vec brush = m_brushPos;
    static CFlow* s_flow = m_flow;
    int slot = m_slot;
    int partnerSlot = ((slot & 1) ^ 1) + (slot / 2) * 2;
    CPlayer* partner;
    Vec other;
    Vec dir;
    Vec push;
    Vec pull;
    float dist;

    for (int i = 0; i < 4; i++) {
        partner = s_flow->GetPlayer(i);
        if (partnerSlot == partner->GetSlot()) {
            break;
        }
    }
    Vec partnerPos = partner->GetPos();
    m_bumped = 0;
    PSVECSubtract(&pos, &partnerPos, &dir);
    dist = VecMag(&dir);
    if (dist < 120.00001f) {
        PSVECScale(&dir, &dir, (120.00001f - dist) / dist);
        PSVECScale(&dir, &push, -0.5f);
        PSVECScale(&dir, &pull, 0.5f);
        PSVECAdd(&push, &partnerPos, &partnerPos);
        PSVECAdd(&pull, &pos, &pos);
        partner->m_pos.x = partnerPos.x;
        partner->m_pos.y = partnerPos.y;
        partner->m_pos.z = partnerPos.z;
        m_bumped = 1;
    }
    other = partner->GetBrushPos();
    PSVECSubtract(&pos, &other, &dir);
    dist = VecMag(&dir);
    if (dist < 120.00001f) {
        PSVECScale(&dir, &dir, (120.00001f - dist) / dist);
        PSVECScale(&dir, &push, -0.5f);
        PSVECScale(&dir, &pull, 0.5f);
        PSVECAdd(&push, &partnerPos, &partnerPos);
        PSVECAdd(&pull, &pos, &pos);
        partner->m_pos.x = partnerPos.x;
        partner->m_pos.y = partnerPos.y;
        partner->m_pos.z = partnerPos.z;
        m_bumped = 1;
    }
    other = partner->GetBrushPos();
    PSVECSubtract(&brush, &other, &dir);
    dist = VecMag(&dir);
    if (dist < 100.0f) {
        Vec hit = dir;

        PSVECScale(&hit, &hit, -0.5f);
        PSVECAdd(&brush, &hit, &hit);
        PSVECScale(&dir, &dir, (100.0f - dist) / dist);
        PSVECScale(&dir, &push, -0.5f);
        PSVECScale(&dir, &pull, 0.5f);
        PSVECAdd(&push, &partnerPos, &partnerPos);
        PSVECAdd(&pull, &pos, &pos);
        partner->m_pos.x = partnerPos.x;
        partner->m_pos.y = partnerPos.y;
        partner->m_pos.z = partnerPos.z;
        if ((m_hitCount & 31) == 0) {
            CharEffectHitCreate(1, &hit, &m_rot);
        }
        m_hitCount++;
        omVibrate(GetPlayerNo(), 1, 6, 6);
        m_bumped = 1;
    } else {
        m_hitCount = 0;
    }
}

CRunner::CRunner(Process_s* om, const MotionEntry* tbl, int motNum, u32 dataNum) : CModelBase(om, tbl, motNum, dataNum)
{
    m_time = 0;
    m_jumpVel = 20.0f;
    m_jumped = 0;
    Vec pos[2] = { { -325.0f, 0.0f, -100.0f }, { 325.0f, 0.0f, -100.0f } };
    static const u32 s_childData[2] = { 0x590006, 0x590007 }; /* after pos: rodata 590 (pos) precedes 5A8 */
    for (int i = 0; i < 2; i++) {
        m_child[i] = new CGuruguru(om, s_childData[i], i);
        CGuruguru* child = m_child[i];
        child->m_pos.x = pos[i].x;
        child->m_pos.y = pos[i].y;
        child->m_pos.z = pos[i].z;
    }
    HuAudFXPlay(0x7A2);
}

CModelBase::~CModelBase() {}

CRunner::~CRunner()
{
    int i;

    for (i = 0; i < 2; i++) {
        delete m_child[i];
    }
}

void CRunner::UpdateMain()
{
    m_rot.y = 90.0f;
    m_time++;
    if (m_time < 72.0f) {
        m_reqMotion = 1;
        m_pos.x += 5.0f;
    } else {
        m_reqMotion = 2;
        m_pos.x += 11.666667f;
        if (!m_jumped) {
            Hu3DMotionSpeedSet(GetModel(), 2.0f);
        } else {
            Hu3DMotionSpeedSet(GetModel(), 0.5f);
        }
    }
    if (m_pos.x > -340.0f && m_pos.x < -300.0f) {
        for (int i = 0; i < 2; i++) {
            m_child[i]->appear();
        }
    }
    if (m_pos.x > -200.0f && m_pos.x < 300.0f) {
        if (m_pos.x < 0.0f) {
            m_jumpVel += -m_jumpVel / 6.0f;
            m_pos.y += m_jumpVel;
        } else {
            m_jumpVel += (20.0f - m_jumpVel) / 6.0f;
            m_pos.y += -m_jumpVel;
        }
        if (!m_jumped) {
            CharEffectShoeHitCreate(1, &m_pos, &m_rot);
            m_jumped = 1;
        }
    }
    UpdateModel();
}

} // namespace m531
