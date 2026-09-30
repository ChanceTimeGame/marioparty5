/* scorespr.cpp -- m539::CScoreSprMan / CScoreSpr (dead code in retail: see scorespr.h).
 * Retail order: CScoreSprMan ctor, [~CSingleton<CScoreSprMan>], dtor, on_new_mode, on_update; CScoreSpr ctor,
 * [~TLinkItem<CScoreSpr>], dtor, DeleteAll, UpdateAll, Update, statePop, stateRise, execList; the list dtor
 * (FA04) BEFORE __sinit (FA5C) -- m501 aisu's placement, not m536's (open, SKELETON.md).
 * F6: every function masked 0 (raw residue: pooled literal / DestructorChain labels). */
#include "REL/m539Dll/scorespr.h"

namespace m539 {

CScoreSprList CScoreSpr::list;

CScoreSprMan::CScoreSprMan() {}

CScoreSprMan::~CScoreSprMan()
{
    CScoreSpr::DeleteAll();
}

void CScoreSprMan::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

void CScoreSprMan::on_update()
{
    CScoreSpr::UpdateAll();
}

CScoreSpr::CScoreSpr(const Vec* pos, int value, int type) : m_pos(*pos), m_value(value), m_count(0)
{
    CLinkNode::insertBack(list.asList());
    m_score = MgScoreCreate(0x960032, -1, 0);
    if (m_score == 0) {
        delete this; /* retail: the ctor then returns the freed pointer (dead code) */
        return;
    }
    m_state = type == 0 ? &CScoreSpr::statePop : &CScoreSpr::stateRise;
    MgScoreMaxDigitSet(m_score, type == 1 ? 2 : 3);
    MgScoreDispOff(m_score);
    MgScorePosSet(m_score, m_pos.x, m_pos.y);
    MgScoreScaleSet(m_score, 1.0f, 1.0f);
    MgScoreColorSet(m_score, 0xFF, 0xD8, 0x15);
}

CScoreSpr::~CScoreSpr()
{
    if (m_score) {
        MgScoreKill(m_score);
    }
}

void CScoreSpr::DeleteAll()
{
    while (!list.isEmpty()) {
        CScoreSpr* s = list.last();
        delete s;
    }
}

void CScoreSpr::UpdateAll()
{
    execList(list.asList(), Update);
}

void CScoreSpr::Update(CScoreSpr* s)
{
    (s->*s->m_state)();
}

void CScoreSpr::statePop()
{
    float t = (float)m_count / 60.0f;
    float a = 1.0f - t * t; /* computed and clamped, never used (retail) */
    if (a < 0.0f) {
        a = 0.0f;
    }
    MgScoreDispOn(m_score);
    MgScoreValueSet(m_score, m_value);
    MgScorePosSet(m_score, m_pos.x - 2.0f * t, m_pos.y - t);
    float scale = 1.0f + 2.0f * t;
    MgScoreScaleSet(m_score, scale, scale);
    m_count++;
    if ((double)m_count > 30.0) {
        m_count = 30;
    }
}

void CScoreSpr::stateRise()
{
    float t = (float)m_count / 60.0f;
    float a = 1.0f - t * t;
    if (a < 0.0f) {
        a = 0.0f;
    }
    MgScoreDispOn(m_score);
    MgScoreValueSet(m_score, m_value);
    MgScoreTPLvlSet(m_score, a);
    MgScorePosSet(m_score, m_pos.x - 2.0f * t, m_pos.y + 80.0f * t);
    float scale = 1.0f + 2.0f * t;
    MgScoreScaleSet(m_score, scale, scale);
    m_count++;
    if ((float)m_count >= 60.0f) {
        delete this;
    }
}

void CScoreSpr::execList(CLinkList* list, void (*fn)(CScoreSpr*))
{
    if (!list->isEmpty()) {
        CScoreSprList tmp;
        list->copyLink(tmp.asList());
        while (!tmp.isEmpty()) {
            CScoreSpr* s = tmp.begin();
            s->unlink();
            s->CLinkNode::insertBack(list);
            fn(s);
        }
    }
}

} // namespace m539
