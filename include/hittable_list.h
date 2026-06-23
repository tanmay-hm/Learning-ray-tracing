#pragma once

#include "hittable.h"
#include "util.h"
#include "aabb.h"

class hittable_list : public hittable {
    public:
        std::vector<shared_ptr<hittable>> objects;

        hittable_list() {};

        hittable_list(shared_ptr<hittable> obj) {
            add(obj);
        }

        void clear(){
            objects.clear();
            bbox = aabb();
        }

        void add(shared_ptr<hittable> obj){
            objects.push_back(obj);
            bbox = aabb(bbox,obj->bounding_box());
        }

        bool hit(const ray& r,interval t_range, hit_record& rec) const override {
            hit_record temp_rec;
            bool hit_anything = false;
            auto closest_so_far = t_range.max;

            for (const auto& object : objects) {
                if (object->hit(r,interval(t_range.min,closest_so_far), temp_rec)) {
                    hit_anything = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                }
            }

            return hit_anything;
        }

        aabb bounding_box() const override{
            return bbox;
        }
        
    private:
        aabb bbox;
};