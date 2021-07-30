#ifndef LEVEL_ONE_H
#define LEVEL_ONE_H

#include "level.h"

class LevelOne : public Level {
public:
  LevelOne();

  Block makeBlock() override;
};


#endif
