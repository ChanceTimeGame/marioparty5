/* singleton.h -- CSingleton<T>: an empty base that registers the one live T.
 * The retail asserts name the pointer `ms_pointer` (singleton.h:39 GetInstance, :53 ctor, :61 dtor), so the
 * assert() lines below must stay on those line numbers (they are part of .data).
 *
 * Storage: the retail linker kept ONE weak copy of each CSingleton<T>::ms_pointer, in the first TU of the
 * link order that instantiated it (m501: CMinigameCore; gamemaster: CStage, CCameraObj; asiato: CParticle),
 * at the end of that TU's .bss. There is deliberately no generic definition here: each ms_pointer is an
 * explicit specialisation defined at the end of the TU that owns it (CW treats even a declaration-only
 * explicit specialisation as a definition, so the host-only declarations below are #ifndef __MWERKS__).
 * symbols.txt calls them instance__13CMinigameCore, stageInstance__/cameraInstance__Q24m50111CGameMaster
 * and lbl_1_bss_54 (map.<unit>.txt).
 */
#ifndef MGCPP_SINGLETON_H
#define MGCPP_SINGLETON_H

#include "REL/mgcpp/assert.h"













template <class T>
class CSingleton {
public:
    static T* ms_pointer;

    /* the three bodies sit on the retail assert lines 39 / 53 / 61 */

    static T* GetInstance()
    {
        assert(ms_pointer != 0);
        return ms_pointer;
    }









    CSingleton()
    {
        assert(ms_pointer == 0);
        ms_pointer = static_cast<T*>(this);
    }



    ~CSingleton()
    {
        assert(ms_pointer != 0);
        ms_pointer = 0;
    }

    /* no assert: CMinigameCore::ObjUpdate/MgExit read the pointer through a one-temp inline like this */
    static T* GetInstancePtr() { return ms_pointer; }
};

#endif
