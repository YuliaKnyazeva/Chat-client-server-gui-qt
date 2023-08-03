#include "loginForm.h"
#include "registrationform.h"
#include "ui_loginForm.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1",7777);
    ui->textBrowser->append("Connected to server");
    nextBlocksize=0;
    connect(socket,&QTcpSocket::readyRead,this,&MainWindow::ReadFromServer);
    connect(socket,&QTcpSocket::disconnected,socket,&QTcpSocket::deleteLater);
    r = new registrationForm();
    c = new chatForm();
    connect(r,&registrationForm::accepted,this,&MainWindow::SendToSever);
    connect(r,&registrationForm::rejected,this,&MainWindow::show);
    connect(c,&chatForm::sendMessage,this,&MainWindow::Data);
    connect(this,&MainWindow::incomingPrivateMessage,c,&chatForm::incomingPrivateMessage);
    connect(this,&MainWindow::incomingCommonMessage,c,&chatForm::incomingCommonMessage);
    connect(c,&chatForm::closeChat,this,&MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReadFromServer()
{
    QDataStream in(socket);
    (in.setVersion(QDataStream::Qt_6_5));
     if (in.status() == QDataStream::Ok)
     {
         for(;;) {
             if (nextBlocksize==0)
             {if (socket->bytesAvailable()<2)
                {
                     break;
                }
                in>>nextBlocksize;
               }
             if (socket->bytesAvailable()<nextBlocksize)
                    {
                     break;
                    }
            QString str;
            int operation;
            in>>str;
            ui->textBrowser->append(str);
            nextBlocksize=0;
            QStringList temp=str.split(u'|');
            operation = temp[0].toInt();
            switch (operation)
            {
            case 1: //Если авторизация на сервере прошла успешно
            this->close();
            c->show();

         break;
            case 2: // Если регистрация на сервере прошла успешно
            c->show();
         break;
            case 3: //Получаем приватные сообщения от пользователей
        emit incomingPrivateMessage(str);
         break;
            case 4: //Получаем общие сообщения
        emit incomingCommonMessage(str);
         break;
            case 10:
         ui->textBrowser->append("Invalid login or password");
        break;
            case 20:
        r->show();
             }
            break;
         }
     }
 }

void MainWindow::SendToSever(QString str)
{
     data.clear();
     QDataStream out(&data,QIODevice::WriteOnly);
     out.setVersion(QDataStream::Qt_6_5);
     out<<quint16(0)<<str;
     out.device()->seek(0);
     out<<quint16(data.size()-sizeof(quint16));
     socket->write(data);
}

void MainWindow::on_SignIn_clicked()
{
     QString str="1|";
     str.append(ui->loginEdit->text()+"|"+ui->passwordEdit->text());
     login=ui->loginEdit->text();
     password=ui->passwordEdit->text();
     SendToSever(str);
}

void MainWindow::on_SignUp_clicked()
{
    r->show();
    //this->close();
}

void MainWindow::on_Exit_clicked()
{
    qApp->exit(0);
}

void MainWindow::Data(QString str)
{
    ui->textBrowser->append(str);
    QStringList temp=str.split(u'|');
    QString str1;
    if(str=="41")
    {
         SendToSever(str);
    }
    if(str=="4")
    {
         str.append("|"+login);
         SendToSever(str);
    }
    else{
    str1="3|";
         str1.append(login+"|"+temp[1]+"|"+temp[2]);
    SendToSever(str1);}
}
