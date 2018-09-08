#include "blockparser.h"
#include <QVariant>
#include <QtGlobal>

BlockParser::BlockParser(QString Path) {
  fp = new QFile(Path);
  if (!fp->open(QIODevice::ReadOnly)) {
    // Do something here to handle the error
  }
  QJsonParseError tJsonError;
  this->JsonObj =
      new QJsonDocument(QJsonDocument::fromJson(fp->readAll(), &tJsonError));
  if (tJsonError.error != QJsonParseError::NoError) {
    // Do something here to handle the error
  }
}

QString BlockParser::getBlockName() {
  // if you want access something , get the jsonObj First.
  const QJsonObject &tObj = this->JsonObj->object();
  QJsonObject::const_iterator tIter = tObj.constFind(QString("name"));
  if (tIter != tObj.end() && (*tIter).isString())
    return (*tIter).toString();
  else
    // Do something here to handle the error
    throw - 1;
}

void BlockParser::getBlockInput() {
  // if you want access something , get the jsonObj First.
  const QJsonObject &tObj = this->JsonObj->object();
  QJsonObject::const_iterator tIter = tObj.constFind(QString("Input"));
  if (tIter != tObj.end() && (*tIter).isArray()) {
    QJsonArray array = (*tIter).toArray();
    for (int i = 0; i < array.size(); i++) {
      QJsonObject Objtemp = array.at(i).toObject();
      QJsonObject::const_iterator Itertemp = Objtemp.constFind("description");
      if (Itertemp != Objtemp.end() && (*Itertemp).isString()) {
        InputDes.insert(i, (*Itertemp).toString());
      }

      Itertemp = Objtemp.constFind("id");
      if (Itertemp != Objtemp.end() && (*Itertemp).isString()) {
        InputId.insert(i, (*Itertemp).toString());
      }
    }
  } else
    // Do something here to handle the error
    throw - 1;

  qDebug() << InputId;
  qDebug() << InputDes;
}

void BlockParser::getBlockOutput() {
  // if you want access something , get the jsonObj First.
  const QJsonObject &tObj = this->JsonObj->object();
  QJsonObject::const_iterator tIter = tObj.constFind(QString("Output"));
  if (tIter != tObj.end() && (*tIter).isArray()) {
    QJsonArray array = (*tIter).toArray();
    for (int i = 0; i < array.size(); i++) {
      QJsonObject Objtemp = array.at(i).toObject();
      QJsonObject::const_iterator Itertemp = Objtemp.constFind("description");
      if (Itertemp != Objtemp.end() && (*Itertemp).isString()) {
        OutputDes.insert(i, (*Itertemp).toString());
      }

      Itertemp = Objtemp.constFind("id");
      if (Itertemp != Objtemp.end() && (*Itertemp).isString()) {
        OutputId.insert(i, (*Itertemp).toString());
      }
    }
  } else
    // Do something here to handle the error
    throw - 1;

  qDebug() << OutputId;
  qDebug() << OutputDes;
}

QStringList BlockParser::ReturnInId() { return InputId; }

QStringList BlockParser::ReturnInDes() { return InputDes; }

QStringList BlockParser::ReturnOutId() { return OutputId; }

QStringList BlockParser::ReturnOutDes() { return OutputDes; }
