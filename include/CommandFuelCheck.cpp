#include <iostream>
#include "CommandFuelCheck.h"

class CommandFuelCheckP
{
public:
    object* obj;

    CommandFuelCheckP(object* obj) :
        obj(obj)
    {
    }
};

CommandFuelCheck::CommandFuelCheck(object* obj) :
    imp(new CommandFuelCheckP(obj))
{
    this->getStr("CommandFuelCheck");
}

CommandFuelCheck::~CommandFuelCheck() { delete imp;}

void CommandFuelCheck::execute()
{
    std::cout << "Start execute of CommandFuelCheck" << std::endl;
    if(imp->obj->state().fuel < 0)
        throw std::runtime_error ("Object has not fuel");
}

void CommandFuelCheck::getStr(std::string value)
{
    this->str = value;
}

std::string CommandFuelCheck::setStr()
{
    return this->str;
}

object* CommandFuelCheck::obj() const
{
    return imp->obj;
}
