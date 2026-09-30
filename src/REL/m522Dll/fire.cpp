#include "REL/m522Dll/fire.h"
#include "REL/mgcpp/random.h"
extern "C" {
#include "game/hsfformat.h"
void GXSetVtxAttrFmtv(GXVtxFmt vtxfmt, GXVtxAttrFmtList* list);
}

namespace m522 {

/* .bss 0: the spin speed of the sun and the fire sprites (deg per frame; 17/1440 = 4.25/360). Retail initialises it
 * dynamically (.ctors __sinit 4934: one lfs + stfs). Every constant spelling (4.25f / 360.0f, 17.0f / 1440.0f, the
 * literal) folds to a static initialiser with no .ctors in CW, so the value comes through an inline function (raw 0;
 * the original expression is unknown -- a guess) */
static inline float SpinSpeed()
{
    return 0.011805556f;
}
static float s_spinSpeed = SpinSpeed();

/* fn_1_0. The id local is `id()`'s s16 (extsh + mr, extsh at each call); Hu3DModelLightInfoSet's result is kept in
 * a dead local (retail stores it to the stack); the wave loop caches end() (begin read first). */
CSun::CSun()
    : CModel(0x500002u), m_rot(0.0f), m_speed(s_spinSpeed), m_waves(WAVE_NUM)
{
    HU3DMODELID id = this->id();
    setLayer(2);
    setAttr(HU3D_MOTATTR_LOOP);
    Hu3DModelMatHookSet((int)id, MatHook);
    s32 lights = Hu3DModelLightInfoSet((int)id, 1);
    for (std::vector<Wave>::iterator w = m_waves.begin(), e = m_waves.end(); w != e; ++w) {
        w->phase = 0.0f;
        w->speed = CRandom::frandom(-2.0f, 2.0f) * M_PI / 108.0;
        w->amp = CRandom::frandom(1.0f, 127.0f);
    }
    GXInitTexObj(&m_tex, m_texData, TEX_W, TEX_H, GX_TF_IA8, GX_REPEAT, GX_REPEAT, GX_FALSE);
}

CSun::~CSun() {}

void CSun::Update()
{
    Spin();
    UpdateTexture();
}

void CSun::StopSpin()
{
    m_speed = 0.0f;
}

void CSun::SetShadowSun()
{
    setShadowMapObj("sun01");
}

void CSun::Spin()
{
    Vec rot = { 0.0f, 0.0f, 0.0f };
    rot.y = m_rot;
    setRot(&rot);
    m_rot += m_speed;
}

/* fn_1_510: the waves and the texel pairs walk together and stop at either end (both ends cached) */
void CSun::UpdateTexture()
{
    std::vector<Wave>::iterator w = m_waves.begin(), we = m_waves.end();
    u8* t = m_texData;
    u8* te = m_texData + sizeof(m_texData);
    for (; t != te && w != we; t += 2, ++w) {
        float phase = w->Advance();
        const float& amp = w->amp;
        t[0] = 128.0 + amp * sin(phase);
        t[1] = 128.0 + amp * cos(phase);
    }
    DCFlushRangeNoSync(m_texData, sizeof(m_texData));
}

float Wave::Advance()
{
    return phase += speed;
}

void CSun::MatHook(HU3DDRAWOBJ* drawObj, HSFMATERIAL* material)
{
    static const f32 indMtx[2][3] = { { 0.08f, 0.0f, 0.0f }, { 0.0f, 0.08f, 0.0f } };

    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    CSun* sun = GetInstance();
    GXLoadTexObj(&sun->m_tex, GX_TEXMAP1);
    GXSetNumIndStages(1);
    GXSetIndTexMtx(GX_ITM_0, (f32(*)[3])indMtx, 0);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD0, GX_TEXMAP1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_4, GX_ITS_4);
    GXSetNumTevStages(2);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVREG0);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVREG0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_C0, GX_CC_TEXC, GX_CC_HALF, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
}

/* lbl_1_data_44: the two HSF objects of model 0x500004 (AddTiles, DrawObj). Non-const pointers: retail's table is
 * .data (the strings "fire01" / "prominence" precede it). */
static const char* s_objName[2] = { "fire01", "prominence" };

CFire::CFire() : m_model(new CModel(0x500004u)), m_rot(0.0f)
{
    setLayer(1);
    m_model->setAttr(HU3D_ATTR_DISPOFF);
    AddTiles(0);
    AddTiles(1);
}

CFire::~CFire() {}

void CFire::AddTiles(int i)
{
    HSFOBJECT* obj = Hu3DModelObjPtrGet(m_model->id(), (char*)s_objName[i]);
    if (obj) {
        HSFBUFFER* faces = obj->mesh.face;
        HSFFACE* face = (HSFFACE*)faces->data;
        for (int k = 0; k < faces->count; k++, face++) {
            if ((face->type & HSF_FACE_MASK) == HSF_FACE_QUAD) {
                m_tiles.push_back(Tile(i));
            }
        }
    }
}

