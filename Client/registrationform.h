#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H

#include <QDialog>

namespace Ui {
class registrationForm;
}

class registrationForm : public QDialog
{
    Q_OBJECT

public:
    explicit registrationForm(QWidget *parent = nullptr);
    ~registrationForm();
signals:
    void accepted(QString str);
private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::registrationForm *ui;
};

#endif // REGISTRATIONFORM_H
