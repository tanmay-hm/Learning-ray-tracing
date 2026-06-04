#pragma once

#include <cmath>
#include <ostream>

class vec3{
    public:
        double x,y,z;

        vec3() : x{0},y{0},z{0} {}
        vec3(double a,double b,double c) : x{a},y{b},z{c} {}
        
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