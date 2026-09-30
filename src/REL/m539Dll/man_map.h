/* man_map.h -- man_map.cpp: m539::CMapMan (the arena: shadow receiver 0x610001, the lit map 0x610000, the
 * global multi-shadow from its "inf_light1", two CHeiho walkers, a full-screen sprite 0x61000B that fades in
 * over 48 frames in mode 1) and m539::CLerp<T>, the tween CMapMan and CScore share.
 * man_map.cpp includes minigame.h (the 120/210/210 triple is in man_map.o's .bss/__sinit); this header does not. */
#ifndef M539_MAN_MAP_H
#define M539_MAN_MAP_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include <memory>

namespace m539 {

class CHeiho;

/* CLerp<T>: value eases from -> to over n+1 steps (in double). A template: its three functions are emitted
 * weak at the END of man_map.o (C750/C794/C7C8, after the auto_ptr<CHeiho> ctor) and called out of line by
 * man_map and score; Set(to, n) does not inline Set(from, to, n) (template bodies are generated at the end).
 * GC: m_n +0, m_count +4, m_value +8, m_from +0xC, m_to +0x10; size 0x14. Trivially destructible.
 * The name and template-ness are ours (sheet §9 Q5). */
template <class T>
class CLerp {
public:
    /* inline: CMapMan's and CScore's mem-initializers call Set(to, n) in member order (their `m_x(0.0f, 0)`) */
    CLerp(T to, int n) { Set(to, n); }
    void Set(T to, int n);          /* fn_1_C750 Set(m_value, to, n): reads m_value (uninitialised in the ctors,
                                     * harmless there: n == 0 overwrites it) */
    void Set(T from, T to, int n);  /* fn_1_C794 n == 0: value = from = to = `to` */
    T Update();                     /* fn_1_C7C8 */

    int m_n;     /* 0x00 */
    int m_count; /* 0x04 */
    T m_value;   /* 0x08 */
    T m_from;    /* 0x0C */
    T m_to;      /* 0x10 */
};

template <class T>
void CLerp<T>::Set(T to, int n)
{
    Set(m_value, to, n);
}

template <class T>
void CLerp<T>::Set(T from, T to, int n)
{
    m_n = n;
    m_count = 0;
    if (n == 0) {
        m_value = to;
        m_from = to;
        m_to = to;
    } else {
        m_value = from;
        m_from = from;
        m_to = to;
    }
}

template <class T>
T CLerp<T>::Update()
{
    T v = m_value;
    if (m_count <= m_n) {
        double num = ++m_count;
        double t = num / (m_n + 1);
        v = m_from * (1.0 - t) + m_to * t;
        m_value = v;
    }
    return v;
}

/* GC: CGameObject +0x00 (vptr +8, m_execFlags +0xC), empty CSingleton<CMapMan> at +0x10 (shares the offset with
 * m_shadow), m_shadow +0x10, m_map +0x14, m_heiho +0x18, m_proc +0x20 (12-byte PTMF), m_grp +0x2C, m_alpha
 * +0x30; size 0x44 (game_master `li r3,0x44`). Vtable data_418 {~, on_new_mode, on_update} + a .data pad word. */
class CMapMan : public CGameObject, public CSingleton<CMapMan> {
public:
    typedef void (CMapMan::*ProcFunc)();

    /* fn_1_BEBC (unreferenced): GetInstance() with the result spilled and dropped (sheet §9 Q4; name ours) */
    static void CheckInstance();
    static void SetShadowReceiver(s16 id); /* fn_1_BF2C unreferenced; inlined into the ctor */
    CMapMan();                             /* fn_1_BF70 */
    void stateIdle();                      /* fn_1_C540 empty; the only m_proc */
    virtual void on_update();              /* fn_1_C544 */
    virtual void on_new_mode(int mode);    /* fn_1_C5CC mode 1 starts the fade-in */
    /* fn_1_C634: neither kills the sprite group nor frees the sprite anim (the overlay heap does) */
    virtual ~CMapMan();

    std::auto_ptr<CModel> m_shadow;    /* 0x10 new CModel(0x610001), NOT through CModelMan */
    std::auto_ptr<CModel> m_map;       /* 0x14 new CModel(0x610000) */
    std::auto_ptr<CHeiho> m_heiho[2];  /* 0x18 __construct_array */
    ProcFunc m_proc;                   /* 0x20 (12 bytes on CW) */
    int m_grp;                         /* 0x2C HuSprGrpCreate (an s16 widened) */
    CLerp<float> m_alpha;              /* 0x30 sprite alpha */
};

} // namespace m539

#ifndef __MWERKS__
template <> m539::CMapMan* CSingleton<m539::CMapMan>::ms_pointer; /* defined in game_master.cpp */
#endif

#endif
