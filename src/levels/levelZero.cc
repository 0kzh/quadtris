#include "levelZero.h"
#include <iostream>
#include <fstream>

LevelZero::LevelZero(std::string blkfile) {
  filename_ = blkfile;
  cur_ = 0;
  char blk;

  ifstream blklist (filename_);
  if (blklist.is_open()) {
    while (!blklist.eof()) {
        blklist >> blk;
        blocks_.push_back(blk);
    }
  }
  blklist.close();
 }

Block LevelZero::makeBlock() {
  cur_ = (cur_ + 1) % blocks_.size();
  return Block{static_cast<BlockType>blocks_[cur_-1], false, 0};
}
