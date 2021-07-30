#ifndef LEVEL_THREE_H_
#define LEVEL_THREE_H_

#include "level.h"

class LevelThree : public Level {
    public:
        LevelThree();
        Block makeBlock() override;
};

#endif
