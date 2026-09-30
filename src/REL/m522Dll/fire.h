#ifndef M522_FIRE_H
#define M522_FIRE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/singleton.h"
#include "REL/m522Dll/sunfire.h"
#include <memory>
#include <vector>

namespace m522 {

/* one oscillator of the sun's warp texture (12 bytes, POD) */
struct Wave {
    float Advance(); /* fn_1_614 phase += speed; returns the new phase (called, not inlined: defined after) */

    float phase; /* 0x0 */
    float speed; /* 0x4 frand(-2, 2) * pi / 108 rad per frame */
    float amp;   /* 0x8 frand(1, 127) */
};

class CSun : public CModel, public CSingleton<CSun> {
public:
    enum { TEX_W = 32, TEX_H = 32, WAVE_NUM = 0x400 };

    CSun();                   /* fn_1_0 */
    ~CSun();                  /* fn_1_360 (non-virtual; deleted by stage's auto_ptr<CSun>) */
    void Update();            /* fn_1_428 Spin(); UpdateTexture() (stage on_update) */
    void StopSpin();          /* fn_1_460 m_speed = 0 (stage BreakBlock, last block) */
    void SetShadowSun();      /* fn_1_474 setShadowMapObj("sun01") (stage BreakBlock, last block) */
    void Spin();              /* fn_1_4A4 */
    void UpdateTexture();
    /* fn_1_628: the Hu3D material hook (TEXMAP1 = m_tex through GetInstance, one indirect warp stage) */
    static void MatHook(HU3DDRAWOBJ* drawObj, HSFMATERIAL* material);

    /* 0x0 CModel base (s16 id), 0x2 empty CSingleton<CSun> base */
    float m_rot;                /* 0x004 spin angle (deg) */
    float m_speed;              /* 0x008 s_spinSpeed; 0 after StopSpin */
    GXTexObj m_tex;             /* 0x00C IA8 32x32, REPEAT/REPEAT (GC 0x20 bytes; larger on the host) */
    u8 m_texData[TEX_W * TEX_H * 2] ATTRIBUTE_ALIGN(32); /* 0x040 IA8 texel pairs, rewritten every frame */
    std::vector<Wave> m_waves;  /* 0x840 WAVE_NUM oscillators */
};

/* Tile's wait counter: a class with a user copy ctor AND operator= (MSL agent, notebook 20260926-m522-msl: only this
 * gives insert<Tile> 27E8 masked 0 -- the 3-level `&this->wait` chain of its inline copy; plain ints: masked 130) */
struct Wait {
    Wait() {}
    Wait(const Wait& o) : v(o.v) {}
    Wait& operator=(const Wait& o)
    {
        v = o.v;
        return *this;
    }
    Wait& operator=(s32 n)
    {
        v = n;
        return *this;
    }

    s32 v;
};

/* one sprite tile on a quad face (16 bytes) */
struct Tile {
    Tile(int type);                  /* fn_1_B88 */
    /* fn_1_C2C: a 4-word copy (unreferenced). Name ours; its exact kind (copy ctor / operator= / a setter) is F1's:
     * a user Tile copy or assignment may change insert<Tile>'s inline copy (SKELETON.md §6) */
    void Copy(const Tile& t);
    void Update();                   /* fn_1_C50 (unreferenced; inlined in CFire::update) */
    void GetUV(float* u0, float* v0, float* u1, float* v1); /* fn_1_D50 (unreferenced; inlined in DrawObj) */

    s32 type;      /* 0x0 0 fire01, 1 prominence (cmpwi 1) */
    s32 lastFrame; /* 0x4 0x3F / 0x8F (signed cmpw) */
    s32 frame;     /* 0x8 &15 = column, /16 = row */
    Wait wait;     /* 0xC > 0 hides the tile (prominence pause) */
};

class CFire : public CSunFireObj {
public:
    CFire();                           /* fn_1_824 */
    virtual ~CFire();                  /* fn_1_A10 */
    void AddTiles(int i);              /* fn_1_AB0 one Tile per quad face of s_objName[i] */
    virtual void update();             /* fn_1_F84 every tile (inline Tile::Update); m_rot += s_spinSpeed */
    virtual void draw(Mtx* mtx);       /* fn_1_10C8 GX setup, billboard matrix, DrawObj(0), DrawObj(1) */
    void DrawObj(int i, Mtx view, Mtx bb, std::vector<Tile>::iterator* cursor);

    std::auto_ptr<CModel> m_model;     /* 0x14 0x500004 (hidden: the face / vertex source) */
    float m_rot;                       /* 0x18 screen-plane rotation (deg) */
    std::vector<Tile> m_tiles;         /* 0x1C */
};

/* one spark (0x24; non-POD: the trail vector) */
struct Flare {
    Flare(const Vec* pos, const Vec* vel, float life); /* fn_1_1BC0 */
    bool Update();                     /* fn_1_1D30 (unreferenced; inlined in CFlare::update): true while alive */
    void Draw();                       /* fn_1_24FC two GX_LINES vertices (head yellow, tail red) */
    /* trail point i (Update, Draw). Retail reads MSL's data pointer through its reference accessor, with no
     * begin() temporary (1D30 / 24FC: `lwz r4,0(this+8)` straight into the add) -- a guess at MSL's spelling;
     * no public MSL member emits it, so the CW form names the member (lead: an MSL accessor?) */
#ifdef __MWERKS__
    Vec& Point(u32 i) { return trail.data_.first()[i]; }
#else
    Vec& Point(u32 i) { return trail[i]; }
#endif

    std::vector<Vec> trail;            /* 0x00 8-point ring */
    Vec vel;                           /* 0x0C */
    float life0;                       /* 0x18 */
    float life;                        /* 0x1C */
    u32 head;                          /* 0x20 (cmplw / divwu: unsigned) */
};

class CFlare : public CSunFireObj {
public:
    CFlare(Vec* centre, float power, float time, int n); /* fn_1_17E8 (bubble Burst: 200, 2, 0x40) */
    virtual ~CFlare();                 /* fn_1_1B38 */
    virtual void update();
    virtual void draw(Mtx* mtx);       /* fn_1_232C */

    std::vector<Flare> m_flares;       /* 0x14 */
};

} // namespace m522

#ifndef __MWERKS__
template <> m522::CSun* CSingleton<m522::CSun>::ms_pointer; /* defined in fire.cpp (bss 0x10) */
#endif

#endif
