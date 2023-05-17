#pragma once
#include "Object.h"

class UserEquipment : public Object {
private:
    double Lat; //широта
    double Lon; //долгота
    double Alt; //высота
public:
UserEquipment(int object_id, double x0, double y0);

void move();

void print() const;

double get_lat(double x) const;

double get_lon(double y) const;

void convert_to_geographic_coordinates(double x, double y, double z);
};