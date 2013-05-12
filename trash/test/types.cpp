#include "types.h"

void createBasic(database *db)
{
    if(db->isOpen())
    {
        // current for reconfigure

        db->redoTable();

        db->setRecord(WALL,"#");
        db->setRecord(FLOOR,".");
        db->setRecord(PLAYER,"@");
        db->setRecord(DOOR,"+");

    }
}

QMap<int,QChar> getRecords(database *db)
{
    QMap<int,QChar> mapTypes;
    mapTypes[WALL] = db->getRecord(WALL).at(0);
    mapTypes[DOOR] = db->getRecord(DOOR).at(0);
    mapTypes[FLOOR] = db->getRecord(FLOOR).at(0);
    mapTypes[PLAYER] = db->getRecord(PLAYER).at(0);
    return mapTypes;
}
