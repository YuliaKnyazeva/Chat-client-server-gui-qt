#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _server = new QTcpServer(this);
    connect(_server,&QTcpServer::newConnection,this,&MainWindow::SlotnewConnection);
    if (!_server->listen(QHostAddress::Any,7777))
    {
        ui->Messages->append("server is not srarted");
    }
    else
    {
        ui->Messages->append("Server is started");
    }
    nextBlocksize=0;
    ui->Users->append(db.showUsers());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SlotnewConnection()
{
    _socket=_server->nextPendingConnection();
    connect(_socket,&QTcpSocket::readyRead,this,&MainWindow::SlotServerRead);
    connect(_socket,&QTcpSocket::disconnected,this,&MainWindow::SlotClientDisconnect);
    _sockets.push_back(_socket);
    ui->Messages->append("Client connected");
}

void MainWindow::SlotClientDisconnect()
{
    _socket->close();
    ui->Messages->append("Client disconnected");
}

void MainWindow::SendToClient(QString& str)
{
    data.clear();
    QDataStream out(&data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_5);
    out<<quint16(0)<<str;
    out.device()->seek(0);
    out<<quint16(data.size()-sizeof(quint16));
    _socket->write(data);
}
void MainWindow::SlotServerRead()
{
    _socket = (QTcpSocket*)sender();
    QDataStream in(_socket);
    in.setVersion(QDataStream::Qt_6_5);
    if (in.status() == QDataStream::Ok)
    {
        for(;;)
        {
            if (nextBlocksize==0)
            {
                if (_socket->bytesAvailable()<2)
                {
                    break;
                }
                in>>nextBlocksize;
            }
            if (_socket->bytesAvailable()<nextBlocksize)
                {
                    break;
                }
    QString str, str1;
    int operation;
    in>>str;
    ui->Messages->append(str);
    nextBlocksize=0;
    QStringList temp=str.split(u'|');
    operation = temp[0].toInt();
    switch (operation)
    {
    case 1: // Авторизация

    if(db.checkUser(temp[1],temp[2]))
    {                    
        str1="1";
        ui->Messages->append("Autorization successful. User "+db.GetName(temp[1],temp[2])+" is online."+"\n");
        SendToClient(str1);
        }
        else
    {
        str1="10";
        ui->Messages->append("Invalid login or password \n");
        SendToClient(str1);
        }
    break;

    case 2://Регистрация
    if(db.checkLogin(temp[2]))
    {
        db.addUserInDb(temp[1],temp[2],temp[3]);
        ui->Messages->append("Registration succesful. Added new user in database.\n");
        SendToClient(str);
        }
    else
    {
        ui->Messages->append("Registration canceled. Login already exists.\n"+str);
        str="20";
        SendToClient(str);
        }
        break;

    case 3:
        db.addMessageInDb(temp[1],temp[2],temp[3]);
        ui->Messages->append("User "+temp[1]+" send message to user "+temp[3]+": "+temp[2]+"\n");
        break;

    case 4:
        str1=db.showPrivateMessages(temp[1]);
        SendToClient(str1);
        ui->Messages->append("Sending private messages");
        break;
    case 41:
        str1=db.showCommonMessages();
        SendToClient(str1);
        ui->Messages->append("Sending common messages");
    }
    break;
    }
}
}

void MainWindow::on_DisconnectUser_clicked()
{
ui->Messages->clear();
}

