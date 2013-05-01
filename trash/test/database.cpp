#include "database.h"
#include <QDebug>

database::database(QObject *parent) :
    QObject(parent)
{
    createDb();
    createTable();
}

database::~database()
{
}

void database::createDb()
{
   db = QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName("..\bb.test");
   if(!db.open())
       qDebug() << "Problem" << db.lastError();
   else
       qDebug() << "Not-a problem " << db.lastError();
}


void database::createTable()
{
    QSqlQuery qry(db);
    QString s;
    s = QString("create table if not exists objtable (id integer, object text);");

    if(!qry.exec(s))
        qDebug() << "Create table problem";
    else
        qDebug() << "Not-a create table problem";

}

void database::setRecord(const int id, const QString &text)
{
    QSqlQuery qry(db);
    QString s;
    s = QString("")
}

void database::deleteTable()
{
}
