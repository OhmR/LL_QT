#include <baseblock.h>
#include <QtGlobal>

BaseBlock::BaseBlock(QStringList InputId, QStringList InputDes,
                     QStringList OutputId, QStringList OutputDes,
                     QString BlockName) {
  this->InputId = InputId;
  this->OutputId = OutputId;
  this->InputDes = InputDes;
  this->OutputDes = OutputDes;
  this->BlockName = BlockName;
  this->input = InputId.size();
  this->output = OutputId.size();
}

QString BaseBlock::InId(int index) {  // index from 0 to size-1
  if (index >= InputId.size()) {
    qDebug() << "baseblock.cpp : InId error!";
    throw - 1;
  }
  return this->InputId.at(index);
}

QString BaseBlock::InDes(int index) {  // index from 0 to size-1
  if (index >= InputDes.size()) {
    qDebug() << "baseblock.cpp : InDes error!";
    throw - 1;
  }
  return this->InputDes.at(index);
}

QString BaseBlock::OutId(int index) {  // index from 0 to size-1
  if (index >= OutputId.size()) {
    qDebug() << "baseblock.cpp : OutId error!";
    throw - 1;
  }
  return this->OutputId.at(index);
}

QString BaseBlock::OutDes(int index) {  // index from 0 to size-1
  if (index >= OutputDes.size()) {
    qDebug() << "baseblock.cpp : OutDes error!";
    throw - 1;
  }
  return this->OutputDes.at(index);
}

QString BaseBlock::ReturnBlockName() { return BlockName; }

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
    }
    case fixed: {
      painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
      painter->setBrush(Qt::white);
      mPosition.width = 4 * 10;
      mPosition.height = qMax(input, output) * 2 * 10;

      painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
      painter->setBrush(Qt::white);
      painter->drawRect(mPosition.leftTopPoint.x(), mPosition.leftTopPoint.y(),
                        mPosition.width, mPosition.height);

      // draw the port in block
      //      painter->setPen(QPen(Qt::blue, 2));
      //      QList<QPoint> temp = mBlocks[i].OutPortPos();

      //      for (int j = 0; j < temp.size(); j++) {
      //        p.drawLine(temp[j], QPoint(temp[j].x() + 3, temp[j].y()));
      //      }

      //      temp = mBlocks[i].InPortPos();
      //      for (int j = 0; j < temp.size(); j++) {
      //        p.drawLine(temp[j], QPoint(temp[j].x() - 3, temp[j].y()));
      //      }
    }

    case loaded:
    default:
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
