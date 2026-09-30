/* player.cpp -- m568::CPlayer. Retail order: IsSolo, HitCounter::operator(), resetPos, startResultSoloWin,
 * startResultTeamWin, startWinLoseMotion, startWinLoseMotion2, finish, procResult, setStartPos, CreateTube,
 * CreateInput, ctor, [~auto_ptr<CTube>, ~vector<int>, ~__vector_pod<int>, ~__vector_base<int>, ~auto_ptr<CInput>,
 * ~TLinkItem<CPlayer>], addMotion, update, setMotion, procInit, procMain, control, updateModel, steer, motionB,
 * motionA, [__vector_pod<int>::at, ForEachSpherePair, insert, reserve], __sinit (the minigame.h triple).
 * Asserts: player.cpp:140 (DIE) and :193 (the motion count). .data 5A8..6A0: the procResult PTMF (twice), the
 * a_set strings, "DIE!", the player.cpp strings, procInit PTMF, the motion-count string, procMain PTMF, the MSL
 * vector error strings. .rodata 400..488. .bss A80..A90: the triple.
 * F3: every function masked 0 (the raw residue is pooled-string labels and register numbering). */
#include "REL/mgcpp/minigame.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/m568Dll/player.h"
#include "REL/m568Dll/stage.h"

namespace m568 {

bool IsSolo(int idx)
{
    return GwPlayerConf[idx].grp == 0;
}

void HitCounter::operator()(CSphere* a, CSphere* b)
{
    if (HitCheckSphere(a, b)) {
        ++n;
    }
}

/* player 1198C (weak, name ours): f(a->GetSphere(), b->GetSphere()) for every unordered pair of the set; the outer
 * walk stops at end()->prev() (the set's +4); both bounds are read once. The functor is passed by reference. */
template <class T, class F>
void ForEachSpherePair(ASet<T>* set, F& f)
{
    T* a = set->begin();
    CLinkNode* e = set->end();
    CLinkNode* last = e->prev();
    for (; a != last; a = a->next()) {
        for (T* b = a->next(); b != e; b = b->next()) {
            f(a->GetSphere(), b->GetSphere());
        }
    }
}

void CPlayer::resetPos()
{
    setStartPos(-4000.0f, 16000.0f);
    m_tube->Reset(&m_sphere.pos);
}

void CPlayer::startResultSoloWin()
{
    setStartPos(-500.0f, 0.0f);
    setMotion(5, false);
    setProc(&CPlayer::procResult);
    m_isWinner = m_isSolo;
    finish();
}

void CPlayer::startResultTeamWin()
{
    setStartPos(0.0f, -500.0f);
    setMotion(5, false);
    setProc(&CPlayer::procResult);
    m_isWinner = !m_isSolo;
    finish();
}

void CPlayer::startWinLoseMotion()
{
    setMotion(m_isWinner ? 6 : 7, true);
}

void CPlayer::startWinLoseMotion2()
{
    setMotion(m_isWinner ? 6 : 7, true);
}

/* the winners are AddWinner'd; every input is dropped; the losers' tubes are deleted (unlinked from ASet<CTube>:
 * the set being walked is the PLAYER set, so this is safe), the winners' stop 250 behind their rider */
void CPlayer::finish()
{
    if (m_isWinner) {
        CMinigameCore::AddWinner(m_idx);
    }
    m_input.reset(0);
    if (!m_isWinner) {
        m_tube.reset(0);
    } else {
        m_tube->Stop();
        Vec p = m_sphere.pos;
        p.z -= 250.0f;
        m_tube->Reset(&p);
    }
}

/* the model's matrix = m translated to (x, y, z) (name ours; inlined) */
static inline void SetModelMtx(Mtx m, Mtx* dst, float x, float y, float z)
{
    PSMTXTransApply(m, *dst, x, y, z);
}

void CPlayer::procResult()
{
    Mtx m;
    PSMTXIdentity(m);
    SetModelMtx(m, m_model->getMatrix(), m_sphere.pos.x, m_sphere.pos.y, m_sphere.pos.z);
}

/* line padding: the asserts below are retail's player.cpp:140 and :193 */








/* the team's start slots (lbl_1_rodata_414) */
static const float s_teamX[4] = { -300.0f, 0.0f, 300.0f, 600.0f };

/* retail: CStage::SnapToGround's result is stored (stb to the stack) and never read -- transcribed */
void CPlayer::setStartPos(float zTeam, float zSolo)
{
    m_sphere.pos.y = 0.0f;
    m_sphere.pos.z = m_isSolo ? zSolo : zTeam;
    if (m_isSolo) {
        m_sphere.pos.x = CGameObject::GetUpdateMode() == 3 ? -150.0f : 0.0f;
        return;
    }
    for (int i = 0; i < 4; i++) {
        m_sphere.pos.x = s_teamX[i];
        bool dead = CStage::SnapToGround(&m_sphere.pos);
        HitCounter c;
        c.n = 0;
        ForEachSpherePair(ASet<CPlayer>::instance(), c);
        if (c.count() == 0) {
            return;
        }
    }
    assert(!"DIE!");
}

CTube* CPlayer::CreateTube(int idx)
{
    return new CTube(IsSolo(idx) ? 0 : 1, GwPlayerConf[idx].charNo);
}

CInput* CPlayer::CreateInput(int idx)
{
    if (GwPlayerConf[idx].grp == 0) {
        if (GwPlayerConf[idx].type) {
            return new CInputComSolo;
        }
        return new CInputPad(idx);
    }
    if (GwPlayerConf[idx].type) {
        return new CInputComTeam;
    }
    return new CInputPad(idx);
}

/* the COM level (name ours; inlined: retail evaluates the level before the input pointer) */
static inline void SetLevel(CInput* input, float level)
{
    input->m_level = level;
}

/* line padding 2: the ctor's assert is retail's player.cpp:193 */


/* CreateInput, CreateTube, IsSolo, SetLevel and setStartPos are inlined (retail) */
CPlayer::CPlayer(int idx)
    : m_input(CreateInput(idx)), m_unk3C(0), m_mot_id(), m_model(new CModel(GwPlayerConf[idx].charNo, 2)),
      m_tube(CreateTube(idx))
{
    m_isSolo = IsSolo(idx);
    insertBack(ASet<CPlayer>::instance());
    m_sphere.r = 150.0f;
    SetLevel(m_input.get(), (GwPlayerConf[idx].dif + 1) / 4.0f);
    m_idx = idx;
    m_charNo = GwPlayerConf[idx].charNo;
    m_curMot = -1;
    m_mot_id.clear();
    m_mot_id.reserve(NUMBEROF_MOTION);
    addMotion(0x8C0053); /* 0 idle ride */
    addMotion(0x8C0054); /* 1 B */
    addMotion(0x8C0055); /* 2 A */
    addMotion(0x8C0056); /* 3 steer pose */
    addMotion(0x8C003F); /* 4 knocked out */
    addMotion(0x8C0000); /* 5 result idle */
    addMotion(0x8C0006); /* 6 win */
    addMotion(0x8C0007); /* 7 lose */
    assert(m_mot_id.size() == NUMBEROF_MOTION);
    CharMotionDataClose(m_charNo);
    HU3DMODELID id = m_model->id();
    Hu3DModelShadowSet(id);
    Hu3DModelShadowDispOn(id);
    Hu3DModelLayerSet(id, 0);
    Hu3DModelCameraSet(id, 1);
    setStartPos(-4000.0f, 16000.0f);
    m_tube->Reset(&m_sphere.pos);
    setProc(&CPlayer::procInit);
    m_spin = 0.0f;
}

void CPlayer::addMotion(int dataNum)
{
    s16 id = CharMotionCreate(m_charNo, dataNum);
    m_mot_id.push_back(id);
}

void CPlayer::update()
{
    if (m_proc) {
        (this->*m_proc)();
    }
    int idx = m_idx;
    if (!GwPlayerConf[idx].type) {
        CTube* tube = m_tube.get();
        if (tube && tube->TakeEvent()) {
            omVibrate(idx, 30, 6, 6);
        }
    }
}

void CPlayer::setMotion(int no, bool once)
{
    s16 mdl = m_model->id();
    s16 mot = m_mot_id[no];
    if (m_curMot != no) {
        if (m_curMot == 3) {
            /* retail: Set (not Reset) when leaving the paused steer pose (sheet §7.5) */
            Hu3DModelAttrSet(mdl, HU3D_MOTATTR_PAUSE);
        }
        if (no != 3) {
            CharMotionShiftSet(m_charNo, mot, 0.0f, (float)(no == 5 ? 0.0 : 18.0), !once ? HU3D_MOTATTR_LOOP : 0);
        } else {
            CharMotionShiftSet(m_charNo, mot, 9.0f, 18.0f, HU3D_MOTATTR_PAUSE);
        }
        m_curMot = no;
    }
}

/* setMotion inlined */
void CPlayer::procInit()
{
    if (m_isSolo) {
        setMotion(0, false);
    } else {
        setMotion(3, false);
    }
    setProc(&CPlayer::procMain);
}

void CPlayer::procMain()
{
    control();
    updateModel();
}

void CPlayer::control()
{
    if (CGameObject::GetUpdateMode() != 2) {
        steer(0.0f);
        return;
    }
    if (m_input.get() == NULL || m_tube.get() == NULL) {
        return;
    }
    CInput* input = m_input.get();
    input->update(m_tube.get());
    if (input->m_data.b) {
        m_tube->Brake();
        motionB();
    } else {
        Vec v = { 0.0f, 0.0f, 0.0f };
        v.x = input->m_data.stickX;
        if (input->m_data.a) {
            v.z = -1.0f;
            motionA();
        } else {
            steer(input->m_data.stickX);
        }
        m_tube->AddSteer(&v);
    }
}

void CPlayer::setModelPos(Mtx m, const Vec* pos)
{
    SetModelMtx(m, m_model->getMatrix(), pos->x, pos->y, pos->z);
}

/* the knocked-out tumble about a point 50 above the tube */
void CPlayer::updateModel()
{
    Mtx m;
    Mtx t;
    Quaternion q;
    PSMTXRotRad(m, 'Y', M_PI);
    if (m_tube->IsOut()) {
        m_spin += 6.0;
        if (m_spin > 360.0f) {
            m_spin -= 360.0f;
        }
        PSMTXTransApply(m, m, 0.0f, -50.0f, 0.0f);
        float spin = m_spin;
        PSMTXRotRad(t, 'X', 0.017453292f * spin);
        PSMTXConcat(t, m, m);
        PSMTXTransApply(m, m, 0.0f, 50.0f, 0.0f);
    }
    m_tube->GetRot(&q);
    PSMTXQuat(t, &q);
    PSMTXConcat(t, m, m);
    setModelPos(m, m_tube->GetPos());
    if (m_tube->IsOut()) {
        setMotion(4, false);
        return;
    }
}

/* setMotion inlined; the stick maps to a frame of the paused steer pose */
void CPlayer::steer(float x)
{
    if (!m_isSolo) {
        setMotion(3, false);
        if (m_curMot == 3) {
            m_model->setAttr(HU3D_MOTATTR_PAUSE);
            x = 9.0f + -9.0f * x;
            s16 mdl = m_model->id();
            Hu3DMotionTimeSet(mdl, x);
            Hu3DModelAttrSet(mdl, HU3D_MOTATTR_PAUSE);
        }
    }
}

void CPlayer::motionB()
{
    if (!m_isSolo) {
        setMotion(1, true);
    }
}

void CPlayer::motionA()
{
    if (!m_isSolo) {
        setMotion(2, true);
    }
}

} // namespace m568
