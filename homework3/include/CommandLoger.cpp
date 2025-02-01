#include <iostream>
#include "CommandLoger.h"

CommandLoger::CommandLoger()
{
    this->getStr("CommandLoger");
}

void CommandLoger::execute()
{
    std::cout << "Start execute of CommandLoger" << std::endl;
}

void CommandLoger::execute(ICommand* cmd)
{
    std::cout << "Exception of " << cmd->setStr() << std::endl;
}

void CommandLoger::getStr(std::string value)
{
    this->str = value;
}

std::string CommandLoger::setStr()
{
    return this->str;
}
