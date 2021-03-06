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
  std::optional<Block> nextBlock_;
  std::optional<Block> hintBlock_;

  GridShape grid_;

public:
  static std::map<int, int> blockIdToCount;
  static std::map<int, int> blockIdToCreatedAtLvl;

  Grid(int height, int width);

  int height() const;

  int width() const;

  GridShape &grid();

  std::optional<Block> &fallingBlock();

  std::optional<Block> &nextBlock();

  std::optional<Block> &hintBlock();

  void setNextBlocks(const std::optional<Block> &);

  // game is over if the fallingBlock collides with the grid
  bool isGameOver() const;

  void restart();

  // clears lines at bottom of grid. returns number of lines cleared.
  int clearLines();

  void setHintBlock();

private:
  void initializeGrid();

  double gridScore() const;

  int numHoles() const;

  int aggregateHeight() const;

  int completeLines() const;

  int bumpiness() const;

  int colHeight(int col) const;

  static int numIslands(std::vector<GridItem> &r);
};

#endif