#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <windows.h>

using namespace std;

class Coordinates { // Класс для координат
public:
    double x;
    double y;

    Coordinates() {
        x = 0;
        y = 0;
    }

    Coordinates(double x0, double y0) {
        x = x0;
        y = y0;
    }
};

class Object { // Класс для объекта
public:
    int id;
    vector<Coordinates> path;
    Coordinates current_position;
    // Конструктор
    Object(int object_id, double x0, double y0) {
        id = object_id;
        current_position = Coordinates(x0, y0);
        path.push_back(current_position);
    }

    double distance_traveled() { // Метод для рассчета пройденного расстояния
        double distance = 0;
        for (int i = 1; i < path.size(); i++) {
            distance += sqrt(pow(path[i].x - path[i-1].x, 2) + pow(path[i].y - path[i-1].y, 2));
        }
        return distance;
    }

    double distance_to_target(Coordinates target) { // Метод для рассчета расстояния до цели
        return sqrt(pow(target.x - current_position.x, 2) + pow(target.y - current_position.y, 2));
    }

    void move() { // Метод для перемещения объекта
        srand(time(NULL));
        double x = current_position.x + ((rand() % 5) - 2);
        double y = current_position.y + ((rand() % 5) - 2);
        // Ограничение для перемещения объекта в пределах матрицы 10x10
        if (current_position.x + x > 9) x = 9 - current_position.x;
        if (current_position.y + y > 9) y = 9 - current_position.y;
        if (current_position.x + x < 0) x = -current_position.x;
        if (current_position.y + y < 0) y = -current_position.y;
        current_position = Coordinates(x, y);
        path.push_back(current_position);
    }
};

void print(Object obj, double distance_traveled, double distance_to_target) {
    cout << "Object id: " << obj.id << endl;
    cout << "Current position: (" << obj.current_position.x << ", " << obj.current_position.y << ")" << endl;
    cout << "Distance traveled: " << distance_traveled << endl;
    cout << "Distance to target: " << distance_to_target << endl;
    
    // Вывод матрицы перемещения объекта
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (i == round(obj.current_position.y) && j == round(obj.current_position.x)) {
                cout << "S ";
            } else {
                cout << "- ";
            }
        }
        cout << endl;
    }

    cout << endl;
    Sleep(1000);
    //system("pause");
    system("cls");
}

int main() {
    
    Object obj(1, 5, 5); // Создание объекта и задание начальных координат
    Coordinates target(10, 10); // Создание целевых координат

    while (true) {
        obj.move(); // Перемещение объекта
        // Рассчет расстояний
        double distance_traveled = obj.distance_traveled();
        double distance_to_target = obj.distance_to_target(target);

        print(obj, distance_traveled, distance_to_target);
    }

    return 0;
}
