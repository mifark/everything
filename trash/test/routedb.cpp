/**
  \file routedb.cpp
  \brief содержит класс для работы с psql хранилищем маршрутов
  \author Кузема А К
  */
#include "routedb.h"


RouteDb::RouteDb(bool is_sqlite, QObject *parent) :
    QObject(parent)
{
    ConnectionName = CreateConnectionName();
    this->is_sqlite = is_sqlite;
    if(!is_sqlite)
    {
        if(readConfig(data))
        {
            setDB(data);
        }
    }
    else
        setSqlDB();
}
RouteDb::~RouteDb()
{
}

bool RouteDb::setSqlDB(QString location)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString dir;
    if(location.isEmpty())
        dir = QDir::homePath() + "/" + ".marker-m";
    else
        dir = location;
    db.setDatabaseName(dir +"/" + "route.db");
    if(!db.open())
    {
            qDebug() << "formfvk dberr:::" << db.lastError().text();
            return false;
    }
    createRoutesTable();
    return true;
}

bool RouteDb::setDB(HOST_INFO::QServInfo data)
{
    db = QSqlDatabase::addDatabase("QPSQL",ConnectionName);
    db.setDatabaseName(data.dbname);
    db.setHostName(data.host);
    db.setUserName(data.user);
    db.setPassword(data.password);
    db.setPort(data.port);
    if(!db.open())
    {
            qDebug() << "countfvk dberr:::" << db.lastError().text();
            return false;
    }

    createRoutesTable();
    return true;
}


bool RouteDb::readConfig(HOST_INFO::QServInfo &data)
{
    QString path = QDir::homePath()+"/"+".marker-m";
    QDir dir(path+"/");
    if(!dir.exists())
        if(!dir.mkpath(path+"/"))
        {
            qDebug() << "formfvk::Error. Can't create folder:" << path;
            return false;
        }

    config = new QConfigFile(path,"route");
    config->ReadFile();
    if(!config->isExist("dbname"))
    {
        config->SetParam("host", "232-svn");
        config->SetParam("port",5432);
        config->SetParam("user","postgres");
        config->SetParam("pass","postgres");
        config->SetParam("dbname","route_k");
        config->WriteFile();
        config->ReadFile();
    }

    QVariant param;
    if(config->GetParam("host",param))
        data.host = param.toString();
    else
        data.host = data.defHost();

    if(config->GetParam("port",param))
        data.port= param.toInt();
    else
        data.port = data.defPort();

    if(config->GetParam("user",param))
        data.user = param.toString();
    else
        data.user = "postgres";

    if(config->GetParam("pass",param))
        data.password = param.toString();
    else
        data.password = "postgres";

    if(config->GetParam("dbname",param))
        data.dbname = param.toString();
    else
        data.dbname =  "route_k";

    qDebug()<<"formFvk:: host: "<<data.host<<" , user: "<<data.user<<" db_name: "<<data.dbname;

    return true;
}

bool RouteDb::createRoutesTable()
{
    bool exrtable=false,exrpoint=false;
    if(!db.isOpen())
        return false;
    QSqlQuery query(db);
    QString str;

    if(!is_sqlite)
    {
        str = QString("select * from information_schema.tables");
        if(!query.exec(str))
        {
            qDebug() << "formfvk dberr:::" << query.lastError();
            return false;
        }
        while(query.next())
        {
           if(query.value(2).toString()=="routestable")
               exrtable = true;
           else if(query.value(2).toString()=="pointstable")
               exrpoint = true;
        }
    }

    if(!exrtable)
    {
        query.clear();
        str = QString("create table routestable (rname text primary key, rcomment text, rdrawn boolean, rborder boolean)");
        if(!query.exec(str))
        {
            qDebug() << "formfvk dberr:::create routestable" << query.lastError();
            return false;
        }
    }
    if(!exrpoint)
    {
        query.clear();
        str = QString("create table pointstable (rname text references routestable(rname) on delete cascade, fi real, lm real, width real, pname text, knee text)");
        if(!query.exec(str))
        {
            qDebug() << "formfvk dberr:::create pointstable" << query.lastError();
            return false;
        }
    }
    return true;
}

