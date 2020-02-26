#include "book.h"
#include "ui_Book.h"
#include <QStringList>
#include <QMessageBox>
#include <QDate>
#include <QDebug>

Book::Book(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Book)
{
    ui->setupUi(this);

    QStringList list;//添加图书类别
    for(int i = 0; i < 26; i++)
        list.append(catagory[i]);
    ui->BookCategory->addItems(list);

}

Book::~Book()
{
    delete ui;
}


void Book::on_BookSearchPushButton_clicked()
{
    int condition = 0;//有无已知条件

    //复合查询条件
    QString bookcategory = ui->BookCategory->currentText();

    QString booktitle = ui->BookTitle->text();

    QString bookpress = ui->BookPress->text();

    QString upperyear = ui->BookUpperYear->text();
    QString loweryear = ui->BookLowerYear->text();
    int lower_year = ui->BookLowerYear->value();
    int upper_year = ui->BookUpperYear->value();

    QString bookauthor = ui->BookAuthor->text();

    QString upperprice = ui->BookUpperPrice->text();
    QString lowerprice = ui->BookLowerPrice->text();
    QString query = "select * from book ";

    //开始查询
    if(lower_year>upper_year && lower_year>0 && upper_year>0){
        QMessageBox::warning(nullptr, tr("年份错误"), tr("年份输入有误"));
        return;
    }
    if(lowerprice.toDouble()>upperprice.toDouble() && lowerprice.toDouble()>0  && upperprice.toDouble()>0){
        QMessageBox::warning(nullptr, tr("价格错误"), tr("价格输入有误"));
        return;
    }


    if(QString::compare(bookcategory, ""))
    {
            query.append("where category = '" + bookcategory + "' ");
            condition = 1;
    }

    if(QString::compare(booktitle, ""))
    {
        if(condition == 0){
            query.append("where title like '%" + booktitle + "%' ");//涵盖其中字眼即可，不需要书名和书一一对应
            condition = 1;
        }
        else
            query.append("and title like '%" + booktitle + "%' ");
    }

    if(QString::compare(bookpress, ""))
    {
        if(condition == 0)
        {
            query.append("where press like '%" + bookpress + "%' ");
            condition = 1;
        }
        else
            query.append("and press like '%" + bookpress + "%' ");
    }

    if(QString::compare(bookauthor, ""))
    {
        if(condition == 0)
        {
            query.append("where author like '%" + bookauthor + "%' ");
            condition = 1;
        }
        else
            query.append("and author like '%" + bookauthor + "%' ");
    }


    if(lower_year >= 0 && upper_year >= 0 &&lower_year <= upper_year)
    {
        if(condition == 0)
        {
            query.append("where year <= '" + upperyear +
                         "' and year >= '" + loweryear + "'");
            condition = 1;
        }
        else
            query.append("and year <= '" + upperyear +
                         "' and year >= '" + loweryear + "'");
    }

    if(lowerprice.toDouble() >= 0 && upperprice.toDouble() >= 0 &&lowerprice.toDouble() <= lowerprice.toDouble())
    {
        if(condition == 0)
        {
            query.append("where price between '" + upperprice +
                         "' and '" + lowerprice + "'");
            condition = 1;
        }
        else
            query.append("and price <= '" + upperprice +
                         "' and price >= '" + lowerprice + "'");
    }

    QSqlQuery temp = QSqlQuery(db);
    ui->BookTable->clearContents();
    bookQuery.exec(query);

    int row = 0;
    ui->BookTable->setRowCount(bookQuery.size());
    while(bookQuery.next())
    {
        temp.exec("select * from book where bno = '"
        + bookQuery.value(0).toString() + "'");
        temp.next();
        for(int i = 0; i < 9; i++)
        {
            if(i == 6){
                float b=temp.value(i).toFloat();
                ui->BookTable->setItem(row, i, new QTableWidgetItem(QString::number(b,'f',2)));
            }
            else{
                ui->BookTable->setItem(row, i, new QTableWidgetItem(temp.value(i).toString()));
            }
        }

        row++;
    }
    ui->BookTable->show();
}


