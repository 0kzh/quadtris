#include "../util/types.h"
#include "../util/helper.h"
#include "../grid/grid.h"
#include "../game.h"
#include "block.h"
#include <functional>

using namespace std;

// Block constructor
Block::Block(BlockType type, bool isHeavy) : isHeavy_(isHeavy), type_(type) {
  shape_ = blockTypeToData[type];

  // generate unique ID and assign to each block
  // this helps track when this block is destroyed for bonus scoring
  int blockId = Helper::generateUniqueId();
  for (auto &r : shape_) {
    for (auto &block : r) {
      if (block.val) {
        block.blockId = blockId;
        Grid::blockIdToCount[blockId]++;
      }
    }
  }
  Grid::blockIdToCreatedAtLvl[blockId] = Game::curLevelIdx_;

  height_ = shape_.size();
  width_ = shape_[0].size();
  blockId_ = blockId;

  bottomLeft_ = Point{.x = 0, .y = 2 + height_};
}

// moves the block and returns a bool indicating if we should remove the block
bool Block::move(Direction d, GridShape &g) {
  switch (d) {
    case LEFT:
      if (!intersects(Point{.x =  bottomLeft_.x - 1, .y = bottomLeft_.y}, g)) {
        bottomLeft_.x--;
      }
      break;
    case RIGHT: {
      if (!intersects(Point{.x = bottomLeft_.x + 1, .y = bottomLeft_.y}, g)) {
        bottomLeft_.x++;
      }
      break;
    }
    case DOWN:
      if (!intersects(Point{.x = bottomLeft_.x, .y = bottomLeft_.y + 1}, g)) {
        bottomLeft_.y++;
      } else {
        copyToGrid(g);
        return true;
      }
      break;
  }
  return false;
}

// drops the block until we've reached the bottom of a grid or intersect another block
void Block::drop(GridShape &g) {
  Point newBottomLeft = bottomLeft_;

  // go down until it collides
  do {
    newBottomLeft.y += 1;
  } while (!intersects(newBottomLeft, g));

  // move back to last valid position
  newBottomLeft.y -= 1;

  bottomLeft_ = newBottomLeft;

  copyToGrid(g);
}

// checks if the block intersects with any of the grid blocks
bool Block::intersects(const Point &p, const GridShape &g) {
  return intersects(p, g, shape_);
}

// checks if the block intersects with any of the grid edges
bool Block::intersects(const Point &p, const GridShape &g, const GridShape &blockShape) {
  int x = p.x;
  int y = p.y;
  int gridHeight = g.size();
  int gridWidth = g[0].size();

  int shapeHeight = blockShape.size();
  int shapeWidth = blockShape[0].size();

  for (int r = 0; r < shapeHeight; r++) {
    for (int c = 0; c < shapeWidth; c++) {
      int gridRow = y - (shapeHeight - 1) + r;
      int gridCol = x + c;

      bool inBounds = (gridCol >= 0 && gridCol < gridWidth && gridRow >= 0 && gridRow < gridHeight);
      if (!inBounds) {
        return true;
      }

      if (blockShape[r][c].val) {
        GridItem itemAtPos = g[gridRow][gridCol];
        if (itemAtPos.val) {
          return true;
        }
      }
    }
  }

  return false;
}

// puts the given GridShape onto the grid
void Block::copyToGrid(GridShape &g) {
  int y = bottomLeft_.y;
  int x = bottomLeft_.x;

  for (int r = 0; r < height_; r++) {
    for (int c = 0; c < width_; c++) {
      int gridRow = y - (height_ - 1) + r;
      int gridCol = x + c;

      if (shape_[r][c].val) {
        g[gridRow][gridCol] = GridItem{*shape_[r][c].val, *shape_[r][c].blockId};
      }
    }
  }
}

// rotates the block and returns a bool indicating if we should remove the block
bool Block::rotate(RotationDirection d, const GridShape &g) {
  int gridHeight = g.size();
  int gridWidth = g[0].size();

  switch (d) {
    case CW: {
      GridShape rotated(width_, std::vector<GridItem>(height_, GridItem{nullopt}));

      for (int r = 0; r < height_; r++) {
        for (int c = 0; c < width_; c++) {
          rotated[c][height_ - 1 - r] = shape_[r][c];
        }
      }

      // if rotation is oob, don't do anything
      if (intersects(bottomLeft_, g, rotated)) {
        return false;
      }

      shape_ = rotated;

      swap(height_, width_);
      break;
    }
    case CCW: {
      GridShape rotated(width_, std::vector<GridItem>(height_, GridItem{nullopt}));

      for (int r = 0; r < height_; r++) {
        for (int c = 0; c < width_; c++) {
          rotated[width_ - 1 - c][r] = shape_[r][c];
        }
      }

      // if rotation is oob, don't do anything
      if (intersects(bottomLeft_, g, rotated)) {
        return false;
      }

      shape_ = rotated;

      swap(height_, width_);
      break;
    }
  }

  return false;
}

// height accessor returns an int representing height
int Block::height() const {
  return height_;
}

// width accessor returns an int representing width
int Block::width() const {
  return width_;
}

// bottomLeft location accessor returns a Point representing the bottom left
Point Block::bottomLeft() const {
  return bottomLeft_;
}

// type accessor returns a BlockType representing type of block
BlockType Block::type() const {
  return type_;
}

// setter function that sets the block's type
void Block::setType(BlockType type) {
  shape_ = blockTypeToData[type];
  type_ = type;
  Grid::blockIdToCount.erase(Grid::blockIdToCount.find(blockId_));

  for (auto &r : shape_) {
    for (auto &block : r) {
      if (block.val) {
        block.blockId = blockId_;
        Grid::blockIdToCount[blockId_]++;
      }
    }
  }

  height_ = shape_.size();
  width_ = shape_[0].size();
}

// accessor that returns a GridShape representing the block's shape
GridShape Block::shape() const {
  return shape_;
}

// accessor that returns a boolean representing whether the block is heavy or not
bool Block::heavy() const {
  return isHeavy_;
}
