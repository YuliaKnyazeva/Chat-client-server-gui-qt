#include "chatform.h"
#include "ui_chatform.h"

chatForm::chatForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatForm)
{
    ui->setupUi(this);
}

chatForm::~chatForm()
{
    delete ui;
}

void chatForm::incomingPrivateMessage(QString str)
{
    QStringList temp=str.split(u'|');
    for(const auto &i: temp)
    {
        ui->privateChat->append(i);
    }
}

void chatForm::incomingCommonMessage(QString str)
{
    QStringList temp=str.split(u'|');
    for (auto i:temp){
        ui->commonChat->append(i);
    }
}

void chatForm::on_sendMessage_clicked()
{
    QString str="3|";
    str.append(ui->sendToEdit->text()+"|"+ui->MessageEdit->text());
    emit sendMessage(str);
}

void chatForm::on_exit_clicked()
{
    qApp->exit();
}

void chatForm::on_returnToLoginForm_clicked()
{
    ui->MessageEdit->clear();
    ui->sendToEdit->clear();
    ui->commonChat->clear();
    ui->privateChat->clear();
    this->close();
    emit closeChat();
}


void chatForm::on_LoadCommonMessage_clicked()
{
    emit sendMessage("41");
}


void chatForm::on_loadPrivateMessage_clicked()
{
    emit sendMessage("4");
}

