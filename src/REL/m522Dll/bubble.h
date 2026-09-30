/* bubble.h -- bubble.cpp: the lava bubbles (sheet fire_bubble.md §2.5-§2.6). Names are ours (W0 proposals).
 * m522::CBubbleMan (0x1C; stage's m_bubble, `new` at stage E9D8): the spawner. Three spawn points on a radius-200
 *   circle at height 2500; Spawn() (stage BreakBlock at 6/4/2 blocks left) creates a CBubble at a random remaining
 *   point and records its handle; GetHandles() (player findDanger) purges dead handles.
 *   GC: empty CSingleton<CBubbleMan> base +0 (ms_pointer = bubble.o .bss 0x1C), m_count +0, m_points +4
 *   (vector<Vec>), m_handles +0x10 (vector<int>); no vptr, not a CGameObject. Non-virtual dtor (auto_ptr deletes it).
 * m522::CBubble (0x4C; Spawn `new`): a CSunFireObj with a MgActor body (model 0x50000C), an orange point light
 *   that follows it, and an additive glow disk on the lava (a static display list). On landing it bursts into a
 *   CFlare (fire.h). GC: CSunFireObj +0 (vptr +0xC), m_proc +0x14 (12-byte PTMF), m_light +0x20, m_model +0x24
 *   (auto_ptr), m_actor +0x28, m_spawn +0x2C, m_dead +0x38, m_wasLanded +0x39, m_scale +0x3C, m_alpha +0x40,
 *   m_unk44 +0x44 (write-only), m_frame +0x48. Vtable data_120 {~ 526C, update 5354, draw 5998, onFinish 5748}.
 * bubble.cpp includes no minigame.h (no .ctors). */
#ifndef M522_BUBBLE_H
#define M522_BUBBLE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/singleton.h"
#include "REL/m522Dll/sunfire.h"
#include <memory>
#include <vector>

namespace m522 {

class CBubbleMan : public CSingleton<CBubbleMan> {
public:
    CBubbleMan();                    /* fn_1_4950 */
    ~CBubbleMan();                   /* fn_1_4CF8 */
    void Spawn();                    /* fn_1_4E0C */
    std::vector<int>* GetHandles();

    int m_count;                     /* 0x00 bubbles spawned (the MgActor id is m_count + 4) */
    std::vector<Vec> m_points;       /* 0x04 the remaining spawn points */
    std::vector<int> m_handles;      /* 0x10 CSunFireObj handles of the live bubbles */
};

class CBubble : public CSunFireObj {
public:
    typedef void (CBubble::*ProcFunc)();

    Vec* GetPos(Vec* out);           /* fn_1_4F88 the actor position (player findDanger); before the ctor */
    CBubble(Vec* pos, int id);       /* fn_1_4FE4 */
    virtual ~CBubble();              /* fn_1_526C */
    void Respawn();                  /* fn_1_52FC */
    virtual void update();           /* fn_1_5354 */
    void procMain();                 /* fn_1_557C the only PTMF target (data_114) */
    virtual void onFinish();         /* fn_1_5748 MgActorColAttrSet(actor, 4) (no delete) */
    void UpdateLight();              /* fn_1_577C */
    void procSink();                 /* fn_1_5824 unreferenced (the only m_dead = 1) */
    bool IsLanded();                 /* fn_1_58DC called (not inlined) */
    void Burst(int n);               /* fn_1_58FC new CFlare (not stored) */
    virtual void draw(Mtx* mtx);     /* fn_1_5998 */
    void SetupDraw(Mtx* mtx);        /* fn_1_5A04 */
    void DrawDisk();

    ProcFunc m_proc;                 /* 0x14 (12 bytes on CW) */
    HU3DLIGHTID m_light;             /* 0x20 */
    std::auto_ptr<CModel> m_model;   /* 0x24 0x50000C */
    MGACTOR* m_actor;                /* 0x28 */
    Vec m_spawn;                     /* 0x2C */
    bool m_dead;                     /* 0x38 */
    bool m_wasLanded;                /* 0x39 */
    float m_scale;                   /* 0x3C */
    u8 m_alpha;                      /* 0x40 glow alpha */
    int m_unk44;                     /* 0x44 (int)(600 * rand), write-only */
    int m_frame;                     /* 0x48 */
};

} // namespace m522

#ifndef __MWERKS__
template <> m522::CBubbleMan* CSingleton<m522::CBubbleMan>::ms_pointer; /* defined in bubble.cpp (bss 0x1C) */
#endif

#endif
