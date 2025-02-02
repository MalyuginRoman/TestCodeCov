#include "object.h"
#include "irotateble.h"
 
RotatingAdapter::RotatingAdapter(IocContainer<ICommand> ioc,
                                 std::map<std::string, std::function<ICommand*()>> m_map,
                                 std::map<std::string, std::string> m_scope,
                                 object *obj) :
        ioc(ioc), m_map(m_map), m_scope(m_scope), obj(obj) {}
bool RotatingAdapter::getAngular(object *obj, int dt)
{
  //ioc.resolve("Spaceship.Operations.IRotateble:angular.get", m_map, m_scope, obj);
  return 0;
}
bool RotatingAdapter::setAngular(object *obj)
{
  //ioc.resolve("Spaceship.Operations.IRotateble:angular.set", m_map, m_scope, obj,
  //newValue).Execute();
  return 0;
}
bool RotatingAdapter::getAngularVelocity(object *obj, int dv)
{
  //ioc.resolve("Spaceship.Operations.IRotateble:angular_velocity.get", m_map, m_scope, obj);
  return 0;
}
bool RotatingAdapter::setAngularVelocity(object *obj)
{
  //ioc.resolve("Spaceship.Operations.IRotateble:angular_velocity.set", m_map, m_scope, obj,
  //newValue).Execute();
  return 0;
}
