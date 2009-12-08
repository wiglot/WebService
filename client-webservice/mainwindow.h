#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Client;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void receiveResponse(QString response);

private slots:
    void on_checkLogin_clicked();
    void on_createUser_clicked();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    Client * cli;
};

#endif // MAINWINDOW_H
