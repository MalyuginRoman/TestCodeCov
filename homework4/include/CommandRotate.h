#pragma once
#include "ICommand.h"
#include "object.h"
#include <string>

class CommandRotate : public ICommand
{
public:
    CommandRotate(object* obj);
    ~CommandRotate();

    object* obj() const;

    void execute();
    void getStr(std::string value);
    std::string setStr();
private:
    std::string str;
    class CommandRotateP* imp;
};
