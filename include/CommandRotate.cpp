#include <iostream>
#include "CommandRotate.h"

CommandRotate::CommandRotate()
{
    this->getStr("CommandRotate");
}

void CommandRotate::execute()
{
    //std::cout << "Start execute of CommandRotate" << std::endl;
    throw std::runtime_error("CommandRotate");
}

void CommandRotate::getStr(std::string value)
{
    this->str = value;
}

std::string CommandRotate::setStr()
{
    return this->str;
}
