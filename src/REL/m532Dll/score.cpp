/* score.cpp -- m532::CScore / CTeamScore / CIcon (score.h). Retail order: CScore ctor, [CTeamScore(),
 * ~CSingleton<CScore>], dtor, addPoint, getPoint, showPoints, checkResult, on_new_mode, on_update, DrawHook,
 * draw, setupGX; CIcon setAnim, setPos, setScale, setAlpha, draw; CTeamScore init, setAnims, setAlpha, addPoint,
 * getPoint, show, update, draw; [CLerp<float> Update, Set(to, n), Set(from, to, n)]; __sinit (300/60, 30/12).
 * EXACT: CLerp<float> (m539's, score.h); the dtor / ~CSingleton (camera's shape). The rest drafted whole from
 * the sheet (master_camera_map_score_rumble.md §6) and the asm. */
#include "REL/m532Dll/config.h"
#include "REL/m532Dll/param.h"
#include "REL/m532Dll/score.h"
#include "REL/m532Dll/util.h"

/* score's own dynamically initialised pair (bss A60/A64, after param.h's): the point icon's pop-in length and
 * the windows' fade-in length. Names ours. */
inline int PopLenInit() { return 30; }
inline int FadeLenInit() { return 12; }
static int s_popLen = PopLenInit();   /* 30 */
static int s_fadeLen = FadeLenInit(); /* 12 */

namespace m532 {

/* lbl_1_rodata_310 */
static const u32 s_animNo[3] = { 0x5A0015, 0x5A0016, 0x5A0017 };

/* fn_1_CB30. The group / sprite ids are never stored (retail). */
CScore::CScore() : m_active(false), m_fade(0.0f, 0)
{
    for (int i = 0; i < 3; i++) {
        m_anim[i] = HuSprAnimRead(HuDataSelHeapReadNum(s_animNo[i], HU_MEMNUM_OVL, HEAP_MODEL));
    }
    s16 grp = HuSprGrpCreate(1);
    s16 spr = HuSprFuncCreate(DrawHook, 99);
    HuSprGrpMemberSet((int)grp, 0, (int)spr); /* the int casts are the extsh at the call (retail) */
    m_team[0].init(60.0f, 60.0f, 250, 0, 30);
    m_team[1].init(516.0f, 60.0f, 0, 50, 250);
    m_team[0].setAnims(m_anim[1], m_anim[0]);
    m_team[1].setAnims(m_anim[2], m_anim[0]);
}

CScore::~CScore() {}

void CScore::addPoint(int team)
{
    m_team[team].addPoint();
}

int CScore::getPoint(int team)
{
    return m_team[team].getPoint();
}

void CScore::showPoints()
{
    m_team[0].show();
    m_team[1].show();
}

int CScore::checkResult(int round)
{
    int a = m_team[0].getPoint();
    int b = m_team[1].getPoint();
    if (a >= 3 && b < 3) {
        return 0;
    }
    if (a < 3 && b >= 3) {
        return 1;
    }
    if (a >= 3 && b >= 3) {
        return 2; /* unreachable (one point per round) */
    }
    if (round < 5) {
        return PLAYING_GAME;
    }
    if (a > b) {
        return 0;
    }
    if (a < b) {
        return 1;
    }
    if (a <= 0) {
        return 3;
    }
    return 2;
}

void CScore::on_new_mode(int mode)
{
    switch (mode) {
    case 2:
        m_active = true;
        m_fade.Set(1.0f, s_fadeLen);
        m_execFlags &= ~(1 << mode);
        break;
    default:
        m_execFlags &= ~(1 << mode);
        break;
    }
}

void CScore::on_update()
{
    if (m_active) {
        if (m_fade.IsRunning()) {
            float a = m_fade.Get();
            m_team[0].setAlpha(a);
            m_team[1].setAlpha(a);
            m_fade.Update();
        }
        m_team[0].update();
        m_team[1].update();
    }
}

void CScore::DrawHook(HUSPRITE* spr)
{
    GetInstance()->draw();
}

void CScore::draw()
{
    if (m_active) {
        setupGX();
        m_team[0].draw();
        m_team[1].draw();
    }
}

/* lbl_1_rodata_32C / 344 */
static const GXVtxDescList s_vtxDesc[] = { { GX_VA_POS, GX_DIRECT }, { GX_VA_TEX0, GX_DIRECT }, { GX_VA_NULL, GX_NONE } };
static const GXVtxAttrFmtList s_vtxFmt[] = {
    { GX_VA_POS, GX_POS_XY, GX_F32, 0 }, { GX_VA_TEX0, GX_TEX_ST, GX_F32, 0 }, { GX_VA_NULL, GX_POS_XY, GX_U8, 0 }
};

void CScore::setupGX()
{
    Mtx m;
    PSMTXIdentity(m);
    MtxPtr mp = m;
    GXLoadPosMtxImm(mp, GX_PNMTX0);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetCullMode(GX_CULL_NONE);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_LEQUAL, 255);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXClearVtxDesc();
    GXSetVtxDescv((GXVtxDescList*)s_vtxDesc);
    GXSetVtxAttrFmtv(GX_VTXFMT0, (GXVtxAttrFmtList*)s_vtxFmt);
}

