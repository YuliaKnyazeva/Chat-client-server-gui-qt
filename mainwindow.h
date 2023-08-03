 #ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <Database.h>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Database db;
public slots:
    void SlotnewConnection();
    void SlotServerRead();
    void SlotClientDisconnect();

private slots:
    void on_DisconnectUser_clicked();

private:
    Ui::MainWindow *ui;
    QTcpServer *_server;
    QTcpSocket *_socket;
    QVector<QTcpSocket*> _sockets;
    quint16 nextBlocksize;
    QByteArray data;
    void SendToClient(QString &str);
};

#endif // MAINWINDOW_H
