#include "REL/m511Dll/config.h"
#include "REL/m511Dll/boat.h"
#include "REL/m511Dll/stage.h"
#include "REL/m511Dll/water.h"

namespace m511 {

TLinkList<CBoat> CBoat::s_list;

/* lbl_1_rodata_10: the four hull models */
static const u32 s_boatModel[4] = { 0x45000D, 0x45000E, 0x45000F, 0x450010 };

CBoatMan::CBoatMan()
{
    for (int i = 0; i < 4; i++) {
        new CBoat(s_boatModel[i], i);
    }
}

CBoatMan::~CBoatMan()
{
    CBoat::DeleteAll();
}

void CBoatMan::on_update()
{
    CBoat::UpdateAll();
}

void CBoatMan::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    switch (mode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        break;
    }
}

CBoat::CBoat(u32 dataNum, int no) : m_model(dataNum)
{
    m_no = no;
    m_time = 0;
    insertBack(&s_list);
    HU3DMODELID id = m_model.id();
    Hu3DModelScaleSet(id, 1.0f, 1.0f, 1.0f);
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(id, HU3D_ATTR_NOCULL);
    Hu3DModelLayerSet(id, 3);
    Hu3DModelCameraSet(id, 0xF);
    Hu3DMotionTimeSet(id, 0.0f);
    m_rot.x = 0.0f;
    m_rot.y = 0.0f;
    m_rot.z = 0.0f;
    Update();
}

void CBoat::SetPos(int no, Vec* pos, float rotX, float rotY)
{
    bool found = false; /* dead (retail's stb 0 to the stack) */
    CBoat* p = s_list.begin();
    CLinkNode* end = s_list.end();
    for (; p != end; p = p->next()) {
        if (p->m_no == no) {
            p->m_pos = *pos;
            p->m_rot.x = rotX;
            p->m_rot.y = rotY;
            break;
        }
    }
}

void CBoat::DeleteAll()
{
    while (!s_list.isEmpty()) {
        CBoat* p = s_list.last();
        delete p;
    }
}

void CBoat::UpdateAll()
{
    TLinkList<CBoat>::exec(&s_list, UpdateOne);
}

void CBoat::UpdateOne(CBoat* p)
{
    p->Update();
}

void CBoat::Update()
{
    m_model.setRot(&m_rot);
    m_model.setPos(&m_pos);
    m_time++;
}

} // namespace m511

/* The weak template statics the linker kept in boat.o (the first TU to include their headers), .bss 14/18/1C */
template <> m511::CBoatMan* CSingleton<m511::CBoatMan>::ms_pointer = 0;
template <> m511::CStage* CSingleton<m511::CStage>::ms_pointer = 0;
template <> m511::CWater* CSingleton<m511::CWater>::ms_pointer = 0;
