/* input.h -- m539::CInput (input.cpp): a player's one-button input, sampled once a frame by CPlayer::update.
 * CInputPad reads pad A; CInputCom is a CSubThread coroutine that presses 8 times at random 30..59-frame gaps
 * (COM difficulty is never read). The chooser CInput::Create is defined in player.cpp (player.o D010).
 * input.cpp does not include minigame.h (no triple in input.o).
 * GC: CInput vptr +0, m_data +4 (Data: +0 never used, +4 bool on); size 0xC. CInputPad +0xC m_idx, +0x10 m_padNo;
 * size 0x14. CInputCom: CSubThread at +0x10 (8-aligned); size 0x348 (player `li r3,0x348`).
 * Vtables (.data, emitted Com 210, Pad 234, base 244): CInput {~, get = 0 (pure)}; CInputPad {~, get};
 * CInputCom primary {~, get}, secondary {thunk ~, thunk thread_exec}, then thread_exec appended (the CW rule for
 * a non-primary override). ~CInput is defined in input.cpp (source order: after CInputPad()); the derived dtors
 * are implicit (retail emits ~CInputCom/~CInputPad after thread_exec, with the vtables). */
#ifndef M539_INPUT_H
#define M539_INPUT_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/subthread.h"

namespace m539 {

class CInput {
public:
    struct Data {
        int m_unk00; /* 0x0 never read or written (host: never read, so uninitialised is harmless) */
        bool on;     /* 0x4 the button went down this frame */
    };

    CInput() { m_data.on = false; }
    /* 0x08 fn_1_6420: NOT inline -- the key function, so CInput's vtable is emitted only in input.o (an inline
     * dtor put a weak vtable + ~CInput copy into player.o's .data) */
    virtual ~CInput();
    virtual void get(Data* data) = 0;       /* 0x0C */
    void update();                          /* fn_1_6398 on = false; get(&m_data) */
    static CInput* Create(int idx);         /* fn_1_D010 (player.cpp): COM or pad by GwPlayerConf[idx].type */

    Data m_data; /* 0x04 */
};

class CInputPad : public CInput {
public:
    CInputPad(int idx);                     /* fn_1_63E0 */
    virtual void get(Data* data);           /* fn_1_6478 on = HuPadBtnDown[m_padNo] & A */

    int m_idx;   /* 0x0C */
    int m_padNo; /* 0x10 GwPlayerConf[idx].padNo (lha) */
};

class CInputCom : public CInput, public CSubThread {
public:
    CInputCom();                            /* fn_1_64B8 CSubThread(0x8000) */
    virtual void get(Data* data);
    /* fn_1_6558: 8 presses, each after irandom() % 30 + 30 frames; then returns (the thread ends) */
    virtual void thread_exec(CThreadParam param);
};

} // namespace m539

#endif
