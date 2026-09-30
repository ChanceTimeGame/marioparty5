#include "REL/m522Dll/sunfire.h"
extern "C" {
void HuSprTexLoad(ANIMDATA* anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);
}

namespace m522 {

TLinkList<CSunFireObj> CSunFireObj::s_list;
CHandleMan* CSunFireObj::s_handleMan;

/* lbl_1_rodata_420: the two sprite sheets (fire01 tiles, prominence tiles) */
static const u32 s_animNum[2] = { 0x500005, 0x500006 };

/* fn_1_DEA0 (72 insns): m532 E54C plus the anim loop (sheet §5.2) */
CSunFireMan::CSunFireMan(CHandleMan* handleMan) : m_handleMan(handleMan)
{
    for (int i = 0; i < 2; i++) {
        m_anim[i] = HuSprAnimRead(HuDataSelHeapReadNum(s_animNum[i], HU_MEMNUM_OVL, HEAP_MODEL));
    }
    CSunFireObj::s_handleMan = m_handleMan;
}

CSunFireMan::~CSunFireMan()
{
    CSunFireObj::DeleteAll();
}

/* fn_1_E11C (46 insns): all five arguments spilled; the singleton through the :39 assert */
void CSunFireMan::LoadTex(int anim, int texMap, GXTexWrapMode s, GXTexWrapMode t, GXTexFilter f)
{
    CSunFireMan* m = GetInstance();
    HuSprTexLoad(m->m_anim[anim], 0, texMap, s, t, f);
}

/* the bit is cleared first, then a compare tree with EMPTY cases 0 and 5; mode 3 finishes every object and
 * clears the bit again (m532 E794 exactly) */
void CSunFireMan::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    switch (mode) {
    case 0:
        break;
    case 3:
        CSunFireObj::FinishAll();
        m_execFlags &= ~(1 << mode);
        break;
    case 5:
        break;
    }
}

void CSunFireMan::on_update()
{
    CSunFireObj::UpdateAll();
}

void CSunFireObj::UpdateAll()
{
    execList(s_list.asList(), Update);
}

void CSunFireObj::Update(CSunFireObj* o)
{
    o->update();
}

void CSunFireObj::update() {}

void CSunFireObj::HookFunc(HU3DMODEL* model, Mtx* mtx)
{
    ((CSunFireObj*)model->hookData)->draw(mtx);
}

void CSunFireObj::draw(Mtx* mtx) {}

void CSunFireObj::FinishAll()
{
    TLinkList<CSunFireObj>::exec(&s_list, Finish);
}

void CSunFireObj::Finish(CSunFireObj* o)
{
    o->onFinish();
}

void CSunFireObj::DeleteAll()
{
    while (!s_list.isEmpty()) {
        delete s_list.last();
    }
}

CSunFireObj::CSunFireObj() : CModel(HookFunc)
{
    m_handle = s_handleMan->insertHandle(this);
    insertBack(&s_list);
    setHookData(this);
}

CSunFireObj::~CSunFireObj()
{
    s_handleMan->removeHandle(m_handle);
}

int CSunFireObj::GetHandle()
{
    return m_handle;
}

CSunFireObj* CSunFireObj::GetHandlePtr(int handle)
{
    return (CSunFireObj*)s_handleMan->getHandlePtr(handle);
}

void CSunFireObj::execList(CLinkList* list, ExecFunc fn)
{
    if (!list->isEmpty()) {
        TLinkList<CSunFireObj> tmp;
        list->copyLink(tmp.asList());
        while (!tmp.isEmpty()) {
            CSunFireObj* o = tmp.begin();
            o->unlink();
            o->CLinkNode::insertBack(list);
            fn(o);
        }
    }
}

} // namespace m522
