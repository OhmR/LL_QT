#ifndef CANVAS_H
#define CANVAS_H

#include <QOpenGLWidget>
#include <baseblock.h>

class canvas : public QOpenGLWidget
{
public:
    canvas(int x, int y);

private:
    int space;                              //网格点间距像素点
    int blocknum;                           //功能块个数
    int length;
    int width;
    BaseBlock *curblock;                //指向当前块
    BaseBlock *block[100];              //存储已经创立的块
    void addBlock(BaseBlock *a);
    void deleteBlock();
//    int findBlock(QOpenGLWidget *a);         //查找curblock在数组中的下标
    void paintEvent(QPaintEvent *event);    //override;
//    void keyPressEvent(QKeyEvent *e);
//    void mousePressEvent(QMouseEvent *e);
//    void mouseMoveEvent(QMouseEvent *e);
//    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // CANVAS_H
