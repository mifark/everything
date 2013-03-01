#ifndef OSCENE_H
#define OSCENE_H

#include <QGLWidget>
#include <QtOpenGL>


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
//    QPointF mpnt;
//    QList<QPointF> points;
    int point[10][10];
    void generateMap();
    int workAround(int nx, int ny);




};

#endif // OSCENE_H
