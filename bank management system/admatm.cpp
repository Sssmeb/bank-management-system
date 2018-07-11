#include "admatm.h"
#include "ui_admatm.h"
#include "admsearch.h"
#include<QDebug>
#include<QString>
#include<time.h>
#include <typeinfo.h>
#include<QMessageBox>
#include<QFile>
#include<QTextStream>
#include<QIODevice>

admatm::admatm(QString adm_name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admatm)
{
    ui->setupUi(this);
    this->adm_name=adm_name;
    int ret=readFromFile();
    if(ret==-1)
    {
        QMessageBox::critical(this,"打开错误！","系统开小差~请重试！","确定");
        this->close();
    }
}

admatm::~admatm()
{
    delete ui;
}

int admatm::readFromFile()
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

void admatm::on_atm_cancel_clicked()
{
    this->ui->atm_money->clear();
    this->close();
}

void admatm::on_atm_ok_clicked()
{
    int index = this->ui->atm_type->currentIndex();
    QString money = this->ui->atm_money->text();
    doAtm(index,money);
}
void admatm::getUserData(QStringList user)
{
    userData = user;
}

void admatm::doAtm(int index, QString money)
{
//    bool ok;
//    int userMoney = userData.at(5).toInt(&ok,10);
//    //qDebug()<<userMoney;
//    int atm_money = money.toInt(&ok,10);
//    QString rst_money;
//    if(index==0){
//        rst_money = QString::number(userMoney+atm_money);
//    }
//    else if(index==1){
//        rst_money = QString::number(userMoney-atm_money);
//    }
//    QString newdata=userData.at(0)+" "+userData.at(1)+" "+userData.at(2)+" "+userData.at(3)+" "+userData.at(4)+" "+rst_money;
//    qDebug()<<newdata;
//    //writeToFile(newdata);
//    this->close();
//    record(index,money);
//    //此处还有一个代码要实现在search界面中改变原来money的值
    QString atm_type;
    bool ok;
    if(index==0) atm_type = "存款";
    else if(index==1) atm_type = "取款";
    int userMoney = userData.at(5).toInt(&ok,10);
    int atm_money = money.toInt(&ok,10);
    QString content="是否对客户："+userData.at(1)+'\n'+atm_type+" : "+money;
    int ret= QMessageBox::question(this,"请确认信息！",content,"确认","取消");
    if(ret==0)
    {
        record(index,money);
        QFile file("user.txt");
        if(file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            if(index==0){
                this->userData.replace(5,QString::number(userMoney+atm_money));
            }
            else if(index==1){
                if(userMoney-atm_money<0)
                {
                    QMessageBox::critical(this,"取款失败！","余额不足！请重试！","确定");
                    this->userData.replace(5,QString::number(userMoney));
                }
                this->userData.replace(5,QString::number(userMoney-atm_money));
            }
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

QString admatm::getRst()
{
    return userData.at(5);
}

void admatm::record(int index,QString money)
{
    time_t timeSec=time (NULL);	 //获取1970.1.1至当前秒数time_t
    struct tm * timeinfo= localtime ( &timeSec );//创建TimeDate,并转化为当地时间，
    QString name = userData.at(1);
    QString atm_type;
    if(index==0) atm_type = "存款";
    else if(index==1) atm_type = "取款";

    QString atm_money = money;
    QString time1 = asctime (timeinfo);
    QString time = time1.remove(QChar('\n'),Qt::CaseInsensitive).replace(" ","-");
    QString log=name+" "+time+" "+atm_type+" "+atm_money+" "+adm_name+"\n";
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
