#include "REL/mgcpp/minigame.h" /* the 120/210/210 triple is in heiho.o's .bss/__sinit */
#include "REL/m512Dll/heiho.h"
#include <vector>

namespace m512 {

/* lbl_1_bss_AD0: a global vector<s16> nothing uses; __sinit zero-inits it and registers player's weak
 * ~vector<s16> (fn_1_9818) as its dtor */
static std::vector<s16> s_unused;

CHeihoMan::CHeihoMan()
    : m_proc(&CHeihoMan::proc_idle), m_model(0x46000AU), m_item(0x46000BU), m_seDone(false), m_count(0)
{
    HU3DMODELID id = m_model.id();
    m_mot_id.clear();
    m_mot_id.reserve(NUMBEROF_MOTION);
    createMotion(0x460011); /* 0 idle (loop) */
    createMotion(0x460010); /* 1 start (once) */
    /* line padding: the assert below is retail's zako2.cpp:58 */































    assert(m_mot_id.size() == NUMBEROF_MOTION);
    static const Vec pos = { -104.0f, 200.0f, 550.0f };
    m_model.setPos((Vec*)&pos);
    static const Vec rot = { 0.0f, 0.0f, 0.0f };
    m_model.setRot((Vec*)&rot);
    Hu3DModelHookSet(m_model.id(), (char*)"itemhook_R", m_item.id());
    s16 motId = Hu3DMotionIDGet(id);
    Hu3DMotionSet(id, motId);
    Hu3DModelAttrSet(id, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(id, HU3D_MOTATTR_LOOP);
}

s16 CHeihoMan::createMotion(int dataNum)
{
    s16 mot = Hu3DJointMotion(m_model.id(), HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
    m_mot_id.push_back(mot);
    return mot;
}

void CHeihoMan::on_update()
{
    if (m_proc) {
        (this->*m_proc)();
    }
}

void CHeihoMan::proc_start()
{
    setMotion(1, true);
    if (!m_seDone && (float)m_count > 60.0f) {
        m_seDone = true;
        HuAudFXPlay(0x6BA);
    }
    m_count++;
}

/* retail spills and reloads r3 here (10B78/10B7C): check the spelling (sheet §9.7) */
void CHeihoMan::proc_idle()
{
    setMotion(0, false);
}

void CHeihoMan::setMotion(int motion, bool once)
{
    s16 id = m_model.id();
    s16& ref = m_mot_id.at(motion);
    s16 mot = ref;
    if (m_motion != motion) {
        Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
        Hu3DMotionShiftSet(id, mot, 0.0f, 8.0f, !once ? HU3D_MOTATTR_LOOP : 0);
        m_motion = motion;
        if (motion == 1) {
            s16 item = m_item.id();
            Hu3DModelAttrReset(item, HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrReset(item, HU3D_MOTATTR_LOOP);
            Hu3DMotionTimeSet(item, 0.0f);
        }
    }
}

void CHeihoMan::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    switch (mode) {
    case 0:
        break;
    case 1:
        setProc(&CHeihoMan::proc_start);
        break;
    case 2:
        setProc(&CHeihoMan::proc_idle);
        break;
    case 5:
        break;
    }
}

CHeihoMan::~CHeihoMan() {}

} // namespace m512
