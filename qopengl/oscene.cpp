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
    connect(&timer,SIGNAL(timeout()),this,SLOT(lifeperiod()));
    timer.start(2000);
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
    glOrtho( 0, USIZE, USIZE, 0, 0, 1);
    glMatrixMode( GL_MODELVIEW );

}

void OScene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    drawUniverse();
//    drawGrid();

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
    /*
   for(int i=0;i<FSIZE;i++)
   {
       for(int j=0;j<FSIZE;j++)
       {
           if(qrand()%3==0)
               point[i][j] = ACTIVE;
           else
               point[i][j] = FREE;
       }
   }*/
   for(int i=1;i<FSIZE-1;i++)
   {
       point[i][1] = ACTIVE;
//       point[1][i] = ACTIVE;
//       point[FSIZE-2][i] = ACTIVE;
//       point[i][FSIZE-2] = ACTIVE;
   }
   for(int i=0;i<FSIZE;i++)
   {
       point[i][0] = FREE;
       point[0][i] = FREE;
       point[FSIZE-1][i] = FREE;
       point[i][FSIZE-1] = FREE;
   }
}

void OScene::drawGrid()
{
    glLineWidth(1);
    glColor3d(0,1,0);
    glBegin(GL_LINES);
        for(int i=0;i<USIZE;i+=USIZE/FSIZE)
        {
            glVertex2f(0,i);
            glVertex2f(USIZE,i);
            glVertex2f(i,0);
            glVertex2f(i,USIZE);
        }

    glEnd();
}


void OScene::drawUniverse()
{
    glBegin(GL_QUADS);
        for(int i=0;i<FSIZE;i++)
            for(int j=0;j<FSIZE;j++)
            {
                glColor3f(1,0,0);
                if(point[i][j]<1)
                    glColor3f(1,1,1);
                glVertex2f((i) * USIZE / FSIZE, (j) * USIZE / FSIZE);
                glVertex2f((i + 1) * USIZE / FSIZE, (j) * USIZE / FSIZE);
                glVertex2f((i + 1) * USIZE / FSIZE, (j + 1) * USIZE / FSIZE);
                glVertex2f((i) * USIZE / FSIZE, (j + 1) * USIZE / FSIZE);
            }
    glEnd();
}

int OScene::conflict(int xpos, int ypos)
{
   int d[3] = {-1,0,1};
   int count = 0;
   for(int i=0;i<3;i++)
       for(int j=0;j<3;j++)
       {
           if(!(i==j && d[i]==0))
                count += point[xpos + d[i]][ypos + d[j]] == ACTIVE ? 1 : 0;
       }
   return count;
}


void OScene::lifeperiod()
{
    int count;
    int bufferpoint[FSIZE][FSIZE];
    for(int i=1;i<FSIZE-1;++i)
    {
        for(int j=1;j<FSIZE-1;++j)
        {
            count = conflict(i,j);
            if(count<2 || count>3)
                bufferpoint[i][j] = FREE;
            else if(count==3)
                bufferpoint[i][j] = ACTIVE;
            else
                bufferpoint[i][j] = point[i][j];

        }
    }
    for(int i=1;i<FSIZE-1;++i)
        for(int j=1;j<FSIZE-1;++j)
            point[i][j] = bufferpoint[i][j];
    this->updateGL();
}
