#pragma once

#include "hittable.h"
#include "util.h"
#include "material.h"

class sphere : public hittable{
    private:
        ray centre;
        double radius;
        shared_ptr<material> mat;
        aabb b_box;
    public: 
        sphere(const point3& static_c,double rad,shared_ptr<material> mat) : 
        centre(static_c,vec3(0,0,0)),radius(std::fmax(0,rad)), mat(mat) {
            vec3 rad_vec = vec3(radius,radius,radius);
            b_box = aabb(static_c - rad_vec,static_c + rad_vec);
        }

        sphere(const point3& c1,const point3& c2,double rad,shared_ptr<material> mat) : 
        centre(c1,c2-c1),radius(std::fmax(0,rad)), mat(mat) {
            vec3 rad_vec = vec3(radius,radius,radius);
            auto bbox1 = aabb(centre.at(0) - rad_vec,centre.at(0) + rad_vec);
            auto bbox2 = aabb(centre.at(1) - rad_vec,centre.at(1) + rad_vec);
            b_box = aabb(bbox1,bbox2);
        }

        aabb bounding_box() const override{
            return b_box;
        }

        bool hit(const ray&r,interval t_range,hit_record& rec) const override{
            auto current_centre = centre.at(r.time());
            auto orig_centre = current_centre - r.origin();
            auto a = dot(r.direction(),r.direction());
            auto h = dot(r.direction(),orig_centre);
            auto c = dot(orig_centre,orig_centre) - radius*radius;
            auto discriminant = h*h - a*c;

            if(discriminant<0) return false;

            auto root = (h - std::sqrt(discriminant))/a;

            if(!t_range.surrounds(root)){
                root = (h + std::sqrt(discriminant))/a;
                if(!t_range.surrounds(root)){
                    return false;
                }
            }

            rec.t = root;
            rec.hit_location = r.at(rec.t);
            auto out_normal = (rec.hit_location - current_centre)/radius;
            rec.set_face_normal(r,out_normal);
            rec.mat = mat;

            return true;
        }
};