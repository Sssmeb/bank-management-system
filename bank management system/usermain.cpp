#include "usermain.h"
#include "ui_usermain.h"
#include "userget.h"
#include "usersave.h"
#include "usermassage.h"
#include<QMessageBox>
#include<QFile>
#include<QTextStream>
#include<QString>

usermain::usermain(QString userName,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::usermain)
{
    ui->setupUi(this);
    this->userName=userName;
    int ret=readFromFile();
    if(ret==-1)
    {
        QMessageBox::critical(this,"打开错误！","系统开小差~请重试！","确定");
        this->close();
    }
    this->ui->lineEdit->setText(user.at(5));
}

usermain::~usermain()
{
    delete ui;
}

void usermain::on_btn_exit_clicked()
{
    int ret=QMessageBox::critical(this,"确认退出？","是否退出登陆","确定","取消");
    if(ret==0){
        this->close();
    }
}

void usermain::on_btn_input_clicked()
{
    toSave(user);
    this->ui->lineEdit->setText(user.at(5));
}

void usermain::toSave(QStringList user)
{
    QString rst_money;
    usersave usv;
    usv.getUserData(user);
    usv.exec();
    rst_money=usv.getRst();
    this->user.replace(5,rst_money);
}

void usermain::on_btn_output_clicked()
{
    toGet(user);
    this->ui->lineEdit->setText(user.at(5));
}

void usermain::toGet(QStringList user)
{
    QString rst_money;
    userget ugt;
    ugt.getUserData(user);
    ugt.exec();
    rst_money=ugt.getRst();
    this->user.replace(5,rst_money);
}

void usermain::on_btn_change_clicked()
{
    usermassage umg;
    umg.showmassage(user);
    umg.exec();
    this->user = umg.retUser();

}

int usermain::readFromFile()
{
    QFile file("user.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return -1;
    }
    QList<QString> user_lines;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line =in.readLine();
        user_lines.append(line);
    }
    for(int i=0;i<user_lines.length();i++)
    {
        QString userData = user_lines.at(i);
        userData=userData.trimmed();
        this->user=userData.split(" ");
        if(user.at(1)==userName)
                    break;
    }

    //qDebug()<<user_lines.length();
    file.close();
    return 0;
}
