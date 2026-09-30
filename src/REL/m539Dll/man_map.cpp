/* man_map.cpp -- m539::CMapMan, the arena. The asserts are retail's man_map.cpp:42 and :68 (keep the lines).
 * Retail order: CheckInstance, SetShadowReceiver, ctor, [~auto_ptr<CHeiho>, its __defctor, ~CSingleton],
 * stateIdle, on_update, on_new_mode, dtor; auto_ptr<CHeiho>(CHeiho*) and CLerp<float> at the end, __sinit. */
#include "REL/mgcpp/minigame.h"
#include "REL/m539Dll/man_map.h"
#include "REL/m539Dll/heiho.h"

void ShadowSetup(s16 camBit, Vec* lightDir, Vec* target, float size, float depth); /* mgcpp shadow.cpp */

namespace m539 {

/* man_map .rodata 1C0 / 1F0: the walkers' loops */
static const Vec s_path0[4] = { { -961.0f, -60.0f, -1777.0f }, { -1990.0f, -60.0f, -3153.0f },
    { -777.0f, -60.0f, -3088.0f }, { -1838.0f, -60.0f, -2113.0f } };
static const Vec s_path1[4] = { { -89.0f, -60.0f, -1000.0f }, { 1021.0f, -60.0f, -1432.0f },
    { 1021.0f, -60.0f, -1225.0f }, { 1366.0f, -60.0f, -1225.0f } };

void CMapMan::CheckInstance()
{
    CMapMan* p = GetInstance();
}

void CMapMan::SetShadowReceiver(s16 id)
{
    Hu3DModelShadowMapSet(id);
    Hu3DModelShadowDispOn(id);
    Hu3DModelLayerSet(id, 0);
}

/* fn_1_BF70 (294 insns, masked 0; raw residue = pooled string labels only). Retail: the two models go through auto_ptr temporaries
 * (stack slots) into the members; __construct_array(m_heiho, __defctor, ~auto_ptr, 4, 2); each reset inlines
 * ~CHeiho (delete the model, delete); Hu3DModelLightInfoSet / LightIdGet take the ids through two stack
 * shorts (CModel::id() by value); the target Vec is a word copy of .rodata 220; the sprite anim is a local.
 * Host: nothing here depends on GC offsets.
 * Line layout: the ctor's two asserts are man_map.cpp:42 and :68 (their __LINE__ is an immediate),
 * so keep the padding below when editing (fill it, do not add lines above the ctor).
 */
CMapMan::CMapMan() : m_shadow(new CModel(0x610001U)), m_map(new CModel(0x610000U)), m_alpha(0.0f, 0)
{

    int lights = Hu3DModelLightInfoSet(m_map->id(), 1);
    assert(lights > 0);
    m_heiho[0].reset(new CHeiho((Vec*)s_path0, 4));
    m_heiho[1].reset(new CHeiho((Vec*)s_path1, 4));
    SetShadowReceiver(m_shadow->id());
    /* line padding: the assert below is retail's man_map.cpp:68 */




















    HU3DLIGHTID light_id = Hu3DModelLightIdGet(m_map->id(), (char*)"inf_light1");
    assert(light_id >= 0);
    Vec pos;
    Vec dir;
    GXColor col;
    Hu3DGLightParamGet((int)light_id, &pos, &dir, &col); /* (int): retail extsh here (guess at the spelling) */
    Vec target = { 0.0f, 300.0f, -85.0f };
    ShadowSetup(15, &dir, &target, 600.0f, 530.0f);
    Hu3DShadowMultiTPLvlSet(0.5f, 15);
    Hu3DShadowMultiColSet(0x20, 0x20, 0x20, 15);
    ANIMDATA* anim = HuSprAnimRead(HuDataSelHeapReadNum(0x61000B, HU_MEMNUM_OVL, HEAP_MODEL));
    s16 grp = m_grp = HuSprGrpCreate(1);
    HuSprGrpMemberSet(grp, 0, HuSprCreate(anim, 400, 0));
    HuSprTPLvlSet(grp, 0, 0.0f);
    HuSprPosSet(grp, 0, 288.0f, 240.0f);
    ProcFunc proc = &CMapMan::stateIdle; /* PTMF via a stack temp, as retail */
    m_proc = proc;
    m_map->setAttr(HU3D_MOTATTR_LOOP);
}

void CMapMan::stateIdle() {}

void CMapMan::on_update()
{
    if (m_proc) {
        (this->*m_proc)();
    }
    HuSprTPLvlSet(m_grp, 0, m_alpha.Update());
    m_heiho[0]->update();
    m_heiho[1]->update();
}

void CMapMan::on_new_mode(int mode)
{
    if (mode == 1) {
        m_alpha.Set(1.0f, 48);
    }
    m_execFlags &= ~(1 << mode);
}

CMapMan::~CMapMan() {}

} // namespace m539
