/* aisu.cpp -- m501::CAisu: the ice-cream scoops. A scoop falls (aisuAllList), lands and melts
 * (aisuFallList), sinks away and deletes itself, or is caught and stacked on a cone (aisuConeList). */
#include "REL/m501Dll/aisu.h"
#include "REL/m501Dll/gamemaster.h"
#include "REL/m501Dll/stage.h"
#include "REL/m501Dll/particle.h"
#include "REL/m501Dll/random.h"
#include <vector>

namespace m501 {

/* definition order = .bss and __sinit order: Cone, All, Fall (each with its DestructorChain), handleMan */
CLinkList CAisu::aisuConeList;
CLinkList CAisu::aisuAllList;
CLinkList CAisu::aisuFallList;
CHandleMan* CAisu::aisuHandleMan;

void CAisu::init(CHandleMan* handleMan)
{
    aisuHandleMan = handleMan;
    HU3DMODELID id = Hu3DHookFuncCreate(drawHook);
    Hu3DModelLayerSet(id, 0);
    Hu3DModelCameraSet(id, 1);
}

CAisu* CAisu::getHandle(int handle)
{
    return (CAisu*)aisuHandleMan->getHandlePtr(handle);
}

void CAisu::Close()
{
    while (!aisuConeList.isEmpty()) {
        delete aisuConeList.last<CAisu>();
    }
    while (!aisuAllList.isEmpty()) {
        delete aisuAllList.last<CAisu>();
    }
    while (!aisuFallList.isEmpty()) {
        delete aisuFallList.last<CAisu>();
    }
}

CAisu::CAisu(int type, Vec* pos) : m_type(type), m_pos(*pos)
{
    insertBack(&aisuAllList);
    setState(&CAisu::stateStart);
    m_vel.x = 0.0f;
    m_vel.y = 0.0f;
    m_vel.z = 0.0f;
    m_scale = 1.0f;
    setObjName(0);
    m_handle = aisuHandleMan->insertHandle(this);
    m_seNo = HuAudFXPlay(0x624);
}

CAisu::~CAisu()
{
    aisuHandleMan->removeHandle(m_handle);
}

void CAisu::UpdateAll()
{
    execAisuList(&aisuAllList, AisuUpdate);
    execAisuList(&aisuFallList, AisuUpdate);
    execAisuList(&aisuConeList, AisuUpdate);
}

void CAisu::AisuUpdate(CAisu* aisu)
{
    (aisu->*aisu->m_state)();
    if (!aisu->isTaken()) {
        aisu->m_joint.lockMatrix();
        MtxPtr m = aisu->m_joint.getLocal();
        PSMTXTrans(m, aisu->m_pos.x, aisu->m_pos.y, aisu->m_pos.z);
        float scale = aisu->m_scale;
        m[1][1] = scale;
        float width = scale + 2.0f * (1.0f - scale);
        m[0][0] = width;
        m[2][2] = width;
    }
}

/* lbl_1_data_29C / lbl_1_data_2C8 (with their strings before them) */
static const char* s_flavorName[8] = { "str", "mav", "mint", "choco", "melon", "lemon", "ore", "bani" };
static const char* s_nameSuffix[3] = { "_A", "_B", "_C" };

void CAisu::setObjName(int suffix)
{
    sprintf(m_objName, "%s%s", s_flavorName[m_type], s_nameSuffix[suffix]);
}

void CAisu::stateStart()
{
    m_kage = true;
    m_taken = false;
    setState(&CAisu::stateFall);
    m_kageScale = 0.0f;
}

void CAisu::stateFall()
{
    Vec step = m_vel;
    m_vel.y -= 9.80665f * 100.0f / 3600.0;
    PSVECAdd(&m_vel, &step, &step);
    PSVECScale(&step, &step, 0.5f);
    PSVECAdd(&m_pos, &step, &m_pos);
    float k = 5060.02f / m_pos.y;
    float kk = k * k;
    m_kageScale = kk;
    if (m_pos.y <= 5060.02f) {
        playSound(0x626);
        m_pos.y = 5060.02f;
        setObjName(1);
        setState(&CAisu::stateMelt);
        m_kage = false;
        unlink();
        insertBack(&aisuFallList);
        CStage* stage = CSingleton<CStage>::ms_pointer;
        stage->setAisuMotion();
        CParticle::createSplash(&m_pos, m_type);
        aisuHandleMan->removeHandle(m_handle);
        m_handle = aisuHandleMan->insertHandle(this);
    }
}

void CAisu::stateMelt()
{
    m_scale -= 1.0 / 240.0;
    if (m_scale < 0.05f) {
        m_scale = 0.05f;
        setState(&CAisu::stateSink);
    }
}

void CAisu::playSound(int seNo)
{
    HuAudFXStop(m_seNo);
    m_seNo = HuAudFXPlay(seNo);
    /* pan from the scoop's position along the camera's screen x axis (rotated 53.26 deg about the centre) */
    float x = m_pos.x - 1578.489f;
    float z = m_pos.z - 414.244f;
    x = x * cos(0.92960858f) - z * sin(0.92960858f);
    x = x / (double)454.2f;
    /* not clamped, but bounded: scoops spawn inside r=454.2 and players are held inside r=474.2, so |x| <= ~1.05
     * and the pan stays within 47..81 (no musyx pan assert risk) */
    int pan = 64.0f + 16.0f * x;
    HuAudFXPanning(m_seNo, pan);
}

void CAisu::stateSink()
{
    m_pos.y -= 1.0 / 30.0;
    if (m_pos.y <= 5058.02f) {
        delete this;
        return;
    }
}

void CAisu::stateTaken() {}

void CAisu::drawHook(Hu3DModel_s* model, Mtx* mtx)
{
    Hu3DModelObjDrawInit();
    CAisuDrawData data;
    PSMTXCopy(*mtx, data.m_mtx);
    data.m_model = CGameMaster::GetAisuModel()->id();
    drawAisuList(&aisuAllList, &data);
    drawAisuList(&aisuFallList, &data);
    drawAisuList(&aisuConeList, &data);
}

void CAisu::drawAisu(CAisuDrawData* data, CAisu* aisu)
{
    Mtx mtx;
    if (aisu->m_kage) {
        PSMTXTrans(mtx, aisu->m_pos.x, 5068.02f, aisu->m_pos.z);
        mtx[0][0] = 15.0f * aisu->m_kageScale;
        mtx[2][2] = 15.0f * aisu->m_kageScale;
        PSMTXConcat(data->m_mtx, mtx, mtx);
        Hu3DModelObjDraw(data->m_model, (char*)"kage", mtx);
    }
    Mtx* jointMtx = aisu->m_joint.getMatrix();
    PSMTXConcat(data->m_mtx, *jointMtx, mtx);
    Hu3DModelObjDraw(data->m_model, aisu->m_objName, mtx);
}

CJoint* CAisu::doTake(CJoint* super, int n)
{
    playSound(0x625);
    setObjName(2);
    setState(&CAisu::stateTaken);
    m_kage = false;
    m_taken = true;
    m_joint.setSuper(super);
    m_joint.lockMatrix();
    MtxPtr m = m_joint.getLocal();
    if (n != 0) {
        m[2][3] = 60.0f;
        m[0][3] = CRandom::frandom(-10.0f, 10.0f);
        m[1][3] = CRandom::frandom(-10.0f, 10.0f);
    } else {
        m[2][3] = 0.0f;
        m[0][3] = 0.0f;
        m[1][3] = 0.0f;
    }
    Mtx rot;
    PSMTXRotRad(rot, 'X', -1.5707964f);
    PSMTXConcat(m, rot, m);
    unlink();
    insertBack(&aisuConeList);
    aisuHandleMan->removeHandle(m_handle);
    m_handle = aisuHandleMan->insertHandle(this);
    Mtx* jointMtx = m_joint.getMatrix();
    m_pos.x = 0.0f;
    m_pos.y = 0.0f;
    m_pos.z = 0.0f;
    PSMTXMultVec(*jointMtx, &m_pos, &m_pos);
    CParticle::createBurst(&m_pos, m_type);
    return &m_joint;
}

void CAisu::GetHandleList(std::vector<int>& list)
{
    list.clear();
    CAisu* p = aisuAllList.begin<CAisu>();
    CLinkNode* e = aisuAllList.end();
    for (; p != e; p = static_cast<CAisu*>(p->next())) {
        list.push_back(p->m_handle);
    }
}

bool CAisu::checkSlowMove(Vec* pos)
{
    CAisu* p = aisuFallList.begin<CAisu>();
    CLinkNode* e = aisuFallList.end();
    for (; p != e; p = static_cast<CAisu*>(p->next())) {
        float dx = pos->x - p->m_pos.x;
        float dz = pos->z - p->m_pos.z;
        double d = (double)dx * dx + (double)dz * dz;
        if (d < 1600.0) {
            return true;
        }
    }
    return false;
}

CAisu* CAisu::checkTake(Vec* pos, float r)
{
    CAisu* p = aisuAllList.begin<CAisu>();
    CLinkNode* e = aisuAllList.end();
    for (; p != e; p = static_cast<CAisu*>(p->next())) {
        Vec d;
        PSVECSubtract(pos, &p->m_pos, &d);
        float dist = PSVECMag(&d);
        if (dist <= 40.0f + r) {
            return p;
        }
    }
    return NULL;
}

u8 CAisu::isTaken()
{
    return m_taken;
}

void CAisu::GetAisuDist(std::vector<HuVec2f_s>* list)
{
    CAisu* p = aisuAllList.begin<CAisu>();
    CLinkNode* e = aisuAllList.end();
    for (; p != e; p = static_cast<CAisu*>(p->next())) {
        HuVec2f_s v = { 0.0f, 0.0f };
        v.x = p->m_pos.x;
        v.y = p->m_pos.z;
        list->push_back(v);
    }
    p = aisuFallList.begin<CAisu>();
    e = aisuFallList.end();
    for (; p != e; p = static_cast<CAisu*>(p->next())) {
        HuVec2f_s v = { 0.0f, 0.0f };
        v.x = p->m_pos.x;
        v.y = p->m_pos.z;
        list->push_back(v);
    }
}

void CAisu::setPos(Vec* pos, float t)
{
    m_pos.x += t * (pos->x - m_pos.x);
    m_pos.z += t * (pos->z - m_pos.z);
}

void CAisu::drawAisuList(CLinkList* list, CAisuDrawData* data)
{
    drawAisuList(list->begin<CAisu>(), static_cast<CAisu*>(list->end()), data);
}

void CAisu::drawAisuList(CAisu* begin, CAisu* end, CAisuDrawData* data)
{
    for (; begin != end; begin = static_cast<CAisu*>(begin->next())) {
        drawAisu(data, begin);
    }
}

void CAisu::execAisuList(CLinkList* list, void (*func)(CAisu*))
{
    if (!list->isEmpty()) {
        /* move every scoop to a local list, then back one at a time before its callback: a callback may
         * delete its scoop (stateSink) or move it to another list (stateFall, doTake) safely */
        CLinkList tmp;
        list->copyLink(&tmp);
        while (!tmp.isEmpty()) {
            CAisu* a = tmp.begin<CAisu>();
            a->unlink();
            a->insertBack(list);
            func(a);
        }
    }
}

} // namespace m501
