#include "level.h"
#include <iostream>
#include <fstream>

Level::Level() : cur_(0), random_(true) {}

void Level::readFile(std::string f) {
  filename_ = f;
  char blk;

  std::ifstream blklist(filename_);
  if (blklist.is_open()) {
    while (!blklist.eof()) {
      blklist >> blk;
      blocks_.push_back(charToBlockType[blk]);
    }
  }
  blklist.close();
  blocks_.pop_back();
}

void Level::setRandom(bool r) {
  random_ = r;
}
