#include "Coordinates.h"
#include <cmath>

Coordinates::Coordinates() : x(0), y(0), z(0) {}

Coordinates::Coordinates(int x0, int y0) : x(x0), y(y0), z(0) {}

int Coordinates::distance_to_target(const Coordinates& other) const {
    int dx = other.x - x;
    int dy = other.y - y;
    return std::sqrt(dx * dx + dy * dy);
}
