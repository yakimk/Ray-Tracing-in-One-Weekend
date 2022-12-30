#pragma once

#include "ray.hpp"

struct hit_record{
    point p;
    vec3 normal;
    double t;
};

class hittable {
    public:
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const =0;
};