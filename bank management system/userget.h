#ifndef USERGET_H
#define USERGET_H

#include <QDialog>
#include<QStringList>
#include<QString>

namespace Ui {
class userget;
}

class userget : public QDialog
{
    Q_OBJECT

public:
    explicit userget(QWidget *parent = 0);
    ~userget();
    void getUserData(QStringList user);
    void doUserget(QString money);
    void record(QString money);
    int readFromFile();
    QString getRst();

private slots:
    void on_userget_cancel_clicked();


    void on_userget_ok_clicked();

private:
    Ui::userget *ui;
    QStringList userData;
    QList<QString>user_lines;

};

#endif // USERGET_H
