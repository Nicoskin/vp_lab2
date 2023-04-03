#include "Coordinates.h"
#include <cmath>

Coordinates::Coordinates() : x(0), y(0) {}

Coordinates::Coordinates(double x0, double y0) : x(x0), y(y0) {}

double Coordinates::distance_to_target(const Coordinates& other) const {
    double dx = other.x - x;
    double dy = other.y - y;
    return std::sqrt(dx * dx + dy * dy);
}
