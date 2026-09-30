#include "REL/m521Dll/debugline.h"

namespace m521 {

void CDebugLine::DrawHook(HU3DMODEL* model, Mtx* mtx)
{
    CDebugLine* self = (CDebugLine*)model->hookData;
    self->draw(mtx);
}

/* fn_1_AB20 (64 insns, masked 24 = the .rodata 0.0f label shown with dtk's 8-byte tail pad only): the hook data through a model pointer (field by name on the host) */
CDebugLine::CDebugLine()
{
    HU3DMODELID id = Hu3DHookFuncCreate(DrawHook);
    HU3DMODEL* model = &Hu3DData[(int)id];
    model->hookData = this;
    Hu3DModelLayerSet(id, 5);
    Hu3DModelCameraSet(id, 1);
    m_model = id;
    m_start.x = 0.0f;
    m_start.y = 0.0f;
    m_start.z = 0.0f;
    m_end.x = 0.0f;
    m_end.y = 0.0f;
    m_end.z = 0.0f;
    m_color.r = 0xFF;
    m_color.g = 0xFF;
    m_color.b = 0xFF;
    m_color.a = 0xFF;
}

CDebugLine::~CDebugLine()
{
    Hu3DModelKill(m_model);
}

/* fn_1_AC74 (163 insns, raw 0): GEQUAL alpha compare, LO_NOOP, a 2-vertex LINESTRIP. Retail bug kept: the second vertex takes m_start.z */
void CDebugLine::draw(Mtx* mtx)
{
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT0, GX_DF_CLAMP, GX_AF_SPOT);
    GXSetZCompLoc(GX_FALSE);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ONE, GX_LO_NOOP);
    GXSetAlphaUpdate(GX_TRUE);
    Vec* start = &m_start;
    Vec* end = &m_end;
    GXColor* col = &m_color;
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 2);
    GXPosition3f32(start->x, start->y, start->z);
    GXColor4u8(col->r, col->g, col->b, col->a);
    GXPosition3f32(end->x, end->y, start->z);
    GXColor4u8(col->r, col->g, col->b, col->a);
    GXEnd();
}

} // namespace m521
