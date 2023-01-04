#pragma once

#include "hittable.hpp"
#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable{
    public:
        using hittable::hit;
        std::vector<shared_ptr<hittable>> objects;
        hittable_list(){}
        hittable_list(shared_ptr<hittable> object){add(object);}

        void clear(){objects.clear();}
        void add(shared_ptr<hittable> object){objects.push_back(object);}

        virtual bool hit(const ray& ray, double t_min, double t_max, hit_record& rec)const override;

};

bool hittable_list::hit(const ray& ray, double t_min, double t_max, hit_record& rec)const{
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;

    for(const auto& object : objects){
        if(object->hit(ray, t_min, t_max, temp_rec)){
            if (temp_rec.t< closest_so_far){
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }
    }

    return hit_anything;
}