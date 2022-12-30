#include "vec3.hpp"
#include "color.hpp"
#include "ray.hpp"
#include <iostream>
#include<cstdlib>

//t^2 b^2 + 2Atb + A^2-r^2 = 0
bool hit_sphere(const point& center, const double r, ray& ray){
    const double a = dot(ray.direction(), ray.direction());
    const double b = 2*dot(ray.origin()-center, ray.direction());
    const double c = dot(ray.origin()-center, ray.origin()-center) - r*r;
    const double discriminant = b*b -4*a*c;
    return discriminant>0;
}

//It compiles when I remove const before ray& in ray_color args,
//but originally it a book ith has const.
color ray_color(ray& r){
    if (hit_sphere(point(0,0,-1), 0.5, r)){return color(0,1,0);}
    vec3 unit_direction = normalize(r.direction());
    double t = 0.5*(unit_direction.x2()+1);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);

}

int main(){

    //Screen    
    const auto aspect_ratio = 16.0 / 9.0;
    const int width = 400;
    const int height = static_cast<int>(width / aspect_ratio);

    //Camera
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    std::cout << "P3\n" << width << ' ' << height << "\n255\n";
    for (int j=height-1; j>=0;j--){
        std::cerr<<"\rLines remaining: "<<j<<" "<<std::flush;
        for (int i=0;i<width; i++){
            auto u = double(i) / (width-1);
            auto v = double(j) / (height-1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color(r);
            flush_color(std::cout, pixel_color);
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