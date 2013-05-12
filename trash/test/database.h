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
    void setReationsRecord(const int idtype,const int idreact);
    void delRecord(const int id);
    QString getRecord(const int id);

    int getReactionsRecord(bool is_type);


    void createTable();
    void createReactionsTable();

    void deleteTable();
    void deleteReactionsTable();

    bool isOpen();

    void redoTable();
    void redoReactionsTable();

private:

    QSqlDatabase db;
    void createDb();
    
signals:
    

};

#endif // DATABASE_H
