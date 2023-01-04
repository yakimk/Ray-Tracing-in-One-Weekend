#pragma once

#include <cmath>
#include<iostream>
#include<stdexcept>
#include "rtweekend.hpp"

using std::sqrt;

class vec3{
    public:
        double x[3];
        vec3() : x{0,0,0} {}
        vec3(double x,  double y, double z):x{x,y,z} {}
        double x1() const { return x[0]; }
        double x2() const { return x[1]; }
        double x3() const { return x[2]; }
        
        vec3 operator - () const{return vec3(-x[0], -x[1], -x[2]);}

        double operator [] (int a) const{return x[a];}
        double& operator [] (int a) {return x[a];}

        vec3 operator += (int a) const{return vec3(x[0]+a, x[1]+a, x[2]+a);}

        vec3& operator += (const vec3 &v) {
            x[0]+=v.x[0];
            x[1]+=v.x[1];
            x[2]+=v.x[2];
            return *this;
        }

        vec3& operator *= (const double m){
            x[0]*=m;
            x[1]*=m;
            x[2]*=m;
            return *this;
        }

        vec3& operator /= (const double m){
            if (m==0){throw std::invalid_argument("Cannot divide by '0'.");}
            return *this*=1/m;
        }

        double len() const{
            return sqrt(pow(x[0],2)+pow(x[1],2)+pow(x[2],2));
        }

        double square_of_len() const{
            return x[0]*x[0]+x[1]*x[1]+x[2]*x[2];
        }

        inline static vec3 random(){return vec3(random_double(), random_double(), random_double());}

        inline static vec3 random(double min, double max){
            return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
            }
        
        bool near_zero()const{
            const auto s = 1e-8;
            return (fabs(x[0])<s) &&(fabs(x[1])<s) &&(fabs(x[2])<s); 
        }
};

using point = vec3;
using color  = vec3;

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.x[0] << ' ' << v.x[1] << ' ' << v.x[2];
}

inline vec3 operator + (const vec3 &v, const vec3 &w){
    return vec3(v.x[0]+w.x[0], v.x[1]+w.x[1], v.x[2]+w.x[2]);
}

inline vec3 operator - (const vec3 &v, const vec3 &w){
    return vec3(v.x[0]-w.x[0], v.x[1]-w.x[1], v.x[2]-w.x[2]);
}

inline vec3 operator * (double s, const vec3 &v) {
    return vec3(s*v.x[0], s*v.x[1], s*v.x[2]);
}

inline vec3 operator * (const vec3 &v, double s) {
    return (s * v);
}

inline vec3 operator/(const vec3 &v, double t) {
    return (1/t) * v;
}

inline double dot (const vec3 &v, const vec3 &w){
    return v.x[0]*w.x[0]+v.x[1]*w.x[1]+v.x[2]*w.x[2];
}

inline vec3 cross(const vec3 &v, const vec3 &w){
    return vec3(
        v.x[1]*w.x[2]-v.x[2]*w.x[1],
        v.x[2]*w.x[0]-v.x[0]*w.x[2],
        v.x[0]*w.x[1]-v.x[1]*w.x[0]
    );
}

inline vec3 normalize(vec3 v){
    return v/v.len();
}

vec3 random_in_unit_sphere(){
    while (true){
        vec3 p = vec3::random(-1,1);
        if (p.square_of_len()>=1){continue;}
        return p;
    }
}

vec3 random_unit_vector(){return normalize(random_in_unit_sphere());}

vec3 random_in_hemisphere(vec3& normal){
    vec3 bounce = random_in_unit_sphere();
    if (dot(normal,bounce)>0){return bounce;}
    return -bounce;
}

vec3 reflect(const vec3& v, const vec3& n){
    return v-2*n*dot(v,n);
}