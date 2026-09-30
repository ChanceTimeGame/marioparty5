/* asiato.cpp -- m501::CAsiato (footprint decals that fade out) and CAsiatoMan (their list and draw hook). */
#include "REL/mgcpp/minigame.h" /* retail asiato.o has the 120/210/210 triple */
#include "REL/m501Dll/asiato.h"
#include "REL/m501Dll/particle.h"

namespace m501 {

/* lbl_1_bss_48 (+ its DestructorChain) and lbl_1_bss_50 (72, dynamically initialised) */
static CLinkList s_asiatoList;
inline int AsiatoLifeTime() { return 72; }
static int s_asiatoLife = AsiatoLifeTime();

void CAsiatoMan::init()
{
    HU3DMODELID id = Hu3DHookFuncCreate(CAsiato::drawHook);
    Hu3DModelLayerSet(id, 0);
    Hu3DModelCameraSet(id, 1);
}

void CAsiatoMan::update()
{
    CAsiato::execAsiatoList(&s_asiatoList, CAsiato::update);
}

void CAsiatoMan::close()
{
    while (!s_asiatoList.isEmpty()) {
        CAsiato* a = s_asiatoList.last<CAsiato>();
        delete a;
    }
}

CAsiato::CAsiato(Vec* pos, float rot) : m_pos(*pos), m_rot(rot)
{
    m_life = s_asiatoLife;
    insertBack(&s_asiatoList);
}


void CAsiato::update(CAsiato* asiato)
{
    asiato->m_life--;
    if (asiato->m_life < 0) {
        delete asiato;
    }
}

void CAsiato::drawHook(Hu3DModel_s* model, Mtx* mtx)
{
    Hu3DModelObjDrawInit();
    CAsiatoDrawData data;
    PSMTXCopy(*mtx, data.m_mtx);
    data.m_model = CParticle::getInstance()->id();
    drawAsiatoList(&s_asiatoList, &data);
}

void CAsiato::drawAsiato(CAsiatoDrawData* data, CAsiato* asiato)
{
    Mtx mtx;
    PSMTXRotRad(mtx, 'Y', 0.017453292f * asiato->m_rot);
    float scale = (float)asiato->m_life / (float)s_asiatoLife;
    PSMTXScaleApply(mtx, mtx, 60.0f * scale, 1.0f, 60.0f * scale);
    PSMTXTransApply(mtx, mtx, asiato->m_pos.x, 5068.02f, asiato->m_pos.z);
    PSMTXConcat(data->m_mtx, mtx, mtx);
    Hu3DModelObjDraw(data->m_model, (char*)"asiato", mtx);
}

void CAsiato::execAsiatoList(CLinkList* list, void (*func)(CAsiato*))
{
    execAsiatoList(list->begin<CAsiato>(), static_cast<CAsiato*>(list->end()), func);
}

void CAsiato::drawAsiatoList(CLinkList* list, CAsiatoDrawData* data)
{
    drawAsiatoList(list->begin<CAsiato>(), static_cast<CAsiato*>(list->end()), data);
}

void CAsiato::drawAsiatoList(CAsiato* begin, CAsiato* end, CAsiatoDrawData* data)
{
    for (; begin != end; begin = static_cast<CAsiato*>(begin->next())) {
        drawAsiato(data, begin);
    }
}

void CAsiato::execAsiatoList(CAsiato* begin, CAsiato* end, void (*func)(CAsiato*))
{
    /* retail reads p->next after func(p), which may have deleted p (use-after-free, 0x651C) */
    for (; begin != end; begin = static_cast<CAsiato*>(begin->next())) {
        func(begin);
    }
}

} // namespace m501

/* The CParticle singleton pointer: retail's weak template static, kept by the linker in asiato.o (the
 * first TU in link order to instantiate it), at the end of its .bss (singleton.h). symbols.txt:
 * lbl_1_bss_54. */
template <> m501::CParticle* CSingleton<m501::CParticle>::ms_pointer = 0;
