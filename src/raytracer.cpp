#include "util.h"
#include "hittable.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"
#include "material.h"
#include "texture.h"
#include "bvh.h"
#include <fstream>

using namespace std;

int main(){
    auto earth_texture = make_shared<image_texture>("earthmap.jpg");
    auto earth_surface = make_shared<lambertian>(earth_texture);
    auto globe = make_shared<sphere>(point3(0,0,0), 2, earth_surface);

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.width = 800;
    cam.samples_per_pixel = 100;
    cam.max_bounces = 50;

    cam.vfov = 20;
    cam.lookfrom = point3(0,0,12);
    cam.lookat = point3(0,0,0);
    cam.vup = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(hittable_list(globe));
}