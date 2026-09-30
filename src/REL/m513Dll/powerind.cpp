#include "REL/m513Dll/powerind.h"

namespace m513 {

void CPowerInd::CopyHook(HU3DMODEL* model, Mtx* mtx)
{
    CPowerInd* self = CSingleton<CPowerInd>::GetInstancePtr();
    self->CopyScreen(*mtx);
}

CPowerInd::CPowerInd()
{
    HU3DMODELID id = Hu3DHookFuncCreate(CopyHook);
    Hu3DModelLayerSet((int)id, 4); /* the (int) casts: retail's extsh at each use */
    Hu3DModelCameraSet((int)id, 1);
    InitTexObj();
    m_vec.x = 0.0f;
    m_vec.y = 0.0f;
    m_vec.z = 0.0f;
    m_mask = HuSprAnimRead(HuDataSelHeapReadNum(0x470015, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_mask);
    m_particleAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x470016, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_particleAnim);
    m_fireAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x470017, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_fireAnim);
    m_leafAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x470018, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_leafAnim);
    for (int i = 0; i < WARP_NUM; i++) {
        m_warp[i] = HuSprAnimRead(HuDataSelHeapReadNum(0x470019 + i, HU_MEMNUM_OVL, HEAP_MODEL));
        HuSprAnimLock(m_warp[i]);
    }
}

CPowerInd::~CPowerInd()
{
    HuSprAnimKill(m_mask);
    HuSprAnimKill(m_particleAnim);
    HuSprAnimKill(m_fireAnim);
    HuSprAnimKill(m_leafAnim);
    for (int i = 0; i < WARP_NUM; i++) {
        HuSprAnimKill(m_warp[i]);
    }
}

void CPowerInd::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

void CPowerInd::on_update()
{
    m_vec.x += 0.003f;
    m_vec.y += 0.003f;
    m_vec.z += 0.003f;
}

void CPowerInd::InitTexObj()
{
    GXInitTexObj(&m_texObj, m_buf, SCREEN_W, SCREEN_H, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&m_texObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
}

void CPowerInd::CopyEFB()
{
    GXSetTexCopySrc(0, 0, SCREEN_W, SCREEN_H);
    GXSetTexCopyDst(SCREEN_W, SCREEN_H, GX_TF_RGB565, GX_FALSE);
    GXCopyTex(m_buf, GX_FALSE);
}

void CPowerInd::SetProjTexGen(Mtx m)
{
    Mtx texMtx;
    Mtx proj;
    HU3DCAMERA* cam = &Hu3DCamera[Hu3DCameraNo];
    GXSetNumTexGens(1);
    C_MTXLightPerspective(proj, cam->fov, cam->aspect, 0.5f, -0.5f, 0.5f, 0.5f);
    PSMTXConcat(proj, m, texMtx);
    GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
}

/* draws nothing: the projective texgen state is left set, then the whole EFB is copied */
void CPowerInd::CopyScreen(Mtx m)
{
    GXLoadPosMtxImm(m, GX_PNMTX0);
    SetProjTexGen(m);
    CopyEFB();
}

} // namespace m513
