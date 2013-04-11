#include "mform.h"
#include "ui_mform.h"

Mform::Mform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mform)
{
    pe = new PeventTest();
    ui->setupUi(this);
    ui->widlayout->addWidget(pe);
    QPair<int,int> prm = pe->getSizeParams();
    this->pe->setMinimumSize(prm.first,prm.second);
}

Mform::~Mform()
{
    delete pe;
    delete ui;
}
