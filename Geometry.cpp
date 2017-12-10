#include "Geometry.h"
#include <algorithm>

using namespace std;
// Implementation of Point and Ray classes.

Point Point::Infinite(){
    return Point(1E20,1E20,1E20);
}
Point Point::cross(Point p){
    return Point(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);   
}

void Point::normalize(){
    double l = this->length();
    x /= l;
    y /= l;
    z /= l;
}

Point::Point(double xo, double yo, double zo){
    x = xo;
    y = yo;
    z = zo;
}

Point Point::operator- (Point p){
    return Point(x-p.x,y-p.y,z-p.z);   
}

Point Point::operator*(double s){
    return Point(x*s,y*s,z*s);   
}

Point Point::operator+(Point p){
    return Point(p.x+x,p.y+y,p.z+z);   
}

bool Point::operator < (Point p){
    return (this->length() < (p).length());
}

// Dot product
double Point::operator* (Point p){
    return x*p.x+y*p.y+z*p.z;   
}

double Point::length(){
    return sqrt(x*x+y*y+z*z);
}

Ray::Ray(){
}

Ray::Ray(Point po, Point vo){
    p = po;
    v = vo;
    v.normalize();
}

Ray Ray::reflect(Point normal, Point m){
    Ray ret;
    double tmp = -(normal*v);
    
    Point vo = v+(normal*tmp*2.0);
    
    Point p = Point(m.x,m.y,m.z);
    return Ray(p,vo);
}

Ray Ray::refract(Point n, Point p, double ior) {
    Point norm = n;
    Point inci = v;
    norm.normalize();
    inci.normalize();

    double normDotI = norm * inci;
    double refrIdx1 = 1;
    double refrIdx2 = ior;

    if (normDotI < 0)      // we are outside surface and about to enter
        normDotI = -normDotI;
    else
    {
        norm = n * -1;          // flip normal because we are inside surface
        swap(refrIdx1, refrIdx2);
    }
    double eta = refrIdx1 / refrIdx2;
    double k = 1 - eta * eta * (1 - normDotI * normDotI);
    
    Point dir;
    if (k < 0) // total internal reflection
        return Ray(Point::Infinite(), Point::Infinite());
    else 
        dir = inci * eta + norm * (eta * normDotI - sqrt(k));
    
    return Ray(p, dir);
}
