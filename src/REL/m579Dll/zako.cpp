/* zako.cpp -- m579::CZakoMan / CZako / CJugem (zako.h). Retail order (sheet fishline_zako_watereff.md §3.2). Fork F6.
 * EXACT (m512 zako.cpp, adapted): createMotion, on_new_mode, DeleteAll, UpdateAll, updateModel, setMotion (MotionAt),
 * move's guarded s_fps. Drafts / STUBs from the sheet otherwise. Asserts zako.cpp:53 / :352 (test/fixlines.py).
 * .data 6B8..7F7 in first-use order; vtables CJugem 75C, CZakoMan 770 (declaration order reversed); then the orphan
 * strings of zako's own (dropped) vector<s16> at / insert / reserve copies. .bss 1288 chain, 1294 CZako::s_list,
 * 12A0 s_fps (+ guard 12A8). No minigame.h. */
#include "REL/m579Dll/zako.h"
#include "REL/m579Dll/puku2.h"
#include "REL/m579Dll/effect.h"
#include "REL/m579Dll/camera.h"
#include "REL/mgcpp/random.h"

namespace m579 {

TLinkList<CZako> CZako::s_list;

/* DRAFT (fn_1_15AD8, 281 insns): two hidden masters, two joint motions, 12 small zako in the middle, 6 big ones on
 * the ring, 5 + 5 Cheep Cheeps */
CZakoMan::CZakoMan() : m_model0(0x850006U), m_model1(0x850007U)
{
    HU3DMODELID id = m_model0.id();
    Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
    id = m_model1.id();
    Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
    m_mot_id.clear();
    m_mot_id.reserve(NUMBEROF_PMOTION);
    createMotion(0x850008);
    createMotion(0x850009);
    /* line padding (CZakoMan ctor) */























    assert(m_mot_id.size() == NUMBEROF_PMOTION);
    for (int i = 0; i < NUM_ZAKO_S; i++) {
        float a = M_PI * (360.0f * (i / 14.0f)) / 180.0; /* retail: stored, never read */
        Vec pos;
        pos.x = 400.0 * (CRandom::randomMantissa() - 0.5);
        pos.y = -220.0 - 20 * i;
        pos.z = 400.0 * (CRandom::randomMantissa() - 0.5);
        new CZako(&m_model0, &pos, false);
    }
    for (int i = 0; i < NUM_ZAKO_L; i++) {
        float a = M_PI * (360.0f * (i / 6.0f)) / 180.0;
        float r = 900.0f;
        Vec pos;
        pos.x = r * cos(a);
        pos.y = -250.0f;
        pos.z = r * sin(a);
        new CZako(&m_model0, &pos, true); /* retail: m_model0 for the ring zako too */
    }
    for (int i = 0; i < NUM_PUKU; i++) {
        new CPuku(m_model0, 0);
    }
    for (int i = 0; i < NUM_PUKU; i++) {
        new CPuku(m_model1, 1);
    }
}

/* EXACT m512 E904 */
s16 CZakoMan::createMotion(int dataNum)
{
    s16 mot = Hu3DJointMotion(m_model0.id(), HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
    m_mot_id.push_back(mot);
    return mot;
}

CZakoMan::~CZakoMan()
{
    CZako::DeleteAll();
    CPuku::DeleteAll();
}

void CZakoMan::on_update()
{
    CZako::UpdateAll();
    CPuku::UpdateAll();
}

/* EXACT m512 EAF4 */
void CZakoMan::on_new_mode(int mode)
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

/* DRAFT (fn_1_161F4, 108 insns) */
CZako::CZako(CModel* master, const Vec* pos, bool kind) : m_unk1C(0), m_model(*master), m_kind(kind)
{
    insertBack(&s_list);
    m_yaw = 0.0f;
    m_motion = -1;
    m_speed = 0.0f;
    m_pos = *pos;
    HU3DMODELID id = m_model.id();
    Hu3DModelScaleSet(id, 1.0f, 1.0f, 1.0f);
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(id, 0);
    Hu3DModelCameraSet(id, 1);
    m_yaw = 360.0f * CRandom::randomMantissa();
    ClampArea();
    m_count = 0;
    m_phase = 360.0f * CRandom::randomMantissa() - 180.0f;
    m_model.setPos(&m_pos);
    setState(&CZako::stateSwim);
    SetCourse();
}

/* EXACT m536 E8D4 (the implicit ~CZako inlines: ~CModel, ~CLinkNode) */
void CZako::DeleteAll()
{
    while (!s_list.isEmpty()) {
        CZako* z = s_list.last();
        delete z;
    }
}

/* EXACT m512 F070 */
void CZako::UpdateAll()
{
    TLinkList<CZako>::exec(&s_list, Update);
    CZako* first = s_list.begin();
    if (first != s_list.end()) {
        first->unlink();
        first->insertBack(&s_list);
    }
}

void CZako::Update(CZako* z)
{
    (z->*(z->m_state))();
    z->ClampArea();
    z->updateModel();
    z->m_count++;
}

/* Vec setter with DOUBLE components (m512 / m509 SetVec: the yaw is loaded first, then frsp per component) */
static inline Vec& SetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
    return *v;
}

/* m512 F168 */
void CZako::updateModel()
{
    Vec rot;
    SetVec(&rot, 0.0f, m_yaw, 0.0f);
    m_model.setRot(&rot);
    m_model.setPos(&m_pos);
}

/* m512 zako F3F0 (the vector reached through the CZakoMan singleton) */
inline s16& MotionAt(std::vector<s16>& ids, int i)
{
    return ids.at(i);
}

/* out-of-line copy unreferenced: inlined into stateSwim */
void CZako::setMotion(int motion, bool once)
{
    CZakoMan* man = CSingleton<CZakoMan>::GetInstance();
    HU3DMODELID id = m_model.id();
    s16 mot = MotionAt(man->m_mot_id, motion);
    if (m_motion != motion) {
        Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
        Hu3DMotionShiftSet(id, mot, 0.0f, 8.0f, !once ? HU3D_MOTATTR_LOOP : 0);
        m_motion = motion;
    }
}

void CZako::SetCourse()
{
    m_turnTimer = CRandom::irandom() & 0x82;
    float f = 2.0f;
    m_turnRate = f * CRandom::randomMantissa() - 0.5 * f;
    m_targetSpeed = 0.5f + CRandom::randomMantissa();
}

/* DRAFT (fn_1_167B0, 140 insns) */
void CZako::stateSwim()
{
    if (--m_turnTimer < 0) {
        SetCourse();
    }
    m_speed += 0.05f * (m_targetSpeed - m_speed);
    m_yaw += m_turnRate;
    if (m_yaw > 180.0f) {
        m_yaw -= 360.0f;
    }
    if (m_yaw < -180.0f) {
        m_yaw += 360.0f;
    }
    m_speed = 1.0f; /* retail: the eased speed is overwritten */
    move();
    Hu3DMotionSpeedSet(m_model.id(), 1.0f);
    setMotion(0, false);
}

inline double GetFps() { return 60.0; }

/* DRAFT (fn_1_169E0, 162 insns): the guarded function-local static is retail's (m512 CZako::move) */
bool CZako::move()
{
    static double s_fps = GetFps();
    Mtx m;
    Vec dir;
    Vec v;
    dir.x = 0.0f;
    dir.y = 0.0f;
    dir.z = 100.0 * m_speed / s_fps;
    m_phase += 0.8333333f;
    if (m_phase > 180.0f) {
        m_phase -= 360.0f;
    }
    float a = m_yaw + 45.0 * sin(M_PI * m_phase / 180.0);
    if (a > 180.0f) {
        a -= 360.0f;
    }
    if (a < -180.0f) {
        a += 360.0f;
    }
    PSMTXRotRad(m, 'y', 0.017453292f * a);
    PSMTXMultVec(m, &dir, &v);
    m_pos.x += 100.0 * (v.x / s_fps);
    m_pos.y += 100.0 * (v.y / s_fps);
    m_pos.z += 100.0 * (v.z / s_fps);
    if (m_speed <= 0.01f) {
        return false;
    }
    return true;
}

#ifdef __MWERKS__
/* retail inlines MSL's double sqrt (frsqrte + four Newton steps, 0 / NaN / Inf cases): m536 camera's form */
inline double MslSqrt(double x)
{
    if (x > 0.0) {
        double guess = __frsqrte(x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        return x * guess;
    } else if (x == 0.0) {
        return 0;
    } else if (x) {
        return *(float*)__float_nan;
    }
    return *(float*)__float_huge;
}
#else
inline double MslSqrt(double x) { return sqrt(x); }
#endif

/* fn_1_16C68: kind 0 inside r 450, kind 1 in the ring 900..1050; true = clamped */
bool CZako::ClampArea()
{
    double x = m_pos.x;
    double z = m_pos.z;
    double d = MslSqrt(x * x + z * z);
    if (!m_kind) {
        if (d > 450.0) {
            d = 450.0 / d;
            m_pos.x = x * d;
            m_pos.z = z * d;
            return true;
        }
    } else if (d > 1050.0) {
        d = 1050.0 / d;
        m_pos.x = x * d;
        m_pos.z = z * d;
        return true;
    } else if (d < 900.0) {
        d = 900.0 / d;
        m_pos.x = x * d;
        m_pos.z = z * d;
        return true;
    }
    return false;
}

/* DRAFT (fn_1_16F3C, 197 insns) */
CJugem::CJugem() : m_body(0x85000AU), m_bait(0x85000BU), m_fish(0x850006U)
{
    m_shown = false;
    m_done = false;
    m_timer = 0;
    m_splash = false;
    CreateLineHook();
    HU3DMODELID id = m_body.id();
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(id, 3);
    Hu3DModelCameraSet(id, 1);
    id = m_bait.id();
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(id, 3);
    Hu3DModelCameraSet(id, 1);
    id = m_fish.id();
    Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(id, 0);
    Hu3DModelCameraSet(id, 1);
    static const Vec s_fishPos = { 0.0f, -500.0f, 0.0f };
    m_fish.setPos((Vec*)&s_fishPos);
    m_mot_id.clear();
    m_mot_id.reserve(NUMBEROF_PMOTION);
    createMotion(0x85000C);
    createMotion(0x85000D);
    /* line padding (CJugem ctor) */





    assert(m_mot_id.size() == NUMBEROF_PMOTION);
    m_motion = -1;
    m_pos.x = 1000.0f;
    m_pos.y = 1000.0f;
    m_pos.z = -1000.0f;
    m_vel.x = 0.0f;
    m_vel.y = 0.0f;
    m_vel.z = 0.0f;
    setState(&CJugem::stateEnter);
    m_lineOfs = -100.0f;
    m_fishYaw = 0.0f;
    m_fishPitch = 0.0f;
    m_fishAlpha = 0.0f;
}

CJugem::~CJugem()
{
    Hu3DModelKill(m_hookModel);
}

s16 CJugem::createMotion(int dataNum)
{
    s16 mot = Hu3DJointMotion(m_body.id(), HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
    m_mot_id.push_back(mot);
    return mot;
}

/* fn_1_174C8: state; the Lakitu, its bait on the line and (once shown) the fish on the bait */
void CJugem::on_update()
{
    static const Vec s_zero = { 0.0f, 0.0f, 0.0f };
    (this->*m_state)();
    m_timer++;
    if (!m_done) {
        m_body.setRot((Vec*)&s_zero);
        m_body.setPos(&m_pos);
        Vec hp;
        Hu3DModelObjPosGet(m_body.id(), (char*)"itemhook_S", &hp);
        hp.y += m_lineOfs;
        m_bait.setRot((Vec*)&s_zero);
        m_bait.setPos(&hp);
        if (m_shown) {
            if ((m_fishAlpha += 0.05) > 1.0) {
                m_fishAlpha = 1.0f;
            }
            m_fish.setTPLvl(m_fishAlpha);
            if ((m_lineOfs += 13.333333f) > -100.0f) {
                m_lineOfs = -100.0f;
            }
            m_fishYaw += 6.6666665f;
            if (m_fishYaw > 180.0f) {
                m_fishYaw -= 360.0f;
            }
            if ((m_fishPitch -= 4.5) < -90.0) {
                m_fishPitch = -90.0f;
            }
            Vec rot;
            rot.x = m_fishPitch;
            rot.y = m_fishYaw;
            rot.z = 0.0f;
            hp.y -= 50.0f;
            m_fish.setRot(&rot);
            m_fish.setPos(&hp);
            HU3DMODELID id = m_fish.id();
            Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
            if (!m_splash && hp.y > -150.0) {
                m_splash = true;
                new CSplash(&hp, 1);
                CCameraObj::PlaySe(&m_pos, 0x956);
            }
        }
    }
}

/* fn_1_17768: fly in towards (0, 50, 0) paying the line out; after 90 frames show the fish (CZakoMan's motion 0) */
void CJugem::stateEnter()
{
    static const Vec s_target = { 0.0f, 50.0f, 0.0f };
    if ((m_lineOfs -= 6.6666665f) < -400.0f) {
        m_lineOfs = -1000.0f; /* retail */
    }
    PSVECSubtract((Vec*)&s_target, &m_pos, &m_vel);
    PSVECScale(&m_vel, &m_vel, 0.1f);
    PSVECAdd(&m_pos, &m_vel, &m_pos);
    if (m_timer > 90.0f) {
        m_timer = 0;
        m_shown = true;
        CZakoMan* man = CSingleton<CZakoMan>::GetInstance();
        HU3DMODELID id = m_fish.id();
        s16& r = man->m_mot_id.at(0);
        s16 mot = r;
        Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
        Hu3DMotionShiftSet(id, mot, 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
        setState(&CJugem::stateShow);
    }
    setMotion(0, false);
}

/* fn_1_17944 */
void CJugem::stateShow()
{
    if (m_timer > 120.0f) {
        m_timer = 0;
        m_angle = 0.0f;
        setState(&CJugem::stateLeave);
    }
    setMotion(1, true);
}

/* fn_1_17A08: spiral away, rising */
void CJugem::stateLeave()
{
    m_vel.y += 1.0 / 3.0;
    m_angle += 6.6666665f;
    if (m_angle > 180.0f) {
        m_angle -= 360.0f;
    }
    float a = M_PI * m_angle / 180.0;
    float r = 5 * m_timer;
    m_pos.x = r * cos(a);
    m_pos.z = r * sin(a);
    PSVECAdd(&m_pos, &m_vel, &m_pos);
}

/* fn_1_17B40 */
void CJugem::stateHide()
{
    HU3DMODELID id;
    id = m_body.id();
    Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
    id = m_bait.id();
    Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
    id = m_fish.id();
    Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(id, HU3D_MOTATTR_PAUSE);
    m_done = true;
}

void CJugem::setMotion(int motion, bool once)
{
    HU3DMODELID id = m_body.id();
    s16& ref = m_mot_id.at(motion);
    s16 mot = ref;
    if (m_motion != motion) {
        Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
        Hu3DMotionShiftSet(id, mot, 0.0f, 8.0f, !once ? HU3D_MOTATTR_LOOP : 0);
        m_motion = motion;
    }
}

void CJugem::CreateLineHook()
{
    HU3DMODELID id = Hu3DHookFuncCreate(Hook);
    m_hookModel = (int)id;
    HU3DMODEL* model = &Hu3DData[(int)id];
    Hu3DModelLayerSet((int)id, 4);
    Hu3DModelCameraSet((int)id, 1);
    Hu3DModelPosSet((int)id, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet((int)id, 0.0f, 0.0f, 0.0f);
    model->hookData = this;
}

void CJugem::Hook(HU3DMODEL* model, Mtx* mtx)
{
    CJugem* self = (CJugem*)model->hookData;
    self->DrawLine(mtx);
}

void CJugem::DrawLine(Mtx* mtx)
{
    GXSetNumTevStages(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetCullMode(GX_CULL_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    Vec p;
    Hu3DModelObjPosGet(m_body.id(), (char*)"itemhook_S", &p);
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 2);
    GXPosition3f32(p.x, p.y, p.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, 0xFF);
    GXPosition3f32(p.x, p.y + m_lineOfs, p.z);
    GXColor4u8(0xFF, 0xFF, 0xFF, 0xFF);
    GXEnd();
}

void CJugem::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    switch (mode) {
    case 0:
    case 1:
        break;
    case 2:
        setState(&CJugem::stateHide);
        break;
    case 3:
    case 4:
        break;
    }
}

} // namespace m579
