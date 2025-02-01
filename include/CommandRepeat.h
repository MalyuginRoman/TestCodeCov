#pragma once
#include "ICommand.h"
#include "CommandQueue.h"
#include <string>

class CommandRepeat : public ICommand
{
public:
    CommandRepeat();

    void execute();
    void execute(CommandQueue* cmd, ICommand* com);
    void getStr(std::string value);
    std::string setStr();
private:
    std::string str;
};
