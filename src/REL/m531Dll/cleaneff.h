#ifndef M531_CLEANEFF_H
#define M531_CLEANEFF_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/singleton.h"
#include "REL/m531Dll/effect.h"
#include <memory>
#include <vector>

namespace m531 {

class CCleanEff : public CHookEffect {
public:
    GXTexObj m_dirtTex;           /* 0x00010 I8 128x128 over m_dirtTexData */
    GXTexObj m_rippleTex;         /* 0x00030 IA8 16x32 over m_rippleTexData (indirect warp) */
    ANIMDATA* m_anim;             /* 0x00050 0x590005; never locked or killed (retail R2) */
    float m_dirt[128][128] ATTRIBUTE_ALIGN(32); /* 0x00060 [z][x] 0..255; dirty when >= m_threshold */
    u8 m_dirtTexData[0x4000] ATTRIBUTE_ALIGN(32); /* 0x10060 I8 tiles 8x4 */
    u8 m_rippleTexData[0x400] ATTRIBUTE_ALIGN(32); /* 0x14060 IA8 tiles 4x4 */
    s32 m_total;                  /* 0x14460 0x4000 texels */
    float m_threshold;            /* 0x14464 16.0f (also the alpha-compare ref) */
    bool m_painted;               /* 0x14468 painted since the last phase-0 tick (scrub SE) */
    s32 m_dirtyCount;             /* 0x1446C texels >= m_threshold */
    float m_minX;                 /* 0x14470 */
    float m_maxX;                 /* 0x14474 */
    float m_minZ;                 /* 0x14478 */
    float m_maxZ;                 /* 0x1447C */
    Vec m_center;                 /* 0x14480 the quad grows from here (setCenter) */
    float m_grow;                 /* 0x1448C 0..1 (setGrow) */
    std::vector<float> m_brush;   /* 0x14490 radial brush, m_brushW x m_brushH */
    float m_brushSize;            /* 0x1449C 65.0f; brush cache key */
    int m_brushW;                 /* 0x144A0 even */
    int m_brushH;                 /* 0x144A4 */
    float m_scrollU;              /* 0x144A8 ripple scroll [0,1) */
    float m_scrollV;              /* 0x144AC */
    s32 m_seNo;                   /* 0x144B0 minX < 0 ? 0x7A8 : 0x7A9 */
    s32 m_seHandle;               /* 0x144B4 -1 */
    s32 m_phase;                  /* 0x144B8 0..5 (team 1 starts at 5) */
    s32 m_frame;                  /* 0x144BC */

    CCleanEff(Process_s* om, float minX, float maxX, float minZ, float maxZ); /* fn_1_DB1C */
    virtual ~CCleanEff();                           /* fn_1_DF34 */
    void initDirt();                                /* fn_1_E010 */
    void initRipple();                              /* fn_1_E31C */
    void loadAnim();                                /* fn_1_E560 */
    static int ConvTileI8(u8*& dst, const float* src, int stride, int threshold); /* fn_1_E5A4 dead */
    void updateTexture();                           /* fn_1_E694 dead (inlined in on_update) */
    int toTexel(const Vec* p, int* tx, int* tz);    /* fn_1_E800 dead; 1 = was outside (clamped) */
    void makeBrush(float size);                     /* fn_1_E9C8 */
    void paint(const Vec* pos, float size, float amount); /* fn_1_EE68 */
    void soil(const Vec* pos, float size);          /* fn_1_F624 paint +32, dead */
    void clean(const Vec* pos, float size);         /* fn_1_F668 paint -160 (flow mode 3) */
    void setCenter(const Vec* p);                   /* fn_1_F6AC (object.cpp) */
    void setGrow(float t);                          /* fn_1_F6D4 clamp 0..1 */
    float ratio();                                  /* fn_1_F744 1 - dirty/total */
    float ratioInRect(const Vec* a, const Vec* b);  /* fn_1_F7BC (player.cpp COM) */
    void erode();                                   /* fn_1_FDC8 dead (inlined) */
    void updateScroll();                            /* fn_1_100CC dead (inlined) */
    void startSound();                              /* fn_1_10294 dead (inlined) */
    void stopSound();                               /* fn_1_102E0 */
    virtual void on_update();                       /* fn_1_10330 */
    virtual void draw(Mtx* mtx);                    /* fn_1_109C0 */
};

class CCleanEffMan : public CSingleton<CCleanEffMan> {
public:
    CCleanEffMan(Process_s* om);      /* fn_1_D62C */
    ~CCleanEffMan();                  /* fn_1_D8F8 (flow ~CFlow) */
    int judge(bool timeUp);           /* fn_1_DA00 0/1 = that team wins, 2 = neither */
    CCleanEff* get(int team);         /* fn_1_DAEC */

    std::auto_ptr<CCleanEff> m_eff0;  /* 0x0 team 0 */
    std::auto_ptr<CCleanEff> m_eff1;  /* 0x4 team 1 */
};

} // namespace m531

#ifndef __MWERKS__
template <> m531::CCleanEffMan* CSingleton<m531::CCleanEffMan>::ms_pointer; /* defined in flow.cpp */
#endif

#endif
