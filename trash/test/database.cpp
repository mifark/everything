#include "database.h"
#include "types.h"
#include <QDebug>

database::database(QObject *parent) :
    QObject(parent)
{
    createDb();
//    createTable();
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

void database::createReactionsTable()
{
    if(db.isOpen())
    {
        QSqlQuery qry(db);
        QString s;
        s = QString("create table if not exists reacttable (idtype integer, idreact integer);");

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

void database::setReationsRecord(const int idtype, const int idreact)
{
    if(db.isOpen())
    {
        QSqlQuery query(db);
        query.prepare("insert into reacttable (idtype,idreact) values (:idtype,:idreact);");
        query.bindValue(":idtype",idtype);
        query.bindValue(":idreact",idreact);
        if(!query.exec())
            qDebug() << "insert reactions error" << query.lastError();
        else
            qDebug() << "not-a insert reactions record";
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

void database::deleteReactionsTable()
{
    if(db.isOpen())
    {
        QSqlQuery query(db);
        query.prepare("drop table reacttable;");
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
            qDebug() << "get record err" << query.lastError();

        int obj = query.record().indexOf("object");
        while(query.next())
        {
            s = query.value(obj).toString();
        }
        return s;
    }
    return QString();
}

int database::getReactionsRecord(bool is_type)
{
    if(db.isOpen())
    {
        QSqlQuery query(db);
        QString s;
        if(is_type)
            s = "select idtype from reacttable where idreact = :idreact;";
        else
            s = "select idreact from reacttable where idtype = :idtype";

        if(!query.exec())
            qDebug() << "get reactrecord err" << query.lastError();

        int obj;
        if(is_type)
            obj = query.record().indexOf("idtype");
        else
            obj = query.record().indexOf("idreact");

        int ret;
        while(query.next())
        {
            ret = query.value(obj).toInt();
        }
        return ret;

    }
    return -1;
}


bool database::isOpen()
{
    return db.isOpen();
}


void database::redoTable()
{
    deleteTable();
    deleteReactionsTable();
    createTable();
    createReactionsTable();
}
