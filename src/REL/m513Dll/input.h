#ifndef M513_INPUT_H
#define M513_INPUT_H

#include "REL/mgcpp/game.h"

namespace m513 {

class CInput {
public:
    struct Data {
        float x;   /* 0x00 stick x: sin(pi/2 * StkX / 56) (unused by CPlayer) */
        float y;   /* 0x04 stick y (unused) */
        float mag; /* 0x08 |(x, y)| clamped to 1 (unused; update() does not clear it) */
        u32 btn;   /* 0x0C HuPadBtnDown (Pad) / PAD_BUTTON_A pulses (Com) */
        int level; /* 0x10 COM difficulty (CInputCom() only; read into a dead local by CInputCom::get) */
    };

    virtual ~CInput();               /* 0x08 fn_1_6618 (key function) */
    virtual void get(Data* data) = 0; /* 0x0C */
    void update();                   /* fn_1_6578 clears x, y, btn, then get(&m_data) */

    Data m_data; /* 0x04 */
};

class CInputPad : public CInput {
public:
    CInputPad(int idx);           /* fn_1_65E0 */
    virtual void get(Data* data); /* fn_1_6670 */

    int m_idx;   /* 0x18 */
    int m_padNo; /* 0x1C GwPlayerConf[idx].padNo (lha) */
};

class CInputCom : public CInput {
public:
    CInputCom(int idx, int dif);  /* fn_1_69EC */
    virtual ~CInputCom();         /* fn_1_6B60 (the implicit body, written out of line: retail's position) */
    virtual void get(Data* data); /* fn_1_6BCC */

    int m_idx;    /* 0x18 */
    float m_base; /* 0x1C s_comBase[dif] frames */
    float m_bias; /* 0x20 rnd * 3 * (3 - dif) / 3, fixed at creation */
    int m_timer;  /* 0x24 frames to the next A (A when it was < 0) */
};

} // namespace m513

#endif
