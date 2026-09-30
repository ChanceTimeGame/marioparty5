#ifndef M531_AUDIO_H
#define M531_AUDIO_H

#include "REL/mgcpp/game.h"

namespace m531 {

void GetScreenPos(const Vec& pos, s16 camBit, Vec* out); /* fn_1_CB98 unreferenced (inlined into the three below);
                                                         * camBit 0 would index Hu3DCamera[16] (never passed) */
int PlaySEPan(int seNo, Vec pos);                 /* fn_1_CDF8 unreferenced */
void SetVoicePan(s16 charNo, Vec pos);            /* fn_1_D0C4 CharModelVoicePanSet */
void SetSEPan(int seHandle, Vec pos);             /* fn_1_D378 unreferenced */

} // namespace m531

#endif
