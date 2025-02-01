#include <iostream>
#include "CommandFuelBurn.h"

class CommandFuelBurnP
{
public:
    object* obj;

    CommandFuelBurnP(object* obj) :
        obj(obj)
    {
    }
};

CommandFuelBurn::CommandFuelBurn(object* obj) :
    imp(new CommandFuelBurnP(obj))
{
    this->getStr("CommandFuelBurn");
}

CommandFuelBurn::~CommandFuelBurn() { delete imp;}

void CommandFuelBurn::execute()
{
    std::cout << "Start execute of CommandFuelBurn" << std::endl;
    std::cout << imp->obj->state().fuel << std::endl;
    if(imp->obj->getFuel(imp->obj, dF) < 0)
        throw std::runtime_error ("Not enough fuel");
    std::cout << imp->obj->state().fuel << std::endl;
}

void CommandFuelBurn::getStr(std::string value)
{
    this->str = value;
}

std::string CommandFuelBurn::setStr()
{
    return this->str;
}

object* CommandFuelBurn::obj() const
{
    return imp->obj;
}