Tile::Tile(int t)
{
    type = t;
    lastFrame = t == 0 ? 0x3F : 0x8F;
    frame = (int)(lastFrame * CRandom::randomMantissa());
    wait.v = 0;
}

void Tile::Copy(const Tile& t)
{
    type = t.type;
    lastFrame = t.lastFrame;
    frame = t.frame;
    wait.v = t.wait.v;
}

static inline float SecToFrame(float sec)
{
    return 60.0f * sec;
}

void Tile::Update()
{
    bool done = false;
    if (wait.v > 0 && --wait.v == 0) {
        done = true;
    }
    if (wait.v <= 0 && ++frame > lastFrame) {
        frame = 0;
        if (type == 1) {
            wait = SecToFrame(10.0f * CRandom::randomMantissa());
        }
    }
}

/* fn_1_D50 (unreferenced; inlined in DrawObj): the 16-column sprite sheet has {4, 9}[type] rows (a local aggregate,
 * rodata_78); a 1/64-texel inset on every edge */
void Tile::GetUV(float* u0, float* v0, float* u1, float* v1)
{
    int rows[2] = { 4, 9 };
    const int& n = rows[type];
    *u0 = 1.0 / 1024.0 + (frame & 15) / 16.0;
    *u1 = ((frame & 15) + 1) / 16.0 - 1.0 / 1024.0;
    *v0 = (double)(frame / 16) / n + 1.0 / (n * 64);
    *v1 = (double)(frame / 16 + 1) / n - 1.0 / (n * 64);
}

void CFire::update()
{
    for (std::vector<Tile>::iterator it = m_tiles.begin(), e = m_tiles.end(); it != e; ++it) {
        it->Update();
    }
    m_rot += s_spinSpeed;
}

static const GXVtxDescList s_fireVtxDesc[] = { { GX_VA_POS, GX_INDEX16 }, { GX_VA_TEX0, GX_DIRECT }, { GX_VA_NULL, GX_NONE } };
static const GXVtxAttrFmtList s_fireVtxFmt[] = { { GX_VA_POS, GX_POS_XYZ, GX_F32, 0 },
                                                 { GX_VA_TEX0, GX_TEX_ST, GX_F32, 0 },
                                                 { GX_VA_NULL, GX_POS_XY, GX_U8, 0 } };

void CFire::draw(Mtx* mtx)
{
    Mtx bb;
    Mtx rot;

    GXSetNumChans(0);
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
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetAlphaCompare(GX_ALWAYS, 0xFF, GX_AOP_OR, GX_ALWAYS, 0xFF);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_NOOP);
    GXClearVtxDesc();
    GXSetVtxDescv((GXVtxDescList*)s_fireVtxDesc);
    GXSetVtxAttrFmtv(GX_VTXFMT0, (GXVtxAttrFmtList*)s_fireVtxFmt);
    PSMTXInverse(*mtx, bb);
    bb[0][3] = bb[1][3] = bb[2][3] = 0.0f;
    PSMTXRotRad(rot, 'z', MTXDegToRad(m_rot));
    PSMTXConcat(bb, rot, bb);
    std::vector<Tile>::iterator cursor = m_tiles.begin();
    DrawObj(0, *mtx, bb, &cursor);
    DrawObj(1, *mtx, bb, &cursor);
}

