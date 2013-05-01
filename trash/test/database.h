#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql/QtSql>
#include <QtSql/QSqlDatabase>

class database : public QObject
{
    Q_OBJECT
public:

    explicit database(QObject *parent = 0);
    virtual ~database();

    void setRecord(const int id, const QString &text);


    void createTable();

    void deleteTable();

private:

    QSqlDatabase db;
    void createDb();
    
signals:
    
public slots:
    
};

#endif // DATABASE_H