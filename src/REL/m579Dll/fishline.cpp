#include "REL/m579Dll/fishline.h"
#include "REL/m579Dll/player.h"
#include "REL/m579Dll/puku2.h"
#include "REL/m579Dll/camera.h"
#include "REL/mgcpp/random.h"

extern "C" {
/* exported, but its prototype is commented out in game/sprite.h (m522 sunfire precedent) */
void HuSprTexLoad(ANIMDATA* anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);
}

namespace m579 {

/* .bss in definition order: AE0 / 1260 / 1270, then the list 1280 (its DestructorChain 1274) */
static Vec s_ring[CFishLine::NUM_SEG][CFishLine::NUM_RING]; /* lbl_1_bss_AE0 rod cross-section per segment */
static ANIMDATA* s_rodTex[CFishLineMgr::NUM_ROD_TEX];       /* lbl_1_bss_1260 0x85000E..11 (locked) */
static bool s_active;                                       /* lbl_1_bss_1270 bite AI on (modes 2..3) */
TLinkList<CFishLine> CFishLine::s_lineList;

/* (fn_1_10C84, 268 insns): 4 rod textures (four explicit reads, then a lock loop; four loop counters as retail), the ring table
 * (ring i radius 0.25 (24 - i), 8 points at 45 degrees, y 0), then 12 lines at 540 (cos a, 0, sin a),
 * a = 15 + 30 i degrees, yaw -a - 90 (results dropped: they live on s_lineList) */
CFishLineMgr::CFishLineMgr()
{
    int i;
    int j;
    int k;
    int n;
    s_active = 0;
    s_rodTex[0] = HuSprAnimRead(HuDataSelHeapReadNum(0x85000E, HU_MEMNUM_OVL, HEAP_MODEL));
    s_rodTex[1] = HuSprAnimRead(HuDataSelHeapReadNum(0x85000F, HU_MEMNUM_OVL, HEAP_MODEL));
    s_rodTex[2] = HuSprAnimRead(HuDataSelHeapReadNum(0x850010, HU_MEMNUM_OVL, HEAP_MODEL));
    s_rodTex[3] = HuSprAnimRead(HuDataSelHeapReadNum(0x850011, HU_MEMNUM_OVL, HEAP_MODEL));
    for (k = 0; k < NUM_ROD_TEX; k++) {
        HuSprAnimLock(s_rodTex[k]);
    }
    for (i = 0; i < CFishLine::NUM_SEG; i++) {
        float r = 0.25f * (24 - i);
        for (j = 0; j < CFishLine::NUM_RING; j++) {
            s_ring[i][j].x = r * cos(M_PI * (j * 45) / 180.0);
            s_ring[i][j].y = 0.0f;
            s_ring[i][j].z = r * sin(M_PI * (j * 45) / 180.0);
        }
    }
    for (n = 0; n < NUM_LINE; n++) {
        float a = 15.0f + 30.0f * n;
        Vec pos;
        pos.x = 540.0 * cos(M_PI * a / 180.0);
        pos.y = 0.0f;
        pos.z = 540.0 * sin(M_PI * a / 180.0);
        new CFishLine(&pos, n, -a - 90.0f);
    }
}

CFishLineMgr::~CFishLineMgr()
{
    CFishLine::DeleteAll();
    for (int i = 0; i < NUM_ROD_TEX; i++) {
        HuSprAnimKill(s_rodTex[i]);
    }
}

void CFishLineMgr::on_update()
{
    CFishLine::UpdateAll();
}

/* compare chain (3, >=, 2, 0, 5): 2 on, 3 off, 0 / 1 / 4 empty */
void CFishLineMgr::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    switch (mode) {
    case 0:
    case 1:
        break;
    case 2:
        s_active = 1;
        break;
    case 3:
        s_active = 0;
        break;
    case 4:
        break;
    }
}

/* EXACT m537 center_obj CRope::Hook 10888 (hookData by field name: +0x120 on GC) */
void CFishLine::Hook(HU3DMODEL* model, Mtx* mtx)
{
    CFishLine* self = (CFishLine*)model->hookData;
    self->Draw(mtx);
}

