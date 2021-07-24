#include "grid.h"
#include "../util/types.h"
#include <optional>
#include <vector>

using namespace std;

Grid::Grid(int height, int width) {
  height_ = height;
  width_ = width;

  // initialize the grid with empty blocks
  grid_.clear();
  for (int row = 0; row < height_; row++) {
    vector<GridItem> curRow;
    curRow.reserve(width_);
    for (int col = 0; col < width_; col++) {
      curRow.push_back(GridItem{nullopt});
    }
    grid_.push_back(curRow);
  }
}

int Grid::height() const { return height_; }

int Grid::width() const { return width_; }

GridShape &Grid::grid() { return grid_; }

std::optional<Block> &Grid::fallingBlock() {
  return fallingBlock_;
}

void Grid::setFallingBlock(const optional<Block> &b) {
  fallingBlock_ = b;
}
