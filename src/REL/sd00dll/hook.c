/*
 * sd00dll hook.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/sd00dll/asm/REL/sd00dll/hook.s.
 */

#include "REL/sd00dll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "math.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */

/* --- functions (reference order), .data placed before its first user --- */
/* 119 insns */
float SdMachineHookSet(s32 tireNo, HU3DMODELID bodyMdl, HU3DMODELID *tireMdl, HU3DMODELID gunMdl, HU3DMODELID charMdl)
{
    s32 i;
    s32 flag;
    s32 type;
    float ofsY = 0.0f;
    if(bodyMdl == -1) {
        return ofsY;
    }
    flag = sdMachineTireTbl[tireNo].unk34;
    type = flag & 0xF;
    for(i=0; i<4; i++) {
        if(tireMdl[i] == -1) {
            continue;
        }
        if(type == 0) {
            Hu3DModelHookSet(bodyMdl, sdMachineHookTbl[i], tireMdl[i]);
            ofsY = sdMachineTireTbl[tireNo].unk1C;
        } else if(type == 1) {
            if(i < 2) {
                Hu3DModelHookSet(bodyMdl, sdMachineHookTbl[i+4], tireMdl[i]);
                ofsY = sdMachineTireTbl[tireNo].unk1C;
            }
        } else if(i < 1) {
            Hu3DModelHookSet(bodyMdl, sdMachineHookTbl[7], tireMdl[i]);
            ofsY = sdMachineTireTbl[tireNo].unk1C+sdMachineTireTbl[tireNo].unk20;
        }
    }
    if(gunMdl != -1) {
        Hu3DModelHookSet(bodyMdl, sdMachineHookTbl[6], gunMdl);
    }
    if(charMdl != -1) {
        Hu3DModelHookSet(bodyMdl, sdMachineHookTbl[12], charMdl);
    }
    return ofsY;
}

