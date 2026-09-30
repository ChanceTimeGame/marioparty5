#include "REL/m511Dll/config.h"
#include "REL/m511Dll/score.h"

namespace m511 {

CRaceTimer::CRaceTimer(u32 record, bool deca)
{
    m_record = record;
    m_created = false;
    m_deca = deca;
    if (!m_deca) {
        create();
    }
}

CRaceTimer::~CRaceTimer()
{
    if (m_created) {
        MgTimerKill(m_timer);
    }
}

/* normal: a RECORD timer 0..18000 at (292, 70); Decathlon: a SCORE timer 0..5400 at (292, 58) */
void CRaceTimer::create()
{
    if (m_deca) {
        m_timer = MgTimerCreate(MGTIMER_TYPE_SCORE);
        MgTimerParamSet(m_timer, 0, 5400, m_record);
        MgTimerPosSet(m_timer, 292.0f, 58.0f);
    } else {
        m_timer = MgTimerCreate(MGTIMER_TYPE_RECORD);
        MgTimerParamSet(m_timer, 0, 18000, m_record);
        MgTimerPosSet(m_timer, 292.0f, 70.0f);
    }
    MgTimerWinColorSet(m_timer, 0, 0, 0);
    MgTimerRecordDispOn(m_timer);
    m_created = true;
}

void CRaceTimer::createDeca()
{
    if (m_deca) {
        create();
    }
}

void CRaceTimer::start()
{
    MgTimerModeOnSet(m_timer, 0);
}

/* retail pokes the timer directly: stopped, and mode 1 (MGTIMER_MODE_ON) */
void CRaceTimer::stop()
{
    if (!m_timer->stopF) {
        m_timer->stopF = TRUE;
        m_timer->mode = MGTIMER_MODE_ON;
    }
}

bool CRaceTimer::isDone()
{
    bool done = false;
    if (MgTimerDoneCheck(m_timer) && m_created) {
        done = true;
    }
    return done;
}

int CRaceTimer::getValue()
{
    return MgTimerValueGet(m_timer);
}

void CRaceTimer::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    switch (mode) {
    case 0:
        break;
    case 1:
        createDeca();
        break;
    case 2:
        start();
        break;
    case 3:
        stop();
        break;
    case 4:
        break;
    }
}

/* lbl_1_rodata_85C / 870: the pip and frame sprite anims (after create()'s literals 850..858) */
static const u32 s_pipAnim[5] = { 0x450031, 0x450033, 0x450035, 0x450037, 0x450039 };
static const u32 s_frameAnim[5] = { 0x450032, 0x450034, 0x450036, 0x450038, 0x45003A };

CScore::CScore(bool deca)
{
    m_active = false;
    m_deca = deca;
    m_show = true;
    ANIMDATA* frameAnim[5];
    ANIMDATA* pipAnim[5];
    int i;
    for (i = 0; i < 5; i++) {
        pipAnim[i] = HuSprAnimRead(HuDataSelHeapReadNum(s_pipAnim[i], HU_MEMNUM_OVL, HEAP_MODEL));
        frameAnim[i] = HuSprAnimRead(HuDataSelHeapReadNum(s_frameAnim[i], HU_MEMNUM_OVL, HEAP_MODEL));
    }
    for (int n = 0; n < 4; n++) {
        Entry* e = &m_entry[n];
        e->hasTimer = false;
        e->alpha = 0.0f;
        e->win = MgScoreWinCreate(120, 32);
        MgScoreWinColorSet(e->win, 64, 64, 64);
        MgScoreWinTPLvlSet(e->win, 0.8f);
        MgScoreWinDispSet(e->win, 0);
        HUSPRGRPID grp = e->grp = HuSprGrpCreate(10);
        for (int j = 0; j < 5; j++) {
            HuSprGrpMemberSet(grp, j, HuSprCreate(frameAnim[j], 13, 0));
            HuSprPosSet(grp, j, -44.0f + 22.0f * j, 0.0f);
        }
        for (int m = 0; m < 5; m++) {
            HuSprGrpMemberSet(grp, m + 5, HuSprCreate(pipAnim[m], 11, 0));
            HuSprPosSet(grp, m + 5, -44.0f + 22.0f * m, 0.0f);
        }
        for (int k = 0; k < 10; k++) {
            HuSprAttrSet(grp, k, HUSPR_ATTR_NOANIM);
            HuSprAttrSet(grp, k, HUSPR_ATTR_DISPOFF);
        }
    }
}

CScore::~CScore()
{
    for (int i = 0; i < 4; i++) {
        Entry* e = &m_entry[i];
        if (e->hasTimer) {
            MgTimerKill(e->timer);
        }
        HuSprGrpKill(e->grp);
    }
}

