#ifndef OSCENE_H
#define OSCENE_H

#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>

const int USIZE = 500;
const int FSIZE = 15;
const int ACTIVE = 1;
const int FREE = 0;

class OScene : public QGLWidget
{
    Q_OBJECT
public:
    explicit OScene(QWidget *parent=0,QGLWidget *sharewidget=0);
    ~OScene();


protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);


private:
    QTimer timer;
//    QPointF mpnt;
//    QList<QPointF> points;
    int point[FSIZE][FSIZE];
    void generateMap();
    void drawGrid();
    void drawUniverse();
    int conflict(int xpos, int ypos);

private slots:
    void lifeperiod();





};

#endif // OSCENE_H
