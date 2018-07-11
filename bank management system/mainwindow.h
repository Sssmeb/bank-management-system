#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"adduser.h"
#include"admlogin.h"
#include"userlogin.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_3_clicked();

    void on_action_4_triggered();

    void on_pushButton_clicked();

    void on_action_triggered();

    void on_pushButton_2_clicked();

    void on_action_3_triggered();

private:
    Ui::MainWindow *ui;
    adduser au;
    admlogin al;
    userlogin ul;

};

#endif // MAINWINDOW_H
