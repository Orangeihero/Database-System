#include "userInterface.h"
#include "ui_UserInterface.h"

UserInterface::UserInterface(QWidget *parent,QString scno) :
    QMainWindow(parent),
    ui(new Ui::UserInterface)
{
    ui->setupUi(this);

    cno = scno;
    ui->User->setText("当前用户:" + cno);
    ui->BookTable->Book::username = cno;//借了什么书
}

UserInterface::~UserInterface()
{
    delete ui;
}
 void UserInterface::on_ExitAction_triggered()
 {
     QCoreApplication::exit();
 }

