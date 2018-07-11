#include "adduser.h"
#include "ui_adduser.h"
#include<QString>
#include<QMessageBox>
#include<QFile>
#include<QTextStream>
#include<QIODevice>
//#include <QRegExp>

adduser::adduser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adduser)
{
    ui->setupUi(this);
}

adduser::~adduser()
{
    delete ui;
}

void adduser::on_btn_ok_clicked()
{
    QString name=this->ui->le_name->text();
    QString password=this->ui->le_password->text();
    QString password2=this->ui->le_password_2->text();
    QString address=this->ui->le_address->text();
    QString phone=this->ui->le_pnum->text();
//    QMessageBox msgBox;
//    msgBox.setText("姓名： "+name+'\n'+"密码： "+password+'\n'+"地址: "+address+'\n'+"电话："+phone+'\n');
//    msgBox.setInformativeText("是否确定创建?");
//    msgBox.setStandardButtons(QMessageBox::Save  | QMessageBox::Cancel);
//    msgBox.setDefaultButton(QMessageBox::Save);
//    msgBox.addButton("确定",QMessageBox::AcceptRole);
//    msgBox.addButton("取消",QMessageBox::RejectRole);
//    int ret = msgBox.exec();

    QString content="姓名： "+name+'\n'+"地址: "+address+'\n'+"电话："+phone+'\n';
    QString cnt=name+' '+password+' '+address+' '+phone+" 0"+'\n';
    //QRegExp e("^(1)3\d{9}$");
    int pos(0);
    if(name.length()<1||password.length()<6)
    {
        QMessageBox::critical(this,"错误","信息填写不完整，请重新检查","确定");
    }
    else if(password!=password2)
    {
        QMessageBox::critical(this,"错误","密码不匹配，请重新检查","确定");
    }
    /*
    else if(e.)
    {
        QMessageBox::critical(this,"错误","错误的电话号码格式","请重新检查","确定");
    }
    */
    else
    {
        int ret= QMessageBox::question(this,"请确认信息！",content,"确认","取消");
        if(ret==0)
        {
            clearUserInterface();
            writeToFile(cnt);
            this->close();
        }
    }
}

void adduser::clearUserInterface()
{
    this->ui->le_name->clear();
    this->ui->le_address->clear();
    this->ui->le_password->clear();
    this->ui->le_password_2->clear();
    this->ui->le_pnum->clear();
}

QString adduser::getUserCount()
{
    QFile file("user.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return "1";
    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line =in.readLine();
        user_lines.append(line);
    }
    file.close();
    QString user_count;
    int users_count = user_lines.length()-1;
    QString line =user_lines.at(users_count);
    line=line.trimmed();
    QStringList users=line.split(" ");
    bool ok;
    user_count = QString::number(users.at(0).toInt(&ok,10)+1);
    return user_count;
}

void adduser::writeToFile(QString cnt)
{
    QString count = getUserCount();
    QFile file("user.txt");
    if(!file.open(QIODevice::Append|QIODevice::Text))
    {
        QMessageBox::critical(this,"错误","创建失败，请重试","确定");
        return;
    }
    QTextStream out(&file);
    out<<count<<" "<<cnt;
    file.close();

}

void adduser::on_btn_cancel_clicked()
{
    this->close();
}
