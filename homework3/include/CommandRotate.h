#pragma once
#include "ICommand.h"
#include <string>

class CommandRotate : public ICommand
{
public:
    CommandRotate();

    void execute();
    void getStr(std::string value);
    std::string setStr();
private:
    std::string str;
};
