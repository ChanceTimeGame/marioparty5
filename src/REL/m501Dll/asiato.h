/* asiato.h -- m501::CAsiato (asiato.cpp): a footprint decal that fades out, and CAsiatoMan, the static
 * manager that owns their list and draw hook. CAsiato GC size 0x1C, no virtuals. */
#ifndef M501_ASIATO_H
#define M501_ASIATO_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/link.h"

namespace m501 {

/* drawHook's stack record. GC size 0x34 (note: field order differs from CAisuDrawData). */
class CAsiatoDrawData {
public:
    Mtx m_mtx;           /* 0x00 */
    HU3DMODELID m_model; /* 0x30 = CParticle::getInstance()->m_id */
};

/* retail symbols spell this class "7CAsiatoMan" (a length typo in symbols.txt; map.asiato.txt) */
class CAsiatoMan {
public:
    static void init();
    static void update();
    static void close();
};

class CAsiato : public CLinkItem {
public:
    CAsiato(Vec* pos, float rot);
    /* implicit dtor (inlined into close/update); the out-of-line copy after the ctor is ~CLinkItem */
    static void update(CAsiato* asiato);
    static void drawHook(Hu3DModel_s* model, Mtx* mtx);
    /* retail symbol drawAsiato__...FPQ24m5017CAsiatoPQ24m50115CAsiatoDrawData, but r3 is the draw data and
     * r4 the footprint (map.asiato.txt) */
    static void drawAsiato(CAsiatoDrawData* data, CAsiato* asiato);
    static void execAsiatoList(CLinkList* list, void (*func)(CAsiato*));
    static void drawAsiatoList(CLinkList* list, CAsiatoDrawData* data);
    /* retail symbol has two parameters (FPQ24m5017CAsiatoPQ24m50115CAsiatoDrawData); the body takes
     * begin, end, data in r3/r4/r5 (map.asiato.txt) */
    static void drawAsiatoList(CAsiato* begin, CAsiato* end, CAsiatoDrawData* data);
    static void execAsiatoList(CAsiato* begin, CAsiato* end, void (*func)(CAsiato*));

    /* 0x00 CLinkNode */
    Vec m_pos;   /* 0x08 (x/z used) */
    float m_rot; /* 0x14 yaw, degrees */
    int m_life;  /* 0x18 frames left */
};

} // namespace m501

#endif
