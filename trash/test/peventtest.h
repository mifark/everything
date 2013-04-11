#ifndef PEVENTTEST_H
#define PEVENTTEST_H

#include <QWidget>

const int WIDTH = 30;
const int HEIGHT = 30;

class PeventTest : public QWidget
{
    Q_OBJECT
public:
    explicit PeventTest(QWidget *parent = 0);
    QPair<int,int>getSizeParams();

protected:
    void paintEvent(QPaintEvent *);

private:

    QChar map[WIDTH][HEIGHT];
    void setMap();
    QFont font;
    int fontH;
    int fontW;


    
signals:
    
public slots:
    
};

#endif // PEVENTTEST_H
