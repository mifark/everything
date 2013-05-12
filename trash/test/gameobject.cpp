#include "gameobject.h"

GameObject::GameObject(QObject *parent) :
    QObject(parent)
{
    Dbs = new database();

}

GameObject::~GameObject()
{
    delete Dbs;
}


//talk GameObject::collide(talk type)
//{
//    switch(type.type)
//    {
//        case SIMPLE:
//            return talk();
//        case BOOLEAN:
//            {
//                talk ret;
//                ret.type = type.type;
//                bool b = true;
//                ret.return_this = (void *) &b;
//                return ret;
//            }
//    }

//    return talk();
//}

void GameObject::seteType(eTypes type)
{
    this->type = type;
}


