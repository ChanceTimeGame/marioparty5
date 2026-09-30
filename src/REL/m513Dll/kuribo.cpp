#include "REL/m513Dll/player.h"
#include "REL/m513Dll/kuribo.h"
extern "C" {
#include "game/frand.h"
}

namespace m513 {

/* (frand() & 0xFFFF) / 65536: a macro (an inline function holds its result in f31 and saves it) */
#define Rnd() ((1.0f / 65536) * (frand() & 0xFFFF))

/* line padding: the assert below is retail's kuribo.cpp:52 */









CKuribo::CKuribo(Vec* pos, Vec* rot) : m_model(0x47000Fu), m_motion(-1), m_reactMotion(-1), m_mot_id()
{
    m_state = 0;
    m_time = 0.0f;
    m_mode = -1;
    insertBack(ASet<CKuribo>::instance());
    m_unk18 = 60.000004f;
    Vec* p = &m_pos; /* retail forms this+0xC in a register (and moves it once more: 1 insn residue) */
    p->x = pos->x;
    p->y = pos->y;
    p->z = pos->z;
    m_rot.x = rot->x;
    m_rot.y = rot->y;
    m_rot.z = rot->z;
    HU3DMODELID id = m_model.id();
    Hu3DModelCameraSet(id, 1);
    Hu3DModelLayerSet(id, 3);
    m_mot_id.clear();
    m_mot_id.reserve(NUMBEROF_MOTION);
    addMotion(0x470010);
    addMotion(0x470011);
    addMotion(0x470012);
    addMotion(0x470013);
    assert(m_mot_id.size() == NUMBEROF_MOTION);
    setMotion(0, false, 16.0f);
    Hu3DMotionTimeSet(id, 4.0f * (frand() & 31));
    m_model.setPos(&m_pos);
    m_model.setRot(&m_rot);
    m_dir = rot->y == 135.0f ? 0 : 1;
    m_wait = 0.5f * Rnd();
    if ((frand() & 7) == 0) {
        m_rot.y = m_dir == 0 ? 90.0f : 0.0f;
        setMotion(0, false, 16.0f);
        m_state = 3;
        setProc(&CKuribo::procReact);
    } else {
        setProc(&CKuribo::procTurn);
    }
}

CKuribo::~CKuribo() {}

void CKuribo::addMotion(int dataNum)
{
    HU3DMODELID id = m_model.id();
    s16 mot = Hu3DJointMotion(id, HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
    m_mot_id.push_back(mot);
}

void CKuribo::setMotion(int no, bool once, float shift)
{
    HU3DMODELID id = m_model.id();
    s16 mot = m_mot_id[no];
    if (m_motion != no) {
        Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
        Hu3DMotionShiftSet(id, mot, 0.0f, shift, !once ? HU3D_MOTATTR_LOOP : 0);
        m_motion = no;
    }
}

void CKuribo::procTurn()
{
    switch (m_state) {
    case 0:
        m_time += 1.0 / 60.0;
        if (m_time < m_wait) {
            break;
        }
        m_time = 0.0f;
        setMotion(2, false, 16.0f);
        Hu3DMotionShiftStartEndSet(m_model.id(), 60.0f, 159.0f);
        m_state++;
    case 1: {
        m_time += 1.0 / 60.0;
        float speed = m_dir == 0 ? 0.22222222f : 0.25f;
        m_rot.y += m_dir == 0 ? -speed : speed;
        if (m_time < 3.0f) {
            break;
        }
        setMotion(0, false, 16.0f);
        m_state++;
    }
    case 2:
        setProc(&CKuribo::procReact);
        m_state++;
        break;
    }
}

void CKuribo::procReact()
{
    static const int s_motion[3] = { 0, 2, 3 };
    switch (m_state) {
    case 0:
        m_time += 1.0 / 60.0;
        if (m_time < m_wait) {
            break;
        }
        m_time = 0.0f;
        setMotion(m_reactMotion, false, 16.0f);
        if (m_reactMotion == 3) {
            Hu3DMotionShiftStartEndSet(m_model.id(), 40.0f, 159.0f);
        }
        m_time = 0.0f;
        m_wait = 1.0f + 3.0f * Rnd();
        m_state++;
    case 1:
        m_time += 1.0 / 60.0;
        if (m_time < m_wait) {
            break;
        }
        {
            u32 r = frand() % 3;
            setMotion(s_motion[r], false, 16.0f);
            switch (s_motion[r]) {
            case 2:
                Hu3DMotionShiftStartEndSet(m_model.id(), 60.0f, 159.0f);
                break;
            case 3:
                Hu3DMotionShiftStartEndSet(m_model.id(), 40.0f, 159.0f);
                break;
            }
            m_time = 0.0f;
            m_wait = 1.0f + 3.0f * Rnd();
        }
        break;
    }
}

void CKuribo::procEnd()
{
    switch (m_state) {
    case 0:
        m_time += 1.0 / 60.0;
        if (m_time < m_wait) {
            break;
        }
        setMotion(1, false, 16.0f);
        m_state++;
    case 1:
        break;
    }
}

void CKuribo::startEnd()
{
    m_state = 0;
    m_time = 0.0f;
    m_wait = 0.5f * Rnd();
    setProc(&CKuribo::procEnd);
}

void CKuribo::update()
{
    if (m_proc) {
        (this->*m_proc)();
    }
    m_model.setPos(&m_pos);
    m_model.setRot(&m_rot);
}

void CKuribo::setMode(int mode)
{
    if (m_mode != mode) {
        switch (mode) {
        case 0:
            m_reactMotion = 0;
            break;
        case 1:
            m_reactMotion = 3;
            break;
        }
        m_time = 0.0f;
        m_wait = Rnd();
        m_state = 0;
        m_mode = mode;
    }
}

} // namespace m513
