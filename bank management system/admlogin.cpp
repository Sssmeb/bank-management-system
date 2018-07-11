#include "admlogin.h"
#include "ui_admlogin.h"
#include"admmain.h"
#include<QString>
#include<QMessageBox>
#include<QFile>
#include<QTextStream>
#include<QIODevice>

admlogin::admlogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admlogin)
{
    ui->setupUi(this);
}

admlogin::~admlogin()
{
    delete ui;
}

void admlogin::on_btn_ok_clicked()
{
    QString account=this->ui->le_account->text();
    QString password=this->ui->le_password->text();
    if((account=="曹润佳"&&password=="123123")||(account=="曾东方"&&password=="123123")||(account=="陈天润"&&password=="123123")||(account=="黄永慧"&&password=="123123"))
    {
        this->ui->le_account->clear();
        this->ui->le_password->clear();
        this->close();
        admmain am(account);
        am.exec();
    }
    else
    {
        this->ui->le_account->clear();
        this->ui->le_password->clear();
        QMessageBox::critical(this,"错误","您输入的账号或秘密错误！请检查","确定");
    }
}

void admlogin::on_btn_cancel_clicked()
{
    this->close();
}
