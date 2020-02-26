#include "admininterface.h"
#include "ui_admininterface.h"
#include <QStringList>
#include <QApplication>
#include <QMessageBox>
#include <QDate>
#include <QDebug>

AdminInterface::AdminInterface(QWidget *parent,QString id) :
    QMainWindow(parent),
    ui(new Ui::AdminInterface)
{
    ui->setupUi(this);

    adminid = id;
    ui->User->setText("当前管理员:" + adminid);
    ui->BookTable->Book::username = adminid;
    ui->Insert->InsertBook::cno = id;
    ui->Return->ReturnBook::username = adminid;
}

AdminInterface::~AdminInterface()
{
    delete ui;
}

void AdminInterface::on_Exit_triggered()
{
    QCoreApplication::exit();
}

