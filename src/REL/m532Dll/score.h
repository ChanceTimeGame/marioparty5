#ifndef M532_SCORE_H
#define M532_SCORE_H

#include "REL/m532Dll/config.h"
#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"

namespace m532 {

/* The game result (CScore::checkResult, game_master playRounds; the assert names PLAYING_GAME, the other values
 * are unnamed): 0 / 1 = that team won, 2 = draw with points, 3 = scoreless draw. Here, not in game_master.h:
 * score.cpp must not see minigame.h. */
enum { PLAYING_GAME = -1 };

/* CLerp<T> (m539 man_map.h's, exact): value eases from -> to over n+1 steps (in double). Its three functions
 * are emitted weak at the END of score.o (E3B0 Update, E490 Set(to, n), E4D4 Set(from, to, n)).
 * GC: m_n +0, m_count +4, m_value +8, m_from +0xC, m_to +0x10; size 0x14. */
template <class T>
class CLerp {
public:
    /* inline: the mem-initializers call Set(to, n) (CScore m_fade, CTeamScore m_pop) */
    CLerp(T to, int n) { Set(to, n); }
    void Set(T to, int n);
    void Set(T from, T to, int n);
    T Update();
    /* inline accessors (score's callers read through them: on_update's value temp) */
    bool IsRunning() const { return m_count <= m_n; }
    T Get() const { return m_value; }

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

/* One textured 2D quad (screen space, centred). GC 0x1C. Its small methods are defined out of line (emitted,
 * unreferenced) and auto-inlined into CTeamScore's (sheet §6.2). */
class CIcon {
public:
    void setAnim(ANIMDATA* anim);
    void setPos(float x, float y);  /* fn_1_D430 */
    void setScale(float scale);     /* fn_1_D43C */
    void setAlpha(float alpha);     /* fn_1_D444 clamped to [0, 1] */
    void draw();

    ANIMDATA* m_anim; /* 0x00 */
    float m_x;        /* 0x04 */
    float m_y;        /* 0x08 */
    float m_w;        /* 0x0C half width */
    float m_h;        /* 0x10 half height */
    float m_scale;    /* 0x14 */
    float m_alpha;    /* 0x18 */
};

/* One team's window: three background icons and up to three point icons. GC 0xC8; no dtor (the ctor array
 * has no element dtor). */
class CTeamScore {
public:
    /* fn_1_CD18: inline (its out-of-line copy follows the CScore ctor, __construct_array's argument) */
    CTeamScore() : m_pop(0.0f, 0) {}
    void init(float x, float y, u8 r, u8 g, u8 b); /* fn_1_D71C */
    void setAnims(ANIMDATA* back, ANIMDATA* front); /* fn_1_D924 */
    void setAlpha(float alpha);                      /* fn_1_DAA4 */
    void addPoint();                                 /* fn_1_DB80 capped at 3 */
    int getPoint();                                  /* fn_1_DB9C */
    void show();                                     /* fn_1_DBA4 (retail `m_shown - 2` bound, §10) */
    void update();                                   /* fn_1_DC78 */
    void draw();                                     /* fn_1_DDDC */

    s16 m_win;            /* 0x00 MgScoreWinCreate(0x58, 0x28) */
    CIcon m_back[3];      /* 0x04 */
    CIcon m_front[3];     /* 0x58 */
    int m_point;          /* 0xAC */
    int m_shown;          /* 0xB0 */
    CLerp<float> m_pop;   /* 0xB4 the newest point icon's pop-in */
};

class CScore : public CGameObject, public CSingleton<CScore> {
public:
    CScore();                            /* fn_1_CB30 */
    virtual ~CScore();                   /* fn_1_CDE8 kills no window / sprite / anim (retail) */
    void addPoint(int team);             /* fn_1_CEB4 */
    int getPoint(int team);              /* fn_1_CEF0 (player) */
    void showPoints();                   /* fn_1_CF2C */
    int checkResult(int round);          /* fn_1_CF64 PLAYING_GAME (-1) while undecided */
    virtual void on_new_mode(int mode);  /* fn_1_D048 mode 2 fades the windows in */
    virtual void on_update();            /* fn_1_D0DC */
    static void DrawHook(HUSPRITE* spr);
    void draw();                         /* fn_1_D1EC */
    void setupGX();                      /* fn_1_D238 (this unused) */

    bool m_active;             /* 0x10 */
    CLerp<float> m_fade;       /* 0x14 */
    ANIMDATA* m_anim[3];       /* 0x28 0x5A0015/16/17 */
    CTeamScore m_team[2];      /* 0x34 */
};

} // namespace m532

#ifndef __MWERKS__
template <> m532::CScore* CSingleton<m532::CScore>::ms_pointer; /* defined in game_master.cpp */
#endif

#endif
