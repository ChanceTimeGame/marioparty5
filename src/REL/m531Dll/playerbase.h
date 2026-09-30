/* playerbase.h -- m531::CPlayerBase (playerbase.cpp): a character (CharModelCreate) or plain model with its
 * motion table, its own omObj (prio 4, 16/16) and four per-frame states Enter -> Main -> Goal -> Result, each a
 * static trampoline calling a virtual. m531::CModelBase: the plain-model flavour (CRunner's base).
 * GC: m_om +0, m_playerNo +4, m_charNo +6, m_model +8, m_motion[32] +0xA, m_type +0x4A, m_dif +0x4C, m_pad +0x4E,
 * m_curMotion +0x50, m_done +0x54, m_arrived +0x55, m_obj +0x58, m_motTbl +0x5C, m_motNum +0x60, m_stickX +0x64,
 * m_stickY +0x68, m_startPos +0x6C, m_goalPos +0x78, m_pos +0x84, m_rot +0x90, m_scale +0x9C, m_reqMotion +0xA8,
 * m_dataNum +0xAC, vptr +0xB0; size 0xB4. Vtable data_440 {UpdateEnter C74C, UpdateMain C774, UpdateGoal C830,
 * UpdateResult C808, InputPad C83C, InputCom BA5C, Move BA60, ~ C590, Finish CA30, Start CB20}.
 * InputCom/Move are inline empties (retail kept player.o's weak copies BA5C/BA60). CModelBase's vtable (data_394)
 * and dtor (B6C4) are in player.o (the dtor is its key function); its ctor CB34 is here. */
#ifndef M531_PLAYERBASE_H
#define M531_PLAYERBASE_H

#include "REL/mgcpp/game.h"

namespace m531 {

/* one motion: flow rodata_50 (12, players) / rodata_E0 (5, the guide) */
struct MotionEntry {
    u32 dataNum;  /* 0x0 CharMotionCreate / HuDataSelHeapReadNum */
    u32 attr;     /* 0x4 shift attr */
    float shift;  /* 0x8 shift frames */
};

class CPlayerBase {
public:
    Process_s* m_om;            /* 0x00 */
    s16 m_playerNo;             /* 0x04 -1 = model */
    s16 m_charNo;               /* 0x06 -1 = model */
    s16 m_model;                /* 0x08 */
    s16 m_motion[32];           /* 0x0A motion ids (32: guess, bound = next field) */
    s16 m_type;                 /* 0x4A GwPlayerConf.type (0 = human) */
    s16 m_dif;                  /* 0x4C GwPlayerConf.dif */
    s8 m_pad;                   /* 0x4E GwPlayerConf.padNo */
    s32 m_curMotion;            /* 0x50 */
    u8 m_done;                  /* 0x54 result set */
    u8 m_arrived;               /* 0x55 goal reached (flow mode 4 waits on it) */
    omObj_s* m_obj;             /* 0x58 */
    const MotionEntry* m_motTbl; /* 0x5C */
    s32 m_motNum;               /* 0x60 */
    float m_stickX;             /* 0x64 */
    float m_stickY;             /* 0x68 never read */
    Vec m_startPos;             /* 0x6C written by flow only */
    Vec m_goalPos;              /* 0x78 outro walk target (flow) */
    Vec m_pos;                  /* 0x84 */
    Vec m_rot;                  /* 0x90 degrees */
    Vec m_scale;                /* 0x9C never applied */
    s32 m_reqMotion;            /* 0xA8 SetMotion */
    u32 m_dataNum;              /* 0xAC model ctor only */

    /* inline accessors (player.cpp, F4): retail reads these members through an inlined const accessor -- the
     * value lands in a callee-saved temp (s16: lha + extsh) before the call that takes it */
    s16 GetPlayerNo() const { return m_playerNo; }
    s16 GetCharNo() const { return m_charNo; }
    s16 GetModel() const { return m_model; }
    s16 GetType() const { return m_type; }
    s16 GetDif() const { return m_dif; }
    s8 GetPad() const { return m_pad; }
    u8 IsDone() const { return m_done; }
    Vec GetPos() const { return m_pos; }

    static void ObjEnter(omObj_s* obj);    /* fn_1_C0E8 */
    static void ObjMain(omObj_s* obj);     /* fn_1_C130 */
    static void ObjGoal(omObj_s* obj);     /* fn_1_C178 */
    static void ObjResult(omObj_s* obj);   /* fn_1_C1C0 */
    CPlayerBase(Process_s* om, const MotionEntry* tbl, int motNum, s16 playerNo, u16 camBit); /* fn_1_C208 */
    CPlayerBase(Process_s* om, const MotionEntry* tbl, int motNum, u32 dataNum, u16 camBit);  /* fn_1_C390 */
    virtual void UpdateEnter();            /* fn_1_C74C +0x08 */
    virtual void UpdateMain();             /* fn_1_C774 +0x0C */
    virtual void UpdateGoal();             /* fn_1_C830 +0x10 */
    virtual void UpdateResult();           /* fn_1_C808 +0x14 */
    virtual void InputPad();               /* fn_1_C83C +0x18 */
    virtual void InputCom() {}             /* fn_1_BA5C +0x1C (weak, player.o) */
    virtual void Move() {}                 /* fn_1_BA60 +0x20 (weak, player.o) */
    virtual ~CPlayerBase();                /* fn_1_C590 +0x24 */
    virtual void Finish();                 /* fn_1_CA30 +0x28 objFunc = ObjGoal */
    virtual void Start();                  /* fn_1_CB20 +0x2C objFunc = ObjMain */
    void Reset();                          /* fn_1_C654 */
    void SetMotion(int mot);               /* fn_1_C8D8 */
    void UpdateModel();                    /* fn_1_C8E0 */
    void ApplyMotion(int mot);             /* fn_1_C948 */
    void SetResult(int result, int motion); /* fn_1_CA44 0 win (+10 coin bonus), 1 lose, -1 draw */
};

class CModelBase : public CPlayerBase {
public:
    CModelBase(Process_s* om, const MotionEntry* tbl, int motNum, u32 dataNum); /* fn_1_CB34 camBit 1 */
    virtual void UpdateMain() {}           /* fn_1_BA64 (weak, player.o) */
    /* fn_1_B6C4: declared, and defined in player.cpp before ~CRunner (which inlines it): CModelBase's key
     * function, so its vtable (data_394) is emitted strong in player.o and NOT in playerbase.o (which only has
     * the ctor), as retail */
    virtual ~CModelBase();
};

} // namespace m531

#endif
