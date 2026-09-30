/* scorebase.h -- m531::CScoreBase (scorebase.cpp): an omObj (prio 7) whose ObjUpdate forwards to the virtual
 * on_update. Base of CScore (score.cpp). GC: m_om +0, m_obj +4, vptr +8; size 0xC;
 * vtable data_110 {on_update 2BB8, ~ 2C30}. */
#ifndef M531_SCOREBASE_H
#define M531_SCOREBASE_H

#include "REL/mgcpp/game.h"

namespace m531 {

class CScoreBase {
public:
    Process_s* m_om; /* 0x0 */
    omObj_s* m_obj;  /* 0x4 omAddObjEx(om, 7, 0, 0, -1, ObjUpdate); obj->data = this */

    static void ObjUpdate(omObj_s* obj); /* fn_1_2B70 */
    virtual void on_update();            /* fn_1_2BB8 empty (vtable +0x08) */
    CScoreBase(Process_s* om);           /* fn_1_2BBC */
    virtual ~CScoreBase();               /* fn_1_2C30 (vtable +0x0C) */
};

} // namespace m531

#endif
