#ifndef LEVEL_H_
#define LEVEL_H_

class Level {
    protected:
        Level();
    public:
        int levelNum_;
        virtual char returnBlock() = 0;
        virtual bool isHeavy() = 0;
};

#endif
