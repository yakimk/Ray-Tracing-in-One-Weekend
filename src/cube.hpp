#pragma once

#include "hittable.hpp"
#include "vec3.hpp"

// class cube(){
//     public:
//         const point center;
//         const double a,b,c; 
//         cube (){}
//         cube(point center, double a, double b, double c)
//         : center(center), a(a),b(b), c(c),{};

//         virtual bool hit(const ray& ray, double t_min, double t_max, hit_record& rec) const override;
// };

// double find_limit(int coordinate, const point dir, const point orig)const{
//     double limit;
//     switch (coordinate){
//         case 0:
//             //x
//             if 
//             break;
//         case 1:
//             //y
//             break;
//         case 2:
//             //z
//             break;
//     }

//     return q;
// }

// bool cube::hit(const ray& ray, double t_min, double t_max, hit_record& rec)const{
//     const double aproxim = 0.01;
//     const point dir = ray.dir();
//     const point orig = ray.orig();
//         const double x_limit =     
// }

class cube: public hittable{
    public:
        const point center;
        double x1,x2 ,x3;
        cube() {}
        cube(point center, double x1)
         : center(center), x1(x1), x2(x2), x3(x3), {};

        virtual bool hit(const ray& ray, double t_min, double t_max, hit_record& rec) const override; 
};

bool cube::check_ray(const ray& r)const{
    bool hit = false;
    const double tanx = (r.dir().x1()-r.orig().x1())/(r.dir().x3()-r.orig().x3());
    const double tany = (r.dir().x2()-r.orig().x2())/(r.dir().x3()-r.orig().x3());

    const double z_coordinate = center.x3()-r.orig().x3();
    const double tan_down_y = (center.x2()-r.orig().x2()+x1/2)/z_coordinate;
    const double tan_up_y = (center.x2()-r.orig().x2()-x1/2)/z_coordinate;
    const double tan_down_x = (center.x1()-r.orig().x1()+x1/2)/z_coordinate;
    const double tan_up_x = (center.x1()-r.orig().x1()-x1/2)/z_coordinate;

    if (tanx<tan_up_x && tan_down_x < tanx){
        if (tany< tan_up_y && tany < tan_down_y){hit = true;}
    }

    return hit;
}

bool cube::hit(const ray& r, double t_min, double t_max, hit_record& rec)const{
    vec3 oc = r.origin() - center;
    if (check_ray(r)){
        rec.t = root;
        rec.p = r.lin(rec.t);
        vec3 outward_normal = (rec.p - center) / x1;
        rec.set_face_normal(r, outward_normal);

        return true;
    }

}
