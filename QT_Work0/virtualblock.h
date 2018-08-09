#ifndef VIRTUALBLOCK_H
#define VIRTUALBLOCK_H

class VirtualBlock{
public:
    virtual int ReturnX();
    virtual int ReturnY();
    virtual int ReturnSize();
    virtual int ReturnShape();
    virtual int ReturnIn();
    virtual int ReturnOut();

private:
    int x;
    int y;
    int size;
    int shape;  //列不同数值存储不同形状
    int input;  //输入接口数
    int output; //输出接口数
};

#endif // VIRTUALBLOCK_H
