#ifndef BLOCKPARSER_H
#define BLOCKPARSER_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonValue>
#include <QFile>
#include <QDebug>

class BlockParser
{
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
    void parser();
    void build();

private:
    QFile *fp;
    QJsonDocument *JsonObj;
    QJsonValue name_value;
    QString name;
};

#endif // BLOCKPARSER_H
