#include "peventtest.h"
#include <QPainter>
#include <QFontMetrics>
#include <QTime>
#include <QKeyEvent>
#include <QDebug>
#include "database.h"

PeventTest::PeventTest(QWidget *parent) :
    QWidget(parent)
{
    QFontMetrics metrics(font);
    fontH = metrics.height()+2;
    fontW = metrics.width(Types::compare)+4;
    dx << -1 << 0 << 1;
    dy << -1 << 0 << 1;
    player.setX(5);
    player.setY(5);

//    setMap();
}

void PeventTest::paintEvent(QPaintEvent *)
{
//    int yPos = fontH;
//    int xPos;
    QPainter painter;

    painter.begin(this);
    painter.fillRect(rect(),Qt::black);
    painter.setPen(Qt::white);
    for(int y=0,yPos=fontH; y<HEIGHT;y++, yPos+=fontH)
    {
        for(int x=0,xPos=0;x<WIDTH;x++,xPos+=fontW)
        {
            painter.drawText(QPoint(xPos,yPos),dlmap[x][y]);
        }
    }

    painter.end();

}

void PeventTest::setMap()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int x=0; x<WIDTH; ++x)
    {
        lmap.append(QList<QChar>());
        for(int y=0;y<HEIGHT;++y)
        {
            if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1 || qrand() % 40 == 0)
                lmap[x].append(types[Types::WALL]);
            else
                lmap[x].append(types[Types::FLOOR]);
        }
    }
    updateMap();
}

void PeventTest::updateMap()
{
    dlmap = lmap;
   dlmap[player.x()][player.y()] = types[Types::PLAYER];
}

QPair<int,int> PeventTest::getSizeParams()
{
    return QPair<int,int>(fontW*WIDTH,fontH*HEIGHT);
}

void PeventTest::keyPressEvent(QKeyEvent *ev)
{
    switch(ev->key())
    {
        case Qt::Key_Up:
            setPlayerD(dx[1],dy[0]);
            return;
        case Qt::Key_Down:
            setPlayerD(dx[1],dy[2]);
            return;
        case Qt::Key_Left:
            setPlayerD(dx[0],dy[1]);
            return;
        case Qt::Key_Right:
            setPlayerD(dx[2],dy[1]);
            return;
    }
}

bool PeventTest::eventFilter(QObject *obj, QEvent *ev)
{
    if(ev->type()==QEvent::KeyPress)
        keyPressEvent(static_cast<QKeyEvent *>(ev));
   return QObject::eventFilter(obj,ev);
}

void PeventTest::setPlayerD(int x, int y)
{
    int lx = player.x()+x;
    int ly = player.y()+y;
    if(lmap[lx][ly]!=types[Types::WALL])
    {
        player.setX(lx);
        player.setY(ly);
    }

//    emit toRepaint();
    updateMap();
    this->repaint();
}

void PeventTest::setDBPointer(database *db)
{
//    Types::createBasic(db);
    types = Types::getRecords(db);
}
