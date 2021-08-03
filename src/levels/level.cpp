#include "level.h"
#include <iostream>
#include <fstream>

Level::Level() : cur_(0), random_(true), blocksPlaced_(-1) {}

// reads a file containing a sequence of blocks
void Level::readFile(std::string f) {
  filename_ = f;
  char blk;

  std::ifstream blklist(filename_);
  if (blklist.is_open()) {
    while (blklist >> blk) {
      blocks_.push_back(charToBlockType[blk]);
    }
  }
  blklist.close();
}

// setter function
void Level::setRandom(bool r) {
  random_ = r;
}
