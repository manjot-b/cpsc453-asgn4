#include "Object.h"
#include <cmath>

#include <iostream>
using namespace std;

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

Point Triangle::getIntersection(Ray r)
{
    // Moller trumbor triangle intersection algorithm
    Point edge1, edge2, h, s, q;
    float a,f,u,v;
    edge1 = p2 - p1;
    edge2 = p3 - p1;
    h = r.v.cross(edge2);
    a = edge1 * h;
    if (a > -EPS && a < EPS)
        return Point::Infinite();
    f = 1/a;
    s = r.p - p1;
    u = f * (s * h);
    if (u < 0.0 || u > 1.0)
        return Point::Infinite();
    q = s.cross(edge1);
    v = r.v * q * f;
    if (v < 0.0 || u + v > 1.0)
        return Point::Infinite();
    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = edge2 * q * f;
    if (t > EPS) // ray intersection
    {
        Point hit = r.p + r.v * t; 
        return hit;
    }
    else // This means that there is a line intersection but not a ray intersection.
        return Point::Infinite();
}

/*Point Triangle::getIntersection(Ray r){

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
    if (abs(detirm) < EPS)      // equals zero
        return Point::Infinite();
    
    double beta = (j * (e*i - h*f) + k * (g*f - d*i) + l * (d*h - e*g)) / detirm;
    if (beta < EPS || beta - 1 > EPS)
        return Point::Infinite();
    
    double lambda = (i * (a*k - j*b) + h * (j*c - a*l) + g * (b*l - k*c)) / detirm;
    if (lambda < EPS || lambda + beta - 1 > EPS)
        return Point::Infinite();

    double t = -(f * (a*k -j*b) + e * (j*c - a*l) + d * (b*l - k*c) / detirm);
    // cout << "T " << t << endl;

    if (t < EPS)
        return Point::Infinite();

    // Point hit = p1 + (p2 - p1) * beta + (p3 - p1) * lambda;
    Point hit = r.p + r.v * t;
    return hit;
}*/

Point Triangle::getNormal(Point p){
    Point one = p1-p2;
    Point two = p1-p3;
    Point ret = one.cross(two);
    ret.normalize();
    return ret;

    // n.normalize();
    // return n;
}

Point Sphere::getNormal(Point p){
    Point ret = (p-center);
    
    ret.normalize();
    return ret;
}

Point Sphere::getIntersection(Ray r)
{
    // at^2 + bt + c 
    Point origMinCenter = r.p - center;
	double a = r.v * r.v;
    double b = r.v * origMinCenter * 2;
    double c = origMinCenter * origMinCenter - radius*radius;

    double discr = b * b - 4 * a * c;
    
    double t, t1, t2;
    if (discr < 0)
        return Point::Infinite();
    else if (discr < EPS)
        t1 = t2 = -0.5 * b / a;
    else
    {
        double q = b > 0 ? 
            -0.5 * (b + sqrt(discr)) : 
            -0.5 * (b - sqrt(discr));
        t1 = q / a;
        t2 = c / q;
    }

    if (t1 < EPS && t2 < EPS)
        return Point::Infinite();
    else if (t1 < EPS)
        t = t2;
    else if (t2 < EPS)
        t = t1;
    else
        t = t1 < t2 ? t1 : t2;

    Point hit = r.p + (r.v * t);
    return hit;
}

// Point Sphere::getIntersection(Ray r){

// 	// YOUR INTERSECTION CODE HERE.
// 	// RETURN THE POINT OF INTERSECTION FOR THIS SPHERE.
//     Point origMinCenter = r.p - center;
//     double discrim = (r.v * origMinCenter) * (r.v * origMinCenter) - 
//                      (r.v * r.v) * ((origMinCenter * origMinCenter) - radius * radius);
//     if (discrim < EPS)     // less than zero
//         return Point::Infinite();

//     double sqrtDiscrim = sqrt(discrim);
//     double tPos = (-(r.v * origMinCenter) + sqrtDiscrim) /  (r.v * r.v);
//     double tNeg = (-(r.v * origMinCenter) - sqrtDiscrim) /  (r.v * r.v);

//     double t;
    
//     cout << " pos " << tPos << " neg " << tNeg << " ";
//     if (tPos < EPS && tNeg < EPS)
//         return Point::Infinite();
//     else if (tPos < EPS)
//         t = tNeg;
//     else if (tNeg < EPS)
//         t = tPos;
//     else
//         t = tPos < tNeg ? tPos : tNeg;

//     cout << "T " << t << endl; 
//     Point hit = r.p + (r.v * t);
//     return hit;
// }

