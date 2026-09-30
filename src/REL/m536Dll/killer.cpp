/* killer.cpp -- the Bullet Bills: CKillerMan (master model, per-player cooldown, the pool of 8) and CKiller
 * (one bill: a PTMF state machine idle -> fly -> explode -> idle). Functions in reference order (-inline auto
 * inlines only earlier bodies: CheckHit into stateFly, start into Launch). */
#include "REL/m536Dll/killer.h"
#include "REL/m536Dll/killereff.h"
#include "REL/m536Dll/player.h"

namespace m536 {

/* SetVec(Vec*, double, double, double) comes from player.h (m501's form: per-component frsp). */

TLinkList<CKiller> CKiller::list;

CKillerMan::CKillerMan() : m_model(0x5E000AU)
{
    HU3DMODELID id = m_model.id();
    Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
    int i; /* one counter for both loops (retail r31) */
    for (i = 0; i < 4; i++) {
        Slot& slot = m_slot[i];
        slot.active = false;
        slot.timer = 0;
    }
    for (i = 0; i < 8; i++) {
        new CKiller(&m_model, i);
    }
}

CKillerMan::~CKillerMan()
{
    CKiller::DeleteAll();
}

void CKillerMan::on_update()
{
    CKiller::UpdateAll();
    for (int i = 0; i < 4; i++) {
        Slot& slot = m_slot[i];
        if (slot.active) {
            if (++slot.timer > 60.0f) {
                slot.active = false;
            }
        }
    }
}

bool CKillerMan::Shoot(int no, Vec* pos, float rot)
{
    Slot& slot = m_slot[no]; /* retail: no bounds check (callers pass 0..3) */
    if (slot.active == true) {
        return false;
    }
    if (CKiller::Launch(no, pos, rot)) {
        slot.active = true;
        slot.timer = 0;
        return true;
    }
    return false;
}

void CKillerMan::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    switch (mode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        break;
    }
}

CKiller::CKiller(CModel* master, int index) : m_model(*master)
{
    insertBack(&list);
    m_active = false;
    m_index = index;
    HU3DMODELID id = m_model.id();
    Hu3DModelLayerSet(id, 1);
    Hu3DModelCameraSet(id, 1);
    Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
    setState(&CKiller::stateIdle);
}

bool CKiller::CheckHit(int owner, Vec* pos)
{
    CKiller* k = list.begin();
    CLinkNode* end = list.end();
    int unused = 0; /* retail dead store `stw 0,8(r1)` (E800, and F1D0 in stateFly's inlined copy); never read */
    for (; k != end; k = k->next()) {
        if (k->m_owner != owner && k->m_active == true) {
            double dx = k->m_pos.x - pos->x;
            double dz = k->m_pos.z - pos->z;
            if (dx * dx + dz * dz < 2500.0) {
                k->setState(&CKiller::stateExplode);
                return true;
            }
        }
    }
    return false;
}

void CKiller::DeleteAll()
{
    while (!list.isEmpty()) {
        CKiller* k = list.last();
        delete k;
    }
}

void CKiller::UpdateAll()
{
    TLinkList<CKiller>::exec(&list, Update);
    CKiller* first = list.begin();
    if (first != list.end()) {
        first->unlink();
        first->insertBack(&list);
    }
}

/* KillerSpeed: s_dir.z is set at run time under a guard (bss AC4) while x/y are static zeros in .data 608;
 * a non-constant initialiser does that. The spelling is a guess; the layout and code are retail's. */
inline float KillerSpeed() { return 25.0f; }

void CKiller::start(int no, Vec* pos, float rot)
{
    m_active = true;
    m_owner = no;
    m_timer = 0;
    m_pos.x = pos->x;
    m_pos.y = pos->y;
    m_pos.z = pos->z;
    m_rot = rot;
    setState(&CKiller::stateFly);
    static Vec s_dir = { 0.0f, 0.0f, KillerSpeed() }; /* retail: after the state store (.data 5FC < 608) */
    Mtx m;
    PSMTXRotRad(m, 'y', 0.017453292f * rot);
    PSMTXMultVec(m, &s_dir, &m_vel);
    Vec r;
    SetVec(&r, 0.0f, m_rot, 0.0f);
    HU3DMODELID id = m_model.id();
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    Hu3DModelRotSet(id, r.x, r.y, r.z);
    Hu3DModelPosSet(id, m_pos.x, m_pos.y, m_pos.z);
    s16 se = pos->x > 0.0f ? 0x7D3 : 0x7D2;
    HuAudFXPlay(se);
    new CKillerSmoke(&m_pos, rot);
}

bool CKiller::Launch(int no, Vec* pos, float rot)
{
    CKiller* k = list.begin();
    CLinkNode* end = list.end();
    for (; k != end; k = k->next()) {
        if (k->m_active == false) {
            k->start(no, pos, rot);
            return true;
        }
    }
    return false;
}

void CKiller::Update(CKiller* k)
{
    (k->*k->m_state)();
    Vec r;
    SetVec(&r, 0.0f, k->m_rot, 0.0f);
    HU3DMODELID id = k->m_model.id();
    Hu3DModelRotSet(id, r.x, r.y, r.z);
    Hu3DModelScaleSet(id, 0.7f, 0.7f, 0.7f);
    Hu3DModelPosSet(id, k->m_pos.x, k->m_pos.y, k->m_pos.z);
}

/* the four gun bases (rodata 2C8): a bill within 275 (XZ) of one explodes */
static const Vec s_corner[4] = {
    { 860.0f, 0.0f, -860.0f }, { -860.0f, 0.0f, -860.0f }, { 860.0f, 0.0f, 860.0f }, { -860.0f, 0.0f, 860.0f }
};

void CKiller::stateFly()
{
    /* retail: no return after any of the three stateIdle stores below -- a later hit in the same frame
     * overrides them with stateExplode */
    if (m_timer > 120.0f) {
        setState(&CKiller::stateIdle);
    }
    m_pos.x += m_vel.x;
    m_pos.y += m_vel.y;
    m_pos.z += m_vel.z;
    float x = m_pos.x; /* retail loads each coordinate once (f31/f30) and tests |x| by compare+fneg */
    if (HuAbs(x) > 1200.0) {
        setState(&CKiller::stateIdle);
    }
    float z = m_pos.z;
    if (HuAbs(z) > 1200.0) {
        setState(&CKiller::stateIdle);
    }
    m_timer++;
    /* retail dead store: a point 5 frames behind the bill, never read (F134..F190) */
    Vec tail;
    tail.x = m_pos.x - 5.0f * m_vel.x;
    tail.y = m_pos.y - 5.0f * m_vel.y;
    tail.z = m_pos.z - 5.0f * m_vel.z;
    if (CPlayer::CheckHit(m_owner, &m_pos) || CheckHit(m_owner, &m_pos)) {
        setState(&CKiller::stateExplode);
    }
    for (int i = 0; i < 4; i++) {
        float dx = m_pos.x - s_corner[i].x;
        float dz = m_pos.z - s_corner[i].z;
        if (dx * dx + dz * dz < 75625.0) {
            setState(&CKiller::stateExplode);
            break;
        }
    }
}

void CKiller::stateExplode()
{
    new CKillerBomb(&m_pos);
    m_active = false;
    s16 se = m_pos.x > 0.0f ? 0x7D3 : 0x7D2;
    HuAudFXPlay(se);
    HU3DMODELID id = m_model.id();
    Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
    setState(&CKiller::stateIdle);
}

void CKiller::stateIdle()
{
    HU3DMODELID id = m_model.id();
    Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
    m_active = false;
}

} // namespace m536
