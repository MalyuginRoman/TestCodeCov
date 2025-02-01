#pragma once
#include "ICommand.h"
#include "object.h"
#include <string>

class CommandMove : public ICommand
{
public:
    CommandMove(object* obj);
    ~CommandMove();

    object* obj() const;

    void execute();
    void getStr(std::string value);
    std::string setStr();
private:
    std::string str;
    class CommandMoveP* imp;
};
