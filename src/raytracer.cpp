#include "Vector3.h"
#include "color.h"
#include "ray.h"
#include <iostream>
#include <fstream>
using namespace std;

bool hit_sphere(const point3& centre,double radius,const ray& r){
    auto orig_centre = centre - r.origin();
    auto a = dot(r.direction(),r.direction());
    auto b = -2 * dot(r.direction(),orig_centre);
    auto c = dot(orig_centre,orig_centre) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    if(discriminant<0) return false;
    return true;
}

color ray_color(const ray& r){
    if(hit_sphere(point3(0,0,-1),0.5,r)){
        return color(1,0,0);
    }
    color white = color(1,1,1);
    color blue = color(0.5,0.5,1);
    auto blue_intensity = normalise(r.direction()).y;
    blue_intensity = 0.5 * (blue_intensity+1);
    return white*(1-blue_intensity) + blue*blue_intensity;
    // sky gradient (blue to white)
}

int main(){
    // image properties
    double aspect_ratio = 16.0/9.0;
    int image_width = 800;
    int image_height = max(1,int(image_width/aspect_ratio));
    // camera properties (viewport included)
    double focal_length = 1.0;
    point3 camera_centre = point3(0,0,0);
    double viewport_height = 4.0;
    double viewport_width = viewport_height*((double)image_width/image_height);
    // left-right and top-bottom vectors
    vec3 viewport_u = vec3(viewport_width,0,0);
    vec3 viewport_v = vec3(0,-viewport_height,0);
    // pixel deltas
    vec3 pixel_delta_u = viewport_u/image_width;
    vec3 pixel_delta_v = viewport_v/image_height;
    // top-left pixel location
    point3 viewport_top_left = camera_centre - vec3(0,0,focal_length) - viewport_u/2 - viewport_v/2;
    point3 pixel00loc = viewport_top_left + pixel_delta_u/2 + pixel_delta_v;
            // To be modified

    ofstream fp("image.ppm");
    fp << "P3" << endl << image_width << " " << image_height << endl << "255" << endl;
    for(int i=0;i<image_height;i++){
        for(int j=0;j<image_width;j++){
            auto pix = pixel00loc + i*pixel_delta_v + j*pixel_delta_u;
            ray r = ray(camera_centre,pix-camera_centre);
            color_out(fp,ray_color(r));
        }
    }
}