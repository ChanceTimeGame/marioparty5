/* input.cpp -- m539::CInput / CInputPad / CInputCom. Retail order: update, CInputPad(), ~CInput,
 * CInputPad::get, CInputCom(), CInputCom::get, thread_exec, [~CInputCom, ~CInputPad, the two thunks].
 * Complete: all 11 functions raw-identical, .data identical (W1 skeleton). */
#include "REL/m539Dll/input.h"
#include "REL/mgcpp/random.h"

namespace m539 {

void CInput::update()
{
    m_data.on = false;
    get(&m_data);
}

CInputPad::CInputPad(int idx)
{
    m_idx = idx;
    m_padNo = GwPlayerConf[idx].padNo;
}

CInput::~CInput() {}

void CInputPad::get(Data* data)
{
    int pad = m_padNo;
    data->on = (HuPadBtnDown[pad] & PAD_BUTTON_A) != 0;
}

CInputCom::CInputCom() : CSubThread(0x8000) {}

void CInputCom::get(Data* data)
{
    wakeupThread((CThreadParam)data);
}

void CInputCom::thread_exec(CThreadParam param)
{
    Data* data = (Data*)param;
    for (int n = 8; n != 0; n--) {
        int wait = CRandom::irandom() % 30 + 30;
        while (wait > 0) {
            sleepThread(0);
            wait--;
        }
        data->on = true;
    }
}

} // namespace m539
