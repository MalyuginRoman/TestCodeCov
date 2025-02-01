#include <iostream>
#include "CommandRepeat.h"

CommandRepeat::CommandRepeat()
{
    this->getStr("CommandRepeat");
}

void CommandRepeat::execute()
{
    std::cout << "Start execute of CommandRepeat" << std::endl;
}

void CommandRepeat::execute(CommandQueue* cmd, ICommand* com)
{
    std::cout << "Start execute of CommandRepeat" << std::endl;
    cmd->add(com);
}

void CommandRepeat::getStr(std::string value)
{
    this->str = value;
}

std::string CommandRepeat::setStr()
{
    return this->str;
}
