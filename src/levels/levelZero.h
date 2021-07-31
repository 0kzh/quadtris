#ifndef LEVEL_ZERO_H
#define LEVEL_ZERO_H

#include "level.h"
#include <vector>
#include <string>

class LevelZero : public Level {
  private:
    int cur_;
    std::string filename_;
    std::vector<char> blocks_;
  public:
    LevelZero(std::string);
    Block makeBlock() override;
};

#endif
