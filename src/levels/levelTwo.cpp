#include "levelTwo.h"

LevelTwo::LevelTwo() {}

/**
  choose a random index number from a range corresponding to
  block types, chosen with equal probability.
  returns a block with all equal probability.
*/
Block LevelTwo::makeBlock() {
  return Block{static_cast<BlockType>(rand() % (NUM_BLOCK_TYPES - 1)), false};
}
