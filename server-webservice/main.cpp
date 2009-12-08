#include "webservice.h"
#include "webserver.h"

#include <QHostAddress>

#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>

int main (int argc, char ** argv){
    QCoreApplication app(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

     db.setDatabaseName("users.db");
     bool ok = db.open();
     if (!ok){
         return -1;
     }
     QSqlQuery q("Create table users(login VARCHAR(40) not null, pass VARCHAR(24),"
                 "PRIMARY KEY(login));");
     q.exec();
     q.finish();

    WebServer *myWebServer = new WebServer(QHostAddress("127.0.0.1"),12345);
    WebService *sum = new WebService(myWebServer,0);

    myWebServer->addService("add",sum);
    myWebServer->start();

    return  app.exec();

}
