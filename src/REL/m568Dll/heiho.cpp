/* heiho.cpp -- m568::CHeiho. Retail order: ShadowOn, ctor, [~auto_ptr<CModel> (weak: heiho.o is the first TU in
 * link order that emits it; player / stage use the same copy)]. .data 360: "itemhook_L", "itemhook_R",
 * "ski-itemhook-h". No .rodata / .bss / .ctors.
 * F3: masked 0 throughout; the ctor's raw residue is the three pooled hook-name labels only. */
#include "REL/m568Dll/heiho.h"

namespace m568 {

void ShadowOn(s16 id)
{
    Hu3DModelShadowSet(id);
    Hu3DModelShadowDispOn(id);
}

/* retail order; CW spills every inlined id() through stack halfwords by itself (register pressure) */
CHeiho::CHeiho()
    : m_body(new CModel(0x7B0011u)), m_itemL(new CModel(0x7B0014u)), m_itemR(new CModel(0x7B0014u)),
      m_ski(new CModel(0x7B0013u))
{
    void* data = HuDataSelHeapReadNum(0x7B0012, HU_MEMNUM_OVL, HEAP_MODEL);
    HU3DMOTID mot = Hu3DJointMotion(m_body.get()->id(), data);
    Hu3DMotionShapeSet(m_body.get()->id(), mot);
    m_body.get()->setAttr(HU3D_MOTATTR_SHAPE_LOOP);
    Hu3DModelHookSet(m_body.get()->id(), (char*)"itemhook_L", m_itemL.get()->id());
    Hu3DModelHookSet(m_body.get()->id(), (char*)"itemhook_R", m_itemR.get()->id());
    Hu3DModelHookSet(m_ski.get()->id(), (char*)"ski-itemhook-h", m_body.get()->id());
    m_ski.get()->setAttr(HU3D_MOTATTR_LOOP);
    ShadowOn(m_body.get()->id());
    ShadowOn(m_itemL.get()->id());
    ShadowOn(m_itemR.get()->id());
    ShadowOn(m_ski.get()->id());
}

} // namespace m568
