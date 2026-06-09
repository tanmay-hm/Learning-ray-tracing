#include "util.h"
#include "hittable.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"
#include <fstream>

using namespace std;

int main(){
    // Camera

    camera cam;
    cam.aspect_ratio = 16.0/9.0;
    cam.width = 800;
    cam.samples_per_pixel = 100;

    // Objects in scene

    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1),0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    // Render image

    cam.render(world);
    
}