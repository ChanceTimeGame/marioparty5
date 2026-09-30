/* heiho.h -- m539::CHeiho (heiho.cpp): a Shy Guy walker (model 0x61000A) patrolling a fixed 4-point loop;
 * scenery owned by CMapMan (man_map.cpp, two of them). heiho.cpp does not include minigame.h.
 * GC: m_idx +0, m_pos +4, m_target +0x10, m_vel +0x1C, m_yaw +0x28, m_tyaw +0x2C, m_model +0x30, m_path +0x34,
 * m_n +0x38; size 0x3C (man_map `li r3,0x3C`). No base, no vptr. */
#ifndef M539_HEIHO_H
#define M539_HEIHO_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/model.h"
#include <memory>

namespace m539 {

/* degrees <-> 16-bit binary angle and the wrapped difference (m512/m536 player.h; SubAngle/SubAngleMax below
 * are m536 9B50/9C08 exactly) */
inline int DegToAngle(float deg)
{
    return (65536.0 / 360.0) * deg;
}

inline float AngleToDeg(int angle)
{
    return (360.0 / 65536.0) * angle;
}

inline int AngleSub(int a, int b)
{
    return ((a - b - 0x8000) & 0xFFFF) - 0x8000;
}

class CHeiho {
public:
    static float SubAngle(float a, float b);               /* fn_1_9BDC unreferenced (inlined into update) */
    static float SubAngleMax(float a, float b, float max); /* fn_1_9C94 unreferenced (inlined into update) */
    CHeiho(Vec* path, int n);                              /* fn_1_9DF8 CModelMan::Create(0x61000A) */
    void nextPoint();                                      /* fn_1_9EC0 idx = (idx+1) % n; vel toward it, 3.0 */
    void update();                                         /* fn_1_9F6C CMapMan::on_update */

    int m_idx;                     /* 0x00 current waypoint */
    Vec m_pos;                     /* 0x04 */
    Vec m_target;                  /* 0x10 m_path[m_idx] */
    Vec m_vel;                     /* 0x1C */
    float m_yaw;                   /* 0x28 degrees, never wrapped */
    float m_tyaw;                  /* 0x2C atan2(vel.x, vel.z) in degrees */
    std::auto_ptr<CModel> m_model; /* 0x30 */
    Vec* m_path;                   /* 0x34 man_map .rodata 1C0 / 1F0 */
    int m_n;                       /* 0x38 4 */
};

} // namespace m539

#endif
