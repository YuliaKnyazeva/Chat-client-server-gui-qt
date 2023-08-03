#ifndef CHATFORM_H
#define CHATFORM_H

#include <QDialog>

namespace Ui {
class chatForm;
}

class chatForm : public QDialog
{
    Q_OBJECT

public:
    explicit chatForm(QWidget *parent = nullptr);
    ~chatForm();
    void incomingPrivateMessage(QString str);
    void incomingCommonMessage(QString str);

signals:
    void sendMessage(QString str);
    void closeChat();
    void getLogin();

private slots:
    void on_sendMessage_clicked();
    void on_exit_clicked();
    void on_returnToLoginForm_clicked();
    void on_LoadCommonMessage_clicked();
    void on_loadPrivateMessage_clicked();

private:
    Ui::chatForm *ui;
    //QString _login;
    void setLogin(QString str);
};

#endif // CHATFORM_H
