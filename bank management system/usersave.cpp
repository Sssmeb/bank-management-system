#include "usersave.h"
#include "ui_usersave.h"
#include<QDebug>
#include<QString>
#include<time.h>
#include <typeinfo.h>
#include<QMessageBox>
#include<QFile>
#include<QTextStream>
#include<QIODevice>

usersave::usersave(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::usersave)
{
    ui->setupUi(this);
    int ret=readFromFile();
    if(ret==-1)
    {
        QMessageBox::critical(this,"打开错误！","系统开小差~请重试！","确定");
        this->close();
    }
}

usersave::~usersave()
{
    delete ui;
}

int usersave::readFromFile()
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

void usersave::on_usersave_cancel_clicked()
{
    this->ui->usersave_money->clear();
    this->close();
}

void usersave::getUserData(QStringList user)
{
    userData = user;
}


void usersave::on_usersave_ok_clicked()
{
    QString money = this->ui->usersave_money->text();
    doUsersave(money);
}

void usersave::doUsersave(QString money)
{
    bool ok;
    int userMoney = userData.at(5).toInt(&ok,10);
    int usersave_money = money.toInt(&ok,10);
    QString content="是否存款：" + money;
    int ret= QMessageBox::question(this,"请确认信息！",content,"确认","取消");
    if(ret==0)
    {
        record(money);
        QFile file("user.txt");
        if(file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            this->userData.replace(5,QString::number(userMoney+usersave_money));

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

QString usersave::getRst()
{
    return userData.at(5);
}

void usersave::record(QString money)
{
    time_t timeSec=time (NULL);	 //获取1970.1.1至当前秒数time_t
    struct tm * timeinfo= localtime ( &timeSec );//创建TimeDate,并转化为当地时间，
    QString name = userData.at(1);
    QString user_type = "存款";

    QString usersave_money = money;
    QString time1 = asctime (timeinfo);
    QString time = time1.remove(QChar('\n'),Qt::CaseInsensitive).replace(" ","-");
    QString log=name+" "+time+" "+user_type+" "+usersave_money+" 非管理员操作"+"\n";
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
