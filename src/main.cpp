#include "vec3.hpp"
#include "color.hpp"
#include "ray.hpp"
#include <iostream>
#include<cstdlib>


//It compiles when I remove const before ray& in ray_color args,
//but originally it a book ith has const.
color ray_color(ray& r){
    vec3 unit_direction = normalize(r.direction());
    double t = 0.5*(unit_direction.x2()+1);
    return (1-t)*color(1,1,1) + t*color(0.5,0.7,1);
}

int main(){

    //Screen    
    const double aspect_ratio = 16/9;
    const int width = 600;
    const int height = static_cast<int>(400/aspect_ratio);

    //Camera
    double viewport_hegith = 2;
    auto viewport_width = aspect_ratio*viewport_hegith;
    double focal_length = 1;

    point origin = point(0,0,0);
    vec3 vertical = vec3(0,viewport_hegith,0);
    vec3 horizontal = vec3(viewport_width,0,0);
    vec3 lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

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