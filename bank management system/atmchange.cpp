#include "atmchange.h"
#include "ui_atmchange.h"

atmchange::atmchange(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::atmchange)
{
    ui->setupUi(this);
}

atmchange::~atmchange()
{
    delete ui;
}
