#include <iostream>
#include "CommandSimpleMacro.h"

class CommandSimpleMacroP
{
public:
    std::list<ICommand*> cmds;

    CommandSimpleMacroP(std::list<ICommand*> cmds) :
        cmds(cmds)
    {
    }
};

CommandSimpleMacro::CommandSimpleMacro(std::list<ICommand*> cmds) :
    imp(new CommandSimpleMacroP(cmds))
{
    this->getStr("CommandSimpleMacro");
}

CommandSimpleMacro::~CommandSimpleMacro() { delete imp;}

void CommandSimpleMacro::execute()
{
    std::cout << "Start execute of CommandSimpleMacro" << std::endl;
    if(imp->cmds.empty())
        throw std::runtime_error ("Сommand list is empty");
    for(ICommand* i : imp->cmds)
    {
        try
        {
            i->execute();
        } catch (...) {
            throw std::runtime_error ("Pass the error up");
        }
    }

}

void CommandSimpleMacro::getStr(std::string value)
{
    this->str = value;
}

std::string CommandSimpleMacro::setStr()
{
    return this->str;
}
