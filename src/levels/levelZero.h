#ifndef LEVEL_ZERO_H_
#define LEVEL_ZERO_H_

#include "level.h"

class LevelZero : public Level {
    private:
        std::string filename_;
    public:
        LevelZero(std::string);
        Block makeBlock() override;
};

#endif
