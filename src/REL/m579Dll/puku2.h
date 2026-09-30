/* puku2.h -- m579::CPuku (puku2.cpp): the ten Cheep Cheeps (5 small of kind 0, 5 big of kind 1, created by the zako
 * manager with a Hu3DModelLink of its master models). Hidden at y = -500 until a fishing line's pull claims one
 * (Catch, fishline HookFish); follows the line; on release (Launch, fishline ReleaseFish) jumps out with 1.5 g,
 * bounces on the pier, splashes at the surface (y = -150) and hides again below y = -700. Names ours.
 * GC (sheet player_puku2_fishman.md §2.3; size 0x64, zako 15EA0 / 15EDC `li r3,0x64`): TLinkItem (CLinkNode) +0 on
 * s_list, m_proc +0x08 (12-byte PTMF), m_motion +0x14, m_unk18 +0x18 (write-only), m_pos +0x1C, m_prevPos +0x28,
 * m_vel +0x34 (not set by the ctor), m_frame +0x40, m_unk44 +0x44 (never accessed), m_model +0x48 (a MEMBER: ~CModel
 * with flag -1), m_escape +0x4A (not set by the ctor), m_caught +0x4B, m_kind +0x4C, m_line +0x50 (write-only),
 * m_rot +0x54 (degrees), m_above +0x60. No vptr; the implicit dtor is inlined in DeleteAll.
 * Motions: CSingleton<CZakoMan>::GetInstance()->m_mot_id (zako.h). puku2.cpp does not include minigame.h. */
#ifndef M579_PUKU2_H
#define M579_PUKU2_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"

namespace m579 {

class CFishLine;

class CPuku : public TLinkItem<CPuku> {
public:
    typedef void (CPuku::*ProcFunc)();

    CPuku(CModel& src, int kind);                    /* fn_1_6074 */
    static CPuku* Catch(CFishLine* line, int kind);  /* fn_1_62B4 first free one of that kind (fishline HookFish) */
    static void DeleteAll();                         /* fn_1_6388 (= m512 zako EF9C / m536 E8D4) */
    static void UpdateAll();                         /* fn_1_645C exec(Update), rotate (= m512 zako F070) */
    static void Update(CPuku* p);                    /* fn_1_64E0 */
    void checkSurface();                             /* fn_1_6534 new CSplash on a surface crossing */
    void updateModel();                              /* fn_1_660C */
    void setMotion(int no, bool once);               /* fn_1_682C unreferenced (inlined) */
    void procHide();                                 /* fn_1_692C */
    void procCaught();                               /* fn_1_6990 */
    void procJump();
    void Launch(bool escape);
    /* by value: retail copies the PTMF constant to a stack temporary before storing it */
    void setProc(ProcFunc proc) { m_proc = proc; }

    static TLinkList<CPuku> s_list; /* bss 9FC; its DestructorChain 9F0 */

    /* 0x00 CLinkNode (TLinkItem) */
    ProcFunc m_proc;    /* 0x08 (12 bytes on CW) */
    int m_motion;       /* 0x14 -1 */
    int m_unk18;        /* 0x18 0, write-only */
    Vec m_pos;          /* 0x1C */
    Vec m_prevPos;      /* 0x28 */
    Vec m_vel;          /* 0x34 set by Launch */
    int m_frame;        /* 0x40 ++, never read */
    int m_unk44;        /* 0x44 never accessed */
    CModel m_model;     /* 0x48 Hu3DModelLink of the zako manager's master */
    bool m_escape;      /* 0x4A Launch argument */
    bool m_caught;      /* 0x4B */
    int m_kind;         /* 0x4C 0 small, 1 big */
    CFishLine* m_line;  /* 0x50 Catch argument (write-only) */
    Vec m_rot;          /* 0x54 degrees */
    bool m_above;       /* 0x60 above the surface */
};

} // namespace m579

#endif
