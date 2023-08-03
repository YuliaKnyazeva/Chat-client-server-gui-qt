#include "registrationform.h"
#include "ui_registrationform.h"

registrationForm::registrationForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registrationForm)
{
    ui->setupUi(this);
}

registrationForm::~registrationForm()
{
    delete ui;
}

void registrationForm::on_buttonBox_accepted()
{
    QString str="2|";
    str.append(ui->nameEdit->text()+"|"+ui->loginEdit->text()+"|"+ui->passwordEdit->text());
    emit accepted(str);
    ui->nameEdit->clear();
    ui->loginEdit->clear();
    ui->passwordEdit->clear();
}


void registrationForm::on_buttonBox_rejected()
{
    this->close();
}
