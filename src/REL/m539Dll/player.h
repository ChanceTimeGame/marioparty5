/* player.h -- m539::CPlayer (player.cpp): one of the four jumpers. The intro jumps the character onto its
 * slot machine's "head" object; then A (a COM: CInputCom's 8 timed presses) jumps, and each jump's apex stops
 * the machine's next reel (CScore::stopNext). No virtuals, no vptr: CLinkNode is at offset 0 on every ABI.
 * Owned by ASet<CPlayer> (a_set.h, game_master's CObjSet); the dtor is the implicit inline one.
 * player.h does not include minigame.h (player.cpp includes it itself).
 * GC size 0x74 (game_master `li r3,0x74`). */
#ifndef M539_PLAYER_H
#define M539_PLAYER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"
#include "REL/m539Dll/a_set.h"
#include "REL/m539Dll/input.h"
#include <memory>
#include <vector>

namespace m539 {

class CScore;

/* Vec setter with DOUBLE components (m501/m536 player.h): retail stores the non-constant component with
 * `frsp; stfs` (CPlayer::update's rotation Vec, D788) */
inline Vec& SetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
    return *v;
}

class CPlayer : public TLinkItem<CPlayer> {
public:
    typedef void (CPlayer::*ProcFunc)();
    enum { NUMBEROF_MOTION = 7 };
    /* motion slots: 0 idle (loop), 1 jump, 2 unused, 3 intro peak, 4 land, 5 win, 6 lose */

    CPlayer(int idx, CScore* score);   /* fn_1_D0B4 */
    void createMotion(int dataNum);    /* fn_1_D710 m_mot_id.push_back(CharMotionCreate(charNo, dataNum)) */
    void update();                     /* fn_1_D788 PTMF (CGameMaster::on_update, every frame) */
    /* fn_1_D8A0 (unreferenced; inlined 8x): shift to slot unless current; slot 1 for charNo 2/5 starts at the
     * motion's end with blend 2 */
    void setMotion(int slot, bool once);
    void updatePhysics();              /* fn_1_D9E4 gravity, trapezoid step, floor at y = 0 */
    void setState(int state);          /* fn_1_DAF0 0 idle, 1 jump (impulse by charNo), 2 fall, 3 land, 4 end */
    void stateIdle();                  /* fn_1_DEDC A pressed -> jump */
    void stateJump();                  /* fn_1_DF6C apex: CScore::stopNext (+ rumble for humans) */
    void stateFall();                  /* fn_1_E008 */
    void stateLand();                  /* fn_1_E07C */
    void setWin();                     /* fn_1_E114 CGameMaster::setResult: win motion, voice (constant pan) */
    void setLose();                    /* fn_1_E224 CGameMaster::setResult */
    void proc_none();                  /* fn_1_E304 empty, unreferenced (no PTMF either; name ours) */
    void proc_init();                  /* fn_1_E308 start position, 120-frame wait */
    void proc_wait();                  /* fn_1_E394 the jump in from the right */
    void proc_enterJump();             /* fn_1_E554 */
    void proc_enterLand();             /* fn_1_E6C0 onto the head; waits for its velocity (m_headVel.y > 0) */
    void proc_turn();                  /* fn_1_E864 yaw 270 -> 345 */
    void proc_ready();                 /* fn_1_E940 30 frames, then CScore::appear and proc_main */
    void proc_main();                  /* fn_1_E9EC the state machine */

    /* PTMF stores go through a by-value copy (three words to a stack temp, then to m_proc) */
    void setProc(ProcFunc proc) { m_proc = proc; }
    /* stateIdle DEDC: the Data* through an inline with a named local (retail's register hops) */
    CInput::Data* getInputData()
    {
        CInput* input = m_input.get();
        return &input->m_data;
    }
    /* m_count > 0 && --m_count == 0 through an inline (proc_wait E394 / proc_ready E940: the bool return temp) */
    bool countDown()
    {
        return m_count > 0 && --m_count == 0;
    }

    /* 0x00 CLinkNode (through TLinkItem), on ASet<CPlayer> */
    std::auto_ptr<CInput> m_input;    /* 0x08 CInput::Create(idx) (polymorphic delete) */
    ProcFunc m_proc;                  /* 0x0C (12 bytes on CW) */
    int m_idx;                        /* 0x18 player 0..3 */
    int m_charNo;                     /* 0x1C GwPlayerConf[idx].charNo (used as s16) */
    float m_height;                   /* 0x20 CharModelHeightGet; never read */
    Vec m_pos;                        /* 0x24 not set by the ctor (proc_init sets it before physics runs) */
    int m_stateTime;                  /* 0x30 0 on every setState; write-only */
    int m_motion;                     /* 0x34 current m_mot_id slot */
    int m_state;                      /* 0x38 */
    std::vector<s16> m_mot_id;        /* 0x3C seven ids */
    std::auto_ptr<CModel> m_model;    /* 0x48 CModel(charNo, 3) */
    Vec m_vel;                        /* 0x4C */
    Vec m_accel;                      /* 0x58 this frame's impulse; cleared after each physics step */
    float m_yaw;                      /* 0x64 degrees: 270 at start */
    bool m_intro;                     /* 0x68 */
    int m_count;                      /* 0x6C intro countdown */
    CScore* m_score;                  /* 0x70 this player's slot machine */
};

} // namespace m539

#ifndef __MWERKS__
template <> ASet<m539::CPlayer>* ASet<m539::CPlayer>::sm_ptr; /* defined in game_master.cpp */
#endif

#endif
