#ifndef USERLOGIN_H
#define USERLOGIN_H

#include <QDialog>

namespace Ui {
class userlogin;
}

class userlogin : public QDialog
{
    Q_OBJECT

public:
    explicit userlogin(QWidget *parent = 0);
    int try_login(QString account,QString password);
    ~userlogin();

private slots:
    void on_btn_cancel_clicked();

    void on_btm_ok_clicked();

private:
    Ui::userlogin *ui;
     QList<QString>user_lines;
};

#endif // USERLOGIN_H
