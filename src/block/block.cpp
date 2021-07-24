#include "../util/types.h"
#include "block.h"
#include <functional>

using namespace std;

Block::Block(BlockType type, bool isHeavy) : isHeavy_(isHeavy), type_(type) {
  shape_ = blockTypeToData[type];
  height_ = shape_.size();
  width_ = shape_[0].size();

  bottomLeft_ = Point{.x = 0, .y = 2 + height_};
}

bool Block::move(Direction d, const GridShape &g) {
  int gridHeight = g.size();
  int gridWidth = g[0].size();

  auto inside = [&](int x, int y) {
    return (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight);
  };

  switch (d) {
    case LEFT:
      if (inside(bottomLeft_.x - 1, bottomLeft_.y)) {
        bottomLeft_.x--;
        return true;
      }
      break;
    case RIGHT:
      if (inside(bottomLeft_.x + width_, bottomLeft_.y)) {
        bottomLeft_.x++;
        return true;
      }
      break;
    case DOWN:
      cout << bottomLeft_.y << ", " << gridHeight;
      if (inside(bottomLeft_.x, bottomLeft_.y + 1)) {
        bottomLeft_.y++;
        return true;
      }
      break;
  }
  return false;
}

void Block::drop() {

}

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

      shape_ = rotated;

      swap(height_, width_);
      break;
    }
  }
  return false;
}

int Block::height() const {
  return height_;
}

int Block::width() const {
  return width_;
}

Point Block::bottomLeft() const {
  return bottomLeft_;
}

BlockType Block::type() const {
  return type_;
}

GridShape Block::shape() const {
  return shape_;
}
