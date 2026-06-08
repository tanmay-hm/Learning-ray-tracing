#pragma once

#include "hittable.h"
#include <fstream>

class camera{
    public:
        double aspect_ratio = 1.0;
        int width = 100;

        void render(const hittable& world){
            init();
            std::ofstream fp("image.ppm");
            fp << "P3\n" << width << " " << height << "\n255\n";
            for(int i=0;i<height;i++){
                for(int j=0;j<width;j++){
                    auto pix = pixel00loc + i*pixel_delta_v + j*pixel_delta_u;
                    ray r = ray(centre,pix-centre);
                    color_out(fp,ray_color(r,world));
                }
            }
        }
    
    private:
        int height;
        point3 centre;
        point3 pixel00loc;
        vec3 pixel_delta_u;
        vec3 pixel_delta_v;
        
        void init(){

            height = std::max(1,int(width/aspect_ratio));
    
            double focal_length = 1.0;
            centre = point3(0,0,0);
            double viewport_height = 2.0;
            double viewport_width = viewport_height*((double)width/height);
    
            // left-right and top-bottom vectors
    
            vec3 viewport_u = vec3(viewport_width,0,0);
            vec3 viewport_v = vec3(0,-viewport_height,0);
    
            // pixel deltas
    
            pixel_delta_u = viewport_u/width;
            pixel_delta_v = viewport_v/height;
    
            // top-left pixel location
    
            point3 viewport_top_left = centre - vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2;
            pixel00loc = viewport_top_left + pixel_delta_u/2 + pixel_delta_v/2;
        }

        color ray_color(const ray& r,const hittable& world) const{
            hit_record rec;
            if(world.hit(r,interval(0,infinity),rec)){
                return 0.5*(rec.normal+color(1,1,1));
            }
            // sky gradient (blue to white)
            color white = color(1,1,1);
            color blue = color(0.5,0.5,1);
            auto blue_intensity = normalise(r.direction()).y;
            blue_intensity = 0.5 * (blue_intensity+1);
            return white*(1-blue_intensity) + blue*blue_intensity;
        }
};