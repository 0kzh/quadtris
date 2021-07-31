#include "levelZero.h"

#include <iostream>
#include <fstream>

using namespace std;

LevelZero::LevelZero(std::string blkfile) {
  filename_ = blkfile;
  cur_ = 0;
  char blk;

  ifstream blklist(filename_);
  if (blklist.is_open()) {
    while (!blklist.eof()) {
      blklist >> blk;
      blocks_.push_back(charToBlockType[blk]);
    }
  }
  blklist.close();
}

Block LevelZero::makeBlock() {
  Block b = Block{blocks_[cur_], false, 0};
  cur_ = (cur_ + 1) % blocks_.size();
  return b;
}
