#pragma once
#include <vector>
#include "Coordinates.h"

class Object {
private:
    int id;
    std::vector<Coordinates> path;
    Coordinates current_position;
public:
    Object(int object_id, double x0, double y0);

    double distance_traveled() const;

    double distance_to_target(const Coordinates& target) const;

    void move();

    void print() const;
};
