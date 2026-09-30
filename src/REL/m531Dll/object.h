/* object.h -- the stage props (object.cpp; names ours, the flow sheet's):
 *   CStageObjects 0x40, no base/vtable: owns 2 plain CStage models (0x590000 shadow-map floor, 0x590001), the CSpray,
 *                 8 CDrift and 5 CProp; built by CFlow::mode0, deleted by ~CFlow (non-virtual dtor).
 *   CDrift  : CStage 0x34  drifting background model 0x59000A (vtable data_314 {update 8FA0, ~ 7F94})
 *   CGuruguru : CStage 0x60  the guide's two swirl items (created by player.cpp CRunner): appear, drive team 0's
 *                 layer centre/grow while active, pop animation (vtable data_324 {update 8750, ~ 9064})
 *   CProp   : CStage 0x38  decorated prop 0x590011 with a hooked model (vtable data_334 {CStage::on_update 90C8,
 *                 ~ 7FF8} + pad)
 * .data: the drift positions (1D0), the prop table (230), motion kinds (2A8), slow flags (2BC), the strings,
 * the three vtables (reverse class order: 314 CDrift, 324 CGuruguru, 334 CProp). */
#ifndef M531_OBJECT_H
#define M531_OBJECT_H

#include "REL/m531Dll/stage.h"

namespace m531 {

class CSpray;

class CDrift : public CStage {
public:
    CDrift(Process_s* om, const Vec* pos); /* fn_1_8E88 random scale 0.5..1 */
    virtual void on_update();              /* fn_1_8FA0 x += 1/3, wraps at 1200 */
    /* ~CDrift fn_1_7F94: implicit */
};

class CGuruguru : public CStage {
public:
    int m_state;        /* 0x34 0 hidden, 1 active, 2 pop anim, 3 done */
    Vec m_animScale;    /* 0x38 */
    Vec m_basePos;      /* 0x44 */
    int m_count;        /* 0x50 frames */
    int m_index;        /* 0x54 ctor param; only index 0 drives the layer */
    int m_popSub;       /* 0x58 */
    u8 m_sePlayed;      /* 0x5C */

    CGuruguru(Process_s* om, u32 dataNum, int index); /* fn_1_805C (player.cpp B63C) */
    void syncModel();          /* fn_1_8124 unreferenced (inlined at the top of on_update) */
    void appear();             /* fn_1_8190 (player.cpp CRunner) */
    void updateActive();       /* fn_1_81F4 unreferenced (inlined: on_update case 1) */
    void updatePop();          /* fn_1_8410 unreferenced (inlined: on_update case 2) */
    virtual void on_update();  /* fn_1_8750 */
    virtual ~CGuruguru();      /* fn_1_9064 */
};

class CProp : public CStage {
public:
    s16 m_hookModel;    /* 0x34 0x590010 hooked on "g003m2-itemhook_R"; never killed (retail) */

    CProp(Process_s* om, int i, int motKind, Vec pos, Vec rot, u8 slow); /* fn_1_8CD4 (i unused) */
    /* ~CProp fn_1_7FF8: implicit */
};

class CStageObjects {
public:
    CStageObjects(Process_s* om);  /* fn_1_7BB0 */
    ~CStageObjects();              /* fn_1_7E40 */

    CStage* m_base0;      /* 0x00 0x590000 (Hu3DModelShadowMapSet) */
    CStage* m_base1;      /* 0x04 0x590001 */
    CSpray* m_spray;      /* 0x08 */
    CDrift* m_drift[8];   /* 0x0C */
    CProp* m_prop[5];     /* 0x2C */
};

} // namespace m531

#endif
