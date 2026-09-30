/* score.cpp -- m536::CScore: the lives HUD. SKELETON: bodies marked STUB are the function forks'. */
#include "REL/m536Dll/score.h"

namespace m536 {

CScore::CScore()
{
    m_active = false;
    ANIMDATA* frameAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x5E000B, HU_MEMNUM_OVL, HEAP_MODEL));
    ANIMDATA* heartFrameAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x5E000C, HU_MEMNUM_OVL, HEAP_MODEL));
    ANIMDATA* heartAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x5E000D, HU_MEMNUM_OVL, HEAP_MODEL));
    for (int i = 0; i < 4; i++) {
        Entry* e = &m_entry[i];
        HUSPRGRPID grp = HuSprGrpCreate(8);
        e->grp = grp;
        HuSprGrpMemberSet(grp, 0, HuSprCreate(frameAnim, 400, 0));
        HuSprGrpMemberSet(grp, 2, HuSprCreate(heartFrameAnim, 300, 0));
        HuSprGrpMemberSet(grp, 3, HuSprCreate(heartFrameAnim, 300, 0));
        HuSprGrpMemberSet(grp, 4, HuSprCreate(heartFrameAnim, 300, 0));
        HuSprPosSet(grp, 2, -8.0f, 0.0f);
        HuSprPosSet(grp, 3, 14.0f, 0.0f);
        HuSprPosSet(grp, 4, 36.0f, 0.0f);
        HuSprGrpMemberSet(grp, 5, HuSprCreate(heartAnim, 100, 0));
        HuSprGrpMemberSet(grp, 6, HuSprCreate(heartAnim, 100, 0));
        HuSprGrpMemberSet(grp, 7, HuSprCreate(heartAnim, 100, 0));
        HuSprPosSet(grp, 5, -8.0f, 0.0f);
        HuSprPosSet(grp, 6, 14.0f, 0.0f);
        HuSprPosSet(grp, 7, 36.0f, 0.0f);
        for (int k = 0; k < 8; k++) {
            HuSprAttrSet(grp, k, HUSPR_ATTR_NOANIM);
            HuSprAttrSet(grp, k, HUSPR_ATTR_DISPOFF);
        }
    }
}

/* lbl_1_data_564: character icon data numbers by charNo (15 entries; 0x960025 skipped, the last two repeat
 * 0x96002A). Non-const .data. */
static s32 s_charIcon[15] = {
    0x960020, 0x960021, 0x960022, 0x960023, 0x960024, 0x960026, 0x960027, 0x960028,
    0x960029, 0x96002A, 0x96002B, 0x96002C, 0x96002D, 0x96002A, 0x96002A,
};

/* lbl_1_rodata_268: per-player HUD corner. Defined after the ctor: retail .rodata has the ctor's
 * literals first (258..264), then this table (268). */
static const HuVec2f s_hudPos[4] = {
    { 70.0f, 54.0f },
    { 508.0f, 54.0f },
    { 70.0f, 424.0f },
    { 508.0f, 424.0f },
};

void CScore::initPlayer(int pno, int charNo)
{
    Entry* e = &m_entry[pno];
    e->charNo = charNo;
    e->value = 0;
    e->x = s_hudPos[pno].x;
    e->y = s_hudPos[pno].y;
    ANIMDATA* anim = HuSprAnimRead(HuDataSelHeapReadNum(s_charIcon[charNo], HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprGrpMemberSet(e->grp, 1, HuSprCreate(anim, 300, 0));
    HuSprPosSet(e->grp, 1, -36.0f, 0.0f);
    HuSprAttrSet(e->grp, 1, HUSPR_ATTR_DISPOFF);
    HuSprGrpPosSet(e->grp, e->x, e->y);
    for (int j = 0; j < 3; j++) {
        e->anim[j] = 18;
    }
}

void CScore::setValue(int pno, int value)
{
    m_entry[pno].value = value;
}

/* hearts below the value shrink back to 0, the lost ones count up to 18 (18 = hidden) */
void CScore::updateCount(Entry* e)
{
    for (int j = 0; j < 3; j++) {
        if (j < e->value) {
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
    int i;
    for (i = 0; i < 5; i++) {
        HuSprAttrReset(e->grp, i, HUSPR_ATTR_DISPOFF);
    }
    for (i = 0; i <= 3; i++) {
        if (e->anim[i] < 18.0) {
            HuSprAttrReset(e->grp, i + 5, HUSPR_ATTR_DISPOFF);
            float scale = (float)(e->anim[i] + 18.0) / 18.0;
            HuSprScaleSet(e->grp, i + 5, scale, scale);
            float tpLvl = (float)(18.0 - e->anim[i]) / 18.0;
            HuSprTPLvlSet(e->grp, i + 5, tpLvl);
        } else {
            HuSprAttrSet(e->grp, i + 5, HUSPR_ATTR_DISPOFF);
        }
    }
}

void CScore::on_update()
{
    if (m_active) {
        for (int i = 0; i < 4; i++) {
            Entry* e = &m_entry[i];
            updateCount(e);
            updateDisp(e);
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

CScore::~CScore() {}

} // namespace m536
