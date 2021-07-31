#ifndef LEVEL_ZERO_H
#define LEVEL_ZERO_H

#include "level.h"
#include <vector>

class LevelZero : public Level {
  private:
    int cur_;
    std::vector<char> blocks_;
  public:
    LevelZero();
    Block makeBlock() override;
};

#endif
