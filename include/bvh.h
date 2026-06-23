#pragma once 

#include "util.h"
#include "aabb.h"
#include "hittable_list.h"

#include <algorithm>

class bvh_node : public hittable{
    public:
        shared_ptr<hittable> left,right;
        aabb bbox;

        bvh_node(hittable_list list) : bvh_node(list.objects,0,list.objects.size()) {}

        bvh_node(std::vector<shared_ptr<hittable>> objects,int start,int end){
            int size = end-start;
            if(size==1){
                left = right = objects[start];
            }
            else if(size==2){
                left = objects[start];
                right = objects[start+1];
            }
            else{
                auto axis = random_int(0,2);
                auto compare = axis==0 ? box_x_compare : axis==1 ? box_y_compare : box_z_compare;
                std::sort(objects.begin()+start,objects.end()+end,compare);
                int mid = (start+end)/2;
                left = make_shared<bvh_node>(objects,start,mid);
                right = make_shared<bvh_node>(objects,mid,end);
            }

            bbox = aabb(left->bounding_box(), right->bounding_box());
        }

        bool hit(const ray& r,interval trange,hit_record& rec) const override{
            if(!bbox.hit(r,trange)){
                return false;
            }

            bool leftHit = left->hit(r,trange,rec);
            bool rightHit = right->hit(r,interval(trange.min, leftHit ? rec.t : trange.max),rec);

            return leftHit || rightHit;
        }

        aabb bounding_box() const override{
            return bbox;
        }

    private:
        static bool box_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b, int axis_index){
            auto a_axis_interval = a->bounding_box().axis_interval(axis_index);
            auto b_axis_interval = b->bounding_box().axis_interval(axis_index);
            return a_axis_interval.min < b_axis_interval.min;
        }

        static bool box_x_compare (const shared_ptr<hittable> a, const shared_ptr<hittable> b){
            return box_compare(a, b, 0);
        }

        static bool box_y_compare (const shared_ptr<hittable> a, const shared_ptr<hittable> b){
            return box_compare(a, b, 1);
        }

        static bool box_z_compare (const shared_ptr<hittable> a, const shared_ptr<hittable> b){
            return box_compare(a, b, 2);
        }
};