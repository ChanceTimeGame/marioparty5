#ifndef M537_CENTER_OBJ_H
#define M537_CENTER_OBJ_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"
#include <memory>
#include <vector>

namespace m537 {

class Node {
public:
    void Set(const Vec* p); /* fn_1_110A4 pos = prev = p; vel = 0 (out of line; inlined in Layout) */
    void Integrate();       /* fn_1_11108 pos += vel; pos.y -= 3g */
    void Settle();          /* fn_1_11158 vel = (pos - prev) * 0.8; prev = pos */

    Vec pos;  /* 0x00 */
    Vec prev; /* 0x0C */
    Vec vel;  /* 0x18 */
};

/* CModel is a BASE (+8), not a member: ~CRope passes it flag 0 (a member gets -1; m522 CSolo precedent). Same
 * offsets as the proven layout. */
class CRope : public TLinkItem<CRope>, public CModel {
public:
    enum { NUM_NODE = 16 };

    static void UpdateFunc(CRope* r);           /* fn_1_10860 the s_ropeList exec callback */
    static void Hook(HU3DMODEL* model, Mtx* mtx); /* fn_1_10888 ((CRope*)hookData)->Draw(mtx) */
    CRope(int idx, const Vec* anchor);          /* fn_1_108CC */
    ~CRope();                                   /* fn_1_10B20 NON-virtual; the sprite is not killed (retail) */
    void Reset(const Vec* anchor);              /* fn_1_10BB0 (player updateMarker) */
    void LoadTex(int idx);                      /* fn_1_10BF0 */
    static void LimitBend(const Vec* a, const Vec* b, Vec* c, float len, float maxAng);
    void Update();                              /* fn_1_10DA8 */
    void Layout(const Vec* anchor);             /* fn_1_111C0 */
    void Draw(Mtx* mtx);                        /* fn_1_114E4 SetupGX + DrawRibbon */
    void SetupGX(Mtx* mtx);                     /* fn_1_11524 */
    static void RibbonSide(const Vec* eye, const Vec p[3], Vec out[2], float w);
    void DrawRibbon();

    /* 0x00 CLinkNode (TLinkItem) */
    /* 0x08 CModel base: CModel(Hook), layer 5, hookData = this */
    int m_num;                    /* 0x0C NUM_NODE (signed) */
    float m_segLen;               /* 0x10 24.0 */
    std::vector<Node> m_node;     /* 0x14 vector(16, Node()) */
    Vec m_dir;                    /* 0x20 normalize(anchor - centre) * 30 */
    bool m_started;               /* 0x2C Update skips the first frame */
    ANIMDATA* m_anim;             /* 0x30 0x5F000B + idx (never killed: retail) */
};

/* CModel is a BASE (+0, with the empty CSingleton base): ~CCenterObj passes it flag 0 (a member gets -1). */
class CCenterObj : public CSingleton<CCenterObj>, public CModel {
public:
    enum { NUM_ROPE = 4 };

    CCenterObj();                  /* fn_1_FF4C */
    ~CCenterObj();                 /* fn_1_10230 NON-virtual (gm on_close: delete GetInstancePtr()) */
    const Vec* GetPos();           /* fn_1_102E8 unreferenced */
    CRope* GetRope(int i);         /* fn_1_102F0 (player updateMarker) */
    void Release();                /* fn_1_10300 (player JudgeAll) */
    void Update();                 /* fn_1_1030C (unreferenced; inlined in Exec) */
    static void Exec();            /* fn_1_10590 (gm on_update) Update + every rope */

    /* 0x00 CModel base: 0x5F000A (layer 5, 0x40000001) */
    bool m_released;                      /* 0x02 */
    Vec m_target;                         /* 0x04 (0, 1050, 0); CPlayer::GetCenter keeps it at <= 1 survivor */
    Vec m_pos;                            /* 0x10 read by CRope::Update */
    Vec m_vel;                            /* 0x1C when released */
    std::auto_ptr<CRope> m_rope[NUM_ROPE]; /* 0x28 */
};

} // namespace m537

#ifndef __MWERKS__
template <> m537::CCenterObj* CSingleton<m537::CCenterObj>::ms_pointer; /* defined in game_master.cpp (bss A0C) */
#endif

#endif
