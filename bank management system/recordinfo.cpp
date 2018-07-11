#include "recordinfo.h"
#include "ui_recordinfo.h"

recordinfo::recordinfo(QList<QString> rst_records, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::recordinfo)
{
    ui->setupUi(this);
    this->records =rst_records;
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

recordinfo::~recordinfo()
{
    delete ui;
}

void recordinfo::on_btn_close_clicked()
{
    this->close();
}

void recordinfo::display()
{
    for(int i=0;i<(records.length());i++)
    {
        QString line =records.at(i);
        line=line.trimmed();
        QStringList subs=line.split(" ");
        for(int j=0;j<subs.length();j++)
        {
            this->model->setItem(i,j,new QStandardItem(subs.at(j)));
        }
    }
}
