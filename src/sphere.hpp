#pragma once

#include"hittable.hpp"
#include"vec3.hpp"

class sphere:public hitable{
    public:
        point center;
        double r;
        sphere() {}
        sphere(point center, double r) : center(center), r(r) {};

        virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override; 
}

bool sphere::hit(ray& ray, double t_min, double t_max, hit_record& rec){
    vec3 oc = ray.origin() - center;
    const double a = dot(ray.direction(), ray.direction());
    const double half_b = dot(oc, ray.direction());
    const double c = dot(oc,oc) - r*r;


    const double discriminant = (half_b*half_b -a*c);
    if (discriminant<0){return false;}
    auto sqrtd = sqrt(discriminant);
    auto root = (-half_b - sqrtd) / a;

    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = ray.lin(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(ray, outward_normal);
    rec.normal = (rec.p - center )/radius;

    return true;
}
