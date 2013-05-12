
#include <QObject>
#include <QString>
#include <QMap>
#include "database.h"

enum eTypes{WALL,FLOOR,PLAYER,DOOR};
static const QChar compare='w';
void createBasic(database *db);
QMap<int,QChar> getRecords(database *db);

