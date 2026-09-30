#ifndef M531_STAGE_H
#define M531_STAGE_H

#include "REL/mgcpp/game.h"

namespace m531 {

class CStage {
public:
    Process_s* m_om; /* 0x00 */
    s16 m_model;     /* 0x04 */
    omObj_s* m_obj;  /* 0x08 omAddObjEx(om, prio, 16, 16, -1, ObjUpdate); obj->data = this */
    Vec m_pos;       /* 0x0C */
    Vec m_rot;       /* 0x18 degrees */
    Vec m_scale;     /* 0x24 */

    static void ObjUpdate(omObj_s* obj);  /* fn_1_BEAC */
    virtual void on_update() {}           /* fn_1_90C8 (weak, kept from object.o) */
    CStage(Process_s* om, u32 dataNum, s16 layer, s16 prio, u16 camBit); /* fn_1_BEF4 */
    virtual ~CStage();                    /* fn_1_C038 */
    void setShadow();                     /* fn_1_C0B0 */
    s16 GetModel() const { return m_model; } /* inline only: CW -O0 extsh's the returned s16 into a temp */
};

} // namespace m531

#endif
