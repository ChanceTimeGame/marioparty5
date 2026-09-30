#include "REL/m511Dll/config.h"
#include "REL/m511Dll/staryaji.h"
#include "REL/m511Dll/star.h"
#include "REL/m511Dll/boatshadow.h"
#include "REL/m511Dll/angle.h"

extern "C" {
void HuSprTexLoad(ANIMDATA* anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);
}

namespace m511 {

TLinkList<CStarYaji> CStarYaji::list;

/* the borrowed arrow texture (CEffTex, through GetInstance: singleton.h:39) */
static inline ANIMDATA* GetYajiAnim(CEffTex* tex)
{
    return tex->m_yajiAnim;
}

CStarYajiMan::CStarYajiMan() {}

CStarYajiMan::~CStarYajiMan()
{
    CStarYaji::DeleteAll();
}

void CStarYajiMan::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

void CStarYajiMan::on_update()
{
    CStarYaji::UpdateAll();
}

void CStarYaji::DrawHook(HU3DMODEL* model, Mtx* mtx)
{
    CStarYaji* self = (CStarYaji*)model->hookData;
    if (self->m_visible && self->m_hasTarget) {
        self->Draw(mtx);
    }
}

/* lbl_1_rodata_430: each arrow is seen only by its player's camera */
static const int s_camMask[4] = { 1, 2, 4, 8 };

CStarYaji::CStarYaji(int player, int charNo)
    : m_visible(false), m_hasTarget(true), m_rotY(0.0f), m_alpha(0.0f), m_frame(0), m_player(player),
      m_charNo(charNo)
{
    insertBack(&list);
    HU3DMODELID id = Hu3DHookFuncCreate(DrawHook);
    m_model = (int)id;
    HU3DMODEL* model = &Hu3DData[(int)id];
    Hu3DModelPosSet((int)id, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet((int)id, 0.0f, 0.0f, 0.0f);
    Hu3DModelLayerSet((int)id, 6);
    Hu3DModelCameraSet((int)id, s_camMask[player]);
    model->hookData = this;
    CEffTex* tex = CSingleton<CEffTex>::GetInstance();
    m_anim = GetYajiAnim(tex);
}

CStarYaji::~CStarYaji()
{
    Hu3DModelKill(m_model);
}

void CStarYaji::DeleteAll()
{
    while (!list.isEmpty()) {
        CStarYaji* p = list.last();
        delete p;
    }
}

void CStarYaji::UpdateAll()
{
    TLinkList<CStarYaji>::exec(&list, Update);
}

/* the arrow of `player` now points from pos to gate (the goal is 5); an arrow standing exactly on its target has
 * none */
void CStarYaji::SetTarget(int player, Vec* pos, int gate, float heading)
{
    CLinkNode* end;
    CStarYaji* p;
    for (p = list.begin(), end = list.end(); p != end; p = p->next()) {
        if (p->m_player != player) {
            continue;
        }
        Vec target;
        CStarMan::GetPos(gate, &target);
        if (target.x != pos->x || target.z != pos->z) {
            float rotY = 180.0 * (atan2(target.x - pos->x, target.z - pos->z) / M_PI);
            p->m_heading = heading;
            p->m_rotY = rotY;
            p->m_hasTarget = true;
        } else {
            p->m_hasTarget = false;
        }
        p->m_target = gate;
        p->m_pos = *pos;
        break;
    }
}

void CStarYaji::ShowAll()
{
    CLinkNode* end;
    CStarYaji* p;
    for (p = list.begin(), end = list.end(); p != end; p = p->next()) {
        p->m_visible = true;
    }
}

void CStarYaji::HideAll()
{
    CLinkNode* end;
    CStarYaji* p;
    for (p = list.begin(), end = list.end(); p != end; p = p->next()) {
        p->m_visible = false;
    }
}

void CStarYaji::Hide(int player)
{
    CLinkNode* end;
    CStarYaji* p;
    for (p = list.begin(), end = list.end(); p != end; p = p->next()) {
        if (p->m_player == player) {
            p->m_visible = false;
        }
    }
}

/* fade (10 a frame, 0..192); tilt the arrow down the more the boat faces away from the target; 100 above the boat */
void CStarYaji::Update(CStarYaji* p)
{
    if (p->m_visible) {
        if ((p->m_alpha += 10.0f) > 192.0f) {
            p->m_alpha = 192.0f;
        }
    } else {
        if ((p->m_alpha -= 10.0f) < 0.0f) {
            p->m_alpha = 0.0f;
        }
    }
    p->m_frame++;
    float diff = SubAngle(p->m_rotY, p->m_heading);
    float absDiff;
    if (diff < 0.0f) {
        absDiff = -diff;
    } else {
        absDiff = diff;
    }
    float tilt = -(90.0f - absDiff) / 4.0f;
    Hu3DModelRotSet(p->m_model, tilt, p->m_rotY, 0.0f);
    Hu3DModelPosSet(p->m_model, p->m_pos.x, 100.0f + p->m_pos.y, p->m_pos.z);
}

void CStarYaji::SetupGX()
{
    HuSprTexLoad(m_anim, 0, GX_TEXMAP0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    Mtx texMtx;
    PSMTXIdentity(texMtx);
    GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetCullMode(GX_CULL_NONE);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetZCompLoc(GX_TRUE);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetAlphaCompare(GX_ALWAYS, 0xFF, GX_AOP_OR, GX_ALWAYS, 0xFF);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
}

/* lbl_1_rodata_46C / 4AC: the arrow outline {x, z} (tip at z 400) and its texture coordinates {s, t} */
struct ArrowXZ {
    float x;
    float z;
};
struct ArrowST {
    float s;
    float t;
};
static const ArrowXZ s_shape[8] = {
    { 0.0f, 400.0f },   { 50.0f, 300.0f },  { 25.0f, 300.0f },  { 25.0f, 200.0f },
    { 0.0f, 200.0f },   { -25.0f, 200.0f }, { -25.0f, 300.0f }, { -50.0f, 300.0f },
};
static const ArrowST s_uv[8] = {
    { 0.0f, 0.0f },   { -0.5f, 2.0f }, { -0.25f, 2.0f }, { -0.25f, 4.0f },
    { 0.0f, 4.0f },   { 0.25f, 4.0f }, { 0.25f, 2.0f },  { 0.5f, 2.0f },
};

/* red at the fade alpha; toward the goal (target 5) it pulses green and grows (32-frame cycle); the arrow slides
 * along its axis and the texture scrolls */
void CStarYaji::Draw(Mtx* mtx)
{
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    SetupGX();
    float scale = 1.0f;
    GXColor color = { 0xFF, 0x00, 0x00, 0xFF };
    color.a = m_alpha;
    if (m_target == 5) {
        color.g = 255.0f * ((m_frame & 31) / 31.0f);
        scale = 1.0f + (m_frame & 31) / 31.0f;
    }
    GXSetTevColor(GX_TEVREG0, color);
    float scroll = (m_frame & 15) / 16.0f;
    float slide = 100.0f * ((m_frame & 31) / 32.0f) - 100.0f;
    GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 8);
    for (int i = 0; i < 8; i++) {
        float x = scale * s_shape[i].x;
        float z = 200.0f + scale * (s_shape[i].z - 200.0f);
        GXPosition3f32(x, 0.0f, z + slide);
        GXTexCoord2f32(s_uv[i].s, scroll + s_uv[i].t);
    }
    GXEnd();
}

} // namespace m511
