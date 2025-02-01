#pragma once
#include <list>
#include <string>

class object
{
public:
    object(int id, int velocity, double angular, double angularVelocity, int placeX, int placeY);
    ~object();

    int id() const;
    int velocity() const;
    double angular() const;
    double angularVelocity() const;
    int placeX() const;
    int placeY() const;
    void setVelocity(int value);
    void setAngular(double value);
    void setAngularVelocity(double value);
    void setPlaceX(int value);
    void setPlaceY(int value);
private:
    class objectP* imp;
};

class objectList
{
public:
    objectList();
    ~objectList();
    void reset();


    int defaultVelocity() const;
    double defaultAngular() const;
    double defaultAngularVelocity() const;
    int defaultPlaceX() const;
    int defaultPlaceY() const;
    void setDefaultVelocity(int value);
    void setDefaultAngular(double value);
    void setDefaultAngularVelocity(double value);
    void setDefaultPlaceX(int value);
    void setDefaultPlaceY(int value);

    object* add(int id, int velocity, double angular, double angularVelocity, int placeX, int placeY);
    bool isEmpty() const;
    int count() const;
    const std::list<object *>& list() const;
private:
    class objectListP* imp;
};
