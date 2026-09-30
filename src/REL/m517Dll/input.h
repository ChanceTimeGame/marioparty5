#ifndef M517_INPUT_H
#define M517_INPUT_H

#include "REL/mgcpp/game.h"

namespace m517 {

class CInput {
public:
    struct Data {
        float x;   /* 0x00 stick x */
        float y;   /* 0x04 stick y (the world z axis) */
        float mag; /* 0x08 |(x, y)| clamped to 1 */
        int level; /* 0x0C COM difficulty (the COM ctors) */
    };

    CInput();                         /* fn_1_7B2C (unreferenced; inlined) x = y = mag = 0, level = 0 */
    void update();                    /* fn_1_7B74 (player procPlay) */
    virtual ~CInput();                /* 0x08 fn_1_7C44 (key function) */
    virtual void get(Data* data) = 0; /* 0x0C */
    /* the COM difficulty (retail reads it through an accessor: lwz + mr) */
    int GetLevel() const { return m_data.level; }

    Data m_data; /* 0x04 */
};

class CInputPad : public CInput {
public:
    CInputPad(int idx);           /* fn_1_7BD4 */
    virtual void get(Data* data); /* fn_1_7C9C */

    int m_idx;   /* 0x14 */
    int m_padNo; /* 0x18 GwPlayerConf[idx].padNo (lha) */
};

class CInputCom : public CInput {
public:
    CInputCom(int idx, int dif);  /* fn_1_8000 */
    virtual ~CInputCom();         /* fn_1_8134 (the implicit body, out of line: retail's position) */
    virtual void get(Data* data); /* fn_1_81A0 */
    bool Think(float dist);       /* fn_1_83E0 */
    Vec SidePoint(float r, float deg, bool alongVel); /* fn_1_881C (hidden result) */
    Vec OppositePoint(float r);   /* fn_1_8B4C (hidden result) */
    /* by value: the inlined copies in Straddle / SegCross are retail's by-value temporaries */
    float Side(Vec a, Vec b, Vec c);                 /* fn_1_8BD4 (unreferenced; `this` unused) */
    u8 Straddle(Vec a, Vec b, Vec c, Vec d);         /* fn_1_8C88 (unreferenced) */
    bool SegCross(const Vec* a0, const Vec* a1, const Vec* b0, const Vec* b1); /* fn_1_8EB8 */
    void Update();                /* fn_1_96AC */

    Vec m_self;
    Vec m_ballPos; /* 0x20 the ball owner's position, y 0 (idem) */
    Vec m_ballVel; /* 0x2C the ball's delta, or zero below speed 0.05 */
    float m_speed; /* 0x38 the ball's GetSpeedRatio (idem) */
    int m_idx;     /* 0x3C player number */
    Vec m_stick;   /* 0x40 output: x, power (y), z */
    Vec m_target;  /* 0x4C chosen by Think */
    Vec m_smooth;  /* 0x58 eased toward m_target (/54) */
    float m_timer; /* 0x64 += 1/60 (write-only) */
    bool m_fresh;  /* 0x68 a fresh target (1 at creation) */
};

class CInputComSolo : public CInput {
public:
    enum { NUM_RUNNER = 3 };

    CInputComSolo(int dif);       /* fn_1_9930 */
    virtual void get(Data* data); /* fn_1_99EC */
    void ChooseTarget();          /* fn_1_9C54 */
    void Update();

    Vec m_self;                /* 0x14 own (solo) position, y 0 */
    Vec m_pos[NUM_RUNNER];     /* 0x20 runner positions, y 0 */
    Vec m_vel[NUM_RUNNER];     /* 0x44 runner motion (CPlayer::m_move) */
    float m_speed;             /* 0x68 own ball's speed ratio */
    bool m_out[NUM_RUNNER];    /* 0x6C runner caught */
    bool m_down[NUM_RUNNER];   /* 0x6F runner stunned (motion 5) */
    float m_timer;             /* 0x74 retarget timer (+1/60) */
    int m_target;              /* 0x78 0..2 */
    int m_mode;                /* 0x7C 0 chase, 1 chase with a 500 lead, 2 back to the centre */
    int m_count;               /* 0x80 retargets (odd: mode 2) */
};

} // namespace m517

#endif
