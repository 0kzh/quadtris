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

std::optional<Block> &Grid::hintBlock() {
  return hintBlock_;
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

  // might screw up hint so recalculate it
  if (hintBlock_) {
    setHintBlock();
  }

  return (int) pow(Game::curLevelIdx_ + linesCleared, 2);
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

// from https://codemyroad.wordpress.com/2013/04/14/tetris-ai-the-near-perfect-player/
double Grid::gridScore() const {
  double heightWeight = -0.510066;
  double linesWeight = 0.760666;
  double holesWeight = -0.35663;
  double bumpinessWeight = -0.184483;

  return heightWeight * aggregateHeight() + linesWeight * completeLines() + holesWeight * numHoles() +
         bumpinessWeight * bumpiness();
}

int Grid::colHeight(int col) const {
  int row = 0;
  for (; row < height_ && !grid_[row][col].val; row++);
  return height_ - row;
}

int Grid::aggregateHeight() const {
  int total = 0;
  for (int c = 0; c < width_; c++) {
    total += colHeight(c);
  }
  return total;
}

int Grid::completeLines() const {
  int total = 0;
  for (auto &row : grid_) {
    bool isFilled = std::all_of(row.begin(), row.end(), [](GridItem item) { return !!item.val; });
    if (isFilled) {
      total++;
    }
  }
  return total;
}

int Grid::bumpiness() const {
  int total = 0;
  for (int c = 0; c < width_ - 1; c++) {
    total += abs(colHeight(c) - colHeight(c + 1));
  }
  return total;
}

int Grid::numHoles() const {
  int holes = 0;
  for (int col = 0; col < width_; col++) {
    bool foundBlock = false;
    for (int row = 0; row < height_; row++) {
      if (grid_[row][col].val) {
        foundBlock = true;
      } else if (foundBlock) {
        holes++;
      }
    }
  }
  return holes;
}

void Grid::setHintBlock() {
  if (!fallingBlock_) {
    return;
  }

  Block origHint = Block{fallingBlock_->type(), false};
  Block curHint = origHint;
  pair<double, Block> bestHint = make_pair(INT_MIN, origHint); // deep copy
  GridShape original = grid_; // deep copy

  // go through all positions and rotations
  for (int x = 0; x < width_; x++) {
    for (int i = 0; i < 4; i++) {
      curHint = origHint;
      // move to x position
      for (int _ = 0; _ < x; _++) {
        curHint.move(RIGHT, grid_);
      }

      // rotate to orientation
      for (int _ = 0; _ < i; _++) {
        curHint.rotate(CW, grid_);
      }

      curHint.drop(grid_);

      // lower score is better
      double score = gridScore();
      if (score > bestHint.first) {
        bestHint.first = score;
        bestHint.second = curHint;
      }

      grid_ = original;
    }
  }

  hintBlock_ = bestHint.second;
}