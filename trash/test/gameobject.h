#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include "types.h"
#include "database.h"

class GameObject : public QObject
{
    Q_OBJECT
public:
    explicit GameObject(QObject *parent = 0);
    ~GameObject();

//    talk collide(talk type);
    void seteType(eTypes type);


private:

    eTypes type;
    database *Dbs;

    bool block();
    bool freeToGo();
    bool onOpen(Qt::Key k);
    
signals:
    
public slots:
    
};

#endif // GAMEOBJECT_H
