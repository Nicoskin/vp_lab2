#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <windows.h>
#include <vector>

#pragma once

#define MAT 20

class Coordinates {
public:
    double x;
    double y;
    double z;

    Coordinates();
    Coordinates(double x0, double y0);

    double distance_to_target(const Coordinates& other) const;
};

Coordinates::Coordinates() : x(0), y(0), z(0) {}

Coordinates::Coordinates(double x0, double y0) : x(x0), y(y0), z(0) {}

double Coordinates::distance_to_target(const Coordinates& other) const {
    double dx = other.x - x;
    double dy = other.y - y;
    return std::sqrt(dx * dx + dy * dy);
}


class Object {
private:
    int id;
    std::vector<Coordinates> path;
    Coordinates current_position;
public:
    Object(int object_id, double x0, double y0);

    double distance_traveled() const;

    double distance_to_target(double lat, double lon) const;

    void move();

    void print() const;

    double get_x() const { return current_position.x; }

    double get_y() const { return current_position.y; }

    double get_z() const { return current_position.z; }
};

Object::Object(int object_id, double x0, double y0)
    : id(object_id), current_position(x0, y0) {
    path.push_back(current_position);
}

double Object::distance_traveled() const {
    double distance = 0;
    for (size_t i = 1; i < path.size(); ++i) {
        distance += path[i].distance_to_target(path[i - 1]);
    }
    return distance;
}

double Object::distance_to_target(double x, double y) const {
    const double earth_radius = 6371000;
    double lat1 = asin(get_z() / earth_radius);
    double lon1 = atan2(get_x(), get_y());
    double alt1 = 0;

    double lat2 = asin(z / earth_radius);//z
    double lon2 = atan2(x, y);
    double alt2 = 0;

    double dx = (lon2 - lon1) * cos((lat1 + lat2) / 2);
    double dy = lat2 - lat1;
    double dz = alt2 - alt1;

    double dist = sqrt(dx * dx + dy * dy + dz * dz) * earth_radius;
    return dist;
}

void Object::move() {
    std::srand(std::time(nullptr));
    double x = current_position.x + ((std::rand() % 5) - 2);
    double y = current_position.y + ((std::rand() % 5) - 2);
    if (x > MAT-1) x = MAT-1 - current_position.x;
    if (y > MAT-1) y = MAT-1 - current_position.y;
    if (x < 0) x = -current_position.x;
    if (y < 0) y = -current_position.y;
    current_position = Coordinates(x, y);
    path.push_back(current_position);
}

void Object::print() const {
    std::cout << "Object id: " << id << '\n';
    std::cout << "Current position: (" << current_position.x << ", " << current_position.y << ")\n";
    std::cout << "Distance traveled: " << distance_traveled() << '\n';
    std::cout << "Distance to target: " << distance_to_target(10, 10) << '\n';
    //std::cout << "x = "<< get_x() << "     y = " << get_y() << '\n';

    for (int i = 0; i < MAT; ++i) {
        for (int j = 0; j < MAT; ++j) {
            if (i == std::round(current_position.y) && j == std::round(current_position.x)) {
                std::cout << "S ";
            } else {
                std::cout << "- ";
            }
        }
        std::cout << '\n';
    }

    std::cout << '\n';
    Sleep(1500);
    system("cls");
};

class UserEquipment : public Object {
private:
    double Lat; //широта
    double Lon; //долгота
    double Alt; //высота
public:
    UserEquipment(int object_id, double x0, double y0)
        : Object(object_id, x0, y0) {}

    void move() {
        Object::move();
        convert_to_geographic_coordinates(get_x(),get_y(),get_z());
    }

    void convert_to_geographic_coordinates(double x, double y, double z) {
        double earth_radius = 6371000; // в метрах
        Lat = asin(z / earth_radius);
        Lon = atan2(y, x);
        Alt = z + earth_radius;
    }

    void print() const {
        Object::print();
        std::cout << "Geographic coordinates: (" << Lat << ", " << Lon << ", " << Alt << ")\n";
    }

    double get_lat(double x, double y, double z) const { return asin(z / 6371000); }
    double get_lon(double x, double y, double z) const { return atan2(y, x); }

    
};

int main() {
    UserEquipment ue(10, 10, 3);
    while (true) {
        ue.move();
        ue.print();
    }
    return 0;
}