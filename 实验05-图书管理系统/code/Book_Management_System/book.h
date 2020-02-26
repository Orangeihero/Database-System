#ifndef BOOK_H
#define BOOK_H

#include <QWidget>
#include <QDialog>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

extern QSqlDatabase db;
extern QSqlQuery bookQuery;
extern QSqlQuery adminQuery;
extern QSqlQuery borrowQuery;
extern QSqlQuery cardQuery;

namespace Ui {
class Book;
}

class Book : public QWidget
{
    Q_OBJECT

public:
    explicit Book(QWidget *parent = nullptr);
    Ui::Book *ui;
    QString username;
    ~Book();

private slots:

    void on_BookSearchPushButton_clicked();//查询图书操作
    void on_AllBookPushButton_clicked();//查询所有图书
    void on_BorrowPushButton_clicked();//借书
    void on_RefreshPushButton_clicked();//刷新
private:
    //根据中国图书馆图书分类法，将图书分为22类+题目中要求的三类
    QString catagory[26] =
        {"","马列主义毛邓思想","哲学","社会科学总论","政治法律","军事",
        "经济","文化科学教育体育","语言文字","文学","艺术",
        "历史地理","自然科学总论","数理科学和化学","天文学地球科学",
         "生物科学","医药卫生","农业科学","工业技术","交通运输","航空航天",
        "环境科学安全科学","综合性图书","计算机","教育","英语"};

};

#endif // BOOK_H
