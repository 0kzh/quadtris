#ifndef LEVEL_FOUR_H_
#define LEVEL_FOUR_H_

#include "level.h"

/*
 * Implements abstract base class Level's
 * pure virtual functions to model specific
 * behaviour
 */
class LevelFour : public Level {
    public:
        LevelFour();
        Block makeBlock() override;
};

#endif
