#ifndef BASEBLOCK_H
#define BASEBLOCK_H

#include <QDebug>
#include <QList>
#include <QStringList>
#include "iblock.h"

/*!
 * \brief The BaseBlock class
 * Baseblock is block which common appearance. Typically , a Baseblock is an
 * rectangle with some extra pins.
 *
 * A Baseblock has two kinds of pins. One is "input Pin" which  will be
 * disposed on the left side of the rectangle. Another is  "output Pin" which
 * will be  disposed on the right side of the rectangle.
 *
 * This class holds the data which are needed when drawing this block to
 * Canvas. Such as block's position , geometric info  and etc.
 *
 * This class also implements some function for user to  "interact" with the the
 * Block.
 *
 * In some way, This class represents both "Controller" layer and "model" layer
 * in MVC design pattern.
 */
class BaseBlock : public QObject, public IBlock {
  Q_OBJECT
  Q_INTERFACES(IBlock)

 public:
  int input;   //输入接口数
  int output;  //输出接口数
  BaseBlock(QStringList InputId, QStringList InputDes, QStringList OutputId,
            QStringList OutputDes, QString BlockName);
  QString ReturnBlockName();
  QString InId(int index);
  QString OutId(int index);
  QString InDes(int index);
  QString OutDes(int index);
  QList<QPoint> InPortPos();   // Input Ports Position
  QList<QPoint> OutPortPos();  // Output Ports Position
  void paintSelf(QPainter* painter) override;
  void setPosition(position* a) override;
  void setStatus(BlockStatus a) override;
 signals:
  void statusChange();

 private:
  QStringList InputId;
  QStringList InputDes;
  QStringList OutputId;
  QStringList OutputDes;
  QString BlockName;
};

#endif  // BASEBLOCK_H
