#include "mainwindow.h"
#include "client.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->cli = new Client("localhost",12345);
    connect(cli,SIGNAL(response(QString)), this, SLOT(receiveResponse(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_checkLogin_clicked(){
    cli->checkLogin(ui->login->text());

}

void MainWindow::on_createUser_clicked(){
    cli->createUser(ui->login->text(), ui->pass->text());

}

void MainWindow::receiveResponse(QString response){
    ui->responseText->setText(response);

}

