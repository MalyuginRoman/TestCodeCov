#pragma once
#include "ICommand.h"
#include "object.h"
#include <string>

class CommandFuelCheck : public ICommand
{
public:
    CommandFuelCheck(object* obj);
    ~CommandFuelCheck();

    object* obj() const;

    void execute();
    void getStr(std::string value);
    std::string setStr();
private:
    std::string str;
    class CommandFuelCheckP* imp;
};
