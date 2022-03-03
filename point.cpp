#include "point.h"
#include <cmath>
#include <iostream>

Point::Point(double x, double y) : x_(x), y_(y) {}

Point::Point(const Point &p) = default;

double Point::x() const {
    return Point::x_;
};

double Point::y() const {
    return Point::y_;
}

Point& Point::operator=(const Point &p1) = default;

double Point::v_len() const {
    return (sqrt(x_ * x_ + y_ * y_));
}


std::ostream &operator<<(std::ostream &out, const Point &p) {
    out << "(" << p.x() << ", " << p.y() << ")\n";
    return out;
}

Point operator+(const Point &p1, const Point &p2) {
    Point res(p1.x() + p2.x(), p1.y() + p2.y());
    return res;
}

Point operator/(const Point &p1, const double a) {
    Point res(p1.x() / a, p1.y() / a);
    return res;
}

Point operator*(const Point &p1, const double a) {
    Point res(p1.x() * a, p1.y() * a);
    return res;
}

