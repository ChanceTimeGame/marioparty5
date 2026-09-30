/* camera.cpp -- CCamera: a look-at camera (eye m_pos, m_up, look-at point m_target) with helpers to
 * rotate/move it, convert to and from a CCameraView (position + quaternion), and a pad-driven debug mode. */
#include "REL/mgcpp/camera.h"
#ifndef MGCPP_CAMERA_DEBUG_ONLY /* knob (m509): everything up to the debug camera; see line 171 */
/* pitch about the camera's own x axis by a degrees, then yaw about world Y by b degrees; keeps the eye */
void CCamera::rotateCamera(float a, float b)
{
    Vec x, y, z;
    Mtx rotAxis, rotY, m;

    getLookAtVec(&x, &y, &z);
    MTXRotAxisRad(rotAxis, &x, MTXDegToRad(a));
    MTXRotRad(rotY, 'Y', MTXDegToRad(b));
    MTXConcat(rotAxis, rotY, m);
    MTXMultVecSR(m, &z, &z);
    MTXMultVecSR(m, &y, &m_up);
    VECSubtract(&m_pos, &z, &m_target);
}

/* rolls the up vector about the view direction by deg degrees */
void CCamera::rotateCameraUp(float deg)
{
    Vec dir;
    Mtx m;

    VECSubtract(&m_target, &m_pos, &dir);
    MTXRotAxisRad(m, &dir, MTXDegToRad(deg));
    MTXMultVec(m, &m_up, &m_up);
}

/* the look-at matrix rows: x = right, y = up, z = backwards (towards the eye) */
void CCamera::getLookAtVec(Vec* x, Vec* y, Vec* z)
{
    Mtx m;

    MTXLookAt(m, &m_pos, &m_up, &m_target);
    x->x = m[0][0];
    x->y = m[0][1];
    x->z = m[0][2];
    y->x = m[1][0];
    y->y = m[1][1];
    y->z = m[1][2];
    z->x = m[2][0];
    z->y = m[2][1];
    z->z = m[2][2];
}

/* camera space -> world space */
void CCamera::getLookAtMtxInverse(Mtx* m)
{
    MTXLookAt(*m, &m_pos, &m_up, &m_target);
    MTXInverse(*m, *m);
}

/* moves eye and target by v given in camera space */
void CCamera::applyOffsetLocal(Vec* v)
{
    Vec ofs;
    Mtx m;

    getLookAtMtxInverse(&m);
    MTXMultVecSR(m, v, &ofs);
    applyOffset(&ofs);
}

/* moves eye and target by v (world space) */
void CCamera::applyOffset(Vec* v)
{
    VECAdd(v, &m_target, &m_target);
    VECAdd(v, &m_pos, &m_pos);
}

void CCamera::resetLookAt()
{
    m_up.x = 0.0f;
    m_up.y = 1.0f;
    m_up.z = 0.0f;
    m_pos.x = 0.0f;
    m_pos.y = 0.0f;
    m_pos.z = 5000.0f;
    m_target.x = 0.0f;
    m_target.y = 0.0f;
    m_target.z = 0.0f;
}

void CCamera::setView(CCameraView* v)
{
    Mtx m;

    MTXQuat(m, &v->rot);
    m_up.x = m[0][1];
    m_up.y = m[1][1];
    m_up.z = m[2][1];
    m_pos.x = v->pos.x;
    m_pos.y = v->pos.y;
    m_pos.z = v->pos.z;
    m_target.x = v->pos.x - m[0][2];
    m_target.y = v->pos.y - m[1][2];
    m_target.z = v->pos.z - m[2][2];
}

void CCamera::getView(CCameraView* v)
{
    Mtx m;

    getLookAtMtxInverse(&m);
    v->pos.x = m_pos.x;
    v->pos.y = m_pos.y;
    v->pos.z = m_pos.z;
    QUATMtx(&v->rot, m);
}

/* slerps the orientation and lerps the position from a (t = 0) to b (t = 1) */
void CCamera::lerpView(CCameraView* a, CCameraView* b, float t)
{
    Vec pa, pb;
    CCameraView v;

    QUATSlerp(&a->rot, &b->rot, &v.rot, t);
    VECScale(&a->pos, &pa, 1.0f - t);
    VECScale(&b->pos, &pb, t);
    VECAdd(&pa, &pb, &v.pos);
    setView(&v);
}

