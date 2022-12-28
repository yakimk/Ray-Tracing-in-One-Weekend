#pragma once

#include "vec3.hpp"

class ray{
    public:
        point orig;
        vec3 dir;
        ray() {}
        ray(const point& origin, const vec3& direction)
            : orig(origin), dir(direction)
        {}
        point origin(){return orig;}
        vec3 direction(){return dir;}

        point lin(double t) const{
            return orig + t*dir;
        }
};