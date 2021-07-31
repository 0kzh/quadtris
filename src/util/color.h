#ifndef COLOR_H
#define COLOR_H

#include "types.h"
#include <map>

struct Color {
  int r;
  int g;
  int b;
};

struct ColorSet {
  Color base;
  Color highlight;
  Color shadow;
};

inline std::map<BlockType, ColorSet> blockColors{
    {I,    {Color{0, 240, 238}, Color{178, 251, 250}, Color{0, 216, 214}}},
    {J,    {Color{0, 0, 239},   Color{180, 178, 251}, Color{0, 0, 120},}},
    {L,    {Color{240, 160, 1}, Color{252, 228, 178}, Color{216, 145, 0},}},
    {O,    {Color{241, 240, 0}, Color{251, 251, 180}, Color{218, 216, 0}}},
    {S,    {Color{0, 240, 0},   Color{179, 252, 180}, Color{0, 216, 0}}},
    {Z,    {Color{241, 1, 1},   Color{255, 177, 178}, Color{217, 0, 2}}},
    {T,    {Color{159, 0, 240}, Color{226, 180, 252}, Color{142, 1, 217}}},
    {WALL, {Color{79, 79, 79},  Color{200, 200, 200}, Color{26, 26, 26}}}
};

#endif
