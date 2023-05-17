#pragma once
#define MAT 20
class Coordinates {
public:
    int x;
    int y;
    int z;

    Coordinates();
    Coordinates(int x0, int y0);

    int distance_to_target(const Coordinates& other) const;
};