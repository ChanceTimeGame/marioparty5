#ifndef M513_AUDIO_H
#define M513_AUDIO_H

#include "REL/mgcpp/game.h"

namespace m513 {

void GetScreenPos(const Vec& pos, s16 camBit, Vec* out); /* fn_1_14348 unreferenced (inlined in the two below) */
int PlaySe(int seNo, Vec pos);                           /* fn_1_145A8 heiho, leaf, player */
void SetVoicePan(s16 charNo, Vec pos);                   /* fn_1_14918 player update */

} // namespace m513

#endif
