#include "levelThree.h"

LevelThree::LevelThree() { }

Block LevelTwo::makeBlock() {
  int probs[17] = {0,0,1,1,2,2,3,3,4,4,4,4,5,5,5,5,6,6};
  int r = round(rand() / RAND_MAX * 17);

  return Block{static_cast<BlockType>(probs[r]), true};
}
