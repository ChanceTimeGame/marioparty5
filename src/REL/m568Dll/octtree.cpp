#include "REL/m568Dll/octtree.h"
#include "REL/m568Dll/stage.h"
#include "REL/m568Dll/tube.h"

namespace m568 {

/* lbl_1_rodata_3F0: the obstacle models by kind */
static const u32 s_obstacleModel[2] = { 0x7B0004, 0x7B0005 };

/* retail reaches the stage's collision interface through an inline taking it by reference (no null check on the
 * base conversion, the result copied once more: lead relay, F2's proof in tube.cpp) */
inline const Vec* ObstacleGroundNormal(ICollision& col)
{
    return col.GetNormal();
}

/* retail builds m_sphere in the member-init list (pos copied as words, then r, BEFORE the model ctor): mgcpp's
 * CSphere is an aggregate with no ctor, so the body assigns them (masked residue, OUT.md). The stage singleton is
 * read before the snap; the model is placed at the UNSNAPPED `pos` (retail passes the parameter, not m_sphere.pos). */
CObstacle::CObstacle(int kind, const Vec* pos) : m_model(s_obstacleModel[kind])
{
    m_sphere.pos = *pos;
    m_sphere.r = 100.0f;
    m_hit = false;
    m_se = kind == 0 ? 0x90A : 0x90B;
    CStage* stage = CStage::GetInstance();
    CStage::SnapToGround(&m_sphere.pos);
    const Vec* n = ObstacleGroundNormal(*stage);
    m_normal = *n;
    insertBack(ASet<CObstacle>::instance());
    m_model.setPos(const_cast<Vec*>(pos));
    m_model.setAttr(HU3D_MOTATTR_SHAPE_PAUSE);
}

void CObstacle::Hit(CTube* t)
{
    if (!IsHit() && t->IsSolo()) {
        m_model.resetAttr(HU3D_MOTATTR_SHAPE_PAUSE);
        CStage::SetSePos(&m_sphere.pos, HuAudFXPlay(m_se));
        m_hit = true;
    }
}

void RelocateOctree(OctNode* nodes, int count)
{
    OctNode* n = nodes;
    OctNode* end = nodes + count;
    for (; n != end; n++) {
        for (int i = 0; i < 8; i++) {
            if ((u32)n->child[i] == 0xFFFFFFFF) {
                n->child[i] = NULL;
            } else {
                n->child[i] = &nodes[(u32)n->child[i]];
            }
        }
    }
}

bool AABB::Contains(float x, float y, float z)
{
    if (min.x > x) {
        return false;
    }
    if (min.y > y) {
        return false;
    }
    if (min.z > z) {
        return false;
    }
    if (max.x < x) {
        return false;
    }
    if (max.y < y) {
        return false;
    }
    if (max.z < z) {
        return false;
    }
    return true;
}

OctNode* FindLeaf(OctNode* p, float x, float y, float z)
{
    if (!p->box.Contains(x, y, z)) {
        return NULL;
    }
    while (p->child[0]) {
        OctNode* parent = p;
        for (int i = 0; i < 8; i++) {
            OctNode* c = p->child[i];
            if (c->box.Contains(x, y, z)) {
                p = c;
                break;
            }
        }
        /* retail's octtree.cpp:86 (the file above is longer than retail's: host blocks, comments) */
#line 86
        assert(p != parent);
    }
    return p;
}

} // namespace m568
