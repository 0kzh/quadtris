#include "levelOne.h"

LevelOne::LevelOne() {}

/**
  choose a random index number from an array holding numbers corresponding to
  block types, chosen with equal probability. There are 1/12 S and Z blocks,
  2/12 of all the other blocks.
  returns a block with skewed probability 1/12 for S,Z, 1/6 for rest 
*/
Block LevelOne::makeBlock() {
  int probs[12] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 5, 6, 6};
  int r = rand() % (sizeof(probs) / sizeof(probs[0]));

  return Block{static_cast<BlockType>(probs[r]), false};
}
