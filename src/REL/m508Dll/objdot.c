/*
 * objdot.c -- the trailing pair.
 *
 * m508.o ends with a SECOND out-of-line copy of m526dll/math.c's
 * MathDot2DGet and MathCross2DGet, at fn_1_A154 and fn_1_A174, after the
 * whole object library. object.o has no such pair. Both are already emitted
 * once at fn_1_5D20/fn_1_5D40 with math.c's other twelve, and every caller in
 * the unit inlines them, so this second copy can only come from a second
 * definition in a file that CodeWarrior closes AFTER objlib.c: an #included
 * file's .text is emitted as its own section, ordered by where the include
 * ends, so a file included at the bottom of m508.c lands past the library.
 *
 * What the original file was is not recoverable from the object -- the bodies
 * are byte-identical to math.c's, so this is a reconstruction of the LAYOUT,
 * not of the reason. See the report/NOTES entry before trusting it.
 */
static float fn_1_A154(HuVec2f *a, HuVec2f *b)
{
    return (a->x*b->x)+(a->y*b->y);
}

static float fn_1_A174(HuVec2f *a, HuVec2f *b)
{
    return (a->x*b->y)-(a->y*b->x);
}
