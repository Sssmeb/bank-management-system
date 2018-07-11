#ifndef USERMAIN_H
#define USERMAIN_H

#include <QDialog>
#include<QStringList>

namespace Ui {
class usermain;
}

class usermain : public QDialog
{
    Q_OBJECT

public:
    explicit usermain(QString userName,QWidget *parent = 0);
    int readFromFile();
    void toSave(QStringList money);
    void toGet(QStringList money);
    QList<QString> retUserLines();
    ~usermain();

private slots:
    void on_btn_exit_clicked();

    void on_btn_input_clicked();

    void on_btn_output_clicked();

    void on_btn_change_clicked();

private:
    Ui::usermain *ui;
    QList<QString> user_lines;
    QStringList user;
    QString userName;
};

#endif // USERMAIN_H
