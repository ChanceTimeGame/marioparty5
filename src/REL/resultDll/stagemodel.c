/*
 * resultDll stagemodel.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/resultDll/asm/REL/resultDll/stagemodel.s.
 */

#include "REL/resultDll.h"

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x512 gap_05_00000512_bss (0x6): alignment gap */
/* 0x412 */ HU3DMODELID StageMdlId[128];
/* 0x312 */ HU3DMOTID StageMotId[128];
/* 0x310 */ static HU3DMODELID DummyMdlId; /* unreferenced */
/* 0x210 */ HUSPRID StageSprId[128];
/* 0x208 */ HU3DMODELID StageCharMdlId[4];
/* 0x1F0 */ HU3DMOTID StageCharMotId[4][3];
/* 0x1E8 */ HU3DMODELID StageToueiMdlId[4];

/* --- functions (reference order), .data placed before its first user --- */
