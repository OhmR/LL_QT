#include <baseblock.h>

BaseBlock::BaseBlock(QStringList InputId,
                     QStringList InputDes,
                     QStringList OutputId,
                     QStringList OutputDes,
                     QString BlockName){
    this->InputId = InputId;
    this->OutputId = OutputId;
    this->InputDes = InputDes;
    this->OutputDes = OutputDes;
    this->BlockName = BlockName;
    this->input = InputId.size();
    this->output = OutputId.size();
}

int BaseBlock::ReturnX(){
    return x;
}

int BaseBlock::ReturnY(){
    return y;
}

int BaseBlock::ReturnSize(){
    return size;
}

int BaseBlock::ReturnShape(){
    return shape;
}

int BaseBlock::ReturnIn(){
    return input;
}

int BaseBlock::ReturnOut(){
    return output;
}

QString
BaseBlock::InId(int index){     //index from 0 to size-1
    if(index >= InputId.size())
    {
        qDebug()<<"baseblock.cpp : InId error!";
        throw -1;
    }
    return this->InputId.at(index);
}

QString
BaseBlock::InDes(int index){     //index from 0 to size-1
    if(index >= InputDes.size())
    {
        qDebug()<<"baseblock.cpp : InDes error!";
        throw -1;
    }
    return this->InputDes.at(index);
}

QString
BaseBlock::OutId(int index){     //index from 0 to size-1
    if(index >= OutputId.size())
    {
        qDebug()<<"baseblock.cpp : OutId error!";
        throw -1;
    }
    return this->OutputId.at(index);
}

QString
BaseBlock::OutDes(int index){     //index from 0 to size-1
    if(index >= OutputDes.size())
    {
        qDebug()<<"baseblock.cpp : OutDes error!";
        throw -1;
    }
    return this->OutputDes.at(index);
}

QString
BaseBlock::ReturnBlockName(){
    return BlockName;
}
