#pragma once

#include <cmath>
#include<iostream>
#include<stdexcept>

using std::sqrt;

class vec3{
    public:
        float x[3];
        vec3() : x{0,0,0} {}
        vec3(float x, float y, float z):x{x,y,z} {}
        float x1() const { return x[0]; }
        float x2() const { return x[1]; }
        float x3() const { return x[2]; }
        
        vec3 operator - () const{return vec3(-x[0], -x[1], -x[2]);}

        float operator [] (int a) const{return x[a];}
        float& operator [] (int a) {return x[a];}

        vec3 operator += (int a) const{return vec3(x[0]+a, x[1]+a, x[2]+a);}

        vec3& operator += (const vec3 &v) {
            x[0]+= v.x[0];
            x[1]+=v.x[1];
            x[2]+=v.x[2];
            return *this;
        }

        vec3& operator *= (const float m){
            x[0]*=m;
            x[1]*=m;
            x[2]*=m;
            return *this;
        }

        vec3& operator /= (const float m){
            if (m==0){throw std::invalid_argument("Cannot divide by '0'.");}
            return *this*=1/m;
        }

        double len() const{
            return sqrt(pow(x[0],2)+pow(x[1],2)+pow(x[2],2));
        }

        double square_of_len() const{
            return x[0]*x[0]+x[1]*x[1]+x[2]*x[2];
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

inline float dot (const vec3 &v, const vec3 &w){
    return v.x[0]*w.x[0]+v.x[1]*w.x[1]+v.x[2]*w.x[2];
}

inline vec3 cross(const vec3 &v, const vec3 &w){
    return vec3(
        v.x[1]*w.x[2]-v.x[2]*w.x[1],
        v.x[2]*w.x[0]-v.x[0]*w.x[2],
        v.x[0]*w.x[1]-v.x[1]*w.x[0]
    );
}

inline vec3 normalize(const vec3 &v){
    return v/v.len();
}