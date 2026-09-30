#include "REL/m513Dll/audio.h"

namespace m513 {

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


/* pan, then the volume by the distance to camera 0 (the by-value pos is
 * reused as the difference: retail) */
int PlaySe(int seNo, Vec pos)
{
    HU3DCAMERA* cam = &Hu3DCamera[0];
    Vec out;
    float sx;
    s16 pan;
    int h;

    GetScreenPos(pos, 1, &out);
    sx = out.x / 640.0f;
    pan = 32.0f + 64.0f * sx;
    PSVECSubtract(&pos, &cam->pos, &pos);
    float d = PSVECMag(&pos);
    float t = (3000.0f - d) / 3000.0f;
    s16 vol = 0;
    if (t > 0.0f) {
        vol = 104.0f + 23.0f * t;
    }
    h = HuAudFXPlay(seNo);
    HuAudFXPanning(h, pan);
    HuAudFXVolSet(h, vol);
    return h;
}

void SetVoicePan(s16 charNo, Vec pos)
{
    Vec out;
    float sx;
    s16 pan;

    GetScreenPos(pos, 1, &out);
    sx = out.x / 640.0f;
    pan = 32.0f + 64.0f * sx;
    CharModelVoicePanSet(charNo, pan);
}

} // namespace m513
