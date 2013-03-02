#include "mainform.h"
#include "ui_mainform.h"

mainform::mainform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainform)
{
    owidget = new OScene(0,0);
    ui->setupUi(this);
//    ui->gridLayout->addWidget(owidget);
    ui->horizontalLayout->addWidget(owidget);
}

mainform::~mainform()
{
    delete owidget;
    delete ui;
}