void CFire::DrawObj(int i, Mtx view, Mtx bb, std::vector<Tile>::iterator* cursor)
{
    Mtx m;
    const char* name = s_objName[i];
    Hu3DModelObjMtxGet(m_model->id(), (char*)name, m);
    PSMTXConcat(view, m, m);
    PSMTXConcat(m, bb, m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    CSunFireMan::LoadTex(i, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    HSFOBJECT* obj = Hu3DModelObjPtrGet(m_model->id(), (char*)name);
    HSFBUFFER* faces = obj->mesh.face;
    HSFFACE* face = (HSFFACE*)faces->data;
    GXSetArray(GX_VA_POS, obj->mesh.vertex->data, sizeof(HuVecF));
    for (int k = 0; k < faces->count && *cursor != m_tiles.end(); k++, face++) {
        if ((face->type & HSF_FACE_MASK) == HSF_FACE_QUAD) {
            const Wait& wait = (*cursor)->wait;
            if (wait.v <= 0) {
                float u0, v0, u1, v1;
                (*cursor)->GetUV(&u0, &v0, &u1, &v1);
                GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                GXPosition1x16(face->index[0].vertex);
                GXTexCoord2f32(u0, v0);
                GXPosition1x16(face->index[2].vertex);
                GXTexCoord2f32(u1, v0);
                GXPosition1x16(face->index[3].vertex);
                GXTexCoord2f32(u1, v1);
                GXPosition1x16(face->index[1].vertex);
                GXTexCoord2f32(u0, v1);
                GXEnd();
            }
            ++*cursor;
        }
    }
}

/* ---- CFlare / Flare (.text 0x17E8..0x26A8) ---- */

/* m532 util.h's setter with DOUBLE components (the three frandom results are held as doubles, `frsp; stfs`) */
static inline Vec& SetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
    return *v;
}

/* m513 misc.h's PSVEC wrapper returning the result by reference (the named reference materialises: addi; mr) */
static inline Vec& VecScale(const Vec* v, Vec* d, float s)
{
    PSVECScale(v, d, s);
    return *d;
}

static inline Vec& VecAdd(const Vec* a, const Vec* b, Vec* d)
{
    PSVECAdd(a, b, d);
    return *d;
}

static inline float VecMag(const Vec* v)
{
    return PSVECMag(v);
}

/* fn_1_17E8 (bubble Burst): n sparks leave `centre` in random upward-biased directions, starting 0.1 * power out and
 * travelling `power` units in `time` seconds */
CFlare::CFlare(Vec* centre, float power, float time, int n)
{
    setLayer(6);
    m_flares.clear();
    for (int i = 0; i < n; i++) {
        Vec pos;
        Vec dir;
        SetVec(&dir, CRandom::frandom(-1.0f, 1.0f), CRandom::frandom(-0.01f, -1.0f), CRandom::frandom(-1.0f, 1.0f));
        PSVECNormalize(&dir, &dir);
        Vec& start = VecScale(&dir, &pos, 0.1 * power);
        PSVECAdd(centre, &start, &start);
        float speed = power / SecToFrame(time);
        PSVECScale(&dir, &dir, speed);
        Flare tmp(&pos, &dir, power);
        m_flares.push_back(tmp);
    }
}

CFlare::~CFlare() {}

Flare::Flare(const Vec* pos, const Vec* v, float l) : vel(*v), life0(l), life(l), head(0)
{
    trail.clear();
    trail.assign(8, *pos);
}

static inline float Damp(float v, float j)
{
    return 0.8 * v + 0.2 * j;
}

/* fn_1_1D30 (unreferenced; inlined in CFlare::update): the head moves one step along the 8-point ring by vel, the
 * life drops by the distance travelled, vel is damped towards a random upward jitter; true while alive */
bool Flare::Update()
{
    Vec& from = Point(head);
    if (++head >= trail.size()) {
        head = 0;
    }
    Vec& to = Point(head);
    VecAdd(&from, &vel, &to);
    life -= VecMag(&vel);
    Vec jitter = { 0.0f, 0.0f, 0.0f };
    jitter.x = CRandom::frandom(-4.0f, 4.0f);
    jitter.y = CRandom::frandom(0.0f, 4.0f);
    jitter.z = CRandom::frandom(-4.0f, 4.0f);
    vel.x = Damp(vel.x, jitter.x);
    vel.y = Damp(vel.y, jitter.y);
    vel.z = Damp(vel.z, jitter.z);
    return life > 0.0f;
}

void CFlare::update()
{
    for (Flare *it = m_flares.begin(), *end = m_flares.end(); it != end; ++it) {
        if (!it->Update()) {
            m_flares.erase(it);
        }
    }
    if (m_flares.size() == 0) {
        delete this;
    }
}

static const GXVtxDescList s_flareVtxDesc[] = { { GX_VA_POS, GX_DIRECT }, { GX_VA_CLR0, GX_DIRECT }, { GX_VA_NULL, GX_NONE } };
static const GXVtxAttrFmtList s_flareVtxFmt[] = { { GX_VA_POS, GX_POS_XYZ, GX_F32, 0 },
                                                  { GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0 },
                                                  { GX_VA_NULL, GX_POS_XY, GX_U8, 0 } };

void CFlare::draw(Mtx* mtx)
{
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetCullMode(GX_CULL_NONE);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetZCompLoc(GX_TRUE);
    GXSetZMode(GX_TRUE, GX_LESS, GX_FALSE);
    GXSetAlphaCompare(GX_ALWAYS, 0xFF, GX_AOP_OR, GX_ALWAYS, 0xFF);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
    GXClearVtxDesc();
    GXSetVtxDescv((GXVtxDescList*)s_flareVtxDesc);
    GXSetVtxAttrFmtv(GX_VTXFMT0, (GXVtxAttrFmtList*)s_flareVtxFmt);
    GXSetLineWidth(6, GX_TO_ZERO);
    std::vector<Flare>::iterator it = m_flares.begin(), end = m_flares.end();
    GXBegin(GX_LINES, GX_VTXFMT0, m_flares.size() * 2);
    for (; it != end; ++it) {
        it->Draw();
    }
    GXEnd();
}

/* fn_1_24FC: the segment from the head (yellow, alpha = remaining life) to the oldest point (red, alpha 0) */
void Flare::Draw()
{
    Vec& p0 = Point(head);
    Vec& p1 = Point((head + 1) % trail.size());
    int a = 255.0f * life / life0;
    GXPosition3f32(p0.x, p0.y, p0.z);
    GXColor4u8(0xFF, 0xFF, 0x00, a);
    GXPosition3f32(p1.x, p1.y, p1.z);
    GXColor4u8(0xFF, 0x00, 0x00, 0x00);
}

} // namespace m522

template <> m522::CSun* CSingleton<m522::CSun>::ms_pointer = 0;
template <> m522::CSunFireMan* CSingleton<m522::CSunFireMan>::ms_pointer = 0;
