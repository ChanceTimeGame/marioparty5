#include "REL/m513Dll/leaf.h"
#include "REL/m513Dll/powerind.h"
#include "REL/m513Dll/heiho.h"
#include "REL/m513Dll/audio.h"
extern "C" {
#include "game/frand.h"
}

namespace m513 {

void CLeafEffect::Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx m)
{
    CLeafEffect* self = (CLeafEffect*)particle->work;
    self->UpdateParticles(m);
}

CLeafEffect::CLeafEffect(Vec* pos) : m_pos(*pos)
{
    int id = Hu3DParticleCreate(CSingleton<CPowerInd>::GetInstance()->GetLeafAnim(), 64);
    m_particle = (HU3DPARTICLE*)Hu3DData[(HU3DMODELID)id].hookData;
    m_particle->work = this;
    Hu3DParticleHookSet(id, Hook);
    Hu3DParticleColSet(id, 0xFF, 0xFF, 0x80);
    Hu3DParticleTPLvlSet(id, 0.0f);
    Hu3DParticleBlendModeSet(id, 0);
    Hu3DModelLayerSet(id, 5);
    Hu3DModelCameraSet(id, 1);
    Hu3DModelPosSet(id, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(id, 0.0f, 0.0f, 0.0f);
    m_id = id;
    int i;
    HU3DPARTICLEDATA* p;
    for (i = 0, p = m_particle->data; i < m_particle->maxCnt; i++, p++) {
        InitParticle(p);
    }
}

CLeafEffect::~CLeafEffect()
{
    m_particle->work = 0;
    Hu3DModelKill(m_id);
}

void CLeafEffect::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    if (m_allDead) {
        delete this;
    }
}

/* fn_1_7B00: a leaf at the emitter, fade-in speed 4..19, size 5..15, a random spin and a burst velocity
 * (14 * g/36 per axis, z always toward the camera) */
void CLeafEffect::InitParticle(HU3DPARTICLEDATA* p)
{
    p->time = 0;
    p->parManId = (frand() & 15) + 4;
    p->pos.x = m_pos.x;
    p->pos.y = m_pos.y;
    p->pos.z = m_pos.z;
    p->scale = 0.5f * (100.0f * (0.1f + 0.2f * ((1.0f / 65536) * (frand() & 0xFFFF))));
    p->zRot = 0.017453292f * (360.0f * ((1.0f / 65536) * (frand() & 0xFFFF)));
    p->vel.x = 0.27240694444444447 * (14.0f * ((1.0f / 32768) * ((frand() & 0xFFFF) - 32768.0f)));
    p->vel.y = 0.27240694444444447 * (14.0f * ((1.0f / 32768) * ((frand() & 0xFFFF) - 32768.0f)));
    p->vel.z = 0.27240694444444447 * -(14.0f * ((1.0f / 65536) * (frand() & 0xFFFF)));
    p->color.a = 0;
}

/* fn_1_7D8C: time 0 fades in by 16 to 255, then fades out by parManId; below 20 the leaf is dead (time 255).
 * m_allDead is true only when no particle is alive (on_new_mode then deletes the effect). */
void CLeafEffect::UpdateParticles(Mtx m)
{
    HU3DMODEL* model = &Hu3DData[m_id];
    HU3DPARTICLE* particle = m_particle;
    m_allDead = true;
    int i;
    HU3DPARTICLEDATA* p;
    for (i = 0, p = particle->data; i < particle->maxCnt; i++, p++) {
        if (p->time == 255) {
            continue;
        }
        if (p->time == 0) {
            p->color.a += 16;
            if (p->color.a > 235) {
                p->color.a = 255;
                p->time++;
            }
        } else {
            p->color.a -= p->parManId;
            if (p->color.a < 20) {
                p->color.a = 0;
                p->time = 255;
            }
        }
        p->zRot += 0.017453292f;
        p->vel.x *= 0.99f;
        p->vel.y *= 0.99f;
        p->vel.z *= 0.99f;
        p->pos.x += p->vel.x;
        p->pos.y += p->vel.y;
        p->pos.z += p->vel.z;
        m_allDead = false;
    }
}

/* lbl_1_rodata_184: the leaf models (only [0], [1] are used) */
static const u32 s_leafData[3] = { 0x470005, 0x470006, 0x470007 };

