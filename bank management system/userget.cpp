#include "userget.h"
#include "ui_userget.h"
#include<QDebug>
#include<QString>
#include<time.h>
#include <typeinfo.h>
#include<QMessageBox>
#include<QFile>
#include<QTextStream>
#include<QIODevice>

userget::userget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userget)
{
    ui->setupUi(this);
    int ret=readFromFile();
    if(ret==-1)
    {
        QMessageBox::critical(this,"打开错误！","系统开小差~请重试！","确定");
        this->close();
    }
}

userget::~userget()
{
    delete ui;
}

int userget::readFromFile()
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

void userget::on_userget_cancel_clicked()
{
    this->ui->userget_money->clear();
    this->close();
}

void userget::getUserData(QStringList user)
{
    userData = user;
}

void userget::on_userget_ok_clicked()
{
    QString money = this->ui->userget_money->text();
    doUserget(money);
}


void userget::doUserget(QString money)
{
    bool ok;
    int userMoney = userData.at(5).toInt(&ok,10);
    int userget_money = money.toInt(&ok,10);
    QString content="是否取款：" + money;
    int ret= QMessageBox::question(this,"请确认信息！",content,"确认","取消");
    if(ret==0)
    {
        record(money);
        if(userMoney-userget_money<0)
        {
            QMessageBox::critical(this,"取款失败！","余额不足！请重试！","确定");
            this->ui->userget_money->clear();
        }
        else{
            QFile file("user.txt");
            if(file.open(QIODevice::WriteOnly|QIODevice::Text))
            {
                this->userData.replace(5,QString::number(userMoney-userget_money));

                QTextStream out(&file);
                for(int i=0;i<(user_lines.length());i++)
                {
                    QString line =user_lines.at(i);
                    line=line.trimmed();
                    QStringList subs=line.split(" ");
                    if(subs.at(1)==userData.at(1))
                    {
                       QString temp=userData.at(0)+" "+userData.at(1)+" "+userData.at(2)+" "+userData.at(3)+" "+userData.at(4)+" "+userData.at(5);
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
                this->close();
            }
            else
            {
                QMessageBox::critical(this,"错误","操作失败，请重试","确定");
            }
        }
    }
}

QString userget::getRst()
{
    return userData.at(5);
}

void userget::record(QString money)
{
    time_t timeSec=time (NULL);	 //获取1970.1.1至当前秒数time_t
    struct tm * timeinfo= localtime ( &timeSec );//创建TimeDate,并转化为当地时间，
    QString name = userData.at(1);
    QString user_type = "取款";

    QString userget_money = money;
    QString time1 = asctime (timeinfo);
    QString time = time1.remove(QChar('\n'),Qt::CaseInsensitive).replace(" ","-");
    QString log=name+" "+time+" "+user_type+" "+userget_money+" 非管理员操作"+"\n";

    QFile file("record.txt");
    if(!file.open(QIODevice::Append|QIODevice::Text))
    {
        QMessageBox::critical(this,"错误","创建失败，请重试","确定");
        return;
    }
    QTextStream out(&file);
    out<<log;
    file.close();
}
