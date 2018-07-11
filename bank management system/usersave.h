#ifndef USERSAVE_H
#define USERSAVE_H

#include <QDialog>
#include<QStringList>
#include<QString>

namespace Ui {
class usersave;
}

class usersave : public QDialog
{
    Q_OBJECT

public:
    explicit usersave(QWidget *parent = 0);
    ~usersave();
    void getUserData(QStringList user);
    void doUsersave(QString money);
    void record(QString money);
    int readFromFile();
    QString getRst();

private slots:
    void on_usersave_cancel_clicked();

    void on_usersave_ok_clicked();

private:
    Ui::usersave *ui;
    QStringList userData;
    QList<QString>user_lines;
};

#endif // USERSAVE_H
