#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>

class GameObject : public QObject
{
    Q_OBJECT
public:
    explicit GameObject(QObject *parent = 0);
    virtual ~GameObject();
    void collide();
    
signals:
    
public slots:
    
};

#endif // GAMEOBJECT_H
