#ifndef ADMRECORD_H
#define ADMRECORD_H

#include <QDialog>
#include<QString>
#include<QList>
#include<QStandardItem>
#include<QStandardItemModel>
#include<QStringList>
#include"recordinfo.h"

namespace Ui {
class admrecord;
}

class admrecord : public QDialog
{
    Q_OBJECT

public:
    explicit admrecord(QWidget *parent = 0);
    ~admrecord();
    void display();
    int readToFile();
    void dosearch(int i,QString info);

private slots:
    void on_btn_cancel_clicked();

    void on_btn_search_clicked();

private:
    Ui::admrecord *ui;
    QList<QString> record_lines;
    QStringList record;
    QStandardItemModel * model;
};

#endif // ADMRECORD_H
