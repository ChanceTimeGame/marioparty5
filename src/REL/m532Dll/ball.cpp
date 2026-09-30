#include "REL/m532Dll/config.h"
#include "REL/m532Dll/param.h"
#include "REL/m532Dll/ball.h"
#include "REL/m532Dll/man_map.h"
#include "REL/m532Dll/player.h"
#include "REL/m532Dll/util.h"
extern "C" {
#include "game/hsfex.h" /* Hu3DMtxRotGet */
}

namespace m532 {

/* inline helpers: their result temporaries are predict's `fmr f31,f30` (14E4) and the t^2 / n^2 computed ahead
 * of the statement into a register of their own (predict 1534, throwTo 1644) */
static inline float Square(float x)
{
    return x * x;
}

static inline float SecToFrame(float sec)
{
    return 60.0f * sec;
}

/* the reference result and parameter: Orient's `mr r30,r29` (D5C), the CBall ctor's two spilled pointer
 * temporaries (13B4..13C4) */
static inline Vec& VecNormalize(Vec& v)
{
    PSVECNormalize(&v, &v);
    return v;
}

/* a pointer through a local: with Orient's own `dir`, the two pointer temporaries of D58..D60 */
static inline void VecUnit(Vec* v)
{
    Vec* u = v;
    PSVECNormalize(u, u);
}

static inline void VecScale(Vec& v, float s)
{
    PSVECScale(&v, &v, s);
}

/* the result temporary is Orient's `fmr f27,f1; fmr f1,f27` into acos (D7C) */
static inline float VecDot(Vec* a, const Vec* b)
{
    return PSVECDotProduct(a, b);
}

/* float parameters: Orient loads the translation into three temporaries, z first (DE4..DF8) */
static inline void MtxTransApply(Mtx src, Mtx dst, float x, float y, float z)
{
    PSMTXTransApply(src, dst, x, y, z);
}

/* lbl_1_rodata_10: the four ball masters */
static const u32 s_ballModel[4] = { 0x5A0005, 0x5A0006, 0x5A0007, 0x5A0008 };

CBallMan::CBallMan()
{
    m_unk20 = -1;
    m_ropeAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x5A0009, HU_MEMNUM_OVL, HEAP_MODEL));
    for (int i = 0; i < 4; i++) {
        m_model[i].reset(new CModel(s_ballModel[i]));
        m_model[i]->setAttr(HU3D_ATTR_DISPOFF);
    }
}

CBallMan::~CBallMan() {}

CModel* CBallMan::GetModel(int kind)
{
    CModel* m = GetInstance()->m_model[kind & 3].get();
    Hu3DMotionSet(m->id(), -1);
    m->setAttr(HU3D_MOTATTR_PAUSE);
    return m;
}

s16 CBallMan::GetUnk20()
{
    return GetInstance()->m_unk20;
}

