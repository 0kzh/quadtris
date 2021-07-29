#ifndef LEVEL_FOUR_H_
#define LEVEL_FOUR_H_

#include "level.h"

class LevelFour : public Level {
    public:
        LevelFour();
        char returnBlock();
        bool isHeavy();
};

#endif
