#include "REL/m513Dll/player.h"
#include "REL/m513Dll/heiho.h"
#include "REL/m513Dll/leaf.h"
#include "REL/m513Dll/audio.h"

namespace m513 {

CHeihoCarrier::CHeihoCarrier()
{
    m_model.reset(new CModel(0x47000Du));
}

CHeihoCarrier::~CHeihoCarrier() {}

bool CHeihoCarrier::getHookPos(int i, Vec* pos, Vec* rot)
{
    static char* names[4] = { (char*)"p01", (char*)"p02", (char*)"p03", (char*)"p04" };
    HU3DMODELID id = m_model->id();
    HSFOBJECT* obj = Hu3DModelObjPtrGet(id, names[i]);
    if (obj) {
        *pos = *(Vec*)&obj->mesh.curr.pos;
        *rot = *(Vec*)&obj->mesh.curr.rot;
        rot->y += 90.0f;
    }
    return !Hu3DMotionEndCheck(id);
}

/* line padding: the assert below is retail's heiho.cpp:88 */




























CHeiho::CHeiho(int idx) : m_model(0x470008u), m_motion(-1), m_mot_id()
{
    m_idx = idx;
    m_state = 0;
    m_time = 0.0f;
    m_seTime = 0.0f;
    m_throwFrame = 0;
    insertBack(ASet<CHeiho>::instance());
    m_unk28 = 60.000004f;
    HU3DMODELID id = m_model.id();
    Hu3DModelCameraSet(id, 1);
    Hu3DModelLayerSet(id, 3);
    Hu3DModelShadowSet(id);
    Hu3DModelShadowDispOn(id);
    m_mot_id.clear();
    m_mot_id.reserve(NUMBEROF_MOTION);
    addMotion(0x470009);
    addMotion(0x47000B);
    addMotion(0x47000C);
    addMotion(0x47000A);
    assert(m_mot_id.size() == NUMBEROF_MOTION);
    m_pos.x = 0.0f;
    m_pos.y = 0.0f;
    m_pos.z = 0.0f;
    m_rot.x = 0.0f;
    m_rot.y = 0.0f;
    m_rot.z = 0.0f;
    m_model.setPos(&m_pos);
    createItem();
    setMotion(0, false, 8.0f);
    setProc(&CHeiho::procMain);
}

CHeiho::~CHeiho() {}

void CHeiho::createItem()
{
    HU3DMODELID id = m_model.id();
    HU3DMODELID item = Hu3DModelCreate(HuDataSelHeapReadNum(0x47000E, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelHookSet(id, (char*)"itemhook_L", item);
    Hu3DModelRotSet(item, 0.0f, 270.0f, 0.0f);
    Hu3DModelLayerSet(item, 3);
    Hu3DModelCameraSet(item, 1);
    Hu3DModelShadowSet(item);
    Hu3DModelShadowDispOn(item);
    m_item = item;
}

void CHeiho::releaseItem()
{
    HU3DMODELID id = m_model.id();
    Hu3DModelHookReset(id);
    Hu3DModelKill(m_item);
}

void CHeiho::giveLeaf()
{
    ASet<CLeaf>* leaves = ASet<CLeaf>::instance();
    CLeaf* l = leaves->begin();
    CLinkNode* end = leaves->end();
    for (; l != end; l = l->next()) {
        if (l->m_idx == m_idx) {
            break;
        }
    }
    l->Show();
}

void CHeiho::procNone() {}

/* state 0 ride the carrier hook (getHookPos inlined; its result unused), SE 0x2C2 every 0.25 s, hop off after
 * s_rideTime[idx] s; 1 ease rot.y to 0 and z to -340 for 1 s; 2 throw: at frame 15 release the item, show the
 * player's tree, SE s_se[idx]; 3 at the motion end idle + procNone. Cases fall through (retail). */
void CHeiho::procMain()
{
    static float s_rideTime[4] = { 4.0f, 3.5f, 3.0f, 2.5f };
    switch (m_state) {
    case 0: {
        CHeihoCarrier* carrier = CSingleton<CHeihoCarrier>::GetInstance();
        setMotion(1, false, 8.0f);
        carrier->getHookPos(m_idx, &m_pos, &m_rot);
        m_time += 1.0 / 60.0;
        m_seTime += 1.0 / 60.0;
        if (m_seTime > 0.25f) {
            PlaySe(0x2C2, m_pos);
            m_seTime = 0.0f;
        }
        if (m_time < s_rideTime[m_idx]) {
            break;
        }
        m_time = 0.0f;
        m_state++;
    }
    case 1:
        m_rot.y += -m_rot.y / 12.0f;
        m_pos.z += (-340.0f - m_pos.z) / 30.0f;
        m_time += 1.0 / 60.0;
        if (m_time < 1.0f) {
            break;
        }
        setMotion(2, true, 8.0f);
        m_state++;
    case 2:
        if (m_throwFrame != 0xFF) {
            m_throwFrame++;
            if (m_throwFrame == 15) {
                releaseItem();
                giveLeaf();
                m_throwFrame = 0xFF;
                static const int s_se[4] = { 0x6D1, 0x6D2, 0x6D3, 0x6D4 };
                PlaySe(s_se[m_idx], m_pos);
            }
        }
        if (!Hu3DMotionEndCheck(m_model.id())) {
            break;
        }
        m_state++;
    case 3:
        setMotion(0, false, 8.0f);
        setProc(&CHeiho::procNone);
        break;
    }
}

void CHeiho::update()
{
    if (m_proc) {
        (this->*m_proc)();
    }
    m_model.setPos(&m_pos);
    m_model.setRot(&m_rot);
}

void CHeiho::addMotion(int dataNum)
{
    HU3DMODELID id = m_model.id();
    s16 mot = Hu3DJointMotion(id, HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
    m_mot_id.push_back(mot);
}

void CHeiho::setMotion(int no, bool once, float shift)
{
    HU3DMODELID id = m_model.id();
    s16 mot = m_mot_id[no];
    if (m_motion != no) {
        Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
        Hu3DMotionShiftSet(id, mot, 0.0f, shift, !once ? HU3D_MOTATTR_LOOP : 0);
        m_motion = no;
    }
}

void CHeiho::cheer()
{
    PlaySe(0x2C5, m_pos);
    setMotion(3, false, 8.0f);
    setProc(&CHeiho::procNone);
}

} // namespace m513
