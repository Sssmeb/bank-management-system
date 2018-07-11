#include "admrecord.h"
#include "ui_admrecord.h"
#include<QMessageBox>
#include<QFile>
#include<QDebug>
#include<QTextStream>

admrecord::admrecord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::admrecord)
{
    ui->setupUi(this);
    int ret=readToFile();
    if(ret==-1)
    {
        QMessageBox::critical(this,"打开错误！","文件打开失败！请重试！","确定");
        this->close();
    }
    else{
        this->model = new QStandardItemModel;
        this->model->setHorizontalHeaderItem(0,new QStandardItem("用户名"));
        this->model->setHorizontalHeaderItem(1,new QStandardItem("操作时间"));
        this->model->setHorizontalHeaderItem(2,new QStandardItem("操作类型"));
        this->model->setHorizontalHeaderItem(3,new QStandardItem("操作金额"));
        this->model->setHorizontalHeaderItem(4,new QStandardItem("管理员操作"));

        this->ui->record_msg->setModel(model);
        this->ui->record_msg->verticalHeader()->hide();
        display();
    }
}

admrecord::~admrecord()
{
    delete ui;
}

void admrecord::on_btn_cancel_clicked()
{
    int ret=QMessageBox::critical(this,"确认退出？","是否退出交易记录查询","确定","取消");
    if(ret==0){
        this->close();
    }
}

void admrecord::on_btn_search_clicked()
{
    int index = this->ui->info_type->currentIndex();
    QString info = this->ui->le_info->text();
    this->ui->le_info->clear();
    if(index==0){
        dosearch(0,info);
    }
    else if(index==1){
        dosearch(4,info);
    }
    else if(index==2){
        dosearch(2,info);
    }
    display();
}

int admrecord::readToFile()
{
    QFile file("record.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return -1;
    }
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line =in.readLine();
        record_lines.append(line);
    }
    //qDebug()<<record_lines.length();
    file.close();
    return 0;
}

void admrecord::display()
{
    for(int i=0;i<(record_lines.length());i++)
    {
        QString line =record_lines.at(i);
        line=line.trimmed();
        QStringList subs=line.split(" ");
        for(int j=0;j<subs.length();j++)
        {
            this->model->setItem(i,j,new QStandardItem(subs.at(j)));
        }
    }
}

void admrecord::dosearch(int i, QString info)
{
    QList<QString> rst_records;
    int j=0;
    for(j=0;j<record_lines.length();j++)
    {
        QString line =record_lines.at(j);
        line=line.trimmed();
        this->record=line.split(" ");
        if(record.at(i)==info)
        {
            rst_records.append(line);
        }
    }
    if(rst_records.length()==0)
    {
        QMessageBox::critical(this,"匹配失败！","输入错误或记录不存在","确定");
        return;
    }
    recordinfo rei(rst_records);
    rei.exec();

}
