#pragma once

#include <cmath>
#include <iostream>

using std::sqrt;

class vect3 {
    public:
        vect3();
        vect3(double e0, double e1, double e2);

        double e[3];
        double x() const;
        double y() const;
        double z() const;

        friend std::ostream& operator << (std::ostream& os, const vect3& v);
        vect3 operator-() const;
        double operator[](int i) const;
        double& operator[](int i);

        vect3 operator+(vect3 v) const;

        vect3 operator-(vect3 v) const;

        vect3 operator*(vect3 v) const;

        vect3 operator*(double t) const;

        // vect3 operator*(vect3 v, double t);

        vect3 operator/(double t);

        vect3& operator+=(vect3 v);

        vect3& operator*=(const double t);

        vect3& operator/=(const double t);

        double dot(vect3 v);

        vect3 cross(vect3 v);

        vect3 unit_vector();

        double length() const;

        double length_squared() const;

};


vect3 operator*(double t, const vect3 &v);

// Type aliases for vec3
using p3 = vect3;   // 3D point
using color = glm::vec3 ;    // RGB color