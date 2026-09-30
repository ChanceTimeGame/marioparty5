/* cleaneff.cpp -- CCleanEffMan and CCleanEff (cleaneff.h), in retail order. The MSL pieces come out of this unit:
 * ~auto_ptr<CCleanEff> (D7F0) and ~CSingleton<CCleanEffMan> (D86C) weak copies after the manager's ctor, the three
 * vector<float> dtor levels (DD90/DE24/DEB0) after CCleanEff's ctor, and __vector_pod<float>::resize/erase/insert
 * (110C8/11178/11220) from makeBrush's `m_brush.resize(w * h)` (its default `const float&` fill is data_49C).
 * Skeleton: `STUB (fn_1_XXXX, N insns)` bodies are placeholders; behaviour in the W0 sheet
 * (../20260925-m531-w0/game/cleaneff_effect_score_stage.md §2-§4, §7-§8). */
#include "REL/m531Dll/cleaneff.h"
extern "C" {
#include "game/frand.h"
void HuSprTexLoad(ANIMDATA* anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);
}

namespace m531 {

/* File-local inline helpers (CW -O0 + inline auto: every one is inlined; their shapes decide identity). Unnamed
 * namespace: other m531 units define their own Square/SetVec/... and a host link must not merge them.
 * Min/Max: a plain ternary (the result is copied twice before use: makeBrush ED50.., paint F2F8.., ratioInRect F854..);
 * Clamp: early returns (no copy: toTexel, paint); Square(const T&) as m501. */
namespace {

template <class T> inline T Min(T a, T b)
{
    return a < b ? a : b;
}

template <class T> inline T Max(T a, T b)
{
    return a > b ? a : b;
}

template <class T> inline T Square(const T& v)
{
    return v * v;
}

template <class T> inline T Clamp(T v, T lo, T hi)
{
    if (v < lo) {
        return lo;
    }
    if (v > hi) {
        return hi;
    }
    return v;
}

/* vector<float> begin() as a raw pointer. Retail copies begin() one temporary more than the in-tree <vector>
 * gives (makeBrush EC5C.., paint F394..); m501's nested inline with a pointer conversion reproduces it (m501
 * player.cpp VecBegin; probably MSL's own scalar begin() -- reported). The host's iterators are classes. */
template <class T> inline T* VecBegin(std::vector<T>& v)
{
    return (T*)v.begin();
}

/* byte offset of texel (x, y) in the 16-wide IA8 ripple texture (4x4 texel tiles, 2 bytes per texel) */
inline int TexelIA8(int x, int y)
{
    return ((x & 3) + (y & 3) * 4 + (x >> 2) * 16 + (y >> 2) * 4 * 16) * 2;
}

/* m501/m536/m539's SetVec: double components give the frsp per stored component (ratioInRect) */
inline Vec& SetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
    return *v;
}

} // namespace

/* ---- CCleanEffMan ---- */

CCleanEffMan::CCleanEffMan(Process_s* om)
{
    m_eff0.reset(new CCleanEff(om, -525.0f, -125.0f, -230.0f, 610.0f));
    m_eff1.reset(new CCleanEff(om, 125.0f, 525.0f, -230.0f, 610.0f));
    m_eff1->setGrow(1.0f);
}

CCleanEffMan::~CCleanEffMan() {}

int CCleanEffMan::judge(bool timeUp)
{
    int a = (int)(100.0f * m_eff0->ratio());
    int b = (int)(100.0f * m_eff1->ratio());

    if (timeUp) {
        if (a > b) {
            return 0;
        }
        if (a < b) {
            return 1;
        }
        return 2;
    }
    if (a >= 100 && b < 100) {
        return 0;
    }
    if (b >= 100 && a < 100) {
        return 1;
    }
    return 2;
}

CCleanEff* CCleanEffMan::get(int team)
{
    switch (team) {
    case 0:
        return m_eff0.get();
    case 1:
        return m_eff1.get();
    default:
        return m_eff0.get();
    }
}

/* ---- CCleanEff ---- */

CCleanEff::CCleanEff(Process_s* om, float minX, float maxX, float minZ, float maxZ)
    : CHookEffect(om, 2, 5, 1), m_total(128 * 128), m_threshold(16.0f), m_painted(false), m_dirtyCount(0),
      m_minX(minX), m_maxX(maxX), m_minZ(minZ), m_maxZ(maxZ), m_grow(0.0f), m_brushSize(65.0f), m_brushW(0),
      m_brushH(0), m_scrollU(0.0f), m_scrollV(0.0f), m_seNo(minX < 0.0f ? 0x7A8 : 0x7A9), m_seHandle(-1),
      m_phase(minX < 0.0f ? 0 : 5), m_frame(0)
{
    /* the (double) casts give retail's frsp before each store (DCEC, DD30) */
    m_center.x = (double)((minX + maxX) / 2.0f);
    m_center.y = 0.0f;
    m_center.z = (double)(0.75f * minZ + 0.25f * maxZ);
    initDirt();
    initRipple();
    loadAnim();
}

