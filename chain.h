#include <iostream>
#include <vector>
#include "point.h"

#ifndef LAB1_CHAIN_H
#define LAB1_CHAIN_H


class Chain {
protected:
    std::vector<Point> vertices_;
    unsigned int len_;
public:
    Chain(const Chain &c);

    Chain &operator=(const Chain &c1);

    Chain();

    Chain(const std::vector<Point> &vertices);


    unsigned int get_len() const;

    std::vector<Point> get_vertices();

    int add_point(const Point& a);

    int del_point(unsigned int index);

    double length();
};

std::ostream &operator<<(std::ostream &out, Chain c);


class ClosedChain : public Chain {
public:
    ClosedChain &operator=(const ClosedChain &c1);

    ClosedChain(const ClosedChain &c);

    ClosedChain();

    ClosedChain(const std::vector<Point> &vertices);

    double perimeter();

    bool self_intersected();
};


#endif //LAB1_CHAIN_H
