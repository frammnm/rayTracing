#pragma once

#include "hittable.h"
#include "vect3.h"

class sphere : public hittable {
    public:
        sphere() {}
        sphere(p3 cen, double r) : center(cen), radius(r) {};

        virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        p3 center;
        double radius;
};

