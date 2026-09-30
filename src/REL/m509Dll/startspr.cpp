/* startspr.cpp -- m509::CStartSpr: the pre-game player-start panel (character icon + slot frame per player).
 * SKELETON: drafted whole from the W0 sheet (player_random_startspr.md §B); the fork verifies it.
 * Retail order: ctor, (the weak ~CSingleton<CStartSpr> copy), dtor, on_update, on_new_mode. */
#include "REL/m509Dll/startspr.h"

namespace m509 {

/* lbl_1_data_3308: the slot-frame sprites by player; lbl_1_data_3318: the character icons by charNo (13 and
 * 14 repeat index 10's, as m536's s_charIcon). Writable .data, before the singleton strings. */
static s32 s_slotData[4] = { 0x430006, 0x430007, 0x430008, 0x430009 };
static s32 s_charData[15] = {
    0x43000A, 0x43000B, 0x43000C, 0x43000D, 0x43000E, 0x43000F, 0x430010, 0x430011,
    0x430012, 0x430013, 0x430014, 0x430015, 0x430016, 0x430014, 0x430014,
};

/* lbl_1_rodata_230: the panel positions (screen quadrants) */
static const float s_pos[4][2] = { { 118.0f, 126.0f }, { 460.0f, 126.0f }, { 118.0f, 384.0f }, { 460.0f, 384.0f } };

/* charNo: the four players' characters (CPlayer::CreateStartSpr; retail: 0..14, sheet E.8) */
CStartSpr::CStartSpr(int* charNo)
{
    m_fadeOut = false;
    m_timer = 0;
    m_alpha = 0.0f;
    ANIMDATA* slotAnim[4];
    ANIMDATA* charAnim[4];
    for (int i = 0; i < 4; i++) {
        slotAnim[i] = HuSprAnimRead(HuDataSelHeapReadNum(s_slotData[i], HU_MEMNUM_OVL, HEAP_MODEL));
        charAnim[i] = HuSprAnimRead(HuDataSelHeapReadNum(s_charData[charNo[i]], HU_MEMNUM_OVL, HEAP_MODEL));
    }
    for (int i = 0; i < 4; i++) {
        Entry* e = &m_entry[i];
        e->x = s_pos[i][0];
        e->y = s_pos[i][1];
        int k;
        HUSPRGRPID grp = HuSprGrpCreate(2);
        e->grp = grp;
        HuSprGrpMemberSet(grp, 0, HuSprCreate(charAnim[i], 200, 0));
        HuSprGrpMemberSet(grp, 1, HuSprCreate(slotAnim[i], 100, 0));
        HuSprGrpPosSet(e->grp, e->x, e->y);
        for (k = 0; k < 2; k++) {
            HuSprAttrSet(grp, k, HUSPR_ATTR_NOANIM);
            HuSprAttrSet(grp, k, HUSPR_ATTR_DISPOFF);
        }
    }
}

/* the anims are not killed (retail) */
CStartSpr::~CStartSpr()
{
    for (int i = 0; i < 4; i++) {
        Entry* e = &m_entry[i];
        HuSprGrpKill(e->grp);
    }
}

/* hidden for 60 frames; fades in at 1/30 per frame; after mode 1/2 fades out and deletes itself */
void CStartSpr::on_update()
{
    m_timer++;
    if ((float)m_timer < 60.0f) {
        return;
    }
    if (!m_fadeOut) {
        m_alpha += 0.033333335f;
        if (m_alpha > 1.0) {
            m_alpha = 1.0f;
        }
    } else {
        m_alpha -= 0.033333335f;
        if (m_alpha < 0.0f) {
            delete this;
            return;
        }
    }
    for (int i = 0; i < 4; i++) {
        Entry* e = &m_entry[i];
        for (int k = 0; k < 2; k++) {
            HuSprTPLvlSet(e->grp, k, m_alpha);
            HuSprAttrReset(e->grp, k, HUSPR_ATTR_DISPOFF);
        }
    }
}

void CStartSpr::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    switch (mode) {
    case 0:
        break;
    case 1:
        m_fadeOut = true;
        break;
    case 2:
        m_fadeOut = true;
        break;
    case 5:
        break;
    }
}

} // namespace m509

/* bss_50: the singleton pointer, in startspr's own .bss (the only TU that instantiates it) */
template <> m509::CStartSpr* CSingleton<m509::CStartSpr>::ms_pointer = 0;
