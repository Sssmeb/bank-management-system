#include "usermassage.h"
#include "ui_usermassage.h"
#include<QStringList>
#include<QString>
#include<QDebug>
#include<QMessageBox>
#include<qfile.h>

usermassage::usermassage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::usermassage)
{
    ui->setupUi(this);
    int ret=readFromFile();
    if(ret==-1)
    {
        QMessageBox::critical(this,"打开错误！","系统开小差~请重试！","确定");
        this->close();
    }
}

usermassage::~usermassage()
{
    delete ui;
}

/*void usermassage::getUserData(QStringList user)
{
    userData = user;
}*/

void usermassage::showmassage(QStringList users)
{
    this->user = users;
    this->ui->le_Name->setText(user.at(1));
    this->ui->le_Password->setText(user.at(2));
    this->ui->le_Addr->setText(user.at(3));
    this->ui->le_Tel->setText(user.at(4));
}

void usermassage::on_btn_ok_clicked()
{
    QString new_name = this->ui->le_Name->text();
    QString new_passward = this->ui->le_Password->text();
    QString new_address = this->ui->le_Addr->text();
    QString new_phone = this->ui->le_Tel->text();
    QString content = "尊敬的"+user.at(1)+"是否修改以下信息"+":"+'\n'+"新名字:"+new_name+"\n"+"新密码:"+new_passward+'\n'+"新地址:"+new_address+'\n'+"新电话:"+new_phone;
    int ret= QMessageBox::question(this,"请确认信息！",content,"确认","取消");
    if(ret==0)
    {
        this->user.replace(2,new_passward);
        this->user.replace(3,new_address);
        this->user.replace(4,new_phone);
        QFile file("user.txt");
        if(file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QTextStream out(&file);
            for(int i=0;i<(user_lines.length());i++)
            {
                QString line =user_lines.at(i);
                line=line.trimmed();
                QStringList subs=line.split(" ");
                if(subs.at(1)==user.at(1))
                {
                   QString temp=user.at(0)+" "+user.at(1)+" "+new_passward+" "+new_address+" "+new_phone+" "+user.at(5);
                   temp.replace(0,temp.length(),temp);
                   out<<temp;
                   if(i!=(user_lines.length())-1)
                    {
                     out<<'\n';
                    }
                   continue;
                }
                 else
                 {
                     out<<line<<'\n';
                 }
            }
            file.close();
        }
        else
        {
            QMessageBox::critical(this,"错误","操作失败，请重试","确定");
        }
        this->close();
    }
}



void usermassage::on_btn_cancel_clicked()
{
    this->close();
}

int usermassage::readFromFile()
{
    QFile file("user.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return -1;
    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line =in.readLine();
        user_lines.append(line);
    }
    file.close();
    return 0;
}

QStringList usermassage::retUser()
{
    return user;
}
