#include "../util/types.h"
#include "block.h"

using namespace std;

Block::Block(BlockType type, bool isHeavy) : isHeavy_(isHeavy), type_(type) {
  shape_ = blockTypeToData[type];
  height_ = shape_.size();
  width_ = shape_[0].size();

  bottomLeft_ = Point{.x = 0, .y = height_};
}

bool Block::move(Direction d) {
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

std::vector<std::vector<GridItem>> Block::shape() const {
  return shape_;
}
