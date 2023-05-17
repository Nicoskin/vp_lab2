#pragma once
#include <vector>
#include "Coordinates.h"

class Object {
private:
    int id;
    std::vector<Coordinates> path;
    Coordinates current_position;
public:
Object(int object_id, int x0, int y0);

double distance_traveled() const;

double distance_to_target(int x, int y) const;

void move();

void print() const;

double get_x() const { return current_position.x; }

double get_y() const { return current_position.y; }

double get_z() const { return current_position.z; }
};