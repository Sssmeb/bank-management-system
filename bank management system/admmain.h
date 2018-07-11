#ifndef ADMMAIN_H
#define ADMMAIN_H
#include"admsearch.h"
#include"admrecord.h"
#include<QList>
#include <QDialog>
#include<QStandardItem>
#include<QStandardItemModel>
#include<QTableWidget>
namespace Ui {
class admmain;
}

class admmain : public QDialog
{
    Q_OBJECT

public:
    explicit admmain(QString adm_name,QWidget *parent = 0);
    ~admmain();
    void dosearch(QString cnt);
    void display();
    int readFromFile();

private slots:
    void on_btn_exit_clicked();

    void on_btn_search_clicked();

    void on_btn_record_clicked();

private:
    Ui::admmain *ui;
    //admsearch as;
    QString adm_name;
    QList<QString>user_lines;
    QStringList users;
    QStandardItemModel * model;
};

#endif // ADMMAIN_H
