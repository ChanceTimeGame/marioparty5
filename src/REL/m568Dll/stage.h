/* stage.h -- m568::CStage (stage.cpp): the course. The model 0x7B0000 (+0x7B0001; 0x7B0003 in mode 4), a global
 * infinite light, a shadow projector that follows the scroll, the collision mesh (a triangle octree from the
 * archive 0x7B0002) behind the ICollision interface, the 11 obstacles, the frame clock (the course scrolls toward
 * -z: GetScrollZ = 6000 - 1450 t), and the skiing Shy Guy prop (CHeiho, once the scroll passes -9000).
 * Static helpers used by the other units: GetGravityDir, GetGravity, ClampToCourse, GetNormPos, SnapToGround,
 * SetSePos (and GetScrollZ through the singleton). stage.cpp does not include minigame.h. Names are ours.
 *
 * GC: CGameObject +0x00 (vptr +8, m_execFlags +0xC), CSingleton<CStage> (empty) at +0x10, ICollision (vptr) at
 * +0x10; m_model +0x14, m_model2 +0x18, m_model3 +0x1C (never assigned), m_archive +0x20, m_heiho +0x24,
 * m_triTable +0x28, m_triCount +0x2C, m_vtxTable +0x30, m_vtxCount +0x34, m_octTable +0x38, m_triIdx +0x3C,
 * m_frame +0x40, m_state +0x44 (12-byte PTMF), m_hitPlane +0x50; size 0x60 (game_master `li r3,0x60`).
 * Vtable __vt__Q24m5686CStage (data_4F0, 0x34): {0, 0, ~, on_new_mode, on_update}, the ICollision-in-CStage part
 * {0, -0x10, thunk Raycast, thunk GetNormal, thunk Project}, then the appended overriders in CStage DECLARATION
 * order (m536 rule): Raycast, Project, GetNormal. ICollision's own table (data_524) {0,0,0,0,0} is emitted here.
 * CSingleton<CStage>::ms_pointer is input.o's .bss 9F0 (explicit specialisation at the end of input.cpp). */
#ifndef M568_STAGE_H
#define M568_STAGE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include "REL/m568Dll/archive.h"
#include "REL/m568Dll/heiho.h"
#include "REL/m568Dll/misc.h"
#include "REL/m568Dll/octtree.h"
#include <memory>

namespace m568 {

/* the collision interface (3 pure virtuals, no virtual dtor; name ours). Slot order +8 Raycast, +C GetNormal,
 * +10 Project. Callers: Raycast (tube x5, stage SnapToGround, camera), GetNormal (tube x4, octtree); Project is
 * never called. */
class ICollision {
public:
    /* the nearest hit of the segment from -> to into *out; true on a hit (the hit plane is then kept) */
    virtual bool Raycast(Vec* out, const Vec* from, const Vec* to) = 0;
    /* the normal of the last hit plane (shared by every caller: whoever raycast last) */
    virtual const Vec* GetNormal() = 0;
    /* out = p projected onto the last hit plane */
    virtual void Project(Vec* out, const Vec* p) = 0;
};

class CStage : public CGameObject, public CSingleton<CStage>, public ICollision {
public:
    typedef void (CStage::*StateFunc)();
    /* RayNode's walk state (a stack struct; HitTri keeps the nearest hit) */
    struct HitCtx {
        float best;      /* 0x00 the nearest hit's (negative) end distance */
        Tri* hit;        /* 0x04 */
        Vec* out;        /* 0x08 */
        const Vec* from; /* 0x0C */
        const Vec* to;   /* 0x10 */
    };

    static void GetGravityDir(Vec* out);                   /* fn_1_CE20 (0, -sin 60, -cos 60) */
    static void GetGravity(Vec* out, float mass);          /* fn_1_CE54 dir * (9.80665 * 100 * mass / 3600) */
    static void ClampToCourse(Vec* p, float r);            /* fn_1_CED4 x in [-800+r, 800-r], z in scroll window */
    static void GetNormPos(Vec* out, const Vec* p, float r); /* fn_1_D0A0 the position in [-1, 1] of the window */
    static void SetShadowReceiver(s16 id);                 /* fn_1_D21C (unreferenced; inlined 2x) */
    CStage();                                              /* fn_1_D260 */
    void stateNone();                                      /* fn_1_D68C the only state (data_474) */
    static bool SnapToGround(Vec* p);                      /* fn_1_D690 vertical ray 5000 -> -5000; y = 0 on a miss */
    /* fn_1_D7DC: `new CObstacle(kind, &pos[i])` for i < n (self-registering; `this` unused) */
    void CreateObstacles(int kind, const Vec* pos, int n);
    void LoadCollision();                                  /* fn_1_D85C */
    virtual void on_update();                              /* fn_1_D9F0 */
    void UpdateShadow();                                   /* fn_1_DB20 */
    virtual void on_new_mode(int mode);                    /* fn_1_DDA0 */
    float GetScrollZ();                                    /* fn_1_DEC0 6000 + 14.5 * (-100 * frame / 60) */
    void DrawOctNode(const OctNode* n);                    /* fn_1_DF80 debug (unreferenced): GX line strips */
    /* ICollision overriders, in retail DECLARATION order (the appended vtable block): Raycast, Project, GetNormal.
     * Bodies (.text): GetNormal E2FC, Raycast E304, RayNode, HitTri, Project E720. */
    virtual bool Raycast(Vec* out, const Vec* from, const Vec* to); /* fn_1_E304 */
    virtual void Project(Vec* out, const Vec* p);                   /* fn_1_E720 */
    virtual const Vec* GetNormal();                                 /* fn_1_E2FC */
    bool RayNode(Vec* out, const Vec* from, const Vec* to, OctNode* n); /* fn_1_E468 */
    static void HitTri(HitCtx* ctx, Tri* tri, Vec* a, Vec* b, Vec* c);  /* fn_1_E584 writes ms_pointer->m_hitPlane */
    static void SetSePos(const Vec* p, int se);
    virtual ~CStage();                                     /* fn_1_EBC0 */

    /* by value (retail copies the PTMF constant to a stack temporary first) */
    void setState(StateFunc s) { m_state = s; }

    std::auto_ptr<CModel> m_model;    /* 0x14 the course (0x7B0000; 0x7B0003 in mode 4) */
    std::auto_ptr<CModel> m_model2;   /* 0x18 0x7B0001 (reset in mode 4) */
    std::auto_ptr<CModel> m_model3;   /* 0x1C never assigned */
    std::auto_ptr<CArchive> m_archive; /* 0x20 the collision archive */
    std::auto_ptr<CHeiho> m_heiho;    /* 0x24 */
    Tri* m_triTable;                  /* 0x28 "TriangleTable" */
    s32 m_triCount;                   /* 0x2C *"TriangleCount" (never read on CW; the host swaps by it) */
    Vec* m_vtxTable;                  /* 0x30 "VertexTable" */
    s32 m_vtxCount;                   /* 0x34 *"VertexCount" (never read on CW; the host swaps by it) */
    OctNode* m_octTable;              /* 0x38 "OctTable" (host: the native copy, freed in ~CStage) */
    u16* m_triIdx;                    /* 0x3C "TriIdxTable" */
    int m_frame;                      /* 0x40 */
    StateFunc m_state;                /* 0x44 (12 bytes on CW) */
    Plane m_hitPlane;                 /* 0x50 the last hit's plane */
};

} // namespace m568

#ifndef __MWERKS__
template <> m568::CStage* CSingleton<m568::CStage>::ms_pointer; /* defined in input.cpp */
#endif

#endif
