#include "chain.h"

#ifndef LAB1_POLYGON_H
#define LAB1_POLYGON_H


class Polygon : public ClosedChain {
public:
    Polygon();

    Polygon(const Polygon &p);

    Polygon &operator=(const Polygon &c1);

    Polygon(const std::vector<Point> &vertices);

    double oriented_area();
};

class Triangle : public Polygon {
protected:
    double a_side_;
    double b_side_;
    double c_side_;
public:
    Triangle(const Triangle &t);

    Triangle &operator=(const Triangle &c1);

    Triangle(const std::vector<Point> &vertices);



    Point a();

    Point b();

    Point c();

    Point incenter();

    Point centroid();
};

class Trapezoid : public Polygon {
public:
    Trapezoid &operator=(const Trapezoid &c1);

    Trapezoid(const std::vector<Point> &vertices);
};

class RegularPolygon : public Polygon {
public:
    RegularPolygon &operator=(const RegularPolygon &c1);

    RegularPolygon(Point p1, Point p2, unsigned int n);

    RegularPolygon(const std::vector<Point> &vertices);
};

#endif //LAB1_POLYGON_H
