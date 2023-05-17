#include "UserEquipment.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <windows.h>
#include <vector>
#include <iomanip>

UserEquipment::UserEquipment(int object_id, double x0, double y0)
: Object(object_id, x0, y0) {}

void UserEquipment::move() {
Object::move();
convert_to_geographic_coordinates(get_x(),get_y(),get_z());
}

void UserEquipment::convert_to_geographic_coordinates(double x, double y, double z) {
Lat = x * (54.445739 - 54.468142) / (1000 - 1) + 54.468142;
Lon = y * (83.403654 - 83.355417) / (1000 - 1) + 83.355417;
Alt = z;
}

void UserEquipment::print() const {
Object::print();
std::cout << std::fixed << std::setprecision(6);
std::cout << "Geographic coordinates: (" << Lat << ", " << Lon << ", " << Alt << ")\n";
}

double UserEquipment::get_lat(double x) const {
return x * (54.445739 - 54.468142) / (1000 - 1) + 54.468142;
}

double UserEquipment::get_lon(double y) const {
return y * (83.403654 - 83.355417) / (1000 - 1) + 83.355417;
}