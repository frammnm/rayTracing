#include <glm/glm.hpp>

#include "ray.h"


glm::vec3 ray::origin() const  { return orig; }

glm::vec3 ray::direction() const { return dir; }

glm::vec3 ray::at(float t) const {
    return orig + dir * t;
}
