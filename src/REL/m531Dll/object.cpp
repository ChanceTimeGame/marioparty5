/* object.cpp -- CStageObjects, CDrift, CGuruguru, CProp (object.h), in retail order; the weak inline
 * CStage::on_update (stage.h) is first needed here, so object.o carries the copy retail kept (fn_1_90C8).
 * Written whole from the asm (sheet: ../20260925-m531-w0/game/flow_object_audio_master.md §3.7). The retail
 * CW -O0 code goes through the inline CStage::GetModel() (stage.h) for most model ids: its extsh'd return temp.
 * The strings come in retail order (GetInstance's assert, the two joint names, the hook name). */
#include "REL/m531Dll/object.h"
#include "REL/m531Dll/cleaneff.h"
#include "REL/m531Dll/polish.h"
extern "C" {
#include "game/frand.h"
}

namespace m531 {

/* data_1D0: the eight drift positions (passed by pointer; non-const in retail) */
static Vec s_driftPos[8] = {
    { -800.0f, -1200.0f, -300.0f }, { -400.0f, -1200.0f, 0.0f }, { 0.0f, -1200.0f, 200.0f },
    { 400.0f, -1200.0f, 400.0f },   { 800.0f, -1200.0f, 600.0f }, { -300.0f, -1200.0f, 800.0f },
    { -200.0f, -1200.0f, 200.0f },  { -400.0f, -1200.0f, 300.0f },
};

struct PropPlace {
    Vec pos;
    Vec rot;
};

/* data_230: the five props (passed by value) */
static PropPlace s_propPlace[5] = {
    { { -722.0f, -389.0f, -53.0f }, { 0.0f, 59.4f, 0.0f } },
    { { 687.0f, -406.0f, 145.0f }, { 0.0f, -69.5f, 0.0f } },
    { { -13.0f, -582.0f, 433.0f }, { 0.0f, -120.0f, 0.0f } },
    { { -711.0f, -582.0f, 404.0f }, { 0.0f, -226.0f, 0.0f } },
    { { 877.0f, -582.0f, -206.0f }, { 0.0f, -22.4f, 0.0f } },
};

static int s_propMotKind[5] = { 1, 0, 0, 0, 1 }; /* data_2A8 */
static u8 s_propSlow[5] = { 0, 0, 1, 0, 0 };     /* data_2BC */

/* the fmr chain in updateActive (81F4) is an inlined min */
static inline float MinF(float a, float b)
{
    return (a < b) ? a : b;
}

CStageObjects::CStageObjects(Process_s* om)
{
    for (int i = 0; i < 8; i++) {
        m_drift[i] = new CDrift(om, &s_driftPos[i]);
    }
    m_base0 = new CStage(om, 0x590000, 1, 4, 1);
    {
        CStage* base = m_base0;
        Hu3DModelShadowMapSet(base->GetModel());
    }
    m_base1 = new CStage(om, 0x590001, 1, 4, 1);
    for (int i = 0; i < 5; i++) {
        m_prop[i] = new CProp(om, i, s_propMotKind[i], s_propPlace[i].pos, s_propPlace[i].rot, s_propSlow[i]);
    }
    {
        Vec pos = { -732.0f, -222.0f, -185.0f };
        Vec rot = { 0.0f, 45.0f, 0.0f };
        m_spray = new CSpray(0x590003, 12, pos, rot);
    }
}

CStageObjects::~CStageObjects()
{
    for (int i = 0; i < 5; i++) {
        delete m_prop[i];
    }
    delete m_base0;
    delete m_base1;
    delete m_spray;
    for (int i = 0; i < 8; i++) {
        delete m_drift[i];
    }
}

CGuruguru::CGuruguru(Process_s* om, u32 dataNum, int index) : CStage(om, dataNum, 3, 4, 1)
{
    m_state = 0;
    m_count = 0;
    m_index = index;
    m_popSub = 0;
    m_sePlayed = 0;
    setShadow();
    Hu3DModelAttrSet(GetModel(), 0x40000080);
    m_animScale.x = m_animScale.y = m_animScale.z = 1.0f;
}

void CGuruguru::syncModel()
{
    int model = GetModel();

    Hu3DModelPosSet(model, m_pos.x, m_pos.y, m_pos.z);
    Hu3DModelRotSet(model, m_rot.x, m_rot.y, m_rot.z);
}

void CGuruguru::appear()
{
    if (m_state == 0) {
        HuAudFXPlay(0x7A3);
        Hu3DModelAttrReset(GetModel(), 0x40000080);
        m_state = 1;
    }
}

void CGuruguru::updateActive()
{
    int model = GetModel();
    CCleanEff* eff = CCleanEffMan::GetInstance()->get(0);
    Mtx mtx;

    Hu3DModelObjMtxGet(model, (char*)"guruguru6-cyl1", mtx);
    Vec v = { 0.0f, 100.0f, 45.0f };
    PSMTXMultVec(mtx, &v, &v);
    Hu3DModelObjMtxGet(model, (char*)"guruguru6-scale_dmy", mtx);
    float s = MinF(mtx[1][1], 1.0f);
    if (m_index == 0) {
        eff->setCenter(&v);
        eff->setGrow(s);
        if (!m_sePlayed && v.y < 28.0f) {
            HuAudFXPlay(0x7A4);
            HuAudFXPlay(0x7A5);
            m_sePlayed = 1;
        }
    }
    if (s >= 1.0f) {
        m_state = 2;
        m_basePos = m_pos;
        Hu3DModelAttrSet(GetModel(), 0x40000080);
    }
}

void CGuruguru::updatePop()
{
    s16 model = GetModel();
    Vec pos;

    switch (m_popSub) {
    case 0:
        m_animScale.x += (0.2f - m_animScale.x) / 6.0f;
        m_animScale.y += (0.2f - m_animScale.y) / 6.0f;
        m_animScale.z += (0.2f - m_animScale.z) / 6.0f;
        if (m_animScale.x > 0.3f) {
            break;
        }
        m_popSub++;
        /* falls through (retail): the next phase starts in the same frame */
    case 1:
        m_animScale.x += (1.5f - m_animScale.x) / 2.0f;
        m_animScale.y += (1.0f - m_animScale.y) / 2.0f;
        m_animScale.z += (0.5f - m_animScale.z) / 2.0f;
        if (m_animScale.x < 1.3) {
            break;
        }
        m_popSub++;
        /* falls through (retail) */
    case 2:
        m_animScale.x += -m_animScale.x / 5.0f;
        m_animScale.y += -m_animScale.y / 5.0f;
        m_animScale.z += -m_animScale.z / 5.0f;
        if (m_animScale.x > 0.1f) {
            break;
        }
        m_animScale.x = m_animScale.y = m_animScale.z = 0.0f;
        m_state = 3;
        pos.x = m_pos.x;
        pos.y = 22.5f + m_pos.y;
        pos.z = 50.0f + m_pos.z;
        CharEffectHitCreate(1, &pos, &m_rot);
        m_popSub++;
        /* no break: updatePop sits at CW's auto-inline size limit, and on_update inlines it only without one */
    }
    m_pos.y = m_basePos.y + 22.5f * (1.0f - m_animScale.y);
    m_pos.z = m_basePos.z + 50.0f * (1.0f - m_animScale.z);
    Hu3DModelScaleSet(model, m_animScale.x, m_animScale.y, m_animScale.z);
}

void CGuruguru::on_update()
{
    syncModel();
    switch (m_state) {
    case 1:
        updateActive();
        break;
    case 2:
        updatePop();
        break;
    }
    m_count++;
}

CProp::CProp(Process_s* om, int i, int motKind, Vec pos, Vec rot, u8 slow) : CStage(om, 0x590011, 3, 4, 1)
{
    static const u32 motTbl[2] = { 0x590012, 0x590013 }; /* rodata_484 */
    s16 model = GetModel();
    HU3DMOTID motion = Hu3DJointMotion(model, HuDataSelHeapReadNum(motTbl[motKind], HU_MEMNUM_OVL, HEAP_MODEL));

    Hu3DMotionSet(model, motion);
    Hu3DModelAttrSet(model, 0x40000001);
    Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
    Hu3DModelRotSet(model, rot.x, rot.y, rot.z);
    HU3DMODEL* modelP = &Hu3DData[model];
    if (slow) {
        modelP->ambR = 0.5f;
        modelP->ambG = 0.2f;
        modelP->ambB = 0.7f;
    } else {
        modelP->ambR = 0.7f;
        modelP->ambG = 0.7f;
        modelP->ambB = 0.65f;
    }
    m_hookModel = Hu3DModelCreate(HuDataSelHeapReadNum(0x590010, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelHookSet(GetModel(), (char*)"g003m2-itemhook_R", m_hookModel);
}

CDrift::CDrift(Process_s* om, const Vec* pos) : CStage(om, 0x59000A, 0, 4, 1)
{
    s16 model = GetModel();
    float s = 0.5f + 0.5f * ((1.0f / 65536.0f) * (u16)frand());

    Hu3DModelScaleSet(model, s, s, s);
    m_pos = *pos;
}

void CDrift::on_update()
{
    m_pos.x += 1.0f / 3.0f;
    if (m_pos.x > 1200.0f) {
        m_pos.x = -1200.0f;
    }
    s16 model = GetModel();
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(model, m_pos.x, m_pos.y, m_pos.z);
}

CGuruguru::~CGuruguru() {}

} // namespace m531
