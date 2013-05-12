#include "mform.h"
#include "ui_mform.h"
#include <QKeyEvent>
#include <QDebug>

Mform::Mform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mform)
{
    db = new database();
    dbcr = new DatabaseCr();
    pe = new PeventTest();
    pe->setDBPointer(db);
    pe->setMap();
    ui->setupUi(this);
    ui->widlayout->addWidget(pe);
    QPair<int,int> prm = pe->getSizeParams();
    this->pe->setMinimumSize(prm.first,prm.second);
    this->installEventFilter(pe);
    connect(pe,SIGNAL(toRepaint()),this,SLOT(toRepaint()));
    connect(dbcr,SIGNAL(sig_remake()),this,SLOT(on_remake()));
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
    delete dbcr;
}

void Mform::keyPressEvent(QKeyEvent *ev)
{

}

void Mform::on_pushButton_clicked()
{
    dbcr->show();

}

void Mform::on_remake()
{
    createBasic(db);
}
