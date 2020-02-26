#ifndef USER_MANAGE_H
#define USER_MANAGE_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

extern QSqlDatabase db;
extern QSqlQuery bookQuery;
extern QSqlQuery loanQuery;
extern QSqlQuery userQuery;

namespace Ui {
class User_manage;
}

class User_manage : public QWidget
{
    Q_OBJECT

public:
    explicit User_manage(QWidget *parent = nullptr);
    ~User_manage();


private:
    Ui::User_manage *ui;
};

#endif // USER_MANAGE_H
