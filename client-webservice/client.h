#ifndef CLIENT_H
#define CLIENT_H

#include <QDebug>
#include <qtsoap.h>

class Client : public QObject
{
    Q_OBJECT

    public:

        QtSoapHttpTransport http;
        int number1;
        int number2;

        Client(QString addr, int port, QObject *parent = 0);
        void checkLogin(QString log);
        void createUser(QString login, QString pass);

    private slots:
        void getResponse();
signals:
        void response(QString message);
};

#endif

