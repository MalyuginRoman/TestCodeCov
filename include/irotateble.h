#pragma once
#include "ioc.h"

class object;

class IRotatable
{
public:
    virtual bool getAngular(object *obj, int dt) = 0;
    virtual bool setAngular(object *obj) = 0;
    virtual bool getAngularVelocity(object *obj, int dv) = 0;
    virtual bool setAngularVelocity(object *obj) = 0;
};

class RotatingAdapter : public IRotatable
{
    IocContainer<ICommand> ioc;
    std::map<std::string, std::function<ICommand*()>> m_map;
    std::map<std::string, std::string> m_scope;
    int newValue;
    object* obj;
public:
    RotatingAdapter(IocContainer<ICommand> ioc,
                    std::map<std::string, std::function<ICommand*()>> m_map,
                    std::map<std::string, std::string> m_scope,
                    object *obj);
    bool getAngular(object *obj, int dt);
    bool setAngular(object *obj);
    bool getAngularVelocity(object *obj, int dv);
    bool setAngularVelocity(object *obj);
};