/* (fn_1_11308, 172 insns; sheet §2.2 order): pos, idx, yaw, the flags 1C..20 / 444 / 445 = 0, length
 * 600, bite 8, timer 0, idle 240, tension 0, target 2, kick 0, pitch 40, owner / fish 0, insertBack, the hook model
 * (layer 4, camera 1, pos / rot 0, hookData = this), m_phase = irandom(), initRope (fishman), 20 x (bend 0, identity),
 * axis (1, 0, 0), tip / prevTip 0 */
CFishLine::CFishLine(const Vec* pos, int idx, float yaw) : m_pos(*pos), m_idx(idx), m_yaw(yaw)
{
    m_taken = false;
    m_held = false;
    m_holdStart = false;
    m_wasFree = false;
    m_justReleased = false;
    m_drawn = false;
    m_tipValid = false;
    m_length = 600.0f;
    m_bite = BITE_NONE;
    m_biteTimer = 0;
    m_idle = 240;
    m_tension = 0.0f;
    m_tensionTarget = 2.0f;
    m_kick = 0.0f;
    m_pitch = 40.0f;
    m_owner = 0;
    m_fish = 0;
    insertBack(&s_lineList);
    HU3DMODELID id = Hu3DHookFuncCreate(Hook);
    m_hookModel = (int)id;
    HU3DMODEL* model = &Hu3DData[(int)id];
    Hu3DModelLayerSet((int)id, 4);
    Hu3DModelCameraSet((int)id, 1);
    Hu3DModelPosSet((int)id, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet((int)id, 0.0f, 0.0f, 0.0f);
    model->hookData = this;
    m_phase = CRandom::irandom();
    initRope();
    for (int i = 0; i < NUM_SEG; i++) {
        m_bend[i] = 0.0f;
        PSMTXIdentity(m_segMtx[i]);
    }
    m_axis.x = 1.0f;
    m_axis.y = 0.0f;
    m_axis.z = 0.0f;
    m_tip.x = 0.0f;
    m_tip.y = 0.0f;
    m_tip.z = 0.0f;
    m_prevTip.x = 0.0f;
    m_prevTip.y = 0.0f;
    m_prevTip.z = 0.0f;
}

/* EXACT m536 killereff 779C (+ the hook model): unreferenced, inlined in DeleteAll */
CFishLine::~CFishLine()
{
    Hu3DModelKill(m_hookModel);
}

/* EXACT m536 killereff 7804 */
void CFishLine::DeleteAll()
{
    while (!s_lineList.isEmpty()) {
        CFishLine* p = s_lineList.last();
        delete p;
    }
}

void CFishLine::UpdateAll()
{
    TLinkList<CFishLine>::exec(&s_lineList, UpdateFunc);
}

/* the LAST free line within 70 (xz), not the nearest (retail) */
CFishLine* CFishLine::FindFree(const Vec* p)
{
    CFishLine* found = 0;
    CFishLine* l = s_lineList.begin();
    CLinkNode* e = s_lineList.end();
    for (; l != e; l = l->next()) {
        float dx = l->m_pos.x - p->x;
        float dz = l->m_pos.z - p->z;
        if (!l->m_taken && dx * dx + dz * dz < 4900.0f) {
            found = l;
        }
    }
    return found;
}

bool CFishLine::IsBiting(const Vec* p)
{
    CFishLine* l = s_lineList.begin();
    CLinkNode* e = s_lineList.end();
    for (; l != e; l = l->next()) {
        if (l->m_bite < BITE_NONE && !l->m_taken) {
            float dx = l->m_pos.x - p->x;
            float dz = l->m_pos.z - p->z;
            if (dx * dx + dz * dz < 4900.0f) {
                return true;
            }
        }
    }
    return false;
}

bool CFishLine::IsBigBite()
{
    CFishLine* l = s_lineList.begin();
    CLinkNode* e = s_lineList.end();
    for (; l != e; l = l->next()) {
        if (l->m_bite == BITE_BIG) {
            return true;
        }
    }
    return false;
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
/* host: libm sqrt (no __float_nan/__float_huge on the host) */
inline double MslSqrt(double x) { return sqrt(x); }
#endif

/* (fn_1_11990, 169 insns): the nearest free, biting line (xz distance, start 2000), or 0 */
CFishLine* CFishLine::FindNearestBiting(const Vec* p)
{
    CFishLine* found = 0;
    CFishLine* l = s_lineList.begin();
    CLinkNode* e = s_lineList.end();
    float best = 2000.0f;
    for (; l != e; l = l->next()) {
        if (l->m_bite < BITE_NONE && !l->m_taken) {
            float dx = l->m_pos.x - p->x;
            float dz = l->m_pos.z - p->z;
            float d = MslSqrt(dx * dx + dz * dz);
            if (d < best) {
                best = d;
                found = l;
            }
        }
    }
    return found;
}

/* (fn_1_11C34, 126 insns; leaf) */
float CFishLine::GetDistXZ(const Vec* p)
{
    float dx = m_pos.x - p->x;
    float dz = m_pos.z - p->z;
    return MslSqrt(dx * dx + dz * dz);
}

/* (fn_1_11E2C, 232 insns; sheet §3.1): held: kick the target to 15 once, then ease; m_holdCount++.
 * Else the bite timer / per-kind tension targets; while active, free and the hook is under water, a new bite may
 * start (idle > 300, 1/512): kind irandom() & 7 (7 only if no big bite yet), timer 300 + 120 rand, SE 0x95C */
void CFishLine::UpdateBite()
{
    if (m_held) {
        if (!m_holdStart) {
            m_holdStart = true;
            m_tensionTarget = 15.0f;
        } else {
            m_tensionTarget += 0.2f * (1.0f - m_tensionTarget);
        }
        m_holdCount++;
        return;
    }
    if (--m_biteTimer < 0) {
        m_bite = BITE_NONE;
    }
    switch (m_bite) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        if ((CRandom::irandom() & 7) == 0) {
            m_tensionTarget = 4.0f;
        } else {
            m_tensionTarget += 0.1f * (3.2f - m_tensionTarget);
        }
        break;
    case BITE_BIG:
        if ((CRandom::irandom() & 7) == 0) {
            m_tensionTarget = 5.0f;
        } else {
            m_tensionTarget += 0.1f * (4.0f - m_tensionTarget);
        }
        break;
    default:
        if (m_under[NUM_NODE - 1]) {
            m_tensionTarget = 2.0 + 0.5 * sin(M_PI * (360.0f * ((m_phase & 0xFF) / 255.0f)) / 180.0);
        } else {
            m_tensionTarget += 0.1f * (2.0f - m_tensionTarget);
        }
        /* a new bite starts only from the empty state (retail: inside the default case) */
        if (s_active && !m_taken && m_under[NUM_NODE - 1]) {
            if (m_idle++ > 300.0f && (CRandom::irandom() & 0x1FF) == 0) {
                int n = CRandom::irandom() & 7;
                if (n == BITE_BIG && IsBigBite()) {
                    n = 0;
                }
                m_bite = n;
                m_biteTimer = 300.0f + CRandom::randomMantissa() * 120.0f;
                m_idle = 0;
                CCameraObj::PlaySe(&m_pos, 0x95C);
            }
        }
        break;
    }
}

/* (fn_1_121CC, 168 insns; unreferenced, inlined in Update): l = Transpose(segMtx[2]) hook, axis =
 * (0, 1, 0) x l, tension eased 0.1 toward the target, k = tension |l.xz| (double sqrt), bend[i] = 0.0003 k (1 + 1.1 i) */
void CFishLine::CalcBend()
{
    static const Vec s_up = { 0.0f, 1.0f, 0.0f }; /* rodata_658 */
    Mtx m;
    Vec l;
    PSMTXTranspose(m_segMtx[2], m);
    PSMTXMultVec(m, &m_hook, &l);
    PSVECCrossProduct((Vec*)&s_up, &l, &m_axis);
    m_tension += 0.1f * (m_tensionTarget - m_tension);
    float k = m_tension * MslSqrt(l.x * l.x + l.z * l.z);
    for (int i = 1; i < NUM_SEG; i++) {
        float b = 0.0003 * k * (1.0f + 1.1f * i);
        m_bend[i] = b;
    }
}

/* (fn_1_1246C, 391 insns; sheet §3.1): UpdateBite; pitch eased 0.2 toward 30; the line length (tip
 * farther than 370 (xz): -16.666666 to >= 100, else +50 to <= 600); the kick / release flags; once drawn: the tip
 * delta (0 on the release frame), fishman updateHook / updateRope, prevTip = tip; CalcBend (inline) */
void CFishLine::Update()
{
    UpdateBite();
    m_pitch += 0.2f * (30.0 - m_pitch);
    if (m_tipValid) {
        float x = m_tip.x;
        float z = m_tip.z;
        float d = sqrtf(x * x + z * z);
        if (d > 370.0000047683716) {
            m_length -= 16.666666f;
            if (m_length < 100.0f) {
                m_length = 100.0f;
            }
        } else {
            m_length += 50.0f;
            if (m_length > 600.0f) {
                m_length = 600.0f;
            }
        }
    }
    if (m_held) {
        m_kick = 20.0f;
        m_wasFree = false;
        m_justReleased = false;
    } else {
        m_kick *= 0.95;
        if (!m_wasFree) {
            m_justReleased = true;
        } else {
            m_justReleased = false;
        }
        m_wasFree = true;
    }
    if (m_drawn) {
        if (!m_tipValid) {
            m_tipValid = true;
            m_prevTip = m_tip;
        }
        Vec delta;
        if (m_justReleased) {
            delta.x = 0.0f;
            delta.y = 0.0f;
            delta.z = 0.0f;
        } else {
            PSVECSubtract(&m_tip, &m_prevTip, &delta);
        }
        bool r = updateHook(&delta);
        updateRope(&delta, r);
        m_prevTip = m_tip;
        CalcBend();
    }
}

void CFishLine::UpdateFish()
{
    if (m_fish) {
        Vec pos;
        Vec rot = { 0.0f, 0.0f, 0.0f };
        PSVECAdd(&m_tip, &m_hook, &pos);
        float hx = -m_hook.x;
        float hz = -m_hook.z;
        if (0.0f != hx || 0.0f != hz) {
            Vec up = { 0.0f, 1.0f, 0.0f };
            Vec h = m_hook;
            PSVECNormalize(&up, &up);
            PSVECNormalize(&h, &h);
            float dot = PSVECDotProduct(&up, &h);
            float pitch = -90.0 + 180.0 * (acos(dot) / M_PI);
            rot.x = -pitch;
            m_fishYaw = rot.y = 180.0 * (atan2(hx, hz) / M_PI);
        } else {
            rot.x = (hz > 0.0f) ? 90.0f : -90.0f;
            rot.y = m_fishYaw;
        }
        CPuku* fish = m_fish;
        fish->m_pos.x = pos.x;
        fish->m_pos.y = pos.y;
        fish->m_pos.z = pos.z;
        fish->m_rot.x = rot.x;
        fish->m_rot.y = rot.y;
        fish->m_rot.z = rot.z;
        fish->m_rot.z = 0.0f;
    }
}

void CFishLine::UpdateFunc(CFishLine* p)
{
    p->Update();
    p->UpdateFish();
}

/* (fn_1_12F38, 55 insns; unreferenced, inlined in Draw): the line's vertex colour pass */
void CFishLine::SetupLineGX()
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
}

