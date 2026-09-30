#include "REL/m579Dll/fishline.h"

namespace m579 {

/* g per frame^2 (rodata_188) */
#define FISH_G 0.27240694444444447

/* Vec setter with DOUBLE components (m509 player.h's SetVec: the frsp per component) */
static inline void SetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

/* component copy through an inline (updateRope's `old`) */
static inline void CopyVec(Vec* d, const Vec* s)
{
    d->x = s->x;
    d->y = s->y;
    d->z = s->z;
}

/* fn_1_7B4C: hook straight down at the line length, the nodes spaced len/30 (the constraints use len/29: retail) */
void CFishLine::initRope()
{
    SetVec(&m_hookVel, 0.0f, 0.0f, 0.0f);
    SetVec(&m_hook, 0.0f, -m_length, 0.0f);
    for (int i = 0; i < NUM_NODE; i++) {
        m_under[i] = 0;
        SetVec(&m_nodeVel[i], 0.0f, 0.0f, 0.0f);
        SetVec(&m_node[i], 0.0f, -i * (m_length / 30.0f), 0.0f);
    }
}

#ifdef __MWERKS__
/* retail inlines MSL's double sqrt (frsqrte + four Newton steps, 0 / NaN / Inf cases): m536 camera's form */
inline double MslSqrt(double x)
{
    if (x > 0.0) {
        double guess = __frsqrte(x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        return x * guess;
    } else if (x == 0.0) {
        return 0;
    } else if (x) {
        return *(float*)__float_nan;
    }
    return *(float*)__float_huge;
}
#else
inline double MslSqrt(double x) { return sqrt(x); }
#endif

/* fn_1_7CD8: move the hook by the tip shift, gravity, clamp it to the line length (true = clamped); the velocity is
 * damped twice (0.99, then 0.9 under water / 0.99 again: retail) */
bool CFishLine::updateHook(Vec* shift)
{
    bool hit = false;
    PSVECSubtract(&m_hook, shift, &m_hook);
    Vec old;
    old.x = m_hook.x;
    old.y = m_hook.y;
    old.z = m_hook.z;
    m_hookVel.y = m_hookVel.y - FISH_G;
    PSVECAdd(&m_hookVel, &m_hook, &m_hook);
    float x = m_hook.x;
    float y = m_hook.y;
    float z = m_hook.z;
    float r = MslSqrt(x * x + y * y + z * z);
    float len = m_length;
    if (r > len) {
        x = len * (x / r);
        y = len * (y / r);
        z = len * (z / r);
        m_hook.x = x;
        m_hook.y = y;
        m_hook.z = z;
        hit = true;
    }
    PSVECSubtract(&m_hook, &old, &m_hookVel);
    PSVECScale(&m_hookVel, &m_hookVel, 0.99f);
    if (m_under[NUM_NODE - 1]) {
        PSVECScale(&m_hookVel, &m_hookVel, 0.9f);
    } else {
        PSVECScale(&m_hookVel, &m_hookVel, 0.99f);
    }
    return hit;
}

/* fn_1_805C unreferenced (inlined in updateRope): node i follows the tip shift (weight t) and the hook velocity
 * (weight (int)(1 - t)), with gravity */
void CFishLine::moveNode(int i, Vec* v, float t)
{
    Vec a;
    Vec b;
    Vec c;
    int k = 1.0 - t;
    PSVECScale(v, &a, t);
    float s = k; /* a temporary: retail's inlined copy (updateRope) converts k before the call's arguments */
    PSVECScale(&m_hookVel, &b, s);
    PSVECAdd(&a, &b, &c);
    c.y = c.y - FISH_G;
    PSVECAdd(&m_nodeVel[i], &c, &m_nodeVel[i]);
    PSVECAdd(&m_nodeVel[i], &m_node[i], &m_node[i]);
}

/* fn_1_8180 unreferenced (inlined): nodes 1..27 pulled to within len/29 of the previous one (retail stops at 27) */
void CFishLine::relaxForward()
{
    int i;
    float seg = m_length / 29.0f;
    for (i = 1; i < 28; i++) {
        Vec d;
        Vec* p = &m_node[i];
        Vec* q = &m_node[i - 1];
        PSVECSubtract(p, q, &d);
        float len = PSVECMag(&d);
        if (len > seg) {
            len = seg / len;
            PSVECScale(&d, p, len);
            PSVECAdd(p, q, p);
        }
    }
}

/* fn_1_826C unreferenced (inlined): nodes 28..1 pulled to within len/29 of the next one */
void CFishLine::relaxBackward()
{
    int i;
    float seg = m_length / 29.0f;
    for (i = 28; i > 0; i--) {
        Vec d;
        Vec* p = &m_node[i];
        Vec* q = &m_node[i + 1];
        PSVECSubtract(p, q, &d);
        float len = PSVECMag(&d);
        if (len > seg) {
            len = seg / len;
            PSVECScale(&d, p, len);
            PSVECAdd(p, q, p);
        }
    }
}

/* fn_1_8358 unreferenced (inlined): node 0 at the tip, node 29 at the hook, the rest inside both reach spheres.
 * Retail's first constraint scales the stack Vec d before anything wrote it (8438 / 8810): the node is unchanged */
void CFishLine::constrainNodes()
{
    int i;
    Vec d;
    SetVec(&m_node[0], 0.0f, 0.0f, 0.0f);
    m_node[NUM_NODE - 1] = m_hook;
    for (i = 1; i < NUM_NODE - 1; i++) {
        float t = i / 29.0f;
        Vec* p = &m_node[i];
        float lim = m_length * t;
        float len = PSVECMag(p);
        if (len > lim) {
            len = lim / len;
            PSVECScale(&d, &d, len); /* retail: dead (d uninitialised on the first pass) */
        }
        lim = m_length * (1.0f - t);
        PSVECSubtract(p, &m_hook, &d);
        len = PSVECMag(&d);
        if (len > lim) {
            len = lim / len;
            PSVECScale(&d, p, len);
            PSVECAdd(p, &m_hook, p);
        }
    }
}

/* fn_1_84EC: integrate every node (held: snap to hook * w), then (free) constrain and relax both ways, then damp
 * (0.7 under water, else 0.8). `int w = i / 29.0f` is 0 for i < 29 (retail) */
void CFishLine::updateRope(Vec* shift, bool held)
{
    int i;
    int j;
    for (i = 0; i < NUM_NODE; i++) {
        Vec old;
        CopyVec(&old, &m_node[i]);
        int w = i / 29.0f;
        if (held) {
            PSVECScale(&m_hook, &m_node[i], w);
            PSVECSubtract(&m_node[i], &old, &m_nodeVel[i]);
        } else {
            moveNode(i, shift, w);
        }
    }
    if (!held) {
        constrainNodes();
        relaxBackward();
        relaxForward();
    }
    for (j = 0; j < NUM_NODE; j++) {
        if (m_under[j]) {
            PSVECScale(&m_nodeVel[j], &m_nodeVel[j], 0.7f);
        } else {
            PSVECScale(&m_nodeVel[j], &m_nodeVel[j], 0.8f);
        }
    }
}

} // namespace m579
