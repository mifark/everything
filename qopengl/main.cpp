#include <QApplication>
//#include "oscene.h"
#include "mainform.h"

int main(int argc, char** argv)
{

    QApplication app(argc,argv);

    mainform m;
    m.setWindowTitle("helloworld");
    m.show();

//    OScene oscene1;
//    oscene1.setWindowTitle("helloworld");
//    oscene1.setGeometry(100,100,500,500);
//    oscene1.setMouseTracking(true);
//    oscene1.show();
//    oscene1.setCursor(QCursor(Qt::BlankCursor));

    return app.exec();
}
