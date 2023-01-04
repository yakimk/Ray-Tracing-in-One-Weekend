#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees){
    return (degrees/180)*pi;
}


inline double random_double(){
    return ((double) rand() / (RAND_MAX));
}

inline double random_double(double min, double max) {
    return min + (max-min)*random_double();
}


inline double clamp(double min, double max, double value){
    if (value>max){return max;}
    if (value<min){return min;}
    return value;
}

#include "ray.hpp"
#include "vec3.hpp"
#include "materail.hpp"