#ifndef M568_INPUT_H
#define M568_INPUT_H

#include "REL/mgcpp/game.h"

namespace m568 {

class CTube;

class CInput {
public:
    struct Data {
        bool b;       /* 0x0 B held: brake / back */
        bool a;       /* 0x1 A held: forward */
        float stickX; /* 0x4 */
    };

    virtual ~CInput();                          /* 0x08 fn_1_632C (key function) */
    virtual void get(Data* data, CTube* tube) = 0; /* 0x0C */
    void update(CTube* tube);                   /* fn_1_628C clears m_data, then get(&m_data, tube) */

    float Level() { return m_level; }

    Data m_data;   /* 0x04 */
    float m_level; /* 0x0C COM strength (GwPlayerConf.dif + 1) * 0.25, set by CPlayer() */
};

class CInputPad : public CInput {
public:
    CInputPad(int idx);                         /* fn_1_62F4 */
    virtual void get(Data* data, CTube* tube);  /* fn_1_6384 */

    int m_idx;   /* 0x10 */
    int m_padNo; /* 0x14 GwPlayerConf[idx].padNo (lha) */
};

class CInputComTeam : public CInput {
public:
    CInputComTeam();                            /* fn_1_6428 */
    /* the helpers below are unreferenced out-of-line copies of what get / avoidObstacle inline */
    static bool FindObstacle(Vec* out, const Vec* pos);  /* fn_1_6444 an active obstacle dz in (-200, 500), |dx| < 200 */
    static CTube* FindSoloTube();                        /* fn_1_65C4 the first tube with m_isSolo */
    static u32 SlopeMask(const Vec* v);                  /* fn_1_6678 */
    static int Octant(float x, float z);                 /* fn_1_6704 */
    static bool OctantHits(int mask, int oct);           /* fn_1_67BC */
    static int EscapeDir(u32 mask, float x, float z);    /* fn_1_67E4 */
    static void DirToData(const Vec* v, Data* d);        /* fn_1_6954 (no inlined copy) */
    virtual void get(Data* data, CTube* tube);           /* fn_1_69E0 */
    bool avoidObstacle(Data* data, CTube* tube);         /* fn_1_6E94 (`this` unused) */
    void keepAway(Data* data, CTube* tube, CTube* solo); /* fn_1_7110 */
    void SteerAround(Data* data, CTube* tube, CTube* other); /* fn_1_7500 dead code (no caller; `this` unused) */
};

class CInputComSolo : public CInput {
public:
    CInputComSolo();
    virtual void get(Data* data, CTube* tube);  /* fn_1_76BC */
    void resetTimers();                         /* fn_1_7830 */
    CTube* selectTarget(const Vec* pos);        /* fn_1_7998 */
    CTube* nearest(const Vec* pos);             /* fn_1_7C84 the nearest team tube still in, or 0 */

    CTube* m_target;  /* 0x10 */
    u32 m_counter;    /* 0x14 never initialised (retail; only (n >> 8) & 3 is used) */
    int m_retarget;   /* 0x18 frames */
    int m_switch;     /* 0x1C frames ("distracted" while > 0) */
};

} // namespace m568

#endif
