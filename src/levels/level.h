#ifndef LEVEL_H_
#define LEVEL_H_

#include <stdlib.h>
#include <math.h>
#include <string>

class Level {
    protected:
        std::string blockChars_;
        Level();
    public:
        int levelNum_;
        virtual char returnBlock() = 0;
        virtual bool isHeavy() = 0;
};

#endif
