#include "user_manage.h"
#include "ui_user_manage.h"
#include <QMessageBox>
#include <QString>

User_manage::User_manage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::User_manage)
{
    ui->setupUi(this);
}

User_manage::~User_manage()
{
    delete ui;
}

void U
