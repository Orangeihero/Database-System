#include "insertbook.h"
#include "ui_InsertBook.h"
#include <QMessageBox>
#include <QDate>
#include<QFile>
#include<QDebug>
#include <QTextCodec>

InsertBook::InsertBook(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InsertBook)
{
    ui->setupUi(this);

    for(int i = 0; i < 26; i++)
        ui->bookcategory->addItem(catagory[i]);
}

InsertBook::~InsertBook()
{
    delete ui;
}

void InsertBook::on_InsertPushButton_clicked()
{
    //插入的书籍信息
    QString bookbno = ui->bookbno->text();
    QString bookcategory = ui->bookcategory->currentText();
    QString booktitle = ui->booktitle->text();
    QString bookpress = ui->bookpress->text();
    QString bookyear = ui->bookyear->text();
    QString bookauthor = ui->bookauthor->text();
    QString bookprice = ui->bookprice->text();
    QString booktotal = ui->booktotal->text();


    if(QString::compare(bookcategory, "") == 0 ||
            QString::compare(bookbno, "") == 0||
            QString::compare(booktitle, "") == 0||
            QString::compare(bookpress, "") == 0||
            QString::compare(bookyear, "") == 0||
            QString::compare(bookauthor, "") == 0||
            QString::compare(bookprice, "") == 0||
            QString::compare(booktotal, "") == 0){

            QMessageBox::warning(nullptr, "输入信息不完整", "请输入完整且恰当的信息！");
            return;
    }

    bookQuery.exec("select * from book where title = '" + booktitle + "' "
                   + "and press = '" + bookpress + "' "
                   + "and category = '" + bookcategory + "' "
                   + "and bno = '" + bookbno + "' "
                   + "and year = '" + bookyear + "' "
                   + "AND author = '" + bookauthor + "' "
                   + "AND price = '" + bookprice + "' ");

    if(!bookQuery.isActive())
    {
        QMessageBox::warning(nullptr, "错误", "查询错误");
        return;
    }

    if(bookQuery.next())
    {
        bookQuery.exec("update book set total = total + '" + booktotal +
                       "' where bno = '" + bookbno + "'");
        bookQuery.exec("update book set stock = stock + '" + booktotal +
                       "' where bno = '" + bookbno + "'");
        QMessageBox::information(nullptr, "书目被合并", "书目: " + booktitle + " 已被合并到已有条目！");
    }
    else
    {
        bookQuery.exec("insert into book values("
                        "'" + bookbno + "',"
                       "'" + bookcategory + "',"
                       "'" + booktitle + "',"
                       "'" + bookpress + "',"
                       "'" + bookyear + "',"
                       "'" + bookauthor + "',"
                       "'" + bookprice + "',"
                       "'" + booktotal + "',"
                        "'" + booktotal + "')");
        if(bookQuery.isActive())
            QMessageBox::information(nullptr, "成功", "书目: " + booktitle + " 已被输入至数据库！");
    }

}

void InsertBook::on_BatchInsertPushButton_clicked()
{
    QFile file("D:\\QTproject\\final\\data.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
    }
    while(!file.atEnd()) {
        QByteArray line = file.readLine();
        QTextCodec *codec=QTextCodec::codecForName("GB2312");

        QString l=codec->toUnicode(line);
        QString booktotal = l.section(',',7,7);
        QString bookbno = l.section(',',0,0);
        bookbno = bookbno.mid(1,4);
        QString bookstock = l.section(',',8,8);
                bookQuery.exec("select * from book where bno = '" + bookbno + "' ");

                if(!bookQuery.isActive())
                {
                    QMessageBox::warning(nullptr, "错误", "查询错误");
                    return;
                }

                if(bookQuery.next())
                {
                    bookQuery.exec("update book set total = total + '" + booktotal +
                                   "' where bno = '" + bookbno + "'");
                    bookQuery.exec("update book set stock = stock + '" + bookstock +
                                   "' where bno = '" + bookbno + "'");
                    QMessageBox::information(nullptr, "书目被合并", "书目已被合并到已有条目！");
                }
                else{
                                     bookQuery.exec("insert into book values(" + l + ")");
                                     if(!bookQuery.isActive()){
                                         QMessageBox::warning(nullptr, "错误", "错误");
                                         return;
                                     }
                                     else{
                                         QMessageBox::information(nullptr,"插入成功","插入成功");
                                     }
                }

    }
}
