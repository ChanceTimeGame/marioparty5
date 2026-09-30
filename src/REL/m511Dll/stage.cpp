#include "REL/m511Dll/config.h"
#include "REL/m511Dll/stage.h"
#include "REL/m511Dll/water.h"

namespace m511 {

/* lbl_1_data_430 / 434: the fog colour and the no-fog colour (copied byte-wise to the by-value temporary) */
static GXColor s_fogCol = { 0x95, 0xAC, 0xE2, 0x00 };
static GXColor s_noFogCol = { 0xFF, 0xFF, 0xFF, 0x00 };

TLinkList<CBuoy> CBuoy::s_buoys;

/* layer hook 8 (after layer 0): exponential fog 3000..20000 in the lake colour */
void CStage::FogPost(s16 layer)
{
    float fov;
    float near;
    float far;
    Hu3DCameraPerspectiveGet(1, &fov, &near, &far);
    GXSetFog(GX_FOG_PERSP_EXP, 3000.0f, 20000.0f, near, far, s_fogCol);
}

/* layer hook 0: no fog */
void CStage::FogPre(s16 layer)
{
    float fov;
    float near;
    float far;
    Hu3DCameraPerspectiveGet(1, &fov, &near, &far);
    GXSetFog(GX_FOG_NONE, 3000.0f, 20000.0f, near, far, s_noFogCol);
}

CStage::CStage()
    : m_sea(0x450011U), m_12(0x450012U), m_14(0x450013U), m_buoy(0x450014U), m_gateN(0x45001EU),
      m_gateS(0x45001DU), m_1C(0x450015U)
{
    HU3DMODELID id;
    Hu3DLayerHookSet(0, FogPre);
    Hu3DLayerHookSet(8, FogPost);

    id = m_sea.id();
    Hu3DModelLayerSet(id, 0);
    Hu3DModelLightInfoSet(id, 1);
    Hu3DModelPosSet(id, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(id, 15);

    id = m_12.id();
    Hu3DModelLayerSet(id, 1);
    Hu3DModelPosSet(id, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(id, 15);

    id = m_14.id();
    Hu3DModelLayerSet(id, 1);
    Hu3DModelPosSet(id, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(id, HU3D_ATTR_NOCULL);
    Hu3DModelCameraSet(id, 15);

    /* the hidden template every CBuoy links */
    id = m_buoy.id();
    Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);

    id = m_gateN.id();
    Hu3DModelLayerSet(id, 1);
    Hu3DModelPosSet(id, 0.0f, 0.0f, 5000.0f);
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(id, HU3D_ATTR_NOCULL);
    Hu3DModelCameraSet(id, 15);

    id = m_gateS.id();
    Hu3DModelLayerSet(id, 1);
    Hu3DModelPosSet(id, 0.0f, 0.0f, -5000.0f);
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(id, HU3D_ATTR_NOCULL);
    Hu3DModelCameraSet(id, 15);

    id = m_1C.id();
    Hu3DModelLayerSet(id, 4);
    Hu3DModelPosSet(id, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(id, HU3D_ATTR_NOCULL);
    Hu3DModelCameraSet(id, 15);

    /* 38 buoys on the +-5000 square; the gaps at (0, +-5000) are the gate models */
    Vec pos;
    pos.y = -1.25f;
    for (int i = 0; i < 11; i++) {
        if (i != 5) {
            pos.x = i * 10 * 100 - 5000;
            pos.z = -5000.0f;
            new CBuoy(&m_buoy, &pos);
            pos.z = 5000.0f;
            new CBuoy(&m_buoy, &pos);
        }
    }
    for (int j = 1; j < 10; j++) {
        pos.x = -5000.0f;
        pos.z = j * 10 * 100 - 5000;
        new CBuoy(&m_buoy, &pos);
        pos.x = 5000.0f;
        new CBuoy(&m_buoy, &pos);
    }
}

/* no Hu3DLayerHookSet(n, NULL): retail leaves the hooks set */
CStage::~CStage()
{
    CBuoy::KillAll();
}

void CStage::on_update()
{
    CBuoy::UpdateAll();
}

void CStage::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    switch (mode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        break;
    }
}

/* retail sets the position twice (the second setPos should be setRot; the first Update corrects it) */
CBuoy::CBuoy(CModel* src, const Vec* pos) : m_pos(*pos), m_model(*src)
{
    insertBack(&s_buoys);
    HU3DMODELID id = m_model.id();
    Hu3DModelScaleSet(id, 1.0f, 1.0f, 1.0f);
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(id, 1);
    Hu3DModelAttrSet(id, HU3D_ATTR_NOCULL);
    Hu3DModelCameraSet(id, 15);
    m_water = CSingleton<CWater>::GetInstance();
    m_pos.y = m_water->GetHeight(&m_pos);
    m_rot.x = 0.0f;
    m_rot.y = 0.0f;
    m_rot.z = 0.0f;
    m_model.setPos(&m_pos);
    m_model.setPos(&m_rot);
}

/* ~CStage: tail first */
void CBuoy::KillAll()
{
    while (!s_buoys.isEmpty()) {
        CBuoy* p = s_buoys.last();
        delete p;
    }
}

void CBuoy::UpdateAll()
{
    TLinkList<CBuoy>::exec(&s_buoys, UpdateOne);
}

void CBuoy::UpdateOne(CBuoy* p)
{
    p->Update();
}

/* ease to the water height (0.8 a frame) */
void CBuoy::Update()
{
    m_pos.y += 0.8f * (m_water->GetHeight(&m_pos) - m_pos.y);
    m_model.setRot(&m_rot);
    m_model.setPos(&m_pos);
}

} // namespace m511
