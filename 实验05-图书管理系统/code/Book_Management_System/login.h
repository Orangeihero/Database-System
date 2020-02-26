#ifndef LOGIN_H
#define LOGIN_H

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
class LogIn;
}

class LogIn : public QDialog
{
    Q_OBJECT

public:
    explicit LogIn(QWidget *parent = nullptr);
    ~LogIn();

private slots:
    void on_LogInPushButton_clicked();//登录界面

private:
    Ui::LogIn *ui;
};

#endif // LOGIN_H
