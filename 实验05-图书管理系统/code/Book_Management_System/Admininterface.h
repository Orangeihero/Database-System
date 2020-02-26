#ifndef ADMININTERFACE_H
#define ADMININTERFACE_H

#include <QMainWindow>
#include <QDialog>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QWidget>


extern QSqlDatabase db;
extern QSqlQuery bookQuery;
extern QSqlQuery borrowQuery;
extern QSqlQuery cardQuery;
extern QSqlQuery adminQuery;

namespace Ui {
class AdminInterface;
}

class AdminInterface : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminInterface(QWidget *parent = nullptr,QString id = "");
    ~AdminInterface();

private slots:
    void on_Exit_triggered();

private:
    Ui::AdminInterface *ui;
    QString adminid;
};

#endif // ADMININTERFACE_H
