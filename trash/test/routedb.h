/**
  \file routedb.h
  \brief содержит класс для работы с psql хранилищем маршрутов
  \author Кузема А К
  */
#ifndef ROUTEDB_H
#define ROUTEDB_H
#include "pointcol.h"
#include "qconfigfile_base.h"
#include "host_info.h"
#include "inputerrorhandler.h"
#include <QtSql>

/// \class RouteDb
/// Класс для работы с psql.
/// Данные по подключению берутся из файла home/.marker-m/route.cfg (формируется с данными по умолчанию)
class RouteDb : public QObject
{
    Q_OBJECT
public:
    explicit RouteDb(bool is_sqlite,QObject *parent=0);
    ~RouteDb();
    bool readConfig(HOST_INFO::QServInfo &data); ///< \brief прочитать конфигурационный файл.
    bool setDB(HOST_INFO::QServInfo data); ///< \brief Инициализация базы данных.
    bool setSqlDB(QString location="");
    QMap<QString,QString> getTables(); ///< \brief получить список таблиц в бд

    /// \brief Создать таблицу описаний маршрутов и таблицу точек.
    bool createRoutesTable();
    /// \brief Добавить маршрут в таблицу описаний.
    bool addRoute(QString routename, QString routecomment, bool border_shown);
    /// \brief Убрать маршрут.
    bool removeRoute(QString routename);
    /// \brief Заполнить таблицу точек.
    bool bindTable(rtElemCol *rt);
    /// \brief Получить маршрут.
    bool getRoute(rtElemCol *rt);

    /// \brief Пометить нанесенный маршрут.
    /// \param lst - название маршрута
    bool markVisible(const QString &lst, bool is_visible);
    /// \brief Получить нанесенные ранее маршруты.
    /// \param rtList - список из маршрутов
    bool getDrawnRoutes(QList<rtElemCol> &rtList);

    /// \brief принудительно вызвать сообщение от базы данных об обновлении
    void fupdatedb();

    bool setVisibleBorders(QString routename,bool is_visible);

    ieHandler::Errortype saveRouteErrors(rtElemCol *rt);
    void saveRepeatedRoute(rtElemCol &rt);

    /// \brief получить выбранный для задачи маршрут
    /// @{
        void setChoosedTaskRoute(QString route);
        QString getChoosedTaskRoute();
    /// @}

private:
    /// \brief Удалить таблицу маршрута.
    bool dropRoutesTable();

    /// \brief поля и параметры для подключения и управления бд
    /// @{
        QSqlDatabase db;
        QConfigFile *config;
        HOST_INFO::QServInfo data;

        /// \brief название соединения с бд
        QString CreateConnectionName();
        QString ConnectionName;

        QString directory;
        bool is_sqlite;
    /// @}

    /// \brief переменная для хранения имени маршрута, объявленного "выбранным" для маршрутных задач
    QString choosedTaskRoute;

public slots:
    void getRoute(rtElemCol *rt,bool *has_saved);
    void saveRoute(rtElemCol *rt,bool *b);

signals:
    /// \brief сигнал об обновлении базы данных для классов, отображающих информацию из оной
    void updatedb();

};

#endif // ROUTEDB_H
