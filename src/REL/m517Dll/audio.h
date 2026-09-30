#ifndef M517_AUDIO_H
#define M517_AUDIO_H

#include "REL/mgcpp/game.h"

namespace m517 {

void GetScreenPos(const Vec& pos, s16 camBit, Vec* out); /* fn_1_1B48C unreferenced (inlined in the three below) */
int PlaySe(int seNo, Vec pos);                           /* fn_1_1B6EC choro, effect, papereff */
void SetVoicePan(s16 charNo, Vec pos);                   /* fn_1_1B9B8 player update (every frame) */
void SetSePan(int handle, Vec pos);                      /* fn_1_1BC6C effect CBall::Update (every frame) */

} // namespace m517

#endif
