#pragma once

#include"hittable.hpp"
#include"vec3.hpp"

class sphere:public hitable{
    public:
        sphere() {}
        sphere(point center, double r) : center(center), r(r) {};

        virtual bool hit(
            
        )
}