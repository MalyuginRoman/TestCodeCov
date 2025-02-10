#include <iostream>
#include "object.h"
#include "math.h"

const double TR = 0.01745329252;

//******************************* object ******************************
class objectP
{
public:
    int id;
    react state;
    coord place;

    objectP(int id, react state, coord place) :
        id(id),
        state(state),
        place(place)
    { }
    ~objectP()
    { }
};

object::object(int id, react state, coord place) :
    imp(new objectP(id, state, place))
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
react object::state() const
{
    return imp->state;
}
coord object::place() const
{
    return imp->place;
}
void object::setState(react state)
{
    imp->state = state;
}
void object::setPlace(coord place)
{
    imp->place = place;
}

bool object::getPosition(object *obj, int dt)
{
    try
    {
        if(dt > 0)
        {
            coord place = obj->place();
            react state = obj->state();
            double valueV = state.velocity;
            double valueA = place.angular;
            double valueX = valueV * cos(valueA * TR) * dt;
            double valueY = valueV * sin(valueA * TR) * dt;
            place.placeX += valueX;
            place.placeY += valueY;
            obj->setPlace(place);
            return true;
        }
        else
        {
            std::cerr << "It is impossible to move the object with id: " << obj->id() << std::endl;
            throw std::runtime_error ("UnknownTimeStep");
            return false;
        }
    } catch(...) {
        return false;
    }
}

bool object::setPosition(object *obj)
{
    obj->place().placeX;
    obj->place().placeY;
    return true;
}
bool object::getVelocity(object *obj, int du)
{
    try
    {
        react state = obj->state();
        state.velocity = obj->state().velocity + du;
        obj->setState(state);
        return true;
    } catch(...) {
        return false;
    }
}
bool object::setVelocity(object *obj)
{
    obj->state().velocity;
    return true;
}

bool object::getAngular(object *obj, int dt)
{
    try
    {
        if(dt > 0)
        {
            coord place = obj->place();
            double valueA = place.angular;
            react state = obj->state();
            place.angular = valueA + state.angularVelocity * dt;
            obj->setPlace(place);
            return true;
        }
        else
        {
            std::cerr << "It is impossible to rotate the object with id: " << obj->id() << std::endl;
            throw std::runtime_error ("UnknownTimeStep");
            return false;
        }
    } catch(...) {
        return false;
    }
}

bool object::setAngular(object *obj)
{
    obj->place().angular;
    return true;
}
bool object::getAngularVelocity(object *obj, int dv)
{
    react state = obj->state();
    state.angularVelocity = state.angularVelocity + dv;
    obj->setState(state);
    return true;
}
bool object::setAngularVelocity(object *obj)
{
    obj->state().angularVelocity;
    return true;
}

bool object::getFuel(object *obj, int dF)
{
    try
    {
        if(dt > 0)
        {
            react state = obj->state();
            state.fuel = obj->state().fuel - dF;
            obj->setState(state);
            return true;
        }
        else
        {
            std::cerr << "It is impossible to burn fuel the object with id: " << obj->id() << std::endl;
            throw std::runtime_error ("UnknownTimeStep");
            return false;
        }
    } catch(...) {
        return false;
    }
}

//****************************** objectList ***************************
class objectVectorP
{
public:
    std::vector<object*> vector;

    ~objectVectorP()
    {
       vector.clear();
    }
    void reset()
    {
        vector.clear();
    }
    object *add(int id, react state, coord place)
    {
        object* spaceship = new object(id, state, place);
        vector.push_back(spaceship);
        return spaceship;
    }
    object *at(int i)
    {
        return vector.at(i);
    }
};
objectVector::objectVector() : imp(new objectVectorP)
{
}
objectVector::~objectVector()
{
    delete imp;
}
void objectVector::reset()
{
    imp->reset();
}
object *objectVector::add(int id, react state, coord place)
{
    return imp->add(id, state, place);
}
bool objectVector::isEmpty() const
{
    return imp->vector.empty();
}
size_t objectVector::count() const
{
    return imp->vector.size();
}
const std::vector<object *> &objectVector::vector() const
{
    return imp->vector;
}

object *objectVector::at(int i)
{
    return imp->at(i);
}
