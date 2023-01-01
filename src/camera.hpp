#pragma once

#include "rtweekend.hpp"

class camera{
    public:
        camera(){
            auto aspect_ratio = 16/9;
            auto viewport_height = 2;
            auto viewport_width = aspect_ratio * viewport_height;
            auto focal_length = 1;

            origin = point(0,0,0);
            horizontal = vec3(viewport_width, 0,0);
            vertical = vec3(0,viewport_height, 0);
            lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);
        }

        ray get_ray(double u, double v) const {
            return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
        }

    private:
        point origin;
        vec3 horizontal, vertical;
        point lower_left_corner;
};