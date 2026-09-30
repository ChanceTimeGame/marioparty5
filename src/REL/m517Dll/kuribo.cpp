/* kuribo.cpp -- m517::CKuribo, the two background Goombas (player_kuribo.md §2.1, §3.1). Retail order (.text
 * C994..DBB8): ctor, [~auto_ptr<CShadow> CBF4, ~vector<s16> CC4C, ~__vector_pod CCE0, ~__vector_base CD6C (weak)],
 * ~CKuribo, LightSet (dead), AmbSet (dead), on_new_mode, procWalk, procLook (both unreferenced; inlined in
 * on_update), on_update, addMotion, setMotion, [at D778, insert D7F0 (weak)], [thunks DBA0 / DBA8 / DBB0].
 * .data 3F0..480: s_lightPos, s_lightCol (only the dead LightSet), the vtable 400, the MSL vector strings. .rodata
 * 218..248. No .bss, no .ctors (no minigame.h / player.h / util.h). */
#include "REL/m517Dll/config.h"
#include "REL/m517Dll/kuribo.h"
extern "C" {
#include "game/frand.h"
}

namespace m517 {

/* data_3F0 / data_3FC: the stage's light constants (stage.o .data has the same bytes); only LightSet reads them */
static Vec s_lightPos = { 1.0f, 4179.7339f, 3252.001f };
static GXColor s_lightCol = { 0xFF, 0xFF, 0xFF, 0xFF };

/* the first motion id through one inline level: retail's GPR order in the ctor (a named `s16&` local takes the
 * higher register; the direct at() result gets none) */
static inline s16& MotAt(std::vector<s16>& v, int i)
{
    return v.at(i);
}

CKuribo::CKuribo(Vec* pos, Vec* rot, int type)
    : CModel(0x4B000Au), m_mot_id(), m_shadow(0), m_type(type), m_pos(*pos), m_rot(*rot), m_state(0)
{
    HU3DMODELID id = this->id();
    Hu3DModelLayerSet((int)id, 0);
    Hu3DModelLightInfoSet((int)id, 0);
    Hu3DModelPosSet((int)id, pos->x, pos->y, pos->z);
    Hu3DModelRotSet((int)id, rot->x, rot->y, rot->z);
    addMotion(0x4B000B);
    addMotion(0x4B000C);
    Hu3DMotionSet((int)id, MotAt(m_mot_id, 0));
    setAttr(0x40000001);
    m_motion = 0;
    m_timer = 0;
    m_wait = (frand() % 5) * 60;
    /* retail: m_dir stays unset for any other type (the stage passes 0 and 2) */
    switch (m_type) {
    case 0:
        m_dir = frand() & 1;
        break;
    case 1:
        m_dir = 0;
        break;
    case 2:
        m_dir = 1;
        break;
    }
    m_shadow.reset(new CShadow());
}

CKuribo::~CKuribo() {}

/* fn_1_CF08: dead (unreferenced). One identical local light per HSF object (the object pointer is advanced and
 * never read), only when the model has no local light yet. */
void CKuribo::LightSet(s16 model)
{
    Vec dir;
    PSVECNormalize(&s_lightPos, &dir);
    PSVECScale(&dir, &dir, -1.0f);
    HU3DMODEL* m = &Hu3DData[model];
    HSFDATA* hsf = m->hsf;
    if (m->lLightId[0] == -1) {
        HSFOBJECT* obj = hsf->object;
        for (int i = 0; i < hsf->objectNum; i++, obj++) {
            HU3DLIGHTID light = Hu3DLLightCreateV(model, &s_lightPos, &dir, &s_lightCol);
            Hu3DLLightStaticSet(model, light, TRUE);
        }
    }
}

/* fn_1_CFD4: dead */
void CKuribo::AmbSet(s16 model)
{
    Hu3DModelAmbSet(model, 1.0f, 1.0f, 1.0f);
}

void CKuribo::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

/* type 0: wait m_wait, walk-turn (177 deg over 60 frames), walk 1.6666666 / frame until frame 240, re-roll */
void CKuribo::procWalk()
{
    switch (m_state) {
    case 0:
        if (m_timer < m_wait) {
            break;
        }
        m_timer = 0;
        setMotion(MOT_WALK);
        m_state++;
    case 1:
        if (m_dir != 0) {
            m_rot.y += 2.9508197f;
        } else {
            m_rot.y -= 2.9508197f;
        }
        if (m_timer < 60) {
            break;
        }
        m_timer = 0;
        m_state++;
    case 2: {
        float a = M_PI * m_rot.y / 180.0;
        float speed = 1.6666666f;
        m_pos.x += speed * sin(a);
        m_pos.z += speed * cos(a);
        if (m_timer < 240) {
            break;
        }
        setMotion(MOT_IDLE);
        m_wait = (frand() % 5) * 60;
        m_dir = frand() & 1;
        m_timer = 0;
        m_state = 0;
        break;
    }
    }
}

/* types 1 / 2: wait m_wait, swing 44 deg over 60 frames, swap the direction */
void CKuribo::procLook()
{
    switch (m_state) {
    case 0:
        if (m_timer < m_wait) {
            break;
        }
        m_timer = 0;
        setMotion(MOT_WALK);
        m_state++;
    case 1:
        if (m_dir == 0) {
            m_rot.y += 0.73770493f;
        } else {
            m_rot.y -= 0.73770493f;
        }
        if (m_timer < 60) {
            break;
        }
        m_timer = 0;
        m_state++;
        setMotion(MOT_IDLE);
        m_wait = (frand() % 5) * 60;
        m_dir ^= 1;
        m_timer = 0;
        m_state = 0;
        break;
    }
}

void CKuribo::on_update()
{
    if (m_type == -1) {
        return;
    }
    switch (m_type) {
    case 0:
        procWalk();
        break;
    case 1:
    case 2:
        procLook();
        break;
    }
    setPos(&m_pos);
    setRot(&m_rot);
    CShadow* shadow = m_shadow.get();
    shadow->m_pos.x = m_pos.x;
    shadow->m_pos.y = m_pos.y;
    shadow->m_pos.z = m_pos.z;
    m_timer++;
}

void CKuribo::addMotion(int dataNum)
{
    HU3DMODELID id = this->id();
    void* data = HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL);
    s16 mot = Hu3DJointMotion((int)id, data);
    m_mot_id.push_back(mot);
}

/* retail bug kept: m_motion is the index, compared with the motion id (so it always re-shifts) */
void CKuribo::setMotion(int no)
{
    s16 mot;
    s16& ref = m_mot_id.at(no);
    mot = ref;
    if ((u32)m_motion != mot) {
        HU3DMODELID id = this->id();
        Hu3DMotionShiftSet((int)id, mot, 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
        m_motion = no;
    }
}

} // namespace m517
