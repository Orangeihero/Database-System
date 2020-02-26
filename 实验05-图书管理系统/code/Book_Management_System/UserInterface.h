#ifndef USERINTERFACE_H
#define USERINTERFACE_H

//#include "Book.h"
//#include "ui_Book.h"

#include <QWidget>
#include <QMainWindow>
#include <QDialog>
#include <QString>
#include<QMenuBar>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

extern QSqlDatabase db;
extern QSqlQuery bookQuery;
extern QSqlQuery borrowQuery;
extern QSqlQuery cardQuery;

namespace Ui {
class UserInterface;
}

class UserInterface : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserInterface(QWidget *parent = nullptr,QString scno = "");
    ~UserInterface();

private slots:
    void on_ExitAction_triggered();

private:
    Ui::UserInterface *ui;
    QString cno;
};

#endif // USERINTERFACE_H
