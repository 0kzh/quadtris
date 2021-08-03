#ifndef TYPES_H_
#define TYPES_H_

#include <iostream>
#include <optional>
#include <map>
#include <vector>

enum BlockType {
  I, J, L, O, S, Z, T, LFOUR, WALL, HINT
};

// the blocks that we can actually generate
// excludes LFOUR, WALL and HINT types
const int NUM_BLOCK_TYPES = 7;

inline std::map<BlockType, char> blockTypeToChar{
    {I,    'I'},
    {J,    'J'},
    {L,    'L'},
    {O,    'O'},
    {S,    'S'},
    {Z,    'Z'},
    {T,    'T'},
    {LFOUR, '*'},
    {HINT, '?'},
};

inline std::map<char, BlockType> charToBlockType = {
    {'I', I},
    {'J', J},
    {'L', L},
    {'O', O},
    {'S', S},
    {'T', T},
    {'Z', Z},
    {'*', LFOUR}
};

enum Direction {
  LEFT, RIGHT, DOWN
};

enum RotationDirection {
  CW, CCW
};

struct GridItem {
  std::optional<BlockType> val = std::nullopt;
  std::optional<int> blockId = std::nullopt;
};

typedef std::vector<std::vector<GridItem>> GridShape;

std::ostream &operator<<(std::ostream &os, GridItem g);

#endif
