/* flow.h -- m531::CFlow (flow.cpp; name ours): the game. A CGameMaster whose seven per-frame modes run the
 * minigame: 0 setup, 1 intro wait, 2 start message, 3 play (60 s CTimer; each player cleans its side's layer),
 * 4 finish + percentage reveal, 5 results (win/lose motions, playerbase's coin bonus, confetti), 6 exit
 * (`delete this`, omOvlReturnEx). Teams come from sorting (GwPlayerConf[i].grp << 16 | i) with the 2-argument
 * std::sort. And m531::CFlowCamera (flow.cpp; name ours): the one Hu3D camera, an intro pan then an eased chase.
 *
 * CFlow GC layout (size 0x208, ObjectSetup `li r3,0x208`): CGameMaster +0x00..0x2B, m_player +0x2C (by player
 * number), m_guide +0x3C, m_stage +0x40, m_camera +0x44, m_cleanEff +0x48, m_score +0x4C, m_timer +0x50,
 * m_gridA +0x54, m_gridB +0x11C, m_frame +0x1E4, m_startMes +0x1E8, (+0x1EA unused), m_finishMes +0x1EC,
 * m_resultMes +0x1EE, m_endType +0x1F0, m_sub +0x1F4, m_winTeam +0x1F8, m_percent +0x1FC, m_bgm +0x204.
 * Vtable data_120 {~ 3264, on_setup BBCC, on_update 1790, on_close 4BF8, mode0..6 33D8..491C}; key function
 * ~CFlow (out of line in flow.cpp).
 * CFlowCamera GC layout (size 0x50): m_om +0, m_eye +4, m_up +0x10, m_target +0x1C, m_obj +0x28, m_frame +0x2C,
 * m_eyeGoal +0x30, m_targetGoal +0x3C, m_rotY +0x48, vptr +0x4C; vtable data_154 {updateIntro 2FD4,
 * updateChase 30CC} + pad. Its dtor is NOT virtual. */
#ifndef M531_FLOW_H
#define M531_FLOW_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/timer.h"
#include "REL/m531Dll/gamemaster.h"

namespace m531 {

class CPlayer;
class CRunner;
class CStageObjects;
class CCleanEffMan;
class CScore;

/* Vec copy returning the destination (component-wise lfs/stfs; the reference return is what the inlined
 * camera ctor in mode0 spills) */
inline Vec& SetVec(Vec* d, const Vec& s)
{
    d->x = s.x;
    d->y = s.y;
    d->z = s.z;
    return *d;
}

class CFlowCamera {
public:
    Process_s* m_om;   /* 0x00 */
    Vec m_eye;         /* 0x04 current */
    Vec m_up;          /* 0x10 (0,1,0) */
    Vec m_target;      /* 0x1C current */
    omObj_s* m_obj;    /* 0x28 omAddObjEx(om, 1, 0, 0, -1, IntroFunc) */
    int m_frame;       /* 0x2C */
    Vec m_eyeGoal;     /* 0x30 written by CFlow modes 4/5 */
    Vec m_targetGoal;  /* 0x3C written by CFlow modes 4/5 */
    float m_rotY;      /* 0x48 degrees (CPlayer::UpdateResult reads it) */

    static void IntroFunc(omObj_s* obj);  /* fn_1_2CA0 -> updateIntro */
    static void ChaseFunc(omObj_s* obj);  /* fn_1_2CE8 -> updateChase */
    CFlowCamera(Process_s* om);           /* fn_1_2D30 (unreferenced copy; inlined in mode0) */
    ~CFlowCamera();                       /* fn_1_2F64 (unreferenced copy; inlined in ~CFlow) */
    virtual void updateIntro();           /* fn_1_2FD4 vtable +0x08 */
    virtual void updateChase();           /* fn_1_30CC vtable +0x0C */
    void calcAngle();                     /* fn_1_31F8 m_rotY = atan2 of (eye - target) */
    float GetRotY() { return m_rotY; } /* inline (player.cpp UpdateResult, F4) */
    /* inline goal setters: ctor, updateIntro, modes 4/5 (the ctor inlined in mode0 spills their return once
     * less than SetVec's) */
    Vec& setEyeGoal(const Vec& v)
    {
        m_eyeGoal.x = v.x;
        m_eyeGoal.y = v.y;
        m_eyeGoal.z = v.z;
        return m_eyeGoal;
    }
    Vec& setTargetGoal(const Vec& v)
    {
        m_targetGoal.x = v.x;
        m_targetGoal.y = v.y;
        m_targetGoal.z = v.z;
        return m_targetGoal;
    }
};

class CFlow : public CGameMaster {
public:
    CFlow() : m_timer(0) {} /* inline: ObjectSetup; nothing else is initialised (retail) */
    virtual ~CFlow();                     /* fn_1_3264 */
    void unused();                        /* fn_1_33D4 empty, unreferenced (name ours) */
    virtual void mode0();                 /* fn_1_33D8 setup */
    virtual void mode1();                 /* fn_1_3C14 */
    virtual void mode2();                 /* fn_1_3C8C */
    virtual void mode3();                 /* fn_1_3D74 play */
    virtual void mode4();                 /* fn_1_3F60 finish + percentages */
    virtual void mode5();                 /* fn_1_41EC results */
    virtual void mode6();                 /* fn_1_491C exit (`delete this`) */
    bool checkEnd(int time);              /* fn_1_4A18 */
    float getGrid(int team, int x, int z);          /* fn_1_4B6C (player.cpp) */
    void setGrid(int team, int x, int z, float v);  /* fn_1_4BC0 (player.cpp) */
    virtual void on_close();              /* fn_1_4BF8 empty */
    CPlayer* GetPlayer(int no) const { return m_player[no]; } /* inline (player.cpp CollidePartner, F4) */
    CFlowCamera* GetCamera() const { return m_camera; }        /* inline (player.cpp UpdateResult, F4) */

    CPlayer* m_player[4];      /* 0x02C indexed by player number (key & 3), not by slot */
    CRunner* m_guide;          /* 0x03C the intro guide (player.cpp), deleted in mode 2 */
    CStageObjects* m_stage;    /* 0x040 */
    CFlowCamera* m_camera;     /* 0x044 */
    CCleanEffMan* m_cleanEff;  /* 0x048 the singleton */
    CScore* m_score;           /* 0x04C */
    CTimer m_timer;            /* 0x050 3600 frames */
    float m_gridA[10][5];      /* 0x054 team 0 [z][x] COM cell levels (player.cpp) */
    float m_gridB[10][5];      /* 0x11C team 1 */
    int m_frame;               /* 0x1E4 */
    s16 m_startMes;            /* 0x1E8 GAMEMESID */
    s16 m_unk1EA;              /* 0x1EA never accessed */
    s16 m_finishMes;           /* 0x1EC */
    s16 m_resultMes;           /* 0x1EE */
    int m_endType;             /* 0x1F0 -1, 1 early (100 % or double-100 % draw), 0 time-up */
    int m_sub;                 /* 0x1F4 sub-state of modes 4..6 */
    int m_winTeam;             /* 0x1F8 -1 draw, 0, 1 */
    float m_percent[2];        /* 0x1FC (float)(int)(100 * ratio) */
    int m_bgm;                 /* 0x204 HuAudBGMPlay(0x32) */
};

} // namespace m531

#endif
