#include "REL/m522Dll/stage.h"
#include "REL/m522Dll/fire.h"
#include "REL/m522Dll/bubble.h"
#include "REL/m522Dll/camera.h"
#include "REL/m522Dll/player.h"
extern "C" {
#include "game/hsfformat.h"
}

namespace m522 {

/* lbl_1_data_500..540: the tower's blocks, bottom to top (the array is not const: retail's table is .data) */
static const char* s_brockName[CStage::NUM_BLOCKS] = { "brock_a", "brock_b", "brock_c", "brock_d",
                                                 "brock_e", "brock_f", "brock_g", "brock_h" };

/* STUB detail (fn_1_E85C, 199 insns): the mem-initialisers in member order; `->` goes through a stack temporary
 * (the auto_ptr operator-> return) */
CStage::CStage()
    : m_sun(new CSun), m_sky(new CModel(0x500003u)), m_bg(new CModel(0x500001u)), m_tower(new CModel(0x500007u)),
      m_bubble(new CBubbleMan), m_unk2C(-1), m_se(HuAudFXPlay(0x3A2)), m_numBlocks(NUM_BLOCKS),
      m_blocksLeft(m_numBlocks), m_colIdx(0), m_slide(0.0f), m_bgRotY(0.0f)
{
    m_sky->setLayer(3);
    m_sky->setAttr(HU3D_ATTR_ZCMP_OFF);
    m_bg->setLayer(0);
    m_bg->setAttr(HU3D_MOTATTR_LOOP);
    m_tower->setLayer(4);
    Hu3DShadowCreate(35.0f, 1300.0f, 2000.0f);
    Hu3DShadowSizeSet(480);
    Hu3DShadowColSet(0x20, 0x10, 0);
    Hu3DShadowTPLvlSet(0.6f);
    const char* top = s_brockName[m_numBlocks - 1];
    m_tower->setShadowMapObj(top);
    new CFire; /* a CSunFireObj on s_list (deleted by CSunFireMan::DeleteAll) */
    InitCol();
}

CStage::~CStage()
{
    HuAudFXStop(m_se);
}

/* the two floors: an inline reset per element, then MgActorColMapInit over their ids (a local aggregate, rodata_43C) */
void CStage::InitCol()
{
    for (int i = 0; i < 2; i++) {
        m_col[i].reset(new CModel(0x500008u));
        m_col[i].get()->setAttr(HU3D_ATTR_DISPOFF);
    }
    HU3DMODELID ids[2] = { 0 };
    ids[0] = m_col[0]->id();
    ids[1] = m_col[1]->id();
    MgActorColMapInit(ids, 2, 8);
}

/* the top block goes: the next floor rises into place, the camera follows unless it was the last block */
void CStage::BreakBlock(Vec* hitPos)
{
    if (m_blocksLeft <= 0 || m_slide > 0.0f) {
        return;
    }
    m_blocksLeft--;
    m_slide = 2000.0f;
    Vec p = { 0.0f, 0.0f, 0.0f };
    /* lbl_1_rodata_44C: the break SE per remaining block count 0..7 (after the decrement). Function-local:
     * retail's .rodata has it after p's initialiser (rodata_440) */
    static const s32 s_breakSe[NUM_BLOCKS] = { 0x73F, 0x73D, 0x73C, 0x743, 0x742, 0x741, 0x740, 0x73E };
    p.y = (float)((m_blocksLeft - m_numBlocks) * 2 * 100);
    m_col[m_colIdx]->setPos(&p);
    m_colIdx ^= 1;
    if (m_blocksLeft > 0) {
        CSingleton<CCameraObj>::GetInstance()->Lower(200.0f);
        m_tower->setShadowMapObj(s_brockName[m_blocksLeft - 1]);
    } else {
        m_sun->StopSpin();
        m_sun->SetShadowSun();
    }
    switch (m_blocksLeft) {
    case 2:
    case 4:
    case 6:
        CSingleton<CBubbleMan>::GetInstance()->Spawn();
        break;
    }
    s16 pan = GetPan(hitPos); /* the (int) casts below give retail's extsh at each call (an int local extends at the store instead) */
    HuAudFXPlayPan(0x73B, (int)pan);
    HuAudFXPlayPan(s_breakSe[m_blocksLeft], (int)pan);
    HuAudFXPlayPan(0x744, (int)pan);
}

bool CStage::IsDropDone()
{
    return m_slide <= 0.0f;
}

float CStage::GetTopY()
{
    return (float)((m_blocksLeft * 2 + 1) * 100);
}

int CStage::GetBlocksLeft()
{
    return m_blocksLeft;
}

void CStage::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

/* STUB detail (fn_1_F218, 77 insns): the shadow pos / up / target from a local aggregate (rodata_478) */
void CStage::on_update()
{
    if (m_slide > 0.0f) {
        SlideBlock();
    }
    float y = GetTopY();
    struct {
        Vec pos;
        Vec up;
        Vec target;
    } s = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f, 0.0f } };
    s.pos.y = y - 1300.0f;
    s.target.y = y;
    Hu3DShadowPosSet(&s.pos, &s.up, &s.target);
    m_sun->Update();
    RotateBg();
}

void CStage::SlideBlock()
{
    const char* name = s_brockName[m_blocksLeft];
    HSFOBJECT* o = m_tower->getObjPtr(name);
    float* x = &o->mesh.base.pos.x;
    float step = 41.666668f;
    *x += step;
    if ((m_slide -= step) <= 0.0f) {
        m_slide = 0.0f;
        o->flags |= HSF_MATERIAL_DISPOFF;
    }
    Vec p = { 0.0f, 0.0f, 0.0f };
    p.x = *x;
    p.y = (float)((m_blocksLeft + 1 - m_numBlocks) * 200);
    if (m_slide <= 0.0f) {
        p.x = 0.0f;
        p.y -= 400.0f;
    }
    m_col[m_colIdx]->setPos(&p);
}

void CStage::RotateBg()
{
    Vec rot = { 0.0f, 0.0f, 0.0f };
    rot.y = m_bgRotY;
    m_bg->setRot(&rot);
    m_bgRotY = m_bgRotY - 0.004166666666666667;
}

} // namespace m522
