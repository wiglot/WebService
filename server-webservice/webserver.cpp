#include "webserver.h"
#include "webservice.h"

WebServer::WebServer(const QHostAddress &host,quint16 port)
{
    QxtHttpSessionManager(this);
    rootService = new WebService(this,this);
    setPort(port);
    setListenInterface(host);
    setConnector(HttpServer);
    setStaticContentService(rootService);

    qDebug() << "WebServer Started!";
}

WebServer::~WebServer()
{
    delete rootService;
}

void WebServer::incomingRequest(quint32 requestID,
                                const QHttpRequestHeader & header,
                                QxtWebContent *deviceContent)
{
    QxtHttpSessionManager::incomingRequest(requestID, header, deviceContent);
    qDebug() << "Request: "<< requestID;
    qDebug() << "Method: " << header.method();
    qDebug() << "URI: " << header.path();
}

void WebServer::addService(QString uri,WebService *newService)
{
    rootService->addService(uri,newService);
}

