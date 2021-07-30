#include "levelOne.h"

LevelOne::LevelOne() {}

/**
    int r = rand();  // gives you a number from 0 to RAND_MAX
    double d = r / RAND_MAX;  // gives you a number from 0 to 1
    double val = d * 5; // gives you a number from 0 to 5
*/
Block LevelOne::makeBlock() {
  int probs[12] = {0,0,1,1,2,2,3,3,4,5,6,6};
  int r = round(rand() / RAND_MAX * 11);

  return Block{static_cast<BlockType>(probs[r]), false, 1};
}
