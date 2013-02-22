#include "mainform.h"
#include "ui_mainform.h"

mainform::mainform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainform)
{
    owidget = new OScene();
//    ui->verticalLayout->addWidget(owidget);
    ui->gridLayout->addWidget(owidget);
    ui->setupUi(this);
}

mainform::~mainform()
{
    delete owidget;
    delete ui;
}
