#ifndef LEVEL_THREE_H_
#define LEVEL_THREE_H_

#include "level.h"

/*
 * Implements abstract base class Level's
 * pure virtual functions to model specific
 * behaviour
 */
class LevelThree : public Level {
    public:
        LevelThree();
        Block makeBlock() override;
};

#endif
