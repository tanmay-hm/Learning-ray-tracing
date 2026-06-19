#pragma once

#include "hittable.h"
#include "util.h"
#include "material.h"
#include <fstream>

class camera{
    public:
        double aspect_ratio = 1.0;
        int width = 100;
        int samples_per_pixel = 10;
        int max_bounces = 10;
        double vfov = 90.0;
        point3 lookfrom = point3(0,0,0);
        point3 lookat = point3(0,0,-1);
        vec3 vup = vec3(0,1,0);
        double defocus_angle = 0;
        double focus_dist = 10;
        color sky_color = color(0.0,0.25,1);
        int fps = 24;
        int runtime = 1;
        int total_frames = 24;

        void render(const hittable& world){
            init();
            for(int frame = 1;frame<=total_frames;frame++){
                std::string file_name = "Output\\image" + std::to_string(frame) + ".ppm";
                std::ofstream fp(file_name);
                fp << "P3\n" << width << " " << height << "\n255\n";
                for(int j=0;j<height;j++){
                    for(int i=0;i<width;i++){
                        color pixel_color(0,0,0);
                        for(int sample = 0;sample<samples_per_pixel;sample++){
                            ray r = get_ray(i,j,frame);
                            pixel_color += ray_color(r,world,max_bounces);
                        }
                        color_out(fp,pixel_color * pixel_color_scale);
                    }
                }
            }
        }
    
    private:
        int height;
        point3 centre;
        point3 pixel00loc;
        double pixel_color_scale;
        vec3 pixel_delta_u;
        vec3 pixel_delta_v;
        vec3 u,v,w;
        vec3 defocus_disk_u;
        vec3 defocus_disk_v;
        
        void init(){
            
            height = std::max(1,int(width/aspect_ratio));
            pixel_color_scale = 1.0/samples_per_pixel;
            total_frames = runtime*fps;
            
            double h = std::tan(degrees_to_radians(vfov/2));
            double viewport_height = 2.0 * h * focus_dist;
            double viewport_width = viewport_height*((double)width/height);
            w = normalise(lookfrom - lookat);
            u = normalise(cross(vup,w));
            v = cross(w,u);
            centre = lookfrom;
            auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
            defocus_disk_u = u * defocus_radius;
            defocus_disk_v = v * defocus_radius;
    
            // left-right and top-bottom vectors
    
            vec3 viewport_u = u * viewport_width;
            vec3 viewport_v = -v * viewport_height;
    
            // pixel deltas
    
            pixel_delta_u = viewport_u/width;
            pixel_delta_v = viewport_v/height;
    
            // top-left pixel location
    
            point3 viewport_top_left = centre - (focus_dist*w) - viewport_u/2 - viewport_v/2;
            pixel00loc = viewport_top_left + pixel_delta_u/2 + pixel_delta_v/2;
        }

        ray get_ray(int i,int j,int frame_no) const{
            auto offset = sample_square();
            auto pixel_sample = pixel00loc + (i+offset.x)*pixel_delta_u + (j+offset.y)*pixel_delta_v;
            auto ray_origin = (defocus_angle <= 0) ? centre : defocus_disk_sample();
            auto direction = pixel_sample - ray_origin;
            double time = (double)frame_no/fps;
            return ray(ray_origin,direction,time);
        }

        vec3 sample_square() const{
            return vec3(random_double()-0.5,random_double()-0.5,0);
        }

        point3 defocus_disk_sample() const{
            auto p = random_on_disk();
            return centre + (p.x * defocus_disk_u) + (p.y * defocus_disk_v);
        }

        color ray_color(const ray& r,const hittable& world,int depth) const{
            if(depth<0){
                return color(0,0,0);
            }
            hit_record rec;
            if(world.hit(r,interval(0.001,infinity),rec)){
                color attenuation;
                ray scattered;
                if(rec.mat->scatter(r,rec,attenuation,scattered)){
                    return attenuation * ray_color(scattered,world,depth-1);
                }
                return color(0,0,0);
            }
            color white = color(1,1,1);
            auto color_intensity = normalise(r.direction()).y;
            color_intensity = 0.5 * (color_intensity+1);
            return white*(1-color_intensity) + sky_color*color_intensity;
        }
};