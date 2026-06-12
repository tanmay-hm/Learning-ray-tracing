#pragma once

#include "util.h"
#include "Vector3.h"
#include "interval.h"

using color = vec3;

double linear_to_gamma(double c){
    if(c>0){
        return std::sqrt(c);
    }
    return 0;
}

void color_out(std::ostream& out,const color& pix_color){
    double r = pix_color.x;
    double g = pix_color.y;
    double b = pix_color.z;

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    static const interval intensity(0.000,0.999);

    int r_out = int(256 * intensity.clamp(r));
    int g_out = int(256 * intensity.clamp(g));
    int b_out = int(256 * intensity.clamp(b));

    out << r_out << " " << g_out << " " << b_out << "\n";
}