/* score.h -- m531::CScore (score.cpp): the two teams' percentage display, 2 x 3 esprites (0x59000D, prio 10):
 * tens, ones and a fixed bank-10 glyph (guess: "%"), tinted red / blue. Until flow sets m_stopped it shows a
 * random 0..99 roulette every second frame. Created by CFlow::mode0 (`new CScore(om)`, 0x28), deleted through
 * the virtual dtor (vtable +0xC via the vptr at +8).
 * GC: CScoreBase +0 (vptr +8), m_spr +0xC, m_value +0x18, m_stopped +0x20, m_frame +0x24; size 0x28;
 * vtable data_1C0 {on_update 7898, ~ 77E4}. */
#ifndef M531_SCORE_H
#define M531_SCORE_H

#include "REL/m531Dll/scorebase.h"

namespace m531 {

class CScore : public CScoreBase {
public:
    s16 m_spr[2][3]; /* 0x0C [team][tens, ones, "%"] espEntry ids */
    s32 m_value[2];  /* 0x18 zeroed in the ctor, never used (retail R5) */
    u8 m_stopped;    /* 0x20 roulette off; flow mode 4 sets it (`stb 1,0x20`) */
    s32 m_frame;     /* 0x24 */

    CScore(Process_s* om);                /* fn_1_75A8 */
    virtual ~CScore();                    /* fn_1_77E4 */
    virtual void on_update();             /* fn_1_7898 roulette */
    /* fn_1_79E4: banks (value/10)%10 and value%10; value/100 is computed and dropped (retail R4: 100 shows "00") */
    void SetScore(int team, int value);
    void DispOn();                        /* fn_1_7AC0 */
    void DispOff();                       /* fn_1_7B38 */
};

} // namespace m531

#endif
