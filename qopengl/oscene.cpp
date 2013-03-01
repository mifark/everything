#include "oscene.h"

OScene::OScene(QWidget *parent, QGLWidget *sharewidget):
    QGLWidget(parent,sharewidget)
{
    QGLFormat fmt;
    fmt.setDoubleBuffer(true);
    this->setFormat(fmt);
    this->setAutoBufferSwap(true);
    qsrand(QTime::currentTime().second());
    generateMap();
}

OScene::~OScene()
{
    //delete point;
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
    glBegin(GL_QUADS);
        for(int i=0;i<10;i++)
            for(int j=0;j<10;j++)
            {
                glColor3f(1,0,0);
                if(point[i][j]<1)
                    glColor3f(1,1,1);
                glVertex2f((i) * 500 / 10, (j) * 500 / 10);
                glVertex2f((i + 1) * 500 / 10, (j) * 500 / 10);
                glVertex2f((i + 1) * 500 / 10, (j + 1) * 500 / 10);
                glVertex2f((i) * 500 / 10, (j + 1) * 500 / 10);
            }
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

void OScene::generateMap()
{
   for(int i=0;i<10;i++)
   {
       for(int j=0;j<10;j++)
       {
           if(qrand()%4==0)
            this->point[i][j] = 0;
           else
            point[i][j] = 1;
       }
   }
   for(int i=0;i<10;i++)
   {
       point[i][0] = 0;
       point[0][i] = 0;
       point[9][i] = 0;
       point[i][9] = 0;
   }
}

int OScene::workAround(int nx, int ny)
{
    int d[3]={-1,0,1};
    int count;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j+=2)
        {
        count = count + point[d[i]][d[j]]==1 ? 1:0;
        count = count + point[d[j]][d[i]]==1 ? 1:0;
        }
    }

}