/* moves the eye to p and the target with it (keeps the view direction; retail name) */
void CCamera::getOffset(Vec* p)
{
    Vec d;

    VECSubtract(p, &m_pos, &d);
    m_pos.x = p->x;
    m_pos.y = p->y;
    m_pos.z = p->z;
    VECAdd(&m_target, &d, &m_target);
}

/* getOffset to the point a + (b - a) * t */
void CCamera::getOffsetTo(Vec* a, Vec* b, float t)
{
    Vec pa, p;

    VECScale(a, &pa, 1.0f - t);
    VECScale(b, &p, t);
    VECAdd(&pa, &p, &p);
    getOffset(&p);
}

void CCamera::setPos(u16 camBit)
{
    Hu3DCameraPosSetV(camBit, &m_pos, &m_up, &m_target);
}

void CCamera::getPos(u16 camBit)
{
    Hu3DCameraPosGet(camBit, &m_pos, &m_up, &m_target);
}

#define CAMERA_FBITS(f) (*(u32*)&(f))
#else /* MGCPP_CAMERA_DEBUG_ONLY (m509): its debug camera was a source file of its own, after timer.cpp. */
#line 173 "camera_debug.cpp" /* CW emits a TU's code and .data grouped by file: this name places it there */
#endif /* MGCPP_CAMERA_NO_DEBUG: m517 has no debug camera, m509 sets it for its first #include (plan Phase 4) */
#ifndef MGCPP_CAMERA_NO_DEBUG
/* prints the view as a C initialiser of raw float bits */
void CCamera::printView()
{
    CCameraView v;

    getView(&v);
    printf("{{0x%08x,0x%08x,0x%08x},{0x%08x,0x%08x,0x%08x,0x%08x}},\n", CAMERA_FBITS(v.pos.x),
           CAMERA_FBITS(v.pos.y), CAMERA_FBITS(v.pos.z), CAMERA_FBITS(v.rot.x), CAMERA_FBITS(v.rot.y),
           CAMERA_FBITS(v.rot.z), CAMERA_FBITS(v.rot.w));
}

float CCamera::GetStickX(int pad)
{
    return (1.0f / 56.0f) * HuPadStkX[pad];
}

float CCamera::GetStickY(int pad)
{
    return (1.0f / 56.0f) * HuPadStkY[pad];
}

float CCamera::GetSubStickX(int pad)
{
    return (1.0f / 59.0f) * HuPadSubStkX[pad];
}

float CCamera::GetSubStickY(int pad)
{
    return (1.0f / 59.0f) * HuPadSubStkY[pad];
}

/* free camera: stick rotates, d-pad/sub-stick move (B = fast), X/A dolly, Y resets up, B-down prints */
void CCamera::debugView(int pad)
{
    u32 btn = HuPadBtn[pad];
    float speed;
    bool fast;
    Mtx inv;
    Vec move;
    Vec dolly;
    float mag;

    if (btn & PAD_BUTTON_Y) {
        m_up.x = 0.0f;
        m_up.y = 1.0f;
        m_up.z = 0.0f;
    }
    rotateCamera(-4.0f * GetStickY(pad), -4.0f * GetStickX(pad));
    fast = btn & PAD_BUTTON_B;
    speed = fast ? 70.0f : 20.0f;
    getLookAtMtxInverse(&inv);
    move.x = speed * ((btn & PAD_BUTTON_RIGHT) != 0) - speed * ((btn & PAD_BUTTON_LEFT) != 0);
    move.y = speed * ((btn & PAD_BUTTON_UP) != 0) - speed * ((btn & PAD_BUTTON_DOWN) != 0);
    move.x += speed * GetSubStickX(pad);
    move.z = 0.0f;
    MTXMultVecSR(inv, &move, &move);
    move.y += speed * GetSubStickY(pad);
    applyOffset(&move);
    dolly.x = 0.0f;
    dolly.y = 0.0f;
    dolly.z = ((btn & PAD_BUTTON_X) != 0) - ((btn & PAD_BUTTON_A) != 0);
    MTXMultVecSR(inv, &dolly, &dolly);
    dolly.y = 0.0f;
    mag = VECMag(&dolly);
    if (mag > 1e-10f) {
        VECScale(&dolly, &dolly, speed / mag);
        applyOffset(&dolly);
    }
    if (HuPadBtnDown[pad] & PAD_BUTTON_B) {
        printView();
    }
}
#endif /* MGCPP_CAMERA_NO_DEBUG */
