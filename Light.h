#ifndef LIGHT_H
#define LIGHT_H

#include "Color.h"
#include "Geometry.h"

class Light 
{
public:
    Color intensity;
    Point pos;
    
    Light(Point p, Color c)
    {
        pos = p;
        intensity = c;
    }
};

#endif