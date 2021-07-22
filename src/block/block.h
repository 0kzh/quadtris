#ifndef BLOCK_H
#define BLOCK_H

#include "../util/types.h"
#include <memory>
#include <vector>

class Block {
  bool isHeavy_;
  std::vector<std::vector<GridItem>> shape_;

  int height_;
  int width_;

public:
  Block(BlockType type, bool isHeavy);
  bool move(Direction d);
  void drop();
  bool rotate(RotationDirection d);
}

#endif
