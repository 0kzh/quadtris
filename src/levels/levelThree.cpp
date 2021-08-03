#include "levelThree.h"

LevelThree::LevelThree() {}

/**
  if we want random block generation,
  choose a random index number from an array holding numbers corresponding to
  block types, chosen with equal probability. There are 4/18 S and Z blocks,
  2/18 of all the other blocks.      
  Otherwise, return the currect block in the sequence file.                              
  returns a block with skewed probability 2/9 for S,Z, 1/9 for rest or a block from a provided file
*/
Block LevelThree::makeBlock() {
  if (random_) {
    int probs[18] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6};
    int r = rand() % (sizeof(probs) / sizeof(probs[0]));

    return Block{static_cast<BlockType>(probs[r]), true};
  } else {
    Block b = Block{blocks_[cur_], true};
    cur_ = (cur_ + 1) % blocks_.size();
    return b;
  }
}
