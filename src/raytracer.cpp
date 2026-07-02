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

void perlin_spheres() {
    hittable_list world;

    auto pertext = make_shared<noise_texture>(4);
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(pertext)));
    world.add(make_shared<sphere>(point3(0,2,0), 2, make_shared<lambertian>(pertext)));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.width = 800;
    cam.samples_per_pixel = 10;
    cam.max_bounces = 50;

    cam.vfov = 30;
    cam.lookfrom = point3(13,2,3);
    cam.lookat = point3(0,0,0);
    cam.vup = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);
}

void render_earth(){
    auto earth_img = make_shared<image_texture>("earthmap.jpg");
    auto mat = make_shared<lambertian>(earth_img);
    auto globe = make_shared<sphere>(point3(0,0.5,2),3,mat);

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.width = 800;
    cam.samples_per_pixel = 10;
    cam.max_bounces = 50;

    cam.vfov = 60;
    cam.lookfrom = point3(0,0,-5);
    cam.lookat = point3(0,0,2);
    cam.vup = vec3(0,1,0);

    cam.defocus_angle = 0;

    cam.render(hittable_list(globe));
}

void bouncing_spheres(){
    hittable_list world;

    auto checker = make_shared<checkered_texture>(0.32, color(.2, .3, .1), color(.9, .9, .9));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(checker)));

    for (int a = -2; a < 2; a++) {
        for (int b = -2; b < 2; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

    camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.width       = 800;
    cam.samples_per_pixel = 10;
    cam.max_bounces         = 50;

    cam.vfov     = 20;
    cam.lookfrom = point3(13,2,3);
    cam.lookat   = point3(0,0,0);
    cam.vup      = vec3(0,1,0);

    cam.defocus_angle = 0.0;
    cam.focus_dist    = 10.0;

    cam.render(world);
}

int main(){
    switch(1){
        case 1: perlin_spheres(); break;
        case 2: render_earth(); break;
        case 3: bouncing_spheres(); break;
        default: break;
    }
}