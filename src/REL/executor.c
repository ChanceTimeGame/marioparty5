/*
 * The module entry points: every REL's first unit has them at .text 0. The
 * loader calls _prolog after linking a module (static constructors, then
 * ObjectSetup) and _epilog before unlinking it (static destructors). A unit
 * includes this file once, ahead of its first function.
 *
 * CodeWarrior only: _ctors/_dtors come from its linker, and the port loads each
 * module as a shared library and calls ObjectSetup itself (bootDll's boot.c
 * guards its own copy the same way).
 */
#ifdef __MWERKS__
typedef void (*REL_CTORFUNC)(void);
extern const REL_CTORFUNC _ctors[];
extern const REL_CTORFUNC _dtors[];

void ObjectSetup(void);

int _prolog(void) {
    const REL_CTORFUNC* ctors = _ctors;
    while (*ctors != 0) {
        (**ctors)();
        ctors++;
    }
    ObjectSetup();
    return 0;
}

void _epilog(void) {
    const REL_CTORFUNC* dtors = _dtors;
    while (*dtors != 0) {
        (**dtors)();
        dtors++;
    }
}
#endif
