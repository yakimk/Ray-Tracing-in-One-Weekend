#pragma once

#include "rtweekend.hpp"

class material;

struct hit_record{
    point p;
    vec3 normal;
    double t;
    shared_ptr<material> mat_ptr;
    bool front_face;

    inline void set_face_normal(const ray& ray, const vec3& outward_normal){
       front_face = dot(ray.direction(), outward_normal)<0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class hittable {
    public:
        virtual bool hit(const ray& ray, double t_min, double t_max, hit_record& rec)const=0;
};