CLeaf::CLeaf(int idx, Vec* pos, Vec* rot)
    : m_model(0x470004u), m_endTime(0.0f), m_pos(*pos), m_rot(*rot), m_full(false), m_idx(idx), m_step(0),
      m_power(0.0f)
{
    insertBack(ASet<CLeaf>::instance());
    HU3DMODELID id = m_model.id();
    Hu3DModelLayerSet(id, 3);
    Hu3DModelCameraSet(id, 1);
    Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
    Hu3DModelShadowSet(id);
    Hu3DModelShadowDispOn(id);
    m_model.setPos(&m_pos);
    m_model.setRot(&m_rot);
    HU3DMOTID shape = Hu3DMotionIDGet(id);
    Hu3DMotionShapeSet(id, shape);
    Hu3DMotionShapeStartEndSet(id, 0.0f, m_endTime);
    Hu3DMotionShapeSpeedSet(id, 0.2f);
    for (int i = 0; i < 2; i++) {
        m_leafModel[i].reset(new CModel(s_leafData[i]));
        HU3DMODELID leaf = m_leafModel[i]->id();
        HU3DMOTID mot = Hu3DMotionIDGet(leaf);
        Hu3DMotionShapeSet(leaf, mot);
        Hu3DMotionShapeTimeSet(leaf, 0.0f);
        Hu3DModelAttrSet(leaf, HU3D_MOTATTR_SHAPE_PAUSE);
        Hu3DModelAttrSet(leaf, HU3D_ATTR_DISPOFF);
        Hu3DModelLayerSet(leaf, 3);
        Hu3DModelCameraSet(leaf, 1);
        Hu3DModelShadowSet(leaf);
        Hu3DModelShadowDispOn(leaf);
    }
    FindLeafObjects();
    setProc(&CLeaf::proc_null);
}

CLeaf::~CLeaf() {}

void CLeaf::Show()
{
    HU3DMODELID id = m_model.id();
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    for (int i = 0; i < 2; i++) {
        HU3DMODELID leaf = m_leafModel[i]->id();
        Hu3DModelAttrReset(leaf, HU3D_ATTR_DISPOFF);
        PlaceLeaf(i);
    }
}

void CLeaf::ShowLeafMotion(int i)
{
    HU3DMODELID leaf = m_leafModel[i]->id();
    Hu3DModelAttrReset(leaf, HU3D_MOTATTR_SHAPE_PAUSE);
}

void CLeaf::PlaceLeaf(int i)
{
    HSFOBJECT* obj = m_obj[i];
    Mtx m;
    Hu3DModelObjMtxGet(m_model.id(), (char*)"null1", m); /* retail: the matrix is not used */
    Vec pos = *(Vec*)&obj->mesh.curr.pos;
    Vec rot = *(Vec*)&obj->mesh.curr.rot;
    pos.z = -pos.z;
    PSVECAdd(&m_pos, &pos, &pos);
    rot.y = 180.0f;
    m_leafModel[i]->setPos(&pos);
    m_leafModel[i]->setRot(&rot);
}

void CLeaf::FindLeafObjects()
{
    static char* names[3] = { (char*)"leaf01", (char*)"leaf02", (char*)"leaf03" };
    HU3DMODELID id = m_model.id();
    for (int i = 0; i < 2; i++) {
        HSFOBJECT* obj = Hu3DModelObjPtrGet(id, names[i]);
        m_obj[i] = obj;
    }
}

/* lbl_1_rodata_194: the leaf SEs (only [0], [1] reachable) */
static const int s_leafSe[4] = { 0x6D5, 0x6D6, 0x6D7, 0x6D8 };

#define ABS(x) ((x) < 0 ? -x : x)

/* fn_1_85F4: one pump. The shape motion's end advances by dt (clamped at 60) unless the motion lags by more
 * than 0.6 frames; each 20 frames of shape a leaf model starts moving (the second one first) with its SE; at 59
 * the tree is full: SE 0x6D9, a leaf burst 380 above / 100 in front, and the shape plays on to 100. */
void CLeaf::Grow(float dt)
{
    if (m_full == true) {
        return;
    }
    HU3DMODELID id = m_model.id();
    float t = m_endTime + dt;
    HU3DMODEL* model = &Hu3DData[id];
    float cur = model->motShapeWork.time;
    if (ABS(t - cur) > 0.6f) {
        return;
    }
    m_endTime = t;
    if (m_endTime >= 60.0f) {
        m_endTime = 60.0f;
    }
    Hu3DMotionShapeStartEndSet(id, 0.0f, m_endTime);
    m_power = cur / 60.0f;
    if (m_step < 2 && cur >= 20.0f * (m_step + 1)) {
        ShowLeafMotion(2 - (m_step + 1));
        PlaySe(s_leafSe[m_step], m_pos);
        m_step++;
    }
    for (int i = 0; i < 2; i++) {
        PlaceLeaf(i);
    }
    if (cur >= 59.0f && m_full == false) {
        m_full = true;
        PlaySe(0x6D9, m_pos);
        Vec pos = m_pos;
        pos.y += 380.0f;
        pos.z += 100.0f;
        new CLeafEffect(&pos);
        Hu3DMotionShapeSpeedSet(id, 1.0f);
        Hu3DMotionShapeStartEndSet(id, 0.0f, 100.0f);
    }
}

void CLeaf::Exec()
{
    if (m_proc) {
        (this->*m_proc)();
    }
}

void CLeaf::proc_null() {}

} // namespace m513

template <> ASet<m513::CLeaf>* ASet<m513::CLeaf>::sm_ptr = 0;
template <> m513::CHeihoCarrier* CSingleton<m513::CHeihoCarrier>::ms_pointer = 0;
