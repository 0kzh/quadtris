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

int Grid::clearLines() {
  int linesCleared = 0;
  for (int row = height_ - 1; row > 0; row--) {
    auto &gridRow = grid_.at(row);
    bool isFilled = std::all_of(gridRow.begin(), gridRow.end(), [](GridItem item) { return !!item.val; });

    if (isFilled) {
      linesCleared++;
    }
  }

  // for each of the lines, remove from bottom and add a new row to top
  for (int i = 0; i < linesCleared; i++) {
    grid_.pop_back();
    vector<GridItem> blankRow(width_, GridItem{nullopt});
    grid_.insert(grid_.begin(), blankRow);
  }

  return linesCleared;
}
