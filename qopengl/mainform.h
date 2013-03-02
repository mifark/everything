#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include "oscene.h"

namespace Ui {
class mainform;
}

class mainform : public QWidget
{
    Q_OBJECT
    
public:
    explicit mainform(QWidget *parent = 0);
    ~mainform();
    
private:
    Ui::mainform *ui;
    OScene *owidget;
};

#endif // MAINFORM_H
