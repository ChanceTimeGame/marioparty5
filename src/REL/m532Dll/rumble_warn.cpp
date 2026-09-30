/* rumble_warn.cpp -- m532::CRumbleWarn (rumble_warn.h). Retail order: ctor, dtor, update, procGrow, procHold,
 * procFade, procShow, draw, __sinit (the 300/60 pair: s_reactTime is procHold/procShow's frame count).
 * Drafts written whole from the sheet (master_camera_map_score_rumble.md §7) and the asm. */
#include "REL/m532Dll/config.h"
#include "REL/m532Dll/param.h"
#include "REL/m532Dll/rumble_warn.h"
#include "REL/m532Dll/util.h"

namespace m532 {

CRumbleWarn::CRumbleWarn(Vec* pos)
    : m_proc(&CRumbleWarn::procShow),
      m_anim0(HuSprAnimRead(HuDataSelHeapReadNum(0x5A0018, HU_MEMNUM_OVL, HEAP_MODEL))),
      m_anim1(HuSprAnimRead(HuDataSelHeapReadNum(0x5A0019, HU_MEMNUM_OVL, HEAP_MODEL))),
      m_w(m_anim0->bmp->sizeX),
      m_h(m_anim0->bmp->sizeY), m_pos(*pos), m_scale(0.0f), m_alpha(1.0f), m_count(0)
{
    CModel::setLayer(6);
    HuSprAnimLock(m_anim0);
    HuSprAnimLock(m_anim1);
}

CRumbleWarn::~CRumbleWarn()
{
    HuSprAnimKill(m_anim1);
    HuSprAnimKill(m_anim0);
}

void CRumbleWarn::update()
{
    if (!(this->*m_proc)()) {
        delete this;
    }
}

bool CRumbleWarn::procGrow()
{
    float step = 1.0f / 6.0f;
    if ((m_scale += step) >= 1.0) {
        m_scale = 1.0f;
        setProc(&CRumbleWarn::procHold);
    }
    return true;
}

bool CRumbleWarn::procHold()
{
    if (++m_count >= s_reactTime) {
        setProc(&CRumbleWarn::procFade);
    }
    return true;
}

bool CRumbleWarn::procFade()
{
    float step = 1.0f / 12.0f;
    if ((m_alpha -= step) <= 0.0f) {
        return false;
    }
    return true;
}

bool CRumbleWarn::procShow()
{
    m_scale = 1.0f;
    m_alpha = 1.0f;
    return ++m_count < s_reactTime;
}

/* lbl_1_rodata_1A4 / 1A8 / 1C0 */
static const GXColor s_black = { 0, 0, 0, 0 };
static const GXVtxDescList s_vtxDesc[] = { { GX_VA_POS, GX_DIRECT }, { GX_VA_TEX0, GX_DIRECT }, { GX_VA_NULL, GX_NONE } };
static const GXVtxAttrFmtList s_vtxFmt[] = {
    { GX_VA_POS, GX_POS_XYZ, GX_F32, 0 }, { GX_VA_TEX0, GX_TEX_ST, GX_F32, 0 }, { GX_VA_NULL, GX_POS_XY, GX_U8, 0 }
};

/* STUB detail (fn_1_8528, 312 insns): the billboard (the view's inverse rotation), two TEV stages (icon x mask),
 * alpha-tested at 0.75 * alpha */
void CRumbleWarn::draw(Mtx* view)
{
    Mtx inv;
    Mtx m;
    PSMTXInverse(*view, inv);
    inv[0][3] = inv[1][3] = inv[2][3] = 0.0f;
    PSMTXScale(m, m_scale, m_scale, m_scale);
    PSMTXTransApply(m, m, m_pos.x, m_pos.y, m_pos.z);
    PSMTXConcat(*view, m, m);
    PSMTXConcat(m, inv, m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    GXSetNumChans(0);
    HuSprTexLoad(m_anim0, 0, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    HuSprTexLoad(m_anim1, 0, GX_TEXMAP1, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXColor color = s_black;
    color.a = 255.0f * m_alpha;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetNumTevStages(2);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetCullMode(GX_CULL_NONE);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetAlphaCompare(GX_GEQUAL, 0.75 * color.a, GX_AOP_AND, GX_LEQUAL, 255);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXClearVtxDesc();
    GXSetVtxDescv((GXVtxDescList*)s_vtxDesc);
    GXSetVtxAttrFmtv(GX_VTXFMT0, (GXVtxAttrFmtList*)s_vtxFmt);
    float x0 = -m_w;
    float x1 = m_w;
    float y0 = m_h;
    float y1 = -m_h;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(x0, y0, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(x1, y0, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(x1, y1, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(x0, y1, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();
}

} // namespace m532
