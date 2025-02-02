#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <functional>
#include <memory>

using namespace std;

enum CommandCodes
{
    CommandMove = 1,
    CommandRotate = 2,
    CommandCheck = 3,
    CommandBurn = 4,
    CommandLoger = 5,
    CommandEmpty = 6,
    CommandHardStop = 7,
    CommandSoftStop = 8,
    //CommandInternet = 9,
    CommandMoveTo = 10,
    CommandRun = 11,
    CommandAddLast = 12,
    CommandMacro = 100
};
class ICommand
{
public:
    virtual int get_Id_cmd() = 0;
    virtual void execute() = 0;
};
class MoveCommand : public ICommand
{
public:
    int get_Id_cmd()
    {
        return CommandMove;
    }
    void execute()
    {
        cout << "MoveCommand";
    }
};
class RotateCommand : public ICommand
{
public:
    int get_Id_cmd()
    {
        return CommandRotate;
    }
    void execute()
    {
        cout << "RotateCommand";
    }
};
class CheckCommand : public ICommand
{
public:
    int get_Id_cmd()
    {
        return CommandCheck;
    }
    void execute()
    {
        cout << "CheckCommand";
    }
};
class BurnCommand : public ICommand
{
public:
    int get_Id_cmd()
    {
        return CommandBurn;
    }
    void execute()
    {
        cout << "BurnCommand";
    }
};
class AddLastCommand : public ICommand
{
public:
    int get_Id_cmd()
    {
        return CommandAddLast;
    }
    void execute()
    {
        cout << "Start execute AddLastCommand" << endl;
    }
};
class LogerCommand : public ICommand
{
public:
    int get_Id_cmd()
    {
        return CommandLoger;
    }
    void execute()
    {
        cout << "LogerCommand";
    }
};
class EmptyCommand : public ICommand
{
public:
    int get_Id_cmd()
    {
        return CommandEmpty;
    }
    void execute()
    {
        cout << "EmptyCommand";
    }
};
class HardStopCommand : public ICommand
{
public:
    int get_Id_cmd()
    {
        return CommandHardStop;
    }
    void execute()
    {
        cout << "HardStopCommand";
    }
};
class SoftStopCommand : public ICommand
{
public:
    int get_Id_cmd()
    {
        return CommandSoftStop;
    }
    void execute()
    {
        cout << "SoftStopCommand";
    }
};
class MoveToCommand : public ICommand
{
public:
    int get_Id_cmd()
    {
        return CommandMoveTo;
    }
    void execute()
    {
        cout << "MoveToCommand";
    }
};
class RunCommand : public ICommand
{
public:
    int get_Id_cmd()
    {
        return CommandRun;
    }
    void execute()
    {
        cout << "RunCommand";
    }
};
class MacroCommand : public ICommand
{
public:
    int get_Id_cmd()
    {
        return CommandMacro;
    }
    MacroCommand(vector<ICommand*> cmds);
    ~MacroCommand();
    vector<ICommand*> cmds;
    void execute();
private:
    class MacroCommandP* imp;
};

class RegisterCommand : public ICommand
{
public:
    RegisterCommand(map<string, function<ICommand*()>> *m_map, map<string, string> *m_scope);
    ~RegisterCommand();
    map<string, function<ICommand*()>>* m_map;
    map<string, string>* m_scope;
    void execute();
    void registerType(string key_s, string key_f, function<ICommand*()> func);
private:
    class RegisterCommandP* imp;
};

template<class T>
class InternetCommand
{
public:
    T resolve(int operatinID)
    {
        switch (operatinID)
        {
        case CommandMove:
            return new MoveCommand();
            break;
        case CommandRotate:
            return new RotateCommand();
            break;
        case CommandCheck:
            return new CheckCommand();
            break;
        case CommandBurn:
            return new BurnCommand();
            break;
        case CommandLoger:
            return new LogerCommand();
            break;
        case CommandEmpty:
            return new EmptyCommand();
            break;
        case CommandHardStop:
            return new HardStopCommand();
            break;
        case CommandSoftStop:
            return new SoftStopCommand();
            break;
        case CommandMoveTo:
            return new MoveToCommand();
            break;
        case CommandRun:
            return new RunCommand();
            break;
        case CommandAddLast:
            return new AddLastCommand();
            break;
        /*case CommandMacro:
            return new MacroCommand();
            break;*/
        default:
            throw std::runtime_error("unknown command");
            break;
        }
    }
private:
    int operationID;
};
