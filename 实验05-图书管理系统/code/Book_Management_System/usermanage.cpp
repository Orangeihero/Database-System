#include "usermanage.h"
#include "ui_usermanage.h"

#include <QMessageBox>
#include <QString>

#include "register.h"
#include "ui_Register.h"

UserManage::UserManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserManage)
{
    ui->setupUi(this);
}

UserManage::~UserManage()
{
    delete ui;
}

void UserManage::on_AddUser_clicked()
{
    Register *r = new Register(nullptr, this);
    r->show();
}

void UserManage::on_RefreshPushButton_clicked()
{
    QSqlQuery temp = QSqlQuery(db);
    ui->UserTable->clearContents();
   cardQuery.exec("select * from card");

    int row = 0;
    ui->UserTable->setRowCount(cardQuery.size());
    while(cardQuery.next())
    {
        temp.exec("select * from card where cno = '"
                  + cardQuery.value(0).toString() + "'");
        temp.next();
        for(int i = 0; i < 5; i++)
        {
            ui->UserTable->setItem(row, i, new QTableWidgetItem(temp.value(i).toString()));
        }
        row++;
    }
    ui->UserTable->show();
}

void UserManage::on_FindPushButton_clicked()
{
    QSqlQuery temp = QSqlQuery(db);
    ui->UserTable->clearContents();
    QString usercno = ui->UserCno->text();
    cardQuery.exec("select * from card where cno = '"
                   + usercno + "'");

    int row = 0;
    ui->UserTable->setRowCount(cardQuery.size());
    while(cardQuery.next())
    {
        temp.exec("select * from card where cno = '"
        + cardQuery.value(0).toString() + "'");
        temp.next();
        for(int i = 0; i < 5; i++)
        {
            ui->UserTable->setItem(row, i, new QTableWidgetItem(temp.value(i).toString()));
        }
        row++;
    }
    ui->UserTable->show();
}

void UserManage::on_DeleteUser_clicked()
{
    QList<QTableWidgetItem*> list =  ui->UserTable->selectedItems();
    QString usercno = list.at(0)->text();
    borrowQuery.exec("select cno from borrow "
                   "where cno = '" + usercno + "' "
                   "and return_date is null");
    if(!borrowQuery.isActive())
    {
        QMessageBox::warning(nullptr, "内部错误", "查询错误！");
    }
    if(borrowQuery.next())
    {
        QMessageBox::warning(nullptr, "无法删除", "该用户仍有书未归还，无法删除");
    }
    else{
        borrowQuery.exec("delete from borrow where cno = '" + usercno + "'");
        if(borrowQuery.isActive()){
             QMessageBox::information(nullptr, "删除成功", "用户 " + usercno + " 的借阅记录已删除");
        }
        else{
            QMessageBox::warning(nullptr, "删除失败", "用户 " + usercno + " 的借阅记录删除失败");
        }
        cardQuery.exec("delete from card where cno = '" + usercno + "'");
        if(cardQuery.isActive()){
             QMessageBox::information(nullptr, "删除成功", "用户： " + usercno + " 已删除");
        }
        else{
            QMessageBox::warning(nullptr, "删除失败", "用户： " + usercno + " 删除失败");
        }
    }
}

