#ifndef LEVEL_H
#define LEVEL_H

#include "../block/block.h"
#include <string>

class Level {
private:
  int cur_;
  std::string filename_;
  std::vector<BlockType> blocks_;
  bool random_;
public:
  virtual Block makeBlock() = 0;
  virtual ~Level() = default;
  Level();
  void setRandom(bool r);
  void readFile(std::string f);
};

#endif
