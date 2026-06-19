#include "util.h"
#include "hittable.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"
#include "material.h"
#include <fstream>

using namespace std;

int main(){
    // Camera

    camera cam;
    cam.aspect_ratio = 16.0/9.0;
    cam.width = 800;
    cam.samples_per_pixel = 10;
    cam.max_bounces = 50;
    cam.vfov = 60.0;
    cam.lookfrom = point3(0,0,-1);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);
    cam.defocus_angle = 0;
    cam.focus_dist    = 3.4;
    cam.sky_color = color(1.0,0.5,0.2);
    cam.runtime = 3;
    
    // Objects in scene

    hittable_list world;

    auto material_sphere = make_shared<metal>(color(0,1.0,1.0),0.0);

    world.add(make_shared<sphere>(point3(-1,0,1),point3(1,0,1),0.5,material_sphere));

    // Render image

    cam.render(world);
    
}