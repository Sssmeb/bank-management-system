#ifndef ADDUSER_H
#define ADDUSER_H

#include <QDialog>
#include<QString>

namespace Ui {
class adduser;
}

class adduser : public QDialog
{
    Q_OBJECT

public:
    explicit adduser(QWidget *parent = 0);
    ~adduser();
    void clearUserInterface();
    QString getUserCount();
    void writeToFile(QString cnt);

private slots:

    void on_btn_ok_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::adduser *ui;
    QList<QString>user_lines;
};

#endif // ADDUSER_H
