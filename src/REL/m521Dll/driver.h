/* driver.h -- the per-player input source (driver.cpp; driver sheet §2): m521::CDriver (abstract; retail names
 * m521::CDriver, CDriver::INFO, CDriverAsAI and its proc00/01/02/0e/0f are FACTS from __PRETTY_FUNCTION__ / symbols),
 * CDriverAsPad (humans; name ours) and CDriverAsAI (COMs: a stack of PTMF states in a std::deque<Node>).
 * CPlayer owns one through std::auto_ptr<CDriver> (player+0x08) and reads m_info only.
 * GC: CDriver vptr +0, m_info +4 (INFO 0x14); size 0x18. CDriverAsPad 0x20 (m_idx +0x18, m_padNo +0x1C).
 * CDriverAsAI 0x94: CDriver + CModel BASE at +0x18 (~CModel flag 0), m_stack +0x1C (MSL deque, 0x1C bytes) ...
 * Vtables (.data, emitted AI 3BC, Pad 3CC, base 3DC: reverse declaration order): {~, Get}; CDriver's Get is pure.
 * ~CDriver is the key function (out of line after CDriverAsPad()). No RTTI.
 * MSL: <deque> (CW: libs/MSL_C++, m537's; the host uses the platform std::deque). */
#ifndef M521_DRIVER_H
#define M521_DRIVER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/model.h"
#include <deque>


namespace m521 {

class CPlayer;

class CDriver {
public:
    /* the stick / button state CPlayer reads (the name is a FACT). GC 0x14. */
    struct INFO {
        float lv;  /* 0x00 (dif + 1) * 0.25: set by the CPlayer ctor; the AI's CalcWait asserts 0..1 */
        float x;   /* 0x04 stick x */
        float y;   /* 0x08 stick y (the AI writes -z) */
        float mag; /* 0x0C */
        bool btn;  /* 0x10 A (HuPadBtnDown & PAD_BUTTON_A) */
    };

    CDriver()
    {
        m_info.x = 0.0f;
        m_info.y = 0.0f;
        m_info.mag = 0.0f;
        m_info.btn = false;
    }
    virtual ~CDriver();              /* 0x08 fn_1_AFE8 (key function) */
    virtual void Get(INFO& info) = 0; /* 0x0C */
    void Update();                   /* fn_1_AF00 clears x, y, mag, btn, then Get(m_info) (player procMain) */

    INFO m_info; /* 0x04 */
};

class CDriverAsPad : public CDriver {
public:
    CDriverAsPad(int idx);         /* fn_1_AF78 */
    virtual void Get(INFO& info);  /* fn_1_B040 m513 CInputPad::get's stick mapping; btn = A */
    /* ~CDriverAsPad implicit: fn_1_DAA4 (emitted after ~CDriverAsAI) */

    int m_idx;   /* 0x18 */
    int m_padNo; /* 0x1C GwPlayerConf[idx].padNo */
};

class CDriverAsAI : public CDriver, public CModel {
public:
    typedef void (CDriverAsAI::*PROC)(INFO& info);
    struct Node {
        Node(CDriverAsAI* o, PROC f) : obj(o), fn(f) {}
        CDriverAsAI* obj; /* 0x0 always this */
        PROC fn;          /* 0x4 */
    };
    typedef std::deque<Node> Stack;

    CDriverAsAI(CPlayer* player);          /* fn_1_B3CC */
    static int CalcWait(float lv);         /* fn_1_B61C assert driver.cpp:75 (inlined in Get) */
    virtual void Get(INFO& info);
    void proc00(INFO& info);               /* fn_1_BC48 idle + look around (FACT) */
    void proc01(INFO& info);               /* fn_1_BDB0 walk to the grab point (FACT) */
    void StartPush();                      /* fn_1_C060 */
    bool IsHitOtherHand();                 /* fn_1_C164 (unreferenced; inlined in proc02) */
    void proc02(INFO& info);               /* fn_1_C210 push the hand (FACT) */
    void procXX(INFO& info);               /* fn_1_C51C (unreferenced) */
    void procToCenter(INFO& info);         /* fn_1_C790 */
    void procAway(INFO& info);             /* fn_1_C9C8 */
    void proc0e(INFO& info);               /* fn_1_CBF8 face m_dir (FACT) */
    void proc0f(INFO& info);               /* fn_1_CCC4 sidestep + jump (FACT) */
    void Orbit(INFO& info, int sign, float r); /* fn_1_CDDC */
    void Change(PROC p);                   /* fn_1_D0F0 replace the top (push when empty) */
    void Push(PROC p);                     /* fn_1_D1F8 */
    void Pop();                            /* fn_1_D26C */
    void setProcLine(int line, const char* name); /* fn_1_D298 (name unused) */
    static void DrawHook(HU3DMODEL* model, Mtx* mtx); /* fn_1_D2AC empty */
    void DrawDebug(Mtx* mtx);
    /* ~CDriverAsAI implicit: fn_1_D9D4 */

    /* 0x18 CModel base (hook model: layer 5, camera 1) */
    Stack m_stack;       /* 0x1C */
    CPlayer* m_player;   /* 0x38 */
    int m_hand;          /* 0x3C 0 hour / 1 minute (set each frame before use) */
    int m_hit;           /* 0x40 CClock::HitHands result (-1 / 0 / 1) */
    Vec m_hitDir;        /* 0x44 */
    float m_hitDepth;    /* 0x50 */
    Vec m_dir;           /* 0x54 push / face / sidestep direction */
    int m_wait;          /* 0x60 */
    int m_stuck;         /* 0x64 s_stuckTime countdown */
    int m_timer2;        /* 0x68 (procXX only) */
    int m_frame;
    float m_baseYaw;     /* 0x70 */
    bool m_overlap;      /* 0x74 hands overlap (hysteresis 40 / 80) */
    Vec m_goal;          /* 0x78 grab point */
    int m_unk84[3];      /* 0x84 never accessed */
    int m_procLine;      /* 0x90 -1; setProcLine(__LINE__) */
};

} // namespace m521

#endif
