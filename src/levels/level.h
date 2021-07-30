#ifndef LEVEL_H
#define LEVEL_H

#include "../block/block.h"
#include <stdlib.h>
#include <math.h>
#include <string>

class Level {
public:
  virtual Block makeBlock() = 0;

  virtual ~Level() = default;
};

#endif
