#include "oscene.h"

OScene::OScene()
{
    QGLFormat fmt;
    fmt.setDoubleBuffer(true);
    this->setFormat(fmt);
    this->setAutoBufferSwap(true);
}

void OScene::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho( 0, 500, 500, 0, 0, 1);
    glMatrixMode( GL_MODELVIEW );

}

void OScene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_LINE_STRIP);
    glColor3d(1,0,0);
    glVertex2d(10,0);
    glVertex2d(30,100);

    glEnd();

}

void OScene::initializeGL()
{
    qglClearColor(Qt::black);
    glLoadIdentity();

}

void OScene::mouseMoveEvent(QMouseEvent *ev)
{

    updateGL();

}

void OScene::mousePressEvent(QMouseEvent *ev)
{

}

void OScene::mouseReleaseEvent(QMouseEvent *ev)
{

}
