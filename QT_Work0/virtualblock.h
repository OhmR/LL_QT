#ifndef VIRTUALBLOCK_H
#define VIRTUALBLOCK_H

class VirtualBlock{
public:
// You need pure virtual not virtual function in this class.

    virtual int ReturnX() = 0 ;
    virtual int ReturnY()= 0;
    virtual int ReturnSize()= 0;
    virtual int ReturnShape()= 0;
    virtual int ReturnIn() = 0 ;
    virtual int ReturnOut()  =0 ;


//Pure Abstract base class does not need private members.
//Since you can not instantiate VirtualBlock, you can not access these private members.
//So i just comment them.


//piivate:
//    int x;
//    int y;
//    int size;
//    int shape;  //列不同数值存储不同形状
//    int input;  //输入接口数
//    int output; //输出接口数
};


#endif // VIRTUALBLOCK_H
