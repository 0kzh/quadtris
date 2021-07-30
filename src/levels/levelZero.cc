#include "levelZero.h"
#include <string>

LevelOne::LevelOne(std::string s) {
    filename_ = s;
    levelNum_ = 1;
}

char LevelOne::returnBlock() {
    // read file
}

bool LevelOne::isHeavy() {
    return false;
}
