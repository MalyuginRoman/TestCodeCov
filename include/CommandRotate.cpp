#include <iostream>
#include "CommandRotate.h"

class CommandRotateP
{
public:
    object* obj;

    CommandRotateP(object* obj) :
        obj(obj)
    {
    }
};

CommandRotate::CommandRotate(object* obj) :
    imp(new CommandRotateP(obj))
{
    this->getStr("CommandRotate");
}

CommandRotate::~CommandRotate() { delete imp;}

void CommandRotate::execute()
{
    std::cout << "Start execute of CommandRotate" << std::endl;
    if(imp->obj->place().placeX < 0 && imp->obj->place().placeY < 0)
        throw std::runtime_error ("Object not found");
    if(!imp->obj->getAngularVelocity(imp->obj, 0))
        throw std::runtime_error ("Unknown angular velocity");
    std::cout << imp->obj->place().angular << std::endl;
    if(!imp->obj->getAngular(imp->obj, dt))
        throw std::runtime_error ("Unknown position");
    std::cout << imp->obj->place().angular << std::endl;
}

void CommandRotate::getStr(std::string value)
{
    this->str = value;
}

std::string CommandRotate::setStr()
{
    return this->str;
}

object* CommandRotate::obj() const
{
    return imp->obj;
}
