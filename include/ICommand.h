#pragma once
#include <string>

class ICommand
{
public:
    virtual void execute() = 0;
    virtual std::string setStr() = 0;
};
