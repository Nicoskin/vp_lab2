#include "Object.h"
#include "Coordinates.h"

int main() {
    Object obj(1, 5, 5);
    while (true) {
        obj.move();
        obj.print();
    }
    return 0;
}