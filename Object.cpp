#include "Object.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <windows.h>

using namespace std;

Object::Object(int object_id, double x0, double y0)
    : id(object_id), current_position(x0, y0) {
    path.push_back(current_position);
}

double  Object::distance_traveled() const {
    double distance = 0;
    for (size_t i = 1; i < path.size(); ++i) {
        distance += path[i].distance_to_target(path[i - 1]);
    }
    return distance;
}

void  Object::move() {
    std::srand(std::time(nullptr));
    double x = current_position.x + ((std::rand() % 5) - 2);
    double y = current_position.y + ((std::rand() % 5) - 2);
    if (x > 9) x = 9 - current_position.x;
    if (y > 9) y = 9 - current_position.y;
    if (x < 0) x = -current_position.x;
    if (y < 0) y = -current_position.y;
    current_position = Coordinates(x, y);
    path.push_back(current_position);
}

void  Object::print() const {
    std::cout << "Object id: " << id << '\n';
    std::cout << "Current position: (" << current_position.x << ", " << current_position.y << ")\n";
    std::cout << "Distance traveled: " << distance_traveled() << '\n';
    std::cout << "Distance to target: " << current_position.distance_to_target(Coordinates(10, 10)) << '\n';

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (i == std::round(current_position.y) && j == std::round(current_position.x)) {
                std::cout << "S ";
            } else {
                std::cout << "- ";
            }
        }
        std::cout << '\n';
    }

    std::cout << '\n';
    Sleep(1000);
    system("cls");
};