CCleanEff::~CCleanEff()
{
    stopSound();
}

void CCleanEff::initDirt()
{
    /* 14-lobed egg of value 240 with a cosine rim; retail's rim start is the double 1.0 - (double)0.08f
     * (rodata 698 = 0.9200000017881393), not 0.92f */
    const double rimWidth = 0.08f;
    const double rimStart = 1.0 - rimWidth;
    float* p = &m_dirt[0][0];
    int n = 0;

    for (float z = -1.4921875f; z < 0.5f; z += 0.015625f) {
        for (float x = -0.9921875f; x < 1.0; x += 0.015625f) {
            float v = z < 0.0f ? z / -1.5f : z / 0.5f;
            float a = 14.0f * atanf(x / v);
            float r = 0.05 * sin(a) + 1.05 * (Square(x) + Square(v));
            float d = r < 1.0f ? (r <= rimStart ? 240.0 : 240.0 * cos(1.5707963267948966 * ((r - rimStart) / rimWidth))) : 0.0;
            if (d >= m_threshold) {
                n++;
            }
            *p++ = d;
        }
    }
    m_dirtyCount = n;
    GXInitTexObj(&m_dirtTex, m_dirtTexData, 128, 128, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
}

void CCleanEff::initRipple()
{
    for (int row = 0; row < 32; row++) {
        for (int col = 0; col < 16; col++) {
            int i = TexelIA8(col, row);
            float fx = 2 * col / 16.0f - 1.0f;
            float fz = 2 * row / 32.0f - 1.0f;
            float t = 9.42477796076938 * (Square(fx) + Square(fz));
            m_rippleTexData[i] = 128.0 + 24.0 * sin(t);
            m_rippleTexData[i + 1] = 128.0 + 48.0 * cos(t);
        }
    }
    DCFlushRange(m_rippleTexData, sizeof(m_rippleTexData));
    GXInitTexObj(&m_rippleTex, m_rippleTexData, 16, 32, GX_TF_IA8, GX_REPEAT, GX_REPEAT, GX_FALSE);
}

void CCleanEff::loadAnim()
{
    m_anim = HuSprAnimRead(HuDataSelHeapReadNum(0x590005, HU_MEMNUM_OVL, HEAP_MODEL));
}

int CCleanEff::ConvTileI8(u8*& dst, const float* src, int stride, int threshold)
{
    int count = 0;
    int row;

    for (row = 0; row < 4; row++) {
        u8 buf[8];
        int col;
        for (col = 0; col < 8; col++) {
            float v = src[col];
            buf[col] = v;
            count += v >= threshold ? 1 : 0;
        }
        /* one 8-texel row as a 64-bit copy (retail E63C: lwz/lwz, stw lo/stw hi) */
        *(u64*)dst = *(u64*)buf;
        src += stride;
        dst += sizeof(buf);
    }
    return count;
}

void CCleanEff::updateTexture()
{
    if (m_phase == 4) {
        u8* dst = m_dirtTexData;
        int count = 0;
        int tz;
        for (tz = 0; tz < 128; tz += 4) {
            int tx;
            for (tx = 0; tx < 128; tx += 8) {
                count += ConvTileI8(dst, &m_dirt[tz][tx], 128, (int)m_threshold);
            }
        }
        DCFlushRangeNoSync(m_dirtTexData, sizeof(m_dirtTexData));
        m_dirtyCount = count;
    }
}

int CCleanEff::toTexel(const Vec* p, int* tx, int* tz)
{
    float w = m_maxX - m_minX;
    float d = m_maxZ - m_minZ;
    float px = p->x - m_minX;
    float pz = p->z - m_minZ;
    *tx = 128.0f * px / w;
    *tz = 128.0f * pz / d;
    bool out = *tx < 0 || *tx >= 128 || *tz < 0 || *tz >= 128;
    if (out) {
        *tx = Clamp(*tx, 0, 127);
        *tz = Clamp(*tz, 0, 127);
    }
    return out;
}

void CCleanEff::makeBrush(float size)
{
    if (m_brush.size() != 0 && m_brushSize == size) {
        return;
    }
    Vec v = {0.0f, 0.0f, 0.0f};
    v.x = m_minX + size;
    v.z = m_minZ + size;
    int w;
    int h;
    toTexel(&v, &w, &h);
    w &= ~1;
    if (w < 2 || h < 2) {
        m_brush.clear();
        m_brushSize = 0.0f;
        m_brushW = 0;
        m_brushH = 0;
        return;
    }
    m_brush.resize(w * h);
    float* dst = VecBegin(m_brush);
    float sx = 2.0 / w;
    float sz = 2.0 / h;
    for (float z = -1.0 + sz / 2.0; z < 1.0; z += sz) {
        for (float x = -1.0 + sx / 2.0; x < 1.0; x += sx) {
            float b = 1.0f - Min(Square(x) + Square(z), 1.0f);
            *dst++ = b;
        }
    }
    m_brushSize = size;
    m_brushW = w;
    m_brushH = h;
}

void CCleanEff::paint(const Vec* pos, float size, float amount)
{
    /* retail: paints only on phase-0 frames, so 5 of 6 clean() calls are no-ops (sheet R3) */
    if (m_phase != 0) {
        return;
    }
    size = fabs(size);
    makeBrush(size);
    Vec lo = {0.0f, 0.0f, 0.0f};
    lo.x = pos->x - size / 2.0f;
    lo.z = pos->z - size / 2.0f;
    Vec hi = {0.0f, 0.0f, 0.0f};
    hi.x = pos->x + size / 2.0f;
    hi.z = pos->z + size / 2.0f;
    int tx0;
    int tz0;
    toTexel(&lo, &tx0, &tz0);
    int tx1;
    int tz1;
    toTexel(&hi, &tx1, &tz1);
    if (tx0 == tx1 || tz0 == tz1) {
        return;
    }
    int w = Min(tx1 - tx0 + 1, m_brushW) & ~1;
    int h = Min(tz1 - tz0 + 1, m_brushH);
    float* dst = &m_dirt[tz0][tx0];
    float* src = VecBegin(m_brush);
    if (w < m_brushW && tx0 == 0) {
        src += m_brushW - w;
    }
    if (h < m_brushH && tz0 == 0) {
        src += m_brushW * (m_brushH - h);
    }
    bool changed = false;
    for (int z = 0; z < h; z++) {
        for (int x = 0; x < w; x += 2) {
            float d0 = dst[x];
            float d1 = dst[x + 1];
            float pair[2] = {0.0f, 0.0f};
            pair[0] = Clamp(d0 + amount * src[x], 0.0f, 255.0f);
            pair[1] = Clamp(d1 + amount * src[x + 1], 0.0f, 255.0f);
            *(u64*)&dst[x] = *(u64*)pair; /* retail: one 64-bit copy (lwz x2, stw +4 then +0) */
            /* retail bug (F544..F558): the second test compares d0, not d1, with the new second texel */
            if (d0 != pair[0] || d0 != pair[1]) {
                changed = true;
            }
        }
        src += m_brushW;
        dst += 128;
    }
    m_painted = changed;
}

void CCleanEff::soil(const Vec* pos, float size)
{
    paint(pos, size, 32.0f);
}

void CCleanEff::clean(const Vec* pos, float size)
{
    paint(pos, size, -160.0f);
}

void CCleanEff::setCenter(const Vec* p)
{
    m_center = *p;
}

void CCleanEff::setGrow(float t)
{
    float v;
    if (t < 0.0f) {
        v = 0.0f;
    } else if (t > 1.0f) {
        v = 1.0f;
    } else {
        v = t;
    }
    m_grow = v;
}

float CCleanEff::ratio()
{
    return 1.0f - (float)m_dirtyCount / (float)m_total;
}

float CCleanEff::ratioInRect(const Vec* a, const Vec* b)
{
    Vec lo;
    SetVec(&lo, Min(a->x, b->x), 0.0f, Min(a->z, b->z));
    Vec hi;
    SetVec(&hi, Max(a->x, b->x), 0.0f, Max(a->z, b->z));
    int tx0;
    int tz0;
    toTexel(&lo, &tx0, &tz0);
    int tx1;
    int tz1;
    toTexel(&hi, &tx1, &tz1);
    if (tx0 == tx1 || tz0 == tz1) {
        return 1.0f;
    }
    float area = (tx1 - tx0) * (tz1 - tz0);
    float clean = area;
    for (int z = tz0; z < tz1; z++) {
        for (int x = tx0; x < tx1; x++) {
            clean -= m_dirt[z][x] < m_threshold ? 0 : 1;
        }
    }
    return clean / area;
}

/* erode's clamp (retail FFD8: a float max inlined, two register copies) */
static inline float ErodeMax(float a, float b)
{
    return a > b ? a : b;
}

void CCleanEff::erode()
{
    if (m_phase == 2) {
        float step = 3.1875f;
        int count = 0;
        int z;
        for (z = 0; z < 128; z++) {
            int x;
            for (x = 0; x < 128; x++) {
                float* p = &m_dirt[z][x];
                if (*p <= 0.0f) {
                    continue;
                }
                {
                    float left = x > 0 ? m_dirt[z][x - 1] : 0.0f;
                    float right = x < 127 ? m_dirt[z][x + 1] : 0.0f;
                    float up = z > 0 ? m_dirt[z - 1][x] : 0.0f;
                    float down = z < 127 ? m_dirt[z + 1][x] : 0.0f;
                    if (left <= 0.0f || right <= 0.0f || up <= 0.0f || down <= 0.0f) {
                        *p = ErodeMax(0.0f, *p - step);
                    }
                    if (*p >= m_threshold) {
                        count++;
                    }
                }
            }
        }
        m_dirtyCount = count;
    }
}

void CCleanEff::updateScroll()
{
    float t = 2.0 * M_PI * ((float)m_frame / 7200.0f);

    /* rodata 768 is the float 0x3A03126E, one ulp below 0.0005f (a folded quotient in the original, e.g.
     * 3.6f / 7200: unknown) -- spelled as its exact value */
    m_scrollU += 0.00049999997f * sin(t);
    m_scrollV += 0.00049999997f * cos(t);
    if (m_scrollU > 1.0f) {
        m_scrollU -= 1.0f;
    } else if (m_scrollU < 0.0f) {
        m_scrollU += 1.0f;
    }
    if (m_scrollV > 1.0f) {
        m_scrollV -= 1.0f;
    } else if (m_scrollV < 0.0f) {
        m_scrollV += 1.0f;
    }
}

void CCleanEff::startSound()
{
    if (m_seHandle < 0) {
        m_seHandle = HuAudFXPlay(m_seNo);
    }
}

void CCleanEff::stopSound()
{
    if (m_seHandle >= 0) {
        HuAudFXStop(m_seHandle);
        m_seHandle = -1;
    }
}

void CCleanEff::on_update()
{
    if (m_phase == 0) {
        if (m_painted) {
            startSound();
        } else {
            stopSound();
        }
        m_painted = false;
    }
    erode();
    updateTexture();
    updateScroll();
    if (++m_phase >= 6) {
        m_phase = 0;
    }
    ++m_frame;
}

/* draw's quad corners grow from m_center to the full rectangle (retail 10D34: an inline lerp, the results
 * round-trip through the stack) */
static inline float GrowLerp(float a, float b, double t)
{
    return (1.0 - t) * a + t * b;
}

void CCleanEff::draw(Mtx* mtx)
{
    static const f32 indMtx[2][3] = { { 0.1f, 0.0f, 0.0f }, { 0.0f, 0.1f, 0.0f } };
    float t;
    float x0;
    float x1;
    float z0;
    float z1;
    float y;
    float u0;
    float u1;
    float v0;
    float v1;

    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXSetNumChans(0);
    HuSprTexLoad(m_anim, 0, GX_TEXMAP0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXLoadTexObj(&m_rippleTex, GX_TEXMAP1);
    GXLoadTexObj(&m_dirtTex, GX_TEXMAP2);
    GXSetNumTexGens(2);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumIndStages(1);
    GXSetIndTexMtx(GX_ITM_0, (f32(*)[3])indMtx, 0); /* the SDK prototype is non-const */
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD0, GX_TEXMAP1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_8, GX_ITS_4);
    static const GXColor color = { 59, 181, 59, 24 };
    GXSetTevColor(GX_TEVREG0, color);
    GXSetNumTevStages(2);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD1, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_TEXC, GX_CC_A0, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVREG1);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVREG1);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP2, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C1);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetCullMode(GX_CULL_NONE);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetAlphaCompare(GX_GEQUAL, m_threshold, GX_AOP_AND, GX_LEQUAL, 255);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZMode(GX_FALSE, GX_NEVER, GX_FALSE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX1, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX1, GX_TEX_ST, GX_F32, 0);
    t = m_grow;
    x0 = GrowLerp(m_center.x, m_minX, t);
    x1 = GrowLerp(m_center.x, m_maxX, t);
    z0 = GrowLerp(m_center.z, m_minZ, t);
    z1 = GrowLerp(m_center.z, m_maxZ, t);
    y = GrowLerp(m_center.y, 0.0, t);
    u0 = m_scrollU;
    u1 = u0 + 0.5;
    v0 = m_scrollV;
    v1 = v0 + 1.0;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(x0, y, z0);
    GXTexCoord2f32(0.0f, 0.0f);
    GXTexCoord2f32(u0, v0);
    GXPosition3f32(x1, y, z0);
    GXTexCoord2f32(1.0f, 0.0f);
    GXTexCoord2f32(u1, v0);
    GXPosition3f32(x1, y, z1);
    GXTexCoord2f32(1.0f, 1.0f);
    GXTexCoord2f32(u1, v1);
    GXPosition3f32(x0, y, z1);
    GXTexCoord2f32(0.0f, 1.0f);
    GXTexCoord2f32(u0, v1);
    GXEnd();
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetNumIndStages(0);
}

} // namespace m531
