#pragma once
#include "Object.h"
#include <iostream>
#include <cmath>

class UserEquipment : public Object {
private:
    double Lat; //широта
    double Lon; //долгота
public:
    UserEquipment(int object_id, double x0, double y0)
        : Object(object_id, x0, y0) {}

    void move() {
        Object::move();
        convert_to_geographic_coordinates();
    }

    void convert_to_geographic_coordinates() {
        double earth_radius = 6371000; // в метрах
        double x = get_x() * M_PI / 180.0;
        double y = get_y() * M_PI / 180.0;
        Lat = y * earth_radius;
        Lon = x * earth_radius * cos(y);
    }

    void print() const {
        Object::print();
        std::cout << "Geographic coordinates: (" << Lat << ", " << Lon << ")\n";
    }

};
