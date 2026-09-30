#include "REL/m513Dll/player.h"
#include "REL/m513Dll/input.h"
#include "REL/m513Dll/powerind.h"
extern "C" {
#include "game/frand.h"
}

namespace m513 {

void CInput::update()
{
    m_data.x = 0.0f;
    m_data.y = 0.0f;
    m_data.btn = 0;
    get(&m_data);
}

CInputPad::CInputPad(int idx)
{
    m_idx = idx;
    m_padNo = GwPlayerConf[idx].padNo;
}

CInput::~CInput() {}

/* the stick is mapped (double precision) and dropped by CPlayer; only btn matters */
void CInputPad::get(Data* data)
{
    int padNo = m_padNo;
    double x = (1.0f / 56.0f) * (s8)HuPadStkX[padNo];
    double y = (1.0f / 56.0f) * (s8)HuPadStkY[padNo];
    x = sin(M_PI * x / 2.0);
    y = sin(M_PI * y / -2.0);
    double m = sqrt(x * x + y * y);
    if (m > 1.0) {
        double inv = 1.0 / m;
        x *= inv;
        y *= inv;
        m = 1.0;
    }
    data->x = x;
    data->y = y;
    data->mag = m;
    data->btn = HuPadBtnDown[padNo];
}

/* lbl_1_data_248: the COM's base interval (frames) by difficulty (non-const: .data) */
static float s_comBase[4] = { 9.5f, 5.5f, 4.5f, 2.5f };

/* (frand() & 0xFFFF) / 65536 as an expression: an inline function keeps its result in a saved FPR; a literal
 * division by 65536.0f is not turned into the retail fmul */
#define RND() ((1.0f / 65536) * (frand() & 0xFFFF))

CInputCom::CInputCom(int idx, int dif)
{
    m_idx = idx;
    m_data.level = dif;
    m_bias = ((3.0f - dif) / 3.0f) * (3.0f * RND());
    m_base = s_comBase[dif];
    m_timer = m_bias + (m_base + 2.5f * RND());
}

CInputCom::~CInputCom() {}

void CInputCom::get(Data* data)
{
    int level = data->level; /* retail: read into a dead local */
    data->btn = 0;
    u8 unused = 0;
    if (m_timer-- < 0) {
        data->btn |= PAD_BUTTON_A;
        m_timer = m_bias + (m_base + 2.5f * RND());
    }
}

} // namespace m513

template <> m513::CPowerInd* CSingleton<m513::CPowerInd>::ms_pointer = 0;
