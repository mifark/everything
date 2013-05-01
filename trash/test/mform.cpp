#include "mform.h"
#include "ui_mform.h"
#include <QKeyEvent>
#include <QDebug>
#include "database.h"

Mform::Mform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mform)
{
    database db;
    pe = new PeventTest();
    ui->setupUi(this);
    ui->widlayout->addWidget(pe);
    QPair<int,int> prm = pe->getSizeParams();
    this->pe->setMinimumSize(prm.first,prm.second);
    this->installEventFilter(pe);
    connect(pe,SIGNAL(toRepaint()),this,SLOT(toRepaint()));
}

void Mform::toRepaint()
{
    this->repaint();
    this->resize(this->width(),this->height());
}

Mform::~Mform()
{
    delete pe;
    delete ui;
}

void Mform::keyPressEvent(QKeyEvent *ev)
{

}
