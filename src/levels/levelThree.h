#ifndef LEVEL_THREE_H_
#define LEVEL_THREE_H_

#include "level.h"

class LevelThree : public Level {
    public:
        LevelThree();
        char returnBlock();
        bool isHeavy();
};

#endif
