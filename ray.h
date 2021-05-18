#pragma once

#include <glm/glm.hpp>


class ray {
    public:
        ray() {}
        ray(const glm::vec3& origin, const glm::vec3& direction)
            : orig(origin), dir(direction)
        {}

        glm::vec3 origin() const;
        glm::vec3 direction() const;
        glm::vec3 at(double t) const;
        

    public:
        glm::vec3 orig;
        glm::vec3 dir;
};
