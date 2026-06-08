#pragma once

class interval{
    public:
        double min,max;

        interval() : min(infinity),max(-infinity) {}
        interval(double mini,double maxi) : min(mini), max(maxi) {}

        double size(){
            return max-min;
        }

        bool includes(double x) const{
            return min<=x && x<=max;
        }

        bool surrounds(double x) const{
            return min<x && x<max;
        }

        static const interval empty, universe;
};

const interval interval::empty    = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);