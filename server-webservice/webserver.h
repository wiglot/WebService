
#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "webservice.h"
#include <QHostAddress>
#include <QxtHttpSessionManager>


class WebServer : public QxtHttpSessionManager {

Q_OBJECT

public:
    WebServer(const QHostAddress &host , quint16 port);
    virtual ~WebServer();

    void addService(QString uri,WebService *newService);

signals:
    void postReceived(QByteArray content);

protected:
    void incomingRequest(quint32 requestID,
                         const QHttpRequestHeader & header,
                         QxtWebContent *deviceContent);

private:
    WebService *rootService;
};


#endif

