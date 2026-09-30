#include "REL/m531Dll/flow.h"
#include "REL/m531Dll/player.h"
#include "REL/m531Dll/object.h"
#include "REL/m531Dll/cleaneff.h"
#include "REL/m531Dll/score.h"
#include "REL/m531Dll/polish.h"
extern "C" {
#include "game/frand.h" /* not in mgcpp/game.h */
}
#include <algorithm>

namespace m531 {

/* rodata_50: the players' 12 motions */
static const MotionEntry s_playerMotion[12] = {
    { 0x8C0000, 0x40000001, 8.0f }, { 0x8C0001, 0x40000001, 8.0f }, { 0x8C0002, 0x40000001, 8.0f },
    { 0x8C0003, 0, 8.0f },          { 0x8C0004, 0, 8.0f },          { 0x8C0009, 0, 8.0f },
    { 0x8C0010, 0, 8.0f },          { 0x8C0011, 0, 8.0f },          { 0x8C0006, 0, 1.0f },
    { 0x8C0007, 0, 1.0f },          { 0x8C0029, 0x40000001, 8.0f }, { 0x8C004D, 0x40000001, 8.0f },
};

/* rodata_E0: the guide's 5 motions */
static const MotionEntry s_guideMotion[5] = {
    { 0x59000F, 0x40000001, 8.0f }, { 0x59000F, 0x40000001, 8.0f }, { 0x59000F, 0x40000001, 8.0f },
    { 0x59000F, 0x40000001, 8.0f }, { 0x59000F, 0x40000001, 8.0f },
};

/* rodata_11C (dtk merged it into E0): unreferenced in retail, still emitted. Keep it in place. */
struct PosRot {
    Vec pos;
    Vec rot;
};
static const PosRot s_unusedPos[2] = {
    { { -1000.0f, 0.0f, 560.0f }, { 0.0f, 180.0f, 0.0f } },
    { { 1000.0f, 0.0f, 560.0f }, { 0.0f, 180.0f, 0.0f } },
};

/* rodata_14C: where each sorted slot k drops in (pos -> m_pos and m_startPos, rot -> m_rot) */
static const PosRot s_startPos[4] = {
    { { -450.0f, 1000.0f, -130.0f }, { 0.0f, 0.0f, 0.0f } },
    { { -200.0f, 1000.0f, 560.0f }, { 0.0f, 180.0f, 0.0f } },
    { { 200.0f, 1000.0f, 560.0f }, { 0.0f, 180.0f, 0.0f } },
    { { 450.0f, 1000.0f, -130.0f }, { 0.0f, 0.0f, 0.0f } },
};

/* rodata_1AC: the outro walk targets (only pos is read -> m_goalPos) */
static const PosRot s_goalPos[4] = {
    { { -420.0f, 10.0f, 560.0f }, { 0.0f, 180.0f, 0.0f } },
    { { -230.0f, 10.0f, 560.0f }, { 0.0f, 180.0f, 0.0f } },
    { { 230.0f, 10.0f, 560.0f }, { 0.0f, 180.0f, 0.0f } },
    { { 420.0f, 10.0f, 560.0f }, { 0.0f, 180.0f, 0.0f } },
};

/* camera {eye, target} pairs: finish (mode 4), team 0 / team 1 wins (mode 5), intro (ctor) */
struct CamPos {
    Vec eye;
    Vec target;
};
static const CamPos s_camFinish = { { 0.0f, 300.0f, 2800.0f }, { 0.0f, 100.0f, 600.0f } };      /* rodata_20C */
static const CamPos s_camWin0 = { { -825.0f, 900.0f, 2600.0f }, { -325.0f, -100.0f, 600.0f } }; /* rodata_224 */
static const CamPos s_camWin1 = { { 825.0f, 900.0f, 2600.0f }, { 325.0f, -100.0f, 600.0f } };   /* rodata_23C */
static const CamPos s_camIntro = { { -325.0f, 300.0f, 1000.0f }, { -325.0f, 0.0f, -250.0f } };  /* rodata_254 */

/* rodata_26C: the chase goal after the intro, then the projection (also the shadow camera's); [6] unread */
struct CamParam {
    Vec eye;
    Vec target;
    float unused;
    float fov;
    float nearZ; /* not `near`/`far`: Windows headers define those as macros */
    float farZ;
};
static const CamParam s_camParam = {
    { 3.279f, 2531.566f, 1651.557f }, { 3.279f, -570.875f, 28.275f }, 0.0f, 25.0f, 20.0f, 32768.0f,
};

/* rodata_294: the shadow camera direction (normalised, then scaled to 3400) */
static const Vec s_shadowDir = { -4425.815f, 6717.712f, 5071.9f };

/* CPlayer accessors flow uses (inline, file-local; names ours): each is one inline return level */
static inline int GetSlot(CPlayer* p)
{
    return p->m_slot;
}

static inline s16 GetCharNo(CPlayer* p)
{
    return (s16)p->m_charNo;
}

static inline Vec GetBrushPos(CPlayer* p)
{
    return p->m_brushPos;
}

/* bool of the u8 (retail: lbz; clrlwi; cmplwi) */
static inline bool IsArrived(CPlayer* p)
{
    return (u8)p->m_arrived;
}

/* CScore: stop the roulette (score.cpp shows the SetScore values from then on) */
static inline void StopRoulette(CScore* score)
{
    score->m_stopped = 1;
}

/* the guide's start position (mode0 keeps the object in a register, as an inline member call would) */
static inline void SetPos(CPlayerBase* p, const Vec& v)
{
    p->m_pos.x = v.x;
    p->m_pos.y = v.y;
    p->m_pos.z = v.z;
}

/* the camera ctor's goal copies (guess: retail spills this result once more than a Vec* return does inside the
 * mode0-inlined ctor -- 2 lwz short there, masked 2; SetVec/Vec& forms spill once too often) */
static inline Vec* CopyVec(Vec* d, const Vec& s)
{
    d->x = s.x;
    d->y = s.y;
    d->z = s.z;
    return d;
}

/* ---- CFlowCamera ---- */

void CFlowCamera::IntroFunc(omObj_s* obj)
{
    CFlowCamera* self = (CFlowCamera*)obj->data;
    self->updateIntro();
}

void CFlowCamera::ChaseFunc(omObj_s* obj)
{
    CFlowCamera* self = (CFlowCamera*)obj->data;
    self->updateChase();
}

CFlowCamera::CFlowCamera(Process_s* om)
{
    m_om = om;
    m_frame = 0;
    m_rotY = 0.0f;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, s_camParam.fov, s_camParam.nearZ, s_camParam.farZ, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    m_obj = omAddObjEx(om, 1, 0, 0, -1, IntroFunc);
    m_obj->data = this;
    Vec up = { 0.0f, 1.0f, 0.0f };
    SetVec(&m_eye, s_camIntro.eye);
    SetVec(&m_up, up);
    SetVec(&m_target, s_camIntro.target);
    Hu3DCameraPosSetV(1, (Vec*)&s_camIntro.eye, &up, (Vec*)&s_camIntro.target);
    CopyVec(&m_eyeGoal, s_camIntro.eye);
    CopyVec(&m_targetGoal, s_camIntro.target);
}

CFlowCamera::~CFlowCamera()
{
    m_obj->data = 0;
    omDelObjEx(m_om, m_obj);
}

void CFlowCamera::updateIntro()
{
    float speed = 30.0f; /* dead (retail) */
    Vec* eye = &m_eye;
    Vec* up = &m_up;
    Vec* target = &m_target;

    Hu3DCameraPosSetV(1, eye, up, target);
    m_frame++;
    if (m_frame >= 180) {
        setTargetGoal(s_camParam.target);
        setEyeGoal(s_camParam.eye);
        m_obj->objFunc = ChaseFunc;
    }
}

void CFlowCamera::updateChase()
{
    float speed = 30.0f;
    Vec* eye = &m_eye;
    Vec* up = &m_up;
    Vec* target = &m_target;

    eye->x += (m_eyeGoal.x - eye->x) / speed;
    eye->y += (m_eyeGoal.y - eye->y) / speed;
    eye->z += (m_eyeGoal.z - eye->z) / speed;
    target->x += (m_targetGoal.x - target->x) / speed;
    target->y += (m_targetGoal.y - target->y) / speed;
    target->z += (m_targetGoal.z - target->z) / speed;
    Hu3DCameraPosSetV(1, eye, up, target);
    calcAngle();
}

void CFlowCamera::calcAngle()
{
    Vec d;

    PSVECSubtract(&m_eye, &m_target, &d);
    m_rotY = 180.0 * (atan2(d.x, d.z) / M_PI);
}

/* ---- CFlow ---- */

CFlow::~CFlow()
{
    int i;

    for (i = 0; i < 4; i++) {
        delete m_player[i];
    }
    delete m_guide;
    delete m_camera;
    delete m_cleanEff;
    delete m_stage;
    delete m_score;
}

void CFlow::unused() {}

void CFlow::mode0()
{
    unsigned int key[4];
    int i;
    int k;
    int z;
    int x;

    Hu3DBGColorSet(0x1D, 0x80, 0xFD);
    m_camera = new CFlowCamera(GetOm());
    Vec lightPos = { 0.0f, 171.01f, 469.85f };
    Vec lightDir = { 0.0f, -0.68f, -0.94f };
    GXColor lightColor = { 0xFF, 0xFF, 0xFF, 0xFF };
    PSVECNormalize(&lightDir, &lightDir);
    int light = Hu3DGLightCreateV(&lightPos, &lightDir, &lightColor);
    Hu3DGLightInfinitytSet(light);
    Hu3DGLightStaticSet(light, 1);
    Hu3DShadowCreate(s_camParam.fov, s_camParam.nearZ, s_camParam.farZ);
    Hu3DShadowTPLvlSet(0.2f);
    Vec shadowUp = { 0.0f, 1.0f, 0.0f };
    Vec shadowTarget = { 0.0f, 0.0f, 0.0f };
    Vec shadowPos;
    PSVECNormalize((Vec*)&s_shadowDir, &shadowPos);
    PSVECScale(&shadowPos, &shadowPos, 3400.0f);
    Hu3DShadowPosSet(&shadowPos, &shadowUp, &shadowTarget);
    m_stage = new CStageObjects(GetOm());
    m_cleanEff = new CCleanEffMan(GetOm());
    for (i = 0; i < 4; i++) {
        key[i] = (GwPlayerConf[i].grp << 16) | i;
    }
    std::sort(key, key + 4);
    for (k = 0; k < 4; k++) {
        int no = key[k] & 3;
        CCleanEff* floor = m_cleanEff->get(k / 2);
        CPlayer* p = new CPlayer(this, floor, s_playerMotion, 12, no, k);

        SetVec(&p->m_pos, s_startPos[k].pos);
        SetVec(&p->m_startPos, s_startPos[k].pos);
        SetVec(&p->m_goalPos, s_goalPos[k].pos);
        SetVec(&p->m_rot, s_startPos[k].rot);
        m_player[no] = p;
    }
    Vec guidePos = { -700.0f, 0.3f, -200.0f };
    m_guide = new CRunner(GetOm(), s_guideMotion, 5, 0x59000E);
    SetPos(m_guide, guidePos);
    WipeCreate(WIPE_MODE_IN, 5, 60);
    m_startMes = -1;
    m_finishMes = -1;
    m_resultMes = -1;
    m_frame = 0;
    m_winTeam = -1;
    m_endType = -1;
    m_score = new CScore(GetOm());
    m_score->DispOff();
    for (z = 0; z < 10; z++) {
        for (x = 0; x < 5; x++) {
            m_gridA[z][x] = 0.0f;
            m_gridB[z][x] = 0.0f;
        }
    }
    m_percent[0] = 0.0f;
    m_percent[1] = 0.0f;
    m_bgm = HuAudBGMPlay(0x32);
    setMode(1);
}

void CFlow::mode1()
{
    if (!WipeCheckEnd()) {
        m_frame++;
        if (m_frame >= 180) {
            m_frame = 0;
            m_startMes = GameMesMgStartCreate();
            setMode(2);
        }
    }
}

void CFlow::mode2()
{
    int i;

    if (!GameMesStatGet(m_startMes)) {
        GameMesDispSet(m_startMes, GAMEMES_DISP_SET, -1);
        m_timer.setParam(3600, 0, 0);
        m_timer.setModeOn(1);
        for (i = 0; i < 4; i++) {
            m_player[i]->Start();
        }
        delete m_guide;
        m_guide = 0;
        setMode(3);
    }
}

void CFlow::mode3()
{
    int i;
    int side;
    int k;

    for (i = 0; i < 4; i++) {
        int slot = GetSlot(m_player[i]);
        CCleanEff* floor = m_cleanEff->get(slot / 2);
        floor->clean(&static_cast<const Vec&>(GetBrushPos(m_player[i])), 130.0f);
    }
    int time = m_timer.getValue();
    if (checkEnd(time) || m_timer.checkDone()) {
        if (m_endType == 1) {
            m_timer.setModeOff();
        }
        for (side = 0; side < 2; side++) {
            CCleanEff* floor = m_cleanEff->get(side);
            int percent = 100.0f * floor->ratio();
            m_percent[side] = percent;
        }
        m_finishMes = GameMesMgFinishCreate();
        m_timer.stopTimer();
        for (k = 0; k < 4; k++) {
            m_player[k]->Finish();
        }
        m_sub = 0;
        m_frame = 0;
        HuAudSStreamFadeOut(m_bgm, 100);
        setMode(4);
    }
}

void CFlow::mode4()
{
    switch (m_sub) {
    case 0:
        if (GameMesStatGet(m_finishMes)) {
            break;
        }
        GameMesDispSet(m_finishMes, GAMEMES_DISP_SET, -1);
        m_camera->setEyeGoal(s_camFinish.eye);
        m_camera->setTargetGoal(s_camFinish.target);
        m_sub++;
    case 1: {
        bool all = true;
        int i;

        for (i = 0; i < 4; i++) {
            if (!IsArrived(m_player[i])) {
                all = false;
            }
        }
        if (!all) {
            break;
        }
        if (m_endType == 0) {
            m_score->DispOn();
            HuAudFXPlay(0x1D);
            m_sub++;
        } else {
            m_sub = -1;
        }
    }
    case 2: {
        int side;

        if (++m_frame < 90.0) {
            break;
        }
        for (side = 0; side < 2; side++) {
            int value = m_percent[side];
            m_score->SetScore(side, value);
        }
        StopRoulette(m_score);
        m_frame = 0;
        if (m_endType == 0) {
            HuAudFXPlay(0x1E);
        }
        m_sub++;
    }
    case 3:
        if (++m_frame < 90.0) {
            break;
        }
        m_sub++;
    default:
        m_sub = 0;
        m_frame = 0;
        setMode(5);
        break;
    }
}

void CFlow::mode5()
{
    switch (m_sub) {
    case 0:
        if (GameMesStatGet(m_finishMes)) {
            break;
        }
        GameMesDispSet(m_finishMes, GAMEMES_DISP_SET, -1);
        if (m_winTeam != -1) {
            int winner[2];
            int n = 0;
            int i;

            for (i = 0; i < 4; i++) {
                if (m_winTeam == 0) {
                    if (GetSlot(m_player[i]) < 2) {
                        m_player[i]->SetResult(0, 8);
                        winner[n] = i;
                        n++;
                    } else {
                        m_player[i]->SetResult(1, 9);
                    }
                } else {
                    if (GetSlot(m_player[i]) > 1) {
                        m_player[i]->SetResult(0, 8);
                        winner[n] = i;
                        n++;
                    } else {
                        m_player[i]->SetResult(1, 9);
                    }
                }
            }
            m_resultMes = GameMesCreate(GAMEMES_MES_MG_WINNER, GAMEMES_MG_TYPE_WIN, GetCharNo(m_player[winner[0]]),
                GetCharNo(m_player[winner[1]]), GAMEMES_MG_WINNER_NONE, GAMEMES_MG_WINNER_NONE);
            if (m_winTeam == 0) {
                m_camera->setEyeGoal(s_camWin0.eye);
                m_camera->setTargetGoal(s_camWin0.target);
            } else {
                m_camera->setEyeGoal(s_camWin1.eye);
                m_camera->setTargetGoal(s_camWin1.target);
            }
            HuAudJinglePlay(0x79);
        } else {
            s16 charNo[4];
            int i;

            m_resultMes = GameMesMgDrawCreate();
            for (i = 0; i < 4; i++) {
                m_player[i]->SetResult(-1, 9);
                charNo[i] = GetCharNo(m_player[i]);
            }
            HuAudJinglePlay(0x7B);
            CharLoseVoicePlay(charNo[0], charNo[1], charNo[2], charNo[3]);
        }
        HuAudFXPlay(0x7AA);
        m_sub++;
    case 1:
        m_frame++;
        if ((m_percent[0] == 100.0f || m_percent[1] == 100.0f) && m_frame % 15 == 0 && m_winTeam != -1) {
            float side = m_winTeam == 0 ? -1.0f : 1.0f;
            Vec pos;
            Vec rot = { 0.0f, 0.0f, 0.0f };

            pos.x = side * (325.0f + 200.0f * ((1.0f / 32768) * ((frand() & 0xFFFF) - 32768.0f)));
            pos.y = -(200.0f * ((1.0f / 65536) * (frand() & 0xFFFF)));
            pos.z = 700.0f;
            new CConfetti(10, pos, rot);
            pos.x = 550.0f * side;
            pos.y = -(200.0f * ((1.0f / 65536) * (frand() & 0xFFFF)));
            pos.z = -252.0f + 43.8f * (20.0f * ((1.0f / 65536) * (frand() & 0xFFFF)));
            new CConfetti(10, pos, rot);
        }
        if (m_frame < 210.0) {
            break;
        }
        GameMesDispSet(m_resultMes, GAMEMES_DISP_SET, -1);
    default:
        m_sub = 0;
        setMode(6);
        break;
    }
}

void CFlow::mode6()
{
    switch (m_sub) {
    case 0:
        WipeCreate(WIPE_MODE_OUT, 6, 60);
        delete m_score;
        m_score = 0;
        m_sub++;
    case 1:
        if (WipeCheckEnd()) {
            break;
        }
        m_sub++;
    default:
        delete this;
        GameMesClose();
        HuAudFadeOut(60);
        omOvlReturnEx(1, 1);
        break;
    }
}

bool CFlow::checkEnd(int time)
{
    CCleanEffMan* man = m_cleanEff;
    int result;

    if (time > 0) {
        result = man->judge(false);
        if (result != 2) {
            if (result == 0) {
                m_winTeam = 0;
            } else {
                m_winTeam = 1;
            }
            m_endType = 1;
            return true;
        }
        CCleanEff* eff0 = man->get(0);
        CCleanEff* eff1 = man->get(1);
        if (eff0->ratio() >= 1.0f && eff1->ratio() >= 1.0f) {
            m_winTeam = -1;
            m_endType = 1;
            return true;
        }
    } else {
        result = man->judge(true);
        if (result != 2) {
            if (result == 0) {
                m_winTeam = 0;
            } else {
                m_winTeam = 1;
            }
        } else {
            m_winTeam = -1;
        }
        m_endType = 0;
        return true;
    }
    return false;
}

float CFlow::getGrid(int team, int x, int z)
{
    float v;

    if (team == 0) {
        v = m_gridA[z][x];
    } else {
        v = m_gridB[z][x];
    }
    return v;
}

void CFlow::setGrid(int team, int x, int z, float v)
{
    if (team == 0) {
        m_gridA[z][x] = v;
    } else {
        m_gridB[z][x] = v;
    }
}

void CFlow::on_close() {}

} // namespace m531

/* bss_1C: the weak template static retail kept in flow.o (object.o/cleaneff.o use it). Declared at the TU end;
 * CW still allocates it before the sort statics (bss_20/24), as retail. */
#ifdef __MWERKS__
template <> m531::CCleanEffMan* CSingleton<m531::CCleanEffMan>::ms_pointer;
#else
template <> m531::CCleanEffMan* CSingleton<m531::CCleanEffMan>::ms_pointer = 0;
#endif
