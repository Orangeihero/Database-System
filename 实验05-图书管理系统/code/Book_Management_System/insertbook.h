#ifndef INSERTBOOK_H
#define INSERTBOOK_H

#include <QWidget>
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

extern QSqlDatabase db;
extern QSqlQuery bookQuery;
extern QSqlQuery borrowQuery;
extern QSqlQuery cardrQuery;

namespace Ui {
class InsertBook;
}

class InsertBook : public QWidget
{
    Q_OBJECT

public:
    explicit InsertBook(QWidget *parent = nullptr);
    ~InsertBook();

    QString cno;

private slots:
    void on_InsertPushButton_clicked();//单本导入
    void on_BatchInsertPushButton_clicked();//批量导入
private:
    Ui::InsertBook *ui;
    QString catagory[26] =
        {"","马列主义毛邓思想","哲学","社会科学总论","政治法律","军事",
        "经济","文化科学教育体育","语言文字","文学","艺术",
        "历史地理","自然科学总论","数理科学和化学","天文学地球科学",
         "生物科学","医药卫生","农业科学","工业技术","交通运输","航空航天",
        "环境科学安全科学","综合性图书","计算机","教育","英语"};
};

#endif // INSERTBOOK_H
