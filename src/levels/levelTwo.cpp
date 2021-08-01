#include "levelTwo.h"

LevelTwo::LevelTwo() {}

Block LevelTwo::makeBlock() {
  return Block{static_cast<BlockType>(rand() % NUM_BLOCK_TYPES - 1), false};
}
