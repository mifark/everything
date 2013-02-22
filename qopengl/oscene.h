#ifndef OSCENE_H
#define OSCENE_H

//#include <QtOpenGL/QGLWidget>
//#include <QtOpenGL/qgl.h>
//#include <QtOpenGL/QtOpenGL>
#include <QtOpenGL>

class OScene : public QGLWidget
{
    Q_OBJECT
public:
    explicit OScene();


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




};

#endif // OSCENE_H
