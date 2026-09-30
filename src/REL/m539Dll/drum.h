#ifndef M539_DRUM_H
#define M539_DRUM_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/tlink.h"
#include <map>
#include <memory>

namespace m539 {

class CDrum;

/* GC: std::map<u32, CModel*> at +0 (empty CSingleton base also at +0, the ctor stores `this` unadjusted);
 * size 0xC (game_master `li r3,0xC`). No vptr. Created by CGameMaster(), deleted by ~CGameMaster (straight
 * from ms_pointer, no assert). ms_pointer = drum .bss 9F0 (drum.o is the first TU to instantiate it). */
class CModelMan : public CSingleton<CModelMan> {
public:
    typedef std::map<u32, CModel*> ModelMap;

    CModelMan();                    /* fn_1_6ED0 */
    ~CModelMan();                   /* fn_1_70E0 frees the nodes only: the cached CModels are owned elsewhere */
    CModel* create(u32 num);
    static CModel* Create(u32 num); /* fn_1_72E8 GetInstance()->create(num) */

    ModelMap m_map; /* 0x0 */
};

#ifndef M539_DRUM_INCOMPLETE

/* GC: TLinkItem<CDrum> (CLinkNode, never inserted) +0, m_angle +8 (degrees), m_speed +0xC (not set by the
 * ctor), m_state +0x10 (0 idle, 1 spinning, 2 stop requested, 3 stopped), 16 unused bytes +0x14, m_body +0x24,
 * m_stop +0x28, m_hit +0x2C, m_press +0x30; size 0x34 (score `li r3,0x34`). No vptr. */
class CDrum : public TLinkItem<CDrum> {
public:
    /* fn_1_6704: the three models at the translation of `obj` on `base`, camera bit 1 << cam */
    CDrum(CModel* base, char* obj, int cam);
    void Update();        /* fn_1_6A24 spin; the press rebound; the body's X rotation from m_angle */
    void Start();         /* fn_1_6B44 speed 48, state 1 */
    void Stop();          /* fn_1_6B60 state 2, snap to a random face, PlayHit */
    void Press();         /* fn_1_6BEC press motion, m_press = 3 */
    void PlayHit();       /* fn_1_6C64 */
    void RemoveBody();    /* fn_1_6D54 m_body.reset(): the centre reel (always wild) */
    bool IsStopped();     /* fn_1_6DA0 state >= 2 (unreferenced; inlined into GetSymbol) */
    int GetSymbol();      /* fn_1_6DBC 3 = no body (wild), 4 = spinning, else the face 0..2 */

    float m_angle;                 /* 0x08 */
    float m_speed;                 /* 0x0C */
    int m_state;                   /* 0x10 */
    u8 m_unk14[0x10];              /* 0x14 never read or written in the REL (sheet §9 Q1) */
    std::auto_ptr<CModel> m_body;  /* 0x24 0x610005 the reel */
    std::auto_ptr<CModel> m_stop;  /* 0x28 0x610006 stop motion */
    std::auto_ptr<CModel> m_hit;   /* 0x2C 0x610007 win motion */
    int m_press;                   /* 0x30 press countdown */
};

/* GC: +0 never touched, m_total +4; a stack object in CScore::checkLine */
class CSlotJudge {
public:
    CSlotJudge();                   /* fn_1_6E3C m_total = 0 */
    /* fn_1_6E48: pays when a == c and (b == a or b is the wild 3): symbol 0 -> 5, 1 -> 10, 2 -> 50; adds to
     * m_total and returns the payout (0 = no line) */
    int Judge(int a, int b, int c);
    int GetTotal() { return m_total; }

    int m_unk00; /* 0x0 */
    int m_total; /* 0x4 */
};

#endif /* M539_DRUM_INCOMPLETE */

} // namespace m539

#ifndef __MWERKS__
template <> m539::CModelMan* CSingleton<m539::CModelMan>::ms_pointer; /* defined in drum.cpp */
#endif

#endif
