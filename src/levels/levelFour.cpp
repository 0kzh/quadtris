#include "levelFour.h"

LevelFour::LevelFour() {}

/**
    int r = rand();  // gives you a number from 0 to RAND_MAX
    double d = r / RAND_MAX;  // gives you a number from 0 to 1
    double val = d * 5; // gives you a number from 0 to 5
*/
Block LevelFour::makeBlock() {
	if(random_) {
		int probs[18] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6};
		int r = rand() % (sizeof(probs) / sizeof(probs[0]));
		return Block{static_cast<BlockType>(probs[r]), true, 4};
	} else {
		Block b = Block{blocks_[cur_], true, 4};
  		cur_ = (cur_ + 1) % blocks_.size();
  		return b;
	}
}
