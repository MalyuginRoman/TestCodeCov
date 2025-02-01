#pragma once
#include "object.h"

class EventManager
{
public:
    EventManager();
    ~EventManager();

    bool init(objectList* list);
    bool execute(objectList* list);

private:
    class EventManagerP* imp;
};
