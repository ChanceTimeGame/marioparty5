/* aisu.h -- m501::CAisu (aisu.cpp): an ice-cream scoop. It falls (on aisuAllList), lands and melts
 * (aisuFallList), or is caught and stacked on a cone (aisuConeList); one CLinkNode, one list at a time.
 * Its state is a PTMF. Handles into CGameMaster's CHandleMan identify scoops to the players.
 * GC size 0xC8. No virtuals. */
#ifndef M501_AISU_H
#define M501_AISU_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/link.h"
#include "REL/mgcpp/handle.h"
#include "REL/m501Dll/joint.h"
#include <vector>

namespace m501 {

/* drawHook's stack record for drawAisu/drawAisuList. GC size 0x34. */
class CAisuDrawData {
public:
    HU3DMODELID m_model; /* 0x00 = *CGameMaster::GetAisuModel() */
    Mtx m_mtx;           /* 0x04 the hook's matrix */
};

class CAisu : public CLinkItem {
public:
    typedef void (CAisu::*StateFunc)();
    /* by value: retail copies each PTMF constant to a stack temporary before storing it */
    void setState(StateFunc state) { m_state = state; }

    static void init(CHandleMan* handleMan);
    static CAisu* getHandle(int handle);
    static void Close();
    CAisu(int type, Vec* pos);
    ~CAisu();
    static void UpdateAll();
    static void AisuUpdate(CAisu* aisu);
    void setObjName(int suffix);
    void stateStart();  /* fn_1_7988 */
    void stateFall();   /* fn_1_79FC */
    void stateMelt();   /* fn_1_7BF0 */
    void playSound(int seNo);
    void stateSink();   /* fn_1_7D94 */
    void stateTaken();  /* fn_1_7E3C */
    static void drawHook(Hu3DModel_s* model, Mtx* mtx);
    /* retail symbol drawAisu__...FPQ24m5015CAisuPQ24m50113CAisuDrawData, but r3 is the draw data and r4
     * the scoop (map.aisu.txt) */
    static void drawAisu(CAisuDrawData* data, CAisu* aisu);
    CJoint* doTake(CJoint* super, int n);
    static void GetHandleList(std::vector<int>& list);
    static bool checkSlowMove(Vec* pos);
    static CAisu* checkTake(Vec* pos, float r);
    u8 isTaken();     /* fn_1_8500 */
    static void GetAisuDist(std::vector<HuVec2f_s>* list); /* fn_1_8510 (pointer, like CPlayer::GetPlayerDist; the ABI cannot tell) */
    void setPos(Vec* pos, float t);
    static void drawAisuList(CLinkList* list, CAisuDrawData* data);
    static void drawAisuList(CAisu* begin, CAisu* end, CAisuDrawData* data);
    static void execAisuList(CLinkList* list, void (*func)(CAisu*));

    static CLinkList aisuConeList;
    static CLinkList aisuAllList;
    static CLinkList aisuFallList;
    static CHandleMan* aisuHandleMan;

    /* 0x00 CLinkNode */
    StateFunc m_state;   /* 0x08 (12 bytes on CW) */
    int m_type;          /* 0x14 flavour 0..7 */
    bool m_kage : 1;     /* 0x18 bit7 (CW MSB-first): shadow visible */
    bool m_taken : 1;    /* 0x18 bit6: on a cone (bool: isTaken returns it without a 0/1 normalisation) */
    float m_scale;       /* 0x1C */
    float m_kageScale;   /* 0x20 */
    Vec m_pos;           /* 0x24 read by CPlayer */
    Vec m_vel;           /* 0x30 */
    char m_objName[16];  /* 0x3C "%s%s" flavour + suffix */
    int m_seNo;          /* 0x4C HuAudFXPlay handle */
    CJoint m_joint;      /* 0x50 */
    int m_handle;        /* 0xC4 CHandleMan handle, read by CPlayer */
};

} // namespace m501

#endif
