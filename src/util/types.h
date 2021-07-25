#ifndef TYPES_H_
#define TYPES_H_

#include <iostream>
#include <optional>
#include <map>

enum BlockType {
  I, J, L, O, S, Z, T
};

inline std::map<BlockType, char> blockTypeToString{
    {I, 'I'},
    {J, 'J'},
    {L, 'L'},
    {O, 'O'},
    {S, 'S'},
    {Z, 'Z'},
    {T, 'T'}
};

enum Direction {
  LEFT, RIGHT, DOWN
};

enum RotationDirection {
  CW, CCW
};

struct GridItem {
  std::optional<BlockType> val = std::nullopt;
};

typedef std::vector<std::vector<GridItem>> GridShape;

std::ostream &operator<<(std::ostream &os, GridItem g);

#endif