/* om.cpp -- CMinigameCore's class operator new/delete, COMObj. Retail order; the sphere helpers are sphere.cpp.
 * The two asserts must stay on om.cpp lines 24 and 31 (retail .data). */
#include "REL/mgcpp/om.h"
#include "REL/mgcpp/minigame.h"
#include "REL/mgcpp/assert.h"

/* CMinigameCore lives in the overlay heap tag (freed in bulk with the overlay), like global new */













void* CMinigameCore::operator new(size_t size)
{
    void* ptr = HuMemDirectMallocNum(HEAP_HEAP, size, HU_MEMNUM_OVL);
    assert(ptr != NULL);
    return ptr;
}

void* CMinigameCore::operator new[](size_t size)
{
    void* ptr = HuMemDirectMallocNum(HEAP_HEAP, size, HU_MEMNUM_OVL);
    assert(ptr != NULL);
    return ptr;
}

void CMinigameCore::operator delete(void* p)
{
    if (p) {
        HuMemDirectFree(p);
    }
}

void CMinigameCore::operator delete[](void* p)
{
    if (p) {
        HuMemDirectFree(p);
    }
}

/* attach: obj->data = this, and the object's update calls on_update */
COMObj::COMObj(omObj_s* obj)
{
    obj->data = this;
    obj->objFunc = OmObjUpdate;
}

void COMObj::OmObjUpdate(omObj_s* obj)
{
    COMObj* self = (COMObj*)obj->data;
    self->on_update(obj);
}

void COMObj::on_update(omObj_s* obj) {}

/* RETAIL BUG (unreferenced in m501): omDelObjEx frees obj->data again (objmain.c), after `delete` has
 * already freed it, because obj->data is not cleared here. */
void COMObj::OmObjDelete(omObj_s* obj)
{
    COMObj* self = (COMObj*)obj->data;
    delete self;
    omDelObjEx(HuPrcCurrentGet(), obj);
}

COMObj::~COMObj() {}

void COMObj::OmObjDelete(Process_s* objman, omObj_s* obj)
{
    COMObj* self = (COMObj*)obj->data;
    delete self;
    omDelObjEx(objman, obj);
}
