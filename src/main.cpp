#include <iostream>
#include<cstdlib>

int main(){
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
}