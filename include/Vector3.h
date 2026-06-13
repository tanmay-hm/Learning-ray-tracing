#pragma once

#include <cmath>
#include <ostream>
#include "util.h"

class vec3{
    public:
        double x,y,z;

        vec3() : x{0},y{0},z{0} {}
        vec3(double a,double b,double c) : x{a},y{b},z{c} {}

        static vec3 random(){
            return vec3(random_double(),random_double(),random_double());
        }

        static vec3 random(double min,double max){
            return vec3(random_double(min,max),random_double(min,max),random_double(min,max));
        }

        bool near_zero() const{
            double limit = 1e-8;
            return (std::fabs(x) < limit) && (std::fabs(y) < limit) && (std::fabs(z) < limit);
        }
        
        double length() const{
            return std::sqrt(squared_length());
        }
        double squared_length() const{
            return x*x + y*y + z*z;
        }
        vec3 operator-() const{
            return vec3(-x,-y,-z);
        }
        vec3& operator+=(const vec3& other){
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }
        vec3& operator-=(const vec3& other){
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }
        vec3& operator*=(double f){
            x *=f;
            y *=f;
            z *=f;
            return *this;
        }
        vec3& operator/=(double f){
            return *this*=(1/f);
        }
};

using point3 = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.x << ' ' << v.y << ' ' << v.z;
}
inline vec3 operator+(vec3 left, const vec3& right){
    left+=right;
    return left;
}
inline vec3 operator-(vec3 left,const vec3& right){
    left-=right;
    return left;
}
inline vec3 operator*(vec3 left,double f){
    return left*=f;
}
inline vec3 operator*(double f,vec3 right){
    return right*=f;
}
inline vec3 operator/(vec3 left,double f){
    return left/=f;
}
inline vec3 operator*(vec3 left,vec3 right){
    return vec3(left.x*right.x,left.y*right.y,left.z*right.z);
}
inline double dot(const vec3& left,const vec3& right){
    return left.x * right.x + left.y * right.y + left.z * right.z;
}
inline vec3 cross(const vec3& left,const vec3& right){
    double nx = left.y*right.z - left.z * right.y;
    double ny = left.z*right.x - left.x*right.z;
    double nz = left.x*right.y - left.y*right.x;
    return vec3(nx,ny,nz);
}
inline vec3 normalise(const vec3& v){
    return v/v.length();
}
inline vec3 random_unit_vector(){
    while(true){
        vec3 v = vec3::random(-1,1);
        auto lensq = v.squared_length();
        if(1e-160<lensq && lensq<=1){
            return v/std::sqrt(lensq);
        }
    }
}
inline vec3 random_on_hemisphere(const vec3& normal){
    vec3 output = random_unit_vector();
    if(dot(output,normal)>0.0){
        return output;
    }
    else{
        return -output;
    }
}

inline vec3 reflect(const vec3& incident, const vec3& normal){
    vec3 reflected = incident - 2*dot(incident,normal)*normal;
    return reflected;
}