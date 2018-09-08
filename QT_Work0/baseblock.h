#ifndef BASEBLOCK_H
#define BASEBLOCK_H

#include "./virtualblock.h"
#include <QStringList>
#include <QDebug>

class BaseBlock : public VirtualBlock{
public:
    BaseBlock(QStringList InputId,
              QStringList InputDes,
              QStringList OutputId,
              QStringList OutputDes,
              QString BlockName);
    int ReturnX() override;
    int ReturnY() override;
    int ReturnSize() override;
    int ReturnShape() override;
    int ReturnIn() override;
    int ReturnOut() override;
    QString ReturnBlockName();
    QString InId(int index);
    QString OutId(int index);
    QString InDes(int index);
    QString OutDes(int index);
    ~BaseBlock(){}

private:
    int x;
    int y;
    int size;
    int shape;  //列不同数值存储不同形状
    int input;  //输入接口数
    int output; //输出接口数
    QStringList InputId;
    QStringList InputDes;
    QStringList OutputId;
    QStringList OutputDes;
    QString BlockName;
};

#endif // BASEBLOCK_H