void Book::on_AllBookPushButton_clicked()
{
    QSqlQuery temp = QSqlQuery(db);
    ui->BookTable->clearContents();
    bookQuery.exec("select * from book");

    int row = 0;
    ui->BookTable->setRowCount(bookQuery.size());
    while(bookQuery.next())
    {
        temp.exec("select * from book where bno = '"
        + bookQuery.value(0).toString() + "'");
        temp.next();
        for(int i = 0; i < 9; i++)
        {
            if(i == 6){
                float b=temp.value(i).toFloat();
                ui->BookTable->setItem(row, i, new QTableWidgetItem(QString::number(b,'f',2)));
            }
            else{
                ui->BookTable->setItem(row, i, new QTableWidgetItem(temp.value(i).toString()));
            }
        }
        row++;
    }
    ui->BookTable->show();
}

void Book::on_RefreshPushButton_clicked()
{
    QSqlQuery temp = QSqlQuery(db);
    ui->BookTable->clearContents();
    bookQuery.exec("select * from book");

    int row = 0;
    ui->BookTable->setRowCount(bookQuery.size());
    while(bookQuery.next())
    {
        temp.exec("select * from book where bno = '"
        + bookQuery.value(0).toString() + "'");
        temp.next();
        for(int i = 0; i < 9; i++)
        {
            if(i == 6){
                float b=temp.value(i).toFloat();
                ui->BookTable->setItem(row, i, new QTableWidgetItem(QString::number(b,'f',2)));
            }
            else{
                ui->BookTable->setItem(row, i, new QTableWidgetItem(temp.value(i).toString()));
            }
        }
        row++;
    }
    ui->BookTable->show();
}


void Book::on_BorrowPushButton_clicked()
{
    adminQuery.exec("select ID from admin where ID = '"
                    + username + "'");

    if(!adminQuery.isActive())
    {
        QMessageBox::warning(nullptr, "错误", "出现错误");
        return;
    }

    if(!adminQuery.next())//只有管理员可以操作借书
    {
        QMessageBox::warning(nullptr, "无借书权限", "您无借书权限！");
        return;
    }
    else //有权限
    {
        QString borrower = ui->BorrowName->text();
        borrowQuery.exec("select bno from borrow where cno = '"
                       + username + "'");
        if(!borrowQuery.isActive())
        {
            QMessageBox::warning(nullptr, "内部错误", "出现内部错误！");
            return;
        }
        if(borrowQuery.size() >= 12) //根据浙江大学图书馆管理规定，超过12本就不再能借书了
        {
            QMessageBox::warning(nullptr, "借书书目超量", "您最多只能借12本书！");
            return;
        }
        else //借书
        {
            int number;
            QList<QTableWidgetItem*> list = ui->BookTable->selectedItems();
            if(list.isEmpty())
            {
                QMessageBox::warning(nullptr, "未选择任何项目", "请选择您要借阅的书！");
                return;
            }
            QString bookbno = list.at(0)->text();
            QDate d = QDate::currentDate();
            QString date = d.toString("yyyy-MM-dd");

            bookQuery.exec("select stock from book where bno = '"
                           + bookbno + "'");
            if(!bookQuery.isActive())
            {
                QMessageBox::warning(nullptr, "内部错误", "出现内部错误！");
                return;
            }
            if(bookQuery.next())
            {
                number = bookQuery.value(0).toInt();
                if(number == 0)
                {
                    QMessageBox::warning(nullptr, "库存不足", "库存不足,无法借书！");
                    return;
                }
                else
                {
                    borrowQuery.exec("insert into borrow values ('"
                                   + borrower + "','"
                                   + bookbno + "','"
                                   + username + "','"
                                   + date + "',"
                                   + "null)");

                    if(borrowQuery.isActive())
                    {
                        bookQuery.exec("update book set "
                                       "stock = stock - 1 where bno = '"
                                        + bookbno + "'");

                        QMessageBox::information(nullptr, "借书成功", "借书成功！");
                        on_BookSearchPushButton_clicked();
                    }
                    else
                    {
                        QMessageBox::warning(0, "内部错误", "借书失败！");
                        return;
                    }
                }
            }
        }
    }
}
















