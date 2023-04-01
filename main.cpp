#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <windows.h>

class Coordinates {
public:
    double x;
    double y;

    Coordinates() : x(0), y(0) {}
    Coordinates(double x0, double y0) : x(x0), y(y0) {}
};

class Object {
private:
    int id;
    std::vector<Coordinates> path;
    Coordinates current_position;
public:
    Object(int object_id, double x0, double y0)
        : id(object_id), current_position(x0, y0) {
        path.push_back(current_position);
    }

    double distance_traveled() const {
        double distance = 0;
        for (size_t i = 1; i < path.size(); ++i) {
            double dx = path[i].x - path[i - 1].x;
            double dy = path[i].y - path[i - 1].y;
            distance += std::sqrt(dx * dx + dy * dy);
        }
        return distance;
    }

    double distance_to_target(const Coordinates& target) const {
        double dx = target.x - current_position.x;
        double dy = target.y - current_position.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    void move() {
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

    void print() const {
        std::cout << "Object id: " << id << '\n';
        std::cout << "Current position: (" << current_position.x << ", " << current_position.y << ")\n";
        std::cout << "Distance traveled: " << distance_traveled() << '\n';
        std::cout << "Distance to target: " << distance_to_target(Coordinates(10, 10)) << '\n';

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
    }


};

int main() {
    Object obj(1, 5, 5);
    while (true) {
        obj.move();
        obj.print();
    }
    return 0;
}
