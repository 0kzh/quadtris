#ifndef LEVEL_ONE_H_
#define LEVEL_ONE_H_

#include "level.h"

class LevelOne : public Level {
    private:
        std::string filename_;
    public:
        LevelOne(std::string);
        char returnBlock();
        bool isHeavy();
};

#endif
