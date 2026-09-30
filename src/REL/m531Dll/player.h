/* player.h -- m531::CPlayer (player.cpp): a player on its team's half: drops in, walks in circles steered by
 * main stick X (COM: picks the dirtiest grid cell), carries a brush model and a CSparkle, pushes its teammate
 * apart; flow drives Start/Finish/SetResult. m531::CRunner (name ours): the intro guide that runs across with its
 * two CGuruguru. Both hold the owning CFlow; five member functions cache it in guarded function-local statics
 * (`static CFlow* s_flow = m_flow;`, bss 34..58: retail hazard on a second play if the REL stays loaded).
 * CPlayer GC: CPlayerBase +0 (vptr +0xB0), m_turnVel +0xB4, m_flow +0xB8, m_floor +0xBC, m_sparkle +0xC0,
 *   m_brush +0xC4, m_brushPos +0xC8, m_enterTime +0xD4, m_landed +0xD8, m_fallVel +0xDC, m_team +0xE0,
 *   m_turnTarget +0xE4, m_hitCount +0xE8, m_bumped +0xEC, m_comThreshold +0xF0, m_slot +0xF4, m_comReverse +0xF8,
 *   m_seNo +0xFC, m_comFrame +0x100, m_turnDir +0x104, m_comCell +0x108, m_comTurnFrames +0x114,
 *   m_comCellLevel +0x118, m_comCellCenter +0x11C, m_brushOfs +0x128; size 0x134 (flow `li r3,0x134`).
 *   Vtable data_3C4 {964C, 97E4, 9878, 9BF4, 9EF4, 9F1C, AA98, ~ 948C, 9E54, 9CC4} + pad.
 * CRunner GC: CModelBase +0, m_time +0xB4, m_child +0xB8, m_jumpVel +0xC0, m_jumped +0xC4; size 0xC8.
 *   Vtable data_364 {C74C, UpdateMain B7F4, C830, C808, C83C, BA5C, BA60, ~ B728, CA30, CB20}. */
#ifndef M531_PLAYER_H
#define M531_PLAYER_H

#include "REL/m531Dll/playerbase.h"

namespace m531 {

class CFlow;
class CCleanEff;
class CSparkle;
class CGuruguru;

float LerpAngle(float from, float to, float t); /* fn_1_90CC no caller (inlined into UpdateGoal) */
float AngleDiff(float from, float to);          /* fn_1_91D0 no caller (inlined into ComSteer) */

class CPlayer : public CPlayerBase {
public:
    float m_turnVel;         /* 0x0B4 */
    CFlow* m_flow;           /* 0x0B8 */
    CCleanEff* m_floor;      /* 0x0BC this team's layer */
    CSparkle* m_sparkle;     /* 0x0C0 */
    s16 m_brush;             /* 0x0C4 brush model on item hook 2 */
    Vec m_brushPos;          /* 0x0C8 where flow cleans */
    float m_enterTime;       /* 0x0D4 */
    u8 m_landed;             /* 0x0D8 */
    float m_fallVel;         /* 0x0DC */
    s32 m_team;              /* 0x0E0 slot >> 1 */
    float m_turnTarget;      /* 0x0E4 +-2 deg/frame */
    s32 m_hitCount;          /* 0x0E8 */
    u8 m_bumped;             /* 0x0EC */
    float m_comThreshold;    /* 0x0F0 0.9, +0.05 */
    s32 m_slot;              /* 0x0F4 sorted slot (flow reads it) */
    u8 m_comReverse;         /* 0x0F8 */
    s32 m_seNo;              /* 0x0FC looping spin SE handle */
    s32 m_comFrame;          /* 0x100 */
    s32 m_turnDir;           /* 0x104 +-1 */
    Vec m_comCell;           /* 0x108 x, z = cell (floats of ints); y never written */
    s32 m_comTurnFrames;     /* 0x114 */
    float m_comCellLevel;    /* 0x118 */
    Vec m_comCellCenter;     /* 0x11C */
    Vec m_brushOfs;          /* 0x128 */

    CPlayer(CFlow* flow, CCleanEff* floor, const MotionEntry* tbl, int motNum, s16 playerNo, int slot); /* 9270 */
    virtual ~CPlayer();                  /* fn_1_948C */
    void CreateBrush();                  /* fn_1_9520 */
    void CreateDust();                   /* fn_1_95DC no caller (inlined into Finish) */
    virtual void UpdateEnter();          /* fn_1_964C */
    virtual void UpdateMain();           /* fn_1_97E4 */
    virtual void UpdateGoal();           /* fn_1_9878 */
    virtual void UpdateResult();         /* fn_1_9BF4 */
    virtual void Start();                /* fn_1_9CC4 */
    virtual void Finish();               /* fn_1_9E54 */
    virtual void InputPad();             /* fn_1_9EF4 */
    virtual void InputCom();             /* fn_1_9F1C */
    void ComSelectTarget();              /* fn_1_9FFC */
    void ComSelectTargetExcept(int x, int z); /* fn_1_A2C8 */
    float ComGetCellLevel();             /* fn_1_A568 */
    void ComSteer(int dif);              /* fn_1_A714 */
    virtual void Move();                 /* fn_1_AA98 */
    void ClampToFloor();                 /* fn_1_ACF8 */
    void CollidePartner();               /* fn_1_B0BC */
    int GetSlot() const { return m_slot; }          /* inline (CollidePartner) */
    Vec GetBrushPos() const { return m_brushPos; }  /* inline (CollidePartner) */
};

class CRunner : public CModelBase {
public:
    s32 m_time;              /* 0xB4 */
    CGuruguru* m_child[2];   /* 0xB8 */
    float m_jumpVel;         /* 0xC0 20.0 */
    u8 m_jumped;             /* 0xC4 */

    CRunner(Process_s* om, const MotionEntry* tbl, int motNum, u32 dataNum); /* fn_1_B55C */
    virtual ~CRunner();                  /* fn_1_B728 */
    virtual void UpdateMain();           /* fn_1_B7F4 */
};

} // namespace m531

#endif
