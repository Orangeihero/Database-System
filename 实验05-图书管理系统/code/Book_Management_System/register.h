#ifndef REGISTER_H
#define REGISTER_H

#include "login.h"
#include"usermanage.h"

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>


extern QSqlDatabase db;
extern QSqlQuery bookQuery;
extern QSqlQuery borrowQuery;
extern QSqlQuery cardQuery;
extern QSqlQuery adminQuery;

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr,UserManage* u=nullptr);
    ~Register();

private slots:
    void on_RegisterPushButton_clicked();//注册

private:
    Ui::Register *ui;
    LogIn* login;
    UserManage* usermanage;
};

#endif // REGISTER_H
