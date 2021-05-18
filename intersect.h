#pragma once

#include "vect3.h"
#include "ray.h"

#include <iostream>

bool RayIntersectsTriangle(ray* rayInput, 
                           vect3* inTriangle,
                           vect3& outIntersectionPoint)
{
    const float EPSILON = 0.0000001;
    vect3 vertex0 = inTriangle[0];
    vect3 vertex1 = inTriangle[1];  
    vect3 vertex2 = inTriangle[2];
    vect3 edge1, edge2, h, s, q;
    float a,f,u,v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    h = rayInput->direction().cross(edge2);
    a = edge1.dot(h);
    if (a > -EPSILON && a < EPSILON)
        return false;    // This ray is parallel to this triangle.
    f = 1.0/a;
    s = rayInput->origin() - vertex0;
    u = f * s.dot(h);
    if (u < 0.0 || u > 1.0)
        return false;
    q = s.cross(edge1);
    v = f * rayInput->direction().dot(q);
    if (v < 0.0 || u + v > 1.0)
        return false;
    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = f * edge2.dot(q);
    if (t > EPSILON) // ray intersection
    {
        outIntersectionPoint = rayInput->at(t);
        return true;
    }
    else // This means that there is a line intersection but not a ray intersection.
        return false;
}
