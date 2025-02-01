#include "math.h"
#include "MoveCommand.h"
#include "RotateCommand.h"
#include "object.h"

class objectP
{
public:
    int id;
    int velocity;
    double angular;
    double angularVelocity;
    int placeX;
    int placeY;
    objectP(int id, int velocity, double angular, double angularVelocity, int placeX, int placeY) :
        id(id),
        velocity(velocity),
        angular(angular),
        angularVelocity(angularVelocity),
        placeX(placeX),
        placeY(placeY)
    {
    }
};

object::object(int id, int velocity, double angular, double angularVelocity, int placeX, int placeY) :
    imp(new objectP(id, velocity, angular, angularVelocity, placeX, placeY))
{
}
object::~object()
{
    delete imp;
}
int object::id() const
{
    return imp->id;
}
int object::velocity() const
{
    return imp->velocity;
}
double object::angular() const
{
    return imp->angular;
}
double object::angularVelocity() const
{
    return imp->angularVelocity;
}
int object::placeX() const
{
    return imp->placeX;
}
int object::placeY() const
{
    return imp->placeY;
}
void object::setVelocity(int value)
{
    imp->velocity = value;
}
void object::setAngular(double value)
{
    imp->angular = value;
}
void object::setAngularVelocity(double value)
{
    imp->angularVelocity = value;
}
void object::setPlaceX(int value)
{
    imp->placeX = value;
}
void object::setPlaceY(int value)
{
    imp->placeY = value;
}

class objectListP
{
public:
    std::list<object*> list;
    int defaultVelocity;
    double defaultAngular;
    double defaultAngularVelocity;
    int defaultPlaceX;
    int defaultPlaceY;

    objectListP():
        defaultVelocity(0),
        defaultAngular(0.),
        defaultAngularVelocity(0.),
        defaultPlaceX(0),
        defaultPlaceY(0)
    {
    }
    ~objectListP()
    {
        list.clear();
    }
    void reset()
    {
        list.clear();
    }
    object *add(int id, int velocity, double angular, double angularVelocity, int placeX, int placeY)
    {
        object* spaceship = new object(id, velocity, angular, angularVelocity, placeX, placeY);
        list.push_back(spaceship);
        return spaceship;
    }
};
objectList::objectList() : imp(new objectListP)
{
}
objectList::~objectList()
{
    delete imp;
}
void objectList::reset()
{
    imp->reset();
}
int objectList::defaultVelocity() const
{
    return imp->defaultVelocity;
}
double objectList::defaultAngular() const
{
    return imp->defaultAngular;
}
double objectList::defaultAngularVelocity() const
{
    return imp->defaultAngularVelocity;
}
int objectList::defaultPlaceX() const
{
    return imp->defaultPlaceX;
}
int objectList::defaultPlaceY() const
{
    return imp->defaultPlaceY;
}
void objectList::setDefaultVelocity(int value)
{
    imp->defaultVelocity = value;
}
void objectList::setDefaultAngular(double value)
{
    imp->defaultAngular = value;
}
void objectList::setDefaultAngularVelocity(double value)
{
    imp->defaultAngularVelocity = value;
}
void objectList::setDefaultPlaceX(int value)
{
    imp->defaultPlaceX = value;
}
void objectList::setDefaultPlaceY(int value)
{
    imp->defaultPlaceY = value;
}
object *objectList::add(int id, int velocity, double angular, double angularVelocity, int placeX, int placeY)
{
    return imp->add(id, velocity, angular, angularVelocity, placeX, placeY);
}
bool objectList::isEmpty() const
{
    return imp->list.empty();
}
int objectList::count() const
{
    return imp->list.size();
}
const std::list<object *> &objectList::list() const
{
    return imp->list;
}

const double TR = 0.01745329252;

class MoveCommandP
{
public:
    int x;
    int y;
    int v;
    double a1;
    double a2;
    int dt;
    MoveCommandP(int x, int y, double a1, double a2, int v, int dt) :
        x(x),
        y(y),
        a1(a1),
        a2(a2),
        v(v),
        dt(dt)
    {
    }
};

MoveCommand::MoveCommand(int x, int y, double a1, double a2, int v, int dt) :
                         imp(new MoveCommandP(x, y, a1, a2, v, dt))
{ }

bool MoveCommand::getPosition(object *obj, int dt)
{
    obj->setPlaceX(obj->velocity() * cos(obj->angular()*TR) * dt);
    obj->setPlaceY(obj->velocity() * sin(obj->angular()*TR) * dt);
    return true;
}

bool MoveCommand::setPosition(object *obj)
{
    obj->placeX();
    obj->placeY();
    return true;
}
bool MoveCommand::getVelocity(object *obj, int du)
{
    obj->setVelocity(obj->velocity() + du);
    return true;
}
bool MoveCommand::setVelocity(object *obj)
{
    obj->velocity();
    return true;
}

class RotateCommandP
{
public:
    int x;
    int y;
    int v;
    double a1;
    double a2;
    int dt;
    RotateCommandP(int x, int y, double a1, double a2, int v, int dt) :
        x(x),
        y(y),
        a1(a1),
        a2(a2),
        v(v),
        dt(dt)
    {
    }
};

RotateCommand::RotateCommand(int x, int y, double a1, double a2, int v, int dt) :
    imp(new RotateCommandP(x, y, a1, a2, v, dt))
{ }

bool RotateCommand::getAngular(object *obj, int dt)
{
    obj->setAngular(obj->angular() * obj->angularVelocity() * dt);
    return true;
}

bool RotateCommand::setAngular(object *obj)
{
    obj->angular();
    return true;
}
bool RotateCommand::getAngularVelocity(object *obj, int dv)
{
    obj->setAngularVelocity(obj->angularVelocity() + dv);
    return true;
}
bool RotateCommand::setAngularVelocity(object *obj)
{
    obj->angularVelocity();
    return true;
}
