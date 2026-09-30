/* back.cpp -- the background under the maze: CBack (three drifting layer models) and CBackObj (one looping
 * model orbiting the arena). SKELETON: drafted whole from the W0 sheet (master_camera_back_setup.md §4); the
 * fork verifies it. Retail order: CBack ctor, on_update, reset, checkOut, move, update, on_new_mode, CBackObj
 * ctor, on_update, move, on_new_mode; then the two implicit dtors (CBackObj's, CBack's) at the unit end. */
#include "REL/m509Dll/back.h"
#include "REL/m509Dll/random.h"

namespace m509 {

/* lbl_1_data_3398 (writable): layer depth by Layer::no */
static float s_layerY[3] = { -2000.0f, -2700.0f, -3500.0f };

/* Vec setter with DOUBLE components: every store of reset() goes through frsp (sheet §4.3) */
static inline void SetVecD(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

/* degrees <-> 16-bit binary angle (65536 per turn). move (D5A8, and its copy inlined in update D704) is
 * `float deg` local, DegToAngle, the wrap to -0x8000..0x7FFF written in place into `int w`, AngleToDeg: the
 * only spelling (of 12 tried) that gives both functions' saved registers and inline copies */
static inline int DegToAngle(float deg)
{
    return (65536.0 / 360.0) * deg;
}

static inline float AngleToDeg(int angle)
{
    return (360.0 / 65536.0) * angle;
}

CBack::CBack() : m_model0(0x430002U), m_model1(0x430003U), m_model2(0x430004U)
{
    Hu3DModelLayerSet(m_model0.id(), 1);
    Hu3DModelLayerSet(m_model1.id(), 1);
    Hu3DModelLayerSet(m_model2.id(), 1);
    m_layer[0].model = &m_model0;
    m_layer[1].model = &m_model1;
    m_layer[2].model = &m_model2;
    m_finish = false;
    for (int i = 0; i < 3; i++) {
        m_layer[i].no = i;
        reset(&m_layer[i]);
    }
}

void CBack::on_update()
{
    for (int i = 0; i < 3; i++) {
        update(&m_layer[i]);
    }
}

/* respawn at a random edge (after the finish: only the x edges) heading inwards, scale 0 */
void CBack::reset(Layer* l)
{
    int r = CRandom::irandom();
    if (m_finish) {
        r = (r & 1) + 2;
    } else {
        r &= 3;
    }
    float x, z, vx, vz;
    switch (r) {
    case 0:
        x = 100.0f * (15.0f * (CRandom::randomMantissa() - 0.5f));
        z = -2500.0f;
        vx = 20.0f * (CRandom::randomMantissa() - 0.5f);
        vz = 10.0f + 20.0f * CRandom::randomMantissa();
        break;
    case 1:
        x = 100.0f * (15.0f * (CRandom::randomMantissa() - 0.5f));
        z = 2500.0f;
        vx = 20.0f * (CRandom::randomMantissa() - 0.5f);
        vz = -(20.0f * CRandom::randomMantissa()) - 10.0f;
        break;
    case 2:
        x = -3000.0f;
        z = 100.0f * (12.0f * (CRandom::randomMantissa() - 0.5f));
        vx = 10.0f + 20.0f * CRandom::randomMantissa();
        vz = 20.0f * (CRandom::randomMantissa() - 0.5f);
        break;
    case 3:
        x = 3000.0f;
        z = 100.0f * (12.0f * (CRandom::randomMantissa() - 0.5f));
        vx = -(20.0f * CRandom::randomMantissa()) - 10.0f;
        vz = 20.0f * (CRandom::randomMantissa() - 0.5f);
        break;
    }
    l->scale = 0.0f;
    SetVecD(&l->pos, x, s_layerY[l->no], z);
    SetVecD(&l->vel, vx, 0.0f, vz);
    SetVecD(&l->rot, 0.0f, (float)(M_PI * (60.0f * CRandom::randomMantissa()) / 180.0), 0.0f);
    /* CW evaluates the arguments right to left: z's rand() runs before y's (sheet §4.3) */
    SetVecD(&l->rotVel, 0.0f, 180.0f * CRandom::randomMantissa(), 5.0f * (CRandom::randomMantissa() - 0.5f));
}

/* retail bug kept (sheet §8.1): the -x / -z tests compare with +3000 / +2500, so a layer drifting that way is
 * reset every frame */
void CBack::checkOut(Layer* l)
{
    bool out = false;
    if (l->vel.x > 0.0f) {
        if (l->pos.x > 3000.0f) {
            out = true;
        }
    } else if (l->pos.x < 3000.0f) {
        out = true;
    }
    if (l->vel.z > 0.0f) {
        if (l->pos.z > 2500.0f) {
            out = true;
        }
    } else if (l->pos.z < 2500.0f) {
        out = true;
    }
    if (out) {
        reset(l);
    }
}

void CBack::move(Layer* l)
{
    float deg = l->rot.z + l->rotVel.z;
    int w = ((DegToAngle(deg) + 0x8000) & 0xFFFF) - 0x8000;
    l->rot.z = AngleToDeg(w);
    l->model->setRot(&l->rot);
    if ((l->scale += 0.1f) > 1.0f) {
        l->scale = 1.0f;
    }
    Vec s;
    s.x = s.y = s.z = l->scale;
    l->model->setScale(&s);
    l->pos.x += l->vel.x;
    l->pos.z += l->vel.z;
    l->model->setPos(&l->pos);
}

void CBack::update(Layer* l)
{
    checkOut(l);
    move(l);
}

void CBack::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    switch (mode) {
    case 0:
    case 1:
    case 2:
    case 4:
        break;
    case 3:
        m_finish = true;
        break;
    }
}

CBackObj::CBackObj() : m_model(0x430005U)
{
    m_angle = 0.0f;
    m_rotY = 0.0f;
    HU3DMODELID id = m_model.id();
    HU3DMOTID mot = Hu3DMotionIDGet(id);
    Hu3DModelLayerSet(id, 1);
    Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
    Hu3DMotionSet(id, mot);
}

void CBackObj::on_update()
{
    move();
}

/* orbit (500, -1700, -200) at radius 1200 (60 s a turn) while spinning (6 s a turn) */
void CBackObj::move()
{
    if ((m_rotY += 1.0f) > 180.0f) {
        m_rotY -= 360.0f;
    }
    Vec rot;
    SetVecD(&rot, 0.0f, m_rotY, 30.0f);
    m_model.setRot(&rot);
    if ((m_angle += 0.1f) > 180.0f) {
        m_angle -= 360.0f;
    }
    float a = M_PI * m_angle / 180.0;
    m_pos.x = 500.0 + 100.0 * (12.0 * cos(a));
    m_pos.y = -1700.0f;
    m_pos.z = 100.0 * (12.0 * sin(a)) - 200.0;
    m_model.setPos(&m_pos);
}

void CBackObj::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    switch (mode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        break;
    }
}

} // namespace m509
