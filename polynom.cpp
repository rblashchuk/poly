//
// Created by rblas on 03.03.2022.
//

#include "polynom.h"
#include <iostream>

void fourier(std::vector<base> &a, bool invert) {
    int n = (int) a.size();
    if (n == 1) return;

    std::vector<base> a0(n / 2), a1(n / 2);
    for (int i = 0, j = 0; i < n; i += 2, ++j) {
        a0[j] = a[i];
        a1[j] = a[i + 1];
    }
    fourier(a0, invert);
    fourier(a1, invert);

    double alpha = 2 * PI / n * (invert ? -1 : 1);
    base omega(1), omega_n(cos(alpha), sin(alpha));
    for (int i = 0; i < n / 2; ++i) {
        a[i] = a0[i] + omega * a1[i];
        a[i + n / 2] = a0[i] - omega * a1[i];
        if (invert)
            a[i] /= 2, a[i + n / 2] /= 2;
        omega *= omega_n;
    }
}

void mult(const std::vector<double> &a, const std::vector<double> &b, std::vector<double> &res) {
    std::vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    size_t n = 1;
    while (n < std::max(a.size(), b.size())) n <<= 1;
    n <<= 1;

    fa.resize(n);
    fb.resize(n);

    fourier(fa, false);
    fourier(fb, false);

    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];

    fourier(fa, true);

    res.resize(n);
    for (int i = 0; i < n; i++)
        res[i] = fa[i].real();
}

Polynomial::Polynomial(const Polynomial &P) = default;

Polynomial &Polynomial::operator=(const Polynomial &P) = default;


Polynomial::Polynomial() {
    coef_ = {};
    deg_ = 0;
}

Polynomial::Polynomial(const std::vector<double> &coef) {
    for (const double &a: coef) {
        coef_.push_back(a);
    }
    deg_ = coef.size() - 1;
    cut_zeroes();
}

unsigned int Polynomial::get_deg() const {
    return deg_;
}

std::vector<double> Polynomial::get_coef() const {
    return coef_;
}

void Polynomial::cut_zeroes() {
    while (coef_[deg_] == 0) {
        coef_.pop_back();
        deg_ -= 1;
    }
    if (deg_ < 0) deg_ = 0;
}

double Polynomial::operator[](unsigned int i) {
    if (i > deg_) return 0;
    else return coef_[i];
}

Polynomial operator*(Polynomial &P, const double a) {
    std::vector<double> res;
    res.reserve(P.deg_);
    for (int i = 0; i <= P.deg_; i++) res.push_back(P[i] * a);
    return {res};
}

Polynomial operator+(Polynomial &P1, Polynomial &P2) {
    std::vector<double> res;
    unsigned int deg = std::max(P1.deg_, P2.deg_);
    for (int i = 0; i <= deg; i++) {
        res.push_back(P1[i] + P2[i]);
    }
    return {res};
}

Polynomial operator/(Polynomial &P, const double a) {
    std::vector<double> res;
    res.reserve(P.deg_);
    for (int i = 0; i < P.deg_; i++) res.push_back(P[i] / a);
    return {res};
}

std::ostream &operator<<(std::ostream &out, const Polynomial& P) {
    out << P.coef_[0] << " + ";
    for (int i = 1; i < P.deg_; i++) {
        out << P.coef_[i] << "*x^" << i << " + ";
    }
    out << P.coef_[P.deg_] << "*x^" << P.deg_;
    return out;
}

bool operator==(Polynomial &P1, Polynomial &P2) {
    if (P1.deg_ != P2.deg_) return false;

    for (int i = 0; i <= P1.deg_; i++) {
        if (P1[i] != P2[i]) return false;
    }
    return true;
}

bool operator!=(Polynomial &P1, Polynomial &P2) {
    return !(P1 == P2);
}

Polynomial operator-(Polynomial &P1) {
    return P1 * (-1);
}

Polynomial operator*(const Polynomial &P1, const Polynomial &P2)  {
    std::vector<double> a = P1.coef_;
    std::vector<double> b = P2.coef_;
    std::vector<double> ans = {};
    mult(a, b, ans);
    Polynomial Pans = Polynomial(ans);
    return Pans;
}




