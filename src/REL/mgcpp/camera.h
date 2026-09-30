/* camera.h -- CCamera (a look-at camera) and CCameraView (position + orientation), camera.cpp.
 * No virtuals. GC sizes: CCamera 0x24, CCameraView 0x1C. */
#ifndef MGCPP_CAMERA_H
#define MGCPP_CAMERA_H

#include "REL/mgcpp/game.h"

class CCameraView {
public:
    Vec pos;        /* 0x00 */
    Quaternion rot; /* 0x0C */
};

class CCamera {
public:
    void rotateCamera(float a, float b);
    void rotateCameraUp(float deg);
    void getLookAtVec(Vec* x, Vec* y, Vec* z);
    void getLookAtMtxInverse(Mtx* m);
    void applyOffsetLocal(Vec* v);
    void applyOffset(Vec* v);
    void resetLookAt();
    void setView(CCameraView* v);
    void getView(CCameraView* v);
    void lerpView(CCameraView* a, CCameraView* b, float t);
    void getOffset(Vec* p);
    /* retail symbol getOffsetTo__7CCameraFP3VecP3Vec has no float, but the body reads f1 (map.m501.txt) */
    void getOffsetTo(Vec* a, Vec* b, float t);
    void setPos(u16 camBit);
    void getPos(u16 camBit);
    void printView();
    static float GetStickX(int pad);
    static float GetStickY(int pad);
    static float GetSubStickX(int pad);
    static float GetSubStickY(int pad);
    void debugView(int pad);

    Vec m_pos;    /* 0x00 eye */
    Vec m_up;     /* 0x0C */
    Vec m_target; /* 0x18 look-at point */
};

#endif
