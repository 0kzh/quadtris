#ifndef GRID_H
#define GRID_H

#include "../util/types.h"
#include "../block/block.h"
#include <optional>
#include <vector>
#include <map>

class Grid {
  int height_;
  int width_;
  std::optional<Block> fallingBlock_;

  GridShape grid_;

public:
  static std::map<int, int> blockIdToCount;
  static std::map<int, int> blockIdToCreatedAtLvl;
  static std::map<int, int> blockIdToScore;

  Grid(int height, int width);

  int height() const;

  int width() const;

  GridShape &grid();

  std::optional<Block> &fallingBlock();

  void setFallingBlock(const std::optional<Block> &);

  // clears lines at bottom of grid. returns number of lines cleared.
  int clearLines();
};

#endif