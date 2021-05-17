#pragma once

#include "vect3.h"

class ray {
    public:
        ray() {}
        ray(const p3& origin, const vect3& direction)
            : orig(origin), dir(direction)
        {}

        p3 origin() const;
        vect3 direction() const;
        p3 at(double t) const;
        

    public:
        p3 orig;
        vect3 dir;
};