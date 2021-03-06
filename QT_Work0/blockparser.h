#ifndef BLOCKPARSER_H
#define BLOCKPARSER_H

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QStringList>

class BlockParser {
 public:
  /*!
   * \brief Constructor of BlockParser
   * \param Path The  *NIX-like full-path to Module Metadata json file.
   */
  explicit BlockParser(QString Path);
  /*!
   * \brief getBlockName
   * \return The verbose and descriptive name of this block
   */
  QString getBlockName();
  /*!
   * \brief ReturnInId
   * \param a
   * \param b
   * \return
   *
   *Hello
   *===
   *
   * this is `content`
   *
   */
  QStringList ReturnInId();
  QStringList ReturnInDes();
  QStringList ReturnOutId();
  QStringList ReturnOutDes();

 private:
  QFile *fp;
  QJsonDocument *JsonObj;
  QJsonValue name_value;
  QString name;
  QStringList InputId;
  QStringList InputDes;
  QStringList OutputId;
  QStringList OutputDes;
  void getBlockInput();
  void getBlockOutput();
};

#endif  // BLOCKPARSER_H
