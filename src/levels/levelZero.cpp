#include "levelZero.h"

using namespace std;

LevelZero::LevelZero(std::string blkfile) {
  readFile(blkfile);
}

Block LevelZero::makeBlock() {
  Block b = Block{blocks_[cur_], false, 0};
  cur_ = (cur_ + 1) % blocks_.size();
  return b;
}
