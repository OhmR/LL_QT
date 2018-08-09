#include "canvas.h"
#include <QPainter>
#include <QPalette>
#include <QtGui>
#include <stdio.h>

canvas::canvas(int x, int y)
{
    length = y;
    width = x;
    space = 10;
    blocknum = 0;
    this->resize(length, width);

    QPalette pal(this->palette());      //设置背景色为白色
    pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

void canvas::addBlock(BaseBlock *a){
    block[blocknum] = a;
    blocknum++;
}

void canvas::deleteBlock(){     //当前这么写，并未真正删除。
    if(curblock != NULL){
//        int temp = this->findBlock(curblock);
//        for(int i = temp; i < blocknum; i++){
//            block[i] = block[i + 1];
//        }
        blocknum--;
    }
}

void canvas::paintEvent(QPaintEvent *event){
    QPainter p;
    p.begin(this);
    p.setPen(Qt::black);
    p.setBrush(Qt::NoBrush);
    p.setRenderHint(QPainter::Antialiasing);
printf("%d\n", this->size().rheight());
printf("124");
//    for(int x = 0; x < this->size().rheight(); x += space){     //绘制背景点
//        for(int y = 0; y < this->size().rwidth(); y += space){
    for(int x = 0; x < 20; x += space){     //绘制背景点
        for(int y = 0; y < 10; y += space){
            p.drawPoint(x, y);
        }
    }

    p.end();
}

