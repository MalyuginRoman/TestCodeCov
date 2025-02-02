#include "object.h"
#include "imoving.h"
 
MovingAdapter::MovingAdapter(IocContainer<ICommand> ioc,
                                 std::map<std::string, std::function<ICommand*()>> m_map,
                                 std::map<std::string, std::string> m_scope,
                                 object *obj) :
        ioc(ioc), m_map(m_map), m_scope(m_scope), obj(obj) {}
bool MovingAdapter::getPosition(object *obj, int dt)
{
  //ioc.resolve("Spaceship.Operations.IMovable:position.get", m_map, m_scope, obj);
  return 0;
}
bool MovingAdapter::setPosition(object *obj)
{
  //ioc.resolve("Spaceship.Operations.IMovable:position.set", m_map, m_scope, obj,
  //newValue).Execute();
  return 0;
}
bool MovingAdapter::getVelocity(object *obj, int du)
{
  //ioc.resolve("Spaceship.Operations.IMovable:velocity.get", m_map, m_scope, obj);
  return 0;
}
bool MovingAdapter::setVelocity(object *obj)
{
  return 0;
}
