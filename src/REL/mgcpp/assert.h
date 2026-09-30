/* assert.h -- the framework's assert (assert.cpp). Not <assert.h>: __assert_fail is the framework's own
 * (it formats "\nASSERTION FAILED at %s:%d\n%s" and OSPanics from assert.cpp:18), and it is compiled in on
 * retail. The expression text and __FILE__/__LINE__ are part of .data, so keep assert() calls on their
 * retail lines (the W0 fact sheets list every file:line).
 * MGCPP_NO_ASSERT drops the check (camera.cpp's inlined CSingleton has none -- see SKELETON.md). */
#ifndef MGCPP_ASSERT_H
#define MGCPP_ASSERT_H

#include "REL/mgcpp/game.h"

extern "C" void __assert_fail(const char* expr, const char* file, int line);

#ifdef assert
#undef assert
#endif
#ifdef MGCPP_NO_ASSERT
#define assert(e) ((void)0)
#else
#define assert(e) ((e) ? (void)0 : __assert_fail(#e, __FILE__, __LINE__))
#endif


#endif
