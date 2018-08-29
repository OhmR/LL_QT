#include "blockparser.h"
#include <QVariant>
#include <QtGlobal>

BlockParser::BlockParser(QString Path)
{
    fp = new QFile(Path);
    if (!fp->open(QIODevice::ReadOnly))
    {
        //Do something here to handle the error
    }
    QJsonParseError tJsonError;
    this->JsonObj = new QJsonDocument(QJsonDocument::fromJson(fp->readAll(),&tJsonError));
    if(tJsonError.error != QJsonParseError::NoError){
        //Do something here to handle the error
    }
}

QString
BlockParser::getBlockName(){
    //if you want access something , get the jsonObj First.
    const QJsonObject &tObj  =  this->JsonObj->object();
    QJsonObject::const_iterator tIter=tObj.constFind(QString("name"));
    if(tIter!=tObj.end()&& (*tIter).isString())
        return (*tIter).toString();
    else
        //Do something here to handle the error
        throw -1;

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
