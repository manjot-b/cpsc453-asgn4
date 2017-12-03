#include "RayTracer.h"
#include <algorithm>
#include <iostream>

using namespace std;

RayTracer::RayTracer(Scene * s, int maxd, int sm){
  scene = s;
  maxdepth = maxd;
  samples = sm;
}

// This function determines the closest object that a ray intersects.
// The getIntersection() method is polymorphic. Please provide implementations
// for all the objects in your scene (see Object.h and Object.cpp).
Object * RayTracer::intersect(Ray r){
  scene->startIteration();
  Object * current = NULL;
  Object * minObject = NULL;
  Point inter;
  //Initialize min to infinite point;
  Point min = Point::Infinite();
  while((current = scene->getNextObject()) != NULL){
    inter = current->getIntersection(r);
    if((inter - r.p).length() > 1E-6){
      if((inter-r.p).length()  < (min-r.p).length()){
        min = inter;
        minObject = current;
      }
    }
  }
  return minObject;
}

// Trace a ray recursively
Color RayTracer::trace(Ray r, int depth){
  Color rad=Color(0.0,0.0,0.0,0.0);
  
  // YOUR CODE FOR RECURSIVE RAY TRACING GOES HERE
  Object *inter;
  inter = intersect(r);
  if (inter == NULL)
    return rad;

  Point interPt;
  interPt = inter->getIntersection(r);
  rad = rad + Phong(inter->getNormal(interPt), interPt, r, inter->getMaterial(), inter);

  return rad;
}

// Local Phong illumination at a point.
Color RayTracer::Phong(Point normal, Point p, Ray r, Material * m, Object * o){
  Color totalLight = Color(0.0, 0.0, 0.0, 1.0);
  
  // YOUR CODE HERE.
  // There is ambient lighting irrespective of shadow.
  // Specular-diffuse lighting only if the point is not in shadow
  
  // Remember, you need to account for all the light sources.
  
  double intensity = 0.65; // 1.0 for r g and b
  
  // DIFFUSE and SPECULAR
  Color diffuse = Color(0.0, 0.0, 0.0, 1.0);
  Color specular = Color(0.0, 0.0, 0.0, 1.0);
  normal.normalize();
  
      
  for (unsigned int i = 0; i < scene->lights.size(); i++)
  {
    // DIFFUSE
    Point toLight = scene->lights[i] - p;
    toLight.normalize();
    diffuse = diffuse + m->diffuse  * intensity * max(0.0, normal * toLight);
  
    // SPECULAR
    Point reflected = normal * 2 * (toLight * normal) - toLight;
    Point toCamera = r.v * -1;
    toCamera.normalize();
    double specFactor = max( reflected * toCamera, 0.0);
    double dampedFactor = pow(specFactor, m->shininess);
    specular = specular + m->specular * intensity * dampedFactor; 
  }

  //AMBIENT
  Color ambient = m->ambient * intensity;
  
  totalLight = ambient + diffuse + specular;
  return totalLight;
}


// This function generates point on the image plane and starts a trace 
// through them.
// Grid supersampling is also implemented.
Color RayTracer::calculate(int x, int y){
  Color c = Color(0.0,0.0,0.0,0.0);
  for(int i = 1; i <= samples; i++){
    for(int j = 1; j <= samples; j++){
      double one, two;
      // We subtract 0.5 so that the (u,v)-origin is at the
      //center of the image plane.
      one = double(x)-0.5+double(i)/double(samples);
      two = double(y)-0.5+double(j)/double(samples);
      Ray r = scene->makeRay(one,two);
      c = c+trace(r,0);
    }
  }
  c = c*(1.0/double(samples*samples));
  return c;
}

