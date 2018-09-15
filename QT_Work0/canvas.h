#ifndef CANVAS_H
#define CANVAS_H

#include <baseblock.h>
#include <singleparser.h>
#include <QLabel>
#include <QList>
#include <QOpenGLWidget>
#include <QPushButton>
#include <QToolBar>
#include <QVBoxLayout>

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
    predraw_newblock,
    draw_newblock,
    pre_select,
    multiple_select,
    after_select,
    single_focus,
    multiple_focus
  };

 public slots:
  void GetBlockI2C_RS485();

 private:
  int space;     //网格点间距像素点
  int blocknum;  //功能块个数
  int length;
  int wid;
  int status;
  QPoint mousepos;
  QPoint blockpos;

  SingleParser *sParser[10];

  QList<IBlock *> mSelectedBlocks;
  QList<IBlock *> mBlocks;

  // We need Polymophsim here, So use IBlock* not BaseBlock*
  void addBlock(IBlock *a);
  void deleteBlock();
  int max(int a, int b);

  void paintEvent(QPaintEvent *event);  // override;
  void mousePressEvent(QMouseEvent *e);
  void mouseMoveEvent(QMouseEvent *e);
};

#endif  // CANVAS_H
