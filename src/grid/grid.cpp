#include "grid.h"
#include "../util/types.h"
#include "../game.h"
#include <optional>
#include <vector>
#include <cmath>

using namespace std;

map<int, int> Grid::blockIdToCount;
map<int, int> Grid::blockIdToCreatedAtLvl;

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
  int scoredPoints = 0;
  int linesCleared = 0;

  for (int row = 0; row < grid_.size(); row++) {
    auto &gridRow = grid_.at(row);
    bool isFilled = std::all_of(gridRow.begin(), gridRow.end(), [](GridItem item) { return !!item.val; });


    if (isFilled) {
      for (auto &block : gridRow) {
        if (block.blockId) {
          blockIdToCount[*block.blockId]--;
          cout << *block.blockId << ": " << blockIdToCount[*block.blockId] << endl;
          if (blockIdToCount[*block.blockId] == 0) {
            // bonus points
            scoredPoints += (int) pow(blockIdToCreatedAtLvl[*block.blockId] + 1, 2);
            blockIdToCount.erase(blockIdToCount.find(*block.blockId));
            blockIdToCreatedAtLvl.erase(blockIdToCount.find(*block.blockId));
          }
        }
      }
      linesCleared++;
      grid_.erase(grid_.begin() + row);
    }
  }

  // for each of the lines, remove from bottom and add a new row to top
  for (int i = 0; i < linesCleared; i++) {
    vector<GridItem> blankRow(width_, GridItem{nullopt});
    grid_.insert(grid_.begin(), blankRow);
  }

  // calculate score based on scored points
  if (linesCleared == 0) {
    return 0;
  }

  return (int) pow((Game::curLevelIdx_ + 1) + linesCleared, 2);
}
