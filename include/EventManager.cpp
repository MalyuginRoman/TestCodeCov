#include <iostream>
#include <list>
#include "EventManager.h"
#include "MoveCommand.h"
#include "RotateCommand.h"

const int Xmax = 100;
const int Ymax = 100;
const int Tmax = 100;
const int dt = 1;

class MoveCommand;
class RotateCommand;

class EventManagerP
{
public:
    objectList* list;
    int countX, countY;

    EventManagerP():
        countX(0),
        countY(0)
    {
    }
    ~EventManagerP()
    {
    }
    bool init(objectList* starship)
    {
        int count = starship->count();
        std::list<object*> list1 = starship->list();
        for(object* n : list1) //(int i = 0; i < count; i ++)
        {
            object *obj = n; //starship->list().at(i);
            if(!checkPlaceObject(obj)) return false;
            if(!checkVelocityObject(obj)) return false;
            list = starship;
        }
        return true;
    }
    bool checkPlaceObject(const object *obj)
    {
        if(obj->placeX() < 0 || obj->placeY() < 0)
            return false;
        return true;
    }
    bool checkVelocityObject(const object *obj)
    {
        if(obj->velocity() < 0 || obj->angular() < 0)
            return false;
        return true;
    }
    bool execute(objectList* starship)
    {
        std::cout << "Start moving objects" << std::endl;
        int count = starship->count();
        std::list<object*> list1 = starship->list();
        for(object* n : list1) //(int i = 0; i < count; i ++)
        {
            object *obj = n; //starship->list().at(i);
            if(obj->velocity() != 0)
            {
                MoveCommand *mov = new MoveCommand(obj->placeX(), obj->placeY(), obj->velocity(),
                                                   obj->angular(), obj->angularVelocity(), dt);
                mov->getPosition(obj, dt);
            }
            if(obj->angular() != 0)
            {
                RotateCommand  *rot = new RotateCommand (obj->placeX(), obj->placeY(), obj->velocity(),
                                                         obj->angular(), obj->angularVelocity(), dt);
                rot->getAngular(obj, 15);
            }
        }
        return true;
    }
};

EventManager::EventManager() : imp(new EventManagerP)
{
}

EventManager::~EventManager()
{
    delete imp;
}

bool EventManager::init(objectList* list)
{
    bool result = imp->init(list);
    return result;
}

bool EventManager::execute(objectList* list)
{
    bool result = imp->execute(list);
    return result;
}
