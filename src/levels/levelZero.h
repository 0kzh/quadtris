#ifndef LEVEL_ZERO_H
#define LEVEL_ZERO_H

#include "level.h"
#include <string>
#include <vector>

class LevelZero : public Level {
public:
  explicit LevelZero(std::string);
  Block makeBlock() override;
};


#endif
