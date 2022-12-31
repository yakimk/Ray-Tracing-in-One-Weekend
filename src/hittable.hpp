#pragma once

#include "ray.hpp"

struct hit_record{
    point p;
    vec3 normal;
    double t;
    bool front_face;

    inline void set_face_normal(const ray& ray, const vec3& outward_normal){
       front_face = dot(ray.direction(), outward_normal)<0;
<<<<<<< Updated upstream
       normal = front_face ? outward_normal :-outward_normal;
=======
        normal = front_face ? outward_normal :-outward_normal;
>>>>>>> Stashed changes
    }
};

class hittable {
    public:
        virtual bool hit(const ray& ray, double t_min, double t_max, hit_record& rec)const=0;
};