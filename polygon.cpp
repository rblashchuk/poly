//
// Created by rblas on 03.03.2022.
//
#include "chain.h"
#include "polygon.h"
const double PI = 3.141592653589793;

Polygon::Polygon() : ClosedChain() {}

Polygon::Polygon(const Polygon &p) = default;

Polygon &Polygon::operator=(const Polygon &c1) = default;

Polygon::Polygon(const std::vector<Point> &vertices)
        : ClosedChain(vertices) {
    if (this->self_intersected()) {
        std::cerr << "\nError: Chain has self-intersection(s).\n" << std::endl;
        throw -1;
    }
}

double Polygon::oriented_area() {
    double s = 0;
    for (int i = 0; i < len_; i++) {
        s += vertices_[i].x() * vertices_[(i + 1) % len_].y();
        s -= vertices_[(i + 1) % len_].x() * vertices_[i].y();
    }
    return s / 2;
}

Triangle::Triangle(const Triangle &t) = default;

Triangle &Triangle::operator=(const Triangle &c1) = default;

Triangle::Triangle(const std::vector<Point> &vertices) : Polygon(vertices) {
    if (this->get_len() - 3) {
        std::cerr << "\nError: That's not a triangle.\n" << std::endl;
        throw -1;
    }
    Point A = vertices_[0];
    Point B = vertices_[1];
    Point C = vertices_[2];

    a_side_ = sqrt(pow((B.x() - C.x()), 2) + pow((B.y() - C.y()), 2));
    b_side_ = sqrt(pow((A.x() - C.x()), 2) + pow((A.y() - C.y()), 2));
    c_side_ = sqrt(pow((A.x() - B.x()), 2) + pow((A.y() - B.y()), 2));

}

Point Triangle::a() {
    return vertices_[0];
}

Point Triangle::b() {
    return vertices_[1];
}

Point Triangle::c() {
    return vertices_[2];
}

Point Triangle::incenter() {
    double denom = a_side_ + b_side_ + c_side_;
    double x = (a_side_ * a().x() + b_side_ * b().x() + c_side_ * c().x()) / denom;
    double y = (a_side_ * a().y() + b_side_ * b().y() + c_side_ * c().y()) / denom;
    return {x, y};
}

Point Triangle::centroid() {
    return {(a().x() + b().x() + c().x()) / 3, (a().y() + b().y() + c().y()) / 3};
}

Trapezoid &Trapezoid::operator=(const Trapezoid &c1) = default;

Trapezoid::Trapezoid(const std::vector<Point> &vertices) : Polygon(vertices) {
    if (this->get_len() - 4) {
        std::cerr << "\nError: not a quadrilateral.\n" << std::endl;
        throw -1;
    }
    Point p1 = vertices_[0];
    Point p2 = vertices_[1];
    Point p3 = vertices_[2];
    Point p4 = vertices_[3];
    if ((abs((p1.x() - p2.x()) * (p3.y() - p4.y()) - \
            (p3.x() - p4.x()) * (p1.y() - p2.y())) > 0.00000001) && \
            (abs((p2.x() - p3.x()) * (p4.y() - p1.y()) - \
            (p4.x() - p1.x()) * (p2.y() - p3.y())) > 0.00000001)) {

        std::cerr << "\nError: not a trapezoid.\n" << std::endl;
        throw -1;

    }

}

RegularPolygon &RegularPolygon::operator=(const RegularPolygon &c1) = default;

RegularPolygon::RegularPolygon(Point p1, Point p2, unsigned int n) : Polygon() {
    if (n < 2) {
        std::cerr << "\nError: number of vertices can not be less than 2" << std::endl;
        throw -1;
    }
    double alpha = PI * (n - 2) / n;
    double side = sqrt(pow(p2.x() - p1.x(), 2) + pow(p2.y() - p1.y(), 2));

    Point M = (p1 + p2) / 2;
    Point orth = Point(p1.y() - p2.y(), p2.x() - p1.x());
    orth = orth / orth.v_len();

    Point O = M + orth * (side * tan(alpha / 2) / 2);


    std::vector<Point> vertices;
    vertices.push_back(p1);
    vertices.push_back(p2);

    double rotate = PI - alpha;

    for (int i = 2; i < n; i++) {
        Point vertex = Point((p1.x() - O.x()) * cos(rotate * i) - (p1.y() - O.y()) * sin(rotate * i) + O.x(), \
                (p1.x() - O.x()) * sin(rotate * i) + (p1.y() - O.y()) * cos(rotate * i) + O.y());
        vertices.push_back(vertex);
    }
    vertices_ = vertices;
    len_ = n;
}

RegularPolygon::RegularPolygon(const std::vector<Point> &vertices) : Polygon(vertices) {
    Point p1 = vertices_[0];
    Point p2 = vertices_[1];
    double side_length = sqrt((p1.x() - p2.x()) * (p1.x() - p2.x()) + (p1.y() - p2.y()) * (p1.y() - p2.y()));
    double vec_prod = p1.x() * p2.x() + p1.y() * p2.y();

    for (int i = 0; i < len_; i++) {
        Point curr_p1 = vertices_[i];
        Point curr_p2 = vertices_[(i + 1) % len_];

        double curr_side = sqrt((curr_p1.x() - curr_p2.x()) * (curr_p1.x() - curr_p2.x()) +
                                (curr_p1.y() - curr_p2.y()) * (curr_p1.y() - curr_p2.y()));
        double curr_v_pr = curr_p1.x() * curr_p2.x() + curr_p1.y() * curr_p2.y();

        if ((abs(curr_side - side_length) > 0.00000001) ||
            (abs(curr_v_pr - vec_prod) > 0.00000001)) {
            std::cerr << "\nError: this Polygon is not regular\n" << std::endl;
            throw -1;
        }
    }
}

