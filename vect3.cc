#include "vect3.h"
#include <cmath>
#include <iostream>

using std::sqrt;


vect3::vect3() : e{0, 0, 0} {}
vect3::vect3(double e0, double e1, double e2) : e{e0, e1, e2} {}

double vect3::x() const { return e[0]; }
double vect3::y() const { return e[1]; }
double vect3::z() const { return e[2]; }

std::ostream& operator << (std::ostream& os, const vect3& v) {
    os << " ( " << v.e[0] << ", " << v.e[1] << ", " << v.e[2] << ") ";
    return os ;
}

vect3 vect3::operator-() const { return vect3(-e[0], -e[1], -e[2]); }
double vect3::operator[](int i) const { return e[i]; }
double& vect3::operator[](int i) { return e[i]; }


vect3 vect3::operator+(vect3 v) const  {
    return vect3(this->e[0] + v.e[0], this->e[1] + v.e[1], this->e[2] + v.e[2]);
}

vect3 vect3::operator-(vect3 v) const {
    return vect3(this->e[0] - v.e[0], this->e[1] - v.e[1], this->e[2] - v.e[2]);
}

vect3 vect3::operator*(vect3 v) const {
    return vect3(this->e[0] * v.e[0], this->e[1] * v.e[1], this->e[2] * v.e[2]);
}

vect3 vect3::operator*(const double t) const {
    return vect3(t*(this->e[0]), t*(this->e[1]), t*(this->e[2]));
}

vect3 operator*(double t, const vect3 &v) {
    return vect3(t*v.e[0], t*v.e[1], t*v.e[2]);
}


vect3 vect3::operator/(const double t) {
    return vect3((this->e[0])/t, (this->e[1])/t, (this->e[2])/t);
}

vect3& vect3::operator+=(vect3 v) {
    e[0] += v.x();
    e[1] += v.y();
    e[2] += v.z();
    return *this;
}

vect3& vect3::operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

vect3& vect3::operator/=(const double t) {
    e[0] /= t;
    e[1] /= t;
    e[2] /= t;
    return *this;
}

double vect3::dot(vect3 v) {
    return this->e[0] * v.e[0]
         + this->e[1] * v.e[1]
         + this->e[2] * v.e[2];
}

vect3 vect3::cross(vect3 v) {
    return vect3(this->e[1] * v.e[2] - this->e[2] * v.e[1],
                this->e[2] * v.e[0] - this->e[0] * v.e[2],
                this->e[0] * v.e[1] - this->e[1] * v.e[0]);
}

vect3 vect3::unit_vector() {
    double t = this -> length();
    return vect3((this->e[0])/t, (this->e[1])/t, (this->e[2])/t);
}

double vect3::length() const {
    return sqrt(length_squared());
}

double vect3::length_squared() const {
    return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
}