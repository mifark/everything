#ifndef MFORM_H
#define MFORM_H

#include <QWidget>
#include "peventtest.h"
#include "database.h"
#include "databasecr.h"


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
    DatabaseCr *dbcr;

public slots:
    void toRepaint();
private slots:
    void on_pushButton_clicked();

    void on_remake();
};

#endif // MFORM_H
