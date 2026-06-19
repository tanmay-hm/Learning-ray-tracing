#pragma once

#include "Vector3.h"

class ray{
    private:
        point3 orig{point3()};
        vec3 dir{vec3()};
        double tm;
    public:
        ray() = default;
        ray(const point3& origin,const vec3& direction,double time) : orig(origin),dir(direction),tm(time) {}

        ray(const point3& origin,const vec3& direction) : ray(origin,direction,0) {}

        const point3& origin() const{
            return orig;
        }
        const vec3& direction() const{
            return dir;
        }
        const double& time() const{
            return tm;
        }
        point3 at(double t) const{
            return orig + (t*dir);
        }
};