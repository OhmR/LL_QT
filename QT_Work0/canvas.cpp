#include "canvas.h"
#include <QPainter>
#include <QPalette>
#include <QtGui>
#include <QDebug>
#include <blockparser.h>

canvas::canvas(int x, int y)
{
    length = y;
    wid = x;
    space = 10;
    blocknum = 0;
    this->resize(length, wid);

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

//if you don't need to use callback parameters, explictly declare that.
void canvas::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter p;
    p.begin(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QBrush(QColor("green")));
    p.setRenderHint(QPainter::Antialiasing);

    //dont use printf, use qdebug
    qDebug()<<this->size().rheight();
    qDebug()<<"124";

    for(int x = 0; x < this->width(); x += space){     //绘制背景点
        for(int y = 0; y < this->height(); y += space){
            //We need  VISIBLE points, not one pixel! So, please use draw drawEllipse instead of drawPoint~
            p.drawEllipse(QPoint(x,y),1,1);
        }
    }

    //draw the block with information in json
    BlockParser par("/home/ohmr/test.json");
    qDebug()<<par.getBlockName();
    par.getBlockInput();
    par.getBlockOutput();

    BaseBlock block(par.ReturnInId(),
                    par.ReturnInDes(),
                    par.ReturnOutId(),
                    par.ReturnOutDes(),
                    par.getBlockName());

    p.end();
}

