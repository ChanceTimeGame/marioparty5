#ifndef M568_OCTTREE_H
#define M568_OCTTREE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/om.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"
#include "REL/m568Dll/a_set.h"

namespace m568 {

class CTube;

/* an axis-aligned box: min +0, max +0xC (0x18). fn_1_FAB0 Contains is unreferenced; FindLeaf inlines the test. */
struct AABB {
    bool Contains(float x, float y, float z); /* fn_1_FAB0 inclusive */

    Vec min; /* 0x00 */
    Vec max; /* 0x0C */
};

/* a mesh triangle: three vertex indices and a debug colour index (DrawOctNode's rodata_368[attr]) */
struct Tri {
    u16 v[3]; /* 0x0 */
    u16 attr; /* 0x6 */
};

/* the octree node as FindLeaf / RayNode read it: `first` indexes TriIdxTable, `count` triangles; a leaf has
 * child[0] == NULL. GC 0x40. */
struct OctNode {
    u32 first;          /* 0x00 */
    s32 count;          /* 0x04 */
    AABB box;           /* 0x08 */
    OctNode* child[8];  /* 0x20 CW: relocated in place from u32 indices */
};

/* fn_1_FA10: child[i] = (index == -1) ? NULL : &nodes[index], in place */
void RelocateOctree(OctNode* nodes, int count);
OctNode* FindLeaf(OctNode* root, float x, float y, float z);

/* An obstacle on the course (name ours): a sphere of radius 100 with model 0x7B0004 (kind 0) / 0x7B0005 (kind 1),
 * snapped to the ground; the first touch by the SOLO tube plays its SE once and releases the model's shape pause.
 * GC: TLinkItem<CObstacle> +0 (on ASet<CObstacle>, bss 9F4), m_sphere +0x08, m_model +0x18 (2 + pad),
 * m_normal +0x1C, m_hit +0x28, m_se +0x2C; size 0x30 (stage `li r3,0x30`). No vptr. The dtor is the implicit
 * inline one (game_master's ~CObjSet inlines it: ~CModel(+0x18), ~CLinkNode). */
class CObstacle : public TLinkItem<CObstacle> {
public:
    CObstacle(int kind, const Vec* pos); /* fn_1_F7A0 */
    void Hit(CTube* t);                  /* fn_1_F990 from game_master HitTubeOct */
    /* inline accessors (retail reads +0x28 as `lbz; clrlwi` and takes the sphere through an inline return: tube
     * HitObstacle 140D8 (F2), input FindObstacle 6444 / avoidObstacle 6E94 (F4), Hit F990 (IsHit only)) */
    bool IsHit() const { return m_hit; }
    CSphere* GetSphere() { return &m_sphere; }             /* F2 (tube HitObstacle) */
    const CSphere* GetSphere() const { return &m_sphere; } /* F4 (input FindObstacle / avoidObstacle) */

    CSphere m_sphere; /* 0x08 pos = *pos snapped to the ground, r = 100 */
    CModel m_model;   /* 0x18 */
    Vec m_normal;     /* 0x1C the ground normal under it (CStage::GetNormal after the snap) */
    bool m_hit;       /* 0x28 */
    int m_se;         /* 0x2C kind 0: 0x90A, kind 1: 0x90B */
};

} // namespace m568

#ifndef __MWERKS__
template <> ASet<m568::CObstacle>* ASet<m568::CObstacle>::sm_ptr; /* defined in input.cpp */
#endif

#endif
