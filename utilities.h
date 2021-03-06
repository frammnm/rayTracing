#pragma once

#include <random>
#include <cmath>
#include <limits>
#include <memory>


#include "ray.h"
// #include "vect3.h"

using p3 = glm::vec3;   // 3D point
using color = glm::vec3;    // RGB color

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385;

// Utility Functions

inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}


