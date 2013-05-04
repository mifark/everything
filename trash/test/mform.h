#ifndef MFORM_H
#define MFORM_H

#include <QWidget>
#include "peventtest.h"
#include "database.h"

namespace Ui {
class Mform;
}

class Mform : public QWidget
{
    Q_OBJECT
    
public:
    explicit Mform(QWidget *parent = 0);
    ~Mform();

protected:
    void keyPressEvent(QKeyEvent *);
private:
    Ui::Mform *ui;
    PeventTest *pe;
    database *db;

public slots:
    void toRepaint();
};

#endif // MFORM_H
