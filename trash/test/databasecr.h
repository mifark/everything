#ifndef DATABASECR_H
#define DATABASECR_H

#include <QWidget>

namespace Ui {
class DatabaseCr;
}

class DatabaseCr : public QWidget
{
    Q_OBJECT
    
public:
    explicit DatabaseCr(QWidget *parent = 0);
    ~DatabaseCr();

    
private slots:
    void on_pushButton_clicked();

private:
    Ui::DatabaseCr *ui;


signals:
    void sig_remake();
};

#endif // DATABASECR_H
