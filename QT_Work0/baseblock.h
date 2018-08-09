#ifndef BASEBLOCK_H
#define BASEBLOCK_H

#include <virtualblock.h>

class BaseBlock : public VirtualBlock{
public:
    BaseBlock();
    int ReturnX();
    int ReturnY();
    int ReturnSize();
    int ReturnShape();
    int ReturnIn();
    int ReturnOut();

private:
    int x;
    int y;
    int size;
    int shape;  //列不同数值存储不同形状
    int input;  //输入接口数
    int output; //输出接口数
};

#endif // BASEBLOCK_H
