#ifndef LAB1_POINT_H
#define LAB1_POINT_H
#include <iostream>

class Point {
protected:
    double x_;
    double y_;
public:
    Point(double x, double y);

    Point(const Point &p);

    double x() const;

    double y() const;

    Point &operator=(const Point &p1);

    double v_len() const;

};

std::ostream &operator<<(std::ostream &out, const Point& p);

Point operator+(const Point &p1, const Point &p2);

Point operator/(const Point &p1, double a);

Point operator*(const Point &p1, double a);

#endif //LAB1_POINT_H
