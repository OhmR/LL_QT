#include "blockparser.h"

BlockParser::BlockParser()
{
    fp = new QFile("/home/ohmr/test.json");
    fp->open(QIODevice::ReadOnly);
}

void BlockParser::parser()
{
    QJsonParseError json_error;
    QJsonDocument parse_document = QJsonDocument::fromJson(fp->readAll(), &json_error);
    if(json_error.error == QJsonParseError::NoError){
        if(parse_document.isObject()){      //need to be complete
            qDebug()<<"isObject";
            QJsonObject obj = parse_document.object();
            if(obj.contains("name")){   //get name of object
                name_value = obj.take("name");
                if(name_value.isString()){
                    name = name_value.toString();
                }
            }
        }
        else if(parse_document.isArray()){
            qDebug()<<"isArray";
        }
    }

    qDebug()<<parse_document.toVariant();
}
