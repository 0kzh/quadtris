#ifndef LEVEL_FOUR_H_
#define LEVEL_FOUR_H_

#include "level.h"

class LevelFour : public Level {
    public:
        LevelFour();
        Block makeBlock() override;
        void setRandom(bool r);
};

#endif
