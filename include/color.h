#pragma once

#include <iostream>
#include "Vector3.h"

using color = vec3;

void color_out(std::ostream& out,const color& pix_color){
    double r = pix_color.x;
    double g = pix_color.y;
    double b = pix_color.z;
    int r_out = int(255.99999 * r);
    int g_out = int(255.99999 * g);
    int b_out = int(255.99999 * b);

    out << r_out << " " << g_out << " " << b_out << "\n";
}