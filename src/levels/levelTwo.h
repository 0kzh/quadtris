#ifndef LEVEL_TWO_H_
#define LEVEL_TWO_H_

#include "level.h"

/*
 * Implements abstract base class Level's
 * pure virtual functions to model specific
 * behaviour
 */
class LevelTwo : public Level {
    public:
        LevelTwo();
        Block makeBlock() override;
};

#endif