void CFishLine::SetupRodGX(int tex)
{
    Mtx m;
    HuSprTexLoad(s_rodTex[tex], 0, GX_TEXMAP0, GX_REPEAT, GX_CLAMP, GX_LINEAR);
    PSMTXIdentity(m);
    GXLoadTexMtxImm(m, GX_TEXMTX0, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetZMode(GX_TRUE, GX_LESS, GX_TRUE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetChanCtrl(GX_COLOR_NULL, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_COPY);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
}

void CFishLine::CalcRodMtx()
{
    Mtx base;
    Mtx rotX;
    Mtx rotY;
    Mtx m;
    Quaternion q;
    int i;
    if (m_held) {
        m_owner->getHandMtx(base);
    } else {
        PSMTXRotRad(rotY, 'y', 0.017453292f * m_yaw);
        PSMTXRotRad(rotX, 'x', 0.017453292f * (m_pitch + m_kick));
        PSMTXConcat(rotY, rotX, base);
        PSMTXTransApply(base, base, m_pos.x, m_pos.y, m_pos.z);
    }
    for (i = 0; i < NUM_SEG; i++) {
        if (i == 0) {
            PSMTXCopy(base, m_segMtx[i]);
        } else {
            {
                C_QUATRotAxisRad(&q, &m_axis, M_PI * m_bend[i] / 180.0);
                PSMTXQuat(m, &q);
            }
            PSMTXTransApply(m, m, 0.0f, 20.0f, 0.0f);
            PSMTXConcat(m_segMtx[i - 1], m, m_segMtx[i]);
        }
    }
}

/* (fn_1_132F4, 225 insns; unreferenced, inlined in Draw): 30-vertex white line strip (width 6) of
 * node + tip; on the shore ring (500 < d < 800) below y 5 retail stores node.y - (5 + tip.y) (a slip, kept) and
 * draws at y 5; m_under[i] = world y < -150 */
void CFishLine::DrawLine(const Vec* tip)
{
    int i;
    GXSetLineWidth(6, GX_TO_ZERO);
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, NUM_NODE);
    for (i = 0; i < NUM_NODE; i++) {
        float x = m_node[i].x + tip->x;
        float y = m_node[i].y + tip->y;
        float z = m_node[i].z + tip->z;
        double d = MslSqrt(x * x + z * z);
        if (d > 500.0 && d < 800.0 && y < 5.0f) {
            m_node[i].y -= 5.0f + tip->y;
            y = 5.0f;
        }
        if (y < -150.0) {
            m_under[i] = 1;
        } else {
            m_under[i] = 0;
        }
        GXPosition3f32(x, y, z);
        GXColor4u8(0xFF, 0xFF, 0xFF, 0xFF);
    }
    GXEnd();
}

/* lbl_1_data_554 / 584: the rod texture per line and the strip s coordinates (the float running sum
 * -0.15f + 0.125f k: exact bytes, not the nearest literals of -0.025 / 0.1 / 0.225). Non-const: .data. */
static int s_rodTexNo[CFishLineMgr::NUM_LINE] = { 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3 };
static float s_rodS[CFishLine::NUM_RING + 1] = {
    -0.150000006f, -0.025000006f, 0.099999994f, 0.224999994f, 0.349999994f,
    0.474999994f,  0.600000024f,  0.725000024f, 0.850000024f,
};

/* (fn_1_13678, 602 insns; frame 0x9B0): PNMTX0 = view; CalcRodMtx (inline); the rod vertices
 * local[i][j] = segMtx[i] s_ring[i][j]; SetupRodGX(s_rodTexNo[idx]); 19 strips of 18 (s_rodS[j], (20 - i) / 20);
 * tip = segMtx[19] (0, 0, 0); SetupLineGX; DrawLine(&tip); m_drawn = 1 */
void CFishLine::Draw(Mtx* mtx)
{
    static const Vec s_zero = { 0.0f, 0.0f, 0.0f }; /* rodata_6E8 */
    Vec local[NUM_SEG][NUM_RING];
    int i;
    int j;
    int k;
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    CalcRodMtx();
    for (i = 0; i < NUM_SEG; i++) {
        for (j = 0; j < NUM_RING; j++) {
            PSMTXMultVec(m_segMtx[i], &s_ring[i][j], &local[i][j]);
        }
    }
    SetupRodGX(s_rodTexNo[m_idx]);
    for (i = 0; i < NUM_SEG - 1; i++) {
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, (NUM_RING + 1) * 2);
        for (j = 0; j < NUM_RING + 1; j++) {
            k = j & (NUM_RING - 1);
            GXPosition3f32(local[i + 1][k].x, local[i + 1][k].y, local[i + 1][k].z);
            GXTexCoord2f32(s_rodS[j], (20 - (i + 1)) / 20.0f);
            GXPosition3f32(local[i][k].x, local[i][k].y, local[i][k].z);
            GXTexCoord2f32(s_rodS[j], (20 - i) / 20.0f);
        }
        GXEnd();
    }
    PSMTXMultVec(m_segMtx[NUM_SEG - 1], (Vec*)&s_zero, &m_tip);
    SetupLineGX();
    DrawLine(&m_tip);
    m_drawn = true;
}

/* (fn_1_13FE0, 27 insns): no bite (8): no fish; else claim a free Cheep Cheep (big for kind 7) */
void CFishLine::HookFish()
{
    if (m_bite > BITE_BIG) {
        m_fish = 0;
    } else {
        int big = 1;
        if (m_bite < BITE_BIG) {
            big = 0;
        }
        m_fish = CPuku::Catch(this, big);
    }
}

void CFishLine::ReleaseFish(bool escape)
{
    if (m_fish) {
        m_fish->Launch(escape);
        m_fish = 0;
    }
}

} // namespace m579
