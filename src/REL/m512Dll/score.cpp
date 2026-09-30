#include "REL/m512Dll/score.h"

namespace m512 {

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

void CRaceTimer::create()
{
    if (m_deca) {
        m_timer = MgTimerCreate(MGTIMER_TYPE_SCORE);
        MgTimerParamSet(m_timer, 0, 5400, m_record);
        MgTimerPosSet(m_timer, 292.0f, 432.0f);
    } else {
        m_timer = MgTimerCreate(MGTIMER_TYPE_RECORD);
        MgTimerParamSet(m_timer, 0, 18000, m_record);
        MgTimerPosSet(m_timer, 292.0f, 424.0f);
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

/* retail pokes the timer directly: stopped, and mode 1 (MGTIMER_MODE_ON, not OFF: sheet §11.7) */
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

CScore::CScore(bool deca)
{
    m_active = false;
    m_deca = deca;
    ANIMDATA* frameAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x460013, HU_MEMNUM_OVL, HEAP_MODEL));
    ANIMDATA* pipAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x460014, HU_MEMNUM_OVL, HEAP_MODEL));
    for (int i = 0; i < 4; i++) {
        Entry* e = &m_entry[i];
        e->hasTimer = false;
        e->win = MgScoreWinCreate(120, 32);
        MgScoreWinColorSet(e->win, 64, 64, 64);
        MgScoreWinTPLvlSet(e->win, 0.8f);
        MgScoreWinDispSet(e->win, 0);
        HUSPRGRPID grp = e->grp = HuSprGrpCreate(11);
        for (int j = 0; j < 5; j++) {
            HuSprGrpMemberSet(grp, j + 1, HuSprCreate(frameAnim, 13, 0));
            HuSprPosSet(grp, j + 1, -22.0f + 17.0f * j, 0.0f);
        }
        for (int m = 0; m < 5; m++) {
            HuSprGrpMemberSet(grp, m + 6, HuSprCreate(pipAnim, 11, 0));
            HuSprPosSet(grp, m + 6, -22.0f + 17.0f * m, 0.0f);
        }
        for (int k = 0; k < 11; k++) {
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

/* lbl_1_data_484: character icon data numbers by charNo (identical to m536 data_564). Non-const .data. */
static s32 s_charIcon[15] = {
    0x960020, 0x960021, 0x960022, 0x960023, 0x960024, 0x960026, 0x960027, 0x960028,
    0x960029, 0x96002A, 0x96002B, 0x96002C, 0x96002D, 0x96002A, 0x96002A,
};

/* lbl_1_rodata_3B0: per-player HUD corner (after the ctor's literals 388..3A8) */
static const HuVec2f s_hudPos[4] = {
    { 76.0f, 54.0f },
    { 500.0f, 54.0f },
    { 76.0f, 424.0f },
    { 500.0f, 424.0f },
};

void CScore::initPlayer(int pno, int charNo)
{
    Entry* e = &m_entry[pno];
    e->pno = pno;
    e->charNo = charNo;
    e->laps = 0;
    e->x = s_hudPos[pno].x;
    e->y = s_hudPos[pno].y;
    MgScoreWinPosSet(e->win, e->x, e->y);
    ANIMDATA* anim = HuSprAnimRead(HuDataSelHeapReadNum(s_charIcon[charNo], HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprGrpMemberSet(e->grp, 0, HuSprCreate(anim, 12, 0));
    HuSprPosSet(e->grp, 0, -42.0f, 0.0f);
    HuSprAttrSet(e->grp, 0, HUSPR_ATTR_DISPOFF);
    HuSprGrpPosSet(e->grp, e->x, e->y);
    for (int j = 0; j < 5; j++) {
        e->anim[j] = 18;
    }
}

void CScore::setValue(int pno, int laps, int time)
{
    m_entry[pno].laps = laps;
    m_entry[pno].time = time;
}

/* pips below the lap count shrink back to 0, the others count up to 18 (18 = hidden) */
void CScore::updateCount(Entry* e)
{
    for (int j = 0; j < 5; j++) {
        if (j < e->laps) {
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

void CScore::updateDisp(Entry* e)
{
    MgScoreWinDispSet(e->win, 1);
    int i;
    for (i = 0; i < 6; i++) {
        HuSprAttrReset(e->grp, i, HUSPR_ATTR_DISPOFF);
    }
    for (i = 0; i < 5; i++) {
        if (e->anim[i] < 18.0) {
            HuSprAttrReset(e->grp, i + 6, HUSPR_ATTR_DISPOFF);
            float scale = (float)(e->anim[i] + 18.0) / 18.0;
            HuSprScaleSet(e->grp, i + 6, scale, scale);
            float tpLvl = (float)(18.0 - e->anim[i]) / 18.0;
            HuSprTPLvlSet(e->grp, i + 6, tpLvl);
        } else {
            HuSprAttrSet(e->grp, i + 6, HUSPR_ATTR_DISPOFF);
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
        float x = 20.0f + s_hudPos[e->pno].x;
        float y = 8.0f + s_hudPos[e->pno].y;
        MgTimerPosSet(e->timer, x, y);
        MgScoreWinDispSet(e->timer->winGrpId, 0);
        e->timer->winDispF = FALSE;
        e->hasTimer = true;
    }
}

void CScore::hideLaps(Entry* e)
{
    MgScoreWinDispSet(e->win, 1);
    for (int k = 1; k < 11; k++) {
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
            if (m_deca && e->laps >= 5) {
                showTime(e);
                hideLaps(e);
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
        break;
    case 2:
        m_active = true;
        break;
    case 5:
        break;
    }
}

} // namespace m512
