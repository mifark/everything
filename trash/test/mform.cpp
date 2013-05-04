#include "mform.h"
#include "ui_mform.h"
#include <QKeyEvent>
#include <QDebug>

Mform::Mform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mform)
{
    db = new database();
    pe = new PeventTest();
    pe->setDBPointer(db);
    pe->setMap();
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
    delete db;
}

void Mform::keyPressEvent(QKeyEvent *ev)
{

}
