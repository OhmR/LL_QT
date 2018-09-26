#include <baseblock.h>
#include <QtGlobal>

BaseBlock::BaseBlock(BlockParser& bp, int size) : mBlockMetaInfo(bp) {
  this->input = bp.ReturnInId().size();
  this->output = bp.ReturnOutId().size();
  this->setStatus(IBlock::loaded);
  space = size;

  mPosition.width = 4 * space;
  mPosition.height = qMax(input, output) * 2 * space;
}

QList<QPoint> BaseBlock::InPortPos() {
  QList<QPoint> in;
  QPoint* p;
  for (int i = 0; i < this->input; i++) {
    p = new QPoint(this->mPosition.leftTopPoint.x(),
                   this->mPosition.leftTopPoint.y() +
                       (i + 1) * this->mPosition.height / (input + 1));
    in.append(*p);
  }
  return in;
}

QList<QPoint> BaseBlock::OutPortPos() {
  QList<QPoint> out;
  QPoint* p;
  for (int i = 0; i < this->output; i++) {
    p = new QPoint(this->mPosition.leftTopPoint.x() + 40,
                   this->mPosition.leftTopPoint.y() +
                       (i + 1) * this->mPosition.height / (output + 1));
    out.append(*p);
  }
  return out;
}

void BaseBlock::paintSelf(QPainter* painter) {
  switch (mCurStatus) {
    case floating: {
      painter->setPen(QPen(Qt::gray, 2, Qt::DotLine, Qt::RoundCap));
      painter->setBrush(Qt::white);
      painter->drawRect(
          qRound64(mPosition.leftTopPoint.x() / space) * space - 2 * space,
          qRound64(mPosition.leftTopPoint.y() / space) * space -
              qMax(input, output) * space,
          4 * space, qMax(input, output) * 2 * space);
    } break;
    case fixed: {
      painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
      painter->setBrush(Qt::white);

      painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
      painter->setBrush(Qt::white);
      // use overriding function will increase readablility
      painter->drawRect(
          qRound64(mPosition.leftTopPoint.x() / space) * space - 2 * space,
          qRound64(mPosition.leftTopPoint.y() / space) * space -
              qMax(input, output) * space,
          mPosition.width, mPosition.height);
    } break;
    case selected: {
      painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
      painter->setBrush(Qt::white);

      painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
      painter->setBrush(Qt::white);
      // use overriding function will increase readablility
      painter->drawRect(
          qRound64(mPosition.leftTopPoint.x() / space) * space - 2 * space,
          qRound64(mPosition.leftTopPoint.y() / space) * space -
              qMax(input, output) * space,
          mPosition.width, mPosition.height);
      paintSelectFrame(painter);
    } break;
    case loaded:
      break;
  }
}

void BaseBlock::paintSelectFrame(QPainter* painter) {
  painter->setPen(Qt::black);
  painter->setBrush(Qt::NoBrush);
  painter->drawEllipse(BlockLeftBottom(), 5, 5);
  painter->drawEllipse(BlockLeftTop(), 5, 5);
  painter->drawEllipse(BlockRightBottom(), 5, 5);
  painter->drawEllipse(BlockRightTop(), 5, 5);
}

void BaseBlock::setPosition(position* a) {
  mPosition = *a;
  emit statusChange();
}

void BaseBlock::setStatus(BlockStatus a) {
  qDebug() << "SetBlockStatus:" << a;
  mCurStatus = a;
  emit statusChange();
}

int BaseBlock::returnStatus() { return mCurStatus; }

int BaseBlock::returnheight() { return mPosition.height; }

int BaseBlock::returnwidth() { return mPosition.width; }

bool BaseBlock::at_range(QPoint start, QPoint end) {
  if (this->mPosition.leftTopPoint.x() - this->mPosition.width / 2 >
          start.x() &&
      this->mPosition.leftTopPoint.y() - this->mPosition.height / 2 >
          start.y() &&
      this->mPosition.leftTopPoint.x() + this->mPosition.width / 2 < end.x() &&
      this->mPosition.leftTopPoint.y() + this->mPosition.height / 2 < end.y())
    return true;
  else
    return false;
}

bool BaseBlock::contain_point(QPoint point) {
  qDebug() << "mPosition.width";
  qDebug() << mPosition.width;
  qDebug() << "leftTopPoint, point";
  qDebug() << mPosition.leftTopPoint.x() - this->mPosition.width / 2;
  qDebug() << mPosition.leftTopPoint.y() - this->mPosition.height / 2;
  qDebug() << point.x();
  qDebug() << point.y();
  if (this->mPosition.leftTopPoint.x() - this->mPosition.width / 2 <
          point.x() &&
      this->mPosition.leftTopPoint.y() - this->mPosition.height / 2 <
          point.y() &&
      this->mPosition.leftTopPoint.x() + this->mPosition.width / 2 >
          point.x() &&
      this->mPosition.leftTopPoint.y() + this->mPosition.height / 2 > point.y())
    return true;
  else
    return false;
}

QPoint BaseBlock::BlockLeftBottom() {
  return QPoint(
      qRound64(mPosition.leftTopPoint.x() / space) * space - 2 * space,
      qRound64(mPosition.leftTopPoint.y() / space) * space -
          qMax(input, output) * space + mPosition.height);
}

QPoint BaseBlock::BlockLeftTop() {
  return QPoint(
      qRound64(mPosition.leftTopPoint.x() / space) * space - 2 * space,
      qRound64(mPosition.leftTopPoint.y() / space) * space -
          qMax(input, output) * space);
}

QPoint BaseBlock::BlockRightBottom() {
  return QPoint(qRound64(mPosition.leftTopPoint.x() / space) * space -
                    2 * space + mPosition.width,
                qRound64(mPosition.leftTopPoint.y() / space) * space -
                    qMax(input, output) * space + mPosition.height);
}

QPoint BaseBlock::BlockRightTop() {
  return QPoint(qRound64(mPosition.leftTopPoint.x() / space) * space -
                    2 * space + mPosition.width,
                qRound64(mPosition.leftTopPoint.y() / space) * space -
                    qMax(input, output) * space);
}
