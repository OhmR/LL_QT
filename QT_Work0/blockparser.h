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
    BlockParser();
    void parser();
    void build();

private:
    QFile *fp;
    QJsonValue name_value;
    QString name;
};

#endif // BLOCKPARSER_H
