#pragma once

#include "hittable.h"
#include "util.h"
#include "texture.h"

class material{
    public:
        virtual ~material() = default;

        virtual bool scatter(const ray& ray_in,const hit_record& rec,color& attenuation,ray& ray_out) const{
            return false;
        }
};

class lambertian : public material{
    public:
        lambertian(const color& albedo) : tex(make_shared<solid_color>(albedo)) {}

        lambertian(shared_ptr<texture> tex) : tex(tex) {}

        bool scatter(const ray& ray_in,const hit_record& rec,color& attenuation,ray& ray_out) const override{
            auto out_direction = rec.normal + random_unit_vector();
            if(out_direction.near_zero()){
                out_direction = rec.normal;
            }
            ray_out = ray(rec.hit_location,out_direction,ray_in.time());
            attenuation = tex->value(rec.u,rec.v,rec.hit_location);
            return true;
        }
    private:
        shared_ptr<texture> tex;
};

class metal : public material{
    public:
        metal(const color& albedo,double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

        bool scatter(const ray& ray_in,const hit_record& rec,color& attenuation,ray& ray_out) const override{
            vec3 reflected = reflect(ray_in.direction(),rec.normal);
            reflected = normalise(reflected) + (fuzz * random_unit_vector());
            ray_out = ray(rec.hit_location,reflected,ray_in.time());
            attenuation = albedo;
            return true;
        }
    private:
        color albedo;
        double fuzz;
};

class dielectric : public material {
  public:
    dielectric(double refraction_index) : refraction_index(refraction_index) {}

    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& ray_out) const override {
        attenuation = color(1.0, 1.0, 1.0);
        double ri = rec.front_face ? (1.0/refraction_index) : refraction_index;

        vec3 unit_direction = normalise(r_in.direction());
        double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

        bool cannot_refract = ri * sin_theta > 1.0;
        vec3 direction;

        if (cannot_refract || reflectance(cos_theta,ri) > random_double())
            direction = reflect(unit_direction, rec.normal);
        else
            direction = refract(unit_direction, rec.normal, ri);

        ray_out = ray(rec.hit_location, direction,r_in.time());
        return true;
    }

  private:
    double refraction_index;

    static double reflectance(double cosine, double refraction_index){
        auto r0 = (1 - refraction_index) / (1 + refraction_index);
        r0 = r0*r0;
        return r0 + (1-r0)*std::pow((1 - cosine),5);
    }
};