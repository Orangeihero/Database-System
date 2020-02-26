#include "login.h"
#include <QObject>
#include <QApplication>
#include <QMessageBox>
#include <QMainWindow>
#include <QDebug>
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QTextCodec>
#include<QFile>
#include <QTextCodec>

QSqlDatabase db;

QSqlQuery bookQuery;
QSqlQuery borrowQuery;
QSqlQuery cardQuery;
QSqlQuery adminQuery;

bool CreatConnect();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    bool isok = CreatConnect();//记录数据库是否连接成功
    if(isok)
    {
        LogIn login;
        login.exec();
    }
    return a.exec();
}

bool CreatConnect()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("booksystemmanager");
    db.setUserName("root");
    db.setPassword("111111");

    if(!db.open())//连接数据库失败
    {
        QMessageBox::critical(nullptr,QObject::tr("连接数据库失败！！！"),db.lastError().text());
        return false;
    }
    else//连接数据库成功
    {
        QMessageBox::information(nullptr,QObject::tr("Tips"),QObject::tr("连接数据库成功！！！"));
        cardQuery = QSqlQuery(db);
        borrowQuery = QSqlQuery(db);
        bookQuery = QSqlQuery(db);
        adminQuery = QSqlQuery(db);
        return true;
    }
}
