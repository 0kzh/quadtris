#ifndef GRID_H
#define GRID_H

#include "../util/types.h"
#include "../block/block.h"
#include <optional>
#include <vector>

class Grid {
  int height_;
  int width_;
  std::optional<Block> fallingBlock_;

  GridShape grid_;

public:
  Grid(int height, int width);

  int height() const;

  int width() const;

  GridShape &grid();

  std::optional<Block> &fallingBlock();

  void setFallingBlock(const std::optional<Block> &);
};

#endif