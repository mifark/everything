#include "database.h"
#include <QDebug>

database::database(QObject *parent) :
    QObject(parent)
{
    createDb();
    createTable();
    setRecord(1,trUtf8("gh"));
    delRecord(1);
    deleteTable();
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
    QSqlQuery query(db);
    query.prepare("insert into objtable (id,object) values (:nid,:nobject);");
    query.bindValue(":nid",id);
    query.bindValue(":nobject",text);
    if(!query.exec())
        qDebug() << "inserterror " << query.lastError();
}

void database::delRecord(const int id)
{
    QSqlQuery query(db);
    query.prepare("delete from objtable where id = :lid;");
    query.bindValue(":lid",id);
    if(!query.exec())
        qDebug() << "delete record err " << query.lastError();
    else
        qDebug() << "not-a delete record";
}

void database::deleteTable()
{
    QSqlQuery query(db);
    query.prepare("drop table objtable;");
    if(!query.exec())
        qDebug() << "delete table err " << query.lastError();
    else
        qDebug() << "not-a delete table";
}
