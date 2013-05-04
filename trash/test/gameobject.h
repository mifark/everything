#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include "types.h"

class GameObject : public QObject
{
    Q_OBJECT
public:
    explicit GameObject(QObject *parent = 0);
    ~GameObject();

    Types::talk collide(Types::talk type);


private:

    Types::eTypes type;
    
signals:
    
public slots:
    
};

#endif // GAMEOBJECT_H
