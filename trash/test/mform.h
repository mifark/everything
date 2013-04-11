#ifndef MFORM_H
#define MFORM_H

#include <QWidget>
#include "peventtest.h"

namespace Ui {
class Mform;
}

class Mform : public QWidget
{
    Q_OBJECT
    
public:
    explicit Mform(QWidget *parent = 0);
    ~Mform();
    
private:
    Ui::Mform *ui;
    PeventTest *pe;
};

#endif // MFORM_H
