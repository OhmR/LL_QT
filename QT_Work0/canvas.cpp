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
  BaseBlock *block = new BaseBlock(*par, space);
  //  default selected
  mSelectedBlocks.append(block);
  block->setStatus(IBlock::floating);
  this->addBlock(block);
}

void canvas::mouseMoveEvent(QMouseEvent *e) {
  // MouseMove shouldn't trigger the repaint.
  // it must be the status-change which can and only can make the
  // canvas repaint under MVC pattern.
  // may be have any other operations

  if (this->GetStatus() == pre_select) {
    this->setStatus(multiple_select);
    passpos = e->pos();
  }

  if (this->GetStatus() == multiple_select) {
    curpos = e->pos();
    update();
  }

  //  qDebug() << this->GetStatus();

  for (auto &i : mSelectedBlocks)
    if (i->isFloating()) {
      IBlock::position a;
      a.leftTopPoint = e->pos();
      a.width = i->returnwidth();
      a.height = i->returnheight();
      i->setPosition(&a);
    }
}

void canvas::mousePressEvent(QMouseEvent *e) {
  // same problem. Let the status change trigger repainting.

  if (e->button() & Qt::LeftButton) {
    this->setStatus(pre_select);
  }
  //  if (e->button() & Qt::LeftButton)
  //    for (auto &i : mSelectedBlocks) i->setStatus(IBlock::fixed);
  qDebug() << "in Mousepress";
}

void canvas::mouseReleaseEvent(QMouseEvent *e) {
  mSelectedBlocks.clear();
  if (this->GetStatus() == pre_select) {
    for (auto &i : mBlocks) {
      if (i->contain_point(e->pos())) mSelectedBlocks.append(i);
    }
    this->setStatus(after_select);
    update();
  }

  else if (this->GetStatus() == multiple_select) {
    for (auto &i : mBlocks) {
      if (i->at_range(passpos, e->pos())) mSelectedBlocks.append(i);
    }
    this->setStatus(after_select);
    update();
  }

  if (mSelectedBlocks.size() == 0) this->setStatus(idle);

  if (this->GetStatus() == pre_select || this->GetStatus() == multiple_select)
    this->setStatus(after_select);

  // change block status
  if (e->button() & Qt::LeftButton) {
    for (auto &i : mSelectedBlocks) i->setStatus(IBlock::fixed);
  }

  qDebug() << "size of mSelectedBlocks";
  qDebug() << mSelectedBlocks.size();

  qDebug() << "current status of canvas";
  qDebug() << this->status;
}

void canvas::addBlock(IBlock *a) {
  //   I think we should do mBlocks.appeend at here
  mBlocks.append(a);
  QObject::connect(qobject_cast<QObject *>(dynamic_cast<BaseBlock *>(a)),
                   SIGNAL(statusChange()), this, SLOT(update()));
}

void canvas::deleteBlock() {}

void canvas::setStatus(canvasStatus tempStatus) { status = tempStatus; }

int canvas::GetStatus() { return status; }

void canvas::paintEvent(QPaintEvent *event) {
  /*!
   * DO NOT Handle the block status here. Canvas are controller layer of our mvc
   *pattern.
   *Variable mousepos saved some status in the scope of controller, this is
   *kind of anti-pattern.
   *Controller should modify not store the block.
   */
  Q_UNUSED(event);
  QPainter p;
  p.begin(this);
  p.setPen(Qt::NoPen);
  p.setBrush(QBrush(QColor("green")));
  p.setRenderHint(QPainter::Antialiasing, true);
  // Draw the grid
  for (int x = 0; x < this->width(); x += space) {
    for (int y = 0; y < this->height(); y += space) {
      p.drawEllipse(QPoint(x, y), 1, 1);
    }
  }

  // Draw the Rec
  if (this->GetStatus() == multiple_select) {
    p.setPen(QPen(Qt::gray, 2, Qt::DotLine, Qt::RoundCap));
    p.setBrush(Qt::NoBrush);

    p.drawRect(QRect(passpos, curpos));
  }

  // Draw the block
  for (auto &i : mBlocks) i->paintSelf(&p);

  // Draw the selected Blocks' frame
  for (auto &i : mSelectedBlocks) i->paintSelectFrame(&p);

  p.end();
}
