#include "gameobject.h"

GameObject::GameObject(QObject *parent) :
    QObject(parent)
{

}


Types::talk GameObject::collide(Types::talk type)
{
    switch(type.type)
    {
        case Types::SIMPLE:
            return Types::talk();
        case Types::BOOLEAN:
            {
                Types::talk ret;
                ret.type = type.type;
                bool b = true;
                ret.return_this = (void) b;
                return ret;
            }
    }

    return Types::talk();
}
