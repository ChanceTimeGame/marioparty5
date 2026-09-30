/* gun.cpp -- the corner cannons: CGunMan (three hidden master models) and one CGun per player. */
#include "REL/m536Dll/gun.h"

namespace m536 {

TLinkList<CGun> CGun::list;

/* lbl_1_rodata_318: base yaw per corner (degrees). .rodata placement matches (0x318). */
static const float s_cornerYaw[4] = { 45.0f, -45.0f, 135.0f, -135.0f };

/* Vec setter with double components (m501 player.h SetVec): retail builds each rotation on the stack with a
 * `frsp` on the non-constant component (Update FD5C, FE8C) */
static inline Vec& SetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
    return *v;
}

CGunMan::CGunMan() : m_barrel(0x5E0008U), m_base(0x5E0006U), m_drum(0x5E0009U)
{
    HU3DMODELID barrel = m_barrel.id();
    Hu3DModelAttrSet(barrel, HU3D_ATTR_DISPOFF);
    HU3DMODELID base = m_base.id();
    Hu3DModelAttrSet(base, HU3D_ATTR_DISPOFF);
    HU3DMODELID drum = m_drum.id();
    Hu3DModelAttrSet(drum, HU3D_ATTR_DISPOFF);
    for (int i = 0; i < 4; i++) {
        new CGun(&m_barrel, &m_base, &m_drum, i);
    }
}

CGunMan::~CGunMan()
{
    CGun::DeleteAll();
}

void CGunMan::on_update()
{
    CGun::UpdateAll();
}

void CGunMan::on_new_mode(int mode)
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

CGun::CGun(CModel* barrel, CModel* base, CModel* drum, int no) : m_barrel(*barrel), m_base(*base), m_drum(*drum)
{
    insertBack(&list);
    m_no = no;
    HU3DMOTID mot;

    HU3DMODELID barrelId = m_barrel.id();
    Hu3DModelLayerSet(barrelId, 4);
    Hu3DModelCameraSet(barrelId, 1);
    Hu3DModelAttrReset(barrelId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(barrelId, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(barrelId, HU3D_MOTATTR_LOOP);
    mot = Hu3DMotionIDGet(barrelId);
    Hu3DMotionSet(barrelId, mot);

    HU3DMODELID drumId = m_drum.id();
    Hu3DModelLayerSet(drumId, 4);
    Hu3DModelCameraSet(drumId, 1);
    Hu3DModelAttrReset(drumId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(drumId, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(drumId, HU3D_MOTATTR_LOOP);
    mot = Hu3DMotionIDGet(drumId);
    Hu3DMotionSet(drumId, mot);

    HU3DMODELID baseId = m_base.id();
    Hu3DModelLayerSet(baseId, 3);
    Hu3DModelCameraSet(baseId, 1);
    Hu3DModelAttrReset(baseId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(baseId, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(baseId, HU3D_MOTATTR_LOOP);

    setState(&CGun::stateIdle);
    m_counter = 0;
}

void CGun::DeleteAll()
{
    while (!list.isEmpty()) {
        CGun* g = list.last();
        delete g;
    }
}

void CGun::UpdateAll()
{
    TLinkList<CGun>::exec(&list, Update);
}

void CGun::Update(CGun* g)
{
    Vec rot;

    (g->*(g->m_state))();

    SetVec(&rot, 0.0f, g->m_rot, 0.0f);
    HU3DMODELID barrel = g->m_barrel.id();
    Hu3DModelRotSet(barrel, rot.x, rot.y, rot.z);
    Hu3DModelPosSet(barrel, g->m_pos.x, g->m_pos.y, g->m_pos.z);

    HU3DMODELID drum = g->m_drum.id();
    Hu3DMotionSpeedSet(drum, 1.0f);
    float t = (float)(++g->m_counter & 0x3FF) / 1024.0f;
    Hu3DModelRotSet(drum, 0.0f, 360.0 * -(t - 0.5), 0.0f);
    Hu3DModelPosSet(drum, g->m_pos.x, g->m_pos.y, g->m_pos.z);

    SetVec(&rot, 0.0f, s_cornerYaw[g->m_no], 0.0f);
    HU3DMODELID base = g->m_base.id();
    Hu3DModelRotSet(base, rot.x, rot.y, rot.z);
    Hu3DModelPosSet(base, g->m_pos.x, g->m_pos.y - 60.0f, g->m_pos.z);
}

void CGun::stateNull() {}

void CGun::stateIdle() {}

void CGun::SetRot(int no, float rot)
{
    CGun* g = list.begin();
    CLinkNode* end = list.end();
    for (; g != end; g = g->next()) {
        if (g->m_no == no) {
            g->m_rot = rot;
        }
    }
}

void CGun::SetPos(int no, Vec* pos)
{
    CGun* g = list.begin();
    CLinkNode* end = list.end();
    for (; g != end; g = g->next()) {
        if (g->m_no == no) {
            g->m_pos = *pos;
        }
    }
}

void CGun::PlayWin(int no)
{
    CGun* g = list.begin();
    CLinkNode* end = list.end();
    for (; g != end; g = g->next()) {
        if (g->m_no == no) {
            HU3DMODELID id = g->m_base.id();
            Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrReset(id, HU3D_MOTATTR_LOOP);
            HU3DMOTID mot = Hu3DMotionIDGet(id);
            Hu3DMotionSet(id, mot);
        }
    }
}

void CGun::Fire(int no)
{
    CGun* g = list.begin();
    CLinkNode* end = list.end();
    for (; g != end; g = g->next()) {
        if (g->m_no == no) {
            HU3DMODELID id = g->m_barrel.id();
            Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrReset(id, HU3D_MOTATTR_LOOP);
            Hu3DMotionTimeSet(id, 0.0f);
        }
    }
}

void CGun::SetDamage(int no, int hp)
{
    CGun* g = list.begin();
    CLinkNode* end = list.end();
    for (; g != end; g = g->next()) {
        if (g->m_no == no) {
            HU3DMODELID id = g->m_drum.id();
            float max = Hu3DMotionMaxTimeGet(id);
            if (hp == 2) {
                Hu3DMotionTimeSet(id, 0.0f);
                Hu3DMotionStartEndSet(id, 0.0f, max / 2.0f);
            } else {
                Hu3DMotionTimeSet(id, max / 2.0f);
                Hu3DMotionStartEndSet(id, max / 2.0f, max);
            }
            Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrReset(id, HU3D_MOTATTR_LOOP);
        }
    }
}

} // namespace m536
