#include "REL/m513Dll/player.h"
#include "REL/m513Dll/score.h"
extern "C" {
#include "game/esprite.h"
}

namespace m513 {

CScore::CScore(u32 record, bool deca)
{
    m_record = record;
    m_created = false;
    m_deca = deca;
    if (!m_deca) {
        create();
    }
}

/* the deca score windows (m_win) are never killed (retail) */
CScore::~CScore()
{
    if (m_created) {
        if (m_deca) {
            for (int i = 0; i < PLAYER_NUM; i++) {
                MgTimerKill(m_timers[i]);
                espKill(m_icon[i]);
            }
        } else {
            MgTimerKill(m_timer);
        }
    }
}

/* fn_1_13430: the deca corners are a local array (its initializer is rodata_580, copied to the stack); every
 * use reloads its element and m_timers[i] */
void CScore::create()
{
    int pos[4][2] = { { 74, 54 }, { 500, 54 }, { 74, 424 }, { 500, 424 } };
    if (m_deca) {
        for (int i = 0; i < PLAYER_NUM; i++) {
            s16 w = MgScoreWinCreate(120, 32);
            MgScoreWinPosSet(w, pos[i][0], pos[i][1]);
            MgScoreWinDispSet(w, 1);
            m_win[i] = w;
            m_timers[i] = MgTimerCreate(MGTIMER_TYPE_SCORE);
            MgTimerParamSet(m_timers[i], 0, 3600, m_record);
            MgTimerPosSet(m_timers[i], 24.0f + pos[i][0], 8.0f + pos[i][1]);
            MgTimerWinColorSet(m_timers[i], 0, 0, 0);
            MgTimerRecordDispOn(m_timers[i]);
            MgScoreWinDispSet(m_timers[i]->winGrpId, 0);
            m_timers[i]->winDispF = FALSE;
            setIcon(i, GwPlayerConf[i].charNo, pos[i][0] - 42.0f, pos[i][1]);
        }
    } else {
        m_timer = MgTimerCreate(MGTIMER_TYPE_RECORD);
        MgTimerParamSet(m_timer, 0, 18000, m_record);
        MgTimerPosSet(m_timer, 292.0f, 70.0f);
        MgTimerWinColorSet(m_timer, 0, 0, 0);
        MgTimerRecordDispOn(m_timer);
    }
    m_created = true;
}

void CScore::createOnce()
{
    if (!m_created) {
        create();
    }
}

/* lbl_1_data_95C: the character icons by charNo (indexed without a bound check: retail). Non-const: .data. */
static u32 s_iconData[15] = {
    0x960020, 0x960021, 0x960022, 0x960023, 0x960024, 0x960026, 0x960027, 0x960028,
    0x960029, 0x96002A, 0x96002B, 0x96002C, 0x96002D, 0x96002A, 0x96002A,
};

void CScore::setIcon(int i, int charNo, int x, int y)
{
    m_icon[i] = espEntry(s_iconData[charNo], 0, 0);
    espBankSet(m_icon[i], 0);
    espPosSet(m_icon[i], (float)x, (float)y);
    espDispOn(m_icon[i]);
}

void CScore::start()
{
    if (m_deca) {
        for (int i = 0; i < PLAYER_NUM; i++) {
            MgTimerModeOnSet(m_timers[i], 2);
        }
    } else {
        MgTimerModeOnSet(m_timer, 0);
    }
}

void CScore::stopAll()
{
    if (m_deca) {
        for (int i = 0; i < PLAYER_NUM; i++) {
            MgTimerModeOffSet(m_timers[i]);
        }
    } else {
        MgTimerModeOffSet(m_timer);
    }
}

void CScore::stopPlayer(int i)
{
    if (m_deca) {
        MgTimerModeOffSet(m_timers[i]);
        m_timers[i]->flashFlag = MGTIMER_FLASH_COLOR;
    }
}

/* retail pokes the timers directly: stopped, and mode 1 */
void CScore::finish()
{
    if (m_deca) {
        for (int i = 0; i < PLAYER_NUM; i++) {
            if (!m_timers[i]->stopF) {
                m_timers[i]->stopF = TRUE;
                m_timers[i]->mode = MGTIMER_MODE_ON;
            }
        }
    } else {
        if (!m_timer->stopF) {
            m_timer->stopF = TRUE;
            m_timer->mode = MGTIMER_MODE_ON;
        }
    }
}

/* fn_1_13D7C: the deca loop falls out to a trailing return false */
bool CScore::isDone()
{
    if (m_deca) {
        for (int i = 0; i < PLAYER_NUM; i++) {
            if (MgTimerDoneCheck(m_timers[i]) && m_created) {
                return true;
            }
        }
    } else {
        bool done = false;
        if (MgTimerDoneCheck(m_timer) && m_created) {
            done = true;
        }
        return done;
    }
    return false;
}

/* fn_1_13E34: i is ignored in normal mode */
int CScore::getValue(int i)
{
    int v = 0;
    if (m_deca) {
        v = MgTimerValueGet(m_timers[i]);
    } else {
        v = MgTimerValueGet(m_timer);
    }
    return v;
}

void CScore::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    switch (mode) {
    case 0:
        break;
    case 1:
        createOnce();
        break;
    case 2:
        start();
        break;
    case 3:
        stopAll();
        break;
    case 4:
        break;
    }
}

} // namespace m513
