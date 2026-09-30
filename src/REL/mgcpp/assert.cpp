/* assert.cpp -- __assert_fail and the framework fprintf. The OSPanic must stay on line 18. */
#include "REL/mgcpp/assert.h"

#ifdef __MWERKS__
#include <stdarg.h>
#else
#include <stdarg.h>
#endif




/* prints "ASSERTION FAILED at file:line" and the expression, then panics (does not return) */
extern "C" void __assert_fail(const char* expr, const char* file, int line)
{
    char buf[1024];
    sprintf(buf, "\nASSERTION FAILED at %s:%d\n%s", file, line, expr);
    OSPanic(__FILE__, __LINE__, buf);
}

/* ignores the stream and vprintf()s (the MSL vector error path calls it with stderr, then abort()) */
extern "C" int fprintf(FILE* stream, const char* format, ...)
{
    va_list args;
    int ret;
    va_start(args, format);
    ret = vprintf(format, args);
    return ret;
}
