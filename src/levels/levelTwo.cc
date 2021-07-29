#include "levelTwo.h"

LevelTwo::LevelTwo() {
    levelNum_ = 2;
}

char LevelTwo::returnBlock() {
    // random number from [0,6], order is I J L O S Z T
    int r = round(rand() / RAND_MAX * 6);
    return blockChars_[r];    
}

bool LevelTwo::isHeavy() {
    return false;
}
