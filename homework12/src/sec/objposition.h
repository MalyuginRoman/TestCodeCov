#pragma once
#include <map>
#include <list>
#include "object.h"

const double Xmax = 100.;
const double Ymax = 100.;
const int count_system_1 = 4;
const int count_system_2 = 5;
const double eps = 10E-6;

struct coord_interval
{
public:
  double Xmax;
  double Xmin;
  double Ymax;
  double Ymin;
};

struct system_okr
{
public:
  int id_syst_okr;
  bool isEmpty;
  int countObject;
  coord_interval XY;
  std::vector<int> obj_id;
};

struct objectCheck
{
public:
  system_okr p_map;
};

std::map<int, system_okr> func_name(int number)          // формируем системы окрестностей
{
  double Xstart = 0.;
  double Ystart = 0.;
  int sizeXY = 0.;
  std::map<int, system_okr> p_map_c_a;
  int count_system;
  if(number == 1)
    count_system = count_system_1;
  else
    count_system = count_system_2;
  for(int i = 0; i < count_system; i++)
    for(int j = 0; j < count_system; j++)
    {
      system_okr a1;
      a1.XY.Xmin = Xstart + i     * Xmax/count_system;
      a1.XY.Xmax = Xstart +(i + 1)* Xmax/count_system;
      a1.XY.Ymin = Xstart + j     * Ymax/count_system;
      a1.XY.Ymax = Xstart +(j + 1)* Ymax/count_system;
      a1.id_syst_okr = sizeXY;
      a1.isEmpty = true;
      a1.countObject = 0;
      p_map_c_a.emplace(sizeXY, a1);
      sizeXY ++;
    } 
  return p_map_c_a;
}

std::map<int, system_okr> func_obj(std::map<int, system_okr> p_map, objectVector *vector)    // помещаем объекты в системы окрестностей
{
    int countObj = vector->count();
    std::map<int, system_okr> p_map_c = p_map;
    for(int i = 0; i < countObj; i++)
    {
      double current_X = vector->at(i)->place().placeX;
      double current_Y = vector->at(i)->place().placeY;
      int count1 = p_map_c.size();
      for(int j = 0; j < count1; ++j)
      {
        double x1 = p_map_c.at(j).XY.Xmin;
        double x2 = p_map_c.at(j).XY.Xmax;
        double y1 = p_map_c.at(j).XY.Ymin;
        double y2 = p_map_c.at(j).XY.Ymax;
        bool isX = ((x1 - current_X) < eps) && ((current_X - x2) < eps);
        bool isY = ((y1 - current_Y) < eps) && ((current_Y - y2) < eps);
        if(isX && isY)
        {
          p_map_c.at(j).countObject++;
          p_map_c.at(j).isEmpty = false;
          int id_obj = vector->at(i)->id();
          p_map_c.at(j).obj_id.push_back(id_obj);
          break;
        }
      }
    }
    return p_map_c;
}
