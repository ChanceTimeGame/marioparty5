#include "REL/m521Dll/score.h"

namespace m521 {

/* DRAFT (fn_1_17F78, 215 insns; sheet §6.3) */
CScore::CScore()
{
    m_active = false;
    ANIMDATA* markAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x4F0011, HU_MEMNUM_OVL, HEAP_MODEL));
    ANIMDATA* lampAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x4F0012, HU_MEMNUM_OVL, HEAP_MODEL));
    for (int t = 0; t < 2; t++) {
        ANIMDATA* winAnim = HuSprAnimRead(HuDataSelHeapReadNum(t == 0 ? 0x4F000F : 0x4F0010, HU_MEMNUM_OVL, HEAP_MODEL));
        Entry* e = &m_entry[t];
        HUSPRGRPID grp = e->grp = HuSprGrpCreate(8);
        HuSprGrpMemberSet(grp, 0, HuSprCreate(winAnim, 400, 0));
        HuSprGrpMemberSet(grp, 2, HuSprCreate(markAnim, 300, 0));
        HuSprGrpMemberSet(grp, 3, HuSprCreate(markAnim, 300, 0));
        HuSprGrpMemberSet(grp, 4, HuSprCreate(markAnim, 300, 0));
        HuSprPosSet(grp, 2, -22.0f, 0.0f);
        HuSprPosSet(grp, 3, 0.0f, 0.0f);
        HuSprPosSet(grp, 4, 22.0f, 0.0f);
        HuSprGrpMemberSet(grp, 5, HuSprCreate(lampAnim, 100, 0));
        HuSprGrpMemberSet(grp, 6, HuSprCreate(lampAnim, 100, 0));
        HuSprGrpMemberSet(grp, 7, HuSprCreate(lampAnim, 100, 0));
        HuSprPosSet(grp, 5, -22.0f, 0.0f);
        HuSprPosSet(grp, 6, 0.0f, 0.0f);
        HuSprPosSet(grp, 7, 22.0f, 0.0f);
        for (int k = 0; k < 8; k++) {
            HuSprAttrSet(grp, k, HUSPR_ATTR_NOANIM);
            HuSprAttrSet(grp, k, HUSPR_ATTR_DISPOFF);
        }
        initTeam(t);
    }
}

/* lbl_1_rodata_3DC: the HUD corner per team */
static const float s_pos[2][2] = { { 58.0f, 54.0f }, { 520.0f, 54.0f } };

void CScore::initTeam(int t)
{
    Entry* e = &m_entry[t];
    e->value = 0;
    e->x = s_pos[t][0];
    e->y = s_pos[t][1];
    HuSprPosSet(e->grp, 1, -36.0f, 0.0f);
    HuSprAttrSet(e->grp, 1, HUSPR_ATTR_DISPOFF);
    HuSprGrpPosSet(e->grp, e->x, e->y);
    for (int k = 0; k < 3; k++) {
        e->anim[k] = 18;
    }
}

void CScore::setValue(int t, int value)
{
    m_entry[t].value = value;
}

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
    int j;
    for (i = 0; i < 5; i++) {
        HuSprAttrReset(e->grp, i, HUSPR_ATTR_DISPOFF);
    }
    for (j = 0; j <= 3; j++) {
        if (e->anim[j] < 18.0) {
            HuSprAttrReset(e->grp, j + 5, HUSPR_ATTR_DISPOFF);
            float scale = (e->anim[j] + 18.0) / 18.0; /* residue: retail loads 18.0 after the conversion (m536) */
            HuSprScaleSet(e->grp, j + 5, scale, scale);
            float tpLvl = (18.0 - e->anim[j]) / 18.0;
            HuSprTPLvlSet(e->grp, j + 5, tpLvl);
        } else {
            HuSprAttrSet(e->grp, j + 5, HUSPR_ATTR_DISPOFF);
        }
    }
}

void CScore::on_update()
{
    if (m_active) {
        for (int i = 0; i < 2; i++) {
            updateCount(&m_entry[i]);
            updateDisp(&m_entry[i]);
        }
    }
}

void CScore::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    /* every case 0..4 written: CW folds the empty ones into the bare compare chain (m579) */
    switch (mode) {
    case 0:
    case 1:
        break;
    case 2:
        m_active = true;
        break;
    case 3:
    case 4:
        break;
    }
}

CScore::~CScore() {}

} // namespace m521
