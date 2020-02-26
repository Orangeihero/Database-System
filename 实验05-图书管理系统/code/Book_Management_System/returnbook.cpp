#include "returnbook.h"
#include "ui_returnbook.h"
#include<QMessageBox>
#include<QDate>
#include<QDebug>

ReturnBook::ReturnBook(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReturnBook)
{
    ui->setupUi(this);
}

ReturnBook::~ReturnBook()
{
    delete ui;
}

void ReturnBook::on_ReturnPushButton_clicked()
{
    QList<QTableWidgetItem*> list =  ui->BorrowTable->selectedItems();
    QString returndate = list.at(4)->text();

    if(QString::compare(returndate, ""))
    {
        QMessageBox::warning(nullptr,"错误","用户书目已归还！");
    }
    else{
        QString borrower = list.at(0)->text();
        QString bookbno = list.at(1)->text();
        QString adminid = list.at(5)->text();
        QDate d = QDate::currentDate();
        QString date = d.toString("yyyy-MM-dd");

        borrowQuery.exec("update borrow set "
                       "return_date = '" + date + "'"
                       "where cno = '" + borrower + "' "
                       "and bno = '" + bookbno + "' "
                       "and ID = '" + adminid + "'");

        bookQuery.exec("update book set stock = stock + 1"
                       " where bno = '" + bookbno + "'");
        if(!borrowQuery.isActive()&&!bookQuery.isActive())
        {
            QMessageBox::warning(nullptr, "内部错误", "归还失败！");
        }
        if(bookQuery.isActive()&&borrowQuery.isActive())
            QMessageBox::information(nullptr, "归还成功",  " 归还成功！");
    }
}


void ReturnBook::on_RefreshAllPushButton_clicked()
{
    borrowQuery.exec("select * from borrow");

    QString borrowercno;
    QString bookbno;
    QString adminid;
    QString loandate;
    QString returndate;
    QString booktitle;

    if(!borrowQuery.isActive())
    {
        QMessageBox::warning(nullptr, "内部错误", "查询LOAN表错误！");
    }

    int row = 0;

    ui->BorrowTable->setRowCount(borrowQuery.size());

    while(borrowQuery.next())
    {
        borrowercno = borrowQuery.value(0).toString();
        bookbno = borrowQuery.value(1).toString();
        adminid = borrowQuery.value(2).toString();
        loandate = borrowQuery.value(3).toString();
        returndate = borrowQuery.value(4).toString();

        bookQuery.exec("select title from book where bno = '"
                       + bookbno + "'");
        if(bookQuery.next())
            booktitle = bookQuery.value(0).toString();

        ui->BorrowTable->setItem(row, 0, new QTableWidgetItem(borrowercno));
        ui->BorrowTable->setItem(row, 1, new QTableWidgetItem(bookbno));
        ui->BorrowTable->setItem(row, 2, new QTableWidgetItem(booktitle));
        ui->BorrowTable->setItem(row, 3, new QTableWidgetItem(loandate));
        ui->BorrowTable->setItem(row, 4, new QTableWidgetItem(returndate));
        ui->BorrowTable->setItem(row, 5, new QTableWidgetItem(adminid));
        row++;
    }

}

void ReturnBook::on_RefreshThisPushButton_clicked()
{
    QString borrower = ui->BorrowerCno->text();
    borrowQuery.exec("select cno, bno, ID, borrow_date, return_date from borrow "
                   "where cno = '" + borrower + "'");
    QString borrowercno;
    QString bookbno;
    QString adminid;
    QString loandate;
    QString returndate;
    QString booktitle;

    if(!borrowQuery.isActive())
    {
        QMessageBox::warning(nullptr, "内部错误", "查询LOAN表错误！");
    }

    int row = 0;

    ui->BorrowTable->setRowCount(borrowQuery.size());

    while(borrowQuery.next())
    {
        borrowercno = borrowQuery.value(0).toString();
        bookbno = borrowQuery.value(1).toString();
        adminid = borrowQuery.value(2).toString();
        loandate = borrowQuery.value(3).toString();
        returndate = borrowQuery.value(4).toString();

        bookQuery.exec("select title from book where bno = '"
                       + bookbno + "'");
        if(bookQuery.next())
            booktitle = bookQuery.value(0).toString();

        ui->BorrowTable->setItem(row, 0, new QTableWidgetItem(borrowercno));
        ui->BorrowTable->setItem(row, 1, new QTableWidgetItem(bookbno));
        ui->BorrowTable->setItem(row, 2, new QTableWidgetItem(booktitle));
        ui->BorrowTable->setItem(row, 3, new QTableWidgetItem(loandate));
        ui->BorrowTable->setItem(row, 4, new QTableWidgetItem(returndate));
        ui->BorrowTable->setItem(row, 5, new QTableWidgetItem(adminid));
        row++;
    }
}


