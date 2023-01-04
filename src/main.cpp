#include "rtweekend.hpp"
#include "color.hpp"
#include "sphere.hpp"
#include "hittable_list.hpp"
#include "hittable.hpp"
#include <iostream>
#include "camera.hpp"

//It compiles when I remove const before ray& in ray_color args,
//but originally it a book ith has const.
color ray_color(const ray& r, const hittable& world, int depth){
    if (depth<=0){return color (0,0,0);}
    hit_record rec;

    if (world.hit(r,0.001,infinity, rec)){
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)){
            return attenuation*ray_color(scattered, world, depth-1);
        }
        return color(0,0,0);
    }

    vec3 unit_direction = normalize(r.direction());
    double t = 0.5*(unit_direction.x2()+1);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main(){

    const auto aspect_ratio = 16.0 / 9.0;
    const int width = 600;
    const int height = static_cast<int>(width / aspect_ratio);
    int samples_per_pixel = 10;
    const int max_depth = 50;

    //Camera
    camera cam;

    hittable_list world;
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
auto material_center = make_shared<dielectric>(1.5);
auto material_left   = make_shared<dielectric>(1.5);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 1 );

    world.add(make_shared<sphere>(point( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(make_shared<sphere>(point(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point( 1.0,    0.0, -1.0),   0.5, material_right));

    std::cout << "P3\n" << width << ' ' << height << "\n255\n";
    for (int j=height-1; j>=0;j--){
        std::cerr<<"\rLines remaining: "<<j<<" "<<std::flush;
        for (int i=0;i<width;i++){
            color pixel_color(0,0,0);
            for (int q=0; q<samples_per_pixel;q++){
                auto u = (i + random_double()) / (width-1);
                auto v = (j + random_double()) / (height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            flush_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
    std::cerr<<"\nSuccess. \n"<<std::flush;
    return 0;
}
int random_image(){
    int r,g,b;
    const int height = 256;
    const int width = 256;
    std::cout << "P3\n" << width << ' ' << height << "\n255\n";
    for (int j=height-1; j>=0;j--){
        std::cerr<<"\rLines remaining: "<<j<<" "<<std::flush;
        for (int i=0;i<width; i++){
            r= rand()%255;
            g= rand()%255;
            b= rand()%255;
            int ir = static_cast<int>(r);
            int ig = static_cast<int>(g);
            int ib = static_cast<int>(b);
            std::cout<<ir<<' '<<ig<<' '<<ib<<'\n';
        }
    }
    std::cerr<<"\nSuccess. \n"<<std::flush;
    return 0;
}