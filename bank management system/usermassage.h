#ifndef USERMASSAGE_H
#define USERMASSAGE_H

#include <QDialog>
#include<QStringList>
#include<QString>

namespace Ui {
class usermassage;
}

class usermassage : public QDialog
{
    Q_OBJECT

public:
    explicit usermassage(QWidget *parent = 0);
    ~usermassage();
    void showmassage(QStringList users);
    //void getUserData(QStringList user);
    int readFromFile();
    QStringList retUser();

private slots:
    void on_btn_ok_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::usermassage *ui;
    QList<QString> user_lines;
    QStringList user;
    //QStringList userData;
};

#endif // USERMASSAGE_H
