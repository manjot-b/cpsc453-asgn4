#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <cstdlib>
#include "Object.h"
#include "Light.h"
#include <cmath>
using namespace std;

class Scene {

	// camera parameters.
	// Only a perspective camera is supported, and the location of the image plane is not
	// explicit.
    Point * v;
    Point * n;
    Point * u;
    double fov;

    // the location of the camera
    Point C;

    // Currently this ray tracer only supports square N x N images
    // where N is the number of pixels in one direction.
    int N;
    
    unsigned int indexL,indexO;
public:
    // A container to hold objects
    vector<Object *> objects;
    vector<Light *> lights;
    Point * camera;

    Color background;
    Scene(){
        background = Color(0.0,0.0,0.0,1.0);   
    }
    Scene(Point*,Point*,double,int);
    void startIteration(void);
    Object * getNextObject(void);
    Light * getNextLight(void);
    void addObject(Object *);
    void addLight(Light *);
    void setCamera(Point *);
    void setUpVector(Point *);
    void setDirectionVector(Point *);
    Ray makeRay(double,double);
    static Scene* initTestScene(int, double fov);
    static Scene* customScene(int, double fov);
    // can add your own scene here.
    
};

#endif