#include "register.h"
#include "ui_Register.h"

#include <QDebug>
#include <QMessageBox>
#include <QApplication>

Register::Register(QWidget *parent,UserManage* u) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    Register::usermanage = u;
}


Register::~Register()
{
    delete ui;
}

void Register::on_RegisterPushButton_clicked()
{
    if(ui->RegisterCno->text() == "" || ui->RegisterPassword->text() == ""){
        QMessageBox::warning(nullptr, tr("卡号/密码不能为空"), tr("卡号/密码不能为空"));
    }
    else{
        if(ui->RegisterPassword->text().length() > 16||ui->RegisterPassword->text().length() < 2){
            QMessageBox::warning(nullptr, tr("密码长度问题"), tr("密码长度必须在2-16位之间"));
        }
        else{
            cardQuery.exec("select cno from card where cno = '"
                    + ui->RegisterCno->text() + "'");
            if(cardQuery.next()){
                QMessageBox::warning(nullptr, tr("用户已注册"), tr("您已用该卡号注册过用户"));
            }
            else{
                cardQuery.exec("insert into card values('" +
                               ui->RegisterCno->text() + "','"
                               + ui->RegisterPassword->text() + "','"
                               + ui->RegisterName->text() + "','"
                               + ui->RegisterDepartment->text() + "','"
                               + ui->RegisterType->text()+ "')");
                if(cardQuery.isActive()){
                    QMessageBox::about(nullptr,tr("注册成功"),tr("恭喜您，注册成功！"));
                    close();
                }
                else{
                    QMessageBox::about(nullptr,tr("注册失败"),tr("注册失败"));
                }
            }
        }
    }
}
