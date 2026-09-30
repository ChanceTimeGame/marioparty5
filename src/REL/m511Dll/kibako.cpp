#include "REL/m511Dll/config.h"
#include "REL/m511Dll/kibako.h"
#include "REL/m511Dll/water.h"
#include "REL/m511Dll/star.h"
#include "REL/m511Dll/camera.h"
#include "REL/mgcpp/random.h"

namespace m511 {

TLinkList<CKibako> CKibako::s_list;

CKibakoMan::CKibakoMan() : m_model(0x450020U)
{
    HU3DMODELID id = m_model.id();
    Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
}

CKibakoMan::~CKibakoMan()
{
    CKibako::DeleteAll();
}

/* six crates in three rings (1, 2, 3 of them) round the star gates 1..3, 300 * (j + 2) from the gate */
void CKibakoMan::Create()
{
    for (int r = 1; r < 4; r++) {
        for (int j = 0; j < r; j++) {
            Vec pos;
            float a = M_PI * (360.0f * CRandom::randomMantissa() - 180.0f) / 180.0;
            CStarMan::GetPos(r, &pos);
            pos.x += 300.0 * ((j + 2) * cos(a));
            pos.y = 0.0f;
            pos.z += 300.0 * ((j + 2) * sin(a));
            new CKibako(&m_model, &pos);
            printf("%d:%f %f\n", j + r * 5, pos.x, pos.z);
        }
    }
}

void CKibakoMan::on_update()
{
    CKibako::UpdateAll();
}

void CKibakoMan::on_new_mode(int mode)
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

CKibako::CKibako(CModel* src, const Vec* pos)
    : m_floating(true), m_model(0x450020U), m_pos(*pos), m_time(0), m_splashed(false), m_splash(0)
{
    insertBack(&s_list);
    HU3DMODELID id = m_model.id();
    Hu3DModelScaleSet(id, 1.0f, 1.0f, 1.0f);
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(id, 1);
    Hu3DModelCameraSet(id, 0xF);
    Hu3DModelAttrSet(id, 0x40000080);
    Hu3DModelAttrSet(id, 0x4000);
    Hu3DMotionTimeSet(id, 0.0f);
    m_water = CSingleton<CWater>::GetInstance();
    m_rot.x = 0.0f;
    m_rot.y = 0.0f;
    m_rot.z = 0.0f;
    updateModel();
    m_splash.reset(new CKibakoSplash);
}

/* retail: every floating crate within the 200 x 200 box is hit (no break); returns whether any was */
bool CKibako::Hit(const Vec* pos, int player)
{
    bool hit = false;
    CKibako* p = s_list.begin();
    CLinkNode* end = s_list.end();
    for (; p != end; p = p->next()) {
        if (!p->m_floating) {
            continue;
        }
        float dx = p->m_pos.x - pos->x;
        float adx = (dx < 0.0f) ? -dx : dx;
        float dz = p->m_pos.z - pos->z;
        float adz = (dz < 0.0f) ? -dz : dz;
        if (adx < 200.0 && adz < 200.0) {
            HU3DMODELID id = p->m_model.id();
            Hu3DModelAttrReset(id, 0x40000080);
            Hu3DModelAttrReset(id, 0x40000040);
            s16 mot = Hu3DMotionIDGet(id);
            Hu3DMotionSet(id, mot);
            Hu3DMotionTimeSet(id, 0.0f);
            p->m_floating = false;
            p->m_time = 0;
            hit = true;
            p->m_hitPlayer = player;
        }
    }
    return hit;
}

void CKibako::DeleteAll()
{
    while (!s_list.isEmpty()) {
        CKibako* p = s_list.last();
        delete p;
    }
}

void CKibako::UpdateAll()
{
    TLinkList<CKibako>::exec(&s_list, UpdateOne);
}

void CKibako::UpdateOne(CKibako* p)
{
    if (p->m_floating) {
        p->Float();
    } else {
        p->Break();
    }
    p->updateModel();
}

void CKibako::Float()
{
    m_pos.y += 0.02 * (m_water->GetHeight(&m_pos) - m_pos.y);
}

/* lbl_1_rodata_9E8: the per-player crate SE */
static const int s_se[4] = { 0x6B4, 0x6B5, 0x6B6, 0x6B7 };

/* broken: blink for 60 frames, splash + the hitter's SE once past frame 42, then stay hidden */
void CKibako::Break()
{
    if (m_time < 60.0f) {
        if (m_time & 1) {
            m_model.resetAttr(HU3D_ATTR_DISPOFF);
            return;
        }
        if (!m_splashed && m_time > 42.0f) {
            m_splash->Start(&m_pos);
            m_splashed = true;
            CCameraObj::PlaySePlay(&m_pos, s_se[m_hitPlayer], m_hitPlayer);
        }
    }
    m_model.setAttr(HU3D_ATTR_DISPOFF);
}

void CKibako::updateModel()
{
    m_model.setRot(&m_rot);
    m_model.setPos(&m_pos);
    m_time++;
}

} // namespace m511
