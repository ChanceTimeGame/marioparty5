#ifndef M511_STAGE_H
#define M511_STAGE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"

namespace m511 {

class CWater;

class CStage : public CGameObject, public CSingleton<CStage> {
public:
    static void FogPost(s16 layer);     /* fn_1_C55C layer hook 8: GX_FOG_PERSP_EXP 3000..20000, s_fogCol */
    static void FogPre(s16 layer);      /* fn_1_C5EC layer hook 0: GX_FOG_NONE, s_noFogCol */
    CStage();                           /* fn_1_C67C models, hooks, the 38 buoys */
    virtual ~CStage();                  /* fn_1_CCC8 CBuoy::KillAll(); no hook reset (retail) */
    virtual void on_update();           /* fn_1_CDEC CBuoy::UpdateAll() */
    virtual void on_new_mode(int mode); /* fn_1_CE0C clear the bit; empty switch 0..4 */

    CModel m_sea;   /* 0x10 0x450011 layer 0 */
    CModel m_12;    /* 0x12 0x450012 layer 1 */
    CModel m_14;    /* 0x14 0x450013 layer 1 */
    CModel m_buoy;  /* 0x16 0x450014 hidden template of every CBuoy */
    CModel m_gateN; /* 0x18 0x45001E (0, 0, +5000) */
    CModel m_gateS; /* 0x1A 0x45001D (0, 0, -5000) */
    CModel m_1C;    /* 0x1C 0x450015 layer 4 */
};

class CBuoy : public TLinkItem<CBuoy> {
public:
    CBuoy(CModel* src, const Vec* pos); /* fn_1_CE34 retail sets the position twice (setPos(&m_rot)) */
    static void KillAll();              /* fn_1_D00C ~CStage: tail first */
    static void UpdateAll();            /* fn_1_D0E0 */
    static void UpdateOne(CBuoy* p);    /* fn_1_D110 p->Update() */
    void Update();                      /* fn_1_D138 ease to the water height */

    static TLinkList<CBuoy> s_buoys;    /* bss A84; its DestructorChain A78 */

    Vec m_pos;         /* 0x08 */
    Vec m_rot;         /* 0x14 0 */
    CModel m_model;    /* 0x20 CModel(CModel&) of CStage::m_buoy */
    int m_unk24;       /* 0x24 never accessed */
    CWater* m_water;   /* 0x28 CWater::GetInstance() */
};

} // namespace m511

#ifndef __MWERKS__
template <> m511::CStage* CSingleton<m511::CStage>::ms_pointer; /* defined in boat.cpp (.bss 18) */
#endif

#endif
