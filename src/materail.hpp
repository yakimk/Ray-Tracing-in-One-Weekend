#pragma once

#include "rtweekend.hpp"
#include "hittable.hpp"

class material{
    public:
        virtual bool scatter(const ray& r_in, const hit_record& rec,
        color& attenuation, ray& scattered)const =0 ;
};

class lambertian: public material{
    public:
    color albedo;
    lambertian(){}
    lambertian(const color& c)
        :albedo(c){}
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation,ray& scattered)
    const override{

        vec3 scatter_direction = rec.normal + random_unit_vector();

        if (scatter_direction.near_zero()){scatter_direction = rec.normal;}

        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        
        return true;
    }
};

class metal: public material{
    public:
    color albedo;
    metal(){}
    metal(const color& c):albedo(c){}

        virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const override {
            vec3 reflected = reflect(normalize(r_in.direction()), rec.normal);
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }
};