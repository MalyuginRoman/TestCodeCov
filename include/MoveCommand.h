#pragma once

#include "IMovable.h"

class object;

class MoveCommand
{
public:
    MoveCommand(int x, int y, double a1, double a2, int v, int dt);
    virtual bool getPosition(object *obj, int dt);
    virtual bool setPosition(object *obj);
    virtual bool getVelocity(object *obj, int du);
    virtual bool setVelocity(object *obj);
private:
    class MoveCommandP *imp;
};
