/* joint.cpp -- m501::CJoint: a matrix hierarchy node (each player's cone joint, one per scoop).
 * getMatrix() returns the cached world matrix, recomputing it up the m_super chain when dirty.
 * The two asserts must stay on their retail lines (78 and 95): __LINE__ is part of the code.
 *
 * A joint links to its parent (m_super), to its first child (m_child) and to its siblings through a
 * circular ring (m_next/m_prev, self-linked when alone). m_dirty marks the cached world matrix stale;
 * lockMatrixChain() marks a whole subtree. Nothing here is virtual. */
#include "REL/m501Dll/joint.h"
#include "REL/mgcpp/assert.h"

namespace m501 {

CJoint::CJoint()
{
    PSMTXIdentity(m_local);
    m_super = NULL;
    m_next = this;
    m_prev = this;
    m_child = NULL;
    m_dirty = 1;
}

CJoint::~CJoint()
{
    resetSuperJoint();
    CJoint* c = m_child;
    if (c != NULL) {
        CJoint* first = c;
        do {
            CJoint* next = c->m_next;
            c->m_next = c;
            c->m_prev = c;
            c->m_super = NULL;
            c = next;
        } while (c != first);
    }
}

Mtx* CJoint::getMatrix()
{
    if (m_dirty) {
        m_dirty = 0;
        if (m_super == NULL || m_super == this) {
            PSMTXCopy(m_local, m_world);
        } else {
            Mtx* super = m_super->getMatrix();
            PSMTXConcat(*super, m_local, m_world);
        }
    }
    return &m_world;
}

/* Marks this joint and every descendant dirty. CW inlines the recursion 7 levels deep (and getMatrix's 8):
 * the source form -- the lockMatrix() call, the `first` local, getMatrix's `super` temporary -- decides
 * that depth and the stack round trips, so keep it. lockMatrix() is the in-class inline of joint.h; its
 * out-of-line copy is emitted here because the deepest level calls it.
 */
void CJoint::lockMatrixChain()
{
    lockMatrix();
    CJoint* c = m_child;
    if (c != NULL) {
        CJoint* first = c;
        do {
            c->lockMatrixChain();
            c = c->m_next;
        } while (c != first);
    }
}

void CJoint::setSuper(CJoint* super)
{
    if (super == NULL) {
        assert(m_super != NULL);
        Mtx* world = super->getMatrix();
        PSMTXConcat(*world, m_local, m_local);
        resetSuperJoint();
    } else {
        Mtx inv;
        Mtx* world = super->getMatrix();
        PSMTXInverse(*world, inv);
        PSMTXConcat(inv, m_local, m_local);
        setSuperJoint(super);
    }
}

void CJoint::setSuperJoint(CJoint* super)
{
    assert(m_super == NULL);
    m_super = super;
    CJoint* c = super->m_child;
    if (c != NULL) {
        m_prev = c;
        m_next = c->m_next;
        c->m_next->m_prev = this;
        c->m_next = this;
    } else {
        super->m_child = this;
    }
}

/* unlinks this joint from its parent; the parent's first child becomes this joint's next sibling */
void CJoint::resetSuperJoint()
{
    CJoint* next = NULL;
    if (m_next != this) {
        next = m_next;
        m_next->m_prev = m_prev;
        m_prev->m_next = m_next;
        m_next = this;
        m_prev = this;
    }
    if (m_super != NULL) {
        m_super->m_child = next;
        m_super = NULL;
    }
}

} // namespace m501
