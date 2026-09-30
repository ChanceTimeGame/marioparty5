#include "REL/m531Dll/audio.h"

namespace m531 {

void GetScreenPos(const Vec& pos, s16 camBit, Vec* out)
{
    s16 i;
    HU3DCAMERA* cam;
    Mtx lookAt;
    Vec view;
    float w;
    float h;

    for (i = 0; i < 16; i++) {
        if (camBit & (1 << i)) {
            break;
        }
    }
    cam = &Hu3DCamera[i];
    C_MTXLookAt(lookAt, &cam->pos, &cam->up, &cam->target);
    PSMTXMultVec(lookAt, &pos, &view);
    w = 1.2f * (view.z * (sin(M_PI * (cam->fov / 2.0f) / 180.0) / cos(M_PI * (cam->fov / 2.0f) / 180.0)));
    h = view.z * (sin(M_PI * (cam->fov / 2.0f) / 180.0) / cos(M_PI * (cam->fov / 2.0f) / 180.0));
    out->x = 288.0f + view.x * (288.0f / -w);
    out->y = 240.0f + view.y * (240.0f / h);
    out->z = 0.0f;
}


int PlaySEPan(int seNo, Vec pos)
{
    Vec out;
    float sx;
    s16 pan;
    int h;

    GetScreenPos(pos, 1, &out);
    sx = out.x / 640.0f;
    pan = 48.0f + 32.0f * sx;
    h = HuAudFXPlay(seNo);
    HuAudFXPanning(h, pan);
    return h;
}

void SetVoicePan(s16 charNo, Vec pos)
{
    Vec out;
    float sx;
    s16 pan;

    GetScreenPos(pos, 1, &out);
    sx = out.x / 640.0f;
    pan = 48.0f + 32.0f * sx;
    CharModelVoicePanSet(charNo, pan);
}

void SetSEPan(int seHandle, Vec pos)
{
    Vec out;
    float sx;
    s16 pan;

    GetScreenPos(pos, 1, &out);
    sx = out.x / 640.0f;
    pan = 48.0f + 32.0f * sx;
    HuAudFXPanning(seHandle, pan);
}

} // namespace m531
