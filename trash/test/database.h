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
    void delRecord(const int id);
    QString getRecord(const int id);


    void createTable();

    void deleteTable();

    bool isOpen();

private:

    QSqlDatabase db;
    void createDb();
    
signals:
    
public slots:
    
};

#endif // DATABASE_H
