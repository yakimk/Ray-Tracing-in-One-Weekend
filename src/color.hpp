#pragma once

#include "vec3.hpp"
#include<iostream>

void flush_color(std::ostream &out, color pixel_color) {
    out << static_cast<int>(255.999 * pixel_color.x1()) << ' '
        << static_cast<int>(255.999 * pixel_color.x2()) << ' '
        << static_cast<int>(255.999 * pixel_color.x3()) << '\n';
}
