#pragma once

#include "hittable.h"
#include "util.h"

class material{
    public:
        virtual ~material() = default;

        virtual bool scatter(const ray& ray_in,const hit_record& rec,color& attenuation,ray& ray_out) const{
            return false;
        }
};

class lambertian : public material{
    public:
        lambertian(const color& albedo) : albedo(albedo) {}

        bool scatter(const ray& ray_in,const hit_record& rec,color& attenuation,ray& ray_out) const override{
            auto out_direction = rec.normal + random_unit_vector();
            if(out_direction.near_zero()){
                out_direction = rec.normal;
            }
            ray_out = ray(rec.hit_location,out_direction);
            attenuation = albedo;
            return true;
        }
    private:
    color albedo;
};

class metal : public material{
    public:
        metal(const color& albedo,double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

        bool scatter(const ray& ray_in,const hit_record& rec,color& attenuation,ray& ray_out) const override{
            vec3 reflected = reflect(ray_in.direction(),rec.normal);
            reflected = normalise(reflected) + (fuzz * random_unit_vector());
            ray_out = ray(rec.hit_location,reflected);
            attenuation = albedo;
            return true;
        }
    private:
        color albedo;
        double fuzz;
};