bool RouteDb::addRoute(QString routename, QString routecomment, bool border_shown)
{
    if(!db.isOpen())
        return false;
    QSqlQuery query(db);
    query.prepare("insert into routestable (rname,rcomment,rdrawn, rborder) values (:routename, :routecomment, :visible, :border)");
    query.bindValue(":routename",routename);
    query.bindValue(":routecomment",routecomment);
    query.bindValue(":visible","false");
    if(border_shown)
        query.bindValue(":border","true");
    else
        query.bindValue(":border","false");
    if(!query.exec())
    {
        qDebug() << "formfvk dberr::addroute" << query.lastError();
        return false;
    }
    return true;
}

bool RouteDb::bindTable(rtElemCol *rt)
{
    if(!db.isOpen())
        return false;

    QSqlQuery query(db);
    for(int i=0; i<rt->points.size(); i++)
    {
                query.prepare("INSERT INTO pointstable (rname, fi, lm, width, pname, knee) VALUES ( :rname, :fi, :lm, :width, :pname, :knee);");
                query.bindValue(":rname",rt->RouteName);
                query.bindValue(":fi",rt->points[i].point.y());
                query.bindValue(":lm",rt->points[i].point.x());
                query.bindValue(":width",rt->points[i].width);
                query.bindValue(":pname",rt->points[i].name);
                query.bindValue(":knee",rt->points[i].knee);
        if(!query.exec())
        {
            qDebug() << "add to routetable problem: nothing happens";
            return false;
        }
    }
    return true;
}

bool RouteDb::dropRoutesTable()
{
    if(!db.isOpen())
        return false;
    QSqlQuery query(db);
    query.prepare("DROP TABLE routestable");
    if(!query.exec())
    {
        qDebug() << "formfvk dberr:::droproutestable" << query.lastError();
        return false;
    }
    return true;
}

bool RouteDb::removeRoute(QString routename)
{
    if(!db.isOpen())
        return false;
    QSqlQuery query(db);
   QString str1 = QString("delete from routestable where rname = :routename;");
   query.prepare(str1);
   query.bindValue(":routename",routename);
   if(!query.exec())
   {
        qDebug() << "formfvk dberr:::deleteroutestable" << query.lastError();
    }
   emit updatedb();
   return true;
}

QMap<QString,QString> RouteDb::getTables()
{
    if(!db.isOpen())
        qDebug() << "get route tables failed";

    QMap<QString,QString> returnable;
    QSqlQuery query(db);
    QString str = QString("SELECT rname,rcomment FROM routestable");

    if(!query.exec(str))
    {
        qDebug() << "formfvk dberr:::gettables" << query.lastError();
    }
    QSqlQueryModel mdl;
    mdl.setQuery(str,db);

    for (int i=0; i<mdl.rowCount(); i++)
    {
        returnable.insert(mdl.record(i).value("rname").toString(),
                          mdl.record(i).value("rcomment").toString());
    }

    return returnable;
}

bool RouteDb::getRoute(rtElemCol *rt)
{
    if(!db.isOpen())
        return false;

    rt->points.clear();

    QString str = QString("select rname,rcomment,rborder from routestable;");
    QSqlQuery query(db);
    query.prepare(str);
//    query.bindValue(":rname",rt->RouteName);
    if(!query.exec())
    {
        qDebug() << "formfvk dberr:::getroute" << query.lastError();
        return false;
    }

//    int comment = query.record().indexOf("rcomment");
//    rt->RouteComment = query.value(1).toString();
//    rt->has_borders = query.value(2).toBool();

    while(query.next())
    {
        if(rt->RouteName == query.value(0).toString())
        {
            rt->RouteComment = query.value(1).toString();
            rt->has_borders = query.value(2).toBool();
            break;

        }
    }

    str = QString("select * from pointstable where rname = :rname;");
    query.prepare(str);
    query.bindValue(":rname",rt->RouteName);
    if(!query.exec())
    {
        qDebug() << "formfvk dberr:::getroute" << query.lastError();
        return false;
    }

    //запомним позиции полей
    int fi = query.record().indexOf("fi");
    int lm = query.record().indexOf("lm");
    int wd = query.record().indexOf("width");
    int pn = query.record().indexOf("pname");
    int pd = query.record().indexOf("knee");
    //разберем построчно и забьем в контейнер
    while(query.next())
    {
        rtElem rl;
        rl.point = QPointF(query.value(lm).toDouble(),query.value(fi).toDouble());
        rl.width  = query.value(wd).toDouble();
        rl.name = query.value(pn).toString();
        rl.knee = query.value(pd).toString();
        rt->points.append(rl);
    }

    return true;
}

