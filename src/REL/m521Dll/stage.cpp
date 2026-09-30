/* stage.cpp -- m521::CStage (stage.h). Retail order (master_camera_stage_score_debugline.md §5.3): CheckInstance,
 * SetShadowReceiver, ctor, [~auto_ptr<CClock> 14F9C, ~CSingleton<CStage> 14FF4: weak, unreferenced], proc_idle,
 * on_update, on_new_mode, dtor, __sinit (the minigame.h triple).
 * EXACT (m539 man_map BEBC / BF2C): CheckInstance, SetShadowReceiver; on_new_mode (= m501 CParticle / m512 7B14).
 * Drafted from the asm: the ctor (§5.4), on_update, the dtor (implicit member order).
 * .data 5D0..680: the :39 / :61 strings (CheckInstance first), the three writable statics (col, light pos, shadow
 * dir), the ctor's PTMF, its :53 string and the object names, the vtable. .rodata 2D0..318 (s_clockPosR / B / Q first).
 * .bss A98..AA0: the triple. */
#include "REL/mgcpp/minigame.h"
#include "REL/m521Dll/stage.h"
#include "REL/m521Dll/clock.h"
#include "REL/m521Dll/gamemaster.h"

namespace m521 {

void CStage::CheckInstance()
{
    CStage* p = GetInstance();
}

void CStage::SetShadowReceiver(s16 id)
{
    Hu3DModelShadowMapSet(id);
    Hu3DModelShadowDispOn(id);
    Hu3DModelLayerSet(id, 0);
}

/* lbl_1_rodata_2D0 / 2DC / 2E8: the clock pivots, R / B / Q (three objects) */
static const Vec s_clockPosR = { -450.0f, 90.0f, 0.0f };
static const Vec s_clockPosB = { 450.0f, 90.0f, 0.0f };
static const Vec s_clockPosQ = { 0.0f, 342.59369f, -386.138f };

/* lbl_1_data_5EC / 5F0 / 5FC: the light and the shadow direction (non-const: .data) */
static GXColor s_lightCol = { 0xFF, 0xFF, 0xFF, 0xFF };
static Vec s_lightPos = { 0.0f, 100.0f, 1000.0f };
static Vec s_shadowDir = { 0.0f, 1000.0f, 400.0f };

/* DRAFT (fn_1_149C0, 375 insns; sheet §5.4) */
CStage::CStage() : m_clockR(0), m_clockQ(0), m_clockB(0), m_model(new CModel(0x4F0000U)), m_shadowRecv(new CModel(0x4F0001U))
{
    Hu3DLighInit();
    Vec dir;
    PSVECNormalize(&s_lightPos, &dir);
    PSVECScale(&dir, &dir, -1.0f);
    int light = Hu3DGLightCreateV(&s_lightPos, &dir, &s_lightCol);
    Hu3DGLightInfinitytSet(light);
    Hu3DShadowCreate(40.0f, 20.0f, 25000.0f);
    SetShadowReceiver(m_model->id());
    m_model->setAttr(0x40000001);
    Vec d;
    Vec pos;
    Vec up;
    Vec at;
    PSVECNormalize(&s_shadowDir, &d);
    Hu3DShadowTPLvlSet(0.5f);
    at.x = 0.0f;
    at.y = 20.0f;
    at.z = -500.0f;
    PSVECScale(&d, &pos, 3000.0f);
    PSVECAdd(&pos, &at, &pos);
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    Hu3DShadowPosSet(&pos, &up, &at);
    Hu3DShadowColSet(32, 32, 32);
    m_model->shadowMapOffObj((char*)"sphere6");
    m_model->shadowMapOffObj((char*)"sphere12");
    m_model->shadowMapOffObj((char*)"ie_ALL");
    m_model->shadowMapOffObj((char*)"cyl9");
    m_model->shadowMapOffObj((char*)"cyl30");
    Hu3DModelShadowSet(m_shadowRecv->id());
    m_shadowRecv->setAttr(8);
    Hu3DModelShadowMapSet(s_standR->id());
    Hu3DModelShadowMapSet(s_standB->id());
    s_standR->shadowMapOffObj((char*)"tobiraRR");
    s_standR->shadowMapOffObj((char*)"tobiraRL");
    s_standB->shadowMapOffObj((char*)"tobiraBR");
    s_standB->shadowMapOffObj((char*)"tobiraBL");
    m_clockR.reset(new CClock(0, &s_clockPosR));
    m_clockB.reset(new CClock(1, &s_clockPosB));
    m_clockQ.reset(new CClock(2, &s_clockPosQ));
    s_clockR = m_clockR.get();
    s_clockB = m_clockB.get();
    s_clockQ = m_clockQ.get();
    setProc(&CStage::proc_idle);
}

void CStage::proc_idle() {}

/* clocks updated R, B, Q (retail) */
void CStage::on_update()
{
    if (m_proc) {
        (this->*m_proc)();
    }
    m_clockR->Update();
    m_clockB->Update();
    m_clockQ->Update();
}

void CStage::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

CStage::~CStage() {}

} // namespace m521
