/* back.h -- the background under the maze (back.cpp): CBack, three drifting layer models (clouds, guess) at
 * depths -2000/-2700/-3500 that respawn at an edge, and CBackObj, one looping model orbiting the arena.
 * Neither is a singleton; no asserts. back.cpp does not include minigame.h.
 * GC: CBack 0xCC (gamemaster `li r3,0xCC`), CBack::Layer 0x3C, CBackObj 0x28 (`li r3,0x28`).
 * Vtables: data_33A4 CBackObj, data_33B8 CBack ({~, on_new_mode, on_update}); both dtors are implicit and
 * emitted at the unit end (CBackObj's first: DC8C, DD18), with the vtables, in reverse class order. */
#ifndef M509_BACK_H
#define M509_BACK_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/model.h"

namespace m509 {

class CBack : public CGameObject {
public:
    /* one drifting layer (0x3C). Host: `model` is a pointer (0x40 / class 0xD8 on 64-bit; nothing uses offsets) */
    struct Layer {
        int no;         /* 0x00 0..2: index into s_layerY */
        CModel* model;  /* 0x04 &m_model0/1/2 */
        Vec pos;        /* 0x08 y fixed at s_layerY[no] */
        Vec vel;        /* 0x14 x/z drift (y = 0) */
        Vec rot;        /* 0x20 degrees; y is radians written as degrees (retail quirk, sheet §8.2) */
        Vec rotVel;     /* 0x2C only z (spin) is read */
        float scale;    /* 0x38 0 -> 1 (+0.1 per frame) */
    };

    CBack();
    virtual void on_update();         /* fn_1_D004 update() each layer */
    void reset(Layer* l);             /* fn_1_D05C respawn at a random edge */
    void checkOut(Layer* l);          /* fn_1_D4B0 unreferenced copy (inlined in update): reset when "out" */
    void move(Layer* l);              /* fn_1_D5A8 unreferenced copy (inlined in update): spin, scale, drift */
    void update(Layer* l);            /* fn_1_D704 checkOut + move */
    virtual void on_new_mode(int mode);

    bool m_finish;     /* 0x10 set in mode 3: only x-moving respawns afterwards */
    CModel m_model0;   /* 0x12 0x430002 */
    CModel m_model1;   /* 0x14 0x430003 */
    CModel m_model2;   /* 0x16 0x430004 */
    Layer m_layer[3];  /* 0x18 */
};

class CBackObj : public CGameObject {
public:
    CBackObj();
    virtual void on_update();         /* fn_1_DA70 move() */
    void move();                      /* fn_1_DA98 orbit (500, -1700, -200) r 1200, spin */
    virtual void on_new_mode(int mode);

    float m_angle;   /* 0x10 orbit angle, degrees */
    float m_rotY;    /* 0x14 spin, degrees */
    Vec m_pos;       /* 0x18 not set by the ctor; first written in move */
    CModel m_model;  /* 0x24 0x430005, looping motion */
};

} // namespace m509

#endif
