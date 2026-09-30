/* heiho.cpp -- m539::CHeiho, the two Shy Guy walkers. Retail order: SubAngle, SubAngleMax, ctor, nextPoint,
 * update. SKELETON: SubAngle/SubAngleMax are m512/m536's exactly; ctor/nextPoint drafts from the asm; update from
 * the sheet (player_input_heiho_effect.md §3); F5: nextPoint/update written (update: FPR-allocation residue only). */
#include "REL/m539Dll/heiho.h"
#include "REL/m539Dll/drum.h"

namespace m539 {

float CHeiho::SubAngle(float a, float b)
{
    int ia = DegToAngle(a);
    int ib = DegToAngle(b);
    int d = AngleSub(ia, ib);
    return AngleToDeg(d);
}

float CHeiho::SubAngleMax(float a, float b, float max)
{
    float d = SubAngle(a, b);
    float ret;
    if (d < -max) {
        ret = -max;
    } else if (d > max) {
        ret = max;
    } else {
        ret = d;
    }
    return ret;
}

CHeiho::CHeiho(Vec* path, int n) : m_model(CModelMan::Create(0x61000A)), m_path(path), m_n(n)
{
    m_model.get()->setAttr(0x40000041);
    m_yaw = 0.0f;
    m_tyaw = 0.0f;
    m_pos.x = path[0].x;
    m_pos.y = path[0].y;
    m_pos.z = path[0].z;
    m_idx = 0;
    nextPoint();
}

void CHeiho::nextPoint()
{
    int idx = m_idx + 1;
    idx %= m_n;
    m_idx = idx;
    Vec* p = &m_path[idx];
    m_target.x = p->x;
    m_target.y = p->y;
    m_target.z = p->z;
    PSVECSubtract(&m_target, &m_pos, &m_vel);
    PSVECNormalize(&m_vel, &m_vel);
    PSVECScale(&m_vel, &m_vel, 3.0f);
}

void CHeiho::update()
{
    /* fn_1_9F6C: step, turn at a waypoint (nextPoint and SubAngleMax inline); yaw turns at most 5 deg/frame */
    PSVECAdd(&m_vel, &m_pos, &m_pos);
    Vec d;
    PSVECSubtract(&m_target, &m_pos, &d);
    float dist = PSVECMag(&d);
    if (dist < 30.000002f) {
        nextPoint();
    }
    m_tyaw = 180.0 * (atan2(m_vel.x, m_vel.z) / 3.141592653589793);
    m_yaw += SubAngleMax(m_tyaw, m_yaw, 5.0f);
    m_model->setPos(&m_pos);
    Vec rot;
    rot.x = 0.0f;
    rot.y = m_yaw;
    rot.z = 0.0f;
    m_model->setRot(&rot);
}

} // namespace m539
