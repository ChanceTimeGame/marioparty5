#ifndef M579_WATER_H
#define M579_WATER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"

namespace m579 {

class CWater : public CGameObject, public CSingleton<CWater> {
public:
    enum { NUM_ANIM = 3 };

    CWater();                           /* fn_1_97CC */
    virtual ~CWater();                  /* fn_1_996C the three DeleteAlls, HuSprAnimKill x3 */
    static ANIMDATA* GetAnim(int i);    /* fn_1_9A70 unreferenced out-of-line copy: GetInstance()->m_anim[i] (:39) */
    virtual void on_new_mode(int mode); /* fn_1_9AF0 (= m501) */
    virtual void on_update();           /* fn_1_9B08 the three UpdateAlls */

    ANIMDATA* m_anim[NUM_ANIM];         /* 0x10 */
};

class CWaterSpray : public TLinkItem<CWaterSpray> {
public:
    CWaterSpray(Vec* pos);              /* fn_1_9B30 never called (dead) */
    ~CWaterSpray();                     /* fn_1_9C98 (= m536 779C) */
    static void DeleteAll();            /* fn_1_9D00 (= m536 7804) */
    static void UpdateAll();            /* fn_1_9DD0 (= m512 7DAC) */
    static void Update(CWaterSpray* e); /* fn_1_9E00 (= m536 7904) */
    static void Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx); /* fn_1_9E80 */

    static TLinkList<CWaterSpray> s_list; /* bss A54; its DestructorChain A48 */

    s16 m_id;      /* 0x08 */
    int m_unk0C;   /* 0x0C */
};

class CWaterDrop : public TLinkItem<CWaterDrop> {
public:
    CWaterDrop(Vec* pos);               /* fn_1_A084 (puku2 procCaught / procJump) */
    ~CWaterDrop();                      /* fn_1_A204 */
    static void DeleteAll();            /* fn_1_A26C */
    static void UpdateAll();            /* fn_1_A33C */
    static void Update(CWaterDrop* e);  /* fn_1_A36C */
    static void Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx); /* fn_1_A3EC */

    static TLinkList<CWaterDrop> s_list; /* bss A68; its DestructorChain A5C */

    s16 m_id;      /* 0x08 */
    int m_unk0C;   /* 0x0C */
};

class CRipple : public TLinkItem<CRipple>, public CModel {
public:
    typedef void (*ExecFunc)(CRipple* r);

    CRipple(Vec* pos, float maxRadius); /* fn_1_A680 (effect CSplash ctor) */
    ~CRipple();                         /* fn_1_A7AC ~CModel(flag 0), ~CLinkNode */
    static void DrawHook(HU3DMODEL* model, Mtx* mtx); /* fn_1_A818 ((CRipple*)hookData)->Draw(mtx) */
    static void DeleteAll();            /* fn_1_A850 */
    static void UpdateAll();            /* fn_1_A924 execList(&s_list, UpdateThunk) */
    static void UpdateThunk(CRipple* r); /* fn_1_A954 r->Update() (= m509 back DA70) */
    void Update();                      /* fn_1_A97C deletes this at full radius */
    void Draw(Mtx* mtx);
    /* fn_1_AF60: the delete-safe walk (m522 sunfire E65C): defined last, emitted among the template instances */
    static void execList(CLinkList* list, ExecFunc fn);

    static TLinkList<CRipple> s_list;   /* bss A7C; its DestructorChain A70 */

    /* 0x08 CModel base (the hook model) */
    Vec m_pos;          /* 0x0C (Draw uses only x / z: y is fixed at -150) */
    float m_radius;     /* 0x18 0.1 * max -> max over ~44 frames */
    float m_maxRadius;  /* 0x1C */
    u8 m_alpha;         /* 0x20 */
};

} // namespace m579

#ifndef __MWERKS__
template <> m579::CWater* CSingleton<m579::CWater>::ms_pointer; /* defined in puku2.cpp (bss A0C) */
#endif

#endif
