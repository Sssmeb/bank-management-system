#include "admmain.h"
#include "ui_admmain.h"
#include<QMessageBox>
#include<QList>
#include<QStringList>
#include<QDebug>

admmain::admmain(QString adm_name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admmain)
{
    ui->setupUi(this);
    this->adm_name=adm_name;
    int ret=readFromFile();
    if(ret==-1)
    {
        QMessageBox::critical(this,"打开错误！","文件打开失败！请重试！","确定");
        this->close();
    }
    else{
        this->model = new QStandardItemModel;
        this->model->setHorizontalHeaderItem(0,new QStandardItem("编号"));
        this->model->setHorizontalHeaderItem(1,new QStandardItem("姓名"));
        this->model->setHorizontalHeaderItem(2,new QStandardItem("密码"));
        this->model->setHorizontalHeaderItem(3,new QStandardItem("地址"));
        this->model->setHorizontalHeaderItem(4,new QStandardItem("电话"));
        this->model->setHorizontalHeaderItem(5,new QStandardItem("总金额"));

        this->ui->tableView->setModel(model);      
        this->ui->tableView->verticalHeader()->hide();
        display();
    }
}

admmain::~admmain()
{
    delete ui;
}

void admmain::display()
{
    this->model->removeRows(0,model->rowCount());
    this->ui->tableView->setModel(model);
    //qDebug()<<user_lines;
    for(int i=0;i<(user_lines.length());i++)
    {
        //qDebug()<<i;
        QString line =user_lines.at(i);
        line=line.trimmed();
        QStringList subs=line.split(" ");
        for(int j=0;j<subs.length();j++)
        {
            //qDebug()<<j;
            this->model->setItem(i,j,new QStandardItem(subs.at(j)));
        }
    }
}

int admmain::readFromFile()
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

void admmain::on_btn_exit_clicked()
{
    int ret=QMessageBox::critical(this,"确认退出？","是否退出管理员登陆","确定","取消");
    if(ret==0)
    {
        this->close();
    }
}

void admmain::on_btn_search_clicked()
{
    QString cnt=this->ui->le_cnt->text();
    this->ui->le_cnt->clear();
    dosearch(cnt);
    //qDebug()<<"close";
    display();
    //qDebug()<<"display";
}

void admmain::dosearch(QString cnt)
{
    admsearch as(adm_name);
    int i=0;
    for(i=0;i<user_lines.length();i++)
    {
        QString line =user_lines.at(i);
        line=line.trimmed();
        this->users=line.split(" ");
        if(users.at(1)==cnt)
        {
            as.showuser(users);
            as.exec();
            this->user_lines=as.retUserLines();
            break;
        }
        if(i==user_lines.length()-1)
        {
            QMessageBox::critical(this,"匹配失败！","查找不到对应用户！","确定");
        }
    }
}

void admmain::on_btn_record_clicked()
{
    admrecord adr;
    adr.exec();
}
