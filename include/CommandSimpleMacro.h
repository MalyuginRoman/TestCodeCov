#pragma once

#include "ICommand.h"
#include "object.h"
#include <list>

class CommandSimpleMacro : public ICommand
{
public:
    CommandSimpleMacro(std::list<ICommand*> cmds);
    ~CommandSimpleMacro();

    std::list<ICommand*> cmds;

    void execute();
    void getStr(std::string value);
    std::string setStr();
private:
    std::string str;
    class CommandSimpleMacroP* imp;
};
