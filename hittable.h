#pragma once

#include "ray.h"

struct hit_record {
    p3 p;
    vect3 normal;
    double t;
    bool front_face;

    inline void set_face_normal(const ray& r, const vect3& outward_normal) {
        front_face = r.direction().dot(outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class hittable {
    public:
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};