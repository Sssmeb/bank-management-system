#ifndef ADMLOGIN_H
#define ADMLOGIN_H

#include <QDialog>

namespace Ui {
class admlogin;
}

class admlogin : public QDialog
{
    Q_OBJECT

public:
    explicit admlogin(QWidget *parent = 0);
    ~admlogin();

private slots:

    void on_btn_ok_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::admlogin *ui;
};

#endif // ADMLOGIN_H
