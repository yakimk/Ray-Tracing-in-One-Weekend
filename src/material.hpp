#pragma once

#include "rtweekend.hpp"
#include "hittable.hpp"

class material{
    public:
        virtual bool scatter(const ray& r_in, const hit_record& rec,
        color& attenuation, ray& scattered)const = 0 ;
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
    double fuzz;
    metal(){}
    metal(const color& c, double f):albedo(c), fuzz(f<1 ? f:1){}

        virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const override {
            vec3 reflected = reflect(normalize(r_in.direction()), rec.normal);
            scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }
};

class dielectric: public material{
    public:
        double ir;

        dielectric(double index_of_refraction)
            :ir(index_of_refraction){}
        
        virtual bool scatter(
                    const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const override {
            attenuation = color(1.0,1.0,1.0);
            double refraction_ratio = rec.front_face ? (1.0/ir) : ir;

            vec3 unit_direction = normalize(r_in.direction());
            vec3 refracted = refract(unit_direction, rec.normal, refraction_ratio);

            double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

            bool cannot_refract = refraction_ratio * sin_theta > 1.0;
            vec3 direction;

            if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
                direction = reflect(unit_direction, rec.normal);
            else
                direction = refract(unit_direction, rec.normal, refraction_ratio);

            scattered = ray(rec.p, refracted);
            return true;
        }

    private:
        static double reflectance(double cosine, double ref_idx) {
            // Use Schlick's approximation for reflectance.
            auto r0 = (1-ref_idx) / (1+ref_idx);
            r0 = r0*r0;
            return r0 + (1-r0)*pow((1 - cosine),5);
        }

};