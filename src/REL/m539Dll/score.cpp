/* score.cpp -- m539::CScore, the per-player slot machine. Retail order: LoadModelCached, CreateDigit, setDigit,
 * ctor, [~auto_ptr<CScoreSpr>, auto_ptr<CModel> __defctor, auto_ptr<CDrum> __defctor, ~TLinkItem<CScore>],
 * UpdateCell/StartCell/PressCell, start, finishA, appear, spawnBlockEffect, update, startSpin, finishB,
 * stopNext, checkLine, IsAllStopped, updateBlockMtx; auto_ptr<CDrum>(CDrum*) at the end.
 * (sheet master_camera_score_shadow.md §6) */
#include "REL/m539Dll/score.h"
#include "REL/m539Dll/drum.h"
#include "REL/m539Dll/effect.h"

namespace m539 {

/* .rodata: CW emits each file-scope table where it is declared, among the functions' pooled constants, so each
 * table is declared just before its first user (retail .rodata order). */

CModel* CScore::LoadModelCached(u32 dataNum, CModel** cache)
{
    if (*cache) {
        return new CModel(**cache);
    }
    *cache = new CModel(dataNum);
    return *cache;
}

CModel* CScore::CreateDigit(CModel* board, int n)
{
    CModel* m = CModelMan::Create(0x610008);
    char buf[8];
    sprintf(buf, "sd%02d", n);
    Mtx mtx;
    Hu3DModelObjMtxGet(board->id(), buf, mtx);
    Vec pos;
    pos.x = mtx[0][3];
    pos.y = mtx[1][3];
    pos.z = mtx[2][3];
    m->setPos(&pos);
    m->setAttr(HU3D_MOTATTR_PAUSE);
    return m;
}

void CScore::setDigit(int i, float v)
{
    CModel* m = m_digit[i].get();
    v = fmod(v, 10.0);
    v = 10.0f * -v;
    v = fmod(v, 100.0);
    if (v < 0.0f) {
        v += 100.0f;
    }
    Hu3DMotionTimeSet(m->id(), v);
}

CScore::CScore(int no)
    : m_no(no), m_base(CModelMan::Create(0x610002)), m_board(CModelMan::Create(0x610003)),
      m_block(CModelMan::Create(0x610009)), m_head(CModelMan::Create(0x610004)), m_scale(0.0f, 0), m_disp(0.0f, 0),
      m_unkB8(0), m_tick(0)
{
    insertBack(ASet<CScore>::instance());
    m_base->setAttr(HU3D_MOTATTR_LOOP);
    m_head->setAttr(HU3D_MOTATTR_PAUSE);
    m_block->resetAttr(HU3D_MOTATTR_LOOP);
    m_block->setAttr(HU3D_MOTATTR_PAUSE);
    m_block->setMotTime(0);
    CModel* board = m_board.get();
    char name[4] = "d??";
    for (int r = 0; r < 3; r++) {
        name[1] = "012"[r];
        for (int c = 0; c < 3; c++) {
            name[2] = "012"[c];
            m_cell[r][c].reset(new CDrum(board, name, no));
        }
    }
    m_cell[1][1]->RemoveBody();
    m_base->setCamera(1 << no);
    m_head->set_shadow();
    m_block->setCamera(1 << no);
    for (int i = 0; i < 3; i++) {
        m_digit[i].reset(CreateDigit(board, i));
        m_digit[i]->setCamera(1 << no);
        setDigit(i, (float)i);
    }
    m_stopCount = 0;
    m_angle = 3.1415927f;
    m_score = 0;
    m_lastDisp = 0;
}

/* .rodata 358: UNREFERENCED in retail (an old per-player layout table), emitted in place */
static const Vec s_unusedPosA[4] = { { 96.0f, 196.0f, 0.0f }, { 376.0f, 196.0f, 0.0f }, { 96.0f, 416.0f, 0.0f },
    { 376.0f, 416.0f, 0.0f } };

void CScore::UpdateCell(CDrum* d)
{
    d->Update();
}

void CScore::StartCell(CDrum* d)
{
    d->Start();
}

void CScore::PressCell(CDrum* d)
{
    d->Press();
}

void CScore::start()
{
    m_head->resetAttr(HU3D_MOTATTR_PAUSE);
    HuAudFXPlay(0x7E4);
}

void CScore::finishA()
{
    m_scale.Set(0.0f, 0x12);
    HuAudFXPlay(0x7E5);
    if (m_no == 0) {
        spawnBlockEffect();
    }
}

void CScore::appear()
{
    m_scale.Set(1.0f, 0x12);
    if (m_no == 0) {
        HuAudFXPlay(0x7E5);
        spawnBlockEffect();
    }
}

void CScore::spawnBlockEffect()
{
    HSFOBJECT* o = m_block->getObjPtr("block");
    double x, y, z;
    z = 100.0f + o->mesh.base.pos.z;
    y = o->mesh.base.pos.y;
    x = o->mesh.base.pos.x - 20.0f;
    Vec p;
    p.x = x;
    p.y = y;
    p.z = z;
    new CEffect(&p);
}

static const int s_seTick[4] = { 0x7F6, 0x7F8, 0x7F7, 0x7F9 };  /* 390 update */

void CScore::update()
{
    bool tick;
    execCells(UpdateCell);
    Mtx mtx;
    Hu3DModelObjMtxGet(m_head->id(), (char*)"head", mtx);
    Vec* pos = &m_headPos;
    pos->x = mtx[0][3];
    pos->y = mtx[1][3];
    pos->z = mtx[2][3];
    PSVECSubtract(&m_headPos, &m_headPrev, &m_headVel);
    m_headPrev = m_headPos;
    updateBlockMtx();
    float disp = m_disp.Update();
    int hundreds = disp / 100.0f;
    int tens = disp / 10.0f;
    int ones = fmod(disp, 10.0);
    tick = false; /* retail: set and never read */
    if (m_tick > 0 && --m_tick == 0) {
        tick = true;
    }
    if ((int)disp != m_lastDisp) {
        m_lastDisp = (int)disp;
        HuAudFXPlay(s_seTick[m_no]);
        m_tick = 3;
    }
    if (m_spr.get() != 0) {
        CScoreSpr* spr = m_spr.get();
        spr->m_value = (int)disp;
    }
    setDigit(2, hundreds);
    setDigit(1, tens);
    setDigit(0, ones);
}

static const int s_seSpin[4] = { 0x7E6, 0x7E8, 0x7E7, 0x7E9 };  /* 3A0 startSpin */

void CScore::startSpin()
{
    execCells(StartCell);
    m_head->setCamera(1 << m_no);
    m_spinSe = HuAudFXPlay(s_seSpin[m_no]);
}

void CScore::finishB()
{
    execCells(PressCell);
}

static const u8 s_ring[8] = { 0x00, 0x01, 0x02, 0x10, 0x12, 0x20, 0x21, 0x22 }; /* 3B0 row << 4 | col */
static const int s_seStop[4] = { 0x7EA, 0x7EC, 0x7EB, 0x7ED };  /* 3B8 */
static const int s_seStopB[4] = { 0x7EE, 0x7F0, 0x7EF, 0x7F1 }; /* 3C8 */

void CScore::stopNext()
{
    int n = m_stopCount;
    if (n < 8) {
        HuAudFXPlay(s_seStop[m_no]);
        int col = s_ring[n] & 3;
        int row = (s_ring[n] >> 4) & 3;
        m_cell[row][col]->Stop();
        m_stopCount = ++n;
        if (n == 8) {
            HuAudFXStop(m_spinSe);
        }
        m_angle = 0.0f;
        m_block->resetAttr(HU3D_MOTATTR_PAUSE);
        m_block->setMotTime(0);
        HuAudFXPlay(s_seStopB[m_no]);
    }
}

static const u8 s_lines[8][3] = { { 0x00, 0x01, 0x02 }, { 0x10, 0x11, 0x12 }, { 0x20, 0x21, 0x22 },
    { 0x00, 0x10, 0x20 }, { 0x01, 0x11, 0x21 }, { 0x02, 0x12, 0x22 }, { 0x00, 0x11, 0x22 }, { 0x02, 0x11, 0x20 } }; /* 3D8 */
/* .rodata 3F0: UNREFERENCED in retail (a second layout table), emitted in place */
static const Vec s_unusedPosB[4] = { { 64.0f, 140.0f, 0.0f }, { 344.0f, 140.0f, 0.0f }, { 64.0f, 360.0f, 0.0f },
    { 344.0f, 360.0f, 0.0f } };
static const int s_sePay[4] = { 0x7F2, 0x7F4, 0x7F3, 0x7F5 };   /* 420 checkLine */

int CScore::checkLine(int line)
{
    CDrum* c[3];
    for (int k = 0; k < 3; k++) {
        int col = s_lines[line][k] & 3;
        int row = (s_lines[line][k] >> 4) & 3;
        c[k] = m_cell[row][col].get();
    }
    CSlotJudge j;
    if (j.Judge(c[0]->GetSymbol(), c[1]->GetSymbol(), c[2]->GetSymbol())) {
        for (int k = 0; k < 3; k++) {
            c[k]->PlayHit();
        }
    }
    if (j.GetTotal() != 0) {
        m_score += j.GetTotal();
        m_disp.Set((float)m_score, 0x24);
        HuAudFXPlay(s_sePay[m_no]);
    }
    return j.GetTotal();
}

bool CScore::IsAllStopped()
{
    ASet<CScore>* set = ASet<CScore>::instance();
    CScore* p = set->begin();
    CLinkNode* end = set->end();
    for (; p != end; p = p->next()) {
        if (p->m_stopCount != 8) {
            return false;
        }
    }
    return true;
}

void CScore::updateBlockMtx()
{
    HSFOBJECT* o = m_block->getObjPtr("block");
    Mtx* m = m_block->getMatrix();
    float x = o->mesh.base.pos.x;
    float y = o->mesh.base.pos.y;
    float z = o->mesh.base.pos.z;
    float s = m_scale.Update();
    Mtx r;
    PSMTXRotRad(r, 'Y', -0.2617994f);
    PSMTXTrans(*m, -x, -y, -z);
    PSMTXScaleApply(*m, *m, s, s, s);
    PSMTXConcat(*m, r, *m);
    PSMTXTransApply(*m, *m, x, y, z);
}

} // namespace m539
