#pragma once
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <functional>
#include <memory>
#include "object.h"
#include "adapter.h"

using namespace std;

class object;

class ICommand
{
public:
    virtual void execute() = 0;
};

class MoveCommand : public ICommand
{
private:
    object* obj;
public:
    MoveCommand(object* obj)
        : obj(obj) {}
    void execute()
    {
        std::cout << "Start execute MoveCommand" << std::endl;
        if(obj->place().placeX < 0 && obj->place().placeY < 0)
            throw std::runtime_error ("Object not found");
        if(!obj->getVelocity(obj, 0))
            throw std::runtime_error ("Unknown velocity");
        std::cout << obj->place().placeX << "," << obj->place().placeY << std::endl;
        if(!obj->getPosition(obj, dt))
            throw std::runtime_error ("Unknown position");
        std::cout << obj->place().placeX << "," << obj->place().placeY << std::endl;
    }
};

class RotateCommand : public ICommand
{
private:
    object* obj;
public:
    RotateCommand(object* obj)
        : obj(obj) {}
    void execute()
    {
        cout << "Start execute RotateCommand" << endl;
        if(obj->place().placeX < 0 && obj->place().placeY < 0)
            throw std::runtime_error ("Object not found");
        if(!obj->getAngularVelocity(obj, 0))
            throw std::runtime_error ("Unknown angular velocity");
        std::cout << obj->place().angular << std::endl;
        if(!obj->getAngular(obj, dt))
            throw std::runtime_error ("Unknown position");
        std::cout << obj->place().angular << std::endl;
    }
};

class CheckCommand : public ICommand
{
private:
    object* obj;
public:
    CheckCommand(object* obj)
        : obj(obj) {}
    void execute()
    {
        std::cout << "Start execute CheckCommand" << std::endl;
        if(obj->state().fuel < 0)
            throw std::runtime_error ("Object has not fuel");
    }
};

class BurnCommand : public ICommand
{
private:
    object* obj;
public:
    BurnCommand(object* obj)
        : obj(obj) {}
    void execute()
    {
        std::cout << "Start execute BurnCommand" << std::endl;
        std::cout << obj->state().fuel << std::endl;
        if(obj->getFuel(obj, dF) < 0)
            throw std::runtime_error ("Not enough fuel");
        std::cout << obj->state().fuel << std::endl;
    }
};

class CreateAdaptor : public ICommand
{
    IocContainer<ICommand> ioc;
    std::map<std::string, std::function<ICommand*()>> m_map;
    std::map<std::string, std::string> m_scope;
    object* obj;
public:
    CreateAdaptor(IocContainer<ICommand> ioc,
                  std::map<std::string, std::function<ICommand*()>> m_map,
                  std::map<std::string, std::string> m_scope,
                  object *obj);
    void execute()
    {
        std::cout << "Start execute CreateAdaptor" << std::endl;
        Adapter *adapt;
        adapt->generate();
        new MovingAdapter(ioc, m_map, m_scope, obj);
    }
};

class MacroCommand : public ICommand
{
public:
    MacroCommand(list<ICommand*> cmds);
    ~MacroCommand();
    list<ICommand*> cmds;
    void execute();
/*    {
        std::cout << "Start execute MacroCommand" << std::endl;
    }*/
private:
    class MacroCommandP* imp; /**/
};

class RegisterCommand : public ICommand
{
public:
    RegisterCommand(std::map<std::string, std::function<ICommand*()>> *m_map, std::map<std::string, std::string> *m_scope);
    ~RegisterCommand();
    std::map<std::string, std::function<ICommand*()>>* m_map;
    std::map<std::string, std::string>* m_scope;
    void execute();
    void registerType(std::string key_s, std::string key_f, std::function<ICommand*()> func);
private:
    class RegisterCommandP* imp;
};
