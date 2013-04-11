#include <QApplication>
//#include "oscene.h"
#include "mform.h"

int main(int argc, char** argv)
{

    QApplication app(argc,argv);
    Mform form;
    form.show();

    return app.exec();
}
