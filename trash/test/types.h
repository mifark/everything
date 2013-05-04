
#include <QObject>
#include <QString>
#include <QMap>
#include "database.h"

namespace Types{
    enum eTypes{WALL,FLOOR,PLAYER,DOOR};
    static const QChar compare='w';
    void createBasic(database *db);
    QMap<int,QChar> getRecords(database *db);

    enum eTalkType{SIMPLE,BOOLEAN};
    struct talk{
      eTalkType type;
      void return_this;

      talk(){
          type = SIMPLE;
      }

    };
}
