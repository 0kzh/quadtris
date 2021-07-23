#include "../util/types.h"
#include "block.h"
#include <functional>

using namespace std;

Block::Block(BlockType type, bool isHeavy) : isHeavy_(isHeavy), type_(type) {
  shape_ = blockTypeToData[type];
  height_ = shape_.size();
  width_ = shape_[0].size();

  bottomLeft_ = Point{.x = 0, .y = 3};
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
      if (inside(bottomLeft_.x, bottomLeft_.y + height_)) {
        bottomLeft_.y++;
        return true;
      }
      break;
    default:
      return false;
  }
  return false;
}

void Block::drop() {

}

bool Block::rotate(RotationDirection d) {
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
