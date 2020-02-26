#include "login.h"
#include "ui_login.h"

#include "register.h"
#include "ui_Register.h"

#include "userInterface.h"
#include "ui_UserInterface.h"

#include "Admininterface.h"
#include "ui_admininterface.h"

#include <QMessageBox>

LogIn::LogIn(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);
}

LogIn::~LogIn()
{
    delete ui;
}

void LogIn::on_LogInPushButton_clicked()
{
    if(ui->UserNameContent->text() == "" || ui->PasswordContent->text() == "")//如果输入的用户名为空或者密码为空
        QMessageBox::warning(nullptr,tr("您所输入的用户名/密码为空"),tr("您所输入的用户名/密码为空，请重新输入"));
    else{//用户输入了用户名和密码
        if(ui->IdentityComboBox->currentIndex() == 1){//登录者为管理员
            adminQuery.exec("select password from admin where ID = '"
                            + ui->UserNameContent->text() + "'");
            if(!adminQuery.isActive()) return;
            else{

                if(adminQuery.next()){
                    QString password = adminQuery.value(0).toString();
                    if(QString::compare(password, ui->PasswordContent->text()) != 0)//密码错误
                    {
                        QMessageBox::warning(nullptr, tr("密码错误"), tr("密码错误，请输入正确的密码"));
                        return;
                    }
                }
                else{//ID错误
                    QMessageBox::warning(nullptr, tr("ID错误"), tr("ID错误，请输入正确的ID"));
                    return;
                }
                AdminInterface *ai = new AdminInterface(nullptr, ui->UserNameContent->text());//要传入个人信息
                ai->show();
                close();
            }
        }
        else{//登录者为学生
            cardQuery.exec("select password from card where cno = '"
                                    + ui->UserNameContent->text() + "'");
            if(!cardQuery.isActive()) return;
            else{
                if(cardQuery.next()){
                    QString password = cardQuery.value(0).toString();
                    if(QString::compare(password, ui->PasswordContent->text()) != 0)//密码错误
                    {
                        QMessageBox::warning(nullptr, tr("密码错误"), tr("密码错误，请输入正确密码"));
                        return;
                    }
                }
                else{//卡号错误
                    QMessageBox::warning(nullptr, tr("卡号错误"), tr("卡号错误，请输入正确卡号"));
                    return;
                }

                UserInterface *u = new UserInterface(0, ui->UserNameContent->text());//要传入个人信息
                u->show();
                close();
            }
        }
    }
}
