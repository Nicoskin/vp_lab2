#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <windows.h>
#include <vector>
#include <iomanip>
#include "Object.h"
#include "UserEquipment.h"

#define MAT 20

int main() {
    UserEquipment ue(1, 1, 3);
    while (true) {
        ue.move();
        ue.print();
    }
    return 0;
}