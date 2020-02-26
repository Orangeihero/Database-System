#ifndef USERMANAGE_H
#define USERMANAGE_H

#include <QDialog>
#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

extern QSqlDatabase db;
extern QSqlQuery bookQuery;
extern QSqlQuery borrowQuery;
extern QSqlQuery cardQuery;

namespace Ui {
class UserManage;
}

class UserManage : public QWidget
{
    Q_OBJECT

public:
    explicit UserManage(QWidget *parent = nullptr);
    ~UserManage();

private slots:
    void on_AddUser_clicked();//增加一个借书证
    void on_DeleteUser_clicked();//删除一个借书证
    void on_RefreshPushButton_clicked();//更新借书证列表
    void on_FindPushButton_clicked();//搜索

private:
    Ui::UserManage *ui;
};

#endif // USERMANAGE_H
