#include "canvas.h"
#include <blockparser.h>
#include <QDebug>
#include <QPainter>
#include <QPalette>
#include <QPushButton>
#include <QtGui>
#include "iblock.h"

canvas::canvas(int x, int y) {
  status = idle;

  length = y;
  wid = x;
  space = 10;
  blocknum = 0;
  this->resize(length, wid);

  QPalette pal(this->palette());  //设置背景色为白色
  pal.setColor(QPalette::Background, Qt::white);
  this->setAutoFillBackground(true);
  this->setPalette(pal);

  // Ensure that mouse movement is detected without the mouse being pressed
  this->setMouseTracking(true);
}

void canvas::GetBlockI2C_RS485() {
  sParser[0] = new SingleParser("/home/mocking/test.json");
  BlockParser *par = sParser[0]->request();

  par->getBlockInput();
  par->getBlockOutput();

  BaseBlock *block =
      new BaseBlock(par->ReturnInId(), par->ReturnInDes(), par->ReturnOutId(),
                    par->ReturnOutDes(), par->getBlockName());
  // default selected
  mSelectedBlocks.append(block);
  block->setStatus(IBlock::floating);

  this->addBlock(block);
}

void canvas::mouseMoveEvent(QMouseEvent *e) {
  // TODO
  mousepos = e->pos();
  for (auto &i : mSelectedBlocks)
    if (i->isFloating()) {
      IBlock::position a;
      a.leftTopPoint = e->pos();
      i->setPosition(&a);
    }
  // MouseMove shouldn't trigger the repaint.
  // it must be the status-change which can and only can make the
  // canvas repaint under MVC pattern.
  // may be have any other operations
}

void canvas::mousePressEvent(QMouseEvent *e) {
  if (e->button() & Qt::LeftButton) {
    for (auto &i : mSelectedBlocks) i->setStatus(IBlock::fixed);
    update();
  }
}

int canvas::max(int a, int b) { return a > b ? a : b; }

void canvas::addBlock(IBlock *a) {
  //   not do mBlocks.append at here,
  //   I append the new block when i draw it in paintevent
  //   I think we should do mBlocks.appeend at here
  mBlocks.append(a);
  //  QObject::connect(a, SIGNAL(statusChanged()), this, update());

  QObject::connect(qobject_cast<QObject *>(dynamic_cast<BaseBlock *>(a)),
                   SIGNAL(statusChange()), this, SLOT(update()));
}

void canvas::deleteBlock() {  //当前这么写，并未真正删除。
}

// if you don't need to use callback parameters, explictly declare that.
void canvas::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter p;
  p.begin(this);
  p.setPen(Qt::NoPen);
  p.setBrush(QBrush(QColor("green")));
  p.setRenderHint(QPainter::Antialiasing, true);

  // dont use printf, use qdebug

  for (int x = 0; x < this->width(); x += space) {  //绘制背景点
    for (int y = 0; y < this->height(); y += space) {
      p.drawEllipse(QPoint(x, y), 1, 1);
    }
  }
  for (auto &i : mBlocks) i->paintSelf(&p);

  // draw the waiting to add block

  /*!
   * DO NOT Handle the block status here. Canvas are controller layer of our mvc
   *pattern.
   *Variable mousepos saved some status in the scope of controller, this is
   *kind of anti-pattern.
   *Controller should modify not store the block.
   */
  //  if (status == predraw_newblock) {
  //    blockpos =
  //        QPoint(mousepos.x() / space * space, mousepos.y() / space * space);

  //    p.setPen(QPen(Qt::gray, 2, Qt::DotLine, Qt::RoundCap));
  //    p.setBrush(Qt::white);
  //    p.drawRect(blockpos.x() - 2 * space,
  //               blockpos.y() - max(curblock->input, curblock->output) *
  //               space,
  //               4 * space, max(curblock->input, curblock->output) * 2 *
  //               space);
  //  }

  //  // draw new block
  //  if (status == draw_newblock) {
  //    p.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
  //    p.setBrush(Qt::white);

  //    curblock->mPosition.leftTopPoint =
  //        QPoint(blockpos.x() - 2 * space,
  //               blockpos.y() - max(curblock->input, curblock->output) *
  //               space);
  //    curblock->mPosition.width = 4 * space;
  //    curblock->mPosition.height =
  //        max(curblock->input, curblock->output) * 2 * space;
  //    //    p.drawRect(curblock->mPosition.leftTopPoint.x(),
  //    //               curblock->mPosition.leftTopPoint.y(),
  //    //               curblock->mPosition.width, curblock->mPosition.height);
  //    mBlocks.append(*curblock);
  //  }

  // draw the exit block

  //  for (int i = 0; i < mBlocks.size(); i++) {
  //    p.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
  //    p.setBrush(Qt::white);
  //    p.drawRect(mBlocks[i].mPosition.leftTopPoint.x(),
  //               mBlocks[i].mPosition.leftTopPoint.y(),
  //               mBlocks[i].mPosition.width, mBlocks[i].mPosition.height);

  //    // draw the port in block
  //    p.setPen(QPen(Qt::blue, 2));
  //    QList<QPoint> temp = mBlocks[i].OutPortPos();

  //    for (int j = 0; j < temp.size(); j++) {
  //      p.drawLine(temp[j], QPoint(temp[j].x() + 3, temp[j].y()));
  //    }

  //    temp = mBlocks[i].InPortPos();
  //    for (int j = 0; j < temp.size(); j++) {
  //      p.drawLine(temp[j], QPoint(temp[j].x() - 3, temp[j].y()));
  //    }
  //  }

  p.end();
}
