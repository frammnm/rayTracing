#include <glm/glm.hpp>

#include "ray.h"


p3 ray::origin() const  { return orig; }

glm::vec3 ray::direction() const { return dir; }

p3 ray::at(double t) const {
    return orig + dir * t;
}
