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
