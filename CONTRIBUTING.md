# Contributing

Thanks for helping finish Mario Party 5. This page covers how a function goes from the original
code to matching C, what a pull request has to pass, and the compiler behaviour that decides most
of the hard cases. [OPEN_FUNCTIONS.md](OPEN_FUNCTIONS.md) lists what is left.

## Ground rules

- **The build must match.** Every commit passes `config/GP5E01_00/build.sha1`: `ninja` finishes
  without a failed check.
- **Decompiled code only.** No PC-port code, no `#ifdef` for other platforms. (Chance Time keeps its
  port changes in its own repository; see the README.)
- **Non-matching C must be correct C.** A unit may stay `NonMatching`, but a function in it may only
  stay short of 100% once its remaining difference is register allocation, instruction order or a
  name. Ports compile that C, so a wrong constant, stride, comparison or call is a bug, not residue.
- **Real names over guessed ones.** Rename a function, struct or field when you know what it does;
  leave `fn_*` / `lbl_*` otherwise. A name in `symbols.txt` that is a guess is not a retail symbol;
  do not describe it as one.

## Decompiling a function

1. Find the unit in `configure.py` and its source under `src/`. Each REL is a module under
   `src/REL/<name>/`; the DOL is `src/game`, `src/libhu`, `src/msm`, `src/musyx`, the Dolphin SDK (`src/dolphin`) and the
   runtime libraries.
2. **Look for a twin first.** Mario Party 4 and 6 share the engine and most of the SDK, and many
   board, menu and minigame functions exist in two or three games. Search
   [marioparty4](https://github.com/ChanceTimeGame/marioparty4) (100% matched) and
   [marioparty6](https://github.com/ChanceTimeGame/marioparty6) for the callees or constants: a
   matched twin is usually the best start.
3. Otherwise start from the function's assembly (`build/GP5E01_00/asm/`, written by `ninja`) with
   [m2c](https://github.com/matt-kempster/m2c) or on [decomp.me](https://decomp.me) (game and REL
   code: compiler `GC/2.6`, flags `-O0,p`; the unit's exact flags are in `configure.py`).
4. Write the C and compare in [objdiff](https://github.com/encounter/objdiff). A function at 100%
   matches; when every function and the unit's data are 100%, change the unit from `NonMatching` to
   `Matching` in `configure.py` and check that `ninja` still passes `build.sha1`.

## When it will not match

Work the differences in this order; a later kind is usually caused by an earlier one:

1. **A wrong symbol, field or callee** (instructions equal, a relocation differs). Fix the identity;
   this is not a code-generation problem. objdiff compares references by name, so an unnamed
   target label shows up as a differing row too.
2. **A different set of calls or memory accesses.** Finish the body, or look for an inline helper or
   a macro.
3. **Different control flow.** Change the source structure: loop form, early return, condition
   order.
4. **Registers and scheduling only.** Check variable types, declaration order and lifetimes, then try
   [decomp-permuter](https://github.com/simonlindholm/decomp-permuter).

A permuter score of 0 is a candidate, not a match: paste the result verbatim, rebuild, and only
objdiff 100% plus a passing `build.sha1` counts.

### Fakematches

A form that matches only because of what it does to the compiler (a stray `volatile`, a dummy
local, a self-assignment, an empty `do {} while (0)`) is a fakematch. It is better than nothing, so
keep it, but say so in a comment: it usually points at a wrong type, a missing inline or a macro.

## Compiler notes (Metrowerks CodeWarrior)

- **Game and REL code builds at `-O0,p`; the SDK and runtime at `-O4,p`.** The flags are per unit
  in `configure.py`; a library function that is "almost" matching may be in the wrong group.
- **Inline expansion follows definition order.** CodeWarrior expands a `static` (or `inline`)
  function defined earlier in the file inline, even at `-O0,p`; a call to one defined later stays a
  call. When a caller's call list differs from the original, check the order and the spelling of
  the helpers in the file before anything else. An empty stub distorts its callers.
- **Retail often calls a DOL function with no prototype in scope** (audio calls from the `mg*`
  units, `esp*` from the timers). The tell is a missing `mr` copying the result after the call, or
  an extra `extsh` on an `s16` argument. Match it by leaving the prototype out of that unit, not by
  changing the function.
- **C++ compiler-generated functions** (destructors, template members, thunks) are weak symbols.
  They match once they carry the right name in `symbols.txt`; most of what remains at 0% in the C++
  modules is shaped differently, not misnamed.
- **objdiff 100% is not the whole check.** It can show 100% with a reference to the wrong `.bss` or
  `.sbss` symbol (CodeWarrior lays `.sbss` out in reverse declaration order). `build.sha1` is the
  proof; run `ninja` before opening a pull request.
- **Dolphin SDK:** this is a later revision than Mario Party 4's. Start from MP4's file, keep the
  functions that score 100% and decompile only what changed.

## Pull requests

Before opening one:

- `ninja` passes every `build.sha1` check from a clean build (`ninja -t clean && ninja`).
- Every function you changed builds and none scores lower than before (`ninja progress`).
- No unrelated reformatting.

Small pull requests (one unit or a handful of functions) are easiest to review.
