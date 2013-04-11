#include "peventtest.h"
#include <QPainter>
#include <QFontMetrics>
#include <QTime>

PeventTest::PeventTest(QWidget *parent) :
    QWidget(parent)
{
    QFontMetrics metrics(font);
    fontH = metrics.height()+2;
    fontW = metrics.width('w')+4;
    setMap();
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
            painter.drawText(QPoint(xPos,yPos),map[x][y]);
        }
    }




    painter.end();

}

void PeventTest::setMap()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int x=0; x<WIDTH; ++x)
    {
        for(int y=0;y<HEIGHT;++y)
        {
            if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1 || qrand() % 40 == 0)
                map[x][y] = '#';
            else
                map[x][y] = '.';
        }
    }
}

QPair<int,int> PeventTest::getSizeParams()
{
    return QPair<int,int>(fontW*WIDTH,fontH*HEIGHT);
}
