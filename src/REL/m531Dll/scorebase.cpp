/* scorebase.cpp -- CScoreBase (scorebase.h). Every function written whole (skeleton). */
#include "REL/m531Dll/scorebase.h"

namespace m531 {

void CScoreBase::ObjUpdate(omObj_s* obj)
{
    CScoreBase* self = (CScoreBase*)obj->data;
    self->on_update();
}

void CScoreBase::on_update() {}

CScoreBase::CScoreBase(Process_s* om)
{
    m_om = om;
    m_obj = omAddObjEx(om, 7, 0, 0, -1, ObjUpdate);
    m_obj->data = this;
}

CScoreBase::~CScoreBase()
{
    m_obj->data = 0;
    omDelObjEx(m_om, m_obj);
}

} // namespace m531
