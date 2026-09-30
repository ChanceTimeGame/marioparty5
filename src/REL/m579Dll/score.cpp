/* score.cpp -- m579::CScore (score.h). Retail order (sheet master_camera_stage_score_effect_water.md §6.3): ctor,
 * [~CSingleton<CScore> 143D4 weak], initPlayer, setValue, update (unreferenced out-of-line copy), on_update, on_new_mode,
 * dtor.
 * EXACT (adapted from m536 score.cpp, masked 0 per the sheet): on_new_mode (= m512 E65C / m536 E144), the dtor (= m509
 * EA48), ~CSingleton (= m509 E114). The ctor, initPlayer, setValue, update and on_update drafted from the sheet (§6.3).
 * .rodata 6F8: s_pos first (defined before the ctor). .data 5C0..640: the singleton strings (ctor :53, dtor :61),
 * s_icon (5EC, non-const; defined after the ctor so it follows the weak dtor's string), the vtable (+ a pad word).
 * No .bss (ms_pointer: game_master.o A2C). */
#include "REL/m579Dll/score.h"

namespace m579 {

/* lbl_1_rodata_6F8: per-player window corner */
static const float s_pos[4][2] = {
    { 55.0f, 59.0f },
    { 521.0f, 59.0f },
    { 55.0f, 422.0f },
    { 521.0f, 422.0f },
};

/* four windows / icon groups / 2-digit scores, hidden; chr / value / x / y are left
 * for initPlayer (retail) */
CScore::CScore()
{
    m_show = 0;
    for (int i = 0; i < 4; i++) {
        Entry* e = &m_entry[i];
        e->win = MgScoreWinCreate(0x50, 0x28);
        MgScoreWinColorSet(e->win, 0x40, 0x40, 0x40);
        MgScoreWinTPLvlSet(e->win, 0.8f);
        MgScoreWinDispSet(e->win, 0);
        e->grp = HuSprGrpCreate(1);
        MGSCORE* score = e->score = MgScoreCreate(0x960031, -1, 1);
        MgScoreMaxDigitSet(score, 2);
        MgScoreDispOff(score);
        MgScorePosSet(score, 3.0f + s_pos[i][0], s_pos[i][1]);
        MgScoreColorSet(score, 0xFF, 0xD8, 0x15);
        e->alpha = 0.0f;
    }
}

/* lbl_1_data_5EC: character icon data numbers by charNo (15 entries; 0x960025 skipped, the last two repeat
 * 0x96002A). Non-const .data; no bound (retail). */
static s32 s_icon[15] = {
    0x960020, 0x960021, 0x960022, 0x960023, 0x960024, 0x960026, 0x960027, 0x960028,
    0x960029, 0x96002A, 0x96002B, 0x96002C, 0x96002D, 0x96002A, 0x96002A,
};

/* `this` spilled */
void CScore::initPlayer(int i, int chr)
{
    Entry* e = &m_entry[i];
    e->chr = chr;
    e->value = 0;
    e->x = s_pos[i][0];
    e->y = s_pos[i][1];
    MgScoreWinPosSet(e->win, e->x, e->y);
    ANIMDATA* anim = HuSprAnimRead(HuDataSelHeapReadNum(s_icon[chr], HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprGrpMemberSet(e->grp, 0, HuSprCreate(anim, 12, 0));
    HuSprPosSet(e->grp, 0, -21.0f, 0.0f);
    HuSprAttrSet(e->grp, 0, HUSPR_ATTR_DISPOFF);
    HuSprGrpPosSet(e->grp, e->x, e->y);
}

void CScore::setValue(int i, int value)
{
    m_entry[i].value = value;
}

/* fade in and show (`this` unused; unreferenced copy, inlined in on_update) */
void CScore::update(Entry* e)
{
    if ((e->alpha += 0.1) > 1.0f) {
        e->alpha = 1.0f;
    }
    float a = e->alpha;
    MgScoreWinDispSet(e->win, 1);
    MgScoreWinTPLvlSet(e->win, 0.8 * a);
    MgScoreValueSet(e->score, e->value);
    MgScoreDispOn(e->score);
    MgScoreTPLvlSet(e->score, a);
    HuSprAttrReset(e->grp, 0, HUSPR_ATTR_DISPOFF);
    HuSprTPLvlSet(e->grp, 0, a);
}

void CScore::on_update()
{
    if (m_show) {
        for (int i = 0; i < 4; i++) {
            Entry* e = &m_entry[i];
            update(e);
        }
    }
}

void CScore::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    /* every case 0..4 written: CW folds the empty ones into the bare compare chain */
    switch (mode) {
    case 0:
    case 1:
        break;
    case 2:
        m_show = true;
        break;
    case 3:
    case 4:
        break;
    }
}

CScore::~CScore() {}

} // namespace m579
