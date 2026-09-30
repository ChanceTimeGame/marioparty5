#ifndef M509_STARTSPR_H
#define M509_STARTSPR_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"

namespace m509 {

class CStartSpr : public CGameObject, public CSingleton<CStartSpr> {
public:
    struct Entry {
        HUSPRGRPID grp;  /* 0x0 */
        float x;         /* 0x4 */
        float y;         /* 0x8 */
    };

    CStartSpr(int* charNo);           /* fn_1_C924 charNo[4] by player */
    virtual ~CStartSpr();             /* fn_1_CC04 kills the groups (not the anims) */
    virtual void on_update();         /* fn_1_CD08 fade in / out; delete this at alpha < 0 */
    virtual void on_new_mode(int mode);

    bool m_fadeOut;   /* 0x10 */
    int m_timer;      /* 0x14 signed */
    float m_alpha;    /* 0x18 */
    Entry m_entry[4]; /* 0x1C */
};

} // namespace m509

#ifndef __MWERKS__
template <> m509::CStartSpr* CSingleton<m509::CStartSpr>::ms_pointer; /* defined in startspr.cpp */
#endif

#endif
