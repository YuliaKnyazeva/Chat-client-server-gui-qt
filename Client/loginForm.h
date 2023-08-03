#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <registrationform.h>
#include "chatform.h"
#include <User.h>
#include <QMainWindow>
#include <QTcpSocket>
#include <vector>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void ReadFromServer();
    void SendToSever(QString str);
signals:
   void incomingPrivateMessage (QString str);
   void incomingCommonMessage (QString str);

private slots:
    void on_SignIn_clicked();
    void on_SignUp_clicked();
    void on_Exit_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QByteArray data;
    quint16 nextBlocksize;
    QString name, login, password;
    registrationForm *r;
    chatForm *c;
    void Data(QString str);
    QString SetLogin();

};
#endif // MAINWINDOW_H