void CIcon::setAnim(ANIMDATA* anim)
{
    m_anim = anim;
    m_w = anim->bmp->sizeX / 2.0;
    m_h = anim->bmp->sizeY / 2.0;
}

void CIcon::setPos(float x, float y)
{
    m_x = x;
    m_y = y;
}

void CIcon::setScale(float scale)
{
    m_scale = scale;
}

void CIcon::setAlpha(float alpha)
{
    float a;
    if (alpha < 0.0f) {
        a = 0.0f;
    } else if (alpha > 1.0f) {
        a = 1.0f;
    } else {
        a = alpha;
    }
    m_alpha = a;
}

/* lbl_1_rodata_388 */
static const GXColor s_black = { 0, 0, 0, 0 };

void CIcon::draw()
{
    if (m_alpha <= 0.0f) {
        return;
    }
    HuSprTexLoad(m_anim, 0, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    GXColor color = s_black;
    color.a = 255.0f * m_alpha;
    GXSetTevColor(GX_TEVREG0, color);
    float hw = m_scale * m_w;
    float hh = m_scale * m_h;
    float x0 = m_x - hw;
    float x1 = m_x + hw;
    float y0 = m_y - hh;
    float y1 = m_y + hh;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXWGFifo.f32 = x0;
    GXWGFifo.f32 = y0;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = x1;
    GXWGFifo.f32 = y0;
    GXWGFifo.f32 = 1.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = x1;
    GXWGFifo.f32 = y1;
    GXWGFifo.f32 = 1.0f;
    GXWGFifo.f32 = 1.0f;
    GXWGFifo.f32 = x0;
    GXWGFifo.f32 = y1;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 1.0f;
}

void CTeamScore::init(float x, float y, u8 r, u8 g, u8 b)
{
    m_win = MgScoreWinCreate(0x58, 0x28);
    MgScoreWinPosSet(m_win, x, y);
    MgScoreWinColorSet(m_win, r, g, b);
    MgScoreWinTPLvlSet(m_win, 0.0f);
    MgScoreWinDispSet(m_win, 1);
    for (int i = 0; i < 3; i++) {
        float ix = x + 24.0 * (i - 1.0);
        m_back[i].setPos(ix, y);
        m_back[i].setAlpha(0.0f);
        m_back[i].setScale(1.0f);
        m_front[i].setPos(ix, y);
        m_front[i].setAlpha(0.0f);
        m_front[i].setScale(3.0f);
    }
    m_point = 0;
    m_shown = 0;
}

void CTeamScore::setAnims(ANIMDATA* back, ANIMDATA* front)
{
    for (int i = 0; i < 3; i++) {
        m_back[i].setAnim(back);
        m_front[i].setAnim(front);
    }
}

void CTeamScore::setAlpha(float alpha)
{
    MgScoreWinTPLvlSet(m_win, 0.7f * alpha);
    for (int i = 0; i < 3; i++) {
        m_back[i].setAlpha(alpha);
    }
}

void CTeamScore::addPoint()
{
    if (m_point < 3) {
        m_point++;
    }
}

int CTeamScore::getPoint()
{
    return m_point;
}

/* retail bound `m_shown - 2` (sheet §10: probably meant -1; visual only) */
void CTeamScore::show()
{
    if (m_shown < m_point) {
        m_shown = m_point;
        for (int i = 0; i < m_shown - 2; i++) {
            CIcon* icon = &m_front[i];
            icon->setAlpha(1.0f);
            icon->setScale(1.0f);
        }
        m_pop.Set(0.0f, 1.0f, s_popLen);
    }
}

/* inline linear blend (CLerp::Update's formula) */
static inline float Lerp(double from, double to, float t)
{
    return (1.0 - t) * from + t * to;
}

void CTeamScore::update()
{
    if (m_shown > 0 && m_pop.IsRunning()) {
        float t = m_pop.Get();
        float alpha = t;
        float scale = Lerp(4.0, 1.0, t);
        CIcon* icon = &m_front[m_shown - 1];
        icon->setAlpha(alpha);
        icon->setScale(scale);
        m_pop.Update();
    }
}

void CTeamScore::draw()
{
    for (int i = 0; i < 3; i++) {
        m_back[i].draw();
    }
    for (int i = 0; i < m_shown; i++) {
        m_front[i].draw();
    }
}

} // namespace m532
