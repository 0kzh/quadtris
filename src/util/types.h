#ifndef TYPES_H_
#define TYPES_H_

#include <iostream>
#include <optional>
#include <map>
#include <vector>

// enums for all possible block types
enum BlockType {
  I, J, L, O, S, Z, T, LFOUR, WALL, HINT
};

// the blocks that we can actually generate
// excludes LFOUR, WALL and HINT types
const int NUM_BLOCK_TYPES = 7;

// map of block types to their textual representations
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

// map of characters to their block types
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

// enums for all possible directions
enum Direction {
  LEFT, RIGHT, DOWN
};

// enums for all possible rotations
enum RotationDirection {
  CW, CCW
};

// Specifies block type and ID values for a GridItem
struct GridItem {
  std::optional<BlockType> val = std::nullopt;
  std::optional<int> blockId = std::nullopt;
};

// A gridshape is a list of GridItems that defines the shape of 
// a block
typedef std::vector<std::vector<GridItem>> GridShape;

// GridItems are compatible with the << stream operator
std::ostream &operator<<(std::ostream &os, GridItem g);

#endif
