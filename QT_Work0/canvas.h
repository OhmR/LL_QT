#ifndef CANVAS_H
#define CANVAS_H

#include <baseblock.h>
#include <QList>
#include <QOpenGLWidget>

class canvas : public QOpenGLWidget {
 public:
  canvas(int x, int y);
  /*!
   * the canvas state .
   * \dotfile  canvasFSMGraph.dot "canvas state graph"
   *
   */
  enum canvasStatus {
    idle = 1,
    pre_select,
    multiple_select,
    after_select,
    single_focus,
    multiple_focus
  };

 private:
  int space;     //网格点间距像素点
  int blocknum;  //功能块个数
  int length;
  int wid;
  //  BaseBlock *curblock;  //指向当前块

  //  BaseBlock *block[100];  //存储已经创立的块
  QList<BaseBlock> mBlocks;

  void addBlock(BaseBlock *a);
  void deleteBlock();

  //    int findBlock(QOpenGLWidget *a);         //查找curblock在数组中的下标
  void paintEvent(QPaintEvent *event);  // override;
  //    void keyPressEvent(QKeyEvent *e);
  //    void mousePressEvent(QMouseEvent *e);
  //    void mouseMoveEvent(QMouseEvent *e);
  //    void mouseReleaseEvent(QMouseEvent *e);
};

#endif  // CANVAS_H
