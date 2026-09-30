/* drum.cpp -- m539::CDrum (a reel), CSlotJudge, and CModelMan (the std::map model cache). Retail order: CDrum
 * ctor, [~auto_ptr<CModel>, ~TLinkItem<CDrum>], Update .. GetSymbol, CSlotJudge, CModelMan ctor, [~map, ~__tree,
 * ~CSingleton<CModelMan>], ~CModelMan, create, Create; the MSL __tree instances follow at the end of the unit.
 * CModelMan is the MSL notebook's stand-in (20260925-msl-map/test/t_drum.cpp: every __tree/map function
 * raw-identical); create/Create differ from retail in stack-slot offsets only (F5 OUT.md). The CDrum null checks
 * are `get() != NULL` / `== NULL`: the explicit compare is what keeps the loaded pointer in a saved GPR as retail. */
#include "REL/m539Dll/drum.h"
#include "REL/mgcpp/random.h"
#include "REL/mgcpp/new.h"

namespace m539 {

CDrum::CDrum(CModel* base, char* obj, int cam)
    : m_body(CModelMan::Create(0x610005)), m_stop(CModelMan::Create(0x610006)), m_hit(CModelMan::Create(0x610007)),
      m_press(0)
{
    m_body.get()->setCamera(1 << cam);
    m_stop.get()->setCamera(1 << cam);
    m_hit.get()->setCamera(1 << cam);
    m_hit.get()->resetAttr(HU3D_MOTATTR_LOOP);
    m_stop.get()->resetAttr(HU3D_MOTATTR_LOOP);
    m_body.get()->setMotTime(10);
    m_hit.get()->setMotTime(0);
    m_stop.get()->setMotTime(0);
    m_body->setAttr(HU3D_MOTATTR_PAUSE);
    m_hit->setAttr(HU3D_MOTATTR_PAUSE);
    m_stop->setAttr(HU3D_MOTATTR_PAUSE);
    s16 id = m_body->id(); /* retail: dead (three stack shorts) */
    Mtx mtx;
    Hu3DModelObjMtxGet(base->id(), obj, mtx);
    Vec pos;
    pos.x = mtx[0][3];
    pos.y = mtx[1][3];
    pos.z = mtx[2][3];
    m_body->setPos(&pos);
    m_stop->setPos(&pos);
    m_hit->setPos(&pos);
    m_angle = (int)CRandom::frandom(0.0f, 2.5f) * 120;
    m_state = 0;
}

void CDrum::Update()
{
    if (m_body.get() != NULL) {
        switch (m_state) {
        case 0:
            break;
        case 1:
            m_angle += m_speed;
            break;
        case 2:
            m_state = 3;
            break;
        case 3:
            break;
        }
        bool rebound = false;
        if (m_press > 0 && --m_press == 0) {
            rebound = true;
        }
        if (rebound) {
            Hu3DMotionSpeedSet(m_body->id(), 0.3f);
            m_body->setAttr(HU3D_MOTATTR_REV);
        }
        Mtx* mtx = m_body->getMatrix();
        PSMTXRotRad(*mtx, 'X', 0.017453292f * m_angle);
    }
}

void CDrum::Start()
{
    m_speed = 48.0f;
    m_state = 1;
}

void CDrum::Stop()
{
    m_state = 2;
    m_angle = (int)CRandom::frandom(0.0f, 2.5f) * 120;
    PlayHit();
}

void CDrum::Press()
{
    if (m_body.get() != NULL) {
        m_press = 3;
        m_body->resetAttr(HU3D_MOTATTR_PAUSE);
        m_body->setMotTime(0);
    }
}

void CDrum::PlayHit()
{
    if (m_body.get() != NULL) {
        Hu3DMotionSpeedSet(m_body->id(), 1.0f);
        m_stop->resetAttr(HU3D_MOTATTR_PAUSE);
        m_stop->setMotTime(0);
        if (m_state == 3) {
            m_hit->resetAttr(HU3D_MOTATTR_PAUSE);
            m_hit->setMotTime(0);
            m_body->resetAttr(HU3D_MOTATTR_PAUSE);
            m_body->resetAttr(HU3D_MOTATTR_REV);
            m_body->setMotTime(0);
        }
    }
}

void CDrum::RemoveBody()
{
    m_body.reset();
}

bool CDrum::IsStopped()
{
    return m_state >= 2;
}

int CDrum::GetSymbol()
{
    if (m_body.get() == NULL) {
        return 3;
    }
    if (!IsStopped()) {
        return 4;
    }
    if (m_angle < 120.0f) {
        return 1;
    }
    if (m_angle < 240.0f) {
        return 2;
    }
    return 0;
}

CSlotJudge::CSlotJudge()
{
    m_total = 0;
}

int CSlotJudge::Judge(int a, int b, int c)
{
    int pts = 0;
    if (a != c) {
        return 0;
    }
    if (a != b && b != 3) {
        return 0;
    }
    switch (a) {
    case 0:
        pts = 5;
        break;
    case 1:
        pts = 10;
        break;
    case 2:
        pts = 50;
        break;
    }
    m_total += pts;
    return pts;
}

CModelMan::CModelMan() {}

CModelMan::~CModelMan() {}

CModel* CModelMan::create(u32 num)
{
    ModelMap::iterator it = m_map.find(num);
    if (it == m_map.end()) {
        CModel* m = new CModel(num);
        m_map.insert(ModelMap::value_type(num, m));
        return m;
    }
    CModel* m = new CModel(*it->second);
    return m;
}

CModel* CModelMan::Create(u32 num)
{
    return GetInstance()->create(num);
}

} // namespace m539

/* lbl_1_bss_9F0: drum.o is the first TU in link order to instantiate it (end of its .bss) */
template <> m539::CModelMan* CSingleton<m539::CModelMan>::ms_pointer = 0;
