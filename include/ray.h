#pragma once

#include "Vector3.h"

class ray{
    private:
        point3 orig{point3()};
        vec3 dir{vec3()};
    public:
        ray() = default;
        ray(const point3& origin,const vec3& direction) : orig(origin),dir(direction) {}

        const point3& origin() const{
            return orig;
        }
        const vec3& direction() const{
            return dir;
        }
        point3 at(double t) const{
            return orig + (t*dir);
        }
};