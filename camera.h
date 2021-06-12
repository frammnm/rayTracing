#pragma once


#include "utilities.h"

class camera {
    public:
        camera() {
            auto aspect_ratio = 16.0 / 9.0;
            auto viewport_height = 2.0;
            auto viewport_width = aspect_ratio * viewport_height;
            auto focal_length = 1.0;

            origin = p3(0, 0, 0);
            horizontal = vect3(viewport_width, 0.0, 0.0);
            vertical = vect3(0.0, viewport_height, 0.0);
            lower_left_corner = origin - horizontal/2 - vertical/2 - vect3(0, 0, focal_length);
        }

        ray get_ray(double u, double v) const {
            return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
        }

    private:
        p3 origin;
        p3 lower_left_corner;
        vect3 horizontal;
        vect3 vertical;
};