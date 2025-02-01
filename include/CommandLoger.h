#pragma once
#include "ICommand.h"
#include <string>

class CommandLoger : public ICommand
{
public:
    CommandLoger();

    void execute();
    void execute(ICommand* cmd);
    void getStr(std::string value);
    std::string setStr();
private:
    std::string str;
};
