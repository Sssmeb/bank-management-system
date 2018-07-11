#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    this->au.show();
}

void MainWindow::on_action_4_triggered()
{
    this->au.show();
}

void MainWindow::on_pushButton_clicked()
{
    this->al.show();
}

void MainWindow::on_action_triggered()
{
    this->al.show();
}

void MainWindow::on_pushButton_2_clicked()
{
    this->ul.show();
}

void MainWindow::on_action_3_triggered()
{
    this->ul.show();
}
