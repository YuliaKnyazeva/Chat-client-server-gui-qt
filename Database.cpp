#include "Database.h"
#include <QMessageBox>
#include <QWidget>
#include <QSqlError>

Database::Database()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("testdb");
    db.setUserName("root");
    db.setPassword("poison");
    if (db.open())
    {
        qDebug() << "Connect to database successfull!";
    }
    else
    {
        qDebug()<<"Error open database because"<<db.lastError().text();
        qDebug() <<"Error coonect to databse";
    }
}

Database::~Database()
{
    db.close();
    qDebug() << "Disconnect database";
}


void Database::CreateTables() //
{
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS users(id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255), login VARCHAR(255), password VARCHAR(255))");
    query.exec("CREATE TABLE IF NOT EXISTS users(id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255), login VARCHAR(255), password VARCHAR(255))");
    query.exec("INSERT INTO users(id, name, login, password) values(default, 'Daria', 'Daria', '123')");
    query.exec("INSERT INTO users(id, name, login, password) values(default, 'Lida', 'Lida', '234')");
    query.exec("INSERT INTO users(id, name, login, password) values(default, 'Nastya', 'Nastya', '345')");
    query.exec("CREATE TABLE IF NOT EXISTS messages(id INT AUTO_INCREMENT PRIMARY KEY, from_id VARCHAR(255), to_id VARCHAR(255), text VARCHAR(255))");
    query.exec("INSERT INTO messages(id, from_id, to_id, text) values(default, 'Lida', 'Daria', 'Hi!')");
    query.exec("INSERT INTO messages(id, from_id, to_id, text) values(default, 'Daria', 'all', 'Hi all!')");
}

void Database::addUserInDb(const QString name, const QString login, QString password) //Работает
{
    QSqlQuery query;
    query.exec("INSERT INTO users (id, name, login, password) VALUES (default,' " + name + "','" + login + "','" + password + "')");
}

void Database::addMessageInDb(const QString from, const QString to, const QString text)
{
    QSqlQuery query;
    query.exec("INSERT INTO messages (id, from_id, to_id, text) VALUES (default,' " + from + "','" + to + "','" + text + "')");
}

bool Database::checkLogin(const QString login) // Проверка, свободен ли логин - работает
{
    QSqlQuery query;
    query.exec("SELECT * FROM users WHERE login='" + login + "'");
    if(query.next())
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Database::checkUser(const QString login, const QString password) // Проверка авторизации - работает
{
    QSqlQuery query("SELECT name FROM users WHERE login='" + login + "' and password='" + password + "'");
    if(query.next())
    {
        return true;
    }
    else
    {
    return false;
    }
}
QString Database::GetName(const QString login, const QString password)
{
    QString name;
    QSqlQuery query("SELECT name FROM users WHERE login='" + login + "' and password='" + password + "'");
    if(query.next())
    {
        QSqlRecord rec=query.record();
        name = query.value(rec.indexOf("name")).toString();
    }
    qDebug()<<name;
    return name;
}
QString Database::showUsers()
{
    QString name;
    QSqlQuery query("SELECT name FROM users");
    while(query.next())
    {
        QSqlRecord rec=query.record();
        QString tempname = query.value(rec.indexOf("name")).toString();
        name.append(tempname+"\n");
    }
    return name;
}

QString Database::showPrivateMessages(const QString login)
{
    QString messages="3";
    QSqlQuery query("SELECT from_id, text FROM messages WHERE to_id='"+login+"'");
    while(query.next())
    {
        QSqlRecord rec=query.record();
        QString from = query.value(rec.indexOf("from_id")).toString();
        QString tempmes = query.value(rec.indexOf("text")).toString();
        messages.append("|"+from+":"+tempmes);
    }
    return messages;
}

QString Database::showCommonMessages()
{
    QString messages="4";
    QSqlQuery query("SELECT from_id, text FROM messages WHERE to_id='all'");
    while(query.next())
    {
        QSqlRecord rec=query.record();
        QString from = query.value(rec.indexOf("from_id")).toString();
        QString tempmes = query.value(rec.indexOf("text")).toString();
        messages.append("|"+from+":"+tempmes);
    }
    return messages;
}
