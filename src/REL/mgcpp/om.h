/* om.h -- COMObj (om.cpp): a C++ object attached to an omObj (obj->data = this, objFunc = OmObjUpdate),
 * and the two sphere helpers (defined in sphere.cpp). GC: COMObj vptr +0, size 4. */
#ifndef MGCPP_OM_H
#define MGCPP_OM_H

#include "REL/mgcpp/game.h"

class COMObj {
public:
    /* vtable order: ~COMObj, on_update */
    virtual ~COMObj();
    virtual void on_update(omObj_s* obj);

    COMObj(omObj_s* obj);
    static void OmObjUpdate(omObj_s* obj);
    static void OmObjDelete(omObj_s* obj);
    static void OmObjDelete(Process_s* objman, omObj_s* obj);
};

/* {pos, radius}: CPlayer keeps one at +0x48 */
struct CSphere {
    /* m521 player Clamp builds one as `CSphere pivot(center, r)`: retail copies the Vec word by word through this
     * ctor (m568 CObstacle's masked residue is the same missing ctor). */
    CSphere() {}
    CSphere(const Vec& p, float rr) : pos(p), r(rr) {}
    /* retail reads the radius through an inline accessor (it puts each load in its own register) */
    float radius() { return r; }

    Vec pos;  /* 0x0 */
    float r;  /* 0xC */
};

/* fn_1_4F0C: |a.pos - b.pos| < a.r + b.r. Unreferenced. */
bool HitCheckSphere(CSphere* a, CSphere* b);
/* fn_1_4FB4: if overlapping, push a and b apart (a gets -ratio, b 1-ratio of k * overlap). External:
 * player.cpp calls it. */
bool HitPushSphere(CSphere* a, CSphere* b, float ratio, float k);

#endif
