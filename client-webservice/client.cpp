#include "client.h"



Client::Client(QString addr, int port, QObject *parent) : QObject(parent)
{
    http.setHost(addr, port);
    // Or use just http.setHost(host)
    connect(&http, SIGNAL(responseReady()), this, SLOT(getResponse()));

}

void Client::checkLogin(QString login)
{
    QtSoapMessage request;
    request.setMethod("ExistLogin");
    request.addMethodArgument("login", "", login);
    qDebug() << "Checking login: " << login;
    http.submitRequest(request, "/add/");
}

void Client::createUser(QString login, QString pass){
    QtSoapMessage request;
    request.setMethod("CreateUser");
    request.addMethodArgument("login", "", login);
    request.addMethodArgument("pass", "", pass);
    qDebug() << "Checking login: " << login;
    http.submitRequest(request, "/add/");
}

void Client::getResponse()
{
    const QtSoapMessage &message = http.getResponse();
    if (message.isFault()) {
        qDebug("Error: %s", qPrintable(message.faultString().toString()));
    }
    qDebug()<< message.returnValue().toString();
    emit response(message.returnValue().toString());

}



