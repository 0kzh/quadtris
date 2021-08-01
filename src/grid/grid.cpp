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

  initializeGrid();
}

void Grid::initializeGrid() {
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

void Grid::restart() {
  initializeGrid();
  fallingBlock_ = nullopt;
  nextBlock_ = nullopt;

  blockIdToCount.clear();
  blockIdToCreatedAtLvl.clear();
}

std::optional<Block> &Grid::fallingBlock() {
  return fallingBlock_;
}

std::optional<Block> &Grid::nextBlock() {
  return nextBlock_;
}

void Grid::setNextBlocks(const optional<Block> &b) {
  fallingBlock_ = nextBlock_;
  nextBlock_ = b;
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
          if (blockIdToCount[*block.blockId] == 0) {
            // bonus points
            scoredPoints += (int) pow(blockIdToCreatedAtLvl[*block.blockId] + 1, 2);

            blockIdToCount.erase(blockIdToCount.find(*block.blockId));
            blockIdToCreatedAtLvl.erase(blockIdToCreatedAtLvl.find(*block.blockId));
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

bool Grid::isGameOver() const {
  if (fallingBlock_) {
    Block b = *fallingBlock_;
    for (int r = 0; r < b.height(); r++) {
      for (int c = 0; c < b.width(); c++) {
        int gridRow = b.bottomLeft().y - (b.height() - 1) + r;
        int gridCol = b.bottomLeft().x + c;

        if (b.shape()[r][c].val) {
          if (grid_[gridRow][gridCol].val) {
            return true;
          }
        }
      }
    }
  }
  return false;
}
