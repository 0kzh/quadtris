#ifndef TYPES_H_
#define TYPES_H_

#include <iostream>
#include <optional>

enum BlockType { I, J, O, S, Z, T };

enum Direction { LEFT, RIGHT, DOWN };

enum RotationDirection { CW, CCW };

struct GridItem {
  std::optional<BlockType> val = std::nullopt;
};

std::ostream &operator<<(std::ostream &os, const GridItem g);

#endif