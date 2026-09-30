#ifndef MGCPP_NEW_H
#define MGCPP_NEW_H

#include "REL/mgcpp/game.h"

void* operator new(size_t size);   /* __nw__FUl   */
void* operator new[](size_t size); /* __nwa__FUl  */
void operator delete(void* p);     /* __dl__FPv   */
void operator delete[](void* p);   /* __dla__FPv  */

#endif
