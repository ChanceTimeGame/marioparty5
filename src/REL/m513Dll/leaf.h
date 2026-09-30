#ifndef M513_LEAF_H
#define M513_LEAF_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"
#include "REL/m513Dll/a_set.h"
#include <memory>

namespace m513 {

class CLeafEffect : public CGameObject {
public:
    /* fn_1_77A4: the particle hook: ((CLeafEffect*)p->work)->UpdateParticles(m) */
    static void Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx m);
    CLeafEffect(Vec* pos);               /* fn_1_77E8 (unreferenced; inlined in CLeaf::Grow) */
    virtual ~CLeafEffect();              /* fn_1_79EC */
    virtual void on_new_mode(int mode);  /* fn_1_7A80 clears the bit; deletes this once every particle died */
    void InitParticle(HU3DPARTICLEDATA* p); /* fn_1_7B00 */
    void UpdateParticles(Mtx m);         /* fn_1_7D8C */

    HU3DMODELID m_id;         /* 0x10 Hu3DParticleCreate(leaf anim, 64) */
    HU3DPARTICLE* m_particle; /* 0x14 Hu3DData[m_id].hookData; ->work = this */
    bool m_allDead;           /* 0x18 set by the hook when no particle is alive */
    Vec m_pos;                /* 0x1C emitter */
};

class CLeaf : public TLinkItem<CLeaf> {
public:
    typedef void (CLeaf::*ProcFunc)();

    CLeaf(int idx, Vec* pos, Vec* rot); /* fn_1_7F04 */
    ~CLeaf();                           /* fn_1_8310 (non-virtual; deleting form called by CObjSet / player) */
    void Show();                        /* fn_1_8394 (heiho) unhides the tree and both leaves */
    void ShowLeafMotion(int i);         /* fn_1_8428 (unreferenced) */
    void PlaceLeaf(int i);              /* fn_1_8490 a leaf on its HSF object ("null1" matrix read, unused) */
    void FindLeafObjects();             /* fn_1_8578 "leaf01" / "leaf02" */
    void Grow(float dt);                /* fn_1_85F4 player: Grow(0.5) per A press */
    void Exec();                        /* fn_1_8E24 PTMF gamemaster data_3F4 */
    void proc_null();                   /* fn_1_8E6C PTMF data_2D4 */

    /* by value: the retail ctor copies the PTMF constant through a temp */
    void setProc(ProcFunc proc) { m_proc = proc; }

    /* read by CPlayer::procControl (const accessors: lbz; clrlwi / a float load) */
    bool IsFull() const { return m_full; }
    float GetPower() const { return m_power; }
    int GetIdx() const { return m_idx; }

    /* 0x00 CLinkNode (TLinkItem), on ASet<CLeaf> */
    CModel m_model;                        /* 0x08 tree 0x470004 */
    std::auto_ptr<CModel> m_leafModel[2];  /* 0x0C 0x470005 / 0x470006 */
    float m_endTime;                       /* 0x14 shape-motion end, 0..60 */
    int m_unk18;                           /* 0x18 never referenced */
    Vec m_pos;                             /* 0x1C */
    Vec m_rot;                             /* 0x28 */
    bool m_full;                           /* 0x34 the shape motion reached frame 59 */
    int m_idx;                             /* 0x38 player number */
    int m_step;                            /* 0x3C leaves shown 0..2 */
    float m_power;                         /* 0x40 shape time / 60 */
    HSFOBJECT* m_obj[2];                   /* 0x44 "leaf01" / "leaf02" */
    ProcFunc m_proc;                       /* 0x4C proc_null (12 bytes on CW) */
};

} // namespace m513

#ifndef __MWERKS__
template <> ASet<m513::CLeaf>* ASet<m513::CLeaf>::sm_ptr; /* defined in leaf.cpp */
#endif

#endif
