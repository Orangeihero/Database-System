#ifndef RETURNBOOK_H
#define RETURNBOOK_H

#include <QWidget>
#include <QDialog>
#include <QString>
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
class ReturnBook;
}

class ReturnBook : public QWidget
{
    Q_OBJECT

public:
    explicit ReturnBook(QWidget *parent = nullptr);
    Ui::ReturnBook *ui;
    QString username;
    ~ReturnBook();

private slots:
    void on_ReturnPushButton_clicked();//归还
    void on_RefreshThisPushButton_clicked();//更新特定用户的借阅记录
    void on_RefreshAllPushButton_clicked();//更新所有用户的借阅记录

private:


};

#endif // RETURNBOOK_H
