#ifndef LEVELONE_H
#define LEVELONE_H

#include "level.h"

class LevelOne : public Level {
public:
  LevelOne();

  Block makeBlock() override;
};


#endif
