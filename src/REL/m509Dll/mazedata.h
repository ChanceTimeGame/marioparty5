/* mazedata.h -- m509::mazeData (mazedata.cpp): the 64 prebuilt maze layouts, 12 rows of 16 cell bytes each
 * (x 0..14 real, column 15 / row 11 phantom = 0xCF). A byte: bit 7 wall on the cell's left edge, bit 6 wall on
 * its top edge, low nibble the direction to the goal (1 -Z, 2 +Z, 3 -X, 4 +X, 5 goal at (7,5); 0xF phantom).
 * In .data (writable: a const table would move to .rodata), data_210, 0x3000 bytes. Read by
 * CMazeSelector::setLayout (maze.cpp) only. */
#ifndef M509_MAZEDATA_H
#define M509_MAZEDATA_H

#include "REL/mgcpp/game.h"

namespace m509 {

enum { MAZE_LAYOUTS = 64, MAZE_ROWS = 12, MAZE_COLS = 16 };

extern u8 mazeData[MAZE_LAYOUTS][MAZE_ROWS][MAZE_COLS];

} // namespace m509

#endif
