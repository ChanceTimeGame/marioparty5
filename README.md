# Mario Party 5 (US) decompilation

A matching decompilation of Mario Party 5 (GameCube, US, `GP5E01_00`). Built with the original
compilers, it produces a `main.dol` and RELs byte-identical to the retail game.

**Progress:** 18,000 of 21,231 functions match (84.8%), 82.3% of code bytes. Everything else is either
decompiled C that does not yet compile to identical code, or code with no C yet.
[OPEN_FUNCTIONS.md](OPEN_FUNCTIONS.md) lists every one of them.

This repository is a fork of [mariopartyrd/marioparty5](https://github.com/mariopartyrd/marioparty5).
Thanks to everyone who worked on it.

## Why this fork exists: Chance Time

This fork is the decompilation behind Mario Party 5 in **Chance Time**, a native PC port of the
N64 and GameCube Mario Party games. Chance Time ships no game data: players supply their own ROM
or disc.

How the two fit together:

- **This repository is a pure matching decompilation.** It holds decompiled game code only, with
  no PC-port code, no `#ifdef` for a PC build and no host types. Every commit passes the
  `build.sha1` check against the retail disc.
- **Chance Time compiles this code for the PC.** While Mario Party 5 is short of 100%, matching
  work is done alongside the port and published here with every port change removed. Once it
  reaches 100%, Chance Time takes this repository as a submodule and keeps its own changes as a
  patch series on top, as it already does for
  [Mario Party 4](https://github.com/ChanceTimeGame/marioparty4).
- **Non-matching C must still be correct.** The PC port compiles every unit's C, including units
  still marked `NonMatching`, so a function is only left short of 100% once its remaining
  difference is register allocation, instruction order or a symbol name: same calls, same
  constants, same stores.
- **The Mario Party games share an engine.** Mario Party 4 is fully matched
  ([ChanceTimeGame/marioparty4](https://github.com/ChanceTimeGame/marioparty4)) and Mario Party 6
  is under way ([ChanceTimeGame/marioparty6](https://github.com/ChanceTimeGame/marioparty6)). A
  matched function in one game is often the starting point for its twin in another, and Mario
  Party 4's Dolphin SDK and runtime sources are the base for this game's later revision.

Once Mario Party 5 reaches 100% this repository is finished: it takes genuine decompilation fixes
only.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for the workflow, the checks a change must pass and the
compiler details that matter, and [OPEN_FUNCTIONS.md](OPEN_FUNCTIONS.md) for where to start. Pull
requests are welcome.

## Building

This repository contains no game assets or assembly. You need your own copy of the game.

1. Install [Python 3](https://www.python.org/downloads/) and
   [ninja](https://github.com/ninja-build/ninja/releases) (`pip install ninja` works). On Linux
   x86-64, [wibo](https://github.com/decompals/wibo) is downloaded for the Windows compilers; on
   other Linux platforms and on macOS, install Wine. On Windows, use native tools: WSL is not
   needed.
2. `git clone https://github.com/ChanceTimeGame/marioparty5`.
3. Put your disc image (ISO, RVZ, WIA, WBFS, CISO, NFS, GCZ or TGC) in `orig/GP5E01_00/`. After the
   first build it can be deleted.
4. `python configure.py`, then `ninja`. The build checks every output against
   `config/GP5E01_00/build.sha1`; `ninja progress` prints the totals.

To compare functions, open the repository in [objdiff](https://github.com/encounter/objdiff): it
reads `objdiff.json`, written by the first build, and rebuilds on every change.
