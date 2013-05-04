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
    if(db.isOpen())
    {
        QSqlQuery qry(db);
        QString s;
        s = QString("create table if not exists objtable (id integer, object text);");

        if(!qry.exec(s))
            qDebug() << "Create table problem";
        else
            qDebug() << "Not-a create table problem";
    }
}

void database::setRecord(const int id, const QString &text)
{
    if(db.isOpen())
    {
        QSqlQuery query(db);
        query.prepare("insert into objtable (id,object) values (:nid,:nobject);");
        query.bindValue(":nid",id);
        query.bindValue(":nobject",text);
        if(!query.exec())
            qDebug() << "inserterror " << query.lastError();
        else
            qDebug() << "not-a insert record";
    }
}

void database::delRecord(const int id)
{
    if(db.isOpen())
    {
        QSqlQuery query(db);
        query.prepare("delete from objtable where id = :lid;");
        query.bindValue(":lid",id);
        if(!query.exec())
            qDebug() << "delete record err " << query.lastError();
        else
            qDebug() << "not-a delete record";
    }
}

void database::deleteTable()
{
    if(db.isOpen())
    {
        QSqlQuery query(db);
        query.prepare("drop table objtable;");
        if(!query.exec())
            qDebug() << "delete table err " << query.lastError();
        else
            qDebug() << "not-a delete table";
    }
}

QString database::getRecord(const int id)
{
    if(db.isOpen())
    {
        QSqlQuery query(db);
        QString s;
        query.prepare("select object from objtable where id = :lid;");
        query.bindValue(":lid",id);
        if(!query.exec())
            qDebug() << "det record err" << query.lastError();

        int obj = query.record().indexOf("object");
        while(query.next())
        {
            s = query.value(obj).toString();
        }
        return s;

    }

}


bool database::isOpen()
{
    return db.isOpen();
}
