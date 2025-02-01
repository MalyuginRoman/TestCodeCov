#pragma once

const int dt = 1;
const int dF = 1;

/*!
  Координаты и ориентация объекта
*/
struct coord
{
    double placeX;
    double placeY;
    double angular;
};

/*!
  Линейная и угловая скорости объекта, запас топлива
*/
struct react
{
    double velocity;
    double angularVelocity;
    double fuel;
};

/*!
  ID номер действия и временной шаг, на котором это действие происходит
*/
class action
{
public:
    action(int actionID, int timeStep);
    ~action();

    int actionID() const;
    int timeStep() const;

private:
    class actionP* imp;
};
