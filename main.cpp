#include <iostream>
#include "polynom.h"
#include "point.h"
#include "chain.h"
#include "polygon.h"


int main() {
    RegularPolygon pol = RegularPolygon(Point(0, 1), Point(1, 2), 10);
    std::cout << pol;
    std::cout << "_____________" <<std::endl;
    Polynomial P1 = Polynomial({1, 2, 1});
    Polynomial P2 = Polynomial({1, 3, 3, 1});
    Polynomial P3 = Polynomial({1, 3, 3, 1, 0, 0, 0});

    std::cout << P1 << "\n" << P2 << "\n" << P1 + P2 << "\n" << P1 / 2 << "\n"\
    << P2 * 3 << "\n" << (P1 == P2) << "\n" << (P2 == P3) << "\n" << P2 * P3;

}
