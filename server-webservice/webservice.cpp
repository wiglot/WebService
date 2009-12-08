#include "webservice.h"
#include "simplesoapparser.h"
#include <QHash>
#include <QDebug>
#include <QxtWebRequestEvent>
#include <QxtWebContent>
#include <QBuffer>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>

WebService::WebService(QxtAbstractWebSessionManager * sm , QObject * parent):QxtWebServiceDirectory(sm, parent){
	
}

WebService::~WebService(){

}

void WebService::indexRequested(QxtWebRequestEvent *event)
{
    qDebug() << "Request Headers: ";

  //  QHash::const_iterator i = event->headers.constBegin();

//     while (i != event->headers.constEnd()) {
 //        qDebug() << i.key() << ": " << i.value();
//         ++i;
//     }

    if (event->method.compare("POST")==0) {
        QxtWebContent *myContent = event->content;
        qDebug() << "Bytes to read: " << myContent->unreadBytes();
        myContent->waitForAllContent();
        QByteArray requestContent = myContent->readAll();


        qDebug() << "Content: ";
        qDebug() << requestContent;

        //Parse XML
        SimpleSoapParser handler;
        QXmlSimpleReader reader;
        reader.setContentHandler(&handler);
        reader.setErrorHandler(&handler);

        QBuffer xml(&requestContent);
        QXmlInputSource xmlInputSource(&xml);
        if (!reader.parse(xmlInputSource)){
            //In case of error on parse...
            postEvent(new QxtWebPageEvent(event->sessionID,
                                          event->requestID,
                                          DEFAULT_MESSAGE));

            return;
        }

        if (handler.method() == "ExistLogin"){
            QString bodyMessage = buildResponse(this->checkLogin(handler.arg(0)), "ExistLogin");
            qDebug() << bodyMessage;
            postEvent(new QxtWebPageEvent(event->sessionID,
                                         event->requestID,
                                         bodyMessage.toUtf8()));


        }
        if (handler.method() == "CreateUser"){
            QString bodyMessage = buildResponse(
                              this->createUser(handler.arg(0), handler.arg(1)),
                              "CreateUser");
            qDebug() << bodyMessage;
            postEvent(new QxtWebPageEvent(event->sessionID,
                                         event->requestID,
                                         bodyMessage.toUtf8()));


        }


    } else if (event->method.compare("GET")==0) {
        postEvent(new QxtWebPageEvent(event->sessionID,
                                      event->requestID,
                                      DEFAULT_MESSAGE));
    }
}

QString WebService::buildResponse(QString sum, QString actionName)
{
    QString body;
    body.append("<?xml version=\"1.0\"?>\r\n");
    body.append("<s:Envelope  xmlns:s=\"http://schemas.xmlsoap.org/soap/envelope/\" s:encodingStyle=\"http://schemas.xmlsoap.org/soap/encoding/\">\r\n");
    body.append("<s:Body>\r\n");
    body.append("<u:"+actionName+"Response xmlns:u=\"urn:schemas-upnp-org:service:LoginValidator:1\">\r\n");
    body.append("<"+actionName+">"+sum+"</"+actionName+">\r\n");
    body.append("</u:"+actionName+"Response>\r\n");
    body.append("</s:Body>\r\n");
    body.append("</s:Envelope>\r\n");
    return body;
}

QString WebService::checkLogin(QString login){
    QSqlQuery q ;
    if (q.exec("SELECT count(login) FROM users WHERE login='"+login+"';")){
        if (q.next()){
            if (q.value(0).toInt() == 0){
                return QString("Not Exist");
            }
            return QString("Exist");
        }
    }
    return QString("Sorry, Database error: " + q.lastError().text());

}


QString WebService::createUser(QString user, QString pass){

    QSqlQuery q ;

    if (checkLogin(user) == "Exist"){
        return QString("User allready exist!");
    }

    q.prepare("insert into users values(:a, :b)");
    q.bindValue(":a",user);
    q.bindValue(":b",pass);
    if (q.exec()){
         return QString("Inserted!");
    }
    return QString("Sorry, Database error: " + q.lastError().text());
}
