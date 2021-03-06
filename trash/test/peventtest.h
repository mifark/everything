#ifndef PEVENTTEST_H
#define PEVENTTEST_H

#include "types.h"
#include <QWidget>
#include <QList>

const int WIDTH = 30;
const int HEIGHT = 30;


class PeventTest : public QWidget
{
    Q_OBJECT
public:
    explicit PeventTest(QWidget *parent = 0);
    QPair<int,int>getSizeParams();

    void setDBPointer(database *db);
    void setMap();

protected:
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    bool eventFilter(QObject *, QEvent *);

private:

    QList<QList<QChar> > lmap;
    QList<QList<QChar> > dlmap;

    void updateMap();
    QFont font;
    int fontH;
    int fontW;

    QPoint player;

    void setPlayerD(int x,int y);

    QList<double> dy;
    QList<double> dx;


    QMap<int,QChar> types;
signals:
    void toRepaint();
    
public slots:
    
};

#endif // PEVENTTEST_H
