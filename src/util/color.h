#ifndef COLOR_H
#define COLOR_H

#include "types.h"
#include <map>

//Specifies RGB values for desired colours
struct Color {
  int r;
  int g;
  int b;
};

//Specifies colour sets for thematic use
struct ColorSet {
  Color base;
  Color highlight;
  Color shadow;
};

//Maps types of blocks to their respective colours
inline std::map<BlockType, ColorSet> blockColors{
    {I,    {Color{0, 240, 238}, Color{178, 251, 250}, Color{0, 216, 214}}},
    {J,    {Color{0, 0, 239},   Color{180, 178, 251}, Color{0, 0, 120},}},
    {L,    {Color{240, 160, 1}, Color{252, 228, 178}, Color{216, 145, 0},}},
    {O,    {Color{241, 240, 0}, Color{251, 251, 180}, Color{218, 216, 0}}},
    {S,    {Color{0, 240, 0},   Color{179, 252, 180}, Color{0, 216, 0}}},
    {Z,    {Color{241, 1, 1},   Color{255, 177, 178}, Color{217, 0, 2}}},
    {T,    {Color{159, 0, 240}, Color{226, 180, 252}, Color{142, 1, 217}}},
    {LFOUR,    {Color{204, 102, 0}, Color{240, 189, 138}, Color{102, 51, 0}}},
    {WALL, {Color{79, 79, 79},  Color{200, 200, 200}, Color{26, 26, 26}}},
    {HINT, {Color{25, 25, 25},  Color{50, 50, 50},    Color{10, 10, 10}}}
};

#endif
