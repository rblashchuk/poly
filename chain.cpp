#include "chain.h"

Chain::Chain(const Chain &c) = default;

Chain &Chain::operator=(const Chain &c1) = default;

Chain::Chain() {
    vertices_ = {};
    len_ = 0;
}

Chain::Chain(const std::vector<Point> &vertices) {
    if (vertices.size() < 2) {
        std::cerr << "\nError: number of vertices can not be less than 2" << std::endl;
        throw -1;
    }

    for (const Point &point: vertices) {
        vertices_.push_back(point);
    }
    len_ = vertices.size();
}

unsigned int Chain::get_len() const {
    return len_;
}

std::vector<Point> Chain::get_vertices() {
    return vertices_;
}

int Chain::add_point(const Point &a) {
    vertices_.push_back(a);
    len_ += 1;
    return len_;
}

int Chain::del_point(unsigned int index) {
    if (index >= len_) return -1;
    vertices_.erase(this->vertices_.begin() + index);
    len_ -= 1;
    return len_;
}

double Chain::length() {
    double cnt = 0;
    for (int i = 1; i < len_; i++) {
        double x1 = vertices_[i].x();
        double x2 = vertices_[i - 1].x();
        double y1 = vertices_[i].y();
        double y2 = vertices_[i - 1].y();
        cnt += sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));

    }
    return cnt;
}

std::ostream &operator<<(std::ostream &out, Chain c) {
    unsigned int len = c.get_len();
    std::vector<Point> vertices = c.get_vertices();
    for (int i = 0; i < len; i++) {
        out << vertices[i];
    }
    return out;
}


ClosedChain &ClosedChain::operator=(const ClosedChain &c1) = default;

ClosedChain::ClosedChain(const ClosedChain &c) = default;

ClosedChain::ClosedChain() = default;

ClosedChain::ClosedChain(const std::vector<Point> &vertices) : Chain(vertices) {}

double ClosedChain::perimeter() {

    double ans = length();
    unsigned int n = len_;

    double x1 = vertices_[0].x();
    double x2 = vertices_[n - 1].x();
    double y1 = vertices_[0].y();
    double y2 = vertices_[n - 1].y();
    ans += sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    return ans;
}

bool ClosedChain::self_intersected() {
    bool intersected = false;
    for (int i = 0; i < len_ - 2; i++) {
        for (int j = i + 2; j < len_; j++) {
            Point p1 = vertices_[i];
            Point p2 = vertices_[i + 1];
            Point p3 = vertices_[j];
            Point p4 = vertices_[(j + 1) % len_];
            double a1 = p2.y() - p1.y();
            double b1 = p1.x() - p2.x();
            double c1 = p2.x() * p1.y() - p1.x() * p2.y();

            double a2 = p4.y() - p3.y();
            double b2 = p3.x() - p4.x();
            double c2 = p4.x() * p3.y() - p3.x() * p4.y();

            double denom = a1 * b2 - a2 * b1;

            if (abs(denom) < 0.00000001) continue;
            else {
                double x = (-b2 * c1 + b1 * c2) / denom;
                double y = (-a1 * c2 + a2 * c1) / denom;
                if ((((x - p1.x()) * (x - p2.x()) < -0.00000001) || \
                    ((y - p1.y()) * (y - p2.y()) < -0.00000001)) && \
                    (((x - p3.x()) * (x - p4.x()) < -0.00000001) || \
                    ((y - p3.y()) * (y - p4.y()) < -0.00000001))) {
                    return true;
                } else continue;
            }
        }
    }

    return intersected;
}
