/* score.cpp -- CScore (score.h). Every function written whole (W1 fork F5). */
#include "REL/m531Dll/score.h"
extern "C" {
#include "game/esprite.h"
#include "game/frand.h"
}

namespace m531 {

/* rodata_3F8: team colours (alpha unused) */
static const GXColor s_teamColor[2] = { { 240, 0, 0, 255 }, { 48, 96, 240, 255 } };

CScore::CScore(Process_s* om) : CScoreBase(om)
{
    int i, j;

    m_stopped = 0;
    m_frame = 0;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++) {
            m_spr[i][j] = espEntry(0x59000D, 10, 0);
            espPosSet(m_spr[i][j], 32.0f * j + (144.0f * (2 * (i & 1) + 1) - 32.0f),
                      120.0f * (2 * (s16)(i / 2) + 1));
            espColorSet(m_spr[i][j], s_teamColor[i].r, s_teamColor[i].g, s_teamColor[i].b);
        }
        espBankSet(m_spr[i][2], 10);
    }
    for (i = 0; i < 2; i++) {
        m_value[i] = 0;
    }
}

CScore::~CScore()
{
    int i, j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++) {
            espKill(m_spr[i][j]);
        }
    }
}

void CScore::on_update()
{
    if (!m_stopped && !(++m_frame & 1)) {
        for (int i = 0; i < 2; i++) {
            int v = 100.0f * (0.000015258789f * (frand() & 0xFFFF)); /* 0..99; banked as s16 */
            espBankSet(m_spr[i][0], ((s16)v / 10) % 10);
            espBankSet(m_spr[i][1], (s16)v % 10);
        }
    }
}

void CScore::SetScore(int team, int value)
{
    int hundreds = value / 100; /* retail R4: stored to 0x8(r1) and never read -- 100 % shows "00" */

    espBankSet(m_spr[team][0], (value / 10) % 10);
    espBankSet(m_spr[team][1], value % 10);
}

void CScore::DispOn()
{
    int i, j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++) {
            espDispOn(m_spr[i][j]);
        }
    }
}

void CScore::DispOff()
{
    int i, j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++) {
            espDispOff(m_spr[i][j]);
        }
    }
}

} // namespace m531
