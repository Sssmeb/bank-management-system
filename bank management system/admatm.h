#ifndef ADMATM_H
#define ADMATM_H

#include <QDialog>
#include<QStringList>
#include<QString>

namespace Ui {
class admatm;
}

class admatm : public QDialog
{
    Q_OBJECT

public:
    explicit admatm(QString adm_name,QWidget *parent = 0);
    void getUserData(QStringList user);
    void doAtm(int index,QString money);
    void record(int index,QString money);
    int readFromFile();
    QString getRst();
    ~admatm();

private slots:
    void on_atm_cancel_clicked();
    void on_atm_ok_clicked();

private:
    Ui::admatm *ui;
    QStringList userData;
    QList<QString>user_lines;
    QString adm_name;
};

#endif // ADMATM_H
