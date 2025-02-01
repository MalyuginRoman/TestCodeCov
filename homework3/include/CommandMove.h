#pragma once
#include "ICommand.h"
#include <string>

class CommandMove : public ICommand
{
public:
    CommandMove();

    void execute();
    void getStr(std::string value);
    std::string setStr();
private:
    std::string str;
};
