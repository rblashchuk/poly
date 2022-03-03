//
// Created by rblas on 03.03.2022.
//
#include <iostream>
#include <vector>
#include <complex>

#ifndef LAB1_POLYNOM_POLYNOM_H
#define LAB1_POLYNOM_POLYNOM_H


typedef std::complex<double> base;
const double PI = 3.141592653589793;


class Polynomial {
public:
    std::vector<double> coef_;
    unsigned int deg_;

    Polynomial(const Polynomial &P);

    Polynomial &operator=(const Polynomial &P);

    Polynomial();

    Polynomial(const std::vector<double> &coef);

    unsigned int get_deg() const;

    std::vector<double> get_coef() const;

    void cut_zeroes();

    double operator[](unsigned int i);
};

Polynomial operator*(Polynomial &P, const double a);

Polynomial operator+(Polynomial &P1, Polynomial &P2);


Polynomial operator/(Polynomial &P, const double a);

std::ostream &operator<<(std::ostream &out, const Polynomial& P);

bool operator==(Polynomial &P1, Polynomial &P2);

bool operator!=(Polynomial &P1, Polynomial &P2);

Polynomial operator-(Polynomial &P1);

Polynomial operator*(const Polynomial &P1, const Polynomial &P2);


#endif //LAB1_POLYNOM_POLYNOM_H
