/* stage.h -- m522::CStage (stage.cpp): the tower of 8 blocks ("brock_a".."brock_h" in model 0x500007) over the
 * lava, its two invisible collision floors, the sky / background models, the shadow projector, and the owner of
 * the sun (CSun, fire.h) and the bubble spawner (CBubbleMan, bubble.h). Each solo strike (BreakBlock) knocks the
 * top block out: it slides +2000 in x over 48 frames (SlideBlock), the floors and the camera drop by 200.
 * GC (sheet master_camera_sunfire_stage.md §6.1; size 0x48, gm on_setup `li r3,0x48`): CGameObject +0 (vptr +8,
 * m_execFlags +0xC), empty CSingleton<CStage> +0x10 (ms_pointer = bubble.o .bss 0x18), m_sun +0x10,
 * m_sky +0x14, m_bg +0x18, m_tower +0x1C, m_col[2] +0x20, m_bubble +0x28 (all std::auto_ptr), m_unk2C +0x2C (s16,
 * never read), m_se +0x30, m_numBlocks +0x34, m_blocksLeft +0x38, m_colIdx +0x3C, m_slide +0x40, m_bgRotY +0x44.
 * Vtable data_58C {~ ECC0, on_new_mode F200, on_update F218}. stage.cpp includes no minigame.h (no .ctors).
 * CSun / CBubbleMan are only forward-declared here: the auto_ptr dtors are instantiated in stage.cpp alone. */
#ifndef M522_STAGE_H
#define M522_STAGE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include <memory>

namespace m522 {

class CSun;
class CBubbleMan;

class CStage : public CGameObject, public CSingleton<CStage> {
public:
    enum { NUM_BLOCKS = 8 };

    CStage();                           /* fn_1_E85C */
    virtual ~CStage();                  /* fn_1_ECC0 HuAudFXStop(m_se); the auto_ptrs in reverse order */
    void InitCol();                     /* fn_1_EE24 the two collision floors (0x500008) + MgActorColMapInit */
    void BreakBlock(Vec* hitPos);       /* fn_1_EF38 (player CSolo::procStrike) */
    bool IsDropDone();                  /* fn_1_F194 m_slide <= 0 (gm checkEnd, bubble, player) */
    float GetTopY();                    /* fn_1_F1B8 (2 * m_blocksLeft + 1) * 100 (the lava / tower top) */
    int GetBlocksLeft();                /* fn_1_F1F8 (gm checkEnd, bubble procMain) */
    virtual void on_new_mode(int mode); /* fn_1_F200 clears the bit only */
    virtual void on_update();           /* fn_1_F218 */
    void SlideBlock();                  /* fn_1_F34C */
    void RotateBg();                    /* fn_1_F4E0 */

    std::auto_ptr<CSun> m_sun;          /* 0x10 fire.h (0x860) */
    std::auto_ptr<CModel> m_sky;        /* 0x14 0x500003 (layer 3, ZCMP_OFF) */
    std::auto_ptr<CModel> m_bg;         /* 0x18 0x500001 (layer 0, loop; rotated every frame) */
    std::auto_ptr<CModel> m_tower;      /* 0x1C 0x500007 (layer 4; the blocks) */
    std::auto_ptr<CModel> m_col[2];     /* 0x20 0x500008 x2 (hidden collision floors), __construct_array */
    std::auto_ptr<CBubbleMan> m_bubble; /* 0x28 bubble.h (0x1C) */
    s16 m_unk2C;                        /* 0x2C -1, never read */
    int m_se;                           /* 0x30 HuAudFXPlay(0x3A2) */
    s32 m_numBlocks;                    /* 0x34 8 */
    s32 m_blocksLeft;                   /* 0x38 (signed) */
    s32 m_colIdx;                       /* 0x3C 0/1, toggled by BreakBlock */
    float m_slide;                      /* 0x40 remaining slide distance (> 0 while a block slides) */
    float m_bgRotY;                     /* 0x44 -= 1/240 per frame */
};

} // namespace m522

#ifndef __MWERKS__
template <> m522::CStage* CSingleton<m522::CStage>::ms_pointer; /* defined in bubble.cpp (bss 0x18) */
#endif

#endif
