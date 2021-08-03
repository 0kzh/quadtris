#ifndef LEVEL_ONE_H
#define LEVEL_ONE_H

#include "level.h"


/*
 * Implements abstract base class Level's
 * pure virtual functions to model specific
 * behaviour
 */
class LevelOne : public Level {
public:
  LevelOne();
  Block makeBlock() override;
};


#endif
