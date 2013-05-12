#include "databasecr.h"
#include "ui_databasecr.h"

DatabaseCr::DatabaseCr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatabaseCr)
{
    ui->setupUi(this);
}

DatabaseCr::~DatabaseCr()
{
    delete ui;
}

void DatabaseCr::on_pushButton_clicked()
{

}
