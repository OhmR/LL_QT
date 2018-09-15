#include <baseblock.h>
#include <QtGlobal>

BaseBlock::BaseBlock(BlockParser& bp) : mBlockMetaInfo(bp) {
  this->input = bp.ReturnInId().size();
  this->output = bp.ReturnOutId().size();
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
  qDebug() << "Paint Block";
  switch (mCurStatus) {
    case floating: {
      painter->setPen(QPen(Qt::gray, 2, Qt::DotLine, Qt::RoundCap));
      painter->setBrush(Qt::white);
      painter->drawRect(mPosition.leftTopPoint.x() - 2 * 10,
                        mPosition.leftTopPoint.y() - qMax(input, output) * 10,
                        4 * 10, qMax(input, output) * 2 * 10);
    } break;
    case fixed: {
      painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
      painter->setBrush(Qt::white);
      mPosition.width = 4 * 10;
      mPosition.height = qMax(input, output) * 2 * 10;

      painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
      painter->setBrush(Qt::white);
      // use overriding function will increase readablility
      painter->drawRect(QRectF(mPosition.leftTopPoint,
                               QSize(mPosition.width, mPosition.height)));
    } break;

    case loaded:
      break;
  }
}
void BaseBlock::setPosition(position* a) {
  mPosition = *a;
  emit statusChange();
}

void BaseBlock::setStatus(BlockStatus a) {
  mCurStatus = a;
  emit statusChange();
}
