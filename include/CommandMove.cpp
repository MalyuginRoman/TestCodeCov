#include <iostream>
#include "CommandMove.h"

CommandMove::CommandMove()
{
    this->getStr("CommandMove");
}

void CommandMove::execute()
{
    //std::cout << "Start execute of CommandMove" << std::endl;
    throw std::runtime_error ("CommandMove");
}

void CommandMove::getStr(std::string value)
{
    this->str = value;
}

std::string CommandMove::setStr()
{
    return this->str;
}
