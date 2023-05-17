#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <windows.h>
#include <vector>
#include <iomanip>

#pragma once

#define MAT 20

//#54.4595,83.3800,14z,54.468142,83.355417i,tb
//#54.4595,83.3800,14z,54.445739,83.403654i,tb
class Coordinates {
public:
    int x;
    int y;
    int z;

    Coordinates();
    Coordinates(int x0, int y0);

    int distance_to_target(const Coordinates& other) const;
};

Coordinates::Coordinates() : x(0), y(0), z(0) {}

Coordinates::Coordinates(int x0, int y0) : x(x0), y(y0), z(0) {}

int Coordinates::distance_to_target(const Coordinates& other) const {
    int dx = other.x - x;
    int dy = other.y - y;
    return std::sqrt(dx * dx + dy * dy);
}


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

Object::Object(int object_id, int x0, int y0)
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

double Object::distance_to_target(int x, int y) const {
    const double R = 6371.0; // радиус Земли в километрах
    //std::cout << "d: x = " << x << " y = " << y << "get_x = "<<  get_x()<< "get_y = "<< get_y()<< std::endl;
    double lat1 = (x * (54.445739 - 54.468142) / (1000 - 1) + 54.468142) * M_PI / 180.0;
    double lon1 = (y * (83.403654 - 83.355417) / (1000 - 1) + 83.355417) * M_PI / 180.0;
    double lat2 = (get_x() * (54.445739 - 54.468142) / (1000 - 1) + 54.468142) * M_PI / 180.0;
    double lon2 = (get_y() * (83.403654 - 83.355417) / (1000 - 1) + 83.355417) * M_PI / 180.0;
    //std::cout << "lat1 = " << lat1 << "  lat2 = " << lat2 << "  lon1 = " << lon1 << "  lon2 = " << lon2 << std::endl;
    // вычисление расстояния по формуле Гаверсина
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;
    double a = std::sin(dLat/2) * std::sin(dLat/2) +
               std::cos(lat1) * std::cos(lat2) *
               std::sin(dLon/2) * std::sin(dLon/2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1-a));
    double d = R * c * 1000;
    return d;
}

void Object::move() {
    std::srand(std::time(nullptr));
    double x = current_position.x + ((std::rand() % 5) - 2);
    double y = current_position.y + ((std::rand() % 5) - 2);
    if (x > MAT-1) x = MAT-1 - current_position.x;
    if (y > MAT-1) y = MAT-1 - current_position.y;
    if (x < 0) x = -x;
    if (y < 0) y = -y;
    current_position = Coordinates(x, y);
    path.push_back(current_position);
}

void Object::print() const {
    std::cout << "Object id: " << id << '\n';
    std::cout << "Current position: (" << current_position.x << ", " << current_position.y << ")\n";
    std::cout << std::fixed << std::setprecision(0);
    std::cout << "Distance traveled: " << distance_traveled() << '\n';
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Distance to target: " << distance_to_target(5, 5) << '\n';
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
    //#54.4595,83.3800,14z,54.468142,83.355417i,tb
    //#54.4595,83.3800,14z,54.445739,83.403654i,tb
    //
    void convert_to_geographic_coordinates(double x, double y, double z) {

        Lat = x * (54.445739 - 54.468142) / (1000 - 1) + 54.468142;
        Lon = y * (83.403654 - 83.355417) / (1000 - 1) + 83.355417;
        Alt = z;
    }

    void print() const {
        Object::print();
        std::cout << std::fixed << std::setprecision(6);
        std::cout << "Geographic coordinates: (" << Lat << ", " << Lon << ", " << Alt << ")\n";
    }

    double get_lat(double x) const { return x * (54.445739 - 54.468142) / (1000 - 1) + 54.468142; }
    double get_lon(double y) const { return y * (83.403654 - 83.355417) / (1000 - 1) + 83.355417; }

    
};

int main() {
    UserEquipment ue(1, 1, 3);
    while (true) {
        ue.move();
        ue.print();
    }
    return 0;
}