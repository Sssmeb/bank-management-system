#include "userlogin.h"
#include "ui_userlogin.h"
#include"usermain.h"
#include<QString>
#include<QMessageBox>
#include<QFile>
#include<QTextStream>
#include<QIODevice>

userlogin::userlogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userlogin)
{
    ui->setupUi(this);
}

userlogin::~userlogin()
{
    delete ui;
}

void userlogin::on_btm_ok_clicked()
{
    QString account=this->ui->le_account->text();
    QString password=this->ui->le_password->text();
    int code = try_login(account,password);
        usermain um(account);
        switch (code) {
        case 1:
            this->ui->le_account->clear();
            this->ui->le_password->clear();
            this->close();
            um.exec();
            break;
        case 0:
            QMessageBox::critical(this,"登录失败","密码或用户名输入有误","确认");
            this->ui->le_password->clear();
            break;
        case -1:
            QMessageBox::critical(this,"发生错误","用户信息文件打开失败","确认");
            break;
        default:
            break;
        }

}

void userlogin::on_btn_cancel_clicked()
{
     this->ui->le_account->clear();
     this->close();
}

int userlogin::try_login(QString account,QString password)
{
    QFile file("user.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        return -1;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line =in.readLine();
        user_lines.append(line);
    }
    file.close();
    for(int i=0;i<user_lines.length();i++)
    {
        QString line =user_lines.at(i);
        line=line.trimmed();
        QStringList users=line.split(" ");
        if(users.at(1)==account&&users.at(2)==password)
            return 1;
    }
    return 0;
}
