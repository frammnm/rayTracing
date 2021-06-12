#pragma once

#include <glm/glm.hpp>
#include "utilities.h"

class camera {
    public:
        camera() {
            auto aspect_ratio = 16.0 / 9.0;
            auto viewport_height = 2.0;
            auto viewport_width = aspect_ratio * viewport_height;
            auto focal_length = 1.0;


            origin = glm::vec3(0.0f, 0.0f, 1.0f);
            horizontal = glm::vec3(viewport_width, 0.0, 0.0);
            vertical = glm::vec3(0.0, viewport_height, 0.0);
            lower_left_corner = origin - horizontal/2.0f - vertical/2.0f - glm::vec3(0, 0, focal_length);
        }

        ray get_ray(float u, float v) const {
            return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
        }

        glm::vec3 return_origin() const {
            return origin;
        }

    private:
        glm::vec3 origin;
        glm::vec3 lower_left_corner;
        glm::vec3 horizontal;
        glm::vec3 vertical;
};