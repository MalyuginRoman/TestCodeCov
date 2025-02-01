#pragma once
#include <iostream>
#include "EventManager.h"
#include "object.h"

class objectList;
class EventManager;

void execute_moving()
{
    objectList* list = new objectList;
    EventManager* manager = new EventManager;

    int i = 2;
    list->add(i, 10 * i, 45 * i, 0, 0, 0);

    bool isOk = manager->init(list);
    //if(!isOk) return false;

    isOk = manager->execute(list);
    //if(!isOk) return false;
}
