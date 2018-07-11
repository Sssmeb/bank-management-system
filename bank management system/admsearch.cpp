#include "admsearch.h"
#include "admatm.h"
#include "ui_admsearch.h"
#include<QStringList>
#include<QString>
#include<QDebug>
#include<QMessageBox>
#include<qfile.h>

admsearch::admsearch(QString adm_name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admsearch)
{
    ui->setupUi(this);
    this->adm_name=adm_name;
    int ret=readFromFile();
    if(ret==-1)
    {
        QMessageBox::critical(this,"打开错误！","文件打开失败！请重试！","确定");
        this->close();
    }
}

admsearch::~admsearch()
{
    delete ui;
}

void admsearch::showuser(QStringList users)
{
    this->user = users;
    this->ui->le_num->setText(user.at(0));
    this->ui->le_name->setText(user.at(1));
    this->ui->le_password->setText(user.at(2));
    this->ui->le_address->setText(user.at(3));
    this->ui->le_phone->setText(user.at(4));
    this->ui->le_money->setText(user.at(5));
}

void admsearch::on_pushButton_2_clicked()
{
    this->close();
}

void admsearch::on_pushButton_3_clicked()
{
   toAtm(user);
}

void admsearch::toAtm(QStringList user)
{
    QString rst_money;
    admatm atm(adm_name);
    //qDebug()<<user.at(5);
    atm.getUserData(user);
    atm.exec();
    rst_money=atm.getRst();
    //QString newUserData=user.at(0)+" "+user.at(1)+" "+user.at(2)+" "+user.at(3)+" "+user.at(4)+" "+rst_money;
    //user = newUserData.split(" ");
    this->user.replace(5,rst_money);
    //qDebug()<<rst_money<<this->user.at(5);
    this->ui->le_money->setText(rst_money);
}

int admsearch::readFromFile()
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
    //qDebug()<<user_lines.length();
    file.close();
    return 0;
}

void admsearch::on_admuser_change_clicked()
{
    QString new_passward = this->ui->le_password->text();
    QString new_address = this->ui->le_address->text();
    QString new_phone = this->ui->le_phone->text();
    QString content = "是否对用户"+user.at(1)+"修改以下信息"+":"+'\n'+"新密码:"+new_passward+'\n'+"新地址:"+new_address+'\n'+"新电话:"+new_phone;
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
    }
    //this->close();
}

QList<QString> admsearch::retUserLines()
{
    this->user_lines.clear();
    int ret=readFromFile();
    if(ret==-1)
    {
        QMessageBox::critical(this,"打开错误！","文件打开失败！请重试！","确定");
        this->close();
    }
    return user_lines;
}

void admsearch::on_btn_cancel_clicked()
{
    QString name = this->ui->le_name->text();
    int ret= QMessageBox::critical(this,"注销客户","是否注销客户："+name,"确认","取消");
    if(ret==0)
    {
        QFile file("user.txt");
        if(file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QTextStream out(&file);
            for(int i=0;i<(user_lines.length());i++)
            {
                QString line =user_lines.at(i);
                line=line.trimmed();
                QStringList subs=line.split(" ");
                if(subs.at(1)==name)
                {
                   continue;
                }
                 else
                 {

                     out<<line<<'\n';
                 }
            }
            file.close();
            this->close();
        }
        else
        {
            QMessageBox::critical(this,"错误","操作失败，请重试","确定");
        }
    }
}
