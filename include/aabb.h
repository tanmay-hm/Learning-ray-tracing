#pragma once

#include "util.h"

class aabb{
    public:
        interval x,y,z;
    
        aabb() = default;

        aabb(const interval& x,const interval& y,const interval& z) :
        x(x),y(y),z(z) {}

        aabb(const point3& p1,const point3& p2){
            x = interval(std::min(p1.x,p2.x),std::max(p1.x,p2.x));
            y = interval(std::min(p1.y,p2.y),std::max(p1.y,p2.y));
            z = interval(std::min(p1.z,p2.z),std::max(p1.z,p2.z));
        }

        aabb(const aabb& a,const aabb& b){
            x = interval(a.x,b.x);
            y = interval(a.y,b.y);
            z = interval(a.z,b.z);
        }

        const interval& axis_interval(int axis) const{
            if(axis==1) return y;
            else if(axis==2) return z;
            return x;
        }

        bool hit(const ray& r,interval ray_t) const{
            for(int axis=0;axis<3;axis++){
                auto& intrvl = axis_interval(axis);
                auto coord = r.origin()[axis];
                auto dir = r.direction()[axis];
                auto inv_dir = 1.0/dir;
                auto t1 = (intrvl.min - coord) * inv_dir;
                auto t2 = (intrvl.max - coord) * inv_dir;
                
                if(t1<t2){
                    ray_t.min = std::fmin(t1,ray_t.min);
                    ray_t.max = std::fmax(t2,ray_t.max);
                }
                else{
                    ray_t.min = std::fmin(t2,ray_t.min);
                    ray_t.max = std::fmax(t1,ray_t.max);
                }

                if(ray_t.min>=ray_t.max){
                    return false;
                }
            }
            return true;
        }
        int longest_axis() const{
            if(x.size() > y.size()){
                if(x.size()>z.size()) return 0;
                else return 2;
            }
            else{
                if(z.size() > y.size()) return 2;
                else return 1;
            }
        }
        static const aabb empty,universe;
};

const aabb aabb::empty = aabb(interval::empty,interval::empty,interval::empty);
const aabb aabb::universe = aabb(interval::universe,interval::universe,interval::universe);