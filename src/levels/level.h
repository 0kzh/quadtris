#ifndef LEVEL_H
#define LEVEL_H

#include "../block/block.h"
#include <string>

/**
Implements template design pattern for 5 level child classes
all functions but setRandom(bool) and readFile(std::string) have variable behaviour in subclasses. 
Therefore setRandom(bool) and readFile(std::string) is the template method 
and other functions are declared as pure virtual
*/
class Level {
private:
  std::string filename_;
public:
  Level();
  virtual Block makeBlock() = 0;
  virtual ~Level() = default;
  void setRandom(bool r);
  void readFile(std::string f);
  int blocksPlaced_;
protected:
  int cur_;
  bool random_;
  std::vector<BlockType> blocks_;
};

#endif
