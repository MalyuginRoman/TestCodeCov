#include <iostream>
#include "CommandMove.h"

class CommandMoveP
{
public:
    object* obj;

    CommandMoveP(object* obj) :
        obj(obj)
    {
    }
};

CommandMove::CommandMove(object* obj) :
    imp(new CommandMoveP(obj))
{
    this->getStr("CommandMove");
}

CommandMove::~CommandMove() { delete imp;}

void CommandMove::execute()
{
    std::cout << "Start execute of CommandMove" << std::endl;
    if(imp->obj->place().placeX < 0 && imp->obj->place().placeY < 0)
        throw std::runtime_error ("Object not found");
    if(!imp->obj->getVelocity(imp->obj, 0))
        throw std::runtime_error ("Unknown velocity");
    std::cout << imp->obj->place().placeX << "," << imp->obj->place().placeY << std::endl;
    if(!imp->obj->getPosition(imp->obj, dt))
        throw std::runtime_error ("Unknown position");
    std::cout << imp->obj->place().placeX << "," << imp->obj->place().placeY << std::endl;
}

void CommandMove::getStr(std::string value)
{
    this->str = value;
}

std::string CommandMove::setStr()
{
    return this->str;
}

object* CommandMove::obj() const
{
    return imp->obj;
}