void CBallMan::LoadRopeTex()
{
    HuSprTexLoad(GetInstance()->m_ropeAnim, 0, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
}

CHangBall::CHangBall(float angleOfs, int index)
    : m_model(*CBallMan::GetModel(index)), m_angleOfs(angleOfs), m_index(index), m_shot(false)
{
    m_spinPtr = &m_model.getObjPtr("star_a")->mesh.base.rot.y;
    m_spin = index * 45;
    CModel::setLayer(4);
    m_model.setLayer(4);
    m_model.resetAttr(HU3D_ATTR_DISPOFF);
    CalcPivot();
    SetVec(&m_pos, m_pivot.x, m_pivot.y - 200.0f, m_pivot.z);
    SetVec(&m_attach, m_pos.x, m_pos.y + 40.0, m_pos.z);
    m_vel.x = 0.0f;
    m_vel.y = 0.0f;
    m_vel.z = 0.0f;
}

CHangBall::~CHangBall() {}

int CHangBall::Shoot(Vec* target)
{
    if (m_shot) {
        return 0;
    }
    m_shot = true;
    m_model.setAttr(HU3D_ATTR_DISPOFF);
    HuAudFXPlay(0x7AC);
    CBall* ball = new CBall(&m_pos, target, m_spin, m_index);
    return ball->GetHandle();
}

Vec* CHangBall::GetPos()
{
    return &m_pos;
}

u8 CHangBall::IsShot()
{
    return m_shot;
}

void CHangBall::update()
{
    Move();
    Orient();
    *m_spinPtr = m_spin;
    m_spin += 2.0;
}

void CHangBall::CalcPivot()
{
    float a = m_angleOfs + CSingleton<CMapMan>::GetInstance()->getAngle();
    m_pivot.x = 0.0f;
    m_pivot.y = 1150.0f;
    m_pivot.z = -320.0f;
    Mtx m;
    PSMTXRotRad(m, 'y', MTXDegToRad(a));
    PSMTXMultVec(m, &m_pivot, &m_pivot);
}

/* the pendulum: the rope (200) only constrains when taut; gravity x2 while hanging (retail R5) */
void CHangBall::Move()
{
    CalcPivot();
    Vec old = m_pos;
    PSVECAdd(&m_vel, &m_pos, &m_pos);
    Vec d;
    float len = VecSubMag(&m_pos, &m_pivot, &d);
    if (len > 200.0f) {
        PSVECScale(&d, &d, 200.0f / len);
        PSVECAdd(&m_pivot, &d, &m_pos);
    }
    m_model.setPos(&m_pos);
    PSVECSubtract(&m_pos, &old, &m_vel);
    PSVECScale(&m_vel, &m_vel, 0.98f);
    m_vel.y -= M532_GRAVITY * (float)(m_shot ? 1 : 2);
}

/* lbl_1_rodata_5C / 68 */
static const Vec s_up = { 0.0f, 1.0f, 0.0f };
static const Vec s_attachOfs = { 0.0f, 40.0f, 0.0f };

void CHangBall::Orient()
{
    Mtx m;
    Vec axis;
    Vec v;

    PSVECSubtract(&m_pivot, &m_pos, &v);
    Vec* dir = &v;
    VecUnit(dir);
    float a = acos(VecDot(&v, &s_up));
    if (fabs(a) <= 0.0) {
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = 0.0f;
        m_model.setRot(&v);
        PSVECAdd(&m_pos, &s_attachOfs, &m_attach);
    } else {
        PSVECCrossProduct(&v, &s_up, &axis);
        PSMTXRotAxisRad(m, &axis, -a);
        MtxTransApply(m, m, m_pos.x, m_pos.y, m_pos.z);
        PSMTXMultVec(m, &s_attachOfs, &m_attach);
        Hu3DMtxRotGet(m, &v);
        m_model.setRot(&v);
    }
}

/* lbl_1_rodata_80 / 98: the rope's vertex format */
static const GXVtxDescList s_ropeVtxDesc[] = { { GX_VA_POS, GX_DIRECT }, { GX_VA_TEX0, GX_DIRECT }, { GX_VA_NULL, GX_NONE } };
static const GXVtxAttrFmtList s_ropeVtxFmt[] = {
    { GX_VA_POS, GX_POS_XYZ, GX_F32, 0 }, { GX_VA_TEX0, GX_TEX_ST, GX_F32, 0 }, { GX_VA_NULL, GX_POS_XY, GX_U8, 0 }
};

void CHangBall::draw(Mtx* mtx)
{
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXSetNumChans(0);
    CBallMan::LoadRopeTex();
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetCullMode(GX_CULL_NONE);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetZCompLoc(GX_TRUE);
    GXSetZMode(GX_TRUE, GX_LESS, GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 255, GX_AOP_OR, GX_ALWAYS, 255);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
    GXClearVtxDesc();
    GXSetVtxDescv((GXVtxDescList*)s_ropeVtxDesc);
    GXSetVtxAttrFmtv(GX_VTXFMT0, (GXVtxAttrFmtList*)s_ropeVtxFmt);
    GXEnableTexOffsets(GX_TEXCOORD0, GX_TRUE, GX_FALSE);
    GXSetLineWidth(24, GX_TO_ONE);
    Vec* from = &m_pivot;
    Vec* to = &m_attach;
    GXBegin(GX_LINES, GX_VTXFMT0, 2);
    GXPosition3f32(from->x, from->y, from->z);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(to->x, to->y, to->z);
    GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();
}

CBall::CBall(Vec* from, Vec* to, float spin, int kind)
    : m_state(&CBall::stateFly), m_model(*CBallMan::GetModel(kind)), m_landed(false), m_pos(*from), m_target(*to)
{
    m_spinPtr = &m_model.getObjPtr("star_a")->mesh.base.rot.y;
    m_spin = spin;
    m_model.setLayer(4);
    m_model.resetAttr(HU3D_ATTR_DISPOFF);
    m_vel.x = 0.0f;
    m_vel.y = 0.0f;
    m_vel.z = 0.0f;
    PSVECSubtract(to, from, &m_accel);
    VecScale(VecNormalize(m_accel), M532_GRAVITY);
    Vec d;
    m_dist = VecSubMag(to, from, &d);
}

CBall::~CBall() {}

u8 CBall::isLanded()
{
    return m_landed;
}

Vec* CBall::getPos()
{
    return &m_pos;
}

Vec* CBall::predict(Vec* out, float sec)
{
    out->x = m_pos.x;
    out->y = m_pos.y;
    out->z = m_pos.z;
    float t = SecToFrame(sec);
    out->x += m_vel.x * t;
    out->z += m_vel.z * t;
    out->y += m_vel.y * t - M532_GRAVITY * Square(t) / 2.0f;
    return out;
}

void CBall::hold(Vec* pos)
{
    m_pos = *pos;
    setState(&CBall::stateIdle);
}

/* 54 frames to the target on a ballistic arc */
void CBall::throwTo(Vec* to)
{
    m_target = *to;
    SetVec(&m_vel, to->x - m_pos.x, 0.0f, to->z - m_pos.z);
    float n = 54.0f;
    PSVECScale(&m_vel, &m_vel, 1.0 / n);
    m_vel.y = (to->y - m_pos.y + M532_GRAVITY * Square(n) / 2.0f) / n;
    Vec d;
    m_dist = VecSubMag(to, &m_pos, &d);
    m_landed = false;
    setState(&CBall::stateThrown);
}

void CBall::update()
{
    if (!(this->*m_state)()) {
        delete this;
        return;
    }
    m_model.setPos(&m_pos);
    *m_spinPtr = m_spin;
    m_spin += 2.0;
}

bool CBall::stateIdle()
{
    return true;
}

bool CBall::stateFly()
{
    PSVECAdd(&m_vel, &m_pos, &m_pos);
    PSVECAdd(&m_accel, &m_vel, &m_vel);
    if (CheckArrive()) {
        Land();
    }
    return true;
}

void CBall::Land()
{
    m_model.resetAttr(HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
    HuAudFXPlay(0x7AE);
    setState(&CBall::stateLandWait);
}

bool CBall::stateLandWait()
{
    return Hu3DMotionEndCheck(m_model.id()) ? false : true;
}

bool CBall::stateThrown()
{
    PSVECAdd(&m_vel, &m_pos, &m_pos);
    m_vel.y -= M532_GRAVITY;
    if (CheckArrive()) {
        PlaySe(0x7B1, &m_pos);
        setState(&CBall::stateIdle);
    }
    return true;
}

bool CBall::CheckArrive()
{
    Vec d;
    float dist = VecSubMag(&m_target, &m_pos, &d);
    if (m_vel.y < 0.0f && m_pos.y <= m_target.y) {
        m_landed = true;
        m_pos.x = m_target.x;
        m_pos.y = m_target.y;
        m_pos.z = m_target.z;
    }
    m_dist = dist;
    return m_landed;
}

} // namespace m532

template <> m532::CMapMan* CSingleton<m532::CMapMan>::ms_pointer = 0;
template <> m532::CBallMan* CSingleton<m532::CBallMan>::ms_pointer = 0;
template <> m532::CObjectMan* CSingleton<m532::CObjectMan>::ms_pointer = 0;
