#ifndef RECORDINFO_H
#define RECORDINFO_H

#include <QDialog>
#include<QString>
#include<QList>
#include<QStandardItem>
#include<QStandardItemModel>
#include<QStringList>

namespace Ui {
class recordinfo;
}

class recordinfo : public QDialog
{
    Q_OBJECT

public:
    explicit recordinfo(QList<QString> rst_records,QWidget *parent = 0);
    ~recordinfo();
    void display();

private slots:
    void on_btn_close_clicked();

private:
    Ui::recordinfo *ui;
    QStandardItemModel * model;
    QList<QString> records;
};

#endif // RECORDINFO_H
