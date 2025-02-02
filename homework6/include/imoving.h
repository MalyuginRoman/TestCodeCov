#pragma once
#include "ioc.h"

class object;
class ICommand;

class IMoving
{
public:
    virtual bool getPosition(object *obj, int dt) = 0;
    virtual bool setPosition(object *obj) = 0;
    virtual bool getVelocity(object *obj, int du) = 0;
    virtual bool setVelocity(object *obj) = 0;
};

class MovingAdapter : public IMoving
{
    IocContainer<ICommand> ioc;
    std::map<std::string, std::function<ICommand*()>> m_map;
    std::map<std::string, std::string> m_scope;
    int newValue;
    object* obj;
public:
    MovingAdapter(IocContainer<ICommand> ioc,
                  std::map<std::string, std::function<ICommand*()>> m_map,
                  std::map<std::string, std::string> m_scope,
                  object *obj);
    bool getPosition(object *obj, int dt);
    bool setPosition(object *obj);
    bool getVelocity(object *obj, int du);
    bool setVelocity(object *obj);
};
