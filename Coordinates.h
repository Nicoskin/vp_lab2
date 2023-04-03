#pragma once

class Coordinates {
public:
    double x;
    double y;

    Coordinates();
    Coordinates(double x0, double y0);

    double distance_to_target(const Coordinates& other) const;
};
