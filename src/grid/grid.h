#ifndef GRID_H
#define GRID_H

#include "../util/types.h"
#include <optional>
#include <vector>

class Grid {
  int height_;
  int width_;

  std::vector<std::vector<GridItem>> grid_;

public:
  Grid(int height, int width);
  void draw();

  int height() const;
  int width() const;
  const std::vector<std::vector<GridItem>> &grid() const;
};

#endif