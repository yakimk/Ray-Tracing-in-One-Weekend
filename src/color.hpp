#pragma once

#include "vec3.hpp"
#include<iostream>

void flush_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
    auto r = pixel_color.x1();
    auto g = pixel_color.x2();
    auto b = pixel_color.x3();

    auto scale = samples_per_pixel;
    r /= scale;
    g /=scale;
    b /= scale;

    out << static_cast<int>(255.999 * clamp(0,.999,r)) << ' '
        << static_cast<int>(255.999 *clamp(0,.999,g) ) << ' '
        << static_cast<int>(255.999 * clamp(0,.999,b)) << '\n';
}
