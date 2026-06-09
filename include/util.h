#pragma once

#include <vector>
#include <random>
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>


// C++ Std Usings

using std::make_shared;
using std::shared_ptr;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Random numbers

inline double random_double(){
    static std::uniform_real_distribution<double> dist(0.0, 1.0);
    static std::mt19937 gen(std::random_device{}());
    return dist(gen);
}

inline double random_double(double min, double max){
    return min + (max-min)*random_double();
}

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

// Common Headers

#include "color.h"
#include "ray.h"
#include "Vector3.h"
#include "interval.h"