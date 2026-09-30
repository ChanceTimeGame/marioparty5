#ifndef M579_WATEREFF_H
#define M579_WATEREFF_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include <vector>

namespace m579 {

class CWaterEff : public CGameObject, public CSingleton<CWaterEff>, public CModel {
public:
    CWaterEff();                                     /* fn_1_148AC */
    virtual ~CWaterEff();                            /* fn_1_14D1C frees the copy buffer only (retail) */
    virtual void on_new_mode(int mode);              /* fn_1_14E50 (= m501) */
    static void GetCamera(Vec* pos, float* far);     /* fn_1_14E68 unreferenced (inlined in on_update) */
    virtual void on_update();                        /* fn_1_14ED8 */
    static void Hook(HU3DMODEL* model, Mtx* mtx);    /* fn_1_15130 ((CWaterEff*)hookData)->Draw(mtx) */
    void LoadScreenTex(GXTexMapID map, u32 texMtx, Mtx mv); /* fn_1_15168 unreferenced (inlined) the EFB copy (§4.1) */
    void LoadBumpTex(GXTexMapID map, u32 texMtx);   /* fn_1_15280 unreferenced (inlined) */
    void LoadWaveTex(GXTexMapID map, u32 texMtx);   /* fn_1_152CC unreferenced (inlined) */
    void SetIndStage(GXIndTexStageID stage, GXTexMapID map, GXTexCoordID coord); /* fn_1_1532C unreferenced; this unused */
    void Draw(Mtx* mtx);                             /* fn_1_1537C */
    void DrawDisc();

    /* 0x10 CModel base (the hook model) */
    GXTexObj m_screenTex;          /* 0x14 over m_copyBuf: 320x240 RGB565, clamp */
    GXTexObj m_bumpTex;            /* 0x34 over m_bumpData: 128x128 IA8, repeat, mipmapped (LOD 0..7) */
    std::vector<char> m_copyBuf;   /* 0x54 GXGetTexBufferSize(320, 240, RGB565, 0, 0) bytes */
    void* m_bumpData;              /* 0x60 HuDataSelHeapReadNum(0x850012) (never freed, retail) */
    ANIMDATA* m_waveAnim;          /* 0x64 0x850013 (never killed, retail) */
    Mtx m_model;                   /* 0x68 disc model matrix */
    Mtx m_texMtxWave;              /* 0x98 TEXMTX3 (TC1) */
    Mtx m_texMtxBump;              /* 0xC8 TEXMTX1 (TC2 -> IND0) */
    Mtx m_texMtxWave2;             /* 0xF8 TEXMTX2 (TC3 -> IND1) */
    float m_scrollA;               /* 0x128 -= 10/7 a frame */
    float m_scrollB;               /* 0x12C -= 10/17 a frame */
};

} // namespace m579

#ifndef __MWERKS__
template <> m579::CWaterEff* CSingleton<m579::CWaterEff>::ms_pointer; /* defined in game_master.cpp (bss A24) */
#endif

#endif