void RouteDb::getRoute(rtElemCol *rt, bool *has_saved)
{
   *has_saved = getRoute(rt);
}

bool RouteDb::markVisible(const QString &lst, bool is_visible)
{
    if(!db.isOpen())
        return false;
    QSqlQuery query(db);
            QString svisible = is_visible ? trUtf8("true") : trUtf8("false");
    QString str=QString("UPDATE routestable SET rdrawn = %1 WHERE rname = '%2';").arg(svisible).arg(lst);
    if(!query.exec(str))
    {
        qDebug() << "formfvk dberr:::markvisible" << query.lastError();
            return false;
    }
    emit updatedb();
    return true;
}

bool RouteDb::getDrawnRoutes(QList<rtElemCol> &rtList)
{
    if(!db.isOpen())
        return false;

    QSqlQuery query(db);
    QString str = QString("SELECT * FROM routestable WHERE rdrawn = true;");
    if(!query.exec(str))
    {
        qDebug() << "formfvk dberr:::getdrawnroutes" << query.lastError();
        return false;
    }

    int name = query.record().indexOf("rname");
    QStringList list;
    while(query.next())
    {
        list.append(query.value(name).toString());
    }


    rtElemCol appendable;
    foreach(const QString &str,list)
    {
        appendable.RouteName = str;
        getRoute(&appendable);
        rtList.append(appendable);
        appendable.clear();
    }
    return true;
}


QString RouteDb::CreateConnectionName()
{
    QString rez = QUuid::createUuid().toString();
    rez = rez.mid(2, rez.length()-5);
    return rez;
}


void RouteDb::saveRoute(rtElemCol *rt, bool *b)
{
    *b = false;
    if(!rt->RouteName.isEmpty())
    if(addRoute(rt->RouteName,rt->RouteComment,rt->has_borders))
    {
        if(bindTable(rt))
        {
            *b = true;
        }
    }
   emit updatedb();
    return;
}


void RouteDb::fupdatedb()
{
    emit updatedb();
}

bool RouteDb::setVisibleBorders(QString routename, bool is_visible)
{
    if(!db.isOpen())
        return false;
    QSqlQuery query(db);
            QString svisible = is_visible ? trUtf8("true") : trUtf8("false");
    QString str=QString("UPDATE routestable SET rborder = %1 WHERE rname = '%2';").arg(svisible).arg(routename);
    if(!query.exec(str))
    {
        qDebug() << "formfvk dberr::setVisibleBorders" << query.lastError();
            return false;
    }
    emit updatedb();
    return true;
}


ieHandler::Errortype RouteDb::saveRouteErrors(rtElemCol *rt)
{
    // Проверить на типовые ошибки перед сохранением. Порядок проверки может оказаться критичен!
    if(rt->points.size()<1)
        return ieHandler::esize;
    for(int i=0;i<rt->points.size()-1;i++)
        if(rt->points[i].width==0)
            return ieHandler::enotlastwidth;
    if(rt->RouteName.isEmpty())
        return ieHandler::ename;
    if(rt->RouteName == choosedTaskRoute)
        return ieHandler::eroutetask;
    if(getTables().keys().contains(rt->RouteName))
        return ieHandler::enamerepeat;
    if(rt->points.last().width!=0)
        return ieHandler::elastwidth;

    bool b;
    saveRoute(rt,&b);
    return ieHandler::eno;
}

void RouteDb::saveRepeatedRoute(rtElemCol &rt)
{
    removeRoute(rt.RouteName);
    bool b;
    saveRoute(&rt,&b);
}

void RouteDb::setChoosedTaskRoute(QString route)
{
    choosedTaskRoute = route;
}


QString RouteDb::getChoosedTaskRoute()
{
    return choosedTaskRoute;
}
