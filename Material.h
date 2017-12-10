#ifndef COLOR_H
#include "Color.h"
#endif
#ifndef GEOMETRY_H
#include "Geometry.h"
#endif

// An enumerated type to represent different types of materials.
enum Type{
    REFLECTIVE,
    DIFFUSE,
    REFRACTIVE
};

// A class that represents material properties.
// This can be extended to represent textured materials.
class Material {
    
public:
    Color diffuse, ambient, specular;
    double kr, kt, kd, ior, shininess;
    Type type; 
    // this is for materials to decide!
    Material(){
        kr = 0.0;       // reflectivity
        kt = 0.0;       // transmissive (refraction)
        ior = 1.0;      // index of refraction
        kd = 0.0;
        shininess = 1;  // for specular
        ior = 1;        // index of refraction
    }
    virtual Color getAmbient(Point p){ return ambient;}
    Color getDiffuse(Point p){return diffuse;}
    Color getSpecular(Point p){return specular;}
    void setAmbient(Color c){ambient = c;}
    void setSpecular(Color c){specular = c;}
    void setDiffuse(Color c){diffuse = c;}
};
