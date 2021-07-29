#ifndef LEVEL_TWO_H_
#define LEVEL_TWO_H_

#include "level.h"

class LevelTwo : public Level {
    public:
        LevelTwo();
        char returnBlock();
        bool isHeavy();
};

#endif
