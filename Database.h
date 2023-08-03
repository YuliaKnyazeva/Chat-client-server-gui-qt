#pragma once
#include <iostream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

class Database
{
public:
    Database();
    ~Database();
	void Disconnect();
	void CreateTables();
    void addUserInDb(const QString login, const QString password, const QString name);
    void addMessageInDb(const QString from, const QString to, const QString text);
    bool checkLogin(const QString login);
    bool checkUser(const QString login, const QString password);
    QString showUsers();
    QString showPrivateMessages(const QString login);
    QString showCommonMessages ();
    QString GetName(const QString login, const QString password);
    bool connect;
private:
    QSqlDatabase db;
};

