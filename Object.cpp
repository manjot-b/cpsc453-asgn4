#include "Object.h"
#include <cmath>

void Object::setMaterial(Material * mat){
    m = mat;   
}

Triangle::Triangle(Point v1,Point v2, Point v3, Point no){
    p1 = v1;
    p2 = v2;
    p3 = v3;
    
    n = no;
    isLight = false;
}

Sphere::Sphere(Point p, double r){
    center = p;
    radius = r;
    
    isLight = false;
}
#define EPS 1E-6

Point Triangle::getIntersection(Ray r){

	// YOUR INTERSECTION CODE HERE.
	// RETURN THE POINT OF INTERSECTION FOR THIS TRIANGLE.
    // Source: Fundementals of Computer Graphics pg 79
    Point p1MinP2 = p1 - p2;
    Point p1MinP3 = p1 - p3;
    Point p1MinOrig = p1 - r.p;

    double a = p1MinP2.x;
    double b = p1MinP2.y;
    double c = p1MinP2.z;

    double d = p1MinP3.x;
    double e = p1MinP3.y;
    double f = p1MinP3.z;

    double g = r.v.x;
    double h = r.v.y;
    double i = r.v.z;

    double j = p1MinOrig.x;
    double k = p1MinOrig.y;
    double l = p1MinOrig.z;

    double detirm = a * (e*i -h*f) + b * (g*f - d*i) + c * (d*h - e*g);
    if (detirm > -EPS && detirm < EPS)      // equals zero
        return Point::Infinite();
    
    double beta = (j * (e*i - h*f) + k * (g*f - d*i) + l * (d*h - e*g)) / detirm;
    if (beta < EPS || beta > 1)
        return Point::Infinite();
    
    double lambda = (i * (a*k - j*b) + h * (j*c - a*l) + g * (b*l - k*c)) / detirm;
    if (lambda < EPS || lambda > 1 - beta)
        return Point::Infinite();

    Point hit = p1 + ((p2 - p1) * beta) + ((p3 - p1) * lambda);
    return hit;
}

Point Triangle::getNormal(Point p){
    Point one = p1-p2;
    Point two = p1-p3;
    Point ret = one.cross(two);
    ret.normalize();
    return ret;
}

Point Sphere::getNormal(Point p){
    Point ret = (p-center);
    
    ret.normalize();
    return ret;
}

Point Sphere::getIntersection(Ray r){

	// YOUR INTERSECTION CODE HERE.
	// RETURN THE POINT OF INTERSECTION FOR THIS SPHERE.
    Point origMinCenter = r.p - center;
    double discrim = (r.v * origMinCenter) * (r.v * origMinCenter) - 
                     (r.v * r.v) * ((origMinCenter * origMinCenter) - radius * radius);
    if (discrim <= EPS)     // less than zero
        return Point::Infinite();

    double sqrtDiscrim = sqrt(discrim);
    double tPos = (-(r.v * origMinCenter) + sqrtDiscrim) /  (r.v * r.v);
    double tNeg = (-(r.v * origMinCenter) - sqrtDiscrim) /  (r.v * r.v);

    // if (tPos < EPS)
    // {
    //     if (tNeg < EPS)
    //         return Point::Infinite(); 

    // }

    double t = tPos < tNeg ? tPos : tNeg;

    Point hit = r.p + (r.v * t);
    return hit;
}

