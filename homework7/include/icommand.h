#pragma once
#include <vector>
using namespace std;

class ICommand
{
public:
    virtual void execute() = 0;
};

class MoveCommand : public ICommand
{
    void execute()
    {
        cout << "Start execute MoveCommand" << endl;
    }
};

class RotateCommand : public ICommand
{
    void execute()
    {
        cout << "Start execute RotateCommand" << endl;
    }
};

class CheckCommand : public ICommand
{
    void execute()
    {
        cout << "Start execute CheckCommand" << endl;
    }
};

class BurnCommand : public ICommand
{
    void execute()
    {
        cout << "Start execute BurnCommand" << endl;
    }
};

class LogerCommand : public ICommand
{
public:
    void execute()
    {
        cout << "Start execute LogerCommand" << endl;
    }
};

class EmptyCommand : public ICommand
{
    void execute()
    {
        cout << "Start execute EmptyCommand" << endl;
    }
};

class HardStopCommand : public ICommand
{
    void execute()
    {
        cout << "Start execute HardStopCommand" << endl;
    }
};

class SoftStopCommand : public ICommand
{
    void execute()
    {
        cout << "Start execute SoftStopCommand" << endl;
    }
};

class MacroCommand : public ICommand
{
public:
    MacroCommand(vector<ICommand*> cmds);
    ~MacroCommand();
    vector<ICommand*> cmds;
    void execute();
private:
    class MacroCommandP* imp;
};
