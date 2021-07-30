#include "levelOne.h"

LevelOne::LevelOne() {}

Block LevelOne::makeBlock() {
  return Block{static_cast<BlockType>(rand() % NUM_BLOCK_TYPES - 1), false};
}