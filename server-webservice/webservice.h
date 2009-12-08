#ifndef WEBSERVICE_H
#define WEBSERVICE_H

//#include "xmlparser.h"
#include <QxtWebServiceDirectory>
#define DEFAULT_MESSAGE "<h1>RUN AWAY!</h1>"

class WebService : public QxtWebServiceDirectory {

Q_OBJECT

public:
    WebService(QxtAbstractWebSessionManager * sm , QObject * parent = 0);
    virtual ~WebService();

 protected:
    void indexRequested (QxtWebRequestEvent *event);

private:
    QString checkLogin(QString login);
    QString createUser(QString user, QString pass);

    QString buildResponse(QString sum, QString actionName);
};

#endif

