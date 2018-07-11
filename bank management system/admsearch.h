#ifndef ADMSEARCH_H
#define ADMSEARCH_H

#include <QDialog>
#include<QStringList>

namespace Ui {
class admsearch;
}

class admsearch : public QDialog
{
    Q_OBJECT

public:
    explicit admsearch(QString adm_name,QWidget *parent = 0);
    ~admsearch();
    void showuser(QStringList users);
    int readFromFile();
    void toAtm(QStringList user);
    QList<QString> retUserLines();//返回更新后的数据到上一级窗口

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_admuser_change_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::admsearch *ui;
    QList<QString> user_lines;
    QStringList user;
    QString adm_name;
};

#endif // ADMSEARCH_H
