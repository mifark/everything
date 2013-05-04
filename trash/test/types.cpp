#include "types.h"

void Types::createBasic(database *db)
{
    if(db->isOpen())
    {
        db->setRecord(WALL,"#");
        db->setRecord(FLOOR,".");
        db->setRecord(PLAYER,"@");
        db->setRecord(DOOR,"+");
    }
}

QMap<int,QChar> Types::getRecords(database *db)
{
    QMap<int,QChar> mapTypes;
    mapTypes[Types::WALL] = db->getRecord(Types::WALL).at(0);
    mapTypes[Types::DOOR] = db->getRecord(Types::DOOR).at(0);
    mapTypes[Types::FLOOR] = db->getRecord(Types::FLOOR).at(0);
    mapTypes[Types::PLAYER] = db->getRecord(Types::PLAYER).at(0);
    return mapTypes;
}