/* lbl_1_rodata_8A0: per-player HUD corner (after the ctor's literals 884..898) */
static const HuVec2f s_hudPos[4] = {
    { 76.0f, 218.0f },
    { 500.0f, 218.0f },
    { 76.0f, 424.0f },
    { 500.0f, 424.0f },
};

void CScore::initPlayer(int pno, int charNo)
{
    Entry* e = &m_entry[pno];
    e->pno = pno;
    e->charNo = charNo;
    e->count = 0;
    e->x = s_hudPos[pno].x;
    e->y = s_hudPos[pno].y;
    HuSprGrpPosSet(e->grp, e->x, e->y);
    MgScoreWinPosSet(e->win, e->x, e->y);
    for (int j = 0; j < 5; j++) {
        e->anim[j] = 18;
    }
}

void CScore::setValue(int pno, int count, int time)
{
    m_entry[pno].count = count;
    m_entry[pno].time = time;
}

/* pips below the gate count shrink back to 0, the others count up to 18 (18 = hidden) */
void CScore::updateCount(Entry* e)
{
    for (int j = 0; j < 5; j++) {
        if (j < e->count) {
            if (--e->anim[j] < 0) {
                e->anim[j] = 0;
            }
        } else {
            if (++e->anim[j] > 18.0) {
                e->anim[j] = 18;
            }
        }
    }
}

/* the fade (in 0.1 / out 0.05 a frame), the window and frames at alpha, the pips popping */
void CScore::updateDisp(Entry* e)
{
    if (m_show) {
        if ((e->alpha += 0.1) > 1.0f) {
            e->alpha = 1.0f;
        }
    } else {
        if ((e->alpha -= 0.05) < 0.0f) {
            e->alpha = 0.0f;
        }
    }
    float alpha = e->alpha; /* retail: stored, never read */
    if (e->alpha > 0.0f) {
        MgScoreWinDispSet(e->win, 1);
        MgScoreWinTPLvlSet(e->win, 0.8 * e->alpha);
        for (int i = 0; i < 5; i++) {
            HuSprAttrReset(e->grp, i, HUSPR_ATTR_DISPOFF);
            HuSprTPLvlSet(e->grp, i, e->alpha);
        }
    } else {
        MgScoreWinDispSet(e->win, 0);
        for (int i = 0; i < 5; i++) {
            HuSprAttrSet(e->grp, i, HUSPR_ATTR_DISPOFF);
        }
    }
    for (int k = 0; k < 5; k++) {
        if (e->anim[k] < 18.0) {
            HuSprAttrReset(e->grp, k + 5, HUSPR_ATTR_DISPOFF);
            float scale = (float)(e->anim[k] + 18.0) / 18.0;
            HuSprScaleSet(e->grp, k + 5, scale, scale);
            float tpLvl = (float)(18.0 - e->anim[k]) / 18.0;
            HuSprTPLvlSet(e->grp, k + 5, tpLvl * e->alpha);
        } else {
            HuSprAttrSet(e->grp, k + 5, HUSPR_ATTR_DISPOFF);
        }
    }
}

/* Decathlon: a frozen, flashing SCORE timer with the player's finish frames next to the HUD block */
void CScore::showTime(Entry* e)
{
    if (!e->hasTimer) {
        e->timer = MgTimerCreate(MGTIMER_TYPE_SCORE);
        MgTimerParamSet(e->timer, e->time, e->time, e->time);
        MgTimerModeOnSet(e->timer, MGTIMER_OFFTYPE_FLASH);
        MgTimerRecordDispOn(e->timer);
        if (!e->timer->stopF) { /* CRaceTimer::stop's pokes, repeated (retail) */
            e->timer->stopF = TRUE;
            e->timer->mode = MGTIMER_MODE_ON;
        }
        float x = 10.0f + s_hudPos[e->pno].x;
        float y = 8.0f + s_hudPos[e->pno].y;
        MgTimerPosSet(e->timer, x, y);
        MgScoreWinDispSet(e->timer->winGrpId, 0); /* a timer's window group as a score-window id (retail) */
        e->timer->winDispF = FALSE;
        e->hasTimer = true;
    }
}

void CScore::hideAll(Entry* e)
{
    for (int k = 0; k < 10; k++) {
        HuSprAttrSet(e->grp, k, HUSPR_ATTR_NOANIM);
        HuSprAttrSet(e->grp, k, HUSPR_ATTR_DISPOFF);
    }
}

void CScore::on_update()
{
    if (m_active) {
        for (int i = 0; i < 4; i++) {
            Entry* e = &m_entry[i];
            updateCount(e);
            if (m_deca && e->count > 5) {
                showTime(e);
                hideAll(e);
            } else {
                updateDisp(e);
            }
        }
    }
}

void CScore::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    switch (mode) {
    case 0:
    case 1:
        break;
    case 2:
        m_active = true;
        break;
    case 3:
        if (!m_deca) {
            m_show = false;
        }
        break;
    case 4:
        break;
    }
}

} // namespace m511
