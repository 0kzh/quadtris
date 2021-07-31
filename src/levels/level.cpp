#include "level.h"
#include <iostream>
#include <fstream>

Level::Level() {
	cur_ = 0;
	random_ = true;
}

void Level::readFile(std::string f) {
  filename_ = f;
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

void setRandom(bool r) {
	random_ = r;
}