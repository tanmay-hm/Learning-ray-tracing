#pragma once 

#include "util.h"

struct hit_record{
    point3 hit_location;
    vec3 normal;
    bool front_face;
    double t;

    void set_face_normal(const ray& r,const vec3& out_normal){
        if(dot(r.direction(),out_normal)>0.0){
            front_face = false;
        }
        else{
            front_face = true;
        }
        normal = front_face ? out_normal : -out_normal;
    }
};

class hittable{
    public:
        virtual ~hittable() = default;

        virtual bool hit(const ray& r,double t_min,double t_max,hit_record& rec) const = 0;
};