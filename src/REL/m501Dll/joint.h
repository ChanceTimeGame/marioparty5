/* joint.h -- m501::CJoint (joint.cpp): a matrix hierarchy node (the cone joint of each player, one per
 * scoop). getMatrix() returns the cached world matrix, recomputing it up the m_super chain when dirty.
 * GC size 0x74. No virtuals. */
#ifndef M501_JOINT_H
#define M501_JOINT_H

#include "REL/mgcpp/game.h"

namespace m501 {

class CJoint {
public:
    CJoint();
    ~CJoint();
    Mtx* getMatrix();
    void lockMatrixChain();
    /* inline: retail inlines it into lockMatrixChain (7 levels) and aisu.cpp; joint.o carries the one
     * out-of-line copy, after lockMatrixChain, where the 8th recursion level calls it */
    void lockMatrix() { m_dirty = 1; }
    void setSuper(CJoint* super);
    void setSuperJoint(CJoint* super);
    void resetSuperJoint();

    /* the local matrix, as aisu.cpp uses it (W0 aisu Q4). Two inline levels with a pointer conversion
     * between them: that is what gives retail's `addi rA,aisu,0x50; mr rB,rA; mr rC,rB` (aisu 7890, 8150);
     * a single accessor, with or without a cast, is one copy short (fork C, tested). */
    Mtx* getLocalPtr() { return &m_local; }
    MtxPtr getLocal() { return (MtxPtr)getLocalPtr(); }

    /* marks the joint dirty and hands out its local matrix for writing, in one inline (player shrinkCone
     * CF54..CF64: the stb 0x70 and the three-register reference chain come from the same inline; fork A). It
     * may be retail's lockMatrix() itself returning Mtx&; the merge decides. */
    Mtx& lockLocal()
    {
        m_dirty = 1;
        return m_local;
    }

    Mtx m_local;      /* 0x00 */
    Mtx m_world;      /* 0x30 cached; getMatrix() returns &m_world */
    CJoint* m_super;  /* 0x60 parent */
    CJoint* m_child;  /* 0x64 first child, NULL if none */
    CJoint* m_next;   /* 0x68 sibling ring (self-linked when alone) */
    CJoint* m_prev;   /* 0x6C */
    u8 m_dirty;       /* 0x70 */
};

} // namespace m501

#endif
