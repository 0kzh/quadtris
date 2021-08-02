#ifndef LEVEL_H
#define LEVEL_H

#include "../block/block.h"
#include <string>

class Level {
private:
  std::string filename_;
public:
  virtual Block makeBlock() = 0;

  virtual ~Level() = default;

  Level();

  void setRandom(bool r);

  void readFile(std::string f);

  int blocksPlaced_;
protected:
  int cur_;
  bool random_;
  std::vector<BlockType> blocks_;
};

#